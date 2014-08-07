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


  // Set Reco Parameters
  // ===================
  WCSimParameters::UseSimpleTimeSlew();


  // Initialize Reconstruction
  // =========================
  WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();
  
  // Reconstruct Event
  // =================

  // get first entry
  WCSimInterface::LoadEvent(0);

  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();

  myReco->RunFilter(recoEvent); 

  // print list of filtered digits
  recoEvent->PrintFilterDigitList("recoevent.muon.2000MeV.0001.txt");




}
