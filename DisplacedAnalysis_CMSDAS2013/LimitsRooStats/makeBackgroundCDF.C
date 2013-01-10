//#include <TROOT.h>
//#include <TChain.h>
//#include <TFile.h>
//#include <TCanvas.h>
//#include <TH1F.h>
//#include <TH2F.h>
//#include <TTree.h>
//#include <TGraph.h>

gSystem->Load("libRooFit");
gSystem->Load("libRooFitCore");

const float lumiEle = 4.1;
const float lumiMu = 5.1;

const float normFactor = 4.0;
const float normFactorBkgnd = 1.4;

using namespace RooFit;

void makeBackgroundCDF(void)
{
  //input parameters
  float lowBound=20; // was 50
  float highBound=1000;// was 200
  float rebinFactor=2; // was 2
  float scaleFactor=1; // was not used
  bool isLog = true;
  
  // Select here!
  
  bool isMu = false;
  bool isData = true;
  bool isLoose1 = true; // false for loose_2
  bool isPrompt = true; // set for prompt; overrides the above

  // isPaper & isPAS no longer used -- the plot script now automatically
  // makes all versions in one pass
  
  std::string selection = isLoose1 ? "loose_1" : "loose_2";
  std::string lepTag = isMu ? "mu" : "elec";
  if (isPrompt) {
    lepTag = isMu ? "muon" : "electron";
    selection = "_noLifetimeCuts";
  }
  std::string typeTag = isData ? "data" : "backgroundMC";

  std::string filePrompt = "WinterSelection/masses_data_electron_noLifetimeCuts_rebin.root";
  std::string fileResults = "WinterSelection/masses_data_electron_rebin.root";

  gROOT->ProcessLine(".L ./tdrstyle.C");
  setTDRStyle();
  gStyle->SetOptFit(1);
  // keep all axis & pad titles non-bold
  gStyle->SetTitleFont(42, "");
  gStyle->SetTitleFont(42, "X");
  gStyle->SetTitleFont(42, "Y");
  gStyle->SetTitleX(0.5);
  gStyle->SetTitleAlign(23);
  
  TFile* file_data =  new TFile(filePrompt.c_str(), "READ");
  TH1D* prompt_hist = (TH1D*) file_data->Get("mass");
  prompt_hist->Sumw2();
  prompt_hist->Rebin(rebinFactor);
  prompt_hist->Scale(normFactorBkgnd/prompt_hist->Integral());

  TFile *file2 = new TFile(fileResults.c_str(), "READ");
  TH1D *data_hist = (TH1D*)file2->Get("mass");

  // skip this noise
  // RooRealVar weight("weight", "weight", 0, 50);
  // RooRealVar lxySig("lxySig", "lxySig", 0, 100);
  // RooDataSet *data_unbinned_tmp = RooDataSet::read(fileNameTxt.c_str(), RooArgList(Mass, lxySig, weight));
  // RooDataSet *data_unbinned = new RooDataSet("points", data_unbinned_tmp->GetTitle(), data_unbinned_tmp,
  //					     RooArgList(Mass, weight), NULL, weight.GetName());

  // I am sure that there is a better way to do this but at the moment let's just keep it simple.

  TH1D *prompt_cdf = new TH1D("prompt_cdf", "prompt_cdf", prompt_hist->GetXaxis()->GetNbins(), prompt_hist->GetXaxis()->GetBinLowEdge(1), 
			    prompt_hist->GetXaxis()->GetBinUpEdge(prompt_hist->GetXaxis()->GetNbins()));
  TH1D *data_cdf = new TH1D("data_cdf", "data_cdf", data_hist->GetXaxis()->GetNbins(), data_hist->GetXaxis()->GetBinLowEdge(1), 
			    data_hist->GetXaxis()->GetBinUpEdge(data_hist->GetXaxis()->GetNbins()));

  double cumulative_total = 0;
  for (int i=prompt_hist->GetXaxis()->GetNbins(); i>=1; i--) {
    cumulative_total += prompt_hist->GetBinContent(i);
    prompt_cdf->SetBinContent(i, cumulative_total);
  }

  cumulative_total = 0;
  for (int i=data_hist->GetXaxis()->GetNbins(); i>=1; i--) {
    cumulative_total += data_hist->GetBinContent(i);
    data_cdf->SetBinContent(i, cumulative_total);
  }


  tdrStyle->UseCurrentStyle();
  setTDRStyle();
  tdrStyle->cd();

  data_cdf->SetLineColor(kRed);
  data_cdf->SetLineWidth(2);
  prompt_cdf->SetLineColor(kBlue);
  prompt_cdf->SetLineWidth(2);
  prompt_cdf->GetXaxis()->SetTitle("Dilepton mass (GeV/c^{2})");
  prompt_cdf->GetYaxis()->SetTitle("Cumulative number of events");

  TString cname = Form("fit");
  TCanvas* c1 = new TCanvas(cname,cname,500,500);
  //data_hist->Draw();
  //data_hist->SetMaximum(2*normFactor);
  //data_cdf->Draw("same");

  prompt_cdf->Draw();
  prompt_cdf->SetMaximum(2*normFactor);
  data_cdf->Draw("same");

  gPad->SetLogy();

  gPad->SetTopMargin(0.12);
  gPad->SetRightMargin(0.05);

  TLegend *leg = new TLegend(0.35, 0.60, 0.90, 0.70);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->AddEntry(data_cdf, "Events observed in data", "L");
  leg->AddEntry(prompt_cdf, "Background distribution (prompt data)", "L");
  leg->Draw();

  // Conveniently, we no longer need to generate quite as many versions as previously.
  // The plots in the paper/PAS are only MC, so they have the same CMS Simulation header
  // (although we do need to generate a second version for the AN with the fit parameters).
  // For data plots, we only need the AN version.

  // set up title
  char buf[512];
  if (isData) {
    sprintf(buf, "CMS Preliminary #sqrt{s}=7 TeV L=%.1f fb^{-1}", isMu ? lumiMu : lumiEle);
    //sprintf(buf, "CMS #sqrt{s}=7 TeV L=%.1f fb^{-1}", isMu ? lumiMu : lumiEle);
  } else
    sprintf(buf, "CMS Simulation #sqrt{s}=7 TeV");
  TLatex *t1 = new TLatex(0.02, 0.96, buf);
  t1->SetNDC(kTRUE);
  t1->SetX(0.50);
  t1->SetY(0.94);
  t1->SetTextFont(42);
  t1->SetTextAlign(21);
  t1->Draw();

  TLatex *t2;
  if (isMu) {
    t2 = new TLatex(0.85*highBound, normFactor/2, "#mu^{+}#mu^{-}");
  } else {
    t2 = new TLatex(0.85*highBound, normFactor/2, "e^{+}e^{-}");
  }
  t2->SetTextFont(42);
  t2->SetTextSize(0.05);
  t2->Draw();

  // print version w/o fit parameters first for paper
  sprintf(buf, "BackgroundCDFRenorm_%s.png", isMu ? "muon" : "electron");
  c1->Print(buf);
  sprintf(buf, "BackgroundCDFRenorm_%s.pdf", isMu ? "muon" : "electron");
  c1->Print(buf);
}
