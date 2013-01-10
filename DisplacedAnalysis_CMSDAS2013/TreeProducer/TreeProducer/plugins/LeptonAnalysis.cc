#include "TreeProducer/TreeProducer/plugins/LeptonAnalysis.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/TrackBase.h"
// #include "DataFormats/Common/interface/Vector.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"
#include "Math/Vector4D.h"
#include "Math/GenVector/Boost.h"
#include "TDCacheFile.h"
#include "DataFormats/Math/interface/angle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/MuonReco/interface/MuonTime.h"

#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "DataFormats/Common/interface/MergeableCounter.h"

#include <sstream>
#include <iomanip>

// PAT
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/TriggerPath.h"
#include "DataFormats/PatCandidates/interface/TriggerFilter.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/MET.h"

void LeptonAnalysis::endLuminosityBlock(const edm::LuminosityBlock & lumi, const edm::EventSetup & setup)
{
  // Total number of events is the sum of the events in each of these luminosity blocks
  edm::Handle<edm::MergeableCounter> nEventsTotalCounter;
  lumi.getByLabel("nEventsTotal", nEventsTotalCounter);
  numProcessedEvents_ += nEventsTotalCounter->value;

  //  edm::Handle<edm::MergeableCounter> nEventsAfterEventFilters;
  //  lumi.getByLabel("nEventsPostEventFilter", nEventsAfterEventFilters);
  //  numEventsPassingEventFilters_ += nEventsAfterEventFilters->value;

  edm::Handle<edm::MergeableCounter> nEventsAfterHLTFilter;
  lumi.getByLabel("nEventsPostHLTFilter", nEventsAfterHLTFilter);
  numEventsPassingTrigger_ += nEventsAfterHLTFilter->value;
}

LeptonAnalysis::LeptonAnalysis(const edm::ParameterSet& iConfig):

                                                              checkHitPattern_(NULL),
                                                              generatorTag_(iConfig.getParameter<edm::InputTag>("generatorSrc")),
                                                              pileupTag_(edm::InputTag("addPileupInfo")),
                                                              genEventInfoTag_(edm::InputTag("generator")),
                                                              trigger_(iConfig.getParameter<edm::InputTag>("trigger")),
                                                              triggerEvent_(iConfig.getParameter<edm::InputTag>("triggerEvent")),
                                                              barrelSuperClusters_(iConfig.getParameter<edm::InputTag>("barrelSuperClusters")),
                                                              endcapSuperClusters_(iConfig.getParameter<edm::InputTag>("endcapSuperClusters")),
                                                              signalPDGId_(iConfig.getParameter<std::vector<int>>("signalPDGId")),
                                                              leptonPDGId_(iConfig.getParameter<int>("leptonPDGId")),
                                                              hltPaths_(iConfig.getParameter<std::vector<std::string> >("hltPaths")),
                                                              leptonPtCut_(iConfig.getParameter<double>("leptonPtCut")),
                                                              leptonSCEtCut_(iConfig.getParameter<double>("leptonSCEtCut")),
                                                              useMCTruth_(iConfig.getParameter<bool>("UseMCTruth")),
                                                              numProcessedEvents_(0),
                                                              numEventsPassingEventFilters_(0),
                                                              numEventsPassingTrigger_(0)
{
  if (leptonPDGId_==11) {
    thisLepton_=__lepTypeElectron;
    leptonName_="electron";
  } else if (leptonPDGId_==13) {
    thisLepton_=__lepTypeMuon;
    leptonName_="muon";
  } else if (leptonPDGId_==15) {
    thisLepton_=__lepTypeTau;
    leptonName_="tau";
  } else if (leptonPDGId_==-11) {
    thisLepton_=__lepTypeTrack;
    leptonName_="etrack";
  } else if (leptonPDGId_==-13) {
    thisLepton_=__lepTypeTrack;
    leptonName_="mutrack";
  } else if (leptonPDGId_==-15) {
    thisLepton_=__lepTypeTrack;
    leptonName_="tautrack";
  } else if (leptonPDGId_==22) {
    thisLepton_=__lepTypePhoton;
    leptonName_="photon";
  } else {
    throw cms::Exception("InvalidLeptonPDG") << "abs(leptonPDGId) must be 11, 13 or 15";
  }
  std::cout << "ANALYSIS CHANNEL: " << leptonName_ << std::endl;

  leptonCollTag_[__lepTypeElectron]=iConfig.getParameter<edm::InputTag>("electronSrc");
  leptonCollTag_[__lepTypeMuon]=iConfig.getParameter<edm::InputTag>("muonSrc");
  leptonCollTag_[__lepTypeTau]=iConfig.getParameter<edm::InputTag>("tauSrc");
  leptonCollTag_[__lepTypeTrack]=iConfig.getParameter<edm::InputTag>("trackSrc");

  // introduce short dCache read timeout to work around problems at RAL
  TDCacheFile::SetOpenTimeout(1800);

  // Create the tree
  edm::Service<TFileService> fs_;
  outputTree_ = fs_->make<TTree>("outputTree","outputTree");
  // Single lepton variables
  outputTree_->Branch("candidates","Candidates",&candidates_,32000,0);
  outputTree_->Branch("triggers","std::vector<std::string>",&triggers_,32000,0);

  // To save the total number of processed events
  hTotalProcessedEvents_ = new TH1F("totalProcessedEvents", "Total processed events", 1, 0, 1);
  hEventsPassingEventsFilter_ = new TH1F("eventsPassingEventFilters", "Events passing event filters", 1, 0, 1);
  hEventsPassingTrigger_ = new TH1F("eventsPassingTrigger", "Events passing trigger selection", 1, 0, 1);
}

LeptonAnalysis::~LeptonAnalysis()
{
}

void LeptonAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // event setup
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder_);
  if (checkHitPattern_==NULL) checkHitPattern_ = new CheckHitPattern(iSetup);

  // look at trigger information, this fills the vars_.triggers vector of strings
  bool passesTrigger = doTrigger(iEvent);

  if( passesTrigger ) {

    // Initialize all variables
    initializeVars();

    // get beamspot
    edm::Handle<reco::BeamSpot> beamSpotHandle;
    iEvent.getByLabel ("offlineBeamSpot", beamSpotHandle);
    beamSpot_=(*beamSpotHandle);

    // Fill event based variables
    fillEventBasedInfo(iEvent,iSetup);

    // Fill pseudo leptons
    fillPseudoLeptons(iEvent);

    // Fill dipseudo lepton candidates
    fillDipseudoleptonCandidates(iEvent);

    if ( leptonName_=="photon") {
      // Fill photons
      fillPhotons(iEvent);

      // Fill diphoton candidates
      fillDiphotonCandidates(iEvent);
    }

    // Fill Tree
    outputTree_->Fill();
  }
}

