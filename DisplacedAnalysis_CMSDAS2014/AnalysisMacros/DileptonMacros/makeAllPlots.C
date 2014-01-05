#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TGraphAsymmErrors.h>
#include <TFile.h>
#include <TStyle.h>
#include <TH1.h>
#include <TLine.h>
#include <TPDF.h>
#include <TKey.h>
#include <TROOT.h>
#include <THStack.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TFrame.h>
#include <TLatex.h>
#include <TGraphErrors.h>

#include "AnalysisMacros/CommonMacros/analysisType.h"

// Options (bad global varibales...)
bool unblind = false;
bool rereco = true;
bool correctedData = false;

bool debug = false;

// Signal histos
TString signal1("CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_combined_");
TString signal1Legend("m_{H}=1 TeV} m_{X}=350 GeV");
TString signal1Legend_part1("m_{H}=1000 GeV");
TString signal1Legend_part2("m_{X}=350 GeV");
//TString signal1Legend("Signal 1");

//TString signal1("CombinedFiles/Chi0ToNuLL_MSquark1000_MChi148_combined_");

TString signal2("CombinedFiles/Chi0ToNuLL_MSquark350_MChi148_combined_");
TString signal2Legend("m_{#tilde{q}}=350 GeV m_{#tilde{#Chi}^{0}_{1}}=140 GeV");
TString signal2Legend_part1("m_{#tilde{q}}=350 GeV");
TString signal2Legend_part2("m_{#tilde{#Chi}^{0}_{1}}=140 GeV");
//TString signal2Legend("Signal 2");

//TString signal2("CombinedFiles/HTo2LongLivedTo4F_MH400_MFF50_CTau8To800_combined_");
//TString signal2("CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF150_CTau10To1000_combined_");

TString signal3("CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_combined_");

// Text for axes titles
TString d0SigmaTitle="d_{0}/#sigma_{d}";
TString vertexChi2="Vertex #Chi^{2}";

TString getTypeName(analysisType ana)
{
  TString type("");

  if ( ana==_2eTrack) type = "2eTrack";
  else if ( ana==_2globalOrTrackerMu ) type = "2globalOrTrackerMu";
  else if ( ana==_2muTrack ) type = "2muTrack";
  else if ( ana==_2globalMu ) type = "2globalMu";
  else if ( ana==_2trackerMu ) type = "2trackerMu";
  else if ( ana==_2saMu ) type = "2saMu";

  return type;
}

float getLumi(const bool electrons)
{
  TString lumiFile = "";
  if ( rereco ) {
    if( electrons ) lumiFile = "../LumiFiles/lumi_electron_22Jan.txt";
    else lumiFile = "../LumiFiles/lumi_muon_22Jan.txt";
  }
  else {
    if( electrons ) lumiFile = "../LumiFiles/lumi_electron.txt";
    else lumiFile = "../LumiFiles/lumi_muon.txt";
  }
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
  totalBkgMCIntegral += addHistogram("CombinedFiles/Tau_combined_"+anaType+".root", histoName+"_tau", 46, stack,"DiTau", legend, lumi, minIntegral, maxIntegral );
  totalBkgMCIntegral += addHistogram("CombinedFiles/DYJets_combined_"+anaType+".root", histoName, 2, stack,"DYJets", legend, lumi, minIntegral, maxIntegral );
  totalBkgMCIntegral += addHistogram("CombinedFiles/WJets_combined_"+anaType+".root", histoName, 5, stack,"WJets", legend, lumi, minIntegral, maxIntegral );
  totalBkgMCIntegral += addHistogram("CombinedFiles/QCDenriched_combined_"+anaType+".root", histoName, 4, stack,"QCD", legend, lumi, minIntegral, maxIntegral );

  return totalBkgMCIntegral;
}

void setCanvasTitle( const float lumi ) {

  // Make title for plot
  TString title("");
  if ( lumi < 0) title = "#scale[0.8]{CMS Simulation #sqrt{s} = 8 TeV";
  else {
    title = "#scale[0.8]{CMS Preliminary #sqrt{s} = 8 TeV, L = ";
    char s[32];
    sprintf(s, "%.1f",lumi/1000);
    title += s;
    title +="fb^{-1}}";
  }

  // Set title
  TLatex T1;
  T1.SetNDC();
  T1.DrawLatex(0.2,0.96,title);
}

void addChannelLatex( TString anaType ) {
  // Add latex saying which channel this plot is for
  TString latexText = "#mu^{+}#mu^{-}";
  if (anaType=="2eTrack") {
    latexText = "e^{+}e^{-}";
  }

  TLatex T1;
  T1.SetNDC();
  T1.DrawLatex(0.22,0.87,latexText);
}

