sampleDataSet = '/DoubleMu/Run2012A-recover-06Aug2012-v1/AOD'

# original (i.e. RECO file) release,
# not the one we plan to process them with
sampleRelease = "CMSSW_5_3_3_patch1" 
# release used to create new files with
sampleProcessRelease = "CMSSW_5_3_5" 

sampleNumEvents = 722728 # according to DBS, as of 29 October 2012

# global tag needs to be chosen to match release, trigger menu and alignment conditions.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
sampleGlobalTag = 'FT_53_V6C_AN2::All'

# data quality run/lumi section selection
sampleJSON = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Reprocessing/Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12_JSON_MuonPhys.txt"
        
# restrict run range (mainly to get a sample with consistent trigger configuration)
sampleRunRange = [190456-194076]

# use checkAllFilesOpened whenever possible, and noDuplicateCheck when necessary
sampleDuplicateCheckMode = "checkAllFilesOpened"

# "DATA" or "MC"
sampleType = "DATA"




samplePatDBSName=""

sampleBaseDir="dcap://dcap.pp.rl.ac.uk///pnfs/pp.rl.ac.uk/data/cms/store/user/ejclemen//DoubleMu/Data_Mu_Run2012A2_pat_20121030/0edb1919226478520f35f39bd418eaee/"
samplePatFiles = [
sampleBaseDir+"PATtuple_4_1_8Pk.root",
sampleBaseDir+"PATtuple_5_1_ovr.root",
sampleBaseDir+"PATtuple_34_1_XM0.root",
sampleBaseDir+"PATtuple_12_1_l7E.root",
sampleBaseDir+"PATtuple_42_1_IjF.root",
sampleBaseDir+"PATtuple_43_1_BcR.root",
sampleBaseDir+"PATtuple_30_1_3PZ.root",
sampleBaseDir+"PATtuple_14_1_8Fr.root",
sampleBaseDir+"PATtuple_10_1_3cs.root",
sampleBaseDir+"PATtuple_18_1_oWF.root",
sampleBaseDir+"PATtuple_26_1_fPx.root",
sampleBaseDir+"PATtuple_35_1_wPu.root",
sampleBaseDir+"PATtuple_41_1_omJ.root",
sampleBaseDir+"PATtuple_7_1_80o.root",
sampleBaseDir+"PATtuple_8_1_qA5.root",
sampleBaseDir+"PATtuple_13_1_oOs.root",
sampleBaseDir+"PATtuple_6_1_96P.root",
sampleBaseDir+"PATtuple_39_1_bGo.root",
sampleBaseDir+"PATtuple_15_1_7LK.root",
sampleBaseDir+"PATtuple_17_1_im8.root",
sampleBaseDir+"PATtuple_11_1_XE3.root",
sampleBaseDir+"PATtuple_37_1_cYP.root",
sampleBaseDir+"PATtuple_16_1_mNT.root",
sampleBaseDir+"PATtuple_36_1_G05.root",
sampleBaseDir+"PATtuple_9_1_ZMh.root",
sampleBaseDir+"PATtuple_38_1_6I5.root",
sampleBaseDir+"PATtuple_31_1_26g.root",
sampleBaseDir+"PATtuple_23_1_rUJ.root",
sampleBaseDir+"PATtuple_1_1_1bL.root",
sampleBaseDir+"PATtuple_44_1_mBs.root",
sampleBaseDir+"PATtuple_2_1_w9p.root",
sampleBaseDir+"PATtuple_3_1_NLe.root",
sampleBaseDir+"PATtuple_33_1_UOA.root",
sampleBaseDir+"PATtuple_29_1_ac5.root",
sampleBaseDir+"PATtuple_24_1_X81.root",
sampleBaseDir+"PATtuple_20_1_xJB.root",
sampleBaseDir+"PATtuple_22_1_UZi.root",
sampleBaseDir+"PATtuple_21_1_ecf.root",
sampleBaseDir+"PATtuple_19_1_Nqp.root",
sampleBaseDir+"PATtuple_32_1_6cq.root",
sampleBaseDir+"PATtuple_25_1_wpN.root",
sampleBaseDir+"PATtuple_27_1_2cJ.root",
sampleBaseDir+"PATtuple_28_1_Uvn.root",
sampleBaseDir+"PATtuple_40_1_R93.root",
]
