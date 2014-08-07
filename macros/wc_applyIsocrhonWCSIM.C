{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");
  
  // Path to WCSim ROOT file
  // =======================
  //  TString filename("/lbne/wcsim_root_files/DUSEL_100kton_10inch_40perCent/muon_vtx_20001_wcsim.root");
  TString filename("/lbne/data/water/sim200kton_20110804/singleparticle/rootfiles/muon_minus_002400MeV_200kton.0008.root");
  
  // Load Data
  // =========
  WCSimInterface::LoadData(filename);

  // Load a particular event
  WCSimInterface::LoadEvent(7);

  // Initialize Reconstruction
  // =========================
  WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();

  // Initialize WCSimIsochron
  // =========================
  WCSimIsoChronTransform* myisotest = new WCSimIsoChronTransform(80.,200.);
  //  WCSimIsoChronTransform* myisotest = new WCSimIsoChronTransform(80.,500.);
  
  // Reconstruct Event
  // =================


  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
  int myNdigits = recoEvent->GetNDigits();

  // get true quantities
  Double_t trueVtxX = trueEvent->GetVtxX();
  Double_t trueVtxY = trueEvent->GetVtxY();
  Double_t trueVtxZ = trueEvent->GetVtxZ(); 

  Double_t trueDirX = trueEvent->GetDirX();
  Double_t trueDirY = trueEvent->GetDirY();
  Double_t trueDirZ = trueEvent->GetDirZ();

  std::cout<<"TRUTH: "<<trueVtxX<<" "<<trueVtxY<<" "<<trueVtxZ<<" "<<trueDirX<<" "<<trueDirY<<" "<<trueDirZ<<std::endl;

  // run reconstruction

  WCSimVertexFinder::UseTrueVertex(); // suppress vertex finder to get a reco time close to true...
  myReco->Run(recoEvent);
  Double_t trueVtxTime = recoEvent->GetVtxTime();  //faux true time

  vector< vector<double> > thehits;
  vector<double> hypVtx;
  hypVtx.push_back(trueVtxX*10);
  hypVtx.push_back(trueVtxY*10);
  hypVtx.push_back(trueVtxZ*10);
  hypVtx.push_back(trueVtxTime);
  
  std::cout<<"TRUE VERTEX TIME: "<<trueVtxTime<<std::endl;

  // Fill hits to vector, compatible with current version of IsoChron class
  
  for(int i=0.; i<myNdigits; i++){

    WCSimRecoDigit* adigit = recoEvent->GetDigit(i);
    double xEnd = adigit->GetX();
    double yEnd = adigit->GetY();
    double zEnd = adigit->GetZ();
    double tEnd = adigit->GetTime();
    double nEnd = 1.33;

    //    std::cout<<i<<" "<<xEnd<<std::endl;
    vector<double> hitcoordinates;  hitcoordinates.push_back(xEnd*10);  hitcoordinates.push_back(yEnd*10);  
    hitcoordinates.push_back(zEnd*10);  hitcoordinates.push_back(tEnd); hitcoordinates.push_back(nEnd);
    thehits.push_back(hitcoordinates);
  }

  // run reconstruction

  myisotest->SetConstantIndexofRefraction(1.33);
  myisotest->SetConstantSpeedofParticle(0.999*299.792458);
  myisotest->ApplyTransformPMTres(thehits, hypVtx, 2.0);
  //  myisotest->ApplyTransform(thehits, hypVtx);
 
  TH1D* BCdist = myisotest->getBCDist3D();
  TH2D* S1_vs_alpha = myisotest->getS1vsAlpha(2);
  TH1D* BCdist = myisotest->getBCDist2D();

  TH3D* new3dhisto = myisotest->Get3Dhisto(190);
  //  TH3D* new3dhisto = myisotest->Get3Dhisto(70);
  new3dhisto->SetMarkerSize(0.25);
  new3dhisto->SetMarkerColor(4);
  new3dhisto->Draw();

  //    BCdist->Draw();
  //    myxzproj->Draw("colz");
   
}
