sampleDataSet = '/HTo2LongLivedTo4F_MH-120_MFF-50_CTau50To5000_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 98997

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7A::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"

samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-120_MFF-50_CTau50To5000_8TeV-pythia6/HTo2LongLivedTo4F_MH120_MFF50_CTau50To5000_pat_20121212/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_34_1_DLi.root",
sampleBaseDir+"PATtuple_28_1_aAV.root",
sampleBaseDir+"PATtuple_27_1_02q.root",
sampleBaseDir+"PATtuple_13_1_EIQ.root",
sampleBaseDir+"PATtuple_45_1_yW3.root",
sampleBaseDir+"PATtuple_29_1_qDE.root",
sampleBaseDir+"PATtuple_24_1_wii.root",
sampleBaseDir+"PATtuple_7_1_Lqa.root",
sampleBaseDir+"PATtuple_26_1_fSk.root",
sampleBaseDir+"PATtuple_6_1_ztW.root",
sampleBaseDir+"PATtuple_44_1_LFs.root",
sampleBaseDir+"PATtuple_5_1_OD3.root",
sampleBaseDir+"PATtuple_22_1_TUp.root",
sampleBaseDir+"PATtuple_16_1_OJn.root",
sampleBaseDir+"PATtuple_39_1_D6V.root",
sampleBaseDir+"PATtuple_9_1_pB1.root",
sampleBaseDir+"PATtuple_14_1_ppB.root",
sampleBaseDir+"PATtuple_48_1_5FM.root",
sampleBaseDir+"PATtuple_31_1_Uhi.root",
sampleBaseDir+"PATtuple_42_1_EZ8.root",
sampleBaseDir+"PATtuple_8_1_ECY.root",
sampleBaseDir+"PATtuple_12_1_o8Z.root",
sampleBaseDir+"PATtuple_2_1_M01.root",
sampleBaseDir+"PATtuple_15_1_CZM.root",
sampleBaseDir+"PATtuple_46_1_e1J.root",
sampleBaseDir+"PATtuple_11_1_k0D.root",
sampleBaseDir+"PATtuple_19_1_C11.root",
sampleBaseDir+"PATtuple_30_1_05i.root",
sampleBaseDir+"PATtuple_43_1_PFc.root",
sampleBaseDir+"PATtuple_47_1_1gy.root",
sampleBaseDir+"PATtuple_40_1_xVY.root",
sampleBaseDir+"PATtuple_49_1_v8C.root",
sampleBaseDir+"PATtuple_17_1_XAZ.root",
sampleBaseDir+"PATtuple_32_1_tix.root",
sampleBaseDir+"PATtuple_10_1_1JH.root",
sampleBaseDir+"PATtuple_35_1_pC2.root",
sampleBaseDir+"PATtuple_36_1_XIJ.root",
sampleBaseDir+"PATtuple_3_1_dl1.root",
sampleBaseDir+"PATtuple_18_1_A6E.root",
sampleBaseDir+"PATtuple_20_1_Lfs.root",
sampleBaseDir+"PATtuple_41_1_dii.root",
sampleBaseDir+"PATtuple_37_1_7I5.root",
sampleBaseDir+"PATtuple_23_1_XY4.root",
sampleBaseDir+"PATtuple_33_1_Zfh.root",
sampleBaseDir+"PATtuple_1_1_pWD.root",
sampleBaseDir+"PATtuple_4_1_YZx.root",
sampleBaseDir+"PATtuple_21_1_nOB.root",
sampleBaseDir+"PATtuple_25_1_HG9.root",
sampleBaseDir+"PATtuple_38_1_kmZ.root",
sampleBaseDir+"PATtuple_50_1_HFC.root",
]
