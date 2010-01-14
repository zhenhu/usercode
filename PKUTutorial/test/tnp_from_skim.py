import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

massRange    = ( 8, 12 ); 
massRangeSta = (6, 14)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'file:skim_1.87pb-1.root'
 )
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )    

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Geometry.CommonDetUnit.globalTrackingGeometry_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAny_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorOpposite_cfi")
process.GlobalTag.globaltag = cms.string('MC_31X_V3::All')

##    ____                   _____               _      ____            _               
##   | __ )  __ _ _ __ ___  |_   _| __ __ _  ___| | __ |  _ \ _ __ ___ | |__   ___  ___ 
##   |  _ \ / _` | '__/ _ \   | || '__/ _` |/ __| |/ / | |_) | '__/ _ \| '_ \ / _ \/ __|
##   | |_) | (_| | | |  __/   | || | | (_| | (__|   <  |  __/| | | (_) | |_) |  __/\__ \
##   |____/ \__,_|_|  \___|   |_||_|  \__,_|\___|_|\_\ |_|   |_|  \___/|_.__/ \___||___/
##                                                                                      
##   
process.tkTracks  = cms.EDProducer("ConcreteChargedCandidateProducer", 
    src  = cms.InputTag("goodTracks"),      
    particleType = cms.string("mu+"),
) 
process.tkProbes = cms.EDProducer("CandViewRefSelector",
    src = cms.InputTag("tkTracks"),
    cut = cms.string("pt > 3 && abs(eta) < 2.4"),
)

##    __  __                     ____            _                                 _   _____               
##   |  \/  |_   _  ___  _ __   |  _ \ _ __ ___ | |__   ___  ___    __ _ _ __   __| | |_   _|_ _  __ _ ___ 
##   | |\/| | | | |/ _ \| '_ \  | |_) | '__/ _ \| '_ \ / _ \/ __|  / _` | '_ \ / _` |   | |/ _` |/ _` / __|
##   | |  | | |_| | (_) | | | | |  __/| | | (_) | |_) |  __/\__ \ | (_| | | | | (_| |   | | (_| | (_| \__ \
##   |_|  |_|\__,_|\___/|_| |_| |_|   |_|  \___/|_.__/ \___||___/  \__,_|_| |_|\__,_|   |_|\__,_|\__, |___/
##                                                                                               |___/     
##   
PASS_HLT = "!triggerObjectMatchesByPath('%s').empty()" % ("HLT_Mu3",);
process.tagMuons = cms.EDFilter("PATMuonRefSelector",
    src = cms.InputTag("patMuons"),
    cut = cms.string("isGlobalMuon && pt > 3 && abs(eta) < 2.4 "), 
    filter = cms.bool(True),
)
process.tmProbes = cms.EDFilter("PATMuonRefSelector",
    src = cms.InputTag("patMuons"), # can't use glbMuons as source, as RefSelectors can't be chained :-/
    cut = cms.string("isTrackerMuon && pt > 3 && abs(eta) < 2.1"), # 2.1, as we want to use it for trigger!
)


process.allTagsAndProbes = cms.Sequence(
    process.tagMuons +
    process.tkTracks * process.tkProbes 
    + process.tmProbes 
)

##    ____               _               ____            _                   __  __         ___ ____  
##   |  _ \ __ _ ___ ___(_)_ __   __ _  |  _ \ _ __ ___ | |__   ___  ___ _  |  \/  |_   _  |_ _|  _ \ 
##   | |_) / _` / __/ __| | '_ \ / _` | | |_) | '__/ _ \| '_ \ / _ \/ __(_) | |\/| | | | |  | || | | |
##   |  __/ (_| \__ \__ \ | | | | (_| | |  __/| | | (_) | |_) |  __/\__ \_  | |  | | |_| |  | || |_| |
##   |_|   \__,_|___/___/_|_| |_|\__, | |_|   |_|  \___/|_.__/ \___||___(_) |_|  |_|\__,_| |___|____/ 
##                               |___/                                                                
##   
process.tkToGlbMatch = cms.EDProducer("MatcherUsingTracks",
    src     = cms.InputTag("tkTracks"), # all tracks are available for matching
    matched = cms.InputTag("trackerMuons"), # to all global muons
    algorithm = cms.string("byDirectComparison"), # check that they
    srcTrack = cms.string("tracker"),             # have the same 
    srcState = cms.string("atVertex"),            # tracker track
    matchedTrack = cms.string("tracker"),         # can't check ref
    matchedState = cms.string("atVertex"),        # because of the
    maxDeltaR        = cms.double(0.01),          # embedding.
    maxDeltaLocalPos = cms.double(0.01),
    maxDeltaPtRel    = cms.double(0.01),
    sortBy           = cms.string("deltaR"),
)
process.tkPassingGlb = cms.EDProducer("MatchedCandidateSelector",
    src   = cms.InputTag("tkProbes"),
    match = cms.InputTag("tkToGlbMatch"),
)

