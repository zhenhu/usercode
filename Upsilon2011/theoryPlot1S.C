void theoryPlot1S(){

  double norm = 0.25; 

  gROOT->SetStyle("Plain");

  //gROOT->LoadMacro("../xsection/setTDRStyle_modified.C");
  //setTDRStyle();
  TString ytitle = TString::Format("d^{2}#sigma/dp_{T}dy #times #Beta(#mu#mu)  (nb/(GeV/c))");

  enum enuth {_data=0,_pythia,_cem,_cascade};
  int grcolor[4] = {1,4, 2,8};
  for(int i=0;i<4;i++) grcolor[i]=1; //remove color

  bool sample = 1; //40pb
  //bool sample = 0; //3pb

  if  (sample == 1) TFile cmsFile("xsection_1s_y0_40.root");     //40pb
  else TFile cmsFile("xsection_1s_rap_0_2.root"); //3pb

  TGraphAsymmErrors* cmsdata = ((TMultiGraph*)cmsFile.Get("mg1"))->GetListOfGraphs()->At(1);
  //TGraphAsymmErrors* cmsdata1 = ((TMultiGraph*)cmsFile.Get("mg1"))->GetListOfGraphs()->At(1);

  TCanvas *c2 = new TCanvas();//"c1","title",800,600);
  TH1F *frame = gPad->DrawFrame(0,0.0002,30,1);
  //TH2F * frame = new TH2F("frame","", 1000,0.,30., 0, 0.001,10);
  frame->SetStats(0);

  frame->GetXaxis()->SetTitle("p_{T}^{Y} (GeV/c)");
  frame->GetYaxis()->SetTitle("d#sigma/dp_{T} * BR (nb/(GeV/c))");
  frame->GetXaxis()->SetTitle("p_{T}^{Y} (GeV/c)");
  frame->GetYaxis()->SetTitle(ytitle);
			     
  frame->GetYaxis()->SetTitleOffset(1.1);
  frame->Draw();

  //////////////////////////////////////////////
  ///// PYTHIA
  //////////////////////////////////////////////

  TFile* fp = new TFile("../GenCrossSection/genXSupsilon1S.root"); // open the file
  TH1F* hist1 = (TH1F*)gDirectory->Get("genPt"); // get the hist
  TH1F* genPtLargeBins = (TH1F*)gDirectory->Get("genPtLargeBins"); // get the hist
  TGraphAsymmErrors* genPtLargeBinsGraph = (TGraphAsymmErrors*)gDirectory->Get("genPtLargeBinsGraph");
  //hist1->SetLineWidth(2);
  //hist1->SetLineColor(4);
  //  hist1->Draw();

  ///////////////////////////////////////////////
  ////// Color octet Pierre
  ///////////////////////////////////////////////
  /*
  ifstream in;
  if(opt==1){
  in.open("DirectJpsi_CMSfullrap_clean.dat");
  } 
  if(opt==2){
    in.open("DirectJpsi_CMSrap_0_1.4_clean.dat");
  }
  if(opt==3){
    in.open("DirectJpsi_CMSrap_1.4_2.4_clean.dat");
  }
  Float_t pt[200], xscen[200], xsmin[200], xsmax[200], xserrlow[200], xserrhigh[200],pterr[200], xscen_corr[200], xserrlow_corr[200], xserrhigh_corr[200];
  for(int i=0; i<39; i++){
    in >> pt[i] >> xscen[i] >> xserrlow[i] >> xserrhigh[i]; 
    cout << "pt[i]= " << pt[i] << " xscen[i]= "<< xscen[i] <<"+" << xserrlow[i]<<  "-" << xserrhigh[i]<<  endl;
    xserrlow[i]=fabs(xserrhigh[i]);
    xserrhigh[i]=xserrlow[i];
    pterr[i]=0;
    Float_t factor=1000*0.0598;
    xscen_corr[i]=xscen[i]*factor;
    xserrlow_corr[i]=xserrlow[i]*factor;
    xserrhigh_corr[i]=xserrhigh[i]*factor;
  }
  
  TGraphAsymmErrors* gr;
  gr= new TGraphAsymmErrors(39,pt,xscen_corr,pterr,pterr, xserrlow_corr,xserrhigh_corr);
  gr->SetFillColor(7);
  gr->SetLineColor(7);
  TGraph * grline;
  grline= new TGraph(39,pt,xscen_corr);
  grline->SetLineWidth(5);
  grline->SetLineColor(7);
  */

  ///////////////////////////////////////////
  ///// CASCADE
  ///////////////////////////////////////////
  TH1F* histcascade_dir = new TH1F("hcas1","dsigma/dptjpsi*BR(jpsi->mumu) (pb/GeV) vs ptjpsi ",100,0.,100.);
  TH1F* histcascade_chi2p = new TH1F("hcas2","dsigma/dptjpsi*BR(jpsi->mumu) (pb/GeV) vs ptjpsi ",100,0.,100.);
  TH1F* histcascade_chi1p = new TH1F("hcas3","dsigma/dptjpsi*BR(jpsi->mumu) (pb/GeV) vs ptjpsi ",100,0.,100.);

  ifstream in,in1,in2;
  in.open("Upsilon-txt/upsilon1s-pt-1eta2-dir1s.txt");
  in1.open("Upsilon-txt/upsilon1s-pt-1eta2-chi2p.txt");
  in2.open("Upsilon-txt/upsilon1s-pt-1eta2-chi1p.txt");

  Float_t pt_cas_dir[200], pterr_cas_dir[200], xsc_cas_dir[200];
  Float_t pt_cas_chi2p[200], pterr_cas_chi2p[200], xsc_cas_chi2p[200];
  Float_t pt_cas_chi1p[200], pterr_cas_chi1p[200], xsc_cas_chi1p[200];

  for(int i=1; i<101; i++){
    in >> xsc_cas_dir[i] >> pt_cas_dir[i] ;//cascade_dir;
    in1 >> xsc_cas_chi2p[i] >> pt_cas_chi2p[i];//cascade_chi2p
    in2 >> xsc_cas_chi1p[i] >> pt_cas_chi1p[i];//cascade_chi1p

    cout << "CASCADE_dir: pt[i]= " << pt_cas_dir[i] << " xsc_cas_dir[i]= "<< xsc_cas_dir[i]<<  endl;
    cout << "CASCADE_chi2: pt[i]= " << pt_cas_chi2p[i] << " xsc_cas_chi2p[i]"<< xsc_cas_chi2p[i]<<  endl;
  }
  for(int i=1; i<101; i++){
    histcascade_dir->SetBinContent(i, xsc_cas_dir[i]);
    histcascade_chi2p->SetBinContent(i, xsc_cas_chi2p[i]);
    histcascade_chi1p->SetBinContent(i, xsc_cas_chi1p[i]);
  }
   histcascade_dir->Add(histcascade_chi2p);
   histcascade_dir->Add(histcascade_chi1p);
  cout<<"CASCADE intgrated cross section = "<<histcascade_dir->Integral("width")<<endl;

/*  TFile* f1 = new TFile("cascade-pp-7000-upsilon.root"); // open the file
  f1->cd("BPH10_003");
  TH1F* hh=(TH1F*)gDirectory->Get("h101");
  TFile* f2 = new TFile("cascade-pp-7000-chi_b.root"); // open the file
  f2->cd("BPH10_003");
  TH1F* gg=(TH1F*)gDirectory->Get("h101");
  gg->Add(hh);
  //gg->SetLineWidth(2);
  //gg->SetLineColor(8);
*/

  ////////////////////////
  /// CEM
  ////////////////////////

  TH1F* histcem = new TH1F("htot1","dsigma/dptjpsi*BR(jpsi->mumu) (pb/GeV) vs ptjpsi ",98,1.,50.);
  ifstream in;
  in.open("upsilon_cem.dat");

  Float_t pt[200], pterr[200], xscen[200];
  for(int i=1; i<97; i++){
    Float_t cem;
    in >> pt[i] >> cem;
    // from Ramona Vogt
    xscen[i]=cem*2*3.14*pt[i]*0.0248;
    //cout << i << " CEM: pt[i]= " << pt[i] << " xscen[i]= "<< xscen[i]<<  endl;
    pterr[i]=0; // not known
  }
  for(int i=1; i<97; i++){
    histcem->SetBinContent(i, xscen[i]);
  }
  //histcem->SetLineWidth(2);
  //histcem->SetLineColor(2);
  cout<<"CEM intgrated cross section = "<<histcem->Integral("width")<<endl;


  ////////////////////////
  /// NRQCD
  ////////////////////////

  ifstream in_nrqcd; 
  in_nrqcd.open("upsilon_nrqcd.dat");

  Double_t pt_nrqcd[100], pt_nrqcdErr[100], xsecDown[100], xsecUp[100], xsecMean[100], xsecErr[100];
  for(int i=0; i<45; i++){
    in_nrqcd >> pt_nrqcd[i] >> xsecDown[i] >> xsecUp[i];
	pt_nrqcdErr[i]=0;
	xsecMean[i]=(xsecDown[i]+xsecUp[i])/2.0*norm;
	xsecErr[i]=(xsecDown[i]-xsecUp[i])/2.0*norm;
    //cout << i << " NRQCD: pt[i]= " << pt_nrqcd[i] << " xsecDown[i]= "<< xsecMean[i]-xsecErr[i] << " xsecUp[i]= "<< xsecMean[i]+xsecErr[i] << endl;
  }
  TGraphErrors* nrqcd = new TGraphErrors(45, pt_nrqcd, xsecMean, pt_nrqcdErr, xsecErr);


  ////////////////////////
  /// CMS
  ////////////////////////

  float scale=1.0/0.5; //the feed down fraction factor

  float Nlo_pt[8]={3,5,10,15,20,25,30,35};
  float Nlo_pt_err[8]={0,0,0,0,0,0,0,0};
  float Nlo_high[8];
  float Nlo_low[8];
  float Nlo_high1[8]={0.16,0.095,0.011,0.0015,0.0003,0.00006,0.00002,0.000006};
  float Nlo_low1[8] ={0.065,0.04,0.005,0.00075,0.00013,0.00003,0.00001,0.0000035};
  float Nlo_high0[8]={0.18,0.11, 0.013,0.0018,0.00036,0.000075,0.000025,0.000008};
  float Nlo_low0[8] ={0.07,0.043,0.006,0.001, 0.0002, 0.000045,0.000015,0.000005};
  float Nlo_mean[8];
  float Nlo_error[8];
  for (int i=0; i<8; i++){
	Nlo_high[i]=(Nlo_high0[i]+Nlo_high1[i])/2.0;
	Nlo_low[i]=(Nlo_low0[i]+Nlo_low1[i])/2.0;
    Nlo_mean[i]=(Nlo_high[i]+Nlo_low[i])/2.0;
    Nlo_error[i]=(Nlo_high[i]-Nlo_low[i])/2.0;
    Nlo_mean[i]=Nlo_mean[i]*scale;
    Nlo_error[i]=Nlo_error[i]*scale;
  }
  TGraphErrors* NLO = new TGraphErrors(8,Nlo_pt,Nlo_mean,Nlo_pt_err,Nlo_error);

  float NNlo_pt[7]={5,10,15,20,25,30,35};
  float NNlo_pt_err[7]={0,0,0,0,0,0,0};
  float NNlo_high[8];
  float NNlo_low[8];
  float NNlo_high1[7]={0.24,0.048,0.0089,0.0022,0.00058,0.00018,0.000062};
  float NNlo_low1[7] ={0.042,0.006,0.0012,0.00026,0.00007,0.000026,0.0000097};
  float NNlo_high0[7]={0.27, 0.056, 0.01,  0.0026, 0.0007,  0.00021, 0.000076};
  float NNlo_low0[7] ={0.045,0.0072,0.0015,0.00036,0.000093,0.000035,0.000012};
  float NNlo_mean[7];
  float NNlo_error[7];
  for (int i=0; i<7; i++){
    NNlo_high[i]=(NNlo_high0[i]+NNlo_high1[i])/2.0;
    NNlo_low[i]=(NNlo_low0[i]+NNlo_low1[i])/2.0;
    NNlo_mean[i]=(NNlo_high[i]+NNlo_low[i])/2.0;
    NNlo_error[i]=(NNlo_high[i]-NNlo_low[i])/2.0;
    NNlo_mean[i]=NNlo_mean[i]*scale;
    NNlo_error[i]=NNlo_error[i]*scale;
  }
  TGraphErrors* NNLO = new TGraphErrors(7,NNlo_pt,NNlo_mean,NNlo_pt_err,NNlo_error);


  ////////////////////////////
  /// NOW ALL TOGETHER!
  ////////////////////////////


  c2->cd();
  c2->SetLeftMargin(0.15);
  c2->SetLogy();
  frame->Draw();

  cmsdata->SetLineWidth(3);
  //cmsdata->SetMarkerColor(1);
  //cmsdata->SetMarkerStyle(20);
  //cmsdata->SetMarkerSize(0.5);

  cmsdata->SetLineColor(grcolor[_data]);
  hist1  ->SetLineColor(grcolor[_pythia]);
  histcem->SetLineColor(grcolor[_cem]);
  histcascade_dir     ->SetLineColor(grcolor[_cascade]);
  
  histcascade_dir->SetLineWidth(3);
  histcascade_dir->SetLineStyle(3);
  
  histcem->SetLineWidth(2);
  histcem->SetLineStyle(6);

  nrqcd->SetFillColor(7);
  nrqcd->SetLineColor(7);

  hist1->SetLineWidth(2);
  hist1->SetLineStyle(1);

  NLO->SetFillColor(kGreen);
  NLO->SetFillStyle(3144);
  NLO->SetLineColor(kGreen);

  NNLO->SetFillColor(6);
  NNLO->SetFillStyle(3244);
  NNLO->SetLineColor(6);

  //normalize
  histcascade_dir   ->Scale(norm);
  hist1  ->Scale(norm);
  histcem->Scale(norm);
  if (sample == 1) normalize(cmsdata,1.0/2.4);  // 40pb
  else normalize(cmsdata,1.0/4.0);

  ///// pierre
  //gr->Draw("E4");
  ///// NRQCD
  nrqcd->Draw("3");
  NLO->Draw("same 3");
  NNLO->Draw("same 3");
  ///// cascade 
  histcascade_dir->Draw("same HIST ");
  ///// cem
  histcem->Draw("same L");
  //// /pyt
  hist1->Draw("same HIST c");
  cmsdata->Draw("Psame");
  //cmsdata1->Draw("Psame");

  TLatex latex;
  //latex.DrawLatex(21,0.05,"|y^{#Upsilon}|<2");

  TLatex latex2;
  latex2.DrawLatex(2,0.003,"#Upsilon(1S)");

  TLatex latex3;
  if (sample == 1) latex3.DrawLatex(2,0.001 , "#sqrt{s}=7 TeV, L= 39 pb^{-1}");
  else latex3.DrawLatex(2,0.001 , "#sqrt{s}=7 TeV, L= 3 pb^{-1}");

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9);
  //leg->SetBorderSize(0);
  //leg->SetFillColor(10);

  leg->AddEntry(cmsdata, "CMS data", "PML");
  //leg->AddEntry(gr, "Direct #Upsilon, LO NRQCD, Artoisenet", "FL");
  leg->AddEntry(nrqcd, "NRQCD", "F");
  leg->AddEntry(NLO, "NLO", "F");
  leg->AddEntry(NNLO, "NNLO*", "F");
  leg->AddEntry(hist1,"PYTHIA", "L");
  leg->AddEntry(histcem, "CEM", "L");
  leg->AddEntry(histcascade_dir, "CASCADE", "L");
  leg->Draw();

  //c2->Print("theoryPlot1S.gif");
  //c2->Print("theoryPlot1S.eps");
  //c2->Print("theoryPlot1S.pdf");
  //c2->SaveAs("theoryPlot1S.root");

  hist1->Scale(7.37/15.17);
  hist1->Draw("same HIST c");
  c2->Print("theoryPlot1Sscaled.gif");
  //c2->Print("theoryPlot1Sscaled.eps");
  c2->Print("theoryPlot1Sscaled.pdf");
  //c2->SaveAs("theoryPlot1Sscaled.root");
