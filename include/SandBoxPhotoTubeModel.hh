#ifndef SANDBOXPHOTOTUBEMODEL_HH
#define SANDBOXPHOTOTUBEMODEL_HH

#include "TObject.h"
#include "WCSimRecoDigit.hh"
#include "WCSimRecoCluster.hh"
#include "WCSimTrueLightCluster.hh"
#include <vector>

using namespace std;

class SandBoxPhotoTubeModel : public TObject {

public: 

 SandBoxPhotoTubeModel();
  ~SandBoxPhotoTubeModel();

  WCSimRecoCluster* GetSmeared(WCSimRecoCluster* theHits, vector<double> pmtcenter);
  WCSimRecoCluster* GetSmeared(WCSimTrueLightCluster* theHits, vector<double> pmtcenter);

  WCSimRecoCluster* MCPSmear(WCSimRecoCluster* theHits, vector<double> pmtcenter);
  WCSimRecoCluster* PMTSmear(WCSimRecoCluster* theHits, vector<double> pmtcenter);

  WCSimRecoDigit* SmearSpace(WCSimRecoDigit* aHit);
  WCSimRecoDigit* SmearTime(WCSimRecoDigit* aHit);
  WCSimRecoDigit* SmearSpaceTime(WCSimRecoDigit* aHit);
  WCSimRecoDigit* SmearCharge(WCSimRecoDigit* aHit);


 private: 

  ClassDef(SandBoxPhotoTubeModel,0)
};

#endif
