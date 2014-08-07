#ifndef WCSIMDATACLEANER_HH
#define WCSIMDATACLEANER_HH

#include "TObject.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"

#include <vector>

class WCSimRecoDigit;
class WCSimRecoClusterDigit;
class WCSimRecoCluster;

class WCSimDataCleaner : public TObject {

 public:  

  typedef enum EFilterConfig {
    kNone  = 0,
    kPulseHeight = 1,
    kPulseHeightAndNeighbours = 2,
    kPulseHeightAndClusters = 3, 
    kHitTime = 4//Erika
  } FilterConfig_t;

  static WCSimDataCleaner* Instance();

  static void Config(Int_t config);
  static void MinPulseHeight(Double_t min);
  static void MinHitTime(Double_t minT);//Erika
  static void MaxHitTime(Double_t maxT);//Erika
  static void NeighbourRadius(Double_t radius);
  static void NeighbourDigits(Int_t digits);
  static void ClusterRadius(Double_t radius);
  static void ClusterDigits(Int_t digits);
  static void TimeWindowN(Double_t windowN);
  static void TimeWindowC(Double_t windowC);

  static void PrintParameters();
  void RunPrintParameters();

  void SetConfig(Int_t config)               { fConfig = config; }
  void SetMinPulseHeight(Double_t min)       { fMinPulseHeight = min; }
  void SetMinHitTime(Double_t minT)       { fMinHitTime = minT; }//Erika
  void SetMaxHitTime(Double_t maxT)       { fMaxHitTime = maxT; }//Erika
  void SetNeighbourRadius(Double_t radius)   { fNeighbourRadius = radius; }
  void SetNeighbourDigits(Int_t digits)      { fMinNeighbourDigits = digits; }
  void SetClusterRadius(Double_t radius)     { fClusterRadius = radius; }
  void SetClusterDigits(Int_t digits)        { fMinClusterDigits = digits; }
  void SetTimeWindowNeighbours(Double_t windowN)        { fTimeWindowN = windowN; }
  void SetTimeWindowClusters(Double_t windowC)        { fTimeWindowC = windowC; }

  std::vector<WCSimRecoDigit*>* Run(std::vector<WCSimRecoDigit*>* digitlist);

  std::vector<WCSimRecoDigit*>* ResetDigits(std::vector<WCSimRecoDigit*>* digitlist);
  std::vector<WCSimRecoDigit*>* FilterDigits(std::vector<WCSimRecoDigit*>* digitlist);

  std::vector<WCSimRecoDigit*>* FilterAll(std::vector<WCSimRecoDigit*>* digitlist);
  std::vector<WCSimRecoDigit*>* FilterByPulseHeight(std::vector<WCSimRecoDigit*>* digitlist);
  std::vector<WCSimRecoDigit*>* FilterByHitTime(std::vector<WCSimRecoDigit*>* digitlist);//Erika
  std::vector<WCSimRecoDigit*>* FilterByNeighbours(std::vector<WCSimRecoDigit*>* digitlist);
  std::vector<WCSimRecoDigit*>* FilterByClusters(std::vector<WCSimRecoDigit*>* digitlist);

  std::vector<WCSimRecoCluster*>* RecoClusters(std::vector<WCSimRecoDigit*>* digitlist);

  //std::vector<WCSimRecoDigit*>* FilterGoldenDigits(std::vector<WCSimRecoDigit*>* digitlist);

 private:
  WCSimDataCleaner();
   ~WCSimDataCleaner();

  void Reset();
  
  //histos for cleaning parameters
  TFile* myCleaningFile;
  TH1D* histNeighb;
  TH1D* histDrsq;
  TH1D* histDt;
  TH1D* histClusters;

  // running mode
  Int_t fConfig;

  // cleaning parameters
  Double_t fMinPulseHeight;
  Double_t fMinHitTime;//Erika
  Double_t fMaxHitTime;//Erika
  Double_t fNeighbourRadius;
  Int_t fMinNeighbourDigits;
  Double_t fClusterRadius;
  Int_t fMinClusterDigits;
  Double_t fTimeWindowN;
  Double_t fTimeWindowC;
  Double_t fMinHitsPerCluster;

  // internal containers
  std::vector<Double_t> vNdigitsCluster;  
  std::vector<WCSimRecoCluster*> vClusterList;
  std::vector<WCSimRecoClusterDigit*> vClusterDigitList;
  std::vector<WCSimRecoClusterDigit*> vClusterDigitCollection;

  // vectors of filtered digits
  std::vector<WCSimRecoDigit*>* fFilterAll;
  std::vector<WCSimRecoDigit*>* fFilterByPulseHeight;
  std::vector<WCSimRecoDigit*>* fFilterByHitTime;//Erika
  std::vector<WCSimRecoDigit*>* fFilterByNeighbours;
  std::vector<WCSimRecoDigit*>* fFilterByClusters;

  // vectors of clusters
  std::vector<WCSimRecoCluster*>* fClusterList;

  ClassDef(WCSimDataCleaner,0)

};

#endif







