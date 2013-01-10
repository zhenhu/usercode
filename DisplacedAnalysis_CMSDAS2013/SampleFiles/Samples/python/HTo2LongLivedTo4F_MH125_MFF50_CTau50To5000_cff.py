sampleDataSet = '/HTo2LongLivedTo4F_MH-125_MFF-50_CTau50To5000_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7C-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 100007

sampleXSec = 1 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7G::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "SIGNALMC"


samplePatDBSName="/HTo2LongLivedTo4F_MH-125_MFF-50_CTau50To5000_8TeV-pythia6/ejclemen-HTo2LongLivedTo4F_MH125_MFF50_CTau50To5000_pat_20130103-04b26a77af085d5c5bf10c9186a99cb8/USER"

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-125_MFF-50_CTau50To5000_8TeV-pythia6/HTo2LongLivedTo4F_MH125_MFF50_CTau50To5000_pat_20130103/04b26a77af085d5c5bf10c9186a99cb8/"
samplePatFiles = [
sampleBaseDir+"PATtuple_50_1_JTH.root",
sampleBaseDir+"PATtuple_47_1_ZSB.root",
sampleBaseDir+"PATtuple_48_1_Rdt.root",
sampleBaseDir+"PATtuple_49_1_GHQ.root",
sampleBaseDir+"PATtuple_46_1_Vcc.root",
sampleBaseDir+"PATtuple_51_1_Nu1.root",
sampleBaseDir+"PATtuple_45_1_9gZ.root",
sampleBaseDir+"PATtuple_44_1_vzI.root",
sampleBaseDir+"PATtuple_43_1_258.root",
sampleBaseDir+"PATtuple_35_1_vdT.root",
sampleBaseDir+"PATtuple_42_1_ccG.root",
sampleBaseDir+"PATtuple_41_1_Dfn.root",
sampleBaseDir+"PATtuple_40_1_VrI.root",
sampleBaseDir+"PATtuple_39_1_HbH.root",
sampleBaseDir+"PATtuple_38_1_glM.root",
sampleBaseDir+"PATtuple_37_1_GnG.root",
sampleBaseDir+"PATtuple_36_1_ZBJ.root",
sampleBaseDir+"PATtuple_33_1_1yN.root",
sampleBaseDir+"PATtuple_34_1_hDl.root",
sampleBaseDir+"PATtuple_32_1_twP.root",
sampleBaseDir+"PATtuple_31_1_A5F.root",
sampleBaseDir+"PATtuple_30_1_qqs.root",
sampleBaseDir+"PATtuple_29_1_t92.root",
sampleBaseDir+"PATtuple_28_1_45g.root",
sampleBaseDir+"PATtuple_27_1_hKt.root",
sampleBaseDir+"PATtuple_26_1_ZKb.root",
sampleBaseDir+"PATtuple_25_1_m7C.root",
sampleBaseDir+"PATtuple_24_1_rsb.root",
sampleBaseDir+"PATtuple_23_1_Dhe.root",
sampleBaseDir+"PATtuple_22_1_O0X.root",
sampleBaseDir+"PATtuple_21_1_k6T.root",
sampleBaseDir+"PATtuple_20_1_2Q2.root",
sampleBaseDir+"PATtuple_19_1_RjU.root",
sampleBaseDir+"PATtuple_18_1_3jS.root",
sampleBaseDir+"PATtuple_17_1_tZc.root",
sampleBaseDir+"PATtuple_16_1_ZRS.root",
sampleBaseDir+"PATtuple_15_1_6j6.root",
sampleBaseDir+"PATtuple_14_1_WXX.root",
sampleBaseDir+"PATtuple_13_1_uky.root",
sampleBaseDir+"PATtuple_12_1_e2I.root",
sampleBaseDir+"PATtuple_11_1_Em9.root",
sampleBaseDir+"PATtuple_10_1_scr.root",
sampleBaseDir+"PATtuple_9_1_YRg.root",
sampleBaseDir+"PATtuple_8_1_bsM.root",
sampleBaseDir+"PATtuple_7_1_nvu.root",
sampleBaseDir+"PATtuple_6_1_GSN.root",
sampleBaseDir+"PATtuple_5_1_K2a.root",
sampleBaseDir+"PATtuple_4_1_yqG.root",
sampleBaseDir+"PATtuple_3_1_zFX.root",
sampleBaseDir+"PATtuple_2_1_d7S.root",
sampleBaseDir+"PATtuple_1_1_Elm.root",
]
