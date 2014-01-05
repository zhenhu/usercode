#define DileptonAnalyzer_cxx
#include "DileptonAnalyzer.h"


//
// FUNCTION DEFINITIONS
//

// Get total weight for this event, including PU weight
void DileptonAnalyzer::getEventWeight() {
  double totalWeight = 0;
  if ( dirName_.Contains("Data") ) totalWeight = xsecWeight_;
  else {
    double puweight = puweights_.weight( candidates->nvtx_true );
    //    cout << "Xsec weight : " << xsecWeight_ << endl;
    if ( isSignalMC_ ) {
      totalWeight = puweight * xsecWeight_ * totalProcessedEvents_;
    }
    else totalWeight = puweight * xsecWeight_;
    //    cout << "Total weight : " << totalWeight << endl;
  }


  eventWeight_=totalWeight;
}

// Get lifetime weight to reweight signal MC
// Only for debugging - not used to produce any final results
double DileptonAnalyzer::getLifetimeWeight( const double & llCtau) {
  double oldCtau = 60;
  return 1./reweightFactor_ * exp( llCtau * ( reweightFactor_ - 1.) / (reweightFactor_ * oldCtau));
}

void DileptonAnalyzer::studyNeutralinoPtSpectrum() {
  hists_.h_chiPt_all->Fill( candidates->res1_Pt );
  hists_.h_chiPt_all->Fill( candidates->res2_Pt );

  if ( ( candidates->res1_PdgId < 0 && candidates->res2_PdgId < 0 ) ||
      ( candidates->res1_PdgId > 0 && candidates->res2_PdgId > 0 ) ) {
    hists_.h_chiPt_ss->Fill( candidates->res1_Pt );
    hists_.h_chiPt_ss->Fill( candidates->res2_Pt );
  }
  else {

    hists_.h_chiPt_sas->Fill( candidates->res1_Pt );
    hists_.h_chiPt_sas->Fill( candidates->res2_Pt );
  }
  return;
}

double DileptonAnalyzer::getNeutralinoWeight() {
  if ( ( candidates->res1_PdgId < 0 && candidates->res2_PdgId < 0 ) ||
      ( candidates->res1_PdgId > 0 && candidates->res2_PdgId > 0 ) ) {
    return ssWeight_;
  }
  else {
    return sasWeight_;
  }
}


// Study triggers for signal MC
void DileptonAnalyzer::studyTriggers() {

  // For plots, only interested when only one exotic decays in correct channel
  bool plotEvent=true;
  if ( candidates->ll1_daughterPdgId ==  candidates->ll2_daughterPdgId ) plotEvent=false;

  // Work out which exotic to plot
  bool exoticToPlot=1;
  if ( anaType_==_2eTrack && candidates->ll1_daughterPdgId != 11 ) {
    exoticToPlot=2;
    // Check for now
    if ( candidates->ll2_daughterPdgId != 11 ) cout << "WARNING in studyTriggers" << endl;
  }
  else if ( (anaType_==_2muTrack ||  anaType_==_2globalOrTrackerMu || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu) && candidates->ll1_daughterPdgId != 13  ) {
    exoticToPlot=2;
    // Check for now
    if ( candidates->ll2_daughterPdgId != 13 ) cout << "WARNING in studyTriggers" << endl;
  }

  // Loop over signal trigger to see if one has fired
  for ( unsigned int iTrig = 0; iTrig < signalTriggers_.size(); iTrig++ ) {
    string trigger = signalTriggers_[iTrig];

    bool trigFired = ( find( triggers->begin(), triggers->end(), trigger ) != triggers->end() ? 1 : 0 );

    double target_ctau = (exoticToPlot==1) ? candidates->ll1_ctau : candidates->ll2_ctau;

    if ( trigger == "AnyTrigger" ) {
      if ( plotEvent ) {
        hists_.h_trig_Lxy_all->Fill( (exoticToPlot==1) ? candidates->ll1_decayLength2D : candidates->ll2_decayLength2D );
        hists_.h_trig_ctau_all->Fill( target_ctau );
      }
      trigFired=true;
    }

    if ( trigFired ) {
      triggerFired_[iTrig]++;

      if ( iTrig==triggerToPlot_ ) {
        if ( plotEvent ) {
          hists_.h_trig_Lxy_pass->Fill( (exoticToPlot==1) ? candidates->ll1_decayLength2D : candidates->ll2_decayLength2D );
          hists_.h_trig_ctau_pass->Fill( target_ctau );
        }
      }
    }

    //    // Fill trigger efficiency as function of ctau
    //    for (int i=1; i<=hists_.h_trigEff_meanLifetime[iTrig]->GetXaxis()->GetNbins(); i++) {
    //      float binLifetime = hists_.h_trigEff_meanLifetime[iTrig]->GetXaxis()->GetBinCenter(i);
    //      float weight = (thisNominalLifetime/binLifetime)*exp(-(target_ctau/binLifetime - target_ctau/thisNominalLifetime));
    //      hists_.h_trigEff_meanLifetime[iTrig]->Fill(binLifetime, (trigFired == true), weight);
    //    }
    //    for (unsigned int i=0; i<=nReweightFactors_; i++) {
    //      float binLifetime = lifetimeReweightingFactors_[i]*thisNominalLifetime;
    //      float weight = (thisNominalLifetime/binLifetime)*exp(-(target_ctau/binLifetime - target_ctau/thisNominalLifetime));
    //      hists_.h_trigEff_meanLifetimeLog[iTrig]->Fill(binLifetime, (trigFired == true), weight);
    //    }

  }
}

