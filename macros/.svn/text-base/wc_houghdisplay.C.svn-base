{
  
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

  // Load Data
  // =========
  WCSimInterface::LoadData("/lbne/data/water/sim200kton_20111017/singleparticle/rootfiles/muon_minus_001600MeV_200kton.0001.root");
  //WCSimInterface::LoadData("/r01/lbne/water/wcsim_root_files/DUSEL_200kton_12inch_10perCent/muon_minus_001600MeV_200kton.0001.root");

  // Initialize Reconstruction
  // =========================
  WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();

  // Reconstruct Event
  // =================
 
  // get first entry
  WCSimInterface::LoadEvent(0);

  WCSimRecoEvent* myRecoEvent = WCSimInterface::RecoEvent();
  WCSimTrueEvent* myTrueEvent = WCSimInterface::TrueEvent();


  // apply filter
  myReco->RunFilter(myRecoEvent);


  // True Vertex
  // ===========
  WCSimRecoVertex* myTrueVertex = new WCSimRecoVertex();
  myTrueVertex->SetVertex(myTrueEvent->GetVtxX(),
                          myTrueEvent->GetVtxY(),
                          myTrueEvent->GetVtxZ());

  // Vertex Finder
  // =============
  WCSimVertexFinder* myVertexFinder = WCSimVertexFinder::Instance();
  WCSimRecoVertex* myRecoVertex = myVertexFinder->Run(myRecoEvent);
 
  // Ring Finder
  // ===========
  WCSimRingFinder* myRingFinder = WCSimRingFinder::Instance();

  // Perform Hough Transform
  // ========================
  WCSimHoughTransformArray* myTransformArray = myRingFinder->HoughTransformArray(myRecoEvent,myRecoVertex);  

  // Find Hough Peak
  // ===============    
  Double_t phi = 0.0;
  Double_t costheta = 0.0;
  Double_t hx = 0.0;
  Double_t hy = 0.0;
  Double_t hz = 0.0;
  Double_t angle = 0.0;
  Double_t height = 0.0;
  Int_t bin = 0;
  
  myTransformArray->FindPeak(hx,hy,hz,angle,height);

  Double_t deltaphi = 180.0;
  Int_t bin = myTransformArray->FindBin(angle);
  WCSimHoughTransform* myTransform = myTransformArray->GetHoughTransform(bin);
  TH2D* histTransform = myTransform->GetRotatedTH2D("hello",deltaphi);

  // Plot Truth
  // ==========
  Double_t px = myTrueEvent->GetDirX();
  Double_t py = myTrueEvent->GetDirY();
  Double_t pz = myTrueEvent->GetDirZ();

  if( px!=0.0 ){
    phi = atan(py/px);
  }
  if( px<=0.0 ){
    if( py>0.0 ) phi += TMath::Pi();
    if( py<0.0 ) phi -= TMath::Pi();
  }

  phi *= 180.0/TMath::Pi();
  phi += deltaphi; if( phi>180.0 ) phi -= 360.0;
  costheta = pz;

  marker = new TMarker(phi,costheta,29);
  marker->SetMarkerColor(2);
  marker->SetMarkerSize(2.5);

  // Plot Reco
  // =========
  if( hx!=0.0 ){
    phi = atan(hy/hx);
  }
  if( hx<=0.0 ){
    if( hy>0.0 ) phi += TMath::Pi();
    if( hy<0.0 ) phi -= TMath::Pi();
  }

  phi *= 180.0/TMath::Pi();
  phi += deltaphi; if( phi>180.0 ) phi -= 360.0;
  costheta = hz;

  markerpeak = new TMarker(phi,costheta,29);
  markerpeak->SetMarkerColor(1);
  markerpeak->SetMarkerSize(2.5);

  // Display Hough Transform
  // =======================
  TCanvas* fHoughCanvas = new TCanvas("wcsim_houghtransform_canvas","WCSim HoughTransform Viewer");
  histTransform->Draw("col");
  
  // marker->Draw();      // MC Truth
  // markerpeak->Draw();  // Hough Peak

}
