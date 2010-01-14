import FWCore.ParameterSet.Config as cms
process = cms.Process("Fit")

massRange = ( 8, 12 ); massRangeSta = (6, 14)

# Add your own files here
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

RunFit = cms.EDAnalyzer("TagProbeEDMAnalysis",  
      ## Efficiency/Fitting variables
      CalculateEffSideBand = cms.untracked.bool( False ), ## Calculate and store effs using SB
      CalculateEffFitter   = cms.untracked.bool( True ), ## Calculate and store effs from Roofit
      CalculateEffTruth    = cms.untracked.bool( True ), ## Calculate and store true effs

      ## Set mode to read from files ...
      Mode = cms.untracked.string("Read"),

      ReadFromFiles = cms.untracked.vstring("TO_BE_FILLED"),
      FitFileName   = cms.untracked.string("TO_BE_FILLED"),

      UnbinnedFit  = cms.untracked.bool( True ),
      Do2DFit      = cms.untracked.bool( True ),

      ## Mass window for fitting
      NumBinsMass         = cms.untracked.int32( 20 ), # matters only for the plots, the fit is unbinned
      MassLow             = cms.untracked.double( massRange[0] ),
      MassHigh            = cms.untracked.double( massRange[1] ),
    
      ## Variable Specifications for SB subtractions and Roofit
      NameVar1             = cms.untracked.string( "pt" ),
      Var1BinBoundaries   = cms.untracked.vdouble( 3, 4.5, 6, 8, 20),
      NameVar2             = cms.untracked.string( "eta" ),
      Var2BinBoundaries   = cms.untracked.vdouble( -2.1,-1.2,0.0,1.2,2.1),

      GaussLineShape = cms.untracked.PSet(
              GaussMean        = cms.untracked.vdouble( 9.46, 9.0,  10.0  ),
              GaussSigma       = cms.untracked.vdouble( 0.08, 0.01, 0.15 ),
),

      ## Background variables
      CMSBkgLineShape = cms.untracked.PSet(
	CMSBkgAlpha           = cms.untracked.vdouble( 0 ), # fix these two to zero
	CMSBkgBeta            = cms.untracked.vdouble( 0 ), # so it's just an exp
	CMSBkgPeak            = cms.untracked.vdouble( 9.46 ),
	CMSBkgGamma           = cms.untracked.vdouble( 0, -10, 10 )
      ),

      ## Efficiency variables
      Efficiency        = cms.untracked.vdouble( 0.90,0.0,1.0 ),    
      NumSignal         = cms.untracked.vdouble( 4000.0,-10.0,30000.0 ),    
      NumBkgPass        = cms.untracked.vdouble( 4000.0,-10.0,10000.0 ),    
      NumBkgFail        = cms.untracked.vdouble( 1000.0,-10.0,7000.0  ),    

      ## Variables for sideband subtraction
      SBSPeak            = cms.untracked.double( 9.46 ),   ## Mass peak
      SBSStanDev         = cms.untracked.double( 2 ),      ## SD from peak for subtraction

      # All the following is useless now that we just read and fit
      # but it's required...
      # --------------------------------------------
      MCTruthParentId = cms.untracked.int32(553),
)

process.fitMuFromTkUpsTkM = RunFit.clone(
    ReadFromFiles = [ 'histo_output_MuFromTkUpsTkM_1S.root' ],
    FitFileName   =     'fit_result_MuFromTkUpsTkM_1S.root'  ,
)
process.fitHltFromUpsTm = RunFit.clone(
    ReadFromFiles = [ 'histo_output_HltFromUpsTm_1S.root' ],
    FitFileName   =     'fit_result_HltFromUpsTm_1S.root'  ,
    Var2BinBoundaries   = cms.untracked.vdouble( -2.1,-1.2,0.0,1.2,2.1),
)

process.fitness = cms.Path(
    process.fitMuFromTkUpsTkM +
    process.fitHltFromUpsTm 
)
