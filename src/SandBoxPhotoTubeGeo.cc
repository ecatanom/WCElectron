#include "SandBoxPhotoTubeGeo.hh"
#include <TMath.h>
#include <iostream>

using namespace std;

ClassImp(SandBoxPhotoTubeGeo)
    
  SandBoxPhotoTubeGeo::SandBoxPhotoTubeGeo(int pmttype, double pmtfpdiam)
{
  _pmttype=pmttype; // 0=circular 1=square
  _pmtfootprint_diameter=pmtfpdiam;
}

SandBoxPhotoTubeGeo::~SandBoxPhotoTubeGeo()
{ }

Int_t SandBoxPhotoTubeGeo::PMTtype() {return _pmttype;}

Double_t SandBoxPhotoTubeGeo::PMTdiameter(){return _pmtfootprint_diameter;}

Double_t SandBoxPhotoTubeGeo::PMTwidth()
{
  if( (_pmttype!=0) && (_pmttype!=1) ) {
    cout<<"Error!! PMT type must be either 0 (circular) or 1 (square)!!"<<endl;
    return 0.;
  }
  
  if(_pmttype==0) return _pmtfootprint_diameter;
  else if(_pmttype==1) return (_pmtfootprint_diameter/sqrt(2.)); // for a sqare pmt the footprint diameter is the diagonal of the square.

  return -555;
}

