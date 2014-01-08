#/usr/bin/python
###############################################################################################
# Calculate limits and make plots.
# Should be run only once CRAB jobs produced by makeJob.py have run
#
# This is used to get limits from the mass spectrum.
#
# If you have already calculated the limits by previously running
# makePlot.py, and simply want change the plot style, you
# can speed this up by setting recalcLimits = False below.
#
# Call makePlot.py with argument 1 (2) to get limits on sigma*BR (sigma*BR*acceptance).
# Or argument 11 (12) to simply put limit on mean number of signal events passing cuts.
###############################################################################################

from SignalSampleInfo import *
from convertLimits_rootToTxt import *
import sys
import os

import glob
import subprocess

#===========================================================================================================

#=== Set this to false if you calculated the limits already and just want to change the plotting style.
recalcLimits = True

#===========================================================================================================

# Disable buffering of STDOUT to preserve order of print statements
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)

# Get job options.
jobOpt = JobOptions()

if jobOpt.doNeutralinoLimits:
  sys.exit("ERROR: Limits for neutralinos not supported until mass resolutions become available")

# Note "combine" command options corresponding to CLs or Bayesian.
if jobOpt.limitMethod == "CLs":
  limitMethodCall = "HybridNew"
elif jobOpt.limitMethod == "Bayesian":
  limitMethodCall = "MarkovChainMC"
else:
  sys.exit("ERROR: Unknown limit method option %s" %(jobOpt.limitMethod) )

from optparse import OptionParser
parser = OptionParser()
(options,args) = parser.parse_args()

# Note if limits corrected for acceptance are wanted.
if len(args)!=1:
    print "Please call makePlot.py with argument 1 (2) to get limits corrected (uncorrected) for acceptance."
    print "Or argument 11 (12) to simply put limit on mean number of signal events passing cuts."
    sys.exit(1)

acceptanceOption = int(args[0])

# Create job directory name and directory for output that distinguish acceptance option & limit method.
if acceptanceOption%10 == 1:
    if jobOpt.doNeutralinoLimits:
       jobDirName = "job_%s_neutralino"              %(jobOpt.limitMethod)
       jobOutName = "job_output_%s_neutralino"       %(jobOpt.limitMethod)
       resultDirName = "result_%s_neutralino"        %(jobOpt.limitMethod)
    else:
       jobDirName = "job_%s"              %(jobOpt.limitMethod)
       jobOutName = "job_output_%s"       %(jobOpt.limitMethod)
       resultDirName = "result_%s"        %(jobOpt.limitMethod)
       
elif acceptanceOption%10 == 2:
    if jobOpt.doNeutralinoLimits:
       jobDirName = "job_acc_%s_neutralino"          %(jobOpt.limitMethod)
       jobOutName = "job_output_acc_%s_neutralino"   %(jobOpt.limitMethod)
       resultDirName = "result_acc_%s_neutralino"    %(jobOpt.limitMethod)
    else:
       jobDirName = "job_acc_%s"          %(jobOpt.limitMethod)
       jobOutName = "job_output_acc_%s"   %(jobOpt.limitMethod)
       resultDirName = "result_acc_%s"    %(jobOpt.limitMethod)
else:
    sys.exit("ERROR: Unknown acceptance option %i" %(acceptanceOption) )

samples = getSignalSampleInfo()

leptons = ["Muons", "Electrons"]

# For observed limits, set assumed apriori background uncertainty to infinity
# For expected limits, set it to finite number coming from fit to lifetime distribution
limitTypeList = [ "Expected", "Observed" ]

start_dir = os.getcwd();

print "=== Assumed luminosity = %f/pb (muons) and %f/pb (electrons)===\n"  %( jobOpt.getLumi("Muons"), jobOpt.getLumi("Electrons") ) 

