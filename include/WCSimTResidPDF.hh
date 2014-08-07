#ifndef WCSIMTRESIDPDF_HH
#define WCSIMTRESIDPDF_HH

#include "TObject.h"
#include "TH1.h"
#include "TH3.h"
#include "TH3D.h"
#include "TFile.h"
#include "TDirectory.h"

#include <iostream>
#include <vector>

class WCSimTResidPDF : public TObject {

 public: 

  WCSimTResidPDF();
  
  static WCSimTResidPDF* Instance();
   
  void SetResolutionParameters(Double_t PMTRes);
  void SetParamPDF(double peakval, double width, double gauswidth);
  void SetLandauGaussPDF(double peakval, double width, double gauswidth);
  TH1D* MakeChromPeakPDF(Double_t thedistance, Double_t pmtres); //get the most probable wavelegth for the one hit  
  Double_t MakeChromPeakPDF(Double_t timeResid, Double_t thedistance, Double_t pmtres);
  Double_t MakeChromPeakPDF(Double_t timeResid, Double_t thedistance, Double_t pmtres, Double_t thedistancemu);
  Double_t MakeChromPeakPDF(Double_t timeResid, Double_t distance, Double_t res, Double_t fmin, Double_t fmax);
  Double_t MakeChromPeakPDF(Double_t timeResid, Double_t distance, Double_t res, Int_t op1, Int_t op2, Int_t op3);
  Double_t MakeChromPeakPDFhaha(Double_t timeResid, Double_t distance, Double_t res);
  Double_t MakeChromFuncPDF(Double_t timeResid, Double_t distance, Double_t decayTime);
  Double_t MakeChromLandauPDF(Double_t timeResid, Double_t distance, Double_t res);
  Double_t MakeChromDecayPDF(Double_t timeResid, Double_t distance, Double_t res);
  void MakeGaussPeakPDF(double pmtres);
  void MakeNoisePDF();
  void MakeTotalPDF(double peakfrac, double noisefrac, double scatfrac);

  TH1D*    GetPDFhist(int which);  // returns PDF hist
  Double_t DoSimpleComparison(double tresid);
  Double_t DoParamComparison(double tresid);
  Double_t DoLandauGaussComparison(double tresid);
  Double_t DoFullComparison(double tresid);
  Double_t EvalTResidPDF(double tresidval);
  Double_t GetChromProbTable(Double_t timeResid, Double_t distance, Double_t resolution); //from table
  Double_t GetChromProbHist(Double_t timeResid, Double_t distance, Double_t resolution); //from 3D histogram
  Double_t GetDistanceFromWall(Double_t Cangle, Double_t Ltrack, Double_t phi, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ,  Double_t DetH, Double_t DetR);  
  TH1D* GetDistanceArray(Double_t thebeta, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ,  Double_t DetH, Double_t DetR);

  //vectors which store the values from the WaterModel for each lambda
  std::vector<Double_t> veloLg;
  std::vector<Double_t> initLg;
  std::vector<Double_t> absLg;
  std::vector<Double_t> sctLg;
  std::vector<Double_t> qeLg; 
  
  Double_t minLambda; 
  Double_t maxLambda; 
  Double_t stepLambda;

  TH1D* hPeakPDF;  // peak histo
  TH1D* hNoisePDF; // noise histo 
  TH1D* hScatPDF;  // scatter histo 
  TH1D* hTotalPDF; // peak + noise + scatter histo, i.e. total
  TH1D* theDistanceHist; // calculated distribution of distance to det wall
  TH1D* theLhist;  // simulated distribution of Lmuons
  

  //static Double_t valueChrom[500][300]; //store all the chromPDF values obtained for a number of distances and time residuals

 private: 
  //WCSimTResidPDF();
  ~WCSimTResidPDF();

  void MakeTablePDF();

  //WCSimWaterModel *_thewm;
  Double_t _pmtres;
  Double_t _smearfactor;
  Double_t valueChrom[500][300][60]; //store all the chromPDF values obtained for a number of distances and time residuals
  TFile* fileHisto;
  TH3D* hChromPDF3D;
  

  ClassDef(WCSimTResidPDF,0)

};

#endif
