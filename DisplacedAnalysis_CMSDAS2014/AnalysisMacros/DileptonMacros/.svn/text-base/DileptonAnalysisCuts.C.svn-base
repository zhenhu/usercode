#define DileptonAnalysisCuts_cxx

#include "DileptonAnalysisCuts.h"

DileptonAnalysisCuts::DileptonAnalysisCuts( analysisType analysis, analysisCuts cuts ):
// Initialize cut values so all cands should pass
setOfCuts_(cuts), analysisType_(analysis),
minTrackPt1_(-1), minTrackPt2_(-1), minSCEt1_(-1), minSCEt2_(-1), maxSCEta_(99999), min_gap_SCEta_(99999), max_gap_SCEta_(99999),
maxEta_(9999),
requireOppositeSignD0_(true), cutOnSignedD0_(true), minD0Sig_(-99999), maxD0Sig_(99999999),
maxIso_(9999), maxCaloMatchDeltaR_(999999),
minR9_(-1), maxHoverE_(99999), maxSigmaIetaIeta_barrel_(99999), maxSigmaIetaIeta_endcap_(99999),
requireVertex_(true), minLxySig_(-99999), maxLxySig_(9999),
oppositeCharge_(true), maxVertexChi2_(99999999999), maxHitsBeforeVertex_(9999), maxMissingHitsAfterVertex_(9999),
minDeltaR_(-1), minCosine_(-9999), minDeltaPhi_(0), maxDeltaPhi_(99999999999), minMass_(0)
{
  // Different set of cuts for final, tight, loose etc.

  //
  // FINAL SELECTION CUTS
  //
  if ( setOfCuts_==_final){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=9;
      maxIso_=0.1;
      oppositeCharge_=false;
      maxVertexChi2_=10;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minMass_=15;
      //      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=9;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu || analysisType_==_2globalOrTrackerMu ) {
      // Cuts for di-global muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=9;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-SA muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=9;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }

  //
  // LOOSE SELECTION CUTS
  //

  // Loose lifetime cuts A
  if ( setOfCuts_==_looseA){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=4;
      maxD0Sig_=5;
      maxIso_=0.1;
      oppositeCharge_=false;
      maxVertexChi2_=10;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minMass_=15;
      //      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=2;
      maxD0Sig_=3;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu || analysisType_==_2globalOrTrackerMu ) {
      // Cuts for di-global muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=2;
      maxD0Sig_=3;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-SA muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=2;
      maxD0Sig_=3;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=2;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }

  // Loose lifetime cuts B
  if ( setOfCuts_==_looseB){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=-999999;
      maxD0Sig_=-4.5;
      maxIso_=0.1;
      oppositeCharge_=false;
      maxVertexChi2_=10;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minMass_=15;
      //      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-999999;
      maxD0Sig_=-2.5;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu || analysisType_==_2globalOrTrackerMu ) {
      // Cuts for di-global muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-999999;
      maxD0Sig_=-3;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-SA muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-999999;
      maxD0Sig_=-3;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=2;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }

  // Loose lifetime cuts C
  if ( setOfCuts_==_looseC){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=-999999;
      maxD0Sig_=-5.5;
      maxIso_=0.1;
      oppositeCharge_=false;
      maxVertexChi2_=10;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minMass_=15;
      //      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-999999;
      maxD0Sig_=-5;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu || analysisType_==_2globalOrTrackerMu ) {
      // Cuts for di-global muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-999999;
      maxD0Sig_=-5;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-SA muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-999999;
      maxD0Sig_=-5;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=2;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }

  //
  // REMOVED LIFETIME CUTS
  //
  else if ( setOfCuts_==_removedLifetime){
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=-9999999;
      maxIso_=0.1;
      oppositeCharge_=false;
      maxVertexChi2_=10;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minMass_=15;
//      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-9999999;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu || analysisType_==_2globalOrTrackerMu ) {
      // Cuts for di-global muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-9999999;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-global muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-9999999;
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }

  //
  // REMOVED LIFETIME CUTS NO VERTEX
  //
  else if ( setOfCuts_==_removedLifetimeNoVertex ){
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=-9999999;
      maxIso_=0.1;
      oppositeCharge_=false;
      requireVertex_=false;
      requireOppositeSignD0_=false;
      minMass_=15;
//      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-9999999;
      maxIso_=0.1;
      oppositeCharge_=true;
      requireVertex_=false;
      requireOppositeSignD0_=false;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu || analysisType_==_2globalOrTrackerMu ) {
      // Cuts for di-global muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-9999999;
      maxIso_=0.1;
      oppositeCharge_=true;
      requireVertex_=false;
      requireOppositeSignD0_=false;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-SA muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=-9999999;
      maxIso_=0.1;
      oppositeCharge_=true;
      requireVertex_=false;
      requireOppositeSignD0_=false;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }


  //
  // 2011 SELECTION CUTS
  //
  if ( setOfCuts_==_2011Cuts){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=40;
      minTrackPt2_=25;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxEta_=2;
      minD0Sig_=3;
      maxIso_=0.1;
      minLxySig_=8;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=-1;
      //      minCosine_=-99999999999;
      maxDeltaPhi_=0.8;
      minMass_=15;
      //      minR9_=0.85;
      //      maxHoverE_=1;
      //      maxSigmaIetaIeta_barrel_=0.034;
      //      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=2;
      maxIso_=0.1;
      minLxySig_=5;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=0.2;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu || analysisType_==_2globalOrTrackerMu ) {
      // Cuts for di-global muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=2;
      maxIso_=0.1;
      minLxySig_=5;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=0.2;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-SA muon analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=2;
      maxIso_=0.1;
      minLxySig_=5;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=0.2;
      minMass_=15;
    }
  }

  //
  // FINAL SELECTION CUTS COLLINEARITY
  //
  if ( setOfCuts_==_finalColl){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=12;
      requireOppositeSignD0_ = false;
      cutOnSignedD0_ = false;
      minDeltaPhi_ = 0;
      maxDeltaPhi_ = TMath::PiOver2();
      maxIso_=0.1;
      oppositeCharge_=false;
      maxVertexChi2_=10;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minMass_=15;
      //      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=12;
      requireOppositeSignD0_ = false;
      cutOnSignedD0_ = false;
      minDeltaPhi_ = 0;
      maxDeltaPhi_ = TMath::PiOver2();
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=4;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }

  if ( setOfCuts_==_looseColl){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=4.5;
      requireOppositeSignD0_ = false;
      cutOnSignedD0_ = false;
      minDeltaPhi_ = 0;
      maxDeltaPhi_ = TMath::PiOver2();
      maxIso_=0.1;
      oppositeCharge_=false;
      maxVertexChi2_=10;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minMass_=15;
      //      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=3;
      requireOppositeSignD0_ = false;
      cutOnSignedD0_ = false;
      minDeltaPhi_ = 0;
      maxDeltaPhi_ = TMath::PiOver2();
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=4;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }

  if ( setOfCuts_==_looseControlColl){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=4.5;
      requireOppositeSignD0_ = false;
      cutOnSignedD0_ = false;
      minDeltaPhi_ = TMath::PiOver2();
      maxDeltaPhi_ = TMath::Pi();
      maxIso_=0.1;
      oppositeCharge_=false;
      maxVertexChi2_=10;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minMass_=15;
      //      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=3;
      requireOppositeSignD0_ = false;
      cutOnSignedD0_ = false;
      minDeltaPhi_ = TMath::PiOver2();
      maxDeltaPhi_ = TMath::Pi();
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=4;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }

  if ( setOfCuts_==_controlColl){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt1_=36;
      minTrackPt2_=21;
      minSCEt1_=40;
      minSCEt2_=25;
      maxCaloMatchDeltaR_=0.1;
      maxSCEta_=2.5;
      min_gap_SCEta_=1.442;
      max_gap_SCEta_=1.56;
      maxEta_=2;
      minD0Sig_=12;
      requireOppositeSignD0_ = false;
      cutOnSignedD0_ = false;
      minDeltaPhi_ = TMath::PiOver2();
      maxDeltaPhi_ = TMath::Pi();
      maxIso_=0.1;
      oppositeCharge_=false;
      maxVertexChi2_=10;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=3;
      minMass_=15;
      //      minR9_=0.8;
      maxHoverE_=0.05;
      maxSigmaIetaIeta_barrel_=0.012;
      maxSigmaIetaIeta_endcap_=0.034;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt1_=26;
      minTrackPt2_=minTrackPt1_;
      minSCEt1_=-1;
      minSCEt2_=-1;
      maxEta_=2;
      minD0Sig_=12;
      requireOppositeSignD0_ = false;
      cutOnSignedD0_ = false;
      minDeltaPhi_ = TMath::PiOver2();
      maxDeltaPhi_ = TMath::Pi();
      maxIso_=0.1;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      maxMissingHitsAfterVertex_=4;
      minDeltaR_=0.2;
      minCosine_=-0.79;
      minMass_=15;
    }
  }

  // Print cut values to screen
  if ( setOfCuts_==_final){
    printCutValues();
  }
}

