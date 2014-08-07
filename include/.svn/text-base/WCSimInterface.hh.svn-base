#ifndef WCSIMINTERFACE_HH
#define WCSIMINTERFACE_HH

#include "TObject.h"
#include "TChain.h"

#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

#include <vector>
//#include "TRandom.h"
//#include "TRandom3.h"

class WCSimRecoDigit;
class WCSimRecoEvent;

class WCSimTrueTrack;
class WCSimTrueEvent;

class WCSimInterface : public TObject {

 public: 
  static WCSimInterface* Instance();

  static Bool_t TouchData();
  static Bool_t TouchEvent();

  static void LoadData(const char* file);
  static void LoadEvent(Int_t ievent);
  static Int_t GetNumEvents();

  static WCSimRootTrigger* FilterTrigger(WCSimRootEvent* event);

  static WCSimTrueEvent* TrueEvent();
  static WCSimRecoEvent* RecoEvent();
  
  static WCSimRootEvent* WCSimEvent();
  static WCSimRootTrigger* WCSimTrigger();

  static Int_t GetRunNumber();
  static Int_t GetEventNumber();
  static Int_t GetTriggerNumber();

  static void Reset();

  static void SetEnergyThreshold(Double_t input_mev);
  static void SetRangeThreshold(Double_t input_cm);
  static void SetToUseTrueHits();
  void SmearTrueHits(Double_t ts) { fTimeSmear=ts; fsmeartruth=true; }
  void UsePMTPosition() { fPMTspace=true; }

  void SetTrueEnergyThreshold(Double_t ke) { fEnergyThreshold = ke; }
  void SetTrueRangeThreshold(Double_t ds) { fRangeThreshold = ds; }
  void SetToTrueHits() { fusetruth=true; }
  void SetToMCP() { fuseMCP=true; }
  void SetToGated() { fuseGate=true; }
  Bool_t IsTrueHits(){ return fusetruth; }
  Double_t GetPMTResolution(){ return fTimeSmear; } 

  WCSimRootEvent* GetWCSimEvent(){ return fEvent; }
  WCSimRootTrigger* GetWCSimTrigger(){ return fTrigger; }

  WCSimRootEvent* GetWCSimEvent(Int_t ievent);
  WCSimRootTrigger* GetWCSimTrigger(Int_t ievent);

  void AddFile(const char* file);
  void BuildEvent(Int_t ievent);
  Bool_t CheckEvent();
  Int_t GetEntries();

  void ResetForNewSample();

 private:
  WCSimInterface();
  ~WCSimInterface();

  void BuildTrueEvent(WCSimRootTrigger* event);
  void BuildRecoEvent(WCSimRootTrigger* event);
  void BuildRecoEvent(WCSimRootTrigger* event, bool usetruehits);

  void ResetTrueEvent();
  void ResetRecoEvent();

  std::vector<WCSimRecoDigit*>* fDigitList;
  std::vector<WCSimTrueTrack*>* fTrackList;

  TChain* fChain;
  TChain* fChainGeom;
  //TRandom3* timeRand;

  WCSimRootTrigger* fTrigger0;
  WCSimRootTrigger* fTrigger;
  WCSimRootEvent* fEvent;
  WCSimRootGeom* fGeometry;

  Double_t fEnergyThreshold;
  Double_t fRangeThreshold;
  Bool_t fusetruth;
  Bool_t fsmeartruth;
  Bool_t fPMTspace;
  Bool_t fuseMCP;
  Bool_t fuseGate;
  Double_t fTimeSmear;

  Int_t fCounter;

  ClassDef(WCSimInterface,0)
    
};

#endif
