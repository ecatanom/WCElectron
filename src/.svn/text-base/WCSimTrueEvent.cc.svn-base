#include "WCSimTrueEvent.hh"

#include <iostream>
#include <cmath>

ClassImp(WCSimTrueEvent)

static WCSimTrueEvent* fgTrueEvent = 0;

WCSimTrueEvent* WCSimTrueEvent::Instance()
{
  if( !fgTrueEvent ){
    fgTrueEvent = new WCSimTrueEvent();
  }

  return fgTrueEvent;
}

WCSimTrueEvent::WCSimTrueEvent()
{
  fTrackList = new std::vector<WCSimTrueTrack*>;
  
  this->Reset();
}

WCSimTrueEvent::~WCSimTrueEvent()
{
  delete fTrackList;
}
 
void WCSimTrueEvent::SetHeader( Int_t ipdg,
                                Double_t g4vx, Double_t g4vy, Double_t g4vz,
                                Double_t vx, Double_t vy, Double_t vz,
                                Double_t ex, Double_t ey, Double_t ez,
                                Double_t px, Double_t py, Double_t pz,
                                Double_t trkE, Double_t trkP, Double_t trkM )
{
  fIpdg = ipdg;

  fG4VtxX = g4vx;
  fG4VtxY = g4vy;
  fG4VtxZ = g4vz;

  fVtxX = vx;
  fVtxY = vy;
  fVtxZ = vz;      

  fEndX = ex;
  fEndY = ey;
  fEndZ = ez;    

  fDirX = px;
  fDirY = py;
  fDirZ = pz;

  fTrkE = trkE;
  fTrkP = trkP;
  fTrkM = trkM;
}
  
void WCSimTrueEvent::Reset()
{
  fIpdg = 0;

  fG4VtxX = -99999.9;
  fG4VtxY = -99999.9;
  fG4VtxZ = -99999.9;

  fVtxX = -99999.9;
  fVtxY = -99999.9;
  fVtxZ = -99999.9;     

  fEndX = -99999.9;
  fEndY = -99999.9;
  fEndZ = -99999.9;   

  fDirX = 0.0;
  fDirY = 0.0;
  fDirZ = 0.0;

  fTrkE = 0.0;
  fTrkP = 0.0;
  fTrkM = 0.0;

  fPrimary = 0;

  fFigureOfMerit = -99999.9;

  this->ClearTracks();
 
  return;
}
 
Int_t WCSimTrueEvent::GetNTracks()
{
  return fTrackList->size();
}
  
WCSimTrueTrack* WCSimTrueEvent::GetTrack(Int_t itrack)
{
  return (WCSimTrueTrack*)(fTrackList->at(itrack));
}
  
void WCSimTrueEvent::AddTrack(WCSimTrueTrack* myTrack)
{
  if( myTrack==0 ) return;

  fTrackList->push_back(myTrack);

  Double_t E = myTrack->GetEnergy();
  Double_t M = myTrack->GetMass();

  Double_t fom = E - 1.5*M; // kinetic energy above 
                            // Cherenkov threshold
  if( fPrimary==0 
   || fom>fFigureOfMerit ){
    fPrimary = myTrack;
    fFigureOfMerit = fom;
  }

  return;
}

void WCSimTrueEvent::ClearTracks()
{
  fTrackList->clear();
}

void WCSimTrueEvent::PrintEvent()
{
  std::cout << " *** WCSimTrueEvent::PrintEvent() *** " << std::endl
            << " * Ipdg = " << fIpdg << std::endl
            << " * G4VtxX = " << fG4VtxX << std::endl
	    << " * G4VtxY = " << fG4VtxY << std::endl
	    << " * G4VtxZ = " << fG4VtxZ << std::endl
	    << " * VtxX = " << fVtxX << std::endl
	    << " * VtxY = " << fVtxY << std::endl
	    << " * VtxZ = " << fVtxZ << std::endl
            << " * EndX = " << fEndX << std::endl
	    << " * EndY = " << fEndY << std::endl
	    << " * EndZ = " << fEndZ << std::endl
	    << " * DirX = " << fDirX << std::endl
	    << " * DirY = " << fDirY << std::endl
	    << " * DirZ = " << fDirZ << std::endl
	    << " * TrkE = " << fTrkP << std::endl
	    << " * TrkP = " << fTrkE << std::endl
            << " * TrkM = " << fTrkM << std::endl
            << " *********************************** " << std::endl;

  return;
}

