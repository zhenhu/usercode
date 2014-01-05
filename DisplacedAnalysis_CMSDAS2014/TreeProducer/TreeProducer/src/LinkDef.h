#ifndef LINKDEF_H
#define LINKDEF_H

#include "TreeProducer/TreeProducer/interface/Candidates.h"
#include "TreeProducer/TreeProducer/interface/TreeLepton.h"
#include "TreeProducer/TreeProducer/interface/TreeDipseudoLeptonCandidate.h"
#include "TreeProducer/TreeProducer/interface/TreePhoton.h"
#include "TreeProducer/TreeProducer/interface/TreeDiphotonCandidate.h"

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ class Candidates+;
// #pragma link C++ class std::vector<std::string>+;
#pragma link C++ class TreeLepton+;
#pragma link C++ class TreeDipseudoLeptonCandidate+;
#pragma link C++ class TreePhoton+;
#pragma link C++ class TreeDiphotonCandidate+;
#endif

#endif // LINKDEF_H
