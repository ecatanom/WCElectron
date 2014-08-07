#include "WCSimInterface.hh"
#include "WCSimGeometry.hh"
#include "WCSimParameters.hh"

#include "WCSimTrueEvent.hh"
#include "WCSimTrueTrack.hh"

#include "WCSimRecoEvent.hh"
#include "WCSimRecoDigit.hh"
#include "SandBoxDigitizer.hh"

#include "TF1.h"
#include "TRandom.h"
#include "TRandom3.h"

#include <cmath>
#include <iostream>
#include <cassert>

ClassImp(WCSimInterface)

static WCSimInterface* fgInterface = 0;

Bool_t WCSimInterface::TouchData()
{
  if( WCSimInterface::Instance()->GetEntries()>0 ){
    return true;
  }
  else{
    std::cout << " *** WCSimInterface::TouchData() *** " << std::endl;
    std::cout << "  <error> need to input data... " << std::endl
              << "    Call: WCSimInterface::LoadData(...) " << std::endl;
    return false;
  }
}

WCSimInterface* WCSimInterface::Instance()
{
  if( !fgInterface ){
    fgInterface = new WCSimInterface();
  }

  return fgInterface;
}

void WCSimInterface::LoadData(const char* file)
{
  return WCSimInterface::Instance()->AddFile(file);
}

void WCSimInterface::LoadEvent(Int_t ievent)
{
  return WCSimInterface::Instance()->BuildEvent(ievent);
}

Int_t WCSimInterface::GetNumEvents()
{
  return WCSimInterface::Instance()->GetEntries();
}

Bool_t WCSimInterface::TouchEvent()
{
  return WCSimInterface::Instance()->CheckEvent();
}

Int_t WCSimInterface::GetRunNumber()
{
  return WCSimInterface::RecoEvent()->GetRun();
}

Int_t WCSimInterface::GetEventNumber()
{
  return WCSimInterface::RecoEvent()->GetEvent();
}

Int_t WCSimInterface::GetTriggerNumber()
{
  return WCSimInterface::RecoEvent()->GetTrigger();
}

void WCSimInterface::SetEnergyThreshold(Double_t input_mev)
{
  return WCSimInterface::Instance()->SetTrueEnergyThreshold(input_mev);
}

void WCSimInterface::SetRangeThreshold(Double_t input_cm)
{
  return WCSimInterface::Instance()->SetTrueRangeThreshold(input_cm);
}

void WCSimInterface::SetToUseTrueHits()
{
  return WCSimInterface::Instance()->SetToTrueHits();
}

void WCSimInterface::Reset()
{
  return WCSimInterface::Instance()->ResetForNewSample();
}

WCSimInterface::WCSimInterface()
{
  fDigitList = new std::vector<WCSimRecoDigit*>;
  fTrackList = new std::vector<WCSimTrueTrack*>;  

  fTrigger0 = 0;
  fTrigger = 0;
  fEvent = 0;
  fGeometry = 0;
  fCounter = -1;

  fusetruth=true; //not conventional....TX
  fuseMCP = false;
  fuseGate = false;
  fPMTspace=false;
  fEnergyThreshold = 25.0; // 25 MeV
  fRangeThreshold = 25.0;  // 25 cm

  // create event chain
  fChain = new TChain("wcsimT","chain");
  fChain->SetBranchAddress("wcsimrootevent",&fEvent);

  // create geometry chain
  fChainGeom = new TChain("wcsimGeoT","chainGeom");
  fChainGeom->SetBranchAddress("wcsimrootgeom",&fGeometry);

  this->ResetForNewSample();
}

WCSimInterface::~WCSimInterface()
{
  this->ResetTrueEvent();
  this->ResetRecoEvent();

  delete fDigitList; 
  delete fTrackList;
}

