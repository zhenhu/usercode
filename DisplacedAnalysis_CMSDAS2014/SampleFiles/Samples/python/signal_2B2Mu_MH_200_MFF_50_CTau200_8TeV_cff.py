sampleDataSet = 'dummy'

sampleCMSEnergy = 8000
 
sampleRelease = "CMSSW_5_2_5" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_3" # release used to create new files with

sampleNumEvents = 100000

sampleXSec = 1.0 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V11::All'

sampleDuplicateCheckMode = 'noDuplicateCheck'

sampleType = "MC"

sampleBaseDir = "dcache:/pnfs/cms/WAX/11/store/user/plujan/DisplacedLeptons/"

samplePatFiles = [
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_1.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_10.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_2.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_3.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_4.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_5.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_6.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_7.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_8.root",
    "dcache:/pnfs/cms/WAX/11/store/user/plujan/PATtuples/PATtuple_2B2Mu_MH_200_MFF_50_CTau200_8TeV_9.root",
    ]
