float sum_eta20_25[3], sum_eta25_30[3], sum_eta30_35[3], sum_eta35_40[3], sum_eta40_45[3];

void DrawLHCb(){
	gROOT->LoadMacro("setTDRStyle_modified.C");
	setTDRStyle();

	TCanvas *c2 = new TCanvas();//"c1","title",800,600);
	TH1F *frame = gPad->DrawFrame(0,0,4.5,130);
	frame->SetStats(0);
	frame->GetXaxis()->SetTitle("|y|^{Y(1S)}");
	frame->GetYaxis()->SetTitle("d#sigma/dy (nb)");
	frame->GetYaxis()->SetTitleOffset(1.1);
	frame->Draw();

	//CMS

	TFile cmsFile("xsec_1S_ydiff_39pb.root");
	TGraphAsymmErrors* cmsdata = ((TMultiGraph*)cmsFile.Get("mg1"))->GetListOfGraphs()->At(0);
	TFile cmsFile("xsection_1s_rapdiff.root");
	TGraphAsymmErrors* cmsdata3pb = ((TMultiGraph*)cmsFile.Get("mg1"))->GetListOfGraphs()->At(0);

	double norm = 1.0/0.0248;
	double norm3pb = norm/2;
	normalize(cmsdata,norm);
	normalize(cmsdata3pb,norm3pb);

	cmsdata->SetLineWidth(2);
	cmsdata->SetMarkerStyle(20);
	cmsdata->SetMarkerColor(kBlue);
	cmsdata3pb->SetLineWidth(1);
	cmsdata3pb->SetMarkerStyle(22);
	cmsdata3pb->SetMarkerColor(kRed);
	cmsdata3pb->SetMarkerSize(1.2);

	cmsdata->Draw("PZ");
	cmsdata3pb->Draw("PZ");

	//LHCb

	calculateLHCb();
	float eta[5]={2.25,2.75,3.25,3.75,4.25};
	float eta_err[5]={0.25,0.25,0.25,0.25,0.25};
	float y[5]={sum_eta20_25[0],sum_eta25_30[0],sum_eta30_35[0],sum_eta35_40[0],sum_eta40_45[0]};
	float y_err_stat[5]={sum_eta20_25[1],sum_eta25_30[1],sum_eta30_35[1],sum_eta35_40[1],sum_eta40_45[1]};
	float y_err_syst[5]={sum_eta20_25[2],sum_eta25_30[2],sum_eta30_35[2],sum_eta35_40[2],sum_eta40_45[2]};
	float y_err[5];
	for (int i=0; i<3; i++){
		y_err[i]=y_err_stat[i]+y_err_syst[i];
	}
	TGraphErrors *LHCb = new TGraphErrors(5, eta, y, eta_err, y_err_syst);
	LHCb->SetMarkerColor(kGreen+1);
	LHCb->SetMarkerStyle(21);
	LHCb->Draw("samePZ");

	leg = new TLegend(0.35,0.75,0.9,0.9);
	leg->AddEntry(cmsdata, "CMS 39 pb^{-1} (p_{T}<50 GeV/c)", "PLE");
	leg->AddEntry(cmsdata3pb, "CMS 3 pb^{-1} (p_{T}<30 GeV/c)", "PLE");
	leg->AddEntry(LHCb, "LHCb 32.4 pb^{-1} (p_{T}<15 GeV/c)", "PLE");
	leg->Draw();
	TLatex latex1, latex2;
	latex1.DrawLatex(0.5,15,"#Upsilon(1S)");
	latex2.DrawLatex(0.5,30, "#sqrt{s} = 7 TeV");
}

void normalize(TGraphAsymmErrors *gr, double norm) {
	double nbin    = gr->GetN();
	double* xval   = gr->GetX();
	double* yval   = gr->GetY();
	double* yerr_h = gr->GetEYhigh();
	double* yerr_l = gr->GetEYlow (); 
	for(int i=0; i<nbin; i++) {
		gr->SetPoint(i,xval[i],yval[i]*norm);
		gr->SetPointEYhigh(i,yerr_h[i]*norm);
		gr->SetPointEYlow (i,yerr_l[i]*norm);
	}   
	//cout << "aa " << nbin << endl;
}

void calculateLHCb(){
	ifstream in; 
	in.open("LHCb.dat");
	float eta20_25[15][3], eta25_30[15][3], eta30_35[15][3], eta35_40[15][3], eta40_45[15][3];
	for (int i=0; i<15; i++){
		for (int j=0; j<3; j++){
			in >> eta20_25[i][j];
		}   
		for (int j=0; j<3; j++){
			in >> eta25_30[i][j];
		}   
		for (int j=0; j<3; j++){
			in >> eta30_35[i][j];
		}   
		for (int j=0; j<3; j++){
			in >> eta35_40[i][j];
		}   
		for (int j=0; j<3; j++){
			in >> eta40_45[i][j];
		}   
	}   
	for (int i=0; i<15; i++){
		for (int j=0; j<3; j++){    
			cout<< " " << eta20_25[i][j] << " " << eta25_30[i][j] << " " << eta30_35[i][j] << " " << eta35_40[i][j] << " " << eta40_45[i][j] << " " << endl;
		}   
	}   
	for (int i=0; i<15; i++){
		sum_eta20_25[0] += eta20_25[i][0];
		sum_eta25_30[0] += eta25_30[i][0];
		sum_eta30_35[0] += eta30_35[i][0];
		sum_eta35_40[0] += eta35_40[i][0];
		sum_eta40_45[0] += eta40_45[i][0];

		sum_eta20_25[1] += eta20_25[i][1];
		sum_eta25_30[1] += eta25_30[i][1];
		sum_eta30_35[1] += eta30_35[i][1];
		sum_eta35_40[1] += eta35_40[i][1];
		sum_eta40_45[1] += eta40_45[i][1];

		sum_eta20_25[2] += eta20_25[i][2];
		sum_eta25_30[2] += eta25_30[i][2];
		sum_eta30_35[2] += eta30_35[i][2];
		sum_eta35_40[2] += eta35_40[i][2];
		sum_eta40_45[2] += eta40_45[i][2];

	}   
	for (int i=0; i<3; i++){
		cout << endl << " " << sum_eta20_25[i] << " " << sum_eta25_30[i] << " " << sum_eta30_35[i] << " " << sum_eta35_40[i] << " " << sum_eta40_45[i] << " " << endl;
	}
}

