{
 
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");


  // Load Data
  // =========
  WCSimInterface::LoadData("/lbne/data/water/sim200kton_20111017/singleparticle/rootfiles/muon_minus_001600MeV_200kton.0001.root");
  //WCSimInterface::LoadData("/r01/lbne/water/wcsim_root_files/DUSEL_200kton_12inch_10perCent/muon_minus_001600MeV_200kton.0001.root");

  // Initialize Reconstruction
  // =========================
  WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();
  

  // Reconstruct Event
  // =================

  // get first entry
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

}
