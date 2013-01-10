#define DileptonAnalyzer_cxx
#include "DileptonAnalyzer.h"


//
// FUNCTION DEFINITIONS
//

// Get total weight for this event, including PU weight
void DileptonAnalyzer::getEventWeight() {
  double totalWeight = 0;
  if ( dirName_.Contains("Data") ) totalWeight = weight_;
  else {
    double puweight = puweights_.weight( candidates->nvtx_true );
    totalWeight = puweight * weight_;
  }

  eventWeight_=totalWeight;
}

// Study triggers for signal MC
void DileptonAnalyzer::studyTriggers() {

  // For plot, only interested when only one exotic decays in correct channel
  bool plotEvent=true;
  if ( candidates->ll1_daughterPdgId ==  candidates->ll2_daughterPdgId ) plotEvent=false;

  // Work out which exotic to plot
  bool exoticToPlot=1;
  if ( anaType_==_2eTrack && candidates->ll1_daughterPdgId != 11 ) {
    exoticToPlot=2;
    // Check for now
    if ( candidates->ll2_daughterPdgId != 11 ) std::cout << "WARNING in studyTriggers" << std::endl;
  }
  else if ( (anaType_==_2muTrack || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu) && candidates->ll1_daughterPdgId != 13  ) {
    exoticToPlot=2;
    // Check for now
    if ( candidates->ll2_daughterPdgId != 13 ) std::cout << "WARNING in studyTriggers" << std::endl;
  }

  // Loop over signal trigger to see if one has fired
  for ( unsigned int iTrig = 0; iTrig < signalTriggers_.size(); iTrig++ ) {
    std::string trigger = signalTriggers_[iTrig];

    bool trigFired = ( find( triggers->begin(), triggers->end(), trigger ) != triggers->end() ? 1 : 0 );

    if ( trigger == "AnyTrigger" ) {
      if ( plotEvent ) {
        histograms_.h_trig_Lxy_all->Fill( (exoticToPlot==1) ? candidates->ll1_decayLength2D : candidates->ll2_decayLength2D );
        histograms_.h_trig_ctau_all->Fill( (exoticToPlot==1) ? candidates->ll1_ctau : candidates->ll2_ctau );
      }
      trigFired=true;
    }

    if ( trigFired ) {
      triggerFired_[iTrig]++;

      if ( iTrig==triggerToPlot_ ) {
        if ( plotEvent ) {
          histograms_.h_trig_Lxy_pass->Fill( (exoticToPlot==1) ? candidates->ll1_decayLength2D : candidates->ll2_decayLength2D );
          histograms_.h_trig_ctau_pass->Fill( (exoticToPlot==1) ? candidates->ll1_ctau : candidates->ll2_ctau );
        }
      }
    }
  }
}

// Require a/the signal trigger to have fired
bool DileptonAnalyzer::signalTriggerFired() {
  for ( unsigned int iTrig=0; iTrig<triggers->size(); iTrig++ ) {
    if ( triggers->at(iTrig) == signalTrigger_ ) return true;
  }
  return false;
}

// Checks, given the type of analysis, that the candidate is made up of suitable leptons
bool DileptonAnalyzer::correctLeptonsInCandidate( TreeDipseudoLeptonCandidate & cand )
{
  // Get leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  if ( correctLepton( leptonL ) && correctLepton( leptonH ) ) {
    return true;
  }

  return false;
}

// Check, given the type of analysis, that this is the correct type of lepton
bool DileptonAnalyzer::correctLepton( TreeLepton & lepton )
{
  // Require global muon
  if ( anaType_==_2globalMu ) {
    if ( lepton.isGlobalMuon ) return true;
  }
  // Require tracker muon
  else if ( anaType_==_2trackerMu ) {
    if ( lepton.isTrackerMuon ) return true;
  }
  else if ( anaType_==_2saMu ) {
    if ( lepton.isStandAloneMuon ) return true;
  }
  // Require track+TO
  else if ( anaType_==_2eTrack || anaType_==_2muTrack ) {
    if ( lepton.isCentralTrack ) return true;
  }
  else std::cout << "WARNING : Unidentified lepton" << std::endl;

  return false;
}

