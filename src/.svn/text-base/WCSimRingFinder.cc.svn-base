#include "WCSimRingFinder.hh"

#include "WCSimRecoDigit.hh"
#include "WCSimRecoEvent.hh"
#include "WCSimRecoVertex.hh"
#include "WCSimRecoRing.hh"
#include "WCSimHoughTransform.hh"
#include "WCSimHoughTransformArray.hh"

#include "WCSimGeometry.hh"

#include <cmath>
#include <iostream>
#include <cassert>

ClassImp(WCSimRingFinder)

static WCSimRingFinder* fgRingFinder = 0;

WCSimRingFinder* WCSimRingFinder::Instance()
{
  if( !fgRingFinder ){
    fgRingFinder = new WCSimRingFinder();
  }

  if( !fgRingFinder ){
    assert(fgRingFinder);
  }

  if( fgRingFinder ){

  }

  return fgRingFinder;
}
  
void WCSimRingFinder::UseRecoVertex()
{
  WCSimRingFinder::Instance()->SetUsingRecoVertex();
}

void WCSimRingFinder::HoughX( Int_t x )
{
  WCSimRingFinder::Instance()->SetHoughX(x);
}
  
void WCSimRingFinder::HoughY( Int_t y )
{
  WCSimRingFinder::Instance()->SetHoughY(y);
}
  
void WCSimRingFinder::HoughPoints( Int_t n )
{
  WCSimRingFinder::Instance()->SetHoughPoints(n);
}
  
void WCSimRingFinder::ConeAngleBins( Int_t bins )
{
  WCSimRingFinder::Instance()->SetConeAngleBins(bins);
}

void WCSimRingFinder::ConeAngleMin( Double_t min )
{
  WCSimRingFinder::Instance()->SetConeAngleMin(min);
}

void WCSimRingFinder::ConeAngleMax( Double_t max )
{
  WCSimRingFinder::Instance()->SetConeAngleMax(max);
}

void WCSimRingFinder::PrintParameters()
{
  WCSimRingFinder::Instance()->RunPrintParameters();
}

WCSimRingFinder::WCSimRingFinder()
{
  // use reco vertex
  fUseVertex = 0;

  // default hough transform parameters
  fHoughX = 120;          // bins in phi
  fHoughY = 60;           // bins in cos(theta)
  fHoughPoints = 360;     // hough points

  fConeAngleBins = 30;   // hough angle bins
  fConeAngleMin = 24.5;  // hough cone (min)
  fConeAngleMax = 54.5;  // hough cone (max)
  
  // hough transform object
  fHoughTransform = 0;

  // hough transform array
  fHoughTransformArray = 0;

  // make list of rings
  fRingList = new std::vector<WCSimRecoRing*>;
}

WCSimRingFinder::~WCSimRingFinder()
{
  if( fHoughTransform ){
    delete fHoughTransform;
  }

  if( fHoughTransformArray ){
    delete fHoughTransformArray;
  }

  for( UInt_t i=0; i<fRingList->size(); i++ ){
    delete (WCSimRecoRing*)(fRingList->at(i));
  }
 
  fRingList->clear();

  delete fRingList;
}

void WCSimRingFinder::RunPrintParameters()
{
  std::cout << " *** WCSimRingFinder::PrintParameters() *** " << std::endl;

  std::cout << "  Ring Finder Parameters: " << std::endl
            << "   UseVertex = " << fUseVertex << std::endl
            << "   HoughX = " << fHoughX << std::endl
            << "   HoughY = " << fHoughY << std::endl
            << "   ConeAngleBins = " << fConeAngleBins << std::endl
            << "   ConeAngleMin = " << fConeAngleMin << std::endl
            << "   ConeAngleMax = " << fConeAngleMax << std::endl;

  return;
}

void WCSimRingFinder::Reset()
{

  return;
}

std::vector<WCSimRecoRing*>* WCSimRingFinder::Run(WCSimRecoVertex* myVertex)
{
  std::cout << " *** WCSimRingFinder::Run(Vertex) *** " << std::endl;

  // reset ring list
  // ===============  
  for( UInt_t i=0; i<fRingList->size(); i++ ){
    delete (WCSimRecoRing*)(fRingList->at(i));
  }
 
  // clear ring list
  // ===============
  fRingList->clear();  

  // Make new ring, using vertex
  // ===========================
  WCSimRecoRing* myRing = new WCSimRecoRing(myVertex->GetX(),
                                            myVertex->GetY(),
                                            myVertex->GetZ(),   
                                            myVertex->GetDirX(),
                                            myVertex->GetDirY(),
					    myVertex->GetDirZ(),
					    myVertex->GetConeAngle(), 
                                            0.0); // height of hough peak

  fRingList->push_back(myRing);

  // Return Ring List
  // ================
  return fRingList;
}

