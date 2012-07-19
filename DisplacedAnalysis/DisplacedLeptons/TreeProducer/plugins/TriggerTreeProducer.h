#ifndef TRIGGERTREEPRODUCER_H
#define TRIGGERTREEPRODUCER_H

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"

#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DisplacedLeptons/TreeProducer/interface/PseudoLepton.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

#include "DisplacedLeptons/Samples/interface/GenEventProperties.h"
#include "HarderAnalysisTools/Histograms/interface/HistMap.h"
#include "HarderAnalysisTools/CutManager/interface/CutSummary.h"
#include "HarderAnalysisTools/CheckHitPattern/interface/CheckHitPattern.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DisplacedLeptons/TreeProducer/interface/TriggerObject.h"
#include "DisplacedLeptons/TreeProducer/interface/GenParticle.h"

#include <map>


class TriggerTreeProducer : public edm::EDAnalyzer {

public:
  explicit TriggerTreeProducer(const edm::ParameterSet&);
  ~TriggerTreeProducer();

private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  GenEventProperties::DecayLengthAndType getDecayLengthAndType(const reco::Candidate &part);

  const reco::Candidate* signalOrigin(const reco::Candidate*);

  edm::InputTag generatorTag_;
  edm::InputTag pileupTag_;
  edm::InputTag genEventInfoTag_;
  edm::InputTag trigger_;
  edm::InputTag triggerEvent_;

  // analysis setup
  int signalPDGId_;
  int leptonPDGId_;
  std::vector<std::string> hltPaths_;

  bool useMCTruth_;

  // The tree with all the variables
  edm::Service<TFileService> fs_;
  TTree* outputTree_;

  Int_t event_;
  Int_t run_;
  std::vector<TriggerObject> triggerObjects_;
  std::vector<GenParticle> genParticles_;
  std::vector<std::string> triggers_;
//  Event event;
};


#endif // TRIGGERTREEPRODUCER_H
