sampleDataSet = 'dummy'

sampleCMSEnergy = 7000

sampleRelease = "CMSSW_4_4_2" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_4_4_2" # release used to create new files with

sampleNumEvents = 110000

sampleXSec = 1.0 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START44_V13::All'

sampleDuplicateCheckMode = 'noDuplicateCheck'

sampleType = "MC"

sampleBaseDir = "dcache:/pnfs/cms/WAX/11/store/user/plujan/DisplacedLeptons/"

samplePatFiles = [
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_1.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_10.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_11.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_2.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_3.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_4.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_5.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_6.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_7.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_8.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_4L_MH_200_MFF_20_7TeV_9.root",
    ]
