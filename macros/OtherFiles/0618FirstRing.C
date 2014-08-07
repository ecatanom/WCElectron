/*Este programa imprime event displays para un eventos 
Aplica filtros simples
No usa DisplayViewer
*/

{

  // Load libraries
  // ==============
  //gROOT->Reset();
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");
  
  // Path to WCSim ROOT file
  // =======================
  TString filename("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_MuSct_Ion.root");
  Double_t TResid, LPhot, LMuon, Oangle;
  double bdeltaT, rdeltaT;
  Double_t trueX ;
  Double_t trueY;
  Double_t trueZ ;
  Double_t dirX ;
  Double_t dirY ;
  Double_t dirZ ;
  Double_t trueT ;
  double theta ;
  int myNdigits;
  int NFilterdigits;

  int myeventnumber=0;
  int badevents[]={0, 109, 111, 116, 118, 127, 178, 188, 214, 227, 230, 236, 243, 250, 267, 275, 276, 277, 295, 303, 312, 322, 326, 330, 331, 345, 353, 359, 369, 370, 377, 379, 38, 403, 404, 405, 408, 411, 416, 432, 439, 441, 446, 447, 486, 493, 495, 532, 534, 541, 566, 578, 589, 599, 610, 616, 635, 636, 641, 643, 646, 653, 660, 663, 673, 674, 704, 705, 730, 75, 764, 780, 790, 799, 81, 824, 82, 831, 838, 857, 911, 91, 925, 957, 95, 985, 992}; ///bad events!!!!!
  int goodevents[]={100, 114, 122, 145, 146, 156, 161, 165, 173, 175, 184, 185, 196, 197, 198, 205, 206, 210, 213, 219, 21, 222, 226, 249, 258, 263, 265, 274, 279, 283, 284, 296, 29, 302, 304, 30, 320, 325, 329, 336, 338, 339, 34, 357, 362, 363, 381, 391, 392, 406, 418, 443, 452, 459, 468, 485, 492, 501, 514, 516, 521, 54, 558, 569, 57, 582, 586, 592, 601, 619, 622, 624, 647, 661, 710, 724, 72, 738, 739, 746, 750, 757, 771, 775, 779, 794, 810, 812, 822, 853, 859, 85, 860, 862, 866, 878, 893, 904, 909, 919, 922, 926, 945, 964, 96, 975, 97, 981};

  //int mynevents = sizeof(events)/sizeof(events[0]);

  //-------------------------------------------------------------------------------------- 




  // Load Data
  // =========
  WCSimInterface::LoadData(filename);

  // get first entry
  Bool_t truehit = 1; // 1 is to use true hits
  Bool_t filtered = 1; // 1 is to use Andy's cut
  Bool_t Lmu = 0; // 1 is to use LMuon cut
  Double_t sigma0 = 1.0; //sigma0 = 0.1;
  if(truehit) {WCSimInterface::SetToUseTrueHits();
    WCSimInterface::Instance()->SmearTrueHits(sigma0);}

  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);
  WCSimDataCleaner::Instance()->SetNeighbourRadius(300.0); 
  WCSimDataCleaner::Instance()->SetNeighbourDigits(50.0);
  WCSimDataCleaner::Instance()->SetClusterRadius(300.0);
  WCSimDataCleaner::Instance()->SetClusterDigits(50.0);
  WCSimDataCleaner::Instance()->SetTimeWindowNeighbours(25.0);
  WCSimDataCleaner::Instance()->SetTimeWindowClusters(25.0);

  WCSimInterface::Instance()->SetToMCP();
  //WCSimInterface::Instance()->SetToGated();


 // ring finder configuration
  // =========================
  //WCSimVertexFinder::SeedWithSimpleVertex(0);  
  
  //WCSimVertexFinder::UseTrueVertex(); // use true vertex
 
  WCSimRingFinder::UseRecoVertex();  
  WCSimVertexFinder::PointFitOnly();  
 
