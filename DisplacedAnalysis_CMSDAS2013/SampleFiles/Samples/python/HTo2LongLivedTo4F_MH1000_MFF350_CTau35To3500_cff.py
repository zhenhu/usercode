sampleDataSet = '/HTo2LongLivedTo4F_MH-1000_MFF-350_CTau35To3500_8TeV-pythia6/Summer12_DR53X-DEBUG_PU_S10_START53_V7A-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 99016

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7A::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"



samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-1000_MFF-350_CTau35To3500_8TeV-pythia6/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_pat_20121212/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_39_1_38C.root",
sampleBaseDir+"PATtuple_42_1_GKa.root",
sampleBaseDir+"PATtuple_22_1_ShI.root",
sampleBaseDir+"PATtuple_44_1_kTc.root",
sampleBaseDir+"PATtuple_47_1_Xmj.root",
sampleBaseDir+"PATtuple_24_1_Dfz.root",
sampleBaseDir+"PATtuple_46_1_ej8.root",
sampleBaseDir+"PATtuple_40_1_hca.root",
sampleBaseDir+"PATtuple_30_1_y0P.root",
sampleBaseDir+"PATtuple_34_1_5jy.root",
sampleBaseDir+"PATtuple_31_1_sMS.root",
sampleBaseDir+"PATtuple_33_1_1KH.root",
sampleBaseDir+"PATtuple_5_1_Orf.root",
sampleBaseDir+"PATtuple_45_1_TkI.root",
sampleBaseDir+"PATtuple_19_1_9JZ.root",
sampleBaseDir+"PATtuple_26_1_6XH.root",
sampleBaseDir+"PATtuple_12_1_rJc.root",
sampleBaseDir+"PATtuple_38_1_dTn.root",
sampleBaseDir+"PATtuple_9_1_F7e.root",
sampleBaseDir+"PATtuple_35_1_GMs.root",
sampleBaseDir+"PATtuple_20_1_uWS.root",
sampleBaseDir+"PATtuple_11_1_35k.root",
sampleBaseDir+"PATtuple_7_1_che.root",
sampleBaseDir+"PATtuple_15_1_ixU.root",
sampleBaseDir+"PATtuple_32_1_TUp.root",
sampleBaseDir+"PATtuple_43_1_Odh.root",
sampleBaseDir+"PATtuple_14_1_n4v.root",
sampleBaseDir+"PATtuple_6_1_yEd.root",
sampleBaseDir+"PATtuple_10_1_r94.root",
sampleBaseDir+"PATtuple_48_1_hKJ.root",
sampleBaseDir+"PATtuple_41_1_nxm.root",
sampleBaseDir+"PATtuple_4_1_5wl.root",
sampleBaseDir+"PATtuple_37_1_QiU.root",
sampleBaseDir+"PATtuple_36_1_zST.root",
sampleBaseDir+"PATtuple_29_1_quI.root",
sampleBaseDir+"PATtuple_28_1_hPP.root",
sampleBaseDir+"PATtuple_18_1_Osl.root",
sampleBaseDir+"PATtuple_49_1_xEP.root",
sampleBaseDir+"PATtuple_2_1_Jat.root",
sampleBaseDir+"PATtuple_23_1_YPg.root",
sampleBaseDir+"PATtuple_25_1_FP7.root",
sampleBaseDir+"PATtuple_8_1_wgx.root",
sampleBaseDir+"PATtuple_17_1_Ynl.root",
sampleBaseDir+"PATtuple_13_1_LJn.root",
sampleBaseDir+"PATtuple_27_1_oIA.root",
sampleBaseDir+"PATtuple_1_1_oiv.root",
sampleBaseDir+"PATtuple_21_1_bfh.root",
sampleBaseDir+"PATtuple_3_1_JHr.root",
sampleBaseDir+"PATtuple_16_1_Uk7.root",
sampleBaseDir+"PATtuple_50_1_pTu.root",
]
