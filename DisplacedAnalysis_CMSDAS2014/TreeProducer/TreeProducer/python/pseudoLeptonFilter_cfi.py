import FWCore.ParameterSet.Config as cms

pseudoLeptonFilter = cms.EDFilter("PseudoLeptonFilter",
#                                  minTrackPt1 = cms.double(0),
#                                  minTrackPt2 = cms.double(0),
#                                  minTrackerMuonPt1 = cms.double(0),
#                                  minTrackerMuonPt2 = cms.double(0),
#                                  minGlobalMuonPt1 = cms.double(0),
#                                  minGlobalMuonPt2 = cms.double(0),
#                                  minStandAloneMuonPt1 = cms.double(0),
#                                  minStandAloneMuonPt2 = cms.double(0),
#                                  minSuperClusterEt1 = cms.double(0),
#                                  minSuperClusterEt2 = cms.double(0),
                                  minTrackPt1 = cms.double(23),
                                  minTrackPt2 = cms.double(23),
                                  minTrackerMuonPt1 = cms.double(23),
                                  minTrackerMuonPt2 = cms.double(23),
                                  minGlobalMuonPt1 = cms.double(23),
                                  minGlobalMuonPt2 = cms.double(23),
                                  minStandAloneMuonPt1 = cms.double(23),
                                  minStandAloneMuonPt2 = cms.double(23),
                                  minSuperClusterEt1 = cms.double(36),
                                  minSuperClusterEt2 = cms.double(22),
                                  # Require at least two pseudoleptons with d0/sigma > cut value
                                  minD0Significance = cms.double(-1.),
                                  trackSrc = cms.InputTag("pseudoLeptonProducer"),
                                  barrelSuperClusters = cms.InputTag("correctedHybridSuperClusters"),
                                  endcapSuperClusters = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower")
                                  )