void WCSimInterface::AddFile(const char* file)
{
  std::cout << " *** WCSimInterface::LoadData(...) *** " << std::endl;
  std::cout << "  adding: " << file << std::endl;

  fChain->Add(file);

  std::cout << "   ... total entries=" << fChain->GetEntries() << std::endl;

  if( !fGeometry && fChain->GetEntries()>0 ){
    std::cout << " *** WCSimInterface::LoadGeometry(...) *** " << std::endl;
    fChainGeom->Add(file);
    if( fChainGeom->GetEntries()>0 ){
      fChainGeom->GetEntry(0);
      if( fGeometry ) WCSimGeometry::BuildGeometry(fGeometry);
    }
  }

  return;
}

void WCSimInterface::ResetForNewSample()
{
  if( fChain->GetEntries()>0 ){
    std::cout << " *** WCSimInterface::Reset() *** " << std::endl;  
  }

  // event chain
  if( fChain ){
    fChain->Reset();
    fChain->SetBranchAddress("wcsimrootevent",&fEvent);
    if( fEvent ) delete fEvent; fEvent = 0;
  }

  // geometry chain
  if( fChainGeom ){
    fChainGeom->Reset();
    fChainGeom->SetBranchAddress("wcsimrootgeom",&fGeometry);
    if( fGeometry ) delete fGeometry; fGeometry = 0;
  }

  // reset true event
  this->ResetTrueEvent();

  //  reset reco event
  this->ResetRecoEvent();

  // reset geometry
  WCSimGeometry::Reset();

  fCounter = -1;

  return;
}

void WCSimInterface::ResetTrueEvent()
{
  // Reset 
  // =====
  WCSimTrueEvent::Instance()->Reset();

  // delete list of tracks
  // =====================
  for( UInt_t i=0; i<fTrackList->size(); i++ ){
    delete (WCSimTrueTrack*)(fTrackList->at(i));
  }

  // clear list of tracks
  // ====================
  fTrackList->clear();

  return;
}

void WCSimInterface::ResetRecoEvent()
{
  // Reset 
  // =====
  WCSimRecoEvent::Instance()->Reset();

  // delete list of digits
  // =====================
  for( UInt_t i=0; i<fDigitList->size(); i++ ){
    delete (WCSimRecoDigit*)(fDigitList->at(i));
  }

  // clear list of digits
  // ====================
  fDigitList->clear();

  return;
}

Int_t WCSimInterface::GetEntries()
{
  return fChain->GetEntries();
}

Bool_t WCSimInterface::CheckEvent()
{
  if( fTrigger ) return true;  
  else return false;
}

void WCSimInterface::BuildEvent(Int_t ievent)
{
  std::cout << " *** WCSimInterface::BuildEvent(" << ievent << ") *** " << std::endl;

  if( fCounter==ievent ) return;

  fCounter = ievent;

//Ioana from Tian
  //if( fEvent ) delete fEvent;  

  fEvent = 0; fTrigger = 0; fTrigger0 = 0;
  //Ioana form Tian
  fTrigger->Reset();
  fTrigger0->Reset();
  fEvent->Reset();
  
  
  if( ievent>=0 || ievent<fChain->GetEntries() ){
    fChain->GetEntry(ievent);
  }
  else{
    std::cout << "  <warning>: this event doesn't exist! " << std::endl;
  }

  // Get Trigger
  // ===========
  fTrigger  = WCSimInterface::FilterTrigger(fEvent);
  fTrigger0 = fEvent->GetTrigger(0);

  // Build Reco Event
  // ================
  //BuildRecoEvent(fTrigger,fusetruth);

  // Build Reco Event Using SandBoxDigitizer....TX
  //=================
  SandBoxDigitizer* fDigitize = new SandBoxDigitizer(fTrigger,"test");
  if( fuseMCP ) fDigitize->SetMCP(fTimeSmear,0.0);
  else{
    if( fuseGate ) fDigitize->SetPMT(fTimeSmear,500.0,1.0,1);
    else fDigitize->SetPMT(fTimeSmear,500.0,1.0,0);
  }
  fDigitize->Digitize();
  //============================================

  // Build True Event
  // ================
  BuildTrueEvent(fTrigger0);

  return;
}

