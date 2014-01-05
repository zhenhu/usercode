import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_1.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_10.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_2.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_3.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_4.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_5.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_6.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_7.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_8.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/2B2Mu_MH_400_MFF_150_CTau400_7TeV/HTo2LongLivedTo2B2Mu_MH_400_MFF_150_CTau400_Pythia6_7TeV_CMSSW_4_4_2_FastSim_9.root",
] );
