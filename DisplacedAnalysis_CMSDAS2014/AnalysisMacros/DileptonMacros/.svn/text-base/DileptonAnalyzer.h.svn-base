//////////////////////////////////////////////////////////
//
// SKELETON ANALYZER
// READS IN A TREE FROM THE TREEPRODUCER
// PRODUCES A SIMPLE PLOT
//
//////////////////////////////////////////////////////////

#ifndef DileptonAnalyzer_h
#define DileptonAnalyzer_h

// This is the base class
// Sets everything up to read the tree
// Initializes PU reweighting and counts number of events before/after PAT step
#include "../CommonMacros/treeAnalyzerBase.h"

// Class which handles analysis cuts used
#include "DileptonAnalysisCuts.h"

// Class which manages histograms
#include "Histograms.h"

#include <map>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TRandom3.h>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "../CommonMacros/deltaPhi.h"

// some variables for the trigger efficiency vs. mean lifetime plots
const int nTrigEffBins = 40;
const unsigned int nReweightFactors_ = 11;
const float lifetimeReweightingFactors_[nReweightFactors_] = {1.0/30, 1.0/20, 1.0/10, 1.0/3, 1.0/2, 1, 2, 3, 10, 20, 30};
const float nominalLifetime_ = 80.0; // will need to be improved

using namespace std;

//
// CLASS DEFINITION
//
// Inherits from treeAnalyzerBase
//
class DileptonAnalyzer : public treeAnalyzerBase {
  public :

    // Constructor and destructor
    // Creates treeAnalyzerBase object
    DileptonAnalyzer(TString fileName = "", const double & weight = 1., analysisType analysis=_2eTrack);
    ~DileptonAnalyzer();

    // Loop over entries in tree
    void Loop();

  private :
    // Get the event weight - PU, cross section & number of initial events
    void getEventWeight();

    // Get weight to reweight signal MC lifetime
    // Used for debugging.
    double getLifetimeWeight( const double & llCtau);

    // Study neutralino pt spectrum
    void studyNeutralinoPtSpectrum();
    // For reweighting different components of neutralino pt spectrum
    double getNeutralinoWeight();
    bool reweightNeutralinoPt_;
    double ssWeight_;
    double sasWeight_;

    // Study triggers for signal MC
    void studyTriggers();

    // Study tracking efficiency for signal MC
    void studyTrackingEfficiency();

    // Check if signal trigger fired (used if signal MC)
    bool signalTriggerFired();

    // Check if event passes prefilter requirement (used for signal MC)
    bool passPrefilter();

    // Get corresponding lepton in TreeLepton collection
    const TreeLepton getLepton( unsigned int index );

    // Simple analysis cuts to apply
    // Checks, given the type of analysis, that the candidate is made up of suitable leptons
    bool correctLeptonsInCandidate(TreeDipseudoLeptonCandidate & cand, TreeLepton& leptonL, TreeLepton& leptonH );
    bool correctLepton( TreeLepton & lepton );
    bool leptonTriggerMatch( TreeLepton & lepton );
    bool leptonFromExotic( TreeLepton & lepton );

    // Returns correct mass to use in this channel
    double whichMass( TreeDipseudoLeptonCandidate &cand );

    // Returns which aboslute isolation to use in thie channel
    void whichIso(const TreeDipseudoLeptonCandidate &cand, double &leptonIsoL, double &leptonIsoH);

    // Returns min & max |d0/sigma| in candidate
    double getMinD0( const TreeDipseudoLeptonCandidate &cand );
    double getMaxD0( const TreeDipseudoLeptonCandidate &cand, float minD0Sigma );

    // Checks if this candidate (in signal MC) has been correctly reconstructed
    // i.e. both leptons come from the same exotic
    bool correctlyReconstructed(TreeDipseudoLeptonCandidate & cand, TreeLepton& leptonL, TreeLepton& leptonH, bool debug=false);

    // Count number of exotics in this event that decay to the sensitive channel
    unsigned int storeNumberOfExoticsALL();

    // Store number of exotics that have been RECO'ed
    void storeNumberOfExoticsRECO( TreeDipseudoLeptonCandidate & cand, TreeLepton &leptonL, TreeLepton &leptonH, ofstream & oneExoFile, ofstream & twoExoFile );

