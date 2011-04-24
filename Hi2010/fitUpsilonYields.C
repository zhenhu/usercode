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
double mass_l = 8;
double mass_h = 12;
#define mmin_ mass_l 
#define mmax_ mass_h
#define fmin_ mass_l
#define fmax_ mass_h
double binw_ = 0.1;
double width_ = 0.095;
bool plotpars = true;//false;
TString finput("MassTree_withCuts_full.root");
//TString finput("GlbMuon_hi_MassTree.root");
TString figName_("masspeak_Hi_Upsi_full_all_muPt4"); //output fig names
//TString figName_("GlbMuon_masspeak_pp_all_muPt4");
TString figs_("paperPlots/"); //output fig location
const TString dirname_("");//"upsilonYield"); /* tree location in input file */

using namespace RooFit;
using namespace RooStats;
void fitpeaks(int bin);

void fitUpsilonYields(){
	ofstream outfile("fitresults.out", ios_base::app); 
	//double original_yields[9] = {84.7363, 48.703, 36.5036, 22.285, 29.8004, 32.5132, 41.3552, 17.2833, 24.2914};
	//different binning:
	fitpeaks(0);   
	//fitpeaks(1);
	//fitpeaks(2);
	//fitpeaks(3);
	//fitpeaks(4);
	//fitpeaks(5);
	//fitpeaks(6);
	//fitpeaks(7);
	//fitpeaks(8);
	//fitpeaks(9);
	//fitpeaks(10);
	//fitpeaks(11);
    //fitpeaks(12);
    //fitpeaks(13);

}

