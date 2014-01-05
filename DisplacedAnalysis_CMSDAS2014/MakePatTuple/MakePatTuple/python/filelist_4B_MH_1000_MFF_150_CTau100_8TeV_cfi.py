import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_1.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_10.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_2.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_3.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_4.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_5.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_6.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_7.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_8.root",
"dcache:/pnfs/cms/WAX/11/store/user/plujan/HTo2LongLived/4B_MH_1000_MFF_150_CTau100_8TeV/HTo2LongLivedTo4B_MH_1000_MFF_150_CTau100_Pythia6_8TeV_CMSSW_5_2_5_FastSim_9.root",
] );
