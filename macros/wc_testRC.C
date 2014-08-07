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


  
  RasterizeCircle* rc = new RasterizeCircle(200,-100.5,100.5,200,-100.5,100,200,-100.5,100.5);

  // TVector3 testV(100,800,-10);
  //  TVector3 testV(10,20,800);


  vector<double> testV;
  testV.push_back(500.);
  testV.push_back(80.);
  testV.push_back(100.);
  //  TH3D* therc = rc->Rasterize3Dspeedorder(testV,0.5,80.,0,1,2);
  rc->Rasterize3D(testV,0.5,80.);

  vector<double> testV2;
  testV2.push_back(100.);
  testV2.push_back(-800.);
  testV2.push_back(-20.);
  rc->Rasterize3D(testV2,0.8,40.);

  vector<double> testV2;
  testV2.push_back(-100.);
  testV2.push_back(-20.);
  testV2.push_back(-10.);
  rc->Rasterize3D(testV2,0.4,20.);

  TH3D* therc = rc->returnhisto();




  //  TH3D* therc = rc->Rasterize3Dspeedorder(testV,0.5,80.,0,1,2);
  //  TH3D* therc = rc->Rasterize3Dspeedorder(testV,0.7,80.,0,1,2);

  //  TH3D* therc = rc->Rasterize3Dspeedorder(testV,0.5,80.,0,2,1);
  //  TH3D* therc = rc->Rasterize3Dspeedorder(testV,0.5,80.,2,1,0);
  //  TH3D* therc = rc->Rasterize3Dspeedorder(testV,0.6,80.,1,2,0);

  // TVector3 testV(100,100,-800);
  // therc = rc->Rasterize3Dspeedorder(testV,0.6,80.,0,1,2);
  

  therc->SetMarkerSize(0.2);
  therc->GetXaxis()->SetTitle("x axis");
  therc->GetZaxis()->SetTitle("z axis");

  /*
  TVector3 testV2(100,-600,-10);
  TH3D* thercB = rc->Rasterize3D(testV2,0.6,20.,200,-100.5,100.5);

  TVector3 testV3(100,-100,900);
  TH3D* thercC = rc->Rasterize3D(testV3,0.6,80.,200,-100.5,100.5);
  */
  //  therc->Add(thercB,1);
  //  therc->Add(thercC,1);
  therc->SetMarkerColor(2);
  therc->Draw("box");
  

  /*
  // Initialize Reconstruction
  // =========================
  WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();
  

  // Reconstruct Event
  // =================

  // get first entry
  chain->GetEntry(0);

  // build event
  WCSimInterface::BuildEvent(myEvent);
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