WCSimRootEvent* WCSimInterface::GetWCSimEvent(Int_t ievent)
{
  this->BuildEvent(ievent);

  return fEvent;
}

WCSimRootTrigger* WCSimInterface::GetWCSimTrigger(Int_t ievent)
{
  this->BuildEvent(ievent);
  
  return fTrigger;
}

WCSimRootTrigger* WCSimInterface::FilterTrigger(WCSimRootEvent* myEvent)
{
  // Sanity Check
  // ============
  if( myEvent==0 ) return 0;

  // make a WCSim Trigger 
  // ====================
  WCSimRootTrigger* myTrigger = 0;

  // for now, pick the largest trigger
  // =================================
  Int_t triggerDigits = -1;
  Int_t triggerNumber = -1;
  
  for( Int_t nTrigger = 0; nTrigger<myEvent->GetNumberOfEvents(); nTrigger++ ){
    WCSimRootTrigger* tempTrigger = (WCSimRootTrigger*)(myEvent->GetTrigger(nTrigger));
    Int_t nDigits = 1+tempTrigger->GetCherenkovDigiHits()->GetLast();

    if( nDigits>triggerDigits ){
      triggerDigits = nDigits;
      triggerNumber = nTrigger;
    }
  }

  if( triggerNumber>=0 ){
    myTrigger = (WCSimRootTrigger*)(myEvent->GetTrigger(triggerNumber));
  }

  if( myTrigger ){
    std::cout << " *** WCSimInterface::FilterTrigger(...) *** " << std::endl
              << "  Run = " << myTrigger->GetHeader()->GetRun() << std::endl
              << "  Event = " << myTrigger->GetHeader()->GetEvtNum() << std::endl
              << "  Trigger = " << myTrigger->GetHeader()->GetSubEvtNumber() << std::endl;
  }
  else{
    std::cout << " <warning>: failed to find trigger for this event " << std::endl;
  }

  return myTrigger;
}

WCSimTrueEvent* WCSimInterface::TrueEvent()
{
  return WCSimTrueEvent::Instance();
}

WCSimRecoEvent* WCSimInterface::RecoEvent()
{
  return WCSimRecoEvent::Instance();
}

WCSimRootEvent* WCSimInterface::WCSimEvent()
{
  return WCSimInterface::Instance()->GetWCSimEvent();
}

WCSimRootTrigger* WCSimInterface::WCSimTrigger()
{
  return WCSimInterface::Instance()->GetWCSimTrigger();
}