##    ____               _               ____            _                   _____     _                       
##   |  _ \ __ _ ___ ___(_)_ __   __ _  |  _ \ _ __ ___ | |__   ___  ___ _  |_   _| __(_) __ _  __ _  ___ _ __ 
##   | |_) / _` / __/ __| | '_ \ / _` | | |_) | '__/ _ \| '_ \ / _ \/ __(_)   | || '__| |/ _` |/ _` |/ _ \ '__|
##   |  __/ (_| \__ \__ \ | | | | (_| | |  __/| | | (_) | |_) |  __/\__ \_    | || |  | | (_| | (_| |  __/ |   
##   |_|   \__,_|___/___/_|_| |_|\__, | |_|   |_|  \___/|_.__/ \___||___(_)   |_||_|  |_|\__, |\__, |\___|_|   
##                               |___/                                                   |___/ |___/           
##   
process.tmPassingHLT = cms.EDFilter("PATMuonRefSelector",
    src = cms.InputTag("patMuons"),
    cut = cms.string(process.tmProbes.cut.value() + " && " + PASS_HLT),
)

##    ____               _               ____            _                   ____        ____   _    ____ 
##   |  _ \ __ _ ___ ___(_)_ __   __ _  |  _ \ _ __ ___ | |__   ___  ___ _  | __ )      |  _ \ / \  / ___|
##   | |_) / _` / __/ __| | '_ \ / _` | | |_) | '__/ _ \| '_ \ / _ \/ __(_) |  _ \ _____| |_) / _ \| |  _ 
##   |  __/ (_| \__ \__ \ | | | | (_| | |  __/| | | (_) | |_) |  __/\__ \_  | |_) |_____|  __/ ___ \ |_| |
##   |_|   \__,_|___/___/_|_| |_|\__, | |_|   |_|  \___/|_.__/ \___||___(_) |____/      |_| /_/   \_\____|
##                               |___/                                                                    
##   

## a) Tracker Muon ID
process.muonsUpsTkM = cms.EDProducer("MuonSelectorUpsilon",
    src = cms.InputTag("patMuons"),
    selectGlobalMuons = cms.bool(False)
)
process.tkToMuUpsTkMMatch = process.tkToGlbMatch.clone(matched = "muonsUpsTkM")
process.tkPassingMuUpsTkM = process.tkPassingGlb.clone(match   = "tkToMuUpsTkMMatch")

## b) Hlt From tracker muon
process.muUpsTmProbes = cms.EDProducer("MuonSelectorUpsilon",
    src = cms.InputTag("tmProbes"),
    selectGlobalMuons = cms.bool(False)
)
process.muUpsTmPassingHLT = cms.EDProducer("MuonSelectorUpsilon",
    src = cms.InputTag("tmPassingHLT"),
    selectGlobalMuons = cms.bool(False)
)


process.PAGMuonIDs = cms.Sequence(
    process.muonsUpsTkM * process.tkToMuUpsTkMMatch * process.tkPassingMuUpsTkM +
    process.muUpsTmProbes * process.muUpsTmPassingHLT 
)

process.allPassingProbes = cms.Sequence(
    process.tkToGlbMatch * process.tkPassingGlb +
    process.tmPassingHLT +
    process.PAGMuonIDs 
)



