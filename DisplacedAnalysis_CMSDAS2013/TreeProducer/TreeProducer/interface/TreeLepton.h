#ifndef TREELEPTON_H
#define TREELEPTON_H

struct TreeLepton
{
  TreeLepton() :
    validTrack(-1),
    pt(-999.), eta(-999.), phi(-999.), charge(-999), d0(-999.), d0Significance(-999.), iso(-999.),
    hasCaloMatch(-999), cmDeltaR(999.), cmDeltaEta(999.), cmDeltaPhi(999), scEnergy(-999), scEt(-999), scEta(-999), scPhi(-999),
    cmDeltaR_old(999), differentSCToOldMethod(-999),
    isStandAloneMuon(-999), isGlobalMuon(-999), isTrackerMuon(-999), isCentralTrack(-999),
    triggerMatch(-999), triggerObjectIndex(-1), tmDeltaR(999), index(-999),
    vx(-999.), vy(-999.), vz(-999.),
    genIndex(-999), genPdgId(0), genPt(-999), genVertexX(-999), genVertexY(-999), genVertexZ(-999), genPhi(-999), genEta(-999), genTheta(-999), genSignalOriginPdgId(0)
  {}

  // Is track valid?
  Int_t validTrack;

  // Pt, eta, phi etc. of original lepton tracks
  Float_t pt;
  Float_t eta;
  Float_t phi;
  Int_t charge;
  Float_t d0;
  Float_t d0Significance;
  // Individual lepton isolated
  Float_t iso;

  // Info on matched SC if any
  Int_t hasCaloMatch;
  // Delta R of pseudolepton to nearest trigger object
  Float_t cmDeltaR;
  Float_t cmDeltaEta;
  Float_t cmDeltaPhi;
  Float_t scEnergy;
  Float_t scEt;
  Float_t scEta;
  Float_t scPhi;
  // Comparison with old version
  Float_t cmDeltaR_old;
  Int_t differentSCToOldMethod;

  // What type of lepton
  Int_t isStandAloneMuon;
  Int_t isGlobalMuon;
  Int_t isTrackerMuon;
  Int_t isCentralTrack;

  // Info on trigger match if any
  Int_t triggerMatch;
  // Index of trigger object match
  // Note this is not index in e.g. list of trigger objects
  // This is just so you can work out if two tracks have been matched to the same TO
  Int_t triggerObjectIndex;
  // Delta R of pseudolepton to nearest trigger object
  Float_t tmDeltaR;
  // Compare with old method
  Float_t tmDeltaR_OLD;

  // Index in treeLepton
  Int_t index;
  // Index in pseudoLepton collection (1<->1)
  Int_t pseudoLeptonIndex;

  // Reference point on track
  Float_t vx;
  Float_t vy;
  Float_t vz;

  // Gen Info
  // Index in genParticle collection
  Int_t genIndex;
  Int_t genPdgId;
  Float_t genPt;
  Float_t genVertexX;
  Float_t genVertexY;
  Float_t genVertexZ;
  Float_t genPhi;
  Float_t genEta;
  Float_t genTheta;
  Int_t genSignalOriginPdgId;

  ClassDef(TreeLepton, 1)
};
ClassImp(TreeLepton)

#endif
