#define Histograms_cxx

#include "Histograms.h"

void Histograms::writeHistograms( TFile & outputFile ) {
  outputFile.cd();

  // Write to file
  h_mass_finalCuts->Write();
  h_mt_finalCuts->Write();
  h_Lxy_finalCuts->Write();
  h_nRecoPV_finalCuts->Write();

  h_nMinus1_LxySig_finalCuts->Write();
  h_nMinus1_LxySig_removeDeltaPhi_finalCuts->Write();
  h_nMinus1_vertexChi2_finalCuts->Write();
  h_nMinus1_deltaPhi_finalCuts->Write();
  h_nMinus1_leptonAbsD0Sig_finalCuts->Write();
  h_nMinus1_isolationLeptonL_finalCuts_genMatched->Write();
  h_nMinus1_isolationLeptonH_finalCuts_genMatched->Write();
  h_nMinus1_relIsolationLeptonL_finalCuts_genMatched->Write();
  h_nMinus1_relIsolationLeptonH_finalCuts_genMatched->Write();
  h_nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched->Write();
  h_nMinus1_leptonCaloMatchDeltaR_finalCuts->Write();
  h_nMinus1_leptonCaloMatchDeltaEta_finalCuts->Write();
  h_nMinus1_leptonCaloMatchDeltaPhi_finalCuts->Write();
  h_nMinus1_leptonTrackPt_finalCuts->Write();

  h_mass_removedLifetimeCuts->Write();
  h_nRecoPV_removedLifetimeCuts->Write();
  h_nRecoPV_p5_removedLifetimeCuts->Write();
  h_nRecoPV_m5_removedLifetimeCuts->Write();
  h_leptonLPt_removedLifetimeCuts->Write();
  h_leptonHPt_removedLifetimeCuts->Write();
  h_leptonLEta_removedLifetimeCuts->Write();
  h_leptonHEta_removedLifetimeCuts->Write();
  h_leptonLCaloMatchDeltaR_removedLifetimeCuts->Write();
  h_leptonHCaloMatchDeltaR_removedLifetimeCuts->Write();
  h_LxySig_removedLifetimeCuts->Write();
  h_leptonAbsD0Sig_removedLifetimeCuts->Write();

  h_nMinus1_isolationLeptonL_removedLifetimeCuts->Write();
  h_nMinus1_isolationLeptonH_removedLifetimeCuts->Write();
  h_nMinus1_relIsolationLeptonL_removedLifetimeCuts->Write();
  h_nMinus1_relIsolationLeptonH_removedLifetimeCuts->Write();

  h_trig_Lxy_all->Write();
  h_trig_Lxy_pass->Write();

  h_trig_ctau_all->Write();
  h_trig_ctau_pass->Write();
}

