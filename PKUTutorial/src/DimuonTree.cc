#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Candidate/interface/Particle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "zhenhu/PKUTutorial/interface/DimuonTree.h"

using namespace edm;
using namespace reco;
using namespace std;

DimuonTree::DimuonTree(const edm::ParameterSet& iConfig){
  theRootFileName = iConfig.getParameter<string>("OutputFile");
  hFile =  new TFile(theRootFileName.c_str(),"RECREATE");
}

void DimuonTree::beginJob(const edm::EventSetup& iSetup){
  hFile->cd("");
  tree_Upsilon = new TTree("UpsTree","UpsTree");
  tree_Upsilon->Branch("genMuSize",&genMuSize,"genMuSize/I");
  tree_Upsilon->Branch("genUpsSize",&genUpsSize,"genUpsSize/I");
  tree_Upsilon->Branch("recoMuSize",&recoMuSize,"recoMuSize/I");
  tree_Upsilon->Branch("genMuPt",genMuPt,"genMuPt[genMuSize]/F");
  tree_Upsilon->Branch("genMuEta",genMuEta,"genMuEta[genMuSize]/F");
  tree_Upsilon->Branch("genMuPhi",genMuPhi,"genMuPhi[genMuSize]/F");
  tree_Upsilon->Branch("genMuCharge",genMuCharge,"genMuCharge[genMuSize]/I");
  tree_Upsilon->Branch("genUpsPt",genUpsPt,"genUpsPt[genUpsSize]/F");
  tree_Upsilon->Branch("genUpsEta",genUpsEta,"genUpsEta[genUpsSize]/F");
  tree_Upsilon->Branch("genUpsPhi",genUpsPhi,"genUpsPhi[genUpsSize]/F");
  tree_Upsilon->Branch("genUpsRapidity",genUpsRapidity,"genUpsRapidity[genUpsSize]/F");
  tree_Upsilon->Branch("recoMuPt",recoMuPt,"recoMuPt[recoMuSize]/F");
  tree_Upsilon->Branch("recoMuEta",recoMuEta,"recoMuEta[recoMuSize]/F");
  tree_Upsilon->Branch("recoMuPhi",recoMuPhi,"recoMuPhi[recoMuSize]/F");
  tree_Upsilon->Branch("recoMuCharge",recoMuCharge,"recoMuCharge[recoMuSize]/I");
}

void DimuonTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  genMuSize = 0;
  genUpsSize = 0;
  Handle<GenParticleCollection> genParticles;
  iEvent.getByLabel(InputTag("genParticles"), genParticles);
  if(genParticles.isValid()){
    for(GenParticleCollection::const_iterator p=genParticles->begin(); p!= genParticles->end(); ++p){
      if( p->status() == 1 && abs(p->pdgId()) == 13 && (getMotherId(&(*p)) == 553 || getMotherId(&(*p)) == 100553) ){
        genMuPt[genMuSize] = p->pt();
        genMuEta[genMuSize] = p->eta();
        genMuPhi[genMuSize] = p->phi();
        genMuCharge[genMuSize] = p->charge();
        genMuSize++;
      }else if( p->status() == 2 && (p->pdgId() == 553 || p->pdgId() == 100553) ){
        genUpsPt[genUpsSize] = p->pt();
        genUpsEta[genUpsSize] = p->eta();
        genUpsPhi[genUpsSize] = p->phi();
        TLorentzVector genUps; genUps.SetPtEtaPhiM (p->pt(), p->eta(), p->phi(), 9.46);
        genUpsRapidity[genUpsSize] = genUps.Rapidity();
        genUpsSize++;
      }
    }
  }else{
    LogError("DimuonTree")<<"Could not access GenParticleCollection"<<endl;
//    exit(1);
  }

  recoMuSize = 0;
  Handle<TrackCollection> recoTracks;
  iEvent.getByLabel(InputTag("generalTracks"), recoTracks);
  if(recoTracks.isValid()){
    for(TrackCollection::const_iterator tk = recoTracks->begin(); tk != recoTracks->end(); ++tk){
      recoMuPt[recoMuSize] = tk->pt();
      recoMuEta[recoMuSize] = tk->eta();
      recoMuPhi[recoMuSize] = tk->phi();
      recoMuCharge[recoMuSize] = tk->charge();
      recoMuSize++;
    }
  }else{
    LogDebug("DimuonTree")<<"Could not access recoTrackCollection"<<endl;
//    exit(2);
  }
  
  tree_Upsilon->Fill();
}

void DimuonTree::endJob(){
  hFile->Write(); 
  hFile->Close();
}

DimuonTree::~DimuonTree(){
}

int DimuonTree::getMotherId( const Candidate * p ){
  const Candidate* mother = p->mother();
  if( mother ){
    if( mother->pdgId() == p->pdgId() ){
      return getMotherId(mother);
    }else{
      return mother->pdgId();
    }
  }else{
    return 0;
  }
}

//define this as a plug-in
DEFINE_FWK_MODULE(DimuonTree);
