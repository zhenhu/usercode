/*
performs separate and simultaneous upsilon-mass fits in HI data pp data 

different types of fits can be selected

motation:
- hi: heavy-ion data
- ph: 2.76 pp data with heavy-ion recosntruction
- pp: 2.76 pp data with pp recosntruction 
- p3: 7 tev pp data with pp recosntruction 

inputs required in default configuration : the four data trees

example how to run:
   root -l -b -q suppress.C\(4.0\) >& figs/pt4.0/log &
*/

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
#include "RooUniform.h"
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

#include "RooMinuit.h"

#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/MCMCCalculator.h"
#include "RooStats/UniformProposal.h"
#include "RooStats/FeldmanCousins.h"
#include "RooStats/NumberCountingPdfFactory.h"
#include "RooStats/ConfInterval.h"
#include "RooStats/PointSetInterval.h"
#include "RooStats/LikelihoodInterval.h"
#include "RooStats/LikelihoodIntervalPlot.h"
#include "RooStats/RooStatsUtils.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/MCMCInterval.h"
#include "RooStats/MCMCIntervalPlot.h"
#include "RooStats/ProposalFunction.h"
#include "RooStats/ProposalHelper.h"

#include "cms_stat_001.C";
RooStats::MCMCInterval * StandardBayesianMCMCInterval(RooWorkspace*,
			     RooStats::ModelConfig*,
			     RooAbsData*,
			     double,
			     double,
			     int,
			     int,
			     const char *,
			     int);
 
#include "setTDRStyle_modified.C"
void setTDRStyle();

using namespace RooFit;

bool doMinos = 0;//kFALSE;

const double mmin_    = 7;  
const double mmax_    = 14.;
const int    nptbins  = 50;
int nMassBins_;
double negFr = -1; //allow negative fraction values

bool makePlots = 0;//false;

double ptmumin_ = 4;
TString figDir("figs/");

RooWorkspace* wks = new RooWorkspace("wks","upsilon mass");

RooAbsPdf* buildPdf(); //pdf for separate fitting
RooSimultaneous* buildPdfSimul(RooCategory*); // pdf for simultabeous fitting
RooFitResult* fitYield(RooDataSet*, RooAbsPdf *pdf, TString); 
void dumpFitVal(RooFitResult*, TString);
void plotDistributions(RooDataSet* hi, RooDataSet* ph, RooDataSet* pp, RooDataSet* p3);
void llprof(RooDataSet*, RooAbsPdf*, RooRealVar*); /*placeholder*/

void computeLimit();

