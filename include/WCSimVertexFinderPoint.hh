#ifndef WCSIMVERTEXFINDERPOINT_HH
#define WCSIMVERTEXFINDERPOINT_HH

#include "TObject.h"
#include "TMinuit.h"
#include "TH1.h"
#include "TH3.h"

#include "WCSimRecoVertex.hh"
#include "WCSimRecoCluster.hh"

class WCSimRecoDigit;
class WCSimRecoEvent;

#include <vector>

class WCSimVertexFinderPoint : public TObject {

 public:
  static WCSimVertexFinderPoint* Instance(); //checked

  static void PrintParameters(); //checked
  void RunPrintParameters(); //checked
  void SetConeEdge(Double_t degrees) { fConeEdgeDegrees = degrees; }

  // Run Vertex Fitter (on RecoEvent) using Given Vertex as initial
  WCSimRecoVertex* RunPointFit1(WCSimRecoEvent* myEvent, Double_t vx, Double_t vy, Double_t vz);
  //WCSimRecoVertex* RunPointFit1(WCSimRecoEvent* myEvent, Double_t vx, Double_t vy, Double_t vz, Double_t mysign);
  //WCSimRecoVertex* RunPointFit1(WCSimRecoEvent* myEvent, Double_t vx, Double_t vy, Double_t vz, Double_t dirx, Double_t diry, Double_t dirz);

  // Calculate a Simple Vertex and Direction (from DigitList)
  WCSimRecoVertex* FindSimpleVertex(Double_t vx, Double_t vy, Double_t vz);
  WCSimRecoVertex* FindSimpleDirection(WCSimRecoVertex* vertex);

  // Fit the Vertex and Direction (from DigitList)
  //WCSimRecoVertex* FitPointVertex(std::vector<WCSimRecoDigit*>* digitlist, WCSimRecoVertex* vertex);
  WCSimRecoVertex* FitPointVertex(WCSimRecoEvent* myEvent, WCSimRecoVertex* myVertex);

  // Internal Methods: Run the Fits
  WCSimRecoVertex* FitPointVertex(WCSimRecoVertex* vertex);

  // Internal Methods: Run Fits with Minuit
  //WCSimRecoVertex* FitPointVertexWithMinuit(WCSimRecoVertex* vertex);
  WCSimRecoVertex* FitPointVertexWithMinuitMatt(WCSimRecoVertex* vertex);

  // Internal Methods: Point Vertex Figure of Merit
  void PointVertexChi2(Double_t vx, Double_t vy, Double_t vz, 
                        Double_t& vt, Double_t& chi2);
  void PointVertexChi2(Double_t& vt, Double_t& chi2);

  Double_t FOMCalc(WCSimRecoEvent* myEvent, Double_t vX, Double_t vY, Double_t vZ, Double_t vT, TH1D* myTimeRes);
  //Double_t FOMCalc(WCSimRecoEvent* myEvent, Double_t vX, Double_t vY, Double_t vZ, Double_t vT);
  Double_t AndyFOM(Double_t vX, Double_t vY, Double_t vZ, Double_t vT, TH1D* myTimeRes);
  void AndyFOM(Double_t vX, Double_t vY, Double_t vZ, Double_t vT, Double_t& chi2);
  void AndyFOM(WCSimRecoEvent* myEvent, Double_t vX, Double_t vY, Double_t vZ, Double_t vT, Double_t& chi2);

  // External Methods: Access To Residuals
  Int_t GetNDigits() { return fNdigits; }
  Double_t GetDigitX(Int_t idigit) { return fDigitX[idigit]; }
  Double_t GetDigitY(Int_t idigit) { return fDigitY[idigit]; }
  Double_t GetDigitZ(Int_t idigit) { return fDigitZ[idigit]; }
  Double_t GetDigitT(Int_t idigit) { return fDigitT[idigit]; }
  Double_t GetDigitQ(Int_t idigit) { return fDigitQ[idigit]; }
  Double_t GetDistAngle(Int_t idigit) { return fDistAngle[idigit]; }
  Double_t GetDistPoint(Int_t idigit) { return fDistPoint[idigit]; }
  Double_t GetDistTrack(Int_t idigit) { return fDistTrack[idigit]; }
  Double_t GetDistPhoton(Int_t idigit) { return fDistPhoton[idigit]; }
  Double_t GetDeltaT(Int_t idigit) { return fDeltaT[idigit]; }
  Double_t GetDeltaR(Int_t idigit) { return fDeltaR[idigit]; } 
  Double_t GetDeltaTrack(Int_t idigit) { return fDeltaTrack[idigit]; } 
  Double_t GetDeltaPhoton(Int_t idigit) { return fDeltaPhoton[idigit]; } 
  Double_t GetDelta(Int_t idigit) { return fDelta[idigit]; } 
  Double_t GetDeltaAngle(Int_t idigit) { return fDeltaAngle[idigit]; } 
  Double_t GetDeltaWeight(Int_t idigit) { return fDeltaWeight[idigit]; } 
  Double_t GetDeltaDeweight(Int_t idigit) { return fDeltaDeweight[idigit]; } 

