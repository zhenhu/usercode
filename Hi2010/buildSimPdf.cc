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

#include "TTree.h"
#include "TFile.h"

float mmin = 7.0, mmax = 14.0;
TString dirname_ = "";
TString treeName = "UpsilonTree_allsign";

bool buildPdf(RooWorkspace &ws, bool hi, bool doKeys = false) {

  double const M1S(9.460);
  double const M2S(10.023);
  double const M3S(10.355);
  RooRealVar * mass = ws.var("invariantMass");
  if (!mass) {
    mass = new RooRealVar("invariantMass", "#mu#mu mass", mmin, mmax, 
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
  sigma1.setConstant();
  RooFormulaVar sigma1S("sigma1S", "@0", RooArgList(sigma1));
  RooFormulaVar sigma2S("sigma2S", "@0*@1", RooArgList(sigma1,rat2));
  RooFormulaVar sigma3S("sigma3S", "@0*@1", RooArgList(sigma1,rat3));

  RooRealVar alpha("alpha", "#alpha", 1.6, 0.1, 10.);
  alpha.setConstant();
  RooRealVar npow("npow", "n_{CB}", 2.3, 0.1, 10.);
  npow.setConstant();

  RooCBShape sig1S("sig1S", "sig1S", *mass, mean1S, sigma1S, alpha, npow);
  RooCBShape sig2S("sig2S", "sig2S", *mass, mean2S, sigma2S, alpha, npow);
  RooCBShape sig3S("sig3S", "sig3S", *mass, mean3S, sigma3S, alpha, npow);

  RooRealVar nsig1("nsig1", "N_{1S}", 100, -1000, 1e6);
  RooRealVar f23("f23", "(2S+3S)/1S", 0.5);
  f23.setConstant(false);
  RooRealVar f2("f2", "2S/1S", 0.2);
//   RooRealVar f2("f2", "3S/2S", 0.6, 0., 10.);
  f2.setConstant(false);

  RooFormulaVar nsig2("nsig2", "@0*@1", RooArgList(nsig1,f2));
  RooFormulaVar nsig3("nsig3", "@0*(@1-@2)", RooArgList(nsig1, f23, f2));

//   RooFormulaVar nsig2("nsig2", "@0*@1/(1+@2)", RooArgList(nsig1, f23, f2));
//   RooFormulaVar nsig3("nsig3", "@0*@1*@2/(1+@2)", RooArgList(nsig1, f23, f2));
  RooRealVar turnOn("turnOn","turnOn", 6.);
  turnOn.setConstant(false);
  RooRealVar width("width","width", 1., 0., 20.);
  RooRealVar decay("decay","decay", 7.);
  decay.setConstant(false);
  RooGenericPdf bkgErfExp("bkg","bkg",
		       "exp(-@0/@3)*(TMath::Erf((@0-@1)/@2)+1)",
		       RooArgList(*mass, turnOn, width, decay));

  RooRealVar nbkg("nbkg", "N_{bkg}", 5000., -1000., 1e6);

  RooRealVar bkg_a1("bkg_a1", "a_{1,bkg}", 0., -2., 2.);
  RooRealVar bkg_a2("bkg_a2", "a_{2,bkg}", 0., -2., 2.);
  RooChebychev bkgPoly("bkgPoly", "bkg", *mass, 
		       RooArgList(bkg_a1, bkg_a2));
  RooRealVar * nLikeSign = 0;
  RooKeysPdf * LikeSignPdf = 0;
  RooFormulaVar * nPoly = 0;
  if (doKeys) {

    TString likeSignCut("(QQsign != QQsign::PlusMinus)"
			"&&(dataCat == dataCat::");
    likeSignCut += (hi) ? "hi)" : "pp)";
    RooDataSet * likeSignData = 
      dynamic_cast<RooDataSet*>(ws.data("data")->reduce(likeSignCut));

    assert(likeSignData);
    LikeSignPdf = new RooKeysPdf("bkgLikeSignPdf", "bkgLikeSignPdf", *mass, 
				 *likeSignData, RooKeysPdf::MirrorBoth, 1.2);
    nLikeSign = 
      new RooRealVar("nLikeSign", "nLikeSign", 
		     likeSignData->sumEntries(TString::Format("(%s>%0.1f)&&"
							      "(%s<%0.1f)",
							      mass->GetName(),
							      mmin, 
							      mass->GetName(),
							      mmax)));
    delete likeSignData;
    std::cout << "like sign events: " << nLikeSign->getVal() << '\n';
    nPoly =  new RooFormulaVar ("nPoly", "nPoly", "@0-@1",
				RooArgList(nbkg,*nLikeSign));
  }

//   RooExtendPdf sig1SN("sig1SN", "sig1SN", sig1SN, nsig1);
//   RooExtendPdf sig2SN("sig2SN", "sig2SN", sig2SN, nsig2);
//   RooExtendPdf sig3SN("sig3SN", "sig3SN", sig3SN, nsig3);
//   RooExtendPdf bkgN("bkgN", "bkgN", bkgN, nbkg);

  // RooAddPdf pdf("pdf", "pdf", RooArgList(sig1SN, sig2SN, sig3SN, bkgN));
  RooArgList pdfs(sig1S, sig2S, sig3S);
  RooArgList norms(nsig1, nsig2, nsig3);
  RooAddPdf sig("sig", "sig", pdfs, norms);
  ws.import(sig, RooFit::RenameAllNodes((hi)?"hi":"pp"),
	    RooFit::RenameAllVariablesExcept((hi)? "hi": "pp", 
					     "npow,invariantMass,"
					     "alpha,"
					     "sigma1"), 
	    RooFit::Silence());

  if (doKeys) {
    RooAddPdf bkg("bkg", "bkg", RooArgList(*LikeSignPdf, bkgPoly),
		  RooArgList(*nLikeSign, *nPoly));
    ws.import(bkg, RooFit::RenameAllNodes((hi)?"hi":"pp"),
	      RooFit::RenameAllVariablesExcept((hi)? "hi": "pp", 
					       "npow,invariantMass,"
					       "alpha,"
					       "sigma1"), 
	      RooFit::Silence());
    pdfs.add(RooArgList(*LikeSignPdf, bkgPoly));
    norms.add(RooArgList(*nLikeSign, *nPoly));
  } else {
    if (hi)
      pdfs.add(bkgErfExp);
    else {
      bkgPoly.SetName("bkg");
      pdfs.add(bkgPoly);
    }
    norms.add(nbkg);
  }
//   RooAddPdf pdf(pdfName, pdfName, RooArgList(sig, bkg));

  RooAddPdf pdf("pdf", "pdf", pdfs, norms);

  //pdf.Print("v");
  ws.import(pdf, 
	    RooFit::RenameAllNodes((hi)?"hi":"pp"),
	    RooFit::RenameAllVariablesExcept((hi)? "hi": "pp", 
					     "npow,invariantMass,"
					     "alpha,"
					     "sigma1"),
	    RooFit::RecycleConflictNodes());

  if (doKeys) {
    delete nLikeSign;
    delete LikeSignPdf;
    delete nPoly;
  }
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
	      TString extraCut = "") {

  RooRealVar * mass = ws.var("invariantMass");
  if (!mass) {
    mass = new RooRealVar("invariantMass", "#mu#mu mass", mmin, mmax, 
			  "GeV/c^{2}");
    mass->setBins(70);
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

  RooArgSet cols(*mass, muppt, mumpt, upsPt, upsRapidity, QQsign, Centrality);

  TFile hifile(HIfilename, "read");
  TTree * tree;
  TString dirTree = treeName;
  if (dirname_.Length() > 0)
    dirTree = dirname_ + "/" + treeName;
  hifile.GetObject(dirTree, tree);
  assert(tree);
  TFile temp("DeleteMe.root", "recreate");
  if (extraCut.Length() > 0) {
    TTree * tree2 = tree->CopyTree(extraCut);
    delete tree;
    tree = tree2;
  }

  RooDataSet hidata("hidata", "hidata", tree, cols);
  delete tree;

  TFile ppfile(ppFilename, "read");
  tree = 0;
  ppfile.GetObject(dirTree, tree);
  assert(tree);
  temp.cd();
  if (extraCut.Length() > 0) {
    TTree * tree2 = tree->CopyTree(extraCut);
    delete tree;
    tree = tree2;
  }

  RooDataSet ppdata("ppdata", "ppdata", tree, cols);
  delete tree;

  RooCategory dataCat("dataCat", "dataCat");
  dataCat.defineType("hi");
  dataCat.defineType("pp");

  RooDataSet data("data", "data", cols, RooFit::Index(dataCat),
		  RooFit::Import("hi", hidata), RooFit::Import("pp", ppdata));

//   data.Print("v");
  return ws.import(data/*, RooFit::RecycleConflictNodes(), RooFit::Silence()*/);  
}

double computeRatio(RooRealVar& x, RooRealVar& y) {
  assert(y.getVal() != 0);
  return x.getVal()/y.getVal();
}

double computeRatioError(RooRealVar& x, RooRealVar& y) {
  double err = x.getError()*x.getError()/x.getVal()/x.getVal() +
    y.getError()*y.getError()/y.getVal()/y.getVal();

  return computeRatio(x,y)*sqrt(err);
}
