sampleDataSet = '/HTo2LongLivedTo4F_MH-200_MFF-50_CTau20To2000_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 99048

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7A::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"



samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-200_MFF-50_CTau20To2000_8TeV-pythia6/HTo2LongLivedTo4F_MH200_MFF50_CTau20To2000_pat_20121212/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_38_3_meM.root",
sampleBaseDir+"PATtuple_38_2_R6s.root",
sampleBaseDir+"PATtuple_49_1_SuI.root",
sampleBaseDir+"PATtuple_44_1_JVu.root",
sampleBaseDir+"PATtuple_46_1_Jro.root",
sampleBaseDir+"PATtuple_47_1_VUq.root",
sampleBaseDir+"PATtuple_45_1_jKn.root",
sampleBaseDir+"PATtuple_48_1_wrs.root",
sampleBaseDir+"PATtuple_43_1_oiC.root",
sampleBaseDir+"PATtuple_42_1_nJY.root",
sampleBaseDir+"PATtuple_39_1_BnV.root",
sampleBaseDir+"PATtuple_41_1_WKl.root",
sampleBaseDir+"PATtuple_40_1_FDr.root",
sampleBaseDir+"PATtuple_35_1_pFP.root",
sampleBaseDir+"PATtuple_7_1_6Mc.root",
sampleBaseDir+"PATtuple_26_1_cX2.root",
sampleBaseDir+"PATtuple_36_1_wYr.root",
sampleBaseDir+"PATtuple_27_1_qpL.root",
sampleBaseDir+"PATtuple_50_1_Glx.root",
sampleBaseDir+"PATtuple_14_1_syb.root",
sampleBaseDir+"PATtuple_12_1_wIF.root",
sampleBaseDir+"PATtuple_34_1_k18.root",
sampleBaseDir+"PATtuple_25_1_yyr.root",
sampleBaseDir+"PATtuple_19_1_Vix.root",
sampleBaseDir+"PATtuple_3_1_d0z.root",
sampleBaseDir+"PATtuple_15_1_bTl.root",
sampleBaseDir+"PATtuple_11_1_rap.root",
sampleBaseDir+"PATtuple_31_1_0qE.root",
sampleBaseDir+"PATtuple_22_1_KU3.root",
sampleBaseDir+"PATtuple_17_1_IjZ.root",
sampleBaseDir+"PATtuple_21_1_N6P.root",
sampleBaseDir+"PATtuple_13_1_fti.root",
sampleBaseDir+"PATtuple_4_1_kdO.root",
sampleBaseDir+"PATtuple_28_1_4AQ.root",
sampleBaseDir+"PATtuple_20_1_CgE.root",
sampleBaseDir+"PATtuple_10_1_RIj.root",
sampleBaseDir+"PATtuple_16_1_3zf.root",
sampleBaseDir+"PATtuple_30_1_fO1.root",
sampleBaseDir+"PATtuple_5_1_eGx.root",
sampleBaseDir+"PATtuple_37_1_kG2.root",
sampleBaseDir+"PATtuple_2_1_d6Y.root",
sampleBaseDir+"PATtuple_1_1_uqo.root",
sampleBaseDir+"PATtuple_23_1_QRS.root",
sampleBaseDir+"PATtuple_32_1_zQ5.root",
sampleBaseDir+"PATtuple_24_1_HrA.root",
sampleBaseDir+"PATtuple_6_1_IsP.root",
sampleBaseDir+"PATtuple_33_1_cic.root",
sampleBaseDir+"PATtuple_29_1_Key.root",
sampleBaseDir+"PATtuple_18_1_E08.root",
sampleBaseDir+"PATtuple_8_1_him.root",
sampleBaseDir+"PATtuple_9_1_scp.root",
]