// Checks which cuts have passed and then returns a struct saying which cuts have passed
DileptonAnalysisCuts::PassedWhichCuts DileptonAnalysisCuts::whichCuts( TreeDipseudoLeptonCandidate & candidate, double mass, TreeLepton & leptonL, TreeLepton & leptonH, analysisType analysis, double lxyScale, double d0Scale ) {

  PassedWhichCuts passedCuts;

  // Check if candidate passed each individual cut

  // Cuts on original leptons (before refit)

  // Lepton matched SC Et (electron channel only)
  if ( ( leptonH.photonEt != leptonL.photonEt && ( ( leptonH.photonEt > minSCEt1_ && leptonL.photonEt > minSCEt2_ ) || ( leptonH.photonEt > minSCEt2_ && leptonL.photonEt > minSCEt1_ ) ) ) || analysis != _2eTrack ) passedCuts.passSCEt=true;

  // Check photon is not in ECAL cracks
  bool photonLSCEta = false;
  if ( fabs( leptonL.photonEta) < maxSCEta_ && !( fabs( leptonL.photonEta ) > min_gap_SCEta_ && fabs( leptonL.photonEta ) < max_gap_SCEta_ ) ) photonLSCEta = true;
  bool photonHSCEta = false;
  if ( fabs( leptonH.photonEta) < maxSCEta_ && !( fabs( leptonH.photonEta ) > min_gap_SCEta_ && fabs( leptonH.photonEta ) < max_gap_SCEta_ ) ) photonHSCEta = true;
  if ( ( photonLSCEta && photonHSCEta ) || analysis != _2eTrack ) passedCuts.passSCEta=true;

  // Lepton track pt
  if ( analysis != _2eTrack ) {
    // Only one threshold in muon channel
    if ( leptonH.pt > minTrackPt1_ && leptonL.pt > minTrackPt1_ ) passedCuts.passTrackPt=true;
  }
  else {
    // In electron channel, apply "high" track pt cut on the lepton with the leading SC
    if ( leptonH.photonEt >= leptonL.photonEt ) {
      if ( leptonH.pt > minTrackPt1_ && leptonL.pt > minTrackPt2_ ) passedCuts.passTrackPt=true;
    }
    else if ( leptonH.photonEt < leptonL.photonEt ) {
      if ( leptonL.pt > minTrackPt1_ && leptonH.pt > minTrackPt2_ ) passedCuts.passTrackPt=true;
    }

  }

  passedCuts.passCaloMatch=true;  // No longer require calo matching
  // Check matched photon is within deltaR cone
  // And check these are different photons
  if ( ( leptonH.pmDeltaR < maxCaloMatchDeltaR_ && leptonL.pmDeltaR < maxCaloMatchDeltaR_ &&
      leptonH.photonEta != leptonL.photonEta && leptonH.photonPhi != leptonL.photonPhi && leptonH.photonEt != leptonL.photonEt )
      || analysis != _2eTrack ) {
    passedCuts.passPhotonMatch=true;
  }
  if ( fabs( leptonH.eta ) < maxEta_ && fabs( leptonL.eta ) < maxEta_  ) passedCuts.passEta=true;

  // Lepton d0/sigma
  if ( ( requireOppositeSignD0_ &&candidate.leptonD0SignificanceL_PVrefit_includingPVError * candidate.leptonD0SignificanceH_PVrefit_includingPVError > 0 ) ||
      !requireOppositeSignD0_ ) passedCuts.passOppSignD0=true;
  if ( ( cutOnSignedD0_  && candidate.leptonD0SignificanceL_PVrefit_includingPVError > minD0Sig_ && candidate.leptonD0SignificanceH_PVrefit_includingPVError > minD0Sig_ &&
        candidate.leptonD0SignificanceL_PVrefit_includingPVError < maxD0Sig_ && candidate.leptonD0SignificanceH_PVrefit_includingPVError < maxD0Sig_ ) ||
        ( !cutOnSignedD0_ && fabs( candidate.leptonD0SignificanceL_PVrefit_includingPVError ) > minD0Sig_ && fabs( candidate.leptonD0SignificanceH_PVrefit_includingPVError ) > minD0Sig_ )
  ) passedCuts.passLeptonD0=true;

  // Cuts on original leptons, but need to know about other lepton

  if ( analysis == _2eTrack ) {
    // Slightly larger inner cone for electron channel
    if ( candidate.leptonIsoL4/leptonL.pt < maxIso_ && candidate.leptonIsoH4/leptonH.pt < maxIso_ ) passedCuts.passIso=true;
  }
  else {
    if ( candidate.leptonIsoL/leptonL.pt < maxIso_ && candidate.leptonIsoH/leptonH.pt < maxIso_ ) passedCuts.passIso=true;
  }

  //  if ( ( leptonL.triggerMatch != 0 && leptonH.triggerMatch != 0 && candidate.differentTO ) || !( analysis == _2muTrack) ) passedCuts.passTriggerMatch=true;
  if ( ( leptonL.triggerMatch != 0 && leptonH.triggerMatch != 0 && candidate.differentTO ) || analysis == _2eTrack ) passedCuts.passTriggerMatch=true;
//  passedCuts.passTriggerMatch=true;

  //   Cuts on dilepton
  passedCuts.passMinLxySig=true; // Cut has been removed
  passedCuts.passMaxLxySig=true; // Cut has been removed

  // Opposite charge
  if ( ( oppositeCharge_ && ( leptonL.charge != leptonH.charge ) ) || !oppositeCharge_ ) passedCuts.passOppCharge=true;
  // Vertex
  if ( !requireVertex_ || (requireVertex_ && candidate.validVertex ) ) passedCuts.passRequireVertex=true;
  if ( !requireVertex_ || (requireVertex_ && candidate.vertexChi2 < maxVertexChi2_ ) ) passedCuts.passVertexChi2=true;
  // Delta R between leptons
  if ( candidate.deltaR > minDeltaR_ || analysis == _2eTrack ) passedCuts.passDeltaR=true;
  // Cos alpha
  if ( candidate.cosine > minCosine_ || analysis == _2eTrack ) passedCuts.passCosine=true;
  // Collinearity
  if ( fabs(candidate.dPhiCorr) < maxDeltaPhi_ && fabs(candidate.dPhiCorr) >= minDeltaPhi_ ) passedCuts.passDeltaPhi=true;
  // Dilepton Mass
  if ( mass > minMass_ ) passedCuts.passMass=true;

  // Hits before vertex
  if ( candidate.hitsBeforeVertexL + candidate.hitsBeforeVertexH <= maxHitsBeforeVertex_ ) passedCuts.passHitsBeforeVertex=true;

  // Missing hits after vertex
  if ( candidate.missedLayersAfterVertexL + candidate.missedLayersAfterVertexH <= maxMissingHitsAfterVertex_ ) passedCuts.passMissingHitsAfterVertex=true;

  // Photon ID cuts
  bool passSigmaIetaIeta=false;
  passSigmaIetaIeta = ( fabs(leptonL.photonEta) < 1.55 && leptonL.photonSigmaIetaIeta < maxSigmaIetaIeta_barrel_ ) || ( fabs(leptonL.photonEta) > 1.55 && leptonL.photonSigmaIetaIeta < maxSigmaIetaIeta_endcap_ ) ? true : false;
  bool photonLPass = ( leptonL.photonHadTowOverEm < maxHoverE_ && leptonL.photonR9 > minR9_ && passSigmaIetaIeta ) ? true : false;
  passSigmaIetaIeta = ( fabs(leptonH.photonEta) < 1.55 && leptonH.photonSigmaIetaIeta < maxSigmaIetaIeta_barrel_ ) || ( fabs(leptonH.photonEta) > 1.55 && leptonH.photonSigmaIetaIeta < maxSigmaIetaIeta_endcap_ ) ? true : false;
  bool photonHPass = ( leptonH.photonHadTowOverEm < maxHoverE_ && leptonH.photonR9 > minR9_ && passSigmaIetaIeta ) ? true : false;
  if ( ( photonLPass && photonHPass ) || analysis != _2eTrack ) passedCuts.passPhotonID = true;

  // Muon ID cuts
  if ( ( leptonL.isLooseMuon && leptonH.isLooseMuon ) || analysis != _2globalOrTrackerMu ) passedCuts.passMuonID = true;

  // Track quality cuts
  // These are cuts we will potentially apply to the central tracks corresponding to global/tracker muons
  // To match criteria we apply to tracks in the track+TO analysis
  if ( analysis != _2globalOrTrackerMu ||
       ( ( leptonL.highPurity==1 && leptonH.highPurity==1 ) &&
         ( leptonL.nLayers3D >= 2 && leptonH.nLayers3D >= 2 ) &&
         ( leptonL.nLayers >= 6 && leptonH.nLayers >= 6 ) &&
         ( leptonL.tip < 30.0 && leptonH.tip < 30.0 ) &&
         ( leptonL.lip < 30.0 && leptonH.lip < 30.0 ) ) ) passedCuts.passTrackQuality = true;
  return passedCuts;
}

