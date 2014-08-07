#ifndef WCSIMRECOEVENT_HH
#define WCSIMRECOEVENT_HH

#include "TObject.h"

#include <vector>
#include <map>

class WCSimRecoDigit;
class WCSimRecoVertex;
class WCSimRecoRing;

class WCSimRecoEvent : public TObject {

 public:

  static WCSimRecoEvent* Instance();

  void Reset();

  void SetHeader(Int_t run, 
                 Int_t event, 
                 Int_t trigger);

  Int_t GetRun() { return fRunNum; }
  Int_t GetEvent() { return fEventNum; }
  Int_t GetTrigger() { return fTriggerNum; }

  void AddDigit(Int_t tube, WCSimRecoDigit* digit);
  void AddRing(WCSimRecoRing* track);

  WCSimRecoDigit* GetDigitByTube(Int_t tube);
  Bool_t IsTubeHit(Int_t tube);

  WCSimRecoDigit* GetDigit(Int_t n);
  Int_t GetNDigits();  
  Int_t GetNFilterDigits();

  WCSimRecoRing* GetRing(Int_t n);
  Int_t GetNRings();

  WCSimRecoRing* GetPrimaryRing();

  void SetVertex(WCSimRecoVertex* vertex);
  WCSimRecoVertex* GetVertex();

  Double_t GetVtxX();
  Double_t GetVtxY();
  Double_t GetVtxZ();
  Double_t GetVtxTime();

  Double_t GetDirX(); 
  Double_t GetDirY(); 
  Double_t GetDirZ(); 

  Bool_t FoundVertex();
  Bool_t FoundDirection();
  Bool_t FoundRings();

  void SetFilterDone() { fIsFilterDone = 1; }
  Bool_t IsFilterDone() { return fIsFilterDone; }

  void SetVertexFinderDone() { fIsVertexFinderDone = 1; }
  Bool_t IsVertexFinderDone() { return fIsVertexFinderDone; }

  void SetRingFinderDone() { fIsRingFinderDone = 1; }
  Bool_t IsRingFinderDone() { return fIsRingFinderDone; }

  std::vector<WCSimRecoDigit*>* GetDigitList()       { return fDigitList; }
  std::vector<WCSimRecoRing*>*  GetRingList()        { return fRingList; }

  void PrintDigitList(const char* filename);
  void PrintFilterDigitList(const char* filename);

  void PrintEvent();

 private:
  WCSimRecoEvent();                  
  ~WCSimRecoEvent();

  void ClearDigits();
  void ClearRings();

  Int_t fRunNum;
  Int_t fEventNum;
  Int_t fTriggerNum;

  std::vector<WCSimRecoDigit*>* fDigitList;
  std::vector<WCSimRecoDigit*>* fFilterDigitList;
  std::vector<WCSimRecoRing*>*  fRingList;

  std::map<Int_t,WCSimRecoDigit*> fDigitMap;

  WCSimRecoVertex* fVertex;

  Bool_t fIsFilterDone;
  Bool_t fIsVertexFinderDone;
  Bool_t fIsRingFinderDone;

  ClassDef(WCSimRecoEvent,0)

};

#endif







