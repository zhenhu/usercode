#ifndef PseudoLepton_h
#define PseudoLepton_h

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

class PseudoLepton;
typedef std::vector<PseudoLepton>              PseudoLeptonCollection;
typedef edm::Ref<PseudoLeptonCollection>       PseudoLeptonRef;
typedef edm::RefVector<PseudoLeptonCollection> PseudoLeptonRefVector;

class PseudoLepton : public reco::Track {

 private:

  reco::Particle::LorentzVector p4_;
  const reco::GenParticle* genPart_;
  unsigned genPartSize_;
  bool isStandAloneMuon_;
  bool isGlobalMuon_;
  bool isTrackerMuon_;
  bool isLooseMuon_;
  bool isCentralTrack_;

 public:

  PseudoLepton();
  PseudoLepton(const reco::Track & aTrack);
  virtual ~PseudoLepton();
  
  /// required reimplementation of the Candidate's clone method
  virtual PseudoLepton * clone() const { return new PseudoLepton(*this); }

  /// stuff that we need that is not in reco::Track
  const reco::Particle::LorentzVector& p4() const { return p4_; };
  const reco::GenParticle* genParticle(unsigned i=0) const { if (genPartSize_) return genPart_; else return 0; };
  unsigned genParticlesSize() const { return genPartSize_; };
  bool isTrackerMuon() const { return isTrackerMuon_; };
  bool isGlobalMuon() const { return isGlobalMuon_; };
  bool isStandAloneMuon() const { return isStandAloneMuon_; };
  bool isLooseMuon() const { return isLooseMuon_; };
  bool isCentralTrack() const { return isCentralTrack_; };

  void isStandAloneMuon(bool isMuon) { isStandAloneMuon_=isMuon; };
  void isGlobalMuon(bool isMuon) { isGlobalMuon_=isMuon; };
  void isTrackerMuon(bool isMuon) { isTrackerMuon_=isMuon; };
  void isCentralTrack( bool isTrack) { isCentralTrack_=isTrack; };
  void isLooseMuon( bool isLooseMuon ) { isLooseMuon_=isLooseMuon; };
  void setGenParticle(const reco::GenParticle& gen) { genPart_=&gen; genPartSize_=1; };

};



#endif
