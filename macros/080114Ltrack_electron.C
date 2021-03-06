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
  
  // Load Data
  // =========
   TString filename("/lbne/data2/users/txin/Samples/eminus_1200mev_200kton_10inch_13per_hqe_MuSct.root");
  //TString filename("/lbne/data2/users/txin/Samples/eminus_400mev_200kton_10inch_13per_hqe_MuSct.root");
  //TString filename("/lbne/data2/users/txin/Samples/eminus_400mev_50kton_10inch_13per_hqe_MuSct.root");
  WCSimInterface::LoadData(filename);

  // get first entry
  Bool_t truehit = 1; // 1 is to use true hits
  Bool_t Lmu = 0; // 1 is to use LMuon cut
  Double_t sigma0 = 0.1; //sigma0 = 0.1; //1 ns
  if(truehit) {WCSimInterface::SetToUseTrueHits();
    WCSimInterface::Instance()->SetToMCP();//
    WCSimInterface::Instance()->SmearTrueHits(sigma0);} //Smear sigma0=1ns, we are talking about MCP

  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);//there's no cut
  WCSimDataCleaner::Instance()->SetNeighbourRadius(300.0); //cm
  WCSimDataCleaner::Instance()->SetNeighbourDigits(40.0);//number of neighb
  WCSimDataCleaner::Instance()->SetClusterRadius(300.0);
  WCSimDataCleaner::Instance()->SetClusterDigits(40.0);//at least 50 clusters
  WCSimDataCleaner::Instance()->SetTimeWindowNeighbours(25.0);//ns window
  WCSimDataCleaner::Instance()->SetTimeWindowClusters(25.0);

  //WCSimInterface::Instance()->SetToGated();//use PMT
  //both commented is using ungated PMT


  Bool_t filtered = 0;
  Bool_t drawd = 1; // 1 is to draw the distance plot at the end
  if(drawd){//dist traveled by photon
    double mind = 0.0;
    double maxd = 900.0;
  }
  else{
    double mind = 1500.0;
    double maxd = 5500.0;
  }
  double mindmu = -1000.0;//dist muon
  double maxdmu = 1000.0;
  TH1D* hltrackdata = new TH1D("hltrackdata", ";Ltrack [cm]",100,mindmu,maxdmu);
  TH1D* hltrackdataall = new TH1D("hltrackdataall", ";Ltrack [cm]",100,mindmu,maxdmu);  //Ltrack only
  //TH1D* hltrackdataall = new TH1D("hltrackdataall", ";Oangle [deg]",100,0,180); // Oamgle only
 
 TH1D* hltrackmc = new TH1D("hltrackmc", "Ltrack [cm]",100,mindmu,maxdmu);
  Double_t TResid, LPhot, LMuon, Oangle;
  double bdeltaT, rdeltaT;
  
  
  //LOOP OVER EVENTS
  
  for(Int_t ievt=0;ievt<1000;ievt++ ){
    //ievt=16;
    WCSimInterface::LoadEvent(ievt);
    // build event
    WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
    WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
    //
    WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
    if(filtered) haReco->RunFilter(recoEvent);
    
    int myNdigits = recoEvent->GetNDigits();
    int NFilterdigits = recoEvent->GetNFilterDigits();
  
    // get true quantities
    Double_t trueX = trueEvent->GetVtxX();
    Double_t trueY = trueEvent->GetVtxY();
    Double_t trueZ = trueEvent->GetVtxZ(); 
    if( trueX==0 && trueY==0 && trueZ==0 ) continue;
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
  
  //phenomenology... water model: class that contains index of refraction, attenuation (lambda), initial spectrum, etc. How photon travels through water
  WCSimWaterModel *wm2 = WCSimWaterModel::Instance();
  WCSimTResidPDF *pdf = WCSimTResidPDF::Instance();//dont use this :p
  
  int ifilter = 0;
  for(int i=0; i<myNdigits; i++){
    
   WCSimRecoDigit* adigit = recoEvent->GetDigit(i);
   double hitX = adigit->GetX();
   double hitY = adigit->GetY();
   double hitZ = adigit->GetZ();
   double hitT = adigit->GetTime();
   double qpes = adigit->GetQPEs();//charge
   double res = WCSimParameters::TimeResolution(qpes); 
   
   WCSimVertexGeometry::CalcTResid(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle); 
   //     double Ptemp = pdf->MakeChromPeakPDF(TResid,LPhot,sigma0); 
   if(filtered) hltrackdata->Fill(LMuon); 
   hltrackdataall->Fill(LMuon); //Ltrack only
   //hltrackdataall->Fill(Oangle); //Opening angle only
     ifilter++; 
     //} //loop of the filter
  } //loop over hits
  } // loop over events

  //********************************************************************** 
  // ORIGINAL FUCTION OF LTRACK BY IOANA
  /*  
  Double_t Norm       = 10.0;
  Double_t earlysigma = 100;//50.0;//2.0/sqrt(Norm) that P(l=-20cm)=0.01
  Double_t earlycut   = -1.0;//25.0; // .0
  Double_t latesigma  = 100.0;//2.5/sqrt(Norm);//150.0;// latesigma = 25.0/(10.0*sqrt(Norm)) that P(l=525cm)=0.01
  Double_t latecut    = 0.0;//earlycut+2.0;//earlycut+500;
  Double_t softcutoff = latecut - earlycut;
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  Int_t nbin = hltrackdata->GetNbinsX();
  Double_t width = hltrackdata->GetBinWidth(1);
  Double_t minedge = hltrackdata->GetBinLowEdge(1);
  for(int i=1;i<nbin+1;i++){
      Double_t PLmu       = 0.0;
      Double_t distMuon = minedge + (i-0.5)*width; 
      if( distMuon > latecut ) PLmu = Norm/(1.0+((distMuon-latecut)*(distMuon-latecut)/(latesigma*latesigma)));
      else if ( distMuon > earlycut ) PLmu = Norm;
      else PLmu = Norm/(1.0+((distMuon-earlycut)*(distMuon-earlycut))/(earlysigma*earlysigma));//-1.0
      hltrackmc->SetBinContent(i,PLmu);
      }
  */
  //END OF ORIFINAL PDF
  //********************************************************************** 
  // PDF0 FROM IOANA'S WCVERTEXFINDER
  /*  
   Double_t Norm       = 10.0;
  Double_t softcutoff = 1.0;
  Double_t earlysigma = 100.0/sqrt(Norm);//Ioana...originally = 50
  Double_t earlycut   = 1.0;  
  Double_t latesigma  = 100.0;//Ioana...originally = 50
  Double_t latecut    = 0;
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  Int_t nbin = hltrackdata->GetNbinsX();
  Double_t width = hltrackdata->GetBinWidth(1);
  Double_t minedge = hltrackdata->GetBinLowEdge(1);
  for(int i=1;i<nbin+1;i++){
  Double_t PLmu       = 0.0;
  Double_t distMuon = minedge + (i-0.5)*width; 
 if( distMuon > 1.0 ) PLmu = Norm/(1.0+((distMuon-softcutoff+earlycut)*(distMuon-softcutoff+earlycut)/(latesigma*latesigma)));
 else if ( distMuon > -1.0) PLmu = Norm;
 else PLmu = Norm/(1.0+((distMuon+earlycut)*(distMuon+earlycut))/(earlysigma*earlysigma));//-1.0
 //hltrackmc->SetBinContent(i,PLmu);
//try to introduce the correct bias
    Double_t bias= hltrackdataall->GetBinContent(i);
     hltrackmc->SetBinContent(i,bias*PLmu);
    }*/
  //END OF PDF 0
  
  
  //************************************************************************  
  //PDF3 FOUND BY ERIKA
  /*
  Double_t Norm       = 10.0;
  Double_t earlysigma = 70;//50.0;//2.0/sqrt(Norm) that P(l=-20cm)=0.01
  Double_t earlycut   = -50.0;//25.0; // .0
  Double_t latesigma  = 100.0;//2.5/sqrt(Norm);//150.0;// latesigma = 25.0/(10.0*sqrt(Norm)) that P(l=525cm)=0.01
  Double_t latecut    = 0.0;//earlycut+2.0;//earlycut+500;
  Double_t softcutoff = latecut - earlycut;
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  Int_t nbin = hltrackdataall->GetNbinsX();
  Double_t width = hltrackdataall->GetBinWidth(1);
  Double_t minedge = hltrackdataall->GetBinLowEdge(1);
  for(int i=1;i<nbin+1;i++){
    Double_t PLmu       = 0.0;
    Double_t distMuon = minedge + (i-0.5)*width; 
    if( distMuon > latecut ) PLmu = Norm/(1.0+((distMuon-latecut)*(distMuon-latecut)/(latesigma*latesigma)));
      else if ( distMuon > earlycut ) PLmu = Norm;
      else PLmu = Norm/(1.0+((distMuon-earlycut)*(distMuon-earlycut))/(earlysigma*earlysigma));//-1.0
    
  
    // hltrackmc->SetBinContent(i,PLmu);

    //try to introduce the correct bias
    Double_t bias= hltrackdataall->GetBinContent(i);
    hltrackmc->SetBinContent(i,bias*PLmu);

    }*/
  //END OF PDF3
  //****************************************
  