// Checks if candidate has passed all cuts
// Returns true if all cuts have been passed
bool DileptonAnalysisCuts::passAllCuts( DileptonAnalysisCuts::PassedWhichCuts cuts ) {
  if ( !cuts.passTrackPt ) return false;
  if ( !cuts.passSCEt ) return false;
  if ( !cuts.passSCEta ) return false;
  if ( !cuts.passEta ) return false;
  if ( !cuts.passOppSignD0) return false;
  if ( !cuts.passLeptonD0 ) return false;
  if ( !cuts.passIso ) return false;
  if ( !cuts.passCaloMatch ) return false;
  if ( !cuts.passMinLxySig ) return false;
  if ( !cuts.passMaxLxySig ) return false;
  if ( !cuts.passOppCharge ) return false;
  if ( !cuts.passTriggerMatch ) return false;
  if ( !cuts.passPhotonMatch ) return false;
  if ( !cuts.passRequireVertex ) return false;
  if ( !cuts.passVertexChi2 ) return false;
  if ( !cuts.passHitsBeforeVertex ) return false;
  if ( !cuts.passMissingHitsAfterVertex ) return false;
  if ( !cuts.passDeltaR ) return false;
  if ( !cuts.passCosine ) return false;
  if ( !cuts.passDeltaPhi ) return false;
  if ( !cuts.passMass ) return false;
  if ( !cuts.passPhotonID ) return false;
  if ( !cuts.passMuonID ) return false;
  return true;
}

