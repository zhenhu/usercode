#ifndef CANDIDATES_H
#define CANDIDATES_H

#include <TObject.h>
#include <TLorentzVector.h>
#include <string>
#include <vector>
#include "TreeProducer/TreeProducer/interface/TreeLepton.h"
#include "TreeProducer/TreeProducer/interface/TreeDipseudoLeptonCandidate.h"
#include "TreeProducer/TreeProducer/interface/TreePhoton.h"
#include "TreeProducer/TreeProducer/interface/TreeDiphotonCandidate.h"

struct Candidates : public TObject
{
    Candidates()
    {}

    void clear()
    {
      run = -999;
      event = -999;
      numPV = -999;
      nvtx_m1 = -999;
      nvtx_0 = -999;
      nvtx_p1 = -999;
      nvtx_true = -999;
      ll1_motherPdgId=0;
      ll1_daughterPdgId=0;
      ll1_ctau=-999;
      ll1_decayLength2D=-999;
      ll1_decayLength3D=-999;
      ll1_daughter1_Pt=-999;
      ll1_daughter1_D0=-999;
      ll1_daughter2_Pt=-999;
      ll1_daughter2_D0=-999;
      ll2_motherPdgId=0;
      ll2_daughterPdgId=0;
      ll2_ctau=-999;
      ll2_decayLength2D=-999;
      ll2_decayLength3D=-999;
      ll2_daughter1_Pt=-999;
      ll2_daughter1_D0=-999;
      ll2_daughter2_Pt=-999;
      ll2_daughter2_D0=-999;
      MET = -999.;
      METPhi = -999.;
      // triggers.clear();
      leptons_.clear();
      candidates_.clear();
    }

    // Event related variables
    Int_t run;
    Int_t lumi;
    Int_t event;

    // Reco PV
    Int_t numPV;

    // MC PV
    Int_t nvtx_m1;
    Int_t nvtx_0;
    Int_t nvtx_p1;
    Float_t nvtx_true;

    // MC Gen info

    // LL 1
    Int_t ll1_motherPdgId;
    Int_t ll1_daughterPdgId;
    Float_t ll1_ctau;
    Float_t ll1_decayLength2D;
    Float_t ll1_decayLength3D;
    Float_t ll1_daughter1_Pt;
    Float_t ll1_daughter1_D0;
    Float_t ll1_daughter2_Pt;
    Float_t ll1_daughter2_D0;

    // LL 2
    Int_t ll2_motherPdgId;
    Int_t ll2_daughterPdgId;
    Float_t ll2_ctau;
    Float_t ll2_decayLength2D;
    Float_t ll2_decayLength3D;
    Float_t ll2_daughter1_Pt;
    Float_t ll2_daughter1_D0;
    Float_t ll2_daughter2_Pt;
    Float_t ll2_daughter2_D0;

    // MET
    Float_t MET;
    Float_t METPhi;

    // HLT paths triggered on in a particular event
    // std::vector<std::string> triggers;

    // Pseudoleptons and dipsuedoleptons in event
    std::vector<TreeLepton> leptons_;
    std::vector<TreeDipseudoLeptonCandidate> candidates_;

    // Photons and diphotons in event
    std::vector<TreePhoton> photons_;
    std::vector<TreeDiphotonCandidate> diphotonCandidates_;

    ClassDef(Candidates, 1)
};
ClassImp(Candidates)

#endif // CANDIDATES_H
