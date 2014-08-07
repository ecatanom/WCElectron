{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");
  
  // Path to WCSim ROOT file
  // =======================
  TString filename("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_MuSct_Ion.root");

  // Load Data
  // =========
  WCSimInterface::LoadData(filename);

  // get first entry
  Bool_t truehit = 1; // 1 is to use true hits
  Bool_t filtered = 1; // 1 is to use Andy's cut
  Bool_t Lmu = 0; // 1 is to use LMuon cut
  Double_t sigma0 = 1.0; //sigma0 = 0.1;
  if(truehit) {WCSimInterface::SetToUseTrueHits();
  WCSimInterface::Instance()->SmearTrueHits(sigma0);}

  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);
  WCSimDataCleaner::Instance()->SetNeighbourRadius(300.0); 
  WCSimDataCleaner::Instance()->SetNeighbourDigits(50.0);
  WCSimDataCleaner::Instance()->SetClusterRadius(300.0);
  WCSimDataCleaner::Instance()->SetClusterDigits(50.0);
  WCSimDataCleaner::Instance()->SetTimeWindowNeighbours(25.0);
  WCSimDataCleaner::Instance()->SetTimeWindowClusters(25.0);

  WCSimInterface::Instance()->SetToMCP();
  //WCSimInterface::Instance()->SetToGated();
  WCSimInterface::LoadEvent(145);
 

  TH1D* h1 = new TH1D("h1", "",500,0.0,1000.0);//hitT
  TH1D* h2 = new TH1D("h2", "",400,20.0,60.0);//Opening angle
  TH1D* h3 = new TH1D("h3", "",500,0.0,900.0);//LMuon
  TH1D* h4 = new TH1D("h4", "",500,0.0,100.0);//TResid
  TH2D *d1 = new TH2D("d1","", 200,0.0,1000.0,400,20.0,60.0);//hitT,Oangle
  TH2D *d2 = new TH2D("d2","", 400, 20.0, 60.0, 300, 0.0, 900.0);//Oangle,LMuon
  TH2D *d3 = new TH2D("d3","", 200,0.0,1000.0,300,0.0,900.0);//hitT,LMuon
  TH2D *d4 = new TH2D("d4","", 200,0.0,100.0,400,20.0,60.0);//TResid,Oangle
  TH2D *d5 = new TH2D("d5","", 200,0.0,100.0,300,0.0,900.0);//TResid,LMuon
  Double_t TResid, LPhot, LMuon, Oangle;
  double bdeltaT, rdeltaT;

  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();

  WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
  if(filtered) haReco->RunFilter(recoEvent);

  int myNdigits = recoEvent->GetNDigits();
  int NFilterdigits = recoEvent->GetNFilterDigits();

  Double_t trueX = trueEvent->GetVtxX();
  Double_t trueY = trueEvent->GetVtxY();
  Double_t trueZ = trueEvent->GetVtxZ(); 
  Double_t dirX = trueEvent->GetDirX();
  Double_t dirY = trueEvent->GetDirY();
  Double_t dirZ = trueEvent->GetDirZ();
  Double_t trueT = 0.0;
  double theta = (TMath::Pi())/2.0 - atan(dirZ/sqrt(dirX*dirX+dirY*dirY)); //theta = theta + 3.0/41.0;
  double phi = 0.0;
  if( dirX<0.0 ) phi = TMath::Pi() - asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY>0.0 ) phi = asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY<0.0 ) phi = 2.0*TMath::Pi() + asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  //else( dirY=0.0 ) phi = 0.0;
  dirX = cos(phi)*sin(theta);
  dirY = sin(phi)*sin(theta);
  dirZ = cos(theta);

  WCSimWaterModel *wm2 = WCSimWaterModel::Instance();
  WCSimTResidPDF *pdf = WCSimTResidPDF::Instance();

  int ifilter = 0;
  for(int i=0; i<myNdigits; i++){

   WCSimRecoDigit* adigit = recoEvent->GetDigit(i);
   if( adigit->IsFiltered() || !filtered ){ //if the hit passed the filter
    double hitX = adigit->GetX();
    double hitY = adigit->GetY();
    double hitZ = adigit->GetZ();
    double hitT = adigit->GetTime();
    double qpes = adigit->GetQPEs();
    double res = WCSimParameters::TimeResolution(qpes); 

     WCSimVertexGeometry::CalcTResid(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle); 
     h1->Fill(hitT);
     h2->Fill(Oangle);
     h3->Fill(LMuon);
     h4->Fill(TResid);
     d1->Fill(hitT,Oangle);
     d2->Fill(Oangle,LMuon);
     d3->Fill(hitT,LMuon);
     d4->Fill(TResid,Oangle);
     d5->Fill(TResid,LMuon);
     
     ifilter++; 
    } //loop of the filter
  } //loop over hits

  cout << "WCSim" << endl;
