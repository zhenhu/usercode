#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooAddPdf.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooCBShape.h"
#include "RooPlot.h"
#include "RooMCStudy.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"

#include "RooStats/ModelConfig.h"
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/LikelihoodInterval.h"
#include "RooStats/LikelihoodIntervalPlot.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TAxis.h"
#include "TPaveLabel.h"
#include "RooHist.h"
#include "TPaveText.h"
#include "TText.h"
//#include "TMath"

/*INPUTs*/

double mass_l = 7.0;
double mass_h = 14.0;
#define mmin_ mass_l 
#define mmax_ mass_h
#define fmin_ mass_l
#define fmax_ mass_h
double binw_ = 0.14;
double width_ = 0.092; //0.087;
bool plotpars = 1;//false;
bool doMinos = 1;//kFALSE;
bool PbPb = 1;
RooRealVar *f2Svs1S_pp = new RooRealVar("N_{3S}/N_{1S}pp","Y(3S)/Y(1S) yields pp ratio",0.45455,-1,5);
RooRealVar *f3Svs1S_pp = new RooRealVar("N_{2S}/N_{1S}pp","Y(2S)/Y(1S) yields pp ratio",0.32626,-1,5);
ofstream outfile("fitresults.out", ios_base::app);

TString finput;
TString figName_;
//TString finput("MassTree_TrackerMuon_pp_ppqualityCUts.root");
//TString finput("MassTree_NewCuts_hi.root");
//TString finput("MassTree_NewCuts_pp_HIrereco.root");
//TString finput("MassTree_NewCuts_pp_ppreco.root");
//TString finput("7TeV3pbHiGlobalCuts.root");
//TString finput("/afs/cern.ch/user/d/demattia/public/Trees/40pb_GlbMuon_hi_MassTree.root");

//TString figName_("Muon_pp_ppcut");
//TString figName_("masspeak_Hi"); //output fig names
//TString figName_("masspeak_pp_HIrereco");
//TString figName_("masspeak_pp");
//TString figName_("masspeak_7TeV_3pb");

TString figs_("finalplots/"); //output fig location
const TString dirname_("");//"upsilonYield"); tree location in input file 
TString paramOn_("");
TString suffix_, cut_;

using namespace RooFit;
using namespace RooStats;
void fitpeaks(int bin);
void sidebandFit(bool, RooRealVar*, RooRealVar*, RooRealVar*, RooAbsPdf*, RooAbsPdf*, RooDataSet*, RooPlot*);
void suppression(RooRealVar*, RooFitResult*, RooAbsPdf*, RooAbsPdf*, int, RooDataSet*, RooPlot*);
void setUpLimits(float xMin, float xMax, RooAbsPdf*, RooDataSet*, RooRealVar*, float baseNll);
pair<double, double> ConfidencInterval(float, RooRealVar *fnll, RooDataSet *data, RooAbsPdf *pdf);

