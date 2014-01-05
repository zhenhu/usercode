#define Histograms_cxx

#include "Histograms.h"

Histograms::Histograms(TString suffix=""):
nameSuffix(suffix)
{
  // Book some histograms
  TH1::SetDefaultSumw2();

  // Individual lepton plots
  h_singleLepton_d0=initHist(h_singleLepton_d0,"singleLepton_d0", "Individual lepton d0", 20, 0, 0.2);
  h_singleLepton_d0sigma=initHist(h_singleLepton_d0sigma,"singleLepton_d0sigma", "Individual lepton d0/sigma", 20, 0, 8);
  h_singleLepton_sigma=initHist(h_singleLepton_sigma,"singleLepton_sigma", "Individual lepton sigma", 20, 0, 0.01);

  // Tracking efficiency plots
  h_all_d0=initHist(h_all_d0,"all_d0","Gen all d0",25,0,50);
  h_reco_d0=initHist(h_reco_d0,"reco_d0","Gen recod d0",25,0,50);
  h_all_lxy=initHist(h_all_lxy,"all_lxy","Gen all lxy",50,0,100);
  h_reco_lxy=initHist(h_reco_lxy,"reco_lxy","Gen recod lxy",50,0,100);

  // Neutralino pt plots
  h_chiPt_all=initHist(h_chiPt_all,"ChiPt_all","Neutralino gen pt",75,0,2500);
  h_chiPt_ss=initHist(h_chiPt_ss,"ChiPt_ss","Neutralino gen pt, squark squark production",75,0,2500);
  h_chiPt_sas=initHist(h_chiPt_sas,"ChiPt_sas","Neutralino gen pt, squakr antisquark production",75,0,2500);

  // Final set of cuts
  h_mass_finalCuts=initHist(h_mass_finalCuts,"Mass_finalCuts","Dilepton mass, final cuts",75,0,500);
  h_mt_finalCuts=initHist(h_mt_finalCuts,"Mt_finalCuts", "Dilepton Mt, final cuts", 75, 0, 500);
  h_Lxy_finalCuts=initHist(h_Lxy_finalCuts,"Lxy_finalCuts", "Dilepton Lxy, final cuts", 100, -50, 50);
  h_nRecoPV_finalCuts=initHist(h_nRecoPV_finalCuts,"nRecoPV_finalCuts", "Number reco PV, final cuts", 50, 0, 50);
  h_leptonHSCEta_finalCuts=initHist(h_leptonHSCEta_finalCuts,"leptonHSCEta_finalCuts", "Eta leading lepton, final cuts",60,-3,3);
  h_leptonLSCEta_finalCuts=initHist(h_leptonLSCEta_finalCuts,"leptonLSCEta_finalCuts", "Eta subleading lepton, final cuts",60,-3,3);
  h_minLeptonD0Sig_finalCuts=initHist(h_minLeptonD0Sig_finalCuts,"minLeptonD0Sig_finalCuts", "Max leptond0/sigma, final cuts",60,-20,10);
  h_maxLeptonD0Sig_finalCuts=initHist(h_maxLeptonD0Sig_finalCuts,"maxLeptonD0Sig_finalCuts", "Max leptond0/sigma, final cuts",60,-20,10);
  h_leptonTrackingAlgo_finalCuts=initHist(h_leptonTrackingAlgo_finalCuts,"leptonTrackingAlgo_finalCuts","Tracker reco algo",30,0,30);

  // Reco efficiency plots
  h_allExotics_two_genLxy=initHist(h_allExotics_two_genLxy,"allExotics_two_genLxy", "Gen Lxy of all exotics", 18, 0, 60 );
  h_recoExotics_two_genLxy=initHist(h_recoExotics_two_genLxy,"recoExotics_two_genLxy", "Gen Lxy of reco'd and correctly reco'd exotics", 18, 0, 60 );
  h_recoExotics_coll_two_genLxy=initHist(h_recoExotics_coll_two_genLxy,"recoExotics_coll_two_genLxy", "Gen Lxy of reco'd and correctly reco'd exotics", 18, 0, 60 );
  h_allExotics_one_genLxy=initHist(h_allExotics_one_genLxy,"allExotics_one_genLxy", "Gen Lxy of all exotics", 72, 0, 60 );
  h_recoExotics_one_genLxy=initHist(h_recoExotics_one_genLxy,"recoExotics_one_genLxy", "Gen Lxy of reco'd and correctly reco'd exotics", 72, 0, 60 );
  h_recoExotics_coll_one_genLxy=initHist(h_recoExotics_coll_one_genLxy,"recoExotics_coll_one_genLxy", "Gen Lxy of reco'd and correctly reco'd exotics", 72, 0, 60 );
  h_recoExoticsRemovedLifetime_coll_one_genLxy=initHist(h_recoExoticsRemovedLifetime_coll_one_genLxy,"recoExoticsRemovedLifetime_coll_one_genLxy", "Gen Lxy of reco'd and correctly reco'd exotics", 72, 0, 60 );

  h_allExotics_two_XPt=initHist(h_allExotics_two_XPt,"allExotics_two_XPt", "X pt of all exotics", 50, 0, 1000 );
  h_recoExotics_two_XPt=initHist(h_recoExotics_two_XPt,"recoExotics_two_XPt", "X pt of reco'd and correctly reco'd exotics", 50, 0, 1000 );
  h_recoExotics_coll_two_XPt=initHist(h_recoExotics_coll_two_XPt,"recoExotics_coll_two_XPt", "X pt of reco'd and correctly reco'd exotics", 50, 0, 1000 );
  h_allExotics_one_XPt=initHist(h_allExotics_one_XPt,"allExotics_one_XPt", "X pt of all exotics", 50, 0, 1000 );
  h_recoExotics_one_XPt=initHist(h_recoExotics_one_XPt,"recoExotics_one_XPt", "X pt of reco'd and correctly reco'd exotics", 50, 0, 1000 );
  h_recoExotics_coll_one_XPt=initHist(h_recoExotics_coll_one_XPt,"recoExotics_coll_one_XPt", "X pt of reco'd and correctly reco'd exotics", 50, 0, 1000 );

  h_allExotics_two_nRecoPV=initHist(h_nRecoPV_finalCuts,"allExotics_two_nRecoPV", "Number of reco PV in event, all exotics", 50, 0, 50 );
  h_recoExotics_two_nRecoPV=initHist(h_recoExotics_two_nRecoPV,"recoExotics_two_nRecoPV", "Number of reco PV in event, correctly reco'd exotics", 50, 0, 50 );
  h_recoExotics_coll_two_nRecoPV=initHist(h_recoExotics_coll_two_nRecoPV,"recoExotics_coll_two_nRecoPV", "Number of reco PV in event, correctly reco'd exotics", 50, 0, 50 );
  h_allExotics_one_nRecoPV=initHist(h_allExotics_one_nRecoPV,"allExotics_one_nRecoPV", "Number of reco PV in event, exotics", 50, 0, 50 );
  h_recoExotics_one_nRecoPV=initHist(h_recoExotics_one_nRecoPV,"recoExotics_one_nRecoPV", "Number of reco PV in event, correctly reco'd exotics", 50, 0, 50 );
  h_recoExotics_coll_one_nRecoPV=initHist(h_recoExotics_coll_one_nRecoPV,"recoExotics_coll_one_nRecoPV", "Number of reco PV in event, correctly reco'd exotics", 50, 0, 50 );

  // Photon ID Cuts
  h_photonR9_finalCuts=initHist(h_photonR9_finalCuts,"PhotonR9_finalCuts", "Photon R9, final cuts", 20, 0, 1.1);
  h_photonSigmaIetaIeta_barrel_finalCuts=initHist(h_photonSigmaIetaIeta_barrel_finalCuts,"PhotonSigmaIetaIeta_barrel_finalCuts", "Photon SigmaIetaIeta, barrel, final cuts", 40, 0, 0.05);
  h_photonSigmaIetaIeta_endcap_finalCuts=initHist(h_photonSigmaIetaIeta_endcap_finalCuts,"PhotonSigmaIetaIeta_endcap_finalCuts", "Photon SigmaIetaIeta, endcap, final cuts", 40, 0, 0.05);
  h_photonHadTowOverEm_finalCuts=initHist(h_photonHadTowOverEm_finalCuts,"PhotonHadTowOverEm_finalCuts", "Photon HadTowOverEm, final cuts", 20, 0, 0.2);
  h_photonHadronicOverEm_finalCuts=initHist(h_photonHadronicOverEm_finalCuts,"PhotonHadronicOverEm_finalCuts", "Photon HadronicOverEm, final cuts", 20, 0, 0.2);

  // n-1 final cuts
  h_nMinus1_oppositeCharge_finalCuts=initHist(h_nMinus1_oppositeCharge_finalCuts,"nMinus1_oppositeCharge_finalCuts", "n-1 lepton opposite charges, final cuts",5,-2,2);
  h_nMinus1_vertexChi2_finalCuts=initHist(h_nMinus1_vertexChi2_finalCuts,"nMinus1_vertexChi2_finalCuts", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
  h_nMinus1_deltaPhi_finalCuts=initHist(h_nMinus1_deltaPhi_finalCuts,"nMinus1_deltaPhi_finalCuts", "n-1 Delta Phi, final cuts", 40, 0, 4);
  h_nMinus1_cosine_finalCuts=initHist(h_nMinus1_cosine_finalCuts,"nMinus1_cosine_finalCuts", "n-1 Cosine, final cuts",22,-1.1,1.1);
  h_nMinus1_deltaR_finalCuts=initHist(h_nMinus1_deltaR_finalCuts,"nMinus1_deltaR_finalCuts", "n-1 delta R, final cuts",10,0,0.5);
  h_nMinus1_nHitsBeforeVertex_finalCuts=initHist(h_nMinus1_nHitsBeforeVertex_finalCuts,"nMinus1_nHitsBeforeVertex_finalCuts", "n-1 N hits before vertex", 5, -0.5, 4.5);
  h_nMinus1_nMissingHitsAfterVertex_finalCuts=initHist(h_nMinus1_nMissingHitsAfterVertex_finalCuts,"nMinus1_nMissingHitsAfterVertex_finalCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
  h_nMinus1_leptonD0Sig_finalCuts=initHist(h_nMinus1_leptonD0Sig_finalCuts,"nMinus1_leptonD0Sig_finalCuts", "n-1 Min Lepton D0 Significance, no smearing", 60, -20, 10 );
  h_nMinus1_leptonD0SigMax_finalCuts=initHist(h_nMinus1_leptonD0SigMax_finalCuts,"nMinus1_leptonD0SigMax_finalCuts", "n-1 Max Lepton D0 Significance, no smearing", 80, -20, 20 );
  h_nMinus1_leptonD0SigSameSign_finalCuts=initHist(h_nMinus1_leptonD0SigSameSign_finalCuts,"nMinus1_leptonD0SigSameSign_finalCuts", "n-1 Same sign d0/sigma", 5,-2, 2);
  h_nMinus1_leptonAbsD0Sig_oppositeSignMin_finalCuts=initHist(h_nMinus1_leptonAbsD0Sig_oppositeSignMin_finalCuts,"nMinus1_leptonAbsD0Sig_oppositeSignMin_finalCuts", "n-1 Min Lepton D0 Significance, no smearing", 10, 0, 10 );
  h_nMinus1_leptonD0Sig_oppositeSignMin_finalCuts=initHist(h_nMinus1_leptonD0Sig_oppositeSignMin_finalCuts,"nMinus1_leptonD0Sig_oppositeSignMin_finalCuts", "n-1 opposite sign d0/sigma", 60,-20, 10);
  h_nMinus1_leptonD0Sig_oppositeSignMax_finalCuts=initHist(h_nMinus1_leptonD0Sig_oppositeSignMax_finalCuts,"nMinus1_leptonD0Sig_oppositeSignMax_finalCuts", "n-1 opposite sign d0/sigma", 80, -20, 20 );
  h_nMinus1_leptonCaloMatchDeltaR_finalCuts=initHist(h_nMinus1_leptonCaloMatchDeltaR_finalCuts,"nMinus1_leptonCaloMatchDeltaR_finalCuts","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
  h_nMinus1_leadingLeptonTrackPt_finalCuts=initHist(h_nMinus1_leadingLeptonTrackPt_finalCuts,"nMinus1_leadingLeptonTrackPt_finalCuts","n-1 Leading lepton track pt, final cuts",20,0,80);
  h_nMinus1_subleadingLeptonTrackPt_finalCuts=initHist(h_nMinus1_subleadingLeptonTrackPt_finalCuts,"nMinus1_subleadingLeptonTrackPt_finalCuts","n-1 Subleading lepton track pt, final cuts",20,0,80);
  h_nMinus1_leadingSCEt_finalCuts=initHist(h_nMinus1_leadingSCEt_finalCuts,"nMinus1_leadingSCEt_finalCuts", "n-1 leading SC Et, final cuts",100,0,150);
  h_nMinus1_subleadingSCEt_finalCuts=initHist(h_nMinus1_subleadingSCEt_finalCuts,"nMinus1_subleadingSCEt_finalCuts", "n-1 subleading SC Et, final cuts",100,0,150);
  h_nMinus1_relIso_finalCuts=initHist(h_nMinus1_relIso_finalCuts,"nMinus1_relIso_finalCuts", "n-1 lepton rel iso, final cuts", 40, 0, 0.5);
  h_nMinus1_absIso_finalCuts=initHist(h_nMinus1_absIso_finalCuts,"nMinus1_absIso_finalCuts", "n-1 lepton abs iso, final cuts", 80, 0, 20);

  h_nMinus1_leptonD0Sig_vs_LxySig_finalCuts = new TH2F(TString("nMinus1_leptonD0Sig_vs_LxySig_finalCuts")+nameSuffix, "d0 sig vs lxy sig", 40, 0, 10, 40, 0, 20 );

  // n-1 final cuts, gen matched signal only
  h_nMinus1_isolationLeptonL_finalCuts_genMatched=initHist(h_nMinus1_isolationLeptonL_finalCuts_genMatched,"nMinus1_isolationLeptonL_finalCuts_genMatched", "n-1 Isolation low pt lepton, final cuts, gen matched signal", 80, 0, 20 );
  h_nMinus1_isolationLeptonH_finalCuts_genMatched=initHist(h_nMinus1_isolationLeptonH_finalCuts_genMatched,"nMinus1_isolationHeptonH_finalCuts_genMatched", "n-1 Isolation high pt lepton, final cuts, gen matched signal", 80, 0, 20 );
  h_nMinus1_relIsolationLeptonL_finalCuts_genMatched=initHist(h_nMinus1_relIsolationLeptonL_finalCuts_genMatched,"nMinus1_relIsolationLeptonL_finalCuts_genMatched", "n-1 Rel. Isolation low pt lepton, final cuts, gen matched signal", 20, 0, 0.2 );
  h_nMinus1_relIsolationLeptonH_finalCuts_genMatched=initHist(h_nMinus1_relIsolationLeptonH_finalCuts_genMatched,"nMinus1_relIsolationHeptonH_finalCuts_genMatched", "n-1 Rel. Isolation high pt lepton, final cuts, gen matched signal", 20, 0, 0.2 );

//  //
//  // LOOSE CUTS A
//  //
//  h_mass_looseCutsA=initHist(h_mass_looseCutsA,"Mass_looseCutsA","Dilepton mass, loose cuts",75,0,500);
//  h_mt_looseCutsA=initHist(h_mt_looseCutsA,"Mt_looseCutsA", "Dilepton Mt, final cuts", 75, 0, 500);
//  h_Lxy_looseCutsA=initHist(h_Lxy_looseCutsA,"Lxy_looseCutsA", "Lxy loose cuts",100,0,70);
//  h_nRecoPV_looseCutsA=initHist(h_nRecoPV_looseCutsA,"nRecoPV_looseCutsA", "Number reco PV, final cuts", 50, 0, 50);
//  h_leptonHSCEta_looseCutsA=initHist(h_leptonHSCEta_looseCutsA,"leptonHSCEta_looseCutsA", "Eta leading lepton, final cuts",60,-3,3);
//  h_leptonLSCEta_looseCutsA=initHist(h_leptonLSCEta_looseCutsA,"leptonLSCEta_looseCutsA", "Eta subleading lepton, final cuts",60,-3,3);
//  h_minLeptonD0Sig_looseCutsA=initHist(h_minLeptonD0Sig_looseCutsA,"minLeptonD0Sig_looseCutsA", "Min leptond0/sigma, final cuts",60,-20,10);
//  h_maxLeptonD0Sig_looseCutsA=initHist(h_maxLeptonD0Sig_looseCutsA,"maxLeptonD0Sig_looseCutsA", "Max leptond0/sigma, final cuts",60,-20,10);
//  h_leptonTrackingAlgo_looseCutsA=initHist(h_leptonTrackingAlgo_looseCutsA,"leptonTrackingAlgo_looseCutsA","Tracker reco algo",30,0,30);
//
//  // n-1 final cuts
//  h_nMinus1_oppositeCharge_looseCutsA=initHist(h_nMinus1_oppositeCharge_looseCutsA,"nMinus1_oppositeCharge_looseCutsA", "n-1 lepton opposite charges, final cuts",5,-2,2);
//  h_nMinus1_vertexChi2_looseCutsA=initHist(h_nMinus1_vertexChi2_looseCutsA,"nMinus1_vertexChi2_looseCutsA", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
//  h_nMinus1_deltaPhi_looseCutsA=initHist(h_nMinus1_deltaPhi_looseCutsA,"nMinus1_deltaPhi_looseCutsA", "n-1 Delta Phi, final cuts", 40, 0, 4);
//  h_nMinus1_cosine_looseCutsA=initHist(h_nMinus1_cosine_looseCutsA,"nMinus1_cosine_looseCutsA", "n-1 Cosine, final cuts",22,-1.1,1.1);
//  h_nMinus1_deltaR_looseCutsA=initHist(h_nMinus1_deltaR_looseCutsA,"nMinus1_deltaR_looseCutsA", "n-1 delta R, final cuts",10,0,0.5);
//  h_nMinus1_nHitsBeforeVertex_looseCutsA=initHist(h_nMinus1_nHitsBeforeVertex_looseCutsA,"nMinus1_nHitsBeforeVertex_looseCutsA", "n-1 N hits before vertex", 5, 0, 5);
//  h_nMinus1_nMissingHitsAfterVertex_looseCutsA=initHist(h_nMinus1_nMissingHitsAfterVertex_looseCutsA,"nMinus1_nMissingHitsAfterVertex_looseCutsA", "n-1 N missing hits after vertex", 20, 0, 20);
//  h_nMinus1_leptonCaloMatchDeltaR_looseCutsA=initHist(h_nMinus1_leptonCaloMatchDeltaR_looseCutsA,"nMinus1_leptonCaloMatchDeltaR_looseCutsA","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
//  h_nMinus1_leadingLeptonTrackPt_looseCutsA=initHist(h_nMinus1_leadingLeptonTrackPt_looseCutsA,"nMinus1_leadingLeptonTrackPt_looseCutsA","n-1 Leading lepton track pt, final cuts",20,0,80);
//  h_nMinus1_subleadingLeptonTrackPt_looseCutsA=initHist(h_nMinus1_subleadingLeptonTrackPt_looseCutsA,"nMinus1_subleadingLeptonTrackPt_looseCutsA","n-1 Subleading lepton track pt, final cuts",20,0,80);
//  h_nMinus1_leadingSCEt_looseCutsA=initHist(h_nMinus1_leadingSCEt_looseCutsA,"nMinus1_leadingSCEt_looseCutsA", "n-1 leading SC Et, final cuts",100,0,150);
//  h_nMinus1_subleadingSCEt_looseCutsA=initHist(h_nMinus1_subleadingSCEt_looseCutsA,"nMinus1_subleadingSCEt_looseCutsA", "n-1 subleading SC Et, final cuts",100,0,150);
//  h_nMinus1_relIso_looseCutsA=initHist(h_nMinus1_relIso_looseCutsA,"nMinus1_relIso_looseCutsA", "n-1 lepton rel iso, final cuts", 20, 0, 0.2);
//  h_nMinus1_absIso_looseCutsA=initHist(h_nMinus1_absIso_looseCutsA,"nMinus1_absIso_looseCutsA", "n-1 lepton abs iso, final cuts", 80, 0, 20);
//  // Photon ID Cuts
//  h_photonR9_looseCutsA=initHist(h_photonR9_looseCutsA,"PhotonR9_looseCutsA", "Photon R9, final cuts", 20, 0, 1.1);
//  h_photonSigmaIetaIeta_barrel_looseCutsA=initHist(h_photonSigmaIetaIeta_barrel_looseCutsA,"PhotonSigmaIetaIeta_barrel_looseCutsA", "Photon SigmaIetaIeta, barrel, final cuts", 40, 0, 0.05);
//  h_photonSigmaIetaIeta_endcap_looseCutsA=initHist(h_photonSigmaIetaIeta_endcap_looseCutsA,"PhotonSigmaIetaIeta_endcap_looseCutsA", "Photon SigmaIetaIeta, endcap, final cuts", 40, 0, 0.05);
//  h_photonHadTowOverEm_looseCutsA=initHist(h_photonHadTowOverEm_looseCutsA,"PhotonHadTowOverEm_looseCutsA", "Photon HadTowOverEm, final cuts", 20, 0, 0.2);
//  h_photonHadronicOverEm_looseCutsA=initHist(h_photonHadronicOverEm_looseCutsA,"PhotonHadronicOverEm_looseCutsA", "Photon HadronicOverEm, final cuts", 20, 0, 0.2);
//
//  //
//  // LOOSE CUTS B
//  //
//  h_mass_looseCutsB=initHist(h_mass_looseCutsB,"Mass_looseCutsB","Dilepton mass, loose cuts",75,0,500);
//  h_mt_looseCutsB=initHist(h_mt_looseCutsB,"Mt_looseCutsB", "Dilepton Mt, final cuts", 75, 0, 500);
//  h_Lxy_looseCutsB=initHist(h_Lxy_looseCutsB,"Lxy_looseCutsB", "Lxy loose cuts",100,0,70);
//  h_nRecoPV_looseCutsB=initHist(h_nRecoPV_looseCutsB,"nRecoPV_looseCutsB", "Number reco PV, final cuts", 50, 0, 50);
//  h_leptonHSCEta_looseCutsB=initHist(h_leptonHSCEta_looseCutsB,"leptonHSCEta_looseCutsB", "Eta leading lepton, final cuts",60,-3,3);
//  h_leptonLSCEta_looseCutsB=initHist(h_leptonLSCEta_looseCutsB,"leptonLSCEta_looseCutsB", "Eta subleading lepton, final cuts",60,-3,3);
//  h_minLeptonD0Sig_looseCutsB=initHist(h_minLeptonD0Sig_looseCutsB,"minLeptonD0Sig_looseCutsB", "Min leptond0/sigma, final cuts",60,-20,10);
//  h_maxLeptonD0Sig_looseCutsB=initHist(h_maxLeptonD0Sig_looseCutsB,"maxLeptonD0Sig_looseCutsB", "Max leptond0/sigma, final cuts",60,-20,10);
//  h_leptonTrackingAlgo_looseCutsB=initHist(h_leptonTrackingAlgo_looseCutsB,"leptonTrackingAlgo_looseCutsB","Tracker reco algo",30,0,30);
//
//  // n-1 final cuts
//  h_nMinus1_oppositeCharge_looseCutsB=initHist(h_nMinus1_oppositeCharge_looseCutsB,"nMinus1_oppositeCharge_looseCutsB", "n-1 lepton opposite charges, final cuts",5,-2,2);
//  h_nMinus1_vertexChi2_looseCutsB=initHist(h_nMinus1_vertexChi2_looseCutsB,"nMinus1_vertexChi2_looseCutsB", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
//  h_nMinus1_deltaPhi_looseCutsB=initHist(h_nMinus1_deltaPhi_looseCutsB,"nMinus1_deltaPhi_looseCutsB", "n-1 Delta Phi, final cuts", 40, 0, 4);
//  h_nMinus1_cosine_looseCutsB=initHist(h_nMinus1_cosine_looseCutsB,"nMinus1_cosine_looseCutsB", "n-1 Cosine, final cuts",22,-1.1,1.1);
//  h_nMinus1_deltaR_looseCutsB=initHist(h_nMinus1_deltaR_looseCutsB,"nMinus1_deltaR_looseCutsB", "n-1 delta R, final cuts",10,0,0.5);
//  h_nMinus1_nHitsBeforeVertex_looseCutsB=initHist(h_nMinus1_nHitsBeforeVertex_looseCutsB,"nMinus1_nHitsBeforeVertex_looseCutsB", "n-1 N hits before vertex", 5, 0, 5);
//  h_nMinus1_nMissingHitsAfterVertex_looseCutsB=initHist(h_nMinus1_nMissingHitsAfterVertex_looseCutsB,"nMinus1_nMissingHitsAfterVertex_looseCutsB", "n-1 N missing hits after vertex", 20, 0, 20);
//  h_nMinus1_leptonCaloMatchDeltaR_looseCutsB=initHist(h_nMinus1_leptonCaloMatchDeltaR_looseCutsB,"nMinus1_leptonCaloMatchDeltaR_looseCutsB","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
//  h_nMinus1_leadingLeptonTrackPt_looseCutsB=initHist(h_nMinus1_leadingLeptonTrackPt_looseCutsB,"nMinus1_leadingLeptonTrackPt_looseCutsB","n-1 Leading lepton track pt, final cuts",20,0,80);
//  h_nMinus1_subleadingLeptonTrackPt_looseCutsB=initHist(h_nMinus1_subleadingLeptonTrackPt_looseCutsB,"nMinus1_subleadingLeptonTrackPt_looseCutsB","n-1 Subleading lepton track pt, final cuts",20,0,80);
//  h_nMinus1_leadingSCEt_looseCutsB=initHist(h_nMinus1_leadingSCEt_looseCutsB,"nMinus1_leadingSCEt_looseCutsB", "n-1 leading SC Et, final cuts",100,0,150);
//  h_nMinus1_subleadingSCEt_looseCutsB=initHist(h_nMinus1_subleadingSCEt_looseCutsB,"nMinus1_subleadingSCEt_looseCutsB", "n-1 subleading SC Et, final cuts",100,0,150);
//  h_nMinus1_relIso_looseCutsB=initHist(h_nMinus1_relIso_looseCutsB,"nMinus1_relIso_looseCutsB", "n-1 lepton rel iso, final cuts", 20, 0, 0.2);
//  h_nMinus1_absIso_looseCutsB=initHist(h_nMinus1_absIso_looseCutsB,"nMinus1_absIso_looseCutsB", "n-1 lepton abs iso, final cuts", 80, 0, 20);
//  // Photon ID Cuts
//  h_photonR9_looseCutsB=initHist(h_photonR9_looseCutsB,"PhotonR9_looseCutsB", "Photon R9, final cuts", 20, 0, 1.1);
//  h_photonSigmaIetaIeta_barrel_looseCutsB=initHist(h_photonSigmaIetaIeta_barrel_looseCutsB,"PhotonSigmaIetaIeta_barrel_looseCutsB", "Photon SigmaIetaIeta, barrel, final cuts", 40, 0, 0.05);
//  h_photonSigmaIetaIeta_endcap_looseCutsB=initHist(h_photonSigmaIetaIeta_endcap_looseCutsB,"PhotonSigmaIetaIeta_endcap_looseCutsB", "Photon SigmaIetaIeta, endcap, final cuts", 40, 0, 0.05);
//  h_photonHadTowOverEm_looseCutsB=initHist(h_photonHadTowOverEm_looseCutsB,"PhotonHadTowOverEm_looseCutsB", "Photon HadTowOverEm, final cuts", 20, 0, 0.2);
//  h_photonHadronicOverEm_looseCutsB=initHist(h_photonHadronicOverEm_looseCutsB,"PhotonHadronicOverEm_looseCutsB", "Photon HadronicOverEm, final cuts", 20, 0, 0.2);
//
//  //
//  // LOOSE CUTS C
//  //
//  h_mass_looseCutsC=initHist(h_mass_looseCutsC,"Mass_looseCutsC","Dilepton mass, loose cuts",75,0,500);
//  h_mt_looseCutsC=initHist(h_mt_looseCutsC,"Mt_looseCutsC", "Dilepton Mt, final cuts", 75, 0, 500);
//  h_Lxy_looseCutsC=initHist(h_Lxy_looseCutsC,"Lxy_looseCutsC", "Lxy loose cuts",100,0,70);
//  h_nRecoPV_looseCutsC=initHist(h_nRecoPV_looseCutsC,"nRecoPV_looseCutsC", "Number reco PV, final cuts", 50, 0, 50);
//  h_leptonHSCEta_looseCutsC=initHist(h_leptonHSCEta_looseCutsC,"leptonHSCEta_looseCutsC", "Eta leading lepton, final cuts",60,-3,3);
//  h_leptonLSCEta_looseCutsC=initHist(h_leptonLSCEta_looseCutsC,"leptonLSCEta_looseCutsC", "Eta subleading lepton, final cuts",60,-3,3);
//  h_minLeptonD0Sig_looseCutsC=initHist(h_minLeptonD0Sig_looseCutsC,"minLeptonD0Sig_looseCutsC", "Min leptond0/sigma, final cuts",60,-20,10);
//  h_maxLeptonD0Sig_looseCutsC=initHist(h_maxLeptonD0Sig_looseCutsC,"maxLeptonD0Sig_looseCutsC", "Max leptond0/sigma, final cuts",60,-20,10);
//  h_leptonTrackingAlgo_looseCutsC=initHist(h_leptonTrackingAlgo_looseCutsC,"leptonTrackingAlgo_looseCutsC","Tracker reco algo",30,0,30);
//
//  // n-1 final cuts
//  h_nMinus1_oppositeCharge_looseCutsC=initHist(h_nMinus1_oppositeCharge_looseCutsC,"nMinus1_oppositeCharge_looseCutsC", "n-1 lepton opposite charges, final cuts",5,-2,2);
//  h_nMinus1_vertexChi2_looseCutsC=initHist(h_nMinus1_vertexChi2_looseCutsC,"nMinus1_vertexChi2_looseCutsC", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
//  h_nMinus1_deltaPhi_looseCutsC=initHist(h_nMinus1_deltaPhi_looseCutsC,"nMinus1_deltaPhi_looseCutsC", "n-1 Delta Phi, final cuts", 40, 0, 4);
//  h_nMinus1_cosine_looseCutsC=initHist(h_nMinus1_cosine_looseCutsC,"nMinus1_cosine_looseCutsC", "n-1 Cosine, final cuts",22,-1.1,1.1);
//  h_nMinus1_deltaR_looseCutsC=initHist(h_nMinus1_deltaR_looseCutsC,"nMinus1_deltaR_looseCutsC", "n-1 delta R, final cuts",10,0,0.5);
//  h_nMinus1_nHitsBeforeVertex_looseCutsC=initHist(h_nMinus1_nHitsBeforeVertex_looseCutsC,"nMinus1_nHitsBeforeVertex_looseCutsC", "n-1 N hits before vertex", 5, 0, 5);
//  h_nMinus1_nMissingHitsAfterVertex_looseCutsC=initHist(h_nMinus1_nMissingHitsAfterVertex_looseCutsC,"nMinus1_nMissingHitsAfterVertex_looseCutsC", "n-1 N missing hits after vertex", 20, 0, 20);
//  h_nMinus1_leptonCaloMatchDeltaR_looseCutsC=initHist(h_nMinus1_leptonCaloMatchDeltaR_looseCutsC,"nMinus1_leptonCaloMatchDeltaR_looseCutsC","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
//  h_nMinus1_leadingLeptonTrackPt_looseCutsC=initHist(h_nMinus1_leadingLeptonTrackPt_looseCutsC,"nMinus1_leadingLeptonTrackPt_looseCutsC","n-1 Leading lepton track pt, final cuts",20,0,80);
//  h_nMinus1_subleadingLeptonTrackPt_looseCutsC=initHist(h_nMinus1_subleadingLeptonTrackPt_looseCutsC,"nMinus1_subleadingLeptonTrackPt_looseCutsC","n-1 Subleading lepton track pt, final cuts",20,0,80);
//  h_nMinus1_leadingSCEt_looseCutsC=initHist(h_nMinus1_leadingSCEt_looseCutsC,"nMinus1_leadingSCEt_looseCutsC", "n-1 leading SC Et, final cuts",100,0,150);
//  h_nMinus1_subleadingSCEt_looseCutsC=initHist(h_nMinus1_subleadingSCEt_looseCutsC,"nMinus1_subleadingSCEt_looseCutsC", "n-1 subleading SC Et, final cuts",100,0,150);
//  h_nMinus1_relIso_looseCutsC=initHist(h_nMinus1_relIso_looseCutsC,"nMinus1_relIso_looseCutsC", "n-1 lepton rel iso, final cuts", 20, 0, 0.2);
//  h_nMinus1_absIso_looseCutsC=initHist(h_nMinus1_absIso_looseCutsC,"nMinus1_absIso_looseCutsC", "n-1 lepton abs iso, final cuts", 80, 0, 20);
//  // Photon ID Cuts
//  h_photonR9_looseCutsC=initHist(h_photonR9_looseCutsC,"PhotonR9_looseCutsC", "Photon R9, final cuts", 20, 0, 1.1);
//  h_photonSigmaIetaIeta_barrel_looseCutsC=initHist(h_photonSigmaIetaIeta_barrel_looseCutsC,"PhotonSigmaIetaIeta_barrel_looseCutsC", "Photon SigmaIetaIeta, barrel, final cuts", 40, 0, 0.05);
//  h_photonSigmaIetaIeta_endcap_looseCutsC=initHist(h_photonSigmaIetaIeta_endcap_looseCutsC,"PhotonSigmaIetaIeta_endcap_looseCutsC", "Photon SigmaIetaIeta, endcap, final cuts", 40, 0, 0.05);
//  h_photonHadTowOverEm_looseCutsC=initHist(h_photonHadTowOverEm_looseCutsC,"PhotonHadTowOverEm_looseCutsC", "Photon HadTowOverEm, final cuts", 20, 0, 0.2);
//  h_photonHadronicOverEm_looseCutsC=initHist(h_photonHadronicOverEm_looseCutsC,"PhotonHadronicOverEm_looseCutsC", "Photon HadronicOverEm, final cuts", 20, 0, 0.2);


  // Removed lifetime set of cuts
  h_mass_removedLifetimeCuts=initHist(h_mass_removedLifetimeCuts,"Mass_removedLifetimeCuts", "Dilepton mass, removed lifetime cuts", 75, 0, 500);
  h_mt_removedLifetimeCuts=initHist(h_mt_removedLifetimeCuts,"Mt_removedLifetimeCuts", "Dilepton Mt, removed lifetime cuts", 75, 0, 500);
  h_nRecoPV_removedLifetimeCuts=initHist(h_nRecoPV_removedLifetimeCuts,"nRecoPV", "Number reco PV", 50, 0, 50);
  h_nRecoPV_p5_removedLifetimeCuts=initHist(h_nRecoPV_p5_removedLifetimeCuts,"nRecoPV_p5", "Number reco PV +5", 50, 0, 50);
  h_nRecoPV_m5_removedLifetimeCuts=initHist(h_nRecoPV_m5_removedLifetimeCuts,"nRecoPV_m5", "Number reco PV -5", 50, 0, 50);
  h_leptonLPt_removedLifetimeCuts=initHist(h_leptonLPt_removedLifetimeCuts,"leptonLPt_removedLifetimeCuts", "Lepton L Pt, removed lifetime cuts",50,0,100);
  h_leptonHPt_removedLifetimeCuts=initHist(h_leptonHPt_removedLifetimeCuts,"leptonHPt_removedLifetimeCuts", "Lepton L Pt, removed lifetime cuts",50,0,100);
  h_leptonLEta_removedLifetimeCuts=initHist(h_leptonLEta_removedLifetimeCuts,"leptonLEta_removedLifetimeCuts", "Lepton L Eta, removed lifetime cuts",60,-3,3);
  h_leptonHEta_removedLifetimeCuts=initHist(h_leptonHEta_removedLifetimeCuts,"leptonHEta_removedLifetimeCuts", "Lepton L Eta, removed lifetime cuts",60,-3,3);
  h_leptonHSCEta_removedLifetimeCuts=initHist(h_leptonHSCEta_removedLifetimeCuts,"leptonHSCEta_removedLifetimeCuts", "Eta leading lepton, removed lifetime cuts",60,-3,3);
  h_leptonLSCEta_removedLifetimeCuts=initHist(h_leptonLSCEta_removedLifetimeCuts,"leptonLSCEta_removedLifetimeCuts", "Eta subleading lepton, removed lifetime cuts",60,-3,3);
  h_leptonLCaloMatchDeltaR_removedLifetimeCuts=initHist(h_leptonLCaloMatchDeltaR_removedLifetimeCuts,"leptonLCaloMatchDeltaR_removedLifetimeCuts","Lepton L calo match delta R, removed lifetime cuts",20,0,0.1);
  h_leptonHCaloMatchDeltaR_removedLifetimeCuts=initHist(h_leptonHCaloMatchDeltaR_removedLifetimeCuts,"leptonHCaloMatchDeltaR_removedLifetimeCuts","Lepton H calo match delta R, removed lifetime cuts",20,0,0.1);
  h_Lxy_removedLifetimeCuts=initHist(h_Lxy_removedLifetimeCuts,"Lxy_removedLifetimeCuts", "Lxy removed lifetime cuts",100,0,70);
  h_LxySig_removedLifetimeCuts=initHist(h_LxySig_removedLifetimeCuts,"LxySig_removedLifetimeCuts","Lxy/sigma removed lifetime cuts",60,-30,30);

  h_deltaPhi_removedLifetimeCollCuts=initHist(h_deltaPhi_removedLifetimeCollCuts,"deltaPhi_removedLifetimeCollCuts", "n-1 Delta Phi, removed lifetime cuts", 40, 0, 4);
  h_minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi L 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiL90_forFittingData_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiL90_forFittingData_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiL90_forFittingData_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi L 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts,"minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts", "Abs d0/sigma, bestCand_deltaPhi L 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_forFittingData_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_bestCand_deltaPhiL90_forFittingData_removedLifetimeCollCuts,"minLeptonAbsD0Sig_bestCand_deltaPhiL90_forFittingData_removedLifetimeCollCuts", "Abs d0/sigma, bestCand_deltaPhi L 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts,"minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_removedLifetimeCollCuts","Abs d0/sigma signed using deltaPhi GL 90",80, -20, 20 );
  h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts,"minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts","Abs d0/sigma signed using deltaPhi GL 90",80, -20, 20 );
  h_minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi G 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiG90_algo4_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiG90_algo4_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiG90_algo4_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi G 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiG90_algo5_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiG90_algo5_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiG90_algo5_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi G 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiG90_algo6_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiG90_algo6_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiG90_algo6_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi G 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiG90_algo7_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiG90_algo7_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiG90_algo7_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi G 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiG90_algo8_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiG90_algo8_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiG90_algo8_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi G 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiG90_algo9_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiG90_algo9_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiG90_algo9_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi G 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiG90_algo10_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiG90_algo10_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiG90_algo10_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi G 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiG90_noMissingHits_algo10_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiG90_noMissingHits_algo10_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiG90_noMissingHits_algo10_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi G 90, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts,"minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts", "Abs d0/sigma, bestCand_deltaPhi G 90, removed lifetime cuts", 40, 0, 20);


  h_deltaPhiSigned_removedLifetimeCollCuts=initHist(h_deltaPhiSigned_removedLifetimeCollCuts,"deltaPhiSigned_removedLifetimeCollCuts", "n-1 Delta Phi (Signed), removed lifetime cuts", 80, -4, 4);
  h_minLeptonAbsD0Sig_deltaPhiMinus_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiMinus_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiMinus_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi Minus, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_deltaPhiPlus_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_deltaPhiPlus_removedLifetimeCollCuts,"minLeptonAbsD0Sig_deltaPhiPlus_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi Plus, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_bestCand_deltaPhiMinus_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_bestCand_deltaPhiMinus_removedLifetimeCollCuts,"minLeptonAbsD0Sig_bestCand_deltaPhiMinus_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi Minus, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_bestCand_deltaPhiPlus_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_bestCand_deltaPhiPlus_removedLifetimeCollCuts,"minLeptonAbsD0Sig_bestCand_deltaPhiPlus_removedLifetimeCollCuts", "Abs d0/sigma, deltaPhi Plus, removed lifetime cuts", 40, 0, 20);
  h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts=initHist(h_minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts,"minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts","Abs d0/sigma signed using deltaPhi GL 90",80, -20, 20 );

  h_minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts=initHist(h_minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts,"minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts", "d0/sigma, sign using deltaPhi, removed lifetime cuts", 80, -20, 20);
  h_minLeptonD0Sig_signedWrtDeltaPhi_forFittingData_removedLifetimeCollCuts=initHist(h_minLeptonD0Sig_signedWrtDeltaPhi_forFittingData_removedLifetimeCollCuts,"minLeptonD0Sig_signedWrtDeltaPhi_forFittingData_removedLifetimeCollCuts", "d0/sigma, sign using deltaPhi, removed lifetime cuts", 80, -20, 20);
  h_minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts=initHist(h_minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts,"minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts", "d0/sigma, sign using deltaPhi Perp, removed lifetime cuts", 80, -20, 20);

 //
 // Removed lifetime collinearity
 //
  h_mass_removedLifetime_CollCuts=initHist(h_mass_removedLifetime_CollCuts,"Mass_removedLifetime_CollCuts","Dilepton mass,  cuts",75,0,500);
  h_mass_removedLifetime_controlCollCuts=initHist(h_mass_removedLifetime_controlCollCuts,"Mass_removedLifetime_controlCollCuts","Dilepton mass,  cuts",75,0,500);
  h_nRecoPV_removedLifetimeCollCuts=initHist(h_nRecoPV_removedLifetimeCollCuts,"nRecoPV_removedLifetimeCollCuts", "Number reco PV", 50, 0, 50);
  h_nRecoPV_p5_removedLifetimeCollCuts=initHist(h_nRecoPV_p5_removedLifetimeCollCuts,"nRecoPV_p5_removedLifetimeCollCuts", "Number reco PV +5", 50, 0, 50);
  h_nRecoPV_m5_removedLifetimeCollCuts=initHist(h_nRecoPV_m5_removedLifetimeCollCuts,"nRecoPV_m5_removedLifetimeCollCuts", "Number reco PV -5", 50, 0, 50);
  h_minLeptonAbsD0Sig_PVnorefit_controlCollCuts=initHist(h_minLeptonAbsD0Sig_PVnorefit_controlCollCuts,"minLeptonAbsD0Sig_PVnorefit_controlCollCuts","Minimum signed lepton D0 Significance before PV refit removed lifetime cuts, no smearing",40,0,20);
  h_nCandsPerEvent_deltaPhiG90_removedLifetimeCollCuts=initHist(h_nCandsPerEvent_deltaPhiG90_removedLifetimeCollCuts,"nCandsPerEvent_deltaPhiG90_removedLifetimeCollCuts", "Number of candidates found per event",5, -0.5, 4.5);
  h_nCandsPerEvent_deltaPhiL90_removedLifetimeCollCuts=initHist(h_nCandsPerEvent_deltaPhiL90_removedLifetimeCollCuts,"nCandsPerEvent_deltaPhiL90_removedLifetimeCollCuts", "Number of candidates found per event",5, -0.5, 4.5);

  h_nMinus1_relIsolationLeptonL_removedLifetimeCollCuts=initHist(h_nMinus1_relIsolationLeptonL_removedLifetimeCollCuts,"nMinus1_relIsolationLeptonL_removedLifetimeCollCuts", "Rel isolation cone, low pt lepton", 40, 0, 0.5 );
  h_nMinus1_relIsolationLeptonH_removedLifetimeCollCuts=initHist(h_nMinus1_relIsolationLeptonH_removedLifetimeCollCuts,"nMinus1_relIsolationLeptonH_removedLifetimeCollCuts", "Rel isolation cone, high pt lepton", 40, 0, 0.5 );

  h_nMinus1_trigDeltaR_removedLifetimeCollCuts=initHist(h_nMinus1_trigDeltaR_removedLifetimeCollCuts,"nMinus1_trigDeltaR_removedLifetimeCollCuts","TO-track deltaR",20,0,0.2);
  h_nMinus1_photonDeltaR_removedLifetimeCollCuts=initHist(h_nMinus1_photonDeltaR_removedLifetimeCollCuts,"nMinus1_photonDeltaR_removedLifetimeCollCuts","Photon-track deltaR",20,0,0.2);

  //
 // Final Collinearity Cuts
 //
 h_mass_finalCollCuts=initHist(h_mass_finalCollCuts,"Mass_finalCollCuts","Dilepton mass, loose cuts",75,0,500);
 h_mt_finalCollCuts=initHist(h_mt_finalCollCuts,"Mt_finalCollCuts", "Dilepton Mt, final cuts", 75, 0, 500);
 h_Lxy_finalCollCuts=initHist(h_Lxy_finalCollCuts,"Lxy_finalCollCuts", "Lxy loose cuts",100,0,70);
 h_nRecoPV_finalCollCuts=initHist(h_nRecoPV_finalCollCuts,"nRecoPV_finalCollCuts", "Number reco PV, final cuts", 50, 0, 50);
 h_leptonHSCEta_finalCollCuts=initHist(h_leptonHSCEta_finalCollCuts,"leptonHSCEta_finalCollCuts", "Eta leading lepton, final cuts",60,-3,3);
 h_leptonLSCEta_finalCollCuts=initHist(h_leptonLSCEta_finalCollCuts,"leptonLSCEta_finalCollCuts", "Eta subleading lepton, final cuts",60,-3,3);
 h_minLeptonD0Sig_finalCollCuts=initHist(h_minLeptonD0Sig_finalCollCuts,"minLeptonD0Sig_finalCollCuts", "Min leptond0/sigma, final cuts",60,-20,10);
 h_maxLeptonD0Sig_finalCollCuts=initHist(h_maxLeptonD0Sig_finalCollCuts,"maxLeptonD0Sig_finalCollCuts", "Max leptond0/sigma, final cuts",60,-20,10);
 h_leptonTrackingAlgo_finalCollCuts=initHist(h_leptonTrackingAlgo_finalCollCuts,"leptonTrackingAlgo_finalCollCuts","Tracker reco algo",30,0,30);
 h_ptOverE_finalCollCuts=initHist(h_ptOverE_finalCollCuts,"ptOverE_finalCollCuts","Track pt over ECAL E",20,0,2);
 h_ptMinusE_finalCollCuts=initHist(h_ptMinusE_finalCollCuts,"ptMinusE_finalCollCuts","Track pt over ECAL E",20,0,0.5);
 h_nCandsPerEvent_finalCollCuts=initHist(h_nCandsPerEvent_finalCollCuts,"nCandsPerEvent_finalCollCuts", "Number of candidates found per event",5, -0.5, 4.5);
 h_mass_bestCand_finalCollCuts=initHist(h_mass_bestCand_finalCollCuts,"Mass_bestCand_finalCollCuts","Dilepton mass, loose cuts",75,0,500);
 h_Lxy_bestCand_finalCollCuts=initHist(h_Lxy_bestCand_finalCollCuts,"Lxy_bestCand_finalCollCuts","Dilepton mass, loose cuts",100,0,70);

 // n-1 final cuts
 h_nMinus1_oppositeCharge_finalCollCuts=initHist(h_nMinus1_oppositeCharge_finalCollCuts,"nMinus1_oppositeCharge_finalCollCuts", "n-1 lepton opposite charges, final cuts",5,-2,2);
 h_nMinus1_vertexChi2_finalCollCuts=initHist(h_nMinus1_vertexChi2_finalCollCuts,"nMinus1_vertexChi2_finalCollCuts", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
 h_nMinus1_deltaPhi_finalCollCuts=initHist(h_nMinus1_deltaPhi_finalCollCuts,"nMinus1_deltaPhi_finalCollCuts", "n-1 Delta Phi, final cuts", 40, 0, 4);
 h_nMinus1_cosine_finalCollCuts=initHist(h_nMinus1_cosine_finalCollCuts,"nMinus1_cosine_finalCollCuts", "n-1 Cosine, final cuts",22,-1.1,1.1);
 h_nMinus1_deltaR_finalCollCuts=initHist(h_nMinus1_deltaR_finalCollCuts,"nMinus1_deltaR_finalCollCuts", "n-1 delta R, final cuts",10,0,0.5);
 h_nMinus1_nHitsBeforeVertex_finalCollCuts=initHist(h_nMinus1_nHitsBeforeVertex_finalCollCuts,"nMinus1_nHitsBeforeVertex_finalCollCuts", "n-1 N hits before vertex", 5, -0.5, 4.5);
 h_nMinus1_nMissingHitsAfterVertex_finalCollCuts=initHist(h_nMinus1_nMissingHitsAfterVertex_finalCollCuts,"nMinus1_nMissingHitsAfterVertex_finalCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_minMissingHitsAfterVertex_finalCollCuts=initHist(h_nMinus1_minMissingHitsAfterVertex_finalCollCuts,"nMinus1_minMissingHitsAfterVertex_finalCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_maxMissingHitsAfterVertex_finalCollCuts=initHist(h_nMinus1_maxMissingHitsAfterVertex_finalCollCuts,"nMinus1_maxMissingHitsAfterVertex_finalCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_leptonCaloMatchDeltaR_finalCollCuts=initHist(h_nMinus1_leptonCaloMatchDeltaR_finalCollCuts,"nMinus1_leptonCaloMatchDeltaR_finalCollCuts","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
 h_nMinus1_leadingLeptonTrackPt_finalCollCuts=initHist(h_nMinus1_leadingLeptonTrackPt_finalCollCuts,"nMinus1_leadingLeptonTrackPt_finalCollCuts","n-1 Leading lepton track pt, final cuts",20,0,80);
 h_nMinus1_subleadingLeptonTrackPt_finalCollCuts=initHist(h_nMinus1_subleadingLeptonTrackPt_finalCollCuts,"nMinus1_subleadingLeptonTrackPt_finalCollCuts","n-1 Subleading lepton track pt, final cuts",20,0,80);
 h_nMinus1_leadingSCEt_finalCollCuts=initHist(h_nMinus1_leadingSCEt_finalCollCuts,"nMinus1_leadingSCEt_finalCollCuts", "n-1 leading SC Et, final cuts",100,0,150);
 h_nMinus1_subleadingSCEt_finalCollCuts=initHist(h_nMinus1_subleadingSCEt_finalCollCuts,"nMinus1_subleadingSCEt_finalCollCuts", "n-1 subleading SC Et, final cuts",100,0,150);
 h_nMinus1_relIso_finalCollCuts=initHist(h_nMinus1_relIso_finalCollCuts,"nMinus1_relIso_finalCollCuts", "n-1 lepton rel iso, final cuts", 40, 0, 0.5);
 h_nMinus1_absIso_finalCollCuts=initHist(h_nMinus1_absIso_finalCollCuts,"nMinus1_absIso_finalCollCuts", "n-1 lepton abs iso, final cuts", 80, 0, 20);

 // Photon ID Cuts
 h_photonR9_finalCollCuts=initHist(h_photonR9_finalCollCuts,"PhotonR9_finalCollCuts", "Photon R9, final cuts", 20, 0, 1.1);
 h_photonSigmaIetaIeta_barrel_finalCollCuts=initHist(h_photonSigmaIetaIeta_barrel_finalCollCuts,"PhotonSigmaIetaIeta_barrel_finalCollCuts", "Photon SigmaIetaIeta, barrel, final cuts", 40, 0, 0.05);
 h_photonSigmaIetaIeta_endcap_finalCollCuts=initHist(h_photonSigmaIetaIeta_endcap_finalCollCuts,"PhotonSigmaIetaIeta_endcap_finalCollCuts", "Photon SigmaIetaIeta, endcap, final cuts", 40, 0, 0.05);
 h_photonHadTowOverEm_finalCollCuts=initHist(h_photonHadTowOverEm_finalCollCuts,"PhotonHadTowOverEm_finalCollCuts", "Photon HadTowOverEm, final cuts", 20, 0, 0.2);
 h_photonHadronicOverEm_finalCollCuts=initHist(h_photonHadronicOverEm_finalCollCuts,"PhotonHadronicOverEm_finalCollCuts", "Photon HadronicOverEm, final cuts", 20, 0, 0.2);

 // Isolation Plots
 h_nMinus1_relIsolationLeptonL_vsPU_finalCollCuts_genMatched = new TH2F(TString("nMinus1_relIsolationLeptonL_vsPU_finalCollCuts_genMatched")+nameSuffix, "Rel isolation cone vsPU, low pt lepton", 100, 0, 1.0, 50, 0, 50 );
 h_nMinus1_relIsolationLeptonH_vsPU_finalCollCuts_genMatched = new TH2F(TString("nMinus1_relIsolationLeptonH_vsPU_finalCollCuts_genMatched")+nameSuffix, "Rel isolation cone vsPU, high pt lepton", 100, 0, 1.0, 50, 0, 50 );
 h_nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_all = initHist(h_nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_all,"nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_all", "Number of reco PV, leptonL", 50, 0, 50 );
 h_nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_pass = initHist(h_nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_pass,"nMinus1_fracRelIsoLeptonL_vsPU_finalCollCuts_genMatched_pass", "Number of reco PV, leptonL, pass relIso", 50, 0, 50 );
 h_nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_all = initHist(h_nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_all,"nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_all", "Number of reco PV, leptonH", 50, 0, 50 );
 h_nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_pass = initHist(h_nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_pass,"nMinus1_fracRelIsoLeptonH_vsPU_finalCollCuts_genMatched_pass", "Number of reco PV, leptonH, pass relIso", 50, 0, 50 );


 //
 // Loose Collinearity Cuts
 //
 h_mass_looseCollCuts=initHist(h_mass_looseCollCuts,"Mass_looseCollCuts","Dilepton mass, loose cuts",75,0,500);
 h_mt_looseCollCuts=initHist(h_mt_looseCollCuts,"Mt_looseCollCuts", "Dilepton Mt, final cuts", 75, 0, 500);
 h_Lxy_looseCollCuts=initHist(h_Lxy_looseCollCuts,"Lxy_looseCollCuts", "Lxy loose cuts",100,0,70);
 h_nRecoPV_looseCollCuts=initHist(h_nRecoPV_looseCollCuts,"nRecoPV_looseCollCuts", "Number reco PV, final cuts", 50, 0, 50);
 h_leptonHSCEta_looseCollCuts=initHist(h_leptonHSCEta_looseCollCuts,"leptonHSCEta_looseCollCuts", "Eta leading lepton, final cuts",60,-3,3);
 h_leptonLSCEta_looseCollCuts=initHist(h_leptonLSCEta_looseCollCuts,"leptonLSCEta_looseCollCuts", "Eta subleading lepton, final cuts",60,-3,3);
 h_minLeptonD0Sig_looseCollCuts=initHist(h_minLeptonD0Sig_looseCollCuts,"minLeptonD0Sig_looseCollCuts", "Min leptond0/sigma, final cuts",60,-20,10);
 h_maxLeptonD0Sig_looseCollCuts=initHist(h_maxLeptonD0Sig_looseCollCuts,"maxLeptonD0Sig_looseCollCuts", "Max leptond0/sigma, final cuts",60,-20,10);
 h_leptonTrackingAlgo_looseCollCuts=initHist(h_leptonTrackingAlgo_looseCollCuts,"leptonTrackingAlgo_looseCollCuts","Tracker reco algo",30,0,30);
 h_ptOverE_looseCollCuts=initHist(h_ptOverE_looseCollCuts,"ptOverE_looseCollCuts","Track pt over ECAL E",20,0,2);
 h_ptMinusE_looseCollCuts=initHist(h_ptMinusE_looseCollCuts,"ptMinusE_looseCollCuts","Track pt over ECAL E",20,0,0.5);
 h_nCandsPerEvent_looseCollCuts=initHist(h_nCandsPerEvent_looseCollCuts,"nCandsPerEvent_looseCollCuts", "Number of candidates found per event",5, -0.5, 4.5);

 // n-1 final cuts
 h_nMinus1_oppositeCharge_looseCollCuts=initHist(h_nMinus1_oppositeCharge_looseCollCuts,"nMinus1_oppositeCharge_looseCollCuts", "n-1 lepton opposite charges, final cuts",5,-2,2);
 h_nMinus1_vertexChi2_looseCollCuts=initHist(h_nMinus1_vertexChi2_looseCollCuts,"nMinus1_vertexChi2_looseCollCuts", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
 h_nMinus1_deltaPhi_looseCollCuts=initHist(h_nMinus1_deltaPhi_looseCollCuts,"nMinus1_deltaPhi_looseCollCuts", "n-1 Delta Phi, final cuts", 40, 0, 4);
 h_nMinus1_cosine_looseCollCuts=initHist(h_nMinus1_cosine_looseCollCuts,"nMinus1_cosine_looseCollCuts", "n-1 Cosine, final cuts",22,-1.1,1.1);
 h_nMinus1_deltaR_looseCollCuts=initHist(h_nMinus1_deltaR_looseCollCuts,"nMinus1_deltaR_looseCollCuts", "n-1 delta R, final cuts",10,0,0.5);
 h_nMinus1_nHitsBeforeVertex_looseCollCuts=initHist(h_nMinus1_nHitsBeforeVertex_looseCollCuts,"nMinus1_nHitsBeforeVertex_looseCollCuts", "n-1 N hits before vertex", 5, -0.5, 4.5);
 h_nMinus1_nMissingHitsAfterVertex_looseCollCuts=initHist(h_nMinus1_nMissingHitsAfterVertex_looseCollCuts,"nMinus1_nMissingHitsAfterVertex_looseCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_minMissingHitsAfterVertex_looseCollCuts=initHist(h_nMinus1_minMissingHitsAfterVertex_looseCollCuts,"nMinus1_minMissingHitsAfterVertex_looseCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_maxMissingHitsAfterVertex_looseCollCuts=initHist(h_nMinus1_maxMissingHitsAfterVertex_looseCollCuts,"nMinus1_maxMissingHitsAfterVertex_looseCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_leptonCaloMatchDeltaR_looseCollCuts=initHist(h_nMinus1_leptonCaloMatchDeltaR_looseCollCuts,"nMinus1_leptonCaloMatchDeltaR_looseCollCuts","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
 h_nMinus1_leadingLeptonTrackPt_looseCollCuts=initHist(h_nMinus1_leadingLeptonTrackPt_looseCollCuts,"nMinus1_leadingLeptonTrackPt_looseCollCuts","n-1 Leading lepton track pt, final cuts",20,0,80);
 h_nMinus1_subleadingLeptonTrackPt_looseCollCuts=initHist(h_nMinus1_subleadingLeptonTrackPt_looseCollCuts,"nMinus1_subleadingLeptonTrackPt_looseCollCuts","n-1 Subleading lepton track pt, final cuts",20,0,80);
 h_nMinus1_leadingSCEt_looseCollCuts=initHist(h_nMinus1_leadingSCEt_looseCollCuts,"nMinus1_leadingSCEt_looseCollCuts", "n-1 leading SC Et, final cuts",100,0,150);
 h_nMinus1_subleadingSCEt_looseCollCuts=initHist(h_nMinus1_subleadingSCEt_looseCollCuts,"nMinus1_subleadingSCEt_looseCollCuts", "n-1 subleading SC Et, final cuts",100,0,150);
 h_nMinus1_relIso_looseCollCuts=initHist(h_nMinus1_relIso_looseCollCuts,"nMinus1_relIso_looseCollCuts", "n-1 lepton rel iso, final cuts", 40, 0, 0.5);
 h_nMinus1_absIso_looseCollCuts=initHist(h_nMinus1_absIso_looseCollCuts,"nMinus1_absIso_looseCollCuts", "n-1 lepton abs iso, final cuts", 80, 0, 20);
 // Photon ID Cuts
 h_photonR9_looseCollCuts=initHist(h_photonR9_looseCollCuts,"PhotonR9_looseCollCuts", "Photon R9, final cuts", 20, 0, 1.1);
 h_photonSigmaIetaIeta_barrel_looseCollCuts=initHist(h_photonSigmaIetaIeta_barrel_looseCollCuts,"PhotonSigmaIetaIeta_barrel_looseCollCuts", "Photon SigmaIetaIeta, barrel, final cuts", 40, 0, 0.05);
 h_photonSigmaIetaIeta_endcap_looseCollCuts=initHist(h_photonSigmaIetaIeta_endcap_looseCollCuts,"PhotonSigmaIetaIeta_endcap_looseCollCuts", "Photon SigmaIetaIeta, endcap, final cuts", 40, 0, 0.05);
 h_photonHadTowOverEm_looseCollCuts=initHist(h_photonHadTowOverEm_looseCollCuts,"PhotonHadTowOverEm_looseCollCuts", "Photon HadTowOverEm, final cuts", 20, 0, 0.2);
 h_photonHadronicOverEm_looseCollCuts=initHist(h_photonHadronicOverEm_looseCollCuts,"PhotonHadronicOverEm_looseCollCuts", "Photon HadronicOverEm, final cuts", 20, 0, 0.2);

 //
 // Loose Control Collinearity Cuts
 //
 h_mass_looseControlCollCuts=initHist(h_mass_looseControlCollCuts,"Mass_looseControlCollCuts","Dilepton mass, loose cuts",75,0,500);
 h_mt_looseControlCollCuts=initHist(h_mt_looseControlCollCuts,"Mt_looseControlCollCuts", "Dilepton Mt, final cuts", 75, 0, 500);
 h_Lxy_looseControlCollCuts=initHist(h_Lxy_looseControlCollCuts,"Lxy_looseControlCollCuts", "Lxy loose cuts",100,0,70);
 h_nRecoPV_looseControlCollCuts=initHist(h_nRecoPV_looseControlCollCuts,"nRecoPV_looseControlCollCuts", "Number reco PV, final cuts", 50, 0, 50);
 h_leptonHSCEta_looseControlCollCuts=initHist(h_leptonHSCEta_looseControlCollCuts,"leptonHSCEta_looseControlCollCuts", "Eta leading lepton, final cuts",60,-3,3);
 h_leptonLSCEta_looseControlCollCuts=initHist(h_leptonLSCEta_looseControlCollCuts,"leptonLSCEta_looseControlCollCuts", "Eta subleading lepton, final cuts",60,-3,3);
 h_minLeptonD0Sig_looseControlCollCuts=initHist(h_minLeptonD0Sig_looseControlCollCuts,"minLeptonD0Sig_looseControlCollCuts", "Min leptond0/sigma, final cuts",60,-20,10);
 h_maxLeptonD0Sig_looseControlCollCuts=initHist(h_maxLeptonD0Sig_looseControlCollCuts,"maxLeptonD0Sig_looseControlCollCuts", "Max leptond0/sigma, final cuts",60,-20,10);
 h_leptonTrackingAlgo_looseControlCollCuts=initHist(h_leptonTrackingAlgo_looseControlCollCuts,"leptonTrackingAlgo_looseControlCollCuts","Tracker reco algo",30,0,30);
 h_ptOverE_looseControlCollCuts=initHist(h_ptOverE_looseCollCuts,"ptOverE_looseControlCollCuts","Track pt over ECAL E",20,0,2);
 h_ptMinusE_looseControlCollCuts=initHist(h_ptMinusE_looseControlCollCuts,"ptMinusE_looseControlCollCuts","Track pt over ECAL E",20,0,0.5);
 h_nCandsPerEvent_looseControlCollCuts=initHist(h_nCandsPerEvent_looseControlCollCuts,"nCandsPerEvent_looseControlCollCuts", "Number of candidates found per event",5, -0.5, 4.5);

 // n-1 loose control cuts
 h_nMinus1_oppositeCharge_looseControlCollCuts=initHist(h_nMinus1_oppositeCharge_looseControlCollCuts,"nMinus1_oppositeCharge_looseControlCollCuts", "n-1 lepton opposite charges, final cuts",5,-2,2);
 h_nMinus1_vertexChi2_looseControlCollCuts=initHist(h_nMinus1_vertexChi2_looseControlCollCuts,"nMinus1_vertexChi2_looseControlCollCuts", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
 h_nMinus1_deltaPhi_looseControlCollCuts=initHist(h_nMinus1_deltaPhi_looseControlCollCuts,"nMinus1_deltaPhi_looseControlCollCuts", "n-1 Delta Phi, final cuts", 40, 0, 4);
 h_nMinus1_cosine_looseControlCollCuts=initHist(h_nMinus1_cosine_looseControlCollCuts,"nMinus1_cosine_looseControlCollCuts", "n-1 Cosine, final cuts",22,-1.1,1.1);
 h_nMinus1_deltaR_looseControlCollCuts=initHist(h_nMinus1_deltaR_looseControlCollCuts,"nMinus1_deltaR_looseControlCollCuts", "n-1 delta R, final cuts",10,0,0.5);
 h_nMinus1_nHitsBeforeVertex_looseControlCollCuts=initHist(h_nMinus1_nHitsBeforeVertex_looseControlCollCuts,"nMinus1_nHitsBeforeVertex_looseControlCollCuts", "n-1 N hits before vertex", 5, -0.5, 4.5);
 h_nMinus1_nMissingHitsAfterVertex_looseControlCollCuts=initHist(h_nMinus1_nMissingHitsAfterVertex_looseControlCollCuts,"nMinus1_nMissingHitsAfterVertex_looseControlCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_minMissingHitsAfterVertex_looseControlCollCuts=initHist(h_nMinus1_minMissingHitsAfterVertex_looseControlCollCuts,"nMinus1_minMissingHitsAfterVertex_looseControlCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_maxMissingHitsAfterVertex_looseControlCollCuts=initHist(h_nMinus1_maxMissingHitsAfterVertex_looseControlCollCuts,"nMinus1_maxMissingHitsAfterVertex_looseControlCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_leptonCaloMatchDeltaR_looseControlCollCuts=initHist(h_nMinus1_leptonCaloMatchDeltaR_looseControlCollCuts,"nMinus1_leptonCaloMatchDeltaR_looseControlCollCuts","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
 h_nMinus1_leadingLeptonTrackPt_looseControlCollCuts=initHist(h_nMinus1_leadingLeptonTrackPt_looseControlCollCuts,"nMinus1_leadingLeptonTrackPt_looseControlCollCuts","n-1 Leading lepton track pt, final cuts",20,0,80);
 h_nMinus1_subleadingLeptonTrackPt_looseControlCollCuts=initHist(h_nMinus1_subleadingLeptonTrackPt_looseControlCollCuts,"nMinus1_subleadingLeptonTrackPt_looseControlCollCuts","n-1 Subleading lepton track pt, final cuts",20,0,80);
 h_nMinus1_leadingSCEt_looseControlCollCuts=initHist(h_nMinus1_leadingSCEt_looseControlCollCuts,"nMinus1_leadingSCEt_looseControlCollCuts", "n-1 leading SC Et, final cuts",100,0,150);
 h_nMinus1_subleadingSCEt_looseControlCollCuts=initHist(h_nMinus1_subleadingSCEt_looseControlCollCuts,"nMinus1_subleadingSCEt_looseControlCollCuts", "n-1 subleading SC Et, final cuts",100,0,150);
 h_nMinus1_relIso_looseControlCollCuts=initHist(h_nMinus1_relIso_looseControlCollCuts,"nMinus1_relIso_looseControlCollCuts", "n-1 lepton rel iso, final cuts", 40, 0, 0.5);
 h_nMinus1_relIso3_looseControlCollCuts=initHist(h_nMinus1_relIso3_looseControlCollCuts,"nMinus1_relIso3_looseControlCollCuts", "n-1 lepton rel iso, final cuts", 40, 0, 0.5);
 h_nMinus1_relIso4_looseControlCollCuts=initHist(h_nMinus1_relIso4_looseControlCollCuts,"nMinus1_relIso4_looseControlCollCuts", "n-1 lepton rel iso, final cuts", 40, 0, 0.5);
 h_nMinus1_relIso5_looseControlCollCuts=initHist(h_nMinus1_relIso5_looseControlCollCuts,"nMinus1_relIso5_looseControlCollCuts", "n-1 lepton rel iso, final cuts", 40, 0, 0.5);

 h_nMinus1_absIso_looseControlCollCuts=initHist(h_nMinus1_absIso_looseControlCollCuts,"nMinus1_absIso_looseControlCollCuts", "n-1 lepton abs iso, final cuts", 80, 0, 20);
 // Photon ID Cuts
 h_photonR9_looseControlCollCuts=initHist(h_photonR9_looseControlCollCuts,"PhotonR9_looseControlCollCuts", "Photon R9, final cuts", 20, 0, 1.1);
 h_photonSigmaIetaIeta_barrel_looseControlCollCuts=initHist(h_photonSigmaIetaIeta_barrel_looseControlCollCuts,"PhotonSigmaIetaIeta_barrel_looseControlCollCuts", "Photon SigmaIetaIeta, barrel, final cuts", 40, 0, 0.05);
 h_photonSigmaIetaIeta_endcap_looseControlCollCuts=initHist(h_photonSigmaIetaIeta_endcap_looseControlCollCuts,"PhotonSigmaIetaIeta_endcap_looseControlCollCuts", "Photon SigmaIetaIeta, endcap, final cuts", 40, 0, 0.05);
 h_photonHadTowOverEm_looseControlCollCuts=initHist(h_photonHadTowOverEm_looseControlCollCuts,"PhotonHadTowOverEm_looseControlCollCuts", "Photon HadTowOverEm, final cuts", 20, 0, 0.2);
 h_photonHadronicOverEm_looseControlCollCuts=initHist(h_photonHadronicOverEm_looseControlCollCuts,"PhotonHadronicOverEm_looseControlCollCuts", "Photon HadronicOverEm, final cuts", 20, 0, 0.2);

 //
 //  Control Collinearity Cuts
 //
 h_mass_controlCollCuts=initHist(h_mass_controlCollCuts,"Mass_controlCollCuts","Dilepton mass,  cuts",75,0,500);
 h_mt_controlCollCuts=initHist(h_mt_controlCollCuts,"Mt_controlCollCuts", "Dilepton Mt, final cuts", 75, 0, 500);
 h_Lxy_controlCollCuts=initHist(h_Lxy_controlCollCuts,"Lxy_controlCollCuts", "Lxy  cuts",100,0,70);
 h_nRecoPV_controlCollCuts=initHist(h_nRecoPV_controlCollCuts,"nRecoPV_controlCollCuts", "Number reco PV, final cuts", 50, 0, 50);
 h_leptonHSCEta_controlCollCuts=initHist(h_leptonHSCEta_controlCollCuts,"leptonHSCEta_controlCollCuts", "Eta leading lepton, final cuts",60,-3,3);
 h_leptonLSCEta_controlCollCuts=initHist(h_leptonLSCEta_controlCollCuts,"leptonLSCEta_controlCollCuts", "Eta subleading lepton, final cuts",60,-3,3);
 h_minLeptonD0Sig_controlCollCuts=initHist(h_minLeptonD0Sig_controlCollCuts,"minLeptonD0Sig_controlCollCuts", "Min leptond0/sigma, final cuts",60,-20,10);
 h_maxLeptonD0Sig_controlCollCuts=initHist(h_maxLeptonD0Sig_controlCollCuts,"maxLeptonD0Sig_controlCollCuts", "Max leptond0/sigma, final cuts",60,-20,10);
 h_leptonTrackingAlgo_controlCollCuts=initHist(h_leptonTrackingAlgo_controlCollCuts,"leptonTrackingAlgo_controlCollCuts","Tracker reco algo",30,0,30);
 h_ptOverE_controlCollCuts=initHist(h_ptOverE_controlCollCuts,"ptOverE_controlCollCuts","Track pt over ECAL E",20,0,2);
 h_ptMinusE_controlCollCuts=initHist(h_ptMinusE_controlCollCuts,"ptMinusE_controlCollCuts","Track pt over ECAL E",20,0,0.5);
 h_nCandsPerEvent_controlCollCuts=initHist(h_nCandsPerEvent_controlCollCuts,"nCandsPerEvent_controlCollCuts", "Number of candidates found per event",5, -0.5, 4.5);

 // n-1  control cuts
 h_nMinus1_oppositeCharge_controlCollCuts=initHist(h_nMinus1_oppositeCharge_controlCollCuts,"nMinus1_oppositeCharge_controlCollCuts", "n-1 lepton opposite charges, final cuts",5,-2,2);
 h_nMinus1_vertexChi2_controlCollCuts=initHist(h_nMinus1_vertexChi2_controlCollCuts,"nMinus1_vertexChi2_controlCollCuts", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
 h_nMinus1_deltaPhi_controlCollCuts=initHist(h_nMinus1_deltaPhi_controlCollCuts,"nMinus1_deltaPhi_controlCollCuts", "n-1 Delta Phi, final cuts", 40, 0, 4);
 h_nMinus1_cosine_controlCollCuts=initHist(h_nMinus1_cosine_controlCollCuts,"nMinus1_cosine_controlCollCuts", "n-1 Cosine, final cuts",22,-1.1,1.1);
 h_nMinus1_deltaR_controlCollCuts=initHist(h_nMinus1_deltaR_controlCollCuts,"nMinus1_deltaR_controlCollCuts", "n-1 delta R, final cuts",10,0,0.5);
 h_nMinus1_nHitsBeforeVertex_controlCollCuts=initHist(h_nMinus1_nHitsBeforeVertex_controlCollCuts,"nMinus1_nHitsBeforeVertex_controlCollCuts", "n-1 N hits before vertex", 5, -0.5, 4.5);
 h_nMinus1_nMissingHitsAfterVertex_controlCollCuts=initHist(h_nMinus1_nMissingHitsAfterVertex_controlCollCuts,"nMinus1_nMissingHitsAfterVertex_controlCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_minMissingHitsAfterVertex_controlCollCuts=initHist(h_nMinus1_minMissingHitsAfterVertex_controlCollCuts,"nMinus1_minMissingHitsAfterVertex_controlCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_maxMissingHitsAfterVertex_controlCollCuts=initHist(h_nMinus1_maxMissingHitsAfterVertex_controlCollCuts,"nMinus1_maxMissingHitsAfterVertex_controlCollCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
 h_nMinus1_leptonCaloMatchDeltaR_controlCollCuts=initHist(h_nMinus1_leptonCaloMatchDeltaR_controlCollCuts,"nMinus1_leptonCaloMatchDeltaR_controlCollCuts","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
 h_nMinus1_leadingLeptonTrackPt_controlCollCuts=initHist(h_nMinus1_leadingLeptonTrackPt_controlCollCuts,"nMinus1_leadingLeptonTrackPt_controlCollCuts","n-1 Leading lepton track pt, final cuts",20,0,80);
 h_nMinus1_subleadingLeptonTrackPt_controlCollCuts=initHist(h_nMinus1_subleadingLeptonTrackPt_controlCollCuts,"nMinus1_subleadingLeptonTrackPt_controlCollCuts","n-1 Subleading lepton track pt, final cuts",20,0,80);
 h_nMinus1_leadingSCEt_controlCollCuts=initHist(h_nMinus1_leadingSCEt_controlCollCuts,"nMinus1_leadingSCEt_controlCollCuts", "n-1 leading SC Et, final cuts",100,0,150);
 h_nMinus1_subleadingSCEt_controlCollCuts=initHist(h_nMinus1_subleadingSCEt_controlCollCuts,"nMinus1_subleadingSCEt_controlCollCuts", "n-1 subleading SC Et, final cuts",100,0,150);
 h_nMinus1_relIso_controlCollCuts=initHist(h_nMinus1_relIso_controlCollCuts,"nMinus1_relIso_controlCollCuts", "n-1 lepton rel iso, final cuts", 40, 0, 0.5);
 h_nMinus1_absIso_controlCollCuts=initHist(h_nMinus1_absIso_controlCollCuts,"nMinus1_absIso_controlCollCuts", "n-1 lepton abs iso, final cuts", 80, 0, 20);
 // Photon ID Cuts
 h_photonR9_controlCollCuts=initHist(h_photonR9_controlCollCuts,"PhotonR9_controlCollCuts", "Photon R9, final cuts", 20, 0, 1.1);
 h_photonSigmaIetaIeta_barrel_controlCollCuts=initHist(h_photonSigmaIetaIeta_barrel_controlCollCuts,"PhotonSigmaIetaIeta_barrel_controlCollCuts", "Photon SigmaIetaIeta, barrel, final cuts", 40, 0, 0.05);
 h_photonSigmaIetaIeta_endcap_controlCollCuts=initHist(h_photonSigmaIetaIeta_endcap_controlCollCuts,"PhotonSigmaIetaIeta_endcap_controlCollCuts", "Photon SigmaIetaIeta, endcap, final cuts", 40, 0, 0.05);
 h_photonHadTowOverEm_controlCollCuts=initHist(h_photonHadTowOverEm_controlCollCuts,"PhotonHadTowOverEm_controlCollCuts", "Photon HadTowOverEm, final cuts", 20, 0, 0.2);
 h_photonHadronicOverEm_controlCollCuts=initHist(h_photonHadronicOverEm_controlCollCuts,"PhotonHadronicOverEm_controlCollCuts", "Photon HadronicOverEm, final cuts", 20, 0, 0.2);



  h_minLeptonD0Sig_removedLifetimeCuts=initHist(h_minLeptonD0Sig_removedLifetimeCuts,"minLeptonD0Sig_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, no smearing",80,-20,20);
  h_minLeptonD0Sig_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, no smearing",80,-20,20);

  h_minLeptonD0Sig_signedWrtDileptonPerp_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signedWrtDileptonPerp_removedLifetimeCuts,"minLeptonD0Sig_signedWrtDileptonPerp_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, signed wrt vector perpendicular to dilepton",80,-20,20);

  h_minLeptonD0Sig_removedLifetimeCuts_badRegion=initHist(h_minLeptonD0Sig_removedLifetimeCuts_badRegion,"minLeptonD0Sig_removedLifetimeCuts_badRegion","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_badRegion_corrected=initHist(h_minLeptonD0Sig_removedLifetimeCuts_badRegion_corrected,"minLeptonD0Sig_removedLifetimeCuts_badRegion_corrected","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region after correction",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2=initHist(h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2,"minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2_corrected=initHist(h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2_corrected,"minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2_corrected","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region after correction",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2=initHist(h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2,"minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2_corrected=initHist(h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2_corrected,"minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2_corrected","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region after correction",80,-20,20);

  h_minLeptonD0Sig_removedLifetimeCuts_allRegion=initHist(h_minLeptonD0Sig_removedLifetimeCuts_allRegion,"minLeptonD0Sig_removedLifetimeCuts_allRegion","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_allRegion_corrected=initHist(h_minLeptonD0Sig_removedLifetimeCuts_allRegion_corrected,"minLeptonD0Sig_removedLifetimeCuts_allRegion_corrected","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region after correction",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2=initHist(h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2,"minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2_corrected=initHist(h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2_corrected,"minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2_corrected","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region after correction",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2=initHist(h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2,"minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region",80,-20,20);
  h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2_corrected=initHist(h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2_corrected,"minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2_corrected","Minimum signed lepton D0 Significance removed lifetime cuts in badly aligned region after correction",80,-20,20);

  h_deltaPhi_removedLifetimeCuts_allRegion=initHist(h_deltaPhi_removedLifetimeCuts_allRegion,"deltaPhi_removedLifetimeCuts_allRegion", "Delta phi used for corrections, all regions", 100, -3.5, 3.5);

  h_deltaPhi_dileptonLepton_removedLifetimeCuts_allRegion=initHist(h_deltaPhi_dileptonLepton_removedLifetimeCuts_allRegion,"deltaPhi_dileptonLepton_removedLifetimeCuts_allRegion", "Delta phi used for corrections, all regions", 100, -3.5, 3.5);
  h_deltaPhi_dileptonPerpLepton_removedLifetimeCuts_allRegion=initHist(h_deltaPhi_dileptonPerpLepton_removedLifetimeCuts_allRegion,"deltaPhi_dileptonPerpLepton_removedLifetimeCuts_allRegion", "Delta phi used for corrections, all regions", 100, -3.5, 3.5);

  h_deltaPhi_removedLifetimeCuts_badRegion=initHist(h_deltaPhi_removedLifetimeCuts_badRegion,"deltaPhi_removedLifetimeCuts_badRegion", "Delta phi used for corrections, all regions", 100, -3.5, 3.5);

  h_bothLeptonsD0Sig_d0Corrected_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_d0Corrected_removedLifetimeCuts,"bothLeptonsD0Sig_d0Corrected_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_d0Corrected_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0Corrected_removedLifetimeCuts,"minLeptonD0Sig_d0Corrected_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_d0Corrected_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0Corrected_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_d0Corrected_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);

  h_bothLeptonsD0Sig_d0CorrectedRunDependent_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_d0CorrectedRunDependent_removedLifetimeCuts,"bothLeptonsD0Sig_d0CorrectedRunDependent_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependent",80,-20,20);
  h_minLeptonD0Sig_d0CorrectedRunDependent_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0CorrectedRunDependent_removedLifetimeCuts,"minLeptonD0Sig_d0CorrectedRunDependent_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependent",80,-20,20);
  h_minLeptonD0Sig_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependent",80,-20,20);

  h_bothLeptonsD0Sig_d0CorrectedPixel_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_d0CorrectedPixel_removedLifetimeCuts,"bothLeptonsD0Sig_d0CorrectedPixel_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_d0CorrectedPixel_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0CorrectedPixel_removedLifetimeCuts,"minLeptonD0Sig_d0CorrectedPixel_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_d0CorrectedPixel_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0CorrectedPixel_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_d0CorrectedPixel_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);

  h_bothLeptonsD0Sig_d0CorrectedIP_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_d0CorrectedIP_removedLifetimeCuts,"bothLeptonsD0Sig_d0CorrectedIP_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_d0CorrectedIP_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0CorrectedIP_removedLifetimeCuts,"minLeptonD0Sig_d0CorrectedIP_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_d0CorrectedIP_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0CorrectedIP_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_d0CorrectedIP_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);

  h_bothLeptonsD0Sig_NoCorrections_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_NoCorrections_removedLifetimeCuts,"bothLeptonsD0Sig_NoCorrections_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_NoCorrections_removedLifetimeCuts=initHist(h_minLeptonD0Sig_NoCorrections_removedLifetimeCuts,"minLeptonD0Sig_NoCorrections_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);

  h_bothLeptonsD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts,"bothLeptonsD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependentNoVertex",80,-20,20);
  h_minLeptonD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts,"minLeptonD0Sig_d0CorrectedRunDependentNoVertex_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependentNoVertex",80,-20,20);
  h_minLeptonD0Sig_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependentNoVertex",80,-20,20);

  h_bothLeptonsD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts,"bothLeptonsD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 corrected",80,-20,20);

  h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts,"bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependent",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependent",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependent",80,-20,20);

  h_bothLeptonsD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts,"bothLeptonsD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedNoCorrections",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedNoCorrections",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedNoCorrections",80,-20,20);

  h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts,"bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedCut",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedCut",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedCut_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedCut",80,-20,20);

  h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts=initHist(h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts,"bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependentNoVertex",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependentNoVertex",80,-20,20);
  h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, d0 correctedRunDependentNoVertex",80,-20,20);

  h_minLeptonD0Sig_oppSign_removedLifetimeCuts=initHist(h_minLeptonD0Sig_oppSign_removedLifetimeCuts,"minLeptonD0Sig_oppSign_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, opposite sign d0",60,-20,10);
  h_minLeptonD0Sig_oppSign_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_oppSign_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_oppSign_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, opposite sign d0",60,-20,10);

  h_minLeptonD0Sig_algo4_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo4_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_algo4_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 4",60,-20,10);
  h_minLeptonD0Sig_algo5_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo5_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_algo5_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 5",60,-20,10);
  h_minLeptonD0Sig_algo6_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo6_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_algo6_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 6",60,-20,10);
  h_minLeptonD0Sig_algo7_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo7_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_algo7_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 7",60,-20,10);
  h_minLeptonD0Sig_algo8_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo8_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_algo8_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 8",60,-20,10);
  h_minLeptonD0Sig_algo9_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo9_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_algo9_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 9",60,-20,10);
  h_minLeptonD0Sig_algo10_forFittingData_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo10_forFittingData_removedLifetimeCuts,"minLeptonD0Sig_algo10_forFittingData_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 10",60,-20,10);

  h_minLeptonD0Sig_algo4_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo4_removedLifetimeCuts,"minLeptonD0Sig_algo4_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 4",60,-20,10);
  h_minLeptonD0Sig_algo5_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo5_removedLifetimeCuts,"minLeptonD0Sig_algo5_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 5",60,-20,10);
  h_minLeptonD0Sig_algo6_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo6_removedLifetimeCuts,"minLeptonD0Sig_algo6_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 6",60,-20,10);
  h_minLeptonD0Sig_algo7_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo7_removedLifetimeCuts,"minLeptonD0Sig_algo7_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 7",60,-20,10);
  h_minLeptonD0Sig_algo8_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo8_removedLifetimeCuts,"minLeptonD0Sig_algo8_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 8",60,-20,10);
  h_minLeptonD0Sig_algo9_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo9_removedLifetimeCuts,"minLeptonD0Sig_algo9_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 9",60,-20,10);
  h_minLeptonD0Sig_algo10_removedLifetimeCuts=initHist(h_minLeptonD0Sig_algo10_removedLifetimeCuts,"minLeptonD0Sig_algo10_removedLifetimeCuts","Minimum signed lepton D0 Significance removed lifetime cuts, algo 10",60,-20,10);

  h_leptonD0BS_algo4_forFittingData_removedLifetimeCuts=initHist(h_leptonD0BS_algo4_forFittingData_removedLifetimeCuts,"leptonD0BS_algo4_forFittingData_removedLifetimeCuts","Lepton D0 Significance removed lifetime cuts, algo 4",60,0,0.1);

  h_maxLeptonD0Sig_removedLifetimeCuts=initHist(h_maxLeptonD0Sig_removedLifetimeCuts,"maxLeptonD0Sig_removedLifetimeCuts","Maximum signed lepton D0 Significance removed lifetime cuts, no smearing",60,-20,20);

  h_minLeptonD0Sig_PVnorefit_removedLifetimeCuts=initHist(h_minLeptonD0Sig_PVnorefit_removedLifetimeCuts,"minLeptonD0Sig_PVnorefit_removedLifetimeCuts","Minimum signed lepton D0 Significance before PV refit removed lifetime cuts, no smearing",60,-20,10);

  h_leptonD0_removedLifetimeCuts=initHist(h_leptonD0_removedLifetimeCuts,"leptonD0_removedLifetimeCuts","Signed lepton D0 removed lifetime cuts, no smearing",80,-0.05,0.05);
  h_leptonSig_removedLifetimeCuts=initHist(h_leptonSig_removedLifetimeCuts,"leptonSig_removedLifetimeCuts","Lepton sigma(D0) removed lifetime cuts, no smearing",40,0,0.01);

  h_minLeptonD0SigBL_removedLifetimeCuts=initHist(h_minLeptonD0SigBL_removedLifetimeCuts,"minLeptonD0SigBL_removedLifetimeCuts","Minimum signed lepton D0 Significance wrt BL removed lifetime cuts, no smearing",60,-20,10);

  h_l_vs_h_leptonD0Sig_removedLifetimeCuts = new TH2F(TString("l_vs_h_leptonD0Sig_removedLifetimeCuts")+nameSuffix, "L vs H lepton D0 Significance", 60, 0, 10, 60, 0, 10 );

  h_singleLeptonD0Significance=initHist(h_singleLeptonD0Significance,"singleLeptonD0Significance","Single lepton d0/sigma",60,-20,20);
  h_singleLeptonD0Significance_vs_phi = new TH2F(TString("singleLeptonD0Significance_vs_phi")+nameSuffix, "Single lepton d0/sigma vs phi", 50, -4, 4, 80, -6, 6 );
  h_singleLeptonD0Significance_vs_theta = new TH2F(TString("singleLeptonD0Significance_vs_theta")+nameSuffix, "Single lepton d0/sigma vs theta", 50, 0, 3.5, 80, -6, 6 );
  h_singleLeptonD0Significance_vs_phi_vs_theta = new TH3F(TString("singleLeptonD0Significance_vs_phi_vs_theta")+nameSuffix, "Single lepton d0/sigma vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 300, -40, 40 );
  h_singleLeptonD0SignificanceG2_vs_phi_vs_theta = new TH3F(TString("singleLeptonD0SignificanceG2_vs_phi_vs_theta")+nameSuffix, "Single lepton d0/sigma (G2) vs phi vs theta", 25, -4, 4, 25, 0, 3.5, 300, -40, 40 );
  h_singleLeptonD0Significance_vs_phi_vs_theta_badRun = new TH3F(TString("singleLeptonD0Significance_vs_phi_vs_theta_badRun")+nameSuffix, "Single lepton d0/sigma vs phi vs theta in bad run range", 25, -4, 4, 20, 0, 3.5, 300, -40, 40 );

  h_singleLeptonD0Significance_vs_phi_vs_theta_noVertex = new TH3F(TString("singleLeptonD0Significance_vs_phi_vs_theta_noVertex")+nameSuffix, "Single lepton d0/sigma vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 300, -40, 40 );
  h_singleLeptonD0Significance_vs_phi_vs_theta_badRun_noVertex = new TH3F(TString("singleLeptonD0Significance_vs_phi_vs_theta_badRun_noVertex")+nameSuffix, "Single lepton d0/sigma vs phi vs theta in bad run range", 25, -4, 4, 20, 0, 3.5, 300, -40, 40 );

  h_singleLeptonD0Significance_vs_phi_vs_theta_pixel = new TH3F(TString("singleLeptonD0Significance_vs_phi_vs_theta_pixel")+nameSuffix, "Single lepton d0/sigma vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 300, -40, 40 );
  h_singleLeptonD0Significance_vs_phi_vs_theta_noPixel = new TH3F(TString("singleLeptonD0Significance_vs_phi_vs_theta_noPixel")+nameSuffix, "Single lepton d0/sigma vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 300, -40, 40 );
  h_leptonD0SigFractionMap_all = new TH2F(TString("leptonD0SigFractionMap_all")+nameSuffix, "theta vs phi",  50, 0, 3.5, 50, -4, 4 );
  h_leptonD0SigFractionMap_pass = new TH2F(TString("leptonD0SigFractionMap_pass")+nameSuffix, "theta vs phi", 50, 0, 3.5, 50, -4, 4  );
  h_singleLeptonD0Significance_allRegion=initHist(h_singleLeptonD0Significance_allRegion,"singleLeptonD0Significance_allRegion", "Single lepton d0/sigma in bad region", 80,-20,20 );
  h_singleLeptonD0Significance_allRegion_corrected=initHist(h_singleLeptonD0Significance_allRegion_corrected,"singleLeptonD0Significance_allRegion_corrected", "Single lepton d0/sigma in bad region", 80,-20,20 );
  h_singleLeptonD0Significance_noVertex_allRegion=initHist(h_singleLeptonD0Significance_noVertex_allRegion,"singleLeptonD0Significance_noVertex_allRegion", "Single lepton d0/sigma in bad region", 80,-20,20 );
  h_singleLeptonD0Significance_badRegion=initHist(h_singleLeptonD0Significance_badRegion,"singleLeptonD0Significance_badRegion", "Single lepton d0/sigma in bad region", 80,-20,20 );
  h_singleLeptonD0Significance_badRegion_corrected=initHist(h_singleLeptonD0Significance_badRegion_corrected,"singleLeptonD0Significance_badRegion_corrected", "Single lepton d0/sigma in bad region", 80,-20,20 );

  h_singleLeptonD0Significance_vs_run = new TH2F(TString("singleLeptonD0Significance_vs_run")+nameSuffix, "Single lepton d0/sigma vs run", 18230, 190456, 208686, 100, -40, 40 );
  h_leptonD0SigFraction_vs_run_all = initHist(h_leptonD0SigFraction_vs_run_all,"leptonD0SigFraction_vs_run_all","High d0 fraction vs run", 18230, 190456, 208686);
  h_leptonD0SigFraction_vs_run_pass = initHist(h_leptonD0SigFraction_vs_run_pass,"leptonD0SigFraction_vs_run_pass","High d0 fraction vs run", 18230, 190456, 208686);

  h_singleLeptonZ0_vs_phi_vs_theta = new TH3F(TString("singleLeptonZ0_vs_phi_vs_theta")+nameSuffix, "Single lepton d0/sigma vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 300, -0.5, 0.5 );
  h_singleLeptonZ0_vs_phi_vs_theta_badRun = new TH3F(TString("singleLeptonZ0_vs_phi_vs_theta_badRun")+nameSuffix, "Single lepton d0/sigma vs phi vs theta in bad run range", 25, -4, 4, 20, 0, 3.5, 300, -0.5, 0.5 );
  h_singleLeptonZ0_vs_phi_vs_theta_noVertex = new TH3F(TString("singleLeptonZ0_vs_phi_vs_theta_noVertex")+nameSuffix, "Single lepton d0/sigma vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 300, -0.5, 0.5 );
  h_singleLeptonZ0_vs_phi_vs_theta_badRun_noVertex = new TH3F(TString("singleLeptonZ0_vs_phi_vs_theta_badRun_noVertex")+nameSuffix, "Single lepton d0/sigma vs phi vs theta in bad run range", 25, -4, 4, 20, 0, 3.5, 300, -0.5, 0.5 );
  h_singleLeptonZ0_vs_phi_vs_theta_pixel = new TH3F(TString("singleLeptonZ0_vs_phi_vs_theta_pixel")+nameSuffix, "Single lepton d0/sigma vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 300, -0.5, 0.5 );
  h_singleLeptonZ0_vs_phi_vs_theta_noPixel = new TH3F(TString("singleLeptonZ0_vs_phi_vs_theta_noPixel")+nameSuffix, "Single lepton d0/sigma vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 300, -0.5, 0.5 );
  h_singleLeptonZ0_vs_run = new TH2F(TString("singleLeptonZ0_vs_run")+nameSuffix, "Single lepton d0/sigma vs run", 18230, 190456, 208686, 100, -0.5, 0.5 );

  h_singleLeptonD0_vs_phi = new TH2F(TString("singleLeptonD0_vs_phi")+nameSuffix, "Single lepton d0 vs phi", 50, -4, 4, 400, -0.5, 0.5 );
  h_singleLeptonD0_vs_phi_vs_theta = new TH3F(TString("singleLeptonD0_vs_phi_vs_theta")+nameSuffix, "Single lepton d0 vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 400, -0.5, 0.5 );
  h_singleLeptonD0_vs_phi_vs_theta_badRun = new TH3F(TString("singleLeptonD0_vs_phi_vs_theta_badRun")+nameSuffix, "Single lepton d0 vs phi vs theta in bad run", 25, -4, 4, 20, 0, 3.5, 400, -0.5, 0.5 );
  h_singleLeptonD0_vs_phi_vs_theta_noVertex = new TH3F(TString("singleLeptonD0_vs_phi_vs_theta_noVertex")+nameSuffix, "Single lepton d0 vs phi vs theta", 25, -4, 4, 20, 0, 3.5, 400, -0.5, 0.5 );
  h_singleLeptonD0_vs_phi_vs_theta_badRun_noVertex = new TH3F(TString("singleLeptonD0_vs_phi_vs_theta_badRun_noVertex")+nameSuffix, "Single lepton d0 vs phi vs theta in bad run", 25, -4, 4, 20, 0, 3.5, 400, -0.5, 0.5 );
  h_singleLeptonD0_vs_run = new TH2F(TString("singleLeptonD0_vs_run")+nameSuffix, "Single lepton d0 vs run", 18230, 190456, 208686, 100, -0.5, 0.5 );

  h_leptonTrackingAlgo_removedLifetimeCuts=initHist(h_leptonTrackingAlgo_removedLifetimeCuts,"leptonTrackingAlgo_removedLifetimeCuts","Tracker reco algo",30,0,30);

  h_minLeptonD0Sig_controlTrigger_removedLifetimeCuts=initHist(h_minLeptonD0Sig_controlTrigger_removedLifetimeCuts,"minLeptonD0Sig_controlTrigger_removedLifetimeCuts","Min lepton d0/sigma, control region",60,-20,10);
  h_minLeptonD0Sig_controlVertex_removedLifetimeCuts=initHist(h_minLeptonD0Sig_controlVertex_removedLifetimeCuts,"minLeptonD0Sig_controlVertex_removedLifetimeCuts","Min lepton d0/sigma, control region",60,-20,10);
  h_minLeptonD0Sig_controlIsolation_removedLifetimeCuts=initHist(h_minLeptonD0Sig_controlIsolation_removedLifetimeCuts,"minLeptonD0Sig_controlIsolation_removedLifetimeCuts","Min lepton d0/sigma, control region",60,-20,10);

  // Photon ID Variables
  h_photonR9_removedLifetimeCuts=initHist(h_photonR9_removedLifetimeCuts,"PhotonR9_removedLifetimeCuts", "Photon R9, removed lifetime cuts", 20, 0, 1.1);
  h_photonSigmaIetaIeta_barrel_removedLifetimeCuts=initHist(h_photonSigmaIetaIeta_barrel_removedLifetimeCuts,"PhotonSigmaIetaIeta_barrel_removedLifetimeCuts", "Photon SigmaIetaIeta, barrel, removed lifetime cuts", 40, 0, 0.05);
  h_photonSigmaIetaIeta_endcap_removedLifetimeCuts=initHist(h_photonSigmaIetaIeta_endcap_removedLifetimeCuts,"PhotonSigmaIetaIeta_endcap_removedLifetimeCuts", "Photon SigmaIetaIeta, endcap, removed lifetime cuts", 40, 0, 0.05);
  h_photonHadTowOverEm_removedLifetimeCuts=initHist(h_photonHadTowOverEm_removedLifetimeCuts,"PhotonHadTowOverEm_removedLifetimeCuts", "Photon HadTowOverEm, removed lifetime cuts", 20, 0, 0.2);
  h_photonHadronicOverEm_removedLifetimeCuts=initHist(h_photonHadronicOverEm_removedLifetimeCuts,"PhotonHadronicOverEm_removedLifetimeCuts", "Photon HadronicOverEm, removed lifetime cuts", 20, 0, 0.2);

  // n-1 removed lifetime cuts
  h_nMinus1_isolationLeptonL_removedLifetimeCuts=initHist(h_nMinus1_isolationLeptonL_removedLifetimeCuts,"nMinus1_isolationLeptonL_removedLifetimeCuts", "Sum pt isolation cone, low pt lepton", 80, 0, 20 );
  h_nMinus1_isolationLeptonH_removedLifetimeCuts=initHist(h_nMinus1_isolationLeptonH_removedLifetimeCuts,"nMinus1_isolationLeptonH_removedLifetimeCuts", "Sum pt isolation cone, high pt lepton", 80, 0, 20 );
  h_nMinus1_relIsolationLeptonL_removedLifetimeCuts=initHist(h_nMinus1_relIsolationLeptonL_removedLifetimeCuts,"nMinus1_relIsolationLeptonL_removedLifetimeCuts", "Rel isolation cone, low pt lepton", 40, 0, 0.5 );
  h_nMinus1_relIsolationLeptonH_removedLifetimeCuts=initHist(h_nMinus1_relIsolationLeptonH_removedLifetimeCuts,"nMinus1_relIsolationLeptonH_removedLifetimeCuts", "Rel isolation cone, high pt lepton", 40, 0, 0.5 );
  h_nMinus1_nHitsBeforeVertex_removedLifetimeCuts=initHist(h_nMinus1_nHitsBeforeVertex_removedLifetimeCuts,"nMinus1_nHitsBeforeVertex_removedLifetimeCuts", "n-1 N hits before vertex", 5, -0.5, 4.5);
  h_nMinus1_nMissingHitsAfterVertex_removedLifetimeCuts=initHist(h_nMinus1_nMissingHitsAfterVertex_removedLifetimeCuts,"nMinus1_nMissingHitsAfterVertex_removedLifetimeCuts", "n-1 N missing hits after vertex", 20, -0.5, 19.5);
  h_nMinus1_minMissingHitsAfterVertex_removedLifetimeCuts=initHist(h_nMinus1_nMissingHitsAfterVertex_removedLifetimeCuts,"nMinus1_minMissingHitsAfterVertex_removedLifetimeCuts", "n-1 min missing hits after vertex", 20, -0.5, 19.5);
  h_nMinus1_maxMissingHitsAfterVertex_removedLifetimeCuts=initHist(h_nMinus1_nMissingHitsAfterVertex_removedLifetimeCuts,"nMinus1_maxMissingHitsAfterVertex_removedLifetimeCuts", "n-1 max missing hits after vertex", 20, -0.5, 19.5);
  h_nMinus1_vertexChi2_removedLifetimeCuts=initHist(h_nMinus1_vertexChi2_removedLifetimeCuts,"nMinus1_vertexChi2_removedLifetimeCuts", "n-1 Vertex Chi^2, removed lifetime cuts", 100, 0, 100);
  h_nMinus1_vertexChi2_removedLifetimeCuts_vPrompt=initHist(h_nMinus1_vertexChi2_removedLifetimeCuts_vPrompt,"nMinus1_vertexChi2_removedLifetimeCuts_vPrompt", "n-1 Vertex Chi^2, removed lifetime cuts", 20, 0, 20);

  // PU dependence
  h_nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched = new TH2F(TString("nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched")+nameSuffix, "Sum pt isolation cone vsPU, low pt lepton", 400, 0, 1000, 50, 0, 50 );
  h_nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched = new TH2F(TString("nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched")+nameSuffix, "Sum pt isolation cone vsPU, high pt lepton", 400, 0, 1000, 50, 0, 50 );
  h_nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched = new TH2F(TString("nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched")+nameSuffix, "Rel isolation cone vsPU, low pt lepton", 100, 0, 1.0, 50, 0, 50 );
  h_nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched = new TH2F(TString("nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched")+nameSuffix, "Rel isolation cone vsPU, high pt lepton", 100, 0, 1.0, 50, 0, 50 );
  h_nMinus1_ptLeptonL_vsPU_finalCuts_genMatched = new TH2F(TString("nMinus1_ptLeptonL_vsPU_finalCuts_genMatched")+nameSuffix, "Lepton pt vs PU, low pt lepton", 150, 0, 1000, 50, 0, 50 );
  h_nMinus1_ptLeptonH_vsPU_finalCuts_genMatched = new TH2F(TString("nMinus1_ptLeptonH_vsPU_finalCuts_genMatched")+nameSuffix, "Lepton pt vs PU, high pt lepton", 150, 0, 1000, 50, 0, 50 );

  h_nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_all = initHist(h_nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_all,"nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_all", "Number of reco PV, leptonL", 50, 0, 50 );
  h_nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_pass = initHist(h_nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_pass,"nMinus1_fracRelIsoLeptonL_vsPU_finalCuts_genMatched_pass", "Number of reco PV, leptonL, pass relIso", 50, 0, 50 );
  h_nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_all = initHist(h_nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_all,"nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_all", "Number of reco PV, leptonH", 50, 0, 50 );
  h_nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_pass = initHist(h_nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_pass,"nMinus1_fracRelIsoLeptonH_vsPU_finalCuts_genMatched_pass", "Number of reco PV, leptonH, pass relIso", 50, 0, 50 );

//  //
//  // REMOVED LIFETIME NO VERTEX
//  //
//  h_mass_removedLifetimeNoVertex=initHist(h_mass_removedLifetimeNoVertex,"Mass_removedLifetimeNoVertex","Dilepton mass, loose cuts",75,0,500);
//  h_mt_removedLifetimeNoVertex=initHist(h_mt_removedLifetimeNoVertex,"Mt_removedLifetimeNoVertex", "Dilepton Mt, final cuts", 75, 0, 500);
//  h_Lxy_removedLifetimeNoVertex=initHist(h_Lxy_removedLifetimeNoVertex,"Lxy_removedLifetimeNoVertex", "Lxy loose cuts",100,0,70);
//  h_nRecoPV_removedLifetimeNoVertex=initHist(h_nRecoPV_removedLifetimeNoVertex,"nRecoPV_removedLifetimeNoVertex", "Number reco PV, final cuts", 50, 0, 50);
//  h_leptonHSCEta_removedLifetimeNoVertex=initHist(h_leptonHSCEta_removedLifetimeNoVertex,"leptonHSCEta_removedLifetimeNoVertex", "Eta leading lepton, final cuts",60,-3,3);
//  h_leptonLSCEta_removedLifetimeNoVertex=initHist(h_leptonLSCEta_removedLifetimeNoVertex,"leptonLSCEta_removedLifetimeNoVertex", "Eta subleading lepton, final cuts",60,-3,3);
//  h_minLeptonD0Sig_removedLifetimeNoVertex=initHist(h_minLeptonD0Sig_removedLifetimeNoVertex,"minLeptonD0Sig_removedLifetimeNoVertex", "Min leptond0/sigma, final cuts",80,-20,20);
//  h_maxLeptonD0Sig_removedLifetimeNoVertex=initHist(h_maxLeptonD0Sig_removedLifetimeNoVertex,"maxLeptonD0Sig_removedLifetimeNoVertex", "Max leptond0/sigma, final cuts",80,-20,20);
//  h_leptonTrackingAlgo_removedLifetimeNoVertex=initHist(h_leptonTrackingAlgo_removedLifetimeNoVertex,"leptonTrackingAlgo_removedLifetimeNoVertex","Tracker reco algo",30,0,30);
//
//  // n-1 final cuts
//  h_nMinus1_oppositeCharge_removedLifetimeNoVertex=initHist(h_nMinus1_oppositeCharge_removedLifetimeNoVertex,"nMinus1_oppositeCharge_removedLifetimeNoVertex", "n-1 lepton opposite charges, final cuts",5,-2,2);
//  h_nMinus1_vertexChi2_removedLifetimeNoVertex=initHist(h_nMinus1_vertexChi2_removedLifetimeNoVertex,"nMinus1_vertexChi2_removedLifetimeNoVertex", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
//  h_nMinus1_deltaPhi_removedLifetimeNoVertex=initHist(h_nMinus1_deltaPhi_removedLifetimeNoVertex,"nMinus1_deltaPhi_removedLifetimeNoVertex", "n-1 Delta Phi, final cuts", 40, 0, 4);
//  h_nMinus1_cosine_removedLifetimeNoVertex=initHist(h_nMinus1_cosine_removedLifetimeNoVertex,"nMinus1_cosine_removedLifetimeNoVertex", "n-1 Cosine, final cuts",22,-1.1,1.1);
//  h_nMinus1_deltaR_removedLifetimeNoVertex=initHist(h_nMinus1_deltaR_removedLifetimeNoVertex,"nMinus1_deltaR_removedLifetimeNoVertex", "n-1 delta R, final cuts",10,0,0.5);
//  h_nMinus1_nHitsBeforeVertex_removedLifetimeNoVertex=initHist(h_nMinus1_nHitsBeforeVertex_removedLifetimeNoVertex,"nMinus1_nHitsBeforeVertex_removedLifetimeNoVertex", "n-1 N hits before vertex", 5, 0, 5);
//  h_nMinus1_nMissingHitsAfterVertex_removedLifetimeNoVertex=initHist(h_nMinus1_nMissingHitsAfterVertex_removedLifetimeNoVertex,"nMinus1_nMissingHitsAfterVertex_removedLifetimeNoVertex", "n-1 N missing hits after vertex", 20, 0, 20);
//  h_nMinus1_leptonCaloMatchDeltaR_removedLifetimeNoVertex=initHist(h_nMinus1_leptonCaloMatchDeltaR_removedLifetimeNoVertex,"nMinus1_leptonCaloMatchDeltaR_removedLifetimeNoVertex","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
//  h_nMinus1_leadingLeptonTrackPt_removedLifetimeNoVertex=initHist(h_nMinus1_leadingLeptonTrackPt_removedLifetimeNoVertex,"nMinus1_leadingLeptonTrackPt_removedLifetimeNoVertex","n-1 Leading lepton track pt, final cuts",20,0,80);
//  h_nMinus1_subleadingLeptonTrackPt_removedLifetimeNoVertex=initHist(h_nMinus1_subleadingLeptonTrackPt_removedLifetimeNoVertex,"nMinus1_subleadingLeptonTrackPt_removedLifetimeNoVertex","n-1 Subleading lepton track pt, final cuts",20,0,80);
//  h_nMinus1_leadingSCEt_removedLifetimeNoVertex=initHist(h_nMinus1_leadingSCEt_removedLifetimeNoVertex,"nMinus1_leadingSCEt_removedLifetimeNoVertex", "n-1 leading SC Et, final cuts",100,0,150);
//  h_nMinus1_subleadingSCEt_removedLifetimeNoVertex=initHist(h_nMinus1_subleadingSCEt_removedLifetimeNoVertex,"nMinus1_subleadingSCEt_removedLifetimeNoVertex", "n-1 subleading SC Et, final cuts",100,0,150);
//  h_nMinus1_relIso_removedLifetimeNoVertex=initHist(h_nMinus1_relIso_removedLifetimeNoVertex,"nMinus1_relIso_removedLifetimeNoVertex", "n-1 lepton rel iso, final cuts", 20, 0, 0.2);
//  h_nMinus1_absIso_removedLifetimeNoVertex=initHist(h_nMinus1_absIso_removedLifetimeNoVertex,"nMinus1_absIso_removedLifetimeNoVertex", "n-1 lepton abs iso, final cuts", 80, 0, 20);
//  // Photon ID Cuts
//  h_photonR9_removedLifetimeNoVertex=initHist(h_photonR9_removedLifetimeNoVertex,"PhotonR9_removedLifetimeNoVertex", "Photon R9, final cuts", 20, 0, 1.1);
//  h_photonSigmaIetaIeta_barrel_removedLifetimeNoVertex=initHist(h_photonSigmaIetaIeta_barrel_removedLifetimeNoVertex,"PhotonSigmaIetaIeta_barrel_removedLifetimeNoVertex", "Photon SigmaIetaIeta, barrel, final cuts", 40, 0, 0.05);
//  h_photonSigmaIetaIeta_endcap_removedLifetimeNoVertex=initHist(h_photonSigmaIetaIeta_endcap_removedLifetimeNoVertex,"PhotonSigmaIetaIeta_endcap_removedLifetimeNoVertex", "Photon SigmaIetaIeta, endcap, final cuts", 40, 0, 0.05);
//  h_photonHadTowOverEm_removedLifetimeNoVertex=initHist(h_photonHadTowOverEm_removedLifetimeNoVertex,"PhotonHadTowOverEm_removedLifetimeNoVertex", "Photon HadTowOverEm, final cuts", 20, 0, 0.2);
//  h_photonHadronicOverEm_removedLifetimeNoVertex=initHist(h_photonHadronicOverEm_removedLifetimeNoVertex,"PhotonHadronicOverEm_removedLifetimeNoVertex", "Photon HadronicOverEm, final cuts", 20, 0, 0.2);


  // 2011 Cuts
  h_mass_2011Cuts=initHist(h_mass_2011Cuts,"Mass_2011Cuts", "Dilepton mass, 2011 cuts", 75, 0, 500);

  // Trigger efficiency plots
  h_trig_Lxy_all=initHist(h_trig_Lxy_all,"trig_Lxy_all", "Lxy of all exotics", 20, 0, 200 );
  h_trig_Lxy_pass=initHist(h_trig_Lxy_pass,"trig_Lxy_pass", "Lxy of triggered exotics", 20, 0, 200 );

  h_trig_ctau_all=initHist(h_trig_ctau_all,"trig_ctau_all", "Ctau of all exotics", 100, 0.01, 1000 );
  h_trig_ctau_pass=initHist(h_trig_ctau_pass,"trig_ctau_pass", "Ctau of triggered exotics", 100, 0.01, 1000 );

  h_minD0SigCut_vs_LxySigCut = new TH2F(TString("minD0SigCut_vs_LxySigCut")+nameSuffix, "# candidates passing cuts as function of d0/sigma and Lxy/sigma cut values",10,-0.5,9.5,40,-0.5,39.5);


  // Fill maps of histograms

  // Final Cuts
  histMapFinal["vertexChi2"] = h_nMinus1_vertexChi2_finalCuts;
  histMapFinal["oppositeCharge"] = h_nMinus1_oppositeCharge_finalCuts;
  histMapFinal["deltaPhi"] = h_nMinus1_deltaPhi_finalCuts;
  histMapFinal["cosine"] = h_nMinus1_cosine_finalCuts;
  histMapFinal["deltaR"] = h_nMinus1_deltaR_finalCuts;
  histMapFinal["nHitsBeforeVertex"] = h_nMinus1_nHitsBeforeVertex_finalCuts;
  histMapFinal["nMissingHitsAfterVertex"] = h_nMinus1_nMissingHitsAfterVertex_finalCuts;
  histMapFinal["leptonD0Sig"] = h_nMinus1_leptonD0Sig_finalCuts;
  histMapFinal["leptonD0SigMax"] = h_nMinus1_leptonD0SigMax_finalCuts;
  histMapFinal["leptonD0SigSameSign"] = h_nMinus1_leptonD0SigSameSign_finalCuts;
  histMapFinal["leptonAbsD0Sig_oppositeSignMin"] = h_nMinus1_leptonAbsD0Sig_oppositeSignMin_finalCuts;
  histMapFinal["leptonD0Sig_oppositeSignMin"] = h_nMinus1_leptonD0Sig_oppositeSignMin_finalCuts;
  histMapFinal["leptonD0Sig_oppositeSignMax"] = h_nMinus1_leptonD0Sig_oppositeSignMax_finalCuts;
  histMapFinal["caloMatchDeltaR"] = h_nMinus1_leptonCaloMatchDeltaR_finalCuts;
  histMapFinal["leadingTrackpt"] = h_nMinus1_leadingLeptonTrackPt_finalCuts;
  histMapFinal["subleadingTrackpt"] = h_nMinus1_subleadingLeptonTrackPt_finalCuts;
  histMapFinal["leadingSCEt"] = h_nMinus1_leadingSCEt_finalCuts;
  histMapFinal["subleadingSCEt"] = h_nMinus1_subleadingSCEt_finalCuts;
  histMapFinal["relIso"] = h_nMinus1_relIso_finalCuts;
  histMapFinal["absIso"] = h_nMinus1_absIso_finalCuts;
  histMapFinal["photonR9"] = h_photonR9_finalCuts;
  histMapFinal["photonSigmaIetaIeta_barrel"] = h_photonSigmaIetaIeta_barrel_finalCuts;
  histMapFinal["photonSigmaIetaIeta_endcap"] = h_photonSigmaIetaIeta_endcap_finalCuts;
  histMapFinal["photonHadTowOverEm"] = h_photonHadTowOverEm_finalCuts;
  histMapFinal["photonHadronicOverEm"] = h_photonHadronicOverEm_finalCuts;
  histMapFinal["mass"] = h_mass_finalCuts;
  histMapFinal["mt"] = h_mt_finalCuts;
  histMapFinal["Lxy"] = h_Lxy_finalCuts;
  histMapFinal["nRecoPV"] = h_nRecoPV_finalCuts;
  histMapFinal["TrackingAlgo"] = h_leptonTrackingAlgo_finalCuts;
  histMapFinal["leptonHSCEta"] = h_leptonHSCEta_finalCuts;
  histMapFinal["leptonLSCEta"] = h_leptonLSCEta_finalCuts;
  histMapFinal["leptonD0SigMin_allCuts"] = h_minLeptonD0Sig_finalCuts;
  histMapFinal["leptonD0SigMax_allCuts"] = h_maxLeptonD0Sig_finalCuts;

//  // Loose Cuts A
//  histMapLooseA["vertexChi2"] = h_nMinus1_vertexChi2_looseCutsA;
//  histMapLooseA["oppositeCharge"] = h_nMinus1_oppositeCharge_looseCutsA;
//  histMapLooseA["deltaPhi"] = h_nMinus1_deltaPhi_looseCutsA;
//  histMapLooseA["cosine"] = h_nMinus1_cosine_looseCutsA;
//  histMapLooseA["deltaR"] = h_nMinus1_deltaR_looseCutsA;
//  histMapLooseA["nHitsBeforeVertex"] = h_nMinus1_nHitsBeforeVertex_looseCutsA;
//  histMapLooseA["nMissingHitsAfterVertex"] = h_nMinus1_nMissingHitsAfterVertex_looseCutsA;
//  histMapLooseA["caloMatchDeltaR"] = h_nMinus1_leptonCaloMatchDeltaR_looseCutsA;
//  histMapLooseA["leadingTrackpt"] = h_nMinus1_leadingLeptonTrackPt_looseCutsA;
//  histMapLooseA["subleadingTrackpt"] = h_nMinus1_subleadingLeptonTrackPt_looseCutsA;
//  histMapLooseA["leadingSCEt"] = h_nMinus1_leadingSCEt_looseCutsA;
//  histMapLooseA["subleadingSCEt"] = h_nMinus1_subleadingSCEt_looseCutsA;
//  histMapLooseA["relIso"] = h_nMinus1_relIso_looseCutsA;
//  histMapLooseA["absIso"] = h_nMinus1_absIso_looseCutsA;
//  histMapLooseA["photonR9"] = h_photonR9_looseCutsA;
//  histMapLooseA["photonSigmaIetaIeta_barrel"] = h_photonSigmaIetaIeta_barrel_looseCutsA;
//  histMapLooseA["photonSigmaIetaIeta_endcap"] = h_photonSigmaIetaIeta_endcap_looseCutsA;
//  histMapLooseA["photonHadTowOverEm"] = h_photonHadTowOverEm_looseCutsA;
//  histMapLooseA["photonHadronicOverEm"] = h_photonHadronicOverEm_looseCutsA;
//  histMapLooseA["mass"] = h_mass_looseCutsA;
//  histMapLooseA["mt"] = h_mt_looseCutsA;
//  histMapLooseA["Lxy"] = h_Lxy_looseCutsA;
//  histMapLooseA["nRecoPV"] = h_nRecoPV_looseCutsA;
//  histMapLooseA["TrackingAlgo"] = h_leptonTrackingAlgo_looseCutsA;
//  histMapLooseA["leptonHSCEta"] = h_leptonHSCEta_looseCutsA;
//  histMapLooseA["leptonLSCEta"] = h_leptonLSCEta_looseCutsA;
//  histMapLooseA["leptonD0SigMin_allCuts"] = h_minLeptonD0Sig_looseCutsA;
//  histMapLooseA["leptonD0SigMax_allCuts"] = h_maxLeptonD0Sig_looseCutsA;
//
//  // Loose Cuts B
//  histMapLooseB["vertexChi2"] = h_nMinus1_vertexChi2_looseCutsB;
//  histMapLooseB["oppositeCharge"] = h_nMinus1_oppositeCharge_looseCutsB;
//  histMapLooseB["deltaPhi"] = h_nMinus1_deltaPhi_looseCutsB;
//  histMapLooseB["cosine"] = h_nMinus1_cosine_looseCutsB;
//  histMapLooseB["deltaR"] = h_nMinus1_deltaR_looseCutsB;
//  histMapLooseB["nHitsBeforeVertex"] = h_nMinus1_nHitsBeforeVertex_looseCutsB;
//  histMapLooseB["nMissingHitsAfterVertex"] = h_nMinus1_nMissingHitsAfterVertex_looseCutsB;
//  histMapLooseB["caloMatchDeltaR"] = h_nMinus1_leptonCaloMatchDeltaR_looseCutsB;
//  histMapLooseB["leadingTrackpt"] = h_nMinus1_leadingLeptonTrackPt_looseCutsB;
//  histMapLooseB["subleadingTrackpt"] = h_nMinus1_subleadingLeptonTrackPt_looseCutsB;
//  histMapLooseB["leadingSCEt"] = h_nMinus1_leadingSCEt_looseCutsB;
//  histMapLooseB["subleadingSCEt"] = h_nMinus1_subleadingSCEt_looseCutsB;
//  histMapLooseB["relIso"] = h_nMinus1_relIso_looseCutsB;
//  histMapLooseB["absIso"] = h_nMinus1_absIso_looseCutsB;
//  histMapLooseB["photonR9"] = h_photonR9_looseCutsB;
//  histMapLooseB["photonSigmaIetaIeta_barrel"] = h_photonSigmaIetaIeta_barrel_looseCutsB;
//  histMapLooseB["photonSigmaIetaIeta_endcap"] = h_photonSigmaIetaIeta_endcap_looseCutsB;
//  histMapLooseB["photonHadTowOverEm"] = h_photonHadTowOverEm_looseCutsB;
//  histMapLooseB["photonHadronicOverEm"] = h_photonHadronicOverEm_looseCutsB;
//  histMapLooseB["mass"] = h_mass_looseCutsB;
//  histMapLooseB["mt"] = h_mt_looseCutsB;
//  histMapLooseB["Lxy"] = h_Lxy_looseCutsB;
//  histMapLooseB["nRecoPV"] = h_nRecoPV_looseCutsB;
//  histMapLooseB["TrackingAlgo"] = h_leptonTrackingAlgo_looseCutsB;
//  histMapLooseB["leptonHSCEta"] = h_leptonHSCEta_looseCutsB;
//  histMapLooseB["leptonLSCEta"] = h_leptonLSCEta_looseCutsB;
//  histMapLooseB["leptonD0SigMin_allCuts"] = h_minLeptonD0Sig_looseCutsB;
//  histMapLooseB["leptonD0SigMax_allCuts"] = h_maxLeptonD0Sig_looseCutsB;
//
//  // Loose Cuts C
//  histMapLooseC["vertexChi2"] = h_nMinus1_vertexChi2_looseCutsC;
//  histMapLooseC["oppositeCharge"] = h_nMinus1_oppositeCharge_looseCutsC;
//  histMapLooseC["deltaPhi"] = h_nMinus1_deltaPhi_looseCutsC;
//  histMapLooseC["cosine"] = h_nMinus1_cosine_looseCutsC;
//  histMapLooseC["deltaR"] = h_nMinus1_deltaR_looseCutsC;
//  histMapLooseC["nHitsBeforeVertex"] = h_nMinus1_nHitsBeforeVertex_looseCutsC;
//  histMapLooseC["nMissingHitsAfterVertex"] = h_nMinus1_nMissingHitsAfterVertex_looseCutsC;
//  histMapLooseC["caloMatchDeltaR"] = h_nMinus1_leptonCaloMatchDeltaR_looseCutsC;
//  histMapLooseC["leadingTrackpt"] = h_nMinus1_leadingLeptonTrackPt_looseCutsC;
//  histMapLooseC["subleadingTrackpt"] = h_nMinus1_subleadingLeptonTrackPt_looseCutsC;
//  histMapLooseC["leadingSCEt"] = h_nMinus1_leadingSCEt_looseCutsC;
//  histMapLooseC["subleadingSCEt"] = h_nMinus1_subleadingSCEt_looseCutsC;
//  histMapLooseC["relIso"] = h_nMinus1_relIso_looseCutsC;
//  histMapLooseC["absIso"] = h_nMinus1_absIso_looseCutsC;
//  histMapLooseC["photonR9"] = h_photonR9_looseCutsC;
//  histMapLooseC["photonSigmaIetaIeta_barrel"] = h_photonSigmaIetaIeta_barrel_looseCutsC;
//  histMapLooseC["photonSigmaIetaIeta_endcap"] = h_photonSigmaIetaIeta_endcap_looseCutsC;
//  histMapLooseC["photonHadTowOverEm"] = h_photonHadTowOverEm_looseCutsC;
//  histMapLooseC["photonHadronicOverEm"] = h_photonHadronicOverEm_looseCutsC;
//  histMapLooseC["mass"] = h_mass_looseCutsC;
//  histMapLooseC["mt"] = h_mt_looseCutsC;
//  histMapLooseC["Lxy"] = h_Lxy_looseCutsC;
//  histMapLooseC["nRecoPV"] = h_nRecoPV_looseCutsC;
//  histMapLooseC["TrackingAlgo"] = h_leptonTrackingAlgo_looseCutsC;
//  histMapLooseC["leptonHSCEta"] = h_leptonHSCEta_looseCutsC;
//  histMapLooseC["leptonLSCEta"] = h_leptonLSCEta_looseCutsC;
//  histMapLooseC["leptonD0SigMin_allCuts"] = h_minLeptonD0Sig_looseCutsC;
//  histMapLooseC["leptonD0SigMax_allCuts"] = h_maxLeptonD0Sig_looseCutsC;
//
//  // Removed lifetime no vertex
//  histMapRemovedLifetimeNoVertex["vertexChi2"] = h_nMinus1_vertexChi2_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["oppositeCharge"] = h_nMinus1_oppositeCharge_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["deltaPhi"] = h_nMinus1_deltaPhi_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["cosine"] = h_nMinus1_cosine_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["deltaR"] = h_nMinus1_deltaR_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["nHitsBeforeVertex"] = h_nMinus1_nHitsBeforeVertex_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["nMissingHitsAfterVertex"] = h_nMinus1_nMissingHitsAfterVertex_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["caloMatchDeltaR"] = h_nMinus1_leptonCaloMatchDeltaR_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["leadingTrackpt"] = h_nMinus1_leadingLeptonTrackPt_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["subleadingTrackpt"] = h_nMinus1_subleadingLeptonTrackPt_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["leadingSCEt"] = h_nMinus1_leadingSCEt_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["subleadingSCEt"] = h_nMinus1_subleadingSCEt_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["relIso"] = h_nMinus1_relIso_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["absIso"] = h_nMinus1_absIso_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["photonR9"] = h_photonR9_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["photonSigmaIetaIeta_barrel"] = h_photonSigmaIetaIeta_barrel_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["photonSigmaIetaIeta_endcap"] = h_photonSigmaIetaIeta_endcap_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["photonHadTowOverEm"] = h_photonHadTowOverEm_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["photonHadronicOverEm"] = h_photonHadronicOverEm_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["mass"] = h_mass_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["mt"] = h_mt_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["Lxy"] = h_Lxy_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["nRecoPV"] = h_nRecoPV_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["TrackingAlgo"] = h_leptonTrackingAlgo_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["leptonHSCEta"] = h_leptonHSCEta_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["leptonLSCEta"] = h_leptonLSCEta_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["leptonD0SigMin_allCuts"] = h_minLeptonD0Sig_removedLifetimeNoVertex;
//  histMapRemovedLifetimeNoVertex["leptonD0SigMax_allCuts"] = h_maxLeptonD0Sig_removedLifetimeNoVertex;

  // Final Cuts Coll
  histMapFinalColl["vertexChi2"] = h_nMinus1_vertexChi2_finalCollCuts;
  histMapFinalColl["oppositeCharge"] = h_nMinus1_oppositeCharge_finalCollCuts;
  histMapFinalColl["deltaPhi"] = h_nMinus1_deltaPhi_finalCollCuts;
  histMapFinalColl["cosine"] = h_nMinus1_cosine_finalCollCuts;
  histMapFinalColl["deltaR"] = h_nMinus1_deltaR_finalCollCuts;
  histMapFinalColl["nHitsBeforeVertex"] = h_nMinus1_nHitsBeforeVertex_finalCollCuts;
  histMapFinalColl["nMissingHitsAfterVertex"] = h_nMinus1_nMissingHitsAfterVertex_finalCollCuts;
  histMapFinalColl["minMissingHitsAfterVertex"] = h_nMinus1_minMissingHitsAfterVertex_finalCollCuts;
  histMapFinalColl["maxMissingHitsAfterVertex"] = h_nMinus1_maxMissingHitsAfterVertex_finalCollCuts;
  histMapFinalColl["caloMatchDeltaR"] = h_nMinus1_leptonCaloMatchDeltaR_finalCollCuts;
  histMapFinalColl["leadingTrackpt"] = h_nMinus1_leadingLeptonTrackPt_finalCollCuts;
  histMapFinalColl["subleadingTrackpt"] = h_nMinus1_subleadingLeptonTrackPt_finalCollCuts;
  histMapFinalColl["leadingSCEt"] = h_nMinus1_leadingSCEt_finalCollCuts;
  histMapFinalColl["subleadingSCEt"] = h_nMinus1_subleadingSCEt_finalCollCuts;
  histMapFinalColl["relIso"] = h_nMinus1_relIso_finalCollCuts;
  histMapFinalColl["absIso"] = h_nMinus1_absIso_finalCollCuts;
  histMapFinalColl["photonR9"] = h_photonR9_finalCollCuts;
  histMapFinalColl["photonSigmaIetaIeta_barrel"] = h_photonSigmaIetaIeta_barrel_finalCollCuts;
  histMapFinalColl["photonSigmaIetaIeta_endcap"] = h_photonSigmaIetaIeta_endcap_finalCollCuts;
  histMapFinalColl["photonHadTowOverEm"] = h_photonHadTowOverEm_finalCollCuts;
  histMapFinalColl["photonHadronicOverEm"] = h_photonHadronicOverEm_finalCollCuts;
  histMapFinalColl["mass"] = h_mass_finalCollCuts;
  histMapFinalColl["mt"] = h_mt_finalCollCuts;
  histMapFinalColl["Lxy"] = h_Lxy_finalCollCuts;
  histMapFinalColl["nRecoPV"] = h_nRecoPV_finalCollCuts;
  histMapFinalColl["TrackingAlgo"] = h_leptonTrackingAlgo_finalCollCuts;
  histMapFinalColl["leptonHSCEta"] = h_leptonHSCEta_finalCollCuts;
  histMapFinalColl["leptonLSCEta"] = h_leptonLSCEta_finalCollCuts;
  histMapFinalColl["leptonD0SigMin_allCuts"] = h_minLeptonD0Sig_finalCollCuts;
  histMapFinalColl["leptonD0SigMax_allCuts"] = h_maxLeptonD0Sig_finalCollCuts;\
  histMapFinalColl["ptOverE"] = h_ptOverE_finalCollCuts;
  histMapFinalColl["ptMinusE"] = h_ptMinusE_finalCollCuts;
  histMapFinalColl["nCandsPerEvent"] = h_nCandsPerEvent_finalCollCuts;

  // Loose Cuts Coll
  histMapLooseColl["vertexChi2"] = h_nMinus1_vertexChi2_looseCollCuts;
  histMapLooseColl["oppositeCharge"] = h_nMinus1_oppositeCharge_looseCollCuts;
  histMapLooseColl["deltaPhi"] = h_nMinus1_deltaPhi_looseCollCuts;
  histMapLooseColl["cosine"] = h_nMinus1_cosine_looseCollCuts;
  histMapLooseColl["deltaR"] = h_nMinus1_deltaR_looseCollCuts;
  histMapLooseColl["nHitsBeforeVertex"] = h_nMinus1_nHitsBeforeVertex_looseCollCuts;
  histMapLooseColl["nMissingHitsAfterVertex"] = h_nMinus1_nMissingHitsAfterVertex_looseCollCuts;
  histMapLooseColl["minMissingHitsAfterVertex"] = h_nMinus1_minMissingHitsAfterVertex_looseCollCuts;
  histMapLooseColl["maxMissingHitsAfterVertex"] = h_nMinus1_maxMissingHitsAfterVertex_looseCollCuts;
  histMapLooseColl["caloMatchDeltaR"] = h_nMinus1_leptonCaloMatchDeltaR_looseCollCuts;
  histMapLooseColl["leadingTrackpt"] = h_nMinus1_leadingLeptonTrackPt_looseCollCuts;
  histMapLooseColl["subleadingTrackpt"] = h_nMinus1_subleadingLeptonTrackPt_looseCollCuts;
  histMapLooseColl["leadingSCEt"] = h_nMinus1_leadingSCEt_looseCollCuts;
  histMapLooseColl["subleadingSCEt"] = h_nMinus1_subleadingSCEt_looseCollCuts;
  histMapLooseColl["relIso"] = h_nMinus1_relIso_looseCollCuts;
  histMapLooseColl["absIso"] = h_nMinus1_absIso_looseCollCuts;
  histMapLooseColl["photonR9"] = h_photonR9_looseCollCuts;
  histMapLooseColl["photonSigmaIetaIeta_barrel"] = h_photonSigmaIetaIeta_barrel_looseCollCuts;
  histMapLooseColl["photonSigmaIetaIeta_endcap"] = h_photonSigmaIetaIeta_endcap_looseCollCuts;
  histMapLooseColl["photonHadTowOverEm"] = h_photonHadTowOverEm_looseCollCuts;
  histMapLooseColl["photonHadronicOverEm"] = h_photonHadronicOverEm_looseCollCuts;
  histMapLooseColl["mass"] = h_mass_looseCollCuts;
  histMapLooseColl["mt"] = h_mt_looseCollCuts;
  histMapLooseColl["Lxy"] = h_Lxy_looseCollCuts;
  histMapLooseColl["nRecoPV"] = h_nRecoPV_looseCollCuts;
  histMapLooseColl["TrackingAlgo"] = h_leptonTrackingAlgo_looseCollCuts;
  histMapLooseColl["leptonHSCEta"] = h_leptonHSCEta_looseCollCuts;
  histMapLooseColl["leptonLSCEta"] = h_leptonLSCEta_looseCollCuts;
  histMapLooseColl["leptonD0SigMin_allCuts"] = h_minLeptonD0Sig_looseCollCuts;
  histMapLooseColl["leptonD0SigMax_allCuts"] = h_maxLeptonD0Sig_looseCollCuts;
  histMapLooseColl["ptOverE"] = h_ptOverE_looseCollCuts;
  histMapLooseColl["ptMinusE"] = h_ptMinusE_looseCollCuts;
  histMapLooseColl["nCandsPerEvent"] = h_nCandsPerEvent_looseCollCuts;

  // Loose Control Cuts Coll
  histMapLooseControlColl["vertexChi2"] = h_nMinus1_vertexChi2_looseControlCollCuts;
  histMapLooseControlColl["oppositeCharge"] = h_nMinus1_oppositeCharge_looseControlCollCuts;
  histMapLooseControlColl["deltaPhi"] = h_nMinus1_deltaPhi_looseControlCollCuts;
  histMapLooseControlColl["cosine"] = h_nMinus1_cosine_looseControlCollCuts;
  histMapLooseControlColl["deltaR"] = h_nMinus1_deltaR_looseControlCollCuts;
  histMapLooseControlColl["nHitsBeforeVertex"] = h_nMinus1_nHitsBeforeVertex_looseControlCollCuts;
  histMapLooseControlColl["nMissingHitsAfterVertex"] = h_nMinus1_nMissingHitsAfterVertex_looseControlCollCuts;
  histMapLooseControlColl["minMissingHitsAfterVertex"] = h_nMinus1_minMissingHitsAfterVertex_looseControlCollCuts;
  histMapLooseControlColl["maxMissingHitsAfterVertex"] = h_nMinus1_maxMissingHitsAfterVertex_looseControlCollCuts;
  histMapLooseControlColl["caloMatchDeltaR"] = h_nMinus1_leptonCaloMatchDeltaR_looseControlCollCuts;
  histMapLooseControlColl["leadingTrackpt"] = h_nMinus1_leadingLeptonTrackPt_looseControlCollCuts;
  histMapLooseControlColl["subleadingTrackpt"] = h_nMinus1_subleadingLeptonTrackPt_looseControlCollCuts;
  histMapLooseControlColl["leadingSCEt"] = h_nMinus1_leadingSCEt_looseControlCollCuts;
  histMapLooseControlColl["subleadingSCEt"] = h_nMinus1_subleadingSCEt_looseControlCollCuts;
  histMapLooseControlColl["relIso"] = h_nMinus1_relIso_looseControlCollCuts;
  histMapLooseControlColl["absIso"] = h_nMinus1_absIso_looseControlCollCuts;
  histMapLooseControlColl["photonR9"] = h_photonR9_looseControlCollCuts;
  histMapLooseControlColl["photonSigmaIetaIeta_barrel"] = h_photonSigmaIetaIeta_barrel_looseControlCollCuts;
  histMapLooseControlColl["photonSigmaIetaIeta_endcap"] = h_photonSigmaIetaIeta_endcap_looseControlCollCuts;
  histMapLooseControlColl["photonHadTowOverEm"] = h_photonHadTowOverEm_looseControlCollCuts;
  histMapLooseControlColl["photonHadronicOverEm"] = h_photonHadronicOverEm_looseControlCollCuts;
  histMapLooseControlColl["mass"] = h_mass_looseControlCollCuts;
  histMapLooseControlColl["mt"] = h_mt_looseControlCollCuts;
  histMapLooseControlColl["Lxy"] = h_Lxy_looseControlCollCuts;
  histMapLooseControlColl["nRecoPV"] = h_nRecoPV_looseControlCollCuts;
  histMapLooseControlColl["TrackingAlgo"] = h_leptonTrackingAlgo_looseControlCollCuts;
  histMapLooseControlColl["leptonHSCEta"] = h_leptonHSCEta_looseControlCollCuts;
  histMapLooseControlColl["leptonLSCEta"] = h_leptonLSCEta_looseControlCollCuts;
  histMapLooseControlColl["leptonD0SigMin_allCuts"] = h_minLeptonD0Sig_looseControlCollCuts;
  histMapLooseControlColl["leptonD0SigMax_allCuts"] = h_maxLeptonD0Sig_looseControlCollCuts;
  histMapLooseControlColl["ptOverE"] = h_ptOverE_looseControlCollCuts;
  histMapLooseControlColl["ptMinusE"] = h_ptMinusE_looseControlCollCuts;
  histMapLooseControlColl["d0SigmaNoMissingHits"] = h_minLeptonAbsD0Sig_deltaPhiG90_noMissingHits_algo10_removedLifetimeCollCuts;
  histMapLooseControlColl["nCandsPerEvent"] = h_nCandsPerEvent_looseControlCollCuts;

  //  control Cuts Coll
  histMapControlColl["vertexChi2"] = h_nMinus1_vertexChi2_controlCollCuts;
  histMapControlColl["oppositeCharge"] = h_nMinus1_oppositeCharge_controlCollCuts;
  histMapControlColl["deltaPhi"] = h_nMinus1_deltaPhi_controlCollCuts;
  histMapControlColl["cosine"] = h_nMinus1_cosine_controlCollCuts;
  histMapControlColl["deltaR"] = h_nMinus1_deltaR_controlCollCuts;
  histMapControlColl["nHitsBeforeVertex"] = h_nMinus1_nHitsBeforeVertex_controlCollCuts;
  histMapControlColl["nMissingHitsAfterVertex"] = h_nMinus1_nMissingHitsAfterVertex_controlCollCuts;
  histMapControlColl["minMissingHitsAfterVertex"] = h_nMinus1_minMissingHitsAfterVertex_controlCollCuts;
  histMapControlColl["maxMissingHitsAfterVertex"] = h_nMinus1_maxMissingHitsAfterVertex_controlCollCuts;
  histMapControlColl["caloMatchDeltaR"] = h_nMinus1_leptonCaloMatchDeltaR_controlCollCuts;
  histMapControlColl["leadingTrackpt"] = h_nMinus1_leadingLeptonTrackPt_controlCollCuts;
  histMapControlColl["subleadingTrackpt"] = h_nMinus1_subleadingLeptonTrackPt_controlCollCuts;
  histMapControlColl["leadingSCEt"] = h_nMinus1_leadingSCEt_controlCollCuts;
  histMapControlColl["subleadingSCEt"] = h_nMinus1_subleadingSCEt_controlCollCuts;
  histMapControlColl["relIso"] = h_nMinus1_relIso_controlCollCuts;
  histMapControlColl["absIso"] = h_nMinus1_absIso_controlCollCuts;
  histMapControlColl["photonR9"] = h_photonR9_controlCollCuts;
  histMapControlColl["photonSigmaIetaIeta_barrel"] = h_photonSigmaIetaIeta_barrel_controlCollCuts;
  histMapControlColl["photonSigmaIetaIeta_endcap"] = h_photonSigmaIetaIeta_endcap_controlCollCuts;
  histMapControlColl["photonHadTowOverEm"] = h_photonHadTowOverEm_controlCollCuts;
  histMapControlColl["photonHadronicOverEm"] = h_photonHadronicOverEm_controlCollCuts;
  histMapControlColl["mass"] = h_mass_controlCollCuts;
  histMapControlColl["mt"] = h_mt_controlCollCuts;
  histMapControlColl["Lxy"] = h_Lxy_controlCollCuts;
  histMapControlColl["nRecoPV"] = h_nRecoPV_controlCollCuts;
  histMapControlColl["TrackingAlgo"] = h_leptonTrackingAlgo_controlCollCuts;
  histMapControlColl["leptonHSCEta"] = h_leptonHSCEta_controlCollCuts;
  histMapControlColl["leptonLSCEta"] = h_leptonLSCEta_controlCollCuts;
  histMapControlColl["leptonD0SigMin_allCuts"] = h_minLeptonD0Sig_controlCollCuts;
  histMapControlColl["leptonD0SigMax_allCuts"] = h_maxLeptonD0Sig_controlCollCuts;
  histMapControlColl["ptOverE"] = h_ptOverE_controlCollCuts;
  histMapControlColl["ptMinusE"] = h_ptMinusE_controlCollCuts;
  histMapControlColl["nCandsPerEvent"] = h_nCandsPerEvent_controlCollCuts;

}

Histograms::~Histograms()
{
}

TH1F* Histograms::initHist(TH1F * hist, TString name, TString title, const unsigned int nBins, float xMin, const float xMax){
  hist = new TH1F(name+nameSuffix, title, nBins, xMin, xMax);
  histMap[name]=hist;
  return hist;
}


void Histograms::writeHistograms( TFile & outputFile ) {
  outputFile.cd();

  // Write to file
  for ( map<TString, TH1F*>::const_iterator hist = histMap.begin(); hist != histMap.end(); hist++ ) {
    hist->second->Write();
  }


  // A few TH2F to do manually
  h_nMinus1_leptonD0Sig_vs_LxySig_finalCuts->Write();

  h_l_vs_h_leptonD0Sig_removedLifetimeCuts->Write();
  h_singleLeptonD0Significance_vs_phi->Write();
  h_singleLeptonD0Significance_vs_theta->Write();
  h_singleLeptonD0Significance_vs_phi_vs_theta->Write();
  h_singleLeptonD0SignificanceG2_vs_phi_vs_theta->Write();
  h_singleLeptonD0Significance_vs_phi_vs_theta_badRun->Write();
  h_singleLeptonD0Significance_vs_phi_vs_theta_noVertex->Write();
  h_singleLeptonD0Significance_vs_phi_vs_theta_badRun_noVertex->Write();
  h_singleLeptonD0Significance_vs_phi_vs_theta_pixel->Write();
  h_singleLeptonD0Significance_vs_phi_vs_theta_noPixel->Write();
  h_singleLeptonD0Significance_vs_run->Write();

  h_singleLeptonD0_vs_phi_vs_theta->Write();
  h_singleLeptonD0_vs_phi_vs_theta_badRun->Write();
  h_singleLeptonD0_vs_phi_vs_theta_noVertex->Write();
  h_singleLeptonD0_vs_phi_vs_theta_badRun_noVertex->Write();
  h_singleLeptonD0_vs_run->Write();

  h_singleLeptonZ0_vs_phi_vs_theta->Write();
  h_singleLeptonZ0_vs_phi_vs_theta_badRun->Write();
  h_singleLeptonZ0_vs_phi_vs_theta_noVertex->Write();
  h_singleLeptonZ0_vs_phi_vs_theta_badRun_noVertex->Write();
  h_singleLeptonZ0_vs_phi_vs_theta_pixel->Write();
  h_singleLeptonZ0_vs_phi_vs_theta_noPixel->Write();
  h_singleLeptonZ0_vs_run->Write();

  h_leptonD0SigFractionMap_all->Write();
  h_leptonD0SigFractionMap_pass->Write();

  h_nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_ptLeptonL_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_ptLeptonH_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_relIsolationLeptonL_vsPU_finalCollCuts_genMatched->Write();
  h_nMinus1_relIsolationLeptonH_vsPU_finalCollCuts_genMatched->Write();

  h_minD0SigCut_vs_LxySigCut->Write();


  for (unsigned int i=0; i<h_trigEff_meanLifetime.size(); i++)
    h_trigEff_meanLifetime[i]->Write();
  for (unsigned int i=0; i<h_trigEff_meanLifetimeLog.size(); i++)
    h_trigEff_meanLifetimeLog[i]->Write();

}

void Histograms::drawOverflows() {
  // Draw overflow in final bin

  for ( map<TString, TH1F*>::const_iterator hist = histMap.begin(); hist != histMap.end(); hist++ ) {
    overflow(*hist->second);
  }
}

void Histograms::drawUnderflows() {
  // Draw overflow in final bin
  underflow(*h_nMinus1_leptonD0Sig_finalCuts);
  underflow(*h_nMinus1_leptonD0SigSameSign_finalCuts);
  underflow(*h_nMinus1_leptonD0Sig_oppositeSignMin_finalCuts);
  underflow(*h_nMinus1_leptonD0Sig_oppositeSignMax_finalCuts);
  underflow(*h_minLeptonD0Sig_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_signedWrtDileptonPerp_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_oppSign_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_oppSign_forFittingData_removedLifetimeCuts);

  underflow(*h_singleLeptonD0Significance_allRegion);
  underflow(*h_singleLeptonD0Significance_allRegion_corrected);
  underflow(*h_singleLeptonD0Significance_noVertex_allRegion);
  underflow(*h_singleLeptonD0Significance_badRegion);
  underflow(*h_singleLeptonD0Significance_badRegion_corrected);

  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_badRegion);
  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_badRegion_corrected);

  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2);
  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_badRegion_lp2_corrected);

  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2);
  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_badRegion_gp2_corrected);

  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_allRegion);
  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_allRegion_corrected);

  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2);
  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_allRegion_lp2_corrected);

  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2);
  underflow(*h_minLeptonD0Sig_removedLifetimeCuts_allRegion_gp2_corrected);

  underflow(*h_bothLeptonsD0Sig_d0Corrected_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_d0Corrected_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_d0Corrected_forFittingData_removedLifetimeCuts);

  underflow(*h_bothLeptonsD0Sig_d0CorrectedRunDependent_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_d0CorrectedRunDependent_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts);

  underflow(*h_bothLeptonsD0Sig_d0CorrectedPixel_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_d0CorrectedPixel_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_d0CorrectedPixel_forFittingData_removedLifetimeCuts);

  underflow(*h_bothLeptonsD0Sig_d0CorrectedIP_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_d0CorrectedIP_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_d0CorrectedIP_forFittingData_removedLifetimeCuts);

  underflow(*h_bothLeptonsD0Sig_NoCorrections_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_NoCorrections_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts);

  underflow(*h_bothLeptonsD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_signWrtPerpDilepton_d0Corrected_forFittingData_removedLifetimeCuts);

  underflow(*h_bothLeptonsD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependent_forFittingData_removedLifetimeCuts);

  underflow(*h_bothLeptonsD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts);
  underflow(*h_minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_forFittingData_removedLifetimeCuts);

  underflow(*h_minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts);
  underflow(*h_minLeptonD0Sig_signedWrtDeltaPhi_forFittingData_removedLifetimeCollCuts);
  underflow(*h_minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts);
}

