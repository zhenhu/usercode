sampleDataSet = '/QCD_Pt_170_250_BCtoE_TuneZ2star_8TeV_pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'

sampleCMSEnergy = 8000

sampleRelease = "CMSSW_5_3_2_patch4" # original (i.e. RECO file) release, not the one we plan to process them with
sampleProcessRelease = "CMSSW_5_3_5" # release used to create new files with

sampleNumEvents = 1948112

sampleXSec = 30980.0 * 0.0204 # pb

# global tag can be extracted from file using edmProvDump filename|grep globaltag
# note however that this is the tag for *further* processing, not the original tag
sampleGlobalTag = 'START53_V7F::All'

sampleDuplicateCheckMode = 'checkAllFilesOpened'

sampleType = "BKGMC"



samplePatDBSName=""

sampleBaseDir="/store/user/lpcdve/DisplacedLeptons/QCD_Pt_170_250_BCtoE_pat_20130913/demattia//QCD_Pt_170_250_BCtoE_TuneZ2star_8TeV_pythia6/QCD_Pt_170_250_BCtoE_pat_20130913/5fe3dadd93bf8608b396f970098158ed/"
samplePatFiles = [
sampleBaseDir+"PATtuple_33_1_j0z.root",
sampleBaseDir+"PATtuple_9_1_qnE.root",
sampleBaseDir+"PATtuple_12_1_HsG.root",
sampleBaseDir+"PATtuple_30_1_z2F.root",
sampleBaseDir+"PATtuple_41_1_uv2.root",
sampleBaseDir+"PATtuple_23_1_ubt.root",
sampleBaseDir+"PATtuple_15_1_ThM.root",
sampleBaseDir+"PATtuple_37_1_fK6.root",
sampleBaseDir+"PATtuple_32_1_AAr.root",
sampleBaseDir+"PATtuple_8_1_NRT.root",
sampleBaseDir+"PATtuple_1_1_Sja.root",
sampleBaseDir+"PATtuple_26_1_jDI.root",
sampleBaseDir+"PATtuple_10_1_0t3.root",
sampleBaseDir+"PATtuple_28_1_mPM.root",
sampleBaseDir+"PATtuple_4_1_zwX.root",
sampleBaseDir+"PATtuple_24_1_l0K.root",
sampleBaseDir+"PATtuple_6_1_xVF.root",
sampleBaseDir+"PATtuple_27_1_UwF.root",
sampleBaseDir+"PATtuple_19_1_pDC.root",
sampleBaseDir+"PATtuple_25_1_W8b.root",
sampleBaseDir+"PATtuple_18_1_j21.root",
sampleBaseDir+"PATtuple_29_1_yIL.root",
sampleBaseDir+"PATtuple_16_1_5Zb.root",
sampleBaseDir+"PATtuple_34_1_Bvk.root",
sampleBaseDir+"PATtuple_5_1_4bb.root",
sampleBaseDir+"PATtuple_39_1_WCD.root",
sampleBaseDir+"PATtuple_38_1_9CM.root",
sampleBaseDir+"PATtuple_11_1_xp8.root",
sampleBaseDir+"PATtuple_2_1_PxQ.root",
sampleBaseDir+"PATtuple_13_1_3v7.root",
sampleBaseDir+"PATtuple_35_1_Cpf.root",
sampleBaseDir+"PATtuple_3_1_d1t.root",
sampleBaseDir+"PATtuple_36_1_1gN.root",
sampleBaseDir+"PATtuple_17_1_9Hp.root",
sampleBaseDir+"PATtuple_31_1_CRv.root",
sampleBaseDir+"PATtuple_21_1_JEl.root",
sampleBaseDir+"PATtuple_20_1_r9c.root",
sampleBaseDir+"PATtuple_40_1_DFE.root",
sampleBaseDir+"PATtuple_22_1_s0H.root",
sampleBaseDir+"PATtuple_7_1_b0U.root",
]
