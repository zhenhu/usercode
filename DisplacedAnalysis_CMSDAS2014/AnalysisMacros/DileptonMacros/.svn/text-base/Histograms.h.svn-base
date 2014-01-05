#ifndef Histograms_h
#define Histograms_h

//
// HISTOGRAMS
//

// This class does all the book keeping and handling of histograms

#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TProfile.h>
#include <TString.h>
#include <TFile.h>
#include <map>
#include <math.h>
//#include "AnalysisMacros/CommonMacros/commonTools.C"

using namespace std;

class Histograms {
  public:
    Histograms(TString suffix);
    ~Histograms();

    TString nameSuffix;

    void drawOverflows();
    void drawUnderflows();
    void writeHistograms( TFile & outputFile );
    void deleteHistograms();

    // Histograms

    //
    // Individual lepton plots
    // For comparison with other POGs re d0 and Lxy smearing
    //
    TH1F * h_singleLepton_d0;
    TH1F * h_singleLepton_genMatched_d0;
    TH1F * h_singleLepton_d0sigma;
    TH1F * h_singleLepton_sigma;

    // Tracking efficiency plots
    TH1F * h_all_d0;
    TH1F * h_reco_d0;
    TH1F * h_all_lxy;
    TH1F * h_reco_lxy;

    // Neutralino pt plots
    TH1F * h_chiPt_all;
    TH1F * h_chiPt_ss;
    TH1F * h_chiPt_sas;

    //
    // Final cuts
    //
    TH1F * h_mass_finalCuts;
    TH1F * h_mt_finalCuts;
    TH1F * h_Lxy_finalCuts;
    TH1F * h_nRecoPV_finalCuts;
    TH1F * h_leptonHSCEta_finalCuts;
    TH1F * h_leptonLSCEta_finalCuts;
    TH1F * h_minLeptonD0Sig_finalCuts;
    TH1F * h_maxLeptonD0Sig_finalCuts;
    TH1F * h_leptonTrackingAlgo_finalCuts;

    // Reco efficiency plots
    TH1F * h_allExotics_one_genLxy;
    TH1F * h_recoExotics_one_genLxy;
    TH1F * h_recoExotics_coll_one_genLxy;
    TH1F * h_recoExoticsRemovedLifetime_coll_one_genLxy;

    TH1F * h_allExotics_two_genLxy;
    TH1F * h_recoExotics_two_genLxy;
    TH1F * h_recoExotics_coll_two_genLxy;

    TH1F * h_allExotics_one_XPt;
    TH1F * h_recoExotics_one_XPt;
    TH1F * h_recoExotics_coll_one_XPt;
    TH1F * h_allExotics_two_XPt;
    TH1F * h_recoExotics_two_XPt;
    TH1F * h_recoExotics_coll_two_XPt;

    TH1F * h_allExotics_one_nRecoPV;
    TH1F * h_recoExotics_one_nRecoPV;
    TH1F * h_recoExotics_coll_one_nRecoPV;
    TH1F * h_allExotics_two_nRecoPV;
    TH1F * h_recoExotics_two_nRecoPV;
    TH1F * h_recoExotics_coll_two_nRecoPV;

    // Photon ID cuts
    TH1F * h_photonR9_finalCuts;
    TH1F * h_photonSigmaIetaIeta_barrel_finalCuts;
    TH1F * h_photonSigmaIetaIeta_endcap_finalCuts;
    TH1F * h_photonHadTowOverEm_finalCuts;
    TH1F * h_photonHadronicOverEm_finalCuts;

    // n-1 final cuts
    TH1F * h_nMinus1_oppositeCharge_finalCuts;
    TH1F * h_nMinus1_vertexChi2_finalCuts;
    TH1F * h_nMinus1_deltaPhi_finalCuts;
    TH1F * h_nMinus1_cosine_finalCuts;
    TH1F * h_nMinus1_deltaR_finalCuts;
    TH1F * h_nMinus1_nHitsBeforeVertex_finalCuts;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_finalCuts;
    TH1F * h_nMinus1_leptonD0Sig_finalCuts;
    TH1F * h_nMinus1_leptonD0SigMax_finalCuts;
    TH1F * h_nMinus1_leptonD0SigSameSign_finalCuts;
    TH1F * h_nMinus1_leptonAbsD0Sig_oppositeSignMin_finalCuts;
    TH1F * h_nMinus1_leptonD0Sig_oppositeSignMin_finalCuts;
    TH1F * h_nMinus1_leptonD0Sig_oppositeSignMax_finalCuts;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_finalCuts;
    TH1F * h_nMinus1_leadingLeptonTrackPt_finalCuts;
    TH1F * h_nMinus1_subleadingLeptonTrackPt_finalCuts;
    TH1F * h_nMinus1_leadingSCEt_finalCuts;
    TH1F * h_nMinus1_subleadingSCEt_finalCuts;
    TH1F * h_nMinus1_relIso_finalCuts;
    TH1F * h_nMinus1_absIso_finalCuts;