void Histograms::drawOverflows() {
  // Draw overflow in final bin
  // Example of function in commonTools.C
  overflow(*h_mass_finalCuts);
  overflow(*h_mt_finalCuts);
  overflow(*h_Lxy_finalCuts);
  overflow(*h_nRecoPV_finalCuts);
  overflow(*h_nRecoPV_p5_removedLifetimeCuts);
  overflow(*h_nRecoPV_m5_removedLifetimeCuts);
  overflow(*h_nMinus1_LxySig_finalCuts);
  overflow(*h_nMinus1_LxySig_removeDeltaPhi_finalCuts);
  overflow(*h_nMinus1_vertexChi2_finalCuts);
  overflow(*h_nMinus1_deltaPhi_finalCuts);
  overflow(*h_nMinus1_leptonAbsD0Sig_finalCuts);
  overflow(*h_nMinus1_isolationLeptonL_finalCuts_genMatched);
  overflow(*h_nMinus1_isolationLeptonH_finalCuts_genMatched);
  overflow(*h_nMinus1_relIsolationLeptonL_finalCuts_genMatched);
  overflow(*h_nMinus1_relIsolationLeptonH_finalCuts_genMatched);
  overflow(*h_nMinus1_leptonCaloMatchDeltaR_finalCuts);
  overflow(*h_nMinus1_leptonCaloMatchDeltaEta_finalCuts);
  overflow(*h_nMinus1_leptonCaloMatchDeltaPhi_finalCuts);
  overflow(*h_nMinus1_leptonTrackPt_finalCuts);
  overflow(*h_LxySig_removedLifetimeCuts);
  overflow(*h_leptonAbsD0Sig_removedLifetimeCuts);
  overflow(*h_mass_removedLifetimeCuts);
  overflow(*h_nMinus1_isolationLeptonL_removedLifetimeCuts);
  overflow(*h_nMinus1_isolationLeptonH_removedLifetimeCuts);
  overflow(*h_nMinus1_relIsolationLeptonL_removedLifetimeCuts);
  overflow(*h_nMinus1_relIsolationLeptonH_removedLifetimeCuts);
  overflow(*h_nRecoPV_removedLifetimeCuts);
  overflow(*h_leptonLPt_removedLifetimeCuts);
  overflow(*h_leptonHPt_removedLifetimeCuts);
  overflow(*h_leptonLEta_removedLifetimeCuts);
  overflow(*h_leptonHEta_removedLifetimeCuts);
  overflow(*h_leptonLCaloMatchDeltaR_removedLifetimeCuts);
  overflow(*h_leptonHCaloMatchDeltaR_removedLifetimeCuts);
  overflow(*h_trig_Lxy_all);
  overflow(*h_trig_Lxy_pass);
  overflow(*h_trig_ctau_all);
  overflow(*h_trig_ctau_pass);
}

void Histograms::deleteHistograms() {
  // Delete all histograms

  delete h_mass_finalCuts;
  delete h_mt_finalCuts;
  delete h_Lxy_finalCuts;
  delete h_nRecoPV_finalCuts;
  delete h_nMinus1_LxySig_finalCuts;
  delete h_nMinus1_LxySig_removeDeltaPhi_finalCuts;
  delete h_nMinus1_vertexChi2_finalCuts;
  delete h_nMinus1_deltaPhi_finalCuts;
  delete h_nMinus1_leptonAbsD0Sig_finalCuts;
  delete h_nMinus1_isolationLeptonL_finalCuts_genMatched;
  delete h_nMinus1_isolationLeptonH_finalCuts_genMatched;
  delete h_nMinus1_relIsolationLeptonL_finalCuts_genMatched;
  delete h_nMinus1_relIsolationLeptonH_finalCuts_genMatched;
  delete h_nMinus1_leptonCaloMatchDeltaR_finalCuts;
  delete h_nMinus1_leptonCaloMatchDeltaEta_finalCuts;
  delete h_nMinus1_leptonCaloMatchDeltaPhi_finalCuts;
  delete h_LxySig_removedLifetimeCuts;
  delete h_leptonAbsD0Sig_removedLifetimeCuts;
  delete h_mass_removedLifetimeCuts;
  delete h_nMinus1_isolationLeptonL_removedLifetimeCuts;
  delete h_nMinus1_isolationLeptonH_removedLifetimeCuts;
  delete h_nMinus1_relIsolationLeptonL_removedLifetimeCuts;
  delete h_nMinus1_relIsolationLeptonH_removedLifetimeCuts;
  delete h_nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched;
  delete h_nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched;
  delete h_nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched;
  delete h_nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched;
  delete h_nMinus1_leptonTrackPt_finalCuts;
  delete h_nRecoPV_removedLifetimeCuts;
  delete h_nRecoPV_p5_removedLifetimeCuts;
  delete h_nRecoPV_m5_removedLifetimeCuts;
  delete h_leptonLPt_removedLifetimeCuts;
  delete h_leptonHPt_removedLifetimeCuts;
  delete h_leptonLEta_removedLifetimeCuts;
  delete h_leptonHEta_removedLifetimeCuts;
  delete h_leptonLCaloMatchDeltaR_removedLifetimeCuts;
  delete h_leptonHCaloMatchDeltaR_removedLifetimeCuts;
  delete h_trig_Lxy_all;
  delete h_trig_Lxy_pass;

  delete h_trig_ctau_all;
  delete h_trig_ctau_pass;

}