//---------------------------

  Bool_t showmethering=1; //find and show me the reco ring
    
  //--------------------------------------------------------------------------------------
  
  WCSimDisplayAB* myfakedisplay=new WCSimDisplayAB();
  myfakedisplay->PrintGIF();

  for(int ecounter=0;ecounter<5;ecounter++){
    myeventnumber=badevents[ecounter];
    WCSimInterface::LoadEvent(myeventnumber);
    
    WCSimRecoEvent* theRecoEvent;
    WCSimTrueEvent* theTrueEvent;
    theRecoEvent = WCSimInterface::RecoEvent();
    theTrueEvent = WCSimInterface::TrueEvent();
    WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
    if(filtered) haReco->RunFilter(theRecoEvent);
    if(showmethering) haReco->Run(theRecoEvent);
    
    haReco->RunRecoVertex(theRecoEvent);
    //myfakedisplay->SetFakeVertex(1051.09,2549.22,-3689.69,0.378877,-0.74181,0.553326);
    myfakedisplay->SetFakeVertex(theRecoEvent->GetVtxX(),theRecoEvent->GetVtxY(),theRecoEvent->GetVtxZ(), theRecoEvent->GetDirX(), theRecoEvent->GetDirY(), theRecoEvent->GetDirZ());
    
    myfakedisplay->DrawDisplay(theRecoEvent);
    myfakedisplay->DrawTrueEvent(theTrueEvent);
    myfakedisplay->DrawRecoEvent(theRecoEvent);
    myfakedisplay->PrintDisplay();
cout <<"=====bad========================================"<<ecounter<<endl;
  }
  return;
  //-----------------------------------------------------
 for(int ecounter=0;ecounter<3;ecounter++){
    myeventnumber=goodevents[ecounter];
    WCSimInterface::LoadEvent(myeventnumber);
    
    WCSimRecoEvent* theRecoEvent;
    WCSimTrueEvent* theTrueEvent;
    theRecoEvent = WCSimInterface::RecoEvent();
    theTrueEvent = WCSimInterface::TrueEvent();
    WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
    if(filtered) haReco->RunFilter(theRecoEvent);
    if(showmethering) haReco->Run(theRecoEvent);
    
    haReco->RunRecoVertex(theRecoEvent);
    //myfakedisplay->SetFakeVertex(1051.09,2549.22,-3689.69,0.378877,-0.74181,0.553326);
    myfakedisplay->SetFakeVertex(theRecoEvent->GetVtxX(),theRecoEvent->GetVtxY(),theRecoEvent->GetVtxZ(), theRecoEvent->GetDirX(), theRecoEvent->GetDirY(), theRecoEvent->GetDirZ());
    
    myfakedisplay->DrawDisplay(theRecoEvent);
    //myfakedisplay->DrawTrueEvent(theTrueEvent);
    //myfakedisplay->DrawRecoEvent(theRecoEvent);
    myfakedisplay->PrintDisplay();
cout <<"=====good========================================"<<ecounter<<endl;
  }




  return;
  

WCSimInterface::LoadEvent(100);


  WCSimDisplayViewer* viewer = new WCSimDisplayViewer();
 
  // type of display
  // ===============
  viewer->UseDisplay("AB");      // Default Display
  //viewer->UseDisplay("Vtx");   // Vertex Display
  //viewer->UseDisplay("Eve");   // 3D Display


  // Bool_t fUseFakeInfo;//erika
//   Double_t fakex0,fakey0, fakez0;
//   Double_t fakepx,fakepy, fakepz;
 

  // configuration
  // =============
  viewer->ApplyCuts();
  //viewer->DisplayRecoClusters();  // display clusters
  viewer->DisplayRecoEvent();        // display vertex
  viewer->DisplayTrueEvent();        // display truth

  // display configuration
  // =====================
  viewer->SetPulseHeightCut(-1.0);
  viewer->PrintGIF();
  // viewer->PrintEPS();

  // ring finder configuration
  // =========================
  //WCSimVertexFinder::SeedWithSimpleVertex(0);  
  WCSimVertexFinder::UseTrueVertex(); // use true vertex
  //WCSimRingFinder::UseRecoVertex();   // don't run ring finder
  // WCSimVertexFinder::PointFitOnly();  
//---------------------------
  
  //viewer->WCSimDisplayAB::UseFakeVertex(1);
  viewer->controlStart();
  //viewer->UpdateDisplay(123);
  //viewer->PrintDisplayList();  
  WCSimDisplayAB::Instance()->SetFakeVertex(0.,0.,0.,0.,0.,0.);
  viewer->UpdateDisplay(109);

  //--------------------------------------------------------------------------------------

//   for(int ecounter=0;ecounter<1;ecounter++){
//     //for(int ecounter=0;ecounter<mynevents;ecounter++){
     
//     myeventnumber=goodevents[ecounter];
//     viewer->UpdateDisplay(myeventnumber); //This includes loading the event
//     viewer->controlPrint();
   
     
//     cout <<"===good=========================================="<<ecounter<<endl;
//   }//Loop over event list

// for(int ecounter=0;ecounter<1;ecounter++){
//     //for(int ecounter=0;ecounter<mynevents;ecounter++){
     
//     myeventnumber=badevents[ecounter];
//     viewer->UpdateDisplay(myeventnumber); //This includes loading the event
//     viewer->controlPrint();
   
     
//     cout <<"=====bad========================================"<<ecounter<<endl;
//   }
//Loop over event list


}
