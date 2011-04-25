#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooAddPdf.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooCBShape.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooMCStudy.h"
#include "RooFitResult.h"
#include "RooThresholdCategory.h"
#include "RooBinningCategory.h"
#include "RooSuperCategory.h"
#include "RooWorkspace.h"
#include "RooCategory.h"
#include "RooSimultaneous.h"
#include "RooSimPdfBuilder.h"
#include "RooCatType.h"
#include "Roo1DTable.h"
#include "RooCmdArg.h"
#include "RooChi2Var.h"

//#include "LikelihoodIntervalPlot.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TAxis.h"
#include "TGraphAsymmErrors.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TList.h"
#include "TRegexp.h"
#include "TLatex.h"
#include "TMath.h"


bool doMinos = 1;//kFALSE;

double mmin_=8.0.;  double mmax_=14.;
int nptbins   =50;
int nMassBins_;
using namespace RooFit;

RooWorkspace* wks = new RooWorkspace("wks","upsilon mass");

RooAbsPdf* buildPdf();
RooSimultaneous* buildPdfSimul(RooCategory* sample);

void llprof(RooDataSet *data, RooAbsPdf *pdf, RooRealVar *frac);

RooFitResult* fitYield(RooDataSet*data, RooAbsPdf *pdf, TString name);

