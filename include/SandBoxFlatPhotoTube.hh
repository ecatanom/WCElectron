#ifndef SANDBOXFLATPHOTOTUBE_HH
#define SANDBOXFLATPHOTOTUBE_HH

#include "SandBoxPhotoTubeModel.hh"
#include "TRandom3.h"
#include "WCSimRecoDigit.hh"
#include "TObject.h"
#include "WCSimRecoCluster.hh"
#include "WCSimTrueLightCluster.hh"

class SandBoxFlatPhotoTube : public SandBoxPhotoTubeModel {

 public: 

  SandBoxFlatPhotoTube();
  SandBoxFlatPhotoTube(Int_t dtype, Double_t constQE);
  ~SandBoxFlatPhotoTube();

  WCSimRecoCluster* GetSmeared(WCSimRecoCluster* theHits, vector<double> pmtcenter);
  WCSimRecoCluster* GetSmeared(WCSimTrueLightCluster* theHits, vector<double> pmtcenter);

  WCSimRecoCluster* MCPSmear(WCSimRecoCluster* theHits, vector<double> pmtcenter);
  WCSimRecoCluster* PMTSmear(WCSimRecoCluster* theHits, vector<double> pmtcenter);

  WCSimRecoDigit* SmearSpace(WCSimRecoDigit* aHit);
  WCSimRecoDigit* SmearTime(WCSimRecoDigit* aHit);
  WCSimRecoDigit* SmearSpaceTime(WCSimRecoDigit* aHit);
  WCSimRecoDigit* SmearCharge(WCSimRecoDigit* aHit);


 private: 

  TRandom3 *spaceRand,*timeRand,*chargeRand,*efficRand;

  Int_t _detectortype;
  Bool_t _combinehitsintime;

  Double_t _constQE;
  Double_t _QEcurve;
  Double_t _spacesmear;
  Double_t _timesmear;
  Double_t _chargesmear;

  Double_t _timewindow;

  ClassDef(SandBoxFlatPhotoTube,0)

};

#endif
