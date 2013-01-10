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
#include "TreeProducer/TreeProducer/src/LinkDef.h"

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <map>

// For pileup weights
#include "PileupReweighting.C"

#include "analysisType.C"

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

    // The cross section weight we are applying to this sample
    // For data == 1
    double weight_;

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


treeAnalyzerBase::treeAnalyzerBase(TString fileName, const double & weight, analysisType analysis) : fChain(0), weight_(weight), anaType_(analysis), dirName_("")
{
  // Get location within file of tree for this particular analysis
  TString dirName("dummy");
  if ( anaType_==_2eTrack) dirName = "eTrackAnalysis";
  else if ( anaType_==_2muTrack || anaType_==_2globalMu || anaType_==_2trackerMu || anaType_==_2saMu ) dirName = "muTrackAnalysis";
  else if ( anaType_==_2photon ) dirName = "photonAnalysis";
  else if ( anaType_==_2jet ) dirName = "jetAnalysis";
  else std::cout << "WARNING : Can't work out which directory your tree is in.  Will probably crash." << std::endl;

  std::cout << "anaType_ : " << anaType_ << " dirName : " << dirName.Data() << std::endl;

  TChain * f = new TChain(dirName+"/outputTree");

  // Put in default file name if none specified
  if( fileName == "" ) {
    std::cout << "WARNING : No file name specified, so using some default file.  This may not even exist." << std::endl;
    fileName = "/afs/cern.ch/work/e/ejclemen/DisplacedLeptons2012/CMSSW_5_2_5/src/TreeProducer/TreeProducer/test/histograms.root";
  }

  // Get total number of events we started with, before skimming on trigger
  TFile tempFile(fileName, "READ");
  TDirectory * dir = (TDirectory*)tempFile.Get(dirName);
  totalProcessedEvents_ = ((TH1F*)dir->Get("totalProcessedEvents"))->GetBinContent(1);
  std::cout << "Total processed events : " << totalProcessedEvents_ << std::endl;

  double eventsAfterTrigger = ((TH1F*)dir->Get("eventsPassingTrigger"))->GetBinContent(1);
  std::cout << "Total events after trigger : " << eventsAfterTrigger << std::endl;
  // Divide cross section weight by number of original events
  if( weight_ != -1 ) weight_ /= totalProcessedEvents_;
  // If this is data (weight_==-1), set weight to 1
  if ( weight_ == -1 ) weight_ = 1;

  // Get the name of the directory where the sample is.
  // This will help define the name of the output file
  if( std::string(fileName).find_last_of("/") != std::string::npos ) {
    std::string tempDir(std::string(fileName).substr(0, std::string(fileName).find_last_of("/")));
    dirName_ = tempDir.substr(std::string(tempDir).find_last_of("/")+1);
  }

  f->Add(fileName);
  Init(f);

  // Initialise PU weights
  TString puFile = "../../AnalysisMacros/PileupFiles/pileup_muon.root";
  TString puP5File = "../../AnalysisMacros/PileupFiles/pileup_muon_p5.root";
  TString puM5File = "../../AnalysisMacros/PileupFiles/pileup_muon_m5.root";
  if ( anaType_==_2eTrack ) {
    puFile = "../../AnalysisMacros/PileupFiles/pileup_electron.root";
    puP5File = "../../AnalysisMacros/PileupFiles/pileup_electron_p5.root";
    puM5File = "../../AnalysisMacros/PileupFiles/pileup_electron_m5.root";
  }
  std::cout << "Using pileup file " << puFile.Data() << std::endl;
  puweights_ = PileupReweighting(puFile);
  puweights_p5_ = PileupReweighting(puP5File);
  puweights_m5_ = PileupReweighting(puM5File);

  candidates = NULL;
  triggers = NULL;
}

treeAnalyzerBase::~treeAnalyzerBase()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t treeAnalyzerBase::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t treeAnalyzerBase::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
  }
  return centry;
}

void treeAnalyzerBase::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  //triggers = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("candidates", &candidates, &b_candidates);
  fChain->SetBranchAddress("triggers", &triggers, &b_triggers);
}

void treeAnalyzerBase::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}


#endif // #ifdef treeAnalyzerBase_h
