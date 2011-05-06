#include "RooRandom.h"
#include "RooSimultaneous.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "TCanvas.h"

#include "buildSimPdf.cc"

#include <iostream>

/*
  hiToys : this function will generate and fit pseudo-experiments.
  These pseudo-experiments use the pp shape as the signal shape for
  both pp and hi pseudo-signal with the ability to tweak X_23.

  Parameters: 
  
  Ntoys : number of pseudo-experiements you want to
  produce and fit.  

  parVals : name of a text file that contains the initial values for
  the floating parameters in the fit.  Of the format the RooFit likes
  to read in.

  outfname : a filename for the output of the results of the pseudo
  experiments. This file will contain a line for each
  pseudo-experiment.  Each line will have the results of the floating
  parameters and their generated value if that can be deduced.

  randfname : a filename for a root file containing a RooFitResult
  that will be used to randomize the generation.

  systfname : a filename for a root file containing a RooFitResult
  that will be used to randomize the generation of the fixed signal
  shape parameters.

  desiredX_23 : This will be the X_23 imposed on the data, by
  modifying the hi pdf.

  seed : this is the random seed.  Zero is good, but when running in
  batch one may wish to set it manually to ensure all of the jobs are
  different.
  
 */
void hiToys(int Ntoys, TString parVals, TString outfname, 
	    TString randfname = "", TString systfname = "",
	    double desiredX_23 = 1.0,
	    unsigned int seed = 0) {
  RooWorkspace ws;
  mmin = 7.0; mmax = 14.0; //linearbg_ = false;
  RooCategory dataCat("dataCat", "dataCat");
  dataCat.defineType("hi");
  dataCat.defineType("pp");
  ws.import(dataCat);
  buildSimPdf(ws, dataCat);

  RooRandom::randomGenerator()->SetSeed(seed);

  RooSimultaneous * total = dynamic_cast<RooSimultaneous *>(ws.pdf("simPdf"));

  RooRealVar * invariantMass = ws.var("invariantMass");

  RooArgSet * pars = total->getParameters(RooArgSet(*invariantMass,dataCat));

  pars->readFromFile(parVals);
  RooArgSet truePars;
  pars->snapshot(truePars, true);

  std::cout << "\nfit parameters\n";
  truePars.Print("v");

  RooFitResult * nll = 0;
  RooArgSet * newPars = 0;
  if (randfname.Length() > 0) {
    TFile nllf(randfname);
    nllf.GetObject("hiFitResult", nll);
    assert(nll);
    newPars = new RooArgSet(nll->randomizePars());
    //newPars->Print("v");
    nllf.Close();
  }

  RooFitResult * systRes = 0;
  RooArgSet * systPars = 0;
  if (systfname.Length() > 0) {
    TFile systf(systfname);
    systf.GetObject("hiFitResult", systRes);
    assert(systRes);
    systPars = new RooArgSet(systRes->randomizePars());
    std::cout << "\nsystematic parameters\n";
    systPars->Print("v");
    systf.Close();
  }

  RooRealVar * f23_pp = ws.var("f23_pp");
  RooRealVar * f23_hi = ws.var("f23_hi");
  RooRealVar * f2_pp = ws.var("f2_pp");
  RooRealVar * f2_hi = ws.var("f2_hi");

  RooAbsPdf * sig1S = ws.pdf("sig1S");
  RooAbsPdf * sig2S = ws.pdf("sig2S");
  RooAbsPdf * sig3S = ws.pdf("sig3S");

  RooRealVar * nsig1 = ws.var("nsig1_pp");
  RooAbsReal * nsig2 = ws.function("nsig2_pp");
  RooAbsReal * nsig3 = ws.function("nsig3_pp");

  RooAddPdf sig("sig", "sig", RooArgList(*sig1S, *sig2S, *sig3S),
		   RooArgList(*nsig1, *nsig2, *nsig3));


  ofstream fout(outfname.Data(), ios_base::out|ios_base::trunc); 
  for (int i = 0; i < Ntoys; ++i) {
    pars->readFromFile(parVals);

    if (nll) {
      nll->randomizePars();
      pars->assignValueOnly(*newPars);
    }

    if (systRes) {
      systRes->randomizePars();
      pars->setRealValue("alpha", systPars->getRealValue("alpha", 1.6));
      pars->setRealValue("npow", systPars->getRealValue("npow", 2.3));
      pars->setRealValue("sigma1", systPars->getRealValue("sigma1", 0.092));
    }

    dataCat.setLabel("pp");
    RooDataSet * ppdata = 
      ws.pdf("bkg_pp")->generate(RooArgSet(*invariantMass),
				 RooFit::NumEvents(int(pars->getRealValue("nbkg_pp", 387))));
    RooDataSet * ppsig = 
      sig.generate(RooArgSet(*invariantMass),
		   RooFit::NumEvents(561-ppdata->numEntries()));
    ppsig->Print();
    ppdata->append(*ppsig);
    delete ppsig;

    dataCat.setLabel("hi");
    RooDataSet * hidata = 
      ws.pdf("bkg_hi")->generate(RooArgSet(*invariantMass),
				 RooFit::NumEvents(int(pars->getRealValue("nbkg_hi",530))));

    double holder = f23_pp->getVal();
    f23_pp->setVal(holder*desiredX_23);
    f23_hi->setVal(f23_pp->getVal());
    f2_hi->setVal(f2_pp->getVal());

    RooDataSet * hisig = 
      sig.generate(RooArgSet(*invariantMass), //RooFit::Extended(),
		   RooFit::NumEvents(628-hidata->numEntries()));
    hisig->Print();
    hidata->append(*hisig);
    delete hisig;

    f23_pp->setVal(holder);
    truePars.assignValueOnly(*pars);
    std::cout << "\ngeneration parameters\n";
    pars->Print("v");
    ppdata->Print();
    hidata->Print();
    RooDataSet * data = new RooDataSet("data", "data", 
				       RooArgSet(*invariantMass, dataCat),
				       RooFit::Index(dataCat),
				       RooFit::Link("pp", *ppdata),
				       RooFit::Link("hi", *hidata));
    
    pars->readFromFile(parVals);
    data->Print();

    RooFitResult * fr = total->fitTo(*data, RooFit::Extended(),
    				     RooFit::Minos(false),
    				     RooFit::Save(true));

    if (Ntoys == 1) {
      RooPlot * mf_pp = invariantMass->frame(8., 14., 60);
      dataCat.setLabel("pp");
      ppdata->plotOn(mf_pp);
      total->getPdf("pp")->plotOn(mf_pp);
  
      TCanvas * c1 = new TCanvas("pp", "pp");
      mf_pp->Draw();
      c1->Update();

      RooPlot * mf_hi = invariantMass->frame(8., 14., 60);
      dataCat.setLabel("hi");
      hidata->plotOn(mf_hi);
      total->getPdf("hi")->plotOn(mf_hi);
  
      TCanvas * c2 = new TCanvas("hi", "hi");
      mf_hi->Draw();
      c2->Update();

      pars->writeToFile("lastHItoy.txt");
      fr->Print("v");
      TString f2name(f2_pp->getTitle());
      std::cout << "double ratios (hi/pp)\n"
		<< "---------------------\n"
		<< "(2S+3S)/1S:\t" << computeRatio(*f23_hi, *f23_pp) << " +/- "
		<< computeRatioError(*f23_hi, *f23_pp) << '\n'
		<< f2name(0,5) <<":\t\t" << computeRatio(*f2_hi, *f2_pp) 
		<< " +/- " << computeRatioError(*f2_hi, *f2_pp) << "\n\n";
    } else {

      fout << "nll " << fr->minNll() << ' '
	   << "edm " << fr->edm() << ' '
	   << "covQual " << fr->covQual() << ' ';

      TIter finalPar(fr->floatParsFinal().createIterator());
      RooRealVar * par;
      while ((par = (RooRealVar *)finalPar())) {
	double trueVal = truePars.getRealValue(par->GetName(), 0.);
	fout << par->GetName() << ' '
	     << par->getVal() << ' '
	     << par->getError() << ' '
	     << trueVal << ' ';
      }
      
      fout << '\n';
      delete data;
      delete ppdata;
      delete hidata;
      delete fr;
    }
  }
  delete pars;

}
