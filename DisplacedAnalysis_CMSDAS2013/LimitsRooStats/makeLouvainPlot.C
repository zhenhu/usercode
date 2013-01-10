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
//const bool isMu = false;
//const int nbins = 9;
const bool isMu = true;
const int nbins = 6;

using namespace RooFit;

void makeLouvainPlot(void)
{
  //input parameters
  float lowBound=20; // was 50
  float highBound=600;// was 200
  float rebinFactor=2; // was 2
  float scaleFactor=1; // was not used
  bool isLog = true;
  
  // Select here!
  
  bool isData = false;

  std::string lepTag = isMu ? "muon" : "electron";
  selection = "_noLifetimeCuts";
  std::string typeTag = isData ? "data" : "backgroundMC";
  
  std::string fileNameRoot = "/afs/cern.ch/user/p/plujan/public/displacedfermions/trunk/LimitsRooStats/WinterSelection/masses_"+typeTag+"_"+lepTag+selection+"_rebin.root";
  std::string fileNameTxt = "/afs/cern.ch/user/p/plujan/public/displacedfermions/trunk/LimitsRooStats/WinterSelection/masses_"+typeTag+"_"+lepTag+selection+".txt";
  
  gROOT->ProcessLine(".L ./tdrstyle.C");
  setTDRStyle();
  gStyle->SetOptFit(1);
  // keep all axis & pad titles non-bold
  gStyle->SetTitleFont(42, "");
  gStyle->SetTitleFont(42, "X");
  gStyle->SetTitleFont(42, "Y");
  gStyle->SetTitleX(0.5);
  gStyle->SetTitleAlign(23);
  
  RooRealVar *rooMass_;
  if (isMu)
    rooMass_ = new RooRealVar("mass","M_{#mu#mu} [GeV/c^{2}]",lowBound, highBound);
  else
    rooMass_ = new RooRealVar("mass","M_{ee} [GeV/c^{2}]",lowBound, highBound);
  RooRealVar Mass = *rooMass_;

  //TFile* fout = new TFile("bwFit.root","RECREATE");
  //gROOT->cd();

  TFile* file_data =  new TFile(fileNameRoot.c_str(), "READ");
  TH1* data_hist = (TH1D*) file_data->Get("mass");
  data_hist->Sumw2();
  data_hist->Rebin(rebinFactor);
  data_hist->Scale(scaleFactor);
  RooDataHist* data_binned = new RooDataHist("rdh_data","", *rooMass_, data_hist);

  RooRealVar weight("weight", "weight", 0, 50);
  RooRealVar lxySig("lxySig", "lxySig", 0, 100);
  RooDataSet *data_unbinned_tmp = RooDataSet::read(fileNameTxt.c_str(), RooArgList(Mass, lxySig, weight));

  RooDataSet *data[nbins];

  for (int i=0; i<nbins; i++) {
    float xmin = i*1.0;
    float xmax = i*1.0+1.0;
    
    char cut[512];
    if (i==nbins-1)
      sprintf(cut, "lxySig > %.1f", xmin);
    else
      sprintf(cut, "lxySig > %.1f && lxySig <= %.1f", xmin, xmax);
    
    RooDataSet *dtmp = data_unbinned_tmp->reduce(cut);

    data[i] = new RooDataSet("points", cut, dtmp, RooArgList(Mass, weight), NULL, weight.GetName());
  }

  RooBinning tbins1(20,600);
  tbins1.addUniform(4,20,60);
  tbins1.addUniform(8,60,100);
  tbins1.addUniform(20,100,300);
  tbins1.addUniform(2,300,400);
  tbins1.addUniform(2,400,600);

  RooBinning tbins2(20,600);
  tbins2.addUniform(2,20,60);
  tbins2.addUniform(4,60,100);
  tbins2.addUniform(10,100,300);
  tbins2.addUniform(1,300,400);
  tbins2.addUniform(1,400,600);

  TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
  TLegend *l = new TLegend(0.45, 0.65, 0.92, 0.92);
  l->SetFillColor(0);
  l->SetBorderSize(0);
  l->SetTextFont(62);
  RooPlot* frame1 = Mass.frame(lowBound, highBound);
  for (int i=0; i<nbins; i++) {
    if (i<3)
      data[i]->plotOn(frame1,DataError(RooAbsData::None),Binning(tbins1),DrawOption("L"),LineColor(i+1),LineWidth(2),MarkerSize(0),XErrorSize(0),Rescale(1.0/data[i]->sumEntries()));
    else
      data[i]->plotOn(frame1,DataError(RooAbsData::None),Binning(tbins2),DrawOption("L"),LineColor(i+1),LineWidth(2),MarkerSize(0),XErrorSize(0),Rescale(1.0/data[i]->sumEntries()));
    char d[16];
    sprintf(d, "dummy%d", i);
    TH1F *dummy = new TH1F(d, d, 4, 0, 4);
    dummy->SetLineWidth(2);
    dummy->SetLineColor(i+1);
    l->AddEntry(dummy, data[i]->GetTitle(), "L");
  }

  frame1->Draw();
  frame1->GetYaxis()->SetTitle("Events (arb. norm.)");
  frame1->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
  frame1->SetMaximum(1.5);
  frame1->SetMinimum(0.0000001);
  gPad->SetLogy();
  l->Draw();

  if (!isMu) {
    TLatex *t1 = new TLatex(150, 0.5, "e^{+}e^{-}");
    t1->Draw();
    c1->Print("LouvainPlotEle.png");
  } else {
    TLatex *t1 = new TLatex(150, 0.5, "#mu^{+}#mu^{-}");
    t1->Draw();
    c1->Print("LouvainPlotMu.png");
  }

}
