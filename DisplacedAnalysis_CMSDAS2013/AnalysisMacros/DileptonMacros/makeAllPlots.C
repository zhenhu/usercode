#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <string>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TGraphAsymmErrors.h>
#include <TFile.h>
#include <TStyle.h>
#include <TH1.h>
#include <TKey.h>
#include <TROOT.h>
#include <THStack.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TLatex.h>

#include "AnalysisMacros/CommonMacros/analysisType.C"

// Signal histos
TString signal1("WeightedFiles/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_analysis_20121212_weighted_");

TString signal2("WeightedFiles/HTo2LongLivedTo4F_MH400_MFF50_CTau8To800_analysis_20121212_weighted_");

TString signal3("WeightedFiles/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_analysis_20121212_weighted_");

TString getTypeName(analysisType ana)
{
  TString type("");

  if ( ana==_2eTrack) type = "2eTrack";
  else if ( ana==_2muTrack ) type = "2muTrack";
  else if ( ana==_2globalMu ) type = "2globalMu";
  else if ( ana==_2trackerMu ) type = "2trackerMu";
  else if ( ana==_2saMu ) type = "2saMu";

  return type;
}

float getLumi(const bool electrons)
{
  TString lumiFile = "";
  if( electrons ) lumiFile = "../LumiFiles/lumi_electron.txt";
  else lumiFile = "../LumiFiles/lumi_muon.txt";

  // Read file to get lumi (in /pb)
  ifstream openFile;
  openFile.open(lumiFile.Data());
  // Only one line in file...
  string lumiString = "0";
  if (openFile.is_open()) {
    getline(openFile, lumiString);
    openFile.close();
  }
  return ::atof(lumiString.c_str());
}

// Add a histogram to top of a stack
double addHistogram(const TString & fileName, const TString & histoName, const int color, THStack & hs,
    const TString & leg, TLegend *legend, const float lumi, int minIntegral=1, int maxIntegral=-1 )
{
  TFile * inputFile= new TFile (fileName, "READ");
  TH1F * histo = (TH1F*)inputFile->Get(histoName);
  TH1::SetDefaultSumw2();
  histo->Scale(lumi);

  histo->SetFillColor(color);
  hs.Add(histo);

  legend->AddEntry(histo, leg, "f");

  if ( maxIntegral==-1 ) maxIntegral=histo->GetNbinsX();

  return histo->Integral( minIntegral, maxIntegral );
}

double addBackgroundHistos( TString anaType, const TString & histoName, THStack &stack, TLegend *legend, const float lumi, int minIntegral=1, int maxIntegral=-1 ) {
  double totalBkgMCIntegral=0;

  // addHistogram
  ////
  //// returns integral of histogram
  ////
  //// TString : file name of sample
  //// TString : name of histo in file
  //// int : colour for this sample
  //// THStack : The stack to add this sample to
  //// TString : Label to appear in legend for this sample
  //// TLegend : The legend for the stack
  //// float : lumi to normalise to

  totalBkgMCIntegral += addHistogram("CombinedFiles/ZZ_combined_"+anaType+".root", histoName, 8, stack,"ZZ", legend, lumi, minIntegral, maxIntegral );
  totalBkgMCIntegral += addHistogram("CombinedFiles/WZ_combined_"+anaType+".root", histoName, 7, stack,"WZ", legend, lumi, minIntegral, maxIntegral );
  totalBkgMCIntegral += addHistogram("CombinedFiles/WW_combined_"+anaType+".root", histoName, 6, stack,"WW", legend, lumi, minIntegral, maxIntegral );
  totalBkgMCIntegral += addHistogram("CombinedFiles/TTJets_combined_"+anaType+".root", histoName, 3, stack,"TTJets", legend, lumi, minIntegral, maxIntegral );
  totalBkgMCIntegral += addHistogram("CombinedFiles/DYJets_combined_"+anaType+".root", histoName, 2, stack,"DYJets", legend, lumi, minIntegral, maxIntegral );
  totalBkgMCIntegral += addHistogram("CombinedFiles/WJets_combined_"+anaType+".root", histoName, 5, stack,"WJets", legend, lumi, minIntegral, maxIntegral );
  totalBkgMCIntegral += addHistogram("CombinedFiles/QCD_combined_"+anaType+".root", histoName, 4, stack,"QCD", legend, lumi, minIntegral, maxIntegral );

  return totalBkgMCIntegral;
}

