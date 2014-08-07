{
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit.so"); 
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot");
  gSystem->Load("libWCSimAnalysis.so");
    
  // Load Data
  // =========

  WCSimInterface::LoadData("/lbne/app/users/wetstein/WCSim/branches/dev/DetectorDevelopment/wcsim.root");
  WCSimInterface::LoadEvent(0);
  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();

  Double_t trueVtxX = trueEvent->GetVtxX();
  Double_t trueVtxY = trueEvent->GetVtxY();
  Double_t trueVtxZ = trueEvent->GetVtxZ(); 
 
 
  Double_t trueDirX = trueEvent->GetDirX();
  Double_t trueDirY = trueEvent->GetDirY();
  Double_t trueDirZ = trueEvent->GetDirZ();

  std::cout<<"TRUTH: "<<trueVtxX<<" "<<trueVtxY<<" "<<trueVtxZ<<" "<<trueDirX<<" "<<trueDirY<<" "<<trueDirZ<<std::endl;


  // Open the file
  TFile file("/lbne/app/users/wetstein/WCSim/branches/dev/DetectorDevelopment/wcsim.root");
  
  // Get the a pointer to the tree from the file
  TTree *tree = (TTree*)file->Get("wcsimT");
  
  // Get the number of events
  int nevent = tree->GetEntries();
  printf("nevent %d\n",nevent);
  
  // Create a WCSimRootEvent to put stuff from the tree in

  WCSimRootEvent* wcsimrootsuperevent = new WCSimRootEvent();

  // Set the branch address for reading from the tree
  TBranch *branch = tree->GetBranch("wcsimrootevent");
  branch->SetAddress(&wcsimrootsuperevent);

  // Force deletion to prevent memory leak 
  tree->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);

  // start with the main "subevent", as it contains most of the info
  // and always exists.
  WCSimRootTrigger* wcsimrootevent;
  tree->GetEntry(0); 
  wcsimrootevent = wcsimrootsuperevent->GetTrigger(0);

  SandBoxDigitizer* mDigitize = new SandBoxDigitizer(wcsimrootevent,"test");  

  //  mDigitize->SetPMT(1.0,1.0,false,true);
  mDigitize->SetMCP(1.0,0.0);

  mDigitize->Digitize();
  TH1D* ttt = mDigitize->getdiagnostic(0);
  TH1D* td =  mDigitize->getdiagnostic(1);
  //  TH1D* sd =  mDigitize->getdiagnostic(2);
  TH1D* qd =  mDigitize->getdiagnostic(3);
  
  ttt->Draw();
  TCanvas *c2 = new TCanvas();
  td->Draw();
  //  TCanvas *c3 = new TCanvas();
  //  sd->Draw();
  TCanvas *c4 = new TCanvas();
  qd->Draw();
  
 
  TFile* mf = new TFile("ungatedPMT_2nsB.root","RECREATE");
  ttt->Write("time_ungatedPMT_2ns");
  td->Write("timediff_ungatedPMT_1ns");
  qd->Write("Q_ungatedPMT_2ns");
  mf->Close();
 

  /*
  WCSimRecoEvent* newdigits = SandBoxDigitizer::RecoEvent();

  TH1D* testtime = new TH1D("tty","tty",1000,1.,5000.);

  for(int i=0; i<newdigits->GetNDigits(); i++){
    
    WCSimRecoDigit* aDigit = newdigits->GetDigit(i);
    double tEnd = aDigit->GetTime();

    //    std::cout<<i<<" "<<tEnd<<std::endl;

    testtime->Fill(tEnd);
    
  }

  testtime->Draw();
  */

  /*
  mDigitize->MakeHitsHistogram();

  ttt->Draw();
  //  mDigitize->FindNumberOfGatesFast();
  mDigitize->Digitize();  
  */

  std::cout<<"DONE YO"<<std::endl;

    /*
  WCSimInterface::LoadData("/lbne/app/users/wetstein/WCSim/branches/dev/DetectorDevelopment/wcsim.root");
  WCSimInterface::SetToUseTrueHits();
  WCSimInterface::LoadEvent(0);

  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
  int myNdigits = recoEvent->GetNDigits();

  TH1D* testtime = new TH1D("tt","tt",100,1.,1000.);
  for(int i=0.; i<myNdigits; i++){

    WCSimRecoDigit* adigit = recoEvent->GetDigit(i);
    double xEnd = adigit->GetX();
    double yEnd = adigit->GetY();
    double zEnd = adigit->GetZ();
    double tEnd = adigit->GetTime();

    testtime->Fill(tEnd);

  }

  testtime->Draw();
    */

}