##    __  __       _          _____                 ____            _                                      
##   |  \/  | __ _| | _____  |_   _|_ _  __ _   _  |  _ \ _ __ ___ | |__   ___   _ __ ___   __ _ _ __  ___ 
##   | |\/| |/ _` | |/ / _ \   | |/ _` |/ _` |_| |_| |_) | '__/ _ \| '_ \ / _ \ | '_ ` _ \ / _` | '_ \/ __|
##   | |  | | (_| |   <  __/   | | (_| | (_| |_   _|  __/| | | (_) | |_) |  __/ | | | | | | (_| | |_) \__ \
##   |_|  |_|\__,_|_|\_\___|   |_|\__,_|\__, | |_| |_|   |_|  \___/|_.__/ \___| |_| |_| |_|\__,_| .__/|___/
##                                      |___/                                                   |_|        
tagProbeTemplate = cms.EDProducer("TagProbeProducer",
    TagCollection = cms.InputTag("tagMuons"),
    MassMinCut = cms.untracked.double(massRange[0]),
    MassMaxCut = cms.untracked.double(massRange[1]),
)


process.tagProbeHltFromUpsTm = tagProbeTemplate.clone(  ProbeCollection = cms.InputTag("muUpsTmProbes") )
process.tagProbeTmFromUpsTk = tagProbeTemplate.clone(  ProbeCollection = cms.InputTag("tkProbes") )


process.allTagProbeMaps = cms.Sequence(
    process.tagProbeTmFromUpsTk +
    process.tagProbeHltFromUpsTm
)

##    __  __  ____   __  __       _       _               
##   |  \/  |/ ___| |  \/  | __ _| |_ ___| |__   ___  ___ 
##   | |\/| | |     | |\/| |/ _` | __/ __| '_ \ / _ \/ __|
##   | |  | | |___  | |  | | (_| | || (__| | | |  __/\__ \
##   |_|  |_|\____| |_|  |_|\__,_|\__\___|_| |_|\___||___/
##                                                        
process.muMcMatch = cms.EDFilter("MCTruthDeltaRMatcherNew",
    pdgId = cms.vint32(13),
    src = cms.InputTag("patMuons"),
    distMin = cms.double(0.3),
    matched = cms.InputTag("genMuons")
)
process.tkMcMatch  = process.muMcMatch.clone(src = "tkTracks")

process.allMcMatches = cms.Sequence(process.muMcMatch + process.tkMcMatch)# + process.staMcMatch)

##    _____           _       _ ____            _            _   _ _____            _      
##   |_   _|_ _  __ _( )_ __ ( )  _ \ _ __ ___ | |__   ___  | \ | |_   _|   _ _ __ | | ___ 
##     | |/ _` |/ _` |/| '_ \|/| |_) | '__/ _ \| '_ \ / _ \ |  \| | | || | | | '_ \| |/ _ \
##     | | (_| | (_| | | | | | |  __/| | | (_) | |_) |  __/ | |\  | | || |_| | |_) | |  __/
##     |_|\__,_|\__, | |_| |_| |_|   |_|  \___/|_.__/ \___| |_| \_| |_| \__,_| .__/|_|\___|
##              |___/                                                        |_|           
##
process.TPEdm = cms.EDProducer("TagProbeEDMNtuple",
    tagProbeType = cms.untracked.string( "Muon" ),
    genParticlesTag = cms.untracked.InputTag("genMuons"),
    mcParticles = cms.untracked.vint32(13),
    mcParents   = cms.untracked.vint32( 0),
    
    ## Tag & Probe Muon Candidate Collections
    ## all this will be filled once for each T&P measurement
    tagCandTags = cms.untracked.VInputTag(),
    passProbeCandTags = cms.untracked.VInputTag(),
    allProbeCandTags  = cms.untracked.VInputTag(),
    tagTruthMatchMapTags       = cms.untracked.VInputTag(),
    passProbeTruthMatchMapTags = cms.untracked.VInputTag(),
    allProbeTruthMatchMapTags  = cms.untracked.VInputTag(),
    tagProbeMapTags = cms.untracked.VInputTag(),
    BestProbeCriteria = cms.untracked.vstring(),
    BestProbeInvMass  = cms.untracked.vdouble(),

    ## Ignore the following, we don't care
    triggerEventTag = cms.untracked.InputTag( "hltTriggerSummaryAOD" ),
    hltL1Tag        = cms.untracked.InputTag( "hltSingleMuIsoLevel1Seed" ),
    hltTag          = cms.untracked.InputTag( "hltSingleMuIsoL3IsoFiltered" ),
    triggerDelRMatch     = cms.untracked.double( 0.15 ),
    triggerDelPtRelMatch = cms.untracked.double( 0.15 )
)

