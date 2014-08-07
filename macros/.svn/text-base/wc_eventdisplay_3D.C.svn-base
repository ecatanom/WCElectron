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
  //WCSimInterface::LoadData("/r01/lbne/water/wcsim_root_files/DUSEL_200kton_12inch_10perCent/muon_minus_001600MeV_200kton.0001.root");

  //  WCSimInterface::LoadData("/lbne/data/water/sim200kton_20110804/singleparticle/rootfiles/muon_minus_002400MeV_200kton.0008.root");

  //  WCSimInterface::LoadData("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents_newWCSim/Evt18.root");
  WCSimInterface::LoadData("/lbne/app/users/wetstein/WCSim/branches/dev/DetectorDevelopment/wcsim.root");
  WCSimInterface::SetToUseTrueHits();


  // create viewer: must be called 'viewer'
  // =====================================
  WCSimDisplayViewer* viewer = new WCSimDisplayViewer();
 
  // for EVE display
  // ===============
  viewer->UseDisplay("3D"); 

}
