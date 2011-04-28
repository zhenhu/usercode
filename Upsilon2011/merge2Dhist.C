void merge(TString name, TFile *f1, TFile *f2, TFile *fout){
	TH2F *h = new TH2F("acc_pt35_eta16_pt25_eta24_trk_"+name,name,50,0,50,26,0,26);
	h->SetYTitle("Upsilon Rapidity");
	h->SetXTitle("Upsilon pT (GeV/c)");

	TH2F *h1 = (TH2F*)f1->Get("acc_pt35_eta16_pt25_eta24_trk_"+name);
	h1->SetName("h1");
	//TCanvas *c1 = new TCanvas("c1","c1");
	//c1->cd();
	//h1->Draw("TEXT45");
	for (int eta=0; eta<=27; eta++){
		for (int pt=0; pt<=31; pt++){
			int Bin1 = h1->GetBin(pt,eta);
			double BinContent1 = h1->GetBinContent(Bin1);
			h->SetBinContent(pt,eta,BinContent1);
			//cout<<"pt "<<pt<<" eta "<<eta<<" Bin "<<Bin1<<" content "<<BinContent1<<endl;
		}   
	}   

	TH2F *h2 = (TH2F*)f2->Get("acc_pt35_eta16_pt25_eta24_trk_"+name+"_highpt");
	h2->SetName("h2");
	//TCanvas *c2 = new TCanvas("c2","c2");
	//c2->cd();
	//h2->Draw("TEXT45");
	for (int eta=0; eta<=27; eta++){
		for (int pt=1; pt<=21; pt++){
			int Bin2 = h2->GetBin(pt,eta);
			double BinContent2 = h2->GetBinContent(Bin2);
			int newpt = pt+30;
			h->SetBinContent(newpt,eta,BinContent2);
			//cout<<"pt "<<newpt<<" eta "<<eta<<" Bin "<<Bin2<<" content "<<BinContent2<<endl;
		}   
	}  

	for (int eta=0; eta<=27; eta++){
		for (int pt=0; pt<=51; pt++){
			int Bin = h->GetBin(pt,eta);
			double BinContent = h->GetBinContent(Bin);
			//cout<<"pt "<<pt<<" eta "<<eta<<" Bin "<<Bin<<" content "<<BinContent<<endl;
		}   
	}   
	//TCanvas *c3 = new TCanvas("c3","c3");
	//c3->cd();
	//h->Draw("TEXT45");
	fout->cd();
	h->Write();
}


void merge2Dhist(){
	TFile *f = new TFile("acceptance_pt0-50.root","RECREATE");
	TFile *f_pt0_30 = new TFile("acceptance.root");
	TFile *f_pt30_50 = new TFile("acceptance_hipt2.root");
	merge("unpol",f_pt0_30,f_pt30_50,f);
	merge("helT",f_pt0_30,f_pt30_50,f);
	merge("helL",f_pt0_30,f_pt30_50,f);
	merge("csT",f_pt0_30,f_pt30_50,f);
	merge("csL",f_pt0_30,f_pt30_50,f);
	f->Write();
}

