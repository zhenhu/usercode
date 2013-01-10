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
#include "AnalysisMacros/CommonMacros/treeAnalyzerBase.h"

// Class which handles analysis cuts used
#include "DileptonAnalysisCuts.C"

// Class which manages histograms
#include "Histograms.C"

// A set of functions/tools that are fairly common for all analyses
// e.g. drawing overflow in final bin etc.
#include "AnalysisMacros/CommonMacros/commonTools.C"

#include <map>
#include <TProfile.h>
#include <fstream>
#include <iomanip>


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

    // Study triggers for signal MC
    void studyTriggers();

    // Check if signal trigger fired (used if signal MC)
    bool signalTriggerFired();


    // Get corresponding lepton in TreeLepton collection
    const TreeLepton getLepton( unsigned int index );

    // Simple analysis cuts to apply
    // Checks, given the type of analysis, that the candidate is made up of suitable leptons
    bool correctLeptonsInCandidate(TreeDipseudoLeptonCandidate & cand);
    bool correctLepton( TreeLepton & lepton );
    bool triggerMatching(TreeDipseudoLeptonCandidate & cand);
    bool leptonTriggerMatch( TreeLepton & lepton );
    bool leptonFromExotic( TreeLepton & lepton );
    bool caloMatch(TreeDipseudoLeptonCandidate & cand);

    // Checks if this candidate (in signal MC) has been correctly reconstructed
    // i.e. both leptons come from the same exotic
    bool correctlyReconstructed(TreeDipseudoLeptonCandidate & cand);

    // Count number of exotics in this event that decay to the sensitive channel
    unsigned int getNumberOfExotics();

    // Store number of exotics that have been RECO'ed
    void storeNumberOfExoticsRECO( TreeDipseudoLeptonCandidate & cand );

    // Find index of signal pdg id in signalPdgId_
    unsigned int getIndexOfSignalPdg( int pdgId );

    // Check if there is at least one interesting exotic particle in the event
    bool interestingExoticInEvent();

    // Store signal efficiencies
    void storeSignalEfficiencies( TFile & outputFile );

    // Analysis Cuts Class
    DileptonAnalysisCuts dileptonCuts_final_;
    DileptonAnalysisCuts dileptonCuts_removedLifetime_;

    // Histograms
    Histograms histograms_;

    // Event weight (changes per event)
    double eventWeight_;

    // Smear lxy distributions
    double lxyScale_;

    // Smear d0/sigma distributions
    double d0Scale_;

    // Whether this is signal MC or not
    bool isSignalMC_;
    // Whether this is data or not
    bool isData_;
    // Possible pdg Id of signal MC exotic
    int nSignalParticles_;
    std::vector<int> signalPdgId_;

    // Interesting triggers
    std::vector< std::string > signalTriggers_;
    std::vector< unsigned int > triggerFired_;
    unsigned int triggerToPlot_; // Which trigger to plot in efficiency plots
    std::string signalTrigger_; // The signal trigger that must fire in the event.  Only used for signal MC as no prefiltering has taken place previously

    // How many exotics decay into the channel this analysis is sensitive to
    unsigned int nSensitiveExoticDecayInEvent_;

    // Total number of exotics in the sensitive channel
    std::vector<double> numEvents_oneSensitiveDecay_;
    std::vector<double> numEvents_twoSensitiveDecay_;

    // Number of reconstructed exotics
    std::vector<double> numExoticsRECO_oneSensitiveDecay_;
    std::vector<double> numExoticsRECO_twoSensitiveDecay_;

    // Number of reconstructed exotics (that decay to the sensitive channel)
    std::vector<double> numExoticsCorrectRECO_oneSensitiveDecay_;
    std::vector<double> numExoticsCorrectRECO_twoSensitiveDecay_;

    // Output text files for more detailed efficiency studies e.g. lifetime reweighting
    ofstream allExotics_oneSensitiveDecay_;
    ofstream allExotics_twoSensitiveDecay_;
    ofstream recoExotics_oneSensitiveDecay_;
    ofstream recoExotics_twoSensitiveDecay_;

    // For cut flow study
    std::map< TString, float > cutFlowMap_;
    std::vector< TString > cutNamesInOrder_;
    void monitorCutFlow( DileptonAnalysisCuts::PassedWhichCuts whichCuts, double weight );
    void reportCutFlow( TFile & outputFile );
};