    TH2F * h_nMinus1_leptonD0Sig_vs_LxySig_finalCuts;

    // Gen matched signal only, n-1, final cuts
    TH1F * h_nMinus1_isolationLeptonL_finalCuts_genMatched;
    TH1F * h_nMinus1_isolationLeptonH_finalCuts_genMatched;
    TH1F * h_nMinus1_relIsolationLeptonL_finalCuts_genMatched;
    TH1F * h_nMinus1_relIsolationLeptonH_finalCuts_genMatched;

    // PU dependence
    TH2F * h_nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched;
    TH2F * h_nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched;
    TH2F * h_nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched;
    TH2F * h_nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched;
    TH2F * h_nMinus1_ptLeptonL_vsPU_finalCuts_genMatched;
    TH2F * h_nMinus1_ptLeptonH_vsPU_finalCuts_genMatched;

    TH1F * h_nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_all;
    TH1F * h_nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_pass;
    TH1F * h_nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_all;
    TH1F * h_nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_pass;

    //
    // Loose Cuts A
    //
    TH1F * h_mass_looseCutsA;
    TH1F * h_mt_looseCutsA;
    TH1F * h_Lxy_looseCutsA;
    TH1F * h_nRecoPV_looseCutsA;
    TH1F * h_leptonHSCEta_looseCutsA;
    TH1F * h_leptonLSCEta_looseCutsA;
    TH1F * h_minLeptonD0Sig_looseCutsA;
    TH1F * h_maxLeptonD0Sig_looseCutsA;
    TH1F * h_leptonTrackingAlgo_looseCutsA;

    // n-1 loose cuts
    TH1F * h_nMinus1_oppositeCharge_looseCutsA;
    TH1F * h_nMinus1_vertexChi2_looseCutsA;
    TH1F * h_nMinus1_cosine_looseCutsA;
    TH1F * h_nMinus1_deltaR_looseCutsA;
    TH1F * h_nMinus1_nHitsBeforeVertex_looseCutsA;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_looseCutsA;
    TH1F * h_nMinus1_deltaPhi_looseCutsA;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_looseCutsA;
    TH1F * h_nMinus1_leadingLeptonTrackPt_looseCutsA;
    TH1F * h_nMinus1_subleadingLeptonTrackPt_looseCutsA;
    TH1F * h_nMinus1_leadingSCEt_looseCutsA;
    TH1F * h_nMinus1_subleadingSCEt_looseCutsA;
    TH1F * h_nMinus1_relIso_looseCutsA;
    TH1F * h_nMinus1_absIso_looseCutsA;
    TH1F * h_photonR9_looseCutsA;
    TH1F * h_photonSigmaIetaIeta_barrel_looseCutsA;
    TH1F * h_photonSigmaIetaIeta_endcap_looseCutsA;
    TH1F * h_photonHadTowOverEm_looseCutsA;
    TH1F * h_photonHadronicOverEm_looseCutsA;

    //
    // Loose Cuts B
    //
    TH1F * h_mass_looseCutsB;
    TH1F * h_mt_looseCutsB;
    TH1F * h_Lxy_looseCutsB;
    TH1F * h_nRecoPV_looseCutsB;
    TH1F * h_leptonHSCEta_looseCutsB;
    TH1F * h_leptonLSCEta_looseCutsB;
    TH1F * h_minLeptonD0Sig_looseCutsB;
    TH1F * h_maxLeptonD0Sig_looseCutsB;
    TH1F * h_leptonTrackingAlgo_looseCutsB;