##    _____           _       _ ____            _            _   _ _     _        
##   |_   _|_ _  __ _( )_ __ ( )  _ \ _ __ ___ | |__   ___  | | | (_)___| |_ ___  
##     | |/ _` |/ _` |/| '_ \|/| |_) | '__/ _ \| '_ \ / _ \ | |_| | / __| __/ _ \ 
##     | | (_| | (_| | | | | | |  __/| | | (_) | |_) |  __/ |  _  | \__ \ || (_) |
##     |_|\__,_|\__, | |_| |_| |_|   |_|  \___/|_.__/ \___| |_| |_|_|___/\__\___/ 
##              |___/                                                             
MakeHisto = cms.EDAnalyzer("TagProbeEDMAnalysis",      
      # AFAIK these are the only meaningful parameters for now that we just make the Histo
      # --------------------------------------------
      Mode = cms.untracked.string("Write"),
      FitFileName = cms.untracked.string( "fit_output.root" ),

      TagProbeType = cms.untracked.int32(0),

      MCTruthParentId = cms.untracked.int32(553),
      Weight = cms.untracked.double(1.0),

      CalculateEffSideBand = cms.untracked.bool( True ), ## Calculate and store effs using SB
      CalculateEffFitter   = cms.untracked.bool( True ), ## Calculate and store effs from Roofit
      CalculateEffTruth    = cms.untracked.bool( True ), ## Calculate and store true effs
      UnbinnedFit          = cms.untracked.bool( True ),
      Do2DFit              = cms.untracked.bool( True ),

      NumBinsMass         = cms.untracked.int32( 20 ),
      MassLow             = cms.untracked.double( massRange[0] ),
      MassHigh            = cms.untracked.double( massRange[1] ),

      NameVar1             = cms.untracked.string( "pt" ),
      Var1BinBoundaries   = cms.untracked.vdouble( 3, 4.5, 6, 8, 20 ),
      NameVar2             = cms.untracked.string( "eta" ),
      Var2BinBoundaries   = cms.untracked.vdouble( -2.1,-1.2,0.0,1.2,2.1),

      # All the following is useless now
      # --------------------------------------------
      GaussLineShape = cms.untracked.PSet(
        GaussMean1S  = cms.untracked.vdouble( 9.4,  9,  10. ),
        GaussSigma   = cms.untracked.vdouble( 0.03, 0.01, 0.30 ),
        frac2S       = cms.untracked.vdouble(0.6,0.1,1.0),
        frac3S       = cms.untracked.vdouble(0.2,0.1,0.5)
      ),

#      CMSBkgLineShape = cms.untracked.PSet(
#        CMSBkgAlpha           = cms.untracked.vdouble( 124, 0, 1000 ),
#        CMSBkgBeta            = cms.untracked.vdouble( -0.028,-1.0,1.0 ),
#        CMSBkgPeak            = cms.untracked.vdouble( 91.1876 ),
#        CMSBkgGamma           = cms.untracked.vdouble( 0.0379,0.0,0.5 )
#      ),
      PolynomialLineShape = cms.untracked.PSet(               
        PolyBkgC4 = cms.untracked.vdouble( 0,0,0 ),           
        PolyBkgC3 = cms.untracked.vdouble( 0,0,0 ),           
        PolyBkgC2 = cms.untracked.vdouble( -20,-100,100),     
        PolyBkgC1 = cms.untracked.vdouble(372,-1000,1000),    
        PolyBkgC0 = cms.untracked.vdouble(-1000, -4000, 4000) 
      ),


      Efficiency        = cms.untracked.vdouble( 0.99,0.5,1.0 ),    
      NumSignal         = cms.untracked.vdouble( 4000.0,-10.0,30000.0 ),    
      NumBkgPass        = cms.untracked.vdouble( 4000.0,0.0,10000.0 ),    
      NumBkgFail        = cms.untracked.vdouble( 1000.0,-10.0,7000.0 ),    

      SBSPeak            = cms.untracked.double( 3.1 ),   ## Mass peak
      SBSStanDev         = cms.untracked.double( 2 )        ## SD from peak for subtraction
)

##    __  __       _                          _       _____      ____                        _       _      
##   |  \/  | __ _| | _____    ___  __ _  ___| |__   |_   _| __ |  _ \   _ __ ___   ___   __| |_   _| | ___ 
##   | |\/| |/ _` | |/ / _ \  / _ \/ _` |/ __| '_ \    | || '_ \| |_) | | '_ ` _ \ / _ \ / _` | | | | |/ _ \
##   | |  | | (_| |   <  __/ |  __/ (_| | (__| | | |   | || | | |  __/  | | | | | | (_) | (_| | |_| | |  __/
##   |_|  |_|\__,_|_|\_\___|  \___|\__,_|\___|_| |_|   |_||_| |_|_|     |_| |_| |_|\___/ \__,_|\__,_|_|\___|
##                                                                                                          

