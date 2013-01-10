void makeWidthFits(void) {
  const int n = 4;
  const float x[n] = {20.0, 50.0, 150.0, 350.0};
  const float ex[n] = {0, 0, 0, 0};

  //ele41
  //const float w[n] = {0.58722, 0.86486, 1.34342, 3.11314};
  //const float ew[n] = {0.0101, 0.00943, 0.01456, 0.04668};
  
  //ele41 -- May23 update with new mass resolution increase from Z'
  const float w[n] = {0.64831, 1.0696, 2.13568, 5.04026};
  const float ew[n] = {0.01162, 0.01381, 0.02226, 0.07463};
  
  //mu33
  // const float w[n] = {0.66572, 2.52846, 6.82108, 15.51586};
  // const float ew[n] = {0.02161, 0.02543, 0.06022, 0.12777};

  TGraphErrors *g = new TGraphErrors(n, x, w, ex, ew);
  g->Draw("ALP");
  g->Fit("pol2");

  TCanvas *c2 = new TCanvas("c2", "c2");

  TGraph *ge = new TGraph(n, x, ew);
  ge->Draw("ALP");
  ge->Fit("pol2");
}
