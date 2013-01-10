sampleDataSet = '/DoublePhotonHighPt/Run2012C-24Aug2012-v2/AOD'

# original (i.e. RECO file) release,
# not the one we plan to process them with
sampleRelease = "CMSSW_5_3_2_patch4" 
# release used to create new files with
sampleProcessRelease = "CMSSW_5_3_5" 

sampleNumEvents = 1299618 # according to DBS, as of 30 October 2012

# global tag needs to be chosen to match release, trigger menu and alignment conditions.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
sampleGlobalTag = 'FT_53_V10_AN2::All'

# data quality run/lumi section selection
sampleJSON = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Reprocessing/Cert_198022-198523_8TeV_24Aug2012ReReco_Collisions12_JSON.txt"

# restrict run range (mainly to get a sample with consistent trigger configuration)
sampleRunRange = [190456-99999999]

# use checkAllFilesOpened whenever possible, and noDuplicateCheck when necessary
sampleDuplicateCheckMode = "checkAllFilesOpened"

# "DATA" or "MC"
sampleType = "DATA"




samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//DoublePhotonHighPt/Data_Photon_Run2012C1_pat_20121030/5e90f939b3578737f059f2a1e8e1bb4b/"
samplePatFiles = [
sampleBaseDir+"PATtuple_11_2_hqe.root",
sampleBaseDir+"PATtuple_29_2_3M4.root",
sampleBaseDir+"PATtuple_38_1_hxf.root",
sampleBaseDir+"PATtuple_19_3_am5.root",
sampleBaseDir+"PATtuple_72_2_O0i.root",
sampleBaseDir+"PATtuple_77_1_f28.root",
sampleBaseDir+"PATtuple_36_2_2cB.root",
sampleBaseDir+"PATtuple_66_1_OWH.root",
sampleBaseDir+"PATtuple_69_1_vsy.root",
sampleBaseDir+"PATtuple_67_1_JcE.root",
sampleBaseDir+"PATtuple_57_2_3xt.root",
sampleBaseDir+"PATtuple_59_1_X96.root",
sampleBaseDir+"PATtuple_46_2_soI.root",
sampleBaseDir+"PATtuple_55_1_yGw.root",
sampleBaseDir+"PATtuple_58_1_dg6.root",
sampleBaseDir+"PATtuple_48_1_C8H.root",
sampleBaseDir+"PATtuple_68_1_qSV.root",
sampleBaseDir+"PATtuple_70_1_Hos.root",
sampleBaseDir+"PATtuple_33_1_cwh.root",
sampleBaseDir+"PATtuple_71_1_VGR.root",
sampleBaseDir+"PATtuple_73_1_5Gp.root",
sampleBaseDir+"PATtuple_23_1_QW1.root",
sampleBaseDir+"PATtuple_74_1_yp5.root",
sampleBaseDir+"PATtuple_20_1_3xW.root",
sampleBaseDir+"PATtuple_13_1_oNK.root",
sampleBaseDir+"PATtuple_61_1_ITS.root",
sampleBaseDir+"PATtuple_22_1_iiG.root",
sampleBaseDir+"PATtuple_24_1_qjk.root",
sampleBaseDir+"PATtuple_42_1_LD5.root",
sampleBaseDir+"PATtuple_1_2_nL0.root",
sampleBaseDir+"PATtuple_31_1_iRF.root",
sampleBaseDir+"PATtuple_56_1_GWN.root",
sampleBaseDir+"PATtuple_51_1_KPm.root",
sampleBaseDir+"PATtuple_65_1_vS2.root",
sampleBaseDir+"PATtuple_21_1_YHO.root",
sampleBaseDir+"PATtuple_60_1_kI8.root",
sampleBaseDir+"PATtuple_63_1_sgw.root",
sampleBaseDir+"PATtuple_54_1_IZl.root",
sampleBaseDir+"PATtuple_44_1_cKt.root",
sampleBaseDir+"PATtuple_75_1_amp.root",
sampleBaseDir+"PATtuple_7_1_KxE.root",
sampleBaseDir+"PATtuple_76_1_3IW.root",
sampleBaseDir+"PATtuple_50_1_7L0.root",
sampleBaseDir+"PATtuple_34_1_nDi.root",
sampleBaseDir+"PATtuple_37_1_Fdg.root",
sampleBaseDir+"PATtuple_40_1_5rX.root",
sampleBaseDir+"PATtuple_45_1_ThZ.root",
sampleBaseDir+"PATtuple_43_1_m2X.root",
sampleBaseDir+"PATtuple_47_1_COP.root",
sampleBaseDir+"PATtuple_53_1_nbS.root",
sampleBaseDir+"PATtuple_18_1_IEi.root",
sampleBaseDir+"PATtuple_64_1_N03.root",
sampleBaseDir+"PATtuple_49_1_ItQ.root",
sampleBaseDir+"PATtuple_62_1_m41.root",
sampleBaseDir+"PATtuple_30_1_0ON.root",
sampleBaseDir+"PATtuple_39_1_moD.root",
sampleBaseDir+"PATtuple_41_1_Sya.root",
sampleBaseDir+"PATtuple_52_1_GS9.root",
sampleBaseDir+"PATtuple_32_1_VA7.root",
sampleBaseDir+"PATtuple_26_1_ijj.root",
sampleBaseDir+"PATtuple_28_1_cLS.root",
sampleBaseDir+"PATtuple_10_1_1Bh.root",
sampleBaseDir+"PATtuple_27_1_Nt0.root",
sampleBaseDir+"PATtuple_35_1_Onq.root",
sampleBaseDir+"PATtuple_25_1_9fH.root",
sampleBaseDir+"PATtuple_15_1_xut.root",
sampleBaseDir+"PATtuple_12_1_8rU.root",
sampleBaseDir+"PATtuple_14_1_EmB.root",
sampleBaseDir+"PATtuple_17_1_hTP.root",
sampleBaseDir+"PATtuple_4_1_dea.root",
sampleBaseDir+"PATtuple_3_1_DiY.root",
sampleBaseDir+"PATtuple_9_1_h0u.root",
sampleBaseDir+"PATtuple_2_1_cWa.root",
sampleBaseDir+"PATtuple_6_1_xy9.root",
sampleBaseDir+"PATtuple_16_1_2pr.root",
sampleBaseDir+"PATtuple_8_1_oKm.root",
sampleBaseDir+"PATtuple_5_1_gDj.root",
]