#endif

#ifdef DileptonAnalyzer_cxx
DileptonAnalyzer::DileptonAnalyzer(TString fileName, const double & weight, analysisType analysis) :
                            treeAnalyzerBase(fileName, weight, analysis),
                            eventWeight_(weight),
                            lxyScale_(1.0), d0Scale_(1.0),
                            isSignalMC_(false), isData_(false), nSignalParticles_(0),
                            triggerToPlot_(0),
                            nSensitiveExoticDecayInEvent_(0)
//                numEvents_oneSensitiveDecay_(0), numEvents_twoSensitiveDecay_(0),
//                numExoticsRECO_oneSensitiveDecay_(0), numExoticsRECO_twoSensitiveDecay_(0),
//                numExoticsCorrectRECO_oneSensitiveDecay_(0), numExoticsCorrectRECO_twoSensitiveDecay_(0)
{

  // Is this data?
  if ( fileName.Contains("Data") ) isData_=true;

  // Is this signal MC?
  if ( fileName.Contains("LongLived") ) {
    isSignalMC_=true;

    // Initialize signal MC pdg id container
    if ( isSignalMC_ ) {
      if ( fileName.Contains("HTo2LongLivedTo4F") ) {
        signalPdgId_.push_back(6001113);
        signalPdgId_.push_back(6002113);
        signalPdgId_.push_back(6003113);
      }
      else if ( fileName.Contains("Chi0ToNuLL") ) {
        signalPdgId_.push_back(1000022);  // FIXME Guess at the moment
      }
    }

    // Set number of possible signal particles
    nSignalParticles_=signalPdgId_.size();

    // Set names of intersting signal triggers
    signalTriggers_.push_back("AnyTrigger");
    if ( anaType_==_2eTrack ) {
      signalTriggers_.push_back("HLT_DoublePhoton48_HEVT_v7");
      signalTriggers_.push_back("HLT_Photon36_R9Id85_OR_CaloId10_Iso50_Photon22_R9Id85_OR_CaloId10_Iso50_v5");
      triggerToPlot_=1;
    }
    else if ( anaType_==_2muTrack || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu ) {
      signalTriggers_.push_back("HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v2");
      triggerToPlot_=1;
    }

    if ( signalTriggers_.size() >= 1 ) {
      signalTrigger_=signalTriggers_[1];
      std::cout << "Trigger require in signal MC : " << signalTrigger_.c_str() << std::endl;
    }
    else {
      signalTrigger_="AnyTrigger";
      std::cout << "WARNING : Not requiring a signal trigger for signal MC" << std::endl;
    }

    for ( unsigned int i=0; i < signalTriggers_.size(); i++ ) {
      triggerFired_.push_back(0);
    }

    // Initialize efficiency counters
    for ( int i = 0; i<nSignalParticles_; i++ ) {
      numEvents_oneSensitiveDecay_.push_back(0);
      numEvents_twoSensitiveDecay_.push_back(0);
      numExoticsRECO_oneSensitiveDecay_.push_back(0);
      numExoticsRECO_twoSensitiveDecay_.push_back(0);
      numExoticsCorrectRECO_oneSensitiveDecay_.push_back(0);
      numExoticsCorrectRECO_twoSensitiveDecay_.push_back(0);
    }

    // Get good name for signal effic files
    TString efficFileName=fileName;
    int position=efficFileName.Index("MH",2);
    efficFileName.Remove(0,position);
    position=efficFileName.Index("_analysis");
    efficFileName.Remove(position,efficFileName.Length());

    // Get anaType_ in string format
    TString type("dummy");
    if ( anaType_==_2eTrack) type = "2eTrack";
    else if ( anaType_==_2muTrack ) type = "2muTrack";
    else if ( anaType_==_2globalMu ) type = "2globalMu";
    else if ( anaType_==_2trackerMu ) type = "2trackerMu";
    else if ( anaType_==_2saMu ) type = "2saMu";

    // Open output files for efficiency studies
    allExotics_oneSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_allExotics_"+type+"_"+efficFileName+"_oneDecay.txt");
    allExotics_twoSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_allExotics_"+type+"_"+efficFileName+"_twoDecay.txt");
    recoExotics_oneSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_recoExotics_"+type+"_"+efficFileName+"_oneDecay.txt");
    recoExotics_twoSensitiveDecay_.open("EfficiencyFiles/rawFiles/effic_recoExotics_"+type+"_"+efficFileName+"_twoDecay.txt");

    allExotics_oneSensitiveDecay_ << setprecision(7);
    allExotics_twoSensitiveDecay_ << setprecision(7);
    recoExotics_oneSensitiveDecay_ << setprecision(7);
    recoExotics_twoSensitiveDecay_ << setprecision(7);

  }

  // Initialize analysis cuts
  dileptonCuts_final_=DileptonAnalysisCuts(anaType_,_final);
  dileptonCuts_removedLifetime_=DileptonAnalysisCuts(anaType_,_removedLifetime);

  // Initialize cut flow map - order of cuts important

  cutNamesInOrder_.push_back("AllCandidatesAtBeginningOfMacro");
  cutNamesInOrder_.push_back("CaloMatch");
  cutNamesInOrder_.push_back("LeptonPt");
  cutNamesInOrder_.push_back("LeptonSCEt");
  cutNamesInOrder_.push_back("LeptonAbsEta");
  cutNamesInOrder_.push_back("LeptonAbsD0Sig");
  cutNamesInOrder_.push_back("DileptonOppositeCharge");
  cutNamesInOrder_.push_back("DileptonIsolation");
  cutNamesInOrder_.push_back("DileptonB2BVeto");
  cutNamesInOrder_.push_back("DileptonDeltaR");
  cutNamesInOrder_.push_back("DileptonTriggerMatch");
  cutNamesInOrder_.push_back("DileptonChi2");
  cutNamesInOrder_.push_back("DileptonDeltaPhi");
  cutNamesInOrder_.push_back("DileptonHitsBeforeVertex");
  cutNamesInOrder_.push_back("DileptonAbsLxySig");
  cutNamesInOrder_.push_back("DileptonMass");

  for ( unsigned int iCut = 0; iCut < cutNamesInOrder_.size(); iCut++ ) {
    cutFlowMap_[cutNamesInOrder_[iCut]]=0;
  }

  // Initialize lxy smearing factors for background MC only
  if ( !isSignalMC_ && !isData_ ) {
    // For muon channel
    if ( anaType_==_2muTrack || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu ) {
      lxyScale_ = 1.2;
      d0Scale_ = 0.9;
    }
    // For electron channel
    else if ( anaType_==_2eTrack) {
      lxyScale_ = 1.15;
      d0Scale_ = 0.95;
    }
  }
}

DileptonAnalyzer::~DileptonAnalyzer()
{

  //  std::cout << "--------> One exotic in channel" << std::endl;
  //  std::cout << "Number of events where one exotic decays into this channel : " << numEvents_oneSensitiveDecay_[0] << std::endl;
  //  std::cout << "Number of candidates RECO'd : " << numExoticsRECO_oneSensitiveDecay_ << std::endl;
  //  std::cout << "Number of exotics correctly RECO'd : " << numExoticsCorrectRECO_oneSensitiveDecay_ << std::endl;
  //
  //  std::cout << "--------> Two exotics in channel" << std::endl;
  //  std::cout << "Number of events where two exotic decays into this channel : " << numEvents_twoSensitiveDecay_ << std::endl;
  //  std::cout << "Number of candidates RECO'd : " << numExoticsRECO_twoSensitiveDecay_ << std::endl;
  //  std::cout << "Number of exotics correctly RECO'd : " << numExoticsCorrectRECO_twoSensitiveDecay_ << std::endl;

  // CLose output files
  allExotics_oneSensitiveDecay_.close();
  allExotics_twoSensitiveDecay_.close();
  recoExotics_oneSensitiveDecay_.close();
  recoExotics_twoSensitiveDecay_.close();
}
#endif