    // Find index of signal pdg id in signalPdgId_
    unsigned int getIndexOfSignalPdg( int pdgId );

    // Check if there is at least one interesting exotic particle in the event
    bool interestingExoticInEvent();

    // Store signal efficiencies
    void storeSignalEfficiencies( TFile & outputFile );

    // Check if first and second exotics are within acceptance
    bool ll1WithinAcceptance();
    bool ll2WithinAcceptance();

    // Checks if exotics in event are within acceptance given how many interesting exotics there are in the event
    bool eventWithinAcceptance( const unsigned int nInterestingExotics );


    // Check whether the gen matched leptons of a cand are withing acceptance
    bool withinAcceptnace( TreeDipseudoLeptonCandidate & cand );

    // Simple study of lifetime cuts optimisation
    void optimiseLifetimeCuts( double lxySig, double minD0, double weight );

    // Method using d0 signing
    void studyD0Signing( TreeDipseudoLeptonCandidate &cand, TreeLepton & leptonL, TreeLepton & leptonH, double & mass,Histograms & h, bool fillTextFiles );

    // Study using collinearity to separate signal from background
    void studyCollinearity( TreeDipseudoLeptonCandidate &cand, TreeLepton & leptonL, TreeLepton & leptonH, double & mass, Histograms & h, bool fillTextFiles );

    // Study all the candidates reconstructed in the event
    void studyCandidate( TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , Histograms &h, bool fillTextFiles );

    // Function to fill all plots which are common between each set of cuts e.g. n-1 plots
    void fillPlots( const TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , const double mass, DileptonAnalysisCuts &cuts, const DileptonAnalysisCuts::PassedWhichCuts &passedWhichCuts, map< TString, TH1F* > & histMap, bool isFinalCuts, bool debug=false );

    // Function to fill plots for removed lifetime selection
    // A little different as a few extra things to plot
    void fillRemovedLifetimePlots( TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH, double mass, DileptonAnalysisCuts::PassedWhichCuts removedLifetimeCuts, Histograms & h );

    // Check if event is ditau
    bool isDitauEvent();

    // Checks if the exotics in the event have the central ctau
    bool isCentralCtau();

    // Get pdg of interesting lepton for this analysis
    unsigned int getInterestingLepton();

    // Useful debug function which will spes lots of information about a candidate to the screen
    void outputCandInfoToScreen( const TreeDipseudoLeptonCandidate &cand );

    // Store how many candidates passed selection in each event
    void storeNumberOfCandsPerEvent( Histograms &h );

    TreeDipseudoLeptonCandidate& largestD0Cand( TreeDipseudoLeptonCandidate& cand1, TreeDipseudoLeptonCandidate& cand2 );

//    void bestCandidateSoFar( TreeDipseudoLeptonCandidate& cand, bool signalCand, bool finalCuts );
    void bestCandidateSoFar( TreeDipseudoLeptonCandidate& cand, TreeDipseudoLeptonCandidate*& currentBestCand );

    void plotBestCandidates( bool isCorrectedDataCand=false);

    // Study track mis-alignment
    void studyTrackD0Misalignment( const TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , const bool passVertex, Histograms &h );
    void studyTrackZ0Misalignment( const TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , const bool passVertex, Histograms &h );

    // Fill histograms that perform cross checks of d0 corrections
    void fillD0CorrectionsCrossCheck( TreeLepton & lepton, double d0Sigma_signWrtPerp, double d0Sigma_signWrtDilepton, double deltaPhi, TProfile2D * corrections, Histograms &h );

//    // Find gen match
//    // Attempt to match a reco lepton with a gen lepton from an exotic
//    void findGenMatch( TreeLepton &lepton );

    // Analysis Cuts Class
    DileptonAnalysisCuts dileptonCuts_final_;
    DileptonAnalysisCuts dileptonCuts_looseA_;
    DileptonAnalysisCuts dileptonCuts_looseB_;
    DileptonAnalysisCuts dileptonCuts_looseC_;
    DileptonAnalysisCuts dileptonCuts_removedLifetime_;
    DileptonAnalysisCuts dileptonCuts_removedLifetimeNoVertex_;
    DileptonAnalysisCuts dileptonCuts_2011Cuts_;

