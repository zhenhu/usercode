#/usr/bin/python
#################################################################################################
# This creates the card file and workspace for the upper limit problem.
# It then creates the crab & multicrab cfgs to submit them.
#
# This is used to get limits from the mass spectrum
#
# call makeJob.py with argument 1 (2) to get limits corrected (uncorrected) for acceptance.
#################################################################################################

from SignalSampleInfo import *     # Includes JobOptions class.
from MakeWorkspace import *
import sys
import os
import subprocess

#===========================================================================================================

# Use PBS local batch queue instead of normal CRAB batch queues ?
USE_PBS = True

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
    print "Please call makeJob.py with argument 1 (2) to get limits corrected (uncorrected) for acceptance."
    sys.exit(1)

acceptanceOption = int(args[0])

# Create job directory name and directory for output that distinguish acceptance option & limit method.
if acceptanceOption == 1:
    if jobOpt.doNeutralinoLimits:
        jobDirName = "job_%s_neutralino"              %(jobOpt.limitMethod)
        jobOutName = "job_output_%s_neutralino"       %(jobOpt.limitMethod)
    else:
        jobDirName = "job_%s"              %(jobOpt.limitMethod)
        jobOutName = "job_output_%s"       %(jobOpt.limitMethod)
        
elif acceptanceOption == 2:
    if jobOpt.doNeutralinoLimits:
        jobDirName = "job_acc_%s_neutralino"          %(jobOpt.limitMethod)
        jobOutName = "job_output_acc_%s_neutralino"   %(jobOpt.limitMethod)
    else:
        jobDirName = "job_acc_%s"          %(jobOpt.limitMethod)
        jobOutName = "job_output_acc_%s"   %(jobOpt.limitMethod)
else:
    sys.exit("ERROR: Unknown acceptance option %i" %(acceptanceOption) )

# Get information about signal samples (efficiency, background etc.)
samples = getSignalSampleInfo()

leptons = ["Muons", "Electrons"]

# For observed limits, set assumed apriori background uncertainty to infinity
# For expected limits, set it to finite number coming from fit to lifetime distribution
limitTypeList = [ "Expected", "Observed" ]

# Create directory for jobs
if os.path.exists("%s" %jobDirName):
       istat = subprocess.call("rm -r %s" %jobDirName, shell=True)   
os.mkdir("%s" %jobDirName)

