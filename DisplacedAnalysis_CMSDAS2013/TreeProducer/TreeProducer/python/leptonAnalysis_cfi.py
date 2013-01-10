import FWCore.ParameterSet.Config as cms

analyzeLeptons = cms.EDAnalyzer("LeptonAnalysis",

  # input collections
  electronSrc  = cms.InputTag("selectedPatElectrons"),
  muonSrc      = cms.InputTag("selectedPatMuons"),
  tauSrc       = cms.InputTag("selectedPatTaus"),
  trackSrc     = cms.InputTag("pseudoLeptonProducer"),
  generatorSrc = cms.InputTag("genParticles"),
  trigger      = cms.InputTag("patTrigger"),
  triggerEvent = cms.InputTag("patTriggerEvent"),
  barrelSuperClusters = cms.InputTag("correctedHybridSuperClusters"),
  endcapSuperClusters = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),

  # general analysis setup

  # define which PDG ID is taken as signal
  # 23 = Z
  # 24 = W+
  # 36 = A0
  # 37 = H+
  signalPDGId = cms.vint32(36),

  # define which channel to look at here (with bogus default to force user input)
  leptonPDGId = cms.int32(0),

  # list of triggers we want to look at (here: initialize to a dummy trigger)
  hltPaths = cms.vstring("HLTriggerFinalPath"),

  # loose selection cuts
  leptonPtCut = cms.double(25),
  leptonSCEtCut = cms.double(10),

  UseMCTruth = cms.bool(True),

)