    // n-1 loose cuts
    TH1F * h_nMinus1_oppositeCharge_looseCutsB;
    TH1F * h_nMinus1_vertexChi2_looseCutsB;
    TH1F * h_nMinus1_cosine_looseCutsB;
    TH1F * h_nMinus1_deltaR_looseCutsB;
    TH1F * h_nMinus1_nHitsBeforeVertex_looseCutsB;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_looseCutsB;
    TH1F * h_nMinus1_deltaPhi_looseCutsB;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_looseCutsB;
    TH1F * h_nMinus1_leadingLeptonTrackPt_looseCutsB;
    TH1F * h_nMinus1_subleadingLeptonTrackPt_looseCutsB;
    TH1F * h_nMinus1_leadingSCEt_looseCutsB;
    TH1F * h_nMinus1_subleadingSCEt_looseCutsB;
    TH1F * h_nMinus1_relIso_looseCutsB;
    TH1F * h_nMinus1_absIso_looseCutsB;
    TH1F * h_photonR9_looseCutsB;
    TH1F * h_photonSigmaIetaIeta_barrel_looseCutsB;
    TH1F * h_photonSigmaIetaIeta_endcap_looseCutsB;
    TH1F * h_photonHadTowOverEm_looseCutsB;
    TH1F * h_photonHadronicOverEm_looseCutsB;

    //
    // Loose Cuts C
    //
    TH1F * h_mass_looseCutsC;
    TH1F * h_mt_looseCutsC;
    TH1F * h_Lxy_looseCutsC;
    TH1F * h_nRecoPV_looseCutsC;
    TH1F * h_leptonHSCEta_looseCutsC;
    TH1F * h_leptonLSCEta_looseCutsC;
    TH1F * h_minLeptonD0Sig_looseCutsC;
    TH1F * h_maxLeptonD0Sig_looseCutsC;
    TH1F * h_leptonTrackingAlgo_looseCutsC;

    // n-1 loose cuts
    TH1F * h_nMinus1_oppositeCharge_looseCutsC;
    TH1F * h_nMinus1_vertexChi2_looseCutsC;
    TH1F * h_nMinus1_cosine_looseCutsC;
    TH1F * h_nMinus1_deltaR_looseCutsC;
    TH1F * h_nMinus1_nHitsBeforeVertex_looseCutsC;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_looseCutsC;
    TH1F * h_nMinus1_deltaPhi_looseCutsC;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_looseCutsC;
    TH1F * h_nMinus1_leadingLeptonTrackPt_looseCutsC;
    TH1F * h_nMinus1_subleadingLeptonTrackPt_looseCutsC;
    TH1F * h_nMinus1_leadingSCEt_looseCutsC;
    TH1F * h_nMinus1_subleadingSCEt_looseCutsC;
    TH1F * h_nMinus1_relIso_looseCutsC;
    TH1F * h_nMinus1_absIso_looseCutsC;
    TH1F * h_photonR9_looseCutsC;
    TH1F * h_photonSigmaIetaIeta_barrel_looseCutsC;
    TH1F * h_photonSigmaIetaIeta_endcap_looseCutsC;
    TH1F * h_photonHadTowOverEm_looseCutsC;
    TH1F * h_photonHadronicOverEm_looseCutsC;

    //
    // Removed lifetime cuts
    //
    TH1F * h_mass_removedLifetimeCuts;
    TH1F * h_mt_removedLifetimeCuts;
    TH1F * h_nRecoPV_removedLifetimeCuts;
    TH1F * h_nRecoPV_p5_removedLifetimeCuts;
    TH1F * h_nRecoPV_m5_removedLifetimeCuts;
    TH1F * h_leptonLPt_removedLifetimeCuts;
    TH1F * h_leptonHPt_removedLifetimeCuts;
    TH1F * h_leptonLEta_removedLifetimeCuts;
    TH1F * h_leptonHEta_removedLifetimeCuts;
    TH1F * h_leptonHSCEta_removedLifetimeCuts;
    TH1F * h_leptonLSCEta_removedLifetimeCuts;
    TH1F * h_leptonLCaloMatchDeltaR_removedLifetimeCuts;
    TH1F * h_leptonHCaloMatchDeltaR_removedLifetimeCuts;
    TH1F * h_Lxy_removedLifetimeCuts;
    TH1F * h_LxySig_removedLifetimeCuts;

    //
    // Collinearity study
    //

    // Removed lifetime
    TH1F * h_mass_removedLifetime_CollCuts;
    TH1F * h_mass_removedLifetime_controlCollCuts;
    TH1F * h_nRecoPV_removedLifetimeCollCuts;
    TH1F * h_nRecoPV_p5_removedLifetimeCollCuts;
    TH1F * h_nRecoPV_m5_removedLifetimeCollCuts;