// Print whether each cut was passed or failed
// Useful for debugging
void DileptonAnalysisCuts::printPassForOneCand( DileptonAnalysisCuts::PassedWhichCuts cuts ) {
  cout << "Track pt : " << cuts.passTrackPt << endl;
  cout << "SC Et : " << cuts.passSCEt << endl;
  cout << "SC Eta : " << cuts.passSCEta << endl;
  cout << "Track eta : " << cuts.passEta << endl;
  cout << "Track d0 sig : " << cuts.passLeptonD0 << endl;
  cout << "Opposite sign d0 : "<< cuts.passOppSignD0 << endl;
  cout << "Iso : " << cuts.passIso << endl;
  cout << "Calo Match : " << cuts.passCaloMatch << endl;
  cout << "Min Lxy sig : " << cuts.passMinLxySig << endl;
  cout << "Max Lxy sig : " << cuts.passMaxLxySig << endl;
  cout << "Opposite charge : " << cuts.passOppCharge << endl;
  cout << "Trigger match : " << cuts.passTriggerMatch << endl;
  cout << "Vertex Chi2 : " << cuts.passVertexChi2 << endl;
  cout << "Hits before vertex : " << cuts.passHitsBeforeVertex << endl;
  cout << "Missing hits after vertex : " << cuts.passMissingHitsAfterVertex << endl;
  cout << "Delta R : " << cuts.passDeltaR << endl;
  cout << "Cosine  : " << cuts.passCosine << endl;
  cout << "Delta Phi  : " << cuts.passDeltaPhi << endl;
  cout << "Mass  : " << cuts.passMass << endl;
  cout << "Photon ID  : " << cuts.passPhotonID << endl;
  cout << "Photon Match : " << cuts.passPhotonMatch << endl;
  cout << "Muon ID : " << cuts.passMuonID << endl;
  cout << "Track quality : " << cuts.passTrackQuality << endl;
  cout << endl;
}

