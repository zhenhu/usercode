#include "DileptonAnalyzer.C"

#include <map>
#include <TString.h>
#include "FilesAndWeights.h"

#include "analysisType.C"
/*
  0  _2eTrack, // 2*Track matched to photon TO
  1  _2muTrack, // 2*Track matched to muon TO
  2  _2globalMu, // 2*Global Mu
  3  _2trackerMu, // 2*Tracker Mu
  4  _2saMu, // 2*Stand Alone Mu
  5  _2photon, // 2*Photon/trackless electron
  6  _2jet // Dijet analysis
 */


void fullAnalyzer(analysisType ana)
{
//  std::cout << "Analysis : " << whichAnalysis << std::endl;
//  analysisType ana=whichAnalysis;
  std::cout << "Analysis type : " << ana << std::endl;

  bool electrons=false;
  if (ana==_2eTrack) electrons=true;

  // passing file name, weight and if it is electrons or muons.
  // The weights are the cross sections in pb
  std::map<TString, double> fw(filesAndWeightsMap( electrons ));
  std::map<TString, double>::const_iterator it = fw.begin();

  for( ; it != fw.end(); ++it ) {
    std::cout << "processing: " << it->first << std::endl;

    DileptonAnalyzer analyzer(it->first+"/histograms.root",it->second,ana);
    analyzer.Loop();
  }
}