// Should template this?
template <class T>
void setPlotTitle( T & hist, const float lumi ) {

    // Make title for plot
    TString stackTitle("");
    if ( lumi < 0) stackTitle = "CMS Simulation #sqrt{s} = 8 TeV";
    else {
      stackTitle = "CMS Preliminary #sqrt{s} = 8 TeV, L = ";
      char s[32];
      sprintf(s, "%.1f",lumi/1000);
      stackTitle += s;
      stackTitle +="fb^{-1}";
    }
    // Set title
    hist.SetTitle(stackTitle);
}

//void addChannelLatex( TCanvas & can, TString anaType ) {
//  // Add latex saying which channel this plot is for
//  TString latexText = "#mu^{+}#mu^{-}";
//  if (anaType=="2eTrack") {
//    latexText = "e^{+}e^{-}";
//  }
//
//  TLatex *l1 = new TLatex(20, 20, latexText);
//  l1->Draw();
//}

//template <class T>
TH1F drawMCDataRatio( TH1 * mcHist, TH1 * dataHist) {

  // Axis limits
  double nBinsX = mcHist->GetNbinsX();
  double minX = mcHist->GetBinLowEdge(1);
  double maxX = mcHist->GetBinLowEdge( nBinsX ) + mcHist->GetBinWidth( nBinsX );


  // Define new TH1F for ratio plot
  TH1F ratioHist("MCDataRatio","MCDataRatio", nBinsX, minX, maxX );

  gStyle->SetOptStat(0);
  ratioHist.SetMaximum(2);
  ratioHist.SetMinimum(0);

  // Loop over bins and fill ratio hist
  for ( int bin=0; bin <= nBinsX+1; bin++ ) {

    if ( dataHist->GetBinContent( bin ) == 0 ) {
      ratioHist.SetBinContent( bin, 0 );
      continue;
    }
    double ratio = mcHist->GetBinContent( bin ) / dataHist->GetBinContent( bin );

    ratioHist.SetBinContent( bin, ratio );
  }

  return ratioHist;

}


// Make plots where only signal MC appear
// e.g. isolation plots
void makeSignalPlots(const TString & histoName, TFile * outputFile, TString anaType,
    const TString & xTitle,  const double & xMin, const double & xMax,
    const double & yMin = 0., const double & yMax = 0.,
    bool logY=false)
{
  std::cout << "--->Making Signal only plots" << std::endl;
  TH1::SetDefaultSumw2();

  //
  // SIGNAL MC
  //

  // Not good at the moment - just taking one or two examples to plot and hard coded the names of the files here
  TFile * signalInputFile1= new TFile (signal1+anaType+".root", "READ");
  TH1F * histoSignal1 = (TH1F*)signalInputFile1->Get(histoName);
  histoSignal1->SetStats(0);

  TFile * signalInputFile2= new TFile (signal2+anaType+".root", "READ");
  TH1F * histoSignal2 = (TH1F*)signalInputFile2->Get(histoName);
  histoSignal2->SetStats(0);

  // Output histograms to file
  outputFile->cd();

  // Setup canvas
  TCanvas canvas(histoName+"_signal");
  canvas.cd();
  if ( logY ) gPad->SetLogy();
  canvas.Draw();
  canvas.SetFillColor(kWhite);
  canvas.SetBorderMode(0);

  // Draw signal MC
  histoSignal1->SetLineColor(4);
  histoSignal1->Scale(1/histoSignal1->Integral());
  histoSignal1->GetXaxis()->SetTitle(xTitle);
  histoSignal1->GetYaxis()->SetTitle("Entries");
  histoSignal1->GetXaxis()->SetLimits(xMin,xMax);
  histoSignal1->GetYaxis()->SetLimits(yMin,yMax);
  histoSignal1->Draw();

  histoSignal2->SetLineColor(6);
  histoSignal2->Scale(1/histoSignal2->Integral());
  histoSignal2->Draw("SAME");

  // Draw legend
  TLegend *legend= new TLegend(0.5,0.6,0.85,0.85);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->AddEntry(histoSignal1,"m_{H}=1000 GeV/c^{2} m_{X}=350 GeV/c^{2}","l");
  legend->AddEntry(histoSignal2,"m_{H}=400 GeV/c^{2} m_{X}=50 GeV/c^{2}","l");

  legend->Draw();

  canvas.Update();
  canvas.Write();
}

