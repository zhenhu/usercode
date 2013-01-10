//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 19 13:21:45 2012 by ROOT version 5.32/00
// from TTree outputTree/outputTree
// found on file: histograms.root
//////////////////////////////////////////////////////////


#ifndef treeAnalyzer_h
#define treeAnalyzer_h

#include "CommonMacros/treeAnalyzerBase.h"
#include "CommonMacros/commonTools.C"
#include "CommonMacros/analysisType.C"

class treeAnalyzer : public treeAnalyzerBase {
  public :

    treeAnalyzer(TString fileName = "", const double & weight = 1., const bool electrons = false);
    ~treeAnalyzer();
        
   void     Loop();
   
    // Analysis cuts
    bool acceptanceCuts( std::vector<TreeDipseudoLeptonCandidate>::const_iterator cand );
    bool trackSelectionCuts( std::vector<TreeDipseudoLeptonCandidate>::const_iterator cand, const bool removeIsolationCut = false );
    bool lifetimeRelatedCuts( std::vector<TreeDipseudoLeptonCandidate>::const_iterator candconst, bool removeLifetimeRelatedCuts = false, const bool decayLengthSigniInverted = false);
    bool dileptonSelectionCuts( std::vector<TreeDipseudoLeptonCandidate>::const_iterator cand);
    bool analysisCuts( std::vector<TreeDipseudoLeptonCandidate>::const_iterator cand, const bool removeIsolationCut = false, const bool removeLifetimeRelatedCuts = false, const bool decayLengthSigniInverted = false);

    bool triggerMatching( std::vector<TreeDipseudoLeptonCandidate>::const_iterator cand );
    void initializeCuts();
    double ptCut_;
    double d0SignificanceCut_;
    double dPhiCorrCut_;
    double decayLengthSignificance2DCut_;
};

#endif

#ifdef treeAnalyzer_cxx
treeAnalyzer::treeAnalyzer(TString fileName, const double & weight, const bool electrons) :
  treeAnalyzerBase(fileName, weight, electrons ? _2eTrack : _2muTrack)
{

}

treeAnalyzer::~treeAnalyzer()
{
}
#endif