void fitUpsilonYields(){
	gROOT->LoadMacro("setTDRStyle_modified.C");
	//setTDRStyle();

	if (PbPb) {
		finput = "MassTree_NewCuts_hi.root";
		figName_ = "masspeak_Hi"; //output fig names
	}
	else {
		finput = "MassTree_NewCuts_pp_HIrereco.root";
		figName_ = "masspeak_pp_HIrereco";
	}

	//different binning:
	fitpeaks(0);
	//	fitpeaks(1);
	//	fitpeaks(2);
	//	fitpeaks(3);
	//	fitpeaks(4);
	//	fitpeaks(5);
	//	fitpeaks(6);
	//	fitpeaks(7);
	//	fitpeaks(8);
	//	fitpeaks(9);
	//	fitpeaks(10);
	//	fitpeaks(11);
	//	fitpeaks(12);
	//	fitpeaks(13);
	//	fitpeaks(14);
	//	fitpeaks(15);
	//	fitpeaks(16);
	//	fitpeaks(17);
}

	void fitpeaks(int bin){
		switch (bin)
		{
			case 0:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && abs(upsRapidity)<2.4 && upsPt<20";  //hi acceptance for Upsilon
				//cut_="( (muPlusPt>3.5 && abs(muPlusEta)<1.6) || (muPlusPt>2.5 && abs(muPlusEta)>=1.6 && abs(muPlusEta)<2.4) ) && ( (muMinusPt>3.5 && abs(muMinusEta)<1.6) || (muMinusPt>2.5 && abs(muMinusEta)>=1.6 && abs(muMinusEta)<2.4) ) && abs(upsRapidity)<2.0";   //pp acceptance for Upsilon 
				suffix_="";
				f2Svs1S_pp->setVal(0.45455);
				//f2Svs1S_pp->setVal(0);
				f3Svs1S_pp->setVal(0.32626);
				//f3Svs1S_pp->setVal(0);
				break;
			case 1:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && abs(upsRapidity)>=0 && abs(upsRapidity)<1.2";
				suffix_="_eta0-12"; binw_=0.2;
				break;
			case 2:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && abs(upsRapidity)>=1.2 && abs(upsRapidity)<2.4";
				suffix_="_eta12-24"; binw_=0.2;
				break;
			case 3:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=0 && Centrality<4";
				suffix_="_cntr0-10"; binw_=0.2;
				break;
			case 4:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=4 && Centrality<8";
				suffix_="_cntr10-20"; binw_=0.2;
				break;
			case 5:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=8 && Centrality<50";
				suffix_="_cntr20-100"; binw_=0.2;
				break;
			case 6:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=0 && upsPt<6.5";
				suffix_="_upsPt0-65"; binw_=0.2;
				break;
			case 7:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=6.5 && upsPt<10";
				suffix_="_upsPt65-100"; binw_=0.2;
				break;
			case 8:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=10 && upsPt<20";
				suffix_="_upsPt100-200"; binw_=0.2;
				break;
			case 9:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=0 && upsPt<5";
				suffix_="_upsPt0-50"; binw_=0.2;
				break;
			case 10:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=5.0 && upsPt<20";
				suffix_="_upsPt50-200"; binw_=0.2;
				break;
			case 11:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=6.5 && upsPt<20";
				suffix_="_upsPt65-200"; binw_=0.2;
				break;
			case 12:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=0 && Centrality<8";
				suffix_="_cntr0-20"; binw_=0.2;
				break;
			case 13:
				cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=4 && Centrality<50";
				suffix_="_cntr10-100"; binw_=0.2;
				break;
			case 14:
				cut_="muPlusPt > 3.0 && muMinusPt > 3.0 && abs(upsRapidity)<2.4 && upsPt<20"; 
				suffix_="_MuonPT3"; binw_=0.14; 
				f2Svs1S_pp->setVal(0.272881);
				f3Svs1S_pp->setVal(0.215646);
				break;
			case 15:
				cut_="muPlusPt > 3.5 && muMinusPt > 3.5 && abs(upsRapidity)<2.4 && upsPt<20"; 
				suffix_="_MuonPT4_2"; binw_=0.14;
				f2Svs1S_pp->setVal(0.313659);
				f3Svs1S_pp->setVal(0.230575);
				break;
			case 16:
				cut_="muPlusPt > 4.5 && muMinusPt > 4.5 && abs(upsRapidity)<2.4 && upsPt<20"; 
				suffix_="_MuonPT45"; binw_=0.14;
				f2Svs1S_pp->setVal(0.641356);
				f3Svs1S_pp->setVal(0.509932);
				break;
			case 17:
				cut_="muPlusPt > 5.0 && muMinusPt > 5.0 && abs(upsRapidity)<2.4 && upsPt<20";  
				suffix_="_MuonPT5"; binw_=0.14;
				f2Svs1S_pp->setVal(1.22348);
				f3Svs1S_pp->setVal(0.560287);
				break;

			default:
				cout<<"error in binning"<<endl;
				break;
		}

		cout << "oniafitter processing"
			<< "\n\tInput:  \t" << finput
			<< "\n\tresults:\t" << figs_
			<< endl;
		ofstream outfile("fitresults.out", ios_base::app);
		outfile<<endl<<"**********"<<suffix_<<"**********"<<endl<<endl;

		RooRealVar* mass  = new RooRealVar("invariantMass","#mu#mu mass",mmin_,mmax_,"GeV/c^{2}");
		mass->setRange("R1",7.0,8.8);
		mass->setRange("R2",8.8,10.6);
		mass->setRange("R3",10.6,14);
		const double M1S = 9.46;   //upsilon 1S pgd mass value
		const double M2S = 10.02;  //upsilon 2S pgd mass value
		const double M3S = 10.35;  //upsilon 3S pgd mass value

		RooRealVar *mean    = new RooRealVar("#mu_{#Upsilon(1S)}","#Upsilon mean",M1S,M1S-0.1,M1S+0.1);
		RooRealVar *shift21 = new RooRealVar("shift2","mass diff #Upsilon(1,2S)",M2S-M1S);
		RooRealVar *shift31 = new RooRealVar("shift3","mass diff #Upsilon(1,3S)",M3S-M1S);
		RooRealVar *mscale  = new RooRealVar("mscale","mass scale factor",1.,0.7,1.3);
		mscale->setConstant(kTRUE); /* the def. parameter value is fixed in the fit */

		RooFormulaVar *mean1S = new RooFormulaVar("mean1S","@0",
				RooArgList(*mean));
		RooFormulaVar *mean2S = new RooFormulaVar("mean2S","@0+@1*@2",
				RooArgList(*mean,*mscale,*shift21));
		RooFormulaVar *mean3S = new RooFormulaVar("mean3S","@0+@1*@2",
				RooArgList(*mean,*mscale,*shift31));

		RooRealVar *sigma1 = new RooRealVar("sigma","Sigma_1",0.10,0.01,0.30);    //detector resolution
		RooRealVar *sigma2 = new RooRealVar("#sigma_{#Upsilon(1S)}","Sigma_1S",0.06,0.01,0.30); //Y(1S) resolution
		RooFormulaVar *reso1S = new RooFormulaVar("reso1S","@0"             ,RooArgList(*sigma2));
		RooFormulaVar *reso2S = new RooFormulaVar("reso2S","@0*10.023/9.460",RooArgList(*sigma2));
		RooFormulaVar *reso3S = new RooFormulaVar("reso3S","@0*10.355/9.460",RooArgList(*sigma2));

		/// to describe final state radiation tail on the left of the peaks
		RooRealVar *alpha  = new RooRealVar("alpha","tail shift",1.6,0.2,4);
		//RooRealVar *alpha  = new RooRealVar("alpha","tail shift",1.7,0.2,4);
		RooRealVar *npow   = new RooRealVar("npow","power order",2.3,1,3);
		npow ->setConstant(kTRUE);
		alpha->setConstant(kTRUE);

		/// relative fraction of the two peak components 
		RooRealVar *sigmaFraction = new RooRealVar("sigmaFraction","Sigma Fraction",0.3,0.,1.);
		sigmaFraction->setVal(0);
		sigmaFraction->setConstant(kTRUE);

		/// Upsilon 1S
		//RooCBShape  *gauss1S1 = new RooCBShape ("gauss1S1", "FSR cb 1s",
		//                  *mass,*mean1S,*sigma1,*alpha,*npow);
		RooCBShape  *gauss1S2 = new RooCBShape ("gauss1S2", "FSR cb 1s",
				*mass,*mean1S,*reso1S,*alpha,*npow);
		//RooAddPdf *sig1S      = new RooAddPdf  ("sig1S","1S mass pdf",
		//                  RooArgList(*gauss1S1,*gauss1S2),*sigmaFraction);

		//mean->setVal(9.46);
		//mean->setConstant(kTRUE);
		sigma1->setVal(0);
		sigma1->setConstant(kTRUE);
		sigma2->setVal(width_);        //fix the resolution
		sigma2->setConstant(kTRUE);

		/// Upsilon 2S
		RooCBShape  *gauss2S1 = new RooCBShape ("gauss2S1", "FSR cb 2s", 
				*mass,*mean2S,*sigma1,*alpha,*npow); 
		RooCBShape  *gauss2S2 = new RooCBShape ("gauss2S2", "FSR cb 2s", 
				*mass,*mean2S,*reso2S,*alpha,*npow); 
		RooAddPdf *sig2S      = new RooAddPdf  ("sig2S","2S mass pdf",
				RooArgList(*gauss2S1,*gauss2S2),*sigmaFraction);

		/// Upsilon 3S
		RooCBShape  *gauss3S1 = new RooCBShape ("gauss3S1", "FSR cb 3s", 
				*mass,*mean3S,*sigma1,*alpha,*npow); 
		RooCBShape  *gauss3S2 = new RooCBShape ("gauss3S2", "FSR cb 3s", 
				*mass,*mean3S,*reso3S,*alpha,*npow); 
		RooAddPdf *sig3S      = new RooAddPdf  ("sig3S","3S mass pdf",
				RooArgList(*gauss3S1,*gauss3S2),*sigmaFraction);

		/// Background
		RooRealVar *bkg_a1  = new RooRealVar("bkg_{a1}", "background a1", 0, -1, 1);
		RooRealVar *bkg_a2  = new RooRealVar("bkg_{a2}", "background a2", 0, -1, 1);
		RooAbsPdf  *bkgPdf  = new RooChebychev("bkg","background",
				*mass, RooArgList(*bkg_a1,*bkg_a2));
		//bkg_a1->setVal(0);
		//bkg_a1->setConstant(kTRUE);
		//bkg_a2->setVal(0);
		//bkg_a2->setConstant(kTRUE);

		// only sideband region pdf, using RooPolynomial instead of RooChebychev for multiple ranges fit
		RooRealVar *SB_bkg_a1  = new RooRealVar("SB bkg_{a1}", "background a1", 0, -1, 1);
		RooRealVar *SB_bkg_a2  = new RooRealVar("SB bkg_{a2}", "background a2", 0, -1, 1);
		RooAbsPdf  *SB_bkgPdf  = new RooPolynomial("SB_bkg","side-band background",
				*mass, RooArgList(*SB_bkg_a1,*SB_bkg_a2));

		/// Combined pdf
		int nt = 100000;
		//bool fitfraction = true;
		RooRealVar *nbkgd = new RooRealVar("N_{bkg}","nbkgd",nt*0.75,0,10*nt);
		RooRealVar *SB_nbkgd = new RooRealVar("SB N_{bkg}","SB_nbkgd",nt*0.75,0,10*nt);
		RooRealVar *nsig1f  = new RooRealVar("N_{#Upsilon(1S)}","nsig1S",   nt*0.25,0,10*nt);

		//use the YIELDs of 2S and 3S as free parameters
		//RooRealVar *nsig2f  = new RooRealVar("N_{#Upsilon(2S)}","nsig2S",   nt*0.25,0,10*nt);
		//RooRealVar *nsig3f  = new RooRealVar("N_{#Upsilon(3S)}","nsig3S",   nt*0.25,0,10*nt);

		//use the RATIOs of 2S and 3S as free parameters
		RooRealVar *f2Svs1S = new RooRealVar("N_{2S}/N_{1S}","f2Svs1S",0.4,-0.1,1.4);
		//RooRealVar *f3Svs1S = new RooRealVar("N_{3S}/N_{1S}","f3Svs1S",0.3,-0.1,1.4);
		RooRealVar *f23vs1S = new RooRealVar("N_{2S+3S}/N_{1S}","f23vs1S",0.5,-0.1,1.4);
		RooFormulaVar *nsig2f = new RooFormulaVar("nsig2S","@0*@1", RooArgList(*nsig1f,*f2Svs1S));
		//RooFormulaVar *nsig3f = new RooFormulaVar("nsig3S","@0*@1", RooArgList(*nsig1f,*f3Svs1S));
		RooFormulaVar *nsig3f = new RooFormulaVar("nsig3S","@0*@2-@0*@1", RooArgList(*nsig1f,*f2Svs1S,*f23vs1S));

		//force the ratio to the pp value
		f2Svs1S_pp->setConstant(kTRUE);
		f3Svs1S_pp->setConstant(kTRUE);
		RooFormulaVar *nsig2f_ = new RooFormulaVar("nsig2S_pp","@0*@1", RooArgList(*nsig1f,*f2Svs1S_pp)); 
		RooFormulaVar *nsig3f_ = new RooFormulaVar("nsig3S_pp","@0*@1", RooArgList(*nsig1f,*f3Svs1S_pp)); 

		//only sideband region pdf, using RooPolynomial instead of RooChebychev for multiple ranges fit
		RooAbsPdf  *SB_pdf = new RooAddPdf ("SB_pdf","sideband background pdf",
				RooArgList(*SB_bkgPdf),
				RooArgList(*SB_nbkgd));
		//only signal region pdf, using RooPolynomial instead of RooChebychev for multiple ranges fit
		RooAbsPdf  *S_pdf   = new RooAddPdf ("S_pdf","total signal+background pdf",
				RooArgList(*gauss1S2,*sig2S,*sig3S,*SB_bkgPdf),
				RooArgList(*nsig1f,*nsig2f,*nsig3f,*SB_nbkgd));

		//default pdf
		RooAbsPdf  *pdf   = new RooAddPdf ("pdf","total signal+background pdf",
				RooArgList(*gauss1S2,*sig2S,*sig3S,*bkgPdf),
				RooArgList(*nsig1f,*nsig2f,*nsig3f,*nbkgd));

		//pdf with fixed ratio of the pp ratio
		RooAbsPdf  *pdf_pp   = new RooAddPdf ("pdf_pp","total signal+background pdf",
				RooArgList(*gauss1S2,*sig2S,*sig3S,*bkgPdf),
				RooArgList(*nsig1f,*nsig2f_,*nsig3f_,*nbkgd));

		/*
		/// Background pdf for the pre-fit with only Y(1S) peak 
		RooRealVar *bkg_a1_pre  = new RooRealVar("bkg_a1_pre", "background a1", 0, -1, 1);
		RooRealVar *bkg_a2_pre  = new RooRealVar("bkg_a2_pre", "background a2", 0, -1, 1);
		RooAbsPdf  *bkgPdf_pre  = new RooChebychev("bkgPdf_pre","background",
		 *mass, RooArgList(*bkg_a1_pre,*bkg_a2_pre));
		//bkg_a2_pre->setVal(0);
		//bkg_a2_pre->setConstant(kTRUE);
		/// signl pdf for th pre-fit with only Y(1S) peak
		RooRealVar *nsig_pre  = new RooRealVar("nsig_pre","signal 1 yield",nt*0.25,0,10*nt);
		RooRealVar *nbkgd_pre = new RooRealVar("nbkgd_pre","brackground 1 yield",nt*0.75,0,10*nt);
		RooAbsPdf  *pdf_pre = new RooAddPdf ("pdf_pre","1S signal+background pdf",
		RooArgList(*gauss1S2,*bkgPdf_pre),
		RooArgList(*nsig_pre,*nbkgd_pre));
		 */

		//read the data
		TFile f(finput,"read");
		gDirectory->Cd(finput+":/"+dirname_);
		TTree* theTree     = (TTree*)gROOT->FindObject("UpsilonTree");
		RooRealVar* upsPt  = new RooRealVar("upsPt","p_{T}(#Upsilon)",0,60,"GeV");
		RooRealVar* upsEta = new RooRealVar("upsEta",  "upsEta"  ,-7,7);
		RooRealVar* upsRapidity = new RooRealVar("upsRapidity",  "upsRapidity"  ,-2.4,2.4);
		RooRealVar* vProb = new RooRealVar("vProb",  "vProb"  ,0,1);
		RooRealVar* QQsign = new RooRealVar("QQsign",  "QQsign"  ,-1,5);
		RooRealVar* weight = new RooRealVar("weight",  "weight"  ,-2,2);
		if (PbPb) RooRealVar* Centrality = new RooRealVar("Centrality",  "Centrality"  ,0,40);
		RooRealVar* muPlusPt = new RooRealVar("muPlusPt","muPlusPt",0,50);
		RooRealVar* muPlusEta = new RooRealVar("muPlusEta","muPlusEta",-2.5,2.5);
		RooRealVar* muMinusPt = new RooRealVar("muMinusPt","muMinusPt",0,50);
		RooRealVar* muMinusEta = new RooRealVar("muMinusEta","muMinusEta",-2.5,2.5);

		RooDataSet* data0, *data;
		if (PbPb) data0 = new RooDataSet("data","data",theTree,RooArgSet(*mass,*upsRapidity,*vProb,*upsPt,*Centrality,*muPlusPt,*muMinusPt));
		//data0 = new RooDataSet("data","data",theTree,RooArgSet(*mass,*upsRapidity,*upsPt,*muPlusPt,*muMinusPt,*QQsign,*weight));
		else data0 = new RooDataSet("data","data",theTree,RooArgSet(*mass,*upsRapidity,*upsPt,*muPlusPt,*muMinusPt,*muPlusEta,*muMinusEta));
		data0->Print();
		data = ( RooDataSet*) data0->reduce(Cut(cut_));
		data->Print();

		//the pre-fit with only Y(1S) pdf
		//RooFitResult* fit_1st = pdf_pre->fitTo(*data,Range("R1,R2"),Save(kTRUE));
		//RooFitResult* fit_1st = pdf_pre->fitTo(*data,Save(kTRUE),Extended(kTRUE));
		//mean->setConstant(kTRUE);

		//plot
		TCanvas c; c.cd();
		int nbins = ceil((mmax_-mmin_)/binw_); 
		RooPlot* frame = mass->frame(Bins(nbins),Range(mmin_,mmax_));
		data->plotOn(frame,Name("theData"),MarkerSize(0.8));
		//pdf_pre->plotOn(frame,LineColor(kRed));
		//pdf_pre->plotOn(frame,Components(bkgPdf_pre),LineStyle(kDashed));
		//if(plotpars) pdf_pre->paramOn(frame,Layout(0.65));

		//the nominal fit with default pdf 
		RooFitResult* fit_2nd = pdf->fitTo(*data,Save(kTRUE),Extended(kTRUE),Minos(doMinos));
		//plot
		pdf->plotOn(frame,Name("thePdf"));
		pdf->plotOn(frame,Components("bkg"),Name("theBkg"),LineStyle(kDashed));
		RooArgSet * pars = pdf->getParameters(data);
		int nfloatpars = pars->selectByAttrib("Constant",kFALSE)->getSize();
		float myndof = frame->GetNbinsX() - nfloatpars;
		double mychsq = frame->chiSquare("thePdf","theData",nfloatpars)*myndof;
		if(plotpars) {
			paramOn_ = "_paramOn";
			pdf->paramOn(frame,Layout(0.5,0.9,0.95),Label(Form("#chi^{2}/ndf = %2.1f/%2.0f", mychsq,myndof)));
		}
		else paramOn_ = "";

		outfile<<"Y(1S) yield  : = "<<nsig1f->getVal()<<" +/- "<<nsig1f->getError()<<endl<<endl;
		outfile<<"2S/1S        : = "<<f2Svs1S->getVal()<<" +/- "<<f2Svs1S->getError()<<endl<<endl;
		outfile<<"(3S+2S)/1S   : = "<<f23vs1S->getVal()<<" +/- "<<f23vs1S->getError()<<endl<<endl;
		outfile<<"2S/1S suppression  : = "<< f2Svs1S->getVal()/f2Svs1S_pp->getVal() <<endl<<endl;
		outfile<<"(3S+2S)/1S suppression  : = "<< f23vs1S->getVal()/(f2Svs1S_pp->getVal()+f3Svs1S_pp->getVal())<<endl<<endl;
		outfile<<"free parameter = "<< nfloatpars << ", mychi2 = " << mychsq << ", ndof = " << myndof  << endl << endl;

		//draw and save plots
		data->plotOn(frame,MarkerSize(0.8));
		frame->SetTitle( "" );
		frame->GetXaxis()->SetTitle("#mu#mu invariant mass [GeV/c^{2}]");
		//frame->GetYaxis()->SetTitleOffset(0.9);//(1.3);
		//frame->GetYaxis()->SetLabelSize(0.05);
		frame->Draw();
		if(!plotpars) {
			if (PbPb){
				TLatex latex1;
				latex1.DrawLatex(10.2,57, "CMS, PbPb, #sqrt{s_{NN}} = 2.76 TeV");   
				TLatex latex2;
				latex2.DrawLatex(10.2,50,"p_{T}^{#mu} > 4 GeV/c, |#eta^{#mu}| < 2.4");   
				TLatex latex3;
				latex3.DrawLatex(10.2,43,"p_{T}^{#Upsilon} < 20 GeV/c");
				TLatex latex5;
				latex5.DrawLatex(10.2,36,"L_{int} = 7.28 #mub^{-1}");
				TLatex latex4;
				latex4.DrawLatex(7.5,57, "b)");
			}
			else {
				TLatex latex1;
				latex1.DrawLatex(10.2,71, "CMS, pp, #sqrt{s} = 2.76 TeV");   
				TLatex latex2;
				latex2.DrawLatex(10.2,62,"p_{T}^{#mu} > 4 GeV/c, |#eta^{#mu}| < 2.4");   
				TLatex latex3;
				latex3.DrawLatex(10.2,53,"p_{T}^{#Upsilon} < 20 GeV/c");
				TLatex latex5;
				latex5.DrawLatex(10.2,44,"L_{int} = 225 nb^{-1}");
				TLatex latex4;
				latex4.DrawLatex(7.5,71, "a)");
			}		

		}
		//	c.SaveAs(figs_+figName_+paramOn_+suffix_+".root");
		//	c.SaveAs(figs_+figName_+paramOn_+suffix_+".eps");
		c.SaveAs(figs_+figName_+paramOn_+suffix_+".gif");
		c.SaveAs(figs_+figName_+paramOn_+suffix_+".pdf");

		//overlay the pp ratio, calculate the significance of suppression
		if (PbPb) suppression(nsig1f, fit_2nd, nfloatpars, pdf, pdf_pp, data, frame);

		//setup the limits
		float baseNll = fit_2nd->minNll();
		setUpLimits(-0.08, 0.92, pdf, data, f23vs1S, baseNll);
		//setUpLimits(-0.1, 0.9, pdf, data, f2Svs1S, baseNll);

		//calculate the confidence interval with RooStats
		ConfidencInterval(0.95, f23vs1S, data, pdf);
		//ConfidencInterval(0.95, f2Svs1S, data, pdf);

		//sidebandFit
		sidebandFit(1, SB_bkg_a1, SB_bkg_a2, SB_nbkgd, S_pdf, SB_pdf, data, frame);

		// Print fit results 
		cout << endl << "figure name: "<< figName_ << endl << endl;
		//cout << "the pre-fit with only sideband pdf" << endl ;
		//fit_1st->Print() ;
		cout << "the nominal fit with the default pdf " << endl ;
		fit_2nd->Print() ;
		cout << "  free parameter = "<< nfloatpars << ", mychi2 = " << mychsq << ", ndof = " << myndof << endl << endl;
	}