if recalcLimits:

       # Create directory to contain limit plots
       if os.path.exists(resultDirName):
              istat = subprocess.call("rm -r %s" %resultDirName , shell=True)   
       os.mkdir(resultDirName)

       # Loop over all signal samples

       for l in leptons:

          # Create directories for .txt files containing limit results (all mass points & lifetimes in same directory).
          txt_name = '%s/%s/%s_txt/'                   %(start_dir, resultDirName, l)
          os.mkdir(txt_name)

          for s in samples:

              if s.acceptance == acceptanceOption%10: 

                for tIndex, t in enumerate(s.cTauScaleLoopValues):

                       if not s.enoughMC(l, tIndex, jobOpt.loopOverCTau):
                              continue # Skip this point if not enough MC statistics.


                       # Directory to contain .root files containing limits (in complicated format) produced by Higgs stats code.
                       result_name     = '%s/%s/%s_%i_%i_%s/'                %(start_dir, resultDirName, l, s.MH, s.MX, t)

                       # Create directory for plots and limits
                       os.mkdir(result_name)
                       os.chdir(result_name)

                       # Use infinite apriori background uncertainty for observed limits, and finite apriori uncertainty for expected limits
                       for limitType in limitTypeList:          

                              # Create file to contain printout from combine command (for debugging)
                              cfile = open("combine_%s.output" %limitType, 'w', 0)

                              oldout = sys.stdout
                              sys.stdout = cfile

                              # Input directory to CRAB jobs
                              job_name        = '%s/%s/%s_%i_%i_%s_%s/'         %(start_dir, jobDirName, l, s.MH, s.MX, t, limitType)
                              # Output directory from CRAB jobs
                              job_output_name = '%s/%s/%s_%i_%i_%s_%s/res/'     %(start_dir, jobOutName, l, s.MH, s.MX, t, limitType)

                              print "\n ======= Processing %s =======\n"    %(job_name)

                              os.chdir(job_output_name)

                              # If user didn't do "multicrab -getoutput", must unpack .tgz files produced by crab.
                              if len(glob.glob("TestGrid*.root")) == 0 and len(glob.glob("out_files_*.tgz")) > 0:

                                     for fname in glob.glob("out_files_*.tgz"):
                                            istat = subprocess.call('tar -xzf %s' %(fname), shell=True)

                              os.chdir(result_name)

                              # Backup root file containing cards and input data used in GRID jobs.
                              cmd = "cp -f %s/combine.root %s/combine_%s.root" %(job_name, result_name, limitType)
                              istat = subprocess.call(cmd, shell=True)
                              if istat != 0:
                                     sys.exit("ERROR: whilst executing %s" %cmd)

                              if jobOpt.limitMethod == "CLs":

                                  # Merge root files produced by CRAB jobs
                                  cmd = "hadd -f sum_%s.root %s/TestGrid*.root"    %(limitType, job_output_name)
                                  istat = subprocess.call(cmd, shell=True, stdout=open(os.devnull, "w"))
                                  if istat != 0:
                                         sys.exit("ERROR: whilst executing %s" %cmd)

                                  if limitType == "Observed":
                                         print "\n\n --- Calculating observed %s limit --- \n" %limitMethod
                                         cmd = "combine combine_%s.root -v2 -m 0 -M %s -U --fullGrid --frequentist --rule CLs --testStat LEP --grid=sum_%s.root"  %(limitType, limitMethodCall, limitType)
                                         print cmd,"\n"
                                         istat = subprocess.call(cmd, shell=True, stdout=cfile)
                                         if istat != 0:
                                             sys.exit("ERROR: whilst executing %s" %cmd)

                                  elif limitType == "Expected":
                                         for frac in jobOpt.fracs:
                                             print "\n\n --- Calculating expected %s limits for %.3f band ---\n"  %(limitMethod, frac)
                                             cmd = "combine combine_%s.root -v2 -m 0 -M %s -U --fullGrid --frequentist --rule CLs --testStat LEP --expectedFromGrid %.3f --grid=sum_%s.root"   %(limitType, limitMethodCall, frac, limitType)
                                             print cmd,"\n"
                                             istat = subprocess.call(cmd, shell=True, stdout=cfile)
                                             if istat != 0:
                                                 sys.exit("ERROR: whilst executing %s" %cmd)


                              elif jobOpt.limitMethod == "Bayesian":

                                  # Limit calculation was done by makeJob.py, so just copy results here. (Should be just one file).
                                  if limitType == "Observed":
                                      cmd = "cp %s/higgsCombineTest.*.root higgsCombineTest.%s.mH0.root"  %(job_output_name, limitMethodCall)
                                  elif limitType == "Expected":
                                      cmd = "cp %s/higgsCombineTest.*.root higgsCombineTest.%s.mH0.quantAll.root"  %(job_output_name, limitMethodCall)

                                  print cmd,"\n"
                                  istat = subprocess.call(cmd, shell=True, stdout=cfile)
                                  if istat != 0:
                                      sys.exit("ERROR: whilst executing %s" %cmd)


                              sys.stdout = oldout
                              subprocess.call("cat combine_%s.output" %limitType, shell=True)

                              cfile.close()

                       # Convert all limits from .root to .txt format, so can be read by Paul's plotter.

                       # observed limit
                       obsLimitRootFile = [ "higgsCombineTest.%s.mH0.root" %(limitMethodCall) ] 
                       expLimitRootFiles = []
                       if jobOpt.limitMethod == "CLs":
                           # expected limit for each quantile
                           for frac in jobOpt.fracs:
                                  expLimitsRootFiles.append("higgsCombineTest.%s.mH0.quant%.3f.root" %(limitMethodCall, frac) )
                       elif jobOpt.limitMethod == "Bayesian":
                           # expected limit for each toy, all in one file.
                           expLimitRootFiles.append("higgsCombineTest.%s.mH0.quantAll.root" %(limitMethodCall) )

                       subtractControl = False # efficiency is simply that in signal region.
                       convertLimits_rootToTxt( s, l, tIndex, obsLimitRootFile, expLimitRootFiles, acceptanceOption, subtractControl, txt_name )  

                       os.chdir(start_dir)

