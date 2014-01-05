sampleDataSet = '/QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/Summer12_DR53X-PU_S10_START53_V7A-v2/AODSIM'

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 5998860

sampleXSec = 8148778 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7F::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "BKGMC"



samplePatDBSName=""

sampleBaseDir="/store/user/lpcdve/DisplacedLeptons/QCD_Pt_50to80_pat_20130913/demattia//QCD_Pt-50to80_TuneZ2star_8TeV_pythia6/QCD_Pt_50to80_pat_20130913/5fe3dadd93bf8608b396f970098158ed/"
samplePatFiles = [
sampleBaseDir+"PATtuple_96_1_wby.root",
sampleBaseDir+"PATtuple_92_1_gf9.root",
sampleBaseDir+"PATtuple_37_1_JtR.root",
sampleBaseDir+"PATtuple_31_1_Fl8.root",
sampleBaseDir+"PATtuple_90_1_GT7.root",
sampleBaseDir+"PATtuple_1_1_yFM.root",
sampleBaseDir+"PATtuple_29_1_g2n.root",
sampleBaseDir+"PATtuple_102_1_1n8.root",
sampleBaseDir+"PATtuple_107_1_bro.root",
sampleBaseDir+"PATtuple_25_1_ADB.root",
sampleBaseDir+"PATtuple_38_1_prQ.root",
sampleBaseDir+"PATtuple_85_1_aCs.root",
sampleBaseDir+"PATtuple_16_1_7tZ.root",
sampleBaseDir+"PATtuple_115_1_TTJ.root",
sampleBaseDir+"PATtuple_13_1_cBj.root",
sampleBaseDir+"PATtuple_47_1_uyS.root",
sampleBaseDir+"PATtuple_81_1_R0n.root",
sampleBaseDir+"PATtuple_74_1_CRr.root",
sampleBaseDir+"PATtuple_34_1_s9O.root",
sampleBaseDir+"PATtuple_82_1_Su1.root",
sampleBaseDir+"PATtuple_19_1_1oe.root",
sampleBaseDir+"PATtuple_119_1_xD0.root",
sampleBaseDir+"PATtuple_55_1_bid.root",
sampleBaseDir+"PATtuple_91_1_q8U.root",
sampleBaseDir+"PATtuple_12_1_Wcb.root",
sampleBaseDir+"PATtuple_52_1_8bW.root",
sampleBaseDir+"PATtuple_57_1_jYs.root",
sampleBaseDir+"PATtuple_61_1_Wxy.root",
sampleBaseDir+"PATtuple_10_1_UIM.root",
sampleBaseDir+"PATtuple_88_1_8xk.root",
sampleBaseDir+"PATtuple_94_1_385.root",
sampleBaseDir+"PATtuple_84_1_cSs.root",
sampleBaseDir+"PATtuple_39_1_mkE.root",
sampleBaseDir+"PATtuple_59_1_mTh.root",
sampleBaseDir+"PATtuple_23_1_52s.root",
sampleBaseDir+"PATtuple_72_1_zQf.root",
sampleBaseDir+"PATtuple_45_1_ga1.root",
sampleBaseDir+"PATtuple_56_1_Eby.root",
sampleBaseDir+"PATtuple_118_1_SPf.root",
sampleBaseDir+"PATtuple_2_1_y1E.root",
sampleBaseDir+"PATtuple_7_1_quV.root",
sampleBaseDir+"PATtuple_113_1_xxG.root",
sampleBaseDir+"PATtuple_114_1_p6h.root",
sampleBaseDir+"PATtuple_4_1_kVi.root",
sampleBaseDir+"PATtuple_48_1_ehW.root",
sampleBaseDir+"PATtuple_87_1_n1S.root",
sampleBaseDir+"PATtuple_43_1_esZ.root",
sampleBaseDir+"PATtuple_44_1_raV.root",
sampleBaseDir+"PATtuple_41_1_OyR.root",
sampleBaseDir+"PATtuple_33_1_sVP.root",
sampleBaseDir+"PATtuple_53_1_AtW.root",
sampleBaseDir+"PATtuple_117_1_Yu8.root",
sampleBaseDir+"PATtuple_97_1_Pvv.root",
sampleBaseDir+"PATtuple_83_1_SSO.root",
sampleBaseDir+"PATtuple_54_1_h0R.root",
sampleBaseDir+"PATtuple_112_1_Zej.root",
sampleBaseDir+"PATtuple_105_1_ti2.root",
sampleBaseDir+"PATtuple_14_1_spd.root",
sampleBaseDir+"PATtuple_68_1_tay.root",
sampleBaseDir+"PATtuple_42_1_LDu.root",
sampleBaseDir+"PATtuple_6_1_0qL.root",
sampleBaseDir+"PATtuple_28_1_xjQ.root",
sampleBaseDir+"PATtuple_111_1_9GS.root",
sampleBaseDir+"PATtuple_93_1_ITR.root",
sampleBaseDir+"PATtuple_62_1_nfs.root",
sampleBaseDir+"PATtuple_32_1_G2l.root",
sampleBaseDir+"PATtuple_26_1_KxE.root",
sampleBaseDir+"PATtuple_21_1_zZQ.root",
sampleBaseDir+"PATtuple_49_1_SkT.root",
sampleBaseDir+"PATtuple_5_1_aNg.root",
sampleBaseDir+"PATtuple_18_1_QtC.root",
sampleBaseDir+"PATtuple_46_1_VcC.root",
sampleBaseDir+"PATtuple_71_1_CDc.root",
sampleBaseDir+"PATtuple_65_1_mYG.root",
sampleBaseDir+"PATtuple_40_1_tjY.root",
sampleBaseDir+"PATtuple_76_1_67B.root",
sampleBaseDir+"PATtuple_30_1_xqq.root",
sampleBaseDir+"PATtuple_104_1_3H3.root",
sampleBaseDir+"PATtuple_120_1_YO0.root",
sampleBaseDir+"PATtuple_51_1_iu4.root",
sampleBaseDir+"PATtuple_100_1_jra.root",
sampleBaseDir+"PATtuple_63_1_60H.root",
sampleBaseDir+"PATtuple_8_1_9Ea.root",
sampleBaseDir+"PATtuple_22_1_hcf.root",
sampleBaseDir+"PATtuple_50_1_a2j.root",
sampleBaseDir+"PATtuple_101_1_xW8.root",
sampleBaseDir+"PATtuple_95_1_GKX.root",
sampleBaseDir+"PATtuple_15_1_xa3.root",
sampleBaseDir+"PATtuple_99_1_Rfm.root",
sampleBaseDir+"PATtuple_80_1_hcT.root",
sampleBaseDir+"PATtuple_89_1_8OB.root",
sampleBaseDir+"PATtuple_86_1_Bjh.root",
sampleBaseDir+"PATtuple_108_1_Y7F.root",
sampleBaseDir+"PATtuple_69_1_83r.root",
sampleBaseDir+"PATtuple_64_1_bOw.root",
sampleBaseDir+"PATtuple_9_1_gll.root",
sampleBaseDir+"PATtuple_17_1_hV7.root",
sampleBaseDir+"PATtuple_3_1_nkK.root",
sampleBaseDir+"PATtuple_75_1_CMh.root",
sampleBaseDir+"PATtuple_11_1_r8P.root",
sampleBaseDir+"PATtuple_103_1_KWe.root",
sampleBaseDir+"PATtuple_66_1_Nr9.root",
sampleBaseDir+"PATtuple_67_1_lsW.root",
sampleBaseDir+"PATtuple_77_1_IkQ.root",
]
