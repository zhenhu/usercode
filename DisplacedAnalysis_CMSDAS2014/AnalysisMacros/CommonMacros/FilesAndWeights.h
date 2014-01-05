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
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_analysis_20130731"] = 0.1;
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH1000_MFF150_CTau10To1000_analysis_20130731"] = 0.1;
//  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH1000_MFF50_CTau4To400_analysis_20130731"] = 0.1;
//  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH1000_MFF20_CTau1p5To150_analysis_20130731"] = 0.1;
//
//  // mH = 400 GeV
//  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH400_MFF150_CTau40To4000_analysis_20130731"] = 0.1;
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH400_MFF50_CTau8To800_analysis_20130731"] = 0.1;
//  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH400_MFF20_CTau4To400_analysis_20130731"] = 0.1;
//
//  // mH = 200 GeV
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH200_MFF50_CTau20To2000_analysis_20130731"] = 0.1;
//  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH200_MFF20_CTau7To700_analysis_20130731"] = 0.1;
//
//  // mH = 125 GeV
//  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH125_MFF50_CTau50To5000_analysis_20130731"] = 0.1;
//  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/HTo2LongLivedTo4F_MH125_MFF20_CTau13To1300_analysis_20130731"] = 0.1;
//
//  // Chi0
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Chi0ToNuLL_MSquark1500_MChi494_analysis_20130731"] = 0.1;
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Chi0ToNuLL_MSquark1000_MChi148_analysis_20130731"] = 0.1;
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Chi0ToNuLL_MSquark350_MChi148_analysis_20130731"] = 0.1;
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Chi0ToNuLL_MSquark120_MChi48_analysis_20130731"] = 0.1;

  // Vector bosons

  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/ZZ_analysis_20130807"] = 17.6;
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/WZ_analysis_20130807"] = 33.2;
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/WW_analysis_20130807"] = 54.8;
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/WJetsToLNu_analysis_20130807"] = 36257.2;


  // TTbar

  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/TTJets_FullLept_analysis_20130807"] = 24.77;

  // DY JETS
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/DYJets10_analysis_20130807"] = 12471;
  fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/DYJets50_analysis_20130807"] = 3503.7;


  if (!electrons)
  {
    // QCD mu
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/QCDmu15_analysis_20130807"] = 2738580.0;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/QCDmu20_analysis_20130807"] = 134680.0;


    // Data
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012A1_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012A2_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012B1_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012C1_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012C2_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012D1_analysis_20130731"] = -1;

//     Data
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012A22Jan_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012B22Jan_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012C22Jan_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Mu_Run2012D22Jan_analysis_20130731"] = -1;
  }
  else
  {
    // QCD em
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/QCDem20_analysis_20130807"] = 2914860.0;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/QCDem30_analysis_20130807"] = 4615893.0;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/QCDem80_analysis_20130807"] = 183294.9;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/QCDem170_analysis_20130807"] = 4586.52;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/QCDem250_analysis_20130807"] = 556.75;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/QCDem350_analysis_20130807"] = 89.1;

    // Data
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012A1_analysis_20130731"] = -1.;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012A2_analysis_20130731"] = -1.;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012B1_analysis_20130731"] = -1.;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012C1_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012C2_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012D1_analysis_20130731"] = -1.;

    // Data
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012A22Jan_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012B22Jan_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012C22Jan_analysis_20130731"] = -1;
    fw["/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/workdirs/Data_Photon_Run2012D22Jan_analysis_20130731"] = -1;

  }
  return fw;
}

#endif