#####
## Mu from Tk

## PAG-specific muon IDs

process.TPEdm.tagCandTags       += [ cms.InputTag("tagMuons") ]
process.TPEdm.allProbeCandTags  += [ cms.InputTag("tkProbes")   ]
process.TPEdm.passProbeCandTags += [ cms.InputTag("tkPassingMuUpsTkM") ]
process.TPEdm.tagProbeMapTags   += [ cms.InputTag("tagProbeTmFromUpsTk") ]
process.TPEdm.tagTruthMatchMapTags       += [ cms.InputTag("muMcMatch") ]
process.TPEdm.passProbeTruthMatchMapTags += [ cms.InputTag("tkMcMatch") ]
process.TPEdm.allProbeTruthMatchMapTags  += [ cms.InputTag("tkMcMatch") ]
process.TPEdm.BestProbeCriteria += [ "OneProbe" ]
process.TPEdm.BestProbeInvMass  += [ 9.46 ]
process.fitMuFromTkUpsTkM = MakeHisto.clone( 
    TagProbeType = cms.untracked.int32(0),
    FitFileName = cms.untracked.string( "histo_output_MuFromTkUpsTkM.root"),
)

process.TPEdm.tagCandTags       += [ cms.InputTag("tagMuons") ]
process.TPEdm.allProbeCandTags  += [ cms.InputTag("muUpsTmProbes")   ]
process.TPEdm.passProbeCandTags += [ cms.InputTag("muUpsTmPassingHLT") ]
process.TPEdm.tagProbeMapTags   += [ cms.InputTag("tagProbeHltFromUpsTm") ]
process.TPEdm.tagTruthMatchMapTags       += [ cms.InputTag("muMcMatch") ]
process.TPEdm.passProbeTruthMatchMapTags += [ cms.InputTag("muMcMatch") ]
process.TPEdm.allProbeTruthMatchMapTags  += [ cms.InputTag("muMcMatch") ]
process.TPEdm.BestProbeCriteria += [ "OneProbe" ]
process.TPEdm.BestProbeInvMass  += [ 9.46 ]
process.fitHltFromUpsTkM = MakeHisto.clone( 
    TagProbeType = cms.untracked.int32(1),
    FitFileName = cms.untracked.string( "histo_output_HltFromUpsTm.root"),
    ## need to override eta bins
    Var2BinBoundaries   = cms.untracked.vdouble( -2.1,-1.2,0.0,1.2,2.1 ),
)

process.allTPHistos = cms.Sequence(
    process.TPEdm +
    process.fitMuFromTkUpsTkM +
    process.fitHltFromUpsTkM
)




##    ____       _   _     
##   |  _ \ __ _| |_| |__  
##   | |_) / _` | __| '_ \ 
##   |  __/ (_| | |_| | | |
##   |_|   \__,_|\__|_| |_|
##                         
process.tagAndProbe = cms.Path( 
    process.allTagsAndProbes *
    process.allPassingProbes *
    process.allTagProbeMaps * 
    process.allMcMatches * 
    process.allTPHistos
)

##     ___        _               _   
##    / _ \ _   _| |_ _ __  _   _| |_ 
##   | | | | | | | __| '_ \| | | | __|
##   | |_| | |_| | |_| |_) | |_| | |_ 
##    \___/ \__,_|\__| .__/ \__,_|\__|
##                   |_|              
##
## We define this module, but we don't run it unless needed
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("/tmp/gpetrucc/tuple.root"),
    outputCommands = cms.untracked.vstring("drop *", "keep _TPEdm_*_*"),
    dropMetaDataForDroppedData = cms.untracked.bool(True),
)

##    ____       _                 
##   |  _ \  ___| |__  _   _  __ _ 
##   | | | |/ _ \ '_ \| | | |/ _` |
##   | |_| |  __/ |_) | |_| | (_| |
##   |____/ \___|_.__/ \__,_|\__, |
##                           |___/ 
##

### limit events
#process.maxEvents.input = 100 

