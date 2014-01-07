#ifndef FILESANDWEIGHTS_H
#define FILESANDWEIGHTS_H

#include <map>
#include <TString.h>

std::map<TString, double> filesAndWeightsMap( bool electrons )
{
  // The weights are the cross sections in pb. The number of processed events is read from a histograms in the tree root file.
  // Give data a weight of -1, so we know it is data

  // Files and weights map
  std::map<TString, double> fw;

  // Signal

  //  // mH = 1000 GeV
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_analysis_20131120"] = 0.1;
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH1000_MFF150_CTau10To1000_analysis_20131120"] = 0.1;
//  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH1000_MFF50_CTau4To400_analysis_20131120"] = 0.1;
//  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH1000_MFF20_CTau1p5To150_analysis_20131120"] = 0.1;
//
//  // mH = 400 GeV
//  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH400_MFF150_CTau40To4000_analysis_20131120"] = 0.1;
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH400_MFF50_CTau8To800_analysis_20131120"] = 0.1;
//  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH400_MFF20_CTau4To400_analysis_20131120"] = 0.1;
//
//  // mH = 200 GeV
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH200_MFF50_CTau20To2000_analysis_20131120"] = 0.1;
//  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH200_MFF20_CTau7To700_analysis_20131120"] = 0.1;
//
//  // mH = 125 GeV
//  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH125_MFF50_CTau50To5000_analysis_20131120"] = 0.1;
//  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/HTo2LongLivedTo4F_MH125_MFF20_CTau13To1300_analysis_20131120"] = 0.1;
//
//  // Chi0
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Chi0ToNuLL_MSquark1500_MChi494_analysis_20131120"] = 0.1;
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Chi0ToNuLL_MSquark1000_MChi148_analysis_20131120"] = 0.1;
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Chi0ToNuLL_MSquark350_MChi148_analysis_20131120"] = 0.1;
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Chi0ToNuLL_MSquark120_MChi48_analysis_20131120"] = 0.1;

  // Vector bosons

  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/ZZ_analysis_20131118"] = 17.6;
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/WZ_analysis_20131118"] = 33.2;
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/WW_analysis_20131118"] = 54.8;
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/WJetsToLNu_analysis_20131118"] = 36257.2;


  // TTbar

  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/TTJets_FullLept_analysis_20131118"] = 24.77;

  // DY JETS
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/DYJets10_analysis_20131118"] = 12471;
  fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/DYJets50_analysis_20131118"] = 3503.7;


  if (!electrons)
  {
    // QCD mu
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/QCDmu15_analysis_20131118"] = 2738580.0;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/QCDmu20_analysis_20131118"] = 134680.0;


    // Data
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012A1_analysis_20131120"] = -1;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012A2_analysis_20131120"] = -1;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012B1_analysis_20131120"] = -1;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012C1_analysis_20131120"] = -1;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012C2_analysis_20131120"] = -1;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012D1_analysis_20131120"] = -1;

//     Data
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012A22Jan_analysis_20130909"] = -1;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012B22Jan_analysis_20130909"] = -1;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012C22Jan_analysis_20130909"] = -1;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Mu_Run2012D22Jan_analysis_20130909"] = -1;
  }
  else
  {
    // QCD em
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/QCDem20_analysis_20131118"] = 2914860.0;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/QCDem30_analysis_20131118"] = 4615893.0;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/QCDem80_analysis_20131118"] = 183294.9;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/QCDem170_analysis_20131118"] = 4586.52;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/QCDem250_analysis_20131118"] = 556.75;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/QCDem350_analysis_20131118"] = 89.1;

    // Data
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012A1_analysis_20131120"] = -1.;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012A2_analysis_20131120"] = -1.;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012B1_analysis_20131120"] = -1.;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012C1_analysis_20131120"] = -1;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012C2_analysis_20131120"] = -1;
//    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012D1_analysis_20131120"] = -1.;

    // Data
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012A22Jan_analysis_20131120"] = -1;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012B22Jan_analysis_20131120"] = -1;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012C22Jan_analysis_20131120"] = -1;
    fw["/uscms_data/d3/demattia/ForDL2012/CMSDAS2014/Data_Photon_Run2012D22Jan_analysis_20131115"] = -1;

  }
  return fw;
}

#endif