// Study tracking efficiency
void DileptonAnalyzer::studyTrackingEfficiency() {

  unsigned int interestingLepton=getInterestingLepton();

  vector<double> genLeptonPt;
  vector<double> genLeptonEta;
  vector<double> genLeptonD0;
  vector<double> genLeptonLxy;


  // Fill denominator histograms
  // Only select tracks with gen values within acceptance
  if ( fabs(candidates->ll1_daughterPdgId) == interestingLepton ) {
    if ( candidates->ll1_daughter1_Pt >= 21 && fabs(candidates->ll1_daughter1_Eta) < 2 ) {
      hists_.h_all_d0->Fill( candidates->ll1_daughter1_D0);
      hists_.h_all_lxy->Fill( candidates->ll1_decayLength2D);
      genLeptonPt.push_back( candidates->ll1_daughter1_Pt );
      genLeptonEta.push_back( candidates->ll1_daughter1_Eta );
      genLeptonD0.push_back( candidates->ll1_daughter1_D0 );
      genLeptonLxy.push_back( candidates->ll1_decayLength2D );
    }

    if ( candidates->ll1_daughter2_Pt >= 21 && fabs(candidates->ll1_daughter2_Eta) < 2 ) {
      hists_.h_all_d0->Fill( candidates->ll1_daughter2_D0);
      hists_.h_all_lxy->Fill( candidates->ll1_decayLength2D);
      genLeptonD0.push_back( candidates->ll1_daughter2_D0 );
      genLeptonEta.push_back( candidates->ll1_daughter2_Eta );
      genLeptonPt.push_back( candidates->ll1_daughter2_Pt );
      genLeptonLxy.push_back( candidates->ll1_decayLength2D );
    }

  }

  if ( fabs(candidates->ll2_daughterPdgId) == interestingLepton ) {
    if ( candidates->ll2_daughter1_Pt >= 21 && fabs(candidates->ll2_daughter1_Eta) < 2 ) {
      hists_.h_all_d0->Fill( candidates->ll2_daughter1_D0);
      hists_.h_all_lxy->Fill( candidates->ll2_decayLength2D);
      genLeptonPt.push_back( candidates->ll2_daughter1_Pt );
      genLeptonEta.push_back( candidates->ll2_daughter1_Eta );
      genLeptonD0.push_back( candidates->ll2_daughter1_D0 );
      genLeptonLxy.push_back( candidates->ll2_decayLength2D );
    }

    if ( candidates->ll2_daughter2_Pt >= 21 && fabs(candidates->ll2_daughter2_Eta) < 2 ) {
      hists_.h_all_d0->Fill( candidates->ll2_daughter2_D0);
      hists_.h_all_lxy->Fill( candidates->ll2_decayLength2D);
      genLeptonD0.push_back( candidates->ll2_daughter2_D0 );
      genLeptonEta.push_back( candidates->ll2_daughter2_Eta );
      genLeptonPt.push_back( candidates->ll2_daughter2_Pt );
      genLeptonLxy.push_back( candidates->ll2_decayLength2D );
    }

  }

  // Don't bother going further if no exotics survived gen level cuts
  if ( genLeptonPt.size() == 0 ) return;

  // Loop over leptons in event
  for ( unsigned int iTreeLepton=0; iTreeLepton != candidates->leptons_.size(); ++iTreeLepton ) {

    TreeLepton lepton = candidates->leptons_.at(iTreeLepton);

    // Check this is correct lepton for this type of analysis
    if ( !correctLepton( lepton ) ) continue;

    // Check if correctly gen matched
    // Correct flavour?
    if ( fabs(lepton.genPdgId) == interestingLepton ) {
      bool plotLepton=false;
      // Exotic mother?
      for ( unsigned int iPdg = 0; iPdg < signalPdgId_.size(); iPdg++ ) {
        if ( lepton.genSignalOriginPdgId == signalPdgId_[iPdg] ) {

          plotLepton = true;
          break;
        }
      }

      // Also check lepton has sufficienct pt and is within eta<2
      // i.e. same cuts as above
      if ( lepton.genPt < 21 || fabs(lepton.genEta) > 2 ) plotLepton = false;

      // Also require reco track to have a trigger match
      if ( lepton.triggerMatch == 0 ) plotLepton = true;

      // This lepton is matched to a gen particle which came from an exotic -> plot lepton
      if ( plotLepton ) {

        int exo=-1;
        for ( unsigned int iExo = 0; iExo < genLeptonPt.size(); iExo++ ) {
          if ( lepton.genPt == genLeptonPt[iExo] ) {
            exo=iExo;
            if ( genLeptonPt[iExo]>=21 && fabs( genLeptonEta[iExo] ) < 2 ) {

              hists_.h_reco_d0->Fill( genLeptonD0[exo]);
              hists_.h_reco_lxy->Fill( genLeptonLxy[exo]);
            }
            break;
          }
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
bool DileptonAnalyzer::correctLeptonsInCandidate( TreeDipseudoLeptonCandidate & cand, TreeLepton& leptonL, TreeLepton& leptonH  )
{
  if ( correctLepton( leptonL ) && correctLepton( leptonH ) ) {
    return true;
  }

  return false;
}

// Checks that event has passed prefilter requirement
// Currently applied to signal MC
// Will apply to all samples so we start with same criteria for cut flow
bool DileptonAnalyzer::passPrefilter() {
  double leadingPt=0;
  double subleadingPt=0;

  //  double leadingEt=0;
  //  double subleadingEt=0;

  // Loop over leptons in event
  // Get two highest pt tracks and Et superclusters
  for ( unsigned int iTreeLepton=0; iTreeLepton != candidates->leptons_.size(); ++iTreeLepton ) {

    TreeLepton lepton = candidates->leptons_.at(iTreeLepton);

    // Check this is correct lepton for this type of analysis
    if ( !correctLepton( lepton ) ) continue;

    // Ignore leptons where Et/pt has already been used
    if ( //lepton.photonEt == leadingEt || lepton.photonEt == subleadingEt
        lepton.pt == leadingPt || lepton.pt == subleadingPt ) continue;

    // Finding leading and subleading pt
    if ( lepton.pt > leadingPt ) {
      subleadingPt=leadingPt;
      leadingPt=lepton.pt;
    }
    else if ( lepton.pt > subleadingPt ) {
      subleadingPt=lepton.pt;
    }

    //    // Finding leading and subleading Et
    //    if ( lepton.photonEt > leadingEt ) {
    //      subleadingEt=leadingEt;
    //      leadingEt=lepton.photonEt;
    //    }
    //    else if ( lepton.photonEt > subleadingEt ) {
    //      subleadingEt=lepton.photonEt;
    //    }
  }

  // Do we have two pseudo leptons that pass pt cut
  if ( ( leadingPt > prefilterPtCut_[0] && subleadingPt > prefilterPtCut_[1] ) ) {
    purityCounter_offlineMatch_++;
    purityCounter_eta_++;
    return true;
  }
  else return false;

  // FIXME or note : The current pseudo lepton filter applied at pat tuple creation for background MC and data
  // requires either two tracks with pt>23 or two super clusters with Et > 36 and 22
  // This is not quite the same criteria here, as two pseudo leptons are required with track pt > 23 or two pseudo leptons matched to a supercluster (within delta R of 0.2) have Et above thresholds
  // The delta R matching is very loose and there is a track pt cut of 25 applied to the tracks in the muon channel during the tree producer step.
  // If things look odd (in the cutflow?) maybe apply this prefilter to all samples as a first check?
}

// Check, given the type of analysis, that this is the correct type of lepton
bool DileptonAnalyzer::correctLepton( TreeLepton & lepton )
{
  // Require global muon
  if ( anaType_==_2globalOrTrackerMu) {
    if ( lepton.isGlobalMuon || lepton.isTrackerMuon ) return true;
  }
  else if ( anaType_==_2globalMu ) {
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
  else cout << "WARNING : Unidentified lepton" << endl;

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
  cout << "WARNING : Could not find this lepton in TreeLepton Candidate" << endl;
  return TreeLepton();
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
    //    cout << "This electron doesn't have a match to a gen electron" << endl;
    return false;
  }
  else if ( ( anaType_==_2muTrack ||  anaType_==_2globalOrTrackerMu || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu ) && abs(pdgId) != 13 ) {
    //    cout << "This muon doesn't have a match to a gen muon" << endl;
    return false;
  }

  // Now check parent of lepton
  // FIXME Not very good check...
  if ( lepton.genSignalOriginPdgId > 6000000 ) return true;

  return false;
}

double DileptonAnalyzer::smearMass( double mass, bool barrel1, bool barrel2 ) {
  if ( barrel1 && barrel2 ) {
    return mass * ( 1 + rnd.Gaus(0,EBEBScale_) );
  }
  else if ( !barrel1 && !barrel2 ) {
    return mass * ( 1 + rnd.Gaus(0,EEEEScale_) );
  }
  else {
    return mass * ( 1 + rnd.Gaus(0,EBEEScale_) );
  }

  cout << "WARNING : In smearMass" << endl;
  return 0.1;
}


// Sum number of exotzics this analysis is sensitive to
unsigned int DileptonAnalyzer::storeNumberOfExoticsALL() {

  // Get index of long lived pdg id
  // This is to check there is an interesting exotic in the event
  int pdgId = candidates->ll1_motherPdgId;
  unsigned int indexOfPdgId = getIndexOfSignalPdg( pdgId );
  // Could have mixed events (exotic1->jets, exotic2->leptons) so check other exotic if first one wasn't found to be of interest
  if ( indexOfPdgId == signalPdgId_.size() ) {
    pdgId = candidates->ll2_motherPdgId;
    indexOfPdgId = getIndexOfSignalPdg( candidates->ll2_motherPdgId );
  }

  // Did signal trigger fire in this event?
  bool sigTrig=false;
  if (signalTriggerFired()) sigTrig=true;

  // Check if this particle decay is interesting
  if ( indexOfPdgId < signalPdgId_.size() ) {
    // Count number of exotics decaying into sensitive channel
    int decayParticlePdgId=13;
    if ( anaType_==_2eTrack ) decayParticlePdgId=11;

    // Calculate different event weight with different pu weight
    double puP5weight = puweights_p5_.weight( candidates->nvtx_true );
    double puM5weight = puweights_m5_.weight( candidates->nvtx_true );

    if ( fabs(candidates->ll1_daughterPdgId) == decayParticlePdgId &&  fabs(candidates->ll2_daughterPdgId) == decayParticlePdgId ) {

      // Extra check as neutralino samples can contain neutralino->mu e nu.  ll1_daughterPdgId does not store this info...
      // Just (double) check that at least one neutralino decays to same flavour leptons
      // Add these mixed decays (3 mu + 1 e or 3 e + 1 mu) to epsilon 1
      if ( ( fabs(candidates->ll1_daughter1_PdgId) == decayParticlePdgId && fabs(candidates->ll1_daughter2_PdgId) == decayParticlePdgId ) &&
          ( fabs(candidates->ll2_daughter1_PdgId) == decayParticlePdgId && fabs(candidates->ll2_daughter2_PdgId) == decayParticlePdgId ) ) {
        // Two exotics decayed to this channel
        numEvents_twoSensitiveDecay_[indexOfPdgId] += eventWeight_;
        // Store info of both exotics in event
        allExotics_twoSensitiveDecay_ << sigTrig << " " << eventWeight_ << " " << puM5weight*xsecWeight_*totalProcessedEvents_ << " " << puP5weight*xsecWeight_*totalProcessedEvents_ << " " << ll1WithinAcceptance() << " " << candidates->ll1_ctau << " " << candidates->ll1_E/candidates->ll1_pt << " " << candidates->ll1_motherPdgId << " " << candidates->ll1_daughterPdgId << " " << ll2WithinAcceptance() << " " << candidates->ll2_ctau << " " << candidates->ll2_E/candidates->ll2_pt << " " << candidates->ll2_motherPdgId << " " << candidates->ll2_daughterPdgId << " " << candidates->run << " " << candidates->lumi << " " << candidates->event << endl;
        return 2;
      }
      else {
        // One exotic decayed in this channel
        numEvents_oneSensitiveDecay_[indexOfPdgId] += eventWeight_;
        // Store info of both exotics in event - need both for ctau reweighting
        allExotics_oneSensitiveDecay_ << sigTrig << " " << eventWeight_ << " " << puM5weight*xsecWeight_*totalProcessedEvents_ << " " << puP5weight*xsecWeight_*totalProcessedEvents_ << " " << ll1WithinAcceptance() << " " << candidates->ll1_ctau << " " << candidates->ll1_E/candidates->ll1_pt << " " << candidates->ll1_motherPdgId << " " << candidates->ll1_daughterPdgId << " " << ll2WithinAcceptance() << " " << candidates->ll2_ctau << " " << candidates->ll2_E/candidates->ll2_pt << " " << candidates->ll2_motherPdgId << " " << candidates->ll2_daughterPdgId << " " << candidates->run << " " << candidates->lumi << " " << candidates->event << endl;
        return 1;
      }
    }
    else if ( ( fabs(candidates->ll1_daughterPdgId) == decayParticlePdgId && fabs(candidates->ll1_daughter1_PdgId) == decayParticlePdgId && fabs(candidates->ll1_daughter2_PdgId) == decayParticlePdgId )||
         ( fabs(candidates->ll2_daughterPdgId) == decayParticlePdgId && fabs(candidates->ll2_daughter1_PdgId) == decayParticlePdgId && fabs(candidates->ll2_daughter2_PdgId) == decayParticlePdgId ) ) {
      // One exotic decayed in this channel
      numEvents_oneSensitiveDecay_[indexOfPdgId] += eventWeight_;
      // Store info of both exotics in event - need both for ctau reweighting
      allExotics_oneSensitiveDecay_ << sigTrig << " " << eventWeight_ << " " << puM5weight*xsecWeight_*totalProcessedEvents_ << " " << puP5weight*xsecWeight_*totalProcessedEvents_ << " " << ll1WithinAcceptance() << " " << candidates->ll1_ctau << " " << candidates->ll1_E/candidates->ll1_pt << " " << candidates->ll1_motherPdgId << " " << candidates->ll1_daughterPdgId << " " << ll2WithinAcceptance() << " " << candidates->ll2_ctau << " " << candidates->ll2_E/candidates->ll2_pt << " " << candidates->ll2_motherPdgId << " " << candidates->ll2_daughterPdgId << " " << candidates->run << " " << candidates->lumi << " " << candidates->event << endl;
      return 1;
    }
  }
  else {
    cout << "Warning in storeNumberOfExoticsALL()" << endl;
    cout << "indexOfPdgId : " << indexOfPdgId << endl;
    cout << "Pdg id of mother 1 : " << candidates->ll1_motherPdgId << endl;
    cout << "Pdg id of mother 2 : " << candidates->ll2_motherPdgId << endl;
  }

  return 0;
}




void DileptonAnalyzer::storeNumberOfExoticsRECO( TreeDipseudoLeptonCandidate & cand, TreeLepton &leptonL, TreeLepton &leptonH, ofstream & oneExoFile, ofstream & twoExoFile ) {

  bool correctRECO=correctlyReconstructed( cand, leptonL, leptonH );
  bool candWithinAcceptance=false;
  if ( correctRECO ) candWithinAcceptance = withinAcceptnace( cand );

  // Get long lived pdg id in event
  int pdgId = candidates->ll1_motherPdgId;
  unsigned int indexOfPdgId = getIndexOfSignalPdg( pdgId );
  // Could have crossed events, so check other exotic if the first one wasn't found
  if ( indexOfPdgId == signalPdgId_.size() ) {
    pdgId = candidates->ll2_motherPdgId;
    indexOfPdgId = getIndexOfSignalPdg( pdgId );
  }

  // Did signal trigger fire in this event?
  bool sigTrig=false;
  if (signalTriggerFired()) sigTrig=true;

  if ( indexOfPdgId < signalPdgId_.size() ) {

    // Calculate different event weight with different pu weight
    double puP5weight = puweights_p5_.weight( candidates->nvtx_true );
    double puM5weight = puweights_m5_.weight( candidates->nvtx_true );

    if ( nSensitiveExoticDecayInEvent_ == 1 ) {
      numExoticsRECO_oneSensitiveDecay_[indexOfPdgId] += eventWeight_;
      oneExoFile << sigTrig << " " << eventWeight_ << " " << puM5weight*xsecWeight_*totalProcessedEvents_ << " " << puP5weight*xsecWeight_*totalProcessedEvents_ << " " << ll1WithinAcceptance() << " " << candidates->ll1_ctau << " " << candidates->ll1_E/candidates->ll1_pt << " " << candidates->ll1_motherPdgId << " " << candidates->ll1_daughterPdgId << " " << ll2WithinAcceptance() << " " << candidates->ll2_ctau << " " << candidates->ll2_E/candidates->ll2_pt << " " << candidates->ll2_motherPdgId << " " << candidates->ll2_daughterPdgId << " " << candidates->run << " " << candidates->lumi << " " << candidates->event << endl;
      if ( correctRECO ) {
        numExoticsCorrectRECO_oneSensitiveDecay_[indexOfPdgId] += eventWeight_;
        if ( !candWithinAcceptance ) numExotics_oA_oneSensitiveDecay_[indexOfPdgId] += 1;
      }
    }
    else if ( nSensitiveExoticDecayInEvent_ == 2 ) {
      numExoticsRECO_twoSensitiveDecay_[indexOfPdgId] += eventWeight_;
      twoExoFile << sigTrig << " " << eventWeight_ << " " << puM5weight*xsecWeight_*totalProcessedEvents_ << " " << puP5weight*xsecWeight_*totalProcessedEvents_ << " " << ll1WithinAcceptance() << " " << candidates->ll1_ctau << " " << candidates->ll1_E/candidates->ll1_pt << " " << candidates->ll1_motherPdgId << " " << candidates->ll1_daughterPdgId << " " << ll2WithinAcceptance() << " " << candidates->ll2_ctau << " " << candidates->ll2_E/candidates->ll2_pt << " " << candidates->ll2_motherPdgId << " " << candidates->ll2_daughterPdgId << " " << candidates->run << " " << candidates->lumi << " " << candidates->event << endl;
      if ( correctRECO ) {
        numExoticsCorrectRECO_twoSensitiveDecay_[indexOfPdgId] += eventWeight_;
        if ( !candWithinAcceptance ) numExotics_oA_twoSensitiveDecay_[indexOfPdgId] += 1;
      }
    }
    else {
      cout << "Warning in storeNumberOfExoticsRECO()" << endl;
      cout << "nSensitiveExoticDecayInEvent_ : " << nSensitiveExoticDecayInEvent_ << endl;
    }
  }
  else {
    cout << "Warning in storeNumberOfExoticsRECO()" << endl;
    cout << "indexOfPdgId : " << indexOfPdgId << endl;
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
    // Note: This will only select events where both exotics are the same i.e. will reject crossed events
    if ( signalPdgId_[iExotic] == candidates->ll1_motherPdgId && signalPdgId_[iExotic] == candidates->ll2_motherPdgId ) {

      // Now check that at least one of them decays via an interesting channel
      if ( anaType_==_2eTrack ) {
        if ( fabs( candidates->ll1_daughterPdgId ) == 11 || fabs( candidates->ll2_daughterPdgId ) == 11 ) {
          // Neutralino samples can contain mixed decays neutralino -> mu e nu
          // Just want to make sure at least one neutralino decayed to 2 leptons of same flavour
          if ( ( fabs( candidates->ll1_daughter1_PdgId ) == 11 && fabs( candidates->ll1_daughter2_PdgId ) == 11 ) ||
              ( fabs( candidates->ll2_daughter1_PdgId ) == 11 && fabs( candidates->ll2_daughter2_PdgId ) == 11 ) ) {
            return true;
          }
        }
      }
      else if ( anaType_==_2muTrack ||  anaType_==_2globalOrTrackerMu || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu ) {
        if ( fabs( candidates->ll1_daughterPdgId ) == 13 || fabs( candidates->ll2_daughterPdgId ) == 13 ) {
          if ( ( fabs( candidates->ll1_daughter1_PdgId ) == 13 && fabs( candidates->ll1_daughter2_PdgId ) == 13 ) ||
              ( fabs( candidates->ll2_daughter1_PdgId ) == 13 && fabs( candidates->ll2_daughter2_PdgId ) == 13 ) ) {
            return true;
          }
        }
      }
    }
  }

  // Not an interesting signal MC event
  return false;
}

bool DileptonAnalyzer::correctlyReconstructed(TreeDipseudoLeptonCandidate & cand, TreeLepton& leptonL, TreeLepton& leptonH, bool debug) {

  // Check if leptons have correct flavour (or are even leptons)
  bool correctLeptons=false;
  if ( anaType_==_2eTrack ) {
    if ( debug ) {
      cout << "In electron analysis" << endl;
      cout << "Is track + TO : " << leptonH.isCentralTrack << endl;
      cout << "Is global muon : " << leptonH.isGlobalMuon << endl;
      cout << "Lepton L gen pdg : " << leptonL.genPdgId << endl;
      cout << "Lepton H gen pdg : " << leptonH.genPdgId << endl;
    }
    if ( fabs( leptonL.genPdgId ) == 11 && fabs( leptonH.genPdgId ) == 11 ) correctLeptons=true;
  }
  else {
    if ( debug ) {
      cout << "In muon analysis" << endl;
      cout << "Is track + TO : " << leptonH.isCentralTrack << endl;
      cout << "Is global muon : " << leptonH.isGlobalMuon << endl;
      cout << "Lepton L gen pdg : " << leptonL.genPdgId << endl;
      cout << "Lepton H gen pdg : " << leptonH.genPdgId << endl;
    }
    if ( fabs( leptonL.genPdgId ) == 13 && fabs( leptonH.genPdgId ) == 13 ) correctLeptons=true;
  }

  if ( debug ) cout << "Correct leptons : " << correctLeptons << endl;

  if ( !correctLeptons ) return false;

  // Check leptons aren't matched to same gen particle
  if ( leptonL.genIndex == leptonH.genIndex ) return false;

  // Check if leptons have the same production vertex
  if ( leptonL.genVertexX == leptonH.genVertexX && leptonL.genVertexY == leptonH.genVertexY && leptonL.genVertexZ == leptonH.genVertexZ ) {

    // Check if they have the same parent pdg id
    if ( leptonL.genSignalOriginPdgId == leptonH.genSignalOriginPdgId ) return true;
  }
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

bool DileptonAnalyzer::ll1WithinAcceptance() {
  if (
      ( ( candidates->ll1_daughter1_Pt > acceptancePt1Cut_ && candidates->ll1_daughter2_Pt > acceptancePt2Cut_ ) || ( candidates->ll1_daughter1_Pt > acceptancePt2Cut_ && candidates->ll1_daughter2_Pt > acceptancePt1Cut_ ) )
      && fabs(candidates->ll1_daughter1_Eta) < acceptanceEtaCut_ && fabs(candidates->ll1_daughter2_Eta) < acceptanceEtaCut_
      && fabs(candidates->ll1_decayLength2D) < acceptanceLxyCut_ ) return 1;
  else return 0;
}

bool DileptonAnalyzer::ll2WithinAcceptance() {
  if (
      ( ( candidates->ll2_daughter1_Pt > acceptancePt1Cut_ && candidates->ll2_daughter2_Pt > acceptancePt2Cut_ ) || ( candidates->ll2_daughter1_Pt > acceptancePt2Cut_ && candidates->ll2_daughter2_Pt > acceptancePt1Cut_ ) )
      && fabs(candidates->ll2_daughter1_Eta) < acceptanceEtaCut_ && fabs(candidates->ll2_daughter2_Eta) < acceptanceEtaCut_
      && fabs(candidates->ll2_decayLength2D) < acceptanceLxyCut_ ) return 1;
  else return 0;
}


bool DileptonAnalyzer::eventWithinAcceptance( const unsigned int nInterestingExotics ) {

  unsigned int interestingLepton=getInterestingLepton();

  if ( nInterestingExotics == 1 ) {
    if ( ( interestingLepton == fabs(candidates->ll1_daughterPdgId) && ll1WithinAcceptance() ) ||
        ( interestingLepton == fabs(candidates->ll2_daughterPdgId) && ll2WithinAcceptance() ) ) {
      return true;
    }
  }
  else if ( nInterestingExotics == 2 ) {
    if ( ll1WithinAcceptance() && ll2WithinAcceptance() ) return true;
  }

  return false;
}

// Check, if a candidate has been correctly reco'd, if the gen exotic is outside the acceptance
bool DileptonAnalyzer::withinAcceptnace( TreeDipseudoLeptonCandidate & cand ) {
  // Get original leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  // Check if both leptons are within acceptance cuts
  if ( ( ( leptonL.genPt > acceptancePt1Cut_ && leptonH.genPt > acceptancePt2Cut_ ) || ( leptonL.genPt > acceptancePt2Cut_ && leptonH.genPt > acceptancePt1Cut_ ) )
      && fabs(leptonL.genEta) < acceptanceEtaCut_ && fabs(leptonH.genEta) < acceptanceEtaCut_ ) {
    return true;
  }
  return false;
}

// Vary lifetime cuts and store number of cands passing cuts
void DileptonAnalyzer::optimiseLifetimeCuts( double lxySig, double minD0, double weight ) {

  double lxySigCut = 0;
  double d0SigCut = 0;


  for ( lxySigCut=0; lxySigCut < 40; lxySigCut++ ) {
    if ( lxySig > lxySigCut ) {
      for ( d0SigCut=0; d0SigCut < 10; d0SigCut++ ) {
        if ( minD0 > d0SigCut ) {
          // Fill 2d histogram
          hists_.h_minD0SigCut_vs_LxySigCut->Fill(d0SigCut,lxySigCut,weight);
        }
        else break;
      }
    }
    else break;
  }
}


// Takes track of when (if) this candidate failed a cut
void DileptonAnalyzer::monitorCutFlow( DileptonAnalysisCuts::PassedWhichCuts & whichCuts, map< TString, float > & cutFlowMap, double weight ) {
  // whichCuts has record of which cuts this candidate has passed
  // Increment each counter accordingly
  cutFlowMap["AllCandidatesAfterPrefilter"] += weight;

  if ( whichCuts.passVertexChi2 ) cutFlowMap["DileptonChi2"] += weight; else return;
  if ( whichCuts.passOppCharge ) cutFlowMap["DileptonOppositeCharge"] += weight; else return;
  if ( whichCuts.passOppSignD0) cutFlowMap["SameSignD0"] += weight; else return;
  if ( whichCuts.passTrackPt ) cutFlowMap["LeptonPt"] += weight; else return;
  if ( whichCuts.passEta && whichCuts.passSCEta ) cutFlowMap["LeptonAbsEta"] += weight; else return;
  if ( whichCuts.passCaloMatch) cutFlowMap["CaloMatch"] += weight; else return;
  if ( whichCuts.passPhotonMatch) cutFlowMap["PhotonMatch"] += weight; else return;
  if ( whichCuts.passSCEt ) cutFlowMap["LeptonSCEt"] += weight; else return;
  if ( whichCuts.passPhotonID ) cutFlowMap["PhotonID"] += weight; else return;
  if ( whichCuts.passMuonID ) cutFlowMap["MuonID"] += weight; else return;
  if ( whichCuts.passTrackQuality ) cutFlowMap["TrackQuality"] += weight; else return;
  if ( whichCuts.passTriggerMatch ) cutFlowMap["DileptonTriggerMatch"] += weight; else return;
  if ( whichCuts.passIso ) cutFlowMap["DileptonIsolation"] += weight; else return;
  if ( whichCuts.passMass ) cutFlowMap["DileptonMass"] += weight; else return;
  if ( whichCuts.passCosine ) cutFlowMap["DileptonB2BVeto"] += weight; else return;
  if ( whichCuts.passDeltaR ) cutFlowMap["DileptonDeltaR"] += weight; else return;
  if ( whichCuts.passDeltaPhi ) cutFlowMap["DileptonDeltaPhi"] += weight; else return;
  if ( whichCuts.passLeptonD0 ) cutFlowMap["LeptonD0Sig"] += weight; else return;
  if ( whichCuts.passHitsBeforeVertex ) cutFlowMap["DileptonHitsBeforeVertex"] += weight; else return;
  if ( whichCuts.passMissingHitsAfterVertex ) cutFlowMap["DileptonMissingHitsAfterVertex"] += weight; else return;
  if ( whichCuts.passMinLxySig ) cutFlowMap["DileptonAbsLxySig"] += weight; else return;

  return;
}

// Report cut flow findings to screen
void DileptonAnalyzer::reportCutFlow( TFile & outputFile ) {

  // Store in a TProfile
  TH1F *cutFlow = new TH1F("cutFlow","Cut flow for final set of analysis cuts",25,0.5,25.5);
  TAxis *cutFlowAxis = cutFlow->GetXaxis();

  for ( unsigned int iCut = 0; iCut < cutNamesInOrder_.size(); iCut++ ) {
    cutFlow->SetBinContent( iCut+1, cutFlowMap_[cutNamesInOrder_[iCut]]);
    cutFlowAxis->SetBinLabel( iCut+1, cutNamesInOrder_[iCut]);
  }
  outputFile.cd();
  cutFlow->Write();

  // Store in a TProfile
  TH1F *cutFlowColl = new TH1F("cutFlowColl","Cut flow for final set of analysis cuts",25,0.5,25.5);
  cutFlowAxis = cutFlowColl->GetXaxis();

  // Store number of signal MC exotics before cut flow in separate histogram
  if ( isSignalMC_ ) {
    TH1F *cutFlowColl_preselection = new TH1F("cutFlowColl_preselection","Cut flow for preselection of analysis cuts",25,0.5,25.5);
    TAxis *cutFlowCollAxis_preselection = cutFlowColl_preselection->GetXaxis();
    cutFlowColl_preselection->SetBinContent(0, nExoticsBeforeAcceptance_);
    cutFlowColl_preselection->SetBinContent(1, nExoticsBeforePrefilter_);
    cutFlowCollAxis_preselection->SetBinLabel( 1, "All exotics");
    cutFlowColl_preselection->SetBinContent(2, nExoticsAfterTrigger_);
    cutFlowCollAxis_preselection->SetBinLabel( 2, "After trigger");
    cutFlowColl_preselection->SetBinContent(3, nCorrectlyRecoExoticsBeforePrefilter_);
    cutFlowCollAxis_preselection->SetBinLabel( 3, "After correct reco");

    outputFile.cd();
    cutFlowColl_preselection->Write();

    cutFlowColl->SetBinContent( 0, nExoticsBeforePrefilter_);

  }

  for ( unsigned int iCut = 0; iCut < cutNamesInOrder_.size(); iCut++ ) {
    cutFlowColl->SetBinContent( iCut+1, cutFlowMapColl_[cutNamesInOrder_[iCut]]);
    cutFlowAxis->SetBinLabel( iCut+1, cutNamesInOrder_[iCut]);
  }

  outputFile.cd();
  cutFlowColl->Write();
}


void progressCounter( unsigned int progress ) {

  cout << "\r";
  cout << "[";
  for ( unsigned int i = 0; i < 10; i++ ) {
    if ( i < progress/10 ) cout << "=====";
    else cout << "-----";
  }
  cout << "] " << progress << "%" << flush;
}

// Check if event is ditau
bool DileptonAnalyzer::isDitauEvent() {
  bool isTau = false;
  if ( fabs(candidates->ll1_motherPdgId) == 15 || fabs(candidates->ll2_motherPdgId) == 15 ) isTau = true;
  return isTau;
}

bool DileptonAnalyzer::isCentralCtau() {
  if ( candidates->ll1_motherPdgId==centralPdgId_ || candidates->ll2_motherPdgId==centralPdgId_ ) return true;
  else return false;
}

// Get interesting lepton for this analysis
unsigned int DileptonAnalyzer::getInterestingLepton() {
  if ( anaType_==_2eTrack ) return 11;
  else return 13;
}

void DileptonAnalyzer::outputCandInfoToScreen( const TreeDipseudoLeptonCandidate &cand ){
  // Get leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  cout << endl << "---> Event : " << endl;
  cout << "Event weight : " << eventWeight_ << endl;
  cout << "Run, lumi, event : " << candidates->run << " " << candidates->lumi << " " << candidates->event << endl;
  cout << "Num pv : " << candidates->numPV << endl;
  cout << "Main PV position : " << candidates->pv_x << " " << candidates->pv_y << " " << candidates->pv_z << endl;
  cout << "Errors : " << candidates->pv_xError << " " << candidates->pv_yError << " " << candidates->pv_zError << endl;
  cout << "N tracks : " << candidates->pv_nTracks << endl;
  cout << "Refitted pvRefit position : " << cand.pvRefit_x << " " << cand.pvRefit_y << " " << cand.pvRefit_z << endl;
  cout << "Errors : " << cand.pvRefit_xError << " " << cand.pvRefit_yError << " " << cand.pvRefit_zError << endl;
  cout << "N tracks : " << cand.pvRefit_nTracks << endl;
  cout << "---> Vertex" << endl;
    cout << "Valid : " << cand.validVertex << endl;
  cout << "Chi^2 : " << cand.vertexChi2 << endl;
  cout << "Lxy : " << cand.decayLength_PV << endl;
  cout << "Lxy/sigma : " << cand.decayLengthSignificance_PV << endl;
  cout << "Corr Mass : " << cand.corrDileptonMass << endl;
  //  cout << "Calo corr mass : " << cand.caloCorrMass << endl;
  cout << "Position : " << cand.vx << " " << cand.vy << " " << cand.vz << endl;
  cout << "dPhi : " << cand.dPhiCorr << endl;
  cout << "Missing hits : " << cand.missedLayersAfterVertexL << " " << cand.missedLayersAfterVertexH << endl;
  cout << "Hits before : " << cand.hitsBeforeVertexL << " " << cand.hitsBeforeVertexH << endl;
  cout << "Delta R : " << cand.deltaR << endl;
  cout << "Cos alpha : " << cand.cosine << endl;
  cout << "---> Lepton L" << endl;
  cout << "Valid track : " << leptonL.validTrack << endl;
  //  cout << "Type : " << leptonL.isCentralTrack << " " << leptonL.isGlobalMuon << " " << leptonL.isTrackerMuon << " " << leptonL.isStandAloneMuon << endl;
  cout << "Tracking iteration : " << leptonL.algo << endl;
  cout << "pt : " << leptonL.pt << endl;
  //  cout << "Photon et : " << leptonL.photonEt << endl;
  //  cout << "Photon eta : " << leptonL.photonEta << endl;
  cout << "phi : " << leptonL.phi << endl;
  cout << "theta : " << 2 * atan( exp(-leptonL.eta) ) << endl;
  cout << "eta : " << leptonL.eta << endl;
    cout << "Trigger match : " << leptonL.triggerMatch << endl;
    cout << "Index : " << leptonL.triggerObjectIndex << endl;
  //          cout << "d0 : " << leptonL.d0_PV << endl;
  //          cout << "d0/sigma : " << leptonL.d0Significance_PV << endl;
  //          cout << "d0/sigma incl PV : " << leptonL.d0Significance_PV_includingPVError << endl;
  cout << "Signed d0 wrt PV : " << cand.leptonD0L_PV << endl;
  cout << "wrt BS : " << cand.leptonD0L_BS << endl;
  cout << "Signed d0/sigma : " << cand.leptonD0SignificanceL_PVrefit_includingPVError << endl;
  cout << "Sigma : " << cand.leptonD0L_PV / cand.leptonD0SignificanceL_PVrefit_includingPVError << endl;
  cout << "dz : " << leptonL.dz_PV << endl;
  cout << "dz/sigma : " << leptonL.dzsignificance_PV << endl;
  //          cout << "Iso : " << cand.leptonIsoL << endl;
  cout << "Rel iso : " << cand.leptonIsoL/leptonL.pt << endl;
  //  cout << "Gen pdg id : " << leptonL.genPdgId << endl;
  //  cout << "Gen pt : " << leptonL.genPt << endl;
  //  cout << "Gen vertex : " << leptonL.genVertexX << " " << leptonL.genVertexY << " " << leptonL.genVertexZ << endl;
  //  cout << "Gen d0 : " << leptonL.genD0 << endl;
  //  cout << "Gen mother pdg id : " << leptonL.genSignalOriginPdgId << endl;
  //  cout << "Gen mother ctau : " << leptonL.genSignalOriginCtau << endl;
  //  cout << "Gen mother Lxy : " << leptonL.genSignalOriginLxy << endl;

  cout << "---> Lepton H" << endl;
  cout << "Valid track : " << leptonH.validTrack << endl;
  //  cout << "Type : " << leptonH.isCentralTrack << " " << leptonH.isGlobalMuon << " " << leptonH.isTrackerMuon << " " << leptonH.isStandAloneMuon << endl;
  cout << "Tracking iteration : " << leptonH.algo << endl;
  cout << "pt : " << leptonH.pt << endl;
  //  cout << "Photon et : " << leptonH.photonEt << endl;
  //  cout << "Photon eta : " << leptonH.photonEta << endl;
  cout << "phi : " << leptonH.phi << endl;
  cout << "theta : " << 2 * atan( exp(-leptonH.eta) ) << endl;
  cout << "eta : " << leptonH.eta << endl;
    cout << "Trigger match : " << leptonH.triggerMatch << endl;
    cout << "Index : " << leptonH.triggerObjectIndex << endl;
  //          cout << "d0 : " << leptonH.d0_PV << endl;
  //          cout << "d0/sigma : " << leptonH.d0Significance_PV << endl;
  //          cout << "d0/sigma incl PV : " << leptonH.d0Significance_PV_includingPVError << endl;
  cout << "Signed d0 : " << cand.leptonD0H_PV << " wrt BS : " << cand.leptonD0H_BS << endl;
  cout << "Signed d0/sigma : " << cand.leptonD0SignificanceH_PVrefit_includingPVError << endl;
  cout << "Sigma : " << cand.leptonD0H_PV / cand.leptonD0SignificanceH_PVrefit_includingPVError << endl;
  cout << "dz : " << leptonH.dz_PV << endl;
  cout << "dz/sigma : " << leptonH.dzsignificance_PV << endl;
  //          cout << "Iso : " << cand.leptonIsoH << endl;
  cout << "Rel iso : " << cand.leptonIsoH/leptonH.pt << endl;
  //  cout << "Gen pdg id : " << leptonH.genPdgId << endl;
  //  cout << "Gen pt : " << leptonH.genPt << endl;
  //  cout << "Gen vertex : " << leptonH.genVertexX << " " << leptonH.genVertexY << " " << leptonH.genVertexZ << endl;
  //  cout << "Gen mother pdg id : " << leptonH.genSignalOriginPdgId << endl;
  //  cout << "Gen mother ctau : " << leptonH.genSignalOriginCtau << endl;
  //  cout << "Gen mother Lxy : " << leptonH.genSignalOriginLxy << endl;

  //  cout << "Event gen info" << endl;
  //  cout << "Mother 1" << endl;
  //  cout << "Mother : " << candidates->ll1_motherPdgId << endl;
  //  cout << "Daugher pdgid : " << candidates->ll1_daughterPdgId << endl;
  //  cout << "Ctau : " << candidates->ll1_ctau << endl;
  //  cout << "Pt : " << candidates->ll1_pt << endl;
  //  cout << "Lxy : " << candidates->ll1_decayLength2D << endl;
  //  cout << "Lxyz : " << candidates->ll1_decayLength3D << endl;
  //  cout << "Daughter 1 pt : " << candidates->ll1_daughter1_Pt << endl;
  //  cout << "Daughter 1 eta : " << candidates->ll1_daughter1_Eta << endl;
  //  cout << "Daughter 1 d0 : " << candidates->ll1_daughter1_D0 << endl;
  //  cout << "Daughter 2 pt : " << candidates->ll1_daughter2_Pt << endl;
  //  cout << "Daughter 2 eta : " << candidates->ll1_daughter2_Eta << endl;
  //  cout << "Daughter 2 d0 : " << candidates->ll1_daughter2_D0 << endl;
  //  cout << "Mother 2" << endl;
  //  cout << "Mother : " << candidates->ll2_motherPdgId << endl;
  //  cout << "Daugher pdgid : " << candidates->ll2_daughterPdgId << endl;
  //  cout << "Ctau : " << candidates->ll2_ctau << endl;
  //  cout << "Pt : " << candidates->ll2_pt << endl;
  //  cout << "Lxy : " << candidates->ll2_decayLength2D << endl;
  //  cout << "Lxyz : " << candidates->ll2_decayLength3D << endl;
  //  cout << "Daughter 1 pt : " << candidates->ll2_daughter1_Pt << endl;
  //  cout << "Daughter 1 eta : " << candidates->ll2_daughter1_Eta << endl;
  //  cout << "Daughter 1 d0 : " << candidates->ll2_daughter1_D0 << endl;
  //  cout << "Daughter 2 pt : " << candidates->ll2_daughter2_Pt << endl;
  //  cout << "Daughter 2 eta : " << candidates->ll2_daughter2_Eta << endl;
  //  cout << "Daughter 2 d0 : " << candidates->ll2_daughter2_D0 << endl;


  cout << endl;
}

//// Attempt to match reco lepton to gen lepton from Candidates.h
//void DileptonAnalyzer::findGenMatch( TreeLepton &lepton ){
//
//  unsigned int interestingLepton = getInterestingLepton();
//
//  if ( lepton.genPdgId==0) {
//    cout << "Lepton pt : " << lepton.pt << endl;
//    cout << "Lepton eta : " << lepton.eta << endl;
//    cout << "Current gen match pdg id, pt, eta : " << lepton.genPdgId << " " << lepton.genPt << " " << lepton.genEta << endl;
//
//    if ( fabs(candidates->ll1_daughterPdgId) == interestingLepton ) cout << candidates->ll1_daughter1_Pt << " " << candidates->ll1_daughter2_Pt << endl;
//    if ( fabs(candidates->ll2_daughterPdgId) == interestingLepton ) cout << candidates->ll2_daughter1_Pt << " " << candidates->ll2_daughter2_Pt << endl;
//    cout << endl;
//  }
//}

double DileptonAnalyzer::whichMass( TreeDipseudoLeptonCandidate &cand ) {

  // Get leptons
  TreeLepton leptonL = getLepton( cand.leptonIndexL );
  TreeLepton leptonH = getLepton( cand.leptonIndexH );

  // Choose appropiate mass to plot
  double mass = cand.corrDileptonMass;
  if (anaType_==_2eTrack ) {
    if ( isData_ ) {
      mass = cand.caloCorrMass;
    }
    else {
      // Need to smear mass in electron channel for background MC only
      bool leptonLInBarrel = ( fabs( leptonL.photonEta ) < 1.55 ) ? true : false;
      bool leptonHInBarrel = ( fabs( leptonH.photonEta ) < 1.55 ) ? true : false;
      mass=smearMass( cand.caloCorrMass, leptonLInBarrel, leptonHInBarrel );
    }
  }

  return mass;

}

void DileptonAnalyzer::whichIso( const TreeDipseudoLeptonCandidate &cand, double &leptonIsoL, double &leptonIsoH) {
  if (anaType_==_2eTrack ) {
    leptonIsoL = cand.leptonIsoL4;
    leptonIsoH = cand.leptonIsoH4;
  }
  else {
    leptonIsoL = cand.leptonIsoL;
    leptonIsoH = cand.leptonIsoH;
  }
}

double DileptonAnalyzer::getMinD0( const TreeDipseudoLeptonCandidate &cand ) {
  return min( fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError), fabs(cand.leptonD0SignificanceH_PVrefit_includingPVError)) == fabs( cand.leptonD0SignificanceL_PVrefit_includingPVError ) ?
      cand.leptonD0SignificanceL_PVrefit_includingPVError : cand.leptonD0SignificanceH_PVrefit_includingPVError;
}

double DileptonAnalyzer::getMaxD0( const TreeDipseudoLeptonCandidate &cand, float minD0Sigma ) {
  return ( minD0Sigma == cand.leptonD0SignificanceL_PVrefit_includingPVError ) ? cand.leptonD0SignificanceH_PVrefit_includingPVError : cand.leptonD0SignificanceL_PVrefit_includingPVError;
}

void DileptonAnalyzer::fillRemovedLifetimePlots( TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH, double mass, DileptonAnalysisCuts::PassedWhichCuts removedLifetimeCuts, Histograms & h ) {



//  // Sign of Lxy/sigma
//  int signLxy = 1;
//  if( cand.dPhiCorr > TMath::PiOver2() ) signLxy = -1;
//
//  // All cuts applied
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCuts ) ) {
//    h.h_mass_removedLifetimeCuts->Fill( mass, eventWeight_ );
//    h.h_mt_removedLifetimeCuts->Fill( cand.transverseMass, eventWeight_ );
//    h.h_nRecoPV_removedLifetimeCuts->Fill( candidates->numPV, eventWeight_ );
//
//    // Plot nPV with systematic variations
//    // Calculate different event weight with different pu weight
//    double puP5weight = puweights_p5_.weight( candidates->nvtx_true );
//    double puM5weight = puweights_m5_.weight( candidates->nvtx_true );
//    h.h_nRecoPV_p5_removedLifetimeCuts->Fill(candidates->numPV, puP5weight * xsecWeight_ );
//    h.h_nRecoPV_m5_removedLifetimeCuts->Fill(candidates->numPV, puM5weight * xsecWeight_ );
//
//    // Plots of pt, eta etc.
//    h.h_leptonLPt_removedLifetimeCuts->Fill( leptonL.pt, eventWeight_ );
//    h.h_leptonHPt_removedLifetimeCuts->Fill( leptonH.pt, eventWeight_ );
//    h.h_leptonLEta_removedLifetimeCuts->Fill( leptonL.eta, eventWeight_ );
//    h.h_leptonHEta_removedLifetimeCuts->Fill( leptonH.eta, eventWeight_ );
//    h.h_leptonLCaloMatchDeltaR_removedLifetimeCuts->Fill( leptonL.cmDeltaR, eventWeight_ );
//    h.h_leptonHCaloMatchDeltaR_removedLifetimeCuts->Fill( leptonH.cmDeltaR, eventWeight_ );
//    h.h_Lxy_removedLifetimeCuts->Fill( cand.decayLength_PV, eventWeight_ );
//    h.h_LxySig_removedLifetimeCuts->Fill( signLxy*cand.decayLengthSignificance_PV, eventWeight_ );
//
//    h.h_leptonTrackingAlgo_removedLifetimeCuts->Fill( leptonL.algo, eventWeight_ );
//    h.h_leptonTrackingAlgo_removedLifetimeCuts->Fill( leptonH.algo, eventWeight_ );
//
//    // D0 wrt beamspot
//    h.h_minLeptonD0SigBL_removedLifetimeCuts->Fill(min( leptonL.d0Significance_BS, leptonH.d0Significance_BS), eventWeight_ );
//
//    // Before PV refit
//    // To show improvement after refitting vertex
//    double minD0_PVnorefit = min( fabs(cand.leptonD0SignificanceL_PV_includingPVError), fabs(cand.leptonD0SignificanceH_PV_includingPVError)) == fabs( cand.leptonD0SignificanceL_PV_includingPVError ) ?
//        cand.leptonD0SignificanceL_PV_includingPVError : cand.leptonD0SignificanceH_PV_includingPVError;
//
//    if ( cand.leptonD0SignificanceL_PV_includingPVError * cand.leptonD0SignificanceH_PV_includingPVError > 0 ) {
//      h.h_minLeptonD0Sig_PVnorefit_removedLifetimeCuts->Fill( minD0_PVnorefit, eventWeight_ );
//    }
//
//    // After PV refit
//    float minD0 = getMinD0( cand );
//    float maxD0 = getMaxD0( cand, minD0 );
//
//    // Standard d0/sigma n-1 plot.  Should be identical to d0/sigma n-1 plot from final cuts.  Cross check!
//    h.h_minLeptonD0Sig_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//    h.h_maxLeptonD0Sig_removedLifetimeCuts->Fill( maxD0, eventWeight_ );
//
//    // Plot for different tracking algorithms
//    float trackingAlgo = ( minD0 == cand.leptonD0SignificanceL_PVrefit_includingPVError ) ? leptonL.algo : leptonH.algo;
//    if ( trackingAlgo==4 ) {
//      h.h_minLeptonD0Sig_algo4_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//      h.h_leptonD0BS_algo4_forFittingData_removedLifetimeCuts->Fill( fabs( cand.leptonD0L_BS ), eventWeight_ );
//      h.h_leptonD0BS_algo4_forFittingData_removedLifetimeCuts->Fill( fabs( cand.leptonD0H_BS ), eventWeight_ );
//    }
//    else if ( trackingAlgo==5 ) h.h_minLeptonD0Sig_algo5_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//    else if ( trackingAlgo==6 ) h.h_minLeptonD0Sig_algo6_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//    else if ( trackingAlgo==7 ) h.h_minLeptonD0Sig_algo7_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//    else if ( trackingAlgo==8 ) h.h_minLeptonD0Sig_algo8_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//    else if ( trackingAlgo==9 ) h.h_minLeptonD0Sig_algo9_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//    else if ( trackingAlgo==10 ) h.h_minLeptonD0Sig_algo10_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//
//
//    // Same plots, but with signal region blinded
//    if ( ( anaType_==_2eTrack && minD0 < 6 ) || ( ( anaType_==_2muTrack || anaType_ == _2globalOrTrackerMu ) && minD0 < 4 ) ) {
//      h.h_minLeptonD0Sig_forFittingData_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//
//      // Also plot for different tracking algorithms
//      if ( trackingAlgo==4 ) h.h_minLeptonD0Sig_algo4_forFittingData_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//      else if ( trackingAlgo==5 ) h.h_minLeptonD0Sig_algo5_forFittingData_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//      else if ( trackingAlgo==6 ) h.h_minLeptonD0Sig_algo6_forFittingData_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//      else if ( trackingAlgo==7 ) h.h_minLeptonD0Sig_algo7_forFittingData_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//      else if ( trackingAlgo==8 ) h.h_minLeptonD0Sig_algo8_forFittingData_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//      else if ( trackingAlgo==9 ) h.h_minLeptonD0Sig_algo9_forFittingData_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//      else if ( trackingAlgo==10 ) h.h_minLeptonD0Sig_algo10_forFittingData_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//
//    }
//
//    // D0 and sigma
//    h.h_leptonD0_removedLifetimeCuts->Fill( min( cand.leptonD0L_PV, cand.leptonD0H_PV), eventWeight_ );
//    if ( min(leptonL.d0Significance_PV_includingPVError,leptonH.d0Significance_PV_includingPVError) == leptonL.d0Significance_PV_includingPVError ) {
//      h.h_leptonSig_removedLifetimeCuts->Fill( leptonL.d0_PV/leptonL.d0Significance_PV_includingPVError, eventWeight_ );
//    }
//    else {
//      h.h_leptonSig_removedLifetimeCuts->Fill( leptonH.d0_PV/leptonH.d0Significance_PV_includingPVError, eventWeight_ );
//    }
//
//    // Store masses and weights on candidates that pass this selection cuts
//    removedLifetime_ << mass << " " << eventWeight_ << endl;
//
//    // Very basic optimisation - No longer used.
//    // However keep as useful to show that we can get away without cutting on d0/sigma
//    optimiseLifetimeCuts( signLxy*cand.decayLengthSignificance_PV*lxyScale_, min(leptonL.d0Significance_PV_includingPVError*d0Scale_,leptonH.d0Significance_PV_includingPVError*d0Scale_), eventWeight_ );
//  }
////  else {
////    cout << "Cand failed removed lfietime" << endl;
////    dileptonCuts_removedLifetime_.printPassForOneCand( removedLifetimeCuts );
////    outputCandInfoToScreen( cand );
////    cout << endl;
////
////  }


  // n-1 (for track mis-alignment studies)
  // No requirement on d0/sigma (magnitude or sign)
  // Also study collinearity method here
  DileptonAnalysisCuts::PassedWhichCuts removedLifetimeCutsTemp = removedLifetimeCuts;
  removedLifetimeCutsTemp.passOppSignD0 = true;


  // Only for data
  if ( isData_ ) {
    // Remove d0/sigma requirements to measure bias
    // n-1 (for track mis-alignment studies)
    removedLifetimeCutsTemp = removedLifetimeCuts;
    // Optionally reapply this selection
    bool candPassVertex = ( removedLifetimeCutsTemp.passVertexChi2 );

    removedLifetimeCutsTemp.passOppSignD0 = true;
//    removedLifetimeCutsTemp.passRequireVertex = true;
    removedLifetimeCutsTemp.passVertexChi2 = true;
    if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
      // No requirement on d0/sigma size or sign
      // No requirement on vertex chi2, but can be reapplied using bool
      studyTrackD0Misalignment(cand, leptonL, leptonH, candPassVertex, h);
      studyTrackZ0Misalignment(cand, leptonL, leptonH, candPassVertex, h);
    }
  }

//  // These candidates have no requirement on d0 (magnitude or sign)
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//
//    // Lepton L vs lepton H d0/sigma
//    h.h_l_vs_h_leptonD0Sig_removedLifetimeCuts->Fill( fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError), fabs(cand.leptonD0SignificanceH_PVrefit_includingPVError), eventWeight_ );
//
//    // Get smallest and largest d0/sigma
//    float minD0 = getMinD0( cand );
//    float maxD0 = getMaxD0( cand, minD0 );
//
//    // Plot leptons with opposite sign d0
//    if ( minD0 * maxD0 < 0 ) {
//      h.h_minLeptonD0Sig_oppSign_removedLifetimeCuts->Fill( minD0, eventWeight_ );
//      if ( ( anaType_==_2eTrack && minD0 < 5 && minD0 > -5 ) || ( ( anaType_==_2muTrack || anaType_ == _2globalOrTrackerMu ) && minD0 < 4.5 && minD0 > -3.5 ) ) {
//        h.h_minLeptonD0Sig_oppSign_forFittingData_removedLifetimeCuts->Fill(minD0, eventWeight_ );
//      }
//    }
//
//    // Signed wrt vector perpendicular to dilepton momentum
//    // Magnitude same, just different sign (possibly)
//    // Should make signal symmetric about 0
//    if ( cand.leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError * cand.leptonD0SignificanceH_PVrefit_sigWrtPerpDilepton_includingPVError > 0 ) {
//      float minD0SignPerp = ( min( fabs(cand.leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError),fabs(cand.leptonD0SignificanceH_PVrefit_sigWrtPerpDilepton_includingPVError) ) == fabs(cand.leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError) ) ? cand.leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError : cand.leptonD0SignificanceH_PVrefit_sigWrtPerpDilepton_includingPVError;
//      h.h_minLeptonD0Sig_signedWrtDileptonPerp_removedLifetimeCuts->Fill( minD0SignPerp, eventWeight_ );
//    }
//
//    // Only for data
//    // Repeat above but with corrections on d0/sigma
//    if ( isData_ ) {
//
//      // Same sign d0/sigma and recalculation of min (d0/sigma of the two leptons) is performed inside fillCorrectedD0Sigma
//
//      // Correct d0/sigma by bias (calculated in studyTrackD0Misalignment and python script after) and plot new distribution
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhi_, h.h_bothLeptonsD0Sig_d0Corrected_removedLifetimeCuts,
//          h.h_minLeptonD0Sig_d0Corrected_removedLifetimeCuts, h.h_minLeptonD0Sig_d0Corrected_forFittingData_removedLifetimeCuts, "normal", false );
//
//      // Same corrections but now run dependent
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhi_, h.h_bothLeptonsD0Sig_d0CorrectedRunDependent_removedLifetimeCuts,
//          h.h_minLeptonD0Sig_d0CorrectedRunDependent_removedLifetimeCuts, h.h_minLeptonD0Sig_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts, "normal", true, meanD0SignificanceVsThetaVsPhi_badRun_ );
//
//      // Corrections additionally divided into whether the tracks have pixel hits or not
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhi_pixel_, h.h_bothLeptonsD0Sig_d0CorrectedPixel_removedLifetimeCuts,
//          h.h_minLeptonD0Sig_d0CorrectedPixel_removedLifetimeCuts, h.h_minLeptonD0Sig_d0CorrectedPixel_forFittingData_removedLifetimeCuts, "pixel", false );
//
//      // Corrections based on bias in d0 rather than d0/sigma
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0VsThetaVsPhi_, h.h_bothLeptonsD0Sig_d0CorrectedIP_removedLifetimeCuts,
//          h.h_minLeptonD0Sig_d0CorrectedIP_removedLifetimeCuts, h.h_minLeptonD0Sig_d0CorrectedIP_forFittingData_removedLifetimeCuts, "d0", false );
//
//      // No corrections, just same cuts
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhi_, h.h_bothLeptonsD0Sig_NoCorrections_removedLifetimeCuts,
//          h.h_minLeptonD0Sig_NoCorrections_removedLifetimeCuts, h.h_minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts, "none", false );
//
//      // Normal corrections, d0 signed wrt vector perpendicular to dilepton momentum
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhi_, h.h_bothLeptonsD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts,
//          h.h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts, h.h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_forFittingData_removedLifetimeCuts, "perpToDilepton", false );
//
//      // Corrections derived only from leptons with d0/sigma > 2
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhiCut_, h.h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts,
//          h.h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts, h.h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_forFittingData_removedLifetimeCuts, "perpToDilepton", false );
//
//      // Normal corrections, d0 signed wrt vector perpendicular to dilepton momentum
//      // Run dependent corrections
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhi_, h.h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts,
//          h.h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts, h.h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts, "perpToDilepton", true, meanD0SignificanceVsThetaVsPhi_badRun_ );
//
//      // No corrections, d0 signed wrt vector perpendicular to dilepton momentum
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhi_, h.h_bothLeptonsD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts,
//          h.h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts, h.h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_forFittingData_removedLifetimeCuts, "perpToDileptonNone", false );
//
//      //
//      // Corrections derived without vertex requirement
//      //
//      // Normal, run dependent corrections
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhi_noVertex_, h.h_bothLeptonsD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts,
//                h.h_minLeptonD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts, h.h_minLeptonD0Sig_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts, "normal", true, meanD0SignificanceVsThetaVsPhi_badRun_noVertex_ );
//
//      // Normal, run dependent corrections
//      // Sign d0 wrt vector perpendicular to dilepton momentum
//      fillCorrectedD0Sigma( cand, leptonL, leptonH, meanD0SignificanceVsThetaVsPhi_noVertex_, h.h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts,
//                h.h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts, h.h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts, "perpToDilepton", true, meanD0SignificanceVsThetaVsPhi_badRun_noVertex_ );
//    }
//  }
//
//
//
//  // n-1 (for isolation)
//  removedLifetimeCutsTemp = removedLifetimeCuts;
//  removedLifetimeCutsTemp.passIso = true;
//
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//    h.h_nMinus1_isolationLeptonL_removedLifetimeCuts->Fill( cand.leptonIsoL, eventWeight_ );
//    h.h_nMinus1_isolationLeptonH_removedLifetimeCuts->Fill( cand.leptonIsoH, eventWeight_ );
//    h.h_nMinus1_relIsolationLeptonL_removedLifetimeCuts->Fill( cand.leptonIsoL/leptonL.pt, eventWeight_ );
//    h.h_nMinus1_relIsolationLeptonH_removedLifetimeCuts->Fill( cand.leptonIsoH/leptonH.pt, eventWeight_ );
//  }
//
//  // n-1 for missing hits after vertex
//  removedLifetimeCutsTemp = removedLifetimeCuts;
//  removedLifetimeCutsTemp.passMissingHitsAfterVertex = true;
//
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//    h.h_nMinus1_nMissingHitsAfterVertex_removedLifetimeCuts->Fill( cand.missedLayersAfterVertexL + cand.missedLayersAfterVertexH, eventWeight_ );
//    h.h_nMinus1_maxMissingHitsAfterVertex_removedLifetimeCuts->Fill( max( cand.missedLayersAfterVertexL, cand.missedLayersAfterVertexH), eventWeight_ );
//    h.h_nMinus1_minMissingHitsAfterVertex_removedLifetimeCuts->Fill( min( cand.missedLayersAfterVertexL, cand.missedLayersAfterVertexH), eventWeight_ );
//  }
//
//  // n-1 for hits before vertex
//  removedLifetimeCutsTemp = removedLifetimeCuts;
//  removedLifetimeCutsTemp.passHitsBeforeVertex = true;
//
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//    h.h_nMinus1_nHitsBeforeVertex_removedLifetimeCuts->Fill( cand.hitsBeforeVertexL + cand.hitsBeforeVertexH, eventWeight_ );
//  }
//
//  // n-1 for vertex chi^2
//  removedLifetimeCutsTemp = removedLifetimeCuts;
//  removedLifetimeCutsTemp.passVertexChi2 = true;
//
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//    h.h_nMinus1_vertexChi2_removedLifetimeCuts->Fill( cand.vertexChi2, eventWeight_ );
//
//    if ( fabs(cand.leptonD0L_PV) < 0.001 && fabs(cand.leptonD0H_PV < 0.001) ) {
//      h.h_nMinus1_vertexChi2_removedLifetimeCuts_vPrompt->Fill( cand.vertexChi2, eventWeight_ );
//    }
//  }
//
//  // n-1 (for photon ID)
//  removedLifetimeCutsTemp = removedLifetimeCuts;
//  removedLifetimeCutsTemp.passPhotonID = true;
//
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//    // Photon ID
//    h.h_photonR9_removedLifetimeCuts->Fill( leptonL.photonR9, eventWeight_ );
//    h.h_photonR9_removedLifetimeCuts->Fill( leptonH.photonR9, eventWeight_ );
//    h.h_photonHadTowOverEm_removedLifetimeCuts->Fill( leptonL.photonHadTowOverEm, eventWeight_ );
//    h.h_photonHadTowOverEm_removedLifetimeCuts->Fill( leptonH.photonHadTowOverEm, eventWeight_ );
//
//    if ( fabs( leptonL.photonEta ) < 1.55 ) h.h_photonSigmaIetaIeta_barrel_removedLifetimeCuts->Fill( leptonL.photonSigmaIetaIeta, eventWeight_ );
//    else h.h_photonSigmaIetaIeta_endcap_removedLifetimeCuts->Fill( leptonL.photonSigmaIetaIeta, eventWeight_ );
//    if ( fabs( leptonH.photonEta ) < 1.55 ) h.h_photonSigmaIetaIeta_barrel_removedLifetimeCuts->Fill( leptonH.photonSigmaIetaIeta, eventWeight_ );
//    else h.h_photonSigmaIetaIeta_endcap_removedLifetimeCuts->Fill( leptonH.photonSigmaIetaIeta, eventWeight_ );
//  }
//
//  // For misalignment studies --- Not used. Plan to remove
//  // Try to set up some control region where one lepton fails some id criteria and the other passes
//  removedLifetimeCutsTemp = removedLifetimeCuts;
//  removedLifetimeCutsTemp.passTriggerMatch = true;
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//    // Now require one lepton to have TO match and the other not
//    if ( ( leptonL.triggerMatch != 0 && leptonH.triggerMatch == 0 ) ||
//        ( leptonH.triggerMatch != 0 && leptonL.triggerMatch == 0 ) ) {
//
//      if ( leptonL.triggerMatch != 0 ) {
//        if ( fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError) < fabs( cand.leptonD0SignificanceH_PVrefit_includingPVError ) ) {
//          h.h_minLeptonD0Sig_controlTrigger_removedLifetimeCuts->Fill(cand.leptonD0SignificanceL_PVrefit_includingPVError,eventWeight_);
//        }
//      }
//      else if ( leptonH.triggerMatch != 0 ) {
//        if ( fabs(cand.leptonD0SignificanceH_PVrefit_includingPVError) < fabs( cand.leptonD0SignificanceL_PVrefit_includingPVError ) ) {
//          h.h_minLeptonD0Sig_controlTrigger_removedLifetimeCuts->Fill(cand.leptonD0SignificanceH_PVrefit_includingPVError,eventWeight_);
//        }
//      }
//    }
//  }
//
//  removedLifetimeCutsTemp = removedLifetimeCuts;
//  removedLifetimeCutsTemp.passIso = true;
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//    // Now require one lepton to pass iso and the other to fail
//
//    double maxIso=0.1;
//    double upperIso=0.4;
//    if ( ( cand.leptonIsoL/leptonL.pt < maxIso && cand.leptonIsoH/leptonH.pt > maxIso ) || // L passes, H fails
//        ( cand.leptonIsoH/leptonH.pt < maxIso && cand.leptonIsoL/leptonL.pt > maxIso ) ) { // H passes, L fails
//
//      if ( cand.leptonIsoL/leptonL.pt < maxIso && cand.leptonIsoH/leptonH.pt < upperIso ) { // Also require lepton that fails isolation to pass looser isolation
//        if ( fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError) < fabs( cand.leptonD0SignificanceH_PVrefit_includingPVError ) ) {
//          h.h_minLeptonD0Sig_controlIsolation_removedLifetimeCuts->Fill(cand.leptonD0SignificanceL_PVrefit_includingPVError,eventWeight_);
//        }
//      }
//      else if ( cand.leptonIsoH/leptonH.pt < maxIso && cand.leptonIsoL/leptonL.pt < upperIso ) { // Also require lepton that fails isolation to pass looser isolation
//        if ( fabs(cand.leptonD0SignificanceH_PVrefit_includingPVError) < fabs( cand.leptonD0SignificanceL_PVrefit_includingPVError ) ) {
//          h.h_minLeptonD0Sig_controlIsolation_removedLifetimeCuts->Fill(cand.leptonD0SignificanceH_PVrefit_includingPVError,eventWeight_);
//        }
//      }
//    }
//  }
//
//  removedLifetimeCutsTemp = removedLifetimeCuts;
//  removedLifetimeCutsTemp.passVertexChi2 = true;
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//    // Now require candidate to fail vertex chi2
//    if ( cand.vertexChi2 > 5 ) {
//      float minD0 = getMinD0( cand );
//      h.h_minLeptonD0Sig_controlVertex_removedLifetimeCuts->Fill(minD0,eventWeight_);
//    }
//  }
}

// Study analysis that uses d0 signing
void DileptonAnalyzer::studyD0Signing( TreeDipseudoLeptonCandidate &cand, TreeLepton & leptonL, TreeLepton & leptonH, double & mass, Histograms & h, bool fillTextFiles ) {

  // Apply different sets of analysis cuts
  DileptonAnalysisCuts::PassedWhichCuts finalCuts = dileptonCuts_final_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );
//  DileptonAnalysisCuts::PassedWhichCuts looseCutsA = dileptonCuts_looseA_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );
//  DileptonAnalysisCuts::PassedWhichCuts looseCutsB = dileptonCuts_looseB_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );
//  DileptonAnalysisCuts::PassedWhichCuts looseCutsC = dileptonCuts_looseC_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );
  DileptonAnalysisCuts::PassedWhichCuts removedLifetimeCuts = dileptonCuts_removedLifetime_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );
//  DileptonAnalysisCuts::PassedWhichCuts removedLifetimeCutsNoVertex = dileptonCuts_removedLifetimeNoVertex_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );

  // Only filling histograms for central ctau exotic in signal MC
  if ( ( isSignalMC_ && isCentralCtau() ) || !isSignalMC_ ){
//    // Monitor cut flow for final selection cuts
//    // Apply prefilter so all sample have same/similar starting criteria
//    if ( passPrefilter() && withinAcceptnace( cand ) ) {
//      if ( isSignalMC_ && isCentralCtau() && eventWithinAcceptance( nSensitiveExoticDecayInEvent_ ) ) {
//          monitorCutFlow( finalCuts, cutFlowMap_, eventWeight_ );
//      }
//      else monitorCutFlow( finalCuts, cutFlowMap_, eventWeight_ );
//    }

    // Fill plots for different selection criteria
    // fillPlots method used for all selection except removedLifetime due to extra plots required

    //
    // Final Selection
    //
//    fillPlots( cand, leptonL, leptonH, mass, dileptonCuts_final_, finalCuts, h.histMapFinal, true );


//    //
//    // Loose Cuts A
//    //
//    fillPlots( cand, leptonL, leptonH, mass, dileptonCuts_looseA_, looseCutsA, h.histMapLooseA, false );
//
//    //
//    // Loose Cuts B
//    //
//
//    fillPlots( cand, leptonL, leptonH, mass, dileptonCuts_looseB_, looseCutsB, h.histMapLooseB, false );
//
//    //
//    // Loose Cuts C
//    //
//
//    fillPlots( cand, leptonL, leptonH, mass, dileptonCuts_looseC_, looseCutsC, h.histMapLooseC, false );
//
    //
    // Removed lifetime cuts
    // Keep separate as need to do a few other things
    //

    fillRemovedLifetimePlots( cand, leptonL, leptonH, mass, removedLifetimeCuts, h );

//    //
//    // Removed Lifetime with no vertexing requirement
//    //
//    fillPlots( cand, leptonL, leptonH, mass, dileptonCuts_removedLifetimeNoVertex_, removedLifetimeCutsNoVertex, h.histMapRemovedLifetimeNoVertex, false );

  }

//  // A few extra things to do with candidates passing all selection criteria
//  if ( dileptonCuts_final_.passAllCuts( finalCuts ) ) {
//
//    // A few extra things to do with signal MC for all ctau values
//    if ( isSignalMC_ ) {
//      // Study efficiencies etc.
//
//      // Study gen level info
//      // Count number of correctly reconstructed candidates
//      storeNumberOfExoticsRECO( cand, leptonL, leptonH, recoExotics_oneSensitiveDecay_, recoExotics_twoSensitiveDecay_ );
//
//      // Store reco mass and ctau of this cand
//      // Note if this candidate wasn't correctly reco'd, the two ctau values in the file will either
//      // not make sense or be inconsistent
//      if ( correctlyReconstructed(cand, leptonL, leptonH) ) {
//        allCuts_ << mass << " " << cand.transverseMass << " " << leptonL.genSignalOriginPdgId << " " << leptonL.genSignalOriginCtau << " " << eventWeight_ << endl;
//      }
//
//      if ( !correctlyReconstructed(cand, leptonL, leptonH) ) {
//        nIncorrect_++;
//      }
//      else {
//        nCorrect_++;
//      }
//
//      // Efficiency histograms
//      if ( isCentralCtau() && nSensitiveExoticDecayInEvent_==1 && eventWithinAcceptance( nSensitiveExoticDecayInEvent_ ) ) {
//
//        unsigned int interestingLepton=getInterestingLepton();
//        if ( interestingLepton == fabs(candidates->ll1_daughterPdgId) ) {
//            h.h_recoExotics_one_genLxy->Fill(candidates->ll1_decayLength2D, eventWeight_);
//            if ( candidates->ll1_decayLength2D > 0 && candidates->ll1_decayLength2D < 100 ) h.h_recoExotics_one_XPt->Fill(candidates->ll1_pt, eventWeight_);
//        }
//        else {
//          h.h_recoExotics_one_genLxy->Fill(candidates->ll2_decayLength2D, eventWeight_);
//          if ( candidates->ll2_decayLength2D > 0 && candidates->ll2_decayLength2D < 100 ) h.h_recoExotics_one_XPt->Fill(candidates->ll2_pt, eventWeight_);
//        }
//        h.h_recoExotics_one_nRecoPV->Fill(candidates->numPV, eventWeight_);
//
//
////        // Fill efficiency histo as function of Lxy if correctly reco'd
////        if ( leptonL.genSignalOriginPdgId==centralPdgId_ && eventWithinAcceptance( nSensitiveExoticDecayInEvent_ ) ) {
////          // Store lxy, X pt and # Reco PV of all cands for efficiency plots
////          double genLxy = ( leptonL.genSignalOriginLxy == leptonH.genSignalOriginLxy ) ? leptonL.genSignalOriginLxy : -1;
////          double xPt = ( genLxy == candidates->ll1_decayLength2D ) ? candidates->ll1_pt : candidates->ll2_pt;
////
////          if ( nSensitiveExoticDecayInEvent_==2 ) {
////            h.h_recoExotics_two_genLxy->Fill(genLxy, eventWeight_);
////            if ( genLxy > 0 && genLxy < 100 ) h.h_recoExotics_two_XPt->Fill(xPt, eventWeight_);
////            h.h_recoExotics_two_nRecoPV->Fill(candidates->numPV, eventWeight_);
////          }
////          else if ( nSensitiveExoticDecayInEvent_==1 ) {
////            h.h_recoExotics_one_genLxy->Fill(genLxy, eventWeight_);
////            if ( !(genLxy > 0 && genLxy < 50 ) ) cout << "Weird Lxy : " << genLxy << endl;
////            h.h_recoExotics_one_nRecoPV->Fill(candidates->numPV, eventWeight_);
////          }
////        }
//      }
//    }
//
//    // Save the mass of the candidates passing final selection
//    // Don't fill these for signal MC.  Done elsewhere and in different format
//    if ( isData_ && unblind_ && fillTextFiles ) {
//      allCuts_ << mass << "\t" << cand.transverseMass << "\t" << cand.decayLength_PV << "\t" << cand.leptonD0SignificanceL_PVrefit_includingPVError << "\t" << cand.leptonD0SignificanceH_PVrefit_includingPVError << "\t" << eventWeight_ << "\t" << candidates->run << "\t" << candidates->lumi << "\t" << candidates->event << endl;
//    }
//  }
//
//  // Extra things to do for cands passing removed lifetime criteria
//  if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCuts ) ) {
//
//    if ( isSignalMC_ ) {
//      // Store candidates that pass all selection but are on negative side of d0/sigma distribution
//      if ( cand.leptonD0SignificanceL_PVrefit_includingPVError < -1.0 * dileptonCuts_final_.getTrackD0SigmaCut() && cand.leptonD0SignificanceH_PVrefit_includingPVError < -1.0 * dileptonCuts_final_.getTrackD0SigmaCut() ) {
//        storeNumberOfExoticsRECO( cand, leptonL, leptonH, recoExotics_oneSensitiveDecay_negative_, recoExotics_twoSensitiveDecay_negative_ );
//      }
//    }
//
//    if ( isData_ && fillTextFiles ) {
//      // Store candidates in data that are in negative signal region
//      if ( cand.leptonD0SignificanceL_PVrefit_includingPVError < -1.0 * dileptonCuts_final_.getTrackD0SigmaCut() && cand.leptonD0SignificanceH_PVrefit_includingPVError < -1.0 * dileptonCuts_final_.getTrackD0SigmaCut() ) {
//        allCutsNegative_ << mass << "\t" << cand.transverseMass << "\t" << cand.decayLength_PV << "\t" << cand.leptonD0SignificanceL_PVrefit_includingPVError << "\t" << cand.leptonD0SignificanceH_PVrefit_includingPVError << "\t" << eventWeight_ << "\t" << candidates->run << "\t" << candidates->lumi << "\t" << candidates->event << endl;
//      }
//    }
//  }
//
//  // Extra things to do for cands passing removed lifetime criteria
//  if ( isSignalMC_ ) {
//    DileptonAnalysisCuts::PassedWhichCuts removedLifetimeCutsTemp = removedLifetimeCuts;
//    removedLifetimeCutsTemp.passOppSignD0 = true;
//
//    if ( dileptonCuts_removedLifetime_.passAllCuts( removedLifetimeCutsTemp ) ) {
//      // Also store exotics that have passed removedlifetime selection
//      storeNumberOfExoticsRECO( cand, leptonL, leptonH, recoExotics_oneSensitiveDecay_removedLifetime_, recoExotics_twoSensitiveDecay_removedLifetime_ );
//    }
//  }
//
//  // Extra isolation plots
//  // Correctly reco'd signal MC candidates for central ctau exotics
//  if ( isSignalMC_ && correctlyReconstructed( cand, leptonL, leptonH ) && isCentralCtau() ) {
//
//    DileptonAnalysisCuts::PassedWhichCuts finalCutsTemp = finalCuts;
//    finalCutsTemp.passIso = true;
//
//    if (  dileptonCuts_final_.passAllCuts( finalCutsTemp )  ) {
//      h.h_nMinus1_isolationLeptonL_finalCuts_genMatched->Fill( cand.leptonIsoL, eventWeight_ );
//      h.h_nMinus1_isolationLeptonH_finalCuts_genMatched->Fill( cand.leptonIsoH, eventWeight_ );
//      h.h_nMinus1_relIsolationLeptonL_finalCuts_genMatched->Fill( cand.leptonIsoL/leptonL.pt, eventWeight_ );
//      h.h_nMinus1_relIsolationLeptonH_finalCuts_genMatched->Fill( cand.leptonIsoH/leptonH.pt, eventWeight_ );
//
//      h.h_nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched->Fill( cand.leptonIsoL, candidates->numPV, eventWeight_ );
//      h.h_nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched->Fill( cand.leptonIsoH, candidates->numPV, eventWeight_ );
//      h.h_nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched->Fill( cand.leptonIsoL/leptonL.pt, candidates->numPV, eventWeight_ );
//      h.h_nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched->Fill( cand.leptonIsoH/leptonH.pt, candidates->numPV, eventWeight_ );
//      h.h_nMinus1_ptLeptonL_vsPU_finalCuts_genMatched->Fill( leptonL.pt, candidates->numPV, eventWeight_ );
//      h.h_nMinus1_ptLeptonH_vsPU_finalCuts_genMatched->Fill( leptonH.pt, candidates->numPV, eventWeight_ );
//
//      h.h_nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_all->Fill( candidates->numPV, eventWeight_ );
//      if ( cand.leptonIsoL/leptonL.pt < 0.1 ) h.h_nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_pass->Fill( candidates->numPV, eventWeight_ );
//      h.h_nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_all->Fill( candidates->numPV, eventWeight_ );
//      if ( cand.leptonIsoH/leptonH.pt < 0.1 ) h.h_nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_pass->Fill( candidates->numPV, eventWeight_ );
//    }
//  }
}


// Study analysis that uses collinearity rather than signing d0/sigma
void DileptonAnalyzer::studyCollinearity( TreeDipseudoLeptonCandidate &cand, TreeLepton & leptonL, TreeLepton & leptonH, double & mass,Histograms & h, bool fillCorrectedTextFiles ) {

  if ( cand.leptonD0SignificanceL_PVrefit_includingPVError != cand.leptonD0SignificanceL_PVrefit_includingPVError
      || cand.leptonD0SignificanceH_PVrefit_includingPVError != cand.leptonD0SignificanceH_PVrefit_includingPVError ) return;

  // Two selection criteria
  // One selects candidates with dPhi < 90 and one for dPhi > 90
  DileptonAnalysisCuts::PassedWhichCuts finalCollCuts = dileptonCuts_finalColl_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );
  DileptonAnalysisCuts::PassedWhichCuts looseCollCuts = dileptonCuts_looseColl_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );
  DileptonAnalysisCuts::PassedWhichCuts controlCollCuts = dileptonCuts_controlColl_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );
  DileptonAnalysisCuts::PassedWhichCuts looseControlCollCuts = dileptonCuts_looseControlColl_.whichCuts( cand, mass, leptonL, leptonH, anaType_, lxyScale_, d0Scale_ );

  // For signal MC, store candidates that pass all selection
  if ( isSignalMC_ ) {
    if ( dileptonCuts_finalColl_.passAllCuts( finalCollCuts ) ) {
      storeNumberOfExoticsRECO( cand, leptonL, leptonH, recoExotics_coll_oneSensitiveDecay_, recoExotics_coll_twoSensitiveDecay_ );

      // Efficiency histograms
      if ( isCentralCtau() && nSensitiveExoticDecayInEvent_==1 && eventWithinAcceptance( nSensitiveExoticDecayInEvent_ ) ) {

        unsigned int interestingLepton=getInterestingLepton();
        if ( ( interestingLepton == fabs(candidates->ll1_daughter1_PdgId) && interestingLepton == fabs(candidates->ll1_daughter2_PdgId) ) ) {
          h.h_recoExotics_coll_one_genLxy->Fill(candidates->ll1_decayLength2D, eventWeight_);
          if ( candidates->ll1_decayLength2D > 0 && candidates->ll1_decayLength2D < 50 ) h.h_recoExotics_coll_one_XPt->Fill(candidates->ll1_pt, eventWeight_);
        }
        else if ( ( interestingLepton == fabs(candidates->ll2_daughter1_PdgId) && interestingLepton == fabs(candidates->ll2_daughter2_PdgId) ) ) {
          h.h_recoExotics_coll_one_genLxy->Fill(candidates->ll2_decayLength2D, eventWeight_);
          if ( candidates->ll2_decayLength2D > 0 && candidates->ll2_decayLength2D < 50 ) h.h_recoExotics_coll_one_XPt->Fill(candidates->ll2_pt, eventWeight_);
        }
        h.h_recoExotics_coll_one_nRecoPV->Fill(candidates->numPV, eventWeight_);
      }
    }
    else if ( dileptonCuts_controlColl_.passAllCuts( controlCollCuts ) ) {
      storeNumberOfExoticsRECO( cand, leptonL, leptonH, recoExotics_coll_oneSensitiveDecay_negative_, recoExotics_coll_twoSensitiveDecay_negative_ );
    }
  }

  if ( isData_ ) {

    if ( unblind_ && dileptonCuts_finalColl_.passAllCuts( finalCollCuts ) ) {
      if ( fillCorrectedTextFiles ) {
        allCollCuts_corrected_ << mass << "\t" << cand.transverseMass << "\t" << cand.decayLength_PV << "\t" << cand.leptonD0SignificanceL_PVrefit_includingPVError << "\t" << cand.leptonD0SignificanceH_PVrefit_includingPVError << "\t" << eventWeight_ << "\t" << candidates->run << "\t" << candidates->lumi << "\t" << candidates->event << endl;
      }
      else {
        allCollCuts_ << mass << "\t" << cand.transverseMass << "\t" << cand.decayLength_PV << "\t" << cand.leptonD0SignificanceL_PVrefit_includingPVError << "\t" << cand.leptonD0SignificanceH_PVrefit_includingPVError << "\t" << eventWeight_ << "\t" << candidates->run << "\t" << candidates->lumi << "\t" << candidates->event << endl;
      }
    }
    else if ( dileptonCuts_controlColl_.passAllCuts( controlCollCuts ) ) {
      if ( fillCorrectedTextFiles ) {
        allCollCutsNegative_corrected_ << mass << "\t" << cand.transverseMass << "\t" << cand.decayLength_PV << "\t" << cand.leptonD0SignificanceL_PVrefit_includingPVError << "\t" << cand.leptonD0SignificanceH_PVrefit_includingPVError << "\t" << eventWeight_ << "\t" << candidates->run << "\t" << candidates->lumi << "\t" << candidates->event << endl;
      }
      else {
        allCollCutsNegative_ << mass << "\t" << cand.transverseMass << "\t" << cand.decayLength_PV << "\t" << cand.leptonD0SignificanceL_PVrefit_includingPVError << "\t" << cand.leptonD0SignificanceH_PVrefit_includingPVError << "\t" << eventWeight_ << "\t" << candidates->run << "\t" << candidates->lumi << "\t" << candidates->event << endl;
      }
    }
  }

  // Only fill histograms and cut flow for central ctau exotics
  // And for events where only one exotic decayed to chosen species
  if ( isSignalMC_ && !( isCentralCtau() && nSensitiveExoticDecayInEvent_ == 1 ) ) return;

  // Store cut flow for this analysis
  if ( passPrefilter() ) {
    if ( isSignalMC_ ) {
      // Also only consider correctly reco'd signal MC events
      if ( eventWithinAcceptance(nSensitiveExoticDecayInEvent_) && nSensitiveExoticDecayInEvent_ == 1
          && correctlyReconstructed( cand, leptonL, leptonH ) ) {
        monitorCutFlow( finalCollCuts, cutFlowMapColl_, eventWeight_ );
      }
    }
    else if ( isData_ ) {
      if ( fillCorrectedTextFiles ) monitorCutFlow( finalCollCuts, cutFlowMapColl_, eventWeight_ );
    }
    else monitorCutFlow( finalCollCuts, cutFlowMapColl_, eventWeight_ );
  }

  // Fill n-1 plots
  fillPlots( cand, leptonL, leptonH, mass, dileptonCuts_finalColl_, finalCollCuts, h.histMapFinalColl, false );
  fillPlots( cand, leptonL, leptonH, mass, dileptonCuts_looseColl_, looseCollCuts, h.histMapLooseColl, false );
  fillPlots( cand, leptonL, leptonH, mass, dileptonCuts_looseControlColl_, looseControlCollCuts, h.histMapLooseControlColl, false, true );

  if ( dileptonCuts_looseColl_.passAllCuts( looseCollCuts ) || dileptonCuts_looseControlColl_.passAllCuts( looseControlCollCuts ) ){
    // First plot collinearity for all candidates
    h.h_deltaPhi_removedLifetimeCollCuts->Fill( cand.dPhiCorr, eventWeight_ );
  }

  // Optimise isolation
  DileptonAnalysisCuts::PassedWhichCuts looseControlCollCuts_temp = looseControlCollCuts;
  looseControlCollCuts_temp.passIso = true;

  if ( dileptonCuts_looseControlColl_.passAllCuts( looseControlCollCuts_temp )) {
    h.h_nMinus1_relIso3_looseControlCollCuts->Fill(  max( cand.leptonIsoL/leptonL.pt, cand.leptonIsoH/leptonH.pt), eventWeight_ );
    h.h_nMinus1_relIso4_looseControlCollCuts->Fill(  max( cand.leptonIsoL4/leptonL.pt, cand.leptonIsoH4/leptonH.pt), eventWeight_ );
    h.h_nMinus1_relIso5_looseControlCollCuts->Fill( max( cand.leptonIsoL5/leptonL.pt, cand.leptonIsoH5/leptonH.pt), eventWeight_ );
  }


  // Note how many candidates pass each selection per event
  if ( dileptonCuts_finalColl_.passAllCuts( finalCollCuts ) ) {
    if ( fillCorrectedTextFiles || !isData_ ) ++nCandsPerEvent_final_;
    bestCandidateSoFar( cand, bestFinalSignalCand_);
  }
  if ( fillCorrectedTextFiles || !isData_ ) {

    if ( dileptonCuts_looseColl_.passAllCuts( looseCollCuts ) ) ++nCandsPerEvent_loose_;
    if ( dileptonCuts_controlColl_.passAllCuts( controlCollCuts ) ) ++nCandsPerEvent_control_;
    if ( dileptonCuts_looseControlColl_.passAllCuts( looseControlCollCuts ) ) ++nCandsPerEvent_looseControl_;
  }

  //
  // Fill d0/sigma plots
  //

  // Same criteria as above, but remove d0/sigma requriement
  DileptonAnalysisCuts::PassedWhichCuts finalCollCuts_removedLifetime = finalCollCuts;
  finalCollCuts_removedLifetime.passLeptonD0 = true;
  DileptonAnalysisCuts::PassedWhichCuts controlCollCuts_removedLifetime = controlCollCuts;
  controlCollCuts_removedLifetime.passLeptonD0 = true;

  fillPlots( cand, leptonL, leptonH, mass, dileptonCuts_controlColl_, controlCollCuts_removedLifetime, h.histMapControlColl, false );


  // Select candidates that pass removed lifetime collinearity cuts
  bool candPassVertex = ( finalCollCuts_removedLifetime.passVertexChi2 || controlCollCuts_removedLifetime.passVertexChi2 );
  if ( dileptonCuts_finalColl_.passAllCuts( finalCollCuts_removedLifetime ) || dileptonCuts_controlColl_.passAllCuts( controlCollCuts_removedLifetime ) ) {

    h.h_nMinus1_trigDeltaR_removedLifetimeCollCuts->Fill( max( leptonL.tmDeltaR, leptonH.tmDeltaR));
    h.h_nMinus1_photonDeltaR_removedLifetimeCollCuts->Fill( max( leptonL.pmDeltaR, leptonH.pmDeltaR));

    // Study the tracker misalignment
    // Only for data
    if ( isData_ ) {
      // No requirement on d0/sigma size or sign
      // No requirement on vertex chi2, but can be reapplied using bool
      studyTrackD0Misalignment(cand, leptonL, leptonH, candPassVertex, h);
      studyTrackZ0Misalignment(cand, leptonL, leptonH, candPassVertex, h);
    }

    // Find the smallest d0/sigma of this candidate
    double minD0 = min( fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError), fabs(cand.leptonD0SignificanceH_PVrefit_includingPVError) );

    // Select candidates in signal region
    if ( dileptonCuts_finalColl_.passAllCuts( finalCollCuts_removedLifetime ) ) {

      if ( isSignalMC_ ) {
        if ( isCentralCtau() && nSensitiveExoticDecayInEvent_==1 && eventWithinAcceptance( nSensitiveExoticDecayInEvent_ ) ) {

          unsigned int interestingLepton=getInterestingLepton();
          if ( ( interestingLepton == fabs(candidates->ll1_daughter1_PdgId) && interestingLepton == fabs(candidates->ll1_daughter2_PdgId) ) ) {
            h.h_recoExoticsRemovedLifetime_coll_one_genLxy->Fill(candidates->ll1_decayLength2D, eventWeight_);
          }
          else if ( ( interestingLepton == fabs(candidates->ll2_daughter1_PdgId) && interestingLepton == fabs(candidates->ll2_daughter2_PdgId) ) ) {
            h.h_recoExoticsRemovedLifetime_coll_one_genLxy->Fill(candidates->ll2_decayLength2D, eventWeight_);
          }
        }
      }

      // Is this the best candidate in signal region so far?
      bestCandidateSoFar( cand, bestSignalCand_ );
      if ( ( isData_ && fillCorrectedTextFiles ) || !isData_ ) ++nCandsPerEvent_deltaPhiL90_;

      h.h_minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );

      // Fill version where d0 signed using delta phi
      // Convenient for later
      h.h_minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );

      // Fill blinded version
      if ( ( anaType_==_2eTrack && minD0 < 6 ) || ( ( anaType_==_2muTrack || anaType_ == _2globalOrTrackerMu ) && minD0 < 4 ) ) {
        h.h_minLeptonAbsD0Sig_deltaPhiL90_forFittingData_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
        h.h_minLeptonD0Sig_signedWrtDeltaPhi_forFittingData_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      }
      // Mass
      h.h_mass_removedLifetime_CollCuts->Fill( mass, eventWeight_ );
    }
    // Select candidates in control region
    else if ( dileptonCuts_controlColl_.passAllCuts( controlCollCuts_removedLifetime ) ) {

      // Is this the best candidate in control region so far?
      bestCandidateSoFar( cand, bestControlCand_ );
      if ( ( isData_ && fillCorrectedTextFiles ) || !isData_ ) ++nCandsPerEvent_deltaPhiG90_;

      h.h_minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );

      // Same plots for different track iterations
      // Plot for different tracking algorithms
      float trackingAlgo = ( minD0 == fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError )) ? leptonL.algo : leptonH.algo;
      if ( trackingAlgo==4 ) h.h_minLeptonAbsD0Sig_deltaPhiG90_algo4_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      else if ( trackingAlgo==5 ) h.h_minLeptonAbsD0Sig_deltaPhiG90_algo5_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      else if ( trackingAlgo==6 ) h.h_minLeptonAbsD0Sig_deltaPhiG90_algo6_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      else if ( trackingAlgo==7 ) h.h_minLeptonAbsD0Sig_deltaPhiG90_algo7_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      else if ( trackingAlgo==8 ) h.h_minLeptonAbsD0Sig_deltaPhiG90_algo8_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      else if ( trackingAlgo==9 ) h.h_minLeptonAbsD0Sig_deltaPhiG90_algo9_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      else if ( trackingAlgo==10 ) h.h_minLeptonAbsD0Sig_deltaPhiG90_algo10_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );

      h.h_minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
      h.h_minLeptonD0Sig_signedWrtDeltaPhi_forFittingData_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );

      // Show this distribution before PV refit
      // To show improvement after refitting vertex
      if ( cand.leptonD0SignificanceL_PV_includingPVError == cand.leptonD0SignificanceL_PV_includingPVError &&
          cand.leptonD0SignificanceH_PV_includingPVError == cand.leptonD0SignificanceH_PV_includingPVError ) {
        double minD0_PVnorefit = min( fabs(cand.leptonD0SignificanceL_PV_includingPVError), fabs(cand.leptonD0SignificanceH_PV_includingPVError) );
        h.h_minLeptonAbsD0Sig_PVnorefit_controlCollCuts->Fill( minD0_PVnorefit, eventWeight_ );
      }
      // Mass
      h.h_mass_removedLifetime_controlCollCuts->Fill( mass, eventWeight_ );
    }

    // Get alternative control region by changing deltaPhi definition

    //control distribution, first re-calculate dPhiCorr with sign
    TVector3 leptonVertex( cand.vx, cand.vy, cand.vz );
    TVector3 primaryVertex( candidates->pv_x, candidates->pv_y, candidates->pv_z );
    TVector3 vertexDir = leptonVertex - primaryVertex;
    TLorentzVector totalMom;
    totalMom.SetPtEtaPhiM(cand.ptCorr,cand.etaCorr,cand.phiCorr,cand.corrDileptonMass);
    double dPhiCorrSigned = deltaPhi<TVector3, TLorentzVector>(vertexDir, totalMom);

    // Same variable as before, but signed
    // |deltaPhi| < 90 signal, |deltaPhi| > 90 background
    h.h_deltaPhiSigned_removedLifetimeCollCuts->Fill( dPhiCorrSigned, eventWeight_ );

    // "Perp" equivalent
    // deltaPhi > 0 and deltaPhi < 0 are the two regions
    // Background and signal symmetric
    if ( dPhiCorrSigned <= 0. ) {
      h.h_minLeptonAbsD0Sig_deltaPhiMinus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      h.h_minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
      bestCandidateSoFar( cand, bestL0Cand_ );

    }
    else {
      h.h_minLeptonAbsD0Sig_deltaPhiPlus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      h.h_minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      bestCandidateSoFar( cand, bestG0Cand_ );
    }

    // PU Systematic Plot
    h.h_nRecoPV_removedLifetimeCollCuts->Fill( candidates->numPV, eventWeight_ );
    // Plot nPV with systematic variations
    // Calculate different event weight with different pu weight
    double puP5weight = puweights_p5_.weight( candidates->nvtx_true );
    double puM5weight = puweights_m5_.weight( candidates->nvtx_true );
    h.h_nRecoPV_p5_removedLifetimeCollCuts->Fill(candidates->numPV, puP5weight * xsecWeight_ );
    h.h_nRecoPV_m5_removedLifetimeCollCuts->Fill(candidates->numPV, puM5weight * xsecWeight_ );
  }

