{

  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

  WCSimRecoParameters::PrintParameters();
  WCSimDataCleaner::PrintParameters();
  WCSimVertexFinder::PrintParameters();
  WCSimRingFinder::PrintParameters();

  WCSimRecoNtuple* recoana = new WCSimRecoNtuple();

  recoana->Reset();
  recoana->AddFile("/r01/lbne/water/wcsim_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_12001.root");
  recoana->SetFileName("ntuple.test.2.root");
  recoana->Run(500,1000);

}
