sampleDataSet = '/DoublePhotonHighPt/Run2012D-PromptReco-v1/AOD'

# original (i.e. RECO file) release,
# not the one we plan to process them with
sampleRelease = "CMSSW_5_3_4" 
# release used to create new files with
sampleProcessRelease = "CMSSW_5_3_5" 

sampleNumEvents = 20060017 # according to DBS, as of 30 October 2012

# global tag needs to be chosen to match release, trigger menu and alignment conditions.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
sampleGlobalTag = 'FT_P_V42_AN3::All'

# data quality run/lumi section selection
sampleJSON = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Prompt/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt"

# restrict run range (mainly to get a sample with consistent trigger configuration)
sampleRunRange = [190456-99999999]

# use checkAllFilesOpened whenever possible, and noDuplicateCheck when necessary
sampleDuplicateCheckMode = "checkAllFilesOpened"

# "DATA" or "MC"
sampleType = "DATA"





samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//DoublePhotonHighPt/Data_Photon_Run2012D1_pat_20130102/2a372f40071b596743f1b75f6fed579c/"
samplePatFiles = [
sampleBaseDir+"PATtuple_498_0_Kdh.root",
sampleBaseDir+"PATtuple_582_0_5gx.root",
sampleBaseDir+"PATtuple_194_3_HDi.root",
sampleBaseDir+"PATtuple_383_3_sVM.root",
sampleBaseDir+"PATtuple_497_0_RTM.root",
sampleBaseDir+"PATtuple_502_0_Sxa.root",
sampleBaseDir+"PATtuple_500_0_Ufb.root",
sampleBaseDir+"PATtuple_268_3_ecJ.root",
sampleBaseDir+"PATtuple_142_3_VRy.root",
sampleBaseDir+"PATtuple_523_0_t5z.root",
sampleBaseDir+"PATtuple_522_0_KYN.root",
sampleBaseDir+"PATtuple_157_3_eBP.root",
sampleBaseDir+"PATtuple_499_0_kJF.root",
sampleBaseDir+"PATtuple_570_0_6iz.root",
sampleBaseDir+"PATtuple_525_0_uPK.root",
sampleBaseDir+"PATtuple_287_3_v58.root",
sampleBaseDir+"PATtuple_488_0_R1W.root",
sampleBaseDir+"PATtuple_493_0_M2u.root",
sampleBaseDir+"PATtuple_524_0_4I7.root",
sampleBaseDir+"PATtuple_521_0_R45.root",
sampleBaseDir+"PATtuple_324_3_I5w.root",
sampleBaseDir+"PATtuple_539_0_Igx.root",
sampleBaseDir+"PATtuple_490_0_5IT.root",
sampleBaseDir+"PATtuple_566_0_88A.root",
sampleBaseDir+"PATtuple_579_0_g90.root",
sampleBaseDir+"PATtuple_17_3_FyU.root",
sampleBaseDir+"PATtuple_504_0_bwR.root",
sampleBaseDir+"PATtuple_130_3_xYo.root",
sampleBaseDir+"PATtuple_128_3_Vfy.root",
sampleBaseDir+"PATtuple_501_0_tPz.root",
sampleBaseDir+"PATtuple_505_0_pb6.root",
sampleBaseDir+"PATtuple_511_0_x2C.root",
sampleBaseDir+"PATtuple_517_0_uBI.root",
sampleBaseDir+"PATtuple_495_0_vDc.root",
sampleBaseDir+"PATtuple_513_0_sQc.root",
sampleBaseDir+"PATtuple_496_0_HtE.root",
sampleBaseDir+"PATtuple_388_3_WYK.root",
sampleBaseDir+"PATtuple_492_0_vui.root",
sampleBaseDir+"PATtuple_506_0_Bpg.root",
sampleBaseDir+"PATtuple_510_0_Rj9.root",
sampleBaseDir+"PATtuple_569_0_F56.root",
sampleBaseDir+"PATtuple_519_0_Y2r.root",
sampleBaseDir+"PATtuple_494_0_OGQ.root",
sampleBaseDir+"PATtuple_96_3_APB.root",
sampleBaseDir+"PATtuple_141_3_ojt.root",
sampleBaseDir+"PATtuple_482_3_5Dy.root",
sampleBaseDir+"PATtuple_479_3_wR4.root",
sampleBaseDir+"PATtuple_165_3_15j.root",
sampleBaseDir+"PATtuple_253_3_XSS.root",
sampleBaseDir+"PATtuple_363_2_gD9.root",
sampleBaseDir+"PATtuple_449_2_PdB.root",
sampleBaseDir+"PATtuple_384_2_VVN.root",
sampleBaseDir+"PATtuple_530_0_QU3.root",
sampleBaseDir+"PATtuple_326_2_Og4.root",
sampleBaseDir+"PATtuple_282_3_Jkn.root",
sampleBaseDir+"PATtuple_118_2_mXk.root",
sampleBaseDir+"PATtuple_289_2_lMi.root",
sampleBaseDir+"PATtuple_1_3_s1y.root",
sampleBaseDir+"PATtuple_486_2_ySI.root",
sampleBaseDir+"PATtuple_373_2_Mka.root",
sampleBaseDir+"PATtuple_393_2_Kmm.root",
sampleBaseDir+"PATtuple_470_2_05U.root",
sampleBaseDir+"PATtuple_301_2_bBT.root",
sampleBaseDir+"PATtuple_409_2_nEa.root",
sampleBaseDir+"PATtuple_475_2_G1x.root",
sampleBaseDir+"PATtuple_306_2_bDs.root",
sampleBaseDir+"PATtuple_538_0_oRM.root",
sampleBaseDir+"PATtuple_531_0_fqd.root",
sampleBaseDir+"PATtuple_467_2_v0y.root",
sampleBaseDir+"PATtuple_481_2_xxF.root",
sampleBaseDir+"PATtuple_395_2_9fX.root",
sampleBaseDir+"PATtuple_587_0_0JZ.root",
sampleBaseDir+"PATtuple_185_2_59R.root",
sampleBaseDir+"PATtuple_548_0_7sG.root",
sampleBaseDir+"PATtuple_307_2_pda.root",
sampleBaseDir+"PATtuple_396_2_NJR.root",
sampleBaseDir+"PATtuple_451_2_t1j.root",
sampleBaseDir+"PATtuple_114_3_kYE.root",
sampleBaseDir+"PATtuple_313_2_Cl9.root",
sampleBaseDir+"PATtuple_477_2_b8w.root",
sampleBaseDir+"PATtuple_355_2_1Oa.root",
sampleBaseDir+"PATtuple_375_2_IXL.root",
sampleBaseDir+"PATtuple_537_0_Ytz.root",
sampleBaseDir+"PATtuple_575_0_eZy.root",
sampleBaseDir+"PATtuple_576_0_eFh.root",
sampleBaseDir+"PATtuple_196_2_g9I.root",
sampleBaseDir+"PATtuple_341_2_pNX.root",
sampleBaseDir+"PATtuple_55_3_NHX.root",
sampleBaseDir+"PATtuple_120_2_tWk.root",
sampleBaseDir+"PATtuple_366_2_RzL.root",
sampleBaseDir+"PATtuple_79_2_e5b.root",
sampleBaseDir+"PATtuple_121_2_NPD.root",
sampleBaseDir+"PATtuple_444_2_vGb.root",
sampleBaseDir+"PATtuple_108_2_Jtb.root",
sampleBaseDir+"PATtuple_358_2_n2x.root",
sampleBaseDir+"PATtuple_154_2_PQy.root",
sampleBaseDir+"PATtuple_273_2_lZz.root",
sampleBaseDir+"PATtuple_583_0_Ptr.root",
sampleBaseDir+"PATtuple_413_2_Y5I.root",
sampleBaseDir+"PATtuple_380_2_7sZ.root",
sampleBaseDir+"PATtuple_271_2_9BF.root",
sampleBaseDir+"PATtuple_337_2_0rp.root",
sampleBaseDir+"PATtuple_452_2_V3l.root",
sampleBaseDir+"PATtuple_270_2_AW7.root",
sampleBaseDir+"PATtuple_199_2_0ki.root",
sampleBaseDir+"PATtuple_281_2_vHi.root",
sampleBaseDir+"PATtuple_98_2_18F.root",
sampleBaseDir+"PATtuple_16_2_LVo.root",
sampleBaseDir+"PATtuple_66_2_UWY.root",
sampleBaseDir+"PATtuple_348_2_qg6.root",
sampleBaseDir+"PATtuple_344_2_1ut.root",
sampleBaseDir+"PATtuple_345_2_XR1.root",
sampleBaseDir+"PATtuple_378_2_EIT.root",
sampleBaseDir+"PATtuple_536_0_Uab.root",
sampleBaseDir+"PATtuple_514_0_BhR.root",
sampleBaseDir+"PATtuple_274_2_y8u.root",
sampleBaseDir+"PATtuple_27_2_YLn.root",
sampleBaseDir+"PATtuple_415_2_HJG.root",
sampleBaseDir+"PATtuple_364_2_Nwo.root",
sampleBaseDir+"PATtuple_447_2_ytn.root",
sampleBaseDir+"PATtuple_119_2_Ru0.root",
sampleBaseDir+"PATtuple_414_2_vYH.root",
sampleBaseDir+"PATtuple_430_2_fn1.root",
sampleBaseDir+"PATtuple_328_2_rzX.root",
sampleBaseDir+"PATtuple_404_2_Lj5.root",
sampleBaseDir+"PATtuple_379_2_w8L.root",
sampleBaseDir+"PATtuple_131_3_sVW.root",
sampleBaseDir+"PATtuple_365_2_E0p.root",
sampleBaseDir+"PATtuple_346_2_eAt.root",
sampleBaseDir+"PATtuple_377_2_1ro.root",
sampleBaseDir+"PATtuple_10_2_fLu.root",
sampleBaseDir+"PATtuple_541_0_a9s.root",
sampleBaseDir+"PATtuple_421_2_Rjh.root",
sampleBaseDir+"PATtuple_535_0_5U5.root",
sampleBaseDir+"PATtuple_127_2_fIP.root",
sampleBaseDir+"PATtuple_263_2_3TZ.root",
sampleBaseDir+"PATtuple_7_2_U2L.root",
sampleBaseDir+"PATtuple_5_2_Xgy.root",
sampleBaseDir+"PATtuple_203_2_7Ha.root",
sampleBaseDir+"PATtuple_418_2_XDR.root",
sampleBaseDir+"PATtuple_368_2_z2p.root",
sampleBaseDir+"PATtuple_462_2_Krd.root",
sampleBaseDir+"PATtuple_392_4_vMQ.root",
sampleBaseDir+"PATtuple_586_0_Eeu.root",
sampleBaseDir+"PATtuple_304_3_ars.root",
sampleBaseDir+"PATtuple_491_0_5mw.root",
sampleBaseDir+"PATtuple_489_0_RtA.root",
sampleBaseDir+"PATtuple_305_3_zXe.root",
sampleBaseDir+"PATtuple_123_2_GJ1.root",
sampleBaseDir+"PATtuple_382_2_2j7.root",
sampleBaseDir+"PATtuple_204_2_n66.root",
sampleBaseDir+"PATtuple_318_2_ESs.root",
sampleBaseDir+"PATtuple_12_2_5A8.root",
sampleBaseDir+"PATtuple_195_2_2F4.root",
sampleBaseDir+"PATtuple_435_2_jVk.root",
sampleBaseDir+"PATtuple_293_2_yiP.root",
sampleBaseDir+"PATtuple_39_2_oC4.root",
sampleBaseDir+"PATtuple_294_2_nfZ.root",
sampleBaseDir+"PATtuple_269_2_RJT.root",
sampleBaseDir+"PATtuple_584_0_u2H.root",
sampleBaseDir+"PATtuple_240_2_iEt.root",
sampleBaseDir+"PATtuple_223_2_byO.root",
sampleBaseDir+"PATtuple_197_2_Zug.root",
sampleBaseDir+"PATtuple_68_2_eAe.root",
sampleBaseDir+"PATtuple_283_2_BB2.root",
sampleBaseDir+"PATtuple_163_2_FfT.root",
sampleBaseDir+"PATtuple_217_2_Pf1.root",
sampleBaseDir+"PATtuple_381_2_RTZ.root",
sampleBaseDir+"PATtuple_389_2_w7u.root",
sampleBaseDir+"PATtuple_115_1_Kd1.root",
sampleBaseDir+"PATtuple_340_1_HtY.root",
sampleBaseDir+"PATtuple_25_1_KQJ.root",
sampleBaseDir+"PATtuple_385_1_wqm.root",
sampleBaseDir+"PATtuple_567_0_rnr.root",
sampleBaseDir+"PATtuple_339_1_XPO.root",
sampleBaseDir+"PATtuple_186_1_cqi.root",
sampleBaseDir+"PATtuple_402_1_sN3.root",
sampleBaseDir+"PATtuple_89_1_xJe.root",
sampleBaseDir+"PATtuple_564_0_UTy.root",
sampleBaseDir+"PATtuple_542_0_LCv.root",
sampleBaseDir+"PATtuple_459_1_j6S.root",
sampleBaseDir+"PATtuple_291_1_VKU.root",
sampleBaseDir+"PATtuple_160_1_Bi7.root",
sampleBaseDir+"PATtuple_360_1_NRM.root",
sampleBaseDir+"PATtuple_422_1_2jm.root",
sampleBaseDir+"PATtuple_212_1_jNF.root",
sampleBaseDir+"PATtuple_394_1_q1T.root",
sampleBaseDir+"PATtuple_398_1_CQR.root",
sampleBaseDir+"PATtuple_113_1_n9e.root",
sampleBaseDir+"PATtuple_171_1_xDL.root",
sampleBaseDir+"PATtuple_38_1_2WE.root",
sampleBaseDir+"PATtuple_236_1_34Z.root",
sampleBaseDir+"PATtuple_99_1_Ddq.root",
sampleBaseDir+"PATtuple_400_1_RWS.root",
sampleBaseDir+"PATtuple_320_2_qoD.root",
sampleBaseDir+"PATtuple_48_2_FVi.root",
sampleBaseDir+"PATtuple_361_1_bQ1.root",
sampleBaseDir+"PATtuple_92_1_CCZ.root",
sampleBaseDir+"PATtuple_290_1_tm5.root",
sampleBaseDir+"PATtuple_40_2_XLu.root",
sampleBaseDir+"PATtuple_456_1_cUx.root",
sampleBaseDir+"PATtuple_457_1_ae3.root",
sampleBaseDir+"PATtuple_18_1_kki.root",
sampleBaseDir+"PATtuple_6_1_v5x.root",
sampleBaseDir+"PATtuple_357_1_HrK.root",
sampleBaseDir+"PATtuple_376_1_DB4.root",
sampleBaseDir+"PATtuple_563_0_6pf.root",
sampleBaseDir+"PATtuple_334_1_Bt0.root",
sampleBaseDir+"PATtuple_126_1_OQB.root",
sampleBaseDir+"PATtuple_238_1_265.root",
sampleBaseDir+"PATtuple_88_2_Gvi.root",
sampleBaseDir+"PATtuple_351_2_jnt.root",
sampleBaseDir+"PATtuple_26_3_5IV.root",
sampleBaseDir+"PATtuple_214_3_USd.root",
sampleBaseDir+"PATtuple_91_2_53r.root",
sampleBaseDir+"PATtuple_192_2_ckL.root",
sampleBaseDir+"PATtuple_483_2_MHK.root",
sampleBaseDir+"PATtuple_213_2_8xo.root",
sampleBaseDir+"PATtuple_432_2_raz.root",
sampleBaseDir+"PATtuple_222_2_2Hq.root",
sampleBaseDir+"PATtuple_315_2_5I1.root",
sampleBaseDir+"PATtuple_512_0_gFB.root",
sampleBaseDir+"PATtuple_443_2_po8.root",
sampleBaseDir+"PATtuple_450_2_Odv.root",
sampleBaseDir+"PATtuple_336_2_mfp.root",
sampleBaseDir+"PATtuple_424_2_A9I.root",
sampleBaseDir+"PATtuple_350_2_S4r.root",
sampleBaseDir+"PATtuple_256_2_Nj0.root",
sampleBaseDir+"PATtuple_95_2_e32.root",
sampleBaseDir+"PATtuple_138_2_3xe.root",
sampleBaseDir+"PATtuple_472_2_bjh.root",
sampleBaseDir+"PATtuple_139_2_Khl.root",
sampleBaseDir+"PATtuple_316_3_xl2.root",
sampleBaseDir+"PATtuple_169_2_WLk.root",
sampleBaseDir+"PATtuple_167_2_JJ2.root",
sampleBaseDir+"PATtuple_65_2_BtD.root",
sampleBaseDir+"PATtuple_247_2_dkH.root",
sampleBaseDir+"PATtuple_103_2_s7F.root",
sampleBaseDir+"PATtuple_255_2_CSU.root",
sampleBaseDir+"PATtuple_162_2_fmO.root",
sampleBaseDir+"PATtuple_460_2_IwV.root",
sampleBaseDir+"PATtuple_540_0_vaE.root",
sampleBaseDir+"PATtuple_237_2_6R1.root",
sampleBaseDir+"PATtuple_461_2_tA9.root",
sampleBaseDir+"PATtuple_478_2_FWe.root",
sampleBaseDir+"PATtuple_24_2_rR8.root",
sampleBaseDir+"PATtuple_454_2_NL9.root",
sampleBaseDir+"PATtuple_552_0_ITg.root",
sampleBaseDir+"PATtuple_553_0_XWb.root",
sampleBaseDir+"PATtuple_330_2_fEO.root",
sampleBaseDir+"PATtuple_534_0_6um.root",
sampleBaseDir+"PATtuple_201_2_VIS.root",
sampleBaseDir+"PATtuple_2_2_aKm.root",
sampleBaseDir+"PATtuple_473_2_p7f.root",
sampleBaseDir+"PATtuple_325_2_ad1.root",
sampleBaseDir+"PATtuple_226_2_NMo.root",
sampleBaseDir+"PATtuple_102_2_m1l.root",
sampleBaseDir+"PATtuple_433_2_T6O.root",
sampleBaseDir+"PATtuple_412_2_OLF.root",
sampleBaseDir+"PATtuple_193_2_rzg.root",
sampleBaseDir+"PATtuple_97_1_rJw.root",
sampleBaseDir+"PATtuple_562_0_cxZ.root",
sampleBaseDir+"PATtuple_362_1_Fvk.root",
sampleBaseDir+"PATtuple_343_1_Gi7.root",
sampleBaseDir+"PATtuple_550_0_0Nu.root",
sampleBaseDir+"PATtuple_170_1_bMD.root",
sampleBaseDir+"PATtuple_158_1_O8A.root",
sampleBaseDir+"PATtuple_399_1_Eq9.root",
sampleBaseDir+"PATtuple_219_1_KZr.root",
sampleBaseDir+"PATtuple_284_1_y3e.root",
sampleBaseDir+"PATtuple_267_1_BVy.root",
sampleBaseDir+"PATtuple_31_2_aUT.root",
sampleBaseDir+"PATtuple_104_1_Chb.root",
sampleBaseDir+"PATtuple_129_1_20a.root",
sampleBaseDir+"PATtuple_156_1_BDh.root",
sampleBaseDir+"PATtuple_258_1_mSj.root",
sampleBaseDir+"PATtuple_588_0_JgD.root",
sampleBaseDir+"PATtuple_317_1_QIA.root",
sampleBaseDir+"PATtuple_111_1_SOv.root",
sampleBaseDir+"PATtuple_406_1_6WH.root",
sampleBaseDir+"PATtuple_22_2_Y0t.root",
sampleBaseDir+"PATtuple_401_1_nDs.root",
sampleBaseDir+"PATtuple_527_0_9zF.root",
sampleBaseDir+"PATtuple_349_1_vhs.root",
sampleBaseDir+"PATtuple_423_1_ulV.root",
sampleBaseDir+"PATtuple_314_1_aMQ.root",
sampleBaseDir+"PATtuple_286_1_KB1.root",
sampleBaseDir+"PATtuple_80_1_spf.root",
sampleBaseDir+"PATtuple_93_1_IJQ.root",
sampleBaseDir+"PATtuple_4_1_lxh.root",
sampleBaseDir+"PATtuple_528_0_Nde.root",
sampleBaseDir+"PATtuple_62_2_0ct.root",
sampleBaseDir+"PATtuple_241_1_dvP.root",
sampleBaseDir+"PATtuple_218_1_0gA.root",
sampleBaseDir+"PATtuple_23_1_owK.root",
sampleBaseDir+"PATtuple_100_1_ZdK.root",
sampleBaseDir+"PATtuple_292_1_3C4.root",
sampleBaseDir+"PATtuple_122_1_rGW.root",
sampleBaseDir+"PATtuple_173_1_oQn.root",
sampleBaseDir+"PATtuple_300_2_shs.root",
sampleBaseDir+"PATtuple_434_2_hjH.root",
sampleBaseDir+"PATtuple_532_0_xB0.root",
sampleBaseDir+"PATtuple_161_2_PNN.root",
sampleBaseDir+"PATtuple_578_0_7MT.root",
sampleBaseDir+"PATtuple_342_2_Bm7.root",
sampleBaseDir+"PATtuple_441_2_pu6.root",
sampleBaseDir+"PATtuple_220_2_kn8.root",
sampleBaseDir+"PATtuple_257_2_e9o.root",
sampleBaseDir+"PATtuple_529_0_JsM.root",
sampleBaseDir+"PATtuple_224_2_Vgl.root",
sampleBaseDir+"PATtuple_221_2_pMg.root",
sampleBaseDir+"PATtuple_338_2_xqo.root",
sampleBaseDir+"PATtuple_333_2_sj7.root",
sampleBaseDir+"PATtuple_331_2_j32.root",
sampleBaseDir+"PATtuple_11_2_UkN.root",
sampleBaseDir+"PATtuple_200_2_veI.root",
sampleBaseDir+"PATtuple_516_0_6CN.root",
sampleBaseDir+"PATtuple_52_2_kPL.root",
sampleBaseDir+"PATtuple_417_2_eJD.root",
sampleBaseDir+"PATtuple_453_2_aoW.root",
sampleBaseDir+"PATtuple_554_0_8yd.root",
sampleBaseDir+"PATtuple_297_2_BeW.root",
sampleBaseDir+"PATtuple_437_2_B9V.root",
sampleBaseDir+"PATtuple_69_2_sSk.root",
sampleBaseDir+"PATtuple_202_2_RsA.root",
sampleBaseDir+"PATtuple_558_0_Now.root",
sampleBaseDir+"PATtuple_295_2_L6r.root",
sampleBaseDir+"PATtuple_556_0_RzD.root",
sampleBaseDir+"PATtuple_15_2_O2A.root",
sampleBaseDir+"PATtuple_189_2_zID.root",
sampleBaseDir+"PATtuple_555_0_qrp.root",
sampleBaseDir+"PATtuple_239_2_nns.root",
sampleBaseDir+"PATtuple_543_0_uEY.root",
sampleBaseDir+"PATtuple_468_2_ISC.root",
sampleBaseDir+"PATtuple_164_2_JpQ.root",
sampleBaseDir+"PATtuple_581_0_Yzv.root",
sampleBaseDir+"PATtuple_390_2_wHW.root",
sampleBaseDir+"PATtuple_32_2_mFz.root",
sampleBaseDir+"PATtuple_559_0_OWS.root",
sampleBaseDir+"PATtuple_215_2_57m.root",
sampleBaseDir+"PATtuple_464_2_AVK.root",
sampleBaseDir+"PATtuple_296_2_pvH.root",
sampleBaseDir+"PATtuple_298_3_Vwn.root",
sampleBaseDir+"PATtuple_427_2_pSJ.root",
sampleBaseDir+"PATtuple_445_2_tl6.root",
sampleBaseDir+"PATtuple_242_2_ji2.root",
sampleBaseDir+"PATtuple_335_2_vto.root",
sampleBaseDir+"PATtuple_465_2_VoA.root",
sampleBaseDir+"PATtuple_466_2_uZC.root",
sampleBaseDir+"PATtuple_463_2_xf6.root",
sampleBaseDir+"PATtuple_369_2_RDT.root",
sampleBaseDir+"PATtuple_109_2_WUo.root",
sampleBaseDir+"PATtuple_279_1_na3.root",
sampleBaseDir+"PATtuple_191_1_WsW.root",
sampleBaseDir+"PATtuple_124_1_L6w.root",
sampleBaseDir+"PATtuple_37_2_IFz.root",
sampleBaseDir+"PATtuple_64_1_0uF.root",
sampleBaseDir+"PATtuple_387_1_Y2f.root",
sampleBaseDir+"PATtuple_190_1_Kzk.root",
sampleBaseDir+"PATtuple_280_1_pQB.root",
sampleBaseDir+"PATtuple_397_1_lIl.root",
sampleBaseDir+"PATtuple_458_1_pmu.root",
sampleBaseDir+"PATtuple_431_1_d3Y.root",
sampleBaseDir+"PATtuple_78_1_n3e.root",
sampleBaseDir+"PATtuple_87_1_ePM.root",
sampleBaseDir+"PATtuple_216_1_RxJ.root",
sampleBaseDir+"PATtuple_8_1_bog.root",
sampleBaseDir+"PATtuple_476_1_cWB.root",
sampleBaseDir+"PATtuple_225_2_biA.root",
sampleBaseDir+"PATtuple_442_1_2Bs.root",
sampleBaseDir+"PATtuple_107_1_v1z.root",
sampleBaseDir+"PATtuple_411_1_Qzw.root",
sampleBaseDir+"PATtuple_485_1_yJA.root",
sampleBaseDir+"PATtuple_117_1_aTk.root",
sampleBaseDir+"PATtuple_303_1_JTF.root",
sampleBaseDir+"PATtuple_420_1_8xK.root",
sampleBaseDir+"PATtuple_42_2_KnG.root",
sampleBaseDir+"PATtuple_51_1_yol.root",
sampleBaseDir+"PATtuple_168_1_EoV.root",
sampleBaseDir+"PATtuple_159_1_gb1.root",
sampleBaseDir+"PATtuple_471_1_Ctx.root",
sampleBaseDir+"PATtuple_469_1_OjZ.root",
sampleBaseDir+"PATtuple_356_1_eeY.root",
sampleBaseDir+"PATtuple_302_1_HHj.root",
sampleBaseDir+"PATtuple_187_2_m5w.root",
sampleBaseDir+"PATtuple_551_0_Ita.root",
sampleBaseDir+"PATtuple_487_2_cCa.root",
sampleBaseDir+"PATtuple_101_1_xcA.root",
sampleBaseDir+"PATtuple_155_1_2dj.root",
sampleBaseDir+"PATtuple_254_1_BgD.root",
sampleBaseDir+"PATtuple_374_1_emV.root",
sampleBaseDir+"PATtuple_484_2_KJn.root",
sampleBaseDir+"PATtuple_125_2_H7L.root",
sampleBaseDir+"PATtuple_571_0_y1U.root",
sampleBaseDir+"PATtuple_105_2_AUc.root",
sampleBaseDir+"PATtuple_577_0_TEX.root",
sampleBaseDir+"PATtuple_440_2_G8i.root",
sampleBaseDir+"PATtuple_188_3_13K.root",
sampleBaseDir+"PATtuple_480_2_Uw3.root",
sampleBaseDir+"PATtuple_106_2_kao.root",
sampleBaseDir+"PATtuple_526_0_EhT.root",
sampleBaseDir+"PATtuple_549_0_65W.root",
sampleBaseDir+"PATtuple_436_2_VyK.root",
sampleBaseDir+"PATtuple_386_2_pFx.root",
sampleBaseDir+"PATtuple_359_2_Rck.root",
sampleBaseDir+"PATtuple_264_1_vm3.root",
sampleBaseDir+"PATtuple_19_1_nu5.root",
sampleBaseDir+"PATtuple_149_2_UXT.root",
sampleBaseDir+"PATtuple_90_1_kst.root",
sampleBaseDir+"PATtuple_508_0_wYX.root",
sampleBaseDir+"PATtuple_391_1_rJ1.root",
sampleBaseDir+"PATtuple_71_1_nXi.root",
sampleBaseDir+"PATtuple_455_1_jjr.root",
sampleBaseDir+"PATtuple_405_1_RjE.root",
sampleBaseDir+"PATtuple_439_1_1tw.root",
sampleBaseDir+"PATtuple_140_1_f82.root",
sampleBaseDir+"PATtuple_262_1_0ya.root",
sampleBaseDir+"PATtuple_177_1_YTx.root",
sampleBaseDir+"PATtuple_438_1_c5H.root",
sampleBaseDir+"PATtuple_145_1_Xnv.root",
sampleBaseDir+"PATtuple_332_1_k5v.root",
sampleBaseDir+"PATtuple_407_1_2Jl.root",
sampleBaseDir+"PATtuple_82_1_xXo.root",
sampleBaseDir+"PATtuple_34_1_PWy.root",
sampleBaseDir+"PATtuple_547_0_QTp.root",
sampleBaseDir+"PATtuple_175_1_YsU.root",
sampleBaseDir+"PATtuple_557_0_uig.root",
sampleBaseDir+"PATtuple_310_1_fK6.root",
sampleBaseDir+"PATtuple_58_1_u9P.root",
sampleBaseDir+"PATtuple_135_1_2Yl.root",
sampleBaseDir+"PATtuple_246_1_fFa.root",
sampleBaseDir+"PATtuple_573_0_9zZ.root",
sampleBaseDir+"PATtuple_56_1_B2h.root",
sampleBaseDir+"PATtuple_416_1_t98.root",
sampleBaseDir+"PATtuple_288_1_0Rg.root",
sampleBaseDir+"PATtuple_174_1_nhv.root",
sampleBaseDir+"PATtuple_74_1_0kD.root",
sampleBaseDir+"PATtuple_44_1_k7O.root",
sampleBaseDir+"PATtuple_172_1_jsM.root",
sampleBaseDir+"PATtuple_29_1_7Mh.root",
sampleBaseDir+"PATtuple_134_1_0uH.root",
sampleBaseDir+"PATtuple_568_0_Oun.root",
sampleBaseDir+"PATtuple_428_2_KPx.root",
sampleBaseDir+"PATtuple_561_0_EXx.root",
sampleBaseDir+"PATtuple_259_2_dmz.root",
sampleBaseDir+"PATtuple_323_2_ODN.root",
sampleBaseDir+"PATtuple_580_0_jB2.root",
sampleBaseDir+"PATtuple_180_2_s7u.root",
sampleBaseDir+"PATtuple_352_2_2TX.root",
sampleBaseDir+"PATtuple_347_2_3y6.root",
sampleBaseDir+"PATtuple_322_2_zMf.root",
sampleBaseDir+"PATtuple_46_2_idd.root",
sampleBaseDir+"PATtuple_67_2_xTz.root",
sampleBaseDir+"PATtuple_63_2_OiT.root",
sampleBaseDir+"PATtuple_353_2_QzQ.root",
sampleBaseDir+"PATtuple_309_2_NZj.root",
sampleBaseDir+"PATtuple_278_2_vBl.root",
sampleBaseDir+"PATtuple_198_2_0lA.root",
sampleBaseDir+"PATtuple_94_2_wL7.root",
sampleBaseDir+"PATtuple_426_2_6B5.root",
sampleBaseDir+"PATtuple_367_2_1Vk.root",
sampleBaseDir+"PATtuple_425_2_LHp.root",
sampleBaseDir+"PATtuple_574_0_htU.root",
sampleBaseDir+"PATtuple_311_2_uIO.root",
sampleBaseDir+"PATtuple_329_2_zut.root",
sampleBaseDir+"PATtuple_33_2_UIG.root",
sampleBaseDir+"PATtuple_57_2_x5v.root",
sampleBaseDir+"PATtuple_41_2_yCI.root",
sampleBaseDir+"PATtuple_228_2_9z9.root",
sampleBaseDir+"PATtuple_210_2_fkz.root",
sampleBaseDir+"PATtuple_266_2_k3O.root",
sampleBaseDir+"PATtuple_231_2_Z2Z.root",
sampleBaseDir+"PATtuple_230_2_mCW.root",
sampleBaseDir+"PATtuple_14_2_Bhp.root",
sampleBaseDir+"PATtuple_83_2_zrG.root",
sampleBaseDir+"PATtuple_179_2_k3y.root",
sampleBaseDir+"PATtuple_227_2_XdL.root",
sampleBaseDir+"PATtuple_209_2_7Ah.root",
sampleBaseDir+"PATtuple_166_1_O0T.root",
sampleBaseDir+"PATtuple_60_2_V7M.root",
sampleBaseDir+"PATtuple_3_1_jnF.root",
sampleBaseDir+"PATtuple_9_1_KvH.root",
sampleBaseDir+"PATtuple_308_1_Xmw.root",
sampleBaseDir+"PATtuple_260_1_voi.root",
sampleBaseDir+"PATtuple_81_1_Enn.root",
sampleBaseDir+"PATtuple_73_1_D4z.root",
sampleBaseDir+"PATtuple_144_1_K6C.root",
sampleBaseDir+"PATtuple_70_1_Vxo.root",
sampleBaseDir+"PATtuple_245_1_3Ht.root",
sampleBaseDir+"PATtuple_20_1_PME.root",
sampleBaseDir+"PATtuple_45_1_twj.root",
sampleBaseDir+"PATtuple_243_1_hIE.root",
sampleBaseDir+"PATtuple_370_1_QCh.root",
sampleBaseDir+"PATtuple_112_1_qP3.root",
sampleBaseDir+"PATtuple_136_1_6Ol.root",
sampleBaseDir+"PATtuple_276_1_jHC.root",
sampleBaseDir+"PATtuple_49_1_qjn.root",
sampleBaseDir+"PATtuple_319_1_K85.root",
sampleBaseDir+"PATtuple_565_0_vKk.root",
sampleBaseDir+"PATtuple_30_1_Mvx.root",
sampleBaseDir+"PATtuple_371_1_pUr.root",
sampleBaseDir+"PATtuple_75_1_wWb.root",
sampleBaseDir+"PATtuple_143_1_U9C.root",
sampleBaseDir+"PATtuple_211_1_UQw.root",
sampleBaseDir+"PATtuple_229_1_D3x.root",
sampleBaseDir+"PATtuple_61_1_Yak.root",
sampleBaseDir+"PATtuple_503_0_XWt.root",
sampleBaseDir+"PATtuple_248_1_t5B.root",
sampleBaseDir+"PATtuple_76_1_4x6.root",
sampleBaseDir+"PATtuple_133_1_kEV.root",
sampleBaseDir+"PATtuple_176_1_Xqx.root",
sampleBaseDir+"PATtuple_21_1_JKl.root",
sampleBaseDir+"PATtuple_50_2_cOv.root",
sampleBaseDir+"PATtuple_147_2_OBm.root",
sampleBaseDir+"PATtuple_275_2_7Uh.root",
sampleBaseDir+"PATtuple_299_2_oP5.root",
sampleBaseDir+"PATtuple_47_2_CyH.root",
sampleBaseDir+"PATtuple_72_2_ErG.root",
sampleBaseDir+"PATtuple_277_2_2F1.root",
sampleBaseDir+"PATtuple_59_2_ltG.root",
sampleBaseDir+"PATtuple_43_2_qSX.root",
sampleBaseDir+"PATtuple_153_2_oKF.root",
sampleBaseDir+"PATtuple_152_2_7yr.root",
sampleBaseDir+"PATtuple_77_3_dU8.root",
sampleBaseDir+"PATtuple_410_1_bNg.root",
sampleBaseDir+"PATtuple_116_2_azj.root",
sampleBaseDir+"PATtuple_533_0_2pL.root",
sampleBaseDir+"PATtuple_515_0_tMR.root",
sampleBaseDir+"PATtuple_53_1_ANj.root",
sampleBaseDir+"PATtuple_28_1_OLz.root",
sampleBaseDir+"PATtuple_446_1_243.root",
sampleBaseDir+"PATtuple_110_1_ppI.root",
sampleBaseDir+"PATtuple_206_1_JH4.root",
sampleBaseDir+"PATtuple_285_1_R9B.root",
sampleBaseDir+"PATtuple_327_1_pzb.root",
sampleBaseDir+"PATtuple_408_1_kJ2.root",
sampleBaseDir+"PATtuple_572_0_ip0.root",
sampleBaseDir+"PATtuple_272_1_uS9.root",
sampleBaseDir+"PATtuple_429_1_xfU.root",
sampleBaseDir+"PATtuple_560_0_gup.root",
sampleBaseDir+"PATtuple_261_1_t9k.root",
sampleBaseDir+"PATtuple_419_1_pdS.root",
sampleBaseDir+"PATtuple_132_1_lJm.root",
sampleBaseDir+"PATtuple_321_1_nHI.root",
sampleBaseDir+"PATtuple_546_0_4eb.root",
sampleBaseDir+"PATtuple_518_0_Chi.root",
sampleBaseDir+"PATtuple_509_0_f3Q.root",
sampleBaseDir+"PATtuple_207_1_fjL.root",
sampleBaseDir+"PATtuple_146_1_4a3.root",
sampleBaseDir+"PATtuple_312_1_Pvm.root",
sampleBaseDir+"PATtuple_474_1_h9K.root",
sampleBaseDir+"PATtuple_545_0_C5y.root",
sampleBaseDir+"PATtuple_235_1_DT6.root",
sampleBaseDir+"PATtuple_520_0_vXt.root",
sampleBaseDir+"PATtuple_205_1_9TT.root",
sampleBaseDir+"PATtuple_54_1_18h.root",
sampleBaseDir+"PATtuple_448_1_SIQ.root",
sampleBaseDir+"PATtuple_244_1_Po2.root",
sampleBaseDir+"PATtuple_36_1_5Lq.root",
sampleBaseDir+"PATtuple_544_0_Clo.root",
sampleBaseDir+"PATtuple_208_1_8Tb.root",
sampleBaseDir+"PATtuple_178_1_cxb.root",
sampleBaseDir+"PATtuple_507_0_Arz.root",
sampleBaseDir+"PATtuple_13_1_ECq.root",
sampleBaseDir+"PATtuple_372_1_uwr.root",
sampleBaseDir+"PATtuple_354_1_mIo.root",
sampleBaseDir+"PATtuple_265_1_ufg.root",
sampleBaseDir+"PATtuple_86_1_FCe.root",
sampleBaseDir+"PATtuple_184_1_8vm.root",
sampleBaseDir+"PATtuple_151_1_guE.root",
sampleBaseDir+"PATtuple_233_1_g2k.root",
sampleBaseDir+"PATtuple_585_0_bND.root",
sampleBaseDir+"PATtuple_84_1_lBl.root",
sampleBaseDir+"PATtuple_249_1_sLn.root",
sampleBaseDir+"PATtuple_250_1_GA8.root",
sampleBaseDir+"PATtuple_232_1_Q42.root",
sampleBaseDir+"PATtuple_234_1_niC.root",
sampleBaseDir+"PATtuple_251_1_Nu8.root",
sampleBaseDir+"PATtuple_182_1_NJE.root",
sampleBaseDir+"PATtuple_252_1_Ffl.root",
sampleBaseDir+"PATtuple_85_1_nXq.root",
sampleBaseDir+"PATtuple_148_1_Glt.root",
sampleBaseDir+"PATtuple_181_1_xf2.root",
sampleBaseDir+"PATtuple_35_1_fWC.root",
sampleBaseDir+"PATtuple_150_1_Gve.root",
sampleBaseDir+"PATtuple_183_1_Fh0.root",
]