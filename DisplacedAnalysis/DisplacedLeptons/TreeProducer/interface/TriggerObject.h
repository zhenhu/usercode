#ifndef TRIGGEROBJECT_H
#define TRIGGEROBJECT_H

#include <TObject.h>
#include <TLorentzVector.h>
#include <string>

struct TriggerObject : public TObject
{
  TriggerObject() :
    pt(-999), eta(-999), phi(-999)
  {}
  TriggerObject( const double & inPt, const double & inEta, const double & inPhi ) :
    pt(inPt), eta(inEta), phi(inPhi)
  {}

  Float_t pt;
  Float_t eta;
  Float_t phi;
  std::string triggerName;

  ClassDef(TriggerObject, 1)
};
ClassImp(TriggerObject)

#endif // TRIGGEROBJECT_H
