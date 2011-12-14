#include "RooRandom.h"
#include "RooSimultaneous.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "TCanvas.h"
#include "RooMsgService.h"

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

RooDataSet * genSameSignDatasets(RooWorkspace& ws) {
  RooRealVar * mass = ws.var("invariantMass");
  TIter types(ws.cat("dataCat")->typeIterator());
  RooCatType * type;
  types.Reset();
  RooDataSet * ssData = 
    (RooDataSet *)ws.data("data")->emptyClone("toy_ss_Data");
  RooDataSet * protoData;
  RooAbsPdf * SS;
  while ((type=(RooCatType*)types.Next())) {
    SS = ws.pdf(TString::Format("bkgLikeSignPdf_%s", type->GetName()));
    protoData = 
      (RooDataSet *)ws.data(TString::Format("data_ss_%s", type->GetName()));
    
    RooDataSet * ssTmp = SS->generate(RooArgSet(*mass), 
				      protoData->numEntries(),
				      RooFit::ProtoData(*protoData));
    ssData->append(*ssTmp);
    delete ssTmp;
  }
  return ssData;
}

RooDataSet * genOppositeSignBackground(RooWorkspace& ws, int& Nhi,
				       int& Npp, bool doPoisson = true) {
  RooRealVar * mass = ws.var("invariantMass");
  TIter types(ws.cat("dataCat")->typeIterator());
  RooCatType * type;
  types.Reset();
  RooDataSet * osBkgData = 
    (RooDataSet *)ws.data("data")->emptyClone("toy_os_Data");
  RooDataSet * protoData;
  RooAbsPdf * bkg;
  int N;
  if (doPoisson) {
    Nhi = RooRandom::randomGenerator()->Poisson(Nhi);
    Npp = RooRandom::randomGenerator()->Poisson(Npp);
  }
  while ((type=(RooCatType*)types.Next())) {
    protoData = 
      (RooDataSet*)ws.data(TString::Format("data_os_%s", type->GetName()));
    bkg = ws.pdf(TString::Format("bkg_%s", type->GetName()));
    if ((*type) == "hi")
      N = Nhi;
    else
      N = Npp;
    RooDataSet * tmpData = bkg->generate(RooArgSet(*mass), N,
					 RooFit::ProtoData(*protoData));
    osBkgData->append(*tmpData);
    delete tmpData;
  }
  return osBkgData;
}

RooDataSet * genOppositeSignSignal(RooWorkspace& ws, int Nhi, int Npp) {
  
  RooRealVar * mass = ws.var("invariantMass");
  TIter types(ws.cat("dataCat")->typeIterator());
  RooCatType * type;
  types.Reset();
  RooDataSet * osSigData = 
    (RooDataSet *)ws.data("data")->emptyClone("toy_os_Data");
  RooAbsPdf * sig = ws.pdf("sig_pp");
  RooDataSet * protoData;
  int N;
  while ((type=(RooCatType*)types.Next())) {
    protoData = 
      (RooDataSet*)ws.data(TString::Format("data_os_%s", type->GetName()));
    if ((*type) == "hi")
      N = Nhi;
    else
      N = Npp;
    RooDataSet * tmpData = sig->generate(RooArgSet(*mass), N,
					 RooFit::ProtoData(*protoData));
    osSigData->append(*tmpData);
    delete tmpData;
  }
  return osSigData;
}

