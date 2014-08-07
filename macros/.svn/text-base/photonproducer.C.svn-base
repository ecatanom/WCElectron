{
  gROOT->Reset();
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot");
  gSystem->Load("libWCSimAnalysis.so");

  #include <iostream>
  #include <iomanip>

  double test = 0.0;
  double lmda = 589.;
  double index = 1.33.;
  double velo = 30./1.3333;
  double t=5.0;
  double dist = 3000.;
  double absl = 0.;
  double sctl = 0.0;
  double qe = 0.;
  double att, att1, att2;
  double init,init1,init2;
  double chrom, chrom1, chrom2;
  double lmdastep = 2.0;
  double diststep = 2000.;
  double tempstep = 5.;
  double n0 = WCSimParameters::Instance()->RefractiveIndex(dist);

  /*TH2D *Tflight_lmda = new TH2D("Tflight_lmda","Tflight vs lmda",5000,200,700,1000,0,500);
  TH2D *Tflight_lmda = new TH2D("Tflight_lmda","Tflight vs lmda",5000,200,700,1000,-20.,200);
  TH2D *Init_lmda = new TH2D("Init_lmda","Initial Spectrum vs lmda",6000,100,700,5000,-0.05,0.05);
  TH2D *Att_lmda = new TH2D("Att_lmda","attenuation vs lmda",5000,200,700,1000,0.,1.0);
  TH2D *Velo_lmda = new TH2D("Velo_lmda","velo comparison vs lmda",5000,200,700,5000,10.0,25.0);
  TH2D *Index_lmda = new TH2D("Index_lmda","index vs lmda",5000,200,700,5000,1.0,2.0);
  TH2D *Index_dist = new TH2D("Index_dist","index vs dist, andy",1000,0.0,5000.,5000,1.0,2.0);
  TH2D *lmda_t = new TH2D("lmda_t","lmda vs t",5000,200.,700.,100,0.,50.);
  TH2D *Index_t = new TH2D("Index_lmda","index vs temp",1000,0.,100.,1000,1.30,1.40);
  TH2D *ChromCorr_lmda = new TH2D("ChromCorr_lmda","chromatic correction vs lmda",5000,200,700,1000,0.,0.05);
  TH2D *AbsL_lmda = new TH2D("AbsL_lmda","absorption length vs lmda",5000,200,700,10000,0.,15000.);
  TH2D *AbsL_lmda = new TH2D("AbsL_lmda","absorption length vs lmda",5000,200,700,10000,0.000001,1);
  TH2D *Tnorm_dist = new TH2D("Tnorm_dist","normT vs distance",1000,0.,5000.,1000,0.,2.);
  TH2D *Tflight_lmda = new TH2D("Tflight_lmda","Tflight vs lmda",1000,200.,700.,1000,-20,100);*/
  TH2D *lmda_depen1 = new TH2D("lmda_depen1","",1000,200.0,700.0,1000,15.0,25.0);
  TH2D *lmda_depen2 = new TH2D("lmda_depen2","",1000,-5.0,45.0,1000,0.0,0.1);
  TH2D *lmda_depen3 = new TH2D("lmda_depen3","",2900,190.,710.,10000,0.0,0.2);
  TH2D *dist_depen1 = new TH2D("dist_depen1","",1000,-10.,20.,1000,0.0,0.002);
  TH2D *dist_depen2 = new TH2D("dist_depen2","",1000,-10.,20.,1000,0.0,0.002);
  TH2D *dist_depen3 = new TH2D("dist_depen3","",1000,-10.,20.,1000,0.0,0.002);
  TH2D *dist_depen4 = new TH2D("dist_depen4","",1000,-10.,20.,1000,0.0,0.002);
  TH2D *dist_depen5 = new TH2D("dist_depen5","",1000,-10.,20.,1000,0.0,0.002);
  /*Double_t energyarr[60]={1.56962, 1.58974, 1.61039, 1.63157, 
       1.65333, 1.67567, 1.69863, 1.72222, 
       1.74647, 1.77142,1.7971, 1.82352, 
       1.85074, 1.87878, 1.90769, 1.93749, 
       1.96825, 1.99999, 2.03278, 2.06666,
       2.10169, 2.13793, 2.17543, 2.21428, 
       2.25454, 2.29629, 2.33962, 2.38461, 
       2.43137, 2.47999, 2.53061, 2.58333, 
       2.63829, 2.69565, 2.75555, 2.81817, 
       2.88371, 2.95237, 3.02438, 3.09999,
       3.17948, 3.26315, 3.35134, 3.44444, 
       3.54285, 3.64705, 3.75757, 3.87499, 
       3.99999, 4.13332, 4.27585, 4.42855, 
       4.59258, 4.76922, 4.95999, 5.16665, 
       5.39129, 5.63635, 5.90475, 6.19998 }; //eV
  /*Double_t arr[60]={16.1419,  18.278, 21.0657, 24.8568, 30.3117, 
	38.8341, 54.0231, 81.2306, 120.909, 160.238, 
	193.771, 215.017, 227.747,  243.85, 294.036, 
	321.647,  342.81, 362.827, 378.041, 449.378,
        739.434, 1114.23, 1435.56, 1611.06, 1764.18, 
	2100.95,  2292.9, 2431.33,  3053.6, 4838.23, 
	6539.65, 7682.63, 9137.28, 12220.9, 15270.7, 
	19051.5, 23671.3, 29191.1, 35567.9,   42583,
        49779.6, 56465.3,   61830, 65174.6, 66143.7,   
	  64820,   61635, 57176.2, 52012.1, 46595.7, 
	41242.1, 36146.3, 31415.4, 27097.8, 23205.7, 
	19730.3, 16651.6, 13943.6, 11578.5, 9526.13}; //absorption length, cm*/
  /*Double_t arr[60]={1.32885, 1.32906, 1.32927, 1.32948, 1.3297, 1.32992, 1.33014, 
      1.33037, 1.3306, 1.33084, 1.33109, 1.33134, 1.3316, 1.33186, 1.33213,
      1.33241, 1.3327, 1.33299, 1.33329, 1.33361, 1.33393, 1.33427, 1.33462,
      1.33498, 1.33536, 1.33576, 1.33617, 1.3366, 1.33705, 1.33753, 1.33803,
      1.33855, 1.33911, 1.3397, 1.34033, 1.341, 1.34172, 1.34248, 1.34331,
      1.34419, 1.34515, 1.3462, 1.34733, 1.34858, 1.34994, 1.35145, 1.35312,
      1.35498, 1.35707, 1.35943, 1.36211, 1.36518, 1.36872, 1.37287, 1.37776,
      1.38362, 1.39074, 1.39956, 1.41075, 1.42535};
  Double_t lmdaarr[60];
  for( Int_t kk=0;kk<60;kk++ ){ 
     lmdaarr[kk]=30.0*2.0*3.14*6.58/energyarr[kk]; 
     //std::cout << setprecision(6) << lmdaarr[kk] << ", ";
  }
  //std::cout<< std::endl;
  TGraph* testLg = new TGraph(60, lmdaarr, arr);*/
  WCSimWaterModel* water2 = WCSimWaterModel::Instance();

  //for( t = 0.;t < 100.; t = t+1.){
  //for ( dist = 0.;dist<=5000.;dist=dist+25.){
  double chromnorm, indexnorm;
  for ( lmda=700.;lmda>=200.;lmda=lmda-lmdastep ){
  //for( dist=0.0;dist<=500.;dist+=2.5 ){
  //test = testLg->Eval(lmda,0,"S");
  //index = water2->N_Index(lmda);
  velo = water2->Vg(lmda);
  //Double_t tmuon = water2->TimeMu(dist);
  //init = water2->InitSpect(lmda);
  absl = water2->AbsLength(lmda);
  //att = water2->Atten(lmda,dist);
  //att1 = water2->Atten(lmda,(dist-diststep));
  //att2 = water2->Atten(lmda,(dist+diststep));
  //chrom = water2->FinlSpect(lmda,dist);
  //chrom1 = water2->FinlSpect(lmda,(dist-diststep));
  //chrom2 = water2->FinlSpect(lmda,(dist+diststep));
  //water2->SetOPqe(0);
  //water2->SetQETable(emptyg);
  //qe = water2->QE(lmda);
  lmda_depen1->Fill(lmda,velo);
  lmda_depen2->Fill(lmda,chrom1);
  lmda_depen3->Fill(lmda,chrom2);
  //dist_depen1->Fill(dist,tmuon);
  //dist_depen2->Fill(dist,dist/30.);
  //chromnorm += chrom*qe;
  //indexnorm += index*chrom*qe;
  //std::cout << setprecision(6) << init << ", ";
  }
  lmda_depen1->Draw();
  //std::cout << std::endl;
  /*std::cout << "i am working" << std::endl;
  dist_depen->SetBinContent(Int_t(dist/25.),(indexnorm/chromnorm));
  }*/

  Double_t R = 2500.0; //cm
  Double_t MP = 320.0; //nm
  Double_t _sigma = 250.0; 
  Double_t sigma = 540.0;
  Double_t Vblue = water2->Vg(_sigma);
  Double_t Vred = water2->Vg(sigma);
  Double_t VMP = water2->Vg(MP);
  Double_t Emu = 800.0; //MeV
  Double_t Vmu = 30.0*sqrt(1-(105.0/Emu)*(105.0/Emu)); //cm/ns
  Double_t ccb = Vblue/Vmu;
  Double_t scb = sqrt(Vmu*Vmu-Vblue*Vblue)/Vmu;
  Double_t ccr = Vred/Vmu;
  Double_t scr = sqrt(Vmu*Vmu-Vred*Vred)/Vmu;
  Double_t ccp = VMP/Vmu;
  Double_t scp = sqrt(Vmu*Vmu-VMP*VMP)/Vmu;
  Double_t yred, yblue, yMP, hitr, hitb, hitMP, dtowall, tred, tblue, tMP, xred, xblue, xMP, deltapos, deltat;

//============================plate geometry====================================
  /*for(Int_t i=0;i<20;i++){
     dtowall = 1000.0+200.0*i;
     yMP = dtowall*scp/ccp;
     hitMP = dtowall/(ccp*VMP);
     WCSimVertexGeometry::CalcTResidandDist(0.0,0.0,0.0,0.0,1.0,0.0,0.0,dtowall,yMP,0.0,hitMP,MP,tMP,dist);
     yblue = dtowall*scb/ccb;
     hitb = dtowall/(ccb*Vblue);
     WCSimVertexGeometry::CalcTResidandDist(0.0,0.0,0.0,0.0,1.0,0.0,0.0,dtowall,yblue,0.0,hitb,_sigma,tblue,dist);
     yred = dtowall*scr/ccr;
     hitr = dtowall/(ccr*Vred);
     WCSimVertexGeometry::CalcTResidandDist(0.0,0.0,0.0,0.0,1.0,0.0,0.0,dtowall,yred,0.0,hitr,sigma,tred,dist);
     dist_depen1->Fill(dtowall,tblue);
     dist_depen2->Fill(dtowall,tMP);
     dist_depen3->Fill(dtowall,tred);
  }*/
  /*for(Int_t i=1;i<6;i++){
     dtowall = 1000.0+1000.0*i;
     for(lmda=200.0;lmda<700.;lmda+=5.0){
        VMP = water2->Vg(lmda); 
        ccp = VMP/Vmu;
        scp = sqrt(Vmu*Vmu-VMP*VMP)/Vmu;
        yMP = dtowall*scp/ccp;
        hitMP = dtowall/(ccp*VMP);
        WCSimVertexGeometry::CalcTResidandDist(0.0,0.0,0.0,0.0,1.0,0.0,0.0,dtowall,yMP,0.0,hitMP,lmda,tMP,dist);
        chrom = water2->FinlSpect(lmda,dist);
        if(i==1)dist_depen1->Fill(tMP,chrom);
        if(i==2)dist_depen2->Fill(tMP,chrom);
        if(i==3)dist_depen3->Fill(tMP,chrom);
        if(i==4)dist_depen4->Fill(tMP,chrom);
        if(i==5)dist_depen5->Fill(tMP,chrom);
     }
  }*/
//==========================round geometry=======================================
  /*for(Int_t i=-10;i<10;i++){
     dtowall = 200.0*i;
     xblue = dtowall*scb*scb+sqrt(R*R*ccb*ccb-scb*scb*ccb*ccb*dtowall*dtowall);
     yblue = scb*(xblue-dtowall)/ccb;
     hitb = (-dtowall*ccb+sqrt(R*R-dtowall*dtowall*scb*scb))/Vblue;
     xred = dtowall*scr*scr+sqrt(R*R*ccr*ccr-scr*scr*ccr*ccr*dtowall*dtowall);
     yred = scr*(xred-dtowall)/ccr;
     hitr = (-dtowall*ccr+sqrt(R*R-dtowall*dtowall*scr*scr))/Vred;
     WCSimVertexGeometry::CalcTResidandDist(dtowall,0.0,0.0,0.0,1.0,0.0,0.0,xred,yred,0.0,hitr,sigma,tred,dist);
     WCSimVertexGeometry::CalcTResidandDist(dtowall,0.0,0.0,0.0,1.0,0.0,0.0,xblue,yblue,0.0,hitb,_sigma,tblue,dist);
     xMP = dtowall*scp*scp+sqrt(R*R*ccp*ccp-scp*scp*ccp*ccp*dtowall*dtowall);
     yMP = scp*(xMP-dtowall)/ccp;
     hitMP = (-dtowall*ccp+sqrt(R*R-dtowall*dtowall*scp*scp))/VMP;
     WCSimVertexGeometry::CalcTResidandDist(dtowall,0.0,0.0,0.0,1.0,0.0,0.0,xMP,yMP,0.0,hitMP,MP,tMP,dist);
     //deltapos = R*(acos(ccb)-acos(ccr)-asin(dtowall*scb/R)+asin(dtowall*scr/R));
     //deltat = hitb - hitr;
     dist_depen1->Fill(2500.0-dtowall,tblue);
     dist_depen2->Fill(2500.0-dtowall,tMP);
     dist_depen3->Fill(2500.0-dtowall,tred);
  }*/
  /*for(Int_t i=1;i<6;i++){
     dtowall = 1000.0+1000.0*i;
     dtowall = 2500.0-dtowall;
     for(lmda=200.0;lmda<700.;lmda+=5.0){
        VMP = water2->Vg(lmda); 
        ccp = VMP/Vmu;
        scp = sqrt(Vmu*Vmu-VMP*VMP)/Vmu;
        xMP = dtowall*scp*scp+sqrt(R*R*ccp*ccp-scp*scp*ccp*ccp*dtowall*dtowall);
        yMP = scp*(xMP-dtowall)/ccp;
        hitMP = (-dtowall*ccp+sqrt(R*R-dtowall*dtowall*scp*scp))/VMP;
        WCSimVertexGeometry::CalcTResidandDist(dtowall,0.0,0.0,0.0,1.0,0.0,0.0,xMP,yMP,0.0,hitMP,lmda,tMP,dist);
        chrom = water2->FinlSpect(lmda,dist);
        if(i==1)dist_depen1->Fill(tMP,chrom);
        if(i==2)dist_depen2->Fill(tMP,chrom);
        if(i==3)dist_depen3->Fill(tMP,chrom);
        if(i==4)dist_depen4->Fill(tMP,chrom);
        if(i==5)dist_depen5->Fill(tMP,chrom); }
  }*/
//====================================================================
  /*for(Int_t i=1;i<6;i++){
     lmda = 150.0 + i*100.0;
     velo = water2->Vg(lmda);
     for(Emu=200.0;Emu<1100.0;Emu+=50.0){
        Vmu = 30.0*sqrt(1-(105.0/Emu)*(105.0/Emu)); 
        ccp = 180.0*acos(velo/Vmu)/3.14;
        if(i==1)dist_depen1->Fill(Emu,ccp);
        if(i==2)dist_depen2->Fill(Emu,ccp);
        if(i==3)dist_depen3->Fill(Emu,ccp);
        if(i==4)dist_depen4->Fill(Emu,ccp);
        if(i==5)dist_depen5->Fill(Emu,ccp); 
     }
  }*/

//====================================================================

  /*(dist_depen1->GetXaxis())->SetTitle("time residual (ns)");
  (dist_depen1->GetYaxis())->SetTitle("weight");
  dist_depen1->SetStats(0);
  dist_depen1->SetMarkerSize(0.5);
  dist_depen1->SetMarkerColor(kViolet);
  dist_depen2->SetStats(0);
  dist_depen2->SetMarkerSize(0.5);
  dist_depen2->SetMarkerColor(kBlue);
  dist_depen3->SetStats(0);
  dist_depen3->SetMarkerSize(0.5);
  dist_depen3->SetMarkerColor(kGreen+2);
  dist_depen4->SetStats(0);
  dist_depen4->SetMarkerSize(0.5);
  dist_depen4->SetMarkerColor(kOrange+7);
  dist_depen5->SetStats(0);
  dist_depen5->SetMarkerSize(0.5);
  dist_depen5->SetMarkerColor(kRed+1);*/

  /*TCanvas *c2 = new TCanvas("c2","test canvas",200,10,600,400);
  gPad->SetGrid();
  //gPad->SetLogy();
  dist_depen1->Draw(); dist_depen2->Draw("Same"); dist_depen3->Draw("Same"); dist_depen4->Draw("Same"); dist_depen5->Draw("Same");

  TLegend *mylegend3 = new TLegend(0.2,0.7,0.9,0.9,"");
  mylegend3->AddEntry(dist_depen1, "Vertex Position, 1000cm", "p");
  mylegend3->AddEntry(dist_depen2, "Vertex Position, 2000cm", "p");
  mylegend3->AddEntry(dist_depen3, "Vertex Position, 3000cm", "p");
  mylegend3->AddEntry(dist_depen4, "Vertex Position, 4000cm", "p");
  mylegend3->AddEntry(dist_depen5, "Vertex Position, 5000cm", "p");
  mylegend3->Draw();*/

  //std::cout << water2->NormInit() << std::endl;
  /*dist_depen->SetStats(0);
  dist_depen->SetLineWidth(2);
  dist_depen->Draw();*/
  /*lmda_depen1->SetStats(0);
  (lmda_depen1->GetXaxis())->SetTitle("wavelength (nm)");
  (lmda_depen1->GetYaxis())->SetTitle("Final Spectrum");
  lmda_depen1->SetMarkerColor(kBlue);
  lmda_depen1->SetMarkerSize(0.5);
  lmda_depen1->Draw();
  lmda_depen2->SetStats(0);
  lmda_depen2->SetMarkerColor(kRed);
  lmda_depen2->SetMarkerSize(0.5);
  lmda_depen2->Draw("Same");
  lmda_depen3->SetStats(0);
  lmda_depen3->SetMarkerColor(kGreen+3);
  lmda_depen3->SetMarkerSize(0.5);
  lmda_depen3->Draw("Same");*/

  /*TAxis *xaxis = lmda_depen1->GetXaxis();
  xaxis->SetTitle("wavelength");
  xaxis->SetLabelSize(0.05);
  TAxis *yaxis = lmda_depen1->GetYaxis();
  yaxis->SetTitle("Attenuation Probability");
  yaxis->SetLabelSize(0.05);*/

  /*TPaveText *textbox = new TPaveText(400.,0.0003,550.,0.0005);
  textbox->SetFillColor(18);
  textbox->SetTextAlign(12);
  //TText *text1 = textbox->AddText("floating speed of muon ");
  //TText *text2 = textbox->AddText("fixed speed of muon ");
  //text2->SetTextColor(kRed);
  TText *text2 = textbox->AddText("distance = 10meter ");
  TText *text1 = textbox->AddText("distance = 30meter ");
  TText *text3 = textbox->AddText("distance = 50meter ");
  text1->SetTextColor(kBlue);
  text2->SetTextColor(kRed);
  text3->SetTextColor(kGreen+3);
  textbox->Draw();*/

  //std::cout << lmda << "\t" << index << "\t" << init << "\t" << absl << "\t" << att << "\t" << velo << "\t" << chromnorm << "\t" << (Tnorm/chromnorm) << std::endl;  
}
