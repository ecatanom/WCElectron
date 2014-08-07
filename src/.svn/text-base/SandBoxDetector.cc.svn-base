#include "TObject.h"
#include "SandBoxDetector.hh"
#include "WCSimRecoDigit.hh"
#include "WCSimGeometry.hh"
#include "SandBoxPhotoTubeModel.hh"
#include "SandBoxPhotoTubeGeo.hh"
#include "WCSimRecoObjectTable.hh"
#include "WCSimRecoDigit.hh"
#include "WCSimRecoCluster.hh"
#include "WCSimTrueLightCluster.hh"
#include "WCSimTrueLight.hh"
#include <vector>
#include "TObject.h"

ClassImp(SandBoxDetector)

  SandBoxDetector::SandBoxDetector(){;}
SandBoxDetector::SandBoxDetector(WCSimGeometry* thegeo, SandBoxPhotoTubeGeo* photodet){;}
SandBoxDetector::SandBoxDetector(WCSimGeometry* thegeo){;}

SandBoxDetector::~SandBoxDetector(){;}

void SandBoxDetector::SetDetectorGeometry(WCSimGeometry* thegeo){;}
void SandBoxDetector::SetDetectorGeometry(int type, double d1, double d2, double d3, double clearance){;}
void SandBoxDetector::SetPMTarrays(SandBoxPhotoTubeGeo* pmtgeo, double coverage){;}

WCSimRecoCluster* SandBoxDetector::GetTruePMTHits(WCSimRecoCluster* theHits)
{
  WCSimRecoCluster* truehits = new WCSimRecoCluster();
  return truehits;
}
WCSimRecoCluster* SandBoxDetector::GetTruePMTHits(WCSimTrueLightCluster* theHits)
{
  WCSimRecoCluster* truehits = new WCSimRecoCluster();
  return truehits;
}

// WCSimRecoCluster* SandBoxDetector::GetTruePMTHits(WCSimTrueLightCluster* theHits, SandBoxStepper* stepfunction){;}

WCSimRecoCluster* SandBoxDetector::GetSmearedPMTHits(WCSimRecoCluster* theHits, SandBoxPhotoTubeModel* pmtmodel)
{
  WCSimRecoCluster* smearedhits = new WCSimRecoCluster();
  return smearedhits;
}
WCSimRecoCluster* SandBoxDetector::GetSmearedPMTHits(WCSimTrueLightCluster* theHits, SandBoxPhotoTubeModel* pmtmodel)
{
  WCSimRecoCluster* smearedhits = new WCSimRecoCluster();
  return smearedhits;
}
// WCSimRecoCluster* SandBoxDetector::GetSmearedPMTHits(WCSimTrueLightCluster* theHits, SandBoxPhotoTubeModel* pmtmodel, SandBoxStepper* stepfunction){;}

int SandBoxDetector::GetPMTnumber(int hitnumber)
{
  int pmtnumber=0;
  return pmtnumber;
}

int SandBoxDetector::GetPMThitcount(int pmtnumber)
{
  int hitcount=0;
  return hitcount;
}