//  // Similar selection, but also remove isolation
//  // n-1 (for isolation)
//  finalCollCuts_removedLifetime = finalCollCuts;
//  finalCollCuts_removedLifetime.passLeptonD0 = true;
//  finalCollCuts_removedLifetime.passIso = true;
//  controlCollCuts_removedLifetime = controlCollCuts;
//  controlCollCuts_removedLifetime.passLeptonD0 = true;
//  controlCollCuts_removedLifetime.passIso = true;
//  if ( dileptonCuts_finalColl_.passAllCuts( finalCollCuts_removedLifetime ) || dileptonCuts_controlColl_.passAllCuts( controlCollCuts_removedLifetime ) ) {
//    h.h_nMinus1_relIsolationLeptonL_removedLifetimeCollCuts->Fill( cand.leptonIsoL/leptonL.pt, eventWeight_ );
//    h.h_nMinus1_relIsolationLeptonH_removedLifetimeCollCuts->Fill( cand.leptonIsoH/leptonH.pt, eventWeight_ );
//  }

  // Extra isolation plots
  // Correctly reco'd signal MC candidates for central ctau exotics
  if ( isSignalMC_ && correctlyReconstructed( cand, leptonL, leptonH ) && isCentralCtau() ) {

    DileptonAnalysisCuts::PassedWhichCuts finalCollCutsTemp = finalCollCuts;
    finalCollCutsTemp.passIso = true;

    if (  dileptonCuts_finalColl_.passAllCuts( finalCollCutsTemp )  ) {

      double leptonIsoL=0;
      double leptonIsoH=0;
      whichIso(cand, leptonIsoL, leptonIsoH);

      h.h_nMinus1_relIsolationLeptonL_vsPU_finalCollCuts_genMatched->Fill( leptonIsoL/leptonL.pt, candidates->numPV, eventWeight_ );
      h.h_nMinus1_relIsolationLeptonH_vsPU_finalCollCuts_genMatched->Fill( leptonIsoH/leptonH.pt, candidates->numPV, eventWeight_ );

      h.h_nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_all->Fill( candidates->numPV, eventWeight_ );
      if ( leptonIsoL/leptonL.pt < 0.1 ) h.h_nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_pass->Fill( candidates->numPV, eventWeight_ );
      h.h_nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_all->Fill( candidates->numPV, eventWeight_ );
      if ( leptonIsoH/leptonH.pt < 0.1 ) h.h_nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_pass->Fill( candidates->numPV, eventWeight_ );
    }
  }
}



