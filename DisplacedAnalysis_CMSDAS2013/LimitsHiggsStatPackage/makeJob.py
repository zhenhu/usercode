#/usr/bin/python
########################################################################
# This creates the card file and workspace for the upper limit problem
# It then creates the crab & multicrab cfgs to submit them.
########################################################################

from SignalSampleInfo import *
from MakeWorkspace import *
import sys
import os
import subprocess

# Use PBS local batch queue instead of normal CRAB batch queues ?
USE_PBS = True

# Disable buffering of STDOUT to preserve order of print statements
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)

# Get information about signal samples (efficiency, background etc.)
samples = getSignalSampleInfo()

leptons = ["Muons", "Electrons"]

# For observed limits, set assumed apriori background uncertainty to infinity
# For expected limits, set it to finite number coming from fit to lifetime distribution
aprioriBkgErr = [ "Normal", "Infinity"]

# Create directory for jobs
if os.path.exists('job'):
       istat = subprocess.call('rm -r job', shell=True)   
os.mkdir('job')

# Loop over all signal samples
for sIndex, s in enumerate(samples):

   for l in leptons:

       for tIndex, t in enumerate(s.cTauLoopValues):

              debug = (sIndex == 0 and tIndex == 0)

              # Create RooWorkspace and store in workspace.root
              print "-- Creating RooWorkSpace", debug
              MakeWorkspace(s, l, tIndex, debug, debug)

              # In principal, one should have a loop over exotic lifetime here, but we will skip that
              # as it makes the limit calculation much slower, and the variation in efficiency uncertainty
              # with lifetime is fairly small.
              # N.B. This loop is not needed to handle the variation in efficiency with lifetime, since
              # it is taken care of by convertLimits_rootToTxt.py .

              # for ctauIndex in range( len(sample.ctau) ):

              # Produce two sets of limits with infinite/finite apriori background normalisation uncertainty
              for apriori in aprioriBkgErr:

                     # Make directory for this signal sample
                     name = 'job/%s_%i_%i_%s_%s'    %(l, s.MH, s.MX, t, apriori)
                     print "\n ===== Creating directory %s ===== \n"   %(name)
                     os.mkdir(name)

                     # Copy workspace just created above into it.
                     cmd  = 'cp workspace.root %s;'   %(name)
                     cmd += 'cp workspace.txt %s'     %(name)
                     istat = subprocess.call(cmd, shell=True)

                     # Get input card file combine.txt for 'combine' command and set parameters in it.
                     print "-- Creating card file"
                     
                     effi_relerr = s.effi_relerr[l]
                     if s.loopOverCTau:
                            effi_relerr_use = effi_relerr[tIndex]
                     else:
                            # If not looping over exotica lifetime (to save CPU), then take uncertainty on
                            # efficiency equal to its median value, averaged over all lifetimes.
                            effi_relerr_ave = sorted(effi_relerr)[len(effi_relerr)/2]
                            effi_relerr_use = effi_relerr_ave
                     # Prevent relative error being too large, since it would crash limit code.
                     effi_relerr_use = min(effi_relerr_use, s.maxRelEffErr) 
                     print "effi_relerr ",effi_relerr_use
                     cmd  = 'cp combine_template.txt %s/combine.txt; ' %(name)
                     cmd += 'sed -i "s/effi_relerrTTT/%s/g"       %s/combine.txt; '   %(1 + effi_relerr_use, name)
                     # Convert apriori total background prediction to predictions for Z0 and non-Z0 backgrounds.
                     bkgZ0        = s.bkg[l]     * s.paramZ0Frac[l]
                     bkgZ0_err    = s.bkg_err[l] * s.paramZ0Frac[l]
                     bkgOther     = s.bkg[l]     * (1 - s.paramZ0Frac[l])
                     bkgOther_err = s.bkg_err[l] * (1 - s.paramZ0Frac[l])
                     # Cards expect relative, not absolute background uncertainty. (And an additonal +1 offset).
                     # Also must avoid large relative uncertainties ( > 5 ), since "combine" can become unstable for them.
                     bkgZ0        = max(bkgZ0   , bkgZ0_err    / 5.)
                     bkgZ0_relerr = bkgZ0_err    / bkgZ0
                     # Increase uncertainty to infinity if requested.
                     # In that case, use lnU error distribution, as lnN is unstable for large relative uncertainty.
                     if apriori == "Normal":
                            bkgOther        = max(bkgOther, bkgOther_err / 5.)
                            bkgOther_relerr = bkgOther_err / bkgOther
                            bkgOther_errType = 'lnN'
                     elif apriori == "Infinity":
                            bkgOther        = max(1., bkgOther)
                            bkgOther_relerr = 99.999 * bkgOther
                            bkgOther_errType = 'lnU'                     
                     cmd += 'sed -i "s/bkgZ0TTT/%f/g"             %s/combine.txt; '   %(bkgZ0, name)
                     cmd += 'sed -i "s/bkgZ0_relerrTTT/%f/g"      %s/combine.txt; '   %(1 + bkgZ0_relerr, name)
                     cmd += 'sed -i "s/bkgOtherTTT/%f/g"          %s/combine.txt; '   %(bkgOther, name)
                     cmd += 'sed -i "s/bkgOther_relerrTTT/%f/g"   %s/combine.txt; '   %(1 + bkgOther_relerr, name)
                     cmd += 'sed -i "s/bkgOther_errTypeTTT/%s/g"  %s/combine.txt; '   %(bkgOther_errType, name)
                     # Put in correct relative systematic uncertainty on resonance width.
                     cmd += 'sed -i "s/widthSysTTT/%f/g"          %s/combine.txt; '   %(s.widthSys[l], name)
                     istat = subprocess.call(cmd, shell=True)              
                     cmd += 'cat %s/combine.txt'       %(name)    # Just to check it is OK

                     # Merge workspace and combine.txt into a single file combine.root
                     cmd = '$CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/scripts/text2workspace.py %s/combine.txt -b %s/combine.root'   %(name, name)
                     istat = subprocess.call(cmd, shell=True)
                     if istat != 0:
                            sys.exit("ERROR: whilst executing %s" %cmd)

                     # Create CRAB job to calculate limits.
                     print "-- Creating CRAB job (PBS = %s)"   %(USE_PBS)
                     min_r = 0  # This should encompass the possible expected and observed limits on number of events passing cuts.
                     max_r = s.maxPredictedLimit
                     npoints = 50  # The accuracy achieved will be rather better than (max_r - min_r)/npoints
                     njobs = 1 # If more than 1, the nevents will be split into several jobs to run faster.
                     nevents = 5 # I think nevents * ntoys is effective number of toys
                     ntoys = 500
                     cmd = '$CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/test/makeGridUsingCrab.py combine.root -r -O "-m 0 -U --fullBToys" %i %i -n %i -j %i -t %i -T %i'   %(min_r, max_r, npoints, njobs, nevents, ntoys)
                     istat = subprocess.call(cmd, shell=True)
                     if istat != 0:
                            sys.exit("ERROR: whilst executing %s" %cmd)

                     # If requested, modify CRAB cfg to use PBS queues.
                     if USE_PBS:
                        cmd = 'sed -i "s/scheduler = glite/scheduler = pbs/g"   TestGrid.cfg' 
                        istat = subprocess.call(cmd, shell=True)
                        f = open('TestGrid.cfg','a')
                        f.write( "\n" )
                        f.write( "[PBS] \n" )
                        f.write( "queue=prod \n" )
                        f.write( "resources=cput=12:00:00,walltime=12:00:00,mem=1gb \n" )
                        f.close()
                     else:
                        cmd  = 'sed -i "s/scheduler = glite/scheduler = glidein/g"   TestGrid.cfg; ' 
                        cmd += 'sed -i "s/use_server = 0/use_server = 1/g"   TestGrid.cfg' 
                        istat = subprocess.call(cmd, shell=True)
                        f = open('TestGrid.cfg','a')
                        f.write( "\n" )
                        f.write( "[GRID] \n" )
                        f.write( "se_black_list = T0,T1 \n" )
                        f.write( "ce_black_list = ihep.ac.cn,in2p3.fr,ce2.polgrid.pl,kuragua.uniandes.edu.co,lcgce02.jinr.ru;viking.lesc.doc.ic.ac.uk,sinp.msu.ru,ecdf.ed.ac.uk,gridce.iihe.ac.be,colorado.edu,red-gw2.unl.edu,cebo-t3-01.cr.cnaf.infn.it,cream01.iihe.ac.be,grid.sinica.edu.tw,cream-ce-2.ba.infn.it,phy.bris.ac.uk,T2_KR_KNU,T2_AT_Vienna,T2_TR_METU \n" )
                        f.close()

                     cmd = 'cp TestGrid.* %s'   %(name)
                     istat = subprocess.call(cmd, shell=True)

