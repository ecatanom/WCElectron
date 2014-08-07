{

  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");  
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

  WCSimEventWriter* writer = new WCSimEventWriter();

  writer->AddFile("/lbne/data/water/sim200kton_20111017/singleparticle/rootfiles/muon_minus_001600MeV_200kton.0001.root");
  //writer->AddFile("/r01/lbne/water/wcsim_root_files/DUSEL_200kton_12inch_10perCent/muon_minus_001600MeV_200kton.0001.root");

  writer->WriteOutGeometry();
  writer->WriteOutTracks();
  writer->WriteOutDigits();

  writer->Run(10);


}