void LeptonAnalysis::fillEventBasedInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get the run, event and lumi info
  // Put into tree
  candidates_.run = iEvent.id().run();
  candidates_.lumi = iEvent.id().luminosityBlock();
  candidates_.event = iEvent.id().event();

  // Get the MET info
  try {
    edm::Handle<std::vector<pat::MET> > metHandle;
    iEvent.getByLabel ("patMETs", metHandle);
    // MET info into tree
    candidates_.MET = metHandle->begin()->pt();
    candidates_.METPhi = metHandle->begin()->phi();
  }
  catch (...) {
    //    std::cout << "No pat MET collection found in input file" << std::endl;
  }

  // Get reco primary vertex info
  edm::Handle<reco::VertexCollection> primaryVertex;
  iEvent.getByLabel ("offlinePrimaryVertices", primaryVertex);
  // there should always be a vertex in this collection. even if the primary vertex fit failed,
  // a fake vertex based on the beam spot should be present
  if (primaryVertex->size()==0) {
    std::cout << "no primary vertex found! skipping event" << std::endl;
    return;
  }
  reco::Vertex pv = primaryVertex->front();
  VertexState PVstate(GlobalPoint(pv.x(),pv.y(),pv.z()),GlobalError(pv.covariance()));
  // Set main PV
  primaryVertex_=PVstate;
  // count number of proper primary vertices in event
  int numPV=0;
  for (unsigned i=0; i<primaryVertex->size(); i++) {
    if (!(*primaryVertex)[i].isFake()) ++numPV;
  }

  // Reco pv info into tree
  candidates_.numPV = numPV;

  // evaluate generator-level event properties needed for reweighting,
  // such as PDF, pile-up vertices,
  // decay channels and lifetimes of long-lived particles etc
  if( useMCTruth_ ) {
    GenEventProperties genProp(iEvent,iSetup,signalPDGId_,generatorTag_,
        pileupTag_,genEventInfoTag_);
    // MC pv info into tree
    candidates_.nvtx_m1 = genProp.numPileup(-1);
    candidates_.nvtx_0 = genProp.numPileup(0);
    candidates_.nvtx_p1 = genProp.numPileup(1);
    candidates_.nvtx_true = genProp.numTruePUInteractions();

    // MC info on decay types etc.
    // Only interested if there are two decays (as in our signal MC)
    if ( genProp.numDecays() == 2 ) {
      candidates_.ll1_motherPdgId = genProp.motherId(0);
      candidates_.ll1_daughterPdgId = genProp.decayMode(0);
      candidates_.ll1_ctau = genProp.ctau(0);
      candidates_.ll1_decayLength2D = genProp.decayLength2D(0);
      candidates_.ll1_decayLength3D = genProp.decayLength3D(0);

      candidates_.ll1_daughter1_Pt=genProp.daughterPt(0);
      candidates_.ll1_daughter1_D0=genProp.daughterD0(0);
      candidates_.ll1_daughter2_Pt=genProp.daughterPt(1);
      candidates_.ll1_daughter2_D0=genProp.daughterD0(1);

      candidates_.ll2_motherPdgId = genProp.motherId(1);
      candidates_.ll2_daughterPdgId = genProp.decayMode(1);
      candidates_.ll2_ctau = genProp.ctau(1);
      candidates_.ll2_decayLength2D = genProp.decayLength2D(1);
      candidates_.ll2_decayLength3D = genProp.decayLength3D(1);

      candidates_.ll2_daughter1_Pt=genProp.daughterPt(2);
      candidates_.ll2_daughter1_D0=genProp.daughterD0(2);
      candidates_.ll2_daughter2_Pt=genProp.daughterPt(3);
      candidates_.ll2_daughter2_D0=genProp.daughterD0(3);

    }

    //
    //
    //    // long-lived decay properties
    //    unsigned numDecays_;
    //    std::vector<int> decayModes_;
    //    std::vector<double> decayLength2D_;
    //    std::vector<double> decayLength3D_;
    //    std::vector<double> ctau_;

    //    int decayMode(unsigned i) { if (i<2) return decayModes_[i]; else return -999; }
    //    double decayLength2D(unsigned i) { if (i<2) return decayLength2D_[i]; else return -999; }
    //    double decayLength3D(unsigned i) { if (i<2) return decayLength3D_[i]; else return -999; }
    //    double ctau(unsigned i) { if (i<2) return ctau_[i]; else return -999; }
  }
}

