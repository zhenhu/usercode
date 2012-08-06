#include "RooSimWSTool.h"
#include "RooSimPdfBuilder.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooCategory.h"
#include "RooWorkspace.h"
#include "RooFormulaVar.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooExtendPdf.h"
#include "RooKeysPdf.h"
#include "RooSimultaneous.h"
#include "RooGenericPdf.h"
#include "RooTreeDataStore.h"
#include "RooPlot.h"
#include "RooProdPdf.h"
#include "RooExponential.h"
#include "RooGaussian.h"

#include "TTree.h"
#include "TFile.h"
#include "TPad.h"

//float mmin = 7.0, mmax = 14.0;
TString dirname_ = "";
TString treeName = "UpsilonTree_allsign";

bool buildPdf(RooWorkspace &ws, bool hi, 
	      int bkgModel = 0, 
	      bool doubleRats = false,
	      bool ratOne = false) {

  double const M1S(9.460);
  double const M2S(10.023);
  double const M3S(10.355);
  RooRealVar * mass = ws.var("invariantMass");
  if (!mass) {
    mass = new RooRealVar("invariantMass", "#mu#mu mass", 7., 14., 
			  "GeV/c^{2}");
  }
//   mass->setRange(mmin,mmax);
  RooRealVar mean("mean", "mean", M1S, M1S-0.3, M1S+0.3, "GeV/c^{2}");

  RooConstVar rat2("rat2", "rat2", M2S/M1S);
  RooConstVar rat3("rat3", "rat3", M3S/M1S);

  RooConstVar diff2("diff2", "diff2", M2S-M1S);
  RooConstVar diff3("diff3", "diff3", M3S-M1S);
  RooRealVar mscale("mscale", "mscale", 1.0);


  RooFormulaVar mean1S("mean1S", "@0", RooArgList(mean));
  RooFormulaVar mean2S("mean2S", "@0+@1*@2", RooArgList(mean,diff2,mscale));
  RooFormulaVar mean3S("mean3S", "@0+@1*@2", RooArgList(mean,diff3,mscale));

  RooRealVar sigma1("sigma1", "#sigma_{1}", 0.092, 0.01, 0.3);
  sigma1.setConstant(false);
  RooFormulaVar sigma1S("sigma1S", "@0", RooArgList(sigma1));
  RooFormulaVar sigma2S("sigma2S", "@0*@1", RooArgList(sigma1,rat2));
  RooFormulaVar sigma3S("sigma3S", "@0*@1", RooArgList(sigma1,rat3));

  RooRealVar alpha("alpha", "#alpha", 1.4, 0.1, 10.);
  alpha.setConstant(false);
  RooRealVar npow("npow", "n_{CB}", 2.3, 0.1, 10.);
  npow.setConstant();
  RooRealVar syst_npow("syst_npow", "syst_npow", 0.15);

  RooRealVar a_npow("a_npow", "a_npow", 1.0, 0.01, 1.2);
  RooFormulaVar npowf("npowf", "@0*@1", RooArgList(npow,a_npow));

  RooGaussian systematic_npow("systematic_npow", "systematic_npow",
			      a_npow, RooFit::RooConst(1.0), syst_npow);

  RooCBShape sig1S("sig1S", "sig1S", *mass, mean1S, sigma1S, alpha, npowf);
  RooCBShape sig2S("sig2S", "sig2S", *mass, mean2S, sigma2S, alpha, npowf);
  RooCBShape sig3S("sig3S", "sig3S", *mass, mean3S, sigma3S, alpha, npowf);

  RooRealVar nsig1("nsig1", "N_{1S}", 100, -1000, 1e6);

  RooRealVar f23("f23", "(2S+3S)/1S", 0.97, -0.1, 2.0);
  f23.setConstant(false);
  //RooRealVar f2("f2", "2S/1S", 0.55);
  RooRealVar f2("f2", "3S/2S", 0.6, -0.1, 2.0);
  f2.setConstant(false);
  RooRealVar f3("f3", "3S/1S", 0.5, -0.1, 2.0);
  f3.setConstant(false);

  RooRealVar x23("x23", "#chi_{23}", 0.13);
  x23.setConstant(false);
  RooRealVar x2("x2", "#chi_{2}", 0.175);
  x2.setConstant(false);
  RooRealVar x3("x3", "#chi_{3}", 0.07);
  x3.setError(0.05);
  x3.setConstant(false);


  RooFormulaVar * nsig2 = 0;
  RooFormulaVar * nsig3 = 0;
  if ((hi)&&(doubleRats)) {
    RooRealVar * f2_pp = ws.var("f2_pp");
    RooRealVar * f23_pp = ws.var("f23_pp");
    RooRealVar * f3_pp = ws.var("f3_pp");

    nsig2 = new RooFormulaVar("nsig2", "@0*@1*@2", RooArgList(nsig1, *f2_pp, 
							      x2));
    // nsig3 = new RooFormulaVar("nsig3", "@0*@1*@2", RooArgList(nsig1, *f3_pp, 
    // 							      x3));
    nsig3 = new RooFormulaVar("nsig3", "@0*(@1*@2-@3*@4)", 
    			      RooArgList(nsig1, *f23_pp, x23, *f2_pp, x2));

// use these to have (2S+3S)/1S and 3S/2S
//     nsig2 = new RooFormulaVar("nsig2", "@0*@1*@2/(1+@3*@4)", 
// 			      RooArgList(nsig1, *f23_pp, x23, *f2_pp, x2));
//     nsig3 = new RooFormulaVar("nsig3", "@0*@1*@2*@3*@4/(1+@3*@4)", 
// 			      RooArgList(nsig1, *f23_pp, x23, *f2_pp, x2));
  } else if ((ratOne) && (hi)) {
    RooRealVar * f2_pp = ws.var("f2_pp");
    RooRealVar * f23_pp = ws.var("f23_pp");    
    nsig2 = new RooFormulaVar("nsig2", "@0*@1", RooArgList(nsig1,*f2_pp));
    nsig3 = new RooFormulaVar("nsig3", "@0*(@1-@2)", RooArgList(nsig1, 
								*f23_pp, 
								*f2_pp));
  } else {
    nsig2 = new RooFormulaVar("nsig2", "@0*@1", RooArgList(nsig1,f2));
    // nsig3 = new RooFormulaVar("nsig3", "@0*@1", RooArgList(nsig1,f3));
    nsig3 = new RooFormulaVar("nsig3", "@0*(@1-@2)", RooArgList(nsig1, 
    								f23, f2));
    // these are for the (2S+3S)/1S and 3S/2S
//     nsig2 = new RooFormulaVar("nsig2", "@0*@1/(1+@2)", RooArgList(nsig1,f23,
// 								  f2));
//     nsig3 = new RooFormulaVar("nsig3", "@0*@1*@2/(1+@2)", RooArgList(nsig1, 
// 								     f23, f2));
  }

  RooRealVar turnOn("turnOn","turnOn", 7.9, 4., 14.);
  turnOn.setConstant(false);
  RooRealVar syst_turnOn("syst_turnOn", "syst_turnOn", 0.01);
  RooRealVar a_turnOn("a_turnOn", "a_turnOn", 1.);
  RooFormulaVar turnOnf("turnOnf", "@0*@1", RooArgList(turnOn, a_turnOn));
  RooGaussian systematic_turnOn("systematic_turnOn", "systematic_turnOn",
			       a_turnOn, RooFit::RooConst(1.0), syst_turnOn);



  RooRealVar width("width","width", 1.1, 0., 15.);
  RooRealVar syst_width("syst_width", "syst_width", 0.20);
  RooRealVar a_width("a_width", "a_width", 1.);
  RooFormulaVar widthf("widthf", "@0*@1", RooArgList(width, a_width));
  RooGaussian systematic_width("systematic_width", "systematic_width",
			       a_width, RooFit::RooConst(1.0), syst_width);

  RooRealVar decay("decay","decay", -0.15, -1., 1.);
  decay.setConstant(false);
  RooGenericPdf bkgErf("bkgErf","bkgErf",
		       "(TMath::Erf((@0-@1)/@2)+1)",
		       RooArgList(*mass, turnOnf, widthf));
  RooExponential bkgExp("bkgExp", "bkgExp", *mass, decay);

  RooProdPdf bkgErfExp("bkgErfExp", "bkg", 
		       RooArgList(bkgErf,bkgExp));

  RooRealVar nbkg("nbkg", "N_{bkg}", 5000., -1000., 1e6);

  RooRealVar bkg_a1("bkg_a1", "a_{1,bkg}", 0., -5., 5.);
  bkg_a1.setError(0.1);
  RooRealVar bkg_a2("bkg_a2", "a_{2,bkg}", 0., -5., 5.);
  bkg_a2.setError(0.1);
  //bkg_a2.setConstant();
  RooRealVar bkg_a3("bkg_a3", "a_{3,bkg}", 0., -5., 5.);
  //bkg_a3.setConstant();
  RooChebychev bkgPoly("bkgPoly", "bkg", *mass, 
		       RooArgList(bkg_a1, bkg_a2, bkg_a3));
  RooRealVar syst_bg("syst_bg", "syst", 0.22);
  RooRealVar beta_bg("beta_bg", "beta", 0., -5., 5.);

  RooFormulaVar logNorm("logNorm", "TMath::Power((1+@0),@1)", 
			RooArgList(syst_bg,beta_bg));
  RooFormulaVar nbkgf("nbkgf", "@1*@0", RooArgList(nbkg, logNorm));

  RooGaussian systematic("bkgSyst", "bkgSyst", beta_bg, RooFit::RooConst(0), 
			 RooFit::RooConst(1));

  RooProdPdf bkgErfPoly("bkgErfPoly", "bkg", RooArgList(bkgErf, bkgPoly));
  RooRealVar * nLikeSign = 0;
  RooKeysPdf * LikeSignPdf = 0;
  RooRealVar nPoly("nPoly", "nPoly", 0.);
  nPoly.setConstant(false);
  if (bkgModel == 2) {

    TString likeSignCut("(QQsign != QQsign::PlusMinus)"
			"&&(dataCat == dataCat::");
    likeSignCut += (hi) ? "hi)" : "pp)";
    RooDataSet * likeSignData = 
      dynamic_cast<RooDataSet*>(ws.data("data")->reduce(likeSignCut));

    assert(likeSignData);

    LikeSignPdf = new RooKeysPdf("bkgLikeSignPdf", "bkgLikeSignPdf", *mass, 
				 *likeSignData, RooKeysPdf::NoMirror, 1.5);
    nLikeSign = 
      new RooRealVar("nLikeSign", "nLikeSign", 
		     likeSignData->sumEntries(TString::Format("(%s>%0.1f)&&"
							      "(%s<%0.1f)",
							      mass->GetName(),
							      mass->getMin(), 
							      mass->GetName(),
							      mass->getMax())));
    delete likeSignData;
    std::cout << "like sign events: " << nLikeSign->getVal() << '\n';

    RooAddPdf bkg("bkg", "bkg", RooArgList(*LikeSignPdf, bkgPoly),
		  RooArgList(*nLikeSign, nPoly));
    ws.import(bkg, RooFit::RenameAllNodes((hi)?"hi":"pp"),
	      RooFit::RenameAllVariablesExcept((hi)? "hi": "pp", 
					       "npow,invariantMass,"
					       "alpha,"
					       "sigma1"), 
	      RooFit::Silence());
  }

  TString exceptions = "x23,x2,x3,f2_hi,f3_hi,f23_hi,f2_pp,f3_pp,f23_pp,"
                       "npow,alpha,sigma1,invariantMass,syst_npow,a_npow";
  RooArgList pdfs(sig1S, sig2S, sig3S);
  RooArgList norms(nsig1, *nsig2, *nsig3);
  RooAddPdf sig("sig", "sig", pdfs, norms);
  ws.import(sig, RooFit::RenameAllNodes((hi)?"hi":"pp"),
	    RooFit::RenameAllVariablesExcept((hi)? "hi": "pp", exceptions),
	    RooFit::RecycleConflictNodes());

  RooProdPdf * bkg = 0;
  switch (bkgModel) {
  case 0:
    bkg = new RooProdPdf("bkg", "bkg", RooArgList(bkgErfExp,systematic_turnOn,
						  systematic_width));
    pdfs.add(*bkg);
    norms.add(nbkgf);
    break;
  case 1:
    bkg = new RooProdPdf("bkg", "bkg", RooArgList(bkgPoly));
    pdfs.add(*bkg);
    norms.add(nbkgf);
    break;
  case 2:
    pdfs.add(RooArgList(*LikeSignPdf, bkgPoly));
    norms.add(RooArgList(*nLikeSign, nPoly));
    break;
  case 3:
    pdfs.add(bkgErfExp);
    norms.add(nbkg);
    exceptions += ",turnOn,width";
    break;
  case 4:
    bkgErfPoly.SetName("bkg");
    pdfs.add(bkgErfPoly);
    norms.add(nbkg);
    break;
  case 5:
    pdfs.add(RooArgList(bkgErfExp,bkgPoly));
    norms.add(RooArgList(nbkg,nPoly));
    ws.import(RooProdPdf("bkg", "bkg", 
			 RooArgList(RooAddPdf("add", "add", 
					      RooArgList(bkgErfExp,bkgPoly),
					      RooArgList(nbkg,nPoly)),
				    systematic_turnOn,systematic_width)),
	      RooFit::RenameAllNodes((hi)?"hi":"pp"),
	      RooFit::RenameAllVariablesExcept((hi)? "hi": "pp", exceptions),
	      RooFit::RecycleConflictNodes());
    break;
  default:
    pdfs.add(bkgErfExp);
    norms.add(nbkg);
  }
  
  RooAddPdf pdf_noSyst("pdf_noSyst", "pdf_noSyst", pdfs, norms);
  RooProdPdf pdf("pdf", "pdf", RooArgList(pdf_noSyst, systematic, 
					  systematic_npow));

  //pdf.Print("v");
  ws.import(pdf, 
	    RooFit::RenameAllNodes((hi)?"hi":"pp"),
	    RooFit::RenameAllVariablesExcept((hi)? "hi": "pp", exceptions),
	    RooFit::RecycleConflictNodes());

  if (bkgModel == 2) {
    delete nLikeSign;
    delete LikeSignPdf;
  }
  if (bkg)
    delete bkg;
  delete nsig2;
  delete nsig3;
  return true;
}