void sidebandFit(bool range, RooRealVar *SB_bkg_a1, RooRealVar *SB_bkg_a2, RooRealVar *SB_nbkgd, RooAbsPdf *S_pdf, RooAbsPdf *SB_pdf, RooDataSet *data, RooPlot *frame){
	TCanvas c3; c3.cd();
	frame->remove("thePdf");
	frame->remove("theBkg");
	frame->remove("thePdf_pp");
	RooFitResult* fit_SB = SB_pdf->fitTo(*data,Range("R1,R3"), Save(kTRUE),Extended(kTRUE),Minos(doMinos));
	SB_pdf->plotOn(frame,Name("theBkg_SB"),LineColor(kRed));
	if(plotpars) {
		SB_pdf->paramOn(frame,Layout(0.5,0.9,0.65));
	}   
	SB_bkg_a1->setConstant(kTRUE);
	SB_bkg_a2->setConstant(kTRUE);

	if (!range) {
		//fit full mass spectrum
		RooFitResult* fit_S = S_pdf->fitTo(*data,Save(kTRUE),Extended(kTRUE),Minos(doMinos));
		S_pdf->plotOn(frame,Name("thePdf_SB"));
		RooArgSet * pars = S_pdf->getParameters(data);
		int nfloatpars = pars->selectByAttrib("Constant",kFALSE)->getSize();
		float myndof = frame->GetNbinsX() - nfloatpars;
		double mychsq = frame->chiSquare("thePdf_SB","theData",nfloatpars)*myndof;
	}
	else {
		//fit in the signal range only
		if (PbPb) SB_nbkgd->setVal(SB_nbkgd->getVal()*0.90);
		else SB_nbkgd->setVal(SB_nbkgd->getVal()*0.97);
		SB_nbkgd->setConstant(kTRUE);
		RooFitResult* fit_S = S_pdf->fitTo(*data,Range("R2"),Save(kTRUE),Extended(kTRUE),Minos(doMinos));
		S_pdf->plotOn(frame,/*Range("Full"),*/Name("thePdf_SB"));
		RooArgSet * pars = S_pdf->getParameters(data);
		//calculate chi2 in a mass range
		float bin_Min = (8.8-mmin_)/binw_;
		float bin_Max = (10.6-mmin_)/binw_;
		int binMin = ceil(bin_Min);
		int binMax = ceil(bin_Max);
		int nfloatpars = pars->selectByAttrib("Constant",kFALSE)->getSize();
		//float myndof = frame->GetNbinsX() - nfloatpars;
		float myndof = ceil((10.6-8.8)/binw_) - nfloatpars;
		cout<<binMin<<" "<<binMax<<" "<<nfloatpars<<" "<<myndof<<endl;
		double mychsq = frame->mychiSquare("thePdf_SB","theData",nfloatpars,true,binMin,binMax)*myndof;
	}
	if(plotpars) {
		paramOn_ = "_paramOn";
		S_pdf->paramOn(frame,Layout(0.5,0.9,0.95),Label(Form("#chi^{2}/ndf = %2.1f/%2.0f", mychsq,myndof)));
	}   
	else paramOn_ = ""; 

	cout << endl << "figure name: "<< figName_ << endl << endl;
	cout << "the sideband pdf" << endl ;
	fit_SB->Print() ;
	cout << "the signal pdf " << endl ;
	fit_S->Print() ;
	data->plotOn(frame,MarkerSize(0.8));
	frame->Draw();
	if(!plotpars) {
		if (PbPb){
			TLatex latex1;
			latex1.DrawLatex(10.2,57, "CMS, PbPb, #sqrt{s_{NN}} = 2.76 TeV");   
			TLatex latex2;
			latex2.DrawLatex(10.2,50,"p_{T}^{#mu} > 4 GeV/c, |#eta^{#mu}| < 2.4");   
			TLatex latex3;
			latex3.DrawLatex(10.2,43,"p_{T}^{#Upsilon} < 20 GeV/c");
			TLatex latex5;
			latex5.DrawLatex(10.2,36,"L_{int} = 7.28 #mub^{-1}");
			TLatex latex4;
			latex4.DrawLatex(7.5,57, "b)");
		}   
		else {
			TLatex latex1;
			latex1.DrawLatex(10.2,71, "CMS, pp, #sqrt{s} = 2.76 TeV");   
			TLatex latex2;
			latex2.DrawLatex(10.2,62,"p_{T}^{#mu} > 4 GeV/c, |#eta^{#mu}| < 2.4");   
			TLatex latex3;
			latex3.DrawLatex(10.2,53,"p_{T}^{#Upsilon} < 20 GeV/c");
			TLatex latex5;
			latex5.DrawLatex(10.2,44,"L_{int} = 225 nb^{-1}");
			TLatex latex4;
			latex4.DrawLatex(7.5,71, "a)");
		}            

	}   
	c3.SaveAs(figs_+"sideband_"+figName_+paramOn_+suffix_+".gif");
	c3.SaveAs(figs_+"sideband_"+figName_+paramOn_+suffix_+".pdf");
}

