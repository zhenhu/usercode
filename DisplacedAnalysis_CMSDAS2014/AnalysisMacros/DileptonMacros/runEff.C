#include "MixedChannelEff.C"

#include <map>
#include <TString.h>

#include "AnalysisMacros/CommonMacros/analysisType.C"

/*
  0  _2eTrack, // 2*Track matched to photon TO
  1  _2muTrack, // 2*Track matched to muon TO
  2  _2globalMu, // 2*Global Mu
  3  _2trackerMu, // 2*Tracker Mu
  4  _2saMu, // 2*Stand Alone Mu
  5  _2photon, // 2*Photon/trackless electron
  6  _2jet // Dijet analysis
*/


void runEff()
{
  analysisType ana = _2muTrack;
  //TString infile("/uscms_data/d3/plujan/TreeFiles/histograms_2B2Mu_MH_300_MFF_125_CTau100_8TeV_1.root");
  TString infile("/uscms_data/d3/plujan/TreeFiles/histograms_2B2Mu_MH_1000_MFF_350_CTau350_8TeV_1.root");
  //TString infile("/uscms_data/d3/plujan/TreeFiles/histograms_4B_MH_300_MFF_125_CTau100_8TeV_1.root");
  //TString infile("/uscms_data/d3/plujan/TreeFiles/histograms_4B_MH_1000_MFF_350_CTau350_8TeV_1.root");

  std::cout << "Analysis type : " << ana << std::endl;

  //bool electrons=false;
  //if (ana==_2eTrack) electrons=true;

  MixedChannelEff analyzer(infile, 1, ana);
  analyzer.Loop();
}