void makeIsoPlots( const TString & histoName, TFile * outputFile, TString anaType,
    const TString & xTitle,  const double & xMin, const double & xMax,
    const TString & yTitle, const double & yMin = 0., const double & yMax = 0., bool logY=false )
{
  std::cout << "--->Making Signal only 2D plots" << std::endl;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);

  //
  // SIGNAL MC
  //

  // Not good at the moment - just taking one or two examples to plot and hard coded the names of the files here
  TFile * signalInputFile1= new TFile (signal1+anaType+".root", "READ");
  TH2F * histoSignal1 = (TH2F*)signalInputFile1->Get(histoName);
  histoSignal1->SetStats(0);

  TFile * signalInputFile2= new TFile (signal2+anaType+".root", "READ");
  TH2F * histoSignal2 = (TH2F*)signalInputFile2->Get(histoName);
  histoSignal2->SetStats(0);

  // Output histograms to file
  outputFile->cd();

  // Take ProfileY of 2D histos
  TProfile * tprof1 = new TProfile( *histoSignal1->ProfileY() );
  TProfile * tprof2 = new TProfile( *histoSignal2->ProfileY() );

  // Setup canvas
  TCanvas canvas(histoName+"_signal");
  canvas.cd();
  if ( logY ) gPad->SetLogy();
  canvas.Draw();
  canvas.SetFillColor(kWhite);
  canvas.SetBorderMode(0);

  // Draw signal MC
  tprof1->SetLineColor(4);
  tprof1->SetMarkerStyle(20);
  tprof1->SetMarkerColor(4);
  tprof1->GetXaxis()->SetTitle(xTitle);
  tprof1->GetYaxis()->SetTitle(yTitle);
  tprof1->GetXaxis()->SetLimits(xMin,xMax);
  tprof1->GetYaxis()->SetLimits(yMin,yMax);
  setPlotTitle(*tprof1, -1);
  tprof1->Draw();

  //  tprof2->SetLineColor(3);
  //  tprof2->GetXaxis()->SetTitle(xTitle);
  //  tprof2->GetYaxis()->SetTitle("Entries");
  //  tprof2->GetXaxis()->SetLimits(xMin,xMax);
  //  tprof2->GetYaxis()->SetLimits(yMin,yMax);
  //  setPlotTitle(*tprof2, -1);
  //  tprof2->Draw("SAME");

  // Draw legend
  TLegend *legend= new TLegend(0.5,0.6,0.85,0.85);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->AddEntry(tprof1,"m_{H}=1000 GeV/c^{2} m_{X}=350 GeV/c^{2}","l");
  //  legend->AddEntry(tprof2,"m_{H}=200 GeV/c^{2} m_{X}=50 GeV/c^{2}","l");

  legend->Draw();

  canvas.Update();
  canvas.Write();

  tprof1->Delete();
  tprof2->Delete();
}

