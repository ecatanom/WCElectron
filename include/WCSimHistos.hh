#ifndef WCSIMHISTOS_HH
#define WCSIMHISTOS_HH

#include "TObject.h"
#include "TFile.h"
#include "TH1.h"
#include "TH3.h"
#include "TH3D.h"

class WCSimHistos {

 public: 

  WCSimHistos();
 ~WCSimHistos();
  
  static WCSimHistos* Instance();
   
  void MakeChrom3DHisto(Int_t Ndist,Int_t Ntime,std::string outFile); 
  
 private: 
 
  TH3D* hChromHist;
  TFile* rootfile;
  
  ClassDef(WCSimHistos,0)

};

#endif