// Given an index of a lepton in a candidate, will return the corresponding lepton from TreeLepton collection
// This is needed as it isn't a 1<->1 match
const TreeLepton DileptonAnalyzer::getLepton( unsigned int index ) {
  // Loop over TreeLeptons
  for (  unsigned int i = 0; i < candidates->leptons_.size(); i++) {
    if ( candidates->leptons_[i].index >=0 ) {
      if ( index == abs( candidates->leptons_[i].index ) ) return candidates->leptons_[i];
    }
  }
  std::cout << "WARNING : Could not find this lepton in TreeLepton Candidate" << std::endl;
  return TreeLepton();
}

bool DileptonAnalyzer::triggerMatching( TreeDipseudoLeptonCandidate & cand )
{
  // Get original leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  if( leptonL.triggerMatch != 0 && leptonH.triggerMatch != 0 ) return true;//&& leptonL.triggerObjectIndex != leptonH.triggerObjectIndex ) return true;
  return false;
}

bool DileptonAnalyzer::leptonTriggerMatch( TreeLepton & lepton )
{
  if ( lepton.triggerMatch != 0 ) return true;
  return false;
}

// Check if this lepton is from a LL exotic using gen info
bool DileptonAnalyzer::leptonFromExotic( TreeLepton & lepton )
{
  int pdgId = lepton.genPdgId;

  // Check the gen particle matched to this lepton has the correct pdgid
  if ( (anaType_==_2eTrack) && abs(pdgId) != 11 ) {
    //    std::cout << "This electron doesn't have a match to a gen electron" << std::endl;
    return false;
  }
  else if ( ( anaType_==_2muTrack || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu ) && abs(pdgId) != 13 ) {
    //    std::cout << "This muon doesn't have a match to a gen muon" << std::endl;
    return false;
  }

  // Now check parent of lepton
  // FIXME Not very good check...
  if ( lepton.genSignalOriginPdgId > 6000000 ) return true;

  return false;
}

bool DileptonAnalyzer::caloMatch( TreeDipseudoLeptonCandidate & cand )
{
  // Get original leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  if( leptonL.hasCaloMatch != 0 && leptonH.hasCaloMatch != 0 ) return true;
  return false;
}


// Sum number of exotics this analysis is sensitive to
unsigned int DileptonAnalyzer::getNumberOfExotics() {

  // Get index of long lived pdg id
  // This is to check there is an interesting exotic in the event
  int pdgId = candidates->ll1_motherPdgId;
  unsigned int indexOfPdgId = getIndexOfSignalPdg( pdgId );
  // Could have mixed events (exotic1->jets, exotic2->leptons) so check other exotic if first one wasn't found to be of interest
  if ( indexOfPdgId == signalPdgId_.size() ) {
    pdgId = candidates->ll2_motherPdgId;
    indexOfPdgId = getIndexOfSignalPdg( candidates->ll2_motherPdgId );
  }

  // Check if this particle decay is interesting
  if ( indexOfPdgId < signalPdgId_.size() ) {
    // Count number of exotics decaying into sensitive channel
    int decayParticlePdgId=13;
    if ( anaType_==_2eTrack ) decayParticlePdgId=11;

    if ( fabs(candidates->ll1_daughterPdgId) == decayParticlePdgId &&  fabs(candidates->ll2_daughterPdgId) == decayParticlePdgId ) {
      numEvents_twoSensitiveDecay_[indexOfPdgId] += eventWeight_;
      // Store info of exotic that decays to interesting channel
      allExotics_twoSensitiveDecay_ << eventWeight_ << " " << candidates->ll1_ctau << " " << candidates->ll1_motherPdgId << " " << candidates->ll2_ctau << " " << candidates->ll2_motherPdgId << std::endl;
      return 2;
    }
    else if ( fabs(candidates->ll1_daughterPdgId) == decayParticlePdgId || fabs(candidates->ll2_daughterPdgId) == decayParticlePdgId ) {
      numEvents_oneSensitiveDecay_[indexOfPdgId] += eventWeight_;
      // Store info of both exotics as both decay in interesting channel
      allExotics_oneSensitiveDecay_ << eventWeight_ << " " << candidates->ll1_ctau << " " << candidates->ll1_motherPdgId << " " << candidates->ll2_ctau << " " << candidates->ll2_motherPdgId << std::endl;
      return 1;
    }
  }
  else {
    std::cout << "Warning in getNumberOfExotics()" << std::endl;
    std::cout << "indexOfPdgId : " << indexOfPdgId << std::endl;
    std::cout << "Pdg id of mother 1 : " << candidates->ll1_motherPdgId << std::endl;
    std::cout << "Pdg id of mother 2 : " << candidates->ll2_motherPdgId << std::endl;
  }

  return 0;
}

