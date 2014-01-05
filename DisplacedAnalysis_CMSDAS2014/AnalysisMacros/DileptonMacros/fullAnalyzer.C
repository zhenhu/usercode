#include "DileptonAnalyzer.h"

#include <map>
#include <TString.h>
#include <cstdlib>
#include "AnalysisMacros/CommonMacros/FilesAndWeights.h"
#include "AnalysisMacros/CommonMacros/GetCategory.h"


#include "AnalysisMacros/CommonMacros/analysisType.h"


using namespace std;

/*
  0  _2eTrack, // 2*Track matched to photon TO
  1  _2muTrack, // 2*Track matched to muon TO
  2  _2globalMu, // 2*Global Mu
  3  _2trackerMu, // 2*Tracker Mu
  4  _2saMu, // 2*Stand Alone Mu
  5  _2photon, // 2*Photon/trackless electron
  6  _2jet // Dijet analysis
 */


void fullAnalyzer(analysisType ana, TString cat="All")
{
  bool electrons=false;
  if (ana==_2eTrack) electrons=true;
  // passing file name, weight and if it is electrons or muons.
  // The weights are the cross sections in pb
  map<TString, double> fw(filesAndWeightsMap( electrons ));

  map<TString, double>::const_iterator it = fw.begin();
  for( ; it != fw.end(); ++it ) {

    if ( cat != "all" ){
      TString thisCat = getCategory(it->first);

      if ( thisCat != cat ) {
        if (thisCat.BeginsWith("HTo2LongLived") || thisCat.BeginsWith("Chi0ToNuLL") ) thisCat = "Signal";
        else if ( thisCat.BeginsWith("QCD") ) thisCat = "QCD";
        else if (thisCat == "ZZ" || thisCat == "WZ" || thisCat == "WW" || thisCat == "WJets" || thisCat == "TTJets" ) thisCat = "Diboson";
        else if (thisCat == "Data22JanA" || thisCat == "Data22JanB" || thisCat == "Data22JanC" || thisCat == "Data22JanD") thisCat = "Data22Jan";
        else if (thisCat == "DataA" || thisCat == "DataB" || thisCat == "DataC" || thisCat == "DataD") thisCat = "Data";
        if ( thisCat != cat ) continue;
      }
    }

    cout << "processing: " << it->first << " Weight : " << it->second << " Ana : " << ana << endl;

    DileptonAnalyzer analyzer(it->first+"/histograms.root",it->second,ana);
    analyzer.Loop();
  }
}

#ifndef __CINT__
int main(int argc, char *argv[]) {

  if ( argc < 2 ) {
    cout << "Please provide arguments" << endl;
    cout << "Argument 1 : analysis type (0,1,2...)" << endl;
    cout << "Argument 2 : samples to analyse (ZZ,Diboson,All,...)" << endl;
  }

  analysisType ana;
  ana= analysisType(atoi(argv[1]));
  TString samples(argv[2]);
  fullAnalyzer(ana,samples);
  return 0;
}
#endif