void WCSimInterface::BuildTrueEvent(WCSimRootTrigger* myTrigger)
{
  // Reset
  // =====
  this->ResetTrueEvent();

  // Check for Trigger
  // =================
  if( myTrigger == 0 ){
    return;
  }

  // Build True Event
  // ================
  std::cout << " *** WCSimInterface::BuildTrueEvent(...) *** " << std::endl;


  // Get Array of Tracks
  // ===================
  TClonesArray* fTrackArray = (TClonesArray*)(myTrigger->GetTracks());

  Int_t ipdg = 0;
  Int_t ipdgparent = 0;
  Int_t iflag = 0;
  Double_t trkP = 0.0;  
  Double_t trkE = 0.0;
  Double_t trkM = 0.0;
  Double_t trkK = 0.0;  

  Double_t g4vx = 0.0;
  Double_t g4vy = 0.0;
  Double_t g4vz = 0.0;
  Double_t g4ex = 0.0;
  Double_t g4ey = 0.0;
  Double_t g4ez = 0.0;
  Double_t g4ds = 0.0;  

  Double_t vx = 0.0;
  Double_t vy = 0.0;
  Double_t vz = 0.0;
  Double_t ex = 0.0;
  Double_t ey = 0.0;
  Double_t ez = 0.0;
  Double_t ds = 0.0;
  
  Double_t px = 0.0;
  Double_t py = 0.0;
  Double_t pz = 0.0;    
  Double_t qx = 0.0;
  Double_t qy = 0.0;
  Double_t qz = 0.0;
   
  Int_t vtxReg = -1;
  Int_t endReg = -1;

  Int_t primeIpdg = 0;  
  Double_t primeG4Vx = 0.0;
  Double_t primeG4Vy = 0.0;
  Double_t primeG4Vz = 0.0; 
  Double_t primeG4Ex = 0.0;
  Double_t primeG4Ey = 0.0;
  Double_t primeG4Ez = 0.0; 
  Double_t primeVx = 0.0;
  Double_t primeVy = 0.0;
  Double_t primeVz = 0.0;
  Double_t primeEx = 0.0;
  Double_t primeEy = 0.0;
  Double_t primeEz = 0.0;
  Double_t primePx = 0.0;
  Double_t primePy = 0.0;
  Double_t primePz = 0.0;
  Double_t primeTrkE = 0.0;  
  Double_t primeTrkP = 0.0;
  Double_t primeTrkM = 0.0;

  Double_t beta = 0.0;

  Bool_t possible_track = 0;
  Bool_t new_track = 0;

  std::cout << "  looping over tracks: " << std::endl;

  // loop over tracks
  // =================
  for( Int_t nTrack=0; nTrack<1+fTrackArray->GetLast(); nTrack++ ){
    WCSimRootTrack* myTrack = (WCSimRootTrack*)(fTrackArray->At(nTrack));
    
    // get track properties
    // ====================
    ipdg = myTrack->GetIpnu();
    ipdgparent = myTrack->GetParenttype();
    iflag = myTrack->GetFlag();

    trkP = myTrack->GetP();
    trkE = myTrack->GetE();
    trkM = myTrack->GetM();
    trkK = trkE-trkM;

    g4vx = myTrack->GetStart(0);
    g4vy = myTrack->GetStart(1);
    g4vz = myTrack->GetStart(2);        
    g4ex = myTrack->GetStop(0);
    g4ey = myTrack->GetStop(1);
    g4ez = myTrack->GetStop(2);
    px = myTrack->GetDir(0);
    py = myTrack->GetDir(1);
    pz = myTrack->GetDir(2);

    vx = -99999.9;
    vy = -99999.9;
    vz = -99999.9;
    ex = -99999.9;
    ey = -99999.9;
    ez = -99999.9;
    
    vtxReg = 0;
    endReg = 0;
 
    ds = 0.0;
    beta = 0.0;

    qx = g4ex-g4vx;
    qy = g4ey-g4vy;
    qz = g4ez-g4vz;
    g4ds = sqrt(qx*qx+qy*qy+qz*qz);

    if( g4ds>0.0 ){
      qx /= g4ds;
      qy /= g4ds;
      qz /= g4ds;
    }

    // entry point
    if( endReg>=0 ){
      if( WCSimGeometry::Instance()->InsideDetector(g4vx,g4vy,g4vz) ){
        vx = g4vx; vy = g4vy; vz = g4vz;
      }
      else{
        WCSimGeometry::Instance()->ProjectToNearEdge(g4vx, g4vy, g4vz,
                                                     px, py, pz,
                                                     vx, vy, vz, vtxReg);
        if( vtxReg<0 ){
          WCSimGeometry::Instance()->ProjectToNearEdge(g4vx, g4vy, g4vz,
                                                       qx, qy, qz,
                                                       vx, vy, vz, vtxReg);
	}
      } 
      if( vtxReg<0 ) endReg = -1;
    }
	
    // exit point
    if( vtxReg>=0 ){
      if( WCSimGeometry::Instance()->InsideDetector(g4ex,g4ey,g4ez) ){
        ex = g4ex; ey = g4ey; ez = g4ez;
      }
      else{
        WCSimGeometry::Instance()->ProjectToNearEdge(g4ex, g4ey, g4ez,
                                                     -px, -py, -pz,
                                                     ex, ey, ez, endReg);
        if( endReg<0 ){
          WCSimGeometry::Instance()->ProjectToNearEdge(g4ex, g4ey, g4ez,
                                                       -qx, -qy, -qz,
                                                       ex, ey, ez, endReg);
	}
      }
      if( endReg<0 ) vtxReg = -1;
    }

    // distance travelled through detector
    if( vtxReg>=0 && endReg>=0 ){
      ds = sqrt( (ex-vx)*(ex-vx)
                +(ey-vy)*(ey-vy)
	        +(ez-vz)*(ez-vz) );
    }

    // possible track
    possible_track = 0;
    if( fabs(ipdg)==13 || fabs(ipdg)==11 
  // || fabs(ipdg)==211 || fabs(ipdg)==321 // <- no idea if this is right...
     || fabs(ipdg)==2212 || ipdg==22 ){
      if( trkK>0.0 ){
        beta = trkP/trkE;
        if( trkP/trkE>0.75 ){
          possible_track = 1;
        }
      }
    }

    // new track
    new_track = 0;
    if( possible_track ){
      if( nTrack>=2 
       && trkK>fEnergyThreshold
       && ds>fRangeThreshold ){
        new_track = 1;
      }
    }
  
    // make new track
    // ==============
    if( new_track ){
      WCSimTrueTrack* trueTrack = new WCSimTrueTrack(ipdg,ipdgparent,
                                                     g4vx,g4vy,g4vz,
                                                     g4ex,g4ey,g4ez,
                                                     vx,vy,vz,
                                                     ex,ey,ez,
                                                     px,py,pz,
                                                     trkE,trkP,trkM);
      WCSimTrueEvent::Instance()->AddTrack(trueTrack);

      fTrackList->push_back(trueTrack);
    }

    // print out track info
    std::cout << "   [" << nTrack; if( new_track) std::cout << "*"; std::cout << "] iflag=" << iflag << " pdg=" << ipdg << ", p=" << trkP << " E=" << trkE << " K=" << trkK << std::endl;
    std::cout << "     g4vtx=(" << g4vx << "," << g4vy << "," << g4vz << "), g4end=(" << g4ex << "," << g4ey << "," << g4ez << ") " << std::endl;
    std::cout << "     g4dir=(" << px << "," << py << "," << pz << "), g4trk=(" << qx << "," << qy << "," << qz << ")" << std::endl;
    std::cout << "     vtx=(" << vx << "," << vy << "," << vz << "), end=(" << ex << "," << ey << "," << ez << ") " << std::endl;
    std::cout << "     ds=" << ds << " beta=" << beta << " fom=" << trkE-1.5*trkM;
    if( new_track ) std::cout << " [TRACK] "; // PRINT: MAKE TRACK
    std::cout << std::endl; // PRINT: NEW LINE

    // print warning messages
    if( vtxReg<0 ){
      std::cout << "      <warning> couldn't find detector entry point! " << std::endl;  
    }

    if( endReg<0 ){
      std::cout << "      <warning> couldn't find detector exit point! " << std::endl;  
    }
  }
      
  // assign primary track
  WCSimTrueTrack* myTrack = WCSimTrueEvent::Instance()->GetPrimaryTrack();

  if( myTrack ){
    primeIpdg = myTrack->GetPDG();
    primeG4Vx = myTrack->GetG4VtxX();
    primeG4Vy = myTrack->GetG4VtxY();
    primeG4Vz = myTrack->GetG4VtxZ();
    primeG4Ex = myTrack->GetG4EndX();
    primeG4Ey = myTrack->GetG4EndY();
    primeG4Ez = myTrack->GetG4EndZ();
    primeVx = myTrack->GetVtxX();
    primeVy = myTrack->GetVtxY();
    primeVz = myTrack->GetVtxZ();
    primeEx = myTrack->GetEndX();
    primeEy = myTrack->GetEndY();
    primeEz = myTrack->GetEndZ();
    primePx = myTrack->GetDirX();
    primePy = myTrack->GetDirY();
    primePz = myTrack->GetDirZ();
    primeTrkE = myTrack->GetEnergy();  
    primeTrkP = myTrack->GetMomentum();
    primeTrkM = myTrack->GetMass();
  }

  // set true event header
  WCSimTrueEvent::Instance()->SetHeader(primeIpdg,
                                        primeG4Vx,primeG4Vy,primeG4Vz,
                                        primeVx,primeVy,primeVz,
                                        primeEx,primeEy,primeEz,
                                        primePx,primePy,primePz,
                                        primeTrkE,primeTrkP,primeTrkM);

  std::cout << "  true event info: " << std::endl
            << "   Ipdg = " <<  primeIpdg << std::endl
            << "   G4 Vertex = (" << primeG4Vx << "," << primeG4Vy << "," << primeG4Vz << ") " << std::endl
            << "   G4 End = (" << primeG4Ex << "," << primeG4Ey << "," << primeG4Ez << ") " << std::endl
            << "   Vertex = (" << primeVx << "," << primeVy << "," << primeVz << ") " << std::endl
            << "   End = (" << primeEx << "," << primeEy << "," << primeEz << ") " << std::endl
            << "   Direction = (" << primePx << "," << primePy << "," << primePz << ") " << std::endl
            << "   Energy = " << primeTrkE << " MeV" << std::endl;

  return;
}