// Find value on x axis where you keep 90% of entries
// If startFromZero==true, 90% from 0->cut value returned
// If startFromZero==false, 90% cut value<-infinity
double find90Cut( const TH1F * hist ) {//, bool startFromZero=true ) {

  // Get total integral
  double totalIntegral = hist->Integral();

  // Loop over bins from first bin (after underflow)
  // Stop before final bin
  double integralSoFar=0;
  for ( int bin=1; bin<hist->GetNbinsX()-1; bin++ ) {
    integralSoFar += hist->GetBinContent( bin );

    if ( integralSoFar/totalIntegral >= 0.9 ) {
      std::cout << "Bin : " << bin << " center : " << hist->GetBinCenter( bin ) << std::endl;
      return hist->GetBinCenter( bin );
    }
  }

  std::cout << "WARNING in find90Cut : cut in final bin/overflow";
  return hist->GetBinCenter( hist->GetNbinsX() );
}

// Called within makePlot when making the pu plot
// Basically adds in the +/- 5% systematic error bars
TGraphAsymmErrors makePUPlot( THStack stack, TString anaType, const float lumi ) {

  // Got the stack, now sum the =/- 5% histograms and make two new stacks
  // Make dummy legend etc.
  THStack p5Stack("Background MC p5","");
  THStack m5Stack("Background MC m5","");
  TLegend *legend= new TLegend(0.1,0.1,0.1,0.1);

  addBackgroundHistos( anaType, "nRecoPV_p5", p5Stack, legend, lumi );
  addBackgroundHistos( anaType, "nRecoPV_m5", m5Stack, legend, lumi );

  // Get last histogram in stacks i.e. sum of all backgrounds
  TH1F * hist = new TH1F( *(TH1F*)(stack.GetStack()->Last()) );
  TH1F * p5Hist = new TH1F( *(TH1F*)p5Stack.GetStack()->Last() );
  TH1F * m5Hist = new TH1F( *(TH1F*)m5Stack.GetStack()->Last() );

  // Create structures to make TGraphAssymErrors
  Int_t n=p5Hist->GetNbinsX();
  Double_t x[n]; // x values
  Double_t y[n]; // y values
  Double_t exl[n]; // low x error
  Double_t eyl[n]; // low y error
  Double_t exh[n]; // high x error
  Double_t eyh[n]; // high y error

  // Loop over histos and get values
  for ( int bin=1; bin < n+1; bin++ ) {
    x[bin-1]=hist->GetBinCenter( bin );
    y[bin-1]=hist->GetBinContent( bin );
    exl[bin-1]=hist->GetBinWidth( bin )/2;
    eyl[bin-1]=p5Hist->GetBinContent( bin )-y[bin-1];
    exh[bin-1]=hist->GetBinWidth( bin )/2;
    eyh[bin-1]=y[bin-1]-m5Hist->GetBinContent( bin );
  }


  // Make TGraphAssymErrors
  TGraphAsymmErrors gr(n,x,y,exl,exh,eyl,eyh);

  return gr;
}