void supress() {

  double mass_precision = 0.1;
  nMassBins_ = (int) (mmax_-mmin_)/mass_precision;
  //cout << nMassBins_ << endl;
  //return;

  //gROOT->SetStyle("Plain");
  gROOT->LoadMacro("setTDRStyle_modified.C");
  setTDRStyle();

  //define analysis variable
  RooRealVar* mass  = new RooRealVar("invariantMass","#mu#mu mass",mmin_,mmax_,"GeV/c^{2}"); 
  RooRealVar* muppt = new RooRealVar("muPlusPt" ,"#mu+ pt",2,20,"GeV/c"); 
  RooRealVar* mumpt = new RooRealVar("muMinusPt","#mu- pt",2,20,"GeV/c"); 

  wks->import(*mass);


  //read data ttrees
  TString tree_name("UpsilonTree");
  TString fn_hi("HiTree.root");      TFile f_hi(fn_hi,"read");
  TString fn_pp("ppTree.root");      TFile f_pp(fn_pp,"read");
  TString fn_p3("ppTree3ipb.root");  TFile f_p3(fn_p3,"read");

  gDirectory->Cd(fn_hi+":");
  TTree* tree_hi = (TTree*)gROOT->FindObject(tree_name);

  gDirectory->Cd(fn_pp+":");
  TTree* tree_pp = (TTree*)gROOT->FindObject(tree_name);

  gDirectory->Cd(fn_p3+":/yieldUpsilonTree");
  TTree* tree_p3 = (TTree*)gROOT->FindObject("probe_tree");

  //tree_pp->Print(); tree_hi->Print("v"); return;

  //recast ttrees as dataset
  RooArgSet cols(*mass,*muppt,*mumpt);
  RooDataSet *data_hi_0, *data_hi, *data_pp_0, *data_pp, *data_p3_0, *data_p3;
  data_hi_0 = new RooDataSet("data_hi","data_hi",tree_hi,cols);
  data_hi =  (RooDataSet*) (data_hi_0
			    ->reduce(Cut("invariantMass>8.0&&invariantMass<14"))
			    ->reduce(Cut("muMinusPt>4&&muPlusPt>4")) 
			    ); 
  data_pp_0 = new RooDataSet("data_pp","data_pp",tree_pp,cols);
  data_pp =  (RooDataSet*) (data_pp_0
			    ->reduce(Cut("invariantMass>8.0&&invariantMass<14"))
			    ->reduce(Cut("muMinusPt>4&&muPlusPt>4")) 
			    ); 
  data_p3_0 = new RooDataSet("data_p3","data_p3",tree_p3,cols);
  data_p3 =  (RooDataSet*) (data_p3_0
			    ->reduce(Cut("invariantMass>8.0&&invariantMass<14"))
			    ->reduce(Cut("muMinusPt>4&&muPlusPt>4")) 
			    ); 
  //data_pp->Print("v"); return;
 
  //plot mass distributions
  bool plotmasses = false;
  if(plotmasses) {
  TH1* h_mass_hi = (TH1*) data_hi->createHistogram("invariantMass",nMassBins_);
  TH1* h_mass_pp = (TH1*) data_pp->createHistogram("invariantMass",nMassBins_);
  TH1* h_mass_p3 = (TH1*) data_p3->createHistogram("invariantMass",nMassBins_);
  TCanvas c_m; c_m.Divide(3,1);
  c_m.cd(1);  h_mass_hi->Draw();
  c_m.cd(2);  h_mass_pp->Draw();
  c_m.cd(3);  h_mass_p3->Draw();
  c_m.SaveAs("mass.gif");

  TCanvas c_ks("ks","ks",1000,500); c_ks.Divide(2,1);
  TH1* h_mass_ks_hi =  h_mass_hi->Clone();
  TH1* h_mass_ks_pp =  h_mass_pp->Clone();
  TH1* h_mass_ks_p3 =  h_mass_p3->Clone();

  h_mass_ks_pp->Sumw2();
  h_mass_ks_p3->Sumw2();
  h_mass_ks_pp->Scale(66./125);
  h_mass_ks_p3->Scale(66./3200);
  h_mass_ks_hi->SetLineColor(kRed);  h_mass_ks_hi->SetMarkerColor(kRed);  h_mass_ks_hi->SetMarkerSize(0.8);  
  h_mass_ks_pp->SetLineColor(kBlue); h_mass_ks_pp->SetMarkerColor(kBlue); h_mass_ks_pp->SetMarkerSize(0.8); 
  h_mass_ks_p3->SetLineColor(kGreen);h_mass_ks_p3->SetMarkerColor(kGreen);h_mass_ks_p3->SetMarkerSize(0.8);
  c_ks.cd(1);
  h_mass_ks_hi->SetAxisRange(8,12);
  h_mass_ks_pp->SetAxisRange(8,12);
  h_mass_ks_p3->SetAxisRange(8,12);
  h_mass_ks_hi->DrawCopy();
  h_mass_ks_pp->DrawCopy("same");
  h_mass_ks_p3->DrawCopy("same");
  h_mass_ks_hi->SetAxisRange(9.7,10.6);
  h_mass_ks_pp->SetAxisRange(9.7,10.6);
  h_mass_ks_p3->SetAxisRange(9.7,10.6);
  c_ks.cd(2);
  h_mass_ks_hi->SetAxisRange(0,30,"Y");
  h_mass_ks_hi->Draw();
  h_mass_ks_pp->Draw("same");
  h_mass_ks_p3->Draw("same");
  c_ks.SaveAs("mass_ks.gif");
  cout << "KS-test hi vs pp: " <<  h_mass_ks_hi->KolmogorovTest(h_mass_ks_pp,"N") << endl;
  cout << "KS-test pp vs p3: " <<  h_mass_ks_pp->KolmogorovTest(h_mass_ks_p3,"N") << endl;
  cout << "KS-test hi vs p3: " <<  h_mass_ks_hi->KolmogorovTest(h_mass_ks_p3,"N") << endl;
  //return;
  }

  //tbd: side badn subtracted distributions
  bool plotpt = false;
  if(plotpt){
  TH1* h_pt_hi = (TH1*) data_hi->createHistogram("muMinusPt",nptbins);
       h_pt_hi->Add (data_hi->createHistogram("muPlusPt",nptbins));
  TH1* h_pt_pp = (TH1*) data_pp->createHistogram("muMinusPt",nptbins);
       h_pt_pp->Add (data_pp->createHistogram("muPlusPt",nptbins));
  TH1* h_pt_p3 = (TH1*) data_p3->createHistogram("muMinusPt",nptbins);
       h_pt_p3->Add (data_p3->createHistogram("muPlusPt",nptbins));
  //normalize
  h_pt_hi->Scale(1/h_pt_hi->Integral());
  h_pt_pp->Scale(1/h_pt_pp->Integral());  
  h_pt_p3->Scale(1/h_pt_p3->Integral());  
  TCanvas c_pt; 
  c_pt.SetLogy();
  h_pt_hi->SetLineColor(kRed);   h_pt_hi->SetMarkerColor(kRed);    h_pt_hi->SetMarkerSize(0.8);  
  h_pt_pp->SetLineColor(kBlue);  h_pt_pp->SetMarkerColor(kBlue);   h_pt_pp->SetMarkerSize(0.8);  
  h_pt_p3->SetLineColor(kGreen); h_pt_p3->SetMarkerColor(kGreen);  h_pt_p3->SetMarkerSize(0.8);  
  h_pt_hi->Draw();
  h_pt_pp->Draw("same");
  h_pt_p3->Draw("same");
  c_pt.SaveAs("pt.gif");
  return;
  }

  //separate fitting 
  RooAbsPdf* simplePdf = buildPdf();
  RooFitResult *fitres_hi, *fitres_pp, *fitres_p3;
  bool separate_fit = 1;
  if(separate_fit) {
    fitres_hi = fitYield(data_hi,simplePdf,"hi");
    fitres_pp = fitYield(data_pp,simplePdf,"pp3tev");
    //fitres_p3 = fitYield(data_p3,simplePdf,"pp7tev");
  }
  
  if(0){
    RooRealVar *frac =  wks->var("N_{2S}/N_{1S}");
    llprof(data_hi,simplePdf,frac);
    return;
  }

  //simultaneous fitting

  RooCategory* sample = new RooCategory("sample","sample") ;
  sample->defineType("heavyion") ;
  sample->defineType("ppreference") ;
  
  RooSimultaneous* simPdf = buildPdfSimul(sample);
  
  bool fit_simul_hi_pp = true;
  RooFitResult* fitres_hi_pp;
  if(fit_simul_hi_pp) {
    RooDataSet* data_comb_hi_pp = new 
      RooDataSet("combData HI pp","combined data hi pp",
		 *mass,Index(*sample),Import("heavyion",*data_hi),Import("ppreference",*data_pp));
    
    fitres_hi_pp = simPdf->fitTo(*data_comb_hi_pp, Save(),Extended(kTRUE), Minos(doMinos));

    RooPlot* frame_hi = mass->frame(Bins(nMassBins_),Title("Heavy Ion sample"));
    RooPlot* frame_pp = mass->frame(Bins(nMassBins_),Title("pp 3.76 TeV sample"));
    RooPlot* frame_xx = mass->frame(Title("simultaneous fit parameter values"));

    data_comb_hi_pp->plotOn(frame_hi,MarkerStyle(7), DrawOption("E"),Cut("sample==sample::heavyion"));
    simPdf->plotOn(frame_hi,Slice(*sample,"heavyion"),ProjWData(*sample,*data_comb_hi_pp));
    simPdf->plotOn(frame_hi,Slice(*sample,"heavyion"),ProjWData(*sample,*data_comb_hi_pp),Components("bkg"),LineStyle(kDashed));

    data_comb_hi_pp->plotOn(frame_pp,MarkerStyle(7), DrawOption("E"),Cut("sample==sample::ppreference"));
    simPdf->plotOn(frame_pp,Slice(*sample,"ppreference"),ProjWData(*sample,*data_comb_hi_pp));
    simPdf->plotOn(frame_pp,Slice(*sample,"ppreference"),ProjWData(*sample,*data_comb_hi_pp),Components("bkg_ctl"),LineStyle(kDashed));
    
    simPdf->paramOn(frame_xx, data_comb_hi_pp,"",0,"NELU",0.3,0.9,0.9);
    
    TCanvas c_sim_hi_pp("c1","c1",1200,400);
    c_sim_hi_pp.Divide(3);
    c_sim_hi_pp.cd(1);
    //gPad->SetLeftMargin(0.15) ; 
    //frame_hi->GetYaxis()->SetTitleOffset(1.4);
    frame_hi->Draw();  
    c_sim_hi_pp.cd(2);
    frame_pp->Draw();  
    c_sim_hi_pp.cd(3);
    frame_xx->Draw();  
    c_sim_hi_pp.SaveAs("sim_hi_pp.gif");

  }

  /// simultaneous fit to pp data 2.76 vs 7 TeV
  bool fit_simul_pp_p3 = 0;
  RooFitResult* fitres_pp_p3;
  if(fit_simul_pp_p3){
    
    RooDataSet* data_comb_pp_p3 = new 
      RooDataSet("combData pp 2.76 vs 7 Tev","combined data pp 2.76 vs 7 TeV",
		 *mass,Index(*sample),Import("heavyion",*data_pp),Import("ppreference",*data_p3));
    
    fitres_pp = simPdf->fitTo(*data_comb_pp_p3, Save(),Extended(kTRUE), Minos(doMinos));
    
    RooPlot* frame_p3 = mass->frame(Bins(nMassBins_),Title("pp 3.76 TeV sample"));
    RooPlot* frame_p7 = mass->frame(Bins(nMassBins_),Title("pp 7 TeV sample"));
    RooPlot* frame_xy = mass->frame(Title("simultaneous fit parameter values"));
    
    data_comb_pp_p3->plotOn(frame_p3,MarkerStyle(7), DrawOption("E"),Cut("sample==sample::heavyion"));
    simPdf         ->plotOn(frame_p3,Slice(*sample,"heavyion"),ProjWData(*sample,*data_comb_pp_p3));
    simPdf         ->plotOn(frame_p3,Slice(*sample,"heavyion"),ProjWData(*sample,*data_comb_pp_p3),Components("bkg"),LineStyle(kDashed));
    
    data_comb_pp_p3->plotOn(frame_p7,MarkerStyle(7), DrawOption("E"),Cut("sample==sample::ppreference"));
    simPdf         ->plotOn(frame_p7,Slice(*sample,"ppreference"),ProjWData(*sample,*data_comb_pp_p3));
    simPdf         ->plotOn(frame_p7,Slice(*sample,"ppreference"),ProjWData(*sample,*data_comb_pp_p3),Components("bkg_ctl"),LineStyle(kDashed));
    
    simPdf->paramOn(frame_xy, data_comb_pp_p3,"",0,"NELU",0.3,0.9,0.9);

    TCanvas c_sim_pp_p3("c2","c2",1200,400);
    c_sim_pp_p3.Divide(3);
    c_sim_pp_p3.cd(1);
    //gPad->SetLeftMargin(0.15) ; 
    //frame_hi->GetYaxis()->SetTitleOffset(1.4);
    frame_p3->Draw();  
    c_sim_pp_p3.cd(2);
    frame_p7->Draw();  
    c_sim_pp_p3.cd(3);
    frame_xy->Draw();  
    c_sim_pp_p3.SaveAs("sim_pp_3vs7.gif");
  }


  if(fit_simul_hi_pp) {
    printf("simultaneous heavyion pp sample fitting\n");
    RooRealVar* f2o1hi = (RooRealVar*)fitres_hi_pp->floatParsFinal().find("N_{2S}/N_{1S}");
    printf("\t (2s/1s)_hi = %5.3f +%5.3f %5.3f\n",
	   f2o1hi->getVal(), f2o1hi->getErrorHi(), f2o1hi->getErrorLo() );
    RooRealVar* rat2o1 = (RooRealVar*)fitres_hi_pp->floatParsFinal().find("r(2S/1S;hi/pp)");
    printf("\t (2s/1s)_hi/(2s/1s)_pp = %5.3f +%5.3f %5.3f\n",
	   rat2o1->getVal(), rat2o1->getErrorHi(), rat2o1->getErrorLo() );
  }

  if(separate_fit){
    printf("separate sample fitting\n");
    RooRealVar* f2o1hi = (RooRealVar*)fitres_hi->floatParsFinal().find("N_{2S}/N_{1S}");
    printf("\t (2s/1s)_hi = %5.3f +%5.3f %5.3f\n",
	   f2o1hi->getVal(), f2o1hi->getErrorHi(), f2o1hi->getErrorLo() );   
    RooRealVar* f2o1pp = (RooRealVar*)fitres_pp->floatParsFinal().find("N_{2S}/N_{1S}");
    printf("\t (2s/1s)_pp = %5.3f +%5.3f %5.3f\n",
	   f2o1pp->getVal(), f2o1pp->getErrorHi(), f2o1pp->getErrorLo() );   

    double rat   = f2o1hi->getVal() / f2o1pp->getVal();
    double rat_e = rat * sqrt( pow ( f2o1hi->getError() / f2o1hi->getVal(), 2) + pow(f2o1pp->getError() / f2o1pp->getVal(),2) ); 
			      
    printf("\t (2s/1s)_hi/(2s/1s)_pp  = %5.3f +- %5.3f\n",
	   rat, rat_e); 
  }
  
  return;

}

