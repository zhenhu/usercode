#define PileupReweighting_cxx

#include "PileupReweighting.h"


PileupReweighting::PileupReweighting( TString dataFileName):
dataFileName_(dataFileName)
{

  bool drawThings = false;


  // Get data distribution
  dataFile_ = new TFile( dataFileName_.Data() );
  Data_distr_ = (TH1F*) dataFile_->Get("pileup")->Clone();

  static const unsigned int nBinsX = Data_distr_->GetNbinsX();

//  std::cout << "N bins in data : " << Data_distr_->GetNbinsX() << endl;
//  std::cout << "Low edge : " << Data_distr_->GetBinLowEdge(1) << endl;
//  std::cout << "High edge : " << Data_distr_->GetBinLowEdge(nBinsX) + Data_distr_->GetBinWidth(nBinsX) << endl;
  weights_ = 0;

  // MC distribution, read from array below
  MC_distr_ = new TH1F("PU_generated","Generated pileup distribution (i.e., MC)",60,-0.5,59.5);


  // Summer 12 MC distribution
  // S10 scenario
  // From https://twiki.cern.ch/twiki/bin/view/CMS/Pileup_MC_Gen_Scenarios

  Double_t Summer2012[60] = {
      2.560E-06,
      5.239E-06,
      1.420E-05,
      5.005E-05,
      1.001E-04,
      2.705E-04,
      1.999E-03,
      6.097E-03,
      1.046E-02,
      1.383E-02,
      1.685E-02,
      2.055E-02,
      2.572E-02,
      3.262E-02,
      4.121E-02,
      4.977E-02,
      5.539E-02,
      5.725E-02,
      5.607E-02,
      5.312E-02,
      5.008E-02,
      4.763E-02,
      4.558E-02,
      4.363E-02,
      4.159E-02,
      3.933E-02,
      3.681E-02,
      3.406E-02,
      3.116E-02,
      2.818E-02,
      2.519E-02,
      2.226E-02,
      1.946E-02,
      1.682E-02,
      1.437E-02,
      1.215E-02,
      1.016E-02,
      8.400E-03,
      6.873E-03,
      5.564E-03,
      4.457E-03,
      3.533E-03,
      2.772E-03,
      2.154E-03,
      1.656E-03,
      1.261E-03,
      9.513E-04,
      7.107E-04,
      5.259E-04,
      3.856E-04,
      2.801E-04,
      2.017E-04,
      1.439E-04,
      1.017E-04,
      7.126E-05,
      4.948E-05,
      3.405E-05,
      2.322E-05,
      1.570E-05,
      5.005E-06
  };

  // Fill array with nBinsX
  Double_t TrueData[nBinsX];

  for (unsigned int i=1;i<nBinsX+1;i++) {
    TrueData[i-1]=Data_distr_->GetBinContent(i);
//    std::cout << "Bin : " << i << " Content : " << TrueData[i-1] << std::endl;
  }

  Data_distr_->Reset();
  Data_distr_ = new TH1F("PU_intended","Intended pileup distribution (i.e., Data)",nBinsX,-0.5,59.5);

  //Fill histograms with one generated, one desired distribution

  for (unsigned int i=1;i<61;i++) {
    MC_distr_->SetBinContent(i,Summer2012[i-1]);
  }
  for (unsigned int i=1;i<nBinsX+1;i++) {
    Data_distr_->SetBinContent(i,TrueData[i-1]);
//    std::cout << "Setting bin content : " << i << " as " << TrueData[i-1] << endl;
  }

//  double integral_data = Data_distr_->Integral();
//  double integral_mc = MC_distr_->Integral();

//  std::cout << "Integral data : " << integral_data << " MC : " << integral_mc << std::endl;

  TCanvas *can1 = 0;

  if ( drawThings ) {
    can1 = new TCanvas("can1,","can1",1200,800);
    can1->Divide(2,2);

    can1->cd(1);
    MC_distr_->SetLineColor(kRed);
    Data_distr_->SetLineColor(kBlue);

    Data_distr_->DrawClone();
    MC_distr_->DrawClone("Same");

    can1->cd(2);
  }
  // Normalize histograms
  Data_distr_->Scale(nBinsX/Data_distr_->Integral());
  MC_distr_->Scale(MC_distr_->GetNbinsX()/MC_distr_->Integral());

//  integral_data = Data_distr_->Integral();
//  integral_mc = MC_distr_->Integral();
//
//  std::cout << "Integral data : " << integral_data << " MC : " << integral_mc << std::endl;

  if ( drawThings ) {
    Data_distr_->Draw();
    MC_distr_->Draw("Same");

    can1->cd(3);
  }

  // Calculate weights
  weights_ = (TH1F*) Data_distr_->Clone();
  for (unsigned int i=1;i<nBinsX+1;i++) {

    double dataBinContent = weights_->GetBinContent( i );

    // Find value of x axis in this bin
    double nPV_true_data = weights_->GetXaxis()->GetBinCenter( i );

    // Find corresponding bin in MC distribution
    int binInMC = MC_distr_->GetXaxis()->FindBin( nPV_true_data );

    // Bin content in MC
    double mcBinContent = MC_distr_->GetBinContent( binInMC );

    // Set weight Content
    weights_->SetBinContent( i, dataBinContent / mcBinContent );
  }

  if ( drawThings ) {
    weights_->SetLineColor(kGreen);
    weights_->Draw();
  }

}

PileupReweighting::~PileupReweighting() {
  //  dataFile_->Close();
}



double PileupReweighting::weight( float nPV ) {
  // Which bin?
  int bin = weights_->GetXaxis()->FindBin( nPV - 1 );
  // Return the weight for this value of nPV
  //  double bin = weights_->GetBinContent( bin );
  return weights_->GetBinContent( bin );
}