// Make main selection plots
// n-1, control type plots and plots after all cuts
void makePlot(const TString & histoName, TFile * outputFile, TString anaType,
    const TString & xTitle,  const double & xMin, const double & xMax,
    const double & yMin = 0., const double & yMax = 0., bool logY=false,
    const float lumi = 0, const bool plotData=false, bool drawRatioPlot=false )
{
  std::cout << "----> Making plots for : " << histoName.Data() << std::endl;
  std::cout << "Plotting data ? " << plotData << std::endl;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  // Keep track of integrals of background & data
  double totalBkgMCIntegral = 0;
  //  double totalDataIntegral = 0;

  //
  // DATA
  //

  TH1F * histoData=0;

  if (plotData) {

    TFile * inputFile= new TFile ("CombinedFiles/Data_combined_"+anaType+".root", "READ");
    histoData = (TH1F*)inputFile->Get(histoName);
    //    totalDataIntegral = histoData->Integral();

    histoData->SetStats(0);
    histoData->SetMarkerStyle(21);
    histoData->SetMarkerSize(1);
  }

  //
  // SIGNAL MC
  //


  // Not good at the moment - just taking one or two examples to plot and hard coded the names of the files here
  TFile * signalInputFile1= new TFile (signal1+anaType+".root", "READ");
  TH1F * histoSignal1 = (TH1F*)signalInputFile1->Get(histoName);
  histoSignal1->SetStats(0);
  histoSignal1->Scale(lumi);

  TFile * signalInputFile2= new TFile (signal2+anaType+".root", "READ");
  TH1F * histoSignal2 = (TH1F*)signalInputFile2->Get(histoName);
  histoSignal2->SetStats(0);
  histoSignal2->Scale(lumi);

  int minIntegral=0;
  int maxIntegral=histoSignal1->GetNbinsX();

//  if ( histoName=="nMinus1_isolationLeptonH_removedLifetimeCuts" || histoName=="nMinus1_relIsolationLeptonH_removedLifetimeCuts" ) {
//    //    std::cout << find90Cut( histoSignal1 ) << std::endl;
//    //    std::cout << find90Cut( histoSignal2 ) << std::endl;
//
//    minIntegral=histoSignal1->FindBin( find90Cut(histoSignal1) );
//
//    // Check integral below specific cut
//    if ( histoName=="nMinus1_relIsolationLeptonH_removedLifetimeCuts" ) {
//      std::cout << "Signal 1" << std::endl;
//      std::cout << "Efficiency with rel iso cut at 0.1 : " << histoSignal1->Integral( 1, histoSignal1->FindBin(0.1) ) / histoSignal1->Integral() << std::endl;
//      std::cout << "Efficiency with rel iso cut at 0.05 : " << histoSignal1->Integral( 1, histoSignal1->FindBin(0.05) ) / histoSignal1->Integral() << std::endl;
//      std::cout << "Signal 2" << std::endl;
//      std::cout << "Efficiency with rel iso cut at 0.1 : " << histoSignal2->Integral( 1, histoSignal2->FindBin(0.1) ) / histoSignal2->Integral() << std::endl;
//      std::cout << "Efficiency with rel iso cut at 0.05 : " << histoSignal2->Integral( 1, histoSignal2->FindBin(0.05) ) / histoSignal2->Integral() << std::endl;
//    }
//  }

  TFile * signalInputFile3= new TFile (signal3+anaType+".root", "READ");
  TH1F * histoSignal3 = (TH1F*)signalInputFile3->Get(histoName);
  histoSignal3->SetStats(0);
  histoSignal3->Scale(lumi);

  //
  // BACKGROUND MC
  //

  THStack stack("Background MC","");
  setPlotTitle(stack, lumi);

  // Add all different background MC to this stack
  TLegend *legend= new TLegend(0.5,0.6,0.85,0.85);

  totalBkgMCIntegral = addBackgroundHistos(anaType, histoName, stack, legend, lumi, minIntegral, maxIntegral);


//  if ( histoName=="nMinus1_isolationLeptonH_removedLifetimeCuts" || histoName=="nMinus1_relIsolationLeptonH_removedLifetimeCuts" ) {
//    std::cout << "Integral of background between " << minIntegral << " and " << maxIntegral << " : " << totalBkgMCIntegral << std::endl;
//  }

  // Output histograms to file
  outputFile->cd();

  // Setup canvas
  TCanvas canvas(histoName);
  canvas.cd();
  // Draw one or two pads
  TPad * up = new TPad("u","u",0.01,0.25,0.99,0.99);
  up->SetNumber(1);
  up->Draw();
  TPad * dp = new TPad("d","d",0.01,0.01,0.99,0.25);

  if ( drawRatioPlot ) {
    dp->SetNumber(2);
    dp->UseCurrentStyle();
    dp->Draw();
  }
  else {
    up->SetPad(0.01,0.01,0.99,0.99);
    up->Draw();
  }

  if ( logY ) up->SetLogy();
  canvas.Draw();
  canvas.cd(1);
  up->cd();
  canvas.SetFillColor(kWhite);
  canvas.SetBorderMode(0);


  // Draw background MC
  // There may be zero entries, which will mess up drawing options
  // Not a good fix at the moment
  bool axesExist=false;
  if (totalBkgMCIntegral>0) {
    axesExist=true;

    stack.Draw("HISTE");

    stack.GetXaxis()->SetRangeUser(xMin, xMax);
    stack.SetMaximum(yMax);
    stack.SetMinimum(yMin);
    stack.GetXaxis()->SetTitle(xTitle);
    stack.GetYaxis()->SetTitle("Entries");
  }

  std::cout << "Drawing signal histos" << std::endl;
  // Draw signal MC
  histoSignal1->SetLineStyle(2);
  histoSignal1->SetLineColor(kMagenta+2);
  histoSignal1->SetLineWidth(2);
  if(axesExist) histoSignal1->Draw("same,HIST");
  else histoSignal1->Draw("HIST");

  histoSignal2->SetLineStyle(2);
  histoSignal2->SetLineColor(kGreen+2);
  histoSignal2->SetLineWidth(2);
  if(axesExist) histoSignal2->Draw("same,HIST");
  else histoSignal2->Draw("HIST");

  //  histoSignal3->SetLineStyle(2);
  //  histoSignal3->SetLineColor(4);
  //  histoSignal3->SetLineWidth(2);
  //  histoSignal3->Draw("same,HIST");

  // Draw data
  if ( plotData ) {
    if (axesExist) histoData->Draw("same,P,E,X0");
    else histoData->Draw("P,E,X0");
  }

  // Draw legend
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  if ( plotData ) legend->AddEntry(histoData,"data","p");
  legend->AddEntry(histoSignal1,"m_{H}=1000 GeV/c^{2} m_{X}=350 GeV/c^{2}","l");
  legend->AddEntry(histoSignal2,"m_{H}=400 GeV/c^{2} m_{X}=50 GeV/c^{2}","l");
  //  legend->AddEntry(histoSignal3,"m_{squark}=350 GeV/c^{2} m_{#Chi}=148 GeV/c^{2}","l");

  legend->Draw();

  canvas.Update();

  // Draw mc/data ratio
  if ( drawRatioPlot ) {
    dp->cd();
    TH1F ratioHist( drawMCDataRatio( ((TH1*)stack.GetStack()->Last()), histoData ) );

    // Check content of ratioHist
    ratioHist.GetXaxis()->SetRangeUser(xMin, xMax);
    ratioHist.SetMarkerStyle(20);
    ratioHist.GetYaxis()->SetNdivisions(5,0,0);
    ratioHist.GetYaxis()->SetTickLength(0.01);
    dp->SetGridy();
    ratioHist.Draw("P");
    canvas.Update();
    canvas.Write();
  }
  else canvas.Write();

  // Draw systematic errors for reco PV plot
  // FIXME For some reason, old canvas can't handle this!
  if ( histoName=="nRecoPV" ) {
    TGraphAsymmErrors gr( makePUPlot( stack, anaType, lumi ) );

    // Move back to output file (as other files have been opened and closed in makePUPlot
    outputFile->cd();

    gr.SetFillColor(1);
    gr.SetFillStyle(3001);
    gr.Draw("2P0");
    canvas.Update();

    // Test
    TCanvas can("puSystematic");
    can.cd();
//    can.SetLogy();
    can.Draw();
    gr.SetTitle("TGraphAsymmErrors Example");

    stack.Draw("HISTE");
    gr.Draw("2P0");
    histoData->Draw("P,E,X0SAME");
    legend->Draw();

    can.Update();
    can.Write();
  }
}

