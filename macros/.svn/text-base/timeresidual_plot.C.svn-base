{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

  /*gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit"); 
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");*/
  
  // Path to WCSim ROOT file
  // =======================
  //  TString filename("/lbne/wcsim_root_files/DUSEL_100kton_10inch_40perCent/muon_vtx_20001_wcsim.root");
  //TString filename("/lbne/data/water/sim200kton_20110804/singleparticle/rootfiles/muon_minus_002400MeV_200kton.0008.root");
  TString filename("/lbne/data/water/sim200kton_20110804/singleparticle/rootfiles/muon_plus_001200MeV_200kton.0000.root");

  
  // Load Data
  // =========
  WCSimInterface::LoadData(filename);
  //WCSimInterface::LoadData("/r01/lbne/water/wcsim_root_files/DUSEL_200kton_12inch_10perCent/muon_minus_001600MeV_200kton.0001.root");

  // get first entry
  WCSimInterface::LoadEvent(36);

  // Initialize Reconstruction
  // =========================
  //WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();


  // Initialize 
  // =========================
  //WCSimIsoChronTransform* myisotest = new WCSimIsoChronTransform(200.,500.);
  
  // Reconstruct Event
  // =================

  //for( int i = 1; i<(chain->GetEntries()); i++ ){

   // build event
  // WCSimInterface::BuildEvent(myEvent);
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
  //WCSimVertexFinder::UseTrueVertex(); // suppress vertex finder to get a reco time close to true...

  WCSimVertexFinder* finderit = WCSimVertexFinder::Instance();
  finderit->WCSimVertexFinder::SetChrom(false);
  finderit->WCSimVertexFinder::UsingTrueVertex(true);
  finderit->WCSimVertexFinder::SetPointFitOnly(false);
  finderit->WCSimVertexFinder::SetFitTimeParams();
  //myReco->Run(recoEvent);
  WCSimRecoVertex* myRecoVertex = finderit->WCSimVertexFinder::Run(recoEvent);

  Double_t trueVtxTime = myRecoVertex->GetTime();  //faux true time
  //std::cout << trueVtxTime << std::endl;
  std::cout<<"TRUTH: "<<trueVtxX<<" "<<trueVtxY<<" "<<trueVtxZ<<" "<<trueDirX<<" "<<trueDirY<<" "<<trueDirZ<<std::endl;

  vector< vector<double> > thehits;
  vector<double> hypVtx;

  hypVtx.push_back(trueVtxX*10);
  hypVtx.push_back(trueVtxY*10);
  hypVtx.push_back(trueVtxZ*10);
  hypVtx.push_back(trueVtxTime);
  
  std::cout<<"TRUE VERTEX TIME: "<<trueVtxTime<<std::endl;
  TH1D* hTR = finderit->WCSimVertexFinder::GetTimeResidual();
  TH1D* hP = finderit->WCSimVertexFinder::GetProbability();
  TH1D* hTR2 = finderit->WCSimVertexFinder::GetTimeResidualChrom();
  TH1D* hP2 = finderit->WCSimVertexFinder::GetProbabilityChrom();

  TCanvas *c2 = new TCanvas("c2","test canvas",200,10,600,800);
  c2->Divide(1,2);
  c2->cd(1);
  //c2->SetGrid();
  //gPad->SetLogy();
  hTR->Draw();
  hTR->SetTitle("without chromatic correction");
  c2->cd(2);
  hTR2->Draw();
  hTR2->SetTitle("with chromatic correction");
  /*hP->Draw();
  hP->SetTitle("without chromatic correction");
  c2->cd(2);
  hP2->Draw();
  hP2->SetTitle("with chromatic correction");*/
  
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

  //myisotest->SetConstantIndexofRefraction(1.35);
  //myisotest->SetConstantSpeedofParticle(0.999*299.792458)
  //myisotest->ApplyTransform(thehits, hypVtx);
 
  //TH2D* myxzproj = myisotest->XZProjection(200.);
  //TH1D* BCdist = myisotest->getBCDist();
  
  //BCdist->Draw();
  //TH3D* new3dhisto = myisotest->Get3Dhisto(0);
  //new3dhisto->SetMarkerSize(0.25);
  //  myxzproj->Draw("colz");
 
}