void DileptonAnalyzer::storeNumberOfExoticsRECO( TreeDipseudoLeptonCandidate & cand ) {

  bool correctRECO=correctlyReconstructed( cand );

  // Get long lived pdg id in event
  int pdgId = candidates->ll1_motherPdgId;
  unsigned int indexOfPdgId = getIndexOfSignalPdg( pdgId );
  // Could have crossed events, so check other exotic if the first one wasn't found
  if ( indexOfPdgId == signalPdgId_.size() ) {
    pdgId = candidates->ll2_motherPdgId;
    indexOfPdgId = getIndexOfSignalPdg( pdgId );
  }

  if ( indexOfPdgId < signalPdgId_.size() ) {

    if ( nSensitiveExoticDecayInEvent_ == 1 ) {
      numExoticsRECO_oneSensitiveDecay_[indexOfPdgId] += eventWeight_;
      recoExotics_oneSensitiveDecay_ << eventWeight_ << " " << candidates->ll1_ctau << " " << candidates->ll1_motherPdgId << " " << candidates->ll2_ctau << " " << candidates->ll2_motherPdgId << std::endl;
      if ( correctRECO ) numExoticsCorrectRECO_oneSensitiveDecay_[indexOfPdgId] += eventWeight_;
    }
    else if ( nSensitiveExoticDecayInEvent_ == 2 ) {
      numExoticsRECO_twoSensitiveDecay_[indexOfPdgId] += eventWeight_;
      recoExotics_twoSensitiveDecay_ << eventWeight_ << " " << candidates->ll1_ctau << " " << candidates->ll1_motherPdgId << " " << candidates->ll2_ctau << " " << candidates->ll2_motherPdgId << std::endl;
      if ( correctRECO ) numExoticsCorrectRECO_twoSensitiveDecay_[indexOfPdgId] += eventWeight_;
    }
    else {
      std::cout << "Warning in storeNumberOfExoticsRECO()" << std::endl;
      std::cout << "nSensitiveExoticDecayInEvent_ : " << nSensitiveExoticDecayInEvent_ << std::endl;
    }
  }
  else {
    std::cout << "Warning in storeNumberOfExoticsRECO()" << std::endl;
    std::cout << "indexOfPdgId : " << indexOfPdgId << std::endl;
  }
}

// Given a pdg id, will get the index of that pdg id in signalPdgId_
unsigned int DileptonAnalyzer::getIndexOfSignalPdg( int pdgId ) {
  return ( find( signalPdgId_.begin(), signalPdgId_.end(), pdgId ) ) - signalPdgId_.begin();
}

// Stop processing signal mc event if there isn't any interesting exotics in event
bool DileptonAnalyzer::interestingExoticInEvent() {
  for (unsigned int iExotic=0; iExotic<signalPdgId_.size(); iExotic++ ) {
    // Check if there is a correct species of LL
    if ( signalPdgId_[iExotic] == candidates->ll1_motherPdgId || signalPdgId_[iExotic] == candidates->ll2_motherPdgId ) {
      // Now check if at least one of them decays in the correct channel
      if ( anaType_==_2eTrack ) {
        if ( fabs( candidates->ll1_daughterPdgId ) == 11 || fabs( candidates->ll2_daughterPdgId ) == 11 ) return true;
      }
      else if ( anaType_==_2muTrack || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu ) {
        if ( fabs( candidates->ll1_daughterPdgId ) == 13 || fabs( candidates->ll2_daughterPdgId ) == 13 ) return true;
      }
    }
  }
  return false;
}

bool DileptonAnalyzer::correctlyReconstructed(TreeDipseudoLeptonCandidate & cand) {
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

  //    std::cout << "============= FAIL =============" << std::endl;
  //    std::cout << "Cand mass : " << cand.mass << std::endl;
  //    std::cout << "LeptonL : " << leptonL.genPdgId << " Lepton H : " << leptonH.genPdgId << std::endl;
  //    std::cout << "Lepton L x : " << leptonL.genVertexX << " Lepton H x : " << leptonH.genVertexX << std::endl;
  //    std::cout << "Origin L pdg id : " << leptonL.genSignalOriginPdgId << std::endl;
  //    std::cout << "Origin H pdg id : " << leptonH.genSignalOriginPdgId << std::endl;
  return false;
}