void fitpeaks(int bin){
	TString suffix_, cut_;
	switch (bin)
	{
		case 0:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20";  //hi acceptance for Upsilon
			//cut_="( (muPlusPt>3.5 && abs(muPlusEta)<1.6) || (muPlusPt>2.5 && abs(muPlusEta)>=1.6 && abs(muPlusEta)<2.4) ) && ( (muMinusPt>3.5 && abs(muMinusEta)<1.6) || (muMinusPt>2.5 && abs(muMinusEta)>=1.6 && abs(muMinusEta)<2.4) )";   //pp acceptance for Upsilon 
			suffix_="_all";binw_=0.1;
			break;
		case 1:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && abs(upsRapidity)>=0 && abs(upsRapidity)<1.2";
			suffix_="_eta0-12";binw_=0.2;
			break;
		case 2:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && abs(upsRapidity)>=1.2 && abs(upsRapidity)<2.4";
			suffix_="_eta12-24";binw_=0.2;
			break;
		case 3:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=0 && Centrality<4";
			suffix_="_cntr0-10";binw_=0.2;
			break;
		case 4:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=4 && Centrality<8";
			suffix_="_cntr10-20";binw_=0.2;
			break;
		case 5:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=8 && Centrality<50";
			suffix_="_cntr20-100";binw_=0.2;
			break;
		case 6:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=0 && upsPt<6.5";
			suffix_="_upsPt0-65";binw_=0.2;
			break;
		case 7:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=6.5 && upsPt<10";
			suffix_="_upsPt65-100";binw_=0.2;
			break;
		case 8:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=10 && upsPt<20";
			suffix_="_upsPt100-200";binw_=0.2;
			break;
        case 9:
            cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=0 && upsPt<5";
            suffix_="_upsPt0-50";binw_=0.2;
            break;
        case 10:
            cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=5.0 && upsPt<20";
            suffix_="_upsPt50-200";binw_=0.2;
            break;
		case 11:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt>=6.5 && upsPt<20";
			suffix_="_upsPt65-200";binw_=0.2;
			break;
		case 12:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=0 && Centrality<8";
			suffix_="_cntr0-20";binw_=0.2;
			break;
		case 13:
			cut_="muPlusPt > 4.0 && muMinusPt > 4.0 && upsPt<20 && Centrality>=4 && Centrality<50";
			suffix_="_cntr10-100";binw_=0.2;
			break;

		default:
			cout<<"error in binning"<<endl;
			break;
	}

	cout << "oniafitter processing"
		<< "\n\tInput:  \t" << finput
		<< "\n\tresults:\t" << figs_
		<< endl;

	RooRealVar* mass  = new RooRealVar("invariantMass","#mu#mu mass",mmin_,mmax_,"GeV/c^{2}");
	mass->setRange("R1",8,9.8);
	mass->setRange("R2",10.6,12);
	const double M1S = 9.46;   //upsilon 1S pgd mass value
	const double M2S = 10.02;  //upsilon 2S pgd mass value
	const double M3S = 10.35;  //upsilon 3S pgd mass value

	RooRealVar *mean    = new RooRealVar("mean","#Upsilon mean",M1S,M1S-0.1,M1S+0.1,"GeV/c2");
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
	RooRealVar *sigma2 = new RooRealVar("sigma1S","Sigma_1S",0.06,0.01,0.30); //Y(1S) resolution
	RooFormulaVar *reso1S = new RooFormulaVar("reso1S","@0"             ,RooArgList(*sigma2));
	RooFormulaVar *reso2S = new RooFormulaVar("reso2S","@0*10.023/9.460",RooArgList(*sigma2));
	RooFormulaVar *reso3S = new RooFormulaVar("reso3S","@0*10.355/9.460",RooArgList(*sigma2));

	/// to describe final state radiation tail on the left of the peaks
	RooRealVar *alpha  = new RooRealVar("alpha","tail shift",2.0,0.2,4);
	//RooRealVar *alpha  = new RooRealVar("alpha","tail shift",1.7,0.2,4);
	RooRealVar *npow   = new RooRealVar("npow","power order",1,1,3);
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
	//sigma2->setVal(width_);
	//sigma2->setConstant(kTRUE);

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
	RooRealVar *bkg_a1  = new RooRealVar("bkg_a1", "background a1", 0, -1, 1);
	RooRealVar *bkg_a2  = new RooRealVar("bkg_a2", "background a2", 0, -1, 1);
	RooAbsPdf  *bkgPdf  = new RooChebychev("bkg","linear background",
			*mass, RooArgList(*bkg_a1,*bkg_a2));
	//bkg_a1->setVal(-0.03);
	//bkg_a1->setConstant(kTRUE);
	bkg_a2->setVal(0);
	bkg_a2->setConstant(kTRUE);

	/// Combined pdf
	int nt = 1000;

	//bool fitfraction = true;

	RooRealVar *nbkgd = new RooRealVar("nbkgd","brackground yield",nt*0.75,0,10*nt);
	RooRealVar *nsig1f  = new RooRealVar("nsig1S","Y(1S) yield",   nt*0.25,0,10*nt);
	
	//use yields of 2S and 3S as free parameters
	//RooRealVar *nsig2f  = new RooRealVar("nsig2S","Y(2S) yield",   nt*0.25,0,10*nt);
	//RooRealVar *nsig3f  = new RooRealVar("nsig3S","Y(3S) yield",   nt*0.25,0,10*nt);
	
	//use ratio of 2S and 3S as free parameters
	RooRealVar *f2Svs1S = new RooRealVar("2S/1S","Y(2S)/Y(1S) yields ratio",0.4,0,1);
	RooRealVar *f3Svs1S = new RooRealVar("3S/1S","3/1 sig fration",0.3,0,1);
	//RooRealVar *f23vs1S = new RooRealVar("(2S+3S)/1S","(2+3)/1 sig fration",0.5,0,1);
	RooFormulaVar *nsig2f = new RooFormulaVar("nsig2S","@0*@1", RooArgList(*nsig1f,*f2Svs1S));
	RooFormulaVar *nsig3f = new RooFormulaVar("nsig3S","@0*@1", RooArgList(*nsig1f,*f3Svs1S));
	//RooFormulaVar *nsig3f = new RooFormulaVar("nsig3S","@0*@2-@0*@1", RooArgList(*nsig1f,*f2Svs1S,*f23vs1S));
	
	//force the ratio to the pp value
	RooFormulaVar *nsig2f_ = new RooFormulaVar("nsig2S_","@0*0.491", RooArgList(*nsig1f)); 
	RooFormulaVar *nsig3f_ = new RooFormulaVar("nsig3S_","@0*0.212", RooArgList(*nsig1f)); 

	//f2Svs1S->setVal(0.491);
	//f2Svs1S->setConstant(kTRUE);
	//f3Svs1S->setVal(0);
	//f3Svs1S->setConstant(kTRUE);
	//f23vs1S->setVal(0);
	//f23vs1S->setConstant(kTRUE);

	RooAbsPdf  *pdf   = new RooAddPdf ("pdf","total signal+background pdf",
			RooArgList(*gauss1S2,*sig2S,*sig3S,*bkgPdf),
			RooArgList(*nsig1f,*nsig2f,*nsig3f,*nbkgd));
	//force the ratio to the pp value
	RooAbsPdf  *pdf_pp   = new RooAddPdf ("pdf_pp","total signal+background pdf",
			RooArgList(*gauss1S2,*sig2S,*sig3S,*bkgPdf),
			RooArgList(*nsig1f,*nsig2f_,*nsig3f_,*nbkgd));


	/// Background pdf for the pre-fit with only Y(1S) peak 
	RooRealVar *bkg_a1_pre  = new RooRealVar("bkg_a1_pre", "background a1", 0, -1, 1);
	RooRealVar *bkg_a2_pre  = new RooRealVar("bkg_a2_pre", "background a2", 0, -1, 1);
	RooAbsPdf  *bkgPdf_pre  = new RooChebychev("bkgPdf_pre","linear background",
			*mass, RooArgList(*bkg_a1_pre,*bkg_a2_pre));
	bkg_a2_pre->setVal(0);
	bkg_a2_pre->setConstant(kTRUE);
	/// signl pdf for th pre-fit with only Y(1S) peak
	RooRealVar *nsig_pre  = new RooRealVar("nsig_pre","signal 1 yield",nt*0.25,0,10*nt);
	RooRealVar *nbkgd_pre = new RooRealVar("nbkgd_pre","brackground 1 yield",nt*0.75,0,10*nt);
	RooAbsPdf  *pdf_pre = new RooAddPdf ("pdf_pre","1S signal+background pdf",
			RooArgList(*gauss1S2,*bkgPdf_pre),
			RooArgList(*nsig_pre,*nbkgd_pre));


	//read the data
	TFile f(finput,"read");
	gDirectory->Cd(finput+":/"+dirname_);
	TTree* theTree     = (TTree*)gROOT->FindObject("UpsilonTree");
	RooRealVar* upsPt  = new RooRealVar("upsPt","p_{T}(#Upsilon)",0,60,"GeV");
	RooRealVar* upsEta = new RooRealVar("upsEta",  "upsEta"  ,-7,7);
	RooRealVar* upsRapidity = new RooRealVar("upsRapidity",  "upsRapidity"  ,-2.4,2.4);
	RooRealVar* vProb = new RooRealVar("vProb",  "vProb"  ,0,1);
	/*******************comment the next line for running the pp trees*****************/
	RooRealVar* Centrality = new RooRealVar("Centrality",  "Centrality"  ,0,40);
	/**********************************************************************************/
	RooRealVar* muPlusPt = new RooRealVar("muPlusPt","muPlusPt",0,50);
	RooRealVar* muPlusEta = new RooRealVar("muPlusEta","muPlusEta",-2.5,2.5);
	RooRealVar* muMinusPt = new RooRealVar("muMinusPt","muMinusPt",0,50);
	RooRealVar* muMinusEta = new RooRealVar("muMinusEta","muMinusEta",-2.5,2.5);

	RooDataSet* data0, *data;
	/***********************************for HI*****************************************/
	data0 = new RooDataSet("data","data",theTree,RooArgSet(*mass,*upsRapidity,*vProb,*upsPt,*Centrality,*muPlusPt,*muMinusPt));
	/***********************************for pp*****************************************/
	//data0 = new RooDataSet("data","data",theTree,RooArgSet(*mass,*upsRapidity,*upsPt,*muPlusPt,*muMinusPt,*muPlusEta,*muMinusEta));
	/**********************************************************************************/
	data0->Print();
	data = ( RooDataSet*) data0->reduce(Cut(cut_));
	data->Print();


	//the pre-fit with only Y(1S) pdf
	//RooFitResult* fit_1st = pdf_pre->fitTo(*data,Range("R1,R2"),Save(kTRUE));
	RooFitResult* fit_1st = pdf_pre->fitTo(*data,Save(kTRUE));
	mean->setConstant(kTRUE);
	//plot
	TCanvas c; c.cd();
	int nbins = (mmax_-mmin_)/binw_;
	RooPlot* frame = mass->frame(Bins(nbins),Range(mmin_,mmax_));
	data->plotOn(frame,Name("theData"));
	//pdf_pre->plotOn(frame,LineColor(kRed));
	//pdf_pre->plotOn(frame,Components(bkgPdf_pre),LineStyle(kDashed));
	//if(plotpars) pdf_pre->paramOn(frame,Layout(0.65));


	//the second fit with default pdf 
	RooFitResult* fit_2nd = pdf->fitTo(*data,Save(kTRUE));
	//plot
	pdf->plotOn(frame,Name("thePdf"));
	//pdf->plotOn(frame,Components(bkgPdf),LineStyle(kDashed));
	RooArgSet * pars = pdf->getParameters(data);
	//calculate chi2 in a mass range
	float bin_Min = (9.6-mmin_)/binw_;
	float bin_Max = (10.6-mmin_)/binw_;
	int binMin = (int)bin_Min;
	int binMax = (int)bin_Max;
	int nfloatpars = pars->selectByAttrib("Constant",kFALSE)->getSize(); 
	double mychsq = frame->mychiSquare("thePdf","theData",nfloatpars,false,binMin,binMax);
	if(plotpars) pdf->paramOn(frame,Layout(0.65)/*,Label("3S/1S = 0.212 #pm 0.061"));*/,Label(Form("#chi^{2}/ndf = %2.1f", mychsq)));
	
	
	//the third fit with pp ratio pdf
	//RooFitResult* fit_3rd = pdf_pp->fitTo(*data,Save(kTRUE));
	//pdf_pp->plotOn(frame,Name("thePdf_pp"),LineStyle(kDashed),LineColor(kRed));
	//float chi_2_pp = frame->mychiSquare("thePdf_pp","theData",0,false,binMin,binMax);
	 
	
	//draw and save plots
	data->plotOn(frame);
	frame->SetTitle( "" );
	frame->GetXaxis()->SetTitle("#mu#mu invariant mass [GeV/c^{2}]");
	frame->GetYaxis()->SetTitleOffset(1);
	frame->GetYaxis()->SetTitleSize(0.04);
	frame->Draw();
	c.SaveAs(figs_+figName_+suffix_+".root");
	c.SaveAs(figs_+figName_+suffix_+".eps");
	c.SaveAs(figs_+figName_+suffix_+".gif");
	c.SaveAs(figs_+figName_+suffix_+".pdf");


	//calculate the upper limits
	ProfileLikelihoodCalculator pl(*data,*pdf,*f2Svs1S);
	pl.SetConfidenceLevel(0.95); // 95% interval
	LikelihoodInterval* interval = pl.GetInterval();
	LikelihoodIntervalPlot plot(interval);
	TCanvas c1; c1.cd(); 
	plot.Draw();
	c1.SaveAs(figs_+"nll_frac_hi.gif");
	c1.SaveAs(figs_+"nll_frac_hi.pdf");

	// print out the iterval on the Parameter of Interest
	cout << "\n95% interval on " <<f2Svs1S->GetName()<<" is : ["<<
		interval->LowerLimit(*f2Svs1S) << ", "<<
		interval->UpperLimit(*f2Svs1S) <<"] "<<endl;


	// Print fit results 
	cout << endl << "figure name: "<< figName_ << endl << endl;
	cout << "the pre-fit with only Y1S pdf" << endl ;
	fit_1st->Print() ;
	cout << "the second fit with the default pdf " << endl ;
	fit_2nd->Print() ;
	cout <<"free parameter = "<< nfloatpars << ",     mychi2 = " << mychsq << endl << endl;

	ofstream outfile("fitresults.out", ios_base::app);
	outfile<<endl<<"**********"<<suffix_<<"**********"<<endl<<endl;
	outfile<<"Y(1S) yield: = "<<nsig1f->getVal()<<" +/- "<<nsig1f->getError()<<endl<<endl;
	outfile<<"     chi^2   = " << mychsq << endl << endl;

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

