sampleDataSet = '/HTo2LongLivedTo4F_MH-200_MFF-20_CTau7To700_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 99010

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7A::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"


samplePatDBSName="/HTo2LongLivedTo4F_MH-200_MFF-20_CTau7To700_8TeV-pythia6/ejclemen-HTo2LongLivedTo4F_MH200_MFF20_CTau7To700_pat_20130103-41608ddebc02a57cd9f3d8f6ae282ec6/USER"

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-200_MFF-20_CTau7To700_8TeV-pythia6/HTo2LongLivedTo4F_MH200_MFF20_CTau7To700_pat_20130103/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_49_1_EYB.root",
sampleBaseDir+"PATtuple_47_1_tIw.root",
sampleBaseDir+"PATtuple_48_1_C47.root",
sampleBaseDir+"PATtuple_46_1_9O8.root",
sampleBaseDir+"PATtuple_45_1_PAX.root",
sampleBaseDir+"PATtuple_43_1_Pei.root",
sampleBaseDir+"PATtuple_41_1_gyV.root",
sampleBaseDir+"PATtuple_39_1_cHP.root",
sampleBaseDir+"PATtuple_44_1_Uju.root",
sampleBaseDir+"PATtuple_40_1_i9b.root",
sampleBaseDir+"PATtuple_42_1_tfU.root",
sampleBaseDir+"PATtuple_50_1_WSc.root",
sampleBaseDir+"PATtuple_37_1_eqw.root",
sampleBaseDir+"PATtuple_36_1_uvG.root",
sampleBaseDir+"PATtuple_38_1_Gvj.root",
sampleBaseDir+"PATtuple_35_1_B2J.root",
sampleBaseDir+"PATtuple_34_1_6ER.root",
sampleBaseDir+"PATtuple_32_1_gIk.root",
sampleBaseDir+"PATtuple_33_1_MWx.root",
sampleBaseDir+"PATtuple_30_1_kzp.root",
sampleBaseDir+"PATtuple_31_1_0Vv.root",
sampleBaseDir+"PATtuple_29_1_Vwl.root",
sampleBaseDir+"PATtuple_28_1_cdd.root",
sampleBaseDir+"PATtuple_24_1_arr.root",
sampleBaseDir+"PATtuple_26_1_Css.root",
sampleBaseDir+"PATtuple_27_1_4BP.root",
sampleBaseDir+"PATtuple_23_1_zkP.root",
sampleBaseDir+"PATtuple_25_1_6qH.root",
sampleBaseDir+"PATtuple_21_1_vjC.root",
sampleBaseDir+"PATtuple_18_1_qrx.root",
sampleBaseDir+"PATtuple_19_1_9Ot.root",
sampleBaseDir+"PATtuple_22_1_lMV.root",
sampleBaseDir+"PATtuple_17_1_9GD.root",
sampleBaseDir+"PATtuple_20_1_h6L.root",
sampleBaseDir+"PATtuple_13_1_Ybh.root",
sampleBaseDir+"PATtuple_16_1_TbM.root",
sampleBaseDir+"PATtuple_15_1_11a.root",
sampleBaseDir+"PATtuple_14_1_5LT.root",
sampleBaseDir+"PATtuple_11_1_mM2.root",
sampleBaseDir+"PATtuple_12_1_31x.root",
sampleBaseDir+"PATtuple_9_1_VqA.root",
sampleBaseDir+"PATtuple_10_1_0S2.root",
sampleBaseDir+"PATtuple_8_1_pEw.root",
sampleBaseDir+"PATtuple_7_1_gPD.root",
sampleBaseDir+"PATtuple_5_1_1hj.root",
sampleBaseDir+"PATtuple_4_1_XVe.root",
sampleBaseDir+"PATtuple_2_1_P6N.root",
sampleBaseDir+"PATtuple_6_1_XWz.root",
sampleBaseDir+"PATtuple_1_1_JMV.root",
sampleBaseDir+"PATtuple_3_1_jFK.root",
]
