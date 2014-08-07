{
  
  // Path to WCSim ROOT file
  // =======================
  //  TString filename("/lbne/wcsim_root_files/DUSEL_100kton_10inch_40perCent/muon_vtx_20001_wcsim.root");
  

  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");

  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

    WCSimIsoChronTransform* myisotest = new WCSimIsoChronTransform(133.,100.);
  //  WCSimIsoChronTransform* myisotest = new WCSimIsoChronTransform();

  //  ifstream InFile("../IsoChron/FakeMuonSample2trksPerfecRes.txt", ios::in);
  //  ifstream InFile("2TrkyeschromTestChrombugfix.txt", ios::in);
  //  ifstream InFile("2TrkNoChrom2ns.txt", ios::in);
  //  ifstream InFile("FakeMuonSample2trksPerfecRes.txt", ios::in);
  //  ifstream InFile("../IsoChron/MuonExample.txt", ios::in);  
    ifstream InFile("6M1PI.750MeV.evt0.txt", ios::in);

  double xEnd,yEnd,zEnd,tEnd,nEnd,wt;

  int hitcount=0;
  
  vector< vector<double> > thehits;
  vector<double> hypVtx;
  vector<double> indices;

  WCSimWaterModel* wmwm = new WCSimWaterModel();
  //  cout<<myWM<<endl;
  cout<<"test: "<<wmwm->N_Index(222)<<endl;;

  hypVtx.push_back(100.);
  hypVtx.push_back(0.);
  hypVtx.push_back(0.);
  hypVtx.push_back(0.);


  // Read in text file...
  int hitcount=0;
  TH1D* indexspectrum = new TH1D("cspec","cspec",600,1.2,1.4);
  while((!InFile.eof()) && (hitcount<400000) ) {

    if(hitcount<400000){
      
      if(hitcount%10000==0) cout<<"reading file...hitcount: "<<hitcount<<endl;
      
      InFile >> xEnd >> yEnd >> zEnd >> tEnd; 
      // if index of refrac is included.. 
      // InFile >> xEnd >> yEnd >> zEnd >> tEnd >> nEnd; 

      wt=1;
      indexspectrum->Fill(nEnd);
      indices.push_back(nEnd);
      
      vector<double> hitcoordinates;  hitcoordinates.push_back(xEnd);  hitcoordinates.push_back(yEnd);  
      hitcoordinates.push_back(zEnd);  hitcoordinates.push_back(tEnd); hitcoordinates.push_back(nEnd);
      thehits.push_back(hitcoordinates);
      hitcount++;
    }
  }

  myisotest->SetConstantIndexofRefraction(1.37);
  //  myisotest->AddWaterModel(wmwm);
  myisotest->ApplyTransform(thehits, hypVtx);
  //  myisotest->ApplyTransformChromCorrected(thehits, hypVtx,50,200.,700.);  


  gROOT->SetStyle("Plain"); 

  //  indexspectrum->Draw();

  TH2D* myxzproj = myisotest->XZProjection(200.);
  /*   
  myxzproj->SetTitle("Reconstructed 750 MeV Electron (geant)");
  myxzproj->GetXaxis()->SetRangeUser(0.,2200.);
  myxzproj->GetXaxis()->SetTitle("x position (mm)");
  myxzproj->GetYaxis()->SetRangeUser(-1500.,1500.);
  myxzproj->GetYaxis()->SetTitle("z position (mm)");
  myxzproj->Draw("colz");
  */

  TH1D* maxAlphaDist = myisotest->getMaxAlphaDist();
  TH1D* BCDist2D = myisotest->getBCDist2D();
  TH1D* BCDist3D = myisotest->getBCDist3D();
  TH1D* mS1= myisotest->getMinS1Dist();
  TH2D* mAvsmS1 = myisotest->getS1vsAlpha(1);
  TH1D* ThetaCDist = myisotest->getMaxThetaCDist();
  TH1D* thefinalNdist = myisotest->getnDist(); 
  TH3D* new3dhisto = myisotest->Get3Dhisto(3600);
  new3dhisto->SetLineColor(2);
  new3dhisto->SetMarkerColor(2);
  new3dhisto->Draw("box");

  //  thefinalNdist->SetLineColor(2);
  //  thefinalNdist->Draw("SAME");
  
}