void LeptonAnalysis::fillPseudoLeptons(const edm::Event& iEvent)
{
  // Get pseudoleptons - the "track" source
  edm::Handle<edm::View<PseudoLepton> > particles;
  iEvent.getByLabel(leptonCollTag_[__lepTypeTrack],particles);

  // Load superCluster collections if this is for electrons
  edm::Handle< std::vector<reco::SuperCluster> > barrelSuperClusters;
  edm::Handle< std::vector<reco::SuperCluster> > endcapSuperClusters;
  if( leptonName_ == "etrack" ) {
    iEvent.getByLabel( barrelSuperClusters_, barrelSuperClusters );
    if (barrelSuperClusters.failedToGet()) {
      std::cout << "WARNING: cannot access barrel superclusters for matching" << std::endl;
    }
    iEvent.getByLabel( endcapSuperClusters_, endcapSuperClusters );
    if (endcapSuperClusters.failedToGet()) {
      std::cout << "WARNING: cannot access endcap superclusters for matching" << std::endl;
    }
  }

  // Load gen particles or set the flag to false if they are not available
  bool MCTruthFound = true;
  edm::Handle<edm::View<reco::GenParticle> > mcParticles;
  if( useMCTruth_ ) {
    iEvent.getByLabel(generatorTag_,mcParticles);
    if(mcParticles.failedToGet()) {
      std::cout << "WARNING: cannot access MC truth information." << std::endl;
      MCTruthFound = false;
    }
  }

  // Load trigger objects
  edm::Handle< pat::TriggerEvent > triggerEvent;
  iEvent.getByLabel( triggerEvent_, triggerEvent );
  if (triggerEvent.failedToGet()) {
    std::cout << "WARNING: cannot access triggerEvent for matching" << std::endl;
    //    return;
  }

  int lepton_index=0;

  // First loop on pseudoleptons to fill lepton-based information (trigger matches, calo-matches, muon-matches, etc...)
  for( typename edm::View<PseudoLepton>::const_iterator it = particles->begin(); it != particles->end(); ++it ) {

    //
    // APPLY INITIAL CUTS ON PSEDUOLEPTON
    //

    // Apply cut on track pt
    // FIXME Bad for electrons.  Should cut on SC Et, or at least much looser here
    if (it->pt() < leptonPtCut_) continue;

    // If this is the electron channel, only interested in track matched to TO
    // Also cut on matched SC Et in electron channel
    // Do not save if it doesn't have a calo match
    if ( leptonName_ == "etrack" ) {
      // Only consider tracks here - no muons
      if ( !(it->isCentralTrack() ) ) continue;

      // Check if track has a calo match
      double deltaR = 999;
      double deltaEta = 999;
      double deltaPhi = 999;
      const reco::SuperCluster * matchedSC = findCaloMatch(*it, barrelSuperClusters, endcapSuperClusters, deltaR, deltaEta, deltaPhi );
      // Apply cut if it does
      if ( matchedSC != 0 ) {
        if (matchedSC->energy() * sin( matchedSC->position().theta() ) < leptonSCEtCut_ ) continue;
      }
      else continue;
    }

    // Save this lepton
    candidates_.leptons_.push_back(TreeLepton());
    TreeLepton & lepton = candidates_.leptons_.back();

    // Save calo matching info if this is the electron channel
    if ( leptonName_ == "etrack" ) {
      double deltaR = 999;
      double deltaEta = 999;
      double deltaPhi = 999;
      const reco::SuperCluster * matchedSC = findCaloMatch(*it, barrelSuperClusters, endcapSuperClusters, deltaR, deltaEta, deltaPhi );
      if ( matchedSC == 0 ) {
        lepton.hasCaloMatch=0;
      }
      else {
        lepton.hasCaloMatch=1;
        lepton.cmDeltaR=deltaR;
        lepton.cmDeltaEta=fabs(deltaEta);
        lepton.cmDeltaPhi=fabs(deltaPhi);
        lepton.scEnergy = matchedSC->energy();
        lepton.scEt = matchedSC->energy() * sin( matchedSC->position().theta() );
        lepton.scEta = matchedSC->eta();
        lepton.scPhi = matchedSC->phi();

        // Compare with old method
        double deltaR_OLD=999;
        const reco::SuperCluster * matchedSC_OLD = findCaloMatch_OLD(*it, barrelSuperClusters, endcapSuperClusters, deltaR_OLD);

        // Check if we get a different SC and note "old" deltaR
        if ( matchedSC_OLD == matchedSC ) lepton.differentSCToOldMethod = 0;
        else lepton.differentSCToOldMethod = 1;

        lepton.cmDeltaR_old = deltaR_OLD;
      }
    }

    lepton.index=lepton_index;
    lepton_index++;

    // Index in pseudo lepton collection
    lepton.pseudoLeptonIndex = it - particles->begin();

    // Build the transient track. This contains information on the beamspot and will be used later for extrapolations and vertex fitting.
    reco::TransientTrack tTrack = leptonTrack(*it);

    // Is track valid?
    if ( tTrack.isValid() ) {
      lepton.validTrack=1;

      // Pt etc. of track
      lepton.pt = it->pt();

      lepton.eta = it->eta();
      lepton.phi = it->phi();
      lepton.charge = it->charge();

      // Impact parameter

      double d0=-9999;
      double d0significance=-9999;
      try {
        d0=tTrack.stateAtBeamLine().transverseImpactParameter().value();
        d0significance=tTrack.stateAtBeamLine().transverseImpactParameter().significance();
      } catch (cms::Exception& e) {
        // FIXME
        // Currently make this track non-valid.
        // Setting d0 and d0significance to -9999 implies that these should fail the cut on d0 significance
        // But we cut on abs(d0 significance) so they may pass?
        lepton.validTrack=0;
      };

      lepton.d0 = d0;
      lepton.d0Significance = d0significance;

      // What type of muon?
      lepton.isStandAloneMuon = it->isStandAloneMuon();
      lepton.isGlobalMuon = it->isGlobalMuon();
      lepton.isTrackerMuon = it->isTrackerMuon();
      lepton.isCentralTrack = it->isCentralTrack();

      // Tracker isolation
      lepton.iso = trackerIsolation(iEvent,tTrack.track(),tTrack.track());

      // Gen info for this lepton
      if ( useMCTruth_ && MCTruthFound ) {
        // Find closest stable (status == 1) genParticle by deltaR (correct for DV)
        int genIndex = getGenParticleMatch( mcParticles, *it );

        if (genIndex>=0) {
          const reco::GenParticle matchedGenParticle = mcParticles->at(genIndex);

          lepton.genIndex = genIndex;
          lepton.genPdgId = matchedGenParticle.pdgId();
          lepton.genPt = matchedGenParticle.pt();
          lepton.genVertexX = matchedGenParticle.vx();
          lepton.genVertexY = matchedGenParticle.vy();
          lepton.genVertexZ = matchedGenParticle.vz();
          lepton.genPhi = matchedGenParticle.phi();
          lepton.genEta = matchedGenParticle.eta();
          lepton.genTheta = matchedGenParticle.theta();

          // Note origin of this lepton
          // Will get more info on this later when matched candidate is formed
          const reco::Candidate * origin = signalOrigin(&matchedGenParticle);
          if ( origin != NULL ) lepton.genSignalOriginPdgId = origin->pdgId();
          else lepton.genSignalOriginPdgId = 0;

        }
      }

      // Trigger matching
      // FIXME Currently using old method
      double deltaR=999;
      //    double deltaR_OLD=999;
      int matchedTOIndex = findTrigMatch_OLD(*it, triggerEvent,deltaR);
      if ( matchedTOIndex != 0 ) {
        lepton.triggerMatch = 1;
        lepton.triggerObjectIndex = matchedTOIndex;
        lepton.tmDeltaR=deltaR;

        // Check old trigger matching method
        //      findTrigMatch_OLD(*it, triggerEvent,deltaR_OLD);
        //      lepton.tmDeltaR_OLD=deltaR_OLD;
      }
      else lepton.triggerMatch=0;

      // Reference point on track
      lepton.vx = it->vx();
      lepton.vy = it->vy();
      lepton.vz = it->vz();
    }
    else lepton.validTrack=0;
  }
}

void LeptonAnalysis::fillPhotons(const edm::Event& iEvent)
{

  // Here you need to loop over all photons/super clusters
  // for (...) {

  // Save this photon
  candidates_.photons_.push_back(TreePhoton());
  TreePhoton & photon = candidates_.photons_.back();

  // Fill with rubbish for now
  photon.et=26;
  photon.eta=-1.5;
  photon.phi=0.4;
  photon.time=2.4;

  // } //end for loop over all photons
}

void LeptonAnalysis::fillJets(const edm::Event& iEvent)
{

}

