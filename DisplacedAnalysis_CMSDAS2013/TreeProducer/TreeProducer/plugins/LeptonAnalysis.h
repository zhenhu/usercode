#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// Transient Tracks
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"

// For track extrapolation
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"

#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "TreeProducer/TreeProducer/interface/PseudoLepton.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

#include "TreeProducer/TreeProducer/interface/GenEventProperties.h"
#include "TreeProducer/CheckHitPattern/interface/CheckHitPattern.h"

#include "TTree.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <map>

#include "TreeProducer/TreeProducer/interface/Candidates.h"
#include "TreeProducer/TreeProducer/interface/TreeLepton.h"
#include "TreeProducer/TreeProducer/interface/TreeDipseudoLeptonCandidate.h"

#include "TreeProducer/TreeProducer/interface/TreePhoton.h"
#include "TreeProducer/TreeProducer/interface/TreeDiphotonCandidate.h"

class LeptonAnalysis : public edm::EDAnalyzer {

  public:
  explicit LeptonAnalysis(const edm::ParameterSet&);
  ~LeptonAnalysis();

  private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  void endLuminosityBlock(const edm::LuminosityBlock & lumi, const edm::EventSetup & setup);
  virtual void endJob() ;

  // decay channels
  typedef enum { __lepTypeElectron,
    __lepTypeMuon,
    __lepTypeTau,
    __lepTypeTrack,
    __lepTypePhoton}
  leptonType;
  std::string leptonName_;


  // Useful, but leave out for now as unused
  //  // types of candidates that we distinguish
  //  typedef enum { __catSignal,             // fully reconstructed signal
  //                 __catSignalWrongChannel, // fully reconstructed signal, but wrong decay mode
  //                 __catSignalMixed,        // both leptons from signal, but wrong pairing
  //                 __catOneSigOneBkgWithGen,// one lepton from signal, one from unrelated GenParticle
  //                 __catOneSigOneBadReco,   // one lepton from signal, one without GenParticle at all
  //                 __catGoodButWrongType,   // fully reconstructed *other* resonance (e.g. Z)
  //                 __catBackground }        // both leptons are of non-signal origin
  //               categoryType;

  // FIXME
  // Or just checks it does what we want
  int getGenParticleMatch(const edm::Handle<edm::View<reco::GenParticle> > & mcParticles,
      const PseudoLepton& lepton);

  // FIXME
  // Unused at the moment
  //  int decayChannel(const reco::Candidate&);

  // Given a genParticle/Candidate, will see if this lepton comes from a signal MC particle
  const reco::Candidate* signalOrigin(const reco::Candidate*);

  // EVENT INFO
  // Fill info on event based quantities e.g. run, lumi, event, MET
  void fillEventBasedInfo(const edm::Event&,const edm::EventSetup&);

  // PSEUDO LEPTONS
  // Fill info on individual pseudoleptons e.g. d0, pt, calo & trigger match
  void fillPseudoLeptons(const edm::Event&);
  // Create and fill info on di-pseudolepton candidates e.g. Lxy, refitted pt of leptons
  void fillDipseudoleptonCandidates(const edm::Event&);

  // PHOTONS
  // Note: photons include electrons where the track hasn't been reconstructed
  // Fill info on individual photon candidates
  void fillPhotons(const edm::Event&);
  // Fill info on diphoton candidates
  void fillDiphotonCandidates(const edm::Event&);

  // JETS
  // Fill info on individual jet candidates
  void fillJets(const edm::Event&);
  // Fill info on dijet candidates
  void fillDijetCandidates(const edm::Event&);

  // Check if interesting trigger has fired in this event
  bool doTrigger(const edm::Event&);

  // Find a trigger match to a pseudolepton
  const reco::Particle::LorentzVector * findTrigMatch(const PseudoLepton & lepton,
      const edm::Handle< pat::TriggerEvent > & triggerEvent, double & deltaR );

  // OLD method for comparison
  const int findTrigMatch_OLD(const PseudoLepton & lepton,
      const edm::Handle< pat::TriggerEvent > & triggerEvent, double & deltaR );

