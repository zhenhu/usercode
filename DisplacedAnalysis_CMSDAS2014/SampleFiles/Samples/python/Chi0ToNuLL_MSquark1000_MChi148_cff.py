sampleDataSet = '/LongLivedChi0ToNuLL_MSquark-1000_MChi-148_TuneZ2Star_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 10000

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7A::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"





samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//LongLivedChi0ToNuLL_MSquark-1000_MChi-148_TuneZ2Star_8TeV-pythia6/Chi0ToNuLL_MSquark1000_MChi148_pat_20130123/6116ed9d2ff4828f95fa33fe25241a8f/"
samplePatFiles = [
sampleBaseDir+"PATtuple_3_1_MGq.root",
sampleBaseDir+"PATtuple_2_1_Q3U.root",
sampleBaseDir+"PATtuple_1_1_2rL.root",
sampleBaseDir+"PATtuple_4_1_xBf.root",
sampleBaseDir+"PATtuple_5_1_Dj5.root",
]