//********************************************************************** 
   // PDF4 from PDF0 written as 3 change earlycut to -50
  
  Double_t Norm       = 10.0;
  Double_t earlysigma = 100.0/sqrt(Norm);//Ioana...originally = 50
  Double_t earlycut   = -50.0;  
  Double_t latesigma  = 100.0;//Ioana...originally = 50
  Double_t latecut    = 0;
  Double_t softcutoff= latecut-earlycut;
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  Int_t nbin = hltrackdata->GetNbinsX();
  Double_t width = hltrackdata->GetBinWidth(1);
  Double_t minedge = hltrackdata->GetBinLowEdge(1);
  for(int i=1;i<nbin+1;i++){
  Double_t PLmu       = 0.0;
  Double_t distMuon = minedge + (i-0.5)*width; 
 if( distMuon > 1.0 ) PLmu = Norm/(1.0+((distMuon-latecut)*(distMuon-latecut)/(latesigma*latesigma)));
 else if ( distMuon > earlycut) PLmu = Norm;
 else PLmu = Norm/(1.0+((distMuon-earlycut)*(distMuon-earlycut))/(earlysigma*earlysigma));//-1.0
 hltrackmc->SetBinContent(i,PLmu);
//try to introduce the correct bias
    Double_t bias= hltrackdataall->GetBinContent(i);
   // hltrackmc->SetBinContent(i,bias*PLmu);
    }
  //END OF PDF 4
  /*
  hltrackdataall->SetTitle("1200 MeV 200 kton electron, PDF4, Biased");
  //hltrackdataall->SetTitle("400 MeV 50 kton electron, PDF4, Biased");
 
  //Oangle only
  // hltrackdataall->SetTitle("400 MeV 50 kton electron, ALL");
  //hltrackdataall->SetTitle("1200 MeV 200 kton electron, ALL");
  
  TCanvas* ca1 = new TCanvas("ca1","ca1",500,300);
  //  hltrackdata->Sumw2();
  hltrackdataall->SetLineWidth(2);
  // hltrackdataall->Draw();
  //  hltrackdataall->SetLineColor(kBlue);
  //  hltrackdataall->Draw("same");
  hltrackmc->Scale((hltrackdataall->GetMaximum())/(hltrackmc->GetMaximum()));

  
  hltrackmc->SetLineColor(kRed);
  hltrackmc->SetLineWidth(2);
  hltrackmc->Draw("same");
  */
 
  //PDF only
  TCanvas* ca1 = new TCanvas("ca1","ca1",500,300);
  hltrackmc->SetTitle("PDF4");
 hltrackmc->SetLineColor(kRed);
  hltrackmc->SetLineWidth(2);
  hltrackmc->Draw();


  //Oangle only  
  /* TLine l(42,-10000,42,1100000);
  l.SetLineColor(kRed);
  l.SetLineWidth(2);
  l.SetLineStyle(2);
  l.Draw("same");*/



  // TString nameImage("400Ltrack");
  /* TString nameImage("400Oangle");
  nameImage+=(ievt-1);
  nameImage+=".pdf";
  ca1.Print(nameImage,"pdf");
  */
}