    TH1F * h_deltaPhi_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiL90_forFittingData_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_forFittingData_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiG90_algo4_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiG90_algo5_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiG90_algo6_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiG90_algo7_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiG90_algo8_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiG90_algo9_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiG90_algo10_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiG90_noMissingHits_algo10_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts;
    TH1F * h_deltaPhiSigned_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiMinus_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_deltaPhiPlus_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_bestCand_deltaPhiMinus_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_bestCand_deltaPhiPlus_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts;
    TH1F * h_minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts;
    TH1F * h_minLeptonD0Sig_signedWrtDeltaPhi_forFittingData_removedLifetimeCollCuts;
    TH1F * h_minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts;
    TH1F * h_minLeptonAbsD0Sig_PVnorefit_controlCollCuts;
    TH1F * h_nCandsPerEvent_deltaPhiG90_removedLifetimeCollCuts;
    TH1F * h_nCandsPerEvent_deltaPhiL90_removedLifetimeCollCuts;

    TH1F * h_nMinus1_trigDeltaR_removedLifetimeCollCuts;
    TH1F * h_nMinus1_photonDeltaR_removedLifetimeCollCuts;


    TH1F * h_nMinus1_relIsolationLeptonL_removedLifetimeCollCuts;
    TH1F * h_nMinus1_relIsolationLeptonH_removedLifetimeCollCuts;


    // Final Coll
    TH1F * h_mass_finalCollCuts;
    TH1F * h_mt_finalCollCuts;
    TH1F * h_Lxy_finalCollCuts;
    TH1F * h_nRecoPV_finalCollCuts;
    TH1F * h_leptonHSCEta_finalCollCuts;
    TH1F * h_leptonLSCEta_finalCollCuts;
    TH1F * h_minLeptonD0Sig_finalCollCuts;
    TH1F * h_maxLeptonD0Sig_finalCollCuts;
    TH1F * h_leptonTrackingAlgo_finalCollCuts;
    TH1F * h_ptOverE_finalCollCuts;
    TH1F * h_ptMinusE_finalCollCuts;
    TH1F * h_nCandsPerEvent_finalCollCuts;
    TH1F * h_mass_bestCand_finalCollCuts;
    TH1F * h_Lxy_bestCand_finalCollCuts;

    // n-1 loose cuts
    TH1F * h_nMinus1_oppositeCharge_finalCollCuts;
    TH1F * h_nMinus1_vertexChi2_finalCollCuts;
    TH1F * h_nMinus1_cosine_finalCollCuts;
    TH1F * h_nMinus1_deltaR_finalCollCuts;
    TH1F * h_nMinus1_nHitsBeforeVertex_finalCollCuts;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_finalCollCuts;
    TH1F * h_nMinus1_minMissingHitsAfterVertex_finalCollCuts;
    TH1F * h_nMinus1_maxMissingHitsAfterVertex_finalCollCuts;
    TH1F * h_nMinus1_deltaPhi_finalCollCuts;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_finalCollCuts;
    TH1F * h_nMinus1_leadingLeptonTrackPt_finalCollCuts;
    TH1F * h_nMinus1_subleadingLeptonTrackPt_finalCollCuts;
    TH1F * h_nMinus1_leadingSCEt_finalCollCuts;
    TH1F * h_nMinus1_subleadingSCEt_finalCollCuts;
    TH1F * h_nMinus1_relIso_finalCollCuts;
    TH1F * h_nMinus1_absIso_finalCollCuts;
    TH1F * h_photonR9_finalCollCuts;
    TH1F * h_photonSigmaIetaIeta_barrel_finalCollCuts;
    TH1F * h_photonSigmaIetaIeta_endcap_finalCollCuts;
    TH1F * h_photonHadTowOverEm_finalCollCuts;
    TH1F * h_photonHadronicOverEm_finalCollCuts;

    // Signal isolation plots
    TH2F * h_nMinus1_relIsolationLeptonL_vsPU_finalCollCuts_genMatched;
    TH2F * h_nMinus1_relIsolationLeptonH_vsPU_finalCollCuts_genMatched;
    TH1F * h_nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_all;
    TH1F * h_nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_pass;
    TH1F * h_nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_all;
    TH1F * h_nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_pass;

