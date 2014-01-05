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
  0 _2eTrack, // 2*Track matched to photon TO
  1 _2muTrack, // 2*Track matched to muon TO
  2 _2globalOrTrackerMu, // 2*Global or tracker Mu
  3 _2globalMu, // 2*Global Mu
  4 _2trackerMu, // 2*Tracker Mu
  5 _2saMu, // 2*Stand Alone Mu
  6 _2photon, // 2*Photon/trackless electron
  7 _2jet // Dijet analysis
 */

void fullCombination(analysisType ana)
{
  TString type("");
  bool electrons=false;
  if ( ana==_2eTrack) {
    electrons=true;
    type = "2eTrack";
  }
  else if ( ana==_2globalOrTrackerMu ) type = "2globalOrTrackerMu";
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

    TString fileName("WeightedFiles/"+std::string(it->first).substr(std::string(it->first).find_last_of("/")+1)+"_weighted_"+type+".root");
    categories[category]->Add( TFile::Open(fileName) );

    // Check for tau version
    if ( category != "Data" && !category.BeginsWith("HTo2LongLived") && !category.BeginsWith("Chi0ToNuLL") ) {
      TString tauFileName("WeightedFiles/"+std::string(it->first).substr(std::string(it->first).find_last_of("/")+1)+"_weighted_"+type+"_tau.root");
      if ( categories["Tau"] == 0 ) categories["Tau"] = new TList();
      std::cout << "Adding tau version : " << tauFileName << std::endl;
      categories["Tau"]->Add( TFile::Open(tauFileName) );
    }
    // Check for d0 corrected fiels
    if ( category == "Data" ) {
      TString correctedFileName("WeightedFiles/"+std::string(it->first).substr(std::string(it->first).find_last_of("/")+1)+"_weighted_"+type+"_tipLipCorrected.root");
      if ( categories["Data_tipLipCorrected"] == 0 ) categories["Data_tipLipCorrected"] = new TList();
      std::cout << "Adding tip lip corrected version : " << correctedFileName << std::endl;
      categories["Data_tipLipCorrected"]->Add( TFile::Open(correctedFileName) );
    }
    else if ( category == "Data22Jan") {
      TString correctedFileName("WeightedFiles/"+std::string(it->first).substr(std::string(it->first).find_last_of("/")+1)+"_weighted_"+type+"_tipLipCorrected.root");
      if ( categories["Data22Jan_tipLipCorrected"] == 0 ) categories["Data22Jan_tipLipCorrected"] = new TList();
      std::cout << "Adding tip lip corrected version : " << correctedFileName << std::endl;
      categories["Data22Jan_tipLipCorrected"]->Add( TFile::Open(correctedFileName) );    }

    //    if ( category=="DYJets" ) {
    //      if ( categories["DYJetsTau"] == 0 ) categories["DYJetsTau"] = new TList();
    //      categories["DYJetsTau"]->Add( TFile::Open("WeightedFiles/"+std::string(it->first).substr(std::string(it->first).find_last_of("/")+1)+"_weighted_"+type+"_tau.root") );
    //    }
  }

  TList * combinationsList = new TList();
  std::map<TString, TList*>::const_iterator it2 = categories.begin();
  for( ; it2 != categories.end(); ++it2 ) {
    std::cout << "Doing category : " << it2->first << std::endl;
    TFile *Target = TFile::Open( "CombinedFiles/"+it2->first+"_combined_"+type+".root", "RECREATE" );
    combinationsList->Add( Target );
    mergeFiles( Target, it2->second );
  }
}