// Function which does most of studies of candidate
void DileptonAnalyzer::studyCandidate( TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , Histograms & h, bool fillCorrectedTextFiles ) {

  // Use this if you just want to use correctly reco'd signal candidates (use gen info)
  //  if ( isSignalMC_ && !correctlyReconstructed(cand) ) return;

  // Choose appropiate mass to plot
  double mass = whichMass( cand );

  if ( isSignalMC_ && isCentralCtau() &&
      // Event passes prefilter
      passPrefilter() &&
      // Event is within acceptance at generator level and only one interesting exotic
      eventWithinAcceptance( nSensitiveExoticDecayInEvent_) && nSensitiveExoticDecayInEvent_ == 1 &&
      correctlyReconstructed( cand, leptonL, leptonH ) ) {
    // For cut flow
    // Only interested in case when one exotics decays to chosen species
    nCorrectlyRecoExoticsBeforePrefilter_+=eventWeight_;
    atLeastOneCandInAcceptance_=true;
  }

  //
  // D0 Signing Method
  //
  // All this does is fill bias in d0 and z0 plots.  Suggest to move into studyCollinearity
//  studyD0Signing( cand, leptonL, leptonH, mass, h, fillCorrectedTextFiles);

  //
  // Collinearity methods
  //
  studyCollinearity( cand, leptonL, leptonH, mass, h, fillCorrectedTextFiles );


}

