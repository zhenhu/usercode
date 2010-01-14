import FWCore.ParameterSet.Config as cms

process = cms.Process("MERGE")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'file:skimUpsilon1S_7TeV/skimUpsilon_1.root',
      'file:skimUpsilon2S_7TeV/skimUpsilon_1.root',
      'file:skimUpsilon3S_7TeV/skimUpsilon_1.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_1.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_2.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_3.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_4.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_5.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_6.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_7.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_8.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_9.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_10.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_11.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_12.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_13.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_14.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_15.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_16.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_17.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_18.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_19.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_20.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_21.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_22.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_23.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_24.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_25.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_26.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_27.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_28.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_29.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_30.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_31.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_32.root',
      'file:skimppMuMuX_7TeV/skimUpsilon_33.root'
    )
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("skim_1.87pb-1.root"),
    outputCommands = cms.untracked.vstring(
        "keep *"
    )
)

process.end = cms.EndPath(process.out)

