#include "TreeProducer/TreeProducer/interface/GenEventProperties.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" 
#include "SimDataFormats/GeneratorProducts/interface/PdfInfo.h"
// #include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <algorithm>

GenEventProperties::GenEventProperties()
{
  // initialize data members with unphysical values
  decayModes_.clear();
  motherId_.clear();
  decayLength2D_.clear();
  decayLength3D_.clear();
  ctau_.clear();
  daughterPt_.clear();
  daughterD0_.clear();
  nvtx_m1_     = -999;
  nvtx_0_      = -999;
  nvtx_p1_     = -999;
  nvtx_true_   = -999;
  pdf_id_[0]   = -999;
  pdf_id_[1]   = -999;
  pdf_x_[0]    = -999;
  pdf_x_[1]    = -999;
  pdf_xPDF_[0] = -999;
  pdf_xPDF_[1] = -999;
  pdf_scale_   = -999;
}

GenEventProperties::DecayLengthAndType GenEventProperties::getDecayLengthAndType(const reco::GenParticle & part)
{
  reco::Candidate::Point productionVertex = part.vertex();
  // decay products and decay vertex
  reco::Candidate::Point decayVertex=productionVertex;
  const reco::Candidate* daughter1 = 0;
  const reco::Candidate* daughter2 = 0;
  bool foundDaughter1 = false;
  int decay_pid=0;
  for (unsigned i=0; i<part.numberOfDaughters(); i++) {
    const reco::Candidate* daughter = part.daughter(i);

    int pid = abs(daughter->pdgId());
    if (pid==11 || pid==13 || pid==15 || pid==1 || pid==2 || pid==3 || pid==4 || pid==5) {
      decay_pid=pid;

      // note that original MC signal particle and decay products
      // are in documentation lines (Pythia status 3) and the actual
      // decay length is only available in the actual decay tree
      // (Pythia status 2). The corresponding status 2 particle for each
      // status 3 particle is referenced by a daughter link.
      if (daughter->numberOfDaughters()>0) {
        daughter=daughter->daughter(0);
        decayVertex=daughter->vertex();
      }


      if (!foundDaughter1) daughter1 = daughter;
      else daughter2=daughter;
      foundDaughter1=true;
    }
  }

  // Now have both daughters
  std::vector< const reco::Candidate* > daughters;
  daughters.push_back(daughter1);
  daughters.push_back(daughter2);

  double distance = (decayVertex-productionVertex).r();
  return DecayLengthAndType(decay_pid,
                            fabs(part.pdgId()),
                            (decayVertex-productionVertex).rho(),
                            distance,
                            distance*part.p4().M()/part.p4().P(),
                            daughters);
}


