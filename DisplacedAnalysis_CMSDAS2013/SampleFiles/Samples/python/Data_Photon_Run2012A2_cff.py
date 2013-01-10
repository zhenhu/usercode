sampleDataSet = '/Photon/Run2012A-recover-06Aug2012-v1/AOD'

# original (i.e. RECO file) release,
# not the one we plan to process them with
sampleRelease = "CMSSW_5_3_3_patch1" 
# release used to create new files with
sampleProcessRelease = "CMSSW_5_3_5" 

sampleNumEvents = 1404595 # according to DBS, as of 30 October 2012

# global tag needs to be chosen to match release, trigger menu and alignment conditions.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
sampleGlobalTag = 'FT_53_V6C_AN2::All'

# data quality run/lumi section selection
sampleJSON = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Reprocessing/Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12_JSON.txt"

# restrict run range (mainly to get a sample with consistent trigger configuration)
sampleRunRange = [190456-999999999]

# use checkAllFilesOpened whenever possible, and noDuplicateCheck when necessary
sampleDuplicateCheckMode = "checkAllFilesOpened"

# "DATA" or "MC"
sampleType = "DATA"





samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//Photon/Data_Photon_Run2012A2_pat_20121030/0edb1919226478520f35f39bd418eaee/"
samplePatFiles = [
sampleBaseDir+"PATtuple_25_1_9Ch.root",
sampleBaseDir+"PATtuple_27_1_cs4.root",
sampleBaseDir+"PATtuple_41_1_mAD.root",
sampleBaseDir+"PATtuple_21_1_veZ.root",
sampleBaseDir+"PATtuple_42_1_2Le.root",
sampleBaseDir+"PATtuple_51_1_TNu.root",
sampleBaseDir+"PATtuple_34_1_cXz.root",
sampleBaseDir+"PATtuple_23_1_GkI.root",
sampleBaseDir+"PATtuple_28_1_bc8.root",
sampleBaseDir+"PATtuple_32_1_W8C.root",
sampleBaseDir+"PATtuple_31_1_nWF.root",
sampleBaseDir+"PATtuple_36_1_Rnh.root",
sampleBaseDir+"PATtuple_29_1_m3m.root",
sampleBaseDir+"PATtuple_52_1_mua.root",
sampleBaseDir+"PATtuple_9_1_5s7.root",
sampleBaseDir+"PATtuple_33_1_XHI.root",
sampleBaseDir+"PATtuple_26_1_8q8.root",
sampleBaseDir+"PATtuple_14_1_lBR.root",
sampleBaseDir+"PATtuple_35_1_nib.root",
sampleBaseDir+"PATtuple_46_1_nsb.root",
sampleBaseDir+"PATtuple_48_1_pOb.root",
sampleBaseDir+"PATtuple_43_1_d6x.root",
sampleBaseDir+"PATtuple_45_1_aiJ.root",
sampleBaseDir+"PATtuple_53_1_LJ7.root",
sampleBaseDir+"PATtuple_49_1_xN1.root",
sampleBaseDir+"PATtuple_38_1_8AO.root",
sampleBaseDir+"PATtuple_11_1_ZYe.root",
sampleBaseDir+"PATtuple_2_1_4Ap.root",
sampleBaseDir+"PATtuple_39_1_G6S.root",
sampleBaseDir+"PATtuple_55_1_04m.root",
sampleBaseDir+"PATtuple_54_1_31p.root",
sampleBaseDir+"PATtuple_15_1_sIW.root",
sampleBaseDir+"PATtuple_18_1_ZT4.root",
sampleBaseDir+"PATtuple_50_1_Iph.root",
sampleBaseDir+"PATtuple_13_1_YdT.root",
sampleBaseDir+"PATtuple_1_1_kIZ.root",
sampleBaseDir+"PATtuple_7_1_xnV.root",
sampleBaseDir+"PATtuple_44_1_w7W.root",
sampleBaseDir+"PATtuple_20_1_7HW.root",
sampleBaseDir+"PATtuple_10_1_crS.root",
sampleBaseDir+"PATtuple_22_1_tZb.root",
sampleBaseDir+"PATtuple_30_1_J8g.root",
sampleBaseDir+"PATtuple_19_1_Wmg.root",
sampleBaseDir+"PATtuple_37_1_sAu.root",
sampleBaseDir+"PATtuple_5_1_4Ng.root",
sampleBaseDir+"PATtuple_3_1_hzT.root",
sampleBaseDir+"PATtuple_24_1_UFz.root",
sampleBaseDir+"PATtuple_6_1_TDQ.root",
sampleBaseDir+"PATtuple_40_1_8Yz.root",
sampleBaseDir+"PATtuple_8_1_OfN.root",
sampleBaseDir+"PATtuple_17_1_kaa.root",
sampleBaseDir+"PATtuple_12_1_b7n.root",
sampleBaseDir+"PATtuple_4_1_FQV.root",
sampleBaseDir+"PATtuple_16_1_zNz.root",
sampleBaseDir+"PATtuple_47_1_GUE.root",
]