void DileptonAnalyzer::storeSignalEfficiencies( TFile & outputFile ) {
  // Store in a TProfile
  TProfile *sigEffOne = new TProfile("SignalEfficOneDecay","Signal efficiencies when one exotic decays in this channel",10,0.5,10.5,-9.9e9,9.9e9);
  TAxis *sigEffOneAxis = sigEffOne->GetXaxis();

  TProfile *sigEffTwo = new TProfile("SignalEfficTwoDecay","Signal efficiencies when two exotic decays in this channel",10,0.5,10.5,-9.9e9,9.9e9);
  TAxis *sigEffTwoAxis = sigEffTwo->GetXaxis();

  // Fill set of 3 bins in each TProfile for each exotic
  for ( int iExotic = 0; iExotic < nSignalParticles_; iExotic++ ) {

    TString axisTitle;

    sigEffOne->Fill( iExotic*nSignalParticles_+1, numEvents_oneSensitiveDecay_[iExotic] );
    axisTitle.Form("Number of events coming into macro for exotic %d",signalPdgId_[iExotic]);
    sigEffOneAxis->SetBinLabel( iExotic*nSignalParticles_+1, axisTitle.Data());

    sigEffOne->Fill( iExotic*nSignalParticles_+2, numExoticsRECO_oneSensitiveDecay_[iExotic] );
    axisTitle.Form("Number of candidates RECO'd for exotic %d",signalPdgId_[iExotic]);
    sigEffOneAxis->SetBinLabel( iExotic*nSignalParticles_+2, axisTitle.Data());

    sigEffOne->Fill( iExotic*nSignalParticles_+3, numExoticsCorrectRECO_oneSensitiveDecay_[iExotic] );
    axisTitle.Form("Number of exotics correctly RECO'd for exotic %d",signalPdgId_[iExotic]);
    sigEffOneAxis->SetBinLabel( iExotic*nSignalParticles_+3, axisTitle.Data());

    sigEffTwo->Fill( iExotic*nSignalParticles_+1, numEvents_twoSensitiveDecay_[iExotic] );
    axisTitle.Form("Number of events coming into macro for exotic %d",signalPdgId_[iExotic]);
    sigEffTwoAxis->SetBinLabel( iExotic*nSignalParticles_+1, axisTitle.Data());

    sigEffTwo->Fill( iExotic*nSignalParticles_+2, numExoticsRECO_twoSensitiveDecay_[iExotic] );
    axisTitle.Form("Number of candidates RECO'd for exotic %d",signalPdgId_[iExotic]);
    sigEffTwoAxis->SetBinLabel( iExotic*nSignalParticles_+2, axisTitle.Data());

    sigEffTwo->Fill( iExotic*nSignalParticles_+3, numExoticsCorrectRECO_twoSensitiveDecay_[iExotic] );
    axisTitle.Form("Number of exotics correctly RECO'd for exotic %d",signalPdgId_[iExotic]);
    sigEffTwoAxis->SetBinLabel( iExotic*nSignalParticles_+3, axisTitle.Data());
  }
  outputFile.cd();
  sigEffOne->Write();
  sigEffTwo->Write();
}