//define basic PDF
RooAbsPdf* buildPdf() {

  RooRealVar *mass = wks->var("invariantMass");

  const double M1S(9.460), M2S(10.023), M3S(10.355);
  RooRealVar *mean  = new RooRealVar("#mu_{M}","#Upsilon mean",M1S,M1S-0.3,M1S+0.3);//,"GeV");
  mean->setVal(9.454); //fixed form pp -- tbd include gaussian constraint 
  mean->setConstant(kTRUE);  

  RooRealVar *rat21 = new RooRealVar("rat2","mass ratio #Upsilon(1,2S)",M2S/M1S);
  RooRealVar *rat31 = new RooRealVar("rat3","mass ratio #Upsilon(1,3S)",M3S/M1S);
  rat21->setConstant(kTRUE); 
  rat31->setConstant(kTRUE); 

  RooFormulaVar *mean1S = new RooFormulaVar("mean1S","@0",RooArgList(*mean));
  RooFormulaVar *mean2S = new RooFormulaVar("mean2S","@0*@1", RooArgList(*mean,*rat21));
  RooFormulaVar *mean3S = new RooFormulaVar("mean3S","@0*@1", RooArgList(*mean,*rat31));

  RooRealVar *sigma1 = new RooRealVar("#sigma_{M}","Sigma_1",0.06,0.01,0.30);

  RooFormulaVar *reso1S = new RooFormulaVar("reso1S","@0"             ,RooArgList(*sigma1));
  RooFormulaVar *reso2S = new RooFormulaVar("reso2S","@0*10.023/9.460",RooArgList(*sigma1));
  RooFormulaVar *reso3S = new RooFormulaVar("reso3S","@0*10.355/9.460",RooArgList(*sigma1));
  
  //signal
  RooRealVar *alpha  = new RooRealVar("CB_{#alpha}","tail shift",2.0,0.2,4);
  RooRealVar *npow   = new RooRealVar("CB_{n}","power order",1,1,3);
  npow ->setConstant(kTRUE);
  //alpha->setVal(1.5);//from full fit to 7tev 3/pn data [with same model: single CB] [1.563+-0.054]
  alpha->setConstant(kTRUE);
  RooCBShape  *sig1S = new RooCBShape ("sig1s", "cb 1s", *mass,*mean1S,*reso1S,*alpha,*npow); 
  RooCBShape  *sig2S = new RooCBShape ("sig2s", "cb 2s", *mass,*mean2S,*reso2S,*alpha,*npow); 
  RooCBShape  *sig3S = new RooCBShape ("sig3s", "cb 3s", *mass,*mean3S,*reso3S,*alpha,*npow); 
					  
  //background
  RooRealVar *bkg_a1  = new RooRealVar("bkg_{1}", "background a1", 0, -1, 1);
  RooRealVar *bkg_a2  = new RooRealVar("bkg_{2}", "background a2", -0.2,-2,0);
  RooAbsPdf  *bkgPdf  = new RooChebychev("bkg","linear background",*mass, RooArgList(*bkg_a1,*bkg_a2));
  //RooRealVar *bkglbd  = new RooRealVar("bkg_{expo}", "background a1", 0, -2, 2);
  //RooAbsPdf   *bkgPdf = new RooExponential("bkg", "bkg exponential", *mass, *bkglbd);

  const int nt = 50000;					 
  RooRealVar *nsig1  = new RooRealVar("N_{1S}","signal 1s yield",  100,20,nt);
  RooRealVar *nsig2  = new RooRealVar("N_{2S}","signal 2s yield",  100,20,nt);
  RooRealVar *nsig3  = new RooRealVar("N_{3S}","signal 3s yield",  100,20,nt);
  RooRealVar *nbkgd = new RooRealVar("N_{bkg}","brackground yield",100,20,nt); 
    
  //RooRealVar *f23os = new RooRealVar("f23os","2+3/1+2+3 sig fration",0.4,0,1); 
  //RooRealVar *f2o23 = new RooRealVar("f2o23","2/2+3 sig fration",0.75,0,1); 
  //nsig1f = new RooFormulaVar("nsig1f","@0*(1.-@1)", RooArgList(*nsig,*f23os));
  //nsig2f = new RooFormulaVar("nsig2f","@0*@1*@2", RooArgList(*nsig,*f23os,*f2o23));
  //nsig3f = new RooFormulaVar("nsig3f","@0*@1*(1.-@2)", RooArgList(*nsig,*f23os,*f2o23));

  RooFormulaVar *nsig1f, *nsig2f, *nsig3f;
  RooRealVar *f2o1  = new RooRealVar("N_{2S}/N_{1S}" ,"2/1   sig fration",0.3,0,1); 
  RooRealVar *f3o1  = new RooRealVar("N_{3S}/N_{1S}" ,"3/1   sig fration",0.3,0,1); 
  //RooRealVar *f23o1 = new RooRealVar("N_{2S}+N_{3S} / N_{1S}","2+3/1 sig fration",0.4,0,1); 
  nsig1f = new RooFormulaVar("nsig1f","@0"        , RooArgList(*nsig1));
  nsig2f = new RooFormulaVar("nsig2f","@0*@1"     , RooArgList(*nsig1,*f2o1));
  nsig3f = new RooFormulaVar("nsig3f","@0*@1"     , RooArgList(*nsig1,*f3o1));
  //nsig3f = new RooFormulaVar("nsig3f","@0*(@1-@2)", RooArgList(*nsig1,*f23o1,*f2o1));
  
  RooAbsPdf  *pdf   = new RooAddPdf ("simple_pdf","total signal+background pdf", 
				     RooArgList(*sig1S,*sig2S,*sig3S,*bkgPdf),
				     //			     RooArgList(*nsig1,*nsig2,*nsig3,*nbkgd));
				     RooArgList(*nsig1f,*nsig2f,*nsig3f,*nbkgd)
				     );

  wks->import(*pdf);


  return pdf;

}
//define basic PDF
RooSimultaneous* buildPdfSimul(RooCategory* sample) {

  RooRealVar *mass = wks->var("invariantMass");

  const double M1S(9.460), M2S(10.023), M3S(10.355);
  RooRealVar *mean  = new RooRealVar("#mu_{M}","#Upsilon mean",M1S,M1S-0.3,M1S+0.3);//,"GeV");
  mean->setVal(9.454); //fixed form pp -- tbd include gaussian constraint 
  mean->setConstant(kTRUE);  

  RooRealVar *rat21 = new RooRealVar("rat2","mass ratio #Upsilon(1,2S)",M2S/M1S);
  RooRealVar *rat31 = new RooRealVar("rat3","mass ratio #Upsilon(1,3S)",M3S/M1S);
  rat21->setConstant(kTRUE); 
  rat31->setConstant(kTRUE); 

  RooFormulaVar *mean1S = new RooFormulaVar("mean1S","@0",RooArgList(*mean));
  RooFormulaVar *mean2S = new RooFormulaVar("mean2S","@0*@1", RooArgList(*mean,*rat21));
  RooFormulaVar *mean3S = new RooFormulaVar("mean3S","@0*@1", RooArgList(*mean,*rat31));

  RooRealVar *sigma1 = new RooRealVar("#sigma_{M}","Sigma_1",0.06,0.01,0.30);

  RooFormulaVar *reso1S = new RooFormulaVar("reso1S","@0"             ,RooArgList(*sigma1));
  RooFormulaVar *reso2S = new RooFormulaVar("reso2S","@0*10.023/9.460",RooArgList(*sigma1));
  RooFormulaVar *reso3S = new RooFormulaVar("reso3S","@0*10.355/9.460",RooArgList(*sigma1));
  
  //signal
  RooRealVar *alpha  = new RooRealVar("CB_{#alpha}","tail shift",2.0,0.2,4);
  RooRealVar *npow   = new RooRealVar("CB_{n}","power order",1,1,3);
  npow ->setConstant(kTRUE);
  //alpha->setVal(1.5);//from full fit to 7tev 3/pn data [with same model: single CB] [1.563+-0.054]
  alpha->setConstant(kTRUE);
  RooCBShape  *sig1S = new RooCBShape ("sig1s", "cb 1s", *mass,*mean1S,*reso1S,*alpha,*npow); 
  RooCBShape  *sig2S = new RooCBShape ("sig2s", "cb 2s", *mass,*mean2S,*reso2S,*alpha,*npow); 
  RooCBShape  *sig3S = new RooCBShape ("sig3s", "cb 3s", *mass,*mean3S,*reso3S,*alpha,*npow); 
					  
  //background
  RooRealVar *bkg_a1  = new RooRealVar("bkg_{1}", "background a1", 0, -1, 1);
  RooRealVar *bkg_a2  = new RooRealVar("bkg_{2}", "background a2", -0.2,-2,0);
  RooAbsPdf  *bkgPdf  = new RooChebychev("bkg","background",*mass, RooArgList(*bkg_a1,*bkg_a2));
  RooRealVar *bkg_a1_ctl  = new RooRealVar("bkg_{1,pp}", "background controla 1", 0, -1, 1);
  RooRealVar *bkg_a2_ctl  = new RooRealVar("bkg_{2,pp}", "background controla 2", -0.2,-2,0);
  RooAbsPdf  *bkgPdf_ctl  = new RooChebychev("bkg_ctl","controlbackground",*mass, RooArgList(*bkg_a1_ctl,*bkg_a2_ctl));
  //RooRealVar *bkglbd  = new RooRealVar("bkg_{expo}", "background a1", 0, -2, 2);
  //RooAbsPdf   *bkgPdf = new RooExponential("bkg", "bkg exponential", *mass, *bkglbd);

  const int nt = 50000;					 
  RooRealVar *nsig1  = new RooRealVar("N_{1S,hi}","signal 1s yield",  100,20,nt);
  RooRealVar *nsig2  = new RooRealVar("N_{2S,hi}","signal 2s yield",  100,20,nt);
  RooRealVar *nsig3  = new RooRealVar("N_{3S,hi}","signal 3s yield",  100,20,nt);
  RooRealVar *nbkgd = new RooRealVar("N_{bkg,hi}","brackground yield",100,20,nt); 

  RooRealVar *nsig1_ctl = new RooRealVar("N_{1S,pp}" ,"control signal 1s yield",  100,20,nt);
  RooRealVar *nsig2_ctl = new RooRealVar("N_{2S,pp}" ,"control signal 2s yield",  100,20,nt);
  RooRealVar *nsig3_ctl = new RooRealVar("N_{3S,pp}" ,"control signal 3s yield",  100,20,nt);
  RooRealVar *nbkgd_ctl = new RooRealVar("N_{bkg,pp}","control brackground yield",100,20,nt); 

  RooRealVar *ratio1 = new RooRealVar("r(2S/1S;hi/pp)","hi-pp 2s/1s ratio",0.3,0,1); 
  RooRealVar *ratio2 = new RooRealVar("r(3S/1S;hi/pp)","hi-pp 3s/1s ratio",0.3,0,1); 
    
  RooFormulaVar *nsig1f, *nsig2f, *nsig3f;
  RooFormulaVar *nsig1f_ctl, *nsig2f_ctl, *nsig3f_ctl;

  //RooRealVar *f2o1_ctl = new RooRealVar("N_{2S}/N_{1S}_{ctl}" ,"2/1 control sig fration",0.3,0,1); 
  //RooRealVar *f3o1_ctl = new RooRealVar("N_{3S}/N_{1S}_{ctl}" ,"3/1 control sig fration",0.3,0,1); 

  RooRealVar *f2o1  = new RooRealVar("N_{2S}/N_{1S}" ,"2/1 sig fration",0.3,0,1); 
  RooRealVar *f3o1  = new RooRealVar("N_{3S}/N_{1S}" ,"3/1 sig fration",0.3,0,1); 

  nsig1f = new RooFormulaVar("nsig1f","@0"        , RooArgList(*nsig1));
  nsig2f = new RooFormulaVar("nsig2f","@0*@1"  , RooArgList(*nsig1,*f2o1));
  nsig3f = new RooFormulaVar("nsig3f","@0*@1"  , RooArgList(*nsig1,*f3o1));
  
  nsig1f_ctl = new RooFormulaVar("nsig1f_ctl","@0"        , RooArgList(*nsig1_ctl));
  nsig2f_ctl = new RooFormulaVar("nsig2f_ctl","@0*@1/@2"     , RooArgList(*nsig1_ctl,*f2o1,*ratio1));
  nsig3f_ctl = new RooFormulaVar("nsig3f_ctl","@0*@1/@2"     , RooArgList(*nsig1_ctl,*f3o1,*ratio2));

  //nsig1f = new RooFormulaVar("nsig1f","@0"        , RooArgList(*nsig1));
  //nsig2f = new RooFormulaVar("nsig2f","@0*@1*@2"  , RooArgList(*nsig1,*f2o1,*ratio1));
  //nsig3f = new RooFormulaVar("nsig3f","@0*@1*@2"  , RooArgList(*nsig1,*f3o1,*ratio2));
  
  RooAddPdf  *pdf_ctl  = new RooAddPdf ("pdf_ctl","total pdf control", 
				     RooArgList(*sig1S,*sig2S,*sig3S,*bkgPdf_ctl),
				     RooArgList(*nsig1f_ctl,*nsig2f_ctl,*nsig3f_ctl,*nbkgd_ctl)
					);

  RooAddPdf  *pdf_main = new RooAddPdf ("pdf_main","total pdf main", 
				     RooArgList(*sig1S,*sig2S,*sig3S,*bkgPdf),
				     RooArgList(*nsig1f,*nsig2f,*nsig3f,*nbkgd)
				     );


  //RooCategory sampler("sampler","sampler") ;
  //sampler.defineType("heavyion");
  //sampler.defineType("ppreference");

  RooSimultaneous *simPdf = new RooSimultaneous("simPdf","simultaneous pdf",*sample);
  simPdf->addPdf(*pdf_ctl, "ppreference");
  simPdf->addPdf(*pdf_main,"heavyion");
  return simPdf;

  //wks->import(*pdf_ctl);
  //wks->import(*pdf_main);
}

