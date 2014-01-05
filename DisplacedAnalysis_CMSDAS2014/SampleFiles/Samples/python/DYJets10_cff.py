sampleDataSet = '/DYJetsToLL_M-10To50_TuneZ2Star_8TeV-madgraph/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 37835275

sampleXSec = 12471 # pb 
# Taken NLO(?) xsec from higgs->WW paper/Physics Validation hypernews for filtered dataset, 860.5 pb
# Multiplied by filter efficiency from prep, 0.069

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7F::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "BKGMC"


samplePatDBSName="/DYJetsToLL_M-10To50_TuneZ2Star_8TeV-madgraph/demattia-DYJets10_pat_20130128-a17cb920816cbaf1b2552543d3ac1f74/USER"

sampleBaseDir=""
samplePatFiles = [
]
