import FWCore.ParameterSet.Config as cms
process = cms.Process("Rootuple")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('file:/eos/uscms/store/user/zhenhu/MuOnia/Onia2MuMuPAT-Run2015D-MuOnia-v1/151013_131000/0000/Onia2MuMuPAT_200.root')
)

process.TFileService = cms.Service("TFileService",
   fileName = cms.string('Rootuple.root'),
)

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))

process.load('usercode.Onia.Onia2MuMuRootupler_cfi')
process.p = cms.Path(process.rootuple)

process.rootuple.isMC = cms.bool(False)                 # is mc?
process.rootuple.onia_mass_cuts = cms.vdouble(0.1,500)    # you may need to adjust this
