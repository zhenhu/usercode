#ifndef analysistype
#define analysistype
// Type of analysis you are doing
typedef enum {
  _2eTrack, // 2*Track matched to photon TO
  _2muTrack, // 2*Track matched to muon TO
  _2globalOrTrackerMu, // 2*Global or tracker Mu
  _2globalMu, // 2*Global Mu
  _2trackerMu, // 2*Tracker Mu
  _2saMu, // 2*Stand Alone Mu
  _2photon, // 2*Photon/trackless electron
  _2jet // Dijet analysis
}
analysisType;
#endif
