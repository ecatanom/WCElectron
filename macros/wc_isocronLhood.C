{
  
  // Path to WCSim ROOT file
  // =======================
  TString filename("/lbne/wcsim_root_files/DUSEL_100kton_10inch_40perCent/muon_vtx_20001_wcsim.root");
  

  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");

  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");



  //  ifstream InFile("../IsoChron/FakeMuonSample2trksPerfecRes.txt", ios::in);
  //  ifstream InFile("2TrkyeschromTestChrombugfix.txt", ios::in);
  //  ifstream InFile("2TrknochromTestChrom.txt", ios::in);
  ifstream InFile("6M1E.750MeV.evt0.txt", ios::in);
  
  double xEnd,yEnd,zEnd,tEnd,nEnd,wt;

  int hitcount=0;
  
  vector< vector<double> > thehits;
  vector<double> indices;

  WCSimWaterModel* wmwm = new WCSimWaterModel();
  cout<<"test: "<<wmwm->N_Index(222)<<endl;;

  
  int hitcount=0;
  TH1D* indexspectrum = new TH1D("cspec","cspec",400,1.2,1.4);
  while((!InFile.eof()) && (hitcount<100000) ) {

    if(hitcount<100000){
      
      if(hitcount%10000==0) cout<<"reading file...hitcount: "<<hitcount<<endl;

      //      InFile >> xEnd >> yEnd >> zEnd >> tEnd >> nEnd; 
      InFile >> xEnd >> yEnd >> zEnd >> tEnd; 
      wt=1;
      
      indexspectrum->Fill(nEnd);

      indices.push_back(nEnd);
      
      vector<double> hitcoordinates;  hitcoordinates.push_back(xEnd);  hitcoordinates.push_back(yEnd);  
      hitcoordinates.push_back(zEnd);  hitcoordinates.push_back(tEnd); hitcoordinates.push_back(nEnd);
      thehits.push_back(hitcoordinates);
      hitcount++;
    }
  }


  TGraph *testlhood = new TGraph();
  double vxpos=-2000.;
  double vzposinit=-2000.;
  int nstepsi=21;
  int nstepsj=21;
  double stepsize=200.;

  TH1D*** BCDist = new TH1D*[nstepsi];
  TH2D* twoDFOM = new TH2D("twoDFOM","twoDFOM",21,-2050.,2050.,21,-2050.,2050.);
  TH2D* twoDFOM2 = new TH2D("twoDFOM2","twoDFOM2",21,-2050.,2050.,21,-2050.,2050.);
  TH1D* binfinder = new TH1D("bf","bf",21,-2050.,2050.);
  std::fstream* fitfile =  new std::fstream("vtxscan.electron.txt",std::ios::out);


  for(int i=0; i<nstepsi; i++){
    BCDist[i] = new TH1D[nstepsj];
    double vzpos=vzposinit;
    for(int j=0; j<nstepsj; j++){
    
      cout<<"beginning "<<i<<" "<<j<<endl;

      vector<double> hypVtx;
      hypVtx.push_back(vxpos);
      hypVtx.push_back(0.);
      hypVtx.push_back(vzpos);
      hypVtx.push_back(0.);
      
      WCSimIsoChronTransform* myisotest = new WCSimIsoChronTransform(133.,30.);
      
      myisotest->SetConstantIndexofRefraction(1.4);

      myisotest->ApplyTransform(thehits, hypVtx);
      TH2D* myxzproj = myisotest->XZProjection(0.);
      gROOT->SetStyle("Plain"); 
      
      gStyle->SetPalette(1);
      
      cout<<"OK"<<endl;

      //  myxzproj->Draw("colz");
      
      TString dynamicname;
      dynamicname+="bcdist_";
      dynamicname+=i;
      dynamicname+="_";
      dynamicname+=j;

      BCDist[i][j] = (myisotest->getBCDist())->Clone();
      BCDist[i][j]->SetNameTitle(dynamicname,dynamicname);
      
      int lowr = BCDist[i][j]->FindBin(300.);
      int hir = BCDist[i][j]->FindBin(1500.);
      
      double bcsum=0;
      double bccount=0;
      
      double maxbincontent=0;

      for(int kk=lowr; kk<hir; kk++){
	
	double bc = (double)(BCDist[i][j]->GetBinContent(kk));
	double bv = (double)(BCDist[i][j]->GetBinCenter(kk));
	
	if( (bc>=1) && (bv>maxbincontent) ) maxbincontent = bv;

	double smoothcutoff = 1./(1+exp(-(bv-450)/40.));
	
	bcsum += bv*bc*smoothcutoff;
	bccount += bc*smoothcutoff;
      }
      
      double fom;
      if(bccount>0) fom = bcsum/bccount;
      else fom = 0;
      
      double avgbc=BCDist[i][j]->GetMean();
      //    testlhood->SetPoint(i,vxpos,avgbc);
      int fomxbin = binfinder->FindBin(vxpos);
      int fomzbin = binfinder->FindBin(vzpos);

      twoDFOM->SetBinContent(fomxbin,fomzbin,fom);
      twoDFOM2->SetBinContent(fomxbin,fomzbin,avgbc);
      testlhood->SetPoint(i,vxpos,fom);
      cout<<i<<" "<<j<<" "<<vxpos<<" "<<vzpos<<" "<<avgbc<<" "<<" "<<fomxbin<<" "<<fomzbin<<" "<<fom<<endl;
      (*fitfile)<<i<<" "<<j<<" "<<vxpos<<" "<<vzpos<<" "<<avgbc<<" "<<" "<<fomxbin<<" "<<fomzbin<<" "<<fom<<" "<<maxbincontent<<endl;


      cout<<"stepping"<<endl;
      vzpos+=stepsize;
      cout<<"deleting..."<<endl;
      delete myisotest;
      cout<<"done with that"<<endl;
      // delete BCDist;
      // delete myxzproj;
      
    }
      vxpos+=stepsize;
  }

  /*
  BCDist[6][6]->Draw();
  BCDist[0][6]->SetLineColor(2);
  BCDist[0][6]->Draw("SAME");
  BCDist[10][6]->SetLineColor(4);
  BCDist[10][6]->Draw("SAME");
  */
  /*
  testlhood->SetNameTitle("fomlhood","fomlhood");
  testlhood->Draw("AL");
  */
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  twoDFOM->Draw("colz");

  TFile *tf = new TFile("savecolzEglobal.root","RECREATE");
  twoDFOM->Write();
  twoDFOM2->Write();

  for(int i=0; i<nstepsi; i++){
    for(int j=0; j<nstepsj; j++){

      BCDist[i][j]->Write();
    }
  }

  tf->Close();

  //  ThetaCDist->Draw();
  
  /*
  // Initialize Reconstruction
  // =========================
  WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();
  

  // Reconstruct Event
  // =================

  // get first entry
  chain->GetEntry(0);

  // build event
  WCSimInterface::BuildEvent(myEvent);
  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();

  // run reconstruction
  myReco->Run(recoEvent);

  // get reconstructed quantities
  Double_t recoVtxX = recoEvent->GetVtxX();
  Double_t recoVtxY = recoEvent->GetVtxY();
  Double_t recoVtxZ = recoEvent->GetVtxZ();
  Double_t recoDirX = recoEvent->GetDirX();
  Double_t recoDirY = recoEvent->GetDirY();
  Double_t recoDirZ = recoEvent->GetDirZ();

  std::cout << "  recoVtx=(" << recoVtxX << ", " << recoVtxY << ", " << recoVtxZ << std::endl
            << "           " << recoDirX << ", " << recoDirY << ", " << recoDirZ << ") " << std::endl;

  // Interface to MC Truth
  //======================

  // get true quantities
  Double_t trueVtxX = trueEvent->GetVtxX();
  Double_t trueVtxY = trueEvent->GetVtxY();
  Double_t trueVtxZ = trueEvent->GetVtxZ();  
  Double_t trueDirX = trueEvent->GetDirX();
  Double_t trueDirY = trueEvent->GetDirY();
  Double_t trueDirZ = trueEvent->GetDirZ();

  std::cout << "  trueVtx=(" << trueVtxX << ", " << trueVtxY << ", " << trueVtxZ << std::endl
            << "           " << trueDirX << ", " << trueDirY << ", " << trueDirZ << ") " << std::endl;

  */
}
