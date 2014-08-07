{
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit.so");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

  // Load Data
  // =========
  // WCSimInterface::LoadData("/r01/lbne/water/wcsim_root_files/DUSEL_200kton_12inch_10perCent/muon_minus_001600MeV_200kton.0001.root");
  // WCSimInterface::LoadData("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_noMuSct_Ion.root");

  WCSimInterface::LoadData("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_MuSct_Ion.root");


  //filename tells you kind of event. cuts are underneath
  //exit root .q
  //

  WCSimInterface::SetToUseTrueHits();
  WCSimInterface::Instance()->SmearTrueHits(0.25);
  WCSimDataCleaner::Instance()->NeighbourRadius(300.0);
  WCSimDataCleaner::Instance()->NeighbourDigits(50.0);
  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);
  WCSimInterface::Instance()->SetToMCP();
  //WCSimInterface::Instance()->SetToGated();
  // create viewer: must be called 'viewer'
  // =====================================
  WCSimDisplayViewer* viewer = new WCSimDisplayViewer();
 
  // type of display
  // ===============
  viewer->UseDisplay("AB");      // Default Display
  //viewer->UseDisplay("Vtx");   // Vertex Display
  //viewer->UseDisplay("Eve");   // 3D Display

  // configuration
  // =============
  viewer->ApplyCuts();
  //viewer->DisplayRecoClusters();  // display clusters
  //viewer->DisplayRecoEvent();        // display vertex
  //viewer->DisplayTrueEvent();        // display truth

  // display configuration
  // =====================
  viewer->SetPulseHeightCut(-1.0);
  viewer->PrintGIF();
  // viewer->PrintEPS();

  // ring finder configuration
  // =========================
  WCSimVertexFinder::UseTrueVertex(); // use true vertex
  // WCSimRingFinder::UseRecoVertex();   // don't run ring finder

}