    // Loose Coll
    TH1F * h_mass_looseCollCuts;
    TH1F * h_mt_looseCollCuts;
    TH1F * h_Lxy_looseCollCuts;
    TH1F * h_nRecoPV_looseCollCuts;
    TH1F * h_leptonHSCEta_looseCollCuts;
    TH1F * h_leptonLSCEta_looseCollCuts;
    TH1F * h_minLeptonD0Sig_looseCollCuts;
    TH1F * h_maxLeptonD0Sig_looseCollCuts;
    TH1F * h_leptonTrackingAlgo_looseCollCuts;
    TH1F * h_ptOverE_looseCollCuts;
    TH1F * h_ptMinusE_looseCollCuts;
    TH1F * h_nCandsPerEvent_looseCollCuts;

    // n-1 loose cuts
    TH1F * h_nMinus1_oppositeCharge_looseCollCuts;
    TH1F * h_nMinus1_vertexChi2_looseCollCuts;
    TH1F * h_nMinus1_cosine_looseCollCuts;
    TH1F * h_nMinus1_deltaR_looseCollCuts;
    TH1F * h_nMinus1_nHitsBeforeVertex_looseCollCuts;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_looseCollCuts;
    TH1F * h_nMinus1_minMissingHitsAfterVertex_looseCollCuts;
    TH1F * h_nMinus1_maxMissingHitsAfterVertex_looseCollCuts;
    TH1F * h_nMinus1_deltaPhi_looseCollCuts;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_looseCollCuts;
    TH1F * h_nMinus1_leadingLeptonTrackPt_looseCollCuts;
    TH1F * h_nMinus1_subleadingLeptonTrackPt_looseCollCuts;
    TH1F * h_nMinus1_leadingSCEt_looseCollCuts;
    TH1F * h_nMinus1_subleadingSCEt_looseCollCuts;
    TH1F * h_nMinus1_relIso_looseCollCuts;
    TH1F * h_nMinus1_absIso_looseCollCuts;
    TH1F * h_photonR9_looseCollCuts;
    TH1F * h_photonSigmaIetaIeta_barrel_looseCollCuts;
    TH1F * h_photonSigmaIetaIeta_endcap_looseCollCuts;
    TH1F * h_photonHadTowOverEm_looseCollCuts;
    TH1F * h_photonHadronicOverEm_looseCollCuts;

    // Loose Control Coll
    TH1F * h_mass_looseControlCollCuts;
    TH1F * h_mt_looseControlCollCuts;
    TH1F * h_Lxy_looseControlCollCuts;
    TH1F * h_nRecoPV_looseControlCollCuts;
    TH1F * h_leptonHSCEta_looseControlCollCuts;
    TH1F * h_leptonLSCEta_looseControlCollCuts;
    TH1F * h_minLeptonD0Sig_looseControlCollCuts;
    TH1F * h_maxLeptonD0Sig_looseControlCollCuts;
    TH1F * h_leptonTrackingAlgo_looseControlCollCuts;
    TH1F * h_ptOverE_looseControlCollCuts;
    TH1F * h_ptMinusE_looseControlCollCuts;
    TH1F * h_nCandsPerEvent_looseControlCollCuts;

    // n-1 loose cuts
    TH1F * h_nMinus1_oppositeCharge_looseControlCollCuts;
    TH1F * h_nMinus1_vertexChi2_looseControlCollCuts;
    TH1F * h_nMinus1_cosine_looseControlCollCuts;
    TH1F * h_nMinus1_deltaR_looseControlCollCuts;
    TH1F * h_nMinus1_nHitsBeforeVertex_looseControlCollCuts;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_looseControlCollCuts;
    TH1F * h_nMinus1_minMissingHitsAfterVertex_looseControlCollCuts;
    TH1F * h_nMinus1_maxMissingHitsAfterVertex_looseControlCollCuts;
    TH1F * h_nMinus1_deltaPhi_looseControlCollCuts;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_looseControlCollCuts;
    TH1F * h_nMinus1_leadingLeptonTrackPt_looseControlCollCuts;
    TH1F * h_nMinus1_subleadingLeptonTrackPt_looseControlCollCuts;
    TH1F * h_nMinus1_leadingSCEt_looseControlCollCuts;
    TH1F * h_nMinus1_subleadingSCEt_looseControlCollCuts;
    TH1F * h_nMinus1_relIso_looseControlCollCuts;
    TH1F * h_nMinus1_relIso3_looseControlCollCuts;
    TH1F * h_nMinus1_relIso4_looseControlCollCuts;
    TH1F * h_nMinus1_relIso5_looseControlCollCuts;