const reco::Particle::LorentzVector * LeptonAnalysis::findTrigMatch(const PseudoLepton & lepton,
    const edm::Handle< pat::TriggerEvent > & triggerEvent,
    double &min_deltaR)
{
  // find deltaR match among trigger objects
  min_deltaR=9999.;
  const reco::Particle::LorentzVector* trig_mom=0;

  // Get transient track for this lepton
  reco::TransientTrack tTrack = leptonTrack( lepton );

  // loop over all triggers we are interested in
  for (unsigned itrig=0; itrig<hltPaths_.size(); itrig++) {
    if (!triggerEvent->path(hltPaths_[itrig])) continue;
    if (!triggerEvent->path(hltPaths_[itrig])->wasAccept()) continue;
    // get all trigger objects associated with this HLT path
    const pat::TriggerObjectRefVector triggerObjects(triggerEvent->pathObjects(hltPaths_[itrig],false));
    for (unsigned i=0; i<triggerObjects.size(); i++) {

      //FIXME
      // Not sure what to do here.  Taking "vertex" position of trigger object to get surface...
      GlobalPoint trigObjectPoint( triggerObjects[i]->vx(), triggerObjects[i]->vy(), triggerObjects[i]->vz() );

      double deltaEta=999;
      double deltaPhi=999;
      // Calculate deltaR between SC and track extrapolated to point
      double dR = extrapolateAndDeltaR( tTrack, trigObjectPoint, deltaEta, deltaPhi );
      if (dR<min_deltaR) {
        min_deltaR=dR;
        trig_mom=&(triggerObjects[i]->p4());
      }
    }
  }

  bool trigMatch=(min_deltaR<0.1);
  if (trigMatch) {
    return trig_mom;
  }
  return 0;
}

const int LeptonAnalysis::findTrigMatch_OLD(const PseudoLepton & lepton,
    const edm::Handle< pat::TriggerEvent > & triggerEvent,
    double &min_deltaR)
{
  // find deltaR match among trigger objects
  double lep_eta = lepton.eta();
  double lep_phi = lepton.phi();
  min_deltaR=9999.;
  const reco::Particle::LorentzVector* trig_mom=0;

  // Index to keep track of which TO we match to
  int triggerObjectIndex=0;
  int matchedTOIndex=0;

  // loop over all triggers we are interested in
  for (unsigned itrig=0; itrig<hltPaths_.size(); itrig++) {
    // std::cout << "Trigger path number " << itrig << std::endl;
    if (!triggerEvent->path(hltPaths_[itrig])) continue;
    if (!triggerEvent->path(hltPaths_[itrig])->wasAccept()) continue;
    // get all trigger objects associated with this HLT path
    const pat::TriggerObjectRefVector triggerObjects(triggerEvent->pathObjects(hltPaths_[itrig],false));
    for (unsigned i=0; i<triggerObjects.size(); i++) {
      ++triggerObjectIndex;
      double trig_eta=triggerObjects[i]->eta();
      double trig_phi=triggerObjects[i]->phi();
      double dR=deltaR(lep_eta,lep_phi,trig_eta,trig_phi);
      //      std::cout << "Trigger object number " << i << " Collection : " << triggerObjects[i]->collection().c_str() << "Delta R : " << dR << std::endl;
      if (dR<min_deltaR) {
        matchedTOIndex=triggerObjectIndex;
        min_deltaR=dR;
        trig_mom=&(triggerObjects[i]->p4());
      }
    }
  }

  bool trigMatch=(min_deltaR<0.1);
  if (trigMatch && trig_mom != 0) {
    return matchedTOIndex;
  }
  return 0;
}

// Given a PseudoLepton and the barrel and endcap superclusters returns a pointer to a maching supercluster or a null pointer if no match was found.
const reco::SuperCluster * LeptonAnalysis::findCaloMatch_OLD(const PseudoLepton & lepton,
    const edm::Handle< std::vector<reco::SuperCluster> > & barrelSuperClusters,
    const edm::Handle< std::vector<reco::SuperCluster> > & endcapSuperClusters,
    double &min_deltaR )
{

  //
  // OLD METHOD
  //

  // find deltaR match among superclusters
  double lep_eta=lepton.eta();
  double lep_phi=lepton.phi();
  min_deltaR=9999.;
  const reco::SuperCluster * matchingSC = 0;

  const double deltaRcut=0.2;

  // loop over all barrel superclusters
  if (fabs(lep_eta)<1.48+1.5*deltaRcut) {
    for (unsigned iclus=0; iclus<barrelSuperClusters->size(); iclus++) {
      double clus_eta=(*barrelSuperClusters)[iclus].eta();
      double clus_phi=(*barrelSuperClusters)[iclus].phi();
      double dR=deltaR(lep_eta,lep_phi,clus_eta,clus_phi);
      if (dR<min_deltaR) {
        min_deltaR=dR;
        matchingSC = &(*barrelSuperClusters)[iclus];
      }
    }
  }
  // loop over all endcap superclusters
  if (fabs(lep_eta)>1.48-1.5*deltaRcut) {
    for (unsigned iclus=0; iclus<endcapSuperClusters->size(); iclus++) {
      double clus_eta=(*endcapSuperClusters)[iclus].eta();
      double clus_phi=(*endcapSuperClusters)[iclus].phi();
      double dR=deltaR(lep_eta,lep_phi,clus_eta,clus_phi);
      if (dR<min_deltaR) {
        min_deltaR=dR;
        matchingSC = &(*endcapSuperClusters)[iclus];
      }
    }
  }

  bool caloMatch = (min_deltaR<deltaRcut);
  if( caloMatch ) return matchingSC;
  return 0;
}

// Given a PseudoLepton and the barrel and endcap superclusters returns a pointer to a maching supercluster or a null pointer if no match was found.
const reco::SuperCluster * LeptonAnalysis::findCaloMatch(const PseudoLepton & lepton,
    const edm::Handle< std::vector<reco::SuperCluster> > & barrelSuperClusters,
    const edm::Handle< std::vector<reco::SuperCluster> > & endcapSuperClusters,
    double &min_deltaR, double &min_deltaEta, double &min_deltaPhi )
{

  //
  // NEW METHOD
  //

  double deltaRcut = 0.2;
  min_deltaR=9999.;
  min_deltaPhi=9999.;
  min_deltaEta=9999.;
  const reco::SuperCluster * matchingSC = 0;

  // Get transient track for this lepton
  reco::TransientTrack tTrack = leptonTrack( lepton );

  // Loop over EB SCs
  std::vector<reco::SuperCluster>::const_iterator iclus = barrelSuperClusters->begin();
  for ( ; iclus != barrelSuperClusters->end(); iclus++) {


    // Point on SC surface
    GlobalPoint scPoint( iclus->x(), iclus->y(), iclus->z() );

    // Calculate deltaR between SC and track extrapolated to ECAL surface
    double dEta = 9999.;
    double dPhi = 9999.;
    double dR = extrapolateAndDeltaR( tTrack, scPoint, dEta, dPhi );

    if (dR<min_deltaR) {
      min_deltaR=dR;
      min_deltaPhi=dPhi;
      min_deltaEta=dEta;
      matchingSC = &(*iclus);
    }
  }

  // Similarly for EE SCs
  iclus = endcapSuperClusters->begin();
  for ( ; iclus != endcapSuperClusters->end(); iclus++) {

    GlobalPoint scPoint( iclus->x(), iclus->y(), iclus->z() );

    double dEta = 9999.;
    double dPhi = 9999.;
    double dR = extrapolateAndDeltaR( tTrack, scPoint, dEta, dPhi );

    if (dR<min_deltaR) {
      min_deltaR=dR;
      min_deltaPhi=dPhi;
      min_deltaEta=dEta;
      matchingSC = &(*iclus);
    }
  }

  bool caloMatch = (min_deltaR<deltaRcut);
  if( caloMatch ) return matchingSC;

  return 0;
}

