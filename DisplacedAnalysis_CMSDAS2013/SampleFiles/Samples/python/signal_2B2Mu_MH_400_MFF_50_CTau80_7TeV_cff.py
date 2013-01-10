sampleDataSet = 'dummy'

sampleCMSEnergy = 7000

sampleRelease = "CMSSW_4_4_2" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_4_4_2" # release used to create new files with

sampleNumEvents = 10000

sampleXSec = 1.0 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START44_V13::All'

sampleDuplicateCheckMode = 'noDuplicateCheck'

sampleType = "MC"

sampleBaseDir = "dcache:/pnfs/cms/WAX/11/store/user/plujan/DisplacedLeptons/"

samplePatFiles = [
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_400_MFF_50_CTau80_7TeV_1.root",
    ]