//calculate the confidence interval with RooStats
pair<double, double> ConfidencInterval(float CI, RooRealVar *fnll, RooDataSet *data, RooAbsPdf *pdf)  {  
	ProfileLikelihoodCalculator pl(*data,*pdf,*fnll);
	pl.SetConfidenceLevel(CI); // 95% interval
	LikelihoodInterval* interval = pl.GetInterval();
	LikelihoodIntervalPlot plot(interval);
	TCanvas c4; c4.cd(); 
	plot.Draw();
	TString intrvlName = fnll->GetTitle();
	c4.SaveAs(figs_+"nll_"+intrvlName+"_pp.gif");
	c4.SaveAs(figs_+"nll_"+intrvlName+"_pp.pdf");
	// print out the iterval on the Parameter of Interest
	cout <<endl<< CI <<"\% interval on " <<fnll->GetName()<<" is : ["<<
		interval->LowerLimit(*fnll) << ", "<<
		interval->UpperLimit(*fnll) << "] "<<endl;
	pair<double, double> CnfdncIntrvl;
	CnfdncIntrvl.first  = interval->LowerLimit(*fnll);
	CnfdncIntrvl.second = interval->UpperLimit(*fnll);
	return CnfdncIntrvl;
}


void suppression(RooRealVar *nsig1f, RooFitResult *fit_2nd, int nfloatpars, RooAbsPdf *pdf, RooAbsPdf *pdf_pp, RooDataSet *data, RooPlot *frame){
	//the layout fit with pp ratio pdf
	//nsig1f->setVal(84.47);
	TCanvas c1; c1.cd();
	//pdf->plotOn(frame,Name("thePdf"));
	nsig1f->setConstant(kTRUE);  //fix the 1S yield to the value from the default fit 
	RooFitResult* fit_3rd = pdf_pp->fitTo(*data,Save(kTRUE),Extended(kTRUE));
	pdf_pp->plotOn(frame,Name("thePdf_pp"),LineStyle(kDashed),LineColor(kRed));
	RooArgSet * pars_pp = pdf_pp->getParameters(data);
	int nfloatpars_pp = pars_pp->selectByAttrib("Constant",kFALSE)->getSize();
	float nll2 = fit_2nd->minNll();
	float nll3 = fit_3rd->minNll();
	double chi = 2.0*(nll3-nll2);
	int deltaNDOF = nfloatpars-nfloatpars_pp;
	double cl = 1.0 - TMath::Prob(chi,deltaNDOF)/2;
	double Significance = -RooStats::PValueToSignificance(cl);
	outfile<<endl<<"*************************************"<<endl;
	outfile<<"the delta of S is         : "<<nll3-nll2<<endl;
	outfile<<"the delta of ndof is      : "<<deltaNDOF<<endl;
	outfile<<"the C.L. is               : "<<cl<<endl;
	outfile<<"the significance level is : "<<Significance<<" (one side)"<<endl;
	outfile<<"*************************************"<<endl<<endl;
	outfile<<"the C.L. is : "<<cl<<",  the significance level is : "<<Significance<<" (one side)"<<endl<<endl;
	//draw and save plots
	data->plotOn(frame,MarkerSize(0.8));
	frame->Draw();
	if(!plotpars) {
		TLatex latex1;
		latex1.DrawLatex(10.4,57, "CMS, PbPb, #sqrt{s} = 2.76 TeV");
		TLatex latex2;
		latex2.DrawLatex(10.4,50,"p_{T}^{#mu} > 4 GeV/c, |#eta^{#mu}| < 2.4");
		TLatex latex3;
		latex3.DrawLatex(10.4,43,"p_{T}^{#Upsilon} < 20 GeV/c");
		TLatex latex4;
		latex4.DrawLatex(7.5,57, "b)");
		TLatex latex5;
		latex5.DrawLatex(12,30, "pp lineshape");
		TLatex latex6;
		latex5.DrawLatex(12,23, "PbPb fit");
		TLine L1(11.4,31,11.9,31);
		L1.SetLineColor(kRed);
		L1.SetLineStyle(kDashed);
		L1.SetLineWidth(2);
		L1.Draw();
		TLine L2(11.4,24,11.9,24);
		L2.SetLineColor(kBlue);
		L2.SetLineWidth(2);
		L2.Draw();
	}

	//c1.SaveAs(figs_+"overlay1_"+figName_+paramOn_+suffix_+".root");
	//c1.SaveAs(figs_+"overlay1_"+figName_+paramOn_+suffix_+".eps");
	c1.SaveAs(figs_+"overlay1_"+figName_+paramOn_+suffix_+".gif");
	c1.SaveAs(figs_+"overlay1_"+figName_+paramOn_+suffix_+".pdf");
	nsig1f->setConstant(kFALSE);
}