# Loop over all signal samples
for sIndex, s in enumerate(samples):

  if s.acceptance == acceptanceOption:

     for l in leptons:

         for tIndex, t in enumerate(s.cTauScaleLoopValues):

                if not s.enoughMC(l, tIndex, jobOpt.loopOverCTau):
                       continue # Skip this point if not enough MC statistics.

                debug = (sIndex == 0 and tIndex == 0)

                # Create RooWorkspace and store in workspace.root (independent of acceptance option)
                print "-- Creating RooWorkSpace", debug
                MakeWorkspace(s, l, tIndex, debug, debug)

                # Produce two sets of limits with infinite (=observed limit) / finite (=expected limit) apriori background normalisation uncertainty
                for limitType in limitTypeList:

                       # Make directory for this signal sample
                       subDirName = '%s/%s_%i_%i_%s_%s'    %(jobDirName, l, s.MH, s.MX, t, limitType)
                       print "\n ===== Creating directory %s ===== \n"   %(subDirName)
                       os.mkdir(subDirName)

                       # Copy workspace just created above into it (don't move, since both apriori options want it).
                       cmd  = 'cp workspace.root %s;'   %(subDirName)
                       cmd += 'cp workspace.txt %s'     %(subDirName)
                       istat = subprocess.call(cmd, shell=True)

                       # Get input card file combine.txt for 'combine' command and set parameters in it.
                       print "-- Creating card file"

                       effi_relerrs = s.effi_relerrs[l]
                       if jobOpt.loopOverCTau:
                              effi_relerr_use = effi_relerrs[tIndex]
                       else:
                              # If not looping over exotica lifetime (to save CPU), then take uncertainty on
                              # efficiency equal to its median value, averaged over all lifetimes.
                              effi_relerr_use = s.getMedianEffiRelErr(l)
                              print "DEBUG EFFI ",effi_relerr_use,"\n"
                       # Prevent relative error being too large, since it would crash limit code.
                       effi_relerr_use = min(effi_relerr_use, jobOpt.maxRelEffErr) 
                       print "effi_relerr ",effi_relerr_use
                       # Determine number of backgrounds being used.
                       if s.backgrPdfOption == 1 or s.backgrPdfOption == 2:
                              numBackgrounds = 2
                       elif s.backgrPdfOption == 3:
                              numBackgrounds = 1

                       cmd  = 'cp combine_template_%ibackground.txt %s/combine.txt; ' %(numBackgrounds, subDirName)
                       cmd += 'sed -i "s/effi_relerrTTT/%f/g"       %s/combine.txt; '   %(1 + effi_relerr_use, subDirName)

                       if numBackgrounds == 2: 
                           # Both Z and non-Z background in this case.

                           # Convert apriori total background prediction to predictions for Z0 and non-Z0 backgrounds.
                           bkgZ0        = s.bkg[l]     * s.paramZ0Frac[l]
                           bkgZ0_err    = s.bkg_err[l] * s.paramZ0Frac[l]
                           bkgOther     = s.bkg[l]     * (1 - s.paramZ0Frac[l])
                           bkgOther_err = s.bkg_err[l] * (1 - s.paramZ0Frac[l])
                           # Cards expect relative, not absolute background uncertainty. (And an additonal +1 offset).
                           # Also must avoid large relative uncertainties ( > 3 ), since "combine" can become unstable for them.
                           bkgZ0        = max(bkgZ0   , bkgZ0_err    / 3.)
                           bkgZ0_relerr = bkgZ0_err    / bkgZ0
                           # Increase uncertainty to infinity if requested.
                           # In that case, use lnU error distribution, as lnN is unstable for large relative uncertainty.
                           if limitType == "Expected":
                                  bkgOther        = max(bkgOther, bkgOther_err / 3.)
                                  bkgOther_relerr = bkgOther_err / bkgOther
                                  bkgOther_errType = 'lnN'
                           elif limitType == "Observed":
                                  bkgOther        = max(1., bkgOther)
                                  bkgOther_relerr = 99.999 * bkgOther
                                  bkgOther_errType = 'lnU'                     
                           cmd += 'sed -i "s/bkgZ0TTT/%f/g"             %s/combine.txt; '   %(bkgZ0, subDirName)
                           cmd += 'sed -i "s/bkgZ0_relerrTTT/%f/g"      %s/combine.txt; '   %(1 + bkgZ0_relerr, subDirName)
                           cmd += 'sed -i "s/bkgOtherTTT/%f/g"          %s/combine.txt; '   %(bkgOther, subDirName)
                           cmd += 'sed -i "s/bkgOther_relerrTTT/%f/g"   %s/combine.txt; '   %(1 + bkgOther_relerr, subDirName)
                           cmd += 'sed -i "s/bkgOther_errTypeTTT/%s/g"  %s/combine.txt; '   %(bkgOther_errType, subDirName)

                       elif numBackgrounds == 1:
                           # All background defined as "other" in this case.
                           bkgOther     = s.bkg[l]    
                           bkgOther_err = s.bkg_err[l]
                           # Cards expect relative, not absolute background uncertainty. (And an additonal +1 offset).
                           # Also must avoid large relative uncertainties ( > 3 ), since "combine" can become unstable for them.
                           # Increase uncertainty to infinity if requested.
                           # In that case, use lnU error distribution, as lnN is unstable for large relative uncertainty.
                           if limitType == "Expected":
                                  bkgOther        = max(bkgOther, bkgOther_err / 3.)
                                  bkgOther_relerr = bkgOther_err / bkgOther
                                  bkgOther_errType = 'lnN'
                           elif limitType == "Observed":
                                  bkgOther        = max(1., bkgOther)
                                  bkgOther_relerr = 99.999 * bkgOther
                                  bkgOther_errType = 'lnU'                     
                           cmd += 'sed -i "s/bkgOtherTTT/%f/g"          %s/combine.txt; '   %(bkgOther, subDirName)
                           cmd += 'sed -i "s/bkgOther_relerrTTT/%f/g"   %s/combine.txt; '   %(1 + bkgOther_relerr, subDirName)
                           cmd += 'sed -i "s/bkgOther_errTypeTTT/%s/g"  %s/combine.txt; '   %(bkgOther_errType, subDirName)

                       # Put in correct relative systematic uncertainty on resonance width.
                       cmd += 'sed -i "s/widthSysTTT/%f/g"          %s/combine.txt; '   %(s.widthSys[l], subDirName)
                       istat = subprocess.call(cmd, shell=True)              
                       cmd += 'cat %s/combine.txt'       %(subDirName)    # Just to check it is OK

                       # Merge workspace and combine.txt into a single file combine.root
                       cmd = '$CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/scripts/text2workspace.py %s/combine.txt -b -o %s/combine.root'   %(subDirName, subDirName)
                       istat = subprocess.call(cmd, shell=True)
                       if istat != 0:
                              sys.exit("ERROR: whilst executing %s" %cmd)

                       # Prefix of CRAB job file to be created.
                       crabFileName = "%s/TestGrid"  %(subDirName)

                       # Create CRAB job to calculate limits.
                       # It just creates scripts that refer to combine.root by name, it does not read it in.
                       print "-- Creating CRAB job (PBS = %s)"   %(USE_PBS)
                       min_r = 0  # This should encompass the possible expected and observed limits on number of events passing cuts.
                       max_r = jobOpt.maxPredictedLimit
                       if jobOpt.limitMethod == "CLs":
                           npoints = 50  # The accuracy achieved will be rather better than (max_r - min_r)/npoints
                           njobs = 1 # If more than 1, the nevents will be split into several jobs to run faster.
                           nevents = 1 # I think nevents * ntoys is effective number of toys
                           # Do not set nevents > 1, as this results in forks being used, and these do not work
                           # See https://hypernews.cern.ch/HyperNews/CMS/get/higgs-combination/192/1/1/1.html
                           ntoys = 2500
                           # Unstable if background systematic large.
                           #cmd = '$CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/test/makeGridUsingCrab.py combine.root %i %i -v3 -r -m 0 -O "-U --fullBToys" -n %i -j %i -t %i -T %i'   %(min_r, max_r, npoints, njobs, nevents, ntoys)
                           # better (N.B. "combine" has a buffering error, which results in loss of print output
                           # if verbosity level set to 2 or less).
                           cmd = '$CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/test/makeGridUsingCrab.py combine.root %i %i -v3 -r -m 0 -O "-U --frequentist --rule CLs --testStat LEP" -n %i -j %i -t %i -T %i --out %s'   %(min_r, max_r, npoints, njobs, nevents, ntoys, crabFileName)
                           istat = subprocess.call(cmd, shell=True)
                           if istat != 0:
                              sys.exit("ERROR: whilst executing %s" %cmd)

                       elif jobOpt.limitMethod == "Bayesian":
                           # The makeGridUsingCrab.py script is intended for use with CLs method, so must hack output to use it with Bayesian.
                           cmd = '$CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/test/makeGridUsingCrab.py combine.root 0 0 -j 1 -t 1 --out %s'  %(crabFileName)
                           istat = subprocess.call(cmd, shell=True)
                           if istat != 0:
                              sys.exit("ERROR: whilst executing %s" %cmd)
                           f = open("%s.sh" %crabFileName ,'w')
                           ntoys = 100 # for expected limit (If want 95% intervals, then ntoys & 5% should be >> 1).
                           if limitType == "Observed":
                             ntoys = 0 # observed limit needs no toys
                           f.write( '#!/bin/bash \n' )
                           f.write( 'set -x \n' ) # echo output for debugging
                           f.write( "./combine combine.root -v3 -m 0 -H ProfileLikelihood -M %s -t %i \n" %(limitMethodCall, ntoys) )
                           f.write( 'ls -l \n' )
                           f.write( 'echo "## Done at $(date)"\n')
                           f.close()

                       if USE_PBS:
                          # If requested, modify CRAB cfg to use PBS queues.
                          cmd = 'sed -i "s/scheduler = glite/scheduler = pbs/g"   %s.cfg'  %crabFileName 
                          istat = subprocess.call(cmd, shell=True)
                          f = open('%s.cfg' %crabFileName ,'a')
                          f.write( "\n" )
                          f.write( "[PBS] \n" )
                          f.write( "queue=prod \n" )
                          f.write( "resources=cput=12:00:00,walltime=12:00:00,mem=1gb \n" )
                          f.close()
                       else:
                          # If not using PBS, ensure CRAB uses best scheduler and remote sites.
                          cmd  = 'sed -i "s/scheduler = glite/scheduler = remoteGlidein/g"   %s.cfg; '  %crabFileName 
  #                        cmd += 'sed -i "s/use_server = 0/use_server = 1/g"   %s.cfg'  %crabFileName 
                          istat = subprocess.call(cmd, shell=True)
                          f = open('%s.cfg'  %crabFileName ,'a')
                          f.write( "\n" )
                          f.write( "[GRID] \n" )
                          f.write( "se_black_list = T0,T1 \n" )
  #                        f.write( "ce_black_list = ihep.ac.cn,in2p3.fr,ce2.polgrid.pl,kuragua.uniandes.edu.co,lcgce02.jinr.ru;viking.lesc.doc.ic.ac.uk,sinp.msu.ru,ecdf.ed.ac.uk,gridce.iihe.ac.be,colorado.edu,red-gw2.unl.edu,cebo-t3-01.cr.cnaf.infn.it,cream01.iihe.ac.be,grid.sinica.edu.tw,cream-ce-2.ba.infn.it,phy.bris.ac.uk,T2_KR_KNU,T2_AT_Vienna,T2_TR_METU \n" )
                          f.close()

                istat = subprocess.call('rm workspace.*', shell=True) # Remove workspace to tidy up.