std::vector<WCSimRecoRing*>* WCSimRingFinder::Run(WCSimRecoEvent* myEvent, WCSimRecoVertex* myVertex)
{
  // get filter digit list
  // =====================
  std::vector<WCSimRecoDigit*>* myDigitList = (std::vector<WCSimRecoDigit*>*)(myEvent->GetDigitList());

  // run vertex finder
  // =================
  return (std::vector<WCSimRecoRing*>*)(this->Run(myDigitList,myVertex));
}

std::vector<WCSimRecoRing*>* WCSimRingFinder::Run(std::vector<WCSimRecoDigit*>* myDigitList, WCSimRecoVertex* myVertex)
{
  std::cout << " *** WCSimRingFinder::Run(...) *** " << std::endl;

  // override 
  // ========
  if( fUseVertex ){
    std::cout << "  --- reconstruct ring from vertex --- " << std::endl;
    return this->Run(myVertex);
  }

  // reset ring list
  // ===============  
  for( UInt_t i=0; i<fRingList->size(); i++ ){
    delete (WCSimRecoRing*)(fRingList->at(i));
  }
 
  // clear ring list
  // ===============
  fRingList->clear();

  // apply Hough Transform
  // =====================
  WCSimHoughTransformArray* myHoughTransformArray = (WCSimHoughTransformArray*)(this->HoughTransformArray(myDigitList,myVertex));
  
  // Find Hough Peak
  // ===============
  Double_t houghVtxX = myVertex->GetX();
  Double_t houghVtxY = myVertex->GetY();
  Double_t houghVtxZ = myVertex->GetZ();

  Double_t houghDirX = 0.0;
  Double_t houghDirY = 0.0;
  Double_t houghDirZ = 0.0;
  Double_t houghAngle = 0.0;
  Double_t houghHeight = 0.0;
 
  myHoughTransformArray->FindPeak(houghDirX,houghDirY,houghDirZ,
                                  houghAngle,houghHeight);
  
  // Make New Ring
  // =============
  std::cout << "  found new ring: (vx,vy,vz)=(" << houghVtxX << "," << houghVtxY << "," << houghVtxZ << ") " << std::endl
            << "                  (px,py,pz)=(" << houghDirX << "," << houghDirY << "," << houghDirZ << ") " << std::endl
            << "                   angle=" << houghAngle << " height=" << houghHeight << std::endl;

  WCSimRecoRing* myRing = new WCSimRecoRing(houghVtxX,houghVtxY,houghVtxZ,
                                            houghDirX,houghDirY,houghDirZ,
                                            houghAngle,houghHeight);

  fRingList->push_back(myRing);

  // Return Ring List
  // ================
  return fRingList;
}

WCSimHoughTransform* WCSimRingFinder::HoughTransform(WCSimRecoEvent* myEvent, WCSimRecoVertex* myVertex, Double_t myAngle)
{
  // get filter digit list
  // =====================
  std::vector<WCSimRecoDigit*>* myDigitList = (std::vector<WCSimRecoDigit*>*)(myEvent->GetDigitList());

  // run Hough Transform
  // ===================
  return (WCSimHoughTransform*)(this->HoughTransform(myDigitList,myVertex,myAngle));
}

