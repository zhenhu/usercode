sampleDataSet = '/HTo2LongLivedTo4F_MH-1000_MFF-150_CTau10To1000_8TeV-pythia6/Summer12_DR53X-DEBUG_PU_S10_START53_V7A-v2/AODSIM'  

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

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-1000_MFF-150_CTau10To1000_8TeV-pythia6/HTo2LongLivedTo4F_MH1000_MFF150_CTau10To1000_pat_20121212/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_22_1_ChF.root",
sampleBaseDir+"PATtuple_1_1_b6P.root",
sampleBaseDir+"PATtuple_36_1_Cey.root",
sampleBaseDir+"PATtuple_31_1_OL9.root",
sampleBaseDir+"PATtuple_34_1_PfK.root",
sampleBaseDir+"PATtuple_10_1_xYA.root",
sampleBaseDir+"PATtuple_44_1_nqb.root",
sampleBaseDir+"PATtuple_21_1_kjg.root",
sampleBaseDir+"PATtuple_14_1_sAT.root",
sampleBaseDir+"PATtuple_38_1_HZ4.root",
sampleBaseDir+"PATtuple_2_1_O5h.root",
sampleBaseDir+"PATtuple_42_1_KEU.root",
sampleBaseDir+"PATtuple_37_1_NSv.root",
sampleBaseDir+"PATtuple_18_1_fDx.root",
sampleBaseDir+"PATtuple_20_1_3Wg.root",
sampleBaseDir+"PATtuple_26_1_Y03.root",
sampleBaseDir+"PATtuple_49_1_yMU.root",
sampleBaseDir+"PATtuple_8_1_eZS.root",
sampleBaseDir+"PATtuple_40_1_bRU.root",
sampleBaseDir+"PATtuple_15_1_Tgf.root",
sampleBaseDir+"PATtuple_43_1_oNX.root",
sampleBaseDir+"PATtuple_29_1_O6a.root",
sampleBaseDir+"PATtuple_48_1_Vzc.root",
sampleBaseDir+"PATtuple_17_1_bn3.root",
sampleBaseDir+"PATtuple_32_1_eBk.root",
sampleBaseDir+"PATtuple_39_1_F8X.root",
sampleBaseDir+"PATtuple_24_1_Pz0.root",
sampleBaseDir+"PATtuple_6_1_EHY.root",
sampleBaseDir+"PATtuple_30_1_vvB.root",
sampleBaseDir+"PATtuple_11_1_gcd.root",
sampleBaseDir+"PATtuple_16_1_BKA.root",
sampleBaseDir+"PATtuple_12_1_4Lj.root",
sampleBaseDir+"PATtuple_13_1_SSa.root",
sampleBaseDir+"PATtuple_47_1_XQx.root",
sampleBaseDir+"PATtuple_9_1_j9O.root",
sampleBaseDir+"PATtuple_27_1_ZXp.root",
sampleBaseDir+"PATtuple_19_1_UNs.root",
sampleBaseDir+"PATtuple_45_1_Iu8.root",
sampleBaseDir+"PATtuple_23_1_q73.root",
sampleBaseDir+"PATtuple_28_1_62B.root",
sampleBaseDir+"PATtuple_7_1_f4i.root",
sampleBaseDir+"PATtuple_46_1_5XR.root",
sampleBaseDir+"PATtuple_5_1_5O7.root",
sampleBaseDir+"PATtuple_25_1_3HR.root",
sampleBaseDir+"PATtuple_33_1_ZUm.root",
sampleBaseDir+"PATtuple_35_1_7fr.root",
sampleBaseDir+"PATtuple_4_1_c06.root",
sampleBaseDir+"PATtuple_3_1_sr3.root",
sampleBaseDir+"PATtuple_41_1_17j.root",
sampleBaseDir+"PATtuple_50_1_Bux.root",
]