// Function to fill all plots which are common between each set of cuts e.g. n-1 plots
void DileptonAnalyzer::fillPlots( const TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , const double mass, DileptonAnalysisCuts & cuts, const DileptonAnalysisCuts::PassedWhichCuts & passedWhichCuts, map< TString, TH1F* > & histMap, bool isFinalCuts, bool debug ) {
  //
  // n-1 plots
  //

  DileptonAnalysisCuts::PassedWhichCuts cutsTemp = passedWhichCuts;

  // Chi^2
  cutsTemp = passedWhichCuts;
  cutsTemp.passVertexChi2 = true;
  if ( cuts.passAllCuts( cutsTemp ) ) {
    histMap["vertexChi2"]->Fill( cand.vertexChi2, eventWeight_);
  }

  // Opposite charge
  cutsTemp = passedWhichCuts;
  cutsTemp.passOppCharge = true;

  if (  cuts.passAllCuts( cutsTemp )  ) {
    int leptonCharge = ( leptonL.charge * leptonH.charge > 0 ) ? 1 : -1 ;
    histMap["oppositeCharge"]->Fill( leptonCharge, eventWeight_);
  }

  // dPhi
  cutsTemp = passedWhichCuts;
  cutsTemp.passDeltaPhi = true;

  if (  cuts.passAllCuts( cutsTemp )  ) {
    histMap["deltaPhi"]->Fill( cand.dPhiCorr, eventWeight_);
  }

  // cosine
  cutsTemp = passedWhichCuts;
  cutsTemp.passCosine = true;

  if (  cuts.passAllCuts( cutsTemp )  ) {
    histMap["cosine"]->Fill( cand.cosine, eventWeight_);
  }

  // delta R
  cutsTemp = passedWhichCuts;
  cutsTemp.passDeltaR = true;

  if (  cuts.passAllCuts( cutsTemp )  ) {
    histMap["deltaR"]->Fill( cand.deltaR, eventWeight_);
  }

  // # Hits Before Vertex
  cutsTemp = passedWhichCuts;
  cutsTemp.passHitsBeforeVertex = true;

  if (  cuts.passAllCuts( cutsTemp )  ) {
    histMap["nHitsBeforeVertex"]->Fill( cand.hitsBeforeVertexL + cand.hitsBeforeVertexH, eventWeight_);
  }

  if ( debug ) {
    cutsTemp = passedWhichCuts;
    cutsTemp.passMissingHitsAfterVertex = true;
    cutsTemp.passLeptonD0 = true;
    if (  cuts.passAllCuts( cutsTemp )  ) {

      double minD0 = min( fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError), fabs(cand.leptonD0SignificanceH_PVrefit_includingPVError) );
      if ( minD0 == minD0 ) {
        float trackingAlgo = ( minD0 == fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError )) ? leptonL.algo : leptonH.algo;
        if ( trackingAlgo==10 ) {
          histMap["d0SigmaNoMissingHits"]->Fill( minD0, eventWeight_ );
        }
      }
    }
  }

  // # missing hits after vertex
  cutsTemp = passedWhichCuts;
  cutsTemp.passMissingHitsAfterVertex = true;

  if (  cuts.passAllCuts( cutsTemp )  ) {
    histMap["nMissingHitsAfterVertex"]->Fill( cand.missedLayersAfterVertexL + cand.missedLayersAfterVertexH, eventWeight_ );
    cout << endl << cand.missedLayersAfterVertexL + cand.missedLayersAfterVertexH << endl;
    cout << cand.leptonIsoL/leptonL.pt << " " << cand.leptonIsoH/leptonH.pt << endl;
    cout << cand.leptonIsoL4/leptonL.pt << " " << cand.leptonIsoH4/leptonH.pt << endl;

    histMap["minMissingHitsAfterVertex"]->Fill( min(cand.missedLayersAfterVertexL,  cand.missedLayersAfterVertexH), eventWeight_ );
    histMap["maxMissingHitsAfterVertex"]->Fill( max(cand.missedLayersAfterVertexL, cand.missedLayersAfterVertexH), eventWeight_ );

//    if ( cand.missedLayersAfterVertexL + cand.missedLayersAfterVertexH > 8 ) {
//
//      histMap["ptOverE"]->Fill(leptonL.pt/leptonL.photonEt, eventWeight_);
//      histMap["ptOverE"]->Fill(leptonH.pt/leptonH.photonEt, eventWeight_);
//      histMap["ptMinusE"]->Fill(fabs(1/leptonL.photonEt - 1/leptonL.pt), eventWeight_);
//      histMap["ptMinusE"]->Fill(fabs(1/leptonH.photonEt - 1/leptonH.pt), eventWeight_);
//      float minD0 = getMinD0( cand );
//      float maxD0 = getMaxD0( cand, minD0 );
//      int algo = ( minD0 == cand.leptonD0SignificanceL_PVrefit_includingPVError ) ? leptonL.algo : leptonH.algo;
//      histMap["TrackingAlgo"]->Fill( algo, eventWeight_ );
//
//      cout << endl << "Candidate with large number of missing hits in total" << endl;
//      cout << "Lepton L has "<< cand.missedLayersAfterVertexL << " and lepton H has" << cand.missedLayersAfterVertexH << endl;
//      cout << "Lxy : " << cand.decayLength_PV << endl;
//      cout << "Lxy/sigma : " << cand.decayLengthSignificance_PV << endl;
//      cout << "--------" << endl;
//      cout << "Lepton L" << endl;
//      cout << "--------" << endl;
//      cout << "Track reco algo : " << leptonL.algo << endl;
//      cout << "Chi2 : " << leptonL.trackChi2 << endl;
//      cout << "nLayers : " << leptonL.nLayers << endl;
//      cout << "nLayers3D : " << leptonL.nLayers3D << endl;
//      cout << "Track eta, phi : " << leptonL.eta << " " << leptonL.phi << endl;
//      cout << "Track pt : " <<  leptonL.pt << endl;
//      cout << "Matched photon eta, phi : " << leptonL.photonEta << " " << leptonL.photonPhi << endl;
//      cout << "Matched photon Et : " << leptonL.photonEt << endl;
//      cout << "Rel iso : " << cand.leptonIsoL/leptonL.pt << endl;
//      cout << "--------" << endl;
//      cout << "Lepton H" << endl;
//      cout << "--------" << endl;
//      cout << "Track reco algo : " << leptonH.algo << endl;
//      cout << "Chi2 : " << leptonH.trackChi2 << endl;
//      cout << "nLayers : " << leptonH.nLayers << endl;
//      cout << "nLayers3D : " << leptonH.nLayers3D << endl;
//      cout << "Track eta, phi : " << leptonH.eta << " " << leptonH.phi << endl;
//      cout << "Track pt : " <<  leptonH.pt << endl;
//      cout << "Matched photon eta, phi : " << leptonH.photonEta << " " << leptonH.photonPhi << endl;
//      cout << "Matched photon Et : " << leptonH.photonEt << endl;
//      cout << "Rel iso : " << cand.leptonIsoH/leptonH.pt << endl;
//
//      // Is there another track with small delta R to this track?
//      for ( unsigned int iTreeLepton=0; iTreeLepton != candidates->leptons_.size(); ++iTreeLepton ) {
//
//        TreeLepton lepton = candidates->leptons_.at(iTreeLepton);
//        double dp=std::abs(leptonL.phi-lepton.phi);
//        if (dp>TMath::Pi()) dp-=2*TMath::Pi();
//        double deltaR=sqrt((leptonL.eta-lepton.eta)*(leptonL.eta-lepton.eta) + dp*dp);
//
//        if ( deltaR < 0.03 && deltaR > 0 ) {
//          cout << "===== Found another lepton close to lepton L, delta R : " << deltaR << endl;
//          cout << "Pt, eta, phi : " << lepton.pt << " " << lepton.eta << " " << lepton.phi << endl;
//          cout << "Track reco algo : " << lepton.algo << endl;
//          cout << "NLayers : " << lepton.nLayers << " 3D layers :" << lepton.nLayers3D << endl;
//          cout << "Matched photon Et : " << lepton.photonEt << endl;
//
////          for( unsigned int iTreeCand=0; iTreeCand != candidates->candidates_.size(); ++iTreeCand ) {
////
////            TreeDipseudoLeptonCandidate c = candidates->candidates_.at(iTreeCand);
////
////            // Get leptons corresponding to this candidate
////            TreeLepton lL = getLepton( c.leptonIndexL );
////            TreeLepton lH = getLepton( c.leptonIndexH );
////
////            // Check what type of leptons make up this candidate
////            // Make sure they are relevant to this analysis
////            if ( !correctLeptonsInCandidate(c, lL, lH ) ) continue;
////
////            if ( lL.pt == lepton.pt || lH.pt == lepton.pt ) {
////              cout << "This lepton used in other candidate" << endl;
////            }
////          }
//        }
//
//        dp=std::abs(leptonH.phi-lepton.phi);
//        if (dp>TMath::Pi()) dp-=2*TMath::Pi();
//        deltaR=sqrt((leptonH.eta-lepton.eta)*(leptonH.eta-lepton.eta) + dp*dp);
//
//        if ( deltaR < 0.03 && deltaR > 0 ) {
//          cout << "===== Found another lepton close to lepton H, delta R : " << deltaR << endl;
//          cout << "Pt, eta, phi : " << lepton.pt << " " << lepton.eta << " " << lepton.phi << endl;
//          cout << "Track reco algo : " << lepton.algo << endl;
//          cout << "NLayers : " << lepton.nLayers << " 3D layers :" << lepton.nLayers3D << endl;
//          cout << "Matched photon Et : " << lepton.photonEt << endl;
//
////          for( unsigned int iTreeCand=0; iTreeCand != candidates->candidates_.size(); ++iTreeCand ) {
////
////            TreeDipseudoLeptonCandidate c = candidates->candidates_.at(iTreeCand);
////
////            // Get leptons corresponding to this candidate
////            TreeLepton lL = getLepton( c.leptonIndexL );
////            TreeLepton lH = getLepton( c.leptonIndexH );
////
////            // Check what type of leptons make up this candidate
////            // Make sure they are relevant to this analysis
////            if ( !correctLeptonsInCandidate(c, lL, lH ) ) continue;
////
////            if ( lL.pt == lepton.pt || lH.pt == lepton.pt ) {
////              cout << "This lepton used in other candidate" << endl;
////            }
////          }
//        }
//      }
//
//      //
//      //
//      ////        cout << "pt/E : " << leptonL.pt/leptonL.photonEt << " " << leptonH.pt/leptonH.photonEt << endl;
//      //
//      ////        cout << endl << "Event weight : " << eventWeight_ << endl;
//      ////        cout << "Run, lumi, event : " << candidates->run << " " << candidates->lumi << " " << candidates->event << endl;
//      ////        cout << "Lepton L" << endl;
//      ////        cout << "valid track : " << leptonL.validTrack << endl;
//      ////        cout << "Chi2 : " << leptonL.trackChi2 << endl;
//      ////        cout << "algo : " << leptonL.algo << endl;
//      ////        cout << "nLayers : " << leptonL.nLayers << endl;
//      ////        cout << "nLayers3D : " << leptonL.nLayers3D << endl;
//      ////        cout << "tip : " << leptonL.tip << endl;
//      ////        cout << "lip : " << leptonL.lip << endl;
//      ////        cout << "highPurity : " << leptonL.highPurity << endl;
//      ////        cout << "Missing hits : " << cand.missedLayersAfterVertexL << endl;
//      ////        cout << "Extra hits : " << cand.hitsBeforeVertexL << endl;
//      ////        cout << "Lepton H" << endl;
//      ////        cout << "valid track : " << leptonH.validTrack << endl;
//      ////        cout << "Chi2 : " << leptonH.trackChi2 << endl;
//      ////        cout << "algo : " << leptonH.algo << endl;
//      ////        cout << "nLayers : " << leptonH.nLayers << endl;
//      ////        cout << "nLayers3D : " << leptonH.nLayers3D << endl;
//      ////        cout << "tip : " << leptonH.tip << endl;
//      ////        cout << "lip : " << leptonH.lip << endl;
//      ////        cout << "highPurity : " << leptonH.highPurity << endl;
//      ////        cout << "Missing hits : " << cand.missedLayersAfterVertexH << endl;
//      ////        cout << "Extra hits : " << cand.hitsBeforeVertexH << endl;
//    }
  }

  // d0/sigma
  // Only interesting for final cuts
  if ( isFinalCuts ) {

    // smallest d0/sigma of the two leptons
    cutsTemp = passedWhichCuts;
    cutsTemp.passLeptonD0 = true;

    if (  cuts.passAllCuts( cutsTemp )  ) {
      float minD0 = getMinD0( cand );
      float maxD0 = getMaxD0( cand, minD0 );

      // Check for NAN...
      if ( minD0 == minD0 ) {
        // This plot should be identical to the d0 plot produced in the removed lifetime section
        // Good cross check!
        histMap["leptonD0Sig"]->Fill( minD0, eventWeight_ );
        histMap["leptonD0SigMax"]->Fill( maxD0, eventWeight_ );
      }
    }

    // Sign of d0/sigma
    // Remove requirement on d0 magnitude also
    cutsTemp.passOppSignD0 = true;
    if (  cuts.passAllCuts( cutsTemp )  ) {
      int sameSign = ( cand.leptonD0SignificanceL_PVrefit_includingPVError * cand.leptonD0SignificanceH_PVrefit_includingPVError ) > 0 ? 1 : -1 ;
      histMap["leptonD0SigSameSign"]->Fill( sameSign, eventWeight_ );

      // Make a few plots for candidates with opposite sign d0
      if ( sameSign == -1 ) {
        float minD0 = getMinD0( cand );
        float maxD0 = getMaxD0( cand, minD0 );
        if ( minD0 == minD0 && maxD0 == maxD0 ) {
          histMap["leptonAbsD0Sig_oppositeSignMin"]->Fill( fabs(minD0), eventWeight_ );
          histMap["leptonD0Sig_oppositeSignMin"]->Fill( minD0, eventWeight_ );
          histMap["leptonD0Sig_oppositeSignMax"]->Fill( maxD0, eventWeight_ );
        }
      }
    }
  }

  // Calo match delta R (largest of two leptons)
  cutsTemp = passedWhichCuts;
  cutsTemp.passCaloMatch = true; // Shouldn't do anything at the moment.  Cut at deltaR < 0.2, which is very loose and applied in Tree Producer anyway.
  if (  cuts.passAllCuts( cutsTemp )  ) {
    histMap["caloMatchDeltaR"]->Fill( max(leptonL.cmDeltaR,leptonH.cmDeltaR), eventWeight_ );
  }

  // Track pt cut
  cutsTemp = passedWhichCuts;
  cutsTemp.passTrackPt = true;
  if (  cuts.passAllCuts( cutsTemp )  ) {
    if ( anaType_==_2eTrack ) {
      // In electron channel, the leading lepton is the one with the largest SC Et, not the largest track pt
      if ( leptonH.photonEt >= leptonL.photonEt ) {
        histMap["leadingTrackpt"]->Fill(leptonH.pt,eventWeight_);
        histMap["subleadingTrackpt"]->Fill(leptonL.pt,eventWeight_);
      }
      else {
        histMap["leadingTrackpt"]->Fill(leptonL.pt,eventWeight_);
        histMap["subleadingTrackpt"]->Fill(leptonH.pt,eventWeight_);
      }
    }
    else {
      histMap["leadingTrackpt"]->Fill(max(leptonL.pt,leptonH.pt),eventWeight_);
      histMap["subleadingTrackpt"]->Fill(min(leptonL.pt,leptonH.pt),eventWeight_);
    }
  }

  // SC Et cut
  cutsTemp = passedWhichCuts;
  cutsTemp.passSCEt = true;
  if (  cuts.passAllCuts( cutsTemp )  ) {
    histMap["leadingSCEt"]->Fill(max(leptonL.photonEt,leptonH.photonEt), eventWeight_);
    histMap["subleadingSCEt"]->Fill(min(leptonL.photonEt,leptonH.photonEt), eventWeight_);
  }

  // Isolation
  // All
  cutsTemp = passedWhichCuts;
  cutsTemp.passIso = true;

  if (  cuts.passAllCuts( cutsTemp )  ) {
    double leptonIsoL=0;
    double leptonIsoH=0;
    whichIso(cand, leptonIsoL, leptonIsoH);

    histMap["absIso"]->Fill( max(leptonIsoL,leptonIsoH), eventWeight_ );
    histMap["relIso"]->Fill( max( leptonIsoL/leptonL.pt, leptonIsoH/leptonH.pt), eventWeight_ );
  }

  // Photon ID
  cutsTemp = passedWhichCuts;
  cutsTemp.passPhotonID = true;

  if (  cuts.passAllCuts( cutsTemp )  ) {
    histMap["photonR9"]->Fill( min( leptonL.photonR9, leptonH.photonR9), eventWeight_ );
    if ( fabs( leptonL.photonEta ) < 1.55 ) histMap["photonSigmaIetaIeta_barrel"]->Fill( leptonL.photonSigmaIetaIeta, eventWeight_ );
    else histMap["photonSigmaIetaIeta_endcap"]->Fill( leptonL.photonSigmaIetaIeta, eventWeight_ );
    if ( fabs( leptonH.photonEta ) < 1.55 ) histMap["photonSigmaIetaIeta_barrel"]->Fill( leptonH.photonSigmaIetaIeta, eventWeight_ );
    else histMap["photonSigmaIetaIeta_endcap"]->Fill( leptonH.photonSigmaIetaIeta, eventWeight_ );
    histMap["photonHadTowOverEm"]->Fill( max( leptonL.photonHadTowOverEm, leptonH.photonHadTowOverEm), eventWeight_ );
    histMap["photonHadronicOverEm"]->Fill( max( leptonL.photonHadronicOverEm, leptonH.photonHadronicOverEm), eventWeight_ );
  }

  // Plots after applying all selection requirements (for this set of cuts)
  if ( cuts.passAllCuts( passedWhichCuts ) ) {
    //
    // These candidates have passed all selection criteria
    //
    histMap["mass"]->Fill( mass, eventWeight_ );
    histMap["mt"]->Fill( cand.transverseMass, eventWeight_ );
    histMap["Lxy"]->Fill( cand.decayLength_PV, eventWeight_ );
    histMap["nRecoPV"]->Fill(candidates->numPV, eventWeight_ );


    float minD0 = getMinD0( cand );
    float maxD0 = getMaxD0( cand, minD0 );
    //    int algo = ( minD0 == cand.leptonD0SignificanceL_PVrefit_includingPVError ) ? leptonL.algo : leptonH.algo;
    //    histMap["TrackingAlgo"]->Fill( algo, eventWeight_ );

    histMap["leptonD0SigMin_allCuts"]->Fill(minD0, eventWeight_);
    histMap["leptonD0SigMax_allCuts"]->Fill( maxD0, eventWeight_ );
  }
}

