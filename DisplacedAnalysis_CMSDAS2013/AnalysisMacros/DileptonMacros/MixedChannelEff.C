// a branch of DileptonAnalyzer with some more code for
// studying efficiencies in the 2mu+2jet case

#define MixedChannelEff_cxx
#include "MixedChannelEff.h"

const int nAcceptanceStages = 15;
const char *label[nAcceptanceStages] = {"", "lepton pt", "lepton eta", "lepton d0/sigma", "lepton iso", "lepton charge",
					"cosmic veto", "dilepton deltaR", "trigger match", "vertex chi^2",
					"vertex dPhi", "hits before vertex", "vertex lxy/sigma", "candidate mass", "accepted"};

//
// FUNCTION DEFINITIONS
//

// Get total weight for this event, including PU weight
double MixedChannelEff::getEventWeight() {
  double totalWeight = 0;
  if ( dirName_.Contains("Data") ) totalWeight = weight_;
  else {
    double puweight = puweights_.weight( candidates->nvtx_true );
    totalWeight = puweight * weight_;
  }
  return totalWeight;
}

// Checks, given the type of analysis, that the candidate is made up of suitable leptons
bool MixedChannelEff::correctLeptonsInCandidate( TreeDipseudoLeptonCandidate & cand )
{
  // Get leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  // Require 2 global muons
  if ( anaType_==_2globalMu ) {
    if ( leptonL.isGlobalMuon && leptonH.isGlobalMuon ) {
      return true;
    }
  }
  // Require 2 tracker muons
  else if ( anaType_==_2trackerMu ) {
    if ( leptonL.isTrackerMuon && leptonH.isTrackerMuon ) return true;
  }
  else if ( anaType_==_2saMu ) {
    if ( leptonL.isStandAloneMuon && leptonH.isStandAloneMuon ) return true;
  }
  // Require 2 track+TO
  else if ( anaType_==_2eTrack || anaType_==_2muTrack ) {
    if ( leptonL.isCentralTrack && leptonH.isCentralTrack ) return true;
  }
  else std::cout << "WARNING : Unidentified leptons in this candidate" << std::endl;

  return false;
}

// Given an index of a lepton in a candidate, will return the corresponding lepton from TreeLepton collection
// This is needed as it isn't a 1<->1 match
const TreeLepton MixedChannelEff::getLepton( unsigned int index ) {
  // Loop over TreeLeptons
  for (  unsigned int i = 0; i < candidates->leptons_.size(); i++) {
    if ( candidates->leptons_[i].index >=0 ) {
      if ( index == abs( candidates->leptons_[i].index ) ) return candidates->leptons_[i];
    }
  }
  std::cout << "WARNING : Could not find this lepton in TreeLepton Candidate" << std::endl;
  return TreeLepton();
}

bool MixedChannelEff::triggerMatching( TreeDipseudoLeptonCandidate & cand )
{
  // Get original leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  if( leptonL.triggerMatch != 0 && leptonH.triggerMatch != 0 ) return true;//&& leptonL.triggerObjectIndex != leptonH.triggerObjectIndex ) return true;
  return false;
}

bool MixedChannelEff::caloMatch( TreeDipseudoLeptonCandidate & cand )
{
  // Get original leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  if( leptonL.hasCaloMatch != 0 && leptonH.hasCaloMatch != 0 ) return true;
  return false;
}

bool MixedChannelEff::correctlyReconstructed(TreeDipseudoLeptonCandidate & cand) {
  // Get original leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  // Check if leptons have correct flavour (or are even leptons)
  bool correctLeptons=false;
  if ( anaType_==_2eTrack ) {
    if ( abs( leptonL.genPdgId ) == 11 && abs( leptonH.genPdgId ) == 11 ) correctLeptons=true;
  }
  else if ( abs( leptonL.genPdgId ) == 13 && abs( leptonH.genPdgId ) == 13 ) correctLeptons=true;

  if ( !correctLeptons ) return false;

  // Check if leptons have the same production vertex
  if ( leptonL.genVertexX == leptonH.genVertexX && leptonL.genVertexY == leptonH.genVertexY && leptonL.genVertexZ == leptonH.genVertexZ ) {
    // Check if they have the same parent pdg id
    if ( leptonL.genSignalOriginPdgId == leptonH.genSignalOriginPdgId ) return true;
  }
  return false;
}


