sampleDataSet = '/HTo2LongLivedTo4F_MH-120_MFF-20_CTau13To1300_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 10447 # Very small?!?

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7A::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"






samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-120_MFF-20_CTau13To1300_8TeV-pythia6/HTo2LongLivedTo4F_MH120_MFF20_CTau13To1300_pat_20130123/6116ed9d2ff4828f95fa33fe25241a8f/"
samplePatFiles = [
sampleBaseDir+"PATtuple_4_1_tD4.root",
sampleBaseDir+"PATtuple_3_1_AA0.root",
sampleBaseDir+"PATtuple_2_1_g6H.root",
sampleBaseDir+"PATtuple_1_1_J0W.root",
sampleBaseDir+"PATtuple_5_1_S1L.root",
sampleBaseDir+"PATtuple_6_1_xKo.root",
]