void DileptonAnalyzer::storeNumberOfCandsPerEvent( Histograms &h ) {

  h.histMapFinalColl["nCandsPerEvent"]->Fill( nCandsPerEvent_final_, eventWeight_ );
  h.histMapLooseColl["nCandsPerEvent"]->Fill( nCandsPerEvent_loose_, eventWeight_ );
  h.histMapControlColl["nCandsPerEvent"]->Fill( nCandsPerEvent_control_, eventWeight_ );
  h.histMapLooseControlColl["nCandsPerEvent"]->Fill( nCandsPerEvent_looseControl_, eventWeight_ );

  h.h_nCandsPerEvent_deltaPhiG90_removedLifetimeCollCuts->Fill( nCandsPerEvent_deltaPhiG90_, eventWeight_ );
  h.h_nCandsPerEvent_deltaPhiL90_removedLifetimeCollCuts->Fill( nCandsPerEvent_deltaPhiL90_, eventWeight_ );

  // Reset counters
  nCandsPerEvent_final_=0;
  nCandsPerEvent_loose_=0;
  nCandsPerEvent_control_=0;
  nCandsPerEvent_looseControl_=0;
  nCandsPerEvent_deltaPhiG90_=0;
  nCandsPerEvent_deltaPhiL90_=0;
}

TreeDipseudoLeptonCandidate& DileptonAnalyzer::largestD0Cand( TreeDipseudoLeptonCandidate& cand1, TreeDipseudoLeptonCandidate& cand2 ) {
  // Need to find new control candidate
  double minD0BestCand1 = min( fabs(cand1.leptonD0SignificanceL_PVrefit_includingPVError), fabs(cand1.leptonD0SignificanceH_PVrefit_includingPVError) );
  double maxD0BestCand1 = max( fabs(cand1.leptonD0SignificanceL_PVrefit_includingPVError), fabs(cand1.leptonD0SignificanceH_PVrefit_includingPVError) );

  double minD0BestCand2 = min( fabs(cand2.leptonD0SignificanceL_PVrefit_includingPVError), fabs(cand2.leptonD0SignificanceH_PVrefit_includingPVError) );
  double maxD0BestCand2 = max( fabs(cand2.leptonD0SignificanceL_PVrefit_includingPVError), fabs(cand2.leptonD0SignificanceH_PVrefit_includingPVError) );

  if ( minD0BestCand1 > minD0BestCand2 ) {
    return cand1;
  }
  else if ( minD0BestCand2 > minD0BestCand1 ) {
    return cand2;
  }
  else {
    if ( maxD0BestCand1 > maxD0BestCand2 ) {
      return cand1;
    }
    else {
      return cand2;
    }
  }
}

void DileptonAnalyzer::bestCandidateSoFar( TreeDipseudoLeptonCandidate& cand, TreeDipseudoLeptonCandidate*& currentBestCand ) {
  if ( currentBestCand == 0 ) {
    currentBestCand = &cand;
  }
  else {
    currentBestCand = &( largestD0Cand(cand, *currentBestCand ));
  }
}

void DileptonAnalyzer::plotBestCandidates( bool isCorrectedDataCand ){

  // Plot d0/sigma of best candidate in event
  if ( !(bestSignalCand_==0) ) {
    double minD0 = min( fabs(bestSignalCand_->leptonD0SignificanceL_PVrefit_includingPVError), fabs(bestSignalCand_->leptonD0SignificanceH_PVrefit_includingPVError) );
    if ( isData_ && isCorrectedDataCand ){
      histsCorrected_.h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      histsCorrected_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      if ( ( anaType_==_2eTrack && minD0 < 6 ) || ( ( anaType_==_2muTrack || anaType_ == _2globalOrTrackerMu ) && minD0 < 4 ) ) {
        histsCorrected_.h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_forFittingData_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
        histsCorrected_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      }
    }
    else if ( isDitauEvent() ) {
      histsTau_.h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      histsTau_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );

      if ( ( anaType_==_2eTrack && minD0 < 6 ) || ( ( anaType_==_2muTrack || anaType_ == _2globalOrTrackerMu ) && minD0 < 4 ) ) {
        histsTau_.h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_forFittingData_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
        histsTau_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      }
    }
    else {
      hists_.h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      hists_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      if ( ( anaType_==_2eTrack && minD0 < 6 ) || ( ( anaType_==_2muTrack || anaType_ == _2globalOrTrackerMu ) && minD0 < 4 ) ) {
        hists_.h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_forFittingData_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
        hists_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      }
    }
  }

  // Plot best final candidates
  if ( bestFinalSignalCand_ != 0 ) {
    double mass = whichMass( *bestFinalSignalCand_ );
    if ( isData_ && isCorrectedDataCand ){
      histsCorrected_.h_mass_bestCand_finalCollCuts->Fill( mass, eventWeight_ );
      histsCorrected_.h_Lxy_bestCand_finalCollCuts->Fill( bestFinalSignalCand_->decayLength_PV, eventWeight_ );
    }
    else if ( isDitauEvent() ) {
      histsTau_.h_mass_bestCand_finalCollCuts->Fill( mass, eventWeight_ );
      histsTau_.h_Lxy_bestCand_finalCollCuts->Fill( bestFinalSignalCand_->decayLength_PV, eventWeight_ );
    }
    else {
      hists_.h_mass_bestCand_finalCollCuts->Fill( mass, eventWeight_ );
      hists_.h_Lxy_bestCand_finalCollCuts->Fill( bestFinalSignalCand_->decayLength_PV, eventWeight_ );
    }
  }

  if ( !(bestControlCand_==0) ) {
    double minD0 = min( fabs(bestControlCand_->leptonD0SignificanceL_PVrefit_includingPVError), fabs(bestControlCand_->leptonD0SignificanceH_PVrefit_includingPVError) );
    if ( isData_ && isCorrectedDataCand ) {
      histsCorrected_.h_minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      histsCorrected_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
      histsCorrected_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );

    }
    else if ( isDitauEvent() ) {
      histsTau_.h_minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      histsTau_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
      histsTau_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
    }
    else {
      hists_.h_minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      hists_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
      hists_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
    }
  }

  if ( !(bestL0Cand_==0) ) {
    double minD0 = min( fabs(bestL0Cand_->leptonD0SignificanceL_PVrefit_includingPVError), fabs(bestL0Cand_->leptonD0SignificanceH_PVrefit_includingPVError) );
    if ( isData_ && isCorrectedDataCand ) {
      histsCorrected_.h_minLeptonAbsD0Sig_bestCand_deltaPhiMinus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      histsCorrected_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
    }
    else if ( isDitauEvent() ) {
      histsTau_.h_minLeptonAbsD0Sig_bestCand_deltaPhiMinus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      histsTau_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
    }
    else {
      hists_.h_minLeptonAbsD0Sig_bestCand_deltaPhiMinus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      hists_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts->Fill( -1.0 * minD0, eventWeight_ );
    }
  }

  if ( !(bestG0Cand_==0) ) {
    double minD0 = min( fabs(bestG0Cand_->leptonD0SignificanceL_PVrefit_includingPVError), fabs(bestG0Cand_->leptonD0SignificanceH_PVrefit_includingPVError) );
    if ( isData_ && isCorrectedDataCand ) {
      histsCorrected_.h_minLeptonAbsD0Sig_bestCand_deltaPhiPlus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      histsCorrected_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
    }
    else if ( isDitauEvent() ) {
      histsTau_.h_minLeptonAbsD0Sig_bestCand_deltaPhiPlus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      histsTau_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
    }
    else {
      hists_.h_minLeptonAbsD0Sig_bestCand_deltaPhiPlus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
      hists_.h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts->Fill( minD0, eventWeight_ );
    }
  }
}

void DileptonAnalyzer::studyTrackD0Misalignment( const TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , const bool passVertex, Histograms &h ) {
  // Candidates passed to this method have passed removedLifetimeCriteria
  // BUT no requirement on sign of d0

  // Check for NAN
  // Again, not sure if needed.  Check for source of bug.
  if ( cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp != cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp
      || cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp != cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp ) return;

  // Whether this is a "bad" run range
  bool inBadRange = ( candidates->run >= badRunRangeMin_ && candidates->run <= badRunRangeMax_ ) ? true : false;

  // Corrections where dilepton form vertex
  if ( passVertex ) {
    // Bias in d0/sigma vs phi, theta
    h.h_singleLeptonD0Significance_vs_phi->Fill( leptonL.phi, cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0Significance_vs_phi->Fill( leptonH.phi, cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0Significance_vs_theta->Fill( 2 * atan( exp(-leptonL.eta)), cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0Significance_vs_theta->Fill( 2 * atan( exp(-leptonH.eta)), cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

    // Bias in d0/sigma vs phi and theta simultaneously
    // Measure in two different run ranges as mean bias is seen to change within periods

    if ( inBadRange ) {
      // In bad run range
      h.h_singleLeptonD0Significance_vs_phi_vs_theta_badRun->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
      h.h_singleLeptonD0Significance_vs_phi_vs_theta_badRun->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

      // Bias in d0
      h.h_singleLeptonD0_vs_phi_vs_theta_badRun->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0L_PVrefit_signWrtPerp, eventWeight_ );
      h.h_singleLeptonD0_vs_phi_vs_theta_badRun->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0H_PVrefit_signWrtPerp, eventWeight_ );

//      // Fill debugging/crosscheck histograms
//      fillD0CorrectionsCrossCheck( leptonL, cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, cand.leptonD0SignificanceL_PVrefit_includingPVError, cand.deltaPhiL, meanD0SignificanceVsThetaVsPhi_badRun_, h  );
//      fillD0CorrectionsCrossCheck( leptonH, cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, cand.leptonD0SignificanceH_PVrefit_includingPVError, cand.deltaPhiH, meanD0SignificanceVsThetaVsPhi_badRun_, h  );
    }
    else {
      // All other runs in this period
      h.h_singleLeptonD0Significance_vs_phi_vs_theta->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
      if ( fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp) > 2 )   h.h_singleLeptonD0SignificanceG2_vs_phi_vs_theta->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
      h.h_singleLeptonD0Significance_vs_phi_vs_theta->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
      if ( fabs(cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp) > 2 )   h.h_singleLeptonD0SignificanceG2_vs_phi_vs_theta->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

      // Bias in d0
      h.h_singleLeptonD0_vs_phi_vs_theta->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0L_PVrefit_signWrtPerp, eventWeight_ );
      h.h_singleLeptonD0_vs_phi_vs_theta->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0H_PVrefit_signWrtPerp, eventWeight_ );

//      // Fill debugging/crosscheck histograms
//      fillD0CorrectionsCrossCheck( leptonL, cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, cand.leptonD0SignificanceL_PVrefit_includingPVError, cand.deltaPhiL, meanD0SignificanceVsThetaVsPhi_, h  );
//      fillD0CorrectionsCrossCheck( leptonH, cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, cand.leptonD0SignificanceH_PVrefit_includingPVError, cand.deltaPhiH, meanD0SignificanceVsThetaVsPhi_, h  );
    }


    // Bias in d0/sigma vs phi and theta simultaneously, for tracks with/without pixel hits
    if ( leptonL.algo < 9 ) h.h_singleLeptonD0Significance_vs_phi_vs_theta_pixel->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    else if ( leptonL.algo >= 9 && leptonL.algo < 11 ) h.h_singleLeptonD0Significance_vs_phi_vs_theta_noPixel->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    if ( leptonH.algo < 9 ) h.h_singleLeptonD0Significance_vs_phi_vs_theta_pixel->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    else if ( leptonH.algo >= 9 && leptonH.algo < 11 ) h.h_singleLeptonD0Significance_vs_phi_vs_theta_noPixel->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

    // Bias in d0/sigma vs run
    h.h_singleLeptonD0Significance_vs_run->Fill( candidates->run, cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0Significance_vs_run->Fill( candidates->run, cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

    // Bias in d0 vs run
    h.h_singleLeptonD0_vs_run->Fill( candidates->run, cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0_vs_run->Fill( candidates->run, cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

    h.h_singleLeptonD0Significance->Fill( cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0Significance->Fill( cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

    // Fraction of leptons with large d0/sigma
    h.h_leptonD0SigFractionMap_all->Fill(  2 * atan( exp(-leptonL.eta)), leptonL.phi, eventWeight_ );
    h.h_leptonD0SigFractionMap_all->Fill(  2 * atan( exp(-leptonH.eta)), leptonH.phi, eventWeight_ );
    if ( fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp) > 3 ) h.h_leptonD0SigFractionMap_pass->Fill( 2 * atan( exp(-leptonL.eta)), leptonL.phi, eventWeight_ );
    if ( fabs(cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp) > 3 ) h.h_leptonD0SigFractionMap_pass->Fill( 2 * atan( exp(-leptonH.eta)), leptonH.phi, eventWeight_ );

    h.h_leptonD0SigFraction_vs_run_all->Fill( candidates->run, eventWeight_ );
    h.h_leptonD0SigFraction_vs_run_all->Fill( candidates->run, eventWeight_ );

    if ( fabs(cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp) > 3 ) h.h_leptonD0SigFraction_vs_run_pass->Fill( candidates->run, eventWeight_ );
    if ( fabs(cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp) > 3 ) h.h_leptonD0SigFraction_vs_run_pass->Fill( candidates->run, eventWeight_ );

    // Bias in d0 vs phi and theta
    h.h_singleLeptonD0_vs_phi->Fill( leptonL.phi, cand.leptonD0L_PVrefit_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0_vs_phi->Fill( leptonH.phi, cand.leptonD0H_PVrefit_signWrtPerp, eventWeight_ );

  }

  // Corrections from all dileptons
  // Form a vertex but without chi2 cut

  h.h_singleLeptonD0Significance_noVertex_allRegion->Fill( cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
  h.h_singleLeptonD0Significance_noVertex_allRegion->Fill( cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

  // In bad run range
  if ( inBadRange ) {
    h.h_singleLeptonD0Significance_vs_phi_vs_theta_badRun_noVertex->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0Significance_vs_phi_vs_theta_badRun_noVertex->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

    h.h_singleLeptonD0_vs_phi_vs_theta_badRun_noVertex->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0L_PVrefit_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0_vs_phi_vs_theta_badRun_noVertex->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0H_PVrefit_signWrtPerp, eventWeight_ );
  }
  else {
    // Bias in d0/sigma vs phi and theta simultaneously
    h.h_singleLeptonD0Significance_vs_phi_vs_theta_noVertex->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0Significance_vs_phi_vs_theta_noVertex->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp, eventWeight_ );

    h.h_singleLeptonD0_vs_phi_vs_theta_noVertex->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), cand.leptonD0L_PVrefit_signWrtPerp, eventWeight_ );
    h.h_singleLeptonD0_vs_phi_vs_theta_noVertex->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), cand.leptonD0H_PVrefit_signWrtPerp, eventWeight_ );
  }
}

void DileptonAnalyzer::studyTrackZ0Misalignment( const TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , const bool passVertex, Histograms &h ) {

  // Candidates passed to this method have passed removedLifetimeCriteria
  // BUT no requirement on sign of d0

  // Whether this is a "bad" run range
  bool inBadRange = ( candidates->run >= badRunRangeMin_ && candidates->run < badRunRangeMax_ ) ? true : false;

  // Corrections where dilepton form vertex
  if ( passVertex ) {

    // Bias in d0/sigma vs phi and theta simultaneously
    // Measure in two different run ranges as mean bias is seen to change within periods

    if ( inBadRange ) {
      // In bad run range
      h.h_singleLeptonZ0_vs_phi_vs_theta_badRun->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), leptonL.dz_PV, eventWeight_ );
      h.h_singleLeptonZ0_vs_phi_vs_theta_badRun->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), leptonH.dz_PV, eventWeight_ );
    }
    else {
      // All other runs in this period
      h.h_singleLeptonZ0_vs_phi_vs_theta->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), leptonL.dz_PV, eventWeight_ );
      h.h_singleLeptonZ0_vs_phi_vs_theta->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), leptonH.dz_PV, eventWeight_ );
    }


    // Bias in d0/sigma vs phi and theta simultaneously, for tracks with/without pixel hits
    if ( leptonL.algo < 9 ) h.h_singleLeptonZ0_vs_phi_vs_theta_pixel->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), leptonL.dz_PV, eventWeight_ );
    else if ( leptonL.algo >= 9 && leptonL.algo < 11 ) h.h_singleLeptonZ0_vs_phi_vs_theta_noPixel->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), leptonL.dz_PV, eventWeight_ );
    if ( leptonH.algo < 9 ) h.h_singleLeptonZ0_vs_phi_vs_theta_pixel->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), leptonH.dz_PV, eventWeight_ );
    else if ( leptonH.algo >= 9 && leptonH.algo < 11 ) h.h_singleLeptonZ0_vs_phi_vs_theta_noPixel->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), leptonH.dz_PV, eventWeight_ );

    // Bias in d0/sigma vs run
    h.h_singleLeptonZ0_vs_run->Fill( candidates->run, leptonL.dz_PV, eventWeight_ );
    h.h_singleLeptonZ0_vs_run->Fill( candidates->run, leptonH.dz_PV, eventWeight_ );
  }

  // Corrections from all dileptons
  // Do not necessarily form a vertex

  // In bad run range
  if ( inBadRange ) {
    h.h_singleLeptonZ0_vs_phi_vs_theta_badRun_noVertex->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), leptonL.dz_PV, eventWeight_ );
    h.h_singleLeptonZ0_vs_phi_vs_theta_badRun_noVertex->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), leptonH.dz_PV, eventWeight_ );
  }
  else {
    // Bias in z0/sigma vs phi and theta simultaneously
    h.h_singleLeptonZ0_vs_phi_vs_theta_noVertex->Fill( leptonL.phi, 2 * atan( exp(-leptonL.eta)), leptonL.dz_PV, eventWeight_ );
    h.h_singleLeptonZ0_vs_phi_vs_theta_noVertex->Fill( leptonH.phi, 2 * atan( exp(-leptonH.eta)), leptonH.dz_PV, eventWeight_ );
  }
}

// Perform a few cross checks of d0 corrections
// Look at distributions before/after corrections with exactly the same leptons
// Do this in one region of tracker and all regions
void DileptonAnalyzer::fillD0CorrectionsCrossCheck( TreeLepton & lepton, double d0Sigma_signWrtPerp, double d0Sigma_signWrtDilepton, double deltaPhi, TProfile2D * corrections, Histograms &h ) {
  double piOver2 = TMath::PiOver2();

  // This region seems to have large mean (found by running code and looking at results)
  // Look at 1D distribution in this bin separately
  bool  inBadRegion = ( lepton.phi > 1.12 && lepton.phi < 1.44 && 2 * atan( exp(-lepton.eta)) > 0.35 && 2 * atan( exp(-lepton.eta)) < 0.4375 ) ? true : false;

  // Signed in same way as bias correction
  h.h_singleLeptonD0Significance_allRegion->Fill( d0Sigma_signWrtPerp, eventWeight_ );
  if ( inBadRegion ) h.h_singleLeptonD0Significance_badRegion->Fill( d0Sigma_signWrtPerp, eventWeight_ );

  // Signed wrt dilepton mom, as in main analysis
  h.h_minLeptonD0Sig_removedLifetimeCuts_allRegion->Fill( d0Sigma_signWrtDilepton, eventWeight_ );
  if ( inBadRegion ) h.h_minLeptonD0Sig_removedLifetimeCuts_badRegion->Fill( d0Sigma_signWrtDilepton, eventWeight_ );

  // Plot delta phi (between dilepton momentum and vector perpendicular to lepton)
  h.h_deltaPhi_removedLifetimeCuts_allRegion->Fill( deltaPhi, eventWeight_ );

  // Get delta phi between dilepton momentum and lepton
  if ( deltaPhi < -1.0 * TMath::PiOver2() ) {
    h.h_deltaPhi_dileptonLepton_removedLifetimeCuts_allRegion->Fill( deltaPhi + 3 * TMath::PiOver2(), eventWeight_ );
  }
  else {
    h.h_deltaPhi_dileptonLepton_removedLifetimeCuts_allRegion->Fill( deltaPhi - TMath::PiOver2(), eventWeight_ );
  }

//  if ( fabs( deltaPhi ) <= TMath::PiOver2() ) {
//
//  }
//  else if ( deltaPhi < TMath::PiOver2() ) {
//  }
//  else if ( deltaPhi < -1.0 * TMath::PiOver2() ) {
//    h.h_deltaPhi_dileptonLepton_removedLifetimeCuts_allRegion->Fill( deltaPhi - TMath::PiOver2(), eventWeight_ );
//  }

  // Get delta phi betwee vector perp to dilepton momentum and lepton
//  h_deltaPhi_dileptonPerpLepton_removedLifetimeCuts_allRegion;

  if ( inBadRegion ) h.h_deltaPhi_removedLifetimeCuts_badRegion->Fill( deltaPhi, eventWeight_ );

  // Also look at cands with angle between dilepton mom and vector perpendicular to lepton (delta phi) less than and greater than pi/2
  if ( fabs( deltaPhi ) > piOver2 ) {
    h.h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2->Fill( d0Sigma_signWrtDilepton, eventWeight_ );
    if ( inBadRegion ) h.h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2->Fill( d0Sigma_signWrtDilepton, eventWeight_ );
  }
  else {
    h.h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2->Fill( d0Sigma_signWrtDilepton, eventWeight_ );
    if ( inBadRegion ) h.h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2->Fill( d0Sigma_signWrtDilepton, eventWeight_ );
  }

  // With corrections
  // Done manually and sign determined in equivalent way
  int bin = corrections->FindBin( 2 * atan( exp(-lepton.eta)), lepton.phi );
  double meanD0Sigma = corrections->GetBinContent( bin );
  double correctedD0Sigma = d0Sigma_signWrtPerp - meanD0Sigma;

  // Signed in same way as bias correction
  h.h_singleLeptonD0Significance_allRegion_corrected->Fill( correctedD0Sigma, eventWeight_ );
  if ( inBadRegion ) h.h_singleLeptonD0Significance_badRegion_corrected->Fill( correctedD0Sigma, eventWeight_ );

  // Sign wrt dilepton momentum
  // Work out sign of correction
  if ( d0Sigma_signWrtPerp * d0Sigma_signWrtDilepton < 0 ) {
    correctedD0Sigma = -1.0 * correctedD0Sigma;
  }

  h.h_minLeptonD0Sig_removedLifetimeCuts_allRegion_corrected->Fill( correctedD0Sigma, eventWeight_ );
  if ( inBadRegion ) h.h_minLeptonD0Sig_removedLifetimeCuts_badRegion_corrected->Fill( correctedD0Sigma, eventWeight_ );

  // Again for different bins of delta phi
  if ( fabs( deltaPhi ) > piOver2 ) {
    h.h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2_corrected->Fill( correctedD0Sigma, eventWeight_ );
    if ( inBadRegion ) h.h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2_corrected->Fill( correctedD0Sigma, eventWeight_ );
  }
  else {
    h.h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2_corrected->Fill( correctedD0Sigma, eventWeight_ );
    if ( inBadRegion ) h.h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2_corrected->Fill( correctedD0Sigma, eventWeight_ );
  }
}