// Extrapolate track to surface given by SC and return delta R between two points
const double LeptonAnalysis::extrapolateAndDeltaR( const reco::TransientTrack & tTrack,
    const GlobalPoint & point, double &deltaEta, double &dPhi )
{

  // Extrapolate track to surface of a point
  TrajectoryStateOnSurface trajOnSurface = tTrack.stateOnSurface( point );

  if ( !trajOnSurface.isValid() ) return 9999;

  GlobalPoint trackPositionAtSurface = trajOnSurface.globalPosition();

  // Calculate deltaEta and deltaPhi
  deltaEta=point.eta()-trackPositionAtSurface.eta();
  dPhi=deltaPhi( point.phi(), trackPositionAtSurface.phi() );

  // Return deltaR between two points
  return deltaR( point, trackPositionAtSurface  );
}

/// Check if the triggers selected via cfg are firing for this event.
bool LeptonAnalysis::doTrigger(const edm::Event& iEvent)
{
  // PAT trigger information
  edm::Handle< pat::TriggerEvent > triggerEvent;
  iEvent.getByLabel( triggerEvent_, triggerEvent );
  if (triggerEvent.failedToGet()) {
    std::cout << "WARNING: no TriggerEvent found" << std::endl;
    return false;
  }

  bool takeAllPaths = (hltPaths_.size() == 1 && hltPaths_[0] == "*");
  // now loop over all paths etc and fill histogram for each one that was found
  triggers_.clear();
  for (unsigned i=0; i<triggerEvent->acceptedPaths().size(); i++) {
    std::string trigname(triggerEvent->acceptedPaths()[i]->name());
    ++trigPathSummary_[trigname];
    for (unsigned itrg=0; itrg<hltPaths_.size(); itrg++) {
      if ( hltPaths_[itrg]=="*" ) takeAllPaths=true;
      if( takeAllPaths || trigname==hltPaths_[itrg] ) {
        // FIXME: might want to select a reduced number of triggers to save space in the tree.
        triggers_.push_back(trigname);
      }
    }
  }
  return (triggers_.size()>0);
}

/// Return the closest stable genParticle in deltaR
int LeptonAnalysis::getGenParticleMatch(const edm::Handle<edm::View<reco::GenParticle> > & mcParticles,
    const PseudoLepton& lepton)
{
  double minDeltaR=999;
  int genIndex=-999;

  //  std::cout << "---> Lepton" << std::endl;
  //  std::cout << "Pt of lepton : " << lepton.pt() << std::endl;
  //  std::cout << "Eta, phi of particle : " << lepton.eta() << " " << lepton.phi() << std::endl;
  //  std::cout << "px, py, pz : " << lepton.px() << " " << lepton.py() << " " << lepton.pz() << std::endl;
  //
  //
  //  std::cout << "---> Gen Particles" << std::endl;
  // Loop over genParticles
  for (unsigned imc=0; imc<mcParticles->size(); imc++) {
    reco::GenParticle mcPart=(*mcParticles)[imc];

    // Only choose status == 1 particles
    if (mcPart.status()==3) continue;

    // Ignore neutral genParticles, as we are looking for charged leptons
    // FIXME will probably be terrible for photons
    if (mcPart.charge()==0) continue;

    // Ignore particles which decay further - check this?
    if (mcPart.numberOfDaughters()>0) continue;

    const reco::Candidate * origin = signalOrigin(&mcPart);
    if ( fabs(mcPart.pdgId()) == 13 && origin!=NULL ) {
      //      std::cout << "Gen particle muon pt : " << mcPart.pt() << std::endl;
      //      std::cout << "px, py, pz : " << mcPart.px() << " " << mcPart.py() << " " << mcPart.pz() << std::endl;
      //
      //      std::cout << "Origin of particle : " << origin->pdgId() << std::endl;


    }

    // Calculate deltaR between this genParticle and the lepton
    // For pseudoleptons, the lepton is a track which is extrapolated back to the beamline
    // Is this the same for genParticles?
    double dR=deltaR(lepton.eta(),lepton.phi(),mcPart.eta(),mcPart.phi());
    if (dR<minDeltaR) {
      minDeltaR=dR;
      genIndex=imc;

      //      std::cout << "-----> Delta R : " << dR << std::endl;

    }
  }
  if (minDeltaR<0.1) {
    return genIndex;
  } else {
    return -999;
  }
}

/// Compute the sumPt in a cone. This is absolute isolation.
double LeptonAnalysis::trackerIsolation(const edm::Event& iEvent,
    const reco::Track & plept,
    const reco::Track & pveto)
{
  // FIXME: move to relative isolation
  // FIXME: move the Handle outside and pass it as an argument

  // get PseudoLepton collection. these are high quality tracks
  // and standalone muons. we will only use the tracks for isolation, not muons.
  edm::Handle< PseudoLeptonCollection > trackCollection;
  iEvent.getByLabel( leptonCollTag_[__lepTypeTrack], trackCollection );
  if (trackCollection.failedToGet()) {
    std::cout << "WARNING: PseudoLepton collection not found" << std::endl;
    return -1;
  }

  // loop over all tracks and get deltaR with respect to both leptons
  double sumPt=0;
  for (PseudoLeptonCollection::const_iterator trk=trackCollection->begin();
      trk!=trackCollection->end(); trk++) {
    if (trk->isStandAloneMuon()) continue;
    double deltaRlept=deltaR(plept.eta(),plept.phi(),trk->eta(),trk->phi());
    double deltaRveto=deltaR(pveto.eta(),pveto.phi(),trk->eta(),trk->phi());
    if (deltaRlept<0.3 && deltaRlept>0.03 && deltaRveto>0.03) {
      // inside isolation code, but not close enough to any of the two tracks to suspect
      // that this might actually be one of the two tracks
      sumPt+=trk->pt();
    }
  }
  return sumPt;
}

/// Convert to a transient track and assign the beamspot.
reco::TransientTrack LeptonAnalysis::leptonTrack(const PseudoLepton &track)
{
  reco::TransientTrack ttrack=trackBuilder_->build(track);
  ttrack.setBeamSpot(beamSpot_);
  return ttrack;
}

