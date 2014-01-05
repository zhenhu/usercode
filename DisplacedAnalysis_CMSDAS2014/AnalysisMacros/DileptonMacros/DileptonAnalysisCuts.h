#ifndef DileptonAnalysisCuts_h
#define DileptonAnalysisCuts_h

#include "AnalysisMacros/CommonMacros/treeAnalyzerBase.h"


//
// DILEPTON ANALYSIS CUTS
//

// This class keeps track of which cuts a candidate has failes/passed
// There is no selection on what type of lepton is in the candidate
// There is no selection on trigger or calo matching

// Set of cuts you want to apply
typedef enum {
  // These use d0 signing method
  _final, // final selection cuts
  _looseA, // loose set of cuts 1
  _looseB, // loose set of cuts 2
  _looseC, // loose set of cuts 3
  _2011Cuts, // Similar to 2011 set of cuts
  _removedLifetime, // removed lifetime cuts
  _removedLifetimeNoVertex, // removed lifetime cuts, no vertex

  // These use collinearity method
  _finalColl, // final selection cuts
  _looseColl, // loose selection cuts
  _controlColl, // Invert collinearity to study background
  _looseControlColl // Invert collinearity to study background
}
analysisCuts;

using namespace std;

class DileptonAnalysisCuts {
  public:
    DileptonAnalysisCuts(){};
    DileptonAnalysisCuts( analysisType type, analysisCuts cuts );
    ~DileptonAnalysisCuts() {};

    // Info on which cuts have been passed
    struct PassedWhichCuts
    {
        PassedWhichCuts() :
          passCaloMatch(false),
          passPhotonMatch(false),
          passTrackPt(false),
          passSCEt(false),
          passSCEta(false),
          passEta(false),
          passLeptonD0(false),
          passOppSignD0(false),
          passIso(false),
          passMinLxySig(false),
          passMaxLxySig(false),
          passOppCharge(false),
          passTriggerMatch(false),
          passRequireVertex(false),
          passVertexChi2(false),
          passHitsBeforeVertex(false),
          passMissingHitsAfterVertex(false),
          passDeltaR(false),
          passCosine(false),
          passDeltaPhi(false),
          passMass(false),
          passPhotonID(false),
          passMuonID(false),
          passTrackQuality(false)
        {}

        bool passCaloMatch;
        bool passPhotonMatch;
        bool passTrackPt;
        bool passSCEt;
        bool passSCEta;
        bool passEta;
        bool passLeptonD0;
        bool passOppSignD0;
        bool passIso;
        bool passMinLxySig;
        bool passMaxLxySig;
        bool passOppCharge;
        bool passTriggerMatch;
        bool passRequireVertex;
        bool passVertexChi2;
        bool passHitsBeforeVertex;
        bool passMissingHitsAfterVertex;
        bool passDeltaR;
        bool passCosine;
        bool passDeltaPhi;
        bool passMass;
        bool passPhotonID;
        bool passMuonID;
        bool passTrackQuality;
    };

    // Records which cuts have been passed/failed
    PassedWhichCuts whichCuts( TreeDipseudoLeptonCandidate & candidate, double mass, TreeLepton & leptonL, TreeLepton & leptonH, analysisType analysis, double lxyScale, double d0Scale );
    // Checks of all cuts have been passed
    bool passAllCuts( PassedWhichCuts cuts );

    void printPassForOneCand( DileptonAnalysisCuts::PassedWhichCuts cuts );


    // Useful to print to screen cut info
    void printCutValues();

    // Accessors for cut values
    double getTrackPtCut() { return minTrackPt1_; }
    double getLeadingSCEtCut() { return minSCEt1_; }
    double getSubleadingSCEtCut() { return minSCEt2_; }
    double getTrackEtaCut() { return maxEta_; }
    double getTrackD0SigmaCut() { return minD0Sig_; }


  private:
    // Which set of cuts & analysis
    analysisCuts setOfCuts_;
    analysisType analysisType_;

    // Cut values

    // Individual Leptons
    double minTrackPt1_; // Leading lepton track pt
    double minTrackPt2_; // Subleading lepton track pt
    double minSCEt1_; // Matched SC Et, leading SC threshold
    double minSCEt2_; // Matched SC Et, subleading SC threshold
    double maxSCEta_; // Matched SC max
    double min_gap_SCEta_; // min eta of gap in ECAL to avoid
    double max_gap_SCEta_; // max eta of gap in ECAL to avoid
    double maxEta_; // lepton eta (track)


    bool requireOppositeSignD0_;
    bool cutOnSignedD0_;
    double minD0Sig_; // min value of lepton d0 sig
    double maxD0Sig_; // max value of lepton d0 sig

    double maxIso_; // max sum pt of tracks within isolation cone

    double maxCaloMatchDeltaR_;

    // Photon ID Cuts
    double minR9_;
    double maxHoverE_;
    double maxSigmaIetaIeta_barrel_;
    double maxSigmaIetaIeta_endcap_;

    // Dilepton candidate
    double requireVertex_;

    double minLxySig_; // min value of vertex Lxy significance
    double maxLxySig_; // max value of vertex Lxy significance

    bool oppositeCharge_; // Require leptons oto have opposite charge

    double maxVertexChi2_; // max vertex chi^2

    double maxHitsBeforeVertex_; // max number of hits allowed before vertex
    double maxMissingHitsAfterVertex_; // max number of missing hits allowed after vertex

    double minDeltaR_; // min deltaR between leptons

    double minCosine_; // min 3D angle between two leptons

    double minDeltaPhi_;
    double maxDeltaPhi_; // max value of delta phi between momentum vector of dilepton pair and vector joining primary and displaced vertices

    double minMass_; // min invariant mass of dilepton

};

#endif
