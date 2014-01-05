//////////////////////////////////////////////////////////
//
// SKELETON ANALYZER
// READS IN A TREE FROM THE TREEPRODUCER
// PRODUCES A SIMPLE PLOT
//
//////////////////////////////////////////////////////////

#ifndef MixedChannelEff_h
#define MixedChannelEff_h

// This is the base class
// Sets everything up to read the tree
// Initializes PU reweighting and counts number of events before/after PAT step
#include "AnalysisMacros/CommonMacros/treeAnalyzerBase.h"

// Class which handles analysis cuts used
#include "MixedChannelEffCuts.C"

// Class which manages histograms
#include "Histograms.C"

// A set of functions/tools that are fairly common for all analyses
// e.g. drawing overflow in final bin etc.
#include "AnalysisMacros/CommonMacros/commonTools.C"


//
// CLASS DEFINITION
//
// Inherits from treeAnalyzerBase
//
class MixedChannelEff : public treeAnalyzerBase {
  public :

    // Constructor and destructor
    // Creates treeAnalyzerBase object
    MixedChannelEff(TString fileName = "", const double & weight = 1., analysisType analysis=_2eTrack);
    ~MixedChannelEff();

    // Loop over entries in tree
    void Loop();

  private :
    // Get the event weight - PU, cross section & number of initial events
    double getEventWeight();

    // Get corresponding lepton in TreeLepton collection
    const TreeLepton getLepton( unsigned int index );

    // Simple analysis cuts to apply
    // Checks, given the type of analysis, that the candidate is made up of suitable leptons
    bool correctLeptonsInCandidate(TreeDipseudoLeptonCandidate & cand);
    bool triggerMatching(TreeDipseudoLeptonCandidate & cand);
    bool caloMatch(TreeDipseudoLeptonCandidate & cand);

    // Checks if this candidate (in signal MC) has been correctly reconstructed
    // i.e. both leptons come from the same exotic
    bool correctlyReconstructed(TreeDipseudoLeptonCandidate & cand);

    // Analysis Cuts Class
    MixedChannelEffCuts dileptonCuts_final_;
    MixedChannelEffCuts dileptonCuts_invertedLifetime_;
    MixedChannelEffCuts dileptonCuts_loose_;

    // Histograms
    Histograms histograms_;

    // Whether this is signal MC or not
    bool isSignalMC_;

    // Total number of exotics in the sensitive channel
    unsigned int numExoticsInDecayChannel_;

    // Number of reconstructed exotics
    unsigned int numExoticsRECO_;

    // Number of reconstructed exotics (that decay to the sensitive channel)
    unsigned int numExoticsInDecayChannelRECO_;

};

#endif

#ifdef MixedChannelEff_cxx
MixedChannelEff::MixedChannelEff(TString fileName, const double & weight, analysisType analysis) :
            treeAnalyzerBase(fileName, weight, analysis),
            isSignalMC_(false),
            numExoticsInDecayChannel_(0), numExoticsInDecayChannelRECO_(0)
{

  // Is this signal MC?
  if ( fileName.Contains("LongLived") ) isSignalMC_=true;;

  // Initialize analysis cuts
  dileptonCuts_final_=MixedChannelEffCuts(anaType_,_final);
  dileptonCuts_invertedLifetime_=MixedChannelEffCuts(anaType_,_invertedLifetime);
  dileptonCuts_loose_=MixedChannelEffCuts(anaType_,_loose1);
}

MixedChannelEff::~MixedChannelEff()
{

  std::cout << "Number of exotics decaying into this channel : " << numExoticsInDecayChannel_ << std::endl;
  std::cout << "Number of correctly RECO'd candidates : " << numExoticsInDecayChannelRECO_ << std::endl;
  std::cout << "Total number of RECO'd candidates : " << numExoticsRECO_ << std::endl;
}
#endif