RooFitResult* fitYield(RooDataSet *data, RooAbsPdf *pdf, TString name) {

  RooFitResult* fitres = pdf->fitTo(*data, Save(), Extended(kTRUE), Minos(doMinos));

  RooPlot *frame;
  frame = wks->var("invariantMass")->frame(Bins(nMassBins_));
  data->plotOn(frame,MarkerStyle(7), DrawOption("E"));
  pdf->plotOn(frame);
  pdf->paramOn(frame);

  if(name.Contains("hi"))  
    frame->SetTitle("Heavy Ion sample");
  else if (name.Contains("pp7"))  
    frame->SetTitle("pp 7 TeV sample");
  else if (name.Contains("pp3"))  
    frame->SetTitle("pp 2.76 TeV sample");

  frame->GetXaxis()->SetTitle("#mu^{+}#mu^{-} mass (GeV/c^{2})");
  frame->GetYaxis()->SetTitleOffset(1.65);
  frame->GetYaxis()->SetTitleSize(0.033);
    
  //RooFitResult* fitres_hi = pdf->fitTo(*data_hi, Extended(kTRUE), Minos(kTRUE));
  //pdf->paramOn(frame_hi);
  
  TCanvas c;
  frame->Draw();
  c.SaveAs("mass_fit_"+name+".gif");

  return fitres;
  
}