void Histograms::deleteHistograms() {
  // Delete all histograms

  for ( map<TString, TH1F*>::const_iterator hist = histMap.begin(); hist != histMap.end(); hist++ ) {
    delete hist->second;
  }

  delete h_nMinus1_leptonD0Sig_vs_LxySig_finalCuts;
  delete h_l_vs_h_leptonD0Sig_removedLifetimeCuts;
  delete h_singleLeptonD0_vs_phi;
  delete h_singleLeptonD0Significance_vs_phi;
  delete h_singleLeptonD0Significance_vs_theta;
  delete h_singleLeptonD0Significance_vs_phi_vs_theta;
  delete h_singleLeptonD0SignificanceG2_vs_phi_vs_theta;
  delete h_singleLeptonD0Significance_vs_phi_vs_theta_badRun;
  delete h_singleLeptonD0Significance_vs_phi_vs_theta_noVertex;
  delete h_singleLeptonD0Significance_vs_phi_vs_theta_badRun_noVertex;
  delete h_singleLeptonD0Significance_vs_phi_vs_theta_pixel;
  delete h_singleLeptonD0Significance_vs_phi_vs_theta_noPixel;
  delete h_leptonD0SigFractionMap_all;
  delete h_leptonD0SigFractionMap_pass;
  delete h_singleLeptonD0Significance_vs_run;

  delete h_singleLeptonD0_vs_phi_vs_theta;
  delete h_singleLeptonD0_vs_phi_vs_theta_badRun;
  delete h_singleLeptonD0_vs_phi_vs_theta_noVertex;
  delete h_singleLeptonD0_vs_phi_vs_theta_badRun_noVertex;
  delete h_singleLeptonD0_vs_run;

  delete h_singleLeptonZ0_vs_phi_vs_theta;
  delete h_singleLeptonZ0_vs_phi_vs_theta_badRun;
  delete h_singleLeptonZ0_vs_phi_vs_theta_noVertex;
  delete h_singleLeptonZ0_vs_phi_vs_theta_badRun_noVertex;
  delete h_singleLeptonZ0_vs_phi_vs_theta_pixel;
  delete h_singleLeptonZ0_vs_phi_vs_theta_noPixel;
  delete h_singleLeptonZ0_vs_run;

  delete h_nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched;
  delete h_nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched;
  delete h_nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched;
  delete h_nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched;
  delete h_nMinus1_ptLeptonL_vsPU_finalCuts_genMatched;
  delete h_nMinus1_ptLeptonH_vsPU_finalCuts_genMatched;
  delete h_nMinus1_relIsolationLeptonL_vsPU_finalCollCuts_genMatched;
  delete h_nMinus1_relIsolationLeptonH_vsPU_finalCollCuts_genMatched;

  delete h_minD0SigCut_vs_LxySigCut;

  for (unsigned int i=0; i<h_trigEff_meanLifetime.size(); i++)
    delete h_trigEff_meanLifetime[i];
  for (unsigned int i=0; i<h_trigEff_meanLifetimeLog.size(); i++)
    delete h_trigEff_meanLifetimeLog[i];
}

// Adds overflow of a TH1F in the final bin of the histogram
void Histograms::overflow(TH1F &h)
{
  int  N= h.GetNbinsX();
  h.SetBinContent(N,h.GetBinContent(N)+h.GetBinContent(N+1));
  double errorN=h.GetBinError(N);
  double errorNp1=h.GetBinError(N+1);
  h.SetBinError(N, sqrt( errorN*errorN + errorNp1*errorNp1 ) );

}

// Adds underflow of a TH1F in the first bin of the histogram
void Histograms::underflow(TH1F &h)
{
  h.SetBinContent(1,h.GetBinContent(0)+h.GetBinContent(1));
  double errorN=h.GetBinError(0);
  double errorNp1=h.GetBinError(1);
  h.SetBinError(1, sqrt( errorN*errorN + errorNp1*errorNp1 ) );
}
