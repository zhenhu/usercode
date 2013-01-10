#ifndef GenEventProperties_h
#define GenEventProperties_h

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/PatternTools/interface/TSCBLBuilderNoMaterial.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

#include "FWCore/Framework/interface/ESHandle.h"

class GenEventProperties
{
 private:

  // long-lived decay properties
  unsigned numDecays_;
  std::vector<int> motherId_;
  std::vector<int> decayModes_;
  std::vector<double> decayLength2D_;
  std::vector<double> decayLength3D_;
  std::vector<double> ctau_;

  // Daughter properties
  std::vector<double> daughterPt_;
  std::vector<double> daughterD0_;

  // pile-up vertices
  float nvtx_m1_;
  float nvtx_0_;
  float nvtx_p1_;

  float nvtx_true_;

  // PDF description
  int pdf_id_[2];
  double pdf_x_[2];
  double pdf_xPDF_[2];
  double pdf_scale_;

 public:

  struct DecayLengthAndType
  {
    DecayLengthAndType(const int inputDecayPid,
                       const int inputMotherPid,
                       const double & inputDecayLength2D,
                       const double & inputDecayLength3D,
                       const double & inputctau,
                       std::vector< const reco::Candidate* > inputDaughters
                       ) :
      decayPid(inputDecayPid),
      motherPid(inputMotherPid),
      decayLength2D(inputDecayLength2D),
      decayLength3D(inputDecayLength3D),
      ctau(inputctau)
    { daughters = inputDaughters ; }

    int decayPid;
    int motherPid;
    double decayLength2D;
    double decayLength3D;
    double ctau;
    std::vector< const reco::Candidate* > daughters;
  };

  GenEventProperties();
  GenEventProperties(const edm::Event&,
                     const edm::EventSetup& iSetup,
                     std::vector<int> signalPDGId,
                     edm::InputTag& generatorTag,
                     edm::InputTag& pileupTag,
                     edm::InputTag& genEventInfoTag);

  static DecayLengthAndType getDecayLengthAndType(const reco::GenParticle & part);

  double getGenParticleD0(const edm::Event& iEvent, const edm::EventSetup& iSetup, const reco::Candidate & part);

  // accessors for decay properties
  unsigned numDecays() { return decayModes_.size(); }
  int decayMode(unsigned i) { if (i<2) return decayModes_[i]; else return -999; }
  int motherId(unsigned i) { if (i<2) return motherId_[i]; else return -999; }
  double decayLength2D(unsigned i) { if (i<2) return decayLength2D_[i]; else return -999; }
  double decayLength3D(unsigned i) { if (i<2) return decayLength3D_[i]; else return -999; }
  double ctau(unsigned i) { if (i<2) return ctau_[i]; else return -999; }
  double daughterPt(unsigned i ) { if (i<4) return daughterPt_[i]; else return -999; }
  double daughterD0(unsigned i ) { if (i<4) return daughterD0_[i]; else return -999; }

  // accessors for pile-up
  float numPileupInTime() { return nvtx_0_; }
  float numPileup( int BX ) { if (BX!=0) return (BX==-1) ? nvtx_m1_ : nvtx_p1_; else return nvtx_0_; }
  float numTruePUInteractions() { return nvtx_true_; }

  // accessors for PDF
  int pdfId(unsigned i) { if (i<2) return pdf_id_[i]; else return -999; }
  double pdfX(unsigned i) { if (i<2) return pdf_x_[i]; else return -999; }
  double pdfXPDF(unsigned i) { if (i<2) return pdf_xPDF_[i]; else return -999; }
  double pdfScale() { return pdf_scale_; }
};

#endif