    TH1F * h_nMinus1_absIso_looseControlCollCuts;
    TH1F * h_photonR9_looseControlCollCuts;
    TH1F * h_photonSigmaIetaIeta_barrel_looseControlCollCuts;
    TH1F * h_photonSigmaIetaIeta_endcap_looseControlCollCuts;
    TH1F * h_photonHadTowOverEm_looseControlCollCuts;
    TH1F * h_photonHadronicOverEm_looseControlCollCuts;

    // Control Coll
    TH1F * h_mass_controlCollCuts;
    TH1F * h_mt_controlCollCuts;
    TH1F * h_Lxy_controlCollCuts;
    TH1F * h_nRecoPV_controlCollCuts;
    TH1F * h_leptonHSCEta_controlCollCuts;
    TH1F * h_leptonLSCEta_controlCollCuts;
    TH1F * h_minLeptonD0Sig_controlCollCuts;
    TH1F * h_maxLeptonD0Sig_controlCollCuts;
    TH1F * h_leptonTrackingAlgo_controlCollCuts;
    TH1F * h_ptOverE_controlCollCuts;
    TH1F * h_ptMinusE_controlCollCuts;
    TH1F * h_nCandsPerEvent_controlCollCuts;

    // n-1  cuts
    TH1F * h_nMinus1_oppositeCharge_controlCollCuts;
    TH1F * h_nMinus1_vertexChi2_controlCollCuts;
    TH1F * h_nMinus1_cosine_controlCollCuts;
    TH1F * h_nMinus1_deltaR_controlCollCuts;
    TH1F * h_nMinus1_nHitsBeforeVertex_controlCollCuts;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_controlCollCuts;
    TH1F * h_nMinus1_minMissingHitsAfterVertex_controlCollCuts;
    TH1F * h_nMinus1_maxMissingHitsAfterVertex_controlCollCuts;
    TH1F * h_nMinus1_deltaPhi_controlCollCuts;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_controlCollCuts;
    TH1F * h_nMinus1_leadingLeptonTrackPt_controlCollCuts;
    TH1F * h_nMinus1_subleadingLeptonTrackPt_controlCollCuts;
    TH1F * h_nMinus1_leadingSCEt_controlCollCuts;
    TH1F * h_nMinus1_subleadingSCEt_controlCollCuts;
    TH1F * h_nMinus1_relIso_controlCollCuts;
    TH1F * h_nMinus1_absIso_controlCollCuts;
    TH1F * h_photonR9_controlCollCuts;
    TH1F * h_photonSigmaIetaIeta_barrel_controlCollCuts;
    TH1F * h_photonSigmaIetaIeta_endcap_controlCollCuts;
    TH1F * h_photonHadTowOverEm_controlCollCuts;
    TH1F * h_photonHadronicOverEm_controlCollCuts;

    // d0/sigma
    TH1F * h_minLeptonD0Sig_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_forFittingData_removedLifetimeCuts;

    TH1F * h_minLeptonD0Sig_signedWrtDileptonPerp_removedLifetimeCuts;

    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_badRegion;
    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_badRegion_corrected;

    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2;
    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2_corrected;

    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2;
    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2_corrected;

    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_allRegion;
    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_allRegion_corrected;

    TH1F * h_deltaPhi_removedLifetimeCuts_allRegion;
    TH1F * h_deltaPhi_dileptonLepton_removedLifetimeCuts_allRegion;
    TH1F * h_deltaPhi_dileptonPerpLepton_removedLifetimeCuts_allRegion;

    TH1F * h_deltaPhi_removedLifetimeCuts_badRegion;

    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2;
    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2_corrected;

    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2;
    TH1F * h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2_corrected;


    TH1F * h_bothLeptonsD0Sig_d0Corrected_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0Corrected_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0Corrected_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_d0CorrectedRunDependent_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0CorrectedRunDependent_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_d0CorrectedPixel_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0CorrectedPixel_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0CorrectedPixel_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_d0CorrectedIP_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0CorrectedIP_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_d0CorrectedIP_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_NoCorrections_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_NoCorrections_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_forFittingData_removedLifetimeCuts;

    TH1F * h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts;

    // Opposite sign d0
    TH1F * h_minLeptonD0Sig_oppSign_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_oppSign_forFittingData_removedLifetimeCuts;

    // From different tracking iterations
    TH1F * h_minLeptonD0Sig_algo4_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo5_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo6_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo7_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo8_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo9_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo10_removedLifetimeCuts;

    TH1F * h_minLeptonD0Sig_algo4_forFittingData_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo5_forFittingData_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo6_forFittingData_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo7_forFittingData_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo8_forFittingData_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo9_forFittingData_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_algo10_forFittingData_removedLifetimeCuts;

