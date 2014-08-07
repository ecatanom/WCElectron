{
  
  // Path to WCSim ROOT file
  // =======================
  TString filename("/lbne/wcsim_root_files/DUSEL_100kton_10inch_40perCent/muon_vtx_20001_wcsim.root");
  

  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");

  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

  WCSimIsoChronTransform* myisotest = new WCSimIsoChronTransform();

  ifstream InFile("../IsoChron/FakeMuonSample2trksPerfecRes.txt", ios::in);
  
  double xEnd,yEnd,zEnd,tEnd,wt;

  int hitcount=0;
  
  vector< vector<double> > thehits;
  vector<double> hypVtx;

  WCSimWaterModel* wmwm = new WCSimWaterModel();
  //  cout<<myWM<<endl;
  cout<<"test: "<<wmwm->N_Index(222)<<endl;;

  hypVtx.push_back(0.);
  hypVtx.push_back(0.);
  hypVtx.push_back(0.);
  hypVtx.push_back(0.);

  int hitcount=0;
  while((!InFile.eof()) && (hitcount<50000) ) {

    if(hitcount<50000){
      
      if(hitcount%10000==0) cout<<"reading file...hitcount: "<<hitcount<<endl;

      InFile >> xEnd >> yEnd >> zEnd >> tEnd; 
      wt=1;

      vector<double> hitcoordinates;  hitcoordinates.push_back(xEnd);  hitcoordinates.push_back(yEnd);  
      hitcoordinates.push_back(zEnd);  hitcoordinates.push_back(tEnd);
      thehits.push_back(hitcoordinates);
      hitcount++;
    }
  }

  myisotest->ApplyTransform(thehits, hypVtx);

  TH2D* myxzproj = myisotest->XZProjection();
  gROOT->SetStyle("Plain"); 
  
  gStyle->SetPalette(1);
  myxzproj->Draw("colz");
  

  /*
  // Initialize Reconstruction
  // =========================
  WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();
  

  // Reconstruct Event
  // =================

  // get first entry
  WCSimInterface::LoadData(filename.Data());

  // build event
  WCSimInterface::LoadEvent(0);
  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();

  // run reconstruction
  myReco->Run(recoEvent);

  // get reconstructed quantities
  Double_t recoVtxX = recoEvent->GetVtxX();
  Double_t recoVtxY = recoEvent->GetVtxY();
  Double_t recoVtxZ = recoEvent->GetVtxZ();
  Double_t recoDirX = recoEvent->GetDirX();
  Double_t recoDirY = recoEvent->GetDirY();
  Double_t recoDirZ = recoEvent->GetDirZ();

  std::cout << "  recoVtx=(" << recoVtxX << ", " << recoVtxY << ", " << recoVtxZ << std::endl
            << "           " << recoDirX << ", " << recoDirY << ", " << recoDirZ << ") " << std::endl;

  // Interface to MC Truth
  //======================

  // get true quantities
  Double_t trueVtxX = trueEvent->GetVtxX();
  Double_t trueVtxY = trueEvent->GetVtxY();
  Double_t trueVtxZ = trueEvent->GetVtxZ();  
  Double_t trueDirX = trueEvent->GetDirX();
  Double_t trueDirY = trueEvent->GetDirY();
  Double_t trueDirZ = trueEvent->GetDirZ();

  std::cout << "  trueVtx=(" << trueVtxX << ", " << trueVtxY << ", " << trueVtxZ << std::endl
            << "           " << trueDirX << ", " << trueDirY << ", " << trueDirZ << ") " << std::endl;

  */
}
