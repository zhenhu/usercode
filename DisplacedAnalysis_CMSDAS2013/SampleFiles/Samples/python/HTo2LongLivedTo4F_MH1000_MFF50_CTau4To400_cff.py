sampleDataSet = '/HTo2LongLivedTo4F_MH_1000_MFF_50_CTau4To400_8TeV_pythia6/Summer12_DR53X-DEBUG_PU_S10_START53_V7A-v2/AODSIM'  

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

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH_1000_MFF_50_CTau4To400_8TeV_pythia6/HTo2LongLivedTo4F_MH1000_MFF50_CTau4To400_pat_20121210/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_48_1_6wl.root",
sampleBaseDir+"PATtuple_42_1_h0z.root",
sampleBaseDir+"PATtuple_47_1_g1g.root",
sampleBaseDir+"PATtuple_46_1_Af6.root",
sampleBaseDir+"PATtuple_44_1_pzb.root",
sampleBaseDir+"PATtuple_43_1_rKy.root",
sampleBaseDir+"PATtuple_49_1_yCM.root",
sampleBaseDir+"PATtuple_31_1_qEI.root",
sampleBaseDir+"PATtuple_45_1_cT1.root",
sampleBaseDir+"PATtuple_32_1_Sid.root",
sampleBaseDir+"PATtuple_34_1_IQ1.root",
sampleBaseDir+"PATtuple_26_1_jBx.root",
sampleBaseDir+"PATtuple_41_1_btn.root",
sampleBaseDir+"PATtuple_38_1_pwp.root",
sampleBaseDir+"PATtuple_39_1_0Pc.root",
sampleBaseDir+"PATtuple_37_1_y8V.root",
sampleBaseDir+"PATtuple_36_1_ObN.root",
sampleBaseDir+"PATtuple_24_1_hAT.root",
sampleBaseDir+"PATtuple_25_1_gHQ.root",
sampleBaseDir+"PATtuple_22_1_wfe.root",
sampleBaseDir+"PATtuple_33_1_zYe.root",
sampleBaseDir+"PATtuple_50_1_rmt.root",
sampleBaseDir+"PATtuple_20_1_MvW.root",
sampleBaseDir+"PATtuple_27_1_pDZ.root",
sampleBaseDir+"PATtuple_21_1_vbA.root",
sampleBaseDir+"PATtuple_30_1_jkh.root",
sampleBaseDir+"PATtuple_29_1_YJs.root",
sampleBaseDir+"PATtuple_28_1_TfK.root",
sampleBaseDir+"PATtuple_11_1_uEq.root",
sampleBaseDir+"PATtuple_10_1_SJW.root",
sampleBaseDir+"PATtuple_7_1_mL1.root",
sampleBaseDir+"PATtuple_9_1_6pD.root",
sampleBaseDir+"PATtuple_13_1_ymZ.root",
sampleBaseDir+"PATtuple_16_1_FJP.root",
sampleBaseDir+"PATtuple_15_1_SBV.root",
sampleBaseDir+"PATtuple_18_1_CiE.root",
sampleBaseDir+"PATtuple_19_1_Btr.root",
sampleBaseDir+"PATtuple_17_1_5o1.root",
sampleBaseDir+"PATtuple_6_1_TDO.root",
sampleBaseDir+"PATtuple_8_1_Ms7.root",
sampleBaseDir+"PATtuple_5_1_CaN.root",
sampleBaseDir+"PATtuple_2_1_6xX.root",
sampleBaseDir+"PATtuple_3_1_1Gq.root",
sampleBaseDir+"PATtuple_4_1_gXJ.root",
]