void setUpLimits(float xMin, float xMax, RooAbsPdf *pdf, RooDataSet *data, RooRealVar *param, float baseNll){
	//setting up upper limits
	TCanvas c2; c2.cd();
	int totalBins = 100;
	float BinWidth = (xMax - xMin)/totalBins;
	TH1F *h1 = new TH1F("h1","h1",totalBins,xMin,xMax);
	h1->GetXaxis()->SetTitle(param->getTitle());
	//h1->GetXaxis()->SetRangeUser(-0.1,0.9);
	h1->GetYaxis()->SetTitle("Maximum likelihood");
	TH1F *h2 = new TH1F("h2","h2",totalBins,xMin,xMax);
	gStyle->SetOptStat(kFALSE);
	RooFitResult* fit_nll;
	double MinNll, L, cl;
	for (int i=1; i<=totalBins; i++) {
		param->setVal(xMin + BinWidth*(i-1));
		param->setConstant(kTRUE);
		fit_nll = pdf->fitTo(*data,Save(kTRUE));
		MinNll = fit_nll->minNll()-baseNll;
		L = TMath::Exp(-MinNll);
		cout<<"x = "<<param->getVal()<<", MinNll = "<<MinNll<<", L = "<<L<<endl;
		h1->SetBinContent(i,L);
	}
	for (int i=1; i<=totalBins; i++) {
		cout<<"bin "<<i<<" = "<< h1->GetBinContent(i)<<endl;
	}
	h1->Draw();
	cout<<endl<<"integral = "<<h1->Integral(1,totalBins)<<endl<<endl;
	h1->Scale(1.0/h1->Integral(1,totalBins));
	h1->Draw();
	c2.Update();

	//convoluted with systematic gaussian
	TH1F *h3 = new TH1F("h3","h3",totalBins,xMin,xMax);
	TH1F *h4 = new TH1F("h4","h4",totalBins,xMin,xMax);
	for (int i=1; i<=totalBins; i++) {
		float gausmean = xMin + BinWidth*(i-1);
		cout<<"gausmean = "<<gausmean;
		float gaussigma = 0.00001;
		TH1F *h_syst = new TH1F("h_syst","syst histogram",totalBins,xMin,xMax);
		for (Int_t k=0;k<10000;k++) {h_syst->Fill(gRandom->Gaus(gausmean,gaussigma));}
		double new_nll = 0;
		for (int j=1; j<=totalBins; j++){
			new_nll += (h_syst->GetBinContent(j) * h1->GetBinContent(j));
		}
		cout<<", new value after convolution in bin "<<i<<" = "<<new_nll<<endl;
		h3->SetBinContent(i,new_nll);
		delete h_syst;
	}
	cout<<endl<<"integral = "<<h3->Integral(1,totalBins)<<endl<<endl;
	h3->Scale(1.0/h3->Integral(1,totalBins));
	h3->SetLineColor(kMagenta);
	h3->SetLineWidth(2);
	h3->SetLineStyle(2);
	h3->Draw("same");

	//find out the upper limit
	c2.Update();
	float UpperLimit;
	double CI = 0.842; //0.842; //0.158;
	for (int i=1; i<=totalBins; i++) {
		cl = h1->Integral(1,i);
		cout<<"x = "<< xMin + BinWidth*(i-1) << ", y = " << h1->GetBinContent(i) <<", cl = "<<cl<<endl;
		if (cl<CI) UpperLimit = xMin + BinWidth*(i-1+1);
		h4->SetBinContent(i,cl);
	}   
	float rightmax = 1.1*h4->GetMaximum();
	float y_scale = gPad->GetUymax()/rightmax;
	cout<<gPad->GetUymax()<<" rightmax = "<<rightmax<<", scale = "<<y_scale<<endl;
	h4->SetLineWidth(2);
	h4->SetLineColor(kRed);
	h4->Scale(y_scale);
	h4->Draw("same");
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis->SetLineColor(kRed); axis->SetLabelColor(kRed); 
	axis->SetTitle("confidence level"); axis->SetTitleColor(kRed);
	axis->Draw();

	TLine L1(xMin,y_scale*CI,xMax,y_scale*CI);
	L1.SetLineColor(kBlue);
	L1.Draw();
	TLine L2(UpperLimit,0,UpperLimit,gPad->GetUymax());
	L2.SetLineColor(kBlue);
	L2.Draw();

	TString paramName = param->GetTitle();
	c2.SaveAs(figs_+"UpperLimits_"+paramName+"_hi_syst_Extend1.gif");
	c2.SaveAs(figs_+"UpperLimits_"+paramName+"_hi_syst_Extend1.pdf");
	delete h1; delete h2; delete h3; delete h4;
	param->setConstant(kFALSE);
}


