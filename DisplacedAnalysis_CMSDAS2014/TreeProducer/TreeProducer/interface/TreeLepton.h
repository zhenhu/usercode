#ifndef TREELEPTON_H
#define TREELEPTON_H

struct TreeLepton
{
  TreeLepton() :
    validTrack(-1),trackChi2(-1),nLayers(-1),nLayers3D(-1),tip(-9999),lip(-9999),highPurity(-999),
    pt(-999.), eta(-999.), phi(-999.), charge(-999), d0_BS(-999.), d0Significance_BS(-999.),
    d0_PV(-999.), d0Significance_PV(-999.), d0Significance_PV_includingPVError(-999.),
    dz_PV(-999.), dzsignificance_PV(-999), d03D_PV(-999), d03DSignificance_PV_includingPVError(-999),
    iso(-999.),
    hasCaloMatch(-999), cmDeltaR(999.), cmDeltaEta(999.), cmDeltaPhi(999), scEnergy(-999), scEt(-999), scEta(-999), scPhi(-999),
    cmDeltaR_old(999), differentSCToOldMethod(-999),
    hasPhotonMatch(-999), pmDeltaR(999.), photonEnergy(-999), sameSCAsMatched(-1), photonSCEnergy(-999), photonEt(-999), photonEta(-999), photonPhi(-999),
    photonHadronicOverEm(-1), photonHadTowOverEm(-1), photonSigmaIetaIeta(-1), photonR9(-1),
    isStandAloneMuon(-999), isGlobalMuon(-999), isTrackerMuon(-999), isCentralTrack(-999), isLooseMuon(-999),
    triggerMatch(-999), triggerObjectIndex(-1), tmDeltaR(999), index(-999),
    vx(-999.), vy(-999.), vz(-999.),
    genIndex(-999), genPdgId(0), genPt(-999), genVertexX(-999), genVertexY(-999), genVertexZ(-999), genPhi(-999), genEta(-999), genTheta(-999), genSignalOriginPdgId(0)
  {}

  // Is track valid?
  Int_t validTrack;
  Int_t algo; // Which tracking iteration reco'd this track
  Float_t trackChi2;
  Int_t nLayers;
  Int_t nLayers3D;
  Float_t tip; // As defined in track selectors
  Float_t lip;
  Int_t highPurity; // Is high purity

  // Pt, eta, phi etc. of original lepton tracks
  Float_t pt;
  Float_t eta;
  Float_t phi;
  Int_t charge;

  Float_t d0_BS;
  Float_t d0Significance_BS;
  Float_t d0_PV;
  Float_t d0Significance_PV;
  Float_t d0Significance_PV_includingPVError;
  Float_t dz_PV;
  Float_t dzsignificance_PV;
  Float_t d03D_PV;
  Float_t d03DSignificance_PV_includingPVError;

  // Individual lepton isolated
  Float_t iso;

  // Info on matched SC if any
  Int_t hasCaloMatch;
  Float_t cmDeltaR;  // Delta R of pseudolepton to nearest trigger object
  Float_t cmDeltaEta;
  Float_t cmDeltaPhi;
  Float_t scEnergy;
  Float_t scEt;
  Float_t scEta;
  Float_t scPhi;
  Float_t cmDeltaR_old; // Comparison with old version
  Int_t differentSCToOldMethod;

  // Info on matched photon
  Int_t hasPhotonMatch;
  Float_t pmDeltaR;
  Float_t photonEnergy;
  Int_t sameSCAsMatched;  // Whether the SC of this photon is the same as the one matched by deltaR
  Float_t photonSCEnergy;
  Float_t photonSCEt;
  Float_t photonEt;
  Float_t photonEta;
  Float_t photonPhi;
  // ID variables of photon
  Float_t photonHadronicOverEm;
  Float_t photonHadTowOverEm; // Different to above https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonID2012
  Float_t photonSigmaIetaIeta;
  Float_t photonR9;


  // What type of lepton
  Int_t isStandAloneMuon;
  Int_t isGlobalMuon;
  Int_t isTrackerMuon;
  Int_t isCentralTrack;
  Int_t isLooseMuon; // Does muon pass loose id described in https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId

  Int_t triggerMatch; // Info on trigger match if any
  Int_t triggerObjectIndex;  // Index of trigger object match
  // Note this is not index in e.g. list of trigger objects. This is just so you can work out if two tracks have been matched to the same TO
  Float_t tmDeltaR;// Delta R of pseudolepton to nearest trigger object
  Float_t tmDeltaR_OLD;  // Compare with old method

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
  // These angles are for the gen particle extrapolated back to the beamline
  // Can then compare to a track (small correction mostly)
  Float_t genPhi;
  Float_t genEta;
  Float_t genTheta;
  Float_t genD0;
  Int_t genSignalOriginPdgId;
  Float_t genSignalOriginCtau;
  Float_t genSignalOriginLxy;

  ClassDef(TreeLepton, 1)
};
ClassImp(TreeLepton)

#endif