RooSimultaneous* buildSimPdf(RooWorkspace &ws, RooCategory& dataCat) {

  if (ws.pdf("simPdf"))
    return dynamic_cast<RooSimultaneous *>(ws.pdf("simPdf"));

  RooSimultaneous simPdf("simPdf", "simPdf", dataCat);
  RooAbsPdf * pdf_hi = ws.pdf("pdf_hi");
  RooAbsPdf * pdf_pp = ws.pdf("pdf_pp");
  assert(pdf_hi);
  assert(pdf_pp);
  simPdf.addPdf(*pdf_hi, "hi");
  simPdf.addPdf(*pdf_pp, "pp");
  ws.import(simPdf, RooFit::Silence());
  return dynamic_cast<RooSimultaneous *>(ws.pdf("simPdf"));

}

// RooSimultaneous*  buildNullPdf(RooWorkspace &ws, RooCategory const &dataCat) {
//   if (!ws.pdf("pdf") && buildPdf(ws)) {
//     std::cout << "cannot get pdf.\n";
//     return 0;
//   }

//   RooSimPdfBuilder sb(RooArgSet(*(ws.pdf("pdf"))));
//   RooArgSet * config = sb.createProtoBuildConfig();
//   config->setStringValue("physModels", "pdf");
//   config->setStringValue("splitCats", dataCat.GetName());
//   config->setStringValue("pdf", TString(dataCat.GetName()) + " : f2,nsig1,nbkg,bkg_a1,bkg_a2");

