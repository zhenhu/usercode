// This is a clone of DileptonAnalysisCuts except with
// the pt cuts reverted to their 2011 values, for comparison
// with the 2011 efficiencies.

#define MixedChannelEffCuts_cxx

#include "MixedChannelEffCuts.h"

MixedChannelEffCuts::MixedChannelEffCuts( analysisType analysis, analysisCuts cuts ):
// Initialize cut values so all cands should pass
setOfCuts_(cuts), analysisType_(analysis),
minPt_(-1), maxEta_(9999), minAbsD0Sig_(-99999),
maxIso_(9999), minLxySig_(-99999), maxLxySig_(9999),
oppositeCharge_(true), maxVertexChi2_(-1), maxHitsBeforeVertex_(9999),
minDeltaR_(-1), minCosine_(-9999), minMass_(0)
{
  // Different set of cuts for final, tight, loose etc.

  //
  // FINAL SELECTION CUTS
  //
  if ( setOfCuts_==_final){
    // Set up different sets of cuts, depending on what type of dilepton we are analyzing
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minPt_=41;
      maxEta_=2;
      minAbsD0Sig_=3;
      maxIso_=4;
      minLxySig_=8;
      maxLxySig_=99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=-1;
      minCosine_=99999999999;
      maxDeltaPhi_=0.8;
      minMass_=15;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minPt_=33;
      maxEta_=2;
      minAbsD0Sig_=2;
      maxIso_=4;
      minLxySig_=5;
      maxLxySig_=99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=0.2;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu ) {
      // Cuts for di-global muon analysis
      minPt_=33;
      maxEta_=2;
      minAbsD0Sig_=2;
      maxIso_=4;
      minLxySig_=5;
      maxLxySig_=99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=0.2;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-SA muon analysis
      minPt_=33;
      maxEta_=2;
      minAbsD0Sig_=2;
      maxIso_=4;
      minLxySig_=5;
      maxLxySig_=99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=0.2;
      minMass_=15;
    }
  }

  //
  // INVERTED LIFETIME CUTS
  //
  else if ( setOfCuts_==_invertedLifetime){
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minPt_=51;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=4;
      minLxySig_=-99999999999;
      maxLxySig_=8;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=-1;
      minCosine_=99999999999;
      maxDeltaPhi_=99999999999;
      minMass_=15;

    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minPt_=33;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=4;
      minLxySig_=-99999999999;
      maxLxySig_=5;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=99999999999;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu ) {
      // Cuts for di-global muon analysis
      minPt_=33;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=4;
      minLxySig_=-99999999999;
      maxLxySig_=5;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=99999999999;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-global muon analysis
      minPt_=33;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=4;
      minLxySig_=-99999999999;
      maxLxySig_=5;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=99999999999;
      minMass_=15;
    }
  }

  //
  // LOOSE SET OF CUTS
  //
  else if ( setOfCuts_==_loose1){
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minPt_=51;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=4;
      minLxySig_=3;
      maxLxySig_=99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=-1;
      minCosine_=99999999999;
      maxDeltaPhi_=99999999999;
      minMass_=15;

    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minPt_=33;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=4;
      minLxySig_=3;
      maxLxySig_=99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=99999999999;
      minMass_=15;
    }
    else if ( analysisType_==_2globalMu ) {
      // Cuts for di-global muon analysis
      minPt_=33;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=4;
      minLxySig_=3;
      maxLxySig_=99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=20;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=99999999999;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-global muon analysis
      minPt_=33;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=4;
      minLxySig_=3;
      maxLxySig_=99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=20;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=99999999999;
      minMass_=15;
    }
  }
  // Print cut values to screen
  printCutValues();
}

