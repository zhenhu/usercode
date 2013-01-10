sampleDataSet = '/HTo2LongLivedTo4F_MH-400_MFF-50_CTau8To800_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 99004

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7A::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"

samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-400_MFF-50_CTau8To800_8TeV-pythia6/HTo2LongLivedTo4F_MH400_MFF50_CTau40To4000_pat_20121212/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_48_1_1Pr.root",
sampleBaseDir+"PATtuple_39_1_AWd.root",
sampleBaseDir+"PATtuple_49_1_Zd8.root",
sampleBaseDir+"PATtuple_40_1_eIt.root",
sampleBaseDir+"PATtuple_44_1_jlR.root",
sampleBaseDir+"PATtuple_45_1_Ytv.root",
sampleBaseDir+"PATtuple_47_1_8Qm.root",
sampleBaseDir+"PATtuple_46_1_6wb.root",
sampleBaseDir+"PATtuple_41_1_8cE.root",
sampleBaseDir+"PATtuple_43_1_5Fa.root",
sampleBaseDir+"PATtuple_42_1_9Su.root",
sampleBaseDir+"PATtuple_37_1_G1S.root",
sampleBaseDir+"PATtuple_28_1_ymA.root",
sampleBaseDir+"PATtuple_24_1_FHL.root",
sampleBaseDir+"PATtuple_23_1_CDl.root",
sampleBaseDir+"PATtuple_34_1_Nkr.root",
sampleBaseDir+"PATtuple_35_1_C0R.root",
sampleBaseDir+"PATtuple_29_1_5ao.root",
sampleBaseDir+"PATtuple_38_1_ETH.root",
sampleBaseDir+"PATtuple_36_1_gSw.root",
sampleBaseDir+"PATtuple_26_1_jKR.root",
sampleBaseDir+"PATtuple_22_1_ufn.root",
sampleBaseDir+"PATtuple_18_1_vzV.root",
sampleBaseDir+"PATtuple_31_1_OPj.root",
sampleBaseDir+"PATtuple_33_1_1pD.root",
sampleBaseDir+"PATtuple_16_1_JLg.root",
sampleBaseDir+"PATtuple_32_1_Fku.root",
sampleBaseDir+"PATtuple_25_1_UBc.root",
sampleBaseDir+"PATtuple_17_1_YFe.root",
sampleBaseDir+"PATtuple_14_1_Tx6.root",
sampleBaseDir+"PATtuple_30_1_Z55.root",
sampleBaseDir+"PATtuple_20_1_1AW.root",
sampleBaseDir+"PATtuple_8_1_ycz.root",
sampleBaseDir+"PATtuple_13_1_NlD.root",
sampleBaseDir+"PATtuple_15_1_gqV.root",
sampleBaseDir+"PATtuple_7_1_J2N.root",
sampleBaseDir+"PATtuple_21_1_5w8.root",
sampleBaseDir+"PATtuple_2_1_9oZ.root",
sampleBaseDir+"PATtuple_19_1_nmH.root",
sampleBaseDir+"PATtuple_9_1_iJf.root",
sampleBaseDir+"PATtuple_11_1_no7.root",
sampleBaseDir+"PATtuple_12_1_cK0.root",
sampleBaseDir+"PATtuple_1_1_VZo.root",
sampleBaseDir+"PATtuple_5_1_IAN.root",
sampleBaseDir+"PATtuple_6_1_kqj.root",
sampleBaseDir+"PATtuple_3_1_vJs.root",
sampleBaseDir+"PATtuple_4_1_9P6.root",
sampleBaseDir+"PATtuple_10_1_LQ3.root",
sampleBaseDir+"PATtuple_50_1_KyD.root",
]
