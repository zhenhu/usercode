import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('FWCore.MessageService.MessageLogger_cfi')

# Suppress messages from vertex fitter
process.MessageLogger.categories.append( 'TwoTrackMinimumDistance' )
process.MessageLogger.cerr.TwoTrackMinimumDistance = cms.untracked.PSet( limit =cms.untracked.int32( 0 ) )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load('Configuration/Geometry/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

process.load('TreeProducer.TreeProducer.leptonAnalysis_cfi')

# data sample and sample-specific settings
sampleSignalPID=[6001113,6002113,6003113,6001114,6002114,6003114]
sampleRequireCollision=1
sampleRunE=1
sampleRunMu=1

from SampleFiles.Samples.Debug_sample_cff import *

# Electron - pseudo lepton
process.eTrackAnalysis = process.analyzeLeptons.clone()
process.eTrackAnalysis.signalPDGId = sampleSignalPID
process.eTrackAnalysis.leptonPDGId = -11
process.eTrackAnalysis.leptonPtCut = 10
process.eTrackAnalysis.leptonSCEtCut = 25
process.eTrackAnalysis.hltPaths = cms.vstring(
                                        "HLT_DoublePhoton48_HEVT_v3",
                                        "HLT_DoublePhoton48_HEVT_v4",
                                        "HLT_DoublePhoton48_HEVT_v5",
                                        "HLT_DoublePhoton48_HEVT_v6",
                                        "HLT_DoublePhoton48_HEVT_v7",
                                        "HLT_DoublePhoton48_HEVT_v7",
                                        "HLT_DoublePhoton48_HEVT_v8",
                                         )
# Add "*" if we are looking at signal MC so we don't filter on triggers, but we still have trigger objects to match to
if ( sampleType == "SIGNALMC" ) : process.eTrackAnalysis.hltPaths.append("*")

# Muon - pseudo lepton
process.muTrackAnalysis = process.analyzeLeptons.clone()
process.muTrackAnalysis.signalPDGId = sampleSignalPID
process.muTrackAnalysis.leptonPDGId = -13
process.muTrackAnalysis.leptonPtCut = 25
process.muTrackAnalysis.leptonSCEtCut = 0
process.muTrackAnalysis.hltPaths = cms.vstring(
                                            "HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v1",
                                            "HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v2",
                                            "HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v3",
                                            )
if ( sampleType == "SIGNALMC" ) : process.muTrackAnalysis.hltPaths.append("*")


# create pseudo-leptons for all lepton channels
process.load("TreeProducer.TreeProducer.pseudoLeptonProducer_cfi")

# Set input files
process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string(sampleDuplicateCheckMode),
    fileNames = cms.untracked.vstring(samplePatFiles),
    # Useful for debugging and jumping to a particular event
#    skipEvents = cms.untracked.uint32(2140)
)

# Set global tag
process.GlobalTag.globaltag = sampleGlobalTag
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Output TFileService
process.TFileService = cms.Service("TFileService", 
    fileName = cms.string('histograms.root')
)

process.load("TreeProducer.TreeProducer.goodCollFilter_cff")

process.p = cms.Path()

# Filter on good collisions
if sampleRequireCollision: process.p+=process.goodcollFilter
process.p+=process.pseudoLeptonProducer

# Add electron pseudolepton analysis
if sampleRunE: process.p+=process.eTrackAnalysis
# Add muon psuedolepton analysis
if sampleRunMu: process.p+=process.muTrackAnalysis
