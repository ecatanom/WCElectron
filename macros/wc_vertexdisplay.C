void wc_vertexdisplay( Int_t ievent )
{
  
  // TString filename("/lbne/wcsim_root_files/DUSEL_100kton_10inch_40perCent/muon_vtx_20001_wcsim.root");
  // TString filename("/lbne/wcsim_root_files/DUSEL_150ktonMailbox_10inch_30perCent/muon_vtx_20001mailbox.root");
  TString filename("/lbne/data/water/monoenergetic15pcthqe/electron_vtx_8001_aa.root");

  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");


  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");


  // Load Geometry
  // =============
  TChain* chainGeom = new TChain("wcsimGeoT","chainGeom");

  WCSimRootGeom* myGeom = new WCSimRootGeom();
  chainGeom->SetBranchAddress("wcsimrootgeom",&myGeom);
  chainGeom->Add(filename.Data());

  // look at first entry (should only be one geometry...)
  chainGeom->GetEntry(0);

  // build geometry
  WCSimGeometry::BuildGeometry(myGeom);

  // Load Data
  // =========
  TChain* chain = new TChain("wcsimT","chain");

  WCSimRootEvent* myEvent = new WCSimRootEvent();
  chain->SetBranchAddress("wcsimrootevent",&myEvent);
  chain->Add(filename.Data());
  
  // Initialize Reconstruction
  // =========================
  WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();

  // Reconstruct Event
  // =================

  // get n'th entry
  chain->GetEntry(ievent);

  // build event
  WCSimInterface::BuildEvent(myEvent);
  WCSimRecoEvent* myRecoEvent = WCSimInterface::RecoEvent();
  WCSimTrueEvent* myTrueEvent = WCSimInterface::TrueEvent();

  // run reconstruction
  myReco->Run(myRecoEvent);

  // truth
  Double_t trueVtxX = myTrueEvent->GetVtxX();
  Double_t trueVtxY = myTrueEvent->GetVtxY();
  Double_t trueVtxZ = myTrueEvent->GetVtxZ();  
  Double_t trueDirX = myTrueEvent->GetDirX();
  Double_t trueDirY = myTrueEvent->GetDirY();
  Double_t trueDirZ = myTrueEvent->GetDirZ();

  cout << " Monte Carlo Truth: " << endl;
  cout << "  TrueVtx=(" << trueVtxX << "," << trueVtxY << "," << trueVtxZ << ")" << endl;

  // Reconstruct Vertex
  // ==================
  WCSimVertexFinder* myVertexFinder = WCSimVertexFinder::Instance();
  WCSimVertexViewer* myVertexViewer = WCSimVertexViewer::Instance();
  
  // Point Fit
  // =========
  WCSimRecoVertex* myPointVertex = myVertexFinder->RunPointFit(myRecoEvent);
  //WCSimRecoVertex* myPointVertex = myVertexFinder->RunPointFit(myRecoEvent,trueVtxX,trueVtxY,trueVtxZ,trueDirX,trueDirY,trueDirZ); // USING TRUTH
  myVertexViewer->DisplayPointVertex(myRecoEvent,myPointVertex);

  cout << " Result of Point Fit: " << endl;
  cout << "  PointVtx=(" << myPointVertex->GetX() << "," <<  myPointVertex->GetY() << "," << myPointVertex->GetZ() << "," << myPointVertex->GetTime() << "," << myPointVertex->GetFOM() << ")" << endl;

  // Extended Fit
  // ============
  WCSimRecoVertex* myExtendedVertex = myVertexFinder->RunExtendedFit(myRecoEvent);
  //WCSimRecoVertex* myExtendedVertex = myVertexFinder->RunExtendedFit(myRecoEvent,trueVtxX,trueVtxY,trueVtxZ,trueDirX,trueDirY,trueDirZ); // USING TRUTH
  myVertexViewer->DisplayExtendedVertex(myRecoEvent,myExtendedVertex);

  cout << " Result of Extended Fit: " << endl;
  cout << "  ExtendedVtx=(" << myExtendedVertex->GetX() << "," <<  myExtendedVertex->GetY() << "," << myExtendedVertex->GetZ() << "," << myExtendedVertex->GetTime() << "," << myExtendedVertex->GetFOM() << ")" << endl;

  // Angles
  // ======
  myVertexViewer->DisplayAngles(myRecoEvent,myPointVertex);

}