    TH1F * h_leptonD0BS_algo4_forFittingData_removedLifetimeCuts;


    TH1F * h_maxLeptonD0Sig_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_PVnorefit_removedLifetimeCuts;    // d0/sigma before refit
    TH1F * h_leptonD0_removedLifetimeCuts;    // d0
    TH1F * h_leptonSig_removedLifetimeCuts;    // sigma

    TH1F * h_minLeptonD0SigBL_removedLifetimeCuts;    // wrt BS
    TH2F * h_l_vs_h_leptonD0Sig_removedLifetimeCuts;    // min vs max

    TH1F * h_leptonTrackingAlgo_removedLifetimeCuts;

    // Bias in d0/sigma
    TH1F * h_singleLeptonD0Significance;
    TH2F * h_singleLeptonD0Significance_vs_phi;
    TH2F * h_singleLeptonD0Significance_vs_theta;
    TH3F * h_singleLeptonD0Significance_vs_phi_vs_theta;
    TH3F * h_singleLeptonD0Significance_vs_phi_vs_theta_badRun;
    TH3F * h_singleLeptonD0Significance_vs_phi_vs_theta_noVertex;
    TH3F * h_singleLeptonD0Significance_vs_phi_vs_theta_badRun_noVertex;
    TH3F * h_singleLeptonD0SignificanceG2_vs_phi_vs_theta;
    TH3F * h_singleLeptonD0Significance_vs_phi_vs_theta_pixel;
    TH3F * h_singleLeptonD0Significance_vs_phi_vs_theta_noPixel;
    TH2F * h_leptonD0SigFractionMap_all;
    TH2F * h_leptonD0SigFractionMap_pass;
    TH1F * h_singleLeptonD0Significance_allRegion;
    TH1F * h_singleLeptonD0Significance_allRegion_corrected;
    TH1F * h_singleLeptonD0Significance_noVertex_allRegion;
    TH1F * h_singleLeptonD0Significance_badRegion;
    TH1F * h_singleLeptonD0Significance_badRegion_corrected;

    // Bias in d0
    TH2F * h_singleLeptonD0_vs_phi;
    TH3F * h_singleLeptonD0_vs_phi_vs_theta;
    TH3F * h_singleLeptonD0_vs_phi_vs_theta_badRun;
    TH3F * h_singleLeptonD0_vs_phi_vs_theta_noVertex;
    TH3F * h_singleLeptonD0_vs_phi_vs_theta_badRun_noVertex;
    TH2F * h_singleLeptonD0_vs_run;

    // Bias vs run
    TH2F * h_singleLeptonD0Significance_vs_run;
    TH1F * h_leptonD0SigFraction_vs_run_all;
    TH1F * h_leptonD0SigFraction_vs_run_pass;

    TH1F * h_minLeptonD0Sig_controlTrigger_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_controlVertex_removedLifetimeCuts;
    TH1F * h_minLeptonD0Sig_controlIsolation_removedLifetimeCuts;


    TH3F * h_singleLeptonZ0_vs_phi_vs_theta;
    TH3F * h_singleLeptonZ0_vs_phi_vs_theta_badRun;
    TH3F * h_singleLeptonZ0_vs_phi_vs_theta_noVertex;
    TH3F * h_singleLeptonZ0_vs_phi_vs_theta_badRun_noVertex;
    TH3F * h_singleLeptonZ0_vs_phi_vs_theta_pixel;
    TH3F * h_singleLeptonZ0_vs_phi_vs_theta_noPixel;
    TH2F * h_singleLeptonZ0_vs_run;

    // Photon ID variables
    TH1F * h_photonR9_removedLifetimeCuts;
    TH1F * h_photonSigmaIetaIeta_barrel_removedLifetimeCuts;
    TH1F * h_photonSigmaIetaIeta_endcap_removedLifetimeCuts;
    TH1F * h_photonHadTowOverEm_removedLifetimeCuts;
    TH1F * h_photonHadronicOverEm_removedLifetimeCuts;

