#include "SandBoxFlatPhotoTube.hh"
#include "SandBoxPhotoTubeModel.hh"
#include "WCSimRecoObjectTable.hh"
#include "WCSimRecoDigit.hh"
#include "WCSimRecoCluster.hh"
#include "WCSimTrueLightCluster.hh"

ClassImp(SandBoxFlatPhotoTube)


  SandBoxFlatPhotoTube::SandBoxFlatPhotoTube()
{
  _detectortype=0;
  _constQE=0.;

  spaceRand = new TRandom3(2342343);
  timeRand = new TRandom3(2311343);
  chargeRand = new TRandom3(9011343);
  efficRand = new TRandom3(8733243);
}

SandBoxFlatPhotoTube::SandBoxFlatPhotoTube(Int_t dtype, Double_t constQE)
{
  _detectortype=dtype;
  _constQE=constQE;

  spaceRand = new TRandom3(2342343);
  timeRand = new TRandom3(2311343);
  chargeRand = new TRandom3(9011343);
  efficRand = new TRandom3(8733243);
}

SandBoxFlatPhotoTube::~SandBoxFlatPhotoTube()
{
  delete spaceRand;
  delete timeRand;
  delete chargeRand;
  delete efficRand;
}

WCSimRecoDigit* SandBoxFlatPhotoTube::SmearSpace(WCSimRecoDigit* aHit)
{
  double smx = spaceRand->Gaus(0.,1.);
  double smy = spaceRand->Gaus(0.,1.);
  double smz = spaceRand->Gaus(0.,1.);
 
  double nx = (aHit->GetX()) + smx;
  double ny = (aHit->GetY()) + smy;
  double nz = (aHit->GetZ()) + smz;
 
  WCSimRecoDigit* newHit = new WCSimRecoDigit((aHit->GetRegion()),nx,ny,nz,(aHit->GetRawTime()),(aHit->GetRawQPEs()),(aHit->GetRawPEtube()),(aHit->GetTime()),(aHit->GetQPEs()));
  return newHit;
}

WCSimRecoDigit* SandBoxFlatPhotoTube::SmearTime(WCSimRecoDigit* aHit)
{
  double smt = timeRand->Gaus(0.,1.);
  double nt = (aHit->GetTime()) + smt;

  WCSimRecoDigit* newHit = new WCSimRecoDigit((aHit->GetRegion()),(aHit->GetX()),(aHit->GetY()),(aHit->GetZ()),nt,(aHit->GetRawQPEs()),(aHit->GetRawPEtube()),(aHit->GetTime()),(aHit->GetQPEs()));
  return newHit;
}

WCSimRecoDigit* SandBoxFlatPhotoTube::SmearSpaceTime(WCSimRecoDigit* aHit)
{
  double smx = spaceRand->Gaus(0.,1.);
  double smy = spaceRand->Gaus(0.,1.);
  double smz = spaceRand->Gaus(0.,1.);
  double smt = timeRand->Gaus(0.,1.);

  double nx = (aHit->GetX()) + smx;
  double ny = (aHit->GetY()) + smy;
  double nz = (aHit->GetZ()) + smz;
  double nt = (aHit->GetTime()) + smt;

  WCSimRecoDigit* newHit = new WCSimRecoDigit((aHit->GetRegion()),nx,ny,nz,nt,(aHit->GetRawQPEs()),(aHit->GetRawPEtube()),(aHit->GetTime()),(aHit->GetQPEs()));
  return newHit;
}

WCSimRecoDigit* SandBoxFlatPhotoTube::SmearCharge(WCSimRecoDigit* aHit)
{
  double smQ = chargeRand->Gaus(0.,1.);
  double nQ = (aHit->GetRawQPEs()) + smQ;

  WCSimRecoDigit* newHit = new WCSimRecoDigit((aHit->GetRegion()),(aHit->GetX()),(aHit->GetY()),(aHit->GetZ()),(aHit->GetTime()),nQ,(aHit->GetRawPEtube()),(aHit->GetTime()),(aHit->GetQPEs()));
  return newHit;
}


WCSimRecoCluster*  SandBoxFlatPhotoTube::GetSmeared(WCSimRecoCluster* theHits, vector<double> pmtcenter)
{
  WCSimRecoCluster* newrecocluster; 
  if(_detectortype==0) newrecocluster = PMTSmear(theHits, pmtcenter);
  if(_detectortype==1) newrecocluster = MCPSmear(theHits, pmtcenter);
 
  return newrecocluster;
}

WCSimRecoCluster*  SandBoxFlatPhotoTube::GetSmeared(WCSimTrueLightCluster* theHits, vector<double> pmtcenter)
{
  WCSimRecoCluster* newrecocluster; 

  WCSimRecoCluster* rctheHits = theHits->Convert2RecoCluster();

  if(_detectortype==0) newrecocluster = PMTSmear(rctheHits, pmtcenter);
  if(_detectortype==1) newrecocluster = MCPSmear(rctheHits, pmtcenter);
 
  return newrecocluster;
}

WCSimRecoCluster*  SandBoxFlatPhotoTube::MCPSmear(WCSimRecoCluster* theHits, vector<double> pmtcenter)
{
  WCSimRecoCluster *rclust = new WCSimRecoCluster();

  for(int i=0; i<(theHits->GetNDigits()); i++){

    WCSimRecoDigit* rdig = SmearSpaceTime(theHits->GetDigit(i));
    rclust->AddDigit(rdig);
  }


  return rclust;
}

WCSimRecoCluster*  SandBoxFlatPhotoTube::PMTSmear(WCSimRecoCluster* theHits, vector<double> pmtcenter)
{
  WCSimRecoCluster *rclust = new WCSimRecoCluster();
  
  for(int i=0; i<(theHits->GetNDigits()); i++){

    WCSimRecoDigit* rdig = SmearSpaceTime(theHits->GetDigit(i));
    rclust->AddDigit(rdig);

  }

  return rclust;
}


