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
  pt_.clear();
  pz_.clear();
  E_.clear();
  Et_.clear();
  daughterPt_.clear();
  daughterEta_.clear();
  daughterD0_.clear();
  daughterZ0_.clear();
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

GenEventProperties::DecayLengthAndType GenEventProperties::getDecayLengthAndType(const reco::Candidate & part)
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

    if (pid==11 || pid==13 || pid==1 || pid==2 || pid==3 || pid==4 || pid==5) {
      decay_pid=pid;


      // Look for final state particle
      while ( daughter->numberOfDaughters()>0) {
        daughter=daughter->daughter(0);
        decayVertex=daughter->vertex();
      }

      // note that original MC signal particle and decay products
      // are in documentation lines (Pythia status 3) and the actual
      // decay length is only available in the actual decay tree
      // (Pythia status 2). The corresponding status 2 particle for each
      // status 3 particle is referenced by a daughter link.
      //      if (daughter->numberOfDaughters()>0) {
      //        daughter=daughter->daughter(0);
      //        decayVertex=daughter->vertex();
      //      }


      if (!foundDaughter1) {
        daughter1 = daughter;
      }
      else {
        daughter2=daughter;
      }
      foundDaughter1=true;
    }
  }

  // Now have both daughters
  std::vector< const reco::Candidate* > daughters;
  daughters.push_back(daughter1);
  daughters.push_back(daughter2);

  // Look for mother (resonance like H or squark)
  double resonancePid = 0;
  double resonancePt = -1;
  double resonancePz = -1;

  if ( part.numberOfMothers() > 0 ) {
    const reco::Candidate* mother = part.mother( 0 ) ;
    resonancePid = mother->pdgId();
    resonancePt = mother->pt();
    resonancePz = mother->pz();
  }

  double distance = (decayVertex-productionVertex).r();
  return DecayLengthAndType(decay_pid,
      fabs(part.pdgId()),
      (decayVertex-productionVertex).rho(),
      distance,
      distance*part.p4().M()/part.p4().P(),
      part.pt(),
      part.pz(),
      part.energy(),
      part.et(),
      productionVertex.x(),productionVertex.y(),productionVertex.z(),
      resonancePid, resonancePt, resonancePz,
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
  pt_.clear();
  pz_.clear();
  E_.clear();
  Et_.clear();
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
        ( ( fabs((*mcParticles)[imc].pdgId()) != 15 && (*mcParticles)[imc].status()==3 ) ||
            ( fabs((*mcParticles)[imc].pdgId()) == 15 && (*mcParticles)[imc].status()==2 ) ) ) {

      // long-lived particle and its production vertex
      const reco::GenParticle part=(*mcParticles)[imc];

      // Ignore Z that decay to tau
      if ( (*mcParticles)[imc].pdgId() == 23 ) {
        bool zToTau=false;
        for (unsigned i=0; i<(*mcParticles)[imc].numberOfDaughters(); i++) {
          if ( fabs((*mcParticles)[imc].daughter(i)->pdgId()) == 15 ) {
            zToTau = true;
          }
        }
        if ( zToTau ) continue;
      }

      DecayLengthAndType dlt(getDecayLengthAndType(part));

      for ( int iDau=0;iDau<2;++iDau) {
        if ( dlt.daughters[iDau] == 0 ) continue;
        daughterPt_.push_back(dlt.daughters[iDau]->pt());
        daughterPdgId_.push_back(dlt.daughters[iDau]->pdgId());

        // Extrapolate gen particle back to beam line
        // Can then be compared to tracks
        try{
          TrajectoryStateClosestToBeamLine tsAtClosestApproach = getGenParticleStateClosestToBeamline( iEvent, iSetup, *(dlt.daughters[iDau]));
          GlobalVector p = tsAtClosestApproach.trackStateAtPCA().momentum();
          GlobalPoint v = tsAtClosestApproach.trackStateAtPCA().position();
          daughterEta_.push_back(p.eta());
          // Get d0 for this daughter genParticle
          daughterD0_.push_back( (-v.x()*sin(p.phi())+v.y()*cos(p.phi())) );
          daughterZ0_.push_back( v.z() - (v.x()*cos(p.phi()) + v.y()*sin(p.phi())) / tan(p.theta()) );
        }
        catch(cms::Exception& e){
          daughterEta_.push_back(-999);
          daughterD0_.push_back(-999);
          daughterZ0_.push_back(-999);
        };
      }

      decayModes_.push_back(dlt.decayPid);
      motherId_.push_back(dlt.motherPid);
      decayLength2D_.push_back(dlt.decayLength2D);
      decayLength3D_.push_back(dlt.decayLength3D);
      ctau_.push_back(dlt.ctau);
      pt_.push_back(dlt.pt);
      pz_.push_back(dlt.pz);
      E_.push_back(dlt.E);
      Et_.push_back(dlt.Et);
      resPid_.push_back(dlt.resPid);
      resPt_.push_back(dlt.resPt);
      resPz_.push_back(dlt.resPz);
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

TrajectoryStateClosestToBeamLine GenEventProperties::getGenParticleStateClosestToBeamline( const edm::Event& iEvent, const edm::EventSetup& iSetup, const  reco::Candidate & part ) {
  // Get the magnetice field
  edm::ESHandle<MagneticField> theMagField;
  iSetup.get<IdealMagneticFieldRecord>().get(theMagField);

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

  return tsAtClosestApproach;

}
