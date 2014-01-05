//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun  1 10:44:55 2012 by ROOT version 5.32/00
// from TTree treeAnalyzerBase/treeAnalyzerBase
// found on file: histograms.root
//////////////////////////////////////////////////////////

#ifndef treeAnalyzerBase_h
#define treeAnalyzerBase_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <iostream>

// Candidates
#include "TreeProducer/TreeProducer/interface/Candidates.h"
#include "TreeProducer/TreeProducer/interface/TreeLepton.h"
#include "TreeProducer/TreeProducer/interface/TreeDipseudoLeptonCandidate.h"
#include "TreeProducer/TreeProducer/src/LinkDef.h"

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <map>

// For pileup weights
#include "PileupReweighting.h"

#include "analysisType.h"

class treeAnalyzerBase {
  public :
    int totalProcessedEvents_;
    int eventsPassingTrigger_;

    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

    // Declaration of leaf types
    Candidates      *candidates;
    std::vector<std::string> *triggers;

    // List of branches
    TBranch        *b_candidates;   //!
    TBranch        *b_triggers;   //!

    treeAnalyzerBase(TString fileName = "", const double & weight = 1., analysisType analysis=_2eTrack);
    virtual ~treeAnalyzerBase();
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Show(Long64_t entry = -1);

    // The cross section weight (normalised by number of events) we are applying to this sample
    // For data == 1
    double xsecWeight_;

    // Which analysis we are currently considering
    analysisType anaType_;

    // PU reweighting class
    PileupReweighting puweights_;
    // For systematic studies
    PileupReweighting puweights_p5_;
    PileupReweighting puweights_m5_;

    // Dir name inside file
    TString dirName_;
};

#endif // #ifdef treeAnalyzerBase_h
