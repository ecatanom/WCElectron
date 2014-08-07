{

  // Load libraries
  // ==============
  gROOT->Reset();
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
  
  TObjArray Hlist(0);  
  gStyle->SetOptStat("nemrksi");
  TH1D* h1 ;
  TH1D* h2 ;
  TH1D* h3 ;
  TH1D* h4 ;
  TH1D* h5 ;
  TH2D* d12 ;
  TH2D* d13 ;TH2D* d14 ;TH2D* d15 ;TH2D* d23 ;
  TH2D* d24 ;TH2D* d25 ;TH2D* d34 ;TH2D* d35 ;TH2D* d45b ;
 //  TH3D* d123;   TH3D* d124;  TH3D* d125;  TH3D* d134;  TH3D* d135;
//   TH3D* d145;   TH3D* d234;  TH3D* d235;  TH3D* d245;  TH3D* d345;
 



  //TCanvas *ca1 = new TCanvas("ca1","",400,300);
  // for(int ecounter=0;ecounter<mynevents;ecounter++){
  for(int ecounter=0;ecounter<10;ecounter++){
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
      //--------------------------------
      TString hystoname12("h2D_HT_TR");hystoname12+=myeventnumber;
      d12 = new TH2D(hystoname12,goodness,200,0.0,1000.0,200,-20.0,80.0);
      Hlist.Add(d12);
      TString hystoname13("h2D_HT_LP");hystoname13+=myeventnumber;
      d13 = new TH2D(hystoname13,goodness,200,0.0,1000.0,200,0.0,5500.0);
      Hlist.Add(d13);
      TString hystoname14("h2D_HT_LM");hystoname14+=myeventnumber;
      d14 = new TH2D(hystoname14,goodness,200,0.0,1000.0,200,-500.0,1500.0);
      Hlist.Add(d14);
      TString hystoname15("h2D_HT_OA");hystoname15+=myeventnumber;
      d15 = new TH2D(hystoname15,goodness,200,0.0,1000.0,200,20.0,60.0);
      Hlist.Add(d15);
      TString hystoname23("h2D_TR_LP");hystoname23+=myeventnumber;
      d23 = new TH2D(hystoname23,goodness,200,-20.0,80.0,200,0.0,5500.0);
      Hlist.Add(d23);
      TString hystoname24("h2D_TR_LM");hystoname24+=myeventnumber;
      d24 = new TH2D(hystoname24,goodness,200,-20.0,80.0,200,-500.0,1500.0);
      Hlist.Add(d24);
      TString hystoname25("h2D_TR_OA");hystoname25+=myeventnumber;
      d25 = new TH2D(hystoname25,goodness,200,-20.0,80.0,200,20.0,60.0);
      Hlist.Add(d25);
      TString hystoname34("h2D_LP_LM");hystoname34+=myeventnumber;
      d34 = new TH2D(hystoname34,goodness,200,0.0,5500.0,200,-500.0,1500.0);
      Hlist.Add(d34);
      TString hystoname35("h2D_LP_OA");hystoname35+=myeventnumber;
      d35 = new TH2D(hystoname35,goodness,200,0.0,5500.0,200,20.0,60.0);
      Hlist.Add(d35);
      TString hystoname45b("h2D_LM_OA");hystoname45b+=myeventnumber;
      d45b = new TH2D(hystoname45b,goodness,200,-500.0,1500.0,200,20.0,60.0);
      Hlist.Add(d45b);
    




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
          //d12->Fill(hitT,TResid);   
	  d13->Fill(hitT,LPhot);
	  d14->Fill(hitT,LMuon);    d15->Fill(hitT,Oangle);
	  d23->Fill(TResid,LPhot);  d24->Fill(TResid,LMuon); 
	  d25->Fill(TResid,Oangle); d34->Fill(LPhot,LMuon);  
	  d35->Fill(LPhot,Oangle);  d45b->Fill(LMuon,Oangle);

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

      //--------------------------------------------------
    //   (d12->GetXaxis())->SetTitle("hitT [ns]");
//       (d12->GetYaxis())->SetTitle("TRes [ns]");
       
      (d13->GetXaxis())->SetTitle("hitT [ns]");
      (d13->GetYaxis())->SetTitle("LPhoton");
     
      (d14->GetXaxis())->SetTitle("hitT [ns]");
      (d14->GetYaxis())->SetTitle("LMuon");
     
      (d15->GetXaxis())->SetTitle("hitT [ns]");
      (d15->GetYaxis())->SetTitle("Oangle");
      (d23->GetXaxis())->SetTitle("TRes [ns]");
      (d23->GetYaxis())->SetTitle("LPhoton");

      (d24->GetXaxis())->SetTitle("TRes [ns]");
      (d24->GetYaxis())->SetTitle("LMuon");

      (d25->GetXaxis())->SetTitle("TRes [ns]");
      (d25->GetYaxis())->SetTitle("Oangle");

      (d34->GetXaxis())->SetTitle("LPhoton");
      (d34->GetYaxis())->SetTitle("LMuon");

      (d35->GetXaxis())->SetTitle("LPhoton");
      (d35->GetYaxis())->SetTitle("Oangle");

      (d45b->GetXaxis())->SetTitle("LMuon");
      (d45b->GetYaxis())->SetTitle("Oangle");

      //d12->SetStats(1);   
d13->SetStats(1);   d14->SetStats(1); 
      d15->SetStats(1);   d24->SetStats(1);   d25->SetStats(1);   
      d23->SetStats(1);   d34->SetStats(1);   d35->SetStats(1);   
      d45b->SetStats(1); 

      //d12->GetCorrelationFactor(); d12->GetCovariance();
       d13->GetCorrelationFactor(); d13->GetCovariance();
       d14->GetCorrelationFactor(); d14->GetCovariance();
      d15->GetCorrelationFactor(); d15->GetCovariance();
      d23->GetCorrelationFactor(); d23->GetCovariance();
      d24->GetCorrelationFactor(); d24->GetCovariance();
      d25->GetCorrelationFactor(); d25->GetCovariance();
      d34->GetCorrelationFactor(); d34->GetCovariance();
       d35->GetCorrelationFactor(); d35->GetCovariance();
       d45b->GetCorrelationFactor(); d45b->GetCovariance();



   //    d12->Draw("col"); ca1->Update();
//       TImage *img12 = TImage::Create();
//       img12->FromPad(ca1);
//       TString img12filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_HT_TR");
//       img12filename+=myeventnumber;img12filename+=".png";
//       img12->WriteImage(img12filename);//
      
      d13->Draw("col"); ca1->Update();
      TImage *img13 = TImage::Create();
      img13->FromPad(ca1);
      TString img13filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_HT_LP");
      img13filename+=myeventnumber;img13filename+=".png";
      img13->WriteImage(img13filename);
  
      d14->Draw("col"); ca1->Update();
      TImage *img14 = TImage::Create();
      img14->FromPad(ca1);
      TString img14filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_HT_LM");
      img14filename+=myeventnumber;img14filename+=".png";
      img14->WriteImage(img14filename);

  
      d15->Draw("col"); ca1->Update();
      TImage *img15 = TImage::Create();
      img15->FromPad(ca1);
      TString img15filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_HT_OA");
      img15filename+=myeventnumber;img15filename+=".png";
      img15->WriteImage(img15filename);

  
      d23->Draw("col"); ca1->Update();
      TImage *img23 = TImage::Create();
      img23->FromPad(ca1);
      TString img23filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_TR_LP");
      img23filename+=myeventnumber;img23filename+=".png";
      img23->WriteImage(img23filename);

  
      d24->Draw("col"); ca1->Update();
      TImage *img24 = TImage::Create();
      img24->FromPad(ca1);
      TString img24filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_TR_LM");
      img24filename+=myeventnumber;img24filename+=".png";
      img24->WriteImage(img24filename);

  
      d25->Draw("col"); ca1->Update();
      TImage *img25 = TImage::Create();
      img25->FromPad(ca1);
      TString img25filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_TR_OA");
      img25filename+=myeventnumber;img25filename+=".png";
      img25->WriteImage(img25filename);

  
      d34->Draw("col"); ca1->Update();
      TImage *img34 = TImage::Create();
      img34->FromPad(ca1);
      TString img34filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_LP_LM");
      img34filename+=myeventnumber;img34filename+=".png";
      img34->WriteImage(img34filename);

  
      d35->Draw("col"); ca1->Update();
      TImage *img35 = TImage::Create();
      img35->FromPad(ca1);
      TString img35filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_LP_OA");
      img35filename+=myeventnumber;img35filename+=".png";
      img35->WriteImage(img35filename);

  
      d45b->Draw("col"); ca1->Update();
      TImage *img45 = TImage::Create();
      img45->FromPad(ca1);
      TString img45filename("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/2D/h2D_LM_OA");
      img45filename+=myeventnumber;img45filename+=".png";
      img45->WriteImage(img45filename);



      // cout << "digits: " << myNdigits << " filter digits: " << NFilterdigits << endl;
      // delete h1;
      //delete ca1;
      delete img1;delete img2; delete img3;delete img4; delete img5; 
      //delete img12;  
      delete img13; delete img14;  delete img15;
      delete img23;  delete img24; delete img25;  delete img34;
      delete img35;  delete img45;
      WCSimInterface::Reset();
     
      cout <<"=================================================================================================="<<ecounter<<endl;
    }
  TFile  f1("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Good/goodhistos.root","recreate");
  Hlist->Write();
  f1.Close();
}