# Call Paul's script to make the plots for each Higgs mass and lepton species.
higgs_masses_list = []
for s in samples:
         if s.acceptance == acceptanceOption%10: 
                higgs_masses_list.append(s.MH)
higgs_masses = list(set((higgs_masses_list)))
print higgs_masses

if jobOpt.doNeutralinoLimits:

       for l in leptons:

              os.chdir('%s/%s/'  %(start_dir, resultDirName) )

              getSigmaBRacc = (acceptanceOption%10 == 2)
              cmd = 'cp ../../LimitsRooStats/tdrstyle.C . ;'
              cmd += 'python %s/PlotLimitsLifetimeExpected.py %s %i %i %i'  %(start_dir, l, not jobOpt.doNeutralinoLimits, -1, getSigmaBRacc)
              print '-- ',cmd
              istat = subprocess.call(cmd, shell=True)
              if istat != 0:
                     sys.exit("ERROR: whilst executing %s" %cmd)

else:

   for mH in higgs_masses:

       for l in leptons:

              os.chdir('%s/%s/'  %(start_dir, resultDirName) )

              getSigmaBRacc = (acceptanceOption%10 == 2)
              cmd = 'cp ../../LimitsRooStats/tdrstyle.C . ;'
              cmd += 'python %s/PlotLimitsLifetimeExpected.py %s %i %i %i'  %(start_dir, l, not jobOpt.doNeutralinoLimits, mH, getSigmaBRacc)
              print '-- ',cmd
              istat = subprocess.call(cmd, shell=True)
              if istat != 0:
                     sys.exit("ERROR: whilst executing %s" %cmd)

os.chdir(start_dir)

print "\n Output plots can be found in %s/limits*.png and limits*.pdf\n" %resultDirName

if not recalcLimits:
       print "\n WARNING: you used option NOT to recalculate limits, but instead to use previous results\n"

print "\n PLEASE NOTE: you calculated %s limits\n" %(jobOpt.limitMethod)

if jobOpt.doNeutralinoLimits:

       print "\n PLEASE NOTE: you calculated limits for NEUTRALINOS\n"
  
