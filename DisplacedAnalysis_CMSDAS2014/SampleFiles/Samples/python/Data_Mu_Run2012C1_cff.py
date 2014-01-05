sampleDataSet = '/DoubleMu/Run2012C-24Aug2012-v1/AOD'

# original (i.e. RECO file) release,
# not the one we plan to process them with
sampleRelease = "CMSSW_5_3_2_patch4" 
# release used to create new files with
sampleProcessRelease = "CMSSW_5_3_5" 

sampleNumEvents = 2181586 # according to DBS, as of 29 October 2012

# global tag needs to be chosen to match release, trigger menu and alignment conditions.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
sampleGlobalTag = 'FT_53_V10_AN3::All'

# data quality run/lumi section selection
sampleJSON = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Reprocessing/Cert_198022-198523_8TeV_24Aug2012ReReco_Collisions12_JSON_MuonPhys.txt"
        
# restrict run range (mainly to get a sample with consistent trigger configuration)

# use checkAllFilesOpened whenever possible, and noDuplicateCheck when necessary
sampleDuplicateCheckMode = "checkAllFilesOpened"

# "DATA" or "MC"
sampleType = "DATA"





samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//DoubleMu/Data_Mu_Run2012C1_pat_20130125/de735588d930554b0b4cf64aec119850/"
samplePatFiles = [
sampleBaseDir+"PATtuple_93_3_8kb.root",
sampleBaseDir+"PATtuple_89_3_PPl.root",
sampleBaseDir+"PATtuple_94_3_Ei0.root",
sampleBaseDir+"PATtuple_85_3_VQ0.root",
sampleBaseDir+"PATtuple_77_3_gD2.root",
sampleBaseDir+"PATtuple_131_2_etw.root",
sampleBaseDir+"PATtuple_106_2_GtX.root",
sampleBaseDir+"PATtuple_88_2_bs9.root",
sampleBaseDir+"PATtuple_90_2_Z3v.root",
sampleBaseDir+"PATtuple_104_2_gTX.root",
sampleBaseDir+"PATtuple_92_2_04u.root",
sampleBaseDir+"PATtuple_57_2_vZi.root",
sampleBaseDir+"PATtuple_120_2_4zb.root",
sampleBaseDir+"PATtuple_121_2_BbA.root",
sampleBaseDir+"PATtuple_119_2_Z6P.root",
sampleBaseDir+"PATtuple_116_2_Uwn.root",
sampleBaseDir+"PATtuple_100_2_WBB.root",
sampleBaseDir+"PATtuple_117_2_MNu.root",
sampleBaseDir+"PATtuple_40_2_C5m.root",
sampleBaseDir+"PATtuple_59_2_75p.root",
sampleBaseDir+"PATtuple_72_2_Imp.root",
sampleBaseDir+"PATtuple_68_2_pve.root",
sampleBaseDir+"PATtuple_9_2_5K2.root",
sampleBaseDir+"PATtuple_74_2_E1s.root",
sampleBaseDir+"PATtuple_63_2_hnJ.root",
sampleBaseDir+"PATtuple_67_2_Psx.root",
sampleBaseDir+"PATtuple_58_2_2tG.root",
sampleBaseDir+"PATtuple_37_2_7yi.root",
sampleBaseDir+"PATtuple_49_2_N6Z.root",
sampleBaseDir+"PATtuple_84_2_nFc.root",
sampleBaseDir+"PATtuple_56_2_DZg.root",
sampleBaseDir+"PATtuple_97_2_qrS.root",
sampleBaseDir+"PATtuple_62_2_QLK.root",
sampleBaseDir+"PATtuple_73_2_YSQ.root",
sampleBaseDir+"PATtuple_50_2_x3j.root",
sampleBaseDir+"PATtuple_98_2_VGz.root",
sampleBaseDir+"PATtuple_70_2_wxN.root",
sampleBaseDir+"PATtuple_55_2_aCk.root",
sampleBaseDir+"PATtuple_110_2_ila.root",
sampleBaseDir+"PATtuple_51_2_MuR.root",
sampleBaseDir+"PATtuple_122_2_dFj.root",
sampleBaseDir+"PATtuple_61_2_5CX.root",
sampleBaseDir+"PATtuple_101_2_c9S.root",
sampleBaseDir+"PATtuple_81_2_NcY.root",
sampleBaseDir+"PATtuple_96_2_bRq.root",
sampleBaseDir+"PATtuple_54_2_cbw.root",
sampleBaseDir+"PATtuple_41_2_gZG.root",
sampleBaseDir+"PATtuple_125_2_XDh.root",
sampleBaseDir+"PATtuple_79_2_pmO.root",
sampleBaseDir+"PATtuple_65_2_fx4.root",
sampleBaseDir+"PATtuple_99_2_w25.root",
sampleBaseDir+"PATtuple_64_2_bXa.root",
sampleBaseDir+"PATtuple_123_2_dn8.root",
sampleBaseDir+"PATtuple_47_2_fcr.root",
sampleBaseDir+"PATtuple_115_2_oE3.root",
sampleBaseDir+"PATtuple_66_2_8pJ.root",
sampleBaseDir+"PATtuple_78_2_jef.root",
sampleBaseDir+"PATtuple_80_2_adD.root",
sampleBaseDir+"PATtuple_76_2_ft4.root",
sampleBaseDir+"PATtuple_102_2_jrN.root",
sampleBaseDir+"PATtuple_95_2_pfh.root",
sampleBaseDir+"PATtuple_75_2_tuh.root",
sampleBaseDir+"PATtuple_52_1_OnR.root",
sampleBaseDir+"PATtuple_28_1_uIs.root",
sampleBaseDir+"PATtuple_26_1_fCh.root",
sampleBaseDir+"PATtuple_34_1_D9F.root",
sampleBaseDir+"PATtuple_43_1_mWI.root",
sampleBaseDir+"PATtuple_24_1_K4b.root",
sampleBaseDir+"PATtuple_46_1_xGj.root",
sampleBaseDir+"PATtuple_38_1_8Ku.root",
sampleBaseDir+"PATtuple_42_1_EEf.root",
sampleBaseDir+"PATtuple_18_1_0Cp.root",
sampleBaseDir+"PATtuple_129_1_EMz.root",
sampleBaseDir+"PATtuple_44_1_isC.root",
sampleBaseDir+"PATtuple_12_1_gcO.root",
sampleBaseDir+"PATtuple_126_1_Z5G.root",
sampleBaseDir+"PATtuple_25_1_vUt.root",
sampleBaseDir+"PATtuple_107_1_gXt.root",
sampleBaseDir+"PATtuple_8_1_Qr5.root",
sampleBaseDir+"PATtuple_132_1_wrt.root",
sampleBaseDir+"PATtuple_45_1_3y8.root",
sampleBaseDir+"PATtuple_21_1_5Jz.root",
sampleBaseDir+"PATtuple_1_1_IND.root",
sampleBaseDir+"PATtuple_19_1_w8k.root",
sampleBaseDir+"PATtuple_113_1_IOQ.root",
sampleBaseDir+"PATtuple_71_1_1Sg.root",
sampleBaseDir+"PATtuple_53_1_M5T.root",
sampleBaseDir+"PATtuple_128_1_Pyd.root",
sampleBaseDir+"PATtuple_83_1_Xuz.root",
sampleBaseDir+"PATtuple_16_1_1uZ.root",
sampleBaseDir+"PATtuple_10_1_jwv.root",
sampleBaseDir+"PATtuple_112_1_DEF.root",
sampleBaseDir+"PATtuple_114_1_xTR.root",
sampleBaseDir+"PATtuple_32_1_wIA.root",
sampleBaseDir+"PATtuple_17_1_bma.root",
sampleBaseDir+"PATtuple_30_1_Zrd.root",
sampleBaseDir+"PATtuple_39_1_gWb.root",
sampleBaseDir+"PATtuple_108_1_ccl.root",
sampleBaseDir+"PATtuple_127_1_Qqq.root",
sampleBaseDir+"PATtuple_124_1_p5w.root",
sampleBaseDir+"PATtuple_27_1_74C.root",
sampleBaseDir+"PATtuple_36_1_thd.root",
sampleBaseDir+"PATtuple_87_1_D5L.root",
sampleBaseDir+"PATtuple_23_1_967.root",
sampleBaseDir+"PATtuple_118_1_3RX.root",
sampleBaseDir+"PATtuple_130_1_U8O.root",
sampleBaseDir+"PATtuple_14_1_Gve.root",
sampleBaseDir+"PATtuple_22_1_Opq.root",
sampleBaseDir+"PATtuple_105_1_0xA.root",
sampleBaseDir+"PATtuple_109_1_g6g.root",
sampleBaseDir+"PATtuple_103_1_aol.root",
sampleBaseDir+"PATtuple_13_1_RAC.root",
sampleBaseDir+"PATtuple_111_1_Ngs.root",
sampleBaseDir+"PATtuple_11_1_v4o.root",
sampleBaseDir+"PATtuple_91_1_Chn.root",
sampleBaseDir+"PATtuple_20_1_MqR.root",
sampleBaseDir+"PATtuple_82_1_fy2.root",
sampleBaseDir+"PATtuple_86_1_xsD.root",
sampleBaseDir+"PATtuple_60_1_hfj.root",
sampleBaseDir+"PATtuple_69_1_R5b.root",
sampleBaseDir+"PATtuple_7_1_Pug.root",
sampleBaseDir+"PATtuple_4_1_TRg.root",
sampleBaseDir+"PATtuple_31_1_dlz.root",
sampleBaseDir+"PATtuple_29_1_jTM.root",
sampleBaseDir+"PATtuple_35_1_jHk.root",
sampleBaseDir+"PATtuple_2_1_XdF.root",
sampleBaseDir+"PATtuple_33_1_9XF.root",
sampleBaseDir+"PATtuple_48_1_R58.root",
sampleBaseDir+"PATtuple_15_1_6qr.root",
sampleBaseDir+"PATtuple_3_1_X13.root",
sampleBaseDir+"PATtuple_5_1_86t.root",
sampleBaseDir+"PATtuple_6_1_4Vl.root",
]