Double_t RooPlot::mychiSquare(const char* curvename, const char* histname, Int_t nFitParam, bool chisqRange, int startbin, int stopbin) const
{
	// Calculate and return reduced chi-squared of curve with given name with respect
	// to histogram with given name. If nFitParam is non-zero, it is used to reduce the
	// number of degrees of freedom for a chi^2 for a curve that was fitted to the
	// data with that number of floating parameters

	// Find curve object
	RooCurve* curve = (RooCurve*) findObject(curvename,RooCurve::Class()) ;
	if (!curve) {
		coutE(InputArguments) << "RooPlot::chiSquare(" << GetName() << ") cannot find curve" << endl ;
		return -1. ;
	}

	// Find histogram object
	RooHist* hist = (RooHist*) findObject(histname,RooHist::Class()) ;
	if (!hist) {
		coutE(InputArguments) << "RooPlot::chiSquare(" << GetName() << ") cannot find histogram" << endl ;
		return -1. ;
	}
	return curve->mychiSquare(*hist,nFitParam,chisqRange,startbin,stopbin) ;
}


Double_t RooCurve::mychiSquare(const RooHist& hist, Int_t nFitParam, bool chisqRange, int startbin, int stopbin) const 
{
	// Calculate the chi^2/NDOF of this curve with respect to the histogram
	// 'hist' accounting nFitParam floating parameters in case the curve
	// was the result of a fit

	if (chisqRange) {
		int i = startbin;
		int np = stopbin;
	}
	else {
		Int_t i=0;
		int np = hist.GetN() ;
	}

	Double_t x,y,eyl,eyh,exl,exh ;

	// Find starting and ending bin of histogram based on range of RooCurve
	Double_t xstart,xstop ;

#if ROOT_VERSION_CODE >= ROOT_VERSION(4,0,1)
	GetPoint(0,xstart,y) ;
	GetPoint(GetN()-1,xstop,y) ;
#else
	const_cast<RooCurve*>(this)->GetPoint(0,xstart,y) ;
	const_cast<RooCurve*>(this)->GetPoint(GetN()-1,xstop,y) ;
#endif

	Int_t nbin(0) ;

	Double_t chisq(0) ;
	for (i ; i<np ; i++) {   

		// Retrieve histogram contents
		((RooHist&)hist).GetPoint(i,x,y) ;

		// Check if point is in range of curve
		if (x<xstart || x>xstop) continue ;

		nbin++ ;
		eyl = hist.GetEYlow()[i] ;
		eyh = hist.GetEYhigh()[i] ;
		exl = hist.GetEXlow()[i] ;
		exh = hist.GetEXhigh()[i] ;

		// Integrate function over this bin
		Double_t avg = average(x-exl,x+exh) ;

		// Add pull^2 to chisq
		if (y!=0) {      
			Double_t pull = (y>avg) ? ((y-avg)/eyl) : ((y-avg)/eyh) ;
			chisq += pull*pull ;
		}
	}

	// Return chisq/nDOF 
	return chisq / (nbin-nFitParam) ;
}

