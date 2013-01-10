sampleDataSet = '/HTo2LongLivedTo4F_MH-1000_MFF-20_CTau1p5To150_8TeV-pythia6/Summer12_DR53X-DEBUG_PU_S10_START53_V7A-v2/AODSIM'  

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




samplePatDBSName="/HTo2LongLivedTo4F_MH-1000_MFF-20_CTau1p5To150_8TeV-pythia6/ejclemen-HTo2LongLivedTo4F_MH1000_MFF20_CTau1p5To150_pat_20130103-41608ddebc02a57cd9f3d8f6ae282ec6/USER"

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//HTo2LongLivedTo4F_MH-1000_MFF-20_CTau1p5To150_8TeV-pythia6/HTo2LongLivedTo4F_MH1000_MFF20_CTau1p5To150_pat_20130103/41608ddebc02a57cd9f3d8f6ae282ec6/"
samplePatFiles = [
sampleBaseDir+"PATtuple_21_2_ogh.root",
sampleBaseDir+"PATtuple_1_2_q91.root",
sampleBaseDir+"PATtuple_19_2_vA2.root",
sampleBaseDir+"PATtuple_49_1_TZ9.root",
sampleBaseDir+"PATtuple_48_1_fnU.root",
sampleBaseDir+"PATtuple_47_1_KS8.root",
sampleBaseDir+"PATtuple_46_1_pAu.root",
sampleBaseDir+"PATtuple_45_1_zRg.root",
sampleBaseDir+"PATtuple_42_1_5LQ.root",
sampleBaseDir+"PATtuple_44_1_d5t.root",
sampleBaseDir+"PATtuple_38_1_Avy.root",
sampleBaseDir+"PATtuple_50_1_Pvs.root",
sampleBaseDir+"PATtuple_35_1_sv5.root",
sampleBaseDir+"PATtuple_43_1_8zZ.root",
sampleBaseDir+"PATtuple_37_1_POj.root",
sampleBaseDir+"PATtuple_36_1_7MC.root",
sampleBaseDir+"PATtuple_40_1_p1y.root",
sampleBaseDir+"PATtuple_41_1_TPY.root",
sampleBaseDir+"PATtuple_39_1_6Y9.root",
sampleBaseDir+"PATtuple_34_1_ZRM.root",
sampleBaseDir+"PATtuple_32_1_wc9.root",
sampleBaseDir+"PATtuple_33_1_zu1.root",
sampleBaseDir+"PATtuple_31_1_EOD.root",
sampleBaseDir+"PATtuple_30_1_Wv4.root",
sampleBaseDir+"PATtuple_26_1_aoI.root",
sampleBaseDir+"PATtuple_29_1_8nd.root",
sampleBaseDir+"PATtuple_27_1_xcG.root",
sampleBaseDir+"PATtuple_28_1_dxr.root",
sampleBaseDir+"PATtuple_23_1_7iD.root",
sampleBaseDir+"PATtuple_25_1_Eh0.root",
sampleBaseDir+"PATtuple_24_1_Bna.root",
sampleBaseDir+"PATtuple_22_1_Rca.root",
sampleBaseDir+"PATtuple_20_1_A8h.root",
sampleBaseDir+"PATtuple_18_1_nbc.root",
sampleBaseDir+"PATtuple_16_1_J92.root",
sampleBaseDir+"PATtuple_17_1_rf4.root",
sampleBaseDir+"PATtuple_15_1_PJH.root",
sampleBaseDir+"PATtuple_8_1_ph5.root",
sampleBaseDir+"PATtuple_11_1_JUJ.root",
sampleBaseDir+"PATtuple_9_1_IkA.root",
sampleBaseDir+"PATtuple_7_1_83D.root",
sampleBaseDir+"PATtuple_10_1_AnD.root",
sampleBaseDir+"PATtuple_13_1_8Dn.root",
sampleBaseDir+"PATtuple_14_1_AH2.root",
sampleBaseDir+"PATtuple_12_1_0NF.root",
sampleBaseDir+"PATtuple_3_1_ORw.root",
sampleBaseDir+"PATtuple_5_1_m29.root",
sampleBaseDir+"PATtuple_6_1_nxC.root",
sampleBaseDir+"PATtuple_4_1_ucR.root",
sampleBaseDir+"PATtuple_2_1_ZbA.root",
]
