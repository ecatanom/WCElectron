{
 
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");


  WCSimInterface::LoadData("/lbne/data/water/sim200kton_20111017/singleparticle/rootfiles/muon_minus_001600MeV_200kton.0001.root");
  //WCSimInterface::LoadData("/r01/lbne/water/wcsim_root_files/DUSEL_200kton_12inch_10perCent/muon_minus_001600MeV_200kton.0001.root");

  std::cout << "Number of pmts: " << WCSimGeometry::Instance()->GetNumPMTs() << std::endl;
  
  for( Int_t n=1; n<WCSimGeometry::Instance()->GetNumPMTs(); n++ ){
	
    Int_t tube = n;
    Int_t region = WCSimGeometry::Instance()->GetRegion(n);
    Double_t x = WCSimGeometry::Instance()->GetX(n);
    Double_t y = WCSimGeometry::Instance()->GetY(n);
    Double_t z = WCSimGeometry::Instance()->GetZ(n);
  
    std::cout << " [" << n << "] (x,y,z)=(" << x << "," << y << "," << z << ")" << std::endl;

  }


  // Write Geometry to ROOT Ntuple
  // =============================
  // WCSimGeometry::WriteGeometry("wcsim.geometry.test.root");


}