void suppress(double ptmumin = 4.0) {

  ptmumin_ = ptmumin;

  //figDir+= "pt";
  //figDir+= TString::Format("%3.1f/",ptmumin);

  //gROOT->LoadMacro("cms_stat_001.C");

  //gROOT->LoadMacro("setTDRStyle_modified.C");
  setTDRStyle();
  
  double mass_precision = 0.1;
  nMassBins_ = (int) (mmax_-mmin_)/mass_precision;
  
  RooRealVar* mass    = new RooRealVar("invariantMass","#mu#mu mass",mmin_,mmax_,"GeV/c^{2}"); 
  RooRealVar* muppt   = new RooRealVar("muPlusPt" ,"#mu+ pt"   ,0,50,"GeV/c"); 
  RooRealVar* mumpt   = new RooRealVar("muMinusPt","#mu- pt"  ,0,50,"GeV/c"); 
  RooRealVar* mupeta  = new RooRealVar("muPlusEta" ,"#mu+ eta",-2.4,2.4); 
  RooRealVar* mumeta  = new RooRealVar("muMinusEta","#mu- eta",-2.4,2.4); 
  RooRealVar* upspt   = new RooRealVar("upsPt" ,"#Upsilon pt"   ,0,20,"GeV/c"); 
  RooRealVar* upsrap  = new RooRealVar("upsRapidity" ,"#Upsilon y",-2.4,2.4); 

  wks->import(*mass);

  //read data ttrees
  TString tree_name("UpsilonTree");
  TString fn_hi("hiTree.root");      TFile f_hi(fn_hi,"read"); //heavy ion
  TString fn_ph("phTree.root");      TFile f_ph(fn_ph,"read"); //pp 2.76 TeV pp reco
  TString fn_pp("ppTree.root");      TFile f_pp(fn_pp,"read"); //pp 2.76 TeV pp reco
  TString fn_p3("p3Tree.root");      TFile f_p3(fn_p3,"read"); //pp 7 TeV 3/pb

  gDirectory->Cd(fn_hi+":");
  TTree* tree_hi = (TTree*)gROOT->FindObject(tree_name);

  gDirectory->Cd(fn_ph+":");
  TTree* tree_ph = (TTree*)gROOT->FindObject(tree_name);

  gDirectory->pwd();
  gDirectory->ls();

  gDirectory->Cd(fn_pp+":");
  TTree* tree_pp = (TTree*)gROOT->FindObject(tree_name);

  gDirectory->Cd(fn_p3+":/yieldUpsilonTree");
  TTree* tree_p3 = (TTree*)gROOT->FindObject("probe_tree");

  //gDirectory->Cd(fn_p3+":");
  //TTree* tree_p3 = (TTree*)gROOT->FindObject(tree_name);
  //tree_p3->Print(); tree_hi->Print("v"); return;

  //recast ttrees as dataset
  RooArgSet *cols;
  //if(makePlots)
  cols = new RooArgSet(*mass,*muppt,*mumpt,*mupeta,*mumeta,*upspt,*upsrap);
  //else
  //cols = new RooArgSet(*mass,*muppt,*mumpt);
  RooDataSet *data_hi_0, *data_hi, *data_ph_0, *data_ph, *data_pp_0, *data_pp, *data_p3_0, *data_p3;

  TString massCut = TString::Format("invariantMass>%4.2f&&invariantMass<%4.2f",mmin_,mmax_);
  TString ptCut   = TString::Format("muMinusPt>%4.2f&&muPlusPt>%4.2f && upsPt<20 && upsRapidity<2.4&&upsRapidity>-2.4",ptmumin_,ptmumin_);


  data_hi_0 = new RooDataSet("data_hi","data_hi",tree_hi,*cols);
  data_hi =  (RooDataSet*) (data_hi_0
  			    ->reduce(Cut(massCut))
  			    ->reduce(Cut(ptCut)) 
  			    ); 
  data_ph_0 = new RooDataSet("data_ph","data_ph",tree_ph,*cols);
  data_ph =  (RooDataSet*) (data_ph_0
			    ->reduce(Cut(massCut))
			    ->reduce(Cut(ptCut)) 
			    ); 
  data_pp_0 = new RooDataSet("data_pp","data_pp",tree_pp,*cols);
  data_pp =  (RooDataSet*) (data_pp_0
			    ->reduce(Cut(massCut))
			    ->reduce(Cut(ptCut)) 
			    ); 


  data_p3_0 = new RooDataSet("data_p3","data_p3",tree_p3,*cols);
  data_p3 =  (RooDataSet*) (data_p3_0
			    //->reduce(Cut("invariantMass>7&&invariantMass<15"))
			    ->reduce(Cut(massCut))
			    ->reduce(Cut(ptCut)) 
			    ); 
  //data_ph->Print("v"); return;

  //plot mass distributions
  if(makePlots)
    plotDistributions(data_hi, data_ph, data_pp, data_p3);



  //separate fitting 
  RooAbsPdf* simplePdf = buildPdf();
  RooFitResult *fitres_hi, *fitres_ph, *fitres_pp, *fitres_p3;

  bool separate_fit = 0;
  if(separate_fit) {
    fitres_hi = fitYield(data_hi,simplePdf,"_hi");
    //return;
    fitres_ph = fitYield(data_ph,simplePdf,"_ph_pp276hireco");
    fitres_pp = fitYield(data_pp,simplePdf,"_pp_pp276ppreco");
    fitres_p3 = fitYield(data_p3,simplePdf,"_p3_pp7tev");
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
  
  bool fit_simul_hi_pp = 1;
  RooFitResult* fitres_hi_pp;
  if(fit_simul_hi_pp) {
    RooDataSet* data_comb_hi_pp = new 
      RooDataSet("combData","combined data hi pp",
		 *mass,Index(*sample),Import("heavyion",*data_hi),Import("ppreference",*data_ph));
 
    //wks->import(*sample);
    wks->import(*data_comb_hi_pp);
   
    //computeLimit();
    //return;
   
    fitres_hi_pp = simPdf->fitTo(*data_comb_hi_pp, Save(),Extended(kTRUE), Minos(doMinos));
    //fitres_hi_pp = simPdf->fitTo(*data_comb_hi_pp, Save(),Extended(kTRUE),Constrain(*wks->var("#sigma_{M}")), Minos(doMinos));

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
    c_sim_hi_pp.SaveAs(figDir+"sim_hi_pp.gif");

  }

  /// simultaneous fit to pp data 2.76 vs 7 TeV
  bool fit_simul_pp_p3 = 0;
  RooFitResult* fitres_pp_p3;
  if(fit_simul_pp_p3){
    
    RooDataSet* data_comb_pp_p3 = new 
      RooDataSet("combData pp 2.76 vs 7 Tev","combined data pp 2.76 vs 7 TeV",
		 *mass,Index(*sample),Import("heavyion",*data_pp),Import("ppreference",*data_p3));
    
    fitres_pp_p3 = simPdf->fitTo(*data_comb_pp_p3, Save(),Extended(kTRUE), Minos(doMinos));
    
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
    c_sim_pp_p3.SaveAs(figDir+"sim_pp_3vs7.gif");
  }


  cout << "pt_mu < " << ptmumin_ << endl; 
  
  RooRealVar*f23o1hi, *f23o1pp, *rat23o1; 
  RooRealVar*f2o1hi, *f2o1pp, *rat2o1; 


  if(separate_fit){
    
    printf("\t sigma \t\t yield \t\t N23/N1 \t\t N2/N1 \n");
    dumpFitVal(fitres_hi,"HI");
    dumpFitVal(fitres_ph,"pp hire");
    dumpFitVal(fitres_pp,"pp 2.76");
    dumpFitVal(fitres_p3,"pp 7TeV");
    
    printf("separate sample fitting\n");
    double rat(0), rat_e(0);

    f23o1hi = (RooRealVar*)fitres_hi->floatParsFinal().find("N_{2S+3S}/N_{1S}");
    printf("\t (2s+3s/1s)_hi = %5.3f +%5.3f %5.3f\n",
	   f23o1hi->getVal(), f23o1hi->getErrorHi(), f23o1hi->getErrorLo() );   
    f23o1pp = (RooRealVar*)fitres_ph->floatParsFinal().find("N_{2S+3S}/N_{1S}");
    printf("\t (2s+3s/1s)_pp = %5.3f +%5.3f %5.3f\n",
	   f23o1pp->getVal(), f23o1pp->getErrorHi(), f23o1pp->getErrorLo() );   
    rat   = f23o1hi->getVal() / f23o1pp->getVal();
    rat_e = rat * sqrt( pow ( f23o1hi->getError() / f23o1hi->getVal(), 2) + pow(f23o1pp->getError() / f23o1pp->getVal(),2) ); 
    printf("\t (2s+3s/1s)_hi/(2s+3s/1s)_pp  = %5.3f +%5.3f\n",
	   rat, rat_e); 
    
    f23o1hi = (RooRealVar*)fitres_pp->floatParsFinal().find("N_{2S+3S}/N_{1S}");
    printf("\t (2s+3s/1s)_p3 = %5.3f +%5.3f %5.3f\n",
	   f23o1hi->getVal(), f23o1hi->getErrorHi(), f23o1hi->getErrorLo() );   
    f23o1pp = (RooRealVar*)fitres_p3->floatParsFinal().find("N_{2S+3S}/N_{1S}");
    printf("\t (2s+3s/1s)_p7 = %5.3f +%5.3f %5.3f\n",
	   f23o1pp->getVal(), f23o1pp->getErrorHi(), f23o1pp->getErrorLo() );   
    rat   = f23o1hi->getVal() / f23o1pp->getVal();
    rat_e = rat * sqrt( pow ( f23o1hi->getError() / f23o1hi->getVal(), 2) + pow(f23o1pp->getError() / f23o1pp->getVal(),2) ); 
    printf("\t (2s+3s/1s)_p3/(2s+3s/1s)_p7  = %5.3f +%5.3f\n",
	   rat, rat_e); 
  }
  
  if(fit_simul_hi_pp) {
    printf("simultaneous heavyion pp sample fitting\n");
    f23o1hi = (RooRealVar*)fitres_hi_pp->floatParsFinal().find("N_{2S+3S}/N_{1S}");
    printf("\t (2s+3s/1s)_pp = %5.3f +%5.3f %5.3f\n",
	   f23o1hi->getVal(), f23o1hi->getErrorHi(), f23o1hi->getErrorLo() );
    rat23o1 = (RooRealVar*)fitres_hi_pp->floatParsFinal().find("r(23/1;hi/pp)");
    printf("\t (2s+3s/1s)_hi/(2s+3s/1s)_pp = %5.3f +%5.3f %5.3f\n",
	   rat23o1->getVal(), rat23o1->getErrorHi(), rat23o1->getErrorLo() );

    f2o1hi = (RooRealVar*)fitres_hi_pp->floatParsFinal().find("N_{2S}/N_{1S}");
    printf("\t (2s/1s)_pp = %5.3f +%5.3f %5.3f\n",
	   f2o1hi->getVal(), f2o1hi->getErrorHi(), f2o1hi->getErrorLo() );
    rat2o1 = (RooRealVar*)fitres_hi_pp->floatParsFinal().find("r(2/1;hi/pp)");
    printf("\t (2s/1s)_hi/(2s/1s)_pp = %5.3f +%5.3f %5.3f\n",
	   rat2o1->getVal(), rat2o1->getErrorHi(), rat2o1->getErrorLo() );
  }

 if(fit_simul_pp_p3) {
    printf("simultaneous pp 2.76 vs 7 TeV sample fitting\n");
    f23o1hi = (RooRealVar*)fitres_pp_p3->floatParsFinal().find("N_{2S+3S}/N_{1S}");
    printf("\t (2s+3s/1s)_p7 = %5.3f +%5.3f %5.3f\n",
	   f23o1hi->getVal(), f23o1hi->getErrorHi(), f23o1hi->getErrorLo() );
    rat23o1 = (RooRealVar*)fitres_pp_p3->floatParsFinal().find("r(23/1;hi/pp)");
    printf("\t (2s+3s/1s)_p3/(2s+3s/1s)_p7 = %5.3f +%5.3f %5.3f\n",
	   rat23o1->getVal(), rat23o1->getErrorHi(), rat23o1->getErrorLo() );
  }

  return;

}

//define basic PDF
RooAbsPdf* buildPdf() {

  RooRealVar *mass = wks->var("invariantMass");

  const double M1S(9.460), M2S(10.023), M3S(10.355);
  RooRealVar *mean  = new RooRealVar("#mu_{M}","#Upsilon mean",M1S,M1S-0.3,M1S+0.3);//,"GeV");
  //mean->setVal(9.454); //fixed from pp -- tbd include gaussian constraint 
  //mean->setConstant(kTRUE);  

  RooRealVar *rat21 = new RooRealVar("rat2","mass ratio #Upsilon(1,2S)",M2S/M1S);
  RooRealVar *rat31 = new RooRealVar("rat3","mass ratio #Upsilon(1,3S)",M3S/M1S);
  rat21->setConstant(kTRUE); 
  rat31->setConstant(kTRUE); 

  RooFormulaVar *mean1S = new RooFormulaVar("mean1S","@0"   , RooArgList(*mean));
  RooFormulaVar *mean2S = new RooFormulaVar("mean2S","@0*@1", RooArgList(*mean,*rat21));
  RooFormulaVar *mean3S = new RooFormulaVar("mean3S","@0*@1", RooArgList(*mean,*rat31));

  RooRealVar *sigma1 = new RooRealVar("#sigma_{M}","Sigma_1",0.06,0.04,0.20);
  sigma1->setVal(0.092); //fixed form pp -- tbd include gaussian constraint 
  sigma1->setConstant(kTRUE);  

  RooFormulaVar *reso1S = new RooFormulaVar("reso1S","@0"             ,RooArgList(*sigma1));
  RooFormulaVar *reso2S = new RooFormulaVar("reso2S","@0*10.023/9.460",RooArgList(*sigma1));
  RooFormulaVar *reso3S = new RooFormulaVar("reso3S","@0*10.355/9.460",RooArgList(*sigma1));
  
  //signal
  RooRealVar *alpha  = new RooRealVar("CB_{#alpha}","tail shift",1.6,0.2,4);
  RooRealVar *npow   = new RooRealVar("CB_{n}","power order"    ,2.3,  1,3);
  npow ->setConstant(kTRUE);
  alpha->setConstant(kTRUE);
  //alpha->setVal(1.5);//from full fit to 7tev 3/pn data [with same model: single CB] [1.563+-0.054]
  RooCBShape  *sig1S = new RooCBShape ("sig1s", "cb 1s", *mass,*mean1S,*reso1S,*alpha,*npow); 
  RooCBShape  *sig2S = new RooCBShape ("sig2s", "cb 2s", *mass,*mean2S,*reso2S,*alpha,*npow); 
  RooCBShape  *sig3S = new RooCBShape ("sig3s", "cb 3s", *mass,*mean3S,*reso3S,*alpha,*npow); 
					  
  //background
  RooRealVar *bkg_a1  = new RooRealVar("bkg_{1}", "background a1", -0.3,-1,1);
  RooRealVar *bkg_a2  = new RooRealVar("bkg_{2}", "background a2", 0,-0.5,0.5);
  RooAbsPdf  *bkgPdf  = new RooChebychev("bkg","linear background",*mass, RooArgList(*bkg_a1,*bkg_a2));
  //RooRealVar *bkglbd  = new RooRealVar("bkg_{expo}", "background a1", 0, -2, 2);
  //RooAbsPdf   *bkgPdf = new RooExponential("bkg", "bkg exponential", *mass, *bkglbd);

  const int nt = 1000;					 
  RooRealVar *nsig1  = new RooRealVar("N_{1S}","signal 1s yield",  0.6*nt,0,10*nt);
  //RooRealVar *nsig2  = new RooRealVar("N_{2S}","signal 2s yield",  0.3*nt,0,10*nt);
  //RooRealVar *nsig3  = new RooRealVar("N_{3S}","signal 3s yield",  0.1*nt,0,10*nt);
  RooRealVar *nbkgd  = new RooRealVar("N_{bkg}","brackground yield",  5*nt,0,100*nt); 

  //const int nt = 50000;					 
  //RooRealVar *nsig1  = new RooRealVar("N_{1S}","signal 1s yield",  100,20,nt);
  //RooRealVar *nsig2  = new RooRealVar("N_{2S}","signal 2s yield",  100,20,nt);
  //RooRealVar *nsig3  = new RooRealVar("N_{3S}","signal 3s yield",  100,20,nt);
  //RooRealVar *nbkgd = new RooRealVar("N_{bkg}","brackground yield",100,20,nt); 
    
  //RooRealVar *f23os = new RooRealVar("f23os","2+3/1+2+3 sig fration",0.4,0,1); 
  //RooRealVar *f2o23 = new RooRealVar("f2o23","2/2+3 sig fration",0.75,0,1); 
  //nsig1f = new RooFormulaVar("nsig1f","@0*(1.-@1)", RooArgList(*nsig,*f23os));
  //nsig2f = new RooFormulaVar("nsig2f","@0*@1*@2", RooArgList(*nsig,*f23os,*f2o23));
  //nsig3f = new RooFormulaVar("nsig3f","@0*@1*(1.-@2)", RooArgList(*nsig,*f23os,*f2o23));

  RooFormulaVar *nsig1f, *nsig2f, *nsig3f;
  RooRealVar *f23o1 = new RooRealVar("N_{2S+3S}/N_{1S}" ,"2+3/1 sig fration",0.3,negFr,10); 
  RooRealVar *f2o1  = new RooRealVar("N_{2S}/N_{1S}"     ,"2/1  sig fration",0.3,negFr,10); 
  //RooRealVar *f3o2  = new RooRealVar("N_{3S}/N_{2S}"     ,"3/2  sig fration",0.3,negFr,10); 
  nsig1f = new RooFormulaVar("nsig1f","@0"         , RooArgList(*nsig1));
  //nsig2f = new RooFormulaVar("nsig2f","@0*@1/(1.+@2)"   , RooArgList(*nsig1,*f23o1,*f3o2));
  //nsig3f = new RooFormulaVar("nsig3f","@0*@1*@2*(1.+@3)", RooArgList(*nsig1,*f23o1,*f3o2,*f3o2));
  nsig2f = new RooFormulaVar("nsig2f","@0*@1"      , RooArgList(*nsig1,*f2o1));
  nsig3f = new RooFormulaVar("nsig3f","@0*(@1-@2)" , RooArgList(*nsig1,*f23o1,*f2o1));
  
  RooAbsPdf  *pdf   = new RooAddPdf ("simple_pdf","total signal+background pdf", 
				     RooArgList(*sig1S,*sig2S,*sig3S,*bkgPdf),
				    //RooArgList(*nsig1,*nsig2,*nsig3,*nbkgd));
				     RooArgList(*nsig1f,*nsig2f,*nsig3f,*nbkgd)
				     );

  //wks->import(*pdf);


  return pdf;

}


//define simultaneous PDF
RooSimultaneous* buildPdfSimul(RooCategory* sample) {

  RooRealVar *mass = wks->var("invariantMass");

  const double M1S(9.460), M2S(10.023), M3S(10.355);
  RooRealVar *mean  = new RooRealVar("#mu_{M}","#Upsilon mean",M1S,M1S-0.3,M1S+0.3);//,"GeV");
  mean->setVal(9.454); //fixed form pp -- tbd include gaussian constraint 
  //mean->setConstant(kTRUE);  

  RooRealVar *rat21 = new RooRealVar("rat2","mass ratio #Upsilon(1,2S)",M2S/M1S);
  RooRealVar *rat31 = new RooRealVar("rat3","mass ratio #Upsilon(1,3S)",M3S/M1S);
  rat21->setConstant(kTRUE); 
  rat31->setConstant(kTRUE); 

  RooFormulaVar *mean1S = new RooFormulaVar("mean1S","@0",RooArgList(*mean));
  RooFormulaVar *mean2S = new RooFormulaVar("mean2S","@0*@1", RooArgList(*mean,*rat21));
  RooFormulaVar *mean3S = new RooFormulaVar("mean3S","@0*@1", RooArgList(*mean,*rat31));

  RooRealVar *sigma1 = new RooRealVar("#sigma_{M}","Sigma_1",0.09,0.01,0.30);
  sigma1->setVal(0.092); //fixed form pp -- tbd include gaussian constraint 
  sigma1->setConstant(kTRUE);  

  RooFormulaVar *reso1S = new RooFormulaVar("reso1S","@0"             ,RooArgList(*sigma1));
  RooFormulaVar *reso2S = new RooFormulaVar("reso2S","@0*10.023/9.460",RooArgList(*sigma1));
  RooFormulaVar *reso3S = new RooFormulaVar("reso3S","@0*10.355/9.460",RooArgList(*sigma1));
  
  //signal
  RooRealVar *alpha  = new RooRealVar("CB_{#alpha}","tail shift",1.6,0.2,4);
  RooRealVar *npow   = new RooRealVar("CB_{n}","power order"    ,2.3,  1,3);
  npow ->setConstant(kTRUE);
  alpha->setConstant(kTRUE);//if using the constraint alpha or npow, please remove these lines

  RooCBShape  *sig1S = new RooCBShape ("sig1s", "cb 1s", *mass,*mean1S,*reso1S,*alpha,*npow); 
  RooCBShape  *sig2S = new RooCBShape ("sig2s", "cb 2s", *mass,*mean2S,*reso2S,*alpha,*npow); 
  RooCBShape  *sig3S = new RooCBShape ("sig3s", "cb 3s", *mass,*mean3S,*reso3S,*alpha,*npow); 
					  
  //background
  RooRealVar *bkg_a1  = new RooRealVar("bkg_{1}", "background a1", 0, -1, 1);
  RooRealVar *bkg_a2  = new RooRealVar("bkg_{2}", "background a2", -0.,-0.5,0.5);
  RooAbsPdf  *bkgPdf  = new RooChebychev("bkg","background",*mass, RooArgList(*bkg_a1,*bkg_a2));
  RooRealVar *bkg_a1_ctl  = new RooRealVar("bkg_{1,pp}", "background controla 1", 0, -1,1);
  RooRealVar *bkg_a2_ctl  = new RooRealVar("bkg_{2,pp}", "background controla 2", 0.,-0.5,0.5);
  RooAbsPdf  *bkgPdf_ctl  = new RooChebychev("bkg_ctl","controlbackground",*mass, RooArgList(*bkg_a1_ctl,*bkg_a2_ctl));
  //RooRealVar *bkglbd  = new RooRealVar("bkg_{expo}", "background a1", 0, -2, 2);
  //RooAbsPdf   *bkgPdf = new RooExponential("bkg", "bkg exponential", *mass, *bkglbd);

  int nt = 100;					 
  RooRealVar *nsig1  = new RooRealVar("N_{1S}","signal 1s yield",    0.6*nt,0,10*nt);
  //RooRealVar *nsig2  = new RooRealVar("N_{2S}","signal 2s yield",    0.5*nt,0,10*nt);
  //RooRealVar *nsig3  = new RooRealVar("N_{3S}","signal 3s yield",    0.3*nt,0,10*nt);
  RooRealVar *nbkgd  = new RooRealVar("N_{bkg}","brackground yield",  5*nt,0,100*nt); 

  nt*=10;
  RooRealVar *nsig1_ctl = new RooRealVar("N_{1S,pp}" ,"control signal 1s yield",  0.6*nt,0,10*nt);
  //RooRealVar *nsig2_ctl = new RooRealVar("N_{2S,pp}" ,"control signal 2s yield",  0.3*nt,0,10*nt);
  //RooRealVar *nsig3_ctl = new RooRealVar("N_{3S,pp}" ,"control signal 3s yield",  0.1*nt,0,10*nt);
  RooRealVar *nbkgd_ctl = new RooRealVar("N_{bkg,pp}","control brackground yield", 10*nt,0,100*nt);

  RooFormulaVar *nsig1f, *nsig2f, *nsig3f;
  RooFormulaVar *nsig1f_ctl, *nsig2f_ctl, *nsig3f_ctl;

  //RooRealVar *f2o1_ctl = new RooRealVar("N_{2S}/N_{1S}_{ctl}" ,"2/1 control sig fration",0.3,0,1); 
  //RooRealVar *f3o1_ctl = new RooRealVar("N_{3S}/N_{1S}_{ctl}" ,"3/1 control sig fration",0.3,0,1); 

  //RooRealVar *f3o2  = new RooRealVar("N_{3S}/N_{2S}"   ,"3/2 sig fration"  ,0.3,negFr,10); 
  
  //nsig1f = new RooFormulaVar("nsig1f","@0"              , RooArgList(*nsig1));
  //nsig2f = new RooFormulaVar("nsig2f","@0*@1/(1.+@2)"   , RooArgList(*nsig1,*f23o1,*f3o2));
  //nsig3f = new RooFormulaVar("nsig3f","@0*@1*@2*(1.+@3)", RooArgList(*nsig1,*f23o1,*f3o2,*f3o2));
  //nsig1f = new RooFormulaVar("nsig1f","@0"        , RooArgList(*nsig1));
  //nsig2f = new RooFormulaVar("nsig2f","@0*@1"  , RooArgList(*nsig1,*f2o1));
  //nsig3f = new RooFormulaVar("nsig3f","@0*@1"  , RooArgList(*nsig1,*f3o1));
  
  RooRealVar *ratio1 = new RooRealVar("r(23/1;hi/pp)","hi-pp 2s+3s/1s ratio",0.3,negFr,10); 
  RooRealVar *ratio2 = new RooRealVar("r(2/1;hi/pp)" ,"hi-pp 2s/1s ratio"   ,0.3,negFr,10); 

  RooRealVar *f23o1_ctl = new RooRealVar("N_{2S+3S}/N_{1S}","2+3/1 sig fration",0.3,negFr,10); 
  RooRealVar *f2o1_ctl  = new RooRealVar("N_{2S}/N_{1S}"   ,"2/1  sig fration" ,0.3,negFr,10); 

  RooFormulaVar *f23o1, *f2o1;
  f23o1 = new RooFormulaVar("f23o1","@0*@1" , RooArgList(*f23o1_ctl,*ratio1));
  f2o1  = new RooFormulaVar("f2o1" ,"@0*@1" , RooArgList(*f2o1_ctl ,*ratio2));

  nsig1f     = new RooFormulaVar("nsig1f","@0"             , RooArgList(*nsig1));
  nsig2f     = new RooFormulaVar("nsig2f","@0*@1"          , RooArgList(*nsig1,*f2o1));
  nsig3f     = new RooFormulaVar("nsig3f","@0*(@1-@2)"     , RooArgList(*nsig1,*f23o1,*f2o1));

  nsig1f_ctl = new RooFormulaVar("nsig1f_ctl","@0"         , RooArgList(*nsig1_ctl));
  nsig2f_ctl = new RooFormulaVar("nsig2f_ctl","@0*@1"      , RooArgList(*nsig1_ctl,*f2o1_ctl));
  nsig3f_ctl = new RooFormulaVar("nsig3f_ctl","@0*(@1-@2)" , RooArgList(*nsig1_ctl,*f23o1_ctl,*f2o1_ctl));

  /*
  nsig1f = new RooFormulaVar("nsig1f","@0"         , RooArgList(*nsig1));
  nsig2f = new RooFormulaVar("nsig2f","@0*@1"      , RooArgList(*nsig1,*f2o1));
  nsig3f = new RooFormulaVar("nsig3f","@0*(@1-@2)" , RooArgList(*nsig1,*f23o1,*f2o1));

  RooFormulaVar *f23o1_ctl,  *f2o1_ctl;
  f23o1_ctl = new RooFormulaVar("f23o1_ctl","@0/@1" , RooArgList(*f23o1,*ratio1));
  f2o1_ctl  = new RooFormulaVar("f2o1_ctl" ,"@0/@1" , RooArgList(*f2o1 ,*ratio2));

  nsig1f_ctl = new RooFormulaVar("nsig1f_ctl","@0"         , RooArgList(*nsig1_ctl));
  nsig2f_ctl = new RooFormulaVar("nsig2f_ctl","@0*@1"      , RooArgList(*nsig1_ctl,*f2o1_ctl));
  nsig3f_ctl = new RooFormulaVar("nsig3f_ctl","@0*(@1-@2)" , RooArgList(*nsig1_ctl,*f23o1_ctl,*f2o1_ctl));

   */

 RooAbsPdf* sigma_constr = new RooGaussian("sigma_constr","sigma_constraint",*sigma1,RooConst(sigma1->getVal()),RooConst(0.050));
 RooAbsPdf* alpha_constr = new RooGaussian("alpha_constr","alpha_constraint",*alpha,RooConst(alpha->getVal()),RooConst(0.2));


  RooAddPdf  *pdf_ctl  = new RooAddPdf ("pdf_ctl","total pdf control", 
					RooArgList(*sig1S,*sig2S,*sig3S,*bkgPdf_ctl),
					RooArgList(*nsig1f_ctl,*nsig2f_ctl,*nsig3f_ctl,*nbkgd_ctl)
					);
  
  RooAddPdf  *pdf_uncons = new RooAddPdf ("pdf_uncons","total pdf main", 
					RooArgList(*sig1S,*sig2S,*sig3S,*bkgPdf),
					RooArgList(*nsig1f,*nsig2f,*nsig3f,*nbkgd)
					);


  RooProdPdf *pdf_main = new RooProdPdf("pdf_main","final pdf",RooArgSet(*pdf_uncons));
  //constraint pdf
  //RooProdPdf *pdf_main = new RooProdPdf("pdf_main","final pdf",RooArgSet(*pdf_uncons,*sigma_constr,*alpha_constr));


  //RooCategory sampler("sampler","sampler") ;
  //sampler.defineType("heavyion");
  //sampler.defineType("ppreference");

  RooSimultaneous *simPdf = new RooSimultaneous("simPdf","simultaneous pdf",*sample);
  simPdf->addPdf(*pdf_ctl, "ppreference");
  simPdf->addPdf(*pdf_main,"heavyion");

  wks->import(*simPdf);

  wks->defineSet("poiSet","r(23/1;hi/pp)");
  //wks->defineSet("poiSet","N_{1S}");
  wks->defineSet("obsSet","invariantMass");
  wks->defineSet("nuisanceSet","#mu_{M}"); // does not like spaces

  return simPdf;

  //wks->import(*pdf_ctl);
  //wks->import(*pdf_main);
}


void computeLimit() {

  ModelConfig* mc = new ModelConfig("mconf", wks);
  
  RooAbsPdf* model = wks->pdf("simPdf");
  RooDataSet* data = (RooDataSet*)wks->data("combData");

  //RooFitResult* fit = model->fitTo(*data,Save());
  //RooFitResult* fit = *wks->pdf("simPdf")->fitTo(*wks->data("combData"),Save());

  //model->Print("v");
  //data->Print("v");

  mc->SetWorkspace(*wks);
  mc->SetPdf(*(wks->pdf("simPdf")));
  mc->SetObservables( *wks->set("obsSet") );
  mc->SetParametersOfInterest( *wks->set("poiSet") );
  mc->SetNuisanceParameters( *wks->set("nuisanceSet") );

  double conf_level = 0.95;

  //  StandardBayesianMCMCInterval(wks,mc, data, conf_level, 0,10000,100,"mc2.gif",1); 

			     //double left_side_tail_fraction = -1.0,
			     //int n_mcmc_iterations = 1000000,
			     //int n_mcmc_burn_in_steps = 500,
			     //const char * posterior_plot_file_name = 0,
			     //int verbosity = 1);

  bool doLp = 1; //likelihood profile
  bool doFc = 0; //Feldman-Cousins
  bool doMc = 0; //Markov-Chain monte carlo


  /// ---- likelihood ratio -------------------------------

  ProfileLikelihoodCalculator plc(*data, *mc); 
  plc.SetTestSize(1);
  plc.SetConfidenceLevel(conf_level);
  ConfInterval* lpInt = NULL;
  LikelihoodIntervalPlot plotIntLP;
  if(doLp) {
    lpInt = plc.GetInterval(); 
    plotIntLP = LikelihoodIntervalPlot(((LikelihoodInterval*)lpInt));
    plotIntLP.SetTitle("Profile Likelihood Ratio and Posterior for X23");
    //plotIntLP.SetNPoints(10);
    plotIntLP.SetRange(0,1);
  }
  /*
    define null model for ratio?
    cout get HypoTestResult (GetHypoTest()), and fom there p-value and (1-sided gaussian) significance?
  */

  
  /// ---- feldman-cousins -------------------------------

  FeldmanCousins fc(*data, *mc);
  fc.UseAdaptiveSampling(true);
  fc.FluctuateNumDataEntries(false); // number counting analysis: dataset always has 1 entry with N events observed
  fc.SetNBins(100); // number of points to test per parameter
  fc.SetTestSize(.1);
  //  fc.SaveBeltToFile(true); // optional
  ConfInterval* fcint = NULL;
  LikelihoodIntervalPlot plotIntFC;
  if(doFc) {
    fcint = fc.GetInterval();  // that was easy.
    plotIntFC = (LikelihoodInterval*)fcint;
    plotIntFC = LikelihoodIntervalPlot((LikelihoodInterval*)fcint);
    plotIntFC.SetTitle("fc interval");
  }

  /* problem:
     Exception: RooAbsTestStatistic::initSimMode() ERROR, index category of simultaneous pdf 
       is missing in dataset, aborting
     http://root.cern.ch/svn/root/trunk/roofit/roofitcore/src/RooAbsTestStatistic.cxx
     RooAbsTestStatistic::initSimMode(...)
  */

  ///.---- Markov chain monte carlo -------------------------------

  RooUniform prior("prior","",*mc->GetParametersOfInterest());
  wks->import(prior);
  mc->SetPriorPdf( *(wks->pdf("prior")) );

  RooFitResult* fit = model->fitTo(*data,Save());

  ProposalHelper ph;
  ph.SetVariables((RooArgSet&)fit->floatParsFinal());
  ph.SetCovMatrix(fit->covarianceMatrix());
  ph.SetUpdateProposalParameters(kTRUE); // auto-create mean vars and add mappings
  ph.SetCacheSize(100);
  ProposalFunction* pf = ph.GetProposalFunction();
  
  MCMCCalculator mcmc( *data, *mc );
  mcmc.SetConfidenceLevel(conf_level);
  mcmc.SetProposalFunction(*pf);
  mcmc.SetLeftSideTailFraction(0);
  //mcmc.SetNumBins(100);
  mcmc.SetNumIters(100000);    // Metropolis-Hastings algorithm iterations
  mcmc.SetNumBurnInSteps(100); // first N steps to be ignored as burn-in
  //mcmc.SetTestSize(0.1);
  /*
    for some combinations get:
    [#0] ERROR:InputArguments -- MCMCInterval::CreateVector: creation of vector failed: Number of burn-in steps (num steps to ignore) >= number of steps in Markov chain.

  */

  MCMCInterval*	mcInt = NULL;
  MCMCIntervalPlot plotIntMC;

  if(doMc) {
    mcInt = mcmc.GetInterval();
    plotIntMC = MCMCIntervalPlot(*mcInt);
  }
  
  if(doLp) {
    TCanvas* lrCanvas = new TCanvas("lrCanvas");
    //lrCanvas->Divide(2,1);
    //lrCanvas->cd(1);
    plotIntLP.Draw();
    lrCanvas->SaveAs("lr.gif");
  }    

  TCanvas* fcCanvas= NULL;
  if(doFc) {
    fcCanvas = new TCanvas("fcCanvas");
    plotIntFC.Draw();
  }

  if(doMc) {
    TCanvas mcCanvas("mcCanvas");
    mcCanvas.Divide(2);
    mcCanvas.cd(1);
    plotIntMC.Draw();
    mcCanvas.cd(2);
    plotIntMC.DrawNLLHist();
    //mcCanvas.cd(3);
    //plotIntMC.DrawNLLVsTime();
    //mcCanvas.cd(4);
    //plotIntMC.DrawWeightHist();
    mcCanvas.SaveAs("mc.gif");
  }


  RooRealVar* poi = (RooRealVar*) mc->GetParametersOfInterest()->first();
  cout << "Interval calculation for " <<poi->GetName()<< " @ :" << conf_level << ":" << endl;
  
  // Get Lower and Upper limits from Profile Calculator
  if(doLp)
    cout << "\nLR limts: ["
	 << ((LikelihoodInterval*)lpInt)->LowerLimit(*poi) << ", "
	 << ((LikelihoodInterval*)lpInt)->UpperLimit(*poi) <<"] "
	 << endl;
  
  // Get Lower and Upper limits from FeldmanCousins with profile construction
  if (doFc && fcint != NULL) {
    cout << "\nFC limts: ["
	 << ((PointSetInterval*)fcint)->LowerLimit(*poi) << ", "
	 << ((PointSetInterval*)fcint)->UpperLimit(*poi) <<"] "
	 << endl;
    double fcul = ((PointSetInterval*) fcint)->UpperLimit(*poi);
    double fcll = ((PointSetInterval*) fcint)->LowerLimit(*poi);
    //cout << "FC lower limit on s = " << fcll << endl;
    //cout << "FC upper limit on s = " << fcul << endl;
    TLine* fcllLine = new TLine(fcll, 0, fcll, 1);
    TLine* fculLine = new TLine(fcul, 0, fcul, 1);
    fcllLine->SetLineColor(kRed);
    fculLine->SetLineColor(kRed);
    fcCanvas->cd();
    fcllLine->Draw("same");
    fculLine->Draw("same");
    fcCanvas->Update();
    fcCanvas->SaveAs("fc.gif");
  }

  if(doMc)
    cout << "\nMC mc limts: ["
	 << ((MCMCInterval*)mcInt)->LowerLimit(*poi) << ", "
	 << ((MCMCInterval*)mcInt)->UpperLimit(*poi) <<"] "
	 << "\n\t actual confidence level: " << ((MCMCInterval*)mcInt)->GetActualConfidenceLevel( )
	 << endl << flush;
  
  delete model;
  delete data;
  delete poi;
  delete fcCanvas;

  return;
}

RooFitResult* fitYield(RooDataSet *data, RooAbsPdf *pdf, TString name) {

  RooFitResult* fitres;
  //double mmax(mmax_), mmin(mmin_);

  //if (name.Contains("_p3")) {
  //  if (mmax_>15) mmax = 15;
  //  if (mmin_<7) mmin = 7;
  //  //cout << name << " (" << mmin << "," << mmax << ")\n";
  //}	

  fitres = pdf->fitTo(*data, Save(), Extended(kTRUE), Minos(doMinos));//,Range(mmin,mmax));

  RooPlot *frame;
  frame = wks->var("invariantMass")->frame(Bins(nMassBins_));
  data->plotOn(frame,MarkerStyle(7), DrawOption("E"));
  pdf->plotOn(frame);
  pdf->plotOn(frame,Components("bkg"),LineStyle(kDashed));
  pdf->paramOn(frame);
  data->plotOn(frame,MarkerStyle(7), DrawOption("E"));

  if      (name.Contains("_hi"))  frame->SetTitle("Heavy Ion sample");
  else if (name.Contains("_ph"))  frame->SetTitle("pp 2.76 TeV hi_reco sample");
  else if (name.Contains("_p3"))  frame->SetTitle("pp 7 TeV sample");
  else if (name.Contains("_pp"))  frame->SetTitle("pp 2.76 TeV pp_reco sample");
    
  frame->GetXaxis()->SetTitle("#mu^{+}#mu^{-} mass (GeV/c^{2})");
  frame->GetYaxis()->SetTitleOffset(1.65);
  frame->GetYaxis()->SetTitleSize(0.033);
    
  //RooFitResult* fitres_hi = pdf->fitTo(*data_hi, Extended(kTRUE), Minos(kTRUE));
  //pdf->paramOn(frame_hi);
  
  TCanvas c;
  frame->Draw();
  c.SaveAs(figDir+"mass_fit"+name+".gif");

  return fitres;
  
}

//placeholder, 
//  need to fix + plus use more recent root version to access new roostats fucntionality
void llprof(RooDataSet *data, RooAbsPdf *pdf, RooRealVar *frac){

  RooAbsReal* nll = pdf->createNLL(*data,NumCPU(4));
  RooMinuit(*nll).migrad();

  return;

  RooPlot* frame1 = frac->frame(Bins(10),Range(0.01,0.95),Title("LL and profileLL")) ;
  nll->plotOn(frame1,ShiftToZero()) ;

  RooAbsReal* pll_frac = nll->createProfile(*frac) ;
  pll_frac->plotOn(frame1,LineColor(kRed)) ;
  
  frame1->SetMinimum(0) ;
  frame1->SetMaximum(3) ;
  
  TCanvas c1;
  frame1->Draw() ;
  c1.SaveAs("ll.gif");

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


void plotDistributions(RooDataSet* data_hi, RooDataSet* data_ph, RooDataSet* data_pp, RooDataSet* data_p3) {

    TH1* h_mass_hi = (TH1*) data_hi->createHistogram("invariantMass",nMassBins_);
    TH1* h_mass_ph = (TH1*) data_ph->createHistogram("invariantMass",nMassBins_);
    TH1* h_mass_pp = (TH1*) data_pp->createHistogram("invariantMass",nMassBins_);
    TH1* h_mass_p3 = (TH1*) data_p3->createHistogram("invariantMass",nMassBins_);
    TCanvas c_m; c_m.Divide(2,2);
    c_m.cd(1);  h_mass_hi->Draw();
    c_m.cd(2);  h_mass_ph->Draw();
    c_m.cd(3);  h_mass_pp->Draw();
    c_m.cd(4);  h_mass_p3->Draw();
    c_m.SaveAs(figDir+"mass.gif");
    
    //histogram testing, chi2, kolmogorov-smirnov test, quote p-value, d-value
    //TBD: 
    // -- sideband subtraction
    //  - fit sideband (eg exclude signal region) 
    //  - subtract (extrapoltaed) fitted background from the data
    // -- normalize histograms to same Y(1S) yield
    // -- perform compatibility tests of the two histograms
    //  http://root.cern.ch/root/html/TH1.html#TH1:Chi2Test
    // -- use pp vs p3 as calibration/cross-check

    TH1* h_mass_ks_hi =  (TH1*) h_mass_hi->Clone();
    TH1* h_mass_ks_ph =  (TH1*) h_mass_ph->Clone();
    TH1* h_mass_ks_pp =  (TH1*) h_mass_pp->Clone();
    TH1* h_mass_ks_p3 =  (TH1*) h_mass_p3->Clone();
    
    h_mass_ks_hi->Sumw2();
    h_mass_ks_ph->Sumw2();
    h_mass_ks_pp->Sumw2();
    h_mass_ks_p3->Sumw2();

    //re-normalize to common maximum (1S peak)
    h_mass_ks_hi->Scale(1./h_mass_ks_hi->GetMaximum());
    h_mass_ks_ph->Scale(1./h_mass_ks_ph->GetMaximum());
    h_mass_ks_pp->Scale(1./h_mass_ks_pp->GetMaximum());
    h_mass_ks_p3->Scale(1./h_mass_ks_p3->GetMaximum());

    h_mass_ks_hi->SetLineColor(kRed);  h_mass_ks_hi->SetMarkerColor(kRed);  h_mass_ks_hi->SetMarkerSize(0.8);  
    h_mass_ks_ph->SetLineColor(kBlue); h_mass_ks_ph->SetMarkerColor(kBlue); h_mass_ks_ph->SetMarkerSize(0.8); 
    h_mass_ks_pp->SetLineColor(kGray); h_mass_ks_pp->SetMarkerColor(kGray); h_mass_ks_pp->SetMarkerSize(0.8); 
    h_mass_ks_p3->SetLineColor(kGreen);h_mass_ks_p3->SetMarkerColor(kGreen);h_mass_ks_p3->SetMarkerSize(0.8);

    TCanvas c_ks("ks","ks",1000,500); c_ks.Divide(2,1);
    c_ks.cd(1);
    //h_mass_ks_hi->SetAxisRange(0,50,"Y");
    h_mass_ks_hi->SetAxisRange(8,14);
    h_mass_ks_ph->SetAxisRange(8,14);
    h_mass_ks_pp->SetAxisRange(8,14);
    h_mass_ks_p3->SetAxisRange(8,14);
    h_mass_ks_hi->DrawCopy();
    h_mass_ks_ph->DrawCopy("same");
    h_mass_ks_pp->DrawCopy("same");
    h_mass_ks_p3->DrawCopy("same");
    h_mass_ks_hi->SetAxisRange(9.7,10.6);
    h_mass_ks_ph->SetAxisRange(9.7,10.6);
    h_mass_ks_pp->SetAxisRange(9.7,10.6);
    h_mass_ks_p3->SetAxisRange(9.7,10.6);
    c_ks.cd(2);
    h_mass_ks_hi->SetAxisRange(0,0.6,"Y");
    h_mass_ks_hi->Draw();
    h_mass_ks_ph->Draw("same");
    //h_mass_ks_pp->Draw("same");
    //h_mass_ks_p3->Draw("same");
    c_ks.SaveAs(figDir+"mass_ks.gif");
    cout << "KS-test hi vs ph: " <<  h_mass_ks_hi->KolmogorovTest(h_mass_ks_ph,"N") << endl;
    cout << "KS-test pp vs p3: " <<  h_mass_ks_pp->KolmogorovTest(h_mass_ks_p3,"N") << endl;
    //cout << "KS-test hi vs p3: " <<  h_mass_ks_hi->KolmogorovTest(h_mass_ks_p3,"N") << endl;
    //return;

    //tbd: side-band subtracted distributions
    double k3 = 3;
    TH1* h_pt_hi = (TH1*) data_hi->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("muMinusPt",nptbins);
    h_pt_hi->Add (data_hi->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("muPlusPt",nptbins));
    TH1* h_pt_ph = (TH1*) data_ph->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("muMinusPt",nptbins);
    h_pt_ph->Add (data_ph->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("muPlusPt",nptbins));
    TH1* h_pt_pp = (TH1*) data_pp->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("muMinusPt",nptbins);
    h_pt_pp->Add (data_pp->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("muPlusPt",nptbins));
    TH1* h_pt_p3 = (TH1*) data_p3->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("muMinusPt",nptbins*k3);
    h_pt_p3->Add (data_p3->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("muPlusPt",nptbins*k3));
    //normalize
    h_pt_hi->GetXaxis()->SetRangeUser(0.9*ptmumin_,10);
    h_pt_ph->GetXaxis()->SetRangeUser(0.9*ptmumin_,10);  
    h_pt_pp->GetXaxis()->SetRangeUser(0.9*ptmumin_,10);  
    h_pt_p3->GetXaxis()->SetRangeUser(0.9*ptmumin_,10);  

    h_pt_hi->Scale(1/h_pt_hi->Integral());
    h_pt_ph->Scale(1/h_pt_ph->Integral());  
    h_pt_pp->Scale(1/h_pt_pp->Integral());  
    h_pt_p3->Scale(1/h_pt_p3->Integral()*k3);  
    TCanvas c_pt; 
    //c_pt.SetLogy();
    h_pt_hi->SetLineColor(kRed);   h_pt_hi->SetMarkerColor(kRed);    h_pt_hi->SetMarkerSize(0.8);  
    h_pt_ph->SetLineColor(kBlue);  h_pt_ph->SetMarkerColor(kBlue);   h_pt_ph->SetMarkerSize(0.8);  
    h_pt_pp->SetLineColor(kGray);  h_pt_pp->SetMarkerColor(kGray);   h_pt_pp->SetMarkerSize(0.8);  
    h_pt_p3->SetLineColor(kGreen); h_pt_p3->SetMarkerColor(kGreen);  h_pt_p3->SetMarkerSize(0.8);  
    //h_pt_p3->Draw();
    h_pt_hi->Draw();
    h_pt_ph->Draw("same");
    h_pt_pp->Draw("same");
    h_pt_p3->Draw("same");
    c_pt.SaveAs(figDir+"pt_mu.gif");


    int nbins = 10;
    TH1* h_pt_ups_hi = (TH1*) data_hi->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("upsPt",nbins);
    TH1* h_pt_ups_ph = (TH1*) data_ph->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("upsPt",nbins);
    TH1* h_pt_ups_pp = (TH1*) data_pp->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("upsPt",nbins);
    TH1* h_pt_ups_p3 = (TH1*) data_p3->reduce(Cut("invariantMass>9.2&invariantMass<10.6"))->createHistogram("upsPt",nbins*k3);
 
   //normalize
    h_pt_ups_hi->Scale(1/h_pt_ups_hi->Integral());
    h_pt_ups_ph->Scale(1/h_pt_ups_ph->Integral());  
    h_pt_ups_pp->Scale(1/h_pt_ups_pp->Integral());  
    h_pt_ups_p3->Scale(1/h_pt_ups_p3->Integral()*k3);  
    TCanvas c_pt_ups; 
    //c_pt_ups.SetLogy();
    h_pt_ups_hi->SetLineColor(kRed);   h_pt_ups_hi->SetMarkerColor(kRed);    h_pt_ups_hi->SetMarkerSize(0.8);  
    h_pt_ups_ph->SetLineColor(kBlue);  h_pt_ups_ph->SetMarkerColor(kBlue);   h_pt_ups_ph->SetMarkerSize(0.8);  
    h_pt_ups_pp->SetLineColor(kGray);  h_pt_ups_pp->SetMarkerColor(kGray);   h_pt_ups_pp->SetMarkerSize(0.8);  
    h_pt_ups_p3->SetLineColor(kGreen); h_pt_ups_p3->SetMarkerColor(kGreen);  h_pt_ups_p3->SetMarkerSize(0.8);  
    //h_pt_ups_p3->Draw();
    h_pt_ups_hi->Draw();
    h_pt_ups_ph->Draw("same");
    h_pt_ups_pp->Draw("same");
    h_pt_ups_p3->Draw("same");
    c_pt_ups.SaveAs(figDir+"pt_ups.gif");

    return;
  }


void dumpFitVal(RooFitResult *fitres, TString str) {
  RooRealVar* reso = (RooRealVar*)fitres->floatParsFinal().find("#sigma_{M}");
  RooRealVar* nevt = (RooRealVar*)fitres->floatParsFinal().find("N_{1S}");
  RooRealVar* fr23 = (RooRealVar*)fitres->floatParsFinal().find("N_{2S+3S}/N_{1S}");
  RooRealVar* fr2  = (RooRealVar*)fitres->floatParsFinal().find("N_{2S}/N_{1S}");
  
  TString resol;
  if(!reso)
    resol+="fixed";
  else
    resol = TString::Format("%4.2f +-%4.2f",reso->getVal(), reso->getError());
  //printf("separate sample fitting\n");
  //printf("\t yield \t\t sigma \t\t N23/N1 \t\t N3/N2 \n");
  printf("%s\t %s \t  %4.2f +-%4.2f \t  %4.2f +-%4.2f \t  %4.2f +-%4.2f \n", 
	 str.Data(),
	 resol.Data(), 
	 //reso->getVal(), reso->getError(),
	 nevt->getVal(), nevt->getError(),
	 fr23->getVal(), fr23->getError(),
	 fr2 ->getVal(), fr2 ->getError()
	 );
  
  return;
}

