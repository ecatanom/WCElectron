#ifndef SANDBOXPHOTOTUBEGEO_HH
#define SANDBOXPHOTOTUBEGEO_HH

#include "TObject.h"
#include <iostream>

using namespace std;

class SandBoxPhotoTubeGeo : public TObject {

 public: 
  SandBoxPhotoTubeGeo(int pmttype, double pmtfpdiam);
  ~SandBoxPhotoTubeGeo();

  Int_t PMTtype();
  Double_t PMTdiameter();
  Double_t PMTwidth();

 private: 

  Int_t _pmttype;
  Double_t _pmtfootprint_diameter;

  ClassDef(SandBoxPhotoTubeGeo,0);

};

#endif