  // External Methods: Access to Vertices
  WCSimRecoVertex* GetSimpleVertex()    { return fSimpleVertex; }
  WCSimRecoVertex* GetSimpleDirection() { return fSimpleDirection; }
  WCSimRecoVertex* GetPointVertex()     { return fPointVertex; }
  WCSimRecoVertex* GetPointDirection()  { return fPointDirection; }
  WCSimRecoVertex* GetExtendedVertex()  { return fExtendedVertex; }

  // Internal Methods
  void FillArrays(std::vector<WCSimRecoDigit*>* digitlist);
  void FillArrays(WCSimRecoEvent* myEvent);

  void PointResiduals(Double_t vx, Double_t vy, Double_t vz);  
  void FindSimpleTimeProperties(Double_t& vtime, Double_t& vtimerms);
  void FitTimeProperties(Double_t& vtime, Double_t& chi2);
  void TimePropertiesChi2(Double_t vtime, Double_t& chi2);
  void PenaltyChi2(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t& chi2);
  void PenaltyChi2Matt(Double_t vx, Double_t vy, Double_t vz, Double_t& chi2);
  void PenaltyChi2Matt2(Double_t vx, Double_t vy, Double_t vz, Double_t& chi2);
  void GlbPeakGeo(Double_t *trV, Double_t *dir, Double_t *ftV, Double_t &fopenangle, Double_t &fD, Double_t &fd);
  Double_t TrackL(Double_t vx, Double_t vy, Double_t vz, Double_t dirx, Double_t diry, Double_t dirz);
  Double_t Openagl(Double_t vx, Double_t vy, Double_t vz, Double_t dirx, Double_t diry, Double_t dirz, WCSimRecoEvent* myEvent);
  Double_t DistHit(Double_t vx, Double_t vy, Double_t vz, WCSimRecoEvent* myEvent);
  Double_t BotFrac(WCSimRecoEvent* myEvent);

  // Count Iterations
  Int_t GetIterations() { return fItr; }

  void point_vertex_itr()    { fPointVtxItr++; }
  void vertex_gaus_itr()    { fPointVtxItr++; }

  void point_vertex_reset_itr()    { fPointVtxItr = 0; }
  void vertex_gaus_reset_itr()    { fPointVtxItr = 0; }

  Int_t point_vertex_iterations()    { return fPointVtxItr; }
  Int_t vertex_gaus_iterations()    { return fPointVtxItr; }

  // Reset Everything
  void Reset(); //checked

 private:
  WCSimVertexFinderPoint(); //checked
  ~WCSimVertexFinderPoint(); //checked

  void Clear(); //checked

  Double_t fBaseFOM;
  Double_t fConeEdgeDegrees;

  Bool_t fPass;

  Int_t fNdigits;
  Double_t fMeanQ;
  Double_t fMeanRes;
  //Double_t fRadius = 2750.0;
  //Double_t fHeight = 3200.0;

  Double_t fInputVtxX;
  Double_t fInputVtxY;
  Double_t fInputVtxZ;
  Double_t fInputVtxTime;

  Double_t fInputDirX;
  Double_t fInputDirY;
  Double_t fInputDirZ;
  Double_t fInputDirAngle;

  Double_t fInputVtxFOM;
  
  Double_t* fDigitX;
  Double_t* fDigitY;
  Double_t* fDigitZ;
  Double_t* fDigitT;
  Double_t* fDigitQ;

  Double_t* fDistAngle;
  Double_t* fDistPoint;
  Double_t* fDistTrack;
  Double_t* fDistPhoton;

  Double_t* fDeltaT;
  Double_t* fDeltaR;
  Double_t* fDeltaTrack;
  Double_t* fDeltaPhoton;
  Double_t fsign;

  Double_t* fDelta;
  Double_t* fDeltaAngle;
  Double_t* fDeltaWeight;
  Double_t* fDeltaDeweight;

  Double_t* fAngle;
  Double_t* fAngleWeight;
  Double_t* fAngleDeweight;

  WCSimRecoVertex* fSimpleVertex;
  WCSimRecoVertex* fSimpleDirection;
  WCSimRecoVertex* fPointVertex;
  WCSimRecoVertex* fPointDirection;
  WCSimRecoVertex* fExtendedVertex;

  TMinuit* fMinuitPointVertex;
  TMinuit* fMinuitPointDirection;
  TMinuit* fMinuitExtendedVertex; 
  TMinuit* fMinuitExtendedVertexNested;
  TMinuit* fMinuitTimeFit;

  Int_t fItr;
  Int_t fPointVtxItr;
  Int_t fPointDirItr;
  Int_t fExtendedVtxItr;

  std::vector<WCSimRecoVertex*> vVertexList;

 public:  

  Double_t fVtxX;
  Double_t fVtxY;
  Double_t fVtxZ;
  Double_t fVtxTime;

  Double_t fDirX;
  Double_t fDirY;
  Double_t fDirZ;
  Double_t fDirAngle;
  Double_t ffakex;
  Double_t ffakey;
  Double_t ffakez;

  Double_t fVtxFOM;

  ClassDef(WCSimVertexFinderPoint,0)

};

#endif







