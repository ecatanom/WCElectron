#ifndef WCSIMTRUELIGHT_HH
#define WCSIMTRUELIGHT_HH

#include "WCSimRecoDigit.hh"
#include "TObject.h"

class WCSimTrueLight : public TObject {

 public: 

  WCSimTrueLight(Double_t x, Double_t y, Double_t z, Double_t t , Double_t theta, Double_t phi, Double_t pol1, Double_t pol2, Double_t wavelenght);

  ~WCSimTrueLight();

  Double_t GetX() { return fX; }
  Double_t GetY() { return fY; }
  Double_t GetZ() { return fZ; }
  Double_t GetT() { return fT; }
  Double_t GetThet() { return fThet; }
  Double_t GetPhi() { return fPhi; }
  Double_t GetPol1() { return fP1; }
  Double_t GetPol2() { return fP2; }
  Double_t GetWavelenght() { return fWavelength; }

  WCSimRecoDigit* Convert2Reco();

 private: 

  Double_t fX;
  Double_t fY;
  Double_t fZ;
  Double_t fT;
  Double_t fThet;
  Double_t fPhi;

  Double_t fP1;
  Double_t fP2;

  Double_t fWavelength;

  Bool_t isScattered;

  ClassDef(WCSimTrueLight,0)

};

#endif