/// Convert to a transient track and assign the beamspot.
reco::TransientTrack LeptonAnalysis::leptonTrack(const pat::Electron &electron)
{
  if (!electron.gsfTrack().isNull()) {
    reco::TransientTrack ttrack=trackBuilder_->build(electron.gsfTrack());
    ttrack.setBeamSpot(beamSpot_);
    return ttrack;
  }
  // FIXME
  return reco::TransientTrack();
}

/// Convert to a transient track and assign the beamspot. Take innerTrack if available or outerTrack otherwise.
reco::TransientTrack LeptonAnalysis::leptonTrack(const pat::Muon &muon)
{
  if (!muon.innerTrack().isNull()) {
    reco::TransientTrack ttrack=trackBuilder_->build(muon.innerTrack());
    ttrack.setBeamSpot(beamSpot_);
    return ttrack;
  } else if (!muon.outerTrack().isNull()) {
    reco::TransientTrack ttrack=trackBuilder_->build(muon.outerTrack());
    ttrack.setBeamSpot(beamSpot_);
    return ttrack;
  }
  // FIXME
  return reco::TransientTrack();
}

/// Convert to a transient track and assign the beamspot.
reco::TransientTrack LeptonAnalysis::leptonTrack(const pat::Tau &tau)
{
  if (!tau.leadTrack().isNull()) {
    reco::TransientTrack ttrack=trackBuilder_->build(tau.leadTrack());
    ttrack.setBeamSpot(beamSpot_);
    return ttrack;
  }
  // FIXME
  return reco::TransientTrack();
}

///// lepton IDs are specific to lepton type, but we provide a default template here
//template<class Lepton>
//bool LeptonAnalysis::leptonID(const Lepton& lepton)
//{
//    return true;
//}
//
///// override template for the electron channel, where we do use a specific ID requirement
//bool LeptonAnalysis::leptonID(const pat::Electron& electron)
//{
//  return int(electron.electronID("eidLoose"))&1;
//}

/// Default method, returns -999
double LeptonAnalysis::leptonTiming(const PseudoLepton &track)
{
  return -999;
}

/// Not implemented, returns -999
double LeptonAnalysis::leptonTiming(const pat::Electron &electron)
{
  //DetId seedDetID = electron->superCluster()->seed()->seed();
  return -999;
}

/// Muon timing. Assumes muon coming from inside the detector and has beta == 1
double LeptonAnalysis::leptonTiming(const pat::Muon &muon)
{
  if (muon.isTimeValid()) {
    // use time under the assumption the muon came from inside of the detector
    // and had beta==1.
    return muon.time().timeAtIpInOut;
  } else {
    return -999;
  }
}

/// Not implemented, returns -999
double LeptonAnalysis::leptonTiming(const pat::Tau &tau)
{
  // not implemented
  return -999;
}