/*
  for(int i=0; i<cmsdata->GetN(); i++){
    cmsdata->GetEXhigh()[i+1] = 0;//genPtLargeBins->GetEXhigh()[i];
    cmsdata->GetEXlow()[i+1] = 0;// genPtLargeBins->GetEXlow()[i];
  }
  frame->Draw();
  nrqcd->Draw("same F");
  cmsdata->Draw("same P");
  leg = new TLegend(0.4,0.75,0.9,0.9);
  leg->AddEntry(cmsdata, "CMS data", "PML");
  leg->AddEntry(nrqcd, "NRQCD", "F");
  leg->Draw();
  //latex.DrawLatex(21,0.08,"|y^{#Upsilon}| < 2");
  latex2.DrawLatex(2,0.0015,"#Upsilon(1S)");
  latex3.DrawLatex(2,0.0004 , "#sqrt{s} = 7 TeV, L = 39 pb^{ -1}");
  c2->Print("theoryPlot1S_nrqcd.gif");
  //c2->Print("theoryPlot1S_nrqcd.eps");
  c2->Print("theoryPlot1S_nrqcd.pdf");
  //c2->SaveAs("theoryPlot1S_nrqcd.root");

  for(int i=0; i<cmsdata->GetN(); i++){
    cmsdata->GetEXhigh()[i+1] = 0;//genPtLargeBins->GetEXhigh()[i];
    cmsdata->GetEXlow()[i+1] = 0;// genPtLargeBins->GetEXlow()[i];
  }
  frame->Draw();
  histcascade_dir->Draw("sameHIST");
  cmsdata->Draw("same P");
  leg = new TLegend(0.4,0.75,0.9,0.9);
  leg->AddEntry(cmsdata, "CMS data", "PML");
  leg->AddEntry(histcascade_dir, "CASCADE", "L");
  leg->Draw();
  //latex.DrawLatex(21,0.08,"|y^{#Upsilon}| < 2");
  latex2.DrawLatex(2,0.0015,"#Upsilon(1S)");
  latex3.DrawLatex(2,0.0004 , "#sqrt{s} = 7 TeV, L = 39 pb^{ -1}");
  c2->Print("theoryPlot1S_cascade.gif");
  //c2->Print("theoryPlot1S_cascade.eps");
  c2->Print("theoryPlot1S_cascade.pdf");

  for(int i=0; i<cmsdata->GetN(); i++){
    cmsdata->GetEXhigh()[i+1] = 0;//genPtLargeBins->GetEXhigh()[i];
    cmsdata->GetEXlow()[i+1] = 0;// genPtLargeBins->GetEXlow()[i];
  }
  frame->Draw();
  histcem->Draw("same L");
  cmsdata->Draw("same P");
  leg = new TLegend(0.4,0.75,0.9,0.9);
  leg->AddEntry(cmsdata, "CMS data", "PML");
  leg->AddEntry(histcem,"CEM", "L");
  leg->Draw();
  //latex.DrawLatex(21,0.08,"|y^{#Upsilon}| < 2");
  latex2.DrawLatex(2,0.0015,"#Upsilon(1S)");
  latex3.DrawLatex(2,0.0004 , "#sqrt{s} = 7 TeV, L = 39 pb^{ -1}");
  c2->Print("theoryPlot1S_CEM.gif");
  //c2->Print("theoryPlot1S_CEM.eps");
  c2->Print("theoryPlot1S_CEM.pdf");

  for(int i=0; i<cmsdata->GetN(); i++){
    cmsdata->GetEXhigh()[i+1] = 0;//genPtLargeBins->GetEXhigh()[i];
    cmsdata->GetEXlow()[i+1] = 0;// genPtLargeBins->GetEXlow()[i];
  }
  for(int i=0; i<genPtLargeBinsGraph->GetN(); i++){
    genPtLargeBinsGraph->GetY()[i] = genPtLargeBinsGraph->GetY()[i]*7.37/15.17*norm;
  }
  frame->Draw();
  genPtLargeBinsGraph->SetMarkerStyle(1);
  genPtLargeBinsGraph->SetMarkerSize(0.);
  genPtLargeBinsGraph->Draw("same PEz");
  cmsdata->Draw("same P");
  leg = new TLegend(0.4,0.75,0.9,0.9);
  leg->AddEntry(cmsdata, "CMS data", "PMLE");
  leg->AddEntry(genPtLargeBinsGraph,"PYTHIA (normalized)", "L");
  leg->Draw();
  //latex.DrawLatex(21,0.08,"|y^{#Upsilon}| < 2");
  latex2.DrawLatex(2,0.0015,"#Upsilon(1S)");
  latex3.DrawLatex(2,0.0004 , "#sqrt{s} = 7 TeV, L = 39 pb^{ -1}");
  c2->Print("theoryPlot1Sbinned.gif");
  //c2->Print("theoryPlot1Sbinned.eps");
  c2->Print("theoryPlot1Sbinned.pdf");
  hist1->Draw("same HIST c");
  c2->Print("theoryPlot1Scombined.gif");
  //c2->Print("theoryPlot1Scombined.eps");
  c2->Print("theoryPlot1Scombined.pdf");

  for(int i=0; i<cmsdata->GetN(); i++){
    cmsdata->GetX()[i+1] = genPtLargeBinsGraph->GetX()[i];
    cmsdata->GetEXhigh()[i+1] = 0;//genPtLargeBins->GetEXhigh()[i];
    cmsdata->GetEXlow()[i+1] = 0;//genPtLargeBins->GetEXlow()[i];
  }
  frame->Draw();
  hist1->Draw("same HIST c");
  cmsdata->Draw("same P");
  leg = new TLegend(0.4,0.75,0.9,0.9);
  leg->AddEntry(cmsdata, "CMS data", "PML");
  leg->AddEntry(hist1,"PYTHIA (normalized)", "L");
  leg->Draw();
  //latex.DrawLatex(21,0.08,"|y^{#Upsilon}| < 2");
  latex2.DrawLatex(2,0.0015,"#Upsilon(1S)");
  latex3.DrawLatex(2,0.0004 , "#sqrt{s} = 7 TeV, L = 39 pb^{ -1}");
  c2->Print("theoryPlot1Sxpos.gif");
  //c2->Print("theoryPlot1Sxpos.eps");
  c2->Print("theoryPlot1Sxpos.pdf");
*/
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