# Create multicrab.cfg
F = open('multicrab.cfg','w')
F.write( "[MULTICRAB]\n" )
F.write( "cfg=TestGrid.cfg\n\n" )
F.write( "[COMMON]\n" )
F.write( "USER.ui_working_dir = job_output\n\n" )
for s in samples:
   for l in leptons:
       for t in s.cTauLoopValues:
              for apriori in aprioriBkgErr:
                     name = '%s_%i_%i_%s_%s'    %(l, s.MH, s.MX, t, apriori)
                     F.write( "[%s] \n" %(name) )
                     F.write( "USER.script_exe = job/%s/TestGrid.sh \n"  %(name) )
                     F.write( "USER.additional_input_files = combine, job/%s/combine.root \n"  %(name) )
                     F.write( "USER.output_file = combine.root \n\n" ) # keep copy 

F.close()

if samples[0].loopOverCTau:
       print "Option loopOverCTau = True, so will calculate limits using dedicated calculation at each lifetime point (slow, but accurate)\n"
else:
       print "Option loopOverCTau = False, so will neglect variation in efficiency uncertainty & mass resolution with lifetime (fast)\n"

print "File multicrab.cfg created"
print "Now submit job using multicrab -create -submit"
print "And check status using multicrab -status -c job_output"

# Batch script expects combine command to exist locally.
if os.path.exists("combine"): os.remove("combine")
cmd = 'ln -s `which combine` combine'
istat = subprocess.call(cmd, shell=True)
