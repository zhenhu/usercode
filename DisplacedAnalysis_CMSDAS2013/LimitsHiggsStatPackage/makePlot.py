#/usr/bin/python
########################################################################
# Calculate limits and make plots.
# Should be run only once CRAB jobs produced by makeJob.py have run
########################################################################

from SignalSampleInfo import *
from convertLimits_rootToTxt import *
import sys
import os
import glob
import subprocess

# Disable buffering of STDOUT to preserve order of print statements
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)

samples = getSignalSampleInfo()

leptons = ["Muons", "Electrons"]

# For observed limits, set assumed apriori background uncertainty to infinity
# For expected limits, set it to finite number coming from fit to lifetime distribution
aprioriBkgErr = [ "Normal", "Infinity"]

start_dir = os.getcwd();

print "=== Assumed luminosity = %f/pb (muons) and %f\/pb (electrons)===\n"  %( getLumi("Muons"), getLumi("Electrons") ) 

# Create directory to contain limit plots
if os.path.exists('result'):
       istat = subprocess.call('rm -r result', shell=True)   
os.mkdir('result')

# Loop over all signal samples

for l in leptons:

   # Create directories for .txt files containing limit results (all mass points & lifetimes in same directory).
   txt_name = '%s/result/%s_txt/'                   %(start_dir, l)
   os.mkdir(txt_name)

   for s in samples:

       for tIndex, t in enumerate(s.cTauLoopValues):

              # Directory to contain .root files containing limits (in complicated format) produced by Higgs stats code.
              result_name     = '%s/result/%s_%i_%i_%s/'                %(start_dir, l, s.MH, s.MX, t)

              # Create directory for plots and limits
              os.mkdir(result_name)
              os.chdir(result_name)

              # Create file to contain printout from combine command (for debugging)
              cfile = open("combine.output", 'w', 0)

              # Use infinite apriori background uncertainty for observed limits, and finite apriori uncertainty for expected limits
              for apriori in aprioriBkgErr:          

                     # Input directory to CRAB jobs
                     job_name        = '%s/job/%s_%i_%i_%s_%s/'                %(start_dir, l, s.MH, s.MX, t, apriori)
                     # Output directory from CRAB jobs
                     job_output_name = '%s/job_output/%s_%i_%i_%s_%s/res/'     %(start_dir, l, s.MH, s.MX, t, apriori)

                     print "\n ======= Processing %s =======\n"    %(job_name)

                     os.chdir(job_output_name)

                     # If user didn't do "multicrab -getoutput", must unpack .tgz files produced by crab.
                     if len(glob.glob("TestGrid*.root")) == 0 and len(glob.glob("out_files_*.tgz")) > 0:

                            for fname in glob.glob("out_files_*.tgz"):
                                   istat = subprocess.call('tar -xzf %s' %(fname), shell=True)

                     os.chdir(result_name)
                            
                     # Merge root files produced by CRAB jobs
                     cmd = "hadd -f sum.root %s/TestGrid*.root"    %(job_output_name)
                     istat = subprocess.call(cmd, shell=True, stdout=open(os.devnull, "w"))
                     if istat != 0:
                            sys.exit("ERROR: whilst executing %s" %cmd)

                     # Calculate limits (directing printout to a file)
                     cmd = "cp -f %s/combine.root %s" %(job_name, result_name)
                     istat = subprocess.call(cmd, shell=True)

                     oldout = sys.stdout
                     sys.stdout = cfile

                     if apriori == "Infinity":
                            print "\n\n --- Calculating observed limit --- \n"
                            cmd = "combine combine.root -v1 -m 0 -M HybridNew -U --fullGrid --grid=sum.root"
                            istat = subprocess.call(cmd, shell=True, stdout=cfile)       

                     elif apriori == "Normal":
                            fracs = ('0.500', '0.840', '0.160', '0.975', '0.025')
                            for frac in fracs:
                                   print "\n\n --- Calculating expected limits for %s band ---\n"  %frac
                                   cmd = "combine combine.root -v1 -m 0 -M HybridNew -U --fullGrid --expectedFromGrid %s --grid=sum.root"   %(frac)
                                   istat = subprocess.call(cmd, shell=True, stdout=cfile)
                                   if istat != 0:
                                          sys.exit("ERROR: whilst executing %s" %cmd)

                     sys.stdout = oldout
                     subprocess.call("cat combine.output", shell=True)

              cfile.close()

              # Convert all limits from .root to .txt format, so can be read by Paul's plotter.
              limitsRootFiles = [ 'higgsCombineTest.HybridNew.mH0.root' ] # observed limit
              for frac in fracs:
                     limitsRootFiles.append('higgsCombineTest.HybridNew.mH0.quant%s.root'  %frac)
              convertLimits_rootToTxt( s, l, tIndex, limitsRootFiles , txt_name)  

              os.chdir(start_dir)

# Call Paul's script to make the plots for each Higgs mass and lepton species.
higgs_masses_list = []
for s in samples:
       higgs_masses_list.append(s.MH)
higgs_masses = (higgs_masses_list)
print higgs_masses

for mH in higgs_masses:

       for l in leptons:

              os.chdir('%s/result/'  %start_dir)

              cmd = 'cp ../../LimitsRooStats/tdrstyle.C . ;'
              cmd += 'python %s/PlotLimitsLifetimeExpected.py %s %i CLsIan'  %(start_dir, l, mH)
              print '-- ',cmd
              istat = subprocess.call(cmd, shell=True)
              if istat != 0:
                     sys.exit("ERROR: whilst executing %s" %cmd)

os.chdir(start_dir)

print "\n Output plots can be found in result/limits*.pdf or limits*.png\n"