double DileptonAnalyzer::correctD0Sigma( TreeLepton & lepton, TProfile2D * h, double d0Sigma, double deltaPhi ) {
  // Got lepton theta and phi
  // Get mean d0/sigma in this region
  int bin = h->FindBin( 2 * atan( exp(-lepton.eta)), lepton.phi );
  double meanD0Sigma = h->GetBinContent( bin );

  // Now get sign of correction
  // I.e. if angle between the two different vectors used to sign d0 is less than 90 degrees, then -ve
  if ( fabs(deltaPhi) < TMath::PiOver2() ) {
    // Subtract correction
    meanD0Sigma = -1.0 * meanD0Sigma;
  }
  return d0Sigma + meanD0Sigma;
}

void DileptonAnalyzer::fillCorrectedD0Sigma( const TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , TProfile2D *corrections, TH1F *hisCorr_bothLeptons, TH1F *hisCorr, TH1F *hisCorr_forFittingData, TString typeOfCorrections, bool runDependent, TProfile2D *correction_badRunRange )
{

  // Correct lepton d0/sigma by mean bias in d0/sigma in bins of phi and theta
  double d0SigmaLCorr = -99999;
  double d0SigmaHCorr = -99999;

  TProfile2D* correctionsToUse = corrections;

  if ( runDependent ) {
    bool inBadRange = ( candidates->run >= badRunRangeMin_ && candidates->run <= badRunRangeMax_ ) ? true : false;
    if ( inBadRange && correction_badRunRange != 0 ) {
      correctionsToUse = correction_badRunRange;
    }
  }


  if ( typeOfCorrections=="pixel" ) {
    // Different corrections depending if lepton has pixel hits or not

    // Low pt lepton
    if ( leptonL.algo == 9 || leptonL.algo == 10 ) {
      d0SigmaLCorr = correctD0Sigma( leptonL, meanD0SignificanceVsThetaVsPhi_noPixel_, cand.leptonD0SignificanceL_PVrefit_includingPVError, cand.deltaPhiL );
    }
    else {
      d0SigmaLCorr = correctD0Sigma( leptonL, correctionsToUse, cand.leptonD0SignificanceL_PVrefit_includingPVError, cand.deltaPhiL );
    }

    // High pt lepton
    if ( leptonL.algo == 9 || leptonL.algo == 10 ) {
      d0SigmaHCorr = correctD0Sigma( leptonH, meanD0SignificanceVsThetaVsPhi_noPixel_, cand.leptonD0SignificanceH_PVrefit_includingPVError, cand.deltaPhiH );
    }
    else {
      d0SigmaHCorr = correctD0Sigma( leptonH, correctionsToUse, cand.leptonD0SignificanceH_PVrefit_includingPVError, cand.deltaPhiH );
    }
  }
  else if ( typeOfCorrections=="d0" ) {
    // Corrections based on d0 rather than d0/sigma
    d0SigmaLCorr = correctD0Sigma( leptonL, correctionsToUse, cand.leptonD0L_PVrefit, cand.deltaPhiL );
    d0SigmaHCorr = correctD0Sigma( leptonH, correctionsToUse, cand.leptonD0H_PVrefit, cand.deltaPhiH );

    // Divide by sigma to d0/sigma
    d0SigmaLCorr = d0SigmaLCorr * cand.leptonD0SignificanceL_PVrefit_includingPVError / cand.leptonD0L_PVrefit;
    d0SigmaHCorr = d0SigmaHCorr * cand.leptonD0SignificanceH_PVrefit_includingPVError / cand.leptonD0H_PVrefit;
  }
  else if ( typeOfCorrections=="normal" ){
    // Standard corrections
    d0SigmaLCorr = correctD0Sigma( leptonL, correctionsToUse, cand.leptonD0SignificanceL_PVrefit_includingPVError, cand.deltaPhiL );
    d0SigmaHCorr = correctD0Sigma( leptonH, correctionsToUse, cand.leptonD0SignificanceH_PVrefit_includingPVError, cand.deltaPhiH );
  }
  else if ( typeOfCorrections=="none" ) {
    // Apply no corrections
    // Good for debugging
    d0SigmaLCorr = cand.leptonD0SignificanceL_PVrefit_includingPVError;
    d0SigmaHCorr = cand.leptonD0SignificanceH_PVrefit_includingPVError;
  }
  else if ( typeOfCorrections=="perpToDilepton") {
    // Normal corrections, but d0 is signed wrt vector perpendicular to dilepton momentum

    // Currently doing corrections manually for this case
    int bin = correctionsToUse->FindBin( 2 * atan( exp(-leptonL.eta)), leptonL.phi );
    double meanD0Sigma = correctionsToUse->GetBinContent( bin );

    if ( cand.leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError * cand.leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp > 0 ) {
      d0SigmaLCorr = cand.leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError - meanD0Sigma;
    }
    else {
      d0SigmaLCorr = cand.leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError + meanD0Sigma;
    }

    // Same for lepton H
    bin = correctionsToUse->FindBin( 2 * atan( exp(-leptonH.eta)), leptonH.phi );
    meanD0Sigma = correctionsToUse->GetBinContent( bin );

    if ( cand.leptonD0SignificanceH_PVrefit_sigWrtPerpDilepton_includingPVError * cand.leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp > 0 ) {
      d0SigmaHCorr = cand.leptonD0SignificanceH_PVrefit_sigWrtPerpDilepton_includingPVError - meanD0Sigma;
    }
    else {
      d0SigmaHCorr = cand.leptonD0SignificanceH_PVrefit_sigWrtPerpDilepton_includingPVError + meanD0Sigma;
    }

  }
  else if ( typeOfCorrections=="perpToDileptonNone") {
    // No corrections
    // Sign wrt perp to dilepton
    d0SigmaLCorr = cand.leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError;
    d0SigmaHCorr = cand.leptonD0SignificanceH_PVrefit_sigWrtPerpDilepton_includingPVError;
  }

  // Now have corrected d0/sigma of both leptons


  // Check for NAN.  Not sure if necessary (seen problems else where)
  // Either remove or solve bug...
  if ( d0SigmaLCorr == d0SigmaLCorr && d0SigmaHCorr == d0SigmaHCorr ) {

    // Plot both leptons without sign requirement
    hisCorr_bothLeptons->Fill( d0SigmaLCorr, eventWeight_ );
    hisCorr_bothLeptons->Fill( d0SigmaHCorr, eventWeight_ );

    // Plot minimum d0/sigma after same sign requirement
    // As in main analysis

    if ( d0SigmaLCorr * d0SigmaHCorr > 0 ) {
      // Work out new min D0
      double minD0Corr = min( fabs(d0SigmaLCorr), fabs(d0SigmaHCorr) ) == fabs(d0SigmaLCorr) ? d0SigmaLCorr : d0SigmaHCorr;
      // Fill histogram
      hisCorr->Fill( minD0Corr, eventWeight_ );

      // Also fill blinded version of histogram
      if ( ( anaType_==_2eTrack && minD0Corr < 6 ) || ( ( anaType_==_2muTrack || anaType_ == _2globalOrTrackerMu ) && minD0Corr < 4 ) ) {
        hisCorr_forFittingData->Fill( minD0Corr, eventWeight_ );
      }
    }
  }
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
  cout << "Number of events : " << nentries << endl;

  // Keep track of correctly/incorrectly reconstructed exotics
  int progress=0;

  // Loop over events
  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    // Useful if you only want to run over a subset of events
//      for (Long64_t jentry=2373147; jentry<2373148;jentry++) {
//        for (Long64_t jentry=nentries*0.1; jentry<nentries*0.11;jentry++) {

    // Progress bar
    if ( int(float(jentry)/float(nentries)*100) % 10 == 0 && int(float(jentry)/float(nentries)*100) > progress  ) {
      progress = 100*jentry/nentries;
      progressCounter(progress);
    }
    if ( jentry==nentries-1) {
      progressCounter(100);
      cout << endl;
    }

    // Checks recommended from TTree:MakeClass
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    fChain->GetEntry(jentry);

    // Get event weight
    // PU weight and cross-section weight
    // Also normalised by number of events in MC samples
    getEventWeight();

    // Study neutralino pt spectrum
    if ( isSignalMC_ && candidates->ll1_motherPdgId == 1000022 && candidates->ll2_motherPdgId == 1000022 ) {
      studyNeutralinoPtSpectrum();

      if ( reweightNeutralinoPt_ ) {
        eventWeight_ = eventWeight_ * getNeutralinoWeight();
      }
    }

    if ( isSignalMC_ && reweightExoticLifetime_ ) {
//    cout << getLifetimeWeight( candidates->ll1_ctau ) << " " << getLifetimeWeight( candidates->ll2_ctau ) << endl;
    eventWeight_ = eventWeight_ * getLifetimeWeight( candidates->ll1_ctau ) * getLifetimeWeight( candidates->ll2_ctau );
    }

    // Study gen level info if this is signal MC
    // In particular, get total number of exotics decaying to something this analysis is sensitive to
    if ( isSignalMC_ ) {

      // Filter out events where there is no interesting exotics
      // This can happen when e.g. the generated event is H->XX and one or both X->jj
      if ( !interestingExoticInEvent() ) continue;

      // Keep track of number of exotics decaying in each channel and info about exotics
      // Return number of exotics decaying to interesting channel
      nSensitiveExoticDecayInEvent_=storeNumberOfExoticsALL();

      // Store lxy and X pt of all cands for efficiency plots
      // Only for central lifetime sample
      // Only for exotics within acceptance
      if ( isCentralCtau() ){
        ++nEvents_;
        if ( nSensitiveExoticDecayInEvent_==2 ) {


          if ( ll1WithinAcceptance() && ll2WithinAcceptance() ) {
            hists_.h_allExotics_two_genLxy->Fill(candidates->ll1_decayLength2D, eventWeight_);
            hists_.h_allExotics_two_genLxy->Fill(candidates->ll2_decayLength2D, eventWeight_);
            if ( candidates->ll1_decayLength2D > 0 && candidates->ll1_decayLength2D < 100 )
              hists_.h_allExotics_two_XPt->Fill(candidates->ll1_pt, eventWeight_);
            if ( candidates->ll2_decayLength2D > 0 && candidates->ll2_decayLength2D < 100 )
              hists_.h_allExotics_two_XPt->Fill(candidates->ll2_pt, eventWeight_);
            hists_.h_allExotics_two_nRecoPV->Fill(candidates->numPV, eventWeight_);
            hists_.h_allExotics_two_nRecoPV->Fill(candidates->numPV, eventWeight_);
          }
        }
        else if ( nSensitiveExoticDecayInEvent_==1 ) {

          hists_.h_allExotics_one_nRecoPV->Fill(candidates->numPV, eventWeight_);

          // Work out which exotic to plot
          unsigned int interestingLepton=getInterestingLepton();

          ++nExoticsBeforeAcceptance_;

          if ( eventWithinAcceptance( nSensitiveExoticDecayInEvent_ ) ) {
            // Keep track of number of central ctau exotics considered.  Needed for cutflow
            // Only interested in case where only one exotic decayed to chosen species
            nExoticsBeforePrefilter_ += eventWeight_;
            if ( interestingLepton == fabs(candidates->ll1_daughter1_PdgId) && interestingLepton == fabs(candidates->ll1_daughter2_PdgId) ) {
              hists_.h_allExotics_one_genLxy->Fill(candidates->ll1_decayLength2D, eventWeight_);
              if ( candidates->ll1_decayLength2D > 0 && candidates->ll1_decayLength2D < 100 ) {
                hists_.h_allExotics_one_XPt->Fill(candidates->ll1_pt, eventWeight_);
              }
            }
            else if ( interestingLepton == fabs(candidates->ll2_daughter1_PdgId) && interestingLepton == fabs(candidates->ll2_daughter2_PdgId) ) {
              hists_.h_allExotics_one_genLxy->Fill(candidates->ll2_decayLength2D, eventWeight_);
              if ( candidates->ll2_decayLength2D > 0 && candidates->ll2_decayLength2D < 100 ) {
                hists_.h_allExotics_one_XPt->Fill(candidates->ll2_pt, eventWeight_);
              }
            }
          }
        }
      }
      // Check which triggers fired
      studyTriggers();

      // There has been no signal trigger requirement so far for signal MC
      // Therefore require signal trigger to have fired
      if ( !signalTriggerFired() ) {
        continue;
      }

      if ( isCentralCtau() && eventWithinAcceptance( nSensitiveExoticDecayInEvent_ )) {
        if ( nSensitiveExoticDecayInEvent_==1 ) {
          // For cut flow
          // Only interested in events where one exotic decays to interesting channel
          nExoticsAfterTrigger_ +=eventWeight_;
        }
      }

      // Study tracking efficiency
      // A few cross checks, nothing too important
      studyTrackingEfficiency();
    }

    // FIXME Left over from purity studies - move/remove
    originalCounter_++;
    purityCounter_++;

    // Require the primary vertex to have at least 4 tracks
    // This is so that when we refit the primary vertex after removing the tracks
    // associated to a candidate, there are still at least 2 tracks left...
    if ( candidates->pv_nTracks < 4 ) continue;

    // Loop over leptons in event
    // Just to get a few plots on individual leptons
    // Leave out for now
    //    for ( unsigned int iTreeLepton=0; iTreeLepton != candidates->leptons_.size(); ++iTreeLepton ) {
    //
    //      TreeLepton lepton = candidates->leptons_.at(iTreeLepton);
    //
    //      // Check this is correct lepton for this type of analysis
    //      if ( !correctLepton( lepton ) ) continue;
    //
    //      // Apply basic selection
    //      // These already have some low pt cut applied
    //      bool passedCuts = false;
    //      if ( lepton.pt > 21 && fabs( lepton.eta ) < 2 && lepton.triggerMatch != 0 && lepton.iso/lepton.pt < 0.1 ) passedCuts = true;
    //
    //      if ( passedCuts ) {
    //        hists_.h_singleLepton_d0->Fill( lepton.d0_PV, eventWeight_ );
    //        hists_.h_singleLepton_d0sigma->Fill( lepton.d0Significance_PV_includingPVError, eventWeight_ );
    //        hists_.h_singleLepton_sigma->Fill( lepton.d0_PV/lepton.d0Significance_PV_includingPVError, eventWeight_ );
    //      }
    //    }

    // Loop over (dilepton) candidates in event

    bestControlCand_=0;
    bestSignalCand_=0;
    bestFinalSignalCand_=0;

    for( unsigned int iTreeCand=0; iTreeCand != candidates->candidates_.size(); ++iTreeCand ) {

      TreeDipseudoLeptonCandidate &cand = candidates->candidates_.at(iTreeCand);

      // Get leptons corresponding to this candidate
      TreeLepton leptonL = getLepton( cand.leptonIndexL );
      TreeLepton leptonH = getLepton( cand.leptonIndexH );

      // Check what type of leptons make up this candidate
      // Make sure they are relevant to this analysis
      if ( !correctLeptonsInCandidate(cand, leptonL, leptonH ) ) continue;

      // Study candidates
      // Fill different set of histograms if this is a ditau candidates
      if ( !isDitauEvent() || isData_ || isSignalMC_ ) {
        studyCandidate( cand, leptonL, leptonH, hists_, false );
      }
      else {
        studyCandidate( cand, leptonL, leptonH, histsTau_, false );
      }

    } // cand loop

    plotBestCandidates();

    // Reset best cand
    atLeastOneCandInAcceptance_=false;
    bestControlCand_=0;
    bestSignalCand_=0;
    bestFinalSignalCand_=0;
    bestL0Cand_=0;
    bestG0Cand_=0;


    // Corrected cand loop
    if ( isData_ && useCorrectedCands_ ) {
      for( unsigned int iTreeCand=0; iTreeCand != candidates->candidatesCorrectedTipLip_.size(); ++iTreeCand ) {

        TreeDipseudoLeptonCandidate &cand = candidates->candidatesCorrectedTipLip_.at(iTreeCand);

        // Get leptons corresponding to this candidate
        TreeLepton leptonL = getLepton( cand.leptonIndexL );
        TreeLepton leptonH = getLepton( cand.leptonIndexH );

        // Check what type of leptons make up this candidate
        // Make sure they are relevant to this analysis
        if ( !correctLeptonsInCandidate(cand, leptonL, leptonH ) ) continue;

        // Study candidates
        studyCandidate( cand, leptonL, leptonH, histsCorrected_, true );

      } // corrected cand loop

      plotBestCandidates(true);

      // Reset best cand
      bestControlCand_=0;
      bestSignalCand_=0;
      bestFinalSignalCand_=0;
      bestL0Cand_=0;
      bestG0Cand_=0;
    }

    // Keep track of number of canidadtes reconstructed per event
    if ( isData_ ) {
      storeNumberOfCandsPerEvent( histsCorrected_ );
    }
    else {
      storeNumberOfCandsPerEvent( hists_ );
    }



  } // event loop

  if ( isSignalMC_ ){
    cout << endl << "Number of central ctau exotics : " << nEvents_ << endl;
    cout << "Number of exotics before acceptance : " << nExoticsBeforeAcceptance_ << endl;
    cout << "Number of exotics : " << nExoticsBeforePrefilter_ << endl;
    cout << "Number of exotics after trigger : "<< nExoticsAfterTrigger_ << endl;
    cout << "Number of exotics before prefilter : " << nCorrectlyRecoExoticsBeforePrefilter_ << endl << endl;
    cout << "Trigger efficiency : " << nExoticsAfterTrigger_/nExoticsBeforePrefilter_ * 100 << endl;
    cout << "Tracking preselection efficiency : " << nCorrectlyRecoExoticsBeforePrefilter_/nExoticsAfterTrigger_ * 100 << endl;
    cout << "Total preselection efficiency : " << nCorrectlyRecoExoticsBeforePrefilter_/nExoticsBeforePrefilter_ * 100 << endl << endl;
    cout << setprecision(3);
    cout << nExoticsAfterTrigger_/nExoticsBeforePrefilter_ * 100 << "\\% & " << nCorrectlyRecoExoticsBeforePrefilter_/nExoticsAfterTrigger_ * 100 << "\\% & " << nCorrectlyRecoExoticsBeforePrefilter_/nExoticsBeforePrefilter_ * 100 <<"\\% \\\\" << endl << endl;
  }
  // Draw overflow of hists_ in final bin
  hists_.drawOverflows();
  // Draw underflows in subset of histograms (see Histgorams.C)
  hists_.drawUnderflows();

  // Save hists_
  TString type("dummy");
  if ( anaType_==_2eTrack) type = "2eTrack";
  else if ( anaType_==_2muTrack ) type = "2muTrack";
  else if ( anaType_==_2globalOrTrackerMu ) type = "2globalOrTrackerMu";
  else if ( anaType_==_2globalMu ) type = "2globalMu";
  else if ( anaType_==_2trackerMu ) type = "2trackerMu";
  else if ( anaType_==_2saMu ) type = "2saMu";

  TString outputFileName("WeightedFiles/"+dirName_+"_weighted_"+type+".root");

  TFile outputFile(outputFileName, "RECREATE");
  outputFile.cd();

  // Output histograms to file
  hists_.writeHistograms(outputFile);

  // Report cut flow
  reportCutFlow(outputFile);

  if ( isSignalMC_ ) {

    // Store signal efficiencies
    storeSignalEfficiencies(outputFile);

    // Report trigger info
    //    for ( unsigned int iTrig=0; iTrig < signalTriggers_.size(); iTrig++ ) {
    //      cout << "Trigger : " << signalTriggers_[iTrig].c_str() << " Number times fired : " << triggerFired_[iTrig] << endl;
    //    }

    // Some info to screen
    //    cout << endl;
    //    cout << "Number of correctly reconstructed candidates : " << nCorrect_ << endl;
    //    cout << "Number of incorrectly reconstructed candidates : " << nIncorrect_ << endl;
    //    cout << endl;
    //
    //    cout << "Number of correctly reco'd candidates, but with gen particles outside acceptance," << endl;
    //    for ( int iExo = 0; iExo < nSignalParticles_; iExo++ ) {
    //      cout << "For exotic " << signalPdgId_[iExo] << " one decay in channel : " << numExotics_oA_oneSensitiveDecay_[iExo] << " both decay in channel : " << numExotics_oA_twoSensitiveDecay_[iExo] << endl;
    //    }
    //
    //    cout << "Total number of events processed : " << totalProcessedEvents_ << endl;
    //    cout << endl;

  }

  // Info on trigger purity studies
  //  cout << "===== TRIGGER PURITY STUDIES =====" << endl;
  //  cout << "Total events passing trigger : " << eventsPassingTrigger_ << endl;
  //  cout << "Sanity check counter (all events just before prefilter, but after trigger) : " << originalCounter_ << endl;
  //  cout << "(However, some prefilter already applied at tree producer level!)" << endl;
  //  cout << "---> pt : " << purityCounter_pt_ << " purity wrt previous : " << float(purityCounter_pt_)/float(eventsPassingTrigger_) << endl;
  //  cout << "---> match to offline : " << purityCounter_offlineMatch_ << " purity wrt previous : " << float(purityCounter_offlineMatch_)/float(purityCounter_pt_) << endl;
  //  cout << "---> Et : " << purityCounter_Et_ << " purity wrt previous : " << float(purityCounter_Et_)/float(purityCounter_eta_) << endl;
  //  cout << "---> Final purity : " << purityCounter_ << " purity wrt previous : " << float(purityCounter_)/float(purityCounter_Et_) << endl;
  //  cout << "Trigger purity : " << float(purityCounter_)/float(eventsPassingTrigger_) << endl;

  cout << "Writing and closing files" << endl;
  // Close file
  outputFile.Write();
  outputFile.Close();


  // Output histos for tau studies
  TString outputFileNameTau("WeightedFiles/"+dirName_+"_weighted_"+type+"_tau.root");
  TFile outputFileTau(outputFileNameTau, "RECREATE");
  outputFileTau.cd();
  histsTau_.writeHistograms(outputFileTau);
  outputFileTau.Write();
  outputFileTau.Close();

  // Output histos for corrected candidates
  if ( isData_ && useCorrectedCands_ ) {
    TString outputFileNameCorrected("WeightedFiles/"+dirName_+"_weighted_"+type+"_tipLipCorrected.root");
    TFile outputFileCorrected(outputFileNameCorrected, "RECREATE");
    outputFileCorrected.cd();
    histsCorrected_.writeHistograms(outputFileCorrected);
    outputFileCorrected.Write();
    outputFileCorrected.Close();
  }

  cout << "Deleting histograms" << endl;
  // Delete histograms
  hists_.deleteHistograms();
  cout << "Deleting tau histograms" << endl;
  histsTau_.deleteHistograms();
  if ( useCorrectedCands_ ) {
    cout << "Deleting corrected histograms" << endl;
    histsCorrected_.deleteHistograms();
  }
}

