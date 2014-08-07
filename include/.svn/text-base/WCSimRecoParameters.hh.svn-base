#ifndef WCSIMRECOPARAMETERS_HH
#define WCSIMRECOPARAMETERS_HH

#include "TObject.h"

class WCSimRecoParameters : public TObject {

 public:
  static WCSimRecoParameters* Instance();

  static void UseSimpleParameters();
  static void UseSimpleTimeResolution();
  static void UseSimpleTimeSlew();
  static void UseSimpleRefractiveIndex();

  static Double_t TimeResolution(Double_t Q);
  static Double_t TimeSlew(Double_t Q);
  static Double_t RefractiveIndex(Double_t r);

  static void PrintParameters();
  void RunPrintParameters();

  void SetSimpleTimeResolution() { fUseSimpleTimeResolution = 1; }
  Bool_t SimpleTimeResolution() { return fUseSimpleTimeResolution; }

  void SetSimpleTimeSlew() { fUseSimpleTimeSlew = 1; }
  Bool_t SimpleTimeSlew() { return fUseSimpleTimeSlew; }

  void SetSimpleRefractiveIndex(){ fUseSimpleRefractiveIndex = 1; }
  Bool_t SimpleRefractiveIndex() { return fUseSimpleRefractiveIndex; }

  Double_t GetTimeResolution(Double_t Q);
  Double_t GetTimeSlew(Double_t Q);
  Double_t GetRefractiveIndex(Double_t r);  

  Double_t GetSimpleTimeResolution(Double_t Q);
  Double_t GetSimpleTimeSlew() { return 0.0; }
  Double_t GetSimpleRefractiveIndex() { return 1.33; }

 private:
  WCSimRecoParameters();
  ~WCSimRecoParameters();

  Bool_t fUseSimpleTimeResolution;
  Bool_t fUseSimpleTimeSlew;
  Bool_t fUseSimpleRefractiveIndex;

  ClassDef(WCSimRecoParameters,0)

};

#endif







