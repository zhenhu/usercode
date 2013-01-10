sampleDataSet = '/HTo2LongLivedTo4F_MH-400_MFF-20_CTau4To400_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7C-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 99052

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7A::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"

samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-400_MFF-20_CTau4To400_8TeV-pythia6/HTo2LongLivedTo4F_MH400_MFF20_CTau40To4000_pat_20121212/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_11_1_ZQY.root",
sampleBaseDir+"PATtuple_19_1_EuV.root",
sampleBaseDir+"PATtuple_2_1_eph.root",
sampleBaseDir+"PATtuple_13_1_j8E.root",
sampleBaseDir+"PATtuple_21_1_c3a.root",
sampleBaseDir+"PATtuple_6_1_Yya.root",
sampleBaseDir+"PATtuple_33_1_m08.root",
sampleBaseDir+"PATtuple_25_1_sd4.root",
sampleBaseDir+"PATtuple_17_1_U9d.root",
sampleBaseDir+"PATtuple_9_1_op3.root",
sampleBaseDir+"PATtuple_15_1_rGS.root",
sampleBaseDir+"PATtuple_3_1_5O5.root",
sampleBaseDir+"PATtuple_23_1_DMQ.root",
sampleBaseDir+"PATtuple_10_1_Swu.root",
sampleBaseDir+"PATtuple_36_1_PYZ.root",
sampleBaseDir+"PATtuple_35_1_snE.root",
sampleBaseDir+"PATtuple_20_1_KmW.root",
sampleBaseDir+"PATtuple_8_1_nTt.root",
sampleBaseDir+"PATtuple_4_1_oE4.root",
sampleBaseDir+"PATtuple_37_1_ogC.root",
sampleBaseDir+"PATtuple_5_1_h41.root",
sampleBaseDir+"PATtuple_1_1_2fU.root",
sampleBaseDir+"PATtuple_18_1_kru.root",
sampleBaseDir+"PATtuple_7_1_jJ1.root",
sampleBaseDir+"PATtuple_34_1_pFp.root",
sampleBaseDir+"PATtuple_32_1_3EP.root",
sampleBaseDir+"PATtuple_28_1_OFH.root",
sampleBaseDir+"PATtuple_31_1_Rus.root",
sampleBaseDir+"PATtuple_22_1_2DN.root",
sampleBaseDir+"PATtuple_27_1_Ydq.root",
sampleBaseDir+"PATtuple_26_1_zp8.root",
sampleBaseDir+"PATtuple_16_1_6mf.root",
sampleBaseDir+"PATtuple_30_1_Xw3.root",
sampleBaseDir+"PATtuple_14_1_1h0.root",
sampleBaseDir+"PATtuple_12_1_o8j.root",
sampleBaseDir+"PATtuple_24_1_Hp3.root",
sampleBaseDir+"PATtuple_29_1_MR7.root",
sampleBaseDir+"PATtuple_38_1_UL0.root",
]
