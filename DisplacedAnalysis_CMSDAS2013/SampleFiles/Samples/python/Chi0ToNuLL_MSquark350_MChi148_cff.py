sampleDataSet = '/LongLivedChi0ToNuLL_MSquark-350_MChi-148_TuneZ2Star_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'  

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

samplePatDBSName="/LongLivedChi0ToNuLL_MSquark-350_MChi-148_TuneZ2Star_8TeV-pythia6/ejclemen-Chi0ToNuLL_MSquark350_MChi148_pat_20121031-b1f5749b65c43ac4d1bb8aaff98a484a/USER"

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//LongLivedChi0ToNuLL_MSquark-350_MChi-148_TuneZ2Star_8TeV-pythia6/Chi0ToNuLL_MSquark350_MChi148_pat_20121031/b1f5749b65c43ac4d1bb8aaff98a484a/"
samplePatFiles = [
sampleBaseDir+"PATtuple_4_1_TBD.root",
sampleBaseDir+"PATtuple_3_1_oXC.root",
sampleBaseDir+"PATtuple_5_1_jUY.root",
sampleBaseDir+"PATtuple_1_1_Htj.root",
sampleBaseDir+"PATtuple_2_1_0AU.root",
]
