#include "WCSimTrueLight.hh"
#include "TObject.h"
#include "WCSimRecoDigit.hh"
#include "WCSimRecoObjectTable.hh"

ClassImp(WCSimTrueLight)

  WCSimTrueLight::WCSimTrueLight(Double_t x, Double_t y, Double_t z, Double_t t , Double_t theta, Double_t phi, Double_t pol1, Double_t pol2, Double_t wavelength)
{
  fX=x;
  fY=y;
  fZ=z;
  fT=t;
  
  fThet=theta;
  fPhi=phi;
  
  fP1=pol1;
  fP2=pol2;

  fWavelength=wavelength;

  WCSimRecoObjectTable::Instance()->NewDigit();
}

WCSimTrueLight::~WCSimTrueLight()
{
  WCSimRecoObjectTable::Instance()->DeleteDigit();
}

WCSimRecoDigit* WCSimTrueLight::Convert2Reco()
{
  //take the # per PMT to be 1 (not correct for true hits)
  
  WCSimRecoDigit* ndig = new WCSimRecoDigit(0,(this->GetX()),(this->GetY()),(this->GetZ()),(this->GetT()),1,1,(this->GetT()),1);

  return ndig;
}