//placeholder, 
//  need to fix + plus use more recent root version to access new roostats fucntionality
void llprof(RooDataSet *data, RooAbsPdf *pdf, RooRealVar *frac){

  RooAbsReal* nll = pdf->createNLL(*data,NumCPU(4)) ;
  RooMinuit(*nll).migrad() ;

  return;

  RooPlot* frame1 = frac->frame(Bins(10),Range(0.01,0.95),Title("LL and profileLL")) ;
  nll->plotOn(frame1,ShiftToZero()) ;

  RooAbsReal* pll_frac = nll->createProfile(*frac) ;
  pll_frac->plotOn(frame1,LineColor(kRed)) ;

  frame1->SetMinimum(0) ;
  frame1->SetMaximum(3) ;

  TCanvas c1;
  frame1->Draw() ;
  c1.SavaAs("ll.gif")

  /*
  //profile likelihood
  RooRealVar *f2o1 =  wks->var("N_{2S}/N_{1S}");
  ProfileLikelihoodCalculator pl(*data,*pdf,*f2o1);
  pl.SetConfidenceLevel(0.95); // 95% interval
  LikelihoodInterval* interval = pl.GetInterval();
  LikelihoodIntervalPlot plot(interval);
  TCanvas c1; c1.cd(); 
  plot.Draw();
  */

}