// Takes track of when (if) this candidate failed a cut
void DileptonAnalyzer::monitorCutFlow( DileptonAnalysisCuts::PassedWhichCuts whichCuts, double weight ) {

  // whichCuts has record of which cuts this candidate has passed
  // Increment each counter accordingly
  cutFlowMap_["AllCandidatesAtBeginningOfMacro"] += weight;

  if ( whichCuts.passCaloMatch) cutFlowMap_["CaloMatch"] += weight; else return;
  if ( whichCuts.passSCEt ) cutFlowMap_["LeptonSCEt"] += weight; else return;
  if ( whichCuts.passTrackPt ) cutFlowMap_["LeptonPt"] += weight; else return;
  if ( whichCuts.passEta ) cutFlowMap_["LeptonAbsEta"] += weight; else return;
  if ( whichCuts.passLeptonAbsD0 ) cutFlowMap_["LeptonAbsD0Sig"] += weight; else return;
  if ( whichCuts.passOppCharge ) cutFlowMap_["DileptonOppositeCharge"] += weight; else return;
  if ( whichCuts.passIso ) cutFlowMap_["DileptonIsolation"] += weight; else return;
  if ( whichCuts.passCosine ) cutFlowMap_["DileptonB2BVeto"] += weight; else return;
  if ( whichCuts.passDeltaR ) cutFlowMap_["DileptonDeltaR"] += weight; else return;
  if ( whichCuts.passTriggerMatch ) cutFlowMap_["DileptonTriggerMatch"] += weight; else return;
  if ( whichCuts.passVertexChi2 ) cutFlowMap_["DileptonChi2"] += weight; else return;
  if ( whichCuts.passDeltaPhi ) cutFlowMap_["DileptonDeltaPhi"] += weight; else return;
  if ( whichCuts.passHitsBeforeVertex ) cutFlowMap_["DileptonHitsBeforeVertex"] += weight; else return;
  if ( whichCuts.passMinLxySig ) cutFlowMap_["DileptonAbsLxySig"] += weight; else return;
  if ( whichCuts.passMass ) cutFlowMap_["DileptonMass"] += weight; else return;

  return;
}

// Report cut flow findings to screen
void DileptonAnalyzer::reportCutFlow( TFile & outputFile ) {

  // Store in a TProfile
  TProfile *cutFlow = new TProfile("cutFlow","Cut flow for final set of analysis cuts",20,0.5,20.5,-9.9e9,9.9e9);
  TAxis *cutFlowAxis = cutFlow->GetXaxis();

  for ( unsigned int iCut = 0; iCut < cutNamesInOrder_.size(); iCut++ ) {
    cutFlow->Fill( iCut+1, cutFlowMap_[cutNamesInOrder_[iCut]]);
    cutFlowAxis->SetBinLabel( iCut+1, cutNamesInOrder_[iCut]);
  }

  outputFile.cd();
  cutFlow->Write();
}


//
// END OF FUNCTION DEFINITIONS
//

