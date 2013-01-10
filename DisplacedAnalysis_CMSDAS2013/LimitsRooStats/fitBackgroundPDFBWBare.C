void fitBackgroundPDFBWWinter(void) {
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  const char *name[1] = {"muon"};

  // Some fixes to the TDR style
		   
  //gStyle->SetOptStat(0);
  //gStyle->SetOptFit(0);
  gStyle->SetOptTitle(1);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFont(62);

  char buf[32];
  for (int i=0; i<1; i++) {
    // Now it's binned fits, all the time!
    TFile *infile = new TFile("WinterSelection/masses_backgroundMC_muon_noLifetimeCuts_rebin.root");
    TH1F *h = (TH1F*)infile->Get("mass");
    h->Rebin(5);

    sprintf(buf, "c%d", i);
    TCanvas *c = new TCanvas(buf, "Background fit", 600, 600);
    h->Draw();
    gPad->SetTopMargin(0.08);
    gPad->SetLogy();
    char title[512];
    h->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    h->GetXaxis()->SetRangeUser(20,500);
    h->GetYaxis()->SetTitle("Number of events");
    sprintf(title, "Masses for background MC, %s events", name[i]);
    h->SetTitle(title);
    sprintf(buf, "f%d", i);

    // Pick one version here. The top applies the turnon to only the 1/m^4 component.
    // The bottom applies the turnon to both components and includes a floor (which does not work very well at the moment).
    
    //TF1 *f = new TF1(buf, "[0]*(1/((x*x-[1]*[1])*(x*x-[1]*[1]) + [1]*[1]*[2]*[2]) + [3]*(TMath::Erf((x-[4])/[5])+1)/(x*x*x*x))");
    //f->SetParNames("Norm", "BWMean", "BWWidth", "C", "TurnOn", "TurnOnWidth");

    TF1 *f = new TF1(buf, "[0]*((TMath::Erf((x-[4])/[5])+[6])/(1+[6]))*(1/((x*x-[1]*[1])*(x*x-[1]*[1]) + [1]*[1]*[2]*[2]) + [3]/(x*x*x*x))");
    f->SetParNames("Norm", "BWMean", "BWWidth", "C", "TurnOn", "TurnOnWidth", "TurnOnFloor");

    f->SetParameter(0, 1e12);
    f->SetParameter(1, 90);
    f->SetParameter(2, 5);
    f->SetParameter(3, 0.05);
    f->SetParLimits(3, 0, 1);
    f->SetParameter(4, 90);
    f->SetParLimits(4, 10, 170);
    f->SetParameter(5, 15);

    //for the 2nd version above
    f->SetParameter(4, 20);
    f->SetParLimits(4, -10, 210);
    f->SetParLimits(5, 0, 50);
    f->SetParameter(6, 1.02);
    f->SetParLimits(6, 0, 2);

    //h->Fit(f, "WLL EI", "", 20, 500); // can also use chi2 by removing the LE
    h->Fit(f, "W", "", 20, 500); // the 'W' option sets all weights to 1
    sprintf(title, "BackgroundPDF_%s_BareRoot_Unweighted.png", name[i]);
    c->Print(title);
  }
}
