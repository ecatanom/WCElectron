{

  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

  WCSimVertexNtuple* recoana = new WCSimVertexNtuple();

  recoana->Reset();
  recoana->AddFile("/r01/lbne/water/wcsim_root_files/DUSEL_100kton_10inch_40perCent/muon_vtx_20001_wcsim.root");
  recoana->SetFileName("ntuple.vertex.mu.2000.new.root");
  recoana->Run(250);

  WCSimRecoObjectTable::Instance()->Print();
  gObjectTable->Print();

}