void WCSimInterface::BuildRecoEvent(WCSimRootTrigger* myTrigger)
{

  this->BuildRecoEvent(myTrigger, fusetruth);

}

void WCSimInterface::BuildRecoEvent(WCSimRootTrigger* myTrigger, bool usetruth)
{
  // Reset
  // =====
  this->ResetRecoEvent();

  // check for trigger
  // =================
  if( myTrigger == 0 ){
    return;
  }

  // Build Reco Event
  // ================
  std::cout << " *** WCSimInterface::BuildRecoEvent(...) *** " << std::endl;

  // write header
  // ============
  Int_t runNum = myTrigger->GetHeader()->GetRun();
  Int_t eventNum = myTrigger->GetHeader()->GetEvtNum();
  Int_t triggerNum = myTrigger->GetHeader()->GetSubEvtNumber();

  WCSimRecoEvent::Instance()->SetHeader(runNum,eventNum,triggerNum);

  // get array of digitized (or true) hits
  Int_t tube, region, rawPEtube;
  Double_t rawQ,rawT,calcQ,calcT,x,y,z;

  if(!usetruth){

    TClonesArray* fDigiHitArray = (TClonesArray*)(myTrigger->GetCherenkovDigiHits());

    // loop over digits
    // ================
    for( Int_t nDigit=0; nDigit<1+fDigiHitArray->GetLast(); nDigit++ ){
            
      WCSimRootCherenkovDigiHit* myDigit = (WCSimRootCherenkovDigiHit*)(fDigiHitArray->At(nDigit));
      tube = myDigit->GetTubeId();
      rawQ = myDigit->GetQ();
      rawT = myDigit->GetT();
      rawPEtube = 1; //ht # of photons per PMT is not saved in WCSim for DigiHit 
      
      calcQ = rawQ;
      calcT = rawT - WCSimParameters::TimeSlew(rawQ);
      
      region = WCSimGeometry::Instance()->GetRegion(tube);
      x = WCSimGeometry::Instance()->GetX(tube);
      y = WCSimGeometry::Instance()->GetY(tube);
      z = WCSimGeometry::Instance()->GetZ(tube);

      //std::cout<<x<<" "<<y<<" "<<z<<" "<<calcT<<std::endl;

      WCSimRecoDigit* recoDigit = new WCSimRecoDigit(region,
						     x, y, z,
						     rawT, rawQ, rawPEtube,
						     calcT, calcQ);
      
      WCSimRecoEvent::Instance()->AddDigit(tube,recoDigit);
      
      fDigitList->push_back(recoDigit);
    }
  }
  else{

    //Ioana... comment this all for using old files
        
    std::cout<<"IAMHERE!!!!!!!!!!!!!!!!!!!"<<std::endl;

    TClonesArray *WCHitCoorsArray = myTrigger->GetCherenkovHitCoordinates();
    TClonesArray *WCHitsArray = myTrigger->GetCherenkovHits();
    
    int totalPe = 0;
    int ncherenkovhits = myTrigger->GetNcherenkovhits();


    std::cout<<"now I am HEREEEEE!!!! "<<ncherenkovhits<<std::endl;
    
    //TF1 *f1 = new TF1("f1","exp(-0.5*(x/fTimeSmear)*(x/fTimeSmear))",0,1);
    TRandom3 timeRand;
    Double_t mean = 0.0;
    //std::cout << "timeRand->TRandom::Gaus(0.,fTimeSmear) = " << timeRand.Gaus(mean,fTimeSmear) << std:: endl;
    
    for (int i=0; i< ncherenkovhits; i++)
      {
        //std::cout << "chrenkovhit " << i << std::endl;
      
	WCSimRootCherenkovHit *wcsimrootcherenkovhit = (WCSimRootCherenkovHit*)(WCHitsArray->At(i));
	
	tube = wcsimrootcherenkovhit->GetTubeID();
        Int_t timeArrayIndex = wcsimrootcherenkovhit->GetTotalPe(0);
        Int_t peForTube = wcsimrootcherenkovhit->GetTotalPe(1);
        totalPe += peForTube;
	
	for (int j = timeArrayIndex; j < timeArrayIndex + peForTube; j++)
        {
	
	WCSimRootCherenkovHitCoordinate* HitCoordinate = (WCSimRootCherenkovHitCoordinate*)(WCHitCoorsArray->At(j));
	
	rawT = (HitCoordinate->GetTrueHit()).at(0);
	calcT = (HitCoordinate->GetTrueHit()).at(0);
	
	if(fsmeartruth){ 
	  //TF1 *f1 = new TF1("f1","exp(-0.5*((x-mean)/fTimeSmear)*((x-mean)/fTimeSmear))",0,1);
   	  //double tSmr = f1->GetRandom();
	  
	  Double_t tSmr= timeRand.Gaus(mean,fTimeSmear);
	
	  rawT += tSmr;
	  calcT += tSmr;
	}
	
	rawQ = 1; // 1
	calcQ = 1; // 1
	
	if(fPMTspace){  // use PMT position
          x = WCSimGeometry::Instance()->GetX(tube);
          y = WCSimGeometry::Instance()->GetY(tube);
          z = WCSimGeometry::Instance()->GetZ(tube);
	  
	  //region = (WCSimGeometry::Instance())->SetRegion(x,y,z); //set the region for hit
        }
        else{
      	  x=((HitCoordinate->GetTrueHit()).at(1))/10.;
	  y=((HitCoordinate->GetTrueHit()).at(2))/10.;
	  z=((HitCoordinate->GetTrueHit()).at(3))/10.;
	  
	  //region = 1;
	  //rawQ = 1; calcQ = 1;
	}
	
	region = (WCSimGeometry::Instance())->GetRegion(tube); //set the region for PMT
	
	//std::cout<<x<<" "<<y<<" "<<z<<" "<<calcT<<std::endl;
			
	WCSimRecoDigit* recoDigit = new WCSimRecoDigit(region,
						       x, y, z,
						       rawT, rawQ, peForTube,
						       calcT, calcQ);
	
	if((fPMTspace && j==timeArrayIndex) || !fPMTspace){
          WCSimRecoEvent::Instance()->AddDigit(tube,recoDigit);
	/*
	if( i%154==0 && j==timeArrayIndex ) {
	std::cout << "for i=" << i << " && j=timeArrayIndex: " << tube << " " << x << " " << y << " " << z << " " << calcT << " " << calcQ << std::endl;
	std::cout << "for i=" << i << " " << ((HitCoordinate->GetTrueHit()).at(1))/10. << " " << ((HitCoordinate->GetTrueHit()).at(2))/10. << " " << ((HitCoordinate->GetTrueHit()).at(3))/10. << std::endl;
	}
	*/
	  fDigitList->push_back(recoDigit);
        }					    
   
       }
    }
    
   std::cout<<"DONE DONE DONE"<<std::endl;
   
  }
    
  std::cout << "   Number of Digits = " << WCSimRecoEvent::Instance()->GetNDigits() << std::endl;

  return;
}
