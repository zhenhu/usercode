// Make the background fits.

const bool isPAS = false; // adds "preliminary", now largely obsolete
const int nFiles = 6;
const char *fileTag[nFiles] = {"electron_pt36", "electron_pt41", "electron_pt46",
			       "muon_pt26", "muon_pt33", "muon_unsmeared"};
//updated numbers -- but only for ele_pt41 and mu_pt33
const float lumi[nFiles] = {1.1, 4.1, 4.7, 2.0, 5.1, 5.1};
const float startingFitParameters[nFiles][3][4] = {
  {{35, 0.4, 2, 3},  {35, 0.4, 2, 3},  {35, 0.4, 2, 3}},
  {{250, 0.3, 4, 6}, {7000, 0.07, 7, 3}, {15, 0.6, 7, 3.6}},
  {{20, 0.6, 0.1, 10}, {20, 0.6, 0.1, 10}, {20, 0.6, 0.1, 10}},
  {{1276, 0.3, 64.7, 0.74}, {1276, 0.3, 64.7, 0.74}, {1276, 0.3, 64.7, 0.74}},
  {{1700, 0.32, 50, 0.7}, {1700, 0.31, 76, 0.7}, {900, 0.5, 0, 1}},
  {{1700, 0.32, 50, 0.7}, {1700, 0.31, 76, 0.7}, {900, 0.5, 0, 1}},
};

// which ones to actually use
const int nplots = 2;
const int whichplots[nplots] = {1, 4};

const float lxyCutEle = 8.0;   // lxy/sigma cut for electron channel
const float lxyCutMu = 5.0;    // same for muon channel
const float lxyMax = 20.0;     // maximum lxy/sigma value to use in fits

void plotSingleBackground(TFile *f, float xfit, float xcut, bool isMu, int which, int whichParams, bool useMC = true) {
  TH1F *h;
  if (useMC)
    hi = (TH1F*)f->Get("decayLengthSignificance2D_BackgroundMC");
  else
    hi = (TH1F*)f->Get("decayLengthSignificance2D");

  char namebuf[32];
  sprintf(namebuf, "h-%d%d", which, whichParams);
  h = (TH1F*)hi->Clone(namebuf);
  
  h->SetMarkerColor(kBlack);
  h->SetMarkerStyle(kFullSquare);

  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.10);
  gPad->SetRightMargin(0.04);

  h->GetXaxis()->SetTitle("L_{xy}/#sigma");
  h->GetYaxis()->SetTitle("Number of background events");
  h->GetYaxis()->SetTitleOffset(1.2);
  h->Draw();
  gPad->SetLogy();
  
  float xmax = h->GetXaxis()->GetXmax();
  float ymax = h->GetMaximum();

  sprintf(namebuf, "f1-%d%d", which, whichParams);
  TF1 *f1 = new TF1(namebuf, "[0]*exp(-x/[1]) + [2]*exp(-x/[3])");
  for (int i=0; i<4; i++)
    f1->SetParameter(i, startingFitParameters[which][whichParams][i]);
  if (which == 4) { // && whichParams == 2
    f1->FixParameter(2, 0);
    f1->FixParameter(3, 1);
  }

  float fitmin = 0;
  //if (!isMu) fitmin = 3;
  h->Fit(f1, "LLE", "", fitmin, xfit);

  f1->SetLineColor(kRed);

  sprintf(namebuf, "f2-%d%d", which, whichParams);
  TF1 *f2 = new TF1(namebuf, "[0]*exp(-x/[1]) + [2]*exp(-x/[3])", xfit, xmax);
  for (int i=0; i<=3; i++)
    f2->SetParameter(i, f1->GetParameter(i));
  f2->SetLineColor(kRed);
  f2->SetLineStyle(kDashed);
  f2->Draw("same");
  
  if (!isMu) {
    TLine *l1 = new TLine(xfit, h->GetMinimum(), xfit, ymax);
    l1->SetLineColor(kRed);
    l1->SetLineWidth(2);
    l1->SetLineStyle(kDashed);
    //l1->Draw();
  }

  TLine *l2 = new TLine(xcut, h->GetMinimum(), xcut, ymax);
  l2->SetLineColor(kBlue);
  l2->SetLineWidth(2);
  l2->SetLineStyle(kDashed);
  l2->Draw();

  TArrow *a2 = new TArrow(xcut, ymax/50, xcut+2, ymax/50, 0.02, "|>");
  a2->SetLineWidth(2);
  a2->SetLineColor(kBlue);
  a2->SetFillColor(kBlue);
  a2->Draw();
  TText *at2 = new TText(xcut+2.5, ymax/50, "Signal region");
  at2->SetTextSize(0.05);
  at2->SetTextColor(kBlue);
  at2->SetTextAlign(12);
  at2->SetTextFont(42);
  at2->Draw();

  TLatex *t1;
  char buf[512];
  if (useMC) {
    sprintf(buf, "CMS Simulation #sqrt{s}=7 TeV", lumi[which]);
  } else {
    if (isPAS)
      sprintf(buf, "CMS Preliminary #sqrt{s}=7 TeV L=%.1f fb^{-1}", lumi[which]);
    else
      sprintf(buf, "CMS #sqrt{s}=7 TeV L=%.1f fb^{-1}", lumi[which]);
  }
  h->SetTitle(buf);
  if (isMu) {
    t1 = new TLatex(xmax-4, ymax/5, "#mu^{+}#mu^{-}");
  } else {
    t1 = new TLatex(xmax-4, ymax/5, "e^{+}e^{-}");
  }
  t1->SetTextFont(42);
  t1->SetTextSize(0.05);
  t1->Draw();

  float intbkgnd = f2->Integral(xcut, xmax);

  sprintf(namebuf, "f3-%d%d", which, whichParams);
  std::cout << namebuf << std::endl;
  TF1 *f3 = f2->Clone(namebuf);
  float interr2 = 0;
  float errplus2 = 0;
  float errminus2 = 0;
  for (int i=0; i<4; i++) {
    f3->SetParameter(i, f1->GetParameter(i)+f1->GetParError(i));
    float intplus = f3->Integral(xcut, xmax);
    f3->SetParameter(i, f1->GetParameter(i)-f1->GetParError(i));
    float intminus = f3->Integral(xcut, xmax);
    f3->SetParameter(i, f1->GetParameter(i));
    float interr = (intplus - intminus)/2;
    interr2 += interr*interr;
    errplus2 += (intplus - intbkgnd)*(intplus - intbkgnd);
    errminus2 += (intbkgnd - intminus)*(intbkgnd - intminus);
  }  
  //std::cout << intplus << " " << intminus << std::endl;
  // float interr = (intplus - intminus)/2;
  float interr = sqrt(interr2);
  float errplus = sqrt(errplus2);
  float errminus = sqrt(errminus2);

  std::cout << "Integral from " << xcut << " to " << xmax << " = " << intbkgnd
	    << " + " << errplus << " - " << errminus
	    << " (+/- " << interr << ")" << std::endl;
}