    // n-1 removed lifetime cuts
    TH1F * h_nMinus1_isolationLeptonL_removedLifetimeCuts;
    TH1F * h_nMinus1_isolationLeptonH_removedLifetimeCuts;
    TH1F * h_nMinus1_relIsolationLeptonL_removedLifetimeCuts;
    TH1F * h_nMinus1_relIsolationLeptonH_removedLifetimeCuts;
    TH1F * h_nMinus1_nHitsBeforeVertex_removedLifetimeCuts;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_removedLifetimeCuts;
    TH1F * h_nMinus1_maxMissingHitsAfterVertex_removedLifetimeCuts;
    TH1F * h_nMinus1_minMissingHitsAfterVertex_removedLifetimeCuts;
    TH1F * h_nMinus1_vertexChi2_removedLifetimeCuts;
    TH1F * h_nMinus1_vertexChi2_removedLifetimeCuts_vPrompt;

    //
    // Removed Lifetime, No Vertex
    //
    TH1F * h_mass_removedLifetimeNoVertex;
    TH1F * h_mt_removedLifetimeNoVertex;
    TH1F * h_Lxy_removedLifetimeNoVertex;
    TH1F * h_nRecoPV_removedLifetimeNoVertex;
    TH1F * h_leptonHSCEta_removedLifetimeNoVertex;
    TH1F * h_leptonLSCEta_removedLifetimeNoVertex;
    TH1F * h_minLeptonD0Sig_removedLifetimeNoVertex;
    TH1F * h_maxLeptonD0Sig_removedLifetimeNoVertex;
    TH1F * h_leptonTrackingAlgo_removedLifetimeNoVertex;

    // n-1 loose cuts
    TH1F * h_nMinus1_oppositeCharge_removedLifetimeNoVertex;
    TH1F * h_nMinus1_vertexChi2_removedLifetimeNoVertex;
    TH1F * h_nMinus1_cosine_removedLifetimeNoVertex;
    TH1F * h_nMinus1_deltaR_removedLifetimeNoVertex;
    TH1F * h_nMinus1_nHitsBeforeVertex_removedLifetimeNoVertex;
    TH1F * h_nMinus1_nMissingHitsAfterVertex_removedLifetimeNoVertex;
    TH1F * h_nMinus1_deltaPhi_removedLifetimeNoVertex;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_removedLifetimeNoVertex;
    TH1F * h_nMinus1_leadingLeptonTrackPt_removedLifetimeNoVertex;
    TH1F * h_nMinus1_subleadingLeptonTrackPt_removedLifetimeNoVertex;
    TH1F * h_nMinus1_leadingSCEt_removedLifetimeNoVertex;
    TH1F * h_nMinus1_subleadingSCEt_removedLifetimeNoVertex;
    TH1F * h_nMinus1_relIso_removedLifetimeNoVertex;
    TH1F * h_nMinus1_absIso_removedLifetimeNoVertex;
    TH1F * h_photonR9_removedLifetimeNoVertex;
    TH1F * h_photonSigmaIetaIeta_barrel_removedLifetimeNoVertex;
    TH1F * h_photonSigmaIetaIeta_endcap_removedLifetimeNoVertex;
    TH1F * h_photonHadTowOverEm_removedLifetimeNoVertex;
    TH1F * h_photonHadronicOverEm_removedLifetimeNoVertex;

    //
    // 2011 Cuts
    //
    TH1F * h_mass_2011Cuts;

    //
    // Cut optimisation plots
    //
    TH2F * h_minD0SigCut_vs_LxySigCut;

    //
    // Trigger efficiency plots
    //
    TH1F * h_trig_Lxy_all;
    TH1F * h_trig_Lxy_pass;

    TH1F * h_trig_ctau_all;
    TH1F * h_trig_ctau_pass;

    // Trigger plots vs. mean lifetime
    // Note -- these are NOT created in this class but rather inside
    // DileptonAnalyzer, since they depend on parameters known only
    // to the analyzer.

    vector<TProfile *> h_trigEff_meanLifetime;
    vector<TProfile *> h_trigEff_meanLifetimeLog;

    map< TString, TH1F*> histMap;

    map< TString, TH1F* > histMapFinal;
    map< TString, TH1F* > histMapLooseA;
    map< TString, TH1F* > histMapLooseB;
    map< TString, TH1F* > histMapLooseC;
    map< TString, TH1F* > histMapRemovedLifetimeNoVertex;

    map< TString, TH1F* > histMapFinalColl;
    map< TString, TH1F* > histMapLooseColl;
    map< TString, TH1F* > histMapLooseControlColl;
    map< TString, TH1F* > histMapControlColl;

    TH1F * initHist(TH1F * hist, TString name, TString title, const unsigned int nBins, const float xMin, const float xMax);

    void overflow(TH1F &h);
    void underflow(TH1F &h);
};

#endif
