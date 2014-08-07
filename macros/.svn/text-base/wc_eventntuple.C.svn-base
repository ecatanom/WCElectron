{
 
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit"); 
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

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
  WCSimInterface::LoadData("/lbne/data/water/sim200kton_20111017/singleparticle/rootfiles/muon_minus_001600MeV_200kton.0001.root");
  //WCSimInterface::LoadData("/r01/lbne/water/wcsim_root_files/DUSEL_200kton_12inch_10perCent/muon_minus_001600MeV_200kton.0001.root");

  // Create Ntuple Writer
  // ====================
  WCSimNtupleWriter* ntpwriter = new WCSimNtupleWriter();

  // type of ntuple
  // ==============
  ntpwriter->UseNtuple("Reco");
  // ntpwriter->UseNtuple("Vertex");
  // ntpwriter->UseNtuple("VertexSeed");

  // set file name
  // =============
  ntpwriter->SetFileName("ntuple.reco.muon.root");

  // loop over events
  // =================
  ntpwriter->Run(10);

  WCSimRecoObjectTable::Instance()->Print();
 
}