// Prints value of cuts, useful for debugging
void DileptonAnalysisCuts::printCutValues() {
  cout << "=========================================" << endl;
  cout << "Printing cut values for analysis : " << analysisType_ << endl;
  cout << "And set of cuts : " << setOfCuts_ << endl;
  cout << "===" << endl;
  cout << "---> Lepton cuts" << endl;
  if ( analysisType_==_2eTrack) {
    cout << "Minimum track pt (leading SC) : " << minTrackPt1_ << endl;
    cout << "Minimum track pt (sub-leading SC) : " << minTrackPt2_ << endl;
    cout << "Minimum SC Et (leading SC) : " << minSCEt1_ << endl;
    cout << "Minimum SC Et (sub-leading SC) : " << minSCEt2_ << endl;
  }
  else {
    cout << "Minimum track pt : " << minTrackPt1_ << endl;
  }
  cout << "Maximum eta : " << maxEta_ << endl;
  cout << "Require opposite sign d0 : " << requireOppositeSignD0_ << endl;
  cout << "Minimum d0 significance : " << minD0Sig_ << endl;
  cout << "Maximum d0 significance : " << maxD0Sig_ << endl;
  cout << "Maximum sum pt (isolation) : " << maxIso_ << endl;
  cout << "Maximum calo match delta R : " << maxCaloMatchDeltaR_ << endl;
  cout << "---> Photon ID cuts" << endl;
  cout << "Minimum photon R9 : " << minR9_ << endl;
  cout << "Maximum photon H/E : " << maxHoverE_ << endl;
  cout << "Maximum photon sigma ieta ieta barrel/endcap : " << maxSigmaIetaIeta_barrel_ << "/" << maxSigmaIetaIeta_endcap_ << endl;
  cout << "---> Di Lepton cuts" << endl;
  cout << "Minimum Lxy significance : " << minLxySig_ << endl;
  cout << "Maximum Lxy significance : " << maxLxySig_ << endl;
  cout << "Require opposite charged leptons : " << oppositeCharge_ << endl;
  cout << "Require vertex : " << requireVertex_ << endl;
  cout << "Maximum vertex Chi^2 : " << maxVertexChi2_ << endl;
  cout << "Maximum hits before vertex : " << maxHitsBeforeVertex_ << endl;
  cout << "Maximum missing hits after vertex : " << maxMissingHitsAfterVertex_ << endl;
  cout << "Minimum deltaR between leptons : " << minDeltaR_ << endl;
  cout << "Minimum cos(angle between leptons) : " << minCosine_ << endl;
  cout << "Maximum delta Phi : " << maxDeltaPhi_ << endl;
  cout << "Minimum invariant mass : " << minMass_ << endl;
  cout << "=========================================" << endl;
}
