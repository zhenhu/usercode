sampleDataSet = '/HTo2LongLivedTo4F_MH-400_MFF-150_CTau40To4000_8TeV-pythia6/Summer12_DR53X-DEBUG_PU_S10_START53_V7A-v2/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 99066

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7A::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"


samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-400_MFF-150_CTau40To4000_8TeV-pythia6/HTo2LongLivedTo4F_MH400_MFF150_CTau40To4000_pat_20121212/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_28_1_FNw.root",
sampleBaseDir+"PATtuple_14_1_UHu.root",
sampleBaseDir+"PATtuple_17_1_gFe.root",
sampleBaseDir+"PATtuple_31_1_pCg.root",
sampleBaseDir+"PATtuple_49_1_zBp.root",
sampleBaseDir+"PATtuple_46_1_fO8.root",
sampleBaseDir+"PATtuple_27_1_6cz.root",
sampleBaseDir+"PATtuple_44_1_5Yy.root",
sampleBaseDir+"PATtuple_34_1_jAm.root",
sampleBaseDir+"PATtuple_47_1_xHj.root",
sampleBaseDir+"PATtuple_29_1_Icp.root",
sampleBaseDir+"PATtuple_16_1_JrJ.root",
sampleBaseDir+"PATtuple_40_1_xgr.root",
sampleBaseDir+"PATtuple_18_1_LZj.root",
sampleBaseDir+"PATtuple_24_1_rnF.root",
sampleBaseDir+"PATtuple_15_1_1rR.root",
sampleBaseDir+"PATtuple_20_1_YL3.root",
sampleBaseDir+"PATtuple_8_1_1we.root",
sampleBaseDir+"PATtuple_30_1_DAG.root",
sampleBaseDir+"PATtuple_19_1_4Pa.root",
sampleBaseDir+"PATtuple_5_1_gfW.root",
sampleBaseDir+"PATtuple_4_1_EHv.root",
sampleBaseDir+"PATtuple_25_1_vIx.root",
sampleBaseDir+"PATtuple_23_1_8hp.root",
sampleBaseDir+"PATtuple_42_1_Qiy.root",
sampleBaseDir+"PATtuple_32_1_F6t.root",
sampleBaseDir+"PATtuple_33_1_vS7.root",
sampleBaseDir+"PATtuple_7_1_DKf.root",
sampleBaseDir+"PATtuple_43_1_Gwn.root",
sampleBaseDir+"PATtuple_11_1_Uk3.root",
sampleBaseDir+"PATtuple_41_1_KnW.root",
sampleBaseDir+"PATtuple_22_1_58Z.root",
sampleBaseDir+"PATtuple_13_1_zZx.root",
sampleBaseDir+"PATtuple_3_1_MrC.root",
sampleBaseDir+"PATtuple_26_1_3uo.root",
sampleBaseDir+"PATtuple_45_1_xFj.root",
sampleBaseDir+"PATtuple_39_1_hSm.root",
sampleBaseDir+"PATtuple_2_1_qWo.root",
sampleBaseDir+"PATtuple_35_1_y4X.root",
sampleBaseDir+"PATtuple_21_1_mkU.root",
sampleBaseDir+"PATtuple_36_1_kZe.root",
sampleBaseDir+"PATtuple_12_1_D7L.root",
sampleBaseDir+"PATtuple_6_1_PEz.root",
sampleBaseDir+"PATtuple_38_1_n5Y.root",
sampleBaseDir+"PATtuple_10_1_zPm.root",
sampleBaseDir+"PATtuple_37_1_0iu.root",
sampleBaseDir+"PATtuple_48_1_p14.root",
sampleBaseDir+"PATtuple_9_1_fTo.root",
sampleBaseDir+"PATtuple_1_1_YbC.root",
sampleBaseDir+"PATtuple_50_1_yfu.root",
]