// FIXME: this only takes the signalPDGId, it will need to search also for other daughters of the same mother.
GenEventProperties::GenEventProperties(const edm::Event& iEvent,
                                       const edm::EventSetup& iSetup,
                                       std::vector<int> signalPDGId,
                                       edm::InputTag& generatorTag,
                                       edm::InputTag& pileupTag,
                                       edm::InputTag& genEventInfoTag)
{
  // initialize data members with unphysical values
  decayModes_.clear();
  motherId_.clear();
  decayLength2D_.clear();
  decayLength3D_.clear();
  ctau_.clear();
  nvtx_m1_     = -999;
  nvtx_0_      = -999;
  nvtx_p1_     = -999;
  nvtx_true_   = -999;
  pdf_id_[0]   = -999;
  pdf_id_[1]   = -999;
  pdf_x_[0]    = -999;
  pdf_x_[1]    = -999;
  pdf_xPDF_[0] = -999;
  pdf_xPDF_[1] = -999;
  pdf_scale_   = -999;

  // look for long-lived particles and evaluate decay length
  edm::Handle<edm::View<reco::GenParticle> > mcParticles;
  iEvent.getByLabel(generatorTag,mcParticles);
  if (mcParticles.failedToGet()) return;

  for (unsigned imc=0; imc<mcParticles->size(); imc++) {

    if ( find( signalPDGId.begin(), signalPDGId.end(), abs( (*mcParticles)[imc].pdgId() ) ) != signalPDGId.end() &&
        (*mcParticles)[imc].status()==3 ) {
      // long-lived particle and its production vertex
      const reco::GenParticle part=(*mcParticles)[imc];

      DecayLengthAndType dlt(getDecayLengthAndType(part));

//      std::cout << "----> Mother" << std::endl;
//      std::cout << "Pdg id : " << dlt.motherPid << std::endl;
//      std::cout << "Decay mode : " << dlt.decayPid << std::endl;
//      std::cout << "3D decay length : " << dlt.decayLength3D << std::endl;
//      std::cout << "Daughter 1" << std::endl;
//      std::cout << "Pdg id : " << dlt.daughters[0]->pdgId() << std::endl;
//      std::cout << "Vertex : " << dlt.daughters[0]->vertex() << std::endl;
//      std::cout << "Daughter 2" << std::endl;
//      std::cout << "Pdg id : " << dlt.daughters[1]->pdgId() << std::endl;
//      std::cout << "Vertex : " << dlt.daughters[1]->vertex() << std::endl;

      for ( int iDau=0;iDau<2;++iDau) {
        daughterPt_.push_back(dlt.daughters[iDau]->pt());

        // Get d0 for this daughter genParticle
        daughterD0_.push_back( getGenParticleD0( iEvent, iSetup, *(dlt.daughters[iDau]) ) );
      }

      decayModes_.push_back(dlt.decayPid);
      motherId_.push_back(dlt.motherPid);
      decayLength2D_.push_back(dlt.decayLength2D);
      decayLength3D_.push_back(dlt.decayLength3D);
      ctau_.push_back(dlt.ctau);
    }
  }

  // pile-up information (if any)
  // Storing "true" number of interactions - for 2012 PU, maybe some 2011
  // Also store number of PU interactions in different bunch crossings
  // In case we need to do PU reweighting when running over 2011 data+MC
  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel(pileupTag, PupInfo);
  if (!PupInfo.failedToGet()) {
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    for (PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
      unsigned npv = PVI->getPU_NumInteractions();
      int BX = PVI->getBunchCrossing();
      if (BX == -1) nvtx_m1_=npv;
      if (BX == 0) {
        nvtx_0_=npv;
        // Store true number of
        nvtx_true_ = PVI->getTrueNumInteractions();
      }
      if (BX == 1) nvtx_p1_=npv;
    }
  }
  
  // PDF information (if any)
  edm::Handle<GenEventInfoProduct>  genEventInfo;
  iEvent.getByLabel(genEventInfoTag, genEventInfo);
  if (!genEventInfo.failedToGet()) {
    if (genEventInfo->hasPDF()) {
      const gen::PdfInfo* pdf = genEventInfo->pdf();
      pdf_id_[0]=pdf->id.first;
      pdf_id_[1]=pdf->id.second;
      pdf_x_[0]=pdf->x.first;
      pdf_x_[1]=pdf->x.second;
      pdf_xPDF_[0]=pdf->xPDF.first;
      pdf_xPDF_[1]=pdf->xPDF.second;
      pdf_scale_=pdf->scalePDF;
    }
  }
}

double GenEventProperties::getGenParticleD0( const edm::Event& iEvent, const edm::EventSetup& iSetup, const  reco::Candidate & part ) {
  // Get the magnetice field
  edm::ESHandle<MagneticField> theMagField;
  iSetup.get<IdealMagneticFieldRecord>().get(theMagField);

  // get beamspot
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByLabel ("offlineBeamSpot", beamSpotHandle);

  // Make FreeTrajectoryState of this gen particle
  FreeTrajectoryState fts(GlobalPoint(part.vx(),part.vy(),part.vz()),
                          GlobalVector(part.px(),part.py(),part.pz()),
                          part.charge(),
                          theMagField.product());

  // Get trajectory closest to beam line
  TSCBLBuilderNoMaterial tscblBuilder;
  TrajectoryStateClosestToBeamLine tsAtClosestApproach = tscblBuilder(fts,*beamSpotHandle);

  // Get helix parameters at this point
  GlobalPoint v = tsAtClosestApproach.trackStateAtPCA().position();
  GlobalVector p = tsAtClosestApproach.trackStateAtPCA().momentum();

  double d0 = (-v.x()*sin(p.phi())+v.y()*cos(p.phi()));
  return d0;
}
