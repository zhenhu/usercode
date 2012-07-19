#ifndef GENPARTICLE_H
#define GENPARTICLE_H

#include <TObject.h>
#include <TLorentzVector.h>

/**
 * Simple class used to save genParticles information in a root tree.
 */

struct GenParticle : public TObject
{
  GenParticle() :
    pt(-999), eta(-999), phi(-999), pdgId(-999), motherPdgId(-999), ctau(-999), decayLength2D(-999), decayLength3D(-999)
  {}
  Float_t pt;
  Float_t eta;
  Float_t phi;
  Int_t pdgId;
  Int_t motherPdgId;
  Float_t ctau;
  Float_t decayLength2D;
  Float_t decayLength3D;

  ClassDef(GenParticle, 1)
};
ClassImp(GenParticle)

#endif // GENPARTICLE_H
