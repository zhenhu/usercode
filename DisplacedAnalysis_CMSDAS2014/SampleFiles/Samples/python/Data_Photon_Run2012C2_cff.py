#sampleDataSet = '/DoublePhotonHighPt/Run2012C-PromptReco-v2/AOD'
sampleDataSet = '/DoublePhoton/Run2012C-PromptReco-v2/AOD'

# original (i.e. RECO file) release,
# not the one we plan to process them with
sampleRelease = "CMSSW_5_3_2_patch4" 
# release used to create new files with
sampleProcessRelease = "CMSSW_5_3_5" 

#sampleNumEvents = 17510610 # according to DBS, as of 30 October 2012
sampleNumEvents = 39389624

# global tag needs to be chosen to match release, trigger menu and alignment conditions.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
sampleGlobalTag = 'GR_P_V42_AN3::All'

# data quality run/lumi section selection
sampleJSON = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Prompt/Cert_190456-203002_8TeV_PromptReco_Collisions12_JSON_v2.txt"

# restrict run range (mainly to get a sample with consistent trigger configuration)

# use checkAllFilesOpened whenever possible, and noDuplicateCheck when necessary
sampleDuplicateCheckMode = "checkAllFilesOpened"

# "DATA" or "MC"
sampleType = "DATA"






samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//DoublePhoton/Data_Photon_Run2012C2_pat_20130131_1/305c779411eb21e3b1baec97cb367d9a/"
samplePatFiles = [
sampleBaseDir+"PATtuple_168_3_yrx.root",
sampleBaseDir+"PATtuple_351_3_svs.root",
sampleBaseDir+"PATtuple_465_3_I2x.root",
sampleBaseDir+"PATtuple_432_3_OOr.root",
sampleBaseDir+"PATtuple_237_3_idX.root",
sampleBaseDir+"PATtuple_145_3_x63.root",
sampleBaseDir+"PATtuple_467_3_Ryp.root",
sampleBaseDir+"PATtuple_216_3_1bm.root",
sampleBaseDir+"PATtuple_241_3_gEC.root",
sampleBaseDir+"PATtuple_565_3_9OH.root",
sampleBaseDir+"PATtuple_2_3_KyX.root",
sampleBaseDir+"PATtuple_516_3_vPS.root",
sampleBaseDir+"PATtuple_517_3_9hE.root",
sampleBaseDir+"PATtuple_611_3_EQh.root",
sampleBaseDir+"PATtuple_142_3_j5s.root",
sampleBaseDir+"PATtuple_589_3_lTF.root",
sampleBaseDir+"PATtuple_627_3_xsr.root",
sampleBaseDir+"PATtuple_509_3_uaK.root",
sampleBaseDir+"PATtuple_524_3_hlE.root",
sampleBaseDir+"PATtuple_647_3_Vsy.root",
sampleBaseDir+"PATtuple_32_3_7EU.root",
sampleBaseDir+"PATtuple_460_3_3gn.root",
sampleBaseDir+"PATtuple_569_3_XaD.root",
sampleBaseDir+"PATtuple_449_2_zsc.root",
sampleBaseDir+"PATtuple_585_2_fAf.root",
sampleBaseDir+"PATtuple_323_2_VOS.root",
sampleBaseDir+"PATtuple_408_2_wGt.root",
sampleBaseDir+"PATtuple_587_2_kV6.root",
sampleBaseDir+"PATtuple_304_2_ngx.root",
sampleBaseDir+"PATtuple_462_2_LQI.root",
sampleBaseDir+"PATtuple_539_2_j5G.root",
sampleBaseDir+"PATtuple_407_2_j4A.root",
sampleBaseDir+"PATtuple_433_2_0NQ.root",
sampleBaseDir+"PATtuple_272_2_wvN.root",
sampleBaseDir+"PATtuple_201_2_l1c.root",
sampleBaseDir+"PATtuple_80_2_geJ.root",
sampleBaseDir+"PATtuple_577_2_931.root",
sampleBaseDir+"PATtuple_1_2_hc4.root",
sampleBaseDir+"PATtuple_594_2_sVC.root",
sampleBaseDir+"PATtuple_421_2_Idv.root",
sampleBaseDir+"PATtuple_644_2_3Mt.root",
sampleBaseDir+"PATtuple_417_2_z0S.root",
sampleBaseDir+"PATtuple_554_2_cC6.root",
sampleBaseDir+"PATtuple_555_2_trD.root",
sampleBaseDir+"PATtuple_22_2_XLv.root",
sampleBaseDir+"PATtuple_33_2_452.root",
sampleBaseDir+"PATtuple_81_2_kxy.root",
sampleBaseDir+"PATtuple_409_2_m4F.root",
sampleBaseDir+"PATtuple_493_2_3bA.root",
sampleBaseDir+"PATtuple_454_2_7gC.root",
sampleBaseDir+"PATtuple_526_2_ZtK.root",
sampleBaseDir+"PATtuple_553_2_jJG.root",
sampleBaseDir+"PATtuple_256_2_hjg.root",
sampleBaseDir+"PATtuple_435_7_jyP.root",
sampleBaseDir+"PATtuple_431_6_Wp8.root",
sampleBaseDir+"PATtuple_434_6_sfS.root",
sampleBaseDir+"PATtuple_358_6_NPT.root",
sampleBaseDir+"PATtuple_490_5_yJn.root",
sampleBaseDir+"PATtuple_466_5_Cpk.root",
sampleBaseDir+"PATtuple_525_4_nlw.root",
sampleBaseDir+"PATtuple_450_4_sx1.root",
sampleBaseDir+"PATtuple_507_4_ezR.root",
sampleBaseDir+"PATtuple_588_4_wtd.root",
sampleBaseDir+"PATtuple_584_4_qCV.root",
sampleBaseDir+"PATtuple_596_4_qd8.root",
sampleBaseDir+"PATtuple_613_4_gjq.root",
sampleBaseDir+"PATtuple_564_4_1y7.root",
sampleBaseDir+"PATtuple_422_4_E4e.root",
sampleBaseDir+"PATtuple_307_4_iLi.root",
sampleBaseDir+"PATtuple_478_4_tLG.root",
sampleBaseDir+"PATtuple_630_4_bwA.root",
sampleBaseDir+"PATtuple_325_3_FBP.root",
sampleBaseDir+"PATtuple_389_3_07d.root",
sampleBaseDir+"PATtuple_350_3_8mY.root",
sampleBaseDir+"PATtuple_240_3_sKY.root",
sampleBaseDir+"PATtuple_213_3_Lag.root",
sampleBaseDir+"PATtuple_197_2_Awu.root",
sampleBaseDir+"PATtuple_275_2_uSx.root",
sampleBaseDir+"PATtuple_49_2_ina.root",
sampleBaseDir+"PATtuple_631_2_rsA.root",
sampleBaseDir+"PATtuple_320_2_mip.root",
sampleBaseDir+"PATtuple_455_2_PWw.root",
sampleBaseDir+"PATtuple_629_2_DrK.root",
sampleBaseDir+"PATtuple_267_2_2w5.root",
sampleBaseDir+"PATtuple_217_2_lso.root",
sampleBaseDir+"PATtuple_583_2_8ex.root",
sampleBaseDir+"PATtuple_236_2_a4Z.root",
sampleBaseDir+"PATtuple_628_2_e9B.root",
sampleBaseDir+"PATtuple_580_2_Bzg.root",
sampleBaseDir+"PATtuple_329_2_ID5.root",
sampleBaseDir+"PATtuple_519_2_FhI.root",
sampleBaseDir+"PATtuple_610_2_vJh.root",
sampleBaseDir+"PATtuple_112_2_VJb.root",
sampleBaseDir+"PATtuple_313_2_1rN.root",
sampleBaseDir+"PATtuple_262_2_yaf.root",
sampleBaseDir+"PATtuple_173_2_eb1.root",
sampleBaseDir+"PATtuple_520_2_Sf0.root",
sampleBaseDir+"PATtuple_397_2_ocD.root",
sampleBaseDir+"PATtuple_215_2_bND.root",
sampleBaseDir+"PATtuple_258_2_1kG.root",
sampleBaseDir+"PATtuple_39_2_xrW.root",
sampleBaseDir+"PATtuple_318_2_QXs.root",
sampleBaseDir+"PATtuple_51_2_qVW.root",
sampleBaseDir+"PATtuple_552_2_LCI.root",
sampleBaseDir+"PATtuple_324_2_Jyd.root",
sampleBaseDir+"PATtuple_528_2_mee.root",
sampleBaseDir+"PATtuple_542_2_QKK.root",
sampleBaseDir+"PATtuple_171_2_Asx.root",
sampleBaseDir+"PATtuple_301_2_eqz.root",
sampleBaseDir+"PATtuple_284_2_OHF.root",
sampleBaseDir+"PATtuple_159_2_3Os.root",
sampleBaseDir+"PATtuple_453_2_acA.root",
sampleBaseDir+"PATtuple_220_2_d4x.root",
sampleBaseDir+"PATtuple_143_2_t6E.root",
sampleBaseDir+"PATtuple_544_2_e7r.root",
sampleBaseDir+"PATtuple_195_2_pwD.root",
sampleBaseDir+"PATtuple_566_2_2ax.root",
sampleBaseDir+"PATtuple_592_2_nQC.root",
sampleBaseDir+"PATtuple_276_2_x4m.root",
sampleBaseDir+"PATtuple_68_2_E6q.root",
sampleBaseDir+"PATtuple_8_2_4ZD.root",
sampleBaseDir+"PATtuple_352_2_wME.root",
sampleBaseDir+"PATtuple_494_2_BOg.root",
sampleBaseDir+"PATtuple_227_2_MAM.root",
sampleBaseDir+"PATtuple_468_2_q84.root",
sampleBaseDir+"PATtuple_257_2_d4E.root",
sampleBaseDir+"PATtuple_259_2_mv7.root",
sampleBaseDir+"PATtuple_69_2_Jfz.root",
sampleBaseDir+"PATtuple_196_2_5UF.root",
sampleBaseDir+"PATtuple_646_2_5qS.root",
sampleBaseDir+"PATtuple_282_2_XaZ.root",
sampleBaseDir+"PATtuple_290_2_15d.root",
sampleBaseDir+"PATtuple_591_2_KrD.root",
sampleBaseDir+"PATtuple_160_2_lNV.root",
sampleBaseDir+"PATtuple_636_2_vAY.root",
sampleBaseDir+"PATtuple_279_2_uCW.root",
sampleBaseDir+"PATtuple_530_2_TLw.root",
sampleBaseDir+"PATtuple_182_2_3bB.root",
sampleBaseDir+"PATtuple_485_2_ylf.root",
sampleBaseDir+"PATtuple_458_2_DRM.root",
sampleBaseDir+"PATtuple_617_2_du6.root",
sampleBaseDir+"PATtuple_239_2_f33.root",
sampleBaseDir+"PATtuple_475_2_mm8.root",
sampleBaseDir+"PATtuple_502_2_bX7.root",
sampleBaseDir+"PATtuple_183_2_cij.root",
sampleBaseDir+"PATtuple_207_2_Wxy.root",
sampleBaseDir+"PATtuple_609_2_nnW.root",
sampleBaseDir+"PATtuple_62_2_Ja2.root",
sampleBaseDir+"PATtuple_330_2_034.root",
sampleBaseDir+"PATtuple_15_2_Ufr.root",
sampleBaseDir+"PATtuple_573_2_Hun.root",
sampleBaseDir+"PATtuple_393_2_bMD.root",
sampleBaseDir+"PATtuple_28_2_W7D.root",
sampleBaseDir+"PATtuple_232_2_qbx.root",
sampleBaseDir+"PATtuple_535_2_dxy.root",
sampleBaseDir+"PATtuple_184_2_Z8B.root",
sampleBaseDir+"PATtuple_521_2_gpO.root",
sampleBaseDir+"PATtuple_416_2_C0m.root",
sampleBaseDir+"PATtuple_107_2_xSw.root",
sampleBaseDir+"PATtuple_614_2_uCS.root",
sampleBaseDir+"PATtuple_395_2_120.root",
sampleBaseDir+"PATtuple_21_2_waZ.root",
sampleBaseDir+"PATtuple_495_2_16X.root",
sampleBaseDir+"PATtuple_561_2_ERR.root",
sampleBaseDir+"PATtuple_327_2_79s.root",
sampleBaseDir+"PATtuple_430_2_Hqv.root",
sampleBaseDir+"PATtuple_123_2_tm0.root",
sampleBaseDir+"PATtuple_579_2_qx3.root",
sampleBaseDir+"PATtuple_357_2_Z7o.root",
sampleBaseDir+"PATtuple_317_2_QCE.root",
sampleBaseDir+"PATtuple_418_2_U6K.root",
sampleBaseDir+"PATtuple_390_2_AoL.root",
sampleBaseDir+"PATtuple_242_2_y0x.root",
sampleBaseDir+"PATtuple_558_2_0L7.root",
sampleBaseDir+"PATtuple_479_2_IF4.root",
sampleBaseDir+"PATtuple_124_2_HK4.root",
sampleBaseDir+"PATtuple_590_2_epj.root",
sampleBaseDir+"PATtuple_224_2_If7.root",
sampleBaseDir+"PATtuple_90_2_fZe.root",
sampleBaseDir+"PATtuple_355_2_v7E.root",
sampleBaseDir+"PATtuple_464_2_M5J.root",
sampleBaseDir+"PATtuple_192_2_PAJ.root",
sampleBaseDir+"PATtuple_200_2_EFg.root",
sampleBaseDir+"PATtuple_506_2_qfg.root",
sampleBaseDir+"PATtuple_645_2_xjY.root",
sampleBaseDir+"PATtuple_29_2_oFs.root",
sampleBaseDir+"PATtuple_563_2_JPx.root",
sampleBaseDir+"PATtuple_541_2_Gco.root",
sampleBaseDir+"PATtuple_316_2_Bd8.root",
sampleBaseDir+"PATtuple_83_2_Fzb.root",
sampleBaseDir+"PATtuple_30_2_ZYB.root",
sampleBaseDir+"PATtuple_281_2_CBY.root",
sampleBaseDir+"PATtuple_615_2_jMK.root",
sampleBaseDir+"PATtuple_428_2_Bv2.root",
sampleBaseDir+"PATtuple_31_2_JRn.root",
sampleBaseDir+"PATtuple_356_2_eee.root",
sampleBaseDir+"PATtuple_648_2_tZT.root",
sampleBaseDir+"PATtuple_38_2_wSH.root",
sampleBaseDir+"PATtuple_359_2_mN8.root",
sampleBaseDir+"PATtuple_337_2_xUU.root",
sampleBaseDir+"PATtuple_156_2_9Kv.root",
sampleBaseDir+"PATtuple_576_2_qfP.root",
sampleBaseDir+"PATtuple_599_2_fyp.root",
sampleBaseDir+"PATtuple_221_2_Izk.root",
sampleBaseDir+"PATtuple_523_2_pwl.root",
sampleBaseDir+"PATtuple_354_2_mA7.root",
sampleBaseDir+"PATtuple_419_2_wzt.root",
sampleBaseDir+"PATtuple_285_2_jrS.root",
sampleBaseDir+"PATtuple_155_2_DJq.root",
sampleBaseDir+"PATtuple_17_2_YuP.root",
sampleBaseDir+"PATtuple_346_2_VTZ.root",
sampleBaseDir+"PATtuple_166_2_Eqc.root",
sampleBaseDir+"PATtuple_656_2_X1e.root",
sampleBaseDir+"PATtuple_501_2_ScZ.root",
sampleBaseDir+"PATtuple_66_2_jUC.root",
sampleBaseDir+"PATtuple_189_2_h4D.root",
sampleBaseDir+"PATtuple_188_2_4Wy.root",
sampleBaseDir+"PATtuple_426_2_q26.root",
sampleBaseDir+"PATtuple_367_2_0k5.root",
sampleBaseDir+"PATtuple_59_2_yTX.root",
sampleBaseDir+"PATtuple_291_2_KmY.root",
sampleBaseDir+"PATtuple_398_2_bkC.root",
sampleBaseDir+"PATtuple_608_2_8uA.root",
sampleBaseDir+"PATtuple_474_2_Ad8.root",
sampleBaseDir+"PATtuple_574_2_zVo.root",
sampleBaseDir+"PATtuple_368_2_T4N.root",
sampleBaseDir+"PATtuple_13_2_wgg.root",
sampleBaseDir+"PATtuple_489_2_Fj7.root",
sampleBaseDir+"PATtuple_96_2_76a.root",
sampleBaseDir+"PATtuple_263_2_BGS.root",
sampleBaseDir+"PATtuple_44_2_jay.root",
sampleBaseDir+"PATtuple_11_2_cFg.root",
sampleBaseDir+"PATtuple_349_1_bk6.root",
sampleBaseDir+"PATtuple_456_1_yAH.root",
sampleBaseDir+"PATtuple_619_1_ROo.root",
sampleBaseDir+"PATtuple_600_1_rnZ.root",
sampleBaseDir+"PATtuple_436_1_QSz.root",
sampleBaseDir+"PATtuple_336_1_lV1.root",
sampleBaseDir+"PATtuple_538_1_bUR.root",
sampleBaseDir+"PATtuple_602_1_Ro0.root",
sampleBaseDir+"PATtuple_423_1_Q4j.root",
sampleBaseDir+"PATtuple_360_1_hWb.root",
sampleBaseDir+"PATtuple_499_1_SfN.root",
sampleBaseDir+"PATtuple_508_1_6n7.root",
sampleBaseDir+"PATtuple_414_1_601.root",
sampleBaseDir+"PATtuple_392_1_J10.root",
sampleBaseDir+"PATtuple_223_1_7yv.root",
sampleBaseDir+"PATtuple_571_1_ef5.root",
sampleBaseDir+"PATtuple_529_1_ik4.root",
sampleBaseDir+"PATtuple_222_1_FxH.root",
sampleBaseDir+"PATtuple_277_1_uzh.root",
sampleBaseDir+"PATtuple_622_1_Nyi.root",
sampleBaseDir+"PATtuple_559_1_N1A.root",
sampleBaseDir+"PATtuple_513_1_TAy.root",
sampleBaseDir+"PATtuple_480_1_fGx.root",
sampleBaseDir+"PATtuple_424_1_YIM.root",
sampleBaseDir+"PATtuple_616_1_Sck.root",
sampleBaseDir+"PATtuple_341_1_QAE.root",
sampleBaseDir+"PATtuple_314_1_XlO.root",
sampleBaseDir+"PATtuple_570_1_NUq.root",
sampleBaseDir+"PATtuple_481_1_dru.root",
sampleBaseDir+"PATtuple_363_1_vKv.root",
sampleBaseDir+"PATtuple_328_1_pRy.root",
sampleBaseDir+"PATtuple_605_1_o4C.root",
sampleBaseDir+"PATtuple_546_1_7eE.root",
sampleBaseDir+"PATtuple_339_1_9yt.root",
sampleBaseDir+"PATtuple_203_1_B7G.root",
sampleBaseDir+"PATtuple_121_1_NJl.root",
sampleBaseDir+"PATtuple_298_1_YHC.root",
sampleBaseDir+"PATtuple_472_1_mUa.root",
sampleBaseDir+"PATtuple_311_1_qe3.root",
sampleBaseDir+"PATtuple_191_1_qxa.root",
sampleBaseDir+"PATtuple_459_1_Oy2.root",
sampleBaseDir+"PATtuple_319_1_aty.root",
sampleBaseDir+"PATtuple_442_1_p3t.root",
sampleBaseDir+"PATtuple_606_1_wWT.root",
sampleBaseDir+"PATtuple_332_1_324.root",
sampleBaseDir+"PATtuple_483_1_ZKi.root",
sampleBaseDir+"PATtuple_581_1_WVN.root",
sampleBaseDir+"PATtuple_261_1_lEc.root",
sampleBaseDir+"PATtuple_551_1_DM4.root",
sampleBaseDir+"PATtuple_269_1_oB7.root",
sampleBaseDir+"PATtuple_280_1_YBY.root",
sampleBaseDir+"PATtuple_52_1_WhQ.root",
sampleBaseDir+"PATtuple_534_1_q1f.root",
sampleBaseDir+"PATtuple_400_1_Mag.root",
sampleBaseDir+"PATtuple_547_1_RYq.root",
sampleBaseDir+"PATtuple_295_1_bMQ.root",
sampleBaseDir+"PATtuple_18_1_7S4.root",
sampleBaseDir+"PATtuple_185_2_Uev.root",
sampleBaseDir+"PATtuple_362_2_AOe.root",
sampleBaseDir+"PATtuple_437_2_u61.root",
sampleBaseDir+"PATtuple_205_2_i1g.root",
sampleBaseDir+"PATtuple_378_2_lTt.root",
sampleBaseDir+"PATtuple_230_2_nYL.root",
sampleBaseDir+"PATtuple_470_2_pYS.root",
sampleBaseDir+"PATtuple_219_2_duK.root",
sampleBaseDir+"PATtuple_607_2_w8R.root",
sampleBaseDir+"PATtuple_175_2_UzO.root",
sampleBaseDir+"PATtuple_457_2_rNg.root",
sampleBaseDir+"PATtuple_48_2_8fN.root",
sampleBaseDir+"PATtuple_271_2_jBp.root",
sampleBaseDir+"PATtuple_10_2_TBY.root",
sampleBaseDir+"PATtuple_441_2_wlT.root",
sampleBaseDir+"PATtuple_292_2_lBJ.root",
sampleBaseDir+"PATtuple_650_2_r6Y.root",
sampleBaseDir+"PATtuple_655_2_iid.root",
sampleBaseDir+"PATtuple_601_2_OJi.root",
sampleBaseDir+"PATtuple_473_2_nHr.root",
sampleBaseDir+"PATtuple_152_2_2dY.root",
sampleBaseDir+"PATtuple_632_2_n9Q.root",
sampleBaseDir+"PATtuple_447_2_PAY.root",
sampleBaseDir+"PATtuple_141_2_7AE.root",
sampleBaseDir+"PATtuple_549_2_0d4.root",
sampleBaseDir+"PATtuple_300_2_40l.root",
sampleBaseDir+"PATtuple_113_2_uC7.root",
sampleBaseDir+"PATtuple_95_2_Kc2.root",
sampleBaseDir+"PATtuple_287_2_cKr.root",
sampleBaseDir+"PATtuple_461_1_AHy.root",
sampleBaseDir+"PATtuple_415_1_t6H.root",
sampleBaseDir+"PATtuple_492_1_DqX.root",
sampleBaseDir+"PATtuple_626_1_xhC.root",
sampleBaseDir+"PATtuple_543_1_cMX.root",
sampleBaseDir+"PATtuple_567_1_xAr.root",
sampleBaseDir+"PATtuple_335_1_caE.root",
sampleBaseDir+"PATtuple_612_1_agd.root",
sampleBaseDir+"PATtuple_273_1_xUx.root",
sampleBaseDir+"PATtuple_305_1_zsb.root",
sampleBaseDir+"PATtuple_452_1_Ks9.root",
sampleBaseDir+"PATtuple_652_1_kGQ.root",
sampleBaseDir+"PATtuple_604_1_8Wv.root",
sampleBaseDir+"PATtuple_511_1_Tfs.root",
sampleBaseDir+"PATtuple_326_1_FfJ.root",
sampleBaseDir+"PATtuple_353_1_jWf.root",
sampleBaseDir+"PATtuple_510_1_cdo.root",
sampleBaseDir+"PATtuple_653_1_K8b.root",
sampleBaseDir+"PATtuple_411_1_Dhl.root",
sampleBaseDir+"PATtuple_361_1_u7f.root",
sampleBaseDir+"PATtuple_540_1_UuP.root",
sampleBaseDir+"PATtuple_338_1_Nh1.root",
sampleBaseDir+"PATtuple_514_1_b1f.root",
sampleBaseDir+"PATtuple_391_1_gx5.root",
sampleBaseDir+"PATtuple_575_1_JbE.root",
sampleBaseDir+"PATtuple_603_1_PRA.root",
sampleBaseDir+"PATtuple_522_1_oR7.root",
sampleBaseDir+"PATtuple_438_1_ecs.root",
sampleBaseDir+"PATtuple_235_1_z9u.root",
sampleBaseDir+"PATtuple_625_1_gl5.root",
sampleBaseDir+"PATtuple_518_1_zvS.root",
sampleBaseDir+"PATtuple_322_1_IQP.root",
sampleBaseDir+"PATtuple_312_1_yDK.root",
sampleBaseDir+"PATtuple_396_1_STx.root",
sampleBaseDir+"PATtuple_147_1_rFZ.root",
sampleBaseDir+"PATtuple_399_1_B0p.root",
sampleBaseDir+"PATtuple_126_1_Rn3.root",
sampleBaseDir+"PATtuple_504_1_DAo.root",
sampleBaseDir+"PATtuple_379_1_G6C.root",
sampleBaseDir+"PATtuple_294_1_3xG.root",
sampleBaseDir+"PATtuple_639_1_xyX.root",
sampleBaseDir+"PATtuple_210_1_Cw0.root",
sampleBaseDir+"PATtuple_24_1_LDZ.root",
sampleBaseDir+"PATtuple_505_1_00F.root",
sampleBaseDir+"PATtuple_247_1_cjl.root",
sampleBaseDir+"PATtuple_536_1_Rxd.root",
sampleBaseDir+"PATtuple_642_1_1hm.root",
sampleBaseDir+"PATtuple_347_1_ijH.root",
sampleBaseDir+"PATtuple_296_1_Pbh.root",
sampleBaseDir+"PATtuple_402_1_jZ0.root",
sampleBaseDir+"PATtuple_190_1_EU1.root",
sampleBaseDir+"PATtuple_54_1_Wmm.root",
sampleBaseDir+"PATtuple_293_1_aR6.root",
sampleBaseDir+"PATtuple_252_1_MCf.root",
sampleBaseDir+"PATtuple_148_1_y4e.root",
sampleBaseDir+"PATtuple_109_1_VbG.root",
sampleBaseDir+"PATtuple_283_1_hKZ.root",
sampleBaseDir+"PATtuple_366_1_v5q.root",
sampleBaseDir+"PATtuple_370_1_edI.root",
sampleBaseDir+"PATtuple_228_1_qf9.root",
sampleBaseDir+"PATtuple_249_1_tqd.root",
sampleBaseDir+"PATtuple_73_1_jZF.root",
sampleBaseDir+"PATtuple_157_1_JHr.root",
sampleBaseDir+"PATtuple_268_1_4Sp.root",
sampleBaseDir+"PATtuple_369_1_Uvn.root",
sampleBaseDir+"PATtuple_206_1_ko7.root",
sampleBaseDir+"PATtuple_297_1_lDA.root",
sampleBaseDir+"PATtuple_246_1_3aW.root",
sampleBaseDir+"PATtuple_231_1_H9c.root",
sampleBaseDir+"PATtuple_43_1_qVv.root",
sampleBaseDir+"PATtuple_377_1_h9W.root",
sampleBaseDir+"PATtuple_477_1_XSZ.root",
sampleBaseDir+"PATtuple_286_1_CQe.root",
sampleBaseDir+"PATtuple_476_1_WbO.root",
sampleBaseDir+"PATtuple_161_1_0wN.root",
sampleBaseDir+"PATtuple_376_1_n6a.root",
sampleBaseDir+"PATtuple_42_1_FRy.root",
sampleBaseDir+"PATtuple_253_1_rJx.root",
sampleBaseDir+"PATtuple_255_1_Q3r.root",
sampleBaseDir+"PATtuple_302_1_aJU.root",
sampleBaseDir+"PATtuple_194_1_6fg.root",
sampleBaseDir+"PATtuple_371_1_nPx.root",
sampleBaseDir+"PATtuple_532_1_0Y9.root",
sampleBaseDir+"PATtuple_25_1_yRD.root",
sampleBaseDir+"PATtuple_209_1_lea.root",
sampleBaseDir+"PATtuple_345_1_WQl.root",
sampleBaseDir+"PATtuple_380_1_6VT.root",
sampleBaseDir+"PATtuple_204_1_DQb.root",
sampleBaseDir+"PATtuple_265_1_9AG.root",
sampleBaseDir+"PATtuple_55_1_17O.root",
sampleBaseDir+"PATtuple_384_1_EnR.root",
sampleBaseDir+"PATtuple_250_1_Vqj.root",
sampleBaseDir+"PATtuple_110_1_JJG.root",
sampleBaseDir+"PATtuple_381_1_cAh.root",
sampleBaseDir+"PATtuple_372_1_6FS.root",
sampleBaseDir+"PATtuple_375_1_wvJ.root",
sampleBaseDir+"PATtuple_57_1_6PZ.root",
sampleBaseDir+"PATtuple_560_1_gkN.root",
sampleBaseDir+"PATtuple_595_1_hEP.root",
sampleBaseDir+"PATtuple_649_1_F3y.root",
sampleBaseDir+"PATtuple_429_1_VXV.root",
sampleBaseDir+"PATtuple_303_1_05Z.root",
sampleBaseDir+"PATtuple_515_1_PyT.root",
sampleBaseDir+"PATtuple_597_1_uam.root",
sampleBaseDir+"PATtuple_420_1_yHJ.root",
sampleBaseDir+"PATtuple_578_1_sTv.root",
sampleBaseDir+"PATtuple_643_1_S6u.root",
sampleBaseDir+"PATtuple_410_1_puj.root",
sampleBaseDir+"PATtuple_413_1_KZs.root",
sampleBaseDir+"PATtuple_308_1_98v.root",
sampleBaseDir+"PATtuple_593_1_lFT.root",
sampleBaseDir+"PATtuple_306_1_Gs6.root",
sampleBaseDir+"PATtuple_451_1_Vhm.root",
sampleBaseDir+"PATtuple_463_1_hc4.root",
sampleBaseDir+"PATtuple_388_1_q3r.root",
sampleBaseDir+"PATtuple_556_1_tnu.root",
sampleBaseDir+"PATtuple_598_1_SS4.root",
sampleBaseDir+"PATtuple_562_1_SC9.root",
sampleBaseDir+"PATtuple_334_1_dzt.root",
sampleBaseDir+"PATtuple_557_1_Cgk.root",
sampleBaseDir+"PATtuple_274_1_r5S.root",
sampleBaseDir+"PATtuple_512_1_CIN.root",
sampleBaseDir+"PATtuple_427_1_WyA.root",
sampleBaseDir+"PATtuple_169_1_xj1.root",
sampleBaseDir+"PATtuple_443_1_IdU.root",
sampleBaseDir+"PATtuple_340_1_OrT.root",
sampleBaseDir+"PATtuple_634_1_9pu.root",
sampleBaseDir+"PATtuple_266_1_w1f.root",
sampleBaseDir+"PATtuple_202_1_YkF.root",
sampleBaseDir+"PATtuple_4_1_xa9.root",
sampleBaseDir+"PATtuple_343_1_CDb.root",
sampleBaseDir+"PATtuple_637_1_V16.root",
sampleBaseDir+"PATtuple_348_1_y9l.root",
sampleBaseDir+"PATtuple_91_1_IT3.root",
sampleBaseDir+"PATtuple_640_1_z0h.root",
sampleBaseDir+"PATtuple_36_1_TQK.root",
sampleBaseDir+"PATtuple_108_1_YVI.root",
sampleBaseDir+"PATtuple_572_1_dSF.root",
sampleBaseDir+"PATtuple_469_1_AVy.root",
sampleBaseDir+"PATtuple_444_1_Cad.root",
sampleBaseDir+"PATtuple_401_1_7LN.root",
sampleBaseDir+"PATtuple_245_1_9cj.root",
sampleBaseDir+"PATtuple_67_1_F1j.root",
sampleBaseDir+"PATtuple_445_1_JrQ.root",
sampleBaseDir+"PATtuple_260_1_G4x.root",
sampleBaseDir+"PATtuple_238_1_WYv.root",
sampleBaseDir+"PATtuple_446_1_C3I.root",
sampleBaseDir+"PATtuple_53_1_pgn.root",
sampleBaseDir+"PATtuple_488_1_zJs.root",
sampleBaseDir+"PATtuple_533_1_pJf.root",
sampleBaseDir+"PATtuple_158_1_QSY.root",
sampleBaseDir+"PATtuple_500_1_V1Z.root",
sampleBaseDir+"PATtuple_270_1_9jh.root",
sampleBaseDir+"PATtuple_243_1_iBK.root",
sampleBaseDir+"PATtuple_199_1_ikk.root",
sampleBaseDir+"PATtuple_486_1_A1g.root",
sampleBaseDir+"PATtuple_88_1_9Jk.root",
sampleBaseDir+"PATtuple_487_1_Si3.root",
sampleBaseDir+"PATtuple_641_1_48U.root",
sampleBaseDir+"PATtuple_218_1_iQT.root",
sampleBaseDir+"PATtuple_94_1_75x.root",
sampleBaseDir+"PATtuple_177_1_29H.root",
sampleBaseDir+"PATtuple_179_1_yEt.root",
sampleBaseDir+"PATtuple_19_1_csS.root",
sampleBaseDir+"PATtuple_624_1_Vsf.root",
sampleBaseDir+"PATtuple_180_1_HG8.root",
sampleBaseDir+"PATtuple_6_1_Jn2.root",
sampleBaseDir+"PATtuple_226_1_NGh.root",
sampleBaseDir+"PATtuple_374_1_GYP.root",
sampleBaseDir+"PATtuple_71_1_7IW.root",
sampleBaseDir+"PATtuple_5_1_LfE.root",
sampleBaseDir+"PATtuple_264_1_VJU.root",
sampleBaseDir+"PATtuple_537_1_CT5.root",
sampleBaseDir+"PATtuple_373_1_ZHX.root",
sampleBaseDir+"PATtuple_406_1_k9C.root",
sampleBaseDir+"PATtuple_85_1_UOn.root",
sampleBaseDir+"PATtuple_78_1_aoX.root",
sampleBaseDir+"PATtuple_58_1_CSh.root",
sampleBaseDir+"PATtuple_172_1_QXQ.root",
sampleBaseDir+"PATtuple_405_1_mtF.root",
sampleBaseDir+"PATtuple_40_1_zoc.root",
sampleBaseDir+"PATtuple_84_1_J43.root",
sampleBaseDir+"PATtuple_387_1_UcR.root",
sampleBaseDir+"PATtuple_212_1_bYa.root",
sampleBaseDir+"PATtuple_404_1_L1s.root",
sampleBaseDir+"PATtuple_74_1_reR.root",
sampleBaseDir+"PATtuple_178_1_pZu.root",
sampleBaseDir+"PATtuple_89_1_Wfl.root",
sampleBaseDir+"PATtuple_72_1_1jn.root",
sampleBaseDir+"PATtuple_92_1_NPi.root",
sampleBaseDir+"PATtuple_117_1_AiI.root",
sampleBaseDir+"PATtuple_127_1_QDu.root",
sampleBaseDir+"PATtuple_181_1_4sJ.root",
sampleBaseDir+"PATtuple_382_1_i7C.root",
sampleBaseDir+"PATtuple_403_1_1RQ.root",
sampleBaseDir+"PATtuple_7_1_3nM.root",
sampleBaseDir+"PATtuple_154_1_vvR.root",
sampleBaseDir+"PATtuple_208_1_0OT.root",
sampleBaseDir+"PATtuple_229_1_tgi.root",
sampleBaseDir+"PATtuple_26_1_Tzp.root",
sampleBaseDir+"PATtuple_186_1_anq.root",
sampleBaseDir+"PATtuple_77_1_T2u.root",
sampleBaseDir+"PATtuple_111_1_CiQ.root",
sampleBaseDir+"PATtuple_125_1_wZW.root",
sampleBaseDir+"PATtuple_248_1_uLf.root",
sampleBaseDir+"PATtuple_9_1_5M7.root",
sampleBaseDir+"PATtuple_198_1_9ix.root",
sampleBaseDir+"PATtuple_76_1_hlP.root",
sampleBaseDir+"PATtuple_134_1_6Dk.root",
sampleBaseDir+"PATtuple_120_1_G0k.root",
sampleBaseDir+"PATtuple_128_1_878.root",
sampleBaseDir+"PATtuple_56_1_zZB.root",
sampleBaseDir+"PATtuple_47_1_OuB.root",
sampleBaseDir+"PATtuple_70_1_wag.root",
sampleBaseDir+"PATtuple_41_1_v25.root",
sampleBaseDir+"PATtuple_251_1_FdQ.root",
sampleBaseDir+"PATtuple_385_1_OyG.root",
sampleBaseDir+"PATtuple_86_1_8AK.root",
sampleBaseDir+"PATtuple_34_1_nMr.root",
sampleBaseDir+"PATtuple_144_1_6QH.root",
sampleBaseDir+"PATtuple_187_1_tBv.root",
sampleBaseDir+"PATtuple_82_1_LXn.root",
sampleBaseDir+"PATtuple_20_1_wxC.root",
sampleBaseDir+"PATtuple_75_1_qa8.root",
sampleBaseDir+"PATtuple_116_1_GHu.root",
sampleBaseDir+"PATtuple_60_1_r7Z.root",
sampleBaseDir+"PATtuple_146_1_TLe.root",
sampleBaseDir+"PATtuple_129_1_hc0.root",
sampleBaseDir+"PATtuple_211_1_BZU.root",
sampleBaseDir+"PATtuple_133_1_aaq.root",
sampleBaseDir+"PATtuple_119_1_UdC.root",
sampleBaseDir+"PATtuple_315_1_3g0.root",
sampleBaseDir+"PATtuple_651_1_BFa.root",
sampleBaseDir+"PATtuple_412_1_dzD.root",
sampleBaseDir+"PATtuple_586_1_LO9.root",
sampleBaseDir+"PATtuple_309_1_cjr.root",
sampleBaseDir+"PATtuple_425_1_rbS.root",
sampleBaseDir+"PATtuple_289_1_FlP.root",
sampleBaseDir+"PATtuple_496_1_2nR.root",
sampleBaseDir+"PATtuple_491_1_esG.root",
sampleBaseDir+"PATtuple_545_1_33n.root",
sampleBaseDir+"PATtuple_394_1_oUT.root",
sampleBaseDir+"PATtuple_484_1_DiF.root",
sampleBaseDir+"PATtuple_654_1_NCn.root",
sampleBaseDir+"PATtuple_633_1_h6A.root",
sampleBaseDir+"PATtuple_342_1_gnG.root",
sampleBaseDir+"PATtuple_498_1_SkH.root",
sampleBaseDir+"PATtuple_299_1_JHR.root",
sampleBaseDir+"PATtuple_620_1_4WN.root",
sampleBaseDir+"PATtuple_439_1_wEA.root",
sampleBaseDir+"PATtuple_440_1_OEj.root",
sampleBaseDir+"PATtuple_365_1_W2x.root",
sampleBaseDir+"PATtuple_225_1_jpj.root",
sampleBaseDir+"PATtuple_503_1_CQS.root",
sampleBaseDir+"PATtuple_50_1_UtK.root",
sampleBaseDir+"PATtuple_638_1_7zq.root",
sampleBaseDir+"PATtuple_548_1_IRJ.root",
sampleBaseDir+"PATtuple_244_1_mxn.root",
sampleBaseDir+"PATtuple_214_1_Ixq.root",
sampleBaseDir+"PATtuple_623_1_8Wz.root",
sampleBaseDir+"PATtuple_288_1_P2S.root",
sampleBaseDir+"PATtuple_621_1_Bre.root",
sampleBaseDir+"PATtuple_3_1_h8x.root",
sampleBaseDir+"PATtuple_618_1_roQ.root",
sampleBaseDir+"PATtuple_635_1_0mw.root",
sampleBaseDir+"PATtuple_582_1_dxl.root",
sampleBaseDir+"PATtuple_344_1_EGf.root",
sampleBaseDir+"PATtuple_176_1_ttX.root",
sampleBaseDir+"PATtuple_471_1_Glg.root",
sampleBaseDir+"PATtuple_550_1_6vF.root",
sampleBaseDir+"PATtuple_310_1_3ES.root",
sampleBaseDir+"PATtuple_170_1_KuX.root",
sampleBaseDir+"PATtuple_531_1_LSb.root",
sampleBaseDir+"PATtuple_122_1_27j.root",
sampleBaseDir+"PATtuple_35_1_FNh.root",
sampleBaseDir+"PATtuple_568_1_85P.root",
sampleBaseDir+"PATtuple_364_1_5On.root",
sampleBaseDir+"PATtuple_254_1_Ms8.root",
sampleBaseDir+"PATtuple_87_1_iip.root",
sampleBaseDir+"PATtuple_278_1_Xai.root",
sampleBaseDir+"PATtuple_331_1_UC4.root",
sampleBaseDir+"PATtuple_333_1_eZj.root",
sampleBaseDir+"PATtuple_37_1_xFm.root",
sampleBaseDir+"PATtuple_193_1_m9G.root",
sampleBaseDir+"PATtuple_527_1_QLH.root",
sampleBaseDir+"PATtuple_482_1_0Cg.root",
sampleBaseDir+"PATtuple_174_1_50f.root",
sampleBaseDir+"PATtuple_321_1_l39.root",
sampleBaseDir+"PATtuple_497_1_E3T.root",
sampleBaseDir+"PATtuple_383_1_F3N.root",
sampleBaseDir+"PATtuple_448_1_C7N.root",
sampleBaseDir+"PATtuple_386_1_ItJ.root",
sampleBaseDir+"PATtuple_61_1_Ju4.root",
sampleBaseDir+"PATtuple_93_1_LT9.root",
sampleBaseDir+"PATtuple_234_1_TMe.root",
sampleBaseDir+"PATtuple_115_1_et6.root",
sampleBaseDir+"PATtuple_16_1_I7k.root",
sampleBaseDir+"PATtuple_23_1_6lm.root",
sampleBaseDir+"PATtuple_63_1_DVG.root",
sampleBaseDir+"PATtuple_27_1_VRv.root",
sampleBaseDir+"PATtuple_233_1_rTA.root",
sampleBaseDir+"PATtuple_118_1_k6v.root",
sampleBaseDir+"PATtuple_149_1_V8I.root",
sampleBaseDir+"PATtuple_164_1_wO2.root",
sampleBaseDir+"PATtuple_165_1_AU9.root",
sampleBaseDir+"PATtuple_97_1_uUv.root",
sampleBaseDir+"PATtuple_46_1_9lx.root",
sampleBaseDir+"PATtuple_99_1_z3P.root",
sampleBaseDir+"PATtuple_150_1_8rW.root",
sampleBaseDir+"PATtuple_100_1_GWX.root",
sampleBaseDir+"PATtuple_162_1_k71.root",
sampleBaseDir+"PATtuple_45_1_u2k.root",
sampleBaseDir+"PATtuple_163_1_UB4.root",
sampleBaseDir+"PATtuple_130_1_Wao.root",
sampleBaseDir+"PATtuple_79_1_CV1.root",
sampleBaseDir+"PATtuple_135_1_MDm.root",
sampleBaseDir+"PATtuple_114_1_WE6.root",
sampleBaseDir+"PATtuple_14_1_U1Q.root",
sampleBaseDir+"PATtuple_132_1_C8P.root",
sampleBaseDir+"PATtuple_131_1_hDn.root",
sampleBaseDir+"PATtuple_167_1_qnS.root",
sampleBaseDir+"PATtuple_98_1_Dnw.root",
sampleBaseDir+"PATtuple_153_1_S6R.root",
sampleBaseDir+"PATtuple_104_1_ZWC.root",
sampleBaseDir+"PATtuple_64_1_tjL.root",
sampleBaseDir+"PATtuple_65_1_GGn.root",
sampleBaseDir+"PATtuple_12_1_bWQ.root",
sampleBaseDir+"PATtuple_151_1_kC9.root",
sampleBaseDir+"PATtuple_102_1_OBA.root",
sampleBaseDir+"PATtuple_101_1_u8t.root",
sampleBaseDir+"PATtuple_106_1_SIR.root",
sampleBaseDir+"PATtuple_136_1_eWd.root",
sampleBaseDir+"PATtuple_105_1_orC.root",
sampleBaseDir+"PATtuple_138_1_fMW.root",
sampleBaseDir+"PATtuple_139_1_WCU.root",
sampleBaseDir+"PATtuple_140_1_JaV.root",
sampleBaseDir+"PATtuple_137_1_3H3.root",
sampleBaseDir+"PATtuple_103_1_kZb.root",
]