    DileptonAnalysisCuts dileptonCuts_finalColl_;
    DileptonAnalysisCuts dileptonCuts_looseColl_;
    DileptonAnalysisCuts dileptonCuts_controlColl_;
    DileptonAnalysisCuts dileptonCuts_looseControlColl_;

    // Number of candidates per event
    bool atLeastOneCandInAcceptance_;
    unsigned int nCandsPerEvent_final_;
    unsigned int nCandsPerEvent_loose_;
    unsigned int nCandsPerEvent_control_;
    unsigned int nCandsPerEvent_looseControl_;
    unsigned int nCandsPerEvent_deltaPhiG90_;
    unsigned int nCandsPerEvent_deltaPhiL90_;

    // Best candidate per event in signal and control regions
    // Defined as one with largest min(d0/sigma H,d0/sigma L)
    TreeDipseudoLeptonCandidate *bestSignalCand_;
    TreeDipseudoLeptonCandidate *bestFinalSignalCand_;
    TreeDipseudoLeptonCandidate *bestControlCand_;
    TreeDipseudoLeptonCandidate *bestL0Cand_;
    TreeDipseudoLeptonCandidate *bestG0Cand_;

    // Histograms
    Histograms hists_;
    // Separate histograms for separating out different background components
    // E.g. Separate Z -> Tau Tau from Z -> mu mu / Z -> e e
    Histograms histsTau_;

    // Histograms for corrected cands
    Histograms histsCorrected_;

    // Event weight (changes per event)
    double eventWeight_;

    // Smear lxy distributions
    double lxyScale_;

    // Smear d0/sigma distributions
    double d0Scale_;
    double d0Scale_gaussianWidth_;

    // Whether this is signal MC or not
    bool isSignalMC_;
    // Whether this is data or not
    bool isData_;

    // Possible pdg Id of signal MC exotic
    int nSignalParticles_;
    vector<int> signalPdgId_;

    // Info on "middle"/central exotic
    // Useful for when we want to plat/record info for just one exotic
    int centralPdgId_;

    // Interesting triggers
    vector< string > signalTriggers_;
    vector< unsigned int > triggerFired_;
    unsigned int triggerToPlot_; // Which trigger to plot in efficiency plots
    string signalTrigger_; // The signal trigger that must fire in the event.  Only used for signal MC as no prefiltering has taken place previously


    // Prefilter cuts
    // Loose, but so we end up with the same starting criteria for the cutflow
    vector<double> prefilterPtCut_; // Pt cut applied at trigger/prefilter level
    vector<double> prefilterEtCut_; // Et cut applied at trigger/prefilter level
    double prefilterEtaCut_; // Eta cut applied at prefilter level
    unsigned int originalCounter_; // Sanity check counter - all events after trigger, before prefilter
    unsigned int purityCounter_; // Count how many events pass trigger and prefilter
    unsigned int purityCounter_offlineMatch_; // Breakdown of overall purity
    unsigned int purityCounter_eta_;
    unsigned int purityCounter_Et_;
    unsigned int purityCounter_pt_;

    // How many exotics decay into the channel this analysis is sensitive to
    unsigned int nSensitiveExoticDecayInEvent_;

    // Overall counters
    unsigned int nCorrect_;
    unsigned int nIncorrect_;

    // Total number of exotics in the sensitive channel
    vector<double> numEvents_oneSensitiveDecay_;
    vector<double> numEvents_twoSensitiveDecay_;

    // Number of reconstructed exotics
    vector<double> numExoticsRECO_oneSensitiveDecay_;
    vector<double> numExoticsRECO_twoSensitiveDecay_;

    // Number of correctly reconstructed exotics (that decay to the sensitive channel)
    vector<double> numExoticsCorrectRECO_oneSensitiveDecay_;
    vector<double> numExoticsCorrectRECO_twoSensitiveDecay_;

    // Number of correctly reco'd exotics outside (gen) acceptance
    vector<double> numExotics_oA_oneSensitiveDecay_;
    vector<double> numExotics_oA_twoSensitiveDecay_;

