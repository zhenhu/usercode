#ifndef TREEDIPHOTONCANDIDATE_H
#define TREEDIPHOTONCANDIDATE_H

#include <TObject.h>

struct TreeDiphotonCandidate
{
  TreeDiphotonCandidate() :
    mass(-999.), vertex_x(-999), vertex_y(-999), vertex_z(-999), decayLength(-999.)
  {}

  // Mass of reconstructed candidate
  Float_t mass;

  // Position of recosntructed vertex
  Float_t vertex_x;
  Float_t vertex_y;
  Float_t vertex_z;

  // Reconstructed 2D decay length of candidate
  Float_t decayLength;

  ClassDef(TreeDiphotonCandidate, 1)
};
ClassImp(TreeDiphotonCandidate)

#endif
