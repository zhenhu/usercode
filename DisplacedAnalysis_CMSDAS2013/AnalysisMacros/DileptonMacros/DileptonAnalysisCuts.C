#define DileptonAnalysisCuts_cxx

#include "DileptonAnalysisCuts.h"

DileptonAnalysisCuts::DileptonAnalysisCuts( analysisType analysis, analysisCuts cuts ):
// Initialize cut values so all cands should pass
setOfCuts_(cuts), analysisType_(analysis),
minTrackPt_(-1), maxEta_(9999), minAbsD0Sig_(-99999),
maxIso_(9999), maxCaloMatchDeltaR_(999999),
minLxySig_(-99999), maxLxySig_(9999),
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
      minTrackPt_=26;
      minSCEt_=51;
      maxCaloMatchDeltaR_=0.1;
      maxEta_=2;
      minAbsD0Sig_=3;
      maxIso_=0.1;
      minLxySig_=10;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=-1;
      //      minCosine_=-99999999999;
      maxDeltaPhi_=99999999999;
      minMass_=15;
    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt_=26;
      minSCEt_=-1;
      maxCaloMatchDeltaR_=99999999999;
      maxEta_=2;
      minAbsD0Sig_=3;
      maxIso_=0.1;
      minLxySig_=8;
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
      minTrackPt_=26;
      minSCEt_=-1;
      maxCaloMatchDeltaR_=99999999999;
      maxEta_=2;
      minAbsD0Sig_=3;
      maxIso_=0.1;
      minLxySig_=8;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=0.2;
      minCosine_=-0.95;
      maxDeltaPhi_=99999999999;
      minMass_=15;
    }
    else if ( analysisType_==_2saMu ) {
      // Cuts for di-SA muon analysis
      minTrackPt_=26;
      minSCEt_=-1;
      maxCaloMatchDeltaR_=99999999999;
      maxEta_=2;
      minAbsD0Sig_=3;
      maxIso_=0.1;
      minLxySig_=8;
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
  // REMOVED LIFETIME CUTS
  //
  else if ( setOfCuts_==_removedLifetime){
    if ( analysisType_==_2eTrack) {
      // Cuts for dieletron (track+TO) analysis
      minTrackPt_=26;
      minSCEt_=51;
      maxCaloMatchDeltaR_=0.1;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=0.1;
      minLxySig_=-99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=5;
      maxHitsBeforeVertex_=1;
      minDeltaR_=-1;
      minCosine_=-99999999999;
      maxDeltaPhi_=99999999999;
      minMass_=15;

    }
    else if ( analysisType_==_2muTrack) {
      // Cuts for dimuon (track+TO) analysis
      minTrackPt_=26;
      minSCEt_=-1;
      maxCaloMatchDeltaR_=99999999999;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=0.1;
      minLxySig_=-99999999999;
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
      minTrackPt_=26;
      minSCEt_=-1;
      maxCaloMatchDeltaR_=99999999999;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=0.1;
      minLxySig_=-99999999999;
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
      minTrackPt_=26;
      minSCEt_=-1;
      maxCaloMatchDeltaR_=99999999999;
      maxEta_=2;
      minAbsD0Sig_=0;
      maxIso_=0.1;
      minLxySig_=-99999999999;
      oppositeCharge_=true;
      maxVertexChi2_=5;
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
DileptonAnalysisCuts::PassedWhichCuts DileptonAnalysisCuts::whichCuts( TreeDipseudoLeptonCandidate & candidate, TreeLepton & leptonL, TreeLepton & leptonH, analysisType analysis, double lxyScale, double d0Scale ) {

  PassedWhichCuts passedCuts;

  // Check if candidate passed each individual cut

  // Cuts on original leptons (before refit)

  // Lepton track pt
  if ( leptonH.pt > minTrackPt_ && leptonL.pt > minTrackPt_ ) passedCuts.passTrackPt=true;
  // Lepton matched SC Et (electron channel only)
  if ( ( leptonH.scEt > minSCEt_ && leptonL.scEt > minSCEt_ ) || analysis != _2eTrack ) passedCuts.passSCEt=true;

  if ( ( leptonH.cmDeltaR < maxCaloMatchDeltaR_ && leptonL.cmDeltaR < maxCaloMatchDeltaR_ ) || analysis != _2eTrack ) passedCuts.passCaloMatch=true;
  if ( fabs( leptonH.eta ) < maxEta_ && fabs( leptonL.eta ) < maxEta_  ) passedCuts.passEta=true;
  if ( fabs( leptonH.d0Significance*d0Scale) > minAbsD0Sig_ && fabs( leptonL.d0Significance*d0Scale) > minAbsD0Sig_ ) passedCuts.passLeptonAbsD0=true;

  // Cuts on original leptons, but need to know about other lepton
  if ( candidate.leptonIsoL/candidate.leptonPtL < maxIso_ && candidate.leptonIsoH/candidate.leptonPtH < maxIso_ ) passedCuts.passIso=true;
  if ( ( leptonL.triggerMatch != 0 && leptonH.triggerMatch != 0 && candidate.differentTO ) || !( analysis == _2eTrack || analysis == _2muTrack) ) passedCuts.passTriggerMatch=true;

//   Cuts on dilepton
    int sign = 1;
    if( candidate.dPhiCorr > TMath::PiOver2() ) sign = -1;

  if ( sign*candidate.decayLengthSignificance*lxyScale > minLxySig_ ) passedCuts.passMinLxySig=true;
  // Completely remove cut on max Lxy/sigma
  //  if ( candidate.decayLengthSignificance*lxyScale < maxLxySig_ ) passedCuts.passMaxLxySig=true;
  passedCuts.passMaxLxySig=true;
  if ( ( oppositeCharge_ && ( candidate.leptonChargeL != candidate.leptonChargeH ) ) || !oppositeCharge_ ) passedCuts.passOppCharge=true;
  if ( candidate.vertexChi2 < maxVertexChi2_ ) passedCuts.passVertexChi2=true;
  if ( candidate.deltaR > minDeltaR_ || analysis == _2eTrack ) passedCuts.passDeltaR=true;
  if ( candidate.cosine > minCosine_ || analysis == _2eTrack ) passedCuts.passCosine=true;
  if ( candidate.dPhiCorr < maxDeltaPhi_ ) passedCuts.passDeltaPhi=true;

  double mass = candidate.mass;
  if (analysis==_2eTrack) mass=candidate.caloCorrMass;

  if ( mass > minMass_ ) passedCuts.passMass=true;


  // FIXME No cut on this at the moment
  passedCuts.passHitsBeforeVertex=true;

  return passedCuts;
}

// Checks if candidate has passed all cuts
// Returns true if all cuts have been passed
bool DileptonAnalysisCuts::passAllCuts( DileptonAnalysisCuts::PassedWhichCuts cuts ) {
  if ( !cuts.passTrackPt ) return false;
  if ( !cuts.passSCEt ) return false;
  if ( !cuts.passEta ) return false;
  if ( !cuts.passLeptonAbsD0 ) return false;
  if ( !cuts.passIso ) return false;
  if ( !cuts.passCaloMatch ) return false;
  if ( !cuts.passMinLxySig ) return false;
  if ( !cuts.passMaxLxySig ) return false;
  if ( !cuts.passOppCharge ) return false;
  if ( !cuts.passTriggerMatch ) return false;
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
void DileptonAnalysisCuts::printCutValues() {
  std::cout << "=========================================" << std::endl;
  std::cout << "Printing cut values for analysis : " << analysisType_ << std::endl;
  std::cout << "And set of cuts : " << setOfCuts_ << std::endl;
  std::cout << "===" << std::endl;
  std::cout << "---> Lepton cuts" << std::endl;
  std::cout << "Minimum track pt : " << minTrackPt_ << std::endl;
  std::cout << "Minimum SC Et : " << minSCEt_ << std::endl;
  std::cout << "Maximum eta : " << maxEta_ << std::endl;
  std::cout << "Minimum abs d0 significance : " << minAbsD0Sig_ << std::endl;
  std::cout << "Maximum sum pt (isolation) : " << maxIso_ << std::endl;
  std::cout << "Maximum calo match delta R : " << maxCaloMatchDeltaR_ << std::endl;
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
