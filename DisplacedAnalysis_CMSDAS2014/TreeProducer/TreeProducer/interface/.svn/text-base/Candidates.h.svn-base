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
      pv_x = -999;
      pv_y = -999;
      pv_z = -999;
      pv_xError = -999;
      pv_yError = -999;
      pv_zError = -999;
      pv_nTracks = -999;
      pv_chi2 = -1;
      pv_ndof = -1;
      bs_x = -999;
      bs_y = -999;
      bs_z = -999;
      numPV = -999;
      nvtx_m1 = -999;
      nvtx_0 = -999;
      nvtx_p1 = -999;
      nvtx_true = -999;
      res1_PdgId = 0;
      res1_Pt = -1;
      res1_Pz = -999999;
      res2_PdgId = 0;
      res2_Pt = -1;
      res2_Pz = -999999;
      ll1_motherPdgId=0;
      ll1_daughterPdgId=0;
      ll1_ctau=-999;
      ll1_pt=-999;
      ll1_pz=-999;
      ll1_E=-999;
      ll1_Et=-999;
      ll1_decayLength2D=-999;
      ll1_decayLength3D=-999;
      ll1_daughter1_PdgId=-999;
      ll1_daughter1_Pt=-999;
      ll1_daughter1_Eta=-999;
      ll1_daughter1_D0=-999;
      ll1_daughter1_Z0=-999;
      ll1_daughter2_PdgId=-999;
      ll1_daughter2_Pt=-999;
      ll1_daughter2_Eta=-999;
      ll1_daughter2_D0=-999;
      ll1_daughter2_Z0=-999;
      ll2_motherPdgId=0;
      ll2_daughterPdgId=0;
      ll2_ctau=-999;
      ll2_pt=-999;
      ll2_pz=-999;
      ll2_E=-999;
      ll2_Et=-999;
      ll2_decayLength2D=-999;
      ll2_decayLength3D=-999;
      ll2_daughter1_PdgId=-999;
      ll2_daughter1_Pt=-999;
      ll2_daughter1_Eta=-999;
      ll2_daughter1_D0=-999;
      ll2_daughter1_Z0=-999;
      ll2_daughter2_PdgId=-999;
      ll2_daughter2_Pt=-999;
      ll2_daughter2_Eta=-999;
      ll2_daughter2_D0=-999;
      ll2_daughter2_Z0=-999;
      MET = -999.;
      METPhi = -999.;
      // triggers.clear();
      leptons_.clear();
      candidates_.clear();
      candidatesCorrectedTipLip_.clear();
    }

    // Event related variables
    Int_t run;
    Int_t lumi;
    Int_t event;

    // Position of primary PV (used for d0 calculations
    Float_t pv_x;
    Float_t pv_y;
    Float_t pv_z;
    Float_t pv_xError;
    Float_t pv_yError;
    Float_t pv_zError;
    Float_t pv_nTracks;
    Float_t pv_chi2;
    Float_t pv_ndof;

    // Beam Spot position
    Float_t bs_x;
    Float_t bs_y;
    Float_t bs_z;

    // Reco PV
    Int_t numPV;

    // MC PV
    Int_t nvtx_m1;
    Int_t nvtx_0;
    Int_t nvtx_p1;
    Float_t nvtx_true;

    // MC Gen info

    // It would be good to add these in
    // Mother resonance
    Int_t res1_PdgId;
    Float_t res1_Pt;
    Float_t res1_Pz;
    Int_t res2_PdgId;
    Float_t res2_Pt;
    Float_t res2_Pz;

    // LL 1
    Int_t ll1_motherPdgId;
    Int_t ll1_daughterPdgId;
    Float_t ll1_ctau;
    Float_t ll1_pt;
    Float_t ll1_pz;
    Float_t ll1_E;
    Float_t ll1_Et;
    Float_t ll1_decayLength2D;
    Float_t ll1_decayLength3D;
    Float_t ll1_daughter1_PdgId;
    Float_t ll1_daughter1_Pt;
    Float_t ll1_daughter1_Eta;
    Float_t ll1_daughter1_D0;
    Float_t ll1_daughter1_Z0;
    Float_t ll1_daughter2_PdgId;
    Float_t ll1_daughter2_Pt;
    Float_t ll1_daughter2_Eta;
    Float_t ll1_daughter2_D0;
    Float_t ll1_daughter2_Z0;

    // LL 2
    Int_t ll2_motherPdgId;
    Int_t ll2_daughterPdgId;
    Float_t ll2_ctau;
    Float_t ll2_pt;
    Float_t ll2_pz;
    Float_t ll2_E;
    Float_t ll2_Et;
    Float_t ll2_decayLength2D;
    Float_t ll2_decayLength3D;
    Float_t ll2_daughter1_PdgId;
    Float_t ll2_daughter1_Pt;
    Float_t ll2_daughter1_Eta;
    Float_t ll2_daughter1_D0;
    Float_t ll2_daughter1_Z0;
    Float_t ll2_daughter2_PdgId;
    Float_t ll2_daughter2_Pt;
    Float_t ll2_daughter2_Eta;
    Float_t ll2_daughter2_D0;
    Float_t ll2_daughter2_Z0;

    // MET
    Float_t MET;
    Float_t METPhi;

    // HLT paths triggered on in a particular event
    // std::vector<std::string> triggers;

    // Pseudoleptons and dipsuedoleptons in event
    std::vector<TreeLepton> leptons_;
    std::vector<TreeDipseudoLeptonCandidate> candidates_;
    std::vector<TreeDipseudoLeptonCandidate> candidatesCorrectedTipLip_;

    // Photons and diphotons in event
    std::vector<TreePhoton> photons_;
    std::vector<TreeDiphotonCandidate> diphotonCandidates_;

    ClassDef(Candidates, 1)
};
ClassImp(Candidates)

#endif // CANDIDATES_H