// Checks which cuts have passed and then returns a struct saying which cuts have passed
MixedChannelEffCuts::PassedWhichCuts MixedChannelEffCuts::whichCuts( TreeDipseudoLeptonCandidate & candidate ) {

  PassedWhichCuts passedCuts;

  // Check if candidate passed each individual cut
  if ( candidate.leptonPtH > minPt_ && candidate.leptonPtL > minPt_ ) passedCuts.passPt=true;
  if ( fabs( candidate.leptonEtaH ) < maxEta_ && fabs( candidate.leptonEtaL ) < maxEta_  ) passedCuts.passEta=true;
  if ( fabs( candidate.leptonD0SignificanceL) > minAbsD0Sig_ && fabs( candidate.leptonD0SignificanceH) > minAbsD0Sig_ ) passedCuts.passLeptonAbsD0=true;
  if ( candidate.leptonIsoL < maxIso_ && candidate.leptonIsoH < maxIso_ ) passedCuts.passIso=true;

//  int sign = 1;
//  if( candidate.dPhiCorr > TMath::PiOver2() ) sign = -1;

  if ( candidate.decayLengthSignificance > minLxySig_ ) passedCuts.passMinLxySig=true;
  if ( candidate.decayLengthSignificance < maxLxySig_ ) passedCuts.passMaxLxySig=true;
  if ( ( oppositeCharge_ && ( candidate.leptonChargeL != candidate.leptonChargeH ) ) || !oppositeCharge_ ) passedCuts.passOppCharge=true;
  if ( candidate.vertexChi2 < maxVertexChi2_ ) passedCuts.passVertexChi2=true;
//  if ( candidate.deltaR > minDeltaR_ ) passedCuts.passDeltaR=true;
  passedCuts.passDeltaR=true;
//  if ( candidate.cosine > minCosine_ ) passedCuts.passCosine=true;
  passedCuts.passCosine=true;
  if ( candidate.dPhiCorr < maxDeltaPhi_ ) passedCuts.passDeltaPhi=true;

  if ( candidate.mass > minMass_ ) passedCuts.passMass=true;


  // FIXME No cut on this at the moment
  passedCuts.passHitsBeforeVertex=true;

  return passedCuts;
}

// Checks if candidate has passed all cuts
// Returns true if all cuts have been passed
bool MixedChannelEffCuts::passAllCuts( MixedChannelEffCuts::PassedWhichCuts cuts ) {
  if ( !cuts.passPt ) return false;
  if ( !cuts.passEta ) return false;
  if ( !cuts.passLeptonAbsD0 ) return false;
  if ( !cuts.passIso ) return false;
  if ( !cuts.passMinLxySig ) return false;
  if ( !cuts.passMaxLxySig ) return false;
  if ( !cuts.passOppCharge ) return false;
  if ( !cuts.passVertexChi2 ) return false;
  // FIXME No cut on this at the moment
//  if ( !cuts.passHitsBeforeVertex ) return false;
  if ( !cuts.passDeltaR ) return false;
  if ( !cuts.passCosine ) return false;
  if ( !cuts.passDeltaPhi ) return false;
  if ( !cuts.passMass ) return false;

  return true;
}

// Prints value of cuts, useful for debugging
void MixedChannelEffCuts::printCutValues() {
  std::cout << "=========================================" << std::endl;
  std::cout << "Printing cut values for analysis : " << analysisType_ << std::endl;
  std::cout << "And set of cuts : " << setOfCuts_ << std::endl;
  std::cout << "===" << std::endl;
  std::cout << "---> Lepton cuts" << std::endl;
  std::cout << "Minimum pt : " << minPt_ << std::endl;
  std::cout << "Maximum eta : " << maxEta_ << std::endl;
  std::cout << "Minimum abs d0 significance : " << minAbsD0Sig_ << std::endl;
  std::cout << "Maximum sum pt (isolation) : " << maxIso_ << std::endl;
  std::cout << "---> Di Lepton cuts" << std::endl;
  std::cout << "Minimum Lxy significance : " << minLxySig_ << std::endl;
  std::cout << "Maximum Lxy significance : " << maxLxySig_ << std::endl;
  std::cout << "Require opposite charged leptons : " << oppositeCharge_ << std::endl;
  std::cout << "Maximum vertex Chi^2 : " << maxVertexChi2_ << std::endl;
  std::cout << "Maximum hits before vertex : " << maxHitsBeforeVertex_ << std::endl;
  std::cout << "Minimum deltaR between leptons : " << minDeltaR_ << std::endl;
  std::cout << "Minimum cos(angle between leptons) : " << minCosine_ << std::endl;
  std::cout << "Maximum delta Phi : " << maxDeltaPhi_ << std::endl;
  std::cout << "Minimum invariant mass : " << minMass_ << std::endl;
  std::cout << "=========================================" << std::endl;
}