//
// CONSTRUCTOR
//

DileptonAnalyzer::DileptonAnalyzer(TString fileName, const double & weight, analysisType analysis) :
                                                                  treeAnalyzerBase(fileName, weight, analysis),
                                                                  reweightNeutralinoPt_(false), ssWeight_(-1), sasWeight_(-1),
                                                                  atLeastOneCandInAcceptance_(false),
                                                                  nCandsPerEvent_final_(0), nCandsPerEvent_loose_(0),
                                                                  nCandsPerEvent_control_(0), nCandsPerEvent_looseControl_(0),
                                                                  nCandsPerEvent_deltaPhiG90_(0), nCandsPerEvent_deltaPhiL90_(0),
                                                                  bestSignalCand_(0), bestFinalSignalCand_(0), bestControlCand_(0),
                                                                  bestL0Cand_(0), bestG0Cand_(0),
                                                                  hists_(Histograms("")),
                                                                  histsTau_(Histograms("_tau")),
                                                                  histsCorrected_(Histograms("_tipLipCorrected")),
                                                                  eventWeight_(weight),
                                                                  lxyScale_(1.0), d0Scale_(1.0), d0Scale_gaussianWidth_(0.),
                                                                  isSignalMC_(false), isData_(false), nSignalParticles_(0),
                                                                  triggerToPlot_(0),
                                                                  originalCounter_(0),
                                                                  purityCounter_(0),
                                                                  purityCounter_offlineMatch_(0), // Breakdown of overall purity
                                                                  purityCounter_eta_(0),
                                                                  purityCounter_Et_(0),
                                                                  purityCounter_pt_(0),
                                                                  nSensitiveExoticDecayInEvent_(0),
                                                                  nCorrect_(0), nIncorrect_(0),
                                                                  acceptancePt1Cut_(0), acceptancePt2Cut_(0), acceptanceEtaCut_(0), acceptanceLxyCut_(0),
                                                                  nEvents_(0), nExoticsBeforeAcceptance_(0), nExoticsBeforePrefilter_(0), nExoticsAfterTrigger_(0), nCorrectlyRecoExoticsBeforePrefilter_(0),
                                                                  rnd(0),
                                                                  EBEBScale_(0.0092), EBEEScale_(0.0143), EEEEScale_(0.0125),
                                                                  badRunRangeMin_(999999), badRunRangeMax_(999999),
                                                                  useCorrectedCands_(true),
                                                                  unblind_(false),
                                                                  reweightExoticLifetime_(false),
                                                                  reweightFactor_(1),
                                                                  originalCtau_(350),
                                                                  DEBUGCOUNTER(0)
{

  // Initialize analysis cuts
  dileptonCuts_final_=DileptonAnalysisCuts(anaType_,_final);
  dileptonCuts_looseA_=DileptonAnalysisCuts(anaType_,_looseA);
  dileptonCuts_looseB_=DileptonAnalysisCuts(anaType_,_looseB);
  dileptonCuts_looseC_=DileptonAnalysisCuts(anaType_,_looseC);
  dileptonCuts_removedLifetime_=DileptonAnalysisCuts(anaType_,_removedLifetime);
  dileptonCuts_removedLifetimeNoVertex_=DileptonAnalysisCuts(anaType_,_removedLifetimeNoVertex);

  dileptonCuts_finalColl_=DileptonAnalysisCuts(anaType_,_finalColl);
  dileptonCuts_looseColl_=DileptonAnalysisCuts(anaType_,_looseColl);
  dileptonCuts_controlColl_=DileptonAnalysisCuts(anaType_,_controlColl);
  dileptonCuts_looseControlColl_=DileptonAnalysisCuts(anaType_,_looseControlColl);

  // Get anaType_ in string format
  TString type("dummy");
  if ( anaType_==_2eTrack) type = "2eTrack";
  else if ( anaType_==_2muTrack ) type = "2muTrack";
  else if ( anaType_==_2globalOrTrackerMu ) type = "2globalOrTrackerMu";
  else if ( anaType_==_2globalMu ) type = "2globalMu";
  else if ( anaType_==_2trackerMu ) type = "2trackerMu";
  else if ( anaType_==_2saMu ) type = "2saMu";


  // Is this data?
  if ( fileName.Contains("Data") ) isData_=true;

  // Get good label for output file names
  // Get good name for signal effic files
  TString fileLabel=fileName;
  int position=fileLabel.Index("workdirs/")+9;
  fileLabel.Remove(0,position);
  position=fileLabel.Index("_analysis");
  fileLabel.Remove(position,fileLabel.Length());

  // Is this signal MC?
  if ( fileName.Contains("LongLived") || fileName.Contains("Chi0ToNuLL") ) {
    isSignalMC_=true;

    // Initialize signal MC pdg id container
    if ( isSignalMC_ ) {

      if ( fileName.Contains("HTo2LongLivedTo4F") || fileName.Contains("test") ) {
        signalPdgId_.push_back(6001113);
        signalPdgId_.push_back(6002113);
        signalPdgId_.push_back(6003113);

        centralPdgId_=6002113;
      }
      else if ( fileName.Contains("Chi0ToNuLL") ) {
        signalPdgId_.push_back(1000022);
        centralPdgId_=1000022;
      }
    }

    // Set number of possible signal particles
    nSignalParticles_=signalPdgId_.size();

    // Set names of interesting signal triggers
    signalTriggers_.push_back("AnyTrigger");
    if ( anaType_==_2eTrack ) {

      signalTriggers_.push_back("HLT_Photon36_R9Id85_OR_CaloId10_Iso50_Photon22_R9Id85_OR_CaloId10_Iso50_v5");
      //      signalTriggers_.push_back("HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50_v5");
      //      signalTriggers_.push_back("HLT_Photon36_R9Id85_Photon22_R9Id85_v3");
      //      signalTriggers_.push_back("HLT_DoublePhoton48_HEVT_v7");


      triggerToPlot_=1;
    }
    else if ( anaType_==_2muTrack ||  anaType_==_2globalOrTrackerMu || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu ) {
      signalTriggers_.push_back("HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v2");
      triggerToPlot_=1;
    }

    // Pick which trigger is our main signal trigger
    if ( signalTriggers_.size() >= 1 ) {
      signalTrigger_=signalTriggers_[1];
      cout << "Trigger required in signal MC : " << signalTrigger_.c_str() << endl;

    }
    else {
      signalTrigger_="AnyTrigger";
      cout << "WARNING : Not requiring a signal trigger for signal MC" << endl;
    }

    // Now that we've initialized our triggers, initialize the trigger efficiency histos
    char buf[512];
    for (unsigned int i=0; i<signalTriggers_.size(); i++) {
      sprintf(buf, "trigEff_meanLifetime_%s", signalTriggers_[i].c_str());
      hists_.h_trigEff_meanLifetime.push_back(new TProfile(buf, "Trigger efficiency vs. mean lifetime", nTrigEffBins, 0, nominalLifetime_*20));

      sprintf(buf, "h_trigEff_meanLifetimeLog_%s", signalTriggers_[i].c_str());
      Double_t xlifetimebins[nReweightFactors_+1];
      xlifetimebins[0] = nominalLifetime_*lifetimeReweightingFactors_[0]/2;
      for (unsigned int ibin=0; ibin<nReweightFactors_-1; ibin++)
        xlifetimebins[ibin+1] = nominalLifetime_*(lifetimeReweightingFactors_[ibin]+lifetimeReweightingFactors_[ibin+1])/2;
      xlifetimebins[nReweightFactors_] = nominalLifetime_*lifetimeReweightingFactors_[nReweightFactors_-1]*2;
      hists_.h_trigEff_meanLifetimeLog.push_back(new TProfile(buf, "Trigger efficiency vs. lifetime", nReweightFactors_, xlifetimebins));
    }

    for ( unsigned int i=0; i < signalTriggers_.size(); i++ ) {
      triggerFired_.push_back(0);
    }

    // Initialize efficiency and acceptance counters
    for ( int i = 0; i<nSignalParticles_; i++ ) {
      numEvents_oneSensitiveDecay_.push_back(0);
      numEvents_twoSensitiveDecay_.push_back(0);
      numExoticsRECO_oneSensitiveDecay_.push_back(0);
      numExoticsRECO_twoSensitiveDecay_.push_back(0);
      numExoticsCorrectRECO_oneSensitiveDecay_.push_back(0);
      numExoticsCorrectRECO_twoSensitiveDecay_.push_back(0);
      numExotics_oA_oneSensitiveDecay_.push_back(0);
      numExotics_oA_twoSensitiveDecay_.push_back(0);
    }

    // Open output files for efficiency studies
    allExotics_oneSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_allExotics_"+type+"_"+fileLabel+"_oneDecay.txt");
    allExotics_twoSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_allExotics_"+type+"_"+fileLabel+"_twoDecay.txt");
    recoExotics_oneSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_recoExotics_"+type+"_"+fileLabel+"_oneDecay.txt");
    recoExotics_twoSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_recoExotics_"+type+"_"+fileLabel+"_twoDecay.txt");
    recoExotics_oneSensitiveDecay_negative_.open("EfficiencyFiles/rawFiles/effic_recoExotics_"+type+"_"+fileLabel+"_oneDecay_negative.txt");
    recoExotics_twoSensitiveDecay_negative_.open("EfficiencyFiles/rawFiles/effic_recoExotics_"+type+"_"+fileLabel+"_twoDecay_negative.txt");
    recoExotics_oneSensitiveDecay_removedLifetime_.open("EfficiencyFiles/rawFiles/effic_recoExotics_"+type+"_"+fileLabel+"_oneDecay_removedLifetime.txt");
    recoExotics_twoSensitiveDecay_removedLifetime_.open("EfficiencyFiles/rawFiles/effic_recoExotics_"+type+"_"+fileLabel+"_twoDecay_removedLifetime.txt");

    recoExotics_coll_oneSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_recoExotics_coll_"+type+"_"+fileLabel+"_oneDecay.txt");
    recoExotics_coll_twoSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_recoExotics_coll_"+type+"_"+fileLabel+"_twoDecay.txt");
    recoExotics_coll_oneSensitiveDecay_negative_.open("EfficiencyFiles/rawFiles/effic_recoExotics_coll_"+type+"_"+fileLabel+"_oneDecay_negative.txt");
    recoExotics_coll_twoSensitiveDecay_negative_.open("EfficiencyFiles/rawFiles/effic_recoExotics_coll_"+type+"_"+fileLabel+"_twoDecay_negative.txt");


    allExotics_oneSensitiveDecay_ << setprecision(7);
    allExotics_twoSensitiveDecay_ << setprecision(7);
    recoExotics_oneSensitiveDecay_ << setprecision(7);
    recoExotics_twoSensitiveDecay_ << setprecision(7);
    recoExotics_oneSensitiveDecay_negative_ << setprecision(7);
    recoExotics_twoSensitiveDecay_negative_ << setprecision(7);
    recoExotics_oneSensitiveDecay_removedLifetime_ << setprecision(7);
    recoExotics_twoSensitiveDecay_removedLifetime_ << setprecision(7);

    recoExotics_coll_oneSensitiveDecay_ << setprecision(7);
    recoExotics_coll_twoSensitiveDecay_ << setprecision(7);
    recoExotics_coll_oneSensitiveDecay_negative_ << setprecision(7);
    recoExotics_coll_twoSensitiveDecay_negative_ << setprecision(7);

    // Set gen level acceptance cuts
    if ( anaType_==_2eTrack ) {
      acceptancePt1Cut_=dileptonCuts_final_.getLeadingSCEtCut();
      acceptancePt2Cut_=dileptonCuts_final_.getSubleadingSCEtCut();
    }
    else {
      acceptancePt1Cut_=dileptonCuts_final_.getTrackPtCut();
      acceptancePt2Cut_=acceptancePt1Cut_;
    }
    acceptanceEtaCut_=dileptonCuts_final_.getTrackEtaCut();
    acceptanceLxyCut_=50; // cm

    if ( anaType_==_2eTrack ) allCuts_.open("SignalMassResolutionFiles/electrons/"+fileLabel+".txt");
    else if ( anaType_==_2muTrack ) allCuts_.open("SignalMassResolutionFiles/muons/"+fileLabel+".txt");

    // Initialize neutrlino weights
    if ( reweightNeutralinoPt_ ) {
      if (fileName.Contains("MSquark1500_MChi494")) {
        ssWeight_=0.890;
        sasWeight_=2.31;
      }
      else if (fileName.Contains("MSquark1000_MChi148")) {
        ssWeight_=0.791;
        sasWeight_=1.65;
      }
      else if (fileName.Contains("MSquark350_MChi148")) {
        ssWeight_=2.31;
        sasWeight_=0.882;
      }
      else if (fileName.Contains("MSquark120_MChi48")) {
        ssWeight_=53.1;
        sasWeight_=0.875;
      }
      cout << "Reweighting neutralino pt spectrum" << endl;
      cout << "ssWeight : " << ssWeight_ << endl;
      cout << "sasWeight : " << sasWeight_ << endl;
    }
  }
  else {
    if ( anaType_==_2eTrack ) {
      allCuts_.open("MassFiles/electrons/"+fileLabel+"_positive.txt");
      allCutsNegative_.open("MassFiles/electrons/"+fileLabel+"_negative.txt");
      allCollCuts_.open("MassFiles/electrons/"+fileLabel+"_coll_positive.txt");
      allCollCutsNegative_.open("MassFiles/electrons/"+fileLabel+"_coll_negative.txt");
      allCollCuts_corrected_.open("MassFiles/electrons/"+fileLabel+"_coll_corrected_positive.txt");
      allCollCutsNegative_corrected_.open("MassFiles/electrons/"+fileLabel+"_coll_corrected_negative.txt");
    }
    else if ( anaType_==_2muTrack ) {
      allCuts_.open("MassFiles/muons/"+fileLabel+"_positive.txt");
      allCutsNegative_.open("MassFiles/muons/"+fileLabel+"_negative.txt");
      allCollCuts_.open("MassFiles/muons/"+fileLabel+"_coll_positive.txt");
      allCollCutsNegative_.open("MassFiles/muons/"+fileLabel+"_coll_negative.txt");
      allCollCuts_corrected_.open("MassFiles/muons/"+fileLabel+"_coll_corrected_positive.txt");
      allCollCutsNegative_corrected_.open("MassFiles/muons/"+fileLabel+"_coll_corrected_negative.txt");
    }
    allCuts_ << "Mass\tTransverseMass\tLxy\td0/sigmaL\td0/sigmaH\teventWeight\tRun\tLumi\tEvent" << endl;
    allCutsNegative_ << "Mass\tTransverseMass\tLxy\td0/sigmaL\td0/sigmaH\teventWeight\tRun\tLumi\tEvent" << endl;
    allCollCuts_ << "Mass\tTransverseMass\tLxy\td0/sigmaL\td0/sigmaH\teventWeight\tRun\tLumi\tEvent" << endl;
    allCollCutsNegative_ << "Mass\tTransverseMass\tLxy\td0/sigmaL\td0/sigmaH\teventWeight\tRun\tLumi\tEvent" << endl;
    allCollCuts_corrected_ << "Mass\tTransverseMass\tLxy\td0/sigmaL\td0/sigmaH\teventWeight\tRun\tLumi\tEvent" << endl;
    allCollCutsNegative_corrected_ << "Mass\tTransverseMass\tLxy\td0/sigmaL\td0/sigmaH\teventWeight\tRun\tLumi\tEvent" << endl;
  }

  // Take note of prefilter thresholds
  prefilterEtaCut_=2.0;
  if ( anaType_==_2eTrack ) {
    prefilterPtCut_.push_back(36);
    prefilterPtCut_.push_back(21);
    prefilterEtCut_.push_back(0);
    prefilterEtCut_.push_back(0);
  }
  else {
    prefilterPtCut_.push_back(26);
    prefilterPtCut_.push_back(26);
    prefilterEtCut_.push_back(0);
    prefilterEtCut_.push_back(0);
  }
  if ( prefilterPtCut_.size() < 2 || (anaType_==_2eTrack && prefilterEtCut_.size()<2 ) ) cout << "WARNING : less than two pt/et cuts defined for prefilter.  Will probably crash :-)" << endl;


  // Open output files for background studies
  removedLifetime_.open("BackgroundStudiesFiles/removedLifetimeMass/removedLifetime_"+type+"_"+fileLabel+".txt");
  looseCuts_.open("BackgroundStudiesFiles/looseLifetimeMass/looseCuts_"+type+"_"+fileLabel+".txt");

  // Initialize cut flow map - order of cuts important

  cutNamesInOrder_.push_back("AllCandidatesAfterPrefilter");
  cutNamesInOrder_.push_back("DileptonChi2");
  cutNamesInOrder_.push_back("DileptonOppositeCharge");
  cutNamesInOrder_.push_back("SameSignD0");
  cutNamesInOrder_.push_back("LeptonPt");
  cutNamesInOrder_.push_back("LeptonAbsEta");
  cutNamesInOrder_.push_back("CaloMatch");
  cutNamesInOrder_.push_back("PhotonMatch");
  cutNamesInOrder_.push_back("LeptonSCEt");
  cutNamesInOrder_.push_back("PhotonID");
  cutNamesInOrder_.push_back("MuonID");
  cutNamesInOrder_.push_back("TrackQuality");
  cutNamesInOrder_.push_back("DileptonTriggerMatch");
  cutNamesInOrder_.push_back("DileptonIsolation");
  cutNamesInOrder_.push_back("DileptonMass");
  cutNamesInOrder_.push_back("DileptonB2BVeto");
  cutNamesInOrder_.push_back("DileptonDeltaR");
  cutNamesInOrder_.push_back("DileptonDeltaPhi");
  cutNamesInOrder_.push_back("LeptonD0Sig");
  cutNamesInOrder_.push_back("DileptonHitsBeforeVertex");
  cutNamesInOrder_.push_back("DileptonMissingHitsAfterVertex");
  cutNamesInOrder_.push_back("DileptonAbsLxySig");

  for ( unsigned int iCut = 0; iCut < cutNamesInOrder_.size(); iCut++ ) {
    cutFlowMap_[cutNamesInOrder_[iCut]]=0;
    cutFlowMapColl_[cutNamesInOrder_[iCut]]=0;
  }

  // Initialize lxy smearing factors for background MC only
  if ( !isSignalMC_ && !isData_ ) {
    // For muon channel
    if ( anaType_==_2muTrack ||  anaType_==_2globalOrTrackerMu || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu ) {
      lxyScale_ = 1.1;
      d0Scale_ = 1.00;
    }
    // For electron channel
    else if ( anaType_==_2eTrack) {
      lxyScale_ = 1.1;
      d0Scale_ = 0.95;
      d0Scale_gaussianWidth_ = 1.1;
    }
  }

  // Get histogram of mean d0/sigma vs theta vs phi
  // For correcting d0/sigma of each lepton
  if ( isData_ ) {
    // Get file containing histograms

    // Get correct corrections
    // Different for each run range
    TString reco("PromptReco");
    TString runRange("XYZ");
    if ( fileLabel.Contains("22Jan") ) {
      reco="22JanRereco";
      if ( fileLabel.Contains("A22Jan")) runRange = "A";
      else if ( fileLabel.Contains("B22Jan")) runRange = "B";
      else if ( fileLabel.Contains("C22Jan"))  runRange = "C";
      else if ( fileLabel.Contains("D22Jan"))  runRange = "D";
    }
    else {
      if ( fileLabel.Contains("A1") || fileLabel.Contains("A2") ) runRange = "A";
      else if ( fileLabel.Contains("B1")) runRange = "B";
      else if ( fileLabel.Contains("C1") || fileLabel.Contains("C2"))  runRange = "C";
      else if ( fileLabel.Contains("D1"))  runRange = "D";
    }

    TCanvas *mydummycanvas=new TCanvas();
    mydummycanvas->cd();
    TFile * meanD0SigmaFile = new TFile ("misalignmentPlots/meanD0Significance_vs_phi_vs_theta_"+type+"_"+reco+"_"+runRange+".root", "READ");
    meanD0SigmaFile->GetObject("singleLeptonD0_vs_phi_vs_theta",meanD0VsThetaVsPhi_);
    meanD0SigmaFile->GetObject("singleLeptonD0Significance_vs_phi_vs_theta",meanD0SignificanceVsThetaVsPhi_);
    meanD0SigmaFile->GetObject("singleLeptonD0Significance_vs_phi_vs_theta_badRun",meanD0SignificanceVsThetaVsPhi_badRun_);
    meanD0SigmaFile->GetObject("singleLeptonD0Significance_vs_phi_vs_theta_noVertex",meanD0SignificanceVsThetaVsPhi_noVertex_);
    meanD0SigmaFile->GetObject("singleLeptonD0Significance_vs_phi_vs_theta_badRun_noVertex",meanD0SignificanceVsThetaVsPhi_badRun_noVertex_);
    meanD0SigmaFile->GetObject("singleLeptonD0SignificanceG2_vs_phi_vs_theta",meanD0SignificanceVsThetaVsPhiCut_);
    meanD0SigmaFile->GetObject("singleLeptonD0Significance_vs_phi_vs_theta_pixel",meanD0SignificanceVsThetaVsPhi_pixel_);
    meanD0SigmaFile->GetObject("singleLeptonD0Significance_vs_phi_vs_theta_noPixel",meanD0SignificanceVsThetaVsPhi_noPixel_);

    // Also define run ranges where mean bias in d0/sigma changes within run period.
    // Calculate and use different run ranges in these periods
    if ( fileLabel.Contains("A1") || fileLabel.Contains("A2") || fileLabel.Contains("A22Jan") ) {
      // No separation in run A
      badRunRangeMin_=999999;
      badRunRangeMax_=999999;
    }
    else if ( fileLabel.Contains("B1") || fileLabel.Contains("B22Jan")) {
      badRunRangeMin_=194350;
      badRunRangeMax_=196600;
    }
    else if ( fileLabel.Contains("C1") || fileLabel.Contains("C2") || fileLabel.Contains("C22Jan"))  {
      badRunRangeMin_=200300;
      badRunRangeMax_=203750;
    }
    else if ( fileLabel.Contains("D1") || fileLabel.Contains("D22Jan"))  {
      badRunRangeMin_=207883;
      badRunRangeMax_=208307;
    }

  }

  if ( isSignalMC_ && reweightExoticLifetime_ ) {
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "WARNING - REWEIGHTING EXOTIC LIFETIME" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
  }

}

DileptonAnalyzer::~DileptonAnalyzer()
{
  // Close output files
  allExotics_oneSensitiveDecay_.close();
  allExotics_twoSensitiveDecay_.close();
  recoExotics_oneSensitiveDecay_.close();
  recoExotics_twoSensitiveDecay_.close();
  recoExotics_oneSensitiveDecay_negative_.close();
  recoExotics_twoSensitiveDecay_negative_.close();
  recoExotics_oneSensitiveDecay_removedLifetime_.close();
  recoExotics_twoSensitiveDecay_removedLifetime_.close();

  recoExotics_coll_oneSensitiveDecay_.close();
  recoExotics_coll_twoSensitiveDecay_.close();
  recoExotics_coll_oneSensitiveDecay_negative_.close();
  recoExotics_coll_twoSensitiveDecay_negative_.close();

  removedLifetime_.close();
  looseCuts_.close();

  allCuts_.close();
  allCollCuts_.close();
  allCollCuts_corrected_.close();
  if ( allCutsNegative_.is_open() ) allCutsNegative_.close();
  if ( allCollCutsNegative_.is_open() ) allCollCutsNegative_.close();
  if ( allCollCutsNegative_corrected_.is_open() ) allCollCutsNegative_corrected_.close();
}
;
