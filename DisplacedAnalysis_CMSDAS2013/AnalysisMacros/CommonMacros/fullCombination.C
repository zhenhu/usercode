#include <map>
#include <TString.h>
#include <iostream>
#include <TH1F.h>
#include <TFile.h>
#include <TKey.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TClass.h>
#include <TChain.h>
#include "FilesAndWeights.h"
#include "MergeFiles.h"
#include "GetCategory.h"

#include "treeAnalyzerBase.h"

/*
  0  _2eTrack, // 2*Track matched to photon TO
  1  _2muTrack, // 2*Track matched to muon TO
  2  _2globalMu, // 2*Global Mu
  3  _2trackerMu, // 2*Tracker Mu
  4  _2saMu, // 2*Stand Alone Mu
  5  _2photon, // 2*Photon/trackless electron
  6  _2jet // Dijet analysis
*/

void fullCombination(analysisType ana)
{
  TString type("");
  bool electrons=false;
  if ( ana==_2eTrack) {
    electrons=true;
    type = "2eTrack";
  }
  else if ( ana==_2muTrack ) type = "2muTrack";
  else if ( ana==_2globalMu ) type = "2globalMu";
  else if ( ana==_2trackerMu ) type = "2trackerMu";
  else if ( ana==_2saMu ) type = "2saMu";

  std::map<TString, TList*> categories;
  // Loop over all files
  std::map<TString, double> fw(filesAndWeightsMap( electrons ));
  std::map<TString, double>::const_iterator it = fw.begin();
  for( ; it != fw.end(); ++it ) {
    TString category(getCategory(it->first));

    // Skip unkown categories and signal MC
    if ( category=="" ) {
      std::cout << "Skipping file " << (it->first).Data() << std::endl;
      continue;
    }
    else std::cout << "Got sample " << it->first.Data() << " for category " << category.Data() << std::endl;

    if( categories[category] == 0 ) categories[category] = new TList();
    categories[category]->Add( TFile::Open("WeightedFiles/"+std::string(it->first).substr(std::string(it->first).find_last_of("/")+1)+"_weighted_"+type+".root") );
  }

  TList * combinationsList = new TList();
  std::map<TString, TList*>::const_iterator it2 = categories.begin();
  for( ; it2 != categories.end(); ++it2 ) {
    TFile *Target = TFile::Open( "CombinedFiles/"+it2->first+"_combined_"+type+".root", "RECREATE" );
    combinationsList->Add( Target );
    mergeFiles( Target, it2->second );
  }
}