//   RooArgSet deps(*(ws.var("invariantMass")),dataCat);

//   RooSimultaneous * sim = sb.buildPdf(*config, deps);
//   sim->SetName("simNullPdf");

//   ws.import(*sim, RooFit::RenameConflictNodes("null"),
// 	    RooFit::RenameAllVariablesExcept("null", "invariantMass,dataCat"));

//   return (RooSimultaneous *)ws.pdf("simNullPdf");
// }

bool readData(RooWorkspace &ws, TString HIfilename, TString ppFilename,
	      TString extraCut = "", double mmin = 7., double mmax = 14.) {

  RooRealVar * mass = ws.var("invariantMass");
  bool deleteMass = false;
  if (!mass) {
    mass = new RooRealVar("invariantMass", "#mu#mu mass", mmin, mmax, 
			  "GeV/c^{2}");
    mass->Print();
    deleteMass = true;
  }
  RooRealVar muppt("muPlusPt" ,"#mu+ pt",2,20,"GeV/c"); 
  RooRealVar mumpt("muMinusPt","#mu- pt",2,20,"GeV/c"); 
  RooRealVar upsPt("upsPt","p_{T}(#Upsilon)",0.,"GeV/c");
//   RooRealVar upsEta("upsEta","#eta(#Upsilon)",0.,"");
  RooRealVar upsRapidity("upsRapidity", "upsRapidity", 0.);
  RooCategory QQsign("QQsign", "QQsign");
  QQsign.defineType("PlusMinus", 0);
  QQsign.defineType("PlusPlus", 1);
  QQsign.defineType("MinusMinus", 2);
  RooRealVar Centrality("Centrality", "Centrality", 0.);
  //RooRealVar vProb("vProb","vProb", 0.0, 1.);

  RooArgSet cols(*mass, muppt, mumpt, upsPt, upsRapidity, QQsign, Centrality);
  //cols.add(vProb);

  TFile * hifile = TFile::Open(HIfilename);
  TTree * tree;
  TString dirTree = treeName;
  if (dirname_.Length() > 0)
    dirTree = dirname_ + "/" + treeName;
  hifile->GetObject(dirTree, tree);
  if (!tree)
    hifile->GetObject("UpsilonTree", tree);
  assert(tree);
  TFile temp("DeleteMe.root", "recreate");
  if (extraCut.Length() > 0) {
    TTree * tree2 = tree->CopyTree(extraCut);
    delete tree;
    tree = tree2;
  }

  RooDataSet hidata("hidata", "hidata", tree, cols);
  delete tree;
  delete hifile;

  TFile * ppfile = TFile::Open(ppFilename);
  tree = 0;
  ppfile->GetObject(dirTree, tree);
  if (!tree)
    ppfile->GetObject("UpsilonTree", tree);
  assert(tree);
  temp.cd();
  if (extraCut.Length() > 0) {
    TTree * tree2 = tree->CopyTree(extraCut);
    delete tree;
    tree = tree2;
  }

  RooDataSet ppdata("ppdata", "ppdata", tree, cols);
  delete tree;
  delete ppfile;

  RooCategory dataCat("dataCat", "dataCat");
  dataCat.defineType("hi");
  dataCat.defineType("pp");

  RooDataSet data("data", "data", cols, RooFit::Index(dataCat),
		  RooFit::Import("hi", hidata), RooFit::Import("pp", ppdata));

//   data.Print("v");
  if (deleteMass) delete mass;
  return ws.import(data/*, RooFit::RecycleConflictNodes(), RooFit::Silence()*/);  
}

double computeRatio(RooRealVar& x, RooRealVar& y) {
  assert(y.getVal() != 0);
  return x.getVal()/y.getVal();
}

double computeRatioError(RooRealVar& x, RooRealVar& y, 
			 double correlation = 0.) {
  double err2 = x.getError()*x.getError()/x.getVal()/x.getVal() +
    y.getError()*y.getError()/y.getVal()/y.getVal() - 
    2.*x.getError()*y.getError()/x.getVal()/y.getVal()*correlation;

  return fabs(computeRatio(x,y))*sqrt(err2);
}

double computeSumError(RooRealVar& x, RooRealVar& y,
		       double correlation = 0.) {
  double err2 = x.getError()*x.getError() + y.getError()*y.getError() +
    correlation*x.getError()*y.getError();
  return sqrt(err2);
}
