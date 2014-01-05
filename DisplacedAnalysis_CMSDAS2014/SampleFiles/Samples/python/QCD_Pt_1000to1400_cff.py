sampleDataSet = '/QCD_Pt-1000to1400_TuneZ2star_8TeV_pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 1964088

sampleXSec = 0.737844 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7F::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "BKGMC"



samplePatDBSName=""

sampleBaseDir="/store/user/lpcdve/DisplacedLeptons/QCD_Pt_1000to1400_pat_20130913/demattia//QCD_Pt-1000to1400_TuneZ2star_8TeV_pythia6/QCD_Pt_1000to1400_pat_20130913/5fe3dadd93bf8608b396f970098158ed/"
samplePatFiles = [
sampleBaseDir+"PATtuple_39_1_vad.root",
sampleBaseDir+"PATtuple_37_1_K1R.root",
sampleBaseDir+"PATtuple_36_1_OlI.root",
sampleBaseDir+"PATtuple_19_1_oem.root",
sampleBaseDir+"PATtuple_40_1_KoD.root",
sampleBaseDir+"PATtuple_38_1_0U2.root",
]