void makeBackgroundFits(void) {
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  // Some fixes to the TDR style
		   
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetOptTitle(1);
  gStyle->SetTitleBorderSize(0);
  // keep all axis & pad titles non-bold
  gStyle->SetTitleFont(42, "");
  gStyle->SetTitleFont(42, "X");
  gStyle->SetTitleFont(42, "Y");
  gStyle->SetTitleX(0.5);
  gStyle->SetTitleAlign(23);

  char shortbuf[32];
  char buf[512];

  for (int j=0; j<nplots; j++) {
    int i=whichplots[j];
    int isElectron = 0;
    if (strncmp("ele", fileTag[i], strlen("ele")) == 0) isElectron = 1;
    sprintf(buf, "/afs/cern.ch/user/p/plujan/public/displacedfermions/trunk/LimitsRooStats/WinterSelection/di%s_decayLengthSignificance2D.root",
	    (i==5) ? "muon_unsmeared" : isElectron ? "electron" : "muon");

    TFile *f = new TFile(buf);

    sprintf(shortbuf, "c1-%d", i);
    sprintf(buf, "Background fit for %s, MC, background region", fileTag[i]);
    TCanvas *c1 = new TCanvas(shortbuf, buf, 600, 600);
    if (isElectron)
      plotSingleBackground(f, lxyCutEle, lxyCutEle, false, i, 0);
    else
      plotSingleBackground(f, lxyCutMu, lxyCutMu, true, i, 0);
    
    sprintf(shortbuf, "c2-%d", i);
    sprintf(buf, "Background fit for %s, MC, all regions", fileTag[i]);
    TCanvas *c2 = new TCanvas(shortbuf, buf, 600, 600);
    if (isElectron)
      plotSingleBackground(f, lxyMax, lxyCutEle, false, i, 1);
    else
      plotSingleBackground(f, lxyMax, lxyCutMu, true, i, 1);

    sprintf(shortbuf, "c3-%d", i);
    sprintf(buf, "Background fit for %s, data, background region", fileTag[i]);
    TCanvas *c3 = new TCanvas(shortbuf, buf, 600, 600);
    if (isElectron)
      plotSingleBackground(f, lxyCutEle, lxyCutEle, false, i, 2, false);
    else
      plotSingleBackground(f, lxyCutMu, lxyCutMu, true, i, 2, false);

    if (isPAS) {
      sprintf(buf, "BackgroundFit_MCAll_%s_PAS.png", fileTag[i]);
      c2->Print(buf);
      sprintf(buf, "BackgroundFit_MCAll_%s_PAS.pdf", fileTag[i]);
      c2->Print(buf);
    } else {
      sprintf(buf, "BackgroundFit_MCBkg_%s.png", fileTag[i]);
      //c1->Print(buf);
      sprintf(buf, "BackgroundFit_MCBkg_%s.pdf", fileTag[i]);
      //c1->Print(buf);
      sprintf(buf, "BackgroundFit_MCAll_%s.png", fileTag[i]);
      c2->Print(buf);
      sprintf(buf, "BackgroundFit_MCAll_%s.pdf", fileTag[i]);
      c2->Print(buf);
      sprintf(buf, "BackgroundFit_DataBkg_%s.png", fileTag[i]);
      //c3->Print(buf);
      sprintf(buf, "BackgroundFit_DataBkg_%s.pdf", fileTag[i]);
      //c3->Print(buf);
    }
  }
}
