{
	int bin = 7;
	int bin1 = 3;
	float cent[bin]={22.1, 86.3, 130.0, 187.1, 261.4, 329.4, 381.3};
	float cent1[bin1]={64.2184, 261.4178, 355.3528};
	float centErr[bin]={6,6,6,6,6,6,6};
	float centnoErr[bin]={0,0,0,0};

	//pt > 4 Raa
	float ratio1S[bin]={1.005,0.590,0.681,0.614,0.484,0.432,0.411};
	float ratio1SstatErr[bin]={0.121,0.096,0.069,0.053,0.040,0.048,0.043};
	float ratio1SsystErr[bin]={0.176,0.086,0.085,0.075,0.049,0.046,0.048};
	//    float ratio2S[bin]={0.300,0.251,0.237,0.260,0.068,0.044,0.111};
	//    float ratio2SstatErr[bin]={0.157,0.138,0.098,0.079,0.053,0.060,0.061};
	//    float ratio2SsystErr[bin]={0.069,0.050,0.039,0.043,0.022,0.019,0.020};
	float ratio2010[bin1]={0.677, 0.842, 0.454};
	float ratio2010statErr[bin1]={0.154, 0.212, 0.136};
	float ratio2010systErr[bin1]={0.107, 0.130, 0.079};

	TCanvas *c1 = new TCanvas("c1","c1");
	//gPad->SetLogy();

	TF1 *f4 = new TF1("f4","1",0,400);
	f4->SetLineWidth(1);
	f4->GetXaxis()->SetTitle("N_{part}");
	f4->GetYaxis()->SetTitle("R_{AA}");
	f4->GetYaxis()->SetTitleOffset(1.0);
	f4->GetYaxis()->SetRangeUser(0,1.5);
	f4->GetXaxis()->CenterTitle(kTRUE);
	f4->Draw();

	TGraphErrors *g = new TGraphErrors(bin,cent,ratio1S,centnoErr,ratio1SstatErr);
	g->SetMarkerColor(kGreen+2);
	g->SetMarkerStyle(33);
	g->SetMarkerSize(2);

	TGraphErrors *g1Ssyst = new TGraphErrors(bin,cent,ratio1S,centnoErr,ratio1SsystErr);
	g1Ssyst->SetLineColor(kGreen-9);
	g1Ssyst->SetLineWidth(25);
	g1Ssyst->SetMarkerSize(0);
	g1Ssyst->Draw("e");

	g->Draw("pe");

	TGraphErrors *g1circle = new TGraphErrors(bin,cent,ratio1S,centnoErr,ratio1SstatErr);
	g1circle->SetMarkerStyle(27);
	g1circle->SetMarkerSize(2);
	g1circle->SetLineColor(kBlack);
	g1circle->Draw("p");

	TGraphErrors *g2 = new TGraphErrors(bin1,cent1,ratio2010,centnoErr,ratio2010statErr);
	g2->SetMarkerColor(kMagenta+1);
	g2->SetMarkerStyle(20);
	g2->SetMarkerSize(1.2);

	TGraphErrors *g2Ssyst = new TGraphErrors(bin1,cent1,ratio2010,centnoErr,ratio2010systErr);
	g2Ssyst->SetLineColor(kMagenta-9);
	g2Ssyst->SetLineWidth(25);
	g2Ssyst->SetMarkerSize(0);
	g2Ssyst->Draw("e");

	g2->Draw("pe");

	TGraphErrors *g2circle = new TGraphErrors(bin1,cent1,ratio2010,centnoErr,ratio2010statErr);
	g2circle->SetMarkerStyle(24);
	g2circle->SetMarkerSize(1.2);
	g2circle->SetLineColor(kBlack);
	g2circle->Draw("p");

	float ppy[1]={1};
	float ppx[1]={377};
	float ppxEr[1]={0};
	float ppyErSystematic=sqrt(pow(0.06,2)+pow(0.023,2));
	cout<<"ppyErSystematic"<<ppyErSystematic<<endl;
	float ppyErSyst[1]={ppyErSystematic};
	float ppyErtotal=sqrt(pow(ppyErSystematic,2)+pow(0.12,2));
	float ppyErtol[1]={0};
	TBox *lumiY1S = new TBox(385.0,0.864,400.0,1.136);
	lumiY1S->SetFillColor(kGreen-9);
	lumiY1S->Draw("2");
	TGraphErrors *gpp = new TGraphErrors(1,ppx,ppy,ppxEr,ppyErSyst);
	gpp->SetMarkerSize(0);
	gpp->SetLineColor(kGray);
	gpp->SetLineWidth(10);
	//gpp->Draw("e");
	TGraphErrors *gpptol = new TGraphErrors(1,ppx,ppy,ppxEr,ppyErtol);
	gpptol->SetLineWidth(0);
	gpptol->SetLineColor(kGray);
	gpptol->SetMarkerColor(kRed);
	gpptol->SetMarkerStyle(21);
	gpptol->SetMarkerSize(1.1);
	//gpptol->Draw("p");

	TBox *lumiY2S = new TBox(370.0,0.94,385.0,1.06);
	lumiY2S->SetFillColor(kMagenta-9);
	lumiY2S->Draw("2");

	f4->Draw("same");
	gPad->RedrawAxis();

	TLatex *l1 = new TLatex(50,1.37,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
	l1->SetTextFont(42);
	l1->SetTextSize(0.05);
	//TLatex *l1 = new TLatex(25,1.37,"CMS Preliminary, PbPb #sqrt{s_{NN}} = 2.76 TeV");
	//l1->SetTextSize(0.045);
	l1->Draw();

	TLatex *lumi = new TLatex(240,1.22,"L_{int} = 150 #mub^{-1}");
	//	lumi->Draw();

	TLatex *ly = new TLatex(240,1.1,"|y| < 2.4");
	ly->Draw();

	TLatex *mupt = new TLatex(240,1.05,"p_{T}^{#mu} > 4 GeV/c");
	//	mupt->Draw();

	TLatex *centrality = new TLatex(340,0.62,"0-10%");
	centrality->SetTextSize(0.03);
	centrality->Draw();
	centrality->DrawLatex(240,0.58,"10-20%");
	centrality->DrawLatex(40,0.85,"20-100%");

	TLegend *legend = new TLegend(0.25,0.73,0.6,0.85);
	legend->SetTextSize(0.04);
	legend->SetFillStyle(0);
	legend->SetFillColor(0);
	legend->SetTextFont(42);
	legend->AddEntry(g,"#varUpsilon(1S) 2011","p");
	//legend->AddEntry(g1Ssyst, "#Upsilon(1S), syst. unc.","l");
	legend->AddEntry(g2, "#varUpsilon(1S) 2010","p");
	//legend->AddEntry((TObject*)0, "#Upsilon(2S), syst. unc.","");
	legend->Draw();

	c1->SaveAs("upsilon_RAA_Y1S2010.gif");
	c1->SaveAs("upsilon_RAA_Y1S2010.pdf");
}
