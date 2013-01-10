sampleDataSet = '/DoubleMu/Run2012C-24Aug2012-v1/AOD'

# original (i.e. RECO file) release,
# not the one we plan to process them with
sampleRelease = "CMSSW_5_3_2_patch4" 
# release used to create new files with
sampleProcessRelease = "CMSSW_5_3_5" 

sampleNumEvents = 2181586 # according to DBS, as of 29 October 2012

# global tag needs to be chosen to match release, trigger menu and alignment conditions.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
sampleGlobalTag = 'FT_53_V10_AN2::All'

# data quality run/lumi section selection
sampleJSON = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Reprocessing/Cert_198022-198523_8TeV_24Aug2012ReReco_Collisions12_JSON_MuonPhys.txt"
        
# restrict run range (mainly to get a sample with consistent trigger configuration)
sampleRunRange = [190456-99999999]

# use checkAllFilesOpened whenever possible, and noDuplicateCheck when necessary
sampleDuplicateCheckMode = "checkAllFilesOpened"

# "DATA" or "MC"
sampleType = "DATA"




samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//DoubleMu/Data_Mu_Run2012C1_pat_20121030/5e90f939b3578737f059f2a1e8e1bb4b/"
samplePatFiles = [
sampleBaseDir+"PATtuple_86_2_Hhf.root",
sampleBaseDir+"PATtuple_105_2_IzP.root",
sampleBaseDir+"PATtuple_43_2_teh.root",
sampleBaseDir+"PATtuple_84_2_z01.root",
sampleBaseDir+"PATtuple_121_2_J6Z.root",
sampleBaseDir+"PATtuple_131_2_CR2.root",
sampleBaseDir+"PATtuple_26_2_HDD.root",
sampleBaseDir+"PATtuple_92_2_NRx.root",
sampleBaseDir+"PATtuple_24_2_o3p.root",
sampleBaseDir+"PATtuple_18_1_CdJ.root",
sampleBaseDir+"PATtuple_21_1_HA7.root",
sampleBaseDir+"PATtuple_17_1_SGq.root",
sampleBaseDir+"PATtuple_16_1_oyx.root",
sampleBaseDir+"PATtuple_19_1_XkR.root",
sampleBaseDir+"PATtuple_126_1_RPf.root",
sampleBaseDir+"PATtuple_22_1_Swo.root",
sampleBaseDir+"PATtuple_109_1_Tjg.root",
sampleBaseDir+"PATtuple_32_1_kjl.root",
sampleBaseDir+"PATtuple_110_1_0q0.root",
sampleBaseDir+"PATtuple_94_1_06X.root",
sampleBaseDir+"PATtuple_89_1_7fs.root",
sampleBaseDir+"PATtuple_34_1_cNO.root",
sampleBaseDir+"PATtuple_106_1_ytl.root",
sampleBaseDir+"PATtuple_36_1_GJC.root",
sampleBaseDir+"PATtuple_119_1_1jt.root",
sampleBaseDir+"PATtuple_90_1_7uo.root",
sampleBaseDir+"PATtuple_83_1_8D8.root",
sampleBaseDir+"PATtuple_97_1_1Wm.root",
sampleBaseDir+"PATtuple_129_1_L8d.root",
sampleBaseDir+"PATtuple_107_1_Ata.root",
sampleBaseDir+"PATtuple_116_1_Y9u.root",
sampleBaseDir+"PATtuple_88_1_iZg.root",
sampleBaseDir+"PATtuple_104_1_02h.root",
sampleBaseDir+"PATtuple_82_1_TPw.root",
sampleBaseDir+"PATtuple_113_1_H9R.root",
sampleBaseDir+"PATtuple_128_1_Cei.root",
sampleBaseDir+"PATtuple_115_1_j1l.root",
sampleBaseDir+"PATtuple_74_1_sTI.root",
sampleBaseDir+"PATtuple_120_1_CfQ.root",
sampleBaseDir+"PATtuple_85_1_tlq.root",
sampleBaseDir+"PATtuple_67_1_B31.root",
sampleBaseDir+"PATtuple_73_1_nsW.root",
sampleBaseDir+"PATtuple_27_1_8dh.root",
sampleBaseDir+"PATtuple_112_1_Asa.root",
sampleBaseDir+"PATtuple_52_1_nU1.root",
sampleBaseDir+"PATtuple_30_1_cBF.root",
sampleBaseDir+"PATtuple_45_1_czn.root",
sampleBaseDir+"PATtuple_68_1_v09.root",
sampleBaseDir+"PATtuple_91_1_pXE.root",
sampleBaseDir+"PATtuple_127_1_Mly.root",
sampleBaseDir+"PATtuple_49_1_VTb.root",
sampleBaseDir+"PATtuple_101_1_0lv.root",
sampleBaseDir+"PATtuple_118_1_NjJ.root",
sampleBaseDir+"PATtuple_130_1_B4U.root",
sampleBaseDir+"PATtuple_132_1_hRk.root",
sampleBaseDir+"PATtuple_38_1_zJH.root",
sampleBaseDir+"PATtuple_42_1_YVx.root",
sampleBaseDir+"PATtuple_108_1_oPS.root",
sampleBaseDir+"PATtuple_44_1_r9v.root",
sampleBaseDir+"PATtuple_59_1_NUG.root",
sampleBaseDir+"PATtuple_71_1_w2W.root",
sampleBaseDir+"PATtuple_70_1_2J5.root",
sampleBaseDir+"PATtuple_124_1_VGF.root",
sampleBaseDir+"PATtuple_62_1_vdL.root",
sampleBaseDir+"PATtuple_64_1_EV9.root",
sampleBaseDir+"PATtuple_96_1_0iN.root",
sampleBaseDir+"PATtuple_35_1_Goi.root",
sampleBaseDir+"PATtuple_114_1_Eki.root",
sampleBaseDir+"PATtuple_63_1_dWG.root",
sampleBaseDir+"PATtuple_87_1_yKD.root",
sampleBaseDir+"PATtuple_10_1_gcb.root",
sampleBaseDir+"PATtuple_111_1_7se.root",
sampleBaseDir+"PATtuple_9_1_VyP.root",
sampleBaseDir+"PATtuple_95_1_YH1.root",
sampleBaseDir+"PATtuple_41_1_Une.root",
sampleBaseDir+"PATtuple_25_1_rnF.root",
sampleBaseDir+"PATtuple_80_1_lxa.root",
sampleBaseDir+"PATtuple_37_1_Qlv.root",
sampleBaseDir+"PATtuple_100_1_Tbs.root",
sampleBaseDir+"PATtuple_117_1_ueG.root",
sampleBaseDir+"PATtuple_61_1_icF.root",
sampleBaseDir+"PATtuple_69_1_lAd.root",
sampleBaseDir+"PATtuple_28_1_EeA.root",
sampleBaseDir+"PATtuple_99_1_zl6.root",
sampleBaseDir+"PATtuple_31_1_yun.root",
sampleBaseDir+"PATtuple_103_1_KH1.root",
sampleBaseDir+"PATtuple_125_1_WcJ.root",
sampleBaseDir+"PATtuple_50_1_mg9.root",
sampleBaseDir+"PATtuple_53_1_b2D.root",
sampleBaseDir+"PATtuple_4_1_hXe.root",
sampleBaseDir+"PATtuple_81_1_hMr.root",
sampleBaseDir+"PATtuple_66_1_RaW.root",
sampleBaseDir+"PATtuple_33_1_Txw.root",
sampleBaseDir+"PATtuple_72_1_4Lw.root",
sampleBaseDir+"PATtuple_79_1_Hsi.root",
sampleBaseDir+"PATtuple_123_1_hRw.root",
sampleBaseDir+"PATtuple_54_1_nEb.root",
sampleBaseDir+"PATtuple_122_1_RNy.root",
sampleBaseDir+"PATtuple_12_1_J1d.root",
sampleBaseDir+"PATtuple_75_1_NwV.root",
sampleBaseDir+"PATtuple_102_1_Fvw.root",
sampleBaseDir+"PATtuple_39_1_kMr.root",
sampleBaseDir+"PATtuple_48_1_NA9.root",
sampleBaseDir+"PATtuple_76_1_Gtn.root",
sampleBaseDir+"PATtuple_51_1_yJB.root",
sampleBaseDir+"PATtuple_57_1_75P.root",
sampleBaseDir+"PATtuple_98_1_Vra.root",
sampleBaseDir+"PATtuple_93_1_rEa.root",
sampleBaseDir+"PATtuple_77_1_uiB.root",
sampleBaseDir+"PATtuple_7_1_9Cl.root",
sampleBaseDir+"PATtuple_40_1_gIH.root",
sampleBaseDir+"PATtuple_65_1_hyu.root",
sampleBaseDir+"PATtuple_13_1_s3c.root",
sampleBaseDir+"PATtuple_29_1_Zj7.root",
sampleBaseDir+"PATtuple_60_1_hFz.root",
sampleBaseDir+"PATtuple_8_1_iAj.root",
sampleBaseDir+"PATtuple_56_1_qIq.root",
sampleBaseDir+"PATtuple_14_1_y9B.root",
sampleBaseDir+"PATtuple_78_1_QN9.root",
sampleBaseDir+"PATtuple_58_1_t3N.root",
sampleBaseDir+"PATtuple_47_1_yQ0.root",
sampleBaseDir+"PATtuple_46_1_P1I.root",
sampleBaseDir+"PATtuple_5_1_4Ke.root",
sampleBaseDir+"PATtuple_55_1_Fk9.root",
sampleBaseDir+"PATtuple_1_1_QeQ.root",
sampleBaseDir+"PATtuple_15_1_ybv.root",
sampleBaseDir+"PATtuple_2_1_h9y.root",
sampleBaseDir+"PATtuple_11_1_eBd.root",
sampleBaseDir+"PATtuple_23_1_ca0.root",
sampleBaseDir+"PATtuple_3_1_0PI.root",
sampleBaseDir+"PATtuple_20_1_Zcx.root",
sampleBaseDir+"PATtuple_6_1_SDC.root",
]
