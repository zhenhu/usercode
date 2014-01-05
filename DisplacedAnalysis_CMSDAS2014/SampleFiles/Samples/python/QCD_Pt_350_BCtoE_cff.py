sampleDataSet = '/QCD_Pt_350_BCtoE_TuneZ2star_8TeV_pythia6/Summer12_DR53X-PU_S10_START53_V7A-v2/AODSIM'

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 1948532

sampleXSec = 811.0 * 0.0295 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7F::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "BKGMC"



samplePatDBSName=""

sampleBaseDir="/store/user/lpcdve/DisplacedLeptons/QCD_Pt_350_BCtoE_pat_20130913/demattia//QCD_Pt_350_BCtoE_TuneZ2star_8TeV_pythia6/QCD_Pt_350_BCtoE_pat_20130913/5fe3dadd93bf8608b396f970098158ed/"
samplePatFiles = [
sampleBaseDir+"PATtuple_13_1_K9M.root",
sampleBaseDir+"PATtuple_6_1_5Cm.root",
sampleBaseDir+"PATtuple_21_1_Ud0.root",
sampleBaseDir+"PATtuple_7_1_9fv.root",
sampleBaseDir+"PATtuple_16_1_JtQ.root",
sampleBaseDir+"PATtuple_27_1_2Hu.root",
sampleBaseDir+"PATtuple_4_1_d3R.root",
sampleBaseDir+"PATtuple_24_1_MJw.root",
sampleBaseDir+"PATtuple_38_1_7ZV.root",
sampleBaseDir+"PATtuple_12_1_6m2.root",
sampleBaseDir+"PATtuple_25_1_UBZ.root",
sampleBaseDir+"PATtuple_23_1_CBL.root",
sampleBaseDir+"PATtuple_28_1_wAt.root",
sampleBaseDir+"PATtuple_33_1_HOZ.root",
sampleBaseDir+"PATtuple_14_1_2uR.root",
sampleBaseDir+"PATtuple_8_1_OwA.root",
sampleBaseDir+"PATtuple_26_1_Ul6.root",
sampleBaseDir+"PATtuple_35_1_XZD.root",
sampleBaseDir+"PATtuple_32_1_N64.root",
sampleBaseDir+"PATtuple_3_1_8jm.root",
sampleBaseDir+"PATtuple_36_1_mG3.root",
sampleBaseDir+"PATtuple_40_1_4x6.root",
sampleBaseDir+"PATtuple_31_1_wns.root",
sampleBaseDir+"PATtuple_29_1_PXE.root",
sampleBaseDir+"PATtuple_22_1_UL6.root",
sampleBaseDir+"PATtuple_37_1_jUZ.root",
sampleBaseDir+"PATtuple_15_1_kbN.root",
sampleBaseDir+"PATtuple_1_1_WxS.root",
sampleBaseDir+"PATtuple_11_1_M6R.root",
sampleBaseDir+"PATtuple_19_1_VI4.root",
sampleBaseDir+"PATtuple_34_1_GKL.root",
]
