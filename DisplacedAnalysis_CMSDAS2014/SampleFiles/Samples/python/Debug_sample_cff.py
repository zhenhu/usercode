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

sampleType = "DEBUGSAMPLE"

# ZZ debug sample
#sampleBaseDir="root://eoscms//eos/cms///store/caf/user/ejclemen//ZZ_pat_20120726/ejclemen/ZZ_TuneZ2star_8TeV_pythia6_tauola/ZZ_pat_20120726/d0bbde228835224f42d621e7d54b0549/"
#samplePatFiles = [
#sampleBaseDir+"PATtuple_100_1_uPd.root",
#sampleBaseDir+"PATtuple_9_1_wme.root",
#]

## DYJets50 debug sample
#sampleBaseDir="file:/opt/ppd/newscratch/clement/DisplacedLeptons/DisplacedLeptons2012/PATTuples/DYJets50/"
#samplePatFiles = [
#sampleBaseDir+"PATtuple_100_4_rmK.root",
#]
#sampleType = "BKGMC"

### H Signal debug sample
#sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen/HTo2LongLivedTo4F_MH-1000_MFF-150_CTau10To1000_8TeV-pythia6/HTo2LongLivedTo4F_MH1000_MFF150_CTau10To1000_pat_20130123/6116ed9d2ff4828f95fa33fe25241a8f/"
#samplePatFiles = [
#sampleBaseDir+"PATtuple_10_1_zbD.root",
#sampleBaseDir+"PATtuple_20_1_rU1.root",
#sampleBaseDir+"PATtuple_30_1_wgX.root",
#sampleBaseDir+"PATtuple_40_1_C0L.root",
#]
#sampleType = "SIGNALMC"

sampleBaseDir="dcap://dcap.pp.rl.ac.uk/pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen/HTo2LongLivedTo4F_MH-400_MFF-50_CTau8To800_8TeV-pythia6/HTo2LongLivedTo4F_MH400_MFF50_CTau8To800_pat_20130123/6116ed9d2ff4828f95fa33fe25241a8f/"
samplePatFiles = [
             sampleBaseDir+"PATtuple_40_1_PXz.root",     
                  ]
sampleType = "SIGNALMC"

# ### Chi0 Signal debug sample
# sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//LongLivedChi0ToNuLL_MSquark-1000_MChi-148_TuneZ2Star_8TeV-pythia6/Chi0ToNuLL_MSquark1000_MChi148_pat_20130123/6116ed9d2ff4828f95fa33fe25241a8f/"
# samplePatFiles = [
# sampleBaseDir+"PATtuple_3_1_MGq.root",
# ]

# ### Data debug sample
# sampleBaseDir="dcap://dcap.pp.rl.ac.uk/pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen/DoubleMu/Data_Mu_Run2012A2_pat_20130613/e9f93915bb0e334a67353967efa5d3af/"
# samplePatFiles = [
# sampleBaseDir+"PATtuple_1_1_gaJ.root",
# ]
# sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen/DoublePhoton/Data_Photon_Run2012B1_pat_20130131_1/45dcd3eb17c4ef442abc18f7f9584b64/"
# samplePatFiles = [
# sampleBaseDir+"PATtuple_261_1_N5D.root",
# ]
# sampleType = "DATA"