void LeptonAnalysis::fillDipseudoleptonCandidates(const edm::Event& iEvent)
{
  // Find candidates
  // ---------------
  // first loop over the saved leptons
  for (unsigned ipart1=0; ipart1<candidates_.leptons_.size(); ++ipart1) {

    // second loop over saved leptons
    for (unsigned ipart2=ipart1+1; ipart2<candidates_.leptons_.size(); ++ipart2) {

      // Get leptons
      TreeLepton highPtLepton = candidates_.leptons_[ipart1];
      TreeLepton lowPtLepton = candidates_.leptons_[ipart2];

      // Tracks must be valid
      if ( !( highPtLepton.validTrack && lowPtLepton.validTrack ) ) continue;

      // Make a candidate
      candidates_.candidates_.push_back(TreeDipseudoLeptonCandidate());
      TreeDipseudoLeptonCandidate & candidate = candidates_.candidates_.back();

      // Work out which is high/low pt lepton
      if (highPtLepton.pt<lowPtLepton.pt) {
        highPtLepton=candidates_.leptons_[ipart2];
        lowPtLepton=candidates_.leptons_[ipart1];
      }

      // Get original pseudoleptons
      edm::Handle<edm::View<PseudoLepton> > particles;
      iEvent.getByLabel(leptonCollTag_[__lepTypeTrack],particles);
      PseudoLepton highPtPseudoLepton = particles->at(highPtLepton.pseudoLeptonIndex);
      PseudoLepton lowPtPseudoLepton = particles->at(lowPtLepton.pseudoLeptonIndex);

      // Get original tTrack
      reco::TransientTrack tTrackHighPtLepton = leptonTrack(highPtPseudoLepton);
      reco::TransientTrack tTrackLowPtLepton = leptonTrack(lowPtPseudoLepton);

      // Lepton isolation taking account of other lepton in candidate
      candidate.leptonIsoL = trackerIsolation(iEvent,tTrackLowPtLepton.track(),tTrackHighPtLepton.track());
      candidate.leptonIsoH = trackerIsolation(iEvent,tTrackHighPtLepton.track(),tTrackLowPtLepton.track());

      // Lepton index
      candidate.leptonIndexL = lowPtLepton.index;
      candidate.leptonIndexH = highPtLepton.index;

      // Different TO
      candidate.differentTO = ( lowPtLepton.triggerObjectIndex == highPtLepton.triggerObjectIndex ) ? 0 : 1;

      // ---------- //
      // Vertex fit //
      // ---------- //

      // Gather transient tracks
      std::vector<reco::TransientTrack> fitTracks;
      fitTracks.push_back(tTrackLowPtLepton);
      fitTracks.push_back(tTrackHighPtLepton);
      bool validTracks = (fitTracks[0].isValid() && fitTracks[1].isValid());
      if( !validTracks ) continue;

      // Perform vertex fit if tracks are valid
      if (validTracks) {
        TransientVertex leptonVertex;
        try {
          leptonVertex = vertexFitter_->vertex(fitTracks);
          candidate.validVertex=leptonVertex.isValid();
        } catch(cms::Exception& e) {};

        // Save if vertex is valid
        if (leptonVertex.isValid()) {
          candidate.validVertex=1;

          // Vertex Chi^2
          candidate.vertexChi2 = leptonVertex.normalisedChiSquared();

          // Get refitted lepton tracks
          reco::TransientTrack refittedTrackLowPt(leptonVertex.refittedTrack(tTrackHighPtLepton));
          reco::TransientTrack refittedTrackHighPt(leptonVertex.refittedTrack(tTrackLowPtLepton));

          // Angle between leptons
          // Use original unrefitted tracks
          reco::TrackBase::Vector mom1 = tTrackLowPtLepton.track().momentum();
          reco::TrackBase::Vector mom2 = tTrackHighPtLepton.track().momentum();
          candidate.cosine = mom1.Dot(mom2)/mom1.R()/mom2.R();
          candidate.deltaR = deltaR<reco::TrackBase::Vector,reco::TrackBase::Vector>(mom1,mom2);

          // Refitted lepton track quantites
          candidate.leptonPtL = refittedTrackLowPt.track().pt();
          candidate.leptonPtH = refittedTrackHighPt.track().pt();
          candidate.leptonEtaL = refittedTrackLowPt.track().eta();
          candidate.leptonEtaH = refittedTrackHighPt.track().eta();
          candidate.leptonChargeL = refittedTrackLowPt.track().charge();
          candidate.leptonChargeH = refittedTrackHighPt.track().charge();

          try {
            candidate.leptonD0L = refittedTrackLowPt.stateAtBeamLine().transverseImpactParameter().value();
            candidate.leptonD0SignificanceL = refittedTrackLowPt.stateAtBeamLine().transverseImpactParameter().significance();
            candidate.leptonD0H = refittedTrackHighPt.stateAtBeamLine().transverseImpactParameter().value();
            candidate.leptonD0SignificanceH = refittedTrackHighPt.stateAtBeamLine().transverseImpactParameter().significance();
          } catch (cms::Exception& e) {
            candidate.leptonD0L = -9999;
            candidate.leptonD0SignificanceL = -9999;
            candidate.leptonD0H = -9999;
            candidate.leptonD0SignificanceH = -9999;
          };


          double leptonMass=0.;
          // For electrons
          if (leptonName_=="etrack" || leptonName_=="electron") leptonMass=0.000511;
          // For muons
          if (leptonName_=="mutrack" || leptonName_=="muon") leptonMass=0.106;

          // calculate p_t corrected invariant mass
          ROOT::Math::PxPyPzMVector totalMom(0,0,0,0);
          ROOT::Math::PxPyPzMVector caloCorrectedMom(0,0,0,0);

          // Refitted tracks p4
          ROOT::Math::PxPyPzMVector refittedTrackMomLowPt(refittedTrackLowPt.track().px(),refittedTrackLowPt.track().py(),
              refittedTrackLowPt.track().pz(),leptonMass);
          ROOT::Math::PxPyPzMVector refittedTrackMomHighPt(refittedTrackHighPt.track().px(),refittedTrackHighPt.track().py(),
              refittedTrackHighPt.track().pz(),leptonMass);
          // Refitted momentum
          totalMom = refittedTrackMomLowPt + refittedTrackMomHighPt;
          // Calo corrected momentum
          if( lowPtLepton.hasCaloMatch != 0 ) caloCorrectedMom +=
              (lowPtLepton.scEnergy/refittedTrackLowPt.track().p())*(refittedTrackMomLowPt);
          else caloCorrectedMom += refittedTrackMomLowPt;
          if( highPtLepton.hasCaloMatch != 0 ) caloCorrectedMom +=
              (highPtLepton.scEnergy/refittedTrackHighPt.track().p())*(refittedTrackMomHighPt);
          else caloCorrectedMom += refittedTrackMomHighPt;

          candidate.mass = (refittedTrackMomLowPt+refittedTrackMomHighPt).mass();
          candidate.corrDileptonMass = totalMom.M();
          candidate.caloCorrMass = caloCorrectedMom.M();

          // decay length and significance
          // FIXME: this could be not very appropriate for standAloneMuons with big displacements (>~ 1 m).
          VertexDistanceXY vertTool;
          Measurement1D vertexDist = vertTool.distance(leptonVertex.vertexState(),primaryVertex_);
          candidate.decayLength = vertexDist.value();
          candidate.decayLengthSignificance = vertexDist.significance();

          // vertex flight direction vs dilepton momentum direction
          GlobalVector vertexDir = leptonVertex.position() - primaryVertex_.position();
          ROOT::Math::PxPyPzMVector diLeptonMom = refittedTrackMomLowPt+refittedTrackMomHighPt;
          candidate.dPhi= fabs(deltaPhi<GlobalVector, ROOT::Math::PxPyPzMVector>(vertexDir, diLeptonMom));
          candidate.dPhiCorr = fabs(deltaPhi<GlobalVector, ROOT::Math::PxPyPzMVector>(vertexDir, totalMom));
          candidate.dPhiCaloCorr = fabs(deltaPhi<GlobalVector, ROOT::Math::PxPyPzMVector>(vertexDir, caloCorrectedMom));

          // Candidate poistion
          candidate.vx = leptonVertex.position().x();
          candidate.vy = leptonVertex.position().y();
          candidate.vz = leptonVertex.position().z();

          // general kinematic information about candidate
          candidate.pt=diLeptonMom.pt();
          candidate.eta=diLeptonMom.eta();
          candidate.phi=diLeptonMom.phi();
          candidate.ptCorr = totalMom.pt();
          candidate.etaCorr = totalMom.eta();
          candidate.phiCorr = totalMom.phi();
          candidate.ptCaloCorr = caloCorrectedMom.pt();
          candidate.etaCaloCorr = caloCorrectedMom.eta();
          candidate.phiCaloCorr = caloCorrectedMom.phi();

          // Transverse mass calculation
          // For 3 body final states
          TLorentzVector p4SumReco( diLeptonMom.px(), diLeptonMom.py(), diLeptonMom.pz(), diLeptonMom.E() );
          TVector3 p3Exotic( vertexDir.x(), vertexDir.y(), vertexDir.z() );
          // This is the Pt of the dilepton w.r.t flight direction and hence also equal to Pt of neutrino
          float PtRelExoticDir = p4SumReco.Perp( p3Exotic );
          // Transverse energy of a particle is defined as sqrt(mass squared + pt squared)
          float sumEtRelExoticDir = sqrt(pow(p4SumReco.M(),2) + pow(PtRelExoticDir,2)) + PtRelExoticDir;
          float sumPt = 0.0; // Since dilepton and neutrino have opposite Pt relative to flight direction.
          // Transverse mass of particle pair is defined as sqrt(transverse energy squared - pt squared)
          float Mt = sqrt(pow(sumEtRelExoticDir, 2) - pow(sumPt, 2));
          candidate.transverseMass = Mt;

          //            // scale momenta to force dR=0 (phi component only).
          //            // we scale up because we assume
          //            // the momentum is underestimated due to energy loss
          //            double momScale=-(mom1.y()*vertexDir.x()-mom1.x()*vertexDir.y())/(mom2.y()*vertexDir.x()-mom2.x()*vertexDir.y());
          //            if (momScale>1) {
          //              candidate.scaleCorrMass=((*(part1.p4))+momScale*(*(part2.p4))).mass();
          //            } else {
          //              candidate.scaleCorrMass=((*(part1.p4))/momScale+(*(part2.p4))).mass();
          //            }

          //            // angle between positive lepton momentum in dilepton rest frame and dilepton momentum
          //            math::XYZTLorentzVector positiveMom;
          //            if (part1.transientTrack.track().charge()>0) positiveMom = *(part1.p4); else positiveMom = *(part2.p4);
          //            ROOT::Math::Boost boost;
          //            boost.SetComponents(-diLeptonMom/diLeptonMom.E());
          //            math::XYZTLorentzVector cmsMom = boost(positiveMom);
          //            candidate.cosThetaStar = TMath::Cos(angle<math::XYZTLorentzVector,math::XYZTLorentzVector>
          //            (diLeptonMom,cmsMom));
          //

          int hitsBeforeVertex[2];
          int missedLayersAfterVertex[2];
          if( fitTracks.size() != 2 ) {
            std::cout << "fitTracks size = " << fitTracks.size() << std::endl;
          }

          // Check hit pattern
          for (unsigned i=0; i<fitTracks.size(); i++) {
            std::pair<unsigned int, unsigned int> hitPat
            = checkHitPattern_->analyze(fitTracks[i].track(),leptonVertex);
            // first number: number of hits before vertex
            // second number: number of missed layers after vertex
            hitsBeforeVertex[i] = int(hitPat.first);
            missedLayersAfterVertex[i] = int(hitPat.second);
          }

          candidate.hitsBeforeVertexL = hitsBeforeVertex[0];
          candidate.hitsBeforeVertexH = hitsBeforeVertex[1];
          candidate.missedLayersAfterVertexL = missedLayersAfterVertex[0];
          candidate.missedLayersAfterVertexH = missedLayersAfterVertex[1];
        }
      }

//      // Gen info
//      if( lowPtLepton.genPdgId != 0 ) candidate.pdgIdL = leptons_[iLowPt].genPart->pdgId();
//      if( highPtLepton.genPdgId != 0 ) candidate.pdgIdH = leptons_[iHighPt].genPart->pdgId();
//      if( lowPtLepton.genSignalOriginPdgId != 0 ) candidate.originPdgIdL = leptons_[iLowPt].motherPart->pdgId();
//      if( highPtLepton.genSignalOriginPdgId != 0 ) candidate.originPdgIdH = leptons_[iHighPt].motherPart->pdgId();
//      if( lowPtLepton.genSignalOriginPdgId != 0 && (lowPtLepton.genSignalOriginPdgId == highPtLepton.genSignalOriginPdgId) ) {
//        GenEventProperties::DecayLengthAndType dlt(GenEventProperties::getDecayLengthAndType(*(leptons_[iLowPt].genPart)));
//        candidate.genDecayLength2D = dlt.decayLength2D;
//        candidate.genDecayLength3D = dlt.decayLength3D;
//        candidate.genctau = dlt.ctau;
//      }
    }
  }
}