WCSimHoughTransform* WCSimRingFinder::HoughTransform(std::vector<WCSimRecoDigit*>* myDigitList, WCSimRecoVertex* myVertex, Double_t myAngle)
{
  std::cout << " *** WCSimRingFinder::HoughTransform(...) *** " << std::endl;
  std::cout << "  calculate Hough Transform for cone angle: " << myAngle << std::endl;  
  
  // make new Hough Transform (if necessary)
  // =======================================
  if( fHoughTransform==0 ){
    fHoughTransform = new WCSimHoughTransform(fHoughX,fHoughY);
  }

  // reset Hough Transform
  // =====================
  fHoughTransform->Reset();

  // perform Hough Transform
  // =======================
  for( UInt_t idigit=0; idigit<myDigitList->size(); idigit++ ){
    WCSimRecoDigit* myDigit = (WCSimRecoDigit*)(myDigitList->at(idigit));

    if( myDigit->IsFiltered()==0 ) continue;

    Double_t x = myDigit->GetX();
    Double_t y = myDigit->GetY();
    Double_t z = myDigit->GetZ();

    Double_t vx = myVertex->GetX();
    Double_t vy = myVertex->GetY();
    Double_t vz = myVertex->GetZ();

    Double_t omega = 0.0;
    Double_t rx = 0.0;
    Double_t ry = 0.0;
    Double_t rz = 0.0;
    Double_t nx = 0.0;
    Double_t ny = 0.0;
    Double_t nz = 0.0;
    Double_t r = 0.0;

    Double_t weight = 1.0;

    for( Int_t n=0; n<fHoughPoints; n++ ){
      omega = 360.0*((double)n/(double)fHoughPoints);

      WCSimGeometry::FindCircle(x, y, z,
                                vx, vy, vz,
                                myAngle, omega,
                                rx, ry, rz,
                                nx, ny, nz, r);

      fHoughTransform->Fill(nx,ny,nz,weight);
    }
  }

  // return result of Hough Transform
  // ================================
  return fHoughTransform;
}

WCSimHoughTransformArray* WCSimRingFinder::HoughTransformArray(WCSimRecoEvent* myEvent, WCSimRecoVertex* myVertex)
{
  // get filter digit list
  // =====================
  std::vector<WCSimRecoDigit*>* myDigitList = (std::vector<WCSimRecoDigit*>*)(myEvent->GetDigitList());

  // run Hough Transform
  // ===================
  return (WCSimHoughTransformArray*)(this->HoughTransformArray(myDigitList,myVertex));
}

WCSimHoughTransformArray* WCSimRingFinder::HoughTransformArray(std::vector<WCSimRecoDigit*>* myDigitList, WCSimRecoVertex* myVertex)
{
  std::cout << " *** WCSimRingFinder::HoughTransformArray(...) *** " << std::endl;
  
  // make new Hough Transform array (if necessary)
  // =============================================
  if( fHoughTransformArray==0 ){
    fHoughTransformArray = new WCSimHoughTransformArray( fConeAngleBins,fConeAngleMin,fConeAngleMax,
                                                         fHoughX,fHoughY);
  }

  // reset Hough Transform array
  // ===========================
  fHoughTransformArray->Reset();

  // perform Hough Transform
  // =======================
  for( UInt_t idigit=0; idigit<myDigitList->size(); idigit++ ){
    WCSimRecoDigit* myDigit = (WCSimRecoDigit*)(myDigitList->at(idigit));

    if( myDigit->IsFiltered()==0 ) continue;

    Double_t x = myDigit->GetX();
    Double_t y = myDigit->GetY();
    Double_t z = myDigit->GetZ();

    Double_t vx = myVertex->GetX();
    Double_t vy = myVertex->GetY();
    Double_t vz = myVertex->GetZ();

    Double_t omega = 0.0;
    Double_t rx = 0.0;
    Double_t ry = 0.0;
    Double_t rz = 0.0;
    Double_t nx = 0.0;
    Double_t ny = 0.0;
    Double_t nz = 0.0;
    Double_t r = 0.0;

    Double_t weight = 1.0;

    for( Int_t n=0; n<fHoughPoints; n++ ){
      omega = 360.0*((double)n/(double)fHoughPoints);

      for( Int_t nAngle=0; nAngle<fHoughTransformArray->GetConeAngleBins(); nAngle++ ){
        Double_t myAngle = fHoughTransformArray->GetConeAngle(nAngle);
	WCSimHoughTransform* myHoughTransform = (WCSimHoughTransform*)(fHoughTransformArray->GetHoughTransform(nAngle));
        
        WCSimGeometry::FindCircle(x, y, z,
                                  vx, vy, vz,
                                  myAngle, omega,
                                  rx, ry, rz,
                                  nx, ny, nz, r);

        myHoughTransform->Fill(nx,ny,nz,weight);
      }
    }
  }

  // return result of Hough Transform
  // ================================
  return fHoughTransformArray;
}
