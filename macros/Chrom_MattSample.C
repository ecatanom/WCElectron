{
  
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot");
  gSystem->Load("libWCSimAnalysis");

  #include <iostream>
  #include <fstream>
  #include <iomanip>
  #include <vector>
  #include "TRandom3.h"

  TRandom3 number(42484);


  Double_t hitX = 0.;
  Double_t hitY = 0.;
  Double_t hitZ = 0.;
  Double_t hitT = 0.;
  Int_t nhit = 0;
  Double_t lmda = 0.0;

  Double_t trueX = 0.;
  Double_t trueY = 0.;
  Double_t trueZ = 0.;
  Double_t trueT = 0.;
  Double_t trueE = 0.;
  Double_t dirX = 0.;
  Double_t dirY = 0.;
  Double_t dirZ = 0.;
  Double_t Lphot = 0.0;

  Double_t TResid = 0.0;
  
  TH1D *timeresid1 = new TH1D("timeresid1","",3500,-10.,60.);
  TH1D *timeresid2 = new TH1D("timeresid2","",3500,-10.,60.);
  TH1D *timeresid3 = new TH1D("timeresid3","",3500,-50.,300.);
  TH1D *timeresid4 = new TH1D("timeresid4","",350,-10.,60.);
  //TH1D *timeresid4 = new TH1D("timeresid4","",350,100.,800.);
  TH1D *timeresid5 = new TH1D("timeresid5","",1400,-50.,300.);
  TH1D *timeresid6 = new TH1D("timeresid6","",350,-10.,60.);
  //TH1D *timeresid6 = new TH1D("timeresid6","",350,100.,800.);
  TH1D* Prob = new TH1D("Prob","",350,-10.,60.);
  TH1D* Probnon = new TH1D("Probnon","Probability",350,-15.,55.);
  TH1D* ProbA = new TH1D("ProbA","Probability",350,-10.,60.);
  TH1D* ProbV = new TH1D("ProbAV","Probability",350,-10.,60.);
  TH1D* ProbAV = new TH1D("ProbAVN","Probability",350,-10.,60.);
  TH1D* Prob1 = new TH1D("Prob","Probability",1400,-10.,60.);
  TH2D* lmdadist1 = new TH2D("lmdadist1","",1400,100.,800.,1400,0.0,7000.);
  TH2D* lmdadist2 = new TH2D("lmdadist2","",1400,100.,800.,1400,0.0,7000.);
  TH3D *geoEvt = new TH3D("geoEvt","",1500,-3000.,3000.,1500,-3000.,3000.,2000,-4000.,4000.);
  WCSimRecoEvent* mmevent = WCSimRecoEvent::Instance(); 
  TH1D* D1 = new TH1D("photon distance","",10,0.0,5000.0);

  char hitfname[250];
  //char hitffname[250];

  trueX = -2082.74;
  trueY = -393.175;
  trueZ = 1597.88;
  dirX = 0.450703;
  dirY = 0..607024;
  dirZ = -0.654514; //Evt008

  /*trueX = -79.2276;
  trueY = -951.396;
  trueZ = 3750.86;
  trueT = 0.0;
  trueE = 0.0;
  dirX = 0.305255;
  dirY = 0.916471;
  dirZ = 0.25865; //Evt013*/

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

  ifstream hitf;
  /*hitf.open("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents_withColor/Evt13.YesMuScatteringYesPhotScattering.txt",ios::in); 
  while(! hitf.eof()){
  //for(Int_t ii=0;ii<3000;ii++ ){
     hitf >> hitX >> hitY >> hitZ >> hitT >> lmda;
     //std::cout << hitX << " " << hitY << " " << hitZ << std::endl;
     hitX = hitX/10.0;
     hitY = hitY/10.0;
     hitZ = hitZ/10.0; 
     TResid = WCSimVertexGeometry::CalcResiduals(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, lmda);
     timeresid1->Fill(TResid);
  }
  hitf.close(); std::cout << "haha1" << std::endl;
  //hitf.open("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents_withColor/Evt13.YesMuScatteringYesPhotScattering.txt",ios::in); 
  hitf.open("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents/Evt13.YesMuScatteringYesPhotScattering.txt",ios::in); 
  while(! hitf.eof()){
  //for(Int_t ii=0;ii<3000;ii++ ){
     hitf >> hitX >> hitY >> hitZ >> hitT;
     //std::cout << hitX << " " << hitY << " " << hitZ << std::endl;
     hitX = hitX/10.0;
     hitY = hitY/10.0;
     hitZ = hitZ/10.0;
     TResid = WCSimVertexGeometry::CalcResiduals(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT);
     timeresid2->Fill(TResid-0.5);
  }
  hitf.close(); std::cout << "haha2" << std::endl;*/
  /*hitf.open("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents/Evt8.YesMuScatteringNoPhotScattering.txt",ios::in); 
  while(! hitf.eof()){
  //for(Int_t ii=0;ii<3000;ii++ ){
     hitf >> hitX >> hitY >> hitZ >> hitT;
     //std::cout << hitX << " " << hitY << " " << hitZ << std::endl;
     hitX = hitX/10.0;
     hitY = hitY/10.0;
     hitZ = hitZ/10.0;
     TResid = WCSimVertexGeometry::CalcResiduals(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT);
     timeresid3->Fill(TResid);
  }
  hitf.close(); std::cout << "haha3" << std::endl;*/
  //hitf.open("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents_withColor/Evt8.NoMuScatteringNoPhotScatteringNoBoundaryProcess.txt",ios::in);  
  //hitf.open("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents/Evt23.NoMuScatteringNoPhotScattering.txt",ios::in);
  hitf.open("/lbne/app/users/txin/Samples/WCSimLite/Evt008_NoNoNo.txt",ios::in);
  while(! hitf.eof()){
  //for(Int_t ii=0;ii<3000;ii++ ){
     //hitf >> hitX >> hitY >> hitZ >> hitT;
     hitf >> hitX >> hitY >> hitZ >> hitT >> lmda;
     //std::cout << hitX << " " << hitY << " " << hitZ << std::endl;
     hitX = hitX/10.0;
     hitY = hitY/10.0;
     hitZ = hitZ/10.0;
     WCSimVertexGeometry::CalcTResidandDistMu(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, Lphot);
     //TResid = WCSimVertexGeometry::CalcResiduals(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, lmda);
     timeresid4->Fill(TResid-3.0);
     //if(TResid>9.0)timeresid4->Fill(lmda);
     //D1->Fill(Lphot);
     //lmdadist1->Fill(lmda,Lphot);
  }
  hitf.close(); std::cout << "haha4" << std::endl;
  //Int_t ii=0;
  /*hitf.open("/lbne/app/users/wetstein/SamplesForTian/NewTimingResidCallibration/noscatter/One1GeVMuon_0_0_0meters-evt5_noscatter_0.05ns.txt",ios::in);
  while(! hitf.eof()){
  //for(Int_t ii=0;ii<3000;ii++ ){
     hitf >> hitX >> hitY >> hitZ >> hitT;
     //std::cout << hitX << " " << hitY << " " << hitZ << std::endl;
     hitX = hitX/10.0;
     hitY = hitY/10.0;
     hitZ = hitZ/10.0;
     //if( ii==0 ) std::cout << hitX << " " << hitT << std::endl;
     TResid = WCSimVertexGeometry::CalcResiduals(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT);
     timeresid5->Fill(TResid);
     //ii ++;
  }
  hitf.close(); std::cout << "haha5" << std::endl;*/
  //hitf.open("/lbne/app/users/wetstein/SamplesForTian/TimingResidCallibration/with_scattering/Five1GeVMuons_0-0-0meters_1.00ns.txt",ios::in); 
  //ifstream hitf6; ii = 0;
  //hitf.open("/lbne/app/users/wetstein/SamplesForTian/NewTimingResidCallibration/noscatter/OneGeVMuon_0_0_0meters-evt3_noscatter_perfectres.txt");
  //hitf.open("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents/Evt23.YesMuScatteringYesPhotScattering.txt",ios::in);
  //hitf.open("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents/Evt8.NoMuScatteringNoPhotScattering.txt",ios::in);
  //hitf.open("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents_withColor/Evt8.YesMuScatteringYesPhotScattering.txt",ios::in); 
  hitf.open("/lbne/app/users/txin/Samples/WCSimLite/Evt008_YesYesYes.txt",ios::in);
  //Int_t ii = 0;
  //std::cout << " i am good " << std::endl;
  while(! hitf.eof()){
  //for(Int_t ii=0;ii<3000;ii++){
     //hitf >> hitX >> hitY >> hitZ >> hitT;
     hitf >> hitX >> hitY >> hitZ >> hitT >> lmda;
     //std::cout << hitX << " " << hitY << " " << hitZ << std::endl;
     hitX = hitX/10.0;
     hitY = hitY/10.0;
     hitZ = hitZ/10.0;

     WCSimVertexGeometry::CalcTResidandDistMu(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, Lphot);
     //TResid = WCSimVertexGeometry::CalcResiduals(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, lmda);
     timeresid6->Fill(TResid-2.0);
     //if(TResid>9.0)timeresid6->Fill(lmda);
     D1->Fill(Lphot);

     /*Double_t coverage = number.Rndm();
     if( coverage<=0.5 ) timeresid4->Fill(TResid);
     if( coverage<=0.3 ) timeresid2->Fill(TResid);
     if( coverage<=0.1 ) timeresid1->Fill(TResid);*/
     /*if( hitT<=100.0 && hitT>75. ) timeresid6->Fill(TResid);
     if( hitT<=75.0 && hitT>50. ) timeresid4->Fill(TResid);
     if( hitT<=50.0 && hitT>25. ) timeresid2->Fill(TResid);
     if( hitT<=25.0 && hitT>0. ) timeresid1->Fill(TResid);*/

//=====================================display draw==================================
//fill the RecoEvent
     /*hitT = hitT + 950.;
     WCSimRecoDigit* mydigit = new WCSimRecoDigit(0, hitX, hitY, hitZ, hitT, 1., TResid, 1.);
     mmevent->AddDigit(1,mydigit);*/
     //if( ii==2754 ) std::cout << hitX << std::endl;
//==================================================================================
  }
  hitf.close();
//==============================================
//normalization
  Double_t norm = timeresid6->Integral();
  timeresid6->Scale(1.0/norm);
  norm = timeresid4->Integral();
  timeresid4->Scale(1.0/norm);
  //norm = timeresid2->Integral();
  //timeresid2->Scale(1.0/norm);
  //norm = timeresid1->Integral();
  //timeresid1->Scale(1.0/norm);

//=========================================================draw display
  //WCSimDisplayAB* display = new WCSimDisplayAB();
  //display->DrawEvtUV(mmevent);
//==================================================
  //TF1 *gaus1 = new TF1("gaus1","gaus",-0.3,0.7);
  //timeresid2->Fit(gaus1,"R0");
  //Double_t sigma0 = gaus1->GetParameter(2); 
  Double_t sigma0 = 0.30; //sigma0 = 4.0;
  std::cout << " i am fine. the sigma is extracted out " << std::endl;

  WCSimWaterModel *wm = WCSimWaterModel::Instance();
  WCSimTResidPDF *pdf = new WCSimTResidPDF(wm);

  Double_t delta, dist;
  Double_t Preal, Norm, weight, Pgauss;
  //Double_t Prealnon, Pgaussnon;
  //Double_t PrealA, PgaussA;
  //Double_t PrealV, PgaussV;
  //Double_t PrealAV, PgaussAV;

  for( Int_t jj=0;jj<350;jj++ ){
     delta = 0.2*(jj+0.5) - 20.0;
     Preal = 0.0;
     Norm = 0.0;
     for( Int_t ii=0;ii<10;ii++ ){
        //if( jj%50==0 ) std::cout << "i am fine " << jj << " " << ii << std::endl;
        dist = (ii+0.5)*500.;
        weight = D1->GetBinContent(ii);
        Norm += weight;
        Pgauss = pdf->MakeChromPeakPDF(delta,dist,sigma0); 
	Preal += (500.0*weight)*(Pgauss);
        //Pgauss = pdf->MakeChromPeakPDF(delta,dist,sigma0,0,0,0); 
	//Preal += (500.0*weight)*(Pgauss);
        //Pgaussnon = pdf->MakeChromPeakPDF(delta,dist,sigma0,1,1,1); 
	//Prealnon += (500.0*weight)*(Pgaussnon);
        //PgaussA = pdf->MakeChromPeakPDF(delta,dist,sigma0,0,1,1); 
	//PrealA += (500.0*weight)*(PgaussA);
        //PgaussV = pdf->MakeChromPeakPDF(delta,dist,sigma0,1,0,1); 
	//PrealV += (500.0*weight)*(PgaussV);
        //PgaussAV = pdf->MakeChromPeakPDF(delta,dist,sigma0,0,0,1); 
	//PrealAV += (500.0*weight)*(PgaussAV);
     }

     if( Norm != 0.0) {
       Preal = Preal/Norm;
       //Prealnon = Prealnon/Norm;
       //Probnon->Fill(delta, Prealnon*0.05);
       //PrealA = PrealA/Norm;
       //ProbA->Fill(delta, PrealA*0.05);
       //PrealV = PrealV/Norm;
       //ProbV->Fill(delta, PrealV*0.05);
       //PrealAV = PrealAV/Norm;
       //ProbAV->Fill(delta, PrealAV*0.05);
     }
     Prob->Fill(delta, Preal*0.05);
  }

  std::cout << "Prob is ready" << std::endl;

  norm = Prob->Integral();
  Prob->Scale(0.442/norm);
  //norm = Probnon->Integral();
  //Probnon->Scale(1.0/norm);
  //norm = ProbA->Integral();
  //ProbA->Scale(1.0/norm);
  //norm = ProbV->Integral();
  //ProbV->Scale(1.0/norm);
  //norm = ProbAV->Integral();
  //ProbAV->Scale(1.0/norm);
  Prob->SetStats(0);
  Prob->SetLineColor(kBlue);
  Prob->SetLineWidth(1.75);
  (Prob->GetXaxis())->SetTitle("Time residual (ns)");
  (Prob->GetYaxis())->SetTitle("Probability");

  /*Probnon->SetStats(0);
  Probnon->SetLineColor(kRed);
  Probnon->SetLineWidth(2.0);
  (Probnon->GetXaxis())->SetTitle("Time residual (ns)");
  (Probnon->GetYaxis())->SetTitle("Probability");
  ProbA->SetStats(0);
  ProbA->SetLineColor(kMagenta);
  ProbA->SetLineWidth(2.0);
  (ProbA->GetXaxis())->SetTitle("Time residual (ns)");
  (ProbA->GetYaxis())->SetTitle("Probability");
  ProbV->SetStats(0);
  ProbV->SetLineColor(kBlue);
  ProbV->SetLineWidth(2.0);
  (ProbV->GetXaxis())->SetTitle("Time residual (ns)");
  (ProbV->GetYaxis())->SetTitle("Probability");
  ProbAV->SetStats(0);
  ProbAV->SetLineColor(kGreen+3);
  ProbAV->SetLineWidth(2.0);
  (ProbAV->GetXaxis())->SetTitle("Time residual (ns)");
  (ProbAV->GetYaxis())->SetTitle("Probability");*/
  //Prob->SetFillColor(kCyan-3);
//========================================================
  /*TF1 *gaus4 = new TF1("gaus4","gaus",3.8,4.2);
  TF1 *gaus6 = new TF1("gaus6","gaus",1.1,3.0);
  TF1 *gausP = new TF1("gausP","gaus",-0.4,1.2);
  timeresid4->Fit(gaus4,"R");
  Double_t sigma4 = gaus4->GetParameter(2);
  timeresid6->Fit(gaus6,"R");
  Double_t sigma6 = gaus6->GetParameter(2);
  Prob->Fit(gausP,"R");
  Double_t sigmaP = gausP->GetParameter(2);
  std::cout << setprecision(5) << 3.107345*sigma4 << " " << 3.107345*sigma6 << " " << 3.107345*sigmaP << std::endl;*/
//========================================================
  timeresid6->SetStats(0);
  timeresid6->SetLineWidth(1.75);
  //(timeresid6->GetXaxis())->SetTitle("time residual (ns)");
  //(timeresid6->GetXaxis())->SetTitle("wavelength (nm)");
  //(timeresid6->GetYaxis())->SetTitle("probability");
  /*timeresid5->SetStats(0);
  timeresid5->Draw("Same");
  timeresid5->SetLineColor(kBlue+1);*/
  timeresid4->SetStats(0);
  timeresid4->SetLineColor(kRed);
  timeresid4->SetLineWidth(1.75);
  //(timeresid6->GetXaxis())->SetTitle("time residual (ns)");
  //(timeresid4->GetXaxis())->SetTitle("wavelength (nm)");
  //(timeresid4->GetYaxis())->SetTitle("probability");
  /*timeresid3->SetStats(0);
  timeresid3->Draw("Same");
  timeresid3->SetLineColor(kGreen);*/
  /*timeresid2->SetStats(0);
  timeresid2->SetLineColor(kBlue);
  timeresid2->SetLineWidth(1.5);
  timeresid1->SetStats(0);
  //timeresid1->SetLineColor(kMagenta-5);
  timeresid1->SetLineWidth(1.5);*/
  
  /*lmdadist1->SetStats(0);
  lmdadist1->SetMarkerColor(2);
  lmdadist1->SetMarkerSize(0.3);
  lmdadist2->SetStats(0);
  lmdadist2->SetMarkerSize(0.3);*/

  /*TCanvas* can1 = new TCanvas("can1","",700,500);
  can1->cd();
  timeresid6->Draw(); timeresid4->Draw("Same");
  TLegend *mylegend1 = new TLegend(0.7,0.015,0.9,0.02,"");
  mylegend1->AddEntry(timeresid6, "MuNo/PhotNo/BoundNo", "l");
  mylegend1->AddEntry(timeresid4, "MuYes/PhotNo/BoundNo", "l");
  mylegend1->Draw();
  TCanvas* can2 = new TCanvas("can2","",700,500);
  can2->cd();
  timeresid4->Draw(); timeresid1->Draw("Same");
  TLegend *mylegend2 = new TLegend(0.7,0.015,0.9,0.02,"");
  mylegend2->AddEntry(timeresid1, "MuYes/PhotYes/BoundYes", "l");
  mylegend2->AddEntry(timeresid4, "MuYes/PhotNo/BoundNo", "l");
  mylegend2->Draw();*/
  //mylegend->AddEntry(timeresid3, "0.50ns", "l");
  //mylegend->AddEntry(timeresid4, "MuYes/PhotNo", "l");
  //mylegend->AddEntry(timeresid5, "0.05ns", "l");
  //mylegend1->AddEntry(timeresid6, "MuNo/PhotNo/BoundNo", "l");
  TCanvas* can3 = new TCanvas("can3","",700,500);
  can3->cd();
  Prob->Draw(); 
  timeresid4->Draw("Same"); timeresid6->Draw("Same"); Prob->Draw("Same");
  //Probnon->Draw("Same");ProbA->Draw("Same");ProbV->Draw("Same");//ProbAV->Draw("Same");Prob->Draw("Same");
  //can3->Divide(1,2); can3->cd(1), lmdadist1->Draw(); can3->cd(2); lmdadist2->Draw();
  //timeresid6->Draw();
  TLegend *mylegend3 = new TLegend(0.2,0.7,0.9,0.9,"");
  mylegend3->AddEntry(Prob, "IoanaPDF", "l");
  mylegend3->AddEntry(timeresid6, "YesYesYesYes", "l");
  mylegend3->AddEntry(timeresid4, "NoNoNoYes", "l");
  //mylegend3->AddEntry(Probnon, "IoanaPDFnoneWCSim", "l");
  //mylegend3->AddEntry(ProbA, "IoanaPDFabslWCSim", "l");
  //mylegend3->AddEntry(ProbV, "IoanaPDFindexWCSim", "l");
  //mylegend3->AddEntry(ProbAV, "IoanaPDFabsl&speedWCSim", "l");
  //mylegend3->AddEntry(Prob, "IoanaPDFallWCSim", "l");
  mylegend3->Draw();
  
}
