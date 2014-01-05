#ifndef TREEDIPSEUDOLEPTONCANDIDATE_H
#define TREEDIPSEUDOLEPTONCANDIDATE_H

#include <TObject.h>
#include <TLorentzVector.h>

struct TreeDipseudoLeptonCandidate
{
  TreeDipseudoLeptonCandidate() :
    leptonPtL(-999.), leptonPtH(-999.), leptonEtaL(-999.), leptonEtaH(-999.), leptonChargeL(-999), leptonChargeH(-999), leptonIndexL(-999), leptonIndexH(-999),
    leptonD0L_BS(-9999.), leptonD0H_BS(-9999.), leptonD0SignificanceL_BS(-9999.), leptonD0SignificanceH_BS(-9999.),
    leptonD0L_PV(-9999), leptonD0H_PV(-9999), leptonD0SignificanceL_PV_includingPVError(-9999.), leptonD0SignificanceH_PV_includingPVError(-9999.),
    leptonD0L_PVrefit(-9999), leptonD0H_PVrefit(-9999), leptonD0SignificanceL_PVrefit_includingPVError(-9999.), leptonD0SignificanceH_PVrefit_includingPVError(-9999.),
    leptonD0L_PVrefit_sigWrtPerpDilepton(-9999), leptonD0H_PVrefit_sigWrtPerpDilepton(-9999), leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError(-9999), leptonD0SignificanceH_PVrefit_sigWrtPerpDilepton_includingPVError(-9999),
    leptonD0L_PVrefit_signWrtX(-9999), leptonD0H_PVrefit_signWrtX(-9999), leptonD0SignificanceL_PVrefit_signWrtX_includingPVError(-9999.), leptonD0SignificanceH_PVrefit_signWrtX_includingPVError(-9999.),
    leptonD0L_PVrefit_signWrtPerp(-9999), leptonD0H_PVrefit_signWrtPerp(-9999), leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp(-9999), leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp(-9999), momPhi(-99), dirPhiL(-99), dirPhiH(-99), deltaPhiL(-99), deltaPhiH(-99),
    leptonZ0L_PVRefit(-9999), leptonZ0H_PVRefit(-9999),
    pvRefit_x(-.9),pvRefit_y(-.9),pvRefit_z(-99),pvRefit_xError(-.9),pvRefit_yError(-.9),pvRefit_zError(-.9),pvRefit_nTracks(-9.),
    pvRefit_chi2(-1), pvRefit_ndof(-1),
    leptonIsoL(-999.), leptonIsoH(-999.), leptonIsoL4(-999.), leptonIsoH4(-999.), leptonIsoL5(-999.), leptonIsoH5(-999.),
    cosine(-999.), deltaR(-999.), cosThetaStar(-999.), mass(-999.), corrDileptonMass(-999.),
    caloCorrMass(-999.), scaleCorrMass(-999.), eta(-999.), phi(-999.), etaCorr(-999.), phiCorr(-999.),
    etaCaloCorr(-999.), phiCaloCorr(-999.), decayLength_PV(-999.), decayLengthSignificance_PV(-999.), decayLength_BS(-999.), decayLengthSignificance_BS(-999.),
    dPhi(-999.), dPhiCorr(-999.), dPhiCorrSigned(-999.), dPhiCaloCorr(-999.), hitsBeforeVertexL(-999.), hitsBeforeVertexH(-999.),
    missedLayersAfterVertexL(-999.), missedLayersAfterVertexH(-999.),
    originPdgIdL(-999), originPdgIdH(-999), pdgIdL(-999), pdgIdH(-999), genctau(-999.), genDecayLength2D(-999.), genDecayLength3D(-999.),
    validVertex(-999), vertexChi2(-999.), vx(-999.), vy(-999.), vz(-999.)
  {}

  // Single lepton variables
  // These are the refitted version, so will be slightly different to
  // the corresponding variable in TreeLepton
  Float_t leptonPtL;
  Float_t leptonPtH;
  Float_t leptonEtaL;
  Float_t leptonEtaH;
  Int_t leptonChargeL;
  Int_t leptonChargeH;
  // Index in TreeLepton
  Int_t leptonIndexL;
  Int_t leptonIndexH;
  Float_t leptonD0L_BS;
  Float_t leptonD0H_BS;
  Float_t leptonD0SignificanceL_BS;
  Float_t leptonD0SignificanceH_BS;

  // Lepton Signed Impact Parameters
  // These are wrt PV including PV error
  // And using original (not refitted) tracks
  Float_t leptonD0L_PV;
  Float_t leptonD0H_PV;
  Float_t leptonD0SignificanceL_PV_includingPVError;
  Float_t leptonD0SignificanceH_PV_includingPVError;

