sampleDataSet = '/DoubleMu/Run2012A-recover-06Aug2012-v1/AOD'

# original (i.e. RECO file) release,
# not the one we plan to process them with
sampleRelease = "CMSSW_5_3_3_patch1" 
# release used to create new files with
sampleProcessRelease = "CMSSW_5_3_5" 

sampleNumEvents = 722728 # according to DBS, as of 29 October 2012

# global tag needs to be chosen to match release, trigger menu and alignment conditions.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
sampleGlobalTag = 'FT_53_V6C_AN3::All'

# data quality run/lumi section selection
sampleJSON = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Reprocessing/Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12_JSON_MuonPhys.txt"
        
# restrict run range (mainly to get a sample with consistent trigger configuration)

# use checkAllFilesOpened whenever possible, and noDuplicateCheck when necessary
sampleDuplicateCheckMode = "checkAllFilesOpened"

# "DATA" or "MC"
sampleType = "DATA"





samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//DoubleMu/Data_Mu_Run2012A2_pat_20130125/d5f9471814d838dd25b027d0f99fd7ad/"
samplePatFiles = [
sampleBaseDir+"PATtuple_5_2_tQ3.root",
sampleBaseDir+"PATtuple_40_3_MQI.root",
sampleBaseDir+"PATtuple_6_2_iFa.root",
sampleBaseDir+"PATtuple_15_2_Zgj.root",
sampleBaseDir+"PATtuple_14_2_OVa.root",
sampleBaseDir+"PATtuple_13_2_Zf3.root",
sampleBaseDir+"PATtuple_39_2_PRI.root",
sampleBaseDir+"PATtuple_38_2_2Be.root",
sampleBaseDir+"PATtuple_10_1_AaQ.root",
sampleBaseDir+"PATtuple_11_1_Zgu.root",
sampleBaseDir+"PATtuple_20_1_CFN.root",
sampleBaseDir+"PATtuple_7_1_vEA.root",
sampleBaseDir+"PATtuple_22_1_dAL.root",
sampleBaseDir+"PATtuple_29_1_5cL.root",
sampleBaseDir+"PATtuple_17_1_uWO.root",
sampleBaseDir+"PATtuple_23_1_0xY.root",
sampleBaseDir+"PATtuple_31_1_FGf.root",
sampleBaseDir+"PATtuple_26_1_wiu.root",
sampleBaseDir+"PATtuple_28_1_Cko.root",
sampleBaseDir+"PATtuple_9_1_gdC.root",
sampleBaseDir+"PATtuple_24_1_WtT.root",
sampleBaseDir+"PATtuple_21_1_MWJ.root",
sampleBaseDir+"PATtuple_19_1_j8n.root",
sampleBaseDir+"PATtuple_18_1_IzN.root",
sampleBaseDir+"PATtuple_8_1_ROd.root",
sampleBaseDir+"PATtuple_27_1_WPk.root",
sampleBaseDir+"PATtuple_25_1_4If.root",
sampleBaseDir+"PATtuple_42_1_9d9.root",
sampleBaseDir+"PATtuple_12_1_Fwx.root",
sampleBaseDir+"PATtuple_43_1_Dhr.root",
sampleBaseDir+"PATtuple_35_1_Fw0.root",
sampleBaseDir+"PATtuple_37_1_NQ6.root",
sampleBaseDir+"PATtuple_41_1_PTy.root",
sampleBaseDir+"PATtuple_34_1_2NA.root",
sampleBaseDir+"PATtuple_30_1_CgH.root",
sampleBaseDir+"PATtuple_36_1_MPw.root",
sampleBaseDir+"PATtuple_33_1_Le5.root",
sampleBaseDir+"PATtuple_1_1_NvM.root",
sampleBaseDir+"PATtuple_4_1_hYN.root",
sampleBaseDir+"PATtuple_32_1_Cop.root",
sampleBaseDir+"PATtuple_16_1_SY4.root",
sampleBaseDir+"PATtuple_2_1_Khc.root",
sampleBaseDir+"PATtuple_3_1_49R.root",
sampleBaseDir+"PATtuple_44_1_oU6.root",
]