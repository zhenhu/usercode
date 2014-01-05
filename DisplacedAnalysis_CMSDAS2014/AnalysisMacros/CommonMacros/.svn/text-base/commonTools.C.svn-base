#ifndef commonTools_C
#define commonTools_C

#include <math.h>
#include <TH1F.h>
#include <TLorentzVector.h>



// Creates a TLorentzVector from pt, eta, phi and mass
TLorentzVector convert(const double & pt, const double & eta, const double & phi, const double & mass)
{
  double px = pt*cos(phi);
  double py = pt*sin(phi);
  double tmp = 2*atan(exp(-eta));
  double pz = pt*cos(tmp)/sin(tmp);
  double E  = sqrt(px*px+py*py+pz*pz+mass*mass);

  return TLorentzVector(px,py,pz,E);
}

#endif
