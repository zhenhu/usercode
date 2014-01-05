// -*- C++ -*-
//
// Package:    PseudoLeptonFilter
// Class:      PseudoLeptonFilter
//
/**\class PseudoLeptonFilter PseudoLeptonFilter.cc TreeProducer/TreeProducer/plugins/PseudoLeptonFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Marco De Mattia
//         Created:  Fri Aug 31 12:12:00 GMT 2012
// $Id: PseudoLeptonFilter.cc,v 1.1 2012/05/24 11:53:57 demattia Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "TreeProducer/TreeProducer/interface/PseudoLepton.h"

#include "TrackingTools/Records/interface/TransientTrackRecord.h"


// Transient Tracks
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"

//
// class declaration
//

class PseudoLeptonFilter : public edm::EDFilter {
public:
  explicit PseudoLeptonFilter(const edm::ParameterSet&);
  ~PseudoLeptonFilter();

private:
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  void checkAndReplacePt12( const double & pt, double & pt1, double & pt2 );

  // ----------member data ---------------------------

  double minTrackPt1_, minTrackPt2_;
  double minTrackerMuonPt1_, minTrackerMuonPt2_;
  double minGlobalMuonPt1_, minGlobalMuonPt2_;
  double minStandAloneMuonPt1_, minStandAloneMuonPt2_;
  double minSuperClusterEt1_, minSuperClusterEt2_;
  double minD0Significance_;

  // beamspot
  reco::BeamSpot beamSpot_;

  edm::InputTag leptonCollTag_;
  edm::InputTag barrelSuperClusters_;
  edm::InputTag endcapSuperClusters_;
  edm::ESHandle<TransientTrackBuilder> trackBuilder_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
PseudoLeptonFilter::PseudoLeptonFilter(const edm::ParameterSet& iConfig) :
  minTrackPt1_(iConfig.getParameter<double>("minTrackPt1")),
  minTrackPt2_(iConfig.getParameter<double>("minTrackPt2")),
  minTrackerMuonPt1_(iConfig.getParameter<double>("minTrackerMuonPt1")),
  minTrackerMuonPt2_(iConfig.getParameter<double>("minTrackerMuonPt2")),
  minGlobalMuonPt1_(iConfig.getParameter<double>("minGlobalMuonPt1")),
  minGlobalMuonPt2_(iConfig.getParameter<double>("minGlobalMuonPt2")),
  minStandAloneMuonPt1_(iConfig.getParameter<double>("minStandAloneMuonPt1")),
  minStandAloneMuonPt2_(iConfig.getParameter<double>("minStandAloneMuonPt2")),
  minSuperClusterEt1_(iConfig.getParameter<double>("minSuperClusterEt1")),
  minSuperClusterEt2_(iConfig.getParameter<double>("minSuperClusterEt2")),
  minD0Significance_(iConfig.getParameter<double>("minD0Significance")),
  leptonCollTag_(iConfig.getParameter<edm::InputTag>("trackSrc")),
  barrelSuperClusters_(iConfig.getParameter<edm::InputTag>("barrelSuperClusters")),
  endcapSuperClusters_(iConfig.getParameter<edm::InputTag>("endcapSuperClusters"))
{
}


PseudoLeptonFilter::~PseudoLeptonFilter()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool PseudoLeptonFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle< PseudoLeptonCollection > trackCollection;
  iEvent.getByLabel( leptonCollTag_, trackCollection );
  if (trackCollection.failedToGet()) {
    std::cout << "WARNING: PseudoLepton collection not found" << std::endl;
    return -1;
  }

  // event setup
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder_);

  // get beamspot
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByLabel ("offlineBeamSpot", beamSpotHandle);
  beamSpot_=(*beamSpotHandle);

  double trackPt1 = 0.;
  double trackPt2 = 0.;
  double trackerMuonPt1 = 0.;
  double trackerMuonPt2 = 0.;
  double globalMuonPt1 = 0.;
  double globalMuonPt2 = 0.;
  double standAloneMuonPt1 = 0.;
  double standAloneMuonPt2 = 0.;
  PseudoLeptonCollection::const_iterator it = trackCollection->begin();
  int passingD0SignificanceCut = 0;
  for( ; it != trackCollection->end(); ++it ) {
    reco::TransientTrack tTrack=trackBuilder_->build(*it);
    tTrack.setBeamSpot(beamSpot_);
  	if( fabs(tTrack.stateAtBeamLine().transverseImpactParameter().significance()) < minD0Significance_ ) continue;
    ++passingD0SignificanceCut;
    if( it->isTrackerMuon() ) checkAndReplacePt12( it->pt(), trackerMuonPt1, trackerMuonPt2 );
    else if( it->isGlobalMuon() ) checkAndReplacePt12( it->pt(), globalMuonPt1, globalMuonPt2 );
    else if( it->isStandAloneMuon() ) checkAndReplacePt12( it->pt(), standAloneMuonPt1, standAloneMuonPt2 );
    else checkAndReplacePt12( it->pt(), trackPt1, trackPt2 );
  }

  // Load superCluster collections if this is for electrons
  edm::Handle< std::vector<reco::SuperCluster> > barrelSuperClusters;
  edm::Handle< std::vector<reco::SuperCluster> > endcapSuperClusters;
  iEvent.getByLabel( barrelSuperClusters_, barrelSuperClusters );
  if (barrelSuperClusters.failedToGet()) {
  	std::cout << "WARNING: cannot access barrel superclusters for matching" << std::endl;
  }
  iEvent.getByLabel( endcapSuperClusters_, endcapSuperClusters );
  if (endcapSuperClusters.failedToGet()) {
  	std::cout << "WARNING: cannot access endcap superclusters for matching" << std::endl;
  }

  double superClusterEt1 = 0.;
  double superClusterEt2 = 0.;
  // Loop over EB SCs
  std::vector<reco::SuperCluster>::const_iterator iclus = barrelSuperClusters->begin();
  for ( ; iclus != barrelSuperClusters->end(); iclus++) {
  	checkAndReplacePt12(iclus->energy() * sin( iclus->position().theta() ), superClusterEt1, superClusterEt2 );
  }

  // Similarly for EE SCs
  iclus = endcapSuperClusters->begin();
  for ( ; iclus != endcapSuperClusters->end(); iclus++) {
  	checkAndReplacePt12(iclus->energy() * sin( iclus->position().theta() ), superClusterEt1, superClusterEt2 );
  }

  // If there are not enough pseudoleptons passing the d0/sigma cut skip the event
  if( passingD0SignificanceCut < 2 ) return false;
  if( (trackPt1 > minTrackPt1_ && trackPt2 > minTrackPt2_) ||
      (trackerMuonPt1 > minTrackerMuonPt1_ && trackerMuonPt2 > minTrackerMuonPt2_) ||
      (globalMuonPt1 > minGlobalMuonPt1_ && globalMuonPt2 > minGlobalMuonPt2_) ||
      (globalMuonPt1 > minGlobalMuonPt1_ && trackerMuonPt2 > minTrackerMuonPt2_) ||
      (trackerMuonPt1 > minTrackerMuonPt1_ && globalMuonPt2 > minGlobalMuonPt2_) ||
      (standAloneMuonPt1 > minStandAloneMuonPt1_ && standAloneMuonPt2 > minStandAloneMuonPt2_) ||
      ( (superClusterEt1 > minSuperClusterEt1_ && superClusterEt2 > minSuperClusterEt2_ ) || (superClusterEt2 > minSuperClusterEt1_ && superClusterEt1 > minSuperClusterEt2_)  ) ) {
  	//  	std::cout << "passing with:" << std::endl;
  	//  	std::cout << "trackPt1 = " << trackPt1 << std::endl;
  	//  	std::cout << "trackPt2 = " << trackPt2 << std::endl;
  	//  	std::cout << "trackerMuonPt1 = " << trackerMuonPt1 << std::endl;
  	//  	std::cout << "trackerMuonPt2 = " << trackerMuonPt2 << std::endl;
  	//  	std::cout << "globalMuonPt1 = " << globalMuonPt1 << std::endl;
  	//  	std::cout << "globalMuonPt2 = " << globalMuonPt2 << std::endl;
  	//  	std::cout << "standAloneMuonPt1 = " << standAloneMuonPt1 << std::endl;
  	//  	std::cout << "standAloneMuonPt2 = " << standAloneMuonPt2 << std::endl;
  	//  	std::cout << "superClusterEt1 = " << superClusterEt1 << std::endl;
  	//  	std::cout << "superClusterEt2 = " << superClusterEt2 << std::endl;
  	return true;
  }
  return false;
}

void PseudoLeptonFilter::checkAndReplacePt12( const double & pt, double & pt1, double & pt2 ) {
  if( pt > pt1 ) {
    pt2 = pt1;
    pt1 = pt;
  }
  else if( pt > pt2 ) {
    pt2 = pt;
  }
}

//define this as a plug-in
DEFINE_FWK_MODULE(PseudoLeptonFilter);
