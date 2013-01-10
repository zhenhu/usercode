{
  gROOT->ProcessLine(".include /home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_5/src/");


  // Choose here which analysis to run
  /*
    0  _2eTrack, // 2*Track matched to photon TO
    1  _2muTrack, // 2*Track matched to muon TO
    2  _2globalMu, // 2*Global Mu
    3  _2trackerMu, // 2*Tracker Mu
    4  _2saMu, // 2*Stand Alone Mu
    5  _2photon, // 2*Photon/trackless electron
    6  _2jet // Dijet analysis
   */
  gROOT->ProcessLine(".L ../CommonMacros/analysisType.C+");
  analysisType a=0;

    // Load and run analyzer
    gROOT->ProcessLine(".L fullAnalyzer.C++");
  //   For some reason I do not understand, I can't just do fullAnalyzer(a) here.
  //   However it works if I put it in a separate unnamed script...
    gROOT->ProcessLine(".x runDileptonAnalzyer.C");

   // Load and run full combination
    gROOT->ProcessLine(".L ../CommonMacros/fullCombination.C++");
    fullCombination(a);

  // Load and run makeAllPlots
  // set up the tdr style
//  gROOT->ProcessLine(".L ./tdrstyle.C");
//  setTDRStyle();
    gROOT->ProcessLine(".L makeAllPlots.C+");
    makeAllPlots(a,true);
}
