#ifndef Histograms_h
#define Histograms_h

//
// HISTOGRAMS
//

// This class does all the book keeping and handling of histograms

#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <TFile.h>
#include "AnalysisMacros/CommonMacros/commonTools.C"

class Histograms {
  public:
    Histograms();
    ~Histograms();

    void drawOverflows();
    void writeHistograms( TFile & outputFile );
    void deleteHistograms();

    // Histograms

    //
    // Final cuts
    //
    TH1F * h_mass_finalCuts;
    TH1F * h_mt_finalCuts;
    TH1F * h_Lxy_finalCuts;
    TH1F * h_nRecoPV_finalCuts;

    // n-1 final cuts
    TH1F * h_nMinus1_LxySig_finalCuts;
    TH1F * h_nMinus1_LxySig_removeDeltaPhi_finalCuts;
    TH1F * h_nMinus1_vertexChi2_finalCuts;
    TH1F * h_nMinus1_deltaPhi_finalCuts;
    TH1F * h_nMinus1_leptonAbsD0Sig_finalCuts;
    TH1F * h_nMinus1_leptonCaloMatchDeltaR_finalCuts;
    TH1F * h_nMinus1_leptonCaloMatchDeltaEta_finalCuts;
    TH1F * h_nMinus1_leptonCaloMatchDeltaPhi_finalCuts;
    TH1F * h_nMinus1_leptonTrackPt_finalCuts;


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

    //
    // Removed lifetime cuts
    //
    TH1F * h_mass_removedLifetimeCuts;
    TH1F * h_nRecoPV_removedLifetimeCuts;
    TH1F * h_nRecoPV_p5_removedLifetimeCuts;
    TH1F * h_nRecoPV_m5_removedLifetimeCuts;
    TH1F * h_leptonLPt_removedLifetimeCuts;
    TH1F * h_leptonHPt_removedLifetimeCuts;
    TH1F * h_leptonLEta_removedLifetimeCuts;
    TH1F * h_leptonHEta_removedLifetimeCuts;
    TH1F * h_leptonLCaloMatchDeltaR_removedLifetimeCuts;
    TH1F * h_leptonHCaloMatchDeltaR_removedLifetimeCuts;
    TH1F * h_leptonLCaloMatchDeltaEta_removedLifetimeCuts;
    TH1F * h_leptonHCaloMatchDeltaEta_removedLifetimeCuts;
    TH1F * h_leptonLCaloMatchDeltaPhi_removedLifetimeCuts;
    TH1F * h_leptonHCaloMatchDeltaPhi_removedLifetimeCuts;
    TH1F * h_LxySig_removedLifetimeCuts;
    TH1F * h_leptonAbsD0Sig_removedLifetimeCuts;

    // n-1 removed lifetime cuts
    TH1F * h_nMinus1_isolationLeptonL_removedLifetimeCuts;
    TH1F * h_nMinus1_isolationLeptonH_removedLifetimeCuts;
    TH1F * h_nMinus1_relIsolationLeptonL_removedLifetimeCuts;
    TH1F * h_nMinus1_relIsolationLeptonH_removedLifetimeCuts;


    //
    // Trigger efficiency plots
    //
    TH1F * h_trig_Lxy_all;
    TH1F * h_trig_Lxy_pass;

    TH1F * h_trig_ctau_all;
    TH1F * h_trig_ctau_pass;
};

#endif