void LeptonAnalysis::fillDiphotonCandidates(const edm::Event& iEvent)
{

  // Find diphoton candidates
  // -------------------------
  // first loop over the saved photons
  for (unsigned ipart1=0; ipart1<candidates_.photons_.size(); ++ipart1) {

    // second loop over saved leptons
    for (unsigned ipart2=ipart1+1; ipart2<candidates_.photons_.size(); ++ipart2) {

      // Get photons
      // Commented for now so we don't get build warnings
      // Will go away once they actually get used
      //      TreePhoton highPtPhoton = candidates_.photons_[ipart1];
      //      TreePhoton lowPtPhoton = candidates_.photons_[ipart2];

      // Do some vertex finding etc.

      // If you then decide to save this candidate...
      // Make a candidate
      candidates_.diphotonCandidates_.push_back(TreeDiphotonCandidate());
      TreeDiphotonCandidate & candidate = candidates_.diphotonCandidates_.back();

      // Fill with garbage for now
      candidate.mass=148;

      candidate.vertex_x=25;
      candidate.vertex_y=10;
      candidate.vertex_z=4;

      candidate.decayLength=26.9;
    }

  }
}

void LeptonAnalysis::fillDijetCandidates(const edm::Event& iEvent)
{

}

const reco::Candidate* LeptonAnalysis::signalOrigin(const reco::Candidate* part)
{
  const reco::Candidate* cand = part;
  const reco::Candidate* found2 = NULL;
  const reco::Candidate* found3 = NULL;

  // Whilst you still have a candidate but it's not status 3
  while (cand!=0 && !found3) {
    // Does this have the signal pdgid?
    if (find(signalPDGId_.begin(), signalPDGId_.end(), abs(cand->pdgId())) != signalPDGId_.end() ) {
      // Is it status 3?  If not, still found the status 2 particle
      if (cand->status()==3) found3=cand; else found2=cand;
    }
    // Move on to next mother
    cand=cand->mother();
  }

  if (found3) return found3; else return found2;
}

//int LeptonAnalysis::decayChannel(const reco::Candidate& part)
//{
//  // first check direct descendants
//  for (unsigned i=0; i<part.numberOfDaughters(); i++) {
//    const reco::Candidate* daughter = part.daughter(i);
//    int pid = abs(daughter->pdgId());
//    if (pid==11 || pid==13 || pid==15) return pid;
//  }
//  return 0;
//}

void LeptonAnalysis::beginJob()
{
  vertexFitter_ = new KalmanVertexFitter(true);
}

void LeptonAnalysis::endJob() 
{
  // cut flow histograms
  std::string name=leptonName_;

  // print trigger summary information. use a stupid simple sort algorithm
  std::cout << "===========================================================" << std::endl;
  std::cout << "=== TRIGGER SUMMARY =======================================" << std::endl;
  std::cout << "===========================================================" << std::endl;
  unsigned highestRate=numProcessedEvents_;
  while(highestRate>0) {
    unsigned nextLowest=0;
    for (std::map<std::string,unsigned int>::iterator it=trigPathSummary_.begin();
        it!=trigPathSummary_.end(); it++) {
      if (it->second==highestRate) {
        std::cout << "PATH " << std::setw(6) << it->second << "  " << it->first << std::endl;
      } else if (it->second<highestRate && it->second>nextLowest) {
        nextLowest=it->second;
      }
    }
    highestRate=nextLowest;
  }
  std::cout << "===========================================================" << std::endl;
  highestRate=numProcessedEvents_;
  while(highestRate>0) {
    unsigned nextLowest=0;
    for (std::map<std::string,unsigned int>::iterator it=trigFilterSummary_.begin();
        it!=trigFilterSummary_.end(); it++) {
      if (it->second==highestRate) {
        std::cout << "FILTER " << std::setw(6) << it->second << "  " << it->first << std::endl;
      } else if (it->second<highestRate && it->second>nextLowest) {
        nextLowest=it->second;
      }
    }
    highestRate=nextLowest;
  }
  std::cout << "===========================================================" << std::endl;

  hTotalProcessedEvents_->SetBinContent(1, numProcessedEvents_);
  hEventsPassingEventsFilter_->SetBinContent(1, numEventsPassingEventFilters_);
  hEventsPassingTrigger_->SetBinContent(1, numEventsPassingTrigger_);
  fs_->cd();
  hTotalProcessedEvents_->Write();
  hEventsPassingEventsFilter_->Write();
  hEventsPassingTrigger_->Write();
}

void LeptonAnalysis::initializeVars()
{
  candidates_.clear();
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(LeptonAnalysis);
