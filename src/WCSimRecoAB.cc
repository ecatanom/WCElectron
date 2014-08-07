#include "WCSimRecoAB.hh"

#include "WCSimInterface.hh"

#include "WCSimRecoDigit.hh"
#include "WCSimRecoRing.hh"
#include "WCSimRecoEvent.hh"
#include "WCSimRecoVertex.hh"

#include "WCSimGeometry.hh"
#include "WCSimHoughTransform.hh"

#include "WCSimRingFinder.hh"
#include "WCSimVertexFinder.hh"
#include "WCSimVertexGeometry.hh"
#include "WCSimDataCleaner.hh"

#include "TMath.h"

#include <iostream>
#include <cmath>

ClassImp(WCSimRecoAB)

WCSimRecoAB::WCSimRecoAB()
{
 
}

WCSimRecoAB::~WCSimRecoAB()
{

}

void WCSimRecoAB::Run()
{
  WCSimRecoEvent* myEvent = WCSimInterface::RecoEvent();

  this->Run(myEvent);

  return;
}
  
void WCSimRecoAB::Run(WCSimRecoEvent* myEvent)
{

 
  // filter digits
  // =============
  this->RunFilter(myEvent);

  // reconstruct vertex
  // ==================
  this->RunRecoVertex(myEvent);

  // reconstruct rings
  // =================
  this->RunRecoRings(myEvent);

  return;
}

void WCSimRecoAB::RunFilter(WCSimRecoEvent* myEvent)
{  
  // Get Digit List
  // ==============
  std::vector<WCSimRecoDigit*>* myDigitList = (std::vector<WCSimRecoDigit*>*)(myEvent->GetDigitList()); 

  // Reset Filter
  // ============
  for( UInt_t n=0; n<myDigitList->size(); n++ ){
    WCSimRecoDigit* myDigit = (WCSimRecoDigit*)(myDigitList->at(n));
    myDigit->ResetFilter();
  }

  // Get Data Cleaner
  // ================
  WCSimDataCleaner* myDataCleaner = WCSimDataCleaner::Instance();  
  
  // Run Data Cleaner
  // ================
  std::vector<WCSimRecoDigit*>* myFilterDigitList = (std::vector<WCSimRecoDigit*>*)(myDataCleaner->Run(myDigitList));

  // Set Filter
  // ==========
  for( UInt_t n=0; n<myFilterDigitList->size(); n++ ){
    WCSimRecoDigit* myFilterDigit = (WCSimRecoDigit*)(myFilterDigitList->at(n));
    myFilterDigit->PassFilter();
  }

  // Done!
  // =====
  myEvent->SetFilterDone();

  return;
}

void WCSimRecoAB::RunRecoVertex(WCSimRecoEvent* myEvent)
{
  // Run Filter (if necessary)
  // =========================
  if( myEvent->IsFilterDone()==0 ){
    this->RunFilter(myEvent);
  }

  // Check Filter Digits (bail out if necessary)
  // ===========================================
  if( myEvent->GetNFilterDigits()==0 ){
    myEvent->SetVertexFinderDone();
    return;
  }

  // Get Vertex Finder
  // =================
  WCSimVertexFinder* myVertexFinder = WCSimVertexFinder::Instance();

  // Run Vertex Finder
  // =================
  WCSimRecoVertex* myVertex = (WCSimRecoVertex*)(myVertexFinder->Run(myEvent));
    
  // Set Vertex
  // ==========
  myEvent->SetVertex( myVertex );

  // Done!
  // =====
  myEvent->SetVertexFinderDone();

  return;
}

void WCSimRecoAB::RunRecoRings(WCSimRecoEvent* myEvent)
{
  // Find Vertex (if necessary)
  // ==========================
  if( myEvent->IsVertexFinderDone()==0 ){
    this->RunRecoVertex(myEvent);
  }

  // Check Vertex (bail out if necessary)
  // ====================================
  if( myEvent->FoundVertex()==0 ){
    myEvent->SetRingFinderDone();
    return;
  }

  // Get Vertex
  // ==========
  WCSimRecoVertex* myVertex = (WCSimRecoVertex*)(myEvent->GetVertex());

  // Get Ring Finder
  // ===============
  WCSimRingFinder* myRingFinder = WCSimRingFinder::Instance();

  // Run Ring Finder
  // ===============
  std::vector<WCSimRecoRing*>* myRingList = (std::vector<WCSimRecoRing*>*)(myRingFinder->Run(myEvent,myVertex));

  // Add Rings
  // =========
  for( UInt_t n=0; n<myRingList->size(); n++ ){
    WCSimRecoRing* recoRing = (WCSimRecoRing*)(myRingList->at(n));
    myEvent->AddRing(recoRing);
  }

  // Done!
  // =====
  myEvent->SetRingFinderDone();

  return;
}





