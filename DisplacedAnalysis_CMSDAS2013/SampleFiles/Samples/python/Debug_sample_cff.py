sampleDataSet = '/ZZ_TuneZ2star_8TeV_pythia6_tauola/Summer12-PU_S7_START52_V9-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_2_4_patch3" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_2_5" # release used to create new files with

sampleNumEvents = 9799908

sampleXSec = 8.3;

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START52_V9::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "MC"

# ZZ debug sample
#sampleBaseDir="root://eoscms//eos/cms///store/caf/user/ejclemen//ZZ_pat_20120726/ejclemen/ZZ_TuneZ2star_8TeV_pythia6_tauola/ZZ_pat_20120726/d0bbde228835224f42d621e7d54b0549/"
#samplePatFiles = [
#sampleBaseDir+"PATtuple_100_1_uPd.root",
#sampleBaseDir+"PATtuple_9_1_wme.root",
#]

## DYJets50 debug sample
#sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/DYJets50_pat_20120913/d0bbde228835224f42d621e7d54b0549/"
#samplePatFiles = [
#sampleBaseDir+"PATtuple_292_0_IvO.root",
#sampleBaseDir+"PATtuple_300_0_1qF.root"
#]

### H Signal debug sample
#sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-1000_MFF-350_CTau35To3500_8TeV-pythia6/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_pat_20121030/b1f5749b65c43ac4d1bb8aaff98a484a/"
#samplePatFiles = [
#sampleBaseDir+"PATtuple_17_1_q0d.root",
#]

## Chi0 Signal debug sample
sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//LongLivedChi0ToNuLL_MSquark-1000_MChi-148_TuneZ2Star_8TeV-pythia6/Chi0ToNuLL_MSquark1000_MChi148_pat_20121031/b1f5749b65c43ac4d1bb8aaff98a484a/"
samplePatFiles = [
sampleBaseDir+"PATtuple_4_1_BFx.root",
]

## Data debug sample
#sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//DoubleMu/Data_Mu_Run2012C2_pat_20121101/c50c5bf922918961d6703f23449eaeb8/"
#samplePatFiles = [
#sampleBaseDir+"PATtuple_475_0_mSO.root",
#]