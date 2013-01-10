# the following is a standard PAT production template to start from
from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.coreTools import *

#===============================================================================
# Load sample file
#===============================================================================

# Apply filter on hltpaths?
hltfilter=True

# Some general setup.
# If running on Condor, the Condor run script will replace the below line
# and the appropriate entries in the following lines.
# Since Condor is only applicable to MC, default to appropriate settings for
# it.

sampleUseJets=True  # set default for backwards compatibility

useCondor=False
if (useCondor):
   isMC = True
   sampleUseJets = True
   process.load("MakePatTuple/MakePatTuple/INPUTFILE")
   process.source.duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
   process.source.skipEvents = cms.untracked.uint32(SKIP_EVENTS)
   process.maxEvents.input = cms.untracked.int32(MAX_EVENTS)
   from Configuration.AlCa.autoCond import autoCond
   process.GlobalTag.globaltag = autoCond['startup']
else:
   from SampleFiles.Samples.SAMPLENAME import *
   if (sampleType.find("MC")>=0):
      isMC = True
   else:
      isMC = False
   process.source.duplicateCheckMode = cms.untracked.string(sampleDuplicateCheckMode)
   process.GlobalTag.globaltag = cms.string(sampleGlobalTag)
   process.maxEvents.input = cms.untracked.int32(-1)

#==============================================================================
# Track selection
#==============================================================================
import CommonTools.RecoAlgos.recoTrackRefSelector_cfi
process.trackSel = CommonTools.RecoAlgos.recoTrackRefSelector_cfi.recoTrackRefSelector.clone(
    src = 'generalTracks',
    quality = ['highPurity'],
    ptMin = 1.0,
    tip = 30.0,
    lip = 30.0,
    minHit = 6,
    min3DHit = 2
)

#===============================================================================
# HLT Filter
#===============================================================================

# Turn off HLT filter for signal MC
if ( sampleType == "SIGNALMC" ) :
    hltfilter=False
    pass

import HLTrigger.HLTfilters.hltHighLevel_cfi
process.MyHLTSelection = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
    HLTPaths = [ 'HLT_L2DoubleMu*_NoVertex*',
                 'HLT_DoublePhoton*_HEVT_*',
                 'HLT_HT*_DoubleDisplacedPFJet*_v*',
                 'HLT_HT*_SingleDisplacedPFJet*_v*',
                 "HLT_DoubleDisplacedMu4_DiPFJet40Neutral_*",
                 "HLT_L2TripleMu10_0_0_NoVertex*",
                 "HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack_*",
                 # Higgs->4l triggers
                 # Comment as a lot of extra events
#                 'HLT_Mu17_TkMu8*',
#                 'HLT_DoubleMu7*',
#                 'HLT_Mu13_Mu8*',
#                 'HLT_Mu17_Mu8*',
#                 'HLT_Ele17_CaloTrk_Ele8_CaloTrk*',
#                 'HLT_Mu8_Ele17_CaloTrk*',
#                 'HLT_Mu17_Ele8_CaloTrk*'
                ],
    andOr = True, # False = and, True = or.
    throw = False)

#===============================================================================
# Monitor the hlt filter and the good event filters
#===============================================================================
# Documentation on using these: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookEDMTutorialProducer#EventCount
process.nEventsTotal = cms.EDProducer("EventCountProducer")
process.nEventsPostEventFilter = cms.EDProducer("EventCountProducer")
process.nEventsPostHLTFilter = cms.EDProducer("EventCountProducer")
process.nEventsPostPreFilter = cms.EDProducer("EventCountProducer")

# Also output trig report for more detailed info (in case we are interested)
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load( "HLTrigger.HLTanalyzers.hlTrigReport_cfi" )
process.MessageLogger.categories.append("HLTrigReport")
process.hlTrigReport.HLTriggerResults   = cms.InputTag("TriggerResults", "", "HLT")
process.hlTrigReport.ReferencePath      = cms.untracked.string( "HLTriggerFinalPath" )
process.hlTrigReport.ReferenceRate      = cms.untracked.double( 100.0 )
# process.hlTrigReport.ReportEvery        = "lumi"

#==============================================================================
# Jet setup
#==============================================================================

if (sampleUseJets):
   # Jet energy corrections to use:
   if (isMC):
      inputJetCorrLabel = ('AK5PFchs', ['L1FastJet', 'L2Relative', 'L3Absolute'])
   else:
      inputJetCorrLabel = ('AK5PFchs', ['L1FastJet', 'L2Relative', 'L3Absolute' , 'L2L3Residual'])
    
   # import the jet RECO modules
   process.load('RecoJets.Configuration.RecoPFJets_cff')
   
   # load the PAT config
   process.load("PhysicsTools.PatAlgos.patSequences_cff")
   
   # Configure PAT to use PF2PAT instead of AOD sources
   # this function will modify the PAT sequences.
   from PhysicsTools.PatAlgos.tools.pfTools import *

   # An empty postfix means that only PF2PAT is run,
   # otherwise both standard PAT and PF2PAT are run. In the latter case PF2PAT
   # collections have standard names + postfix (e.g. patElectronPFlow)  
   postfix = "PFlow"
   jetAlgo="AK5"
   usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=isMC, postfix=postfix,
             jetCorrections=(inputJetCorrLabel))

#==============================================================================
# Good vertex, HB/HE noise filter, scraping filter (moved from TreeProducer),
# ECAL laser and HCAL laser filters.
#==============================================================================

# require scraping filter
process.scrapingVeto = cms.EDFilter("FilterOutScraping",
                                    applyfilter = cms.untracked.bool(True),
                                    debugOn = cms.untracked.bool(False),
                                    numtrack = cms.untracked.uint32(10),
                                    thresh = cms.untracked.double(0.25)
                                    )
# HB + HE noise filtering
process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')

# Good vertex filter
process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                           vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                           minimumNDOF = cms.uint32(4) ,
                                           maxAbsZ = cms.double(24),
                                           maxd0 = cms.double(2)
                                           )

# ECAL laser filter
process.load('RecoMET.METFilters.ecalLaserCorrFilter_cfi') 

# HCAL laser filter
import string
import os
import gzip
process.load("EventFilter.HcalRawToDigi.hcallasereventfilter2012_cfi")
#--- taking events list from the release area
file = gzip.GzipFile(os.getenv('CMSSW_RELEASE_BASE')+"/src/EventFilter/HcalRawToDigi/data/AllBadHCALLaser.txt.gz")
#--- alternatively - taking events list from local area
# file = gzip.GzipFile(os.getenv('CMSSW_BASE')+"/src/EventFilter/HcalRawToDigi/data/AllBadHCALLaser.txt.gz")
mylist=file.readlines()  # read all lines in the inputfile
for j in mylist:
        process.hcallasereventfilter2012.EventList.append(string.strip(j)) 
print "A total of %i events read"%len(process.hcallasereventfilter2012.EventList)

#===============================================================================
# EJC - DON'T KNOW WHAT THIS DOES - RELATED TO PAT?
#===============================================================================
# setup MC matching
process.muonMatch.checkCharge = False
process.muonMatch.maxDPtRel = 1000.
process.electronMatch.checkCharge = False

if (not isMC):
   removeMCMatching(process, ['All'])
   if (sampleUseJets):
      removeMCMatchingPF2PAT( process, '' )

if (sampleUseJets):
   # top projections in PF2PAT:
   getattr(process,"pfNoPileUp"+postfix).enable = True
   getattr(process,"pfNoMuon"+postfix).enable = False
   getattr(process,"pfNoElectron"+postfix).enable = False
   
   # verbose flags for the PF2PAT modules
   getattr(process,"pfNoMuon"+postfix).verbose = False
   
#===============================================================================
# Path setup
#===============================================================================

# Define sequence
process.mainSequence = process.patDefaultSequence

# Keep track of original number of events
# Then apply any event filters
process.p = cms.Path(process.nEventsTotal*process.scrapingVeto*process.primaryVertexFilter)

if (not isMC):
    process.p += process.HBHENoiseFilter
    process.p += process.hcallasereventfilter2012
    if ( sampleDataSet.find("Run2012B-13Jul2012")>=0 or sampleDataSet.find("Run2012A-13Jul2012")>=0 ):
        process.p += process.ecalLaserCorrFilter
        pass
    pass

# Keep track of number of events after event filters
process.p += process.nEventsPostEventFilter*process.trackSel

# Optionally apply hlt filter (usually applied except for signal MC)
if (hltfilter):
   process.p +=  process.MyHLTSelection
   pass

# Keep track of number of events after hlt filter
process.p += process.nEventsPostHLTFilter

# Filter to reduce the size of the PATtuples. Require a pair of each with minimum pt. Only trackerMuon and globalMuon are allowed to have mixed pairs.
process.load("TreeProducer.TreeProducer.pseudoLeptonProducer_cfi")
process.load("TreeProducer.TreeProducer.pseudoLeptonFilter_cfi")

process.mainSequence += process.pseudoLeptonProducer
process.mainSequence += process.pseudoLeptonFilter

# Main sequence
process.p += process.mainSequence

# Keep track of number of events after prefilter
process.p += process.nEventsPostPreFilter

if (sampleUseJets):
   process.p += getattr(process,"patPF2PATSequence"+postfix)

process.report = cms.EndPath( process.hlTrigReport )

#===============================================================================
# PAT CONFIGURATION
#===============================================================================

# use only AOD input.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideAodDataTable for what is available in AOD
restrictInputToAOD(process)

# enable PAT trigger functionality
from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTrigger(process)
switchOnTriggerStandAlone(process)
process.patTrigger.processName = "*"

# some PAT objects fail to be produced properly, especially when rerecoing. Thus drop them.
removeSpecificPATObjects(process, ['METs','Taus'])
# not sure why the following statements are required in addition
process.p.remove(process.patMETs)
process.p.remove(process.patTaus)
if (not sampleUseJets):
   removeSpecificPATObjects(process, ['Jets'])
   process.p.remove(process.patJets)

# eliminate cleaning
removeCleaning(process)

#===============================================================================
# Output definition
#===============================================================================

from PhysicsTools.PatAlgos.patEventContent_cff import *

if (useCondor):
   process.out.fileName = cms.untracked.string("OUTPUTFILE")
else:
   process.out.fileName = cms.untracked.string('PATtuple.root')
   
# Keep event counters
process.out.outputCommands += ['keep edmMergeableCounter_*_*_*']
# PAT content
process.out.outputCommands += ['keep *_patTriggerEvent_*_PAT']
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patTriggerStandAloneEventContent
process.out.outputCommands += patExtraAodEventContent # primary vertices, genParticles etc
process.out.outputCommands += ['keep PileupSummaryInfos_*_*_*']
process.out.outputCommands += ['drop *_towerMaker_*_*']
# keep superclusters for track momentum correction in etrack channel
process.out.outputCommands += ['keep *_correctedHybridSuperClusters_*_*']
process.out.outputCommands += ['keep *_correctedMulti5x5SuperClustersWithPreshower_*_*']
# keep high quality track selection
process.out.outputCommands += ['keep *_trackSel_*_*']
# keep standalone muons without IP constraint
process.out.outputCommands += ['keep *_*tandAloneMuons_*_*']
# make sure we store the TrackExtra collection
process.out.outputCommands += ['keep recoTrackExtras_generalTracks__*']
if (sampleUseJets):
   process.out.outputCommands += ['keep *_ak5GenJets_*_SIM']
   process.out.outputCommands += ['keep *_selectedPatJetsPFlow_*_*']
   process.out.outputCommands += ['keep *_goodOfflinePrimaryVertices*_*_*',]    
   process.out.outputCommands += ['keep double_*_rho_*']
   
