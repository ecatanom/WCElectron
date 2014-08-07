#include "WCSimRecoEvent.hh"
#include "WCSimRecoRing.hh"
#include "WCSimRecoVertex.hh"
#include "WCSimRecoDigit.hh"

#include "WCSimRecoObjectTable.hh"

#include <iostream>
#include <fstream>
#include <cassert>

ClassImp(WCSimRecoEvent)

static WCSimRecoEvent* fgRecoEvent = 0;

WCSimRecoEvent* WCSimRecoEvent::Instance()
{
  if( !fgRecoEvent ){
    fgRecoEvent = new WCSimRecoEvent();
  }

  return fgRecoEvent;
}

WCSimRecoEvent::WCSimRecoEvent()
{
  fVertex = new WCSimRecoVertex();

  fDigitList = new std::vector<WCSimRecoDigit*>;
  fRingList = new std::vector<WCSimRecoRing*>;

  fRunNum = -1;
  fEventNum = -1;
  fTriggerNum = -1;

  fIsFilterDone = 0;
  fIsVertexFinderDone = 0;
  fIsRingFinderDone = 0;

  WCSimRecoObjectTable::Instance()->NewEvent();
}

WCSimRecoEvent::~WCSimRecoEvent()
{
  this->Reset();

  delete fVertex;

  delete fDigitList;
  delete fRingList;

  WCSimRecoObjectTable::Instance()->DeleteEvent();
}

void WCSimRecoEvent::Reset()
{  
  fVertex->Reset();

  this->ClearDigits();
  this->ClearRings();

  fDigitMap.clear();

  fRunNum = -1;
  fEventNum = -1;
  fTriggerNum = -1;

  fIsFilterDone = 0;
  fIsVertexFinderDone = 0;
  fIsRingFinderDone = 0;
}

void WCSimRecoEvent::SetHeader(Int_t run, Int_t event, Int_t trigger)
{
  fRunNum = run;
  fEventNum = event;
  fTriggerNum = trigger;
}

void WCSimRecoEvent::AddDigit(Int_t tube, WCSimRecoDigit* digit)
{
  fDigitList->push_back(digit);

  std::map<Int_t,WCSimRecoDigit*>::iterator myDigitMapEntry = fDigitMap.find(tube);
  
  if( myDigitMapEntry==fDigitMap.end() ){
    fDigitMap.insert( std::pair<Int_t,WCSimRecoDigit*>(tube,digit) );
  }

  return;
}

void WCSimRecoEvent::AddRing(WCSimRecoRing* ring)
{
  fRingList->push_back(ring);
}

void WCSimRecoEvent::ClearDigits()
{
  fDigitList->clear();
}

void WCSimRecoEvent::ClearRings()
{
  fRingList->clear();
}

WCSimRecoDigit* WCSimRecoEvent::GetDigitByTube(Int_t tube)
{
  WCSimRecoDigit* digit = 0;

  std::map<Int_t,WCSimRecoDigit*>::iterator myDigitMapEntry = fDigitMap.find(tube);

  if( myDigitMapEntry != fDigitMap.end() ){
    digit = myDigitMapEntry->second;
  }

  return digit;
}

Bool_t WCSimRecoEvent::IsTubeHit(Int_t tube)
{
  std::map<Int_t,WCSimRecoDigit*>::iterator myDigitMapEntry = fDigitMap.find(tube);

  if( myDigitMapEntry != fDigitMap.end() ){
    return 1;
  }
  else{
    return 0;
  }
}

WCSimRecoDigit* WCSimRecoEvent::GetDigit(Int_t n)
{
  return (WCSimRecoDigit*)(fDigitList->at(n));
}
  
Int_t WCSimRecoEvent::GetNDigits()
{
  return fDigitList->size();
}
  
Int_t WCSimRecoEvent::GetNFilterDigits()
{
  Int_t ctr = 0;

  for( Int_t n=0; n<this->GetNDigits(); n++ ){
    WCSimRecoDigit* digit = this->GetDigit(n);
    if( digit->IsFiltered() ) ctr++;
  }

  return ctr;
}

WCSimRecoRing* WCSimRecoEvent::GetRing(Int_t n)
{
  return (WCSimRecoRing*)(fRingList->at(n));
}
  