# Create multicrab.cfg
# N.B. crab copies both the "additional_input_files" and TestGrid.sh into the same working directory
# so TestGrid.sh refers to combine.root without any directory prefix.
F = open("%s/multicrab.cfg" %jobDirName,'w')
F.write( "[MULTICRAB]\n" )
F.write( "cfg=%s.cfg\n\n" %crabFileName )
F.write( "[COMMON]\n" )
F.write( "USER.ui_working_dir = %s \n\n" %jobOutName)
for s in samples:
   if s.acceptance == acceptanceOption: 
     for l in leptons:
         for tIndex, t in enumerate(s.cTauScaleLoopValues):
                if not s.enoughMC(l, tIndex, jobOpt.loopOverCTau):
                       continue # Skip this point if not enough MC statistics.

                for limitType in limitTypeList:
                       name = '%s_%i_%i_%s_%s'    %(l, s.MH, s.MX, t, limitType)
                       # Prefix of CRAB job file
                       subDirName = '%s/%s_%i_%i_%s_%s'    %(jobDirName, l, s.MH, s.MX, t, limitType)
                       crabFileName = "%s/TestGrid"  %(subDirName)
                       F.write( "[%s] \n" %(name) )
                       F.write( "USER.script_exe = %s.sh \n"  %crabFileName )
                       F.write( "USER.additional_input_files = combine, %s/%s/combine.root \n"  %(jobDirName, name) )
                       if jobOpt.limitMethod == "CLs":
                           F.write( "CMSSW.output_file = TestGrid.root, combine.root \n\n" ) # Get file containing toys
                       elif jobOpt.limitMethod == "Bayesian":
                           F.write( "CMSSW.output_file = higgsCombineTest.%s.mH0.root, higgsCombineTest.%s.mH0.123456.root, combine.root \n\n" %(limitMethodCall, limitMethodCall) ) # Get file containing limits (two possible names).

F.close()

if jobOpt.loopOverCTau:
       print "Option loopOverCTau = True, so will calculate limits using dedicated calculation at each lifetime point (slow, but accurate)\n"
else:
       print "Option loopOverCTau = False, so will neglect variation in efficiency uncertainty & mass resolution with lifetime (fast)\n"

print "File multicrab.cfg created"
print "Now submit job using multicrab -create -submit -cfg %s/multicrab.cfg" %jobDirName
print "And check status using multicrab -status -c %s" %jobOutName

# Batch script expects combine command to exist locally.
if os.path.exists("combine"): os.remove("combine")
cmd = 'ln -s `which combine` combine'
istat = subprocess.call(cmd, shell=True)
