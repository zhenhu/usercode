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

using namespace RooFit;

void fitBackgroundPDFBW(void)
{
  //input parameters
  float lowBound=20; // was 50
  float highBound=600;// was 200
  float rebinFactor=2; // was 2
  float scaleFactor=1; // was not used
  bool isLog = true;
  
  // Select here!
  
  bool isMu = true;
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
  
  std::string fileNameRoot = "/afs/cern.ch/user/p/plujan/public/displacedfermions/trunk/LimitsRooStats/WinterSelection/masses_"+typeTag+"_"+lepTag+selection+"_rebin.root";
  std::string fileNameTxt = "/afs/cern.ch/user/p/plujan/public/displacedfermions/trunk/LimitsRooStats/WinterSelection/masses_"+typeTag+"_"+lepTag+selection+".txt";
  
  const char *fitTag = (isMu && !isPrompt) ? "BW" : "BWTurnOnPlusExp";

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
  RooDataSet *data_unbinned = new RooDataSet("points", data_unbinned_tmp->GetTitle(), data_unbinned_tmp,
  					     RooArgList(Mass, weight), NULL, weight.GetName());
  // or this version to skip using the weights
  //				             RooArgList(Mass), NULL, 0);


  // Base shape: Breit-Wigner
  RooRealVar mean("BWMean","BWMean", 70.0, 110.0 );
  RooRealVar width("BWWidth","BWWidth", 0.0, 10.0 );
  RooBreitWigner baseShape("bw","bw",*rooMass_,mean,width);
  mean.setConstant(kFALSE);
  width.setConstant(kFALSE);

  // Gaussian
  // RooRealVar mean("mean", "mean", 90.0);
  // RooRealVar sigma("sigma", "sigma", 0.0, 10.0);
  // RooGaussian baseShape("G", "G", Mass, mean, sigma);
  // mean.setConstant(kFALSE);

  // Landau
  // RooRealVar landmean("landmean", "landmean", 80.0, 100.0);
  // RooRealVar landsigma("landsigma", "landsigma", 0, 20.0);
  // RooLandau baseShape("landau", "Landau", Mass, landmean, landsigma);

  // Crystal Ball
  // RooRealVar cbmean("CBMean", "CBMean" , 70.0, 110.0) ;
  // RooRealVar cbsigma("CBSigma", "CBSigma" , 0, 20.0) ;
  // RooRealVar n("n", "", 0, 10);
  // RooRealVar alpha("alpha", "", -3, 0);
  // RooCBShape baseShape("cball", "crystal ball", *rooMass_, cbmean, cbsigma, alpha, n);
  
  // Choose what to convolute the base shape with below by uncommenting one of these sections.
  // Convolve with Gaussian resolution function
  // RooRealVar mean_g("mean_g","mean_g", -10.0, 10.0 );
  // RooRealVar width_g("width_g","width_g", 0, 10.0 );
  // RooGaussian convShape("G","G",*rooMass_, mean_g, width_g);
  // mean_g.setConstant(kFALSE);
  // width_g.setConstant(kFALSE);

  // Convolve with bifurcated Gaussian
  // RooRealVar mean_bg("mean_bg", "mean_bg", 0);
  // RooRealVar sigma_l("sigma_l", "sigma_l", 5.0);
  // RooRealVar sigma_r("sigma_r", "sigma_r", 50.0);
  // mean_bg.setConstant(kFALSE);
  // sigma_l.setConstant(kFALSE);
  // sigma_r.setConstant(kFALSE);
  // RooBifurGauss convShape("bifurGauss", "bifurcated gaussian", Mass, mean_bg, sigma_l, sigma_r);
  
  // Convolve with Crystal Ball
  //RooRealVar cbmean("CBMean", "CBMean" , -10.0, 10.0) ;
  //RooRealVar cbsigma("CBSigma", "CBSigma" , 0, 10.0) ;
  //RooRealVar n("n", "", 5.1);
  //RooRealVar alpha("alpha", "", -1.3);
  //RooCBShape convShape("cball", "crystal ball", *rooMass_, cbmean, cbsigma, alpha, n);

  // Convolve with Landau
  // RooRealVar landmean("landMean", "landMean", -10.0, 10.0);
  // RooRealVar landsigma("landSigma", "landSigma", -1.0, 20.0);
  // RooLandau convShape("landau", "Landau", Mass, landmean, landsigma);

  // If convolving, use the first line below if there's no second term,
  // or the second line below if there is a second term
  // RooFFTConvPdf signalPdf("sigModel","final signal shape", *rooMass_,  baseShape, convShape);
  // RooFFTConvPdf signalPdfInt("sigModel1", "intermediate signal shape", *rooMass_, baseShape, convShape);
 
  // Or add a second gaussian
  // RooRealVar mean2("mean2", "mean2", 70, 150);
  // mean2.setConstant(kFALSE);
  // RooRealVar sigma2("sigma2", "sigma2", 0, 40);
  // RooGaussian G2("G2", "G2", Mass, mean2, sigma2);
  // RooRealVar gaus_rel_frac("C1", "C1", 0, 1);
  // RooAddPdf signalPdfInt("sigModelInt", "intermediate signal shape", baseShape, G2, gaus_rel_frac);

  // Various choices of additional term are below. Use one (or none).
  // If none AND no convolution, you'll need the line below
  // RooBreitWigner signalPdf = baseShape;

  // Exponential
  // RooRealVar exp_frac("C", "C", 0, 1);
  // RooRealVar exp_fact("a", "a", -0.01);
  // exp_fact.setConstant(kFALSE);
  // RooExponential E("E", "E", *rooMass_, exp_fact);
  // RooAddPdf signalPdf("sigModel", "final signal shape", signalPdfInt, E, exp_frac);
  // RooAddPdf signalPdf("sigModel", "final signal shape", baseShape, E, exp_frac);

  // with flat term added
  // RooRealVar uniform_frac("uniform_frac", "uniform_frac", 0, 1);
  // RooUniform U("U", "U", *rooMass_);
  // RooAddPdf signalPdf("sigModel", "final signal shape", signalPdfInt, U, uniform_frac);

  // with exponential term above 100 added
  // RooRealVar exp_frac("exp_frac", "exp_frac", 0, 1);
  // RooRealVar exp_fact("exp_fact", "exp_fact", -0.05);
  // exp_fact.setConstant(kFALSE);
  // RooGenericPdf E("E", "(@0>100) ? exp(@0*@1) : 0", RooArgSet(Mass, exp_fact));
  // RooAddPdf signalPdf("sigModel", "final signal shape", signalPdfInt, E, exp_frac);
  // RooAddPdf signalPdf("sigModel", "final signal shape", G, E, exp_frac);

  // exponential term with turnon
  RooRealVar C("C", "C", 0, 1);
  RooRealVar a("a", "a", -0.05);
  a.setConstant(kFALSE);
  RooExponential E("E", "E", Mass, a);
  RooRealVar turnOn("turnOn", "turnOn", -50, 250);
  RooRealVar turnOnWidth("turnOnWidth", "turnOnWidth", -5, 155);
  RooGenericPdf turnOnCurve("turnOnCurve", "TMath::Erf((@0-@1)/@2)+1", RooArgSet(Mass, turnOn, turnOnWidth));
  
  // three choices below
  // 1 -- turn on applied to exponential only
  // RooProdPdf expWithTurnOn("expWithTurnOn", "exponential with turn on", E, turnOnCurve);
  // RooAddPdf signalPdf("sigModel", "final signal shape", baseShape, expWithTurnOn, C);

  // 2 -- turn on applied to both
  // RooAddPdf signalPdfInt("sigModelInt", "intermediate signal shape", baseShape, E, C);
  // RooProdPdf signalPdf("sigModel", "final signal shape", signalPdfInt, turnOnCurve);

  // 3 -- turn on applied to BW only
  RooProdPdf bwTurnOn("bwTurnOn", "BW with turn on", baseShape, turnOnCurve);
  RooAddPdf signalPdf("sigModel", "final signal shape", bwTurnOn, E, C);

  // 1/m^4 (or other power, check the formula to see what I'm actually doing!) with turnon
  // RooRealVar C("C", "C", 0, 1);
  // RooRealVar turnOn("turnOn", "turnOn", 80, 100);
  // RooRealVar turnOnWidth("turnOnWidth", "turnOnWidth", 0.00, 95);
  // RooGenericPdf powerWithTurnOn("powerWithTurnOn", "(TMath::Erf((@0-@1)/@2)+1)/(pow(@0,4))", RooArgSet(Mass, turnOn, turnOnWidth));
  // RooRealVar turnOnFloor("turnOnFloor", "turnOnFloor", 0, 1e-6);
  // RooGenericPdf powerWithTurnOn("powerWithTurnOn", "(TMath::Erf((@0-@1)/@2)+1+@3)/(pow(@0,4))", RooArgSet(Mass, turnOn, turnOnWidth, turnOnFloor));
  // RooAddPdf signalPdf("sigModel", "final signal shape", baseShape, powerWithTurnOn, C);

  if (!isMu && isData && !isPrompt) {
    turnOnWidth.setVal(15.0);
  }
  if (isPrompt) {
    turnOn.setVal(90.0);
    //turnOn.setConstant(kTRUE);
    //turnOnWidth.setVal(5.0);
  }

  // Do the fit to the data. You can use either data_binned or data_binned here.

  RooFitResult *fitResult = signalPdf.fitTo(*data_unbinned, Save(true), 
					    Extended(false), 
					    Minos(false),
					    Optimize(2),
					    PrintEvalErrors(-1),
					    Warnings(false), SumW2Error(true)
					    );
  fitResult->Print("v");

  tdrStyle->UseCurrentStyle();
  setTDRStyle();
  tdrStyle->cd();

  // Create binning object with range (10,500)
  //RooBinning tbins(20,500) ;
  //tbins.addUniform(2,20,60) ;
  //tbins.addUniform(18,60,150) ;
  //tbins.addUniform(35,150,500) ;
  // Try using Andrzej's binning
  //double boundaries[] =  {20.0, 29.6, 39.2, 48.8, 58.4, 68.0, 77.6, 87.2, 96.8, 106.4, 117.818, 128.904, 141.205, 155.715, 174.239, 200.061, 239.145, 302.336, 409.346, 596.0};
  //RooBinning tbins(19, boundaries);
  RooBinning tbins(20,600);
  tbins.addUniform(232, 20, 600);

  TString cname = Form("fit");
  TCanvas* c1 = new TCanvas(cname,cname,500,500);
  RooPlot* frame1 = Mass.frame(lowBound, highBound);
  data_unbinned->plotOn(frame1,DataError(RooAbsData::SumW2),Binning(tbins),Rescale(1.0/tbins.averageBinWidth()));
  signalPdf.plotOn(frame1,ProjWData(*data_unbinned),Normalization(1.0/tbins.averageBinWidth(), RooAbsPdf::Relative));
  std::cout<<"chi2/dof = " << frame1->chiSquare(4) << std::endl;
  frame1->Draw("e0");
  frame1->GetYaxis()->SetTitle("Events / (GeV/c^{2})");
  if (isLog) {
    if (isPrompt)
      frame1->SetMinimum(1);
    else {
      if (isMu) {
	frame1->SetMinimum(0.05*scaleFactor);
      } else {
	if (isData)
	  frame1->SetMinimum(0.3*scaleFactor);
	else
	frame1->SetMinimum(0.01*scaleFactor);
      }
      frame1->SetMaximum(frame1->GetMaximum()/tbins.averageBinWidth());
      frame1->SetMinimum(frame1->GetMinimum()/tbins.averageBinWidth());
    }
    gPad->SetLogy();
  }
  gPad->SetTopMargin(0.12);
  gPad->SetRightMargin(0.05);

  // Conveniently, we no longer need to generate quite as many versions as previously.
  // The plots in the paper/PAS are only MC, so they have the same CMS Simulation header
  // (although we do need to generate a second version for the AN with the fit parameters).
  // For data plots, we only need the AN version.

  // set up title
  char buf[512];
  if (isData) {
    // sprintf(buf, "CMS Preliminary #sqrt{s}=7 TeV L=%.1f fb^{-1}", isMu ? lumiMu : lumiEle);
    //sprintf(buf, "CMS #sqrt{s}=7 TeV L=%.1f fb^{-1}", isMu ? lumiMu : lumiEle);
    //sprintf(buf, "CMS Preliminary    #sqrt{s} = 7 TeV    L = %.1f fb^{-1}", isMu ? lumiMu : lumiEle);
    sprintf(buf, "CMS    #sqrt{s} = 7 TeV    L = %.1f fb^{-1}", isMu ? lumiMu : lumiEle);
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
    t2 = new TLatex(0.85*highBound, 0.3*frame1->GetMaximum(), "#mu^{+}#mu^{-}");
  } else {
    t2 = new TLatex(0.85*highBound, 0.3*frame1->GetMaximum(), "e^{+}e^{-}");
  }
  t2->SetTextFont(42);
  t2->SetTextSize(0.05);
  t2->Draw();

  // print version w/o fit parameters first for paper
  sprintf(buf, "BackgroundPDFWinter_%s%s%s_%s_Paper.png",
	  isMu ? "muon" : "electron", isData ? "Data" : "MC", isPrompt ? "Prompt" : isLoose1 ? "L1" : "L2", fitTag);
  c1->Print(buf);
  sprintf(buf, "BackgroundPDFWinter_%s%s%s_%s_Paper.pdf",
	  isMu ? "muon" : "electron", isData ? "Data" : "MC", isPrompt ? "Prompt" : isLoose1 ? "L1" : "L2", fitTag);
  c1->Print(buf);

  // now add fit parameters for AN
  signalPdf.paramOn(frame1,Layout(0.4, 0.92, 0.85));
  frame1->Draw("e0");
  t1->Draw();

  sprintf(buf, "BackgroundPDFWinter_%s%s%s_%s_New.png",
	  isMu ? "muon" : "electron", isData ? "Data" : "MC", isPrompt ? "Prompt" : isLoose1 ? "L1" : "L2", fitTag);
  c1->Print(buf);
  sprintf(buf, "BackgroundPDFWinter_%s%s%s_%s_New.pdf",
	  isMu ? "muon" : "electron", isData ? "Data" : "MC", isPrompt ? "Prompt" : isLoose1 ? "L1" : "L2", fitTag);
  c1->Print(buf);

  //fout->cd();
  //c1->Write();
  //fout->Write();

}
