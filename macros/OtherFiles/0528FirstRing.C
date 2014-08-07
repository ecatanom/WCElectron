//Creates 1D histograms (param HitT, TResid, LPhoton, LMuon, Oangle) for a list of events; saves all histograms in .root file and png images

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
  //int events[]={0, 109, 111, 116, 118, 127, 178, 188, 214, 227, 230, 236, 243, 250, 267, 275, 276, 277, 295, 303, 312, 322, 326, 330, 331, 345, 353, 359, 369, 370, 377, 379, 38, 403, 404, 405, 408, 411, 416, 432, 439, 441, 446, 447, 486, 493, 495, 532, 534, 541, 566, 578, 589, 599, 610, 616, 635, 636, 641, 643, 646, 653, 660, 663, 673, 674, 704, 705, 730, 75, 764, 780, 790, 799, 81, 824, 82, 831, 838, 857, 911, 91, 925, 957, 95, 985, 992}; ///bad events!!!!!
  int events[]={100, 114, 122, 145, 146, 156, 161, 165, 173, 175, 184, 185, 196, 197, 198, 205, 206, 210, 213, 219, 21, 222, 226, 249, 258, 263, 265, 274, 279, 283, 284, 296, 29, 302, 304, 30, 320, 325, 329, 336, 338, 339, 34, 357, 362, 363, 381, 391, 392, 406, 418, 443, 452, 459, 468, 485, 492, 501, 514, 516, 521, 54, 558, 569, 57, 582, 586, 592, 601, 619, 622, 624, 647, 661, 710, 724, 72, 738, 739, 746, 750, 757, 771, 775, 779, 794, 810, 812, 822, 853, 859, 85, 860, 862, 866, 878, 893, 904, 909, 919, 922, 926, 945, 964, 96, 975, 97, 981};

  int mynevents = sizeof(events)/sizeof(events[0]);

  TString goodness("Good");
  //TString goodness("Bad");
  
  TObjArray Hlist(0);  
  gStyle->SetOptStat("nemrksi");
  TH1D* h1 ;
  TH1D* h2 ;
  TH1D* h3 ;
  TH1D* h4 ;
  TH1D* h5 ;
  TH1D* htx ; TH1D* hty ; TH1D* htz ;
  TH1D* hhx ; TH1D* hhy ; TH1D* hhz ;

  //TCanvas *ca1 = new TCanvas("ca1","",400,300);
  for(int ecounter=0;ecounter<mynevents;ecounter++){
     
      myeventnumber=events[ecounter];

      TString hystoname1("h1D_HT_");hystoname1+=myeventnumber;
      h1 = new TH1D(hystoname1,goodness,500,0.0,1000.0);
      Hlist.Add(h1); 
  
      TString hystoname2("h1D_TR_");hystoname2+=myeventnumber;
      h2 = new TH1D(hystoname2,goodness,500,-20.0,80.0);
      Hlist.Add(h2); 

      TString hystoname3("h1D_LP_");hystoname3+=myeventnumber;
      h3 = new TH1D(hystoname3,goodness,500,0.0,5500.0);
      Hlist.Add(h3); 
  
      TString hystoname4("h1D_LM_");hystoname4+=myeventnumber;
      h4 = new TH1D(hystoname4,goodness,500,-500.0,1500.0);
      Hlist.Add(h4); 

      TString hystoname5("h1D_OA_");hystoname5+=myeventnumber;
      h5 = new TH1D(hystoname5,goodness,500,20.0,60.0);
      Hlist.Add(h5); 

      //-----------------
      TString hystonametx("h1D_TX_");hystonametx+=myeventnumber;
      htx = new TH1D(hystonametx,goodness,500,-3000.0,3000.0);
      Hlist.Add(htx);
      TString hystonamety("h1D_TY_");hystonamety+=myeventnumber;
      hty = new TH1D(hystonamety,goodness,500,-3000.0,3000.0);
      Hlist.Add(hty);
      TString hystonametz("h1D_TZ_");hystonametz+=myeventnumber;
      htz = new TH1D(hystonametz,goodness,500,-4000.0,4000.0);
      Hlist.Add(htz);
      TString hystonamehx("h1D_HX_");hystonamehx+=myeventnumber;
      hhx = new TH1D(hystonamehx,goodness,500,-4000.0,4000.0);
      Hlist.Add(hhx);
      TString hystonamehy("h1D_HY_");hystonamehy+=myeventnumber;
      hhy = new TH1D(hystonamehy,goodness,500,-4000.0,4000.0);
      Hlist.Add(hhy);
      TString hystonamehz("h1D_HZ_");hystonamehz+=myeventnumber;
      hhz = new TH1D(hystonamehz,goodness,500,-5000.0,5000.0);
      Hlist.Add(hhz);



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
  
   
      //---------------------------

      
      WCSimInterface::LoadEvent(myeventnumber);
      WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
      WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
      WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
      if(filtered) haReco->RunFilter(recoEvent);

      myNdigits = recoEvent->GetNDigits();
      NFilterdigits = recoEvent->GetNFilterDigits();

      trueX = trueEvent->GetVtxX();
      trueY = trueEvent->GetVtxY();
      trueZ = trueEvent->GetVtxZ(); 
      dirX = trueEvent->GetDirX();
      dirY = trueEvent->GetDirY();
      dirZ = trueEvent->GetDirZ();
      trueT = 0.0;
      theta = (TMath::Pi())/2.0 - atan(dirZ/sqrt(dirX*dirX+dirY*dirY)); //theta = theta + 3.0/41.0;
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
     
	  h1->Fill(hitT);
	  h2->Fill(TResid);
	  h3->Fill(LPhot);
	  h4->Fill(LMuon);
	  h5->Fill(Oangle);
	  htx->Fill(trueX); hhx->Fill(hitX);
	  hty->Fill(trueY); hhy->Fill(hitY);
	  htz->Fill(trueZ); hhz->Fill(hitZ);
     
	  ifilter++; 
	} //loop of the filter
      } //loop over hits

      cout << "WCSim" << endl;
      //================================================================
      //PRINT HISTOGRAM
 
      (h1->GetXaxis())->SetTitle("hitT [ns]");
      (h1->GetYaxis())->SetTitle("Hits"); 
      h1->SetStats(1); 
      TCanvas *ca1 = new TCanvas("ca1","",400,300);
      h1->Draw();ca1->Update();
      TImage *img1 = TImage::Create();
      img1->FromPad(ca1);
      TString img1filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_HT_");img1filename+=myeventnumber;img1filename+=".png";
      img1->WriteImage(img1filename);


      (h2->GetXaxis())->SetTitle("TResid [ns]");
      (h2->GetYaxis())->SetTitle("Hits"); 
      h2->SetStats(1); 
      h2->Draw(); ca1->Update();
      TImage *img2 = TImage::Create();
      img2->FromPad(ca1);
      TString img2filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_TR_");img2filename+=myeventnumber;img2filename+=".png";
      img2->WriteImage(img2filename);



      (h3->GetXaxis())->SetTitle("LPhot");
      (h3->GetYaxis())->SetTitle("Hits"); 
      h3->SetStats(1); 
      //TCanvas *ca3 = new TCanvas("ca3","",400,300);
      h3->Draw(); ca1->Update();
      TImage *img3 = TImage::Create();
      img3->FromPad(ca1);
      TString img3filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_LP_");img3filename+=myeventnumber;img3filename+=".png";
      img3->WriteImage(img3filename);


      (h4->GetXaxis())->SetTitle("LMuon");
      (h4->GetYaxis())->SetTitle("Hits"); 
      h4->SetStats(1); 
      //TCanvas *ca4 = new TCanvas("ca4","",400,300);
      h4->Draw(); ca1->Update();
      TImage *img4 = TImage::Create();
      img4->FromPad(ca1);
      TString img4filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_LM_");img4filename+=myeventnumber;img4filename+=".png";
      img4->WriteImage(img4filename);



      (h5->GetXaxis())->SetTitle("Oangle");
      (h5->GetYaxis())->SetTitle("Hits"); 
      h5->SetStats(1); 
      //TCanvas *ca5 = new TCanvas("ca5","",400,300);
      h5->Draw(); ca1->Update();
      TImage *img5 = TImage::Create();
      img5->FromPad(ca1);
      TString img5filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_OA_");img5filename+=myeventnumber;img5filename+=".png";
      img5->WriteImage(img5filename);

      //---------
      (htx->GetXaxis())->SetTitle("TrueX");
      (htx->GetYaxis())->SetTitle("Hits"); 
      htx->SetStats(1); 
      htx->Draw(); ca1->Update();
      TImage *imgtx = TImage::Create();
      imgtx->FromPad(ca1);
      TString imgtxfilename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_TX_");imgtxfilename+=myeventnumber;imgtxfilename+=".png";
      imgtx->WriteImage(imgtxfilename);

      (hty->GetXaxis())->SetTitle("TrueY");
      (hty->GetYaxis())->SetTitle("Hits"); 
      hty->SetStats(1); 
      hty->Draw(); ca1->Update();
      TImage *imgty = TImage::Create();
      imgty->FromPad(ca1);
      TString imgtyfilename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_TY_");imgtyfilename+=myeventnumber;imgtyfilename+=".png";
      imgty->WriteImage(imgtyfilename);
    
      (htz->GetXaxis())->SetTitle("TrueZ");
      (htz->GetYaxis())->SetTitle("Hits"); 
      htz->SetStats(1); 
      htz->Draw(); ca1->Update();
      TImage *imgtz = TImage::Create();
      imgtz->FromPad(ca1);
      TString imgtzfilename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_TZ_");imgtzfilename+=myeventnumber;imgtzfilename+=".png";
      imgtz->WriteImage(imgtzfilename);
    
      (hhx->GetXaxis())->SetTitle("HitX");
      (hhx->GetYaxis())->SetTitle("Hits");
      hhx->Draw(); ca1->Update();
      TImage *imghx = TImage::Create();
      imghx->FromPad(ca1);
      TString imghxfilename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_HX_");imghxfilename+=myeventnumber;imghxfilename+=".png";
      imghx->WriteImage(imghxfilename);

      (hhy->GetXaxis())->SetTitle("HitY");
      (hhy->GetYaxis())->SetTitle("Hits"); 
      hhy->SetStats(1); 
      hhy->Draw(); ca1->Update();
      TImage *imghy = TImage::Create();
      imghy->FromPad(ca1);
      TString imghyfilename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_HY_");imghyfilename+=myeventnumber;imghyfilename+=".png";
      imghy->WriteImage(imghyfilename);
    
      (hhz->GetXaxis())->SetTitle("HitZ");
      (hhz->GetYaxis())->SetTitle("Hits"); 
      hhz->SetStats(1); 
      hhz->Draw(); ca1->Update();
      TImage *imghz = TImage::Create();
      imghz->FromPad(ca1);
      TString imghzfilename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/h1D_HZ_");imghzfilename+=myeventnumber;imghzfilename+=".png";
      imghz->WriteImage(imghzfilename);

      // cout << "digits: " << myNdigits << " filter digits: " << NFilterdigits << endl;
      // delete h1;
      //delete ca1;
      delete img1;delete img2; delete img3;delete img4; delete img5; 
      delete imgtx;  delete imgty; delete imgtz;
      delete imghx;  delete imghy; delete imghz;
      WCSimInterface::Reset();
     
      cout <<"=================================================================================================="<<ecounter<<endl;
    }
  TFile  f1("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Good/goodhistos.root","recreate");
  //TFile  f1("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Bad/badhistos.root","recreate");
  Hlist->Write();
  f1.Close();
}
