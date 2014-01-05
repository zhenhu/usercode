sampleDataSet = '/QCD_Pt-470to600_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'  

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_8" # release used to create new files with

sampleNumEvents = 3783069

sampleXSec = 115.2 * 0.1024 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7G::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "BKGMC"
samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//QCD_Pt-470to600_MuEnrichedPt5_TuneZ2star_8TeV_pythia6/QCDMu470Pt5_pat_20131129/10b5286681675c887ef3085adebe4aeb/"
samplePatFiles = [
sampleBaseDir+"PATtuple_66_5_Geh.root",
sampleBaseDir+"PATtuple_52_6_fWQ.root",
sampleBaseDir+"PATtuple_49_5_wa1.root",
sampleBaseDir+"PATtuple_51_2_kAj.root",
sampleBaseDir+"PATtuple_72_2_oTG.root",
sampleBaseDir+"PATtuple_59_2_s2p.root",
sampleBaseDir+"PATtuple_21_2_11a.root",
sampleBaseDir+"PATtuple_54_2_Tqm.root",
sampleBaseDir+"PATtuple_65_2_l2d.root",
sampleBaseDir+"PATtuple_34_2_uLq.root",
sampleBaseDir+"PATtuple_18_2_a8i.root",
sampleBaseDir+"PATtuple_10_2_V3I.root",
sampleBaseDir+"PATtuple_69_2_Bfe.root",
sampleBaseDir+"PATtuple_6_2_IRb.root",
sampleBaseDir+"PATtuple_16_1_Qzw.root",
sampleBaseDir+"PATtuple_45_1_5EG.root",
sampleBaseDir+"PATtuple_57_1_5n8.root",
sampleBaseDir+"PATtuple_19_1_rgX.root",
sampleBaseDir+"PATtuple_61_1_oRC.root",
sampleBaseDir+"PATtuple_33_1_tPS.root",
sampleBaseDir+"PATtuple_71_1_GnN.root",
sampleBaseDir+"PATtuple_28_1_ldq.root",
sampleBaseDir+"PATtuple_15_1_X69.root",
sampleBaseDir+"PATtuple_60_1_5xM.root",
sampleBaseDir+"PATtuple_46_1_RkX.root",
sampleBaseDir+"PATtuple_30_1_PHT.root",
sampleBaseDir+"PATtuple_43_1_1kg.root",
sampleBaseDir+"PATtuple_63_1_R5Y.root",
sampleBaseDir+"PATtuple_2_1_jQ9.root",
sampleBaseDir+"PATtuple_38_1_3aE.root",
sampleBaseDir+"PATtuple_67_1_LAm.root",
sampleBaseDir+"PATtuple_12_1_y5z.root",
sampleBaseDir+"PATtuple_44_1_o31.root",
sampleBaseDir+"PATtuple_17_1_GlC.root",
sampleBaseDir+"PATtuple_47_1_ba8.root",
sampleBaseDir+"PATtuple_68_1_pL2.root",
sampleBaseDir+"PATtuple_74_1_1nL.root",
sampleBaseDir+"PATtuple_23_1_CAj.root",
sampleBaseDir+"PATtuple_64_1_CKh.root",
sampleBaseDir+"PATtuple_8_1_bga.root",
sampleBaseDir+"PATtuple_27_1_uhY.root",
sampleBaseDir+"PATtuple_56_1_I3E.root",
sampleBaseDir+"PATtuple_55_1_8zp.root",
sampleBaseDir+"PATtuple_70_1_hqI.root",
sampleBaseDir+"PATtuple_24_1_sQU.root",
sampleBaseDir+"PATtuple_9_1_Kd6.root",
sampleBaseDir+"PATtuple_58_1_GvZ.root",
sampleBaseDir+"PATtuple_62_1_wYA.root",
sampleBaseDir+"PATtuple_13_1_ZSQ.root",
sampleBaseDir+"PATtuple_41_1_7dC.root",
sampleBaseDir+"PATtuple_48_1_FRA.root",
sampleBaseDir+"PATtuple_5_1_ONQ.root",
sampleBaseDir+"PATtuple_75_1_sU3.root",
sampleBaseDir+"PATtuple_25_1_Xhy.root",
sampleBaseDir+"PATtuple_4_1_P4D.root",
sampleBaseDir+"PATtuple_53_1_xQQ.root",
sampleBaseDir+"PATtuple_50_1_vaO.root",
sampleBaseDir+"PATtuple_26_1_QD7.root",
sampleBaseDir+"PATtuple_17_1_T1o.root",
sampleBaseDir+"PATtuple_14_1_fnL.root",
sampleBaseDir+"PATtuple_7_1_DZb.root",
sampleBaseDir+"PATtuple_1_1_rCq.root",
]
