// this determines the two possible ways of determining the
// resolution.  if false, only the nominal resolution and its error
// will be used.  if true, the resolution will be the mean of all
// values and the error will be determined by the SD of all values.

const bool useAllResolutions = false;

void makeWidthFitsResolution(void) {
  const int nmass = 4;
  const int nlife = 21*3;
  const float x[nmass] = {20.0, 50.0, 150.0, 350.0};
  const float ex[nmass] = {0, 0, 0, 0};

  float w_e[nmass];
  float ew_e[nmass];
  float w_mu[nmass];
  float ew_mu[nmass];

  ifstream ifile("/afs/cern.ch/work/p/plujan/public/DisplacedFermions/AnalysisMacros/DileptonMacros/SignalMassResolutionFiles/massResolutions.txt");

  int massesObtained = 0;
  while (massesObtained < 4 && !ifile.eof()) {
    float sum_e = 0;
    float sum2_e = 0;
    float sum_mu = 0;
    float sum2_mu = 0;
    float nominal_res_e, nominal_err_e, nominal_res_mu, nominal_err_mu;
    int pdg;
    float ctau, fact, res_mu, err_mu, res_e, err_e;
    char junk[512];
    ifile.getline(junk, 512); // masses line

    if (strncmp(junk, "Chi0", 4) == 0) {
      // skip this one
      ifile.getline(junk, 512); // header line
      ifile.getline(junk, 512); // blank line
      continue;
    } else if (strncmp(junk, "HTo2LongLived", 13) == 0) {
      // something we want, let's parse it
      int mh, mx, args;
      args = sscanf(junk, "HTo2LongLivedTo4F_MH%d_MFF%d", &mh, &mx);
      if (args < 2) {
	std::cout << "Failed to extract mh and mx from " << junk << std::endl;
	for (int i=0; i<nlife+2; i++) ifile.getline(junk, 512);
	continue;
      }

      if (mh != 1000) {
	// not interested, skip it
	for (int i=0; i<nlife+2; i++) ifile.getline(junk, 512);
	continue;
      }

      std::cout << "Found MH=" << mh << " and MX=" << mx << std::endl;
      // figure out which one it is
      int imass = -1;
      for (int i=0; i<nmass; i++) {
	if (mx == x[i])
	  imass = i;
      }
      if (imass == -1)
	std::cout << "Couldn't find MX=" << mx << " in mass array" << std::endl;

    } else {
      std::cout << "Failed to parse header line " << junk << std::endl;
      continue;
    }

    ifile.getline(junk, 512); // header line
    
    for (int j=0; j<nlife; j++) {
      ifile >> pdg >> ctau >> fact >> res_mu >> err_mu >> res_e >> err_e;

      // std::cout << "j=" << j << " Got " << ctau << " " << res_mu << " " << res_e << std::endl;

      if (fabs(fact-1)<0.001 && pdg == 6002113) {
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

    std::cout << "mass " << x[imass] << " e= " << mean_e << " +/- " << sigma_e
	      << " mu= " << mean_mu << " +/- " << sigma_mu << std::endl;

    w_e[imass] = mean_e;
    ew_e[imass] = sigma_e;
    w_mu[imass] = mean_mu;
    ew_mu[imass] = sigma_mu;

    massesObtained++;
  }
  TCanvas *c1 = new TCanvas("c1", "c1", 800, 400);
  c1->Divide(2,1);
  c1->cd(1);
  TGraphErrors *g_e = new TGraphErrors(nmass, x, w_e, ex, ew_e);
  g_e->Draw("ALP");
  g_e->SetTitle("Resolution, electrons");
  g_e->Fit("pol2");

  c1->cd(2);
  TGraph *ge_e = new TGraph(nmass, x, ew_e);
  ge_e->Draw("ALP");
  ge_e->SetTitle("Resolution uncertainty, electrons");
  ge_e->Fit("pol2");

  TCanvas *c2 = new TCanvas("c2", "c2", 800, 400);
  c2->Divide(2,1);
  c2->cd(1);
  TGraphErrors *g_mu = new TGraphErrors(nmass, x, w_mu, ex, ew_mu);
  g_mu->Draw("ALP");
  g_mu->SetTitle("Resolution, muons");
  g_mu->Fit("pol2");

  c2->cd(2);
  TGraph *ge_mu = new TGraph(nmass, x, ew_mu);
  ge_mu->Draw("ALP");
  ge_mu->SetTitle("Resolution uncertainty, muons");
  ge_mu->Fit("pol1");
}