  Float_t leptonD0L_PVrefit;
  Float_t leptonD0H_PVrefit;
  Float_t leptonD0SignificanceL_PVrefit_includingPVError;
  Float_t leptonD0SignificanceH_PVrefit_includingPVError;

  Float_t leptonD0L_PVrefit_sigWrtPerpDilepton;
  Float_t leptonD0H_PVrefit_sigWrtPerpDilepton;
  Float_t leptonD0SignificanceL_PVrefit_sigWrtPerpDilepton_includingPVError;
  Float_t leptonD0SignificanceH_PVrefit_sigWrtPerpDilepton_includingPVError;

  Float_t leptonD0L_PVrefit_signWrtX;
  Float_t leptonD0H_PVrefit_signWrtX;
  Float_t leptonD0SignificanceL_PVrefit_signWrtX_includingPVError;
  Float_t leptonD0SignificanceH_PVrefit_signWrtX_includingPVError;

  // Sign wrt vector perpendicular to lepton mom and z-axis
  Float_t leptonD0L_PVrefit_signWrtPerp;
  Float_t leptonD0H_PVrefit_signWrtPerp;
  Float_t leptonD0SignificanceL_PVrefit_includingPVError_signWrtPerp;
  Float_t leptonD0SignificanceH_PVrefit_includingPVError_signWrtPerp;

  Float_t momPhi;
  Float_t dirPhiL;
  Float_t dirPhiH;
  Float_t deltaPhiL;
  Float_t deltaPhiH;

  // z0 after pv refit
  Float_t leptonZ0L_PVRefit;
  Float_t leptonZ0H_PVRefit;

  Float_t pvRefit_x;
  Float_t pvRefit_y;
  Float_t pvRefit_z;
  Float_t pvRefit_xError;
  Float_t pvRefit_yError;
  Float_t pvRefit_zError;
  Float_t pvRefit_nTracks;
  Float_t pvRefit_chi2;
  Float_t pvRefit_ndof;


  // Lepton isolation taking account of other lepton in candidate
  Float_t leptonIsoL;
  Float_t leptonIsoH;
  Float_t leptonIsoL4;
  Float_t leptonIsoH4;
  Float_t leptonIsoL5;
  Float_t leptonIsoH5;

  // Di-lepton variables
  Float_t cosine; // to reject cosmics. Leave unbiased by taking the values before refit to vertex
  Float_t deltaR; // for trigger inefficiencies. Leave unbiased as above.
  Float_t cosThetaStar; // angle between positive lepton momentum in dilepton rest frame and dilepton momentum

  // Track matched to different TO?
  Int_t differentTO;

  // In the following:
  // - the default values are from the leptons
  // - the "corr" values are from the leptons after refit to common vertex
  // - the "triggerCorr" values are from the trigger matches
  // - the "caloCorr" values are from the calo matches
  Float_t mass;
  Float_t corrDileptonMass;
  Float_t caloCorrMass;
  Float_t scaleCorrMass; // corrected so that deltaR between vertex flight direction and di-lepton momentum is 0.
  Float_t transverseMass; // For 3 body decays
  Float_t pt;
  Float_t eta;
  Float_t phi;
  Float_t ptCorr;
  Float_t etaCorr;
  Float_t phiCorr;
  Float_t ptCaloCorr;
  Float_t etaCaloCorr;
  Float_t phiCaloCorr;

  Float_t decayLength_PV;
  Float_t decayLengthSignificance_PV;
  Float_t decayLength_BS;
  Float_t decayLengthSignificance_BS;
  Float_t dPhi; // Angle in transverse plane between vertex (secondary-primay) flight direction and di-lepton momentum
  Float_t dPhiCorr; // Same as above but using leptons refitted to vertex to compute di-lepton momentum
  Float_t dPhiCorrSigned;
  Float_t dPhiTriggerCorr; // Same as above using trigger matches to compute di-lepton momentum
  Float_t dPhiCaloCorr;

  Float_t hitsBeforeVertexL;
  Float_t hitsBeforeVertexH;
  Float_t missedLayersAfterVertexL;
  Float_t missedLayersAfterVertexH;

  // Gen level info
  Int_t originPdgIdL;
  Int_t originPdgIdH;
  Int_t pdgIdL;
  Int_t pdgIdH;
  Float_t genctau;
  Float_t genDecayLength2D;
  Float_t genDecayLength3D;

  // Vertex position and quality
  Int_t validVertex;
  Float_t vertexChi2;
  Float_t vx;
  Float_t vy;
  Float_t vz;

  ClassDef(TreeDipseudoLeptonCandidate, 1)
};
ClassImp(TreeDipseudoLeptonCandidate)

#endif
