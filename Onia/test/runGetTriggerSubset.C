#include "GetTriggerSubset.C"
void runGetTriggerSubset()
{
	std::vector<TString> PD, Trigger;
	PD.push_back("Charmonium");        Trigger.push_back("_Jpsi");
	PD.push_back("Charmonium");        Trigger.push_back("_psiprime");
	PD.push_back("Charmonium");        Trigger.push_back("_Bs");
	PD.push_back("MuOnia");            Trigger.push_back("_Upsilon");
	PD.push_back("MuOnia");            Trigger.push_back("_phi");
	PD.push_back("DoubleMuonLowMass"); Trigger.push_back("_");
	PD.push_back("DoubleMuon");        Trigger.push_back("_");

	for (int i=0; i<7; i++) {
		TChain * chain = new TChain("rootuple/oniaTree","");
		chain->Add("/eos/uscms/store/user/zhenhu/"+PD[i]+"/Onia2MuMuRootuple-Run2015B-"+PD[i]+"-v5/f64ae4aafa8965110120322f8d8de3c5/RootupleAll.root"); //run 251143 - 251562
		chain->Add("/eos/uscms/store/user/zhenhu/"+PD[i]+"/Onia2MuMuRootuple-Run2015B-"+PD[i]+"-v6/f64ae4aafa8965110120322f8d8de3c5/RootupleAll.root"); //run 251638 - 251883 
		GetTriggerSubset a(chain);
		a.Loop(PD[i]+Trigger[i]);
	}
}
