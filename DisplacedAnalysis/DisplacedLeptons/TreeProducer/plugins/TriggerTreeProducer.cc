#include "DisplacedLeptons/TreeProducer/plugins/TriggerTreeProducer.h"
#include "HarderAnalysisTools/GenParticleInfo/interface/GenParticleInfo.h"
#include "HarderAnalysisTools/CutManager/interface/CutFlow.h"

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

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/MuonReco/interface/MuonTime.h"

#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"

#include <sstream>
#include <iomanip>

// PAT
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/TriggerPath.h"
#include "DataFormats/PatCandidates/interface/TriggerFilter.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"


TriggerTreeProducer::TriggerTreeProducer(const edm::ParameterSet& iConfig):
  generatorTag_(iConfig.getParameter<edm::InputTag>("generatorSrc")),
  pileupTag_(edm::InputTag("addPileupInfo")),
  genEventInfoTag_(edm::InputTag("generator")),
  trigger_(iConfig.getParameter<edm::InputTag>("trigger")),
  triggerEvent_(iConfig.getParameter<edm::InputTag>("triggerEvent")),
  signalPDGId_(iConfig.getParameter<int>("signalPDGId")),
  leptonPDGId_(iConfig.getParameter<int>("leptonPDGId")),
  hltPaths_(iConfig.getParameter<std::vector<std::string> >("hltPaths")),
  useMCTruth_(iConfig.getParameter<bool>("UseMCTruth"))
{
  // introduce short dCache read timeout to work around problems at RAL
  TDCacheFile::SetOpenTimeout(1800);

  // Create the tree
  edm::Service<TFileService> fs_;
  outputTree_ = fs_->make<TTree>("outputTree","outputTree");
  outputTree_->Branch("event",&event_,"event/I");
  outputTree_->Branch("run",&run_,"run/I");
  outputTree_->Branch("Triggers","std::vector<std::string>",&triggers_, 32000, 0);
  outputTree_->Branch("TriggerObjects","std::vector<TriggerObject>",&triggerObjects_, 32000, 0);
  outputTree_->Branch("GenParticles","std::vector<GenParticle>",&genParticles_, 32000, 0);
}


TriggerTreeProducer::~TriggerTreeProducer()
{
}


void TriggerTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  run_ = iEvent.run();
  event_ = iEvent.id().event();
  triggerObjects_.clear();
  genParticles_.clear();
  triggers_.clear();

  // PAT trigger information
  edm::Handle< pat::TriggerEvent > triggerEvent;
  iEvent.getByLabel( triggerEvent_, triggerEvent );
  if (triggerEvent.failedToGet()) {
    std::cout << "WARNING: no TriggerEvent found" << std::endl;
//    return false;
  }

  bool takeAllPaths = (hltPaths_.size() == 1 && hltPaths_[0] == "*");
  // now loop over all paths etc

  // for (unsigned i=0; i<triggerEvent->paths()->size(); i++) {
  for (unsigned i=0; i<triggerEvent->acceptedPaths().size(); i++) {
    std::string trigname(triggerEvent->acceptedPaths()[i]->name());
    // std::string trigname((*triggerEvent->paths())[i].name());
    bool found = false;
    if (takeAllPaths) found = true;
    else {
      for (unsigned itrg=0; itrg<hltPaths_.size(); itrg++) {
        if( trigname==hltPaths_[itrg] ) {
          found = true;
          break;
        }
      }
    }
    if (found) {
      triggers_.push_back(trigname);
      // if( (*triggerEvent->paths())[i].wasAccept() ) triggers_.push_back(trigname);
      const pat::TriggerObjectRefVector triggerObjects(triggerEvent->pathObjects(trigname,false));
//      if( triggerObjects.size() > 0 ) {
//        std::cout << "number of trigger objects for trigger " << trigname << " = " << triggerObjects.size() << std::endl;
//      }
      for (unsigned i=0; i<triggerObjects.size(); i++) {
        triggerObjects_.push_back(TriggerObject(triggerObjects[i]->pt(), triggerObjects[i]->eta(), triggerObjects[i]->phi()));
        triggerObjects_.back().triggerName = trigname;
      }
    }
  }

  // Load gen particles or set the flag to false if they are not available
  edm::Handle<edm::View<reco::GenParticle> > mcParticles;
  if( useMCTruth_ ) {
    iEvent.getByLabel(generatorTag_,mcParticles);
    if(mcParticles.failedToGet()) {
      std::cout << "WARNING: cannot access MC truth information." << std::endl;
    }

    for (unsigned imc=0; imc<mcParticles->size(); imc++) {
      reco::GenParticle mcPart=(*mcParticles)[imc];
      if (mcPart.status()==3) continue;
      if (mcPart.charge()==0) continue;
      if (mcPart.numberOfDaughters()>0) continue;
      int pdgId = abs(mcPart.pdgId());
      // Selecting only muons or electrons
      if (pdgId != 13 && pdgId != 11) continue;
      genParticles_.push_back(GenParticle());
      genParticles_.back().pt = mcPart.pt();
      genParticles_.back().eta = mcPart.eta();
      genParticles_.back().phi = mcPart.phi();
      genParticles_.back().pdgId = mcPart.pdgId();
//      if (mcPart.mother() != 0) {
//        std::cout << "mother pid = " << mcPart.mother()->pdgId() << std::endl;
//      }
      const reco::Candidate * motherPtr = signalOrigin(&mcPart);
      if( motherPtr != NULL ) {
        genParticles_.back().motherPdgId = motherPtr->pdgId();
        GenEventProperties::DecayLengthAndType dlt(getDecayLengthAndType(*motherPtr));
        genParticles_.back().decayLength2D = dlt.decayLength2D;
        genParticles_.back().decayLength3D = dlt.decayLength3D;
        genParticles_.back().ctau = dlt.ctau;
      }
    }
  }
  outputTree_->Fill();
}

GenEventProperties::DecayLengthAndType TriggerTreeProducer::getDecayLengthAndType(const reco::Candidate & part)
{
  reco::Candidate::Point productionVertex = part.vertex();
  // decay products and decay vertex
  reco::Candidate::Point decayVertex=productionVertex;
  int decay_pid=0;
  // std::cout << "number of daugthers = " << part.numberOfDaughters() << std::endl;
  for (unsigned i=0; i<part.numberOfDaughters(); i++) {
    const reco::Candidate* daughter = part.daughter(i);
    // std::cout << "found daughter with pid = " << daughter->pdgId() << std::endl;
    int pid = abs(daughter->pdgId());
    if (pid==11 || pid==13 || pid==15) {
      decay_pid=pid;
      // note that original MC signal particle and decay products
      // are in documentation lines (Pythia status 3) and the actual
      // decay length is only available in the actual decay tree
      // (Pythia status 2). The corresponding status 2 particle for each
      // status 3 particle is referenced by a daughter link.
      if (daughter->numberOfDaughters()>0) {
        decayVertex=daughter->daughter(0)->vertex();
      }
    }
  }
  double distance = (decayVertex-productionVertex).r();
  return GenEventProperties::DecayLengthAndType(decay_pid,
                                                (decayVertex-productionVertex).rho(),
                                                distance,
                                                distance*part.p4().M()/part.p4().P());
}

const reco::Candidate* TriggerTreeProducer::signalOrigin(const reco::Candidate* part)
{
  const reco::Candidate* cand = part;
  const reco::Candidate* found2 = NULL;
  const reco::Candidate* found3 = NULL;
  while (cand!=0 && !found3) {
    if (abs(cand->pdgId())==signalPDGId_) {
      if (cand->status()==3) found3=cand; else found2=cand;
    }
    cand=cand->mother();
  }
  if (found3) return found3; else return found2;
}

void TriggerTreeProducer::beginJob()
{
}

void TriggerTreeProducer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TriggerTreeProducer);
