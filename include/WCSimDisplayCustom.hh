#ifndef WCSIMDISPLAYCUSTOM_HH
#define WCSIMDISPLAYCUSTOM_HH

#include "TObject.h"
#include "TCanvas.h"
#include "TButton.h"
#include "TChain.h"
#include "TString.h"
#include "TStyle.h"
#include "TROOT.h"

#include <vector>

class WCSimDisplay;
class WCSimReco;

class WCSimRecoEvent;
class WCSimTrueEvent;

class WCSimRootTrigger;
class WCSimRootEvent;
class WCSimRootGeom;

class WCSimDisplayCustom : public TObject
{
 public:

  WCSimDisplayViewer();
  virtual ~WCSimDisplayViewer();

  void RootStyle();
  void Initialize();
  void BuildDisplay();
  void UpdateDisplay(Int_t entry);
  void DisplayEvent(Int_t entry);
  void DisplayRecoClusters(Bool_t yesno = 1){ fDisplayRecoClusters = yesno; }
  void DisplayRecoEvent(Bool_t yesno = 1){ fDisplayRecoEvent = yesno; }
  void DisplayTrueEvent(Bool_t yesno = 1){ fDisplayTrueEvent = yesno; }
  void ApplyCuts(){ fApplyCuts = 1; }
  void SetPulseHeightCut(Double_t cut);
  void PrintGIF(Bool_t yesno = 1);
  void PrintEPS(Bool_t yesno = 1);

//   void PrintDisplayList();

 private:

  TStyle* fRootStyle;

  Int_t fCounter;

  WCSimReco* fReco;
  WCSimRecoEvent* fRecoEvent;
  WCSimTrueEvent* fTrueEvent;

  Int_t fRunNum;
  Int_t fEventNum;
  Int_t fTriggerNum;

  Bool_t fDisplayRecoClusters;
  Bool_t fDisplayRecoEvent;
  Bool_t fDisplayTrueEvent;
  Bool_t fApplyCuts;

  Double_t fPulseHeightCut;

  Bool_t fPrintGIF;
  Bool_t fPrintEPS;

  Bool_t fDisplayReady;

  std::vector<const char*> fDisplayNameList;
  std::vector<WCSimDisplay*> fDisplayList;

  ClassDef(WCSimDisplayCustom,0)
};

#endif 

