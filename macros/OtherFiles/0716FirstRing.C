//Creates 1D histograms (param HitT, TResid, LPhoton, LMuon, Oangle) for a list of events;(before and after LMuon filter) saves all histograms in .root file and png images

{

  // Load libraries
  // ==============
  //gROOT->Reset();
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
 Double_t TResid, LPhot, LMuon, Oangle;
  double bdeltaT, rdeltaT;
  Double_t trueX ;
  Double_t trueY;
  Double_t trueZ ;
  Double_t dirX ;
  Double_t dirY ;
  Double_t dirZ ;
  Double_t trueT ;
  double theta ;
  int myNdigits;
  int NFilterdigits;

  int myeventnumber=0;
  int badevents[]={0, 109, 111, 116, 118, 127, 178, 188, 214, 227, 230, 236, 243, 250, 267, 275, 276, 277, 295, 303, 312, 322, 326, 330, 331, 345, 353, 359, 369, 370, 377, 379, 38, 403, 404, 405, 408, 411, 416, 432, 439, 441, 446, 447, 486, 493, 495, 532, 534, 541, 566, 578, 589, 599, 610, 616, 635, 636, 641, 643, 646, 653, 660, 663, 673, 674, 704, 705, 730, 75, 764, 780, 790, 799, 81, 824, 82, 831, 838, 857, 911, 91, 925, 957, 95, 985, 992}; ///bad events!!!!!
  int goodevents[]={100, 114, 122, 145, 146, 156, 161, 165, 173, 175, 184, 185, 196, 197, 198, 205, 206, 210, 213, 219, 21, 222, 226, 249, 258, 263, 265, 274, 279, 283, 284, 296, 29, 302, 304, 30, 320, 325, 329, 336, 338, 339, 34, 357, 362, 363, 381, 391, 392, 406, 418, 443, 452, 459, 468, 485, 492, 501, 514, 516, 521, 54, 558, 569, 57, 582, 586, 592, 601, 619, 622, 624, 647, 661, 710, 724, 72, 738, 739, 746, 750, 757, 771, 775, 779, 794, 810, 812, 822, 853, 859, 85, 860, 862, 866, 878, 893, 904, 909, 919, 922, 926, 945, 964, 96, 975, 97, 981};

  //int mynevents = sizeof(events)/sizeof(events[0]);

 
  gStyle->SetOptStat("nemrksi");
  TH1D* h1 ;
  TH1D* h2 ;
 

  //TCanvas *ca1 = new TCanvas("ca1","",400,300);
  for(int ecounter=0;ecounter<10;ecounter++){
     
      myeventnumber=ecounter;

      TString hystoname1("h1D_TR_Bef_");hystoname1+=myeventnumber;
      h1 = new TH1D(hystoname1,"Before",500,-10.0,50.0);
      
  
      TString hystoname2("h1D_TR_Af");hystoname2+=myeventnumber;
      h2 = new TH1D(hystoname2,"After",500,-10.0,50.0);
     

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
  WCSimVertexFinder::PointFitOnly();
   
      //---------------------------

      
      WCSimInterface::LoadEvent(myeventnumber);
      WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
      WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
      WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
      if(filtered) haReco->Run(recoEvent);

      myNdigits = recoEvent->GetNDigits();
      NFilterdigits = recoEvent->GetNFilterDigits();

      trueX = recoEvent->GetVtxX();
      trueY = recoEvent->GetVtxY();
      trueZ = recoEvent->GetVtxZ(); 
      dirX = recoEvent->GetDirX();
      dirY = recoEvent->GetDirY();
      dirZ = recoEvent->GetDirZ();
      trueT = 0.0;
     //  theta = (TMath::Pi())/2.0 - atan(dirZ/sqrt(dirX*dirX+dirY*dirY)); //theta = theta + 3.0/41.0;
//       double phi = 0.0;
//       if( dirX<0.0 ) phi = TMath::Pi() - asin(dirY/sqrt(dirX*dirX+dirY*dirY));
//       else if( dirY>0.0 ) phi = asin(dirY/sqrt(dirX*dirX+dirY*dirY));
//       else if( dirY<0.0 ) phi = 2.0*TMath::Pi() + asin(dirY/sqrt(dirX*dirX+dirY*dirY));
//       //else( dirY=0.0 ) phi = 0.0;
//       dirX = cos(phi)*sin(theta);
//       dirY = sin(phi)*sin(theta);
//       dirZ = cos(theta);

      WCSimWaterModel *wm2 = WCSimWaterModel::Instance();
      WCSimTResidPDF *pdf = WCSimTResidPDF::Instance();
   
      //------------------------------------------------------------------ 
     //FILL HISTOGRAM
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
     
	  h1->Fill(TResid);
	  cout << i<< " "<< LMuon << endl;
	  if(LMuon<300) h2->Fill(TResid);
     
	  ifilter++; 
	} //loop of the filter
      } //loop over hits

      cout << "WCSim" << endl;
      //================================================================
      //PRINT HISTOGRAM
 
      (h1->GetXaxis())->SetTitle("TResid");
      (h1->GetYaxis())->SetTitle("Hits"); 
      h1->SetStats(0); 
      TCanvas *ca1 = new TCanvas("ca1","",400,300);
      h1->Draw();//ca1->Update();
      h2->SetStats(1);
      h2->SetLineColor(kRed);
      // h2->Draw();
      h2->Draw("same");


      TImage *img1 = TImage::Create();
       img1->FromPad(ca1);
       TString img1filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/0716files/h1D_TR_");img1filename+=myeventnumber;img1filename+=".png";
       img1->WriteImage(img1filename);

       delete img1;
      //delete h1; delete h2;
    
   
     
      //WCSimInterface::Reset();
     
      cout <<"=================================================================================================="<<ecounter<<endl;
    }

}
