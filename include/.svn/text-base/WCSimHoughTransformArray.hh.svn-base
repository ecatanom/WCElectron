#ifndef WCSIMHOUGHTRANSFORMARRAY_HH
#define WCSIMHOUGHTRANSFORMARRAY_HH

#include "TObject.h"

#include <vector>

class WCSimHoughTransform;

class WCSimHoughTransformArray : public TObject {

 public:
  WCSimHoughTransformArray( Int_t bins, Double_t min, Double_t max,
                            Int_t xbins, Int_t ybins );
  ~WCSimHoughTransformArray();

  void BuildArray( Int_t bins, Double_t min, Double_t max,
                   Int_t xbins, Int_t ybins );
  void PrintArray();

  Int_t GetBins(){ return fConeAngleBins; }
  Int_t GetConeAngleBins(){ return fConeAngleBins; }
  Double_t GetConeAngleMin(){ return fConeAngleMin; }
  Double_t GetConeAngleMax(){ return fConeAngleMax; }
  Double_t GetConeAngle(Int_t bin);

  Double_t GetAngle(Int_t bin);
  Int_t FindBin(Double_t angle);

  WCSimHoughTransform* GetHoughTransform(Int_t nAngle);

  void FindPeak(Int_t& bin, Double_t& height);
  void FindPeak(Double_t& phi, Double_t& costheta, Double_t& angle, Double_t& height);
  void FindPeak(Double_t& hx, Double_t& hy, Double_t& hz, Double_t& angle, Double_t& height);

  void Reset();

 private:

  void DeleteArray();
  
  Int_t fHoughX;
  Int_t fHoughY;
  Int_t fConeAngleBins;
  Double_t fConeAngleMin;
  Double_t fConeAngleMax;

  std::vector<WCSimHoughTransform*> fHoughArray;

  ClassDef(WCSimHoughTransformArray,0)
};

#endif
