{
  gROOT->Reset();

  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit"); 
  gSystem->Load("libMinuit.so"); 
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot");
  gSystem.Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis");
  gSystem->Load("libWCSimAnalysis.so");

  // Open the file
  TFile file("/lbne/app/users/txin/WCSim/branches/dev/DetectorDevelopment/muon013_80per.root");
  //TFile file("/lbne/data/water/sim200kton_20110804/singleparticle/rootfiles/muon_plus_001200MeV_200kton.0000.root");

  //WCSimInterface::SetToUseTrueHits();
  // Get the a pointer to the tree from the file
  TTree *tree = (TTree*)file->Get("wcsimT");
  TTree *geotree = (TTree*)file->Get("wcsimGeoT");
  // Get the number of events
  Int_t nevent = tree->GetEntries();
  //std::cout << nevent << std::endl;
  WCSimRootEvent* wcsimrootsuperevent = new WCSimRootEvent();
  
  WCSimRootGeom* wcsimrootgeometry = new WCSimRootGeom();

  TBranch *geobranch = geotree->GetBranch("wcsimrootgeom");
  geobranch->SetAddress(&wcsimrootgeometry);
  if( geotree->GetEntries()>0 ){
    geotree->GetEntry(0);
    if( wcsimrootgeometry ) WCSimGeometry::BuildGeometry(wcsimrootgeometry);
  }

  // Set the branch address for reading from the tree
  TBranch *branch = tree->GetBranch("wcsimrootevent");
  branch->SetAddress(&wcsimrootsuperevent);
 

  // Force deletion to prevent memory leak 
  tree->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  // start with the main "subevent", as it contains most of the info
  // and always exists.
  WCSimRootTrigger* wcsimrootevent;

  TH1D* h1 = new TH1D("h1", "", 1000, -50., 150.);
  TH1D* h2 = new TH1D("h2", "", 1000, -50., 150.);
  TH1D* h3 = new TH1D("h3", "", 1000, -50., 150.);
  TH1D* Prob = new TH1D("Prob","",1000,-50.,150.);
  TH1D *d1 = new TH1D("d1", "", 10, 0.0, 5000.0);
  Double_t trueX, trueY, trueZ, dirX, dirY, dirZ;
  Double_t hitT, hitX, hitY, hitZ, TResid, LPhot;
  /*trueX = -2082.74;
  trueY = -393.175;
  trueZ = 1597.88;
  dirX = 0.450703;
  dirY = 0..607024;
  dirZ = -0.654514; //Evt008*/

  trueX = -79.2276;
  trueY = -951.396;
  trueZ = 3750.86;
  dirX = 0.305255;
  dirY = 0.916471;
  dirZ = 0.25865; //Evt013

  /*trueX = 1610.54;
  trueY = 487.348;
  trueZ = 2360.42;
  dirX = -0.8311;
  dirY = -0.132674;
  dirZ = -0.540065; //Evt018*/

  /*trueX = 1266.59;
  trueY = -1799;
  trueZ = -949.016;
  dirX = 0.562913;
  dirY = -0.826435;
  dirZ = -0.011606; //Evt023*/
  for (int ev=0; ev<nevent; ev++)
  {
    // Read the event from the tree into the WCSimRootEvent instance
    tree->GetEntry(ev);
    geotree->GetEntry(ev);      
    wcsimrootevent = wcsimrootsuperevent->GetTrigger(0);
    //std::cout << wcsimrootsuperevent->GetNumberOfSubEvents() << " " << wcsimrootevent->GetHeader()->GetDate() << std::endl;
	   
    /*Int_t ntrack = wcsimrootevent->GetNtrack();
    //std::cout << ntrack << std::endl;    
    Int_t i;
    for (i=0; i<ntrack; i++)
    {
      TObject *element = (wcsimrootevent->GetTracks())->At(i);      
      WCSimRootTrack *wcsimroottrack = dynamic_cast<WCSimRootTrack*>(element);
      //for (int j=0; j<2; j++) std::cout << wcsimroottrack->GetDir(j) << std::endl;;      
    }*/

//===============================================================================================
//WCSim_true hit
    Int_t ncherenkovhits     = wcsimrootevent->GetNcherenkovhits();
    //cout << ncherenkovhits << endl;
    // Grab the big arrays of times and parent IDs
    //TClonesArray *timeArray = wcsimrootevent->GetCherenkovHitTimes();
    // Grab the big arrays of times and parent IDs
    TClonesArray *WCHitsArray = wcsimrootevent->GetCherenkovHitCoordinates();
    Int_t totalPe = 0;
    Int_t i;
    // Loop through elements in the TClonesArray of WCSimRootCherenkovHits
    for (i=0; i< ncherenkovhits; i++)
    {
      TObject *Hit = (wcsimrootevent->GetCherenkovHits())->At(i);
      WCSimRootCherenkovHit *wcsimrootcherenkovhit = dynamic_cast<WCSimRootCherenkovHit*>(Hit);

      Int_t tubeNumber     = wcsimrootcherenkovhit->GetTubeID();
      Int_t timeArrayIndex = wcsimrootcherenkovhit->GetTotalPe(0);
      Int_t peForTube      = wcsimrootcherenkovhit->GetTotalPe(1);
      totalPe += peForTube;
      
      for (int j = timeArrayIndex; j < timeArrayIndex + peForTube; j++)
      {
	WCSimRootCherenkovHitCoordinate HitCoordinate = dynamic_cast<WCSimRootCherenkovHitCoordinate>(WCHitsArray->At(j));	  
        hitT = (HitCoordinate->GetTrueHit()).at(0);	       
        hitX = (HitCoordinate->GetTrueHit()).at(1);	      
        hitY = (HitCoordinate->GetTrueHit()).at(2);	      
        hitZ = (HitCoordinate->GetTrueHit()).at(3);	 
        hitX = hitX/10.0; hitY = hitY/10.0; hitZ = hitZ/10.0;
        WCSimVertexGeometry::CalcTResidandDistMu(trueX, trueY, trueZ, 0.0, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot);  	
        //if (i<2) cout << TResid << endl;
        h1->Fill(TResid-5.6);
        d1->Fill(LPhot);
      }

    } // End of loop over Cherenkov hits

//==================================================================================
//Digit Hits
    //cout << wcsimrootsuperevent->GetNumberOfEvents() << endl; //2
    for (int index = 0 ; index < wcsimrootsuperevent->GetNumberOfEvents(); index++) 
    {
      wcsimrootevent = wcsimrootsuperevent->GetTrigger(index);
      //cout << "Sub event number = " << index << "\n";      
      Int_t ncherenkovdigihits = wcsimrootevent->GetNcherenkovdigihits();
      //cout << ncherenkovdigihits << endl;
      for (i=0;i<ncherenkovdigihits;i++)
      {
    	// Loop through elements in the TClonesArray of WCSimRootCherenkovDigHits	
    	TObject *element = (wcsimrootevent->GetCherenkovDigiHits())->At(i);	
    	WCSimRootCherenkovDigiHit *wcsimrootcherenkovdigihit =  dynamic_cast<WCSimRootCherenkovDigiHit*>(element);

    	//printf("q, t, tubeid: %f %f %d \n",wcsimrootcherenkovdigihit->GetQ(), wcsimrootcherenkovdigihit->GetT(),wcsimrootcherenkovdigihit->GetTubeId());
        Int_t tube = wcsimrootcherenkovdigihit->GetTubeId();
        hitX = WCSimGeometry::Instance()->GetX(tube);
        hitY = WCSimGeometry::Instance()->GetY(tube);
        hitZ = WCSimGeometry::Instance()->GetZ(tube);
        hitT = wcsimrootcherenkovdigihit->GetT();
        WCSimVertexGeometry::CalcTResidandDistMu(trueX, trueY, trueZ, 0.0, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot);
        //if(i<2) cout << tube << " "<<  TResid << endl;
	h2->Fill(TResid-900.);
        d1->Fill(LPhot);

      } // End of loop over Cherenkov digihits
    } // End of loop over trigger
    
    // reinitialize super event between loops.
    wcsimrootsuperevent->ReInitialize();

  }

//=============================================================================
//WCSimLite
  ifstream hitf;
  Double_t lmda;
  hitf.open("/lbne/app/users/txin/Samples/WCSimLite/Evt013_YesYesYes.txt",ios::in);
  while(! hitf.eof()){
     hitf >> hitX >> hitY >> hitZ >> hitT >> lmda;
     hitX = hitX/10.0;
     hitY = hitY/10.0;
     hitZ = hitZ/10.0;
     WCSimVertexGeometry::CalcTResidandDistMu(trueX, trueY, trueZ, 0.0, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot);
     h3->Fill(TResid-6.0);
     d1->Fill(LPhot);
  }
  hitf.close();

//======================================================================================
//PDF
  WCSimWaterModel *wm2 = WCSimWaterModel::Instance();
  WCSimTResidPDF *pdf = new WCSimTResidPDF(wm2);
  Double_t sigma0 = 0.30; //sigma0 = 4.0;
  Double_t delta, dist;
  Double_t Preal, Norm, weight, Pgauss;
  for( Int_t jj=0;jj<350;jj++ ){
     delta = 0.2*(jj+0.5) - 20.0;
     Preal = 0.0;
     Norm = 0.0;
     for( Int_t ii=0;ii<10;ii++ ){
        dist = (ii+0.5)*500.;
        weight = d1->GetBinContent(ii);
        Norm += weight;
        Pgauss = pdf->MakeChromPeakPDF(delta,dist,sigma0); 
	Preal += (500.0*weight)*(Pgauss);
     }
     if( Norm != 0.0) {
       Preal = Preal/Norm;
     }
     Prob->Fill(delta-4.0, Preal);
  }

//==================================================================================
  h2->Scale(2.0); h3->Scale(0.38);Prob->Scale(7.5);
  h2->SetLineColor(kRed); h3->SetLineColor(kBlue); Prob->SetLineColor(kCyan-2); Prob->SetLineWidth(2.0);
  h1->Draw(); h2->Draw("Same"); h3->Draw("Same"); Prob->Draw("Same");
  TLegend *mylegend3 = new TLegend(0.2,0.7,0.9,0.9,"");
  mylegend3->AddEntry(h1, "WCSim_true hits", "l");
  mylegend3->AddEntry(h2, "WCSim_digit hits", "l");
  mylegend3->AddEntry(h3, "WCSimLite_true hits", "l");
  mylegend3->AddEntry(Prob, "ChromPDF", "l");
  mylegend3->Draw();

}