//template <class T>
TGraphErrors drawMCDataRatio( TH1 * mcHist, TH1 * dataHist, double xMax=99999) {

  // Axis limits
  double nBinsX = mcHist->GetNbinsX();
  //  double minX = mcHist->GetBinLowEdge(1);
  //  double maxX = mcHist->GetBinLowEdge( nBinsX ) + mcHist->GetBinWidth( nBinsX );


  // Define new TH1F for ratio plot
  //  TH1F ratioHist("MCDataRatio","MCDataRatio", nBinsX, minX, maxX );

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  std::vector<Double_t> binCenters;
  std::vector<Double_t> ratio;
  std::vector<Double_t> xError;
  std::vector<Double_t> yError;

  for ( int bin=1; bin <= nBinsX+1; bin++ ) {
    int originalBin=bin;
    int finalBin=bin;
    double dataBinEntries = dataHist->GetBinContent(bin);
    double mcBinEntries = mcHist->GetBinContent(bin);
    double totalDataError2 = dataHist->GetBinError( bin ) * dataHist->GetBinError( bin );
    double totalMCError2 = mcHist->GetBinError( bin ) * mcHist->GetBinError( bin );

    // Get at least 10 (weighted) entries in data - should hope this is roughly true in MC as well
    //    while ( dataBinEntries < 100 && bin < nBinsX+1 && dataHist->GetBinLowEdge(bin) < xMax ) {
    double yErrorSoFar = 1;
    while ( yErrorSoFar >0.2 && bin < nBinsX+1 && dataHist->GetBinLowEdge(bin) < xMax ) {
      bin++;
      finalBin=bin;
      if ( bin > nBinsX || dataHist->GetBinLowEdge(bin) > xMax ) break;
      dataBinEntries += dataHist->GetBinContent(bin);
      mcBinEntries += mcHist->GetBinContent(bin);

      totalDataError2 += dataHist->GetBinError( bin ) * dataHist->GetBinError( bin );
      totalMCError2 += mcHist->GetBinError( bin ) * mcHist->GetBinError( bin );

      yErrorSoFar = max ( sqrt( totalDataError2 )/dataBinEntries, sqrt( totalMCError2 )/mcBinEntries);
    }

    double binWidth = fabs(dataHist->GetBinLowEdge(originalBin) - dataHist->GetBinLowEdge(finalBin)-dataHist->GetBinWidth(finalBin))/2;
    binCenters.push_back( dataHist->GetBinLowEdge(originalBin)+binWidth);
    if ( mcBinEntries == 0 || dataBinEntries == 0 ) ratio.push_back( -1 );
    else ratio.push_back( mcBinEntries/dataBinEntries );
    xError.push_back(binWidth);
    yError.push_back( sqrt( totalDataError2 / ( dataBinEntries * dataBinEntries ) + totalMCError2 / ( mcBinEntries * mcBinEntries ) ) * mcBinEntries/dataBinEntries );
  }

  unsigned int nBins=binCenters.size();
  double xBins[nBins];
  double yValues[nBins];
  double xErrors[nBins];
  double yErrors[nBins];

  double maxRatio=1;
  double minRatio=1;

  for ( unsigned int bin=0;bin<nBins;bin++) {
    xBins[bin]=binCenters[bin];
    yValues[bin]=ratio[bin];
    if (ratio[bin]>maxRatio && ratio[bin]>3) maxRatio=ratio[bin];
    if (ratio[bin]<minRatio && ratio[bin]<0.3) minRatio=ratio[bin];
    xErrors[bin]=xError[bin];
    yErrors[bin]=yError[bin];
  }

  //  double rangeFromOne = ( fabs(1-maxRatio*1.2) > fabs(1-minRatio*0.8) ) ? fabs(1-maxRatio*1.2) : fabs(1-minRatio*0.8);
  TGraphErrors ratioGraph(nBins,xBins,yValues,xErrors,yErrors);
  //  ratioGraph.SetMaximum(1+rangeFromOne);
  //  ratioGraph.SetMinimum(1-rangeFromOne);
  ratioGraph.SetMaximum(2);
  ratioGraph.SetMinimum(0);
  ratioGraph.SetMarkerSize(0.8);
  ratioGraph.GetYaxis()->SetTitle("MC/Data");
  ratioGraph.GetYaxis()->SetTitleOffset(0.5);
  ratioGraph.GetYaxis()->SetTitleSize(0.1);
  ratioGraph.GetYaxis()->SetLabelSize(0.09);
  ratioGraph.GetXaxis()->SetLabelSize(0.09);

  return ratioGraph;

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

  //  histoSignal2->SetLineColor(6);
  //  histoSignal2->Scale(1/histoSignal2->Integral());
  //  histoSignal2->Draw("SAME");

  // Draw legend
  TLegend *legend= new TLegend(0.5,0.6,0.85,0.85);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->AddEntry(histoSignal1,signal1Legend,"l");
  legend->AddEntry(histoSignal2,signal2Legend,"l");

  legend->Draw();

  canvas.Update();
  canvas.Write();
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

  std::cout << "WARNING in find90Cut : cut in final bin/overflow" << endl;
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

  addBackgroundHistos( anaType, "nRecoPV_p5_removedLifetimeCollCuts", p5Stack, legend, lumi );
  addBackgroundHistos( anaType, "nRecoPV_m5_removedLifetimeCollCuts", m5Stack, legend, lumi );

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
    const float & legMinX, const float & legMinY, const float & legMaxX, const float & legMaxY,
    const TString & xTitle,  const double & xMin, const double & xMax,
    const double & yMin = 0., const double & yMax = 0., bool logY=false,
    const bool & plotCutValue=false, const double & cutValue=-9999,
    const float lumi = 0, const bool plotData=false, TString pdfOutputFile = "", bool drawRatioPlot=false
)
{
  std::cout << "----> Making plots for : " << histoName.Data() << std::endl;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  // Keep track of integrals of background & data
  double totalBkgMCIntegral = 0;


  //
  // SIGNAL MC
  //
  if ( debug ) cout << "Signal" << endl;
  TFile * signalInputFile1= new TFile (signal1+anaType+".root", "READ");
  TH1F * histoSignal1 = (TH1F*)signalInputFile1->Get(histoName);
  histoSignal1->SetStats(0);
  histoSignal1->Scale(lumi);

  // For signal MC, need to add extra weight
  // Have not divided by number of events
  // Get this from cut flow histogram
  TH1F * cutFlowSignal1 = (TH1F*)signalInputFile1->Get("cutFlowColl_preselection");
  double nInitialEventsSignal1 = cutFlowSignal1->GetBinContent(0);
  histoSignal1->Scale(1/nInitialEventsSignal1);

  if ( debug ) cout << "Signal2" << endl;
  TFile * signalInputFile2= new TFile (signal2+anaType+".root", "READ");
  TH1F * histoSignal2 = (TH1F*)signalInputFile2->Get(histoName);
  histoSignal2->SetStats(0);
  histoSignal2->Scale(lumi);
  TH1F * cutFlowSignal2 = (TH1F*)signalInputFile2->Get("cutFlowColl_preselection");
  double nInitialEventsSignal2 = cutFlowSignal2->GetBinContent(0);
  histoSignal2->Scale(1/nInitialEventsSignal2);


  int minIntegral=1;
  int maxIntegral=histoSignal1->GetNbinsX();

  //
  // DATA
  //
  if ( debug ) cout << "Data" << endl;
  TH1F * histoData=0;
  if (plotData) {

    TFile * inputFile = 0;
    if ( rereco ) {
      if ( correctedData ) {
        inputFile= new TFile ("CombinedFiles/Data22Jan_tipLipCorrected_combined_"+anaType+".root", "READ");
      }
      else {
        inputFile= new TFile ("CombinedFiles/Data22Jan_combined_"+anaType+".root", "READ");
      }
    }
    else {
      inputFile= new TFile ("CombinedFiles/Data_combined_"+anaType+".root", "READ");
    }

    TString tempName = histoName;
    if ( histoName == "minLeptonD0Sig_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_forFittingData_removedLifetimeCuts";
    else if ( histoName == "minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts" )  {
      tempName = "minLeptonAbsD0Sig_bestCand_deltaPhiL90_forFittingData_removedLifetimeCollCuts";
    }
    else if ( histoName == "minLeptonD0Sig_d0Corrected_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_d0Corrected_forFittingData_removedLifetimeCuts";
    else if ( histoName == "minLeptonD0Sig_oppSign_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_oppSign_forFittingData_removedLifetimeCuts";
    else if ( histoName == "minLeptonD0Sig_algo4_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_algo4_forFittingData_removedLifetimeCuts";
    else if ( histoName == "minLeptonD0Sig_algo5_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_algo5_forFittingData_removedLifetimeCuts";
    else if ( histoName == "minLeptonD0Sig_algo6_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_algo6_forFittingData_removedLifetimeCuts";
    else if ( histoName == "minLeptonD0Sig_algo7_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_algo7_forFittingData_removedLifetimeCuts";
    else if ( histoName == "minLeptonD0Sig_algo8_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_algo8_forFittingData_removedLifetimeCuts";
    else if ( histoName == "minLeptonD0Sig_algo9_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_algo9_forFittingData_removedLifetimeCuts";
    else if ( histoName == "minLeptonD0Sig_algo10_removedLifetimeCuts" ) tempName = "minLeptonD0Sig_algo10_forFittingData_removedLifetimeCuts";

    if ( correctedData ) tempName = tempName+"_tipLipCorrected";
    histoData = (TH1F*)inputFile->Get(tempName);

    if ( debug ) {
      double totalDataIntegral = histoData->Integral(histoData->FindBin(3),histoData->GetNbinsX());
      cout << "Data integral : " << totalDataIntegral << endl;
      //    totalDataIntegral = histoData->Integral( minIntegral, maxIntegral );
    }
    histoData->SetStats(0);
    histoData->SetMarkerStyle(21);
    histoData->SetMarkerSize(1);

  }

  //
  // BACKGROUND MC
  //
  if ( debug ) cout << "Bkg" << endl;

  THStack stack("Background MC","");

  // Add all different background MC to this stack
  float midX = legMinX + ( legMaxX - legMinX )/2*0.85;
  TLegend *legendBkg= new TLegend(legMinX,legMinY,midX,legMaxY);
  TLegend *legendSignalData= new TLegend(midX,legMinY,legMaxX,legMaxY);
//  legend->SetTextSize(0.025);

  totalBkgMCIntegral = addBackgroundHistos(anaType, histoName, stack, legendBkg, lumi, minIntegral, maxIntegral);
//  totalBkgMCIntegral = addBackgroundHistos(anaType, histoName, stack, legend, lumi, histoData->FindBin(3),histoData->GetNbinsX());

  //  if ( histoName=="nMinus1_vertexChi2_looseCutsA" || histoName=="nMinus1_vertexChi2_looseCutsB" || histoName=="nMinus1_vertexChi2_looseCutsC" || histoName=="nMinus1_vertexChi2_removedLifetimeCuts" ) {
//    cout << "DATA" << endl;
//    std::cout << "Integral of data between " << histoSignal1->GetBinLowEdge(1) << " and " << histoSignal1->GetBinLowEdge(histoSignal1->FindBin( 5 )) << " : " << histoData->Integral(histoSignal1->GetBinLowEdge(1),histoSignal1->FindBin( 5 )) << std::endl;
//    std::cout << "Integral of data between " << histoSignal1->GetBinLowEdge(1) << " and " << histoSignal1->GetBinLowEdge(histoSignal1->FindBin( 8 )) << " : " << histoData->Integral(histoSignal1->GetBinLowEdge(1),histoSignal1->FindBin( 8 )) << std::endl;
//    std::cout << "Integral of data between " << histoSignal1->GetBinLowEdge(1) << " and " << histoSignal1->GetBinLowEdge(histoSignal1->FindBin( 10 )) << " : " << histoData->Integral(histoSignal1->GetBinLowEdge(1),histoSignal1->FindBin( 10 )) << std::endl;
//
//    std::cout << "Integral of background between " << histoSignal1->GetBinLowEdge(minIntegral) << " and " << histoSignal1->GetBinLowEdge(maxIntegral) << " : " << totalBkgMCIntegral << std::endl;
//    if ( histoName=="nMinus1_vertexChi2_removedLifetimeCuts" ) {
//      cout << "Signal 1" << endl;
//      std::cout << "Efficiency of signal for cut between " << histoSignal1->GetBinLowEdge(minIntegral) << " and " << histoSignal1->GetBinLowEdge(histoSignal1->FindBin( 5 )) << " : " << histoSignal1->Integral( minIntegral, histoSignal1->FindBin( 5 ) ) / histoSignal1->Integral(minIntegral,histoSignal1->GetNbinsX() ) * 100 << std::endl;
//      std::cout << "Efficiency of signal for cut between " << histoSignal1->GetBinLowEdge(minIntegral) << " and " << histoSignal1->GetBinLowEdge(histoSignal1->FindBin( 8 )) << " : " << histoSignal1->Integral( minIntegral, histoSignal1->FindBin( 8 ) ) / histoSignal1->Integral(minIntegral,histoSignal1->GetNbinsX() ) * 100 << std::endl;
//      std::cout << "Efficiency of signal for cut between " << histoSignal1->GetBinLowEdge(minIntegral) << " and " << histoSignal1->GetBinLowEdge(histoSignal1->FindBin( 10 )) << " : " << histoSignal1->Integral( minIntegral, histoSignal1->FindBin( 10 ) ) / histoSignal1->Integral(minIntegral,histoSignal1->GetNbinsX() ) * 100 << std::endl;
//      cout << "Signal 2" << endl;
//      std::cout << "Efficiency of signal for cut between " << histoSignal2->GetBinLowEdge(minIntegral) << " and " << histoSignal2->GetBinLowEdge(histoSignal2->FindBin( 5 )) << " : " << histoSignal2->Integral( minIntegral, histoSignal2->FindBin( 5 ) ) / histoSignal2->Integral(minIntegral,histoSignal2->GetNbinsX() ) * 100 << std::endl;
//      std::cout << "Efficiency of signal for cut between " << histoSignal2->GetBinLowEdge(minIntegral) << " and " << histoSignal2->GetBinLowEdge(histoSignal2->FindBin( 8 )) << " : " << histoSignal2->Integral( minIntegral, histoSignal2->FindBin( 8 ) ) / histoSignal2->Integral(minIntegral,histoSignal2->GetNbinsX() ) * 100 << std::endl;
//      std::cout << "Efficiency of signal for cut between " << histoSignal2->GetBinLowEdge(minIntegral) << " and " << histoSignal2->GetBinLowEdge(histoSignal2->FindBin( 10 )) << " : " << histoSignal2->Integral( minIntegral, histoSignal2->FindBin( 10 ) ) / histoSignal2->Integral(minIntegral,histoSignal2->GetNbinsX() ) * 100 << std::endl;
//    }
//  }

  // Begin output of histograms to file
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
//  axesExist=true;  // FIXME - no time to check...if something looks weird with drawing options, come here first

  if ( debug ) std::cout << "Drawing background stack" << std::endl;

  stack.Draw("HISTE");
  stack.GetXaxis()->SetRangeUser(xMin, xMax);
  stack.SetMaximum(yMax);
  stack.SetMinimum(yMin);
  stack.GetXaxis()->SetTitle(xTitle);
  stack.GetYaxis()->SetTitle("Entries");
  axesExist=true;

  // Draw signal MC
  if ( debug ) std::cout << "Drawing signal histos" << std::endl;

  histoSignal1->SetLineStyle(2);
  histoSignal1->SetLineColor(kMagenta+2);
  histoSignal1->SetLineWidth(2);
  if(axesExist) histoSignal1->Draw("same,HIST");
  else {
    axesExist=true;
    histoSignal1->GetXaxis()->SetRangeUser(xMin, xMax);
    histoSignal1->SetMaximum(yMax);
    histoSignal1->SetMinimum(yMin);
    histoSignal1->GetXaxis()->SetTitle(xTitle);
    histoSignal1->GetYaxis()->SetTitle("Entries");
    histoSignal1->Draw("HIST");
  }

  histoSignal2->SetLineStyle(8);
  histoSignal2->SetLineColor(kGreen+2);
  histoSignal2->SetLineWidth(2);
  if(axesExist) histoSignal2->Draw("same,HIST");
  else {
    axesExist=true;
    histoSignal2->GetXaxis()->SetRangeUser(xMin, xMax);
    histoSignal2->SetMaximum(yMax);
    histoSignal2->SetMinimum(yMin);
    histoSignal2->Draw("HIST");
  }

  // Draw data
  if ( plotData ) {
    if (axesExist) histoData->Draw("same,P,E,X0");
    else {
      if ( debug ) std::cout << "Drawing data histo" << std::endl;
      axesExist=true;
      histoData->Draw("P,E,X0");
    }
  }

  // Draw legend
  if ( debug ) std::cout << "Drawing legend" << std::endl;
  legendBkg->SetBorderSize(0);
  legendBkg->SetFillStyle(0);
  legendSignalData->SetBorderSize(0);
  legendSignalData->SetFillStyle(0);
  if ( plotData ) legendSignalData->AddEntry(histoData,"Data","p");
  legendSignalData->AddEntry(histoSignal1,signal1Legend_part1,"l");
  legendSignalData->AddEntry((TObject*)0,signal1Legend_part2,"");
  legendSignalData->AddEntry(histoSignal2,signal2Legend_part1,"l");
  legendSignalData->AddEntry((TObject*)0,signal2Legend_part2,"");

  legendBkg->Draw();
  legendSignalData->Draw();

  // Add line at cut value if requested
  TLine cutLine;
  if ( plotCutValue ) {
    up->Update();
    if ( debug ) cout << canvas.GetUymax() << endl;
    cutLine = TLine(cutValue,yMin,cutValue,yMax);
    cutLine.SetLineWidth(3);
    cutLine.SetLineColor(28);
    cutLine.SetLineStyle(7);
  }
  cutLine.Draw("SAME");

  if ( debug ) std::cout << "Adding decoration" << std::endl;

  // Add channel latex
  addChannelLatex( anaType );

  // Add CMS title
  setCanvasTitle( lumi );

  canvas.Update();

  // Draw systematic errors for reco PV plot
  // FIXME For some reason, old canvas can't handle this!
  if ( histoName=="nRecoPV_removedLifetimeCollCuts" && totalBkgMCIntegral>0 ) {

    TGraphAsymmErrors gr( makePUPlot( stack, anaType, lumi ) );

    // Move back to output file (as other files have been opened and closed in makePUPlot)
    outputFile->cd();
    //    up->cd();

    gr.SetFillColor(1);
    gr.SetFillStyle(3001);
    gr.SetMarkerSize(0);
    gr.Draw("2P0");

    // Test
    TCanvas can("puSystematic");
    can.cd();
    can.SetLogy();
    can.Draw();
    gr.SetTitle("TGraphAsymmErrors Example");

    stack.Draw("HISTE");
    gr.Draw("2P0");
    histoData->Draw("P,E,X0SAME");
    legendBkg->Draw();

    addChannelLatex( anaType );

    can.Update();
    can.Print("output/pdfOutput/"+histoName+"_withSyst_"+anaType+".pdf");
  }

  // Draw mc/data ratio
  TGraphErrors ratioHist;
  if ( drawRatioPlot && totalBkgMCIntegral>0 ) {
    dp->cd();
    ratioHist = drawMCDataRatio( ((TH1*)stack.GetStack()->Last()), histoData, xMax );
    // Check content of ratioHist
    ratioHist.SetMarkerStyle(20);
    ratioHist.GetYaxis()->SetNdivisions(5,0,0);
    ratioHist.GetYaxis()->SetTickLength(0.01);
    dp->SetGridy();
    //    ratioHist.SetNameTitle("","");
    ratioHist.Draw("AP");
    //    ratioHist.GetXaxis()->SetRangeUser( stack.GetXaxis()->GetBinLowEdge(1), stack.GetXaxis()->GetBinUpEdge(stack.GetXaxis()->GetNbins()));
    ratioHist.GetXaxis()->SetRangeUser( xMin, xMax);

    canvas.Update();
    canvas.Write();
  }
  else canvas.Write();

  // Save some histos as root files
  if ( histoName=="minLeptonD0Sig_removedLifetimeCuts" || histoName=="Mass_removedLifetimeCuts" || histoName=="Mass_looseCuts" ||
      histoName=="minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCollCuts" || histoName == "minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCollCuts" ||
      histoName=="minLeptonAbsD0Sig_deltaPhiPlus_removedLifetimeCollCuts" || histoName == "minLeptonAbsD0Sig_deltaPhiMinus_removedLifetimeCollCuts" ||
//      histoName=="minLeptonD0Sig_oppSign_removedLifetimeCuts" ||
//      histoName=="minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts" || histoName=="minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts" ||
//      histoName=="minLeptonD0Sig_d0Corrected_removedLifetimeCuts" ||
      histoName=="minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts" || histoName=="minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts" ||
      histoName=="minLeptonAbsD0Sig_bestCand_deltaPhiMinus_removedLifetimeCollCuts" || histoName=="minLeptonAbsD0Sig_bestCand_deltaPhiPlus_removedLifetimeCollCuts"
          ) {
    if ( debug ) std::cout << "Saving " << histoName.Data() << " as a root file" << std::endl;

    TFile * outputTFile = 0;
    if ( rereco ) {
      if ( correctedData ) {
        outputTFile = new TFile("BackgroundStudiesFiles/"+histoName+"_"+anaType+"_rereco_tiplipCorrected.root","RECREATE");
      }
      else {
        outputTFile = new TFile("BackgroundStudiesFiles/"+histoName+"_"+anaType+"_rereco.root","RECREATE");
      }
    }
    else {
      outputTFile = new TFile("BackgroundStudiesFiles/"+histoName+"_"+anaType+"_promptReco.root","RECREATE");
    }
    if ( totalBkgMCIntegral>0 ) {
      canvas.Write();
      ((TH1*)stack.GetStack()->Last())->Write("Background MC");
    }

    if ( histoData != 0 ) histoData->Write("Data");
    outputTFile->Close();
    delete outputTFile;
  }

  // Save some plots in pdf files
  if ( pdfOutputFile!="" ) {
    canvas.Update();
    TString title("Title:"+histoName);
    canvas.Print(pdfOutputFile,title);
  }

  // Save all as individual pdfs
  canvas.Update();
  if ( debug ) cout << "Saving in " << "output/pdfOutput/"<<histoName<<".pdf" << endl;
  canvas.Print("output/pdfOutput/"+histoName+"_"+anaType+".pdf");
}

// Draw plots which are common between a few set of cuts e.g. for loose selection
void makeCommonPlots( TString anaType, TFile * outputFile, TString pdfOutputFile, double lumi, bool plotData, bool makeRatioPlot, TString cuts, bool plotCutValue ) {

  double yMaxFactor = 1;
  if ( cuts == "controlCollCuts" ) yMaxFactor = 1000;

  if ( plotData == false ) makeRatioPlot = false;

    // Final cuts
    makePlot("Mass_"+cuts, outputFile, anaType, 0.6, 0.55, 0.9, 0.92,
        "mass[Gev/c^{2}]", 0, 500, 0.01, 5000*yMaxFactor, true,
        false, -999,
        lumi, plotData, pdfOutputFile, makeRatioPlot );

    makePlot("Lxy_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.92,
        "Candidate L_{xy} [cm]", 0, 50, 0.01, 5000*yMaxFactor, true,
        false, -999,
        lumi, plotData, pdfOutputFile, makeRatioPlot );

//  makePlot("minLeptonD0Sig_"+cuts, outputFile, anaType, 0.2, 0.6, 0.5, 0.85,
//      "Minimum Signed Lepton d0/#sigma_{d}", -20, 20, 0.01, 5000000, true,
//      false, -999,
//      lumi, plotData, pdfOutputFile );
//
//  makePlot("maxLeptonD0Sig_"+cuts, outputFile, anaType, 0.2, 0.6, 0.5, 0.85,
//      "Maximum Signed Lepton d0/#sigma_{d}", -20, 20, 0.01, 5000000, true,
//      false, -999,
//      lumi, plotData, pdfOutputFile );

  //
  //  // n-1 plots
  //  //    // Electron only plots
  //  if ( anaType == "2eTrack") {
  //    makePlot("PhotonR9_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //        "Min photon R9",0,1.1,0.1,5000000, true,
  //        false, -999,
  //        lumi, plotData, pdfOutputFile);
  //
  //    makePlot("PhotonSigmaIetaIeta_barrel_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //        "Max photon sigma i#eta i#eta barrel",0,0.1,0.1,1200000, true,
  //        false, -999,
  //        lumi, plotData, pdfOutputFile);
  //
  //    makePlot("PhotonSigmaIetaIeta_endcap_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //        "Max photon sigma i#eta i#eta endcap",0,0.1,0.1,30000, false,
  //        false, -999,
  //        lumi, plotData, pdfOutputFile);
  //
  //    makePlot("PhotonHadTowOverEm_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //        "Max photon H/E (tower)",0,0.2,0.1,10000000, true,
  //        false, -999,
  //        lumi, plotData, pdfOutputFile);
  //
  //    makePlot("PhotonHadronicOverEm_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //        "Max photon H/E (cone)",0,0.2,0.1,10000000, true,
  //        false, -999,
  //        lumi, plotData, pdfOutputFile);
  //
  //    makePlot("nMinus1_subleadingSCEt_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //        "Sub-leading SC E_{t}", 0, 150, 0.1, 5000000, true,
  //        false, -999,
  //        lumi, false, pdfOutputFile );
  //
  //    makePlot("nMinus1_leptonCaloMatchDeltaR_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //        "Maximum Lepton Calo Match #Delta R", 0, 0.1, 0.1, 5000000, true,
  //        false, -999,
  //        lumi, false, pdfOutputFile );
  //  }
    // Muon only plots
    if ( anaType == "2muTrack" ) {
      makePlot("nMinus1_cosine_"+cuts, outputFile, anaType, 0.5, 0.57, 0.9, 0.92,
          "cos(#alpha)", -1.2, 1.2, 0.1, 5000*yMaxFactor, true,
          plotCutValue, -0.79,
          lumi, plotData, pdfOutputFile, makeRatioPlot );

      makePlot("nMinus1_deltaR_"+cuts, outputFile, anaType, 0.5, 0.5, 0.85, 0.92,
          "#DeltaR", 0, 0.5, 0.1, 500*yMaxFactor, true,
          plotCutValue, 0.2,
          lumi, plotData, pdfOutputFile, makeRatioPlot );
    }
  //
  //  makePlot("nMinus1_leadingLeptonTrackPt_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //      "Leading Lepton Track p_{t}", 0, 150, 0.1, 5000000, true,
  //      false, -999,
  //      lumi, plotData, pdfOutputFile );
  //
  //  makePlot("nMinus1_subleadingLeptonTrackPt_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //      "Sub-leading Lepton Track p_{t}", 0, 150, 0.1, 5000000, true,
  //      false, -999,
  //      lumi, plotData, pdfOutputFile );
  //
  //  makePlot("nMinus1_oppositeCharge_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
  //      "Sign of charges", -2, 22, 0.001, 5000, true,
  //      false, -999,
  //      lumi, plotData, pdfOutputFile );
  //
//  makePlot("nMinus1_deltaPhi_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "Candidate #Delta#Phi", 0, 4, 0.1, 5000, true,
//      false, -999,
//      lumi, plotData, pdfOutputFile );

    makePlot("nMinus1_nHitsBeforeVertex_"+cuts, outputFile, anaType, 0.52, 0.4, 0.9, 0.92,
        "Number of hits before vertex", 0, 5, 0.1, 5000*yMaxFactor, true,
        plotCutValue, 1.5,
        lumi, plotData, pdfOutputFile, makeRatioPlot );

    makePlot("nMinus1_minMissingHitsAfterVertex_"+cuts, outputFile, anaType, 0.5, 0.5, 0.9, 0.92,
        "Min missing hits after vertex", 0, 20, 0.1, 5000*yMaxFactor, true,
        false, -999,
        lumi, plotData, pdfOutputFile, makeRatioPlot );

    makePlot("nMinus1_maxMissingHitsAfterVertex_"+cuts, outputFile, anaType, 0.7, 0.6, 0.9, 0.92,
        "Max missing hits after vertex", 0, 20, 0.1, 5000*yMaxFactor, true,
        false, -999,
        lumi, plotData, pdfOutputFile, makeRatioPlot );

    makePlot("leptonTrackingAlgo_"+cuts, outputFile, anaType, 0.2, 0.4, 0.4, 0.92,
        "Tracking algo", 0, 11, 0.1, 5000000, true,
        false, -999,
        lumi, plotData, pdfOutputFile, makeRatioPlot );

    if ( anaType == "2muTrack" ) {
      makePlot("nMinus1_vertexChi2_"+cuts, outputFile, anaType, 0.6, 0.5, 0.9, 0.93,
          vertexChi2, 0, 20, 0.1, 5000*yMaxFactor, true,
          plotCutValue, 5,
          lumi, plotData, pdfOutputFile, makeRatioPlot );

      makePlot("nMinus1_nMissingHitsAfterVertex_"+cuts, outputFile, anaType, 0.5, 0.5, 0.9, 0.92,
          "Number of missing hits after vertex", 0, 20, 0.1, 5000*yMaxFactor, true,
          plotCutValue, 4.5,
          lumi, plotData, pdfOutputFile, makeRatioPlot );
    }
    else {
      makePlot("nMinus1_vertexChi2_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.92,
          vertexChi2, 0, 20, 0.1, 5000*yMaxFactor, true,
          plotCutValue, 10,
          lumi, plotData, pdfOutputFile, makeRatioPlot );

      makePlot("nMinus1_nMissingHitsAfterVertex_"+cuts, outputFile, anaType, 0.5, 0.6, 0.9, 0.92,
          "Number of missing hits after vertex", 0, 20, 0.1, 5000*yMaxFactor, true,
          plotCutValue, 3.5,
          lumi, plotData, pdfOutputFile, makeRatioPlot );
    }

    makePlot("nMinus1_relIso_"+cuts, outputFile, anaType, 0.35, 0.6, 0.8, 0.92,
        "#Sigma p_{T}/p_{T}^{lepton}", 0, 0.5, 0.1, 100000*yMaxFactor, true,
        plotCutValue, 0.1,
        lumi, plotData, pdfOutputFile, makeRatioPlot );

    makePlot("nCandsPerEvent_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.92,
        "# reco cands", 0.5, 5.5, 0.1, 500000*yMaxFactor, true,
        false, -999,
        lumi, plotData, pdfOutputFile, makeRatioPlot );

//    makePlot("ptOverE_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "p_{T}/E^{photon}_{T}", 0, 2, 0.1, 10000*yMaxFactor, true,
//        false, -999,
//        lumi, plotData, pdfOutputFile, makeRatioPlot );
//
//    makePlot("ptMinusE_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "|1/E^{photon}_{T}-1/p_{T}|", 0, 2, 0.5, 10000*yMaxFactor, true,
//        false, -999,
//        lumi, plotData, pdfOutputFile, makeRatioPlot );

    //
    //  makePlot("nMinus1_absIso_"+cuts, outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
    //      "#Sigma p_{t} Lepton", 0, 20, 0.1, 10000, true,
    //      false, -999,
  //      lumi, plotData, pdfOutputFile );

}

void makeAllPlots( analysisType ana, bool plotData )
{
  TH1::SetDefaultSumw2();

  bool electrons=false;
  if (ana==_2eTrack) electrons=true;

  TString anaType(getTypeName(ana));
  if ( debug ) std::cout << "Making plots for analysis : " << anaType.Data() << std::endl;

  // Get lumi
  // If not plotting any data, normalise arbitrarily
  float lumi = 20000;
  if ( plotData ) {
    lumi = getLumi(electrons);
    std::cout << "===============================" << std::endl;
    std::cout << "Total lumi in data : " << lumi/1000 << " /fb" << std::endl;
    std::cout << "===============================" << std::endl;
  }
  else std::cout << "Not plotting data, will normalise to lumi of " << lumi/1000 << " /fb" << std::endl;

  TFile * outputFile = 0;
  if ( rereco ) {
    outputFile = new TFile("output/output_"+anaType+"_rereco.root", "RECREATE");
  }
  else {
    outputFile = new TFile("output/output_"+anaType+"_promptReco.root", "RECREATE");
  }

  // PDF output of plots
  // Don't save different versions for prompt/rereco.  Only one set will end up in AN.
  TString pdfOutputFile("output/output_"+anaType+".pdf(");

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


//  // Dilepton Inverted lifetime cuts
//  makePlot("singleLepton_d0", outputFile, anaType, 0.6, 0.55, 0.9, 0.9,
//      "d_{xy}", 0, 500, 0.1, 10000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );
//
//  makePlot("singleLepton_d0sigma", outputFile, anaType, 0.6, 0.55, 0.9, 0.9,
//      "d_{xy} / #sigma_{d}", 0, 500, 0.1, 10000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );
//
//  makePlot("singleLepton_sigma", outputFile, anaType, 0.6, 0.55, 0.9, 0.9,
//      "#sigma_{d}", 0, 500, 0.1, 10000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );


//  makePlot("Mass_removedLifetimeCuts", outputFile, anaType, 0.6, 0.55, 0.9, 0.9,
//      "mass[Gev/c^{2}]", 0, 500, 0.1, 10000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );
//
//  //  makePlot("Mt_removedLifetimeCuts", outputFile, anaType, 0.7, 0.6, 0.95, 0.92,
//  //      "mass[Gev/c^{2}]", 0, 500, 10, 10000000, true,
//  //      false, -999,
//  //      lumi, plotData, pdfOutputFile, true );
//
//  //  makePlot("nMinus1_isolationLeptonH_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "#Sigma p_{t}", 0, 20, 0.1, 10000000, true,
//  //      false, -999,
//  //      lumi, plotData, pdfOutputFile, true );
//  //
//  makePlot("nMinus1_relIsolationLeptonH_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "#Sigma p_{t}/p_{t}^{lepton}", 0, 0.5, 100, 5000000, true,
//      false, -999,
//      lumi, plotData, pdfOutputFile, true );
//  //
//  //  makePlot("leptonLPt_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Lepton L p_{t}", 0, 100, 100, 5000000, true,
//  //      false, -999,
//  //      lumi, plotData, pdfOutputFile );
//  //
//  //  makePlot("leptonHPt_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Lepton H p_{t}", 0, 100, 100, 5000000, true,
//  //      false, -999,
//  //      lumi, plotData, pdfOutputFile );
//  //
//  //  makePlot("leptonLEta_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Lepton L #eta", -3, 3, 10000, 500000, true,
//  //      false, -999,
//  //      lumi, plotData, pdfOutputFile, true );
//  //
//  //  makePlot("leptonHEta_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Lepton H #eta", -3, 3, 10000, 500000, true,
//  //      false, -999,
//  //      lumi, plotData, pdfOutputFile, true );
//  //
//  //  if ( anaType == "2eTrack") {
//  //    makePlot("leptonLCaloMatchDeltaR_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //        "Lepton L Calo Match #Delta R", 0, 0.1, 0.1, 5000000, true,
//  //      false, -999,
//  //        lumi, plotData, pdfOutputFile );
//  //
//  //    makePlot("leptonHCaloMatchDeltaR_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //        "Lepton H Calo Match #Delta R", 0, 0.1, 0.1, 5000000, true,
//  //      false, -999,
//  //        lumi, plotData, pdfOutputFile );
//  //  }
//  //
//  //  makePlot("nMinus1_nHitsBeforeVertex_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Number of hits before vertex", 0, 5, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //  makePlot("nMinus1_nMissingHitsAfterVertex_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Total number of missing hits after vertex", 0, 8, 10, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //  makePlot("nMinus1_maxMissingHitsAfterVertex_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Max number of missing hits after vertex", 0, 8, 10, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //  makePlot("nMinus1_minMissingHitsAfterVertex_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Min number of missing hits after vertex", 0, 8, 10, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  makePlot("nMinus1_vertexChi2_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "Candidate Vertex #Chi^2", 0, 20, 0.1, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );
//
//  //  makePlot("deltaPhi_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //     "#Delta #phi", 0, 4, 0.1, 5000000, true,
//  //    false, -999,
//  //    lumi, false, pdfOutputFile, false );
//
//  //  makePlot("deltaPhi_sameSignD0_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "#Delta #phi", 0, 4, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, false, pdfOutputFile, false );
//
//  //  makePlot("minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Minimum |d0/#sigma_{d}|", 0, 25, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, false, pdfOutputFile, false );
//
//  //  makePlot("minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Minimum |d0/#sigma_{d}|", 0, 25, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, false, pdfOutputFile, false );
//
//  //
//  //  makePlot("nMinus1_vertexChi2_removedLifetimeCuts_vPrompt", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Candidate Vertex #Chi^2 vPrompt", 0, 20, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //
//  //  //  makePlot("leptonSig_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //  //      "Lepton #sigma_{d}", 0, 0.01, 0.01, 100000000, true,
//  //      false, -999,
//  //  //      lumi, true, pdfOutputFile, true );
//  //
//  makePlot("minLeptonD0Sig_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//      "Minimum Signed Lepton d0/#sigma_{d}", -20, 20, 0.1, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );
//
//  makePlot("minLeptonD0Sig_d0Corrected_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, false );
//
//  //  makePlot("minLeptonD0Sig_algo4_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //  makePlot("minLeptonD0Sig_algo5_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //  makePlot("minLeptonD0Sig_algo6_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //  makePlot("minLeptonD0Sig_algo7_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //  makePlot("minLeptonD0Sig_algo8_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //  makePlot("minLeptonD0Sig_algo9_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //  makePlot("minLeptonD0Sig_algo10_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//
//  makePlot("minLeptonD0Sig_oppSign_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );
//
//  //  makePlot("minLeptonD0Sig_controlIsolation_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //    "CONTROL Minimum Signed Lepton d0/#sigma_{d}", -20, 20, 0.1, 5000000, true,
//  //    false, -999,
//  //    lumi, true, pdfOutputFile );
//
//  //makePlot("minLeptonD0Sig_controlTrigger_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //    "CONTROL Minimum Signed Lepton d0/#sigma_{d}", -20, 20, 0.1, 5000000, true,
//  //    false, -999,
//  //    lumi, true, pdfOutputFile );
//
//  //makePlot("minLeptonD0Sig_controlVertex_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//  //    "CONTROL Minimum Signed Lepton d0/#sigma_{d}", -20, 20, 0.1, 5000000, true,
//  //    false, -999,
//  //    lumi, false, pdfOutputFile );
//
//  makePlot("minLeptonD0Sig_PVnorefit_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//      "Minimum Signed Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//      false, -999,
//      lumi, unblind, pdfOutputFile, unblind );
//
//  makePlot("leptonD0_removedLifetimeCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//      "Minimum Signed Lepton d0", -0.05, 0.05, 0.1, 5000000, true,
//      false, -999,
//      lumi, unblind, pdfOutputFile, unblind );
//
//  //
//  //  makePlot("maxLeptonD0Sig_removedLifetimeCuts", outputFile, anaType, 0.75, 0.5, 0.95, 0.9,
//  //      "Maximum Signed Lepton d0/#sigma_{d}", -20, 15, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//  //
//  //  makePlot("minLeptonD0SigBL_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Minimum Lepton d0/#sigma_{d} wrt BS", 0, 10, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, false, pdfOutputFile, false );
//  //
//  //  makePlot("minLeptonD0SigPV_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Minimum Lepton d0/#sigma_{d} wrt PV", 0, 10, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, false, pdfOutputFile, false );
//  //
//  //  makePlot("leptonTrackingAlgo_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //      "Tracking algo", 0, 30, 0.1, 5000000, true,
//  //      false, -999,
//  //      lumi, true, pdfOutputFile, true );
//  //
//
//  //  ///////////////////////////////
//  //  // No looking at signal region!
//  //  ///////////////////////////////
//  //
//  // Final cuts
//  makePlot("Mass_finalCuts", outputFile, anaType, 0.3, 0.62, 0.55, 0.92,
//      "mass[Gev/c^{2}]", 0, 500, 0.01, 5000, true,
//      false, -999,
//      lumi, unblind, pdfOutputFile );
//
//  //
//  //  makePlot("Mt_finalCuts", outputFile, anaType, 0.4, 0.6, 0.8, 0.9,
//  //      "M_{t}[Gev/c^{2}]", 0, 500, 0.01, 5000, true,
//  //      false, -999,
//  //      lumi, unblind, pdfOutputFile );
//  //
//  makePlot("Lxy_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "Candidate L_{xy} [cm]", 0, 50, 0.01, 5000, true,
//      false, -999,
//      lumi, unblind, pdfOutputFile );
//  //
//  //  //  makePlot("maxLeptonD0Sig_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //  //      "Signed Lepton d0/#sigma_{d}", 0, 10, 0.01, 5000, true,
//  //      false, -999,
//  //  //      lumi, unblind, pdfOutputFile );
//  //
//  //  //  makePlot("nRecoPV_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //  //      "Number reco PV",0,50,0.1,1000000, true,
//  //      false, -999,
//  //  //      lumi, unblind, pdfOutputFile);
//  //  //
//  //  //
//  //  //
//  //    // Electron only plots
//  if ( anaType == "2eTrack") {
//    //    makePlot("PhotonR9_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Min photon R9",0,1.1,0.1,5000000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile,true);
//    //
//    makePlot("PhotonSigmaIetaIeta_barrel_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "Max photon sigma i#eta i#eta barrel",0,0.1,0.1,1200000, true,
//        false, -999,
//        lumi, unblind, pdfOutputFile,unblind);
//
//    makePlot("PhotonSigmaIetaIeta_endcap_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "Max photon sigma i#eta i#eta endcap",0,0.1,0.1,30000, false,
//        false, -999,
//        lumi, unblind, pdfOutputFile,unblind);
//    //
//    //    makePlot("PhotonHadTowOverEm_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Max photon H/E (tower)",0,0.2,0.1,10000000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile,true);
//    //
//    //    makePlot("PhotonHadronicOverEm_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Max photon H/E (cone)",0,0.2,0.1,10000000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile,true);
//    //
//    //    makePlot("PhotonR9_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Min photon R9",0,1.1,0.1,1000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile);
//    //
//    makePlot("PhotonSigmaIetaIeta_barrel_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "Max photon sigma i#eta i#eta barrel",0,0.1,0.1,1000, true,
//        false, -999,
//        lumi, unblind, pdfOutputFile);
//
//    makePlot("PhotonSigmaIetaIeta_endcap_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "Max photon sigma i#eta i#eta endcap",0,0.1,0.1,1000, true,
//        false, -999,
//        lumi, unblind, pdfOutputFile);
//    //
//    //    makePlot("PhotonHadTowOverEm_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Max photon H/E (tower)",0,0.2,0.1,1000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile);
//    //
//    //    makePlot("PhotonHadronicOverEm_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Max photon H/E (cone)",0,0.2,0.1,1000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile);
//    //
//    //    makePlot("leptonHSCEta_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Lepton H Photon #eta",-3,3,0.1,5000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile);
//    //
//    //    makePlot("leptonLSCEta_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Lepton L Photon #eta",-3,3,0.1,5000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile);
//    //
//    //    makePlot("leptonHSCEta_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Lepton H Photon #eta",-3,3,0.1,5000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile);
//    //
//    //    makePlot("leptonLSCEta_removedLifetimeCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //        "Lepton L Photon #eta",-3,3,0.1,5000, true,
//    //      false, -999,
//    //        lumi, unblind, pdfOutputFile);
//    //
//    //  makePlot("nMinus1_leadingSCEt_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //      "Leading SC E_{t}", 0, 150, 0.1, 5000000, true,
//    //      true, 40,
//    //      lumi, unblind, pdfOutputFile );
//    //
//    makePlot("nMinus1_subleadingSCEt_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "Sub-leading SC E_{t}", 0, 150, 0.1, 5000000, true,
//        true, 25,
//        lumi, unblind, pdfOutputFile );
//    //
//    //  makePlot("nMinus1_leptonCaloMatchDeltaR_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //      "Maximum Lepton Calo Match #Delta R", 0, 0.1, 0.1, 5000000, true,
//    //      true, 0.1,
//    //      lumi, unblind, pdfOutputFile );
//    //
//    //  makePlot("nMinus1_leadingLeptonTrackPt_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //      "Leading Lepton Track p_{t}", 0, 150, 0.1, 5000000, true,
//    //      true, 36,
//    //      lumi, unblind, pdfOutputFile );
//    //
//    //  makePlot("nMinus1_subleadingLeptonTrackPt_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//    //      "Sub-leading Lepton Track p_{t}", 0, 150, 0.1, 5000000, true,
//    //      true, 21,
//    //      lumi, unblind, pdfOutputFile );
//  }
//  // Muon only plots
//  if ( anaType == "2muTrack" ) {
//    makePlot("nMinus1_cosine_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "cos(#alpha)", -1.1, 1.1, 0.1, 5000, true,
//        true, -0.79,
//        lumi, unblind, pdfOutputFile );
//
//    makePlot("nMinus1_deltaR_finalCuts", outputFile, anaType, 0.5, 0.6, 0.8, 0.9,
//        "#Delta R between leptons", 0, 0.5, 0.1, 500, true,
//        true, 0.2,
//        lumi, unblind, pdfOutputFile );
//
//    makePlot("nMinus1_leadingLeptonTrackPt_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "Leading Lepton Track p_{t}", 0, 150, 0.1, 5000000, true,
//        true, 26,
//        lumi, unblind, pdfOutputFile );
//
//    makePlot("nMinus1_subleadingLeptonTrackPt_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "Sub-leading Lepton Track p_{t}", 0, 150, 0.1, 5000000, true,
//        true, 26,
//        lumi, unblind, pdfOutputFile );
//  }
//  //  //
//  //  //  // n-1 final cuts
//  //  //
//
//  makePlot("nMinus1_oppositeCharge_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "Sign of charges", -2, 22, 0.001, 5000, true,
//      true, 0,
//      lumi, unblind, pdfOutputFile );
//
//  makePlot("nMinus1_deltaPhi_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "Candidate #Delta#Phi", 0, 4, 0.1, 5000, true,
//      false, -999,
//      lumi, unblind, pdfOutputFile );
//
//  makePlot("nMinus1_nHitsBeforeVertex_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "Number of hits before vertex", 0, 5, 0.1, 5000, true,
//      true, 2,
//      lumi, unblind, pdfOutputFile );
//
//  makePlot("nMinus1_nMissingHitsAfterVertex_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "Number of missing hits after vertex", 0, 8, 0.1, 5000, true,
//      true, 4,
//      lumi, unblind, pdfOutputFile );
//
//  //    makePlot("nMinus1_leptonAbsD0Sig_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//  //        "Minimum Lepton d0/#sigma_{d}", 0, 10, 0.1, 5000000, true,
//  //        false, -999,
//  //        lumi, unblind, pdfOutputFile );
//
//  if ( anaType == "2muTrack" ) {
//    makePlot("nMinus1_leptonD0Sig_finalCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//        "Minimum Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//        true, 5,
//        lumi, unblind, pdfOutputFile, unblind );
//
//    makePlot("nMinus1_leptonD0SigMax_finalCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//        "Maximum Lepton d0/#sigma_{d}", -20, 20, 0.1, 5000000, true,
//        true, 5,
//        lumi, unblind, pdfOutputFile, unblind );
//
//    //    makePlot("nMinus1_leptonAbsD0Sig_oppositeSignMin_finalCuts", outputFile, anaType, 0.5, 0.5, 0.85, 0.85,
//    //        "Minimum Abs Lepton d0/#sigma_{d}", -20, 15, 0.1, 5000000, true,
//    //        true, 5,
//    //        lumi, unblind, pdfOutputFile, false );
//
//    makePlot("nMinus1_leptonD0Sig_oppositeSignMin_finalCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//        "Minimum Abs Lepton d0/#sigma_{d}", -20, 15, 0.1, 5000000, true,
//        true, 5,
//        lumi, unblind, pdfOutputFile, false );
//
//    makePlot("nMinus1_leptonD0Sig_oppositeSignMax_finalCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//        "Maximum Abs Lepton d0/#sigma_{d}", -20, 20, 0.1, 5000000, true,
//        true, 5,
//        lumi, unblind, pdfOutputFile, false );
//
//    makePlot("nMinus1_vertexChi2_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "Candidate Vertex #Chi^2", 0, 20, 0.1, 5000, true,
//        true, 5,
//        lumi, unblind, pdfOutputFile );
//  }
//  else if ( anaType == "2eTrack" ) {
//    makePlot("nMinus1_leptonD0Sig_finalCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//        "Minimum Lepton d0/#sigma_{d}", -20, 10, 0.1, 5000000, true,
//        true, 7,
//        lumi, unblind, pdfOutputFile, false );
//
//    makePlot("nMinus1_leptonD0SigMax_finalCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//        "Maximum Lepton d0/#sigma_{d}", -20, 20, 0.1, 5000000, true,
//        true, 7,
//        lumi, unblind, pdfOutputFile, unblind );
//
//    //    makePlot("nMinus1_leptonAbsD0Sig_oppositeSignMin_finalCuts", outputFile, anaType, 0.5, 0.5, 0.85, 0.85,
//    //        "Minimum Abs Lepton d0/#sigma_{d}", -20, 15, 0.1, 5000000, true,
//    //        true, 7,
//    //        lumi, unblind, pdfOutputFile, false );
//
//    makePlot("nMinus1_leptonD0Sig_oppositeSignMin_finalCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//        "Minimum Abs Lepton d0/#sigma_{d}", -20, 15, 0.1, 5000000, true,
//        true, 7,
//        lumi, unblind, pdfOutputFile, false );
//
//    makePlot("nMinus1_leptonD0Sig_oppositeSignMax_finalCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//        "Maximum Abs Lepton d0/#sigma_{d}", -20, 20, 0.1, 5000000, true,
//        true, 7,
//        lumi, unblind, pdfOutputFile, false );
//
//    makePlot("nMinus1_vertexChi2_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//        "Candidate Vertex #Chi^2", 0, 20, 0.1, 5000, true,
//        true, 10,
//        lumi, unblind, pdfOutputFile );
//  }
//  makePlot("nMinus1_leptonD0SigSameSign_finalCuts", outputFile, anaType, 0.2, 0.5, 0.5, 0.85,
//      "Sign of d0/#sigma_{d}'s of leptons", -2, 2, 0.1, 5000000, true,
//      false, -999,
//      lumi, unblind, pdfOutputFile );
//
//
//
//  makePlot("nMinus1_relIso_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "#Sigma p_{t}/p_{t}^{lepton}", 0, 0.2, 0.1, 10000, true,
//      true, 0.1,
//      lumi, unblind, pdfOutputFile );
//
//  makePlot("nMinus1_absIso_finalCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
//      "#Sigma p_{t} Lepton", 0, 20, 0.1, 10000, true,
//      false, -999,
//      lumi, unblind, pdfOutputFile );

  //
  // Loose Cuts
  //

//  makeCommonPlots( anaType, outputFile, pdfOutputFile, lumi, true, "looseCutsA");
//  makeCommonPlots( anaType, outputFile, pdfOutputFile, lumi, true, "looseCutsB");
//  makeCommonPlots( anaType, outputFile, pdfOutputFile, lumi, true, "looseCutsC");
//  makeCommonPlots( anaType, outputFile, pdfOutputFile, lumi, false, "removedLifetimeNoVertex");

//  makePlot("minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts", outputFile, anaType, 0.2, 0.6, 0.5, 0.85,
//      "Minimum Signed Lepton d0/#sigma_{d}", -20, 20, 0.01, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile );
//
//  makePlot("minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts", outputFile, anaType, 0.2, 0.6, 0.5, 0.85,
//      "Minimum Signed Lepton d0/#sigma_{d}", -20, 20, 0.01, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile );
//
//  makePlot("minLeptonD0Sig_signedWrtDileptonPerp_removedLifetimeCuts", outputFile, anaType, 0.2, 0.6, 0.5, 0.85,
//      "Minimum Signed Lepton d0/#sigma_{d}", -20, 20, 0.01, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile );

  //
  // New collinearity cuts
  //

  // Removed lifetime
  makePlot("Mass_removedLifetime_CollCuts", outputFile, anaType, 0.6, 0.55, 0.9, 0.9,
      "Mass[Gev/c^{2}]", 0, 500, 0.1, 10000000, true,
      false, -999,
      lumi, true, pdfOutputFile, true );

  makePlot("Mass_removedLifetime_controlCollCuts", outputFile, anaType, 0.6, 0.55, 0.9, 0.9,
      "Mass[Gev/c^{2}]", 0, 500, 0.1, 10000000, true,
      false, -999,
      lumi, true, pdfOutputFile, true );

    makePlot("nMinus1_relIsolationLeptonH_removedLifetimeCollCuts", outputFile, anaType, 0.6, 0.6, 0.9, 0.9,
        "#Sigma p_{t}/p_{t}^{lepton}", 0, 0.5, 100, 5000000, true,
        false, -999,
        lumi, plotData, pdfOutputFile, true );

  pdfOutputFile="output/output_"+anaType+".pdf";

  makePlot("deltaPhiSigned_removedLifetimeCollCuts", outputFile, anaType, 0.75, 0.6, 0.95, 0.85,
      "Collinearity #Delta#phi", -3.5, 3.5, 1, 5000000, true,
      false, -999,
      lumi, true, pdfOutputFile, true );

  makePlot("nMinus1_deltaPhi_controlCollCuts", outputFile, anaType, 0.65, 0.68, 0.95, 0.93,
      "Collinearity #Delta#phi", 0, 3.5, 1, 50000000, true,
      false, -999,
      lumi, true, pdfOutputFile, true );

  makePlot("deltaPhi_removedLifetimeCollCuts", outputFile, anaType, 0.5, 0.6, 0.9, 0.9,
      "Collinearity #Delta#phi", 0, 4, 0.1, 5000, true,
      false, -999,
      lumi, true, pdfOutputFile, true );

  makePlot("minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCollCuts", outputFile, anaType, 0.5, 0.4, 0.92, 0.92,
      "Min |d_{xy}/#sigma_{xy}|, |#Delta#phi| < #pi/2", 0, 20, 0.01, 5000000, true,
      true, 12,
      lumi, false, pdfOutputFile );

  makePlot("minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCollCuts", outputFile, anaType, 0.5, 0.4, 0.92, 0.92,
      "Min |d_{xy}/#sigma_{xy}|, |#Delta#phi| > #pi/2", 0, 20, 0.01, 5000000, true,
      false, -999,
      lumi, true, pdfOutputFile, true );
//
  makePlot("minLeptonAbsD0Sig_deltaPhiPlus_removedLifetimeCollCuts", outputFile, anaType, 0.5, 0.4, 0.92, 0.92,
      "Min |d_{xy}/#sigma_{xy}|, #Delta#phi > 0", 0, 20, 0.01, 5000000, true,
      false, -999,
      lumi, false, pdfOutputFile );

  makePlot("minLeptonAbsD0Sig_deltaPhiMinus_removedLifetimeCollCuts", outputFile, anaType, 0.5, 0.4, 0.92, 0.92,
      "Min |d_{xy}/#sigma_{xy}|, #Delta#phi < 0", 0, 20, 0.01, 5000000, true,
      false, -999,
      lumi, false, pdfOutputFile );

  makePlot("minLeptonAbsD0Sig_bestCand_deltaPhiG90_removedLifetimeCollCuts", outputFile, anaType, 0.5, 0.4, 0.92, 0.92,
      "Min |d_{xy}/#sigma_{xy}|", 0, 20, 0.01, 5000000, true,
      false, -999,
      lumi, true, pdfOutputFile, true );

  makePlot("minLeptonAbsD0Sig_bestCand_deltaPhiL90_removedLifetimeCollCuts", outputFile, anaType, 0.5, 0.4, 0.92, 0.92,
      "Min |d_{xy}/#sigma_{xy}|", 0, 20, 0.01, 5000000, true,
      false, -999,
      lumi, true, pdfOutputFile );

  makePlot("minLeptonAbsD0Sig_bestCand_deltaPhiMinus_removedLifetimeCollCuts", outputFile, anaType, 0.5, 0.4, 0.92, 0.92,
      "Min |d_{xy}/#sigma_{xy}|", 0, 20, 0.01, 5000000, true,
      false, -999,
      lumi, true, pdfOutputFile );

  makePlot("minLeptonAbsD0Sig_bestCand_deltaPhiPlus_removedLifetimeCollCuts", outputFile, anaType, 0.5, 0.4, 0.92, 0.92,
      "Min |d_{xy}/#sigma_{xy}|", 0, 20, 0.01, 5000000, true,
      false, -999,
      lumi, true, pdfOutputFile );

  makePlot("nCandsPerEvent_deltaPhiG90_removedLifetimeCollCuts", outputFile, anaType, 0.4, 0.6, 0.7, 0.85,
      "# reco cands", 0.5, 5.5, 0.1, 50000000, true,
      false, -999,
      lumi, true, pdfOutputFile );

  makePlot("nCandsPerEvent_deltaPhiL90_removedLifetimeCollCuts", outputFile, anaType, 0.4, 0.6, 0.7, 0.85,
      "# reco cands", 0.5, 5.5, 0.1, 50000000, true,
      false, -999,
      lumi, false, pdfOutputFile );

  makePlot("minLeptonAbsD0Sig_PVnorefit_controlCollCuts", outputFile, anaType, 0.5, 0.4, 0.92, 0.92,
      "Min |d_{xy}/#sigma_{xy}|, #Delta#phi > #pi/2", 0, 20, 0.01, 5000000, true,
      false, -999,
      lumi, true, pdfOutputFile, true );

  makePlot("minLeptonAbsD0Sig_deltaPhiG90_noMissingHits_algo10_removedLifetimeCollCuts", outputFile, anaType, 0.4, 0.6, 0.7, 0.85,
      "Min |d_{xy}/#sigma_{xy}|, #Delta#phi > #pi/2", 0, 20, 0.01, 5000000, true,
      false, -999,
      lumi, true, pdfOutputFile, true );


//  for ( int algo=4; algo < 11; algo++ ) {
//    stringstream a;
//    a << algo;
//    makePlot("minLeptonAbsD0Sig_deltaPhiG90_algo"+a.str()+"_removedLifetimeCollCuts", outputFile, anaType, 0.4, 0.6, 0.7, 0.85,
//        d0SigmaTitle, 0, 20, 0.01, 5000000, true,
//        false, -999,
//        lumi, true, pdfOutputFile, true );
//  }

//  makePlot("minLeptonAbsD0Sig_deltaPhiG90_algo9_removedLifetimeCollCuts", outputFile, anaType, 0.4, 0.6, 0.7, 0.85,
//      d0SigmaTitle, 0, 20, 0.01, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );
//
//  makePlot("minLeptonAbsD0Sig_deltaPhiG90_algo10_removedLifetimeCollCuts", outputFile, anaType, 0.4, 0.6, 0.7, 0.85,
//      d0SigmaTitle, 0, 20, 0.01, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );

//
//  makePlot("minLeptonAbsD0Sig_PVnorefit_controlCollCuts", outputFile, anaType, 0.4, 0.6, 0.7, 0.85,
//      d0SigmaTitle, 0, 20, 0.01, 5000000, true,
//      false, -999,
//      lumi, true, pdfOutputFile, true );
//
//  makePlot("minLeptonD0Sig_signedWrtDeltaPhi_forFittingData_removedLifetimeCollCuts", outputFile, anaType, 0.4, 0.6, 0.7, 0.85,
//      d0SigmaTitle, -20, 20, 0.01, 5000000, true,
//        false, -999,
//        lumi, true, pdfOutputFile, true );
//
//  makePlot("minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts", outputFile, anaType, 0.4, 0.6, 0.7, 0.85,
//      d0SigmaTitle, -20, 20, 0.01, 5000000, true,
//        false, -999,
//        lumi, true, pdfOutputFile, true );
//
  makeCommonPlots( anaType, outputFile, pdfOutputFile, lumi, false, false, "finalCollCuts", true);
  makeCommonPlots( anaType, outputFile, pdfOutputFile, lumi, false, false, "looseCollCuts", true);
  makeCommonPlots( anaType, outputFile, pdfOutputFile, lumi, true, true, "looseControlCollCuts", true);
  makeCommonPlots( anaType, outputFile, pdfOutputFile, lumi, true, true, "controlCollCuts", true);

  // Final cuts, best candidate
  makePlot("Mass_bestCand_finalCollCuts", outputFile, anaType, 0.35, 0.55, 0.7, 0.92,
      "Mass[Gev/c^{2}]", 0, 500, 0.01, 5000, true,
      false, -999,
      lumi, unblind, pdfOutputFile );

  makePlot("Lxy_bestCand_finalCollCuts", outputFile, anaType, 0.6, 0.55, 0.9, 0.9,
      "Candidate L_{xy} [cm]", 0, 50, 0.01, 50, true,
      false, -999,
      lumi, unblind, pdfOutputFile );

  // Event histograms
  pdfOutputFile="output/output_"+anaType+".pdf)";
  makePlot("nRecoPV_removedLifetimeCollCuts", outputFile, anaType, 0.75, 0.6, 0.95, 0.90,
      "Number Reconstructed PV",0,50,0.1,3000000, true,
      false, -999,
      lumi, true, pdfOutputFile, true);


  outputFile->Write();
  outputFile->Close();

}