Int_t WCSimRecoEvent::GetNRings()
{
  return fRingList->size();
}

WCSimRecoRing* WCSimRecoEvent::GetPrimaryRing()
{
  if( fRingList->size()>0 ){
    return (WCSimRecoRing*)(fRingList->at(0));
  }
  else{
    return 0;
  }
}

void WCSimRecoEvent::SetVertex(WCSimRecoVertex* myVertex)
{
  fVertex->Reset();

  if( myVertex->FoundVertex() ){
    fVertex->SetVertex(myVertex->GetX(),
                       myVertex->GetY(),
                       myVertex->GetZ(),
                       myVertex->GetTime());
  }

  if( myVertex->FoundDirection() ){
    fVertex->SetDirection(myVertex->GetDirX(),
                          myVertex->GetDirY(),
                          myVertex->GetDirZ());
  }
 
  fVertex->SetConeAngle(myVertex->GetConeAngle());

  fVertex->SetTrackLength(myVertex->GetTrackLength());

  fVertex->SetFOM(myVertex->GetFOM(), 
                  myVertex->GetIterations(),
                  myVertex->GetPass());

  fVertex->SetStatus(myVertex->GetStatus());
}

WCSimRecoVertex* WCSimRecoEvent::GetVertex()
{ 
  return fVertex; 
}

Double_t WCSimRecoEvent::GetVtxX() 
{ 
  return fVertex->GetX(); 
}
  
Double_t WCSimRecoEvent::GetVtxY() 
{ 
  return fVertex->GetY(); 
}
  
Double_t WCSimRecoEvent::GetVtxZ() 
{ 
  return fVertex->GetZ(); 
}
  
Double_t WCSimRecoEvent::GetVtxTime()
{ 
  return fVertex->GetTime(); 
}
  
Double_t WCSimRecoEvent::GetDirX()
{
  return fVertex->GetDirX();
}
  
Double_t WCSimRecoEvent::GetDirY()
{
  return fVertex->GetDirY();
}
  
Double_t WCSimRecoEvent::GetDirZ()
{
  return fVertex->GetDirZ();
}
    
Bool_t WCSimRecoEvent::FoundVertex()
{
  return fVertex->FoundVertex();
}
  
Bool_t WCSimRecoEvent::FoundDirection()
{
  return fVertex->FoundDirection();
}

Bool_t WCSimRecoEvent::FoundRings()
{
  if( fRingList->size()>0 ) return 1;
  else return 0;
}

void WCSimRecoEvent::PrintDigitList(const char* filename)
{
  ofstream output(filename);

  for( Int_t i=0; i<this->GetNDigits(); i++ ){
    WCSimRecoDigit* myDigit = (WCSimRecoDigit*)(this->GetDigit(i));
    output << myDigit->GetX() << " " << myDigit->GetY() << " " << myDigit->GetZ() << " " << myDigit->GetTime() << " " << myDigit->GetQPEs() << std::endl; 
  }

  output.close();
}

void WCSimRecoEvent::PrintFilterDigitList(const char* filename)
{
  ofstream output(filename);

  for( Int_t i=0; i<this->GetNDigits(); i++ ){
    WCSimRecoDigit* myDigit = (WCSimRecoDigit*)(this->GetDigit(i));
    if( myDigit->IsFiltered() ){
      output << myDigit->GetX() << " " << myDigit->GetY() << " " << myDigit->GetZ() << " " << myDigit->GetTime() << " " << myDigit->GetQPEs() << std::endl;
    }
  }

  output.close();
}

void WCSimRecoEvent::PrintEvent()
{
  std::cout << " *** WCSimRecoEvent::PrintEvent() *** " << std::endl
            << " * VtxX = " << fVertex->GetX() << std::endl
	    << " * VtxY = " << fVertex->GetY() << std::endl
            << " * VtxZ = " << fVertex->GetZ() << std::endl
            << " * VtxTime = = " << fVertex->GetTime() << std::endl
            << " * DirX = " << fVertex->GetDirX() << std::endl
            << " * DirY = " << fVertex->GetDirY() << std::endl
            << " * DirZ = " << fVertex->GetDirZ() << std::endl
            << " * VtxFoM = " << fVertex->GetFOM() << std::endl
            << " ************************************ " << std::endl;

  return;
}
