// this determines the two possible ways of determining the
// resolution.  if false, only the nominal resolution and its error
// will be used.  if true, the resolution will be the mean of all
// values and the error will be determined by the SD of all values.

const bool useAllResolutions = false;

void makeWidthFitsResolution(void) {
  const int nmass = 4;
  const int nlife = 11;
  const float x[nmass] = {20.0, 50.0, 150.0, 350.0};
  const float ex[nmass] = {0, 0, 0, 0};

  float w_e[nmass];
  float ew_e[nmass];
  float w_mu[nmass];
  float ew_mu[nmass];

  ifstream ifile("massResolutions");

  for (int i=0; i<nmass; i++) {
    float sum_e = 0;
    float sum2_e = 0;
    float sum_mu = 0;
    float sum2_mu = 0;
    float nominal_res_e, nominal_err_e, nominal_res_mu, nominal_err_mu;
    float ctau, fact, res_mu, err_mu, res_e, err_e;
    char junk[512];
    ifile.getline(junk, 512); // masses line
    ifile.getline(junk, 512); // header line
    
    for (int j=0; j<nlife; j++) {
      ifile >> ctau >> fact >> res_mu >> err_mu >> res_e >> err_e;

      //std::cout << "Got " << ctau << " " << res_mu << " " << res_e << std::endl;

      if (fabs(fact-1)<0.001) {
	nominal_res_e = res_e;
	nominal_err_e = err_e;
	nominal_res_mu = res_mu;
	nominal_err_mu = err_mu;
      }
      
      sum_e += res_e;
      sum2_e += res_e*res_e;
      
      sum_mu += res_mu;
      sum2_mu += res_mu*res_mu;
    }
    ifile.getline(junk, 512); // blank line
    ifile.getline(junk, 512);

    float mean_e, sigma_e, mean_mu, sigma_mu;

    if (useAllResolutions) {
      mean_e = sum_e/nlife;
      sigma_e = sqrt(sum2_e/nlife - mean_e*mean_e);
      
      mean_mu = sum_mu/nlife;
      sigma_mu = sqrt(sum2_mu/nlife - mean_mu*mean_mu);
    } else {
      mean_e = nominal_res_e;
      sigma_e = nominal_err_e;

      mean_mu = nominal_res_mu;
      sigma_mu = nominal_err_mu;
    }

    std::cout << "mass " << x[i] << " e= " << mean_e << " +/- " << sigma_e
	      << " mu= " << mean_mu << " +/- " << sigma_mu << std::endl;

    w_e[i] = mean_e;
    ew_e[i] = sigma_e;
    w_mu[i] = mean_mu;
    ew_mu[i] = sigma_mu;
  }
  TCanvas *c1 = new TCanvas("c1", "c1", 800, 400);
  c1->Divide(2,1);
  c1->cd(1);
  TGraphErrors *g_e = new TGraphErrors(nmass, x, w_e, ex, ew_e);
  g_e->Draw("ALP");
  g_e->Fit("pol2");

  c1->cd(2);
  TGraph *ge_e = new TGraph(nmass, x, ew_e);
  ge_e->Draw("ALP");
  ge_e->Fit("pol2");

  TCanvas *c2 = new TCanvas("c2", "c2", 800, 400);
  c2->Divide(2,1);
  c2->cd(1);
  TGraphErrors *g_mu = new TGraphErrors(nmass, x, w_mu, ex, ew_mu);
  g_mu->Draw("ALP");
  g_mu->Fit("pol2");

  c2->cd(2);
  TGraph *ge_mu = new TGraph(nmass, x, ew_mu);
  ge_mu->Draw("ALP");
  ge_mu->Fit("pol2");
}