void makeAllPlots( analysisType ana, bool plotData )
{
  TH1::SetDefaultSumw2();

  bool electrons=false;
  if (ana==_2eTrack) electrons=true;

  TString anaType(getTypeName(ana));

  // Get lumi
  // If not plotting any data, normalise arbitrarily
  float lumi = 5000;
  if ( plotData ) {
    lumi = getLumi(electrons);
    std::cout << "===============================" << std::endl;
    std::cout << "Total lumi in data : " << lumi/1000 << " /fb" << std::endl;
    std::cout << "===============================" << std::endl;
  }
  else std::cout << "Not plotting data, will normalise to lumi of " << lumi/1000 << " /fb" << std::endl;

  TFile * outputFile = new TFile("output_"+anaType+".root", "RECREATE");

  // makePlot function
  // Arguments :
  ////
  //// TString : Name of histogram in root file
  //// TFile : Output file
  //// TString : String version of anaType_
  //// TString : x axis label
  //// double : x axis min
  //// double x axis max
  //// double : y axis min
  //// double : y axis max
  //// bool : log y (true) or not (false)
  //// float : lumi to scale histograms to
  //// bool : Plot data (true) or not (false)

  // Dilepton Inverted lifetime cuts
  makePlot("Mass_removedLifetimeCuts", outputFile, anaType,
      "mass[Gev/c^{2}]", 0, 500, 0.1, 10000000, true,
      lumi, plotData );

  makePlot("nMinus1_isolationLeptonH_removedLifetimeCuts", outputFile, anaType,
      "#Sigma p_{t}", 0, 20, 0.1, 10000000, true,
      lumi, plotData );

  makePlot("nMinus1_relIsolationLeptonH_removedLifetimeCuts", outputFile, anaType,
      "#Sigma p_{t}/p_{t}^{lepton}", 0, 0.2, 1, 5000000, true,
      lumi, plotData );

  makePlot("leptonLPt_removedLifetimeCuts", outputFile, anaType,
      "Lepton L p_{t}", 0, 100, 0.1, 5000000, true,
      lumi, plotData );

  makePlot("leptonHPt_removedLifetimeCuts", outputFile, anaType,
      "Lepton H p_{t}", 0, 100, 0.1, 5000000, true,
      lumi, plotData );

  makePlot("leptonLEta_removedLifetimeCuts", outputFile, anaType,
      "Lepton L #eta", -3, 3, 0.1, 5000000, true,
      lumi, plotData );

  makePlot("leptonHEta_removedLifetimeCuts", outputFile, anaType,
      "Lepton H #eta", -3, 3, 0.1, 5000000, true,
      lumi, plotData );

  makePlot("leptonLCaloMatchDeltaR_removedLifetimeCuts", outputFile, anaType,
      "Lepton L Calo Match #Delta R", 0, 0.1, 0.1, 5000000, true,
      lumi, plotData );

  makePlot("leptonHCaloMatchDeltaR_removedLifetimeCuts", outputFile, anaType,
      "Lepton H Calo Match #Delta R", 0, 0.1, 0.1, 5000000, true,
      lumi, plotData );

  makePlot("LxySig_removedLifetimeCuts", outputFile, anaType,
      "L_{xy}/#sigma_{xy}", -20, 5, 0.1, 1000000, true,
      lumi, plotData, true );

  makePlot("leptonAbsD0Sig_removedLifetimeCuts", outputFile, anaType,
      "Minimum Lepton d0/#sigma_{d}", 0, 3.5, 0.1, 1000000, true,
      lumi, plotData, true );


  ///////////////////////////////
  // No looking at signal region!
  ///////////////////////////////

  // Final cuts
  makePlot("Mass_finalCuts", outputFile, anaType,
      "mass[Gev/c^{2}]", 0, 500, 0.01, 5000, true,
      lumi, false );

  makePlot("Lxy_finalCuts", outputFile, anaType,
      "Candidate L_{xy} [cm]", 0, 50, 0.01, 5000, true,
      lumi, false );

  makePlot("nRecoPV_finalCuts", outputFile, anaType,
      "Number reco PV",0,50,0.1,1000000, true,
      lumi, false);

  // n-1 final cuts

  makePlot("nMinus1_LxySig_finalCuts", outputFile, anaType,
      "Candidate L_{xy}/#sigma_{xy}", 0, 30, 0.01, 5000, true,
      lumi, false );

  makePlot("nMinus1_LxySig_removeDeltaPhi_finalCuts", outputFile, anaType,
      "Candidate L_{xy}/#sigma_{xy}", -30, 0, 0.01, 5000, true,
      lumi, true );

  makePlot("nMinus1_vertexChi2_finalCuts", outputFile, anaType,
      "Candidate Vertex #Chi^2", 0, 20, 0.1, 5000, true,
      lumi, false );

  makePlot("nMinus1_deltaPhi_finalCuts", outputFile, anaType,
      "Candidate #Delta#Phi", 0, 1, 0.1, 5000, true,
      lumi, false );

  makePlot("nMinus1_leptonAbsD0Sig_finalCuts", outputFile, anaType,
      "Minimum Lepton d0/#sigma_{d}", 0, 20, 0.1, 5000, true,
      lumi, false );

  makePlot("nMinus1_leptonCaloMatchDeltaR_finalCuts", outputFile, anaType,
      "Maximum Lepton Calo Match #Delta R", 0, 0.1, 0.1, 5000000, true,
      lumi, false );

  makePlot("nMinus1_leptonCaloMatchDeltaEta_finalCuts", outputFile, anaType,
      "Maximum Lepton Calo Match #Delta #eta", 0, 0.1, 0.1, 5000000, true,
      lumi, false );

  makePlot("nMinus1_leptonCaloMatchDeltaPhi_finalCuts", outputFile, anaType,
      "Maximum Lepton Calo Match #Delta #phi", 0, 0.1, 0.1, 5000000, true,
      lumi, false );

  makePlot("nMinus1_leptonTrackPt_finalCuts", outputFile, anaType,
      "Minimum Lepton Track p_{t}", 0, 150, 0.1, 5000000, true,
      lumi, false );

  // Event histograms
  makePlot("nRecoPV", outputFile, anaType,
      "Number reco PV",0,50,0,320000, false,
      lumi, true);


  //  // Signal only plots
  //  makeSignalPlots("nMinus1_isolationLeptonH_finalCuts_genMatched",outputFile, anaType,
  //                  "#Sigma p_{t}", 0, 20, 0.1, 10000000, true);
  //
  //  makeSignalPlots("nMinus1_relIsolationLeptonH_finalCuts_genMatched",outputFile, anaType,
  //                    "#Sigma p_{t}/p_{t}^{lepton}", 0, 0.2, 0.1, 10000000, true);

  // Make 2D plots of isolation vs pileup
  makeIsoPlots("nMinus1_isolationLeptonL_vsPU_finalCuts_genMatched", outputFile, anaType,
      "# reco PV", 0, 50, "#Sigma p_{t} [GeV]", 0, 10, false );

  makeIsoPlots("nMinus1_isolationLeptonH_vsPU_finalCuts_genMatched", outputFile, anaType,
      "# reco PV", 0, 50, "#Sigma p_{t} [GeV]", 0, 10, false );

  makeIsoPlots("nMinus1_relIsolationLeptonL_vsPU_finalCuts_genMatched", outputFile, anaType,
      "# reco PV", 0, 50, "#Sigma p_{t}/p^{lepton L}_{t}", 0, 10, false );

  makeIsoPlots("nMinus1_relIsolationLeptonH_vsPU_finalCuts_genMatched", outputFile, anaType,
      "# reco PV", 0, 50, "#Sigma p_{t}/p^{lepton H}_{t}", 0, 10, false );

  outputFile->Write();
  outputFile->Close();
}

