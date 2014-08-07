{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot");
  gSystem->Load("libWCSimAnalysis");



  // Build Geometry
  // ==============  
  
  //TString cosmicFile("/lbne/data/water/cosmic200kton20110518/rootfiles/cosmic_DUSEL_4850ft_surface_200kton.001.root");

  //TChain* chainGeom = new TChain("wcsimGeoT","chainGeom");

  //WCSimRootGeom* myGeom = new WCSimRootGeom();
  //chainGeom->SetBranchAddress("wcsimrootgeom",&myGeom);
  //chainGeom->Add(cosmicFile.Data());

  // look at first entry (should only be one geometry...)
  //chainGeom->GetEntry(0);

  // build geometry
  //WCSimGeometry::BuildGeometry(myGeom);
  


  // Load Event from Matt
  // ====================

  double hitX;
  double hitY;
  double hitZ;
  double hitT;

  double fScale = 1.0;

  WCSimRecoEvent* myEvent = new WCSimRecoEvent();
  myEvent->SetHeader(0,0,0);

  ifstream inputFile("/lbne/app/users/wetstein/SamplesForTian/1Mu.1GeV.evt0.txt");


  while( inputFile.eof()==0 ){

    hitX = 0.0; hitY = 0.0; hitZ = 0.0; hitT = -99999.9;

    inputFile >> hitX >> hitY >> hitZ >> hitT;

    if( hitT>-99999.9 ){
      WCSimRecoDigit* digit = new WCSimRecoDigit(1, 
                                                 fScale*hitX, fScale*hitY, fScale*hitZ, 
                                                 hitT, 1.0, 
                                                 hitT, 1.0);
      // digit->PassFilter(); // <- needed for newest code
      myEvent->AddDigit(digit);
      myEvent->AddFilterDigit(digit);

    }

  }

  // check digit list
  // ================
  //myEvent->PrintFilterDigitList("digitlist.txt");

  WCSimRecoVertex* myVertex = WCSimVertexFinder::Instance()->RunPointFit(myEvent);


}