//Erika
void WCSimRecoAB::RunSuperFilter(WCSimRecoEvent* myEvent)
{  
  std::cout<<"============== FIRST POINT FIT=================="<< std::endl;
  // Get Digit List
  // ==============
  std::vector<WCSimRecoDigit*>* myDigitList = (std::vector<WCSimRecoDigit*>*)(myEvent->GetDigitList()); 

  // Reset Filter
  // ============
  for( UInt_t n=0; n<myDigitList->size(); n++ ){
    WCSimRecoDigit* myDigit = (WCSimRecoDigit*)(myDigitList->at(n));
    myDigit->ResetFilter();
  }

  // Get Data Cleaner
  // ================
  WCSimDataCleaner* myDataCleaner = WCSimDataCleaner::Instance();  
  
  // Run Data Cleaner
  // ================
  std::vector<WCSimRecoDigit*>* myFilterDigitList = (std::vector<WCSimRecoDigit*>*)(myDataCleaner->Run(myDigitList));

  // Set Filter
  // ==========
  for( UInt_t n=0; n<myFilterDigitList->size(); n++ ){
    WCSimRecoDigit* myFilterDigit = (WCSimRecoDigit*)(myFilterDigitList->at(n));
    myFilterDigit->PassFilter();
  }

//   // Done!
//   // =====
  //myEvent->SetFilterDone();

  //vertex
// Get Vertex Finder
  // =================
  WCSimVertexFinder* myVertexFinder = WCSimVertexFinder::Instance();

  // Run Vertex Finder
  // =================
  WCSimRecoVertex* myVertex = (WCSimRecoVertex*)(myVertexFinder->RunPointFit(myEvent));
    
  // Set Vertex
  // ==========
  myEvent->SetVertex( myVertex );

  // Done!
  // =====
  myEvent->SetVertexFinderDone();
  //myEvent->PrintFilterDigitList("listbefore.dat");
  std::cout << "So far I had "<< myEvent->GetNFilterDigits() << " Filter Digits "<<std::endl;

//------------------
    int myNdigits = myEvent->GetNDigits();
   
    int ifilter = 0;
 Bool_t filtered = 1;
    Double_t TResid, LPhot, LMuon, Oangle;

    double trueT= myVertex->GetTime();
    double trueX= myVertex->GetX();
    double trueY= myVertex->GetY();
    double trueZ= myVertex->GetZ();
    double dirX= myVertex->GetDirX();
    double dirY= myVertex->GetDirY();
    double dirZ= myVertex->GetDirZ();
    
    //for(int i=0; i<30; i++){
   for(int i=0; i<myNdigits; i++){
      WCSimRecoDigit* adigit = myEvent->GetDigit(i);
    
      if( adigit->IsFiltered() || !filtered ){ //if the hit passed the filter
	double hitX = adigit->GetX();
	double hitY = adigit->GetY();
	double hitZ = adigit->GetZ();
	double hitT = adigit->GetTime();
	//double qpes = adigit->GetQPEs();
	//double res = WCSimParameters::TimeResolution(qpes); 
	WCSimVertexGeometry::Instance()->LoadEvent(myEvent);
	WCSimVertexGeometry::Instance()->CalcTResid(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle);
	
	if (LMuon>300) adigit->ResetFilter();
	else {ifilter++;}
	
      } //loop of the filter

     
    } //loop over hits

   std::cout << "Now I have "<< myEvent->GetNFilterDigits()<< " Filter Digits "<<std::endl;

   // std::cout<<"============== SECOND FIT=================="<< std::endl;

   myEvent->SetFilterDone();
//    WCSimVertexGeometry::Instance()->SetSameEventOverride(1);
//    WCSimVertexGeometry::Instance()->LoadEvent(myEvent);
//    //std::cout << "WCSimvgeo sees"<<WCSimVertexGeometry::Instance()->GetNFilterDigits()<<std::endl;
   
//  WCSimVertexFinder* mySVertexFinder = WCSimVertexFinder::Instance();

//   // Run Vertex Finder
//   // =================
//   WCSimRecoVertex* mySVertex = (WCSimRecoVertex*)(mySVertexFinder->Run(myEvent));
    
//   // Set Vertex
//   // ==========
//    myEvent->SetVertex( mySVertex );

//   // Done!
//   // =====
//   myEvent->SetVertexFinderDone();

//   /////// Extra: Find rings
//   Bool_t findtherings=1;

//   if(findtherings){
//     // Get Ring Finder
//     WCSimRingFinder* myRingFinder = WCSimRingFinder::Instance();
  
//     // Run Ring Finder
//     std::vector<WCSimRecoRing*>* myRingList = (std::vector<WCSimRecoRing*>*)(myRingFinder->Run(myEvent,mySVertex));

//     // Add Rings
//     for( UInt_t n=0; n<myRingList->size(); n++ ){
//       WCSimRecoRing* recoRing = (WCSimRecoRing*)(myRingList->at(n));
//       myEvent->AddRing(recoRing);
//     }

//     // Done!
//     myEvent->SetRingFinderDone();
//   }

  return;
}
