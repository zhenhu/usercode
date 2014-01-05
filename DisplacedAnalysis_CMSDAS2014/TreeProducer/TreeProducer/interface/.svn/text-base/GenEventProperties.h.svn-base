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
    std::vector<double> pt_;
    std::vector<double> pz_;
    std::vector<double> E_;
    std::vector<double> Et_;

    // Daughter properties
    std::vector<double> daughterPdgId_;
    std::vector<double> daughterPt_;
    std::vector<double> daughterEta_;
    std::vector<double> daughterD0_;
    std::vector<double> daughterZ0_;

    // Mother resonance/squark properties
    std::vector<int> resPid_;
    std::vector<double> resPt_;
    std::vector<double> resPz_;


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
      DecayLengthAndType(
          const int inputDecayPid,
          const int inputMotherPid,
          const double & inputDecayLength2D,
          const double & inputDecayLength3D,
          const double & inputctau,
          const double & inputPt,
          const double & inputPz,
          const double & inputE,
          const double & inputEt,
          const double & productionX,
          const double & productionY,
          const double & productionZ,
          const double & inputResonancePiD,
          const double & inputResonancePt,
          const double & inputResonancePz,
          std::vector< const reco::Candidate* > inputDaughters
      ) :
        decayPid(inputDecayPid),
        motherPid(inputMotherPid),
        decayLength2D(inputDecayLength2D),
        decayLength3D(inputDecayLength3D),
        ctau(inputctau),
        pt(inputPt),
        pz(inputPz),
        E(inputE),
        Et(inputEt),
        pvX(productionX),
        pvY(productionY),
        pvZ(productionZ),
        resPid(inputResonancePiD),
        resPt(inputResonancePt),
        resPz(inputResonancePz)
      { daughters = inputDaughters ; }

      int decayPid;
      int motherPid;
      double decayLength2D;
      double decayLength3D;
      double ctau;
      double pt;
      double pz;
      double E;
      double Et;
      double pvX;
      double pvY;
      double pvZ;
      double resPid;
      double resPt;
      double resPz;
      std::vector< const reco::Candidate* > daughters;
    };

    GenEventProperties();
    GenEventProperties(const edm::Event&,
        const edm::EventSetup& iSetup,
        std::vector<int> signalPDGId,
        edm::InputTag& generatorTag,
        edm::InputTag& pileupTag,
        edm::InputTag& genEventInfoTag);

    static DecayLengthAndType getDecayLengthAndType(const reco::Candidate & part);

    TrajectoryStateClosestToBeamLine getGenParticleStateClosestToBeamline( const edm::Event& iEvent, const edm::EventSetup& iSetup, const  reco::Candidate & part );

    // accessors for decay properties
    unsigned numDecays() { return decayModes_.size(); }
    int decayMode(unsigned i) { if (i<2) return decayModes_[i]; else return -999; }
    int motherId(unsigned i) { if (i<2) return motherId_[i]; else return -999; }
    int resId(unsigned i) { if (i<2) return resPid_[i]; else return -999; }
    double resPt(unsigned i) { if (i<2) return resPt_[i]; else return -999; }
    double resPz(unsigned i) { if (i<2) return resPz_[i]; else return -999; }

    double decayLength2D(unsigned i) { if (i<2) return decayLength2D_[i]; else return -999; }
    double decayLength3D(unsigned i) { if (i<2) return decayLength3D_[i]; else return -999; }
    double ctau(unsigned i) { if (i<2) return ctau_[i]; else return -999; }
    double pt(unsigned i) { if (i<2) return pt_[i]; else return -999; }
    double pz(unsigned i) { if (i<2) return pz_[i]; else return -999; }
    double E(unsigned i) { if (i<2) return E_[i]; else return -999; }
    double Et(unsigned i) { if (i<2) return Et_[i]; else return -999; }
    double daughterPdgId(unsigned i ) { if (i<4) return daughterPdgId_[i]; else return -999; }
    double daughterPt(unsigned i ) { if (i<4) return daughterPt_[i]; else return -999; }
    double daughterEta(unsigned i ) { if (i<4) return daughterEta_[i]; else return -999; }
    double daughterD0(unsigned i ) { if (i<4) return daughterD0_[i]; else return -999; }
    double daughterZ0(unsigned i ) { if (i<4) return daughterZ0_[i]; else return -999; }

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