#ifdef Histograms_h
Histograms::Histograms()
{
  // Book some histograms
  TH1::SetDefaultSumw2();

  // Final set of cuts
  h_mass_finalCuts = new TH1F("Mass_finalCuts", "Dilepton mass, final cuts", 75, 0, 500);
  h_mt_finalCuts = new TH1F("Mt_finalCuts", "Dilepton Mt, final cuts", 75, 0, 500);
  h_Lxy_finalCuts = new TH1F("Lxy_finalCuts", "Dilepton Lxy, final cuts", 100, -50, 50);
  h_nRecoPV_finalCuts = new TH1F("nRecoPV_finalCuts", "Number reco PV, final cuts", 50, 0, 50);

  // n-1 final cuts
  h_nMinus1_LxySig_finalCuts = new TH1F("nMinus1_LxySig_finalCuts", "n-1 Vertex Lxy significance, final cuts", 60, -30, 30);
  h_nMinus1_LxySig_removeDeltaPhi_finalCuts = new TH1F("nMinus1_LxySig_removeDeltaPhi_finalCuts", "n-1 Vertex Lxy significance, final cuts no deltaPhi", 60, -30, 30);
  h_nMinus1_vertexChi2_finalCuts = new TH1F("nMinus1_vertexChi2_finalCuts", "n-1 Vertex Chi^2, final cuts", 20, 0, 20);
  h_nMinus1_deltaPhi_finalCuts = new TH1F("nMinus1_deltaPhi_finalCuts", "n-1 Delta Phi, final cuts", 20, 0, 1);
  h_nMinus1_leptonAbsD0Sig_finalCuts = new TH1F("nMinus1_leptonAbsD0Sig_finalCuts", "n-1 Min Lepton D0 Significance", 20, 0, 20 );
  h_nMinus1_leptonCaloMatchDeltaR_finalCuts = new TH1F("nMinus1_leptonCaloMatchDeltaR_finalCuts","n-1 Max Lepton calo match delta R, final cuts",20,0,0.1);
  h_nMinus1_leptonCaloMatchDeltaEta_finalCuts = new TH1F("nMinus1_leptonCaloMatchDeltaEta_finalCuts","n-1 Max Lepton calo match delta Eta, final cuts",20,0,0.1);
  h_nMinus1_leptonCaloMatchDeltaPhi_finalCuts = new TH1F("nMinus1_leptonCaloMatchDeltaPhi_finalCuts","n-1 Max Lepton calo match delta Phi, final cuts",20,0,0.1);
  h_nMinus1_leptonTrackPt_finalCuts = new TH1F("nMinus1_leptonTrackPt_finalCuts","n-1 Min Lepton track pt, final cuts",100,0,150);

  // n-1 final cuts, gen matched signal only
  h_nMinus1_isolationLeptonL_finalCuts_genMatched = new TH1F("nMinus1_isolationLeptonL_finalCuts_genMatched", "n-1 Isolation low pt lepton, final cuts, gen matched signal", 80, 0, 20 );
  h_nMinus1_isolationLeptonH_finalCuts_genMatched = new TH1F("nMinus1_isolationHeptonH_finalCuts_genMatched", "n-1 Isolation high pt lepton, final cuts, gen matched signal", 80, 0, 20 );
  h_nMinus1_relIsolationLeptonL_finalCuts_genMatched = new TH1F("nMinus1_relIsolationLeptonL_finalCuts_genMatched", "n-1 Rel. Isolation low pt lepton, final cuts, gen matched signal", 20, 0, 0.2 );
  h_nMinus1_relIsolationLeptonH_finalCuts_genMatched = new TH1F("nMinus1_relIsolationHeptonH_finalCuts_genMatched", "n-1 Rel. Isolation high pt lepton, final cuts, gen matched signal", 20, 0, 0.2 );

  // Removed lifetime set of cuts
  h_mass_removedLifetimeCuts = new TH1F("Mass_removedLifetimeCuts", "Dilepton mass, removed lifetime cuts", 75, 0, 500);
  h_nRecoPV_removedLifetimeCuts = new TH1F("nRecoPV", "Number reco PV", 50, 0, 50);
  h_nRecoPV_p5_removedLifetimeCuts = new TH1F("nRecoPV_p5", "Number reco PV +5", 50, 0, 50);
  h_nRecoPV_m5_removedLifetimeCuts = new TH1F("nRecoPV_m5", "Number reco PV -5", 50, 0, 50);
  h_leptonLPt_removedLifetimeCuts = new TH1F("leptonLPt_removedLifetimeCuts", "Lepton L Pt, removed lifetime cuts",50,0,100);
  h_leptonHPt_removedLifetimeCuts = new TH1F("leptonHPt_removedLifetimeCuts", "Lepton L Pt, removed lifetime cuts",50,0,100);
  h_leptonLEta_removedLifetimeCuts = new TH1F("leptonLEta_removedLifetimeCuts", "Lepton L Eta, removed lifetime cuts",60,-3,3);
  h_leptonHEta_removedLifetimeCuts = new TH1F("leptonHEta_removedLifetimeCuts", "Lepton L Eta, removed lifetime cuts",60,3,3);
  h_leptonLCaloMatchDeltaR_removedLifetimeCuts = new TH1F("leptonLCaloMatchDeltaR_removedLifetimeCuts","Lepton L calo match delta R, removed lifetime cuts",20,0,0.1);
  h_leptonHCaloMatchDeltaR_removedLifetimeCuts = new TH1F("leptonHCaloMatchDeltaR_removedLifetimeCuts","Lepton H calo match delta R, removed lifetime cuts",20,0,0.1);
  h_leptonLCaloMatchDeltaEta_removedLifetimeCuts = new TH1F("leptonLCaloMatchDeltaEta_removedLifetimeCuts","Lepton L calo match delta Eta, removed lifetime cuts",20,0,0.1);
  h_leptonHCaloMatchDeltaEta_removedLifetimeCuts = new TH1F("leptonHCaloMatchDeltaEta_removedLifetimeCuts","Lepton H calo match delta Eta, removed lifetime cuts",20,0,0.1);
  h_leptonLCaloMatchDeltaPhi_removedLifetimeCuts = new TH1F("leptonLCaloMatchDeltaPhi_removedLifetimeCuts","Lepton L calo match delta Phi, removed lifetime cuts",20,0,0.1);
  h_leptonHCaloMatchDeltaPhi_removedLifetimeCuts = new TH1F("leptonHCaloMatchDeltaPhi_removedLifetimeCuts","Lepton H calo match delta Phi, removed lifetime cuts",20,0,0.1);
  h_LxySig_removedLifetimeCuts = new TH1F("LxySig_removedLifetimeCuts","Lxy/sigma removed lifetime cuts",100,-30,30);
  h_leptonAbsD0Sig_removedLifetimeCuts = new TH1F("leptonAbsD0Sig_removedLifetimeCuts","Min Lepton D0 Significance removed lifetime cuts",20,0,5);

  // n-1 removed lifetime cuts
  h_nMinus1_isolationLeptonL_removedLifetimeCuts = new TH1F("nMinus1_isolationLeptonL_removedLifetimeCuts", "Sum pt isolation cone, low pt lepton", 80, 0, 20 );
  h_nMinus1_isolationLeptonH_removedLifetimeCuts = new TH1F("nMinus1_isolationLeptonH_removedLifetimeCuts", "Sum pt isolation cone, high pt lepton", 80, 0, 20 );
  h_nMinus1_relIsolationLeptonL_removedLifetimeCuts = new TH1F("nMinus1_relIsolationLeptonL_removedLifetimeCuts", "Rel isolation cone, low pt lepton", 20, 0, 0.2 );
  h_nMinus1_relIsolationLeptonH_removedLifetimeCuts = new TH1F("nMinus1_relIsolationLeptonH_removedLifetimeCuts", "Rel isolation cone, high pt lepton", 20, 0, 0.2 );

  // PU dependence
  h_nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched = new TH2F("nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched", "Sum pt isolation cone vsPU, low pt lepton", 80, 0, 20, 50, 0, 50 );
  h_nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched = new TH2F("nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched", "Sum pt isolation cone vsPU, high pt lepton", 80, 0, 20, 50, 0, 50 );
  h_nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched = new TH2F("nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched", "Rel isolation cone vsPU, low pt lepton", 20, 0, 0.2, 50, 0, 50 );
  h_nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched = new TH2F("nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched", "Rel isolation cone vsPU, high pt lepton", 20, 0, 0.2, 50, 0, 50 );


  // Trigger efficiency plots
  h_trig_Lxy_all = new TH1F("trig_Lxy_all", "Lxy of all exotics", 20, 0, 200 );
  h_trig_Lxy_pass = new TH1F("trig_Lxy_pass", "Lxy of triggered exotics", 20, 0, 200 );

  h_trig_ctau_all = new TH1F("trig_ctau_all", "Ctau of all exotics", 100, 0.01, 1000 );
  h_trig_ctau_pass = new TH1F("trig_ctau_pass", "Ctau of triggered exotics", 100, 0.01, 1000 );

}

Histograms::~Histograms()
{
}
#endif