void hiToys(int Ntoys, TString parVals, TString outfname, 
	    double ptCut,
	    bool useKeys = false,
	    TString randfname = "", TString systfname = "",
	    /*double desiredX_23 = 1.0,*/ double ppMult = 1.0,
	    unsigned int seed = 0) {
  RooWorkspace ws;
  mmin = 7.0; mmax = 14.0; //linearbg_ = false;
  TString hidatafile("data/dimuonTree_181912-182609.root");
  TString ppdatafile("data/MassTree_NewCuts_pp_HIrereco.root");

  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
  RooRandom::randomGenerator()->SetSeed(seed);

  TString cuts(TString::Format("(muPlusPt > %0.1f) && (muMinusPt > %0.1f) "
			       "&& (abs(upsRapidity)<2.4)", ptCut, ptCut));
  readData(ws, hidatafile, ppdatafile, cuts);
  
  buildPdf(ws, true, useKeys);
  buildPdf(ws, false, useKeys);

  RooCategory * dataCat = ws.cat("dataCat");
  RooCategory * QQsign = ws.cat("QQsign");
  RooSimultaneous * simPdf = buildSimPdf(ws, *dataCat);
    
  RooArgSet * pars = simPdf->getParameters(ws.data("data"));
  pars->readFromFile(parVals);

  RooArgSet truePars, holdPars;
  pars->snapshot(truePars, true);
  pars->snapshot(holdPars, true);

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

  int Npp_tot(ws.var("nsig1_pp")->getVal() +
	      ws.function("nsig2_pp")->getVal() +
	      ws.function("nsig3_pp")->getVal() +
	      ws.var("nbkg_pp")->getVal() + 0.5);
  int Nhi_tot(ws.var("nsig1_hi")->getVal() +
	      ws.function("nsig2_hi")->getVal() +
	      ws.function("nsig3_hi")->getVal() +
	      ws.var("nbkg_hi")->getVal() + 0.5);

  Npp_tot *= ppMult;
  std::cout << "Npp_tot: " << Npp_tot << '\n'
	    << "Nhi_tot: " << Nhi_tot << '\n';

  TIter dataCats(dataCat->typeIterator());
  RooCatType * dataStr;
  dataCats.Reset();
  TString theCut, signStr;
  RooDataSet * tmpData;
  while ((dataStr=(RooCatType*)dataCats.Next())) {
    for(int qq = 0; qq < 2; ++qq) {
      theCut = TString::Format("(dataCat == dataCat::%s)", dataStr->GetName());
      if (qq) {
	theCut += "&&(QQsign != QQsign::PlusMinus)";
	signStr = "ss";
      } else {
	theCut += "&&(QQsign == QQsign::PlusMinus)";
	signStr = "os";
      }
      tmpData = (RooDataSet *)
	ws.data("data")->reduce(RooFit::SelectVars(RooArgSet(*dataCat, 
							     *QQsign)), 
				RooFit::Name(TString::Format("data_%s_%s", 
							     signStr.Data(), 
							     dataStr->GetName())),
				RooFit::Cut(theCut));
      ws.import(*tmpData);
      delete tmpData;
    }
  }
  
  ofstream fout(outfname.Data(), ios_base::out|ios_base::trunc); 

  int Npp_bkg(ws.var("nbkg_pp")->getVal() + 0.5);
  int Nhi_bkg(ws.var("nbkg_hi")->getVal() + 0.5);
  RooDataSet * toyData;
  RooCategory * toyCat;
  RooSimultaneous * simPdfToy;
  RooArgSet * toyPars;
  RooRealVar * par;
  RooFitResult * fr;
  for (int i = 0; i < Ntoys; ++i) {
    pars->readFromFile(parVals);

    if (nll) {
      nll->randomizePars();
      pars->assignValueOnly(*newPars);
    }

    pars->setRealValue("nsig1_pp", pars->getRealValue("nsig1_pp")*ppMult);
    pars->setRealValue("nbkg_pp", pars->getRealValue("nbkg_pp")*ppMult);

    if (systRes) {
      systRes->randomizePars();
      pars->setRealValue("alpha", systPars->getRealValue("alpha", 1.6));
      pars->setRealValue("npow", systPars->getRealValue("npow", 2.3));
      pars->setRealValue("sigma1", systPars->getRealValue("sigma1", 0.092));
    }

//     std::cout << "Generating parameters\n";
//     pars->Print("v");
    Npp_bkg = int(ws.var("nbkg_pp")->getVal() + 0.5);
    Nhi_bkg = int(ws.var("nbkg_hi")->getVal() + 0.5);
    toyData = (RooDataSet *)ws.data("data")->emptyClone();

    if (useKeys) {
      tmpData = genSameSignDatasets(ws);
      toyData->append(*tmpData);
      delete tmpData;
    }
    tmpData = genOppositeSignBackground(ws, Nhi_bkg, Npp_bkg);
    toyData->append(*tmpData);
    delete tmpData;
    tmpData = genOppositeSignSignal(ws, Nhi_tot-Nhi_bkg, Npp_tot-Npp_bkg);
    toyData->append(*tmpData);
    delete tmpData;

    RooWorkspace wsToy("wsToy", "wsToy");
    wsToy.import(*toyData);
    delete toyData;

    buildPdf(wsToy, true, useKeys);
    buildPdf(wsToy, false, useKeys);

    toyCat = wsToy.cat("dataCat");

    simPdfToy = buildSimPdf(wsToy, *toyCat);
    toyPars = simPdfToy->getParameters(wsToy.data("data"));


    toyPars->readFromFile(parVals);
    toyPars->setRealValue("nsig1_pp", 
			  toyPars->getRealValue("nsig1_pp")*ppMult);
    toyPars->setRealValue("nbkg_pp", toyPars->getRealValue("nbkg_pp")*ppMult);
    toyData = 
      (RooDataSet *)wsToy.data("data")->reduce("QQsign==QQsign::PlusMinus");

    fr = simPdfToy->fitTo(*toyData, RooFit::Extended(),
			  RooFit::Minos(false),
			  RooFit::PrintLevel((Ntoys==1) ? 1 : -1),
			  RooFit::Save(true));


    fout << "nll " << fr->minNll() << ' '
	 << "edm " << fr->edm() << ' '
	 << "covQual " << fr->covQual() << ' ';

    TIter finalPar(fr->floatParsFinal().createIterator());
    while ((par = (RooRealVar *)finalPar())) {
      double trueVal = truePars.getRealValue(par->GetName(), 0.);
      fout << par->GetName() << ' '
	   << par->getVal() << ' '
	   << par->getError() << ' '
	   << trueVal << ' ';
    }
    
    fout << '\n';
    delete toyData;
    delete toyPars;
    delete fr;
  }
  delete pars;

}

