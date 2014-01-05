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

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-120_MFF-50_CTau50To5000_8TeV-pythia6/HTo2LongLivedTo4F_MH120_MFF50_CTau50To5000_pat_20130123/6116ed9d2ff4828f95fa33fe25241a8f/"
samplePatFiles = [
sampleBaseDir+"PATtuple_21_1_dnr.root",
sampleBaseDir+"PATtuple_6_1_pBP.root",
sampleBaseDir+"PATtuple_44_1_fg8.root",
sampleBaseDir+"PATtuple_48_1_nbI.root",
sampleBaseDir+"PATtuple_41_1_KXX.root",
sampleBaseDir+"PATtuple_32_1_ZBq.root",
sampleBaseDir+"PATtuple_3_1_JAf.root",
sampleBaseDir+"PATtuple_23_1_a3n.root",
sampleBaseDir+"PATtuple_20_1_UJc.root",
sampleBaseDir+"PATtuple_7_1_ZOj.root",
sampleBaseDir+"PATtuple_43_1_tOT.root",
sampleBaseDir+"PATtuple_40_1_VGR.root",
sampleBaseDir+"PATtuple_38_1_vUZ.root",
sampleBaseDir+"PATtuple_28_1_QnI.root",
sampleBaseDir+"PATtuple_8_1_ReK.root",
sampleBaseDir+"PATtuple_22_1_jmy.root",
sampleBaseDir+"PATtuple_15_1_r5F.root",
sampleBaseDir+"PATtuple_11_1_XGc.root",
sampleBaseDir+"PATtuple_39_1_hGi.root",
sampleBaseDir+"PATtuple_47_1_JUB.root",
sampleBaseDir+"PATtuple_46_1_YEZ.root",
sampleBaseDir+"PATtuple_6_1_OH0.root",
sampleBaseDir+"PATtuple_14_1_cFV.root",
sampleBaseDir+"PATtuple_7_1_vjr.root",
sampleBaseDir+"PATtuple_30_1_F1G.root",
sampleBaseDir+"PATtuple_29_1_IPq.root",
sampleBaseDir+"PATtuple_9_1_eXE.root",
sampleBaseDir+"PATtuple_24_1_CaY.root",
sampleBaseDir+"PATtuple_37_1_SR2.root",
sampleBaseDir+"PATtuple_5_1_onA.root",
sampleBaseDir+"PATtuple_4_1_sKO.root",
sampleBaseDir+"PATtuple_42_1_ZrL.root",
sampleBaseDir+"PATtuple_31_1_u21.root",
sampleBaseDir+"PATtuple_36_1_ORN.root",
sampleBaseDir+"PATtuple_35_1_DtI.root",
sampleBaseDir+"PATtuple_45_1_y4u.root",
sampleBaseDir+"PATtuple_38_1_me8.root",
sampleBaseDir+"PATtuple_12_1_7Yi.root",
sampleBaseDir+"PATtuple_27_1_dp3.root",
sampleBaseDir+"PATtuple_25_1_pFx.root",
sampleBaseDir+"PATtuple_13_1_b1Y.root",
sampleBaseDir+"PATtuple_34_1_FIK.root",
sampleBaseDir+"PATtuple_18_1_uGa.root",
sampleBaseDir+"PATtuple_33_1_Raq.root",
sampleBaseDir+"PATtuple_16_1_D83.root",
sampleBaseDir+"PATtuple_26_1_NHj.root",
sampleBaseDir+"PATtuple_17_1_9AB.root",
sampleBaseDir+"PATtuple_32_1_BCh.root",
sampleBaseDir+"PATtuple_19_1_u9H.root",
sampleBaseDir+"PATtuple_10_1_nr8.root",
sampleBaseDir+"PATtuple_44_1_UFz.root",
sampleBaseDir+"PATtuple_49_1_vRM.root",
sampleBaseDir+"PATtuple_2_1_6W0.root",
sampleBaseDir+"PATtuple_1_1_w4u.root",
sampleBaseDir+"PATtuple_50_1_MbA.root",
]