//============================================================================================
//  d->SetMarkerSize(0.3); //d->Draw();
//  (d->GetXaxis())->SetTitle("muon distance [cm]");
//  (d->GetYaxis())->SetTitle("open angle [degree]");

//  h1->Fill(hitT);
//  h2->Fill(Oangle);
//  h3->Fill(LMuon);
//  d->Fill(hitT,Oangle);
//  d2->Fill(Oangle,LMuon);
//  d3->Fill(hitT,LMuon);
  //h1->SetLineColor(kRed); 
  //h1->SetLineWidth(1.5); 
  (h1->GetXaxis())->SetTitle("hitT [ns]");
  (h1->GetYaxis())->SetTitle("Events");

  //h2->SetLineColor(kBlue); 
  //h1->SetLineWidth(1.5); 
  (h2->GetXaxis())->SetTitle("Opening Angle [degree]");
  (h2->GetYaxis())->SetTitle("Events");

  //h3->SetLineColor(kGreen); 
  //h1->SetLineWidth(1.5); 
  (h3->GetXaxis())->SetTitle("Lmuon [cm]");
  (h3->GetYaxis())->SetTitle("Events");
  
  (h4->GetXaxis())->SetTitle("TResid [ns]");
  (h4->GetYaxis())->SetTitle("Events");
 
  (d1->GetXaxis())->SetTitle("hitT");
  (d1->GetYaxis())->SetTitle("Oangle");

  (d2->GetXaxis())->SetTitle("Oangle");
  (d2->GetYaxis())->SetTitle("Lmuon");

  (d3->GetXaxis())->SetTitle("hitT");
  (d3->GetYaxis())->SetTitle("Lmuon");
  
  (d4->GetXaxis())->SetTitle("TResid");
  (d4->GetYaxis())->SetTitle("Oangle");

  (d5->GetXaxis())->SetTitle("TResid");
  (d5->GetYaxis())->SetTitle("Lmuon");

  TCanvas *ca1 = new TCanvas("ca1","",1200,900);
  ca1->Divide(3,3);
  ca1->cd(1);  h1->Draw(); 
  ca1->cd(2);  h2->Draw(); 
  ca1->cd(3);  h3->Draw();  
  ca1->cd(4);  h4->Draw(); 
  ca1->cd(5);  d1->Draw("col");
  ca1->cd(6);  d2->Draw("col");
  ca1->cd(7);  d3->Draw("col");
  ca1->cd(8);  d4->Draw("col");
  ca1->cd(9);  d5->Draw("col");
 

 //  TCanvas *ca5 = new TCanvas("ca5","",400,900);
//   ca5->Divide(1,3);
//   ca5->cd(1);
//   d->Draw("col"); 
//   ca5->cd(2);
//   d2->Draw("col");
//   ca5->cd(3);
//   d3->Draw("col");

//   TLegend *mylegend = new TLegend(0.5,0.75,0.9,0.9,"");
//   mylegend->AddEntry(h1, "time residual spectrum", "l");
//   mylegend->AddEntry(h2, "PDF", "l");
//   mylegend->AddEntry(h3, "likelihood distribution", "l");
//   //mylegend->Draw();
  cout << "digits: " << myNdigits << " filter digits: " << NFilterdigits << endl;
  
}
