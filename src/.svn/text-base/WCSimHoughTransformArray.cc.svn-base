#include "WCSimHoughTransformArray.hh"
#include "WCSimHoughTransform.hh"

#include <iostream>

ClassImp(WCSimHoughTransformArray)

WCSimHoughTransformArray::WCSimHoughTransformArray(Int_t coneAngleBins, Double_t coneAngleMin, Double_t coneAngleMax, Int_t phiBins, Int_t cosThetaBins)
{
  this->BuildArray(coneAngleBins,coneAngleMin,coneAngleMax,
                   phiBins,cosThetaBins);
}

WCSimHoughTransformArray::~WCSimHoughTransformArray()
{
  this->DeleteArray();
}
 
void WCSimHoughTransformArray::BuildArray(Int_t coneAngleBins, Double_t coneAngleMin, Double_t coneAngleMax, Int_t phiBins, Int_t cosThetaBins)
{
  std::cout << " *** WCSimHoughTransformArray::BuildArray() *** " << std::endl;

  // set parameters
  fHoughX = phiBins;
  fHoughY = cosThetaBins;
  fConeAngleBins = coneAngleBins;
  fConeAngleMin = coneAngleMin;
  fConeAngleMax = coneAngleMax;

  std::cout << "  building Hough Transform Array: (bins,min,max)=(" << fConeAngleBins << "," << fConeAngleMin << "," << fConeAngleMax << ") " << std::endl;

  // clear current array
  this->DeleteArray();

  // create new array
  for( Int_t n=0; n<fConeAngleBins; n++ ){
    WCSimHoughTransform* myHoughTransform = new WCSimHoughTransform(fHoughX,fHoughY);
    fHoughArray.push_back(myHoughTransform);
  }

  return;
}

void WCSimHoughTransformArray::FindPeak(Int_t& bin, Double_t& height)
{
  Int_t bestBin = -1;  
  Double_t bestHeight = 0.0;

  Double_t myHeight = 0.0;  
  
  for( Int_t iBin=0; iBin<this->GetBins(); iBin++ ){
    WCSimHoughTransform* myHoughTransform = this->GetHoughTransform(iBin);
    myHoughTransform->FindPeak(myHeight);

    if( myHeight>bestHeight ){
      bestBin = iBin;
      bestHeight = myHeight;
    }
  }

  bin = bestBin;
  height = bestHeight;

  return;
}

void WCSimHoughTransformArray::FindPeak(Double_t& phi, Double_t& costheta, Double_t& angle, Double_t& height)
{
  Int_t bestBin = -1;  
  Double_t bestPhi = 0.0;
  Double_t bestCosTheta = 0.0;
  Double_t bestHeight = 0.0;
    
  Double_t myPhi = 0.0;
  Double_t myCosTheta = 0.0;
  Double_t myHeight = 0.0;  

  for( Int_t iBin=0; iBin<this->GetBins(); iBin++ ){
    WCSimHoughTransform* myHoughTransform = this->GetHoughTransform(iBin);
    myHoughTransform->FindPeak(myPhi,myCosTheta,myHeight);

    if( myHeight>bestHeight ){
      bestBin = iBin;
      bestPhi = myPhi;
      bestCosTheta = myCosTheta;
      bestHeight = myHeight;
    }
  }  

  angle = this->GetAngle(bestBin);
  phi = bestPhi;
  costheta = bestCosTheta;
  height = bestHeight;

  return;
}
  
void WCSimHoughTransformArray::FindPeak(Double_t& hx, Double_t& hy, Double_t& hz, Double_t& angle, Double_t& height)
{

  Int_t bestBin = -1;  
  Double_t bestDirX = 0.0;
  Double_t bestDirY = 0.0;
  Double_t bestDirZ = 0.0;
  Double_t bestHeight = 0.0;
    
  Double_t myDirX = 0.0;
  Double_t myDirY = 0.0;
  Double_t myDirZ = 0.0;
  Double_t myHeight = 0.0;

  for( Int_t iBin=0; iBin<this->GetBins(); iBin++ ){
    WCSimHoughTransform* myHoughTransform = this->GetHoughTransform(iBin);
    myHoughTransform->FindPeak(myDirX,myDirY,myDirZ,myHeight);

    if( myHeight>bestHeight ){
      bestBin = iBin;
      bestDirX = myDirX;
      bestDirY = myDirY;
      bestDirZ = myDirZ;
      bestHeight = myHeight;
    }
  }

  angle = this->GetAngle(bestBin);
  hx = bestDirX;
  hy = bestDirY;
  hz = bestDirZ;
  height = bestHeight;

  return;
}

Int_t WCSimHoughTransformArray::FindBin(Double_t myAngle)
{
  if( myAngle>=fConeAngleMin && myAngle<fConeAngleMax ){
    return (Int_t)(fConeAngleBins*(myAngle-fConeAngleMin)/(fConeAngleMax-fConeAngleMin));
  }
  else{
    return -1;
  }
}

Double_t WCSimHoughTransformArray::GetAngle(Int_t myBin)
{
  return this->GetConeAngle(myBin);
}

Double_t WCSimHoughTransformArray::GetConeAngle(Int_t myBin)
{
  if( fConeAngleBins>0 ){
    return fConeAngleMin + ((double)(myBin+0.5)/(double)fConeAngleBins)*(fConeAngleMax-fConeAngleMin); 
  }
  else{
    return -45.0;
  }
}

WCSimHoughTransform* WCSimHoughTransformArray::GetHoughTransform(Int_t nAngle)
{
  if( nAngle>=0 && nAngle<fConeAngleBins ){
    return (WCSimHoughTransform*)(fHoughArray.at(nAngle));
  }
  else return 0;
}

void WCSimHoughTransformArray::DeleteArray()
{
  for( UInt_t n=0; n<fHoughArray.size(); n++ ){
    delete (WCSimHoughTransform*)(fHoughArray.at(n));
  }

  fHoughArray.clear();

  return;
}

void WCSimHoughTransformArray::PrintArray()
{
  std::cout << " *** WCSimHoughTransformArray::PrintArray() *** " << std::endl;

  for( Int_t n=0; n<fConeAngleBins; n++ ){
    std::cout << "  [" << n << "] coneAngle=" << this->GetConeAngle(n) << std::endl; 
  }

  return;
}

void WCSimHoughTransformArray::Reset()
{
  // reset each hough transform
  for( UInt_t n=0; n<fHoughArray.size(); n++ ){
    WCSimHoughTransform* myHoughTransform = (WCSimHoughTransform*)(fHoughArray.at(n));
    myHoughTransform->Reset();
  }
}