//
// MAIN ANALYZER LOOP
//
void DileptonAnalyzer::Loop()
{
  // Check you have a file/chain
  if (fChain == 0) return;

  // Get number of entries in chain
  Long64_t nentries = fChain->GetEntries();

  double nEventCount=0;
  double nEventGot=0;

  // Loop over events
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    nEventCount++;
    // Checks recommended from TTree:MakeClass
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nEventGot++;
    fChain->GetEntry(jentry);

    getEventWeight();

    // Study gen level info if this is signal MC
    // In particular, get total number of exotics decaying to something this analysis is sensitive to?
    if ( isSignalMC_ ) {
      // Filter out events where there is no interesting exotics
      // This can happen when e.g. the generated event is H->XX and both X->jj
      if ( !interestingExoticInEvent() ) continue;
      nSensitiveExoticDecayInEvent_=getNumberOfExotics();

      // Check which triggers fired
      studyTriggers();

      if ( !signalTriggerFired() ) continue;
    }

    // Loop over candidates in event
    for( unsigned int iTreeCand=0; iTreeCand != candidates->candidates_.size(); ++iTreeCand ) {

      TreeDipseudoLeptonCandidate cand = candidates->candidates_.at(iTreeCand);

      // Check what type of leptons make up this candidate
      if ( !correctLeptonsInCandidate(cand) ) continue;

      // Get leptons
      TreeLepton leptonL = getLepton( cand.leptonIndexL );
      TreeLepton leptonH = getLepton( cand.leptonIndexH );

      // Choose appropiate mass to plot
      double mass = cand.mass;
      if (anaType_==_2eTrack) mass=cand.caloCorrMass;

      // Sign of Lxy/sigma
      int sign = 1;
      if( cand.dPhiCorr > TMath::PiOver2() ) sign = -1;

      // Apply analysis cuts.
      // And fill histograms_
      DileptonAnalysisCuts::PassedWhichCuts finalCuts = dileptonCuts_final_.whichCuts( cand, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );
      DileptonAnalysisCuts::PassedWhichCuts removedLifetimeCuts = dileptonCuts_removedLifetime_.whichCuts( cand, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );

      // Final Selection
      // n-1 plots

      // Lxy significance
      DileptonAnalysisCuts::PassedWhichCuts finalCutsTemp = finalCuts;
      finalCutsTemp.passMinLxySig = true;
      finalCutsTemp.passMaxLxySig = true;

      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_LxySig_finalCuts->Fill( sign*cand.decayLengthSignificance*lxyScale_, eventWeight_ );
      }

      // Also remove deltaPhi cut to see -ve Lxy/sigma distibution
      finalCutsTemp.passDeltaPhi = true;
      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_LxySig_removeDeltaPhi_finalCuts->Fill( sign*cand.decayLengthSignificance*lxyScale_, eventWeight_ );
      }

      // Chi^2
      finalCutsTemp = finalCuts;
      finalCutsTemp.passVertexChi2 = true;

      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_vertexChi2_finalCuts->Fill( cand.vertexChi2, eventWeight_);
      }

      // dPhi
      finalCutsTemp = finalCuts;
      finalCutsTemp.passDeltaPhi = true;

      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_deltaPhi_finalCuts->Fill( cand.dPhiCorr, eventWeight_);
      }

      // smallest d0/sigma of the two leptons
      finalCutsTemp = finalCuts;
      finalCutsTemp.passLeptonAbsD0 = true;

      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_leptonAbsD0Sig_finalCuts->Fill( std::min(leptonL.d0Significance,leptonH.d0Significance), eventWeight_ );
      }

      // Calo match delta R (largest of two leptons)
      finalCutsTemp = finalCuts;
      finalCutsTemp.passCaloMatch = true; // Shouldn't do anything at the moment.  Cut at deltaR < 0.2, which is very loose and applied in Tree Producer anyway.
      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_leptonCaloMatchDeltaR_finalCuts->Fill( std::max(leptonL.cmDeltaR,leptonH.cmDeltaR), eventWeight_ );
        histograms_.h_nMinus1_leptonCaloMatchDeltaEta_finalCuts->Fill( std::max(leptonL.cmDeltaEta,leptonH.cmDeltaEta), eventWeight_ );
        histograms_.h_nMinus1_leptonCaloMatchDeltaPhi_finalCuts->Fill( std::max(leptonL.cmDeltaPhi,leptonH.cmDeltaPhi), eventWeight_ );
      }

      // Track pt cut
      finalCutsTemp = finalCuts;
      finalCutsTemp.passTrackPt = true;
      if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
        histograms_.h_nMinus1_leptonTrackPt_finalCuts->Fill(std::min(leptonL.pt,leptonH.pt),eventWeight_);
      }

      // Isolation
      // Gen matched signal only
      if ( isSignalMC_ && correctlyReconstructed( cand ) ) {
        finalCutsTemp = finalCuts;
        finalCutsTemp.passIso = true;

        if ( dileptonCuts_final_.passAllCuts( finalCutsTemp ) ) {
          histograms_.h_nMinus1_isolationLeptonL_finalCuts_genMatched->Fill( cand.leptonIsoL, eventWeight_ );
          histograms_.h_nMinus1_isolationLeptonH_finalCuts_genMatched->Fill( cand.leptonIsoH, eventWeight_ );
          histograms_.h_nMinus1_relIsolationLeptonL_finalCuts_genMatched->Fill( cand.leptonIsoL/cand.leptonPtL, eventWeight_ );
          histograms_.h_nMinus1_relIsolationLeptonH_finalCuts_genMatched->Fill( cand.leptonIsoH/cand.leptonPtH, eventWeight_ );

          histograms_.h_nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched->Fill( cand.leptonIsoL, candidates->numPV, eventWeight_ );
          histograms_.h_nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched->Fill( cand.leptonIsoH, candidates->numPV, eventWeight_ );
          histograms_.h_nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched->Fill( cand.leptonIsoL/cand.leptonPtL, candidates->numPV, eventWeight_ );
          histograms_.h_nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched->Fill( cand.leptonIsoH/cand.leptonPtH, candidates->numPV, eventWeight_ );
        }
      }

      // Final selection
      // All cuts

      // Monitor cut flow for final selection cuts
      monitorCutFlow( finalCuts, eventWeight_ );

      if ( dileptonCuts_final_.passAllCuts( finalCuts ) ) {
        //
        // These candidates have passed all final selection criteria
        //
        histograms_.h_mass_finalCuts->Fill( mass, eventWeight_ );
//        histograms_.h_mt_finalCuts->Fill( cand.transverseMass, eventWeight_ );
        histograms_.h_Lxy_finalCuts->Fill( cand.decayLength, eventWeight_ );
        histograms_.h_nRecoPV_finalCuts->Fill(candidates->numPV, eventWeight_ );

        // Study efficiencies etc.

        // Study gen level info
        // Count number of correctly reconstructed candidates
        if ( isSignalMC_ ) storeNumberOfExoticsRECO( cand );

      }

      // Removed lifetime cuts
      // All cuts
      if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCuts ) ) {
        histograms_.h_mass_removedLifetimeCuts->Fill( mass, eventWeight_ );
        histograms_.h_nRecoPV_removedLifetimeCuts->Fill( candidates->numPV, eventWeight_ );

        // Calculate different event weight with different pu weight
        double puP5weight = puweights_p5_.weight( candidates->nvtx_true );
        double puM5weight = puweights_m5_.weight( candidates->nvtx_true );
        histograms_.h_nRecoPV_p5_removedLifetimeCuts->Fill(candidates->numPV, puP5weight * weight_ );
        histograms_.h_nRecoPV_m5_removedLifetimeCuts->Fill(candidates->numPV, puM5weight * weight_ );

        histograms_.h_leptonLPt_removedLifetimeCuts->Fill( leptonL.pt, eventWeight_ );
        histograms_.h_leptonHPt_removedLifetimeCuts->Fill( leptonH.pt, eventWeight_ );
        histograms_.h_leptonLEta_removedLifetimeCuts->Fill( leptonL.eta, eventWeight_ );
        histograms_.h_leptonHEta_removedLifetimeCuts->Fill( leptonH.eta, eventWeight_ );
        histograms_.h_leptonLCaloMatchDeltaR_removedLifetimeCuts->Fill( leptonL.cmDeltaR, eventWeight_ );
        histograms_.h_leptonHCaloMatchDeltaR_removedLifetimeCuts->Fill( leptonH.cmDeltaR, eventWeight_ );
        histograms_.h_LxySig_removedLifetimeCuts->Fill( sign*cand.decayLengthSignificance*lxyScale_, eventWeight_ );
        histograms_.h_leptonAbsD0Sig_removedLifetimeCuts->Fill( std::min(leptonL.d0Significance,leptonH.d0Significance)*d0Scale_, eventWeight_ );
      }

      // n-1 (for isolation)
      DileptonAnalysisCuts::PassedWhichCuts removedLifetimeCutsTemp = removedLifetimeCuts;
      removedLifetimeCutsTemp.passIso = true;

      if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
        histograms_.h_nMinus1_isolationLeptonL_removedLifetimeCuts->Fill( cand.leptonIsoL, eventWeight_ );
        histograms_.h_nMinus1_isolationLeptonH_removedLifetimeCuts->Fill( cand.leptonIsoH, eventWeight_ );
        histograms_.h_nMinus1_relIsolationLeptonL_removedLifetimeCuts->Fill( cand.leptonIsoL/cand.leptonPtL, eventWeight_ );
        histograms_.h_nMinus1_relIsolationLeptonH_removedLifetimeCuts->Fill( cand.leptonIsoH/cand.leptonPtH, eventWeight_ );
      }

    } // cand loop
  } // event loop

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

  TFile outputFile(outputFileName, "RECREATE");
  outputFile.cd();


  histograms_.writeHistograms(outputFile);

  // Report cut flow
  reportCutFlow(outputFile);

  if ( isSignalMC_ ) {

    // Store signal efficiencies
    storeSignalEfficiencies(outputFile);

    // Report trigger info
    for ( unsigned int iTrig=0; iTrig < signalTriggers_.size(); iTrig++ ) {
      std::cout << "Trigger : " << signalTriggers_[iTrig].c_str() << " Number times fired : " << triggerFired_[iTrig] << std::endl;
    }
  }

  std::cout << "Writing and closing files" << std::endl;
  // Close file
  outputFile.Write();
  outputFile.Close();

  std::cout << "Deleting histograms" << std::endl;
  // Delete histograms
  histograms_.deleteHistograms();

}
