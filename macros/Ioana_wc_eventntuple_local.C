
{
  cout <<"1" << endl;
  gSystem->Load("libGeom");
  cout <<"2" << endl;
  gSystem->Load("libEve");
  cout <<"3" << endl;
  gSystem->Load("libMinuit");
  cout <<"4" << endl; 
  gSystem->Load("libCintex");
  cout <<"5" << endl;
  Cintex::Enable();
  cout <<"6" << endl;
  gSystem->Load("libWCSimRootDict");
  cout <<"7" << endl;
  gSystem->Load("libWCSimRoot.so");
  cout <<"8" << endl;
  gSystem->Load("libWCSimAnalysis.so");
  cout <<"9" << endl;
  
  //string inputFile = "muon_minus_000400MeV_200kton.0000";
  //string inputFile = "muon_plus_000800MeV_200kton.0000";
  //string inputFile = "muon_plus_001200MeV_200kton.0000";
  //string inputFile = "muon_plus_001200MeV_200kton.0001_13percentbare";
  //string inputFile = "muon_plus_002000MeV_200kton.0000";
  //string inputFile = "muon_plus_002400MeV_200kton.0000";
  //string inputFile = "muon_plus_002800MeV_200kton.0000";
  //string inputFile = "muon_plus_003200MeV_200kton.0000";
  //string inputFile = "muon_plus_003600MeV_200kton.0000";
  //string inputFile = "muon_plus_004000MeV_200kton.0000";
  //string inputFile = "muon_plus_004400MeV_200kton.0000";
  //string inputFile = "muon_plus_004800MeV_200kton.0000";
  //string inputFile = "wcsim";
  string inputFile = "muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_noMuSct_Ion";
  //string inputFile = "singlemuon_10ev_12percent";
  
  string type = "Reco";

  // Configuration
  // =============
  WCSimRingFinder::UseRecoVertex();      // suppress ring finder

  // Print Parameters
  // ================
  WCSimParameters::PrintParameters();
  WCSimDataCleaner::PrintParameters();
  WCSimVertexFinder::PrintParameters();
  WCSimRingFinder::PrintParameters();

  // Load Data
  // ========= 
  WCSimInterface::LoadData(("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/"+ inputFile +".root").c_str());
  //WCSimInterface::LoadData(("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents_newWCSim/"+ inputFile +".root").c_str());
  //WCSimInterface::LoadData(("/lbne/app/users/txin/WCSim/branches/dev/DetectorDevelopment/"+ inputFile +".root").c_str());
  WCSimInterface::SetToUseTrueHits();
  WCSimInterface::Instance()->SmearTrueHits(0.1);//100 ns=.1 ps change time resoltion characteristic
  WCSimInterface::Instance()->SetToMCP();
  //WCSimInterface::Instance()->SetToGated();

  // Create Ntuple Writer
  // ====================
  WCSimNtupleWriter* ntpwriter = new WCSimNtupleWriter();

  // type of ntuple
  // ==============
  ntpwriter->UseNtuple(type.c_str());
  //ntpwriter->UseNtuple("Reco");
  // ntpwriter->UseNtuple("Vertex");
  // ntpwriter->UseNtuple("VertexSeed");

  // set file name
  // =============
  outfileName = "ntuple_"+type+"_"+inputFile+"testchrom.root";
  ntpwriter->SetFileName(outfileName.c_str());
   //ntpwriter->SetFileName(("ntuple_reco_"+inputFile+".root").c_str());
   //ntpwriter->SetFileName(("ntuple_vertex_"+inputFile+".root").c_str());

  // suppress vertex finder to get a reco time close to true
  //WCSimVertexFinder::UseTrueVertex();

  // loop over events
  // =================
  ntpwriter->Run(2,3); //event numbers, run events between.... i<=x<j, (2,3)runs event 2

  WCSimRecoObjectTable::Instance()->Print();
 
}
