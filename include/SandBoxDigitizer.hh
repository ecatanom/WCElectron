#ifndef SandBoxDigitizer_h
#define SandBoxDigitizer_h 1

#include "TRandom3.h"
#include <map>
#include <vector>
#include "WCSimRecoDigit.hh"
#include "WCSimRecoCluster.hh"
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
#include "TH1.h"

class WCSimRecoDigit;
class WCSimRecoEvent;

class SandBoxDigitizer
{
public:
  
  SandBoxDigitizer(WCSimRootTrigger* mTrigger, TString name);
  ~SandBoxDigitizer();
  
  void SetPMTSize(Float_t inputSize) {PMTSize = inputSize;}
  void ReInitialize() { DigiHitMap.clear(); TriggerTimes.clear(); }    
  int NumberOfGatesInThisEvent() { return TriggerTimes.size(); }
  
public:
  void SetPMT(Double_t tres, Double_t gate, Bool_t smearQ, Bool_t isgated);
  void SetMCP(Double_t tres, Double_t sres);
  void MakeHitsHistogram();
  void FindNumberOfGates();
  void FindNumberOfGatesFast();
  void DigitizeGatePMT(Int_t G);
  void DigitizeUngatedPMT();
  void DigitizeMCP();
  void Digitize();
  Double_t GetTriggerTime(int i) { return TriggerTimes[i];}

  TH1D* getdiagnostic(Int_t i);

  static WCSimRecoEvent* RecoEvent();
  static Double_t GetLongTime() { return LongTime;}
  static Double_t GetPMTDarkRate() { return PMTDarkRate;}
  static Double_t GetEventGateDown() { return eventgatedown;}
  static Double_t GetEventGateUp() { return eventgateup;}
private:
  //void ResetRecoEvent();
  static void Threshold(double& pe,int& iflag){
    double x = pe+0.1; iflag=0;
    double thr; double RDUMMY,err;
    if ( x<1.1) {
      thr = std::min(1.0,
		     -0.06374+x*(3.748+x*(-63.23+x*(452.0+x*(-1449.0+x*(2513.0
									+x*(-2529.+x*(1472.0+x*(-452.2+x*(51.34+x*2.370))))))))));
    } else {
      thr = 1.0;
    }
    TRandom3 arand(323242);
    RDUMMY = arand.Rndm();
    if (thr < RDUMMY) {
      pe = 0.0;
      iflag = 1;
    }
    else {
      err = arand.Gaus(0.0,0.03);
      /////      RandGauss::shoot(0.0,0.03);
      /////      call rngaus(0.0, 0.03, err);
      pe = pe+err;
    }
  }
  
  Double_t rn1pe();

  static const double offset; // hit time offset
  static const double pmtgate; // ns
  static const double eventgateup; // ns
  static const double eventgatedown; // ns
  static const double LongTime; // ns
  static const int GlobalThreshold; //number of hit PMTs within an <=200ns sliding window that decides the global trigger t0
  static const double PMTDarkRate; // kHz

  Int_t triggerhisto[20000]; // for finding t0
  Float_t RealOffset;  // t0 = offset corrected for trigger start
  Float_t MinTime;  // very first hit time
  Float_t PMTSize;

  Double_t _simpleTimeResolution;
  Double_t _simpleSpaceResolution;

  Bool_t _isPMT;
  Bool_t _smearCharge;
  Bool_t _smearTimeMCP;
  Bool_t _smearSpaceMCP;
  Bool_t _isGated;

  TRandom3* _theRand;

  TH1D* timehist;
  TH1D* tdiffhist;
  TH1D* sdiffhist;
  TH1D* qhist;

  std::vector<Double_t> TriggerTimes;
  std::map<Int_t, Int_t> GateMap;
  std::map<int,int> DigiHitMap; // need to check if a hit already exists..
  WCSimRootTrigger* _theTrigger;

  std::vector<WCSimRecoDigit*>  DigitsCollection;  //.....TX


};

#endif








