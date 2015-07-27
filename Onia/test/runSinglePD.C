#include "SinglePD.C"
void runSinglePD()
{
	TChain * chain = new TChain("rootuple/oniaTree","");
	//TString PD = "DoubleMuon";        // all peaks from omega to Z
	//TString PD = "DoubleMuonLowMass"; // 
	TString PD = "Charmonium";        // Bs, Jpsi, psiprime 
	//TString PD = "MuOnia";            // phi, Upsilon

	chain->Add("/eos/uscms/store/user/zhenhu/"+PD+"/Onia2MuMuRootuple-Run2015B-"+PD+"-v5/f64ae4aafa8965110120322f8d8de3c5/RootupleAll.root"); //run 251143 - 251562
	chain->Add("/eos/uscms/store/user/zhenhu/"+PD+"/Onia2MuMuRootuple-Run2015B-"+PD+"-v6/f64ae4aafa8965110120322f8d8de3c5/RootupleAll.root"); //run 251638 - 251883

	SinglePD a(chain);
	a.Loop(PD);
}