//
// END OF FUNCTION DEFINITIONS
//

//
// MAIN ANALYZER LOOP
//
void MixedChannelEff::Loop()
{
  // Check you have a file/chain
  if (fChain == 0) return;

  // Get number of entries in chain
  Long64_t nentries = fChain->GetEntriesFast();

  int unweightedTotalEvents = 0;
  int unweightedAcceptedEvents = 0;
  int nFail[nAcceptanceStages] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int currentFailStage = -1;

  double weightedTotalEvents = 0;
  double weightedAcceptedEvents = 0;

  // Loop over events
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    // Checks recommended from TTree:MakeClass
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    fChain->GetEntry(jentry);

    double eventWeight = getEventWeight();

    unweightedTotalEvents++;
    weightedTotalEvents += eventWeight;
    currentFailStage = -1;
    bool acceptedThisEvent = false;
    
    // Study gen level info if this is signal MC
    // In particular, get total number of exotics decaying to something this analysis is sensitive to?
    if ( isSignalMC_ ) {
      //      std::cout << candidates->ll1_daughterPdgId << std::endl;
      // Count number of exotics decaying into sensitive channel
      if ( anaType_==_2eTrack ) {
        if ( candidates->ll1_daughterPdgId == 11 ) ++numExoticsInDecayChannel_;
        if ( candidates->ll2_daughterPdgId == 11 ) ++numExoticsInDecayChannel_;
      }
      else {
        if ( candidates->ll1_daughterPdgId == 13 ) ++numExoticsInDecayChannel_;
        if ( candidates->ll2_daughterPdgId == 13 ) ++numExoticsInDecayChannel_;
      }
    }

    // Loop over candidates in event
    for( unsigned int iTreeCand=0; iTreeCand != candidates->candidates_.size(); ++iTreeCand ) {

      TreeDipseudoLeptonCandidate cand = candidates->candidates_.at(iTreeCand);

      // Check what type of leptons make up this candidate
      if ( !correctLeptonsInCandidate(cand) ) continue;

      // Require trigger match if this is a track+TO analysis
      if ( ( anaType_==_2eTrack || anaType_==_2muTrack ) && !triggerMatching(cand) ) {
	if (currentFailStage < 8) currentFailStage = 8; // bookkeep this event correctly before moving on
	continue;
      }

      // Require calo match if this is an electron track+TO analysis
      if ( anaType_==_2eTrack && !caloMatch(cand) ) continue;

      // Get leptons
      TreeLepton leptonL = getLepton( cand.leptonIndexL );
      TreeLepton leptonH = getLepton( cand.leptonIndexH );

      // Sign of Lxy/sigma
      int sign = 1;
      if( cand.dPhiCorr > TMath::PiOver2() ) sign = -1;

      // Apply analysis cuts.
      // And fill histograms_
      MixedChannelEffCuts::PassedWhichCuts finalCuts = dileptonCuts_final_.whichCuts( cand );
      MixedChannelEffCuts::PassedWhichCuts invertedCuts = dileptonCuts_invertedLifetime_.whichCuts( cand );
      MixedChannelEffCuts::PassedWhichCuts looseCuts = dileptonCuts_loose_.whichCuts( cand );

      // n-1 plots

      // Lxy significance
      MixedChannelEffCuts::PassedWhichCuts finalCutsTemp = finalCuts;
      finalCutsTemp.passMinLxySig = true;
      finalCutsTemp.passMaxLxySig = true;

      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_LxySig_finalCuts->Fill( sign*cand.decayLengthSignificance, eventWeight );
      }

      // Chi^2
      finalCutsTemp = finalCuts;
      finalCutsTemp.passVertexChi2 = true;

      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_vertexChi2_finalCuts->Fill( cand.vertexChi2, eventWeight);
      }

      // dPhi
      finalCutsTemp = finalCuts;
      finalCutsTemp.passDeltaPhi = true;

      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_deltaPhi_finalCuts->Fill( cand.dPhiCorr, eventWeight);
      }

      // See where this one fails (if at all)
      int failStage;
      if (!finalCuts.passPt) failStage = 1;
      else if (!finalCuts.passEta) failStage = 2;
      else if (!finalCuts.passLeptonAbsD0) failStage = 3;
      else if (!finalCuts.passIso) failStage = 4;
      else if (!finalCuts.passOppCharge) failStage = 5;
      else if (!finalCuts.passCosine) failStage = 6;
      else if (!finalCuts.passDeltaR) failStage = 7;
      // trigger matching is up above -- that's why it's not here
      else if (!finalCuts.passVertexChi2) failStage = 9;
      else if (!finalCuts.passDeltaPhi) failStage = 10;
      else if (!finalCuts.passHitsBeforeVertex) failStage = 11; // warning -- not implemented yet
      else if (!finalCuts.passMinLxySig || !finalCuts.passMaxLxySig) failStage = 12;
      else if (!finalCuts.passMass) failStage = 13;
      else failStage = 14;
      if (failStage > currentFailStage) currentFailStage = failStage;

      if ( dileptonCuts_final_.passAllCuts( finalCuts ) ) {
        //
        // These candidates have passed all final selection criteria
        //
        histograms_.h_mass_finalCuts->Fill( cand.mass, eventWeight );
        histograms_.h_Lxy_finalCuts->Fill( cand.decayLength, eventWeight );
        histograms_.h_deltaR_finalCuts->Fill( cand.deltaR, eventWeight );

//        if ( cand.decayLengthSignificance > 10 ) {
//        std::cout << "Info on cand that's passed all cuts" << std::endl;
//        std::cout << "Correct leptons in cand ? " << correctLeptonsInCandidate(cand) << std::endl;
//        std::cout << "Lepton L pt : " << cand.leptonPtL << std::endl;
//        std::cout << "isSaMuons : " << leptonL.isStandAloneMuon << std::endl;
//        std::cout << "isGlobalMuons : " << leptonL.isGlobalMuon << std::endl;
//        std::cout << "isTrackerMuons : " << leptonL.isTrackerMuon << std::endl;
//        std::cout << "isCentralTrack : " << leptonL.isCentralTrack << std::endl;
//        std::cout << "Index in pseudo lepton : " << leptonL.pseudoLeptonIndex << std::endl;
//        std::cout << "Index in tree lepton : " << leptonL.index << std::endl;
//        std::cout << "Lepton H pt : " << cand.leptonPtH << std::endl;
//        std::cout << "isSaMuons : " << leptonH.isStandAloneMuon << std::endl;
//        std::cout << "isGlobalMuons : " << leptonH.isGlobalMuon << std::endl;
//        std::cout << "isTrackerMuons : " << leptonH.isTrackerMuon << std::endl;
//        std::cout << "isCentralTrack : " << leptonH.isCentralTrack << std::endl;
//        std::cout << "Index in pseudo lepton : " << leptonH.pseudoLeptonIndex << std::endl;
//        std::cout << "Index in tree lepton : " << leptonH.index << std::endl;
//        std::cout << "eventWeight : " << eventWeight << std::endl;
//        std::cout << "mass : " << cand.mass << std::endl;
//        std::cout << "Lxy : " << cand.decayLength << " Lxy/sigma : " << cand.decayLengthSignificance << std::endl;
//        std::cout << "dPhi : " << cand.dPhiCorr << std::endl;
//        std::cout << "Delta R : " << cand.deltaR << std::endl;
//        std::cout << "Cosine : " << cand.cosine << std::endl;
//        std::cout << "Signed Lxy : " << sign * cand.decayLength << " Signed Lxy/sigma : " << sign * cand.decayLengthSignificance << std::endl;
//        std::cout << std::endl;
//        }

        // Study efficiencies etc.
	acceptedThisEvent = true;

        // Study gen level info
        // Count number of correctly reconstructed candidates
        if ( isSignalMC_){
          ++numExoticsRECO_;
          if ( correctlyReconstructed( cand ) ) ++numExoticsInDecayChannelRECO_;
        }

      }

      // Inverted lifetime cuts
      if ( dileptonCuts_invertedLifetime_.passAllCuts( invertedCuts ) ) {
        histograms_.h_mass_invertedLifetimeCuts->Fill( cand.mass, eventWeight );
        histograms_.h_deltaR_invertedLifetimeCuts->Fill( cand.deltaR, eventWeight );
      }

      // Loose cuts
      if ( dileptonCuts_loose_.passAllCuts( looseCuts ) ) {
        histograms_.h_leptonPtL_looseCuts->Fill( cand.leptonPtL, eventWeight);
        histograms_.h_leptonPtH_looseCuts->Fill( cand.leptonPtH, eventWeight);
        histograms_.h_leptonEtaL_looseCuts->Fill( cand.leptonEtaL, eventWeight);
        histograms_.h_leptonEtaH_looseCuts->Fill( cand.leptonEtaH, eventWeight);
        histograms_.h_leptonAbsD0SigL_looseCuts->Fill( fabs(cand.leptonD0SignificanceL), eventWeight);
        histograms_.h_leptonAbsD0SigH_looseCuts->Fill( fabs(cand.leptonD0SignificanceH), eventWeight);
        histograms_.h_leptonIsoL_looseCuts->Fill( leptonL.iso, eventWeight);
        histograms_.h_leptonIsoH_looseCuts->Fill( leptonH.iso, eventWeight);
        histograms_.h_LxySig_looseCuts->Fill( sign*cand.decayLengthSignificance, eventWeight);
        histograms_.h_vertexChi2_looseCuts->Fill( cand.vertexChi2, eventWeight);
        histograms_.h_cosine_looseCuts->Fill( cand.cosine, eventWeight);
        histograms_.h_deltaR_looseCuts->Fill( cand.deltaR, eventWeight);
        histograms_.h_mass_looseCuts->Fill( cand.mass, eventWeight );
      }

      // n-1 cuts

      // Lxy significance
      MixedChannelEffCuts::PassedWhichCuts looseCutsTemp = looseCuts;
      looseCutsTemp.passMinLxySig = true;
      looseCutsTemp.passMaxLxySig = true;

      if ( dileptonCuts_loose_.passAllCuts( looseCutsTemp ) ) {
        histograms_.h_nMinus1_LxySig_looseCuts->Fill( sign*cand.decayLengthSignificance, eventWeight );
      }

    } // cand loop
    
    if (acceptedThisEvent) {
      unweightedAcceptedEvents++;
      weightedAcceptedEvents += eventWeight;
    }
    nFail[currentFailStage]++;

  } // event loop

  std::cout << "Efficiency: unweighted = " << unweightedAcceptedEvents << " / " << unweightedTotalEvents << " = " <<
    unweightedAcceptedEvents/(float)unweightedTotalEvents << std::endl;
  std::cout << "weighted = " << weightedAcceptedEvents << " / " << weightedTotalEvents << " = " <<
    weightedAcceptedEvents/weightedTotalEvents << std::endl;

  std::cout << "== Fails by stage ==" << std::endl;
  for (int i=1; i<nAcceptanceStages; i++) {
    std::cout << "Stage " << i << " (" << label[i] << "): " << nFail[i] << std::endl;
  }

  // Draw overflow of histograms_ in final bin
  histograms_.drawOverflows();

  // Save histograms_
  TString type("dummy");
  if ( anaType_==_2eTrack) type = "2eTrack";
  else if ( anaType_==_2muTrack ) type = "2muTrack";
  else if ( anaType_==_2globalMu ) type = "2globalMu";
  else if ( anaType_==_2trackerMu ) type = "2trackerMu";
  else if ( anaType_==_2saMu ) type = "2saMu";

  TString outputFileName("WeightedFiles/"+dirName_+"_weighted_"+type+".root");
  histograms_.writeHistograms(outputFileName);

  // Delete histograms
  histograms_.deleteHistograms();

}
