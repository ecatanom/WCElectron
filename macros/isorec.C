{
  
  // Path to WCSim ROOT file
  // =======================
  

  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");

  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");


    WCSimIsoChronTransform* myisotest = new WCSimIsoChronTransform(133.,30.);
  //  WCSimIsoChronTransform* myisotest = new WCSimIsoChronTransform();

  //  ifstream InFile("../IsoChron/FakeMuonSample2trksPerfecRes.txt", ios::in);
  //  ifstream InFile("2TrkyeschromTestChrombugfix.txt", ios::in);
  //  ifstream InFile("2TrkNoChrom2ns.txt", ios::in);
    //  ifstream InFile("6M1E.750MeV.evt0.txt", ios::in);
    //  ifstream InFile("6M1E.750MeV.evt0.txt", ios::in);
    //  ifstream InFile("../../PI0samples_6-12-12/FinalPhot1.5GeV_1.txt", ios::in);
    ifstream InFile("../../PI0Esamples_6-13-12/4mSphere/1PI.1.5GeV.evt91.txt", ios::in);
  //  ifstream InFile("../IsoChron/MuonExample.txt", ios::in);  

  double xEnd,yEnd,zEnd,tEnd,nEnd,wt;

  int hitcount=0;
  
  vector< vector<double> > thehits;
  vector<double> hypVtx;
  vector<double> indices;

  WCSimWaterModel* wmwm = WCSimWaterModel::Instance();
  //  cout<<myWM<<endl;
  cout<<"test: "<<wmwm->N_Index(222)<<endl;;

  hypVtx.push_back(0.);
  hypVtx.push_back(0.);
  hypVtx.push_back(0.);
  hypVtx.push_back(0.);

  int hitcount=0;
  TH1D* indexspectrum = new TH1D("cspec","cspec",600,1.2,1.4);
  while((!InFile.eof()) && (hitcount<400000) ) {

    if(hitcount<400000){
      
      if(hitcount%10000==0) cout<<"reading file...hitcount: "<<hitcount<<endl;

       InFile >> xEnd >> yEnd >> zEnd >> tEnd >> nEnd; 
      //           InFile >> xEnd >> yEnd >> zEnd >> tEnd; 
      wt=1;
      
     
      indexspectrum->Fill(nEnd);

      indices.push_back(nEnd);
      
      vector<double> hitcoordinates;  hitcoordinates.push_back(xEnd);  hitcoordinates.push_back(yEnd);  
      hitcoordinates.push_back(zEnd);  hitcoordinates.push_back(tEnd); hitcoordinates.push_back(nEnd);
      thehits.push_back(hitcoordinates);
      hitcount++;
    }
  }

  /*
  double ma=(myisotest->CalcMaxAlpha(1096.656,4.690515));
  //  double ttt=4.690515;
  double ttt=4.93674;
  //  double ddd=1096.656;
  double ddd=1220.654;
  cout<<"maxalpha: "<<(myisotest->CalcMaxAlpha(ddd,ttt))<<" mins1: "<<(myisotest->CalcS1(ma,ddd,ttt))<<" thetaC: "<<(myisotest->CalcMaxEmissionAngle(ddd,ttt))<<endl;


  // Test Index of Refrac Finder

  TGraph* seegraph;
  for(int i=2; i<3; i++){

    vector<double> mev = thehits.at(i);
    double mD = sqrt( mev.at(0)*mev.at(0) + mev.at(1)*mev.at(1) + mev.at(2)*mev.at(2) );
    double mT = mev.at(3);
    double realindex = mev.at(4);
    //    double fitindex = myisotest->FindIndex(mD,mT);
    seegraph = myisotest->FindIndex(mD,mT);
    cout<<"real index: "<<realindex<<endl;
    //    cout<<"Index Fit Results: "<<realindex<<" "<<fitindex<<endl;

  }
  seegraph->SetMarkerSize(0.5);
  seegraph->Draw("AP");
  */

  indexspectrum->Draw();
   

  myisotest->SetConstantIndexofRefraction(1.36);
  myisotest->ApplyTransform(thehits, hypVtx);
  TH2D* myxzproj = myisotest->XZProjection(200.);

  myisotest->AddWaterModel(wmwm);

  //  myisotest->ApplyTransformChromCorrected(thehits, hypVtx,50,200.,700.);

  //  gROOT->SetStyle("Plain"); 

    
  myxzproj->SetTitle("Reconstructed 750 MeV Electron (geant)");
  myxzproj->GetXaxis()->SetRangeUser(0.,2200.);
  myxzproj->GetXaxis()->SetTitle("x position (mm)");
  myxzproj->GetYaxis()->SetRangeUser(-1500.,1500.);
  myxzproj->GetYaxis()->SetTitle("z position (mm)");
 
  myxzproj->Draw("colz");



  TCanvas* tc0 = new TCanvas();
  TPad* mypad = new TPad;
  TH3D* new3dhisto = myisotest->Get3Dhisto(400);
  new3dhisto->SetTitle("Reconstructed 1.5 GeV Pi0 (geant)");
  //  new3dhisto->GetXaxis()->SetRangeUser(0.,2200.);
  //  new3dhisto->GetXaxis()->SetTitle("x position (mm)");
  //  new3dhisto->GetYaxis()->SetRangeUser(-1500.,1500.);
  //  new3dhisto->GetYaxis()->SetTitle("y position (mm)");
  //  new3dhisto->GetZaxis()->SetTitle("z position (mm)");
  mypad->Draw();
  mypad->cd();
  new3dhisto->GetXaxis()->SetRangeUser(0.,1500.);
  //  initialLightDist->GetXaxis()->SetTitle("x (mm)");

  new3dhisto->GetYaxis()->SetRangeUser(-1000.,1000.);
  //  initialLightDist->GetYaxis()->SetTitle("y (mm)");

  new3dhisto->GetZaxis()->SetRangeUser(-1000.,1000.);
  //  initialLightDist->GetZaxis()->SetTitle("z (mm)");

  new3dhisto->SetStats(0);



  new3dhisto->SetLineColor(2);
  new3dhisto->SetMarkerColor(2);
  new3dhisto->Draw("box");

  mypad->SetPhi(0);
  mypad->SetTheta(90);

  TCanvas* tc = new TCanvas();
  TH2D* s1vsalpha = myisotest->getS1vsAlpha(0.);
  s1vsalpha->Draw("colz");

  TCanvas* tc2 = new TCanvas();
  TH1D* bcd = myisotest->getBCDist2D();
  bcd->Draw();



  /*
  TH1D* maxAlphaDist = myisotest->getMaxAlphaDist();
  TH1D* BCDist = myisotest->getBCDist();
  TH1D* mS1= myisotest->getMinS1Dist();
  TH2D* mAvsmS1 = myisotest->getS1vsAlpha();
  TH1D* ThetaCDist = myisotest->getMaxThetaCDist();
  TH1D* thefinalNdist = myisotest->getnDist(); 
  thefinalNdist->SetLineColor(2);
  */
  //  thefinalNdist->Draw("SAME");
  
}