    // Output text files for more detailed efficiency studies e.g. lifetime reweighting
    ofstream allExotics_oneSensitiveDecay_;
    ofstream allExotics_twoSensitiveDecay_;
    ofstream recoExotics_oneSensitiveDecay_;
    ofstream recoExotics_twoSensitiveDecay_;
    ofstream recoExotics_oneSensitiveDecay_negative_;
    ofstream recoExotics_twoSensitiveDecay_negative_;
    ofstream recoExotics_oneSensitiveDecay_removedLifetime_;
    ofstream recoExotics_twoSensitiveDecay_removedLifetime_;

    ofstream recoExotics_coll_oneSensitiveDecay_;
    ofstream recoExotics_coll_twoSensitiveDecay_;
    ofstream recoExotics_coll_oneSensitiveDecay_negative_;
    ofstream recoExotics_coll_twoSensitiveDecay_negative_;

    // Output text files for background shape and normalisation determination
    ofstream removedLifetime_;
    ofstream looseCuts_;

    // Output text files for signal mass resolution studies
    // Used for data to record candidates passing all selection
    ofstream allCuts_;
    ofstream allCutsNegative_;
    ofstream allCollCuts_;
    ofstream allCollCutsNegative_;
    ofstream allCollCuts_corrected_;
    ofstream allCollCutsNegative_corrected_;

    // Counters for calculating gen level acceptance for signal MC
    double acceptancePt1Cut_;
    double acceptancePt2Cut_;
    double acceptanceEtaCut_;
    double acceptanceLxyCut_;

    // For cut flow study
    map< TString, float > cutFlowMap_;
    map< TString, float > cutFlowMapColl_;
    vector< TString > cutNamesInOrder_;
    void monitorCutFlow( DileptonAnalysisCuts::PassedWhichCuts & whichCuts, map< TString, float > & cutFlowMap, double weight );
    void reportCutFlow( TFile & outputFile );
    unsigned int nEvents_;
    unsigned int nExoticsBeforeAcceptance_;
    double nExoticsBeforePrefilter_;
    double nExoticsAfterTrigger_;
    double nCorrectlyRecoExoticsBeforePrefilter_;

    // Random number generator
    // For mass smearing in electron channel
    TRandom3 rnd;

    double smearMass( double mass, bool barrel1, bool barrel2 );
    double EBEBScale_;
    double EBEEScale_;
    double EEEEScale_;

    double correctD0Sigma( TreeLepton & lepton, TProfile2D * h, double d0Sigma, double deltaPhi  );
    void fillCorrectedD0Sigma( const TreeDipseudoLeptonCandidate &cand, TreeLepton& leptonL, TreeLepton& leptonH , TProfile2D *corrections, TH1F *hisCorr_bothLeptons, TH1F *hisCorr, TH1F *hisCorr_forFittingData, TString typeOfCorrections, bool runDependent, TProfile2D *correction_badRunRange = 0 );
    double badRunRangeMin_; // Used to sepearate run ranges where mean bias in d0/sigma changes during run period
    double badRunRangeMax_;
    TProfile2D * meanD0SignificanceVsThetaVsPhi_;
    TProfile2D * meanD0SignificanceVsThetaVsPhi_badRun_;
    TProfile2D * meanD0SignificanceVsThetaVsPhi_noVertex_;
    TProfile2D * meanD0SignificanceVsThetaVsPhi_badRun_noVertex_;
    TProfile2D * meanD0VsThetaVsPhi_;
    TProfile2D * meanD0SignificanceVsThetaVsPhiCut_;
    TProfile2D * meanD0SignificanceVsThetaVsPhi_pixel_;
    TProfile2D * meanD0SignificanceVsThetaVsPhi_noPixel_;

    bool useCorrectedCands_;

    bool unblind_;

    // Use if you want to reweight the exotic lifetime
    // Mainly for cut flow and debugging
    // Note need to know original ctau of sample
    bool reweightExoticLifetime_;
    double reweightFactor_;
    double originalCtau_;

    unsigned int DEBUGCOUNTER;
};

#endif