  // Find a calo match to a pseudolepton
  const reco::SuperCluster * findCaloMatch(const PseudoLepton & lepton,
      const edm::Handle< std::vector<reco::SuperCluster> > & barrelSuperClusters,
      const edm::Handle< std::vector<reco::SuperCluster> > & endcapSuperClusters,
      double & deltaR, double & deltaEta, double & deltaPhi );

  // Extrapolate transient track to surface given by a global point and return delta R
  const double extrapolateAndDeltaR( const reco::TransientTrack & tTrack,
      const GlobalPoint & point, double & deltaEta, double & deltaPhi  );

  // OLD method for comparison
  const reco::SuperCluster * findCaloMatch_OLD(const PseudoLepton & lepton,
      const edm::Handle< std::vector<reco::SuperCluster> > & barrelSuperClusters,
      const edm::Handle< std::vector<reco::SuperCluster> > & endcapSuperClusters,
      double & deltaR );

  // FIXME
  // Unused, but could be good to apply/check any standard ID?
  //  template<class Lepton> bool leptonID(const Lepton&);
  //  bool leptonID(const pat::Electron&);


  // Computes absolute tracker isolation
  double trackerIsolation(const edm::Event& iEvent,
      const reco::Track & plept,
      const reco::Track & pveto);


  // FIX ME
  // At the moment, everything goes through the PseudoLepton method
  // Check implementation for muons
  reco::TransientTrack leptonTrack(const PseudoLepton &);
  reco::TransientTrack leptonTrack(const pat::Electron &);
  reco::TransientTrack leptonTrack(const pat::Muon &);
  reco::TransientTrack leptonTrack(const pat::Tau &);

  // Detector timing
  // No implementation yet
  double leptonTiming(const pat::Electron &);
  double leptonTiming(const pat::Muon &);
  double leptonTiming(const pat::Tau &);
  double leptonTiming(const PseudoLepton &);

  // Initialization
  void initializeVars();

  // beamspot
  reco::BeamSpot beamSpot_;

  // primary vertex
  VertexState primaryVertex_;


  // for displaced vertex fit
  edm::ESHandle<TransientTrackBuilder> trackBuilder_;
  KalmanVertexFitter* vertexFitter_;
  CheckHitPattern* checkHitPattern_;

  // FIXME
  // Unused
  // container for additional signal particle information
  //  typedef struct {
  //    double rt;
  //    double r;
  //    double ndaughters;
  //  } GenInfo_t;
  //  std::map<const reco::Candidate*,GenInfo_t*> GenInfoMap_;

  // input tags  
  edm::InputTag leptonCollTag_[4];
  edm::InputTag generatorTag_;
  edm::InputTag pileupTag_;
  edm::InputTag genEventInfoTag_;
  edm::InputTag trigger_;
  edm::InputTag triggerEvent_;
  edm::InputTag barrelSuperClusters_;
  edm::InputTag endcapSuperClusters_;

  // analysis setup
  std::vector<int> signalPDGId_;
  int leptonPDGId_;
  leptonType thisLepton_;
  std::vector<std::string> hltPaths_;

  // FIXME
  // We apply loose cut on track pt, which is ok for muon channel
  // Not ok for electron channel, should be on SC Et
  // selection cuts
  double leptonPtCut_;
  double leptonSCEtCut_;

  // Use MC Truth info?
  bool useMCTruth_;

  // trigger and event filter summary storage
  unsigned numProcessedEvents_;
  unsigned numEventsPassingEventFilters_;
  unsigned numEventsPassingTrigger_;

  std::map<std::string,unsigned> trigFilterSummary_;
  std::map<std::string,unsigned> trigPathSummary_;

  // To count the total number of events on which the producer runs
  TH1F * hTotalProcessedEvents_;
  TH1F * hEventsPassingEventsFilter_;
  TH1F * hEventsPassingTrigger_;

  // The tree with all the variables
  edm::Service<TFileService> fs_;
  TTree* outputTree_;

  std::vector<std::string> triggers_;

  // Structure holding all the variables
  Candidates candidates_;

};
