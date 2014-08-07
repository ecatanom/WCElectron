{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");

  #include "TRandom3.h"
  TRandom3 numberp(42484);
  #include <iostream>
  #include <iomanip>

  // Path to WCSim ROOT file
  // =======================
  TString filename("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_MuSct_Ion.root");
  //TString filename("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_50percent_DetDev_noMuSct.root");
  //TString filename("/lbne/app/users/wetstein/SamplesForTian/MatchingEvents_newWCSim/Evt8.root");
  //TString filename("/lbne/app/users/txin/WCSim/branches/dev/DetectorDevelopment/wcsim.root");  
   
  // Load Data
  // =========
  WCSimInterface::LoadData(filename);
  Bool_t truehit = 1; // 1 is to use true hits
  Bool_t filtered = 1; // 1 is to use Andy's cut
  if(truehit){ 
    WCSimInterface::SetToUseTrueHits();
    WCSimInterface::Instance()->SmearTrueHits(0.1);
  WCSimInterface::Instance()->SetToMCP();
  WCSimInterface::Instance()->SetToGated();
    //WCSimInterface::Instance()->UsePMTPosition();
  }
  WCSimDataCleaner::Instance()->NeighbourRadius(300.0);
  WCSimDataCleaner::Instance()->NeighbourDigits(50.0);
  //WCSimDataCleaner::Instance()->TimeWindow(25.0);
  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);

  // get first entry 
  WCSimVertexFinder *findit = WCSimVertexFinder::Instance();
  WCSimInterface::LoadEvent(35);
  
  // WCSimInterface::BuildEvent(myEvent);
  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();

  int myNdigits = recoEvent->GetNDigits();
  WCSimRecoAB* haReco = new WCSimRecoAB();
  if(filtered) haReco->RunFilter(recoEvent);
  //if(filtered) haReco->RunSuperFilter(recoEvent);

  // get true quantities
  Double_t trueX = trueEvent->GetVtxX(); //trueX += 1.0;
  Double_t trueY = trueEvent->GetVtxY();
  Double_t trueZ = trueEvent->GetVtxZ(); 
  Double_t dirX = trueEvent->GetDirX();
  Double_t dirY = trueEvent->GetDirY();
  Double_t dirZ = trueEvent->GetDirZ();
  Double_t trueT = 0.0;
  double theta = (TMath::Pi())/2.0 - atan(dirZ/sqrt(dirX*dirX+dirY*dirY));
  double phi = 0.0;
  if( dirX<0.0 ) phi = TMath::Pi() - asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY>0.0 ) phi = asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY<0.0 ) phi = 2.0*TMath::Pi() + asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else( dirY=0.0 ) phi = 0.0;
  int op = 9;
  double range = 25.0;
  double weight = 1.0;

  /*theta = theta - (2.0*TMath::Pi()/180.0);
  phi = phi - (2.0*TMath::Pi()/180.0);
  dirX = sin(theta)*cos(phi);
  dirY = sin(theta)*sin(phi);
  dirZ = cos(theta);*/
  //double step=2.0*range/41.0;
  //trueX = trueX + 0.0*step*dirZ;
  //trueZ = trueZ - 0.0*step*dirX;
  
//======================== draw FOM ==============================
  WCSimTResidPDF *pdf = WCSimTResidPDF::Instance();
  double size;
  double thisX, thisY, thisZ, thisT, thisdx, thisdy, thisdz, thistheta, thisphi,thisAngle;
  thisX = trueX; thisY = trueY; thisZ = trueZ; thisdx = dirX; thisdy = dirY; thisdz = dirZ; thisphi = phi; thistheta = theta;
  TLegend *mylegend = new TLegend(0.5,0.75,0.9,0.9,"");
  double timeFOM = 0.0;
  double coneFOM = 0.0;
  double penaltyFOM = 0.0;

//======================= fit vtxTime ===========================
  Double_t fC = WCSimParameters::SpeedOfLight(); cout << fC << endl;
  /*Double_t j = -3.0;
  trueX = trueX + j*thisdx*size;
  trueY = trueY + j*thisdy*size;
  trueZ = trueZ + j*thisdz*size;
  trueT = 0.1744 + j*size/fC;
  double test1 = findit->FOMhit(recoEvent,thisX,thisY,thisZ,trueT,thisdx,thisdy,thisdz);
  trueT = 0.17438 + j*size/fC;
  double test2 = findit->FOMhit(recoEvent,thisX,thisY,thisZ,trueT,thisdx,thisdy,thisdz);
  trueT = 0.17474 + j*size/fC;
  double test3 = findit->FOMhit(recoEvent,thisX,thisY,thisZ,trueT,thisdx,thisdy,thisdz);
  cout << "maxT: " << setprecision(15) << test1 << " fitT-2: " << test2 << " fitT-3: " << test3 << endl;*/
  //findit->ExtendedVertexChi2(recoEvent,thisX,thisY,thisZ,thisdx,thisdy,thisdz,timeFOM,coneFOM,penaltyFOM,thisT,thisAngle);
  //cout << (thisT-j*size/fC) << " FOM is: " << timeFOM << endl;

  //timeFOM=findit->FOMhit(recoEvent,trueX,trueY,trueZ,trueT,dirX,dirY,dirZ); cout<<timeFOM<<endl;
//=============================PosX=================================
  if( op==1 ){
    TH1D *htime = new TH1D("htime","",41, trueX-range, trueX+range);
    TH1D *hcone = new TH1D("hcone","",41, trueX-range, trueX+range);
    TH1D *hpenalty = new TH1D("hpenalty","",41, trueX-range, trueX+range);
    size = 2.0*range/41.0;
    for(int i=-20;i<21;i++){
      cout << "----------the " << i << " step---------" << endl;
      thisX = trueX + i*size;  
      findit->ExtendedVertexChi2(recoEvent,thisX,thisY,thisZ,thisdx,thisdy,thisdz,timeFOM,coneFOM,penaltyFOM,thisT,thisAngle);
      //findit->ExtendedResiduals(thisX,thisY,thisZ,thisdx,thisdy,thisdz);
      //findit->FitExtendedTimePropertiesLnL(thisT,timeFOM);
      cout << timeFOM << " " << coneFOM << " " << penaltyFOM << endl;
      htime->SetBinContent(i+21,timeFOM);
      hcone->SetBinContent(i+21,coneFOM);
      hpenalty->SetBinContent(i+21,(0.5*timeFOM+0.5*coneFOM+penaltyFOM));
    }
    (htime->GetXaxis())->SetTitle("hypothesis X");
    (htime->GetYaxis())->SetTitle("timeFOM");
    (hcone->GetXaxis())->SetTitle("hypothesis X");
    (hcone->GetYaxis())->SetTitle("coneFOM");
    (hpenalty->GetXaxis())->SetTitle("hypothesis X");
    (hpenalty->GetYaxis())->SetTitle("FOM");
    std::ostringstream sstream;
    sstream << "trueX= " << trueX;
    std::string stri = sstream.str();	
    char *ch = new char[stri.size()+1];
    strcpy(ch, stri.c_str());
    mylegend->AddEntry(htime, ch, "l");
    
  }
//============================PosY===================================
  if( op==2 ){
    TH1D *htime = new TH1D("htime","",41, trueY-range, trueY+range);
    TH1D *hcone = new TH1D("hcone","",41, trueY-range, trueY+range);
    TH1D *hpenalty = new TH1D("hpenalty","",41, trueY-range, trueY+range);
    size = 2.0*range/41.0;
    for(int i=-20;i<21;i++){
      cout << "----------the " << i << " step---------" << endl;
      thisY = trueY + i*size;  
      findit->ExtendedVertexChi2(recoEvent,thisX,thisY,thisZ,thisdx,thisdy,thisdz,timeFOM,coneFOM,penaltyFOM,thisT,thisAngle);
      //cout << timeFOM << " " << coneFOM << " " << penaltyFOM << endl;
      htime->SetBinContent(i+21,timeFOM);
      hcone->SetBinContent(i+21,coneFOM);
      hpenalty->SetBinContent(i+21,(0.5*timeFOM+0.5*coneFOM+penaltyFOM));
    }
    (htime->GetXaxis())->SetTitle("hypothesis Y");
    (htime->GetYaxis())->SetTitle("timeFOM");
    (hcone->GetXaxis())->SetTitle("hypothesis Y");
    (hcone->GetYaxis())->SetTitle("coneFOM");
    (hpenalty->GetXaxis())->SetTitle("hypothesis Y");
    (hpenalty->GetYaxis())->SetTitle("FOM");
    std::ostringstream sstream;
    sstream << "trueY= " << trueY;
    std::string stri = sstream.str();	
    char *ch = new char[stri.size()+1];
    strcpy(ch, stri.c_str());
    mylegend->AddEntry(htime, ch, "l");
  }
//============================PosZ===================================
  /*if( op==3 ){
    TH1D *htime = new TH1D("htime","",21, trueZ-range, trueZ+range);
    size = 2.0*range/21.0;
    for(int i=-10;i<11;i++){
      thisZ = trueZ + i*size;  
      double FOM = 0.0;
      double norm = 0.0;
      for(int l=0; l<NFilterdigits; l++){
        hitX = vhitX[l]; hitY = vhitY[l]; hitZ = vhitZ[l]; hitT = vhitT[l]; res = vRes[l];
        WCSimVertexGeometry::CalcTResidandDistMu(thisX, thisY, thisZ, thisT, thisdx, thisdy, thisdz, hitX, hitY, hitZ, hitT, TResid, LPhot, LMuon);  
        if( (LMuon>0.0 && LMuon<=800.0 ) || !Lmu ){
          double Prob = pdf->MakeChromPeakPDF(TResid,LPhot,res); 
          if( noise ) Prob = Prob + 0.1/NFilterdigits;
          if( Prob>0.0 ) {FOM = FOM - 2*log(Prob); 
          norm += 1.0;}
        }
      }
    if(opN==0) {htime->SetBinContent(i+11,FOM); cout << i << " " << FOM << " " << norm << endl; }
    else { htime->SetBinContent(i+11,FOM/norm); cout << i << " " << FOM << " " << norm << endl; }
    }
  (htime->GetXaxis())->SetTitle("hypothesis Z");
  std::ostringstream sstream;
  sstream << "trueZ= " << trueZ;
  std::string stri = sstream.str();	
  char *ch = new char[stri.size()+1];
  strcpy(ch, stri.c_str());
  mylegend->AddEntry(htime, ch, "l");
  }*/
//==========================Pos Z=========================================
  if( op==3 ){
    TH1D *htime = new TH1D("htime","",41, trueZ-range, trueZ+range);
    TH1D *hcone = new TH1D("hcone","",41, trueZ-range, trueZ+range);
    TH1D *hpenalty = new TH1D("hpenalty","",41, trueZ-range, trueZ+range);
    size = 2.0*range/41.0;
    for(int i=-20;i<21;i++){
      cout << "----------the " << i << " step---------" << endl;
      thisZ = trueZ + i*size;
      findit->ExtendedVertexChi2(recoEvent,thisX,thisY,thisZ,thisdx,thisdy,thisdz,timeFOM,coneFOM,penaltyFOM,thisT,thisAngle);
      //cout << timeFOM << " " << coneFOM << " " << penaltyFOM << endl;
      htime->SetBinContent(i+21,timeFOM);
      hcone->SetBinContent(i+21,coneFOM);
      hpenalty->SetBinContent(i+21,(0.5*timeFOM+0.5*coneFOM+penaltyFOM));
    }
    (htime->GetXaxis())->SetTitle("hypothesis Z");
    (htime->GetYaxis())->SetTitle("timeFOM");
    (hcone->GetXaxis())->SetTitle("hypothesis Z");
    (hcone->GetYaxis())->SetTitle("coneFOM");
    (hpenalty->GetXaxis())->SetTitle("hypothesis Z");
    (hpenalty->GetYaxis())->SetTitle("FOM");
    std::ostringstream sstream;
    sstream << "true z = " << trueZ;
    std::string stri = sstream.str();	
    char *ch = new char[stri.size()+1];
    strcpy(ch, stri.c_str());
    mylegend->AddEntry(htime, ch, "l");
  }
//============================Tvtx===================================
  if( op==4 ){
    TH1D *htime = new TH1D("htime","",41, trueT-range, trueT+range);
    size = 2.0*range/41.0;
    for(int i=-20;i<21;i++){
      thisT = trueT + i*size;  
      double FOM = 0.0;
      double norm = 0.0;
      for(int l=0; l<NFilterdigits; l++){
        hitX = vhitX[l]; hitY = vhitY[l]; hitZ = vhitZ[l]; hitT = vhitT[l]; res = vRes[l];
        WCSimVertexGeometry::CalcTResidandDistMu(thisX, thisY, thisZ, thisT, thisdx, thisdy, thisdz, hitX, hitY, hitZ, hitT, TResid, LPhot, LMuon);  
        if( Lmu ){
        if( LMuon<0.0 ) weight = exp(LMuon/50.0);
        else if( LMuon>LmuMin ) weight = exp(-(LMuon-LmuMin)/100.0);
        else weight = 1.0; }
          double Prob = pdf->MakeChromPeakPDF(TResid,LPhot,res); 
          if( noise ) Prob = weight*Prob + 0.01/NFilterdigits;
          if( Prob>0.0 ) {FOM = FOM - 2*log(Prob); 
          norm += 1.0;}
      }
    if(opN==0) {htime->SetBinContent(i+21,FOM); cout << i << " " << FOM << " " << norm << endl; }
    else { htime->SetBinContent(i+21,FOM/norm); cout << i << " " << FOM << " " << norm << endl; }
    }
  (htime->GetXaxis())->SetTitle("hypothesis T");
  std::ostringstream sstream;
  sstream << "trueT= " << trueT;
  std::string stri = sstream.str();	
  char *ch = new char[stri.size()+1];
  strcpy(ch, stri.c_str());
  mylegend->AddEntry(htime, ch, "l");
  }
//============================theta===================================
  if( op==5 ){
    TH1D *htime = new TH1D("htime","",21, theta-range, theta+range);
    TH1D *hcone = new TH1D("hcone","",21, theta-range, theta+range);
    TH1D *hpenalty = new TH1D("hpenalty","",21, theta-range, theta+range);
    TH1D *ht = new TH1D("ht","",21,-range,range);
    size = 2.0*range/21.0;
    for(int i=-10;i<11;i++){
      cout << "----------the " << i << " step---------" << endl;
      thistheta = theta + i*size;
      thisdx = cos(thisphi)*sin(thistheta);
      thisdy = sin(thisphi)*sin(thistheta);
      thisdz = cos(thistheta);
      findit->ExtendedVertexChi2(recoEvent,thisX,thisY,thisZ,thisdx,thisdy,thisdz,timeFOM,coneFOM,penaltyFOM,thisT,thisAngle);
      //cout << timeFOM << " " << coneFOM << " " << penaltyFOM << endl;
      htime->SetBinContent(i+11,timeFOM);
      hcone->SetBinContent(i+11,coneFOM);
      hpenalty->SetBinContent(i+11,penaltyFOM);
      ht->SetBinContent(i+11,thisT);
    }
    (htime->GetXaxis())->SetTitle("hypothesis theta");
    (htime->GetYaxis())->SetTitle("timeFOM");
    (hcone->GetXaxis())->SetTitle("hypothesis theta");
    (hcone->GetYaxis())->SetTitle("coneFOM");
    (hpenalty->GetXaxis())->SetTitle("hypothesis theta");
    (hpenalty->GetYaxis())->SetTitle("newFOM");
    (ht->GetXaxis())->SetTitle("hypothesis perp2");
    (ht->GetYaxis())->SetTitle("Tfit");
    std::ostringstream sstream;
    sstream << "true theta= " << theta;
    std::string stri = sstream.str();	
    char *ch = new char[stri.size()+1];
    strcpy(ch, stri.c_str());
    mylegend->AddEntry(htime, ch, "l");
  }
//============================phi===================================
  if( op==6 ){
    TH1D *htime = new TH1D("htime","",41, phi-range, phi+range);
    TH1D *hcone = new TH1D("hcone","",41, phi-range, phi+range);
    TH1D *hpenalty = new TH1D("hpenalty","",41, phi-range, phi+range);
    size = 2.0*range/41.0;
    for(int i=-20;i<21;i++){
      thisphi = phi + i*size;
      thisdx = cos(thisphi)*sin(thistheta);
      thisdy = sin(thisphi)*sin(thistheta);
      thisdz = cos(thistheta);
      findit->ExtendedVertexChi2(recoEvent,thisX,thisY,thisZ,thisdx,thisdy,thisdz,timeFOM,coneFOM,penaltyFOM,thisT,thisAngle);
      //cout << timeFOM << " " << coneFOM << " " << penaltyFOM << endl;
      htime->SetBinContent(i+21,timeFOM);
      hcone->SetBinContent(i+21,coneFOM);
      hpenalty->SetBinContent(i+21,(0.5*timeFOM+0.5*coneFOM+penaltyFOM));
    }
    (htime->GetXaxis())->SetTitle("hypothesis phi");
    (htime->GetYaxis())->SetTitle("timeFOM");
    (hcone->GetXaxis())->SetTitle("hypothesis phi");
    (hcone->GetYaxis())->SetTitle("coneFOM");
    (hpenalty->GetXaxis())->SetTitle("hypothesis phi");
    (hpenalty->GetYaxis())->SetTitle("newFOM");
    std::ostringstream sstream;
    sstream << "true phi= " << phi;
    std::string stri = sstream.str();	
    char *ch = new char[stri.size()+1];
    strcpy(ch, stri.c_str());
    mylegend->AddEntry(htime, ch, "l");
  }
//==============================parallel================================
  if( op==7 ){
    TH1D *htime = new TH1D("htime","",21, -range, range);
    TH1D *hcone = new TH1D("htime","",21, -range, range);
    TH1D *hpenalty = new TH1D("hpenalty","",21, -range, range);
    TH1D *ht = new TH1D("ht","",21,-range,range);
    size = 2.0*range/21.0;
    for(int i=-10;i<11;i++){
      thisX = trueX + i*thisdx*size;
      thisY = trueY + i*thisdy*size;
      thisZ = trueZ + i*thisdz*size;
      findit->ExtendedVertexChi2(recoEvent,thisX,thisY,thisZ,thisdx,thisdy,thisdz,timeFOM,coneFOM,penaltyFOM,thisT,thisAngle);
      //double Ttheo = (WCSimWaterModel::Instance())->TimeMu(i*size,1200.0);
      double Ttheo = (i*size)/fC;
      //cout << timeFOM << " " << coneFOM << " " << penaltyFOM << endl;
      htime->SetBinContent(i+11,timeFOM);
      hcone->SetBinContent(i+11,coneFOM);
      hpenalty->SetBinContent(i+11,penaltyFOM);
      ht->SetBinContent(i+11,(thisT-Ttheo));
    }
    (htime->GetXaxis())->SetTitle("hypothesis para");
    (htime->GetYaxis())->SetTitle("timeFOM");
    (hcone->GetXaxis())->SetTitle("hypothesis para");
    (hcone->GetYaxis())->SetTitle("coneFOM");
    (hpenalty->GetXaxis())->SetTitle("hypothesis para");
    (hpenalty->GetYaxis())->SetTitle("newFOM");
    (ht->GetXaxis())->SetTitle("hypothesis para");
    (ht->GetYaxis())->SetTitle("Tfit - Ttheo");
    mylegend->AddEntry(htime, "para_( dirX,dirY,dirZ )", "l");
  }
//==============================perpendicular 1================================
  if( op==8 ){
    TH1D *htime = new TH1D("htime","",41, -range, range);
    TH1D *hcone = new TH1D("htime","",41, -range, range);
    TH1D *hpenalty = new TH1D("hpenalty","",41, -range, range);
    size = 2.0*range/41.0;
    for(int i=-20;i<41;i++){
      thisX = trueX + i*thisdz*size;
      thisZ = trueZ - i*thisdx*size;
      findit->ExtendedVertexChi2(recoEvent,thisX,thisY,thisZ,thisdx,thisdy,thisdz,timeFOM,coneFOM,penaltyFOM,thisT,thisAngle);
      //cout << timeFOM << " " << coneFOM << " " << penaltyFOM << endl;
      htime->SetBinContent(i+21,timeFOM);
      hcone->SetBinContent(i+21,coneFOM);
      hpenalty->SetBinContent(i+21,(0.5*timeFOM+0.5*coneFOM+penaltyFOM));
      //hpenalty->SetBinContent(i+21,penaltyFOM);
    }
    (htime->GetXaxis())->SetTitle("hypothesis perp1");
    (htime->GetYaxis())->SetTitle("timeFOM");
    (hcone->GetXaxis())->SetTitle("hypothesis perp1");
    (hcone->GetYaxis())->SetTitle("coneFOM");
    (hpenalty->GetXaxis())->SetTitle("hypothesis perp1");
    (hpenalty->GetYaxis())->SetTitle("newFOM");
  mylegend->AddEntry(htime, "perp1_( dirZ,0.0,-dirX )", "l");
  }
//==============================perpendicular 2================================
  if( op==9 ){
    TH1D *htime = new TH1D("htime","",21, -range, range);
    TH1D *hcone = new TH1D("htime","",21, -range, range);
    TH1D *hpenalty = new TH1D("hpenalty","",21, -range, range);
    TH1D *ht = new TH1D("ht","",21,-range,range);
    size = 2.0*range/21.0;
    for(int i=-10;i<11;i++){
      thisX = trueX - i*thisdy*size;
      thisY = trueY + i*thisdx*size;
      findit->ExtendedVertexChi2(recoEvent,thisX,thisY,thisZ,thisdx,thisdy,thisdz,timeFOM,coneFOM,penaltyFOM,thisT,thisAngle);
      //cout << timeFOM << " " << coneFOM << " " << penaltyFOM << endl;
      htime->SetBinContent(i+11,timeFOM);
      hcone->SetBinContent(i+11,coneFOM);
      hpenalty->SetBinContent(i+11,penaltyFOM);
      ht->SetBinContent(i+11,thisT);
    }
    (htime->GetXaxis())->SetTitle("hypothesis perp2");
    (htime->GetYaxis())->SetTitle("timeFOM");
    (hcone->GetXaxis())->SetTitle("hypothesis perp2");
    (hcone->GetYaxis())->SetTitle("coneFOM");
    (hpenalty->GetXaxis())->SetTitle("hypothesis perp2");
    (hpenalty->GetYaxis())->SetTitle("newFOM");
    (ht->GetXaxis())->SetTitle("hypothesis perp2");
    (ht->GetYaxis())->SetTitle("Tfit");
    mylegend->AddEntry(htime, "perp2_( -dirY, dirX, 0.0 )", "l");
  }
//==============================perpendicular 2================================
  /*if( op==9 ){
    TH1D *htime = new TH1D("htime","",41, -range, range);
    size = 2.0*range/41.0;
    for(int i=-20;i<21;i++){
      thisX = trueX - i*thisdy*size;
      thisY = trueY + i*thisdx*size;
      double FOM = 0.0;
      double norm = 0.0;
      for(int l=0; l<NFilterdigits; l++){
        hitX = vhitX[l]; hitY = vhitY[l]; hitZ = vhitZ[l]; hitT = vhitT[l]; res = vRes[l];
        WCSimVertexGeometry::CalcTResidandDistMu(thisX, thisY, thisZ, thisT, thisdx, thisdy, thisdz, hitX, hitY, hitZ, hitT, TResid, LPhot, LMuon);  
        if( Lmu ){
        if( LMuon<0.0 ) weight = exp(LMuon/50.0);
        else if( LMuon>LmuMin ) weight = exp(-(LMuon-LmuMin)/100.0);
        else weight = 1.0; }
          double Prob = pdf->MakeChromPeakPDF(TResid,LPhot,res); 
          if( noise ) Prob = weight*Prob + 0.01/NFilterdigits;
          if( Prob>0.0 ) {FOM = FOM - 2*log(Prob); 
          norm += 1.0;}
      }
      if(opN==0) {htime->SetBinContent(i+21,FOM); cout << i << " " << FOM << " " << norm << endl; }
      else { htime->SetBinContent(i+21,FOM/norm); cout << i << " " << FOM << " " << norm << endl; }
    }
    (htime->GetXaxis())->SetTitle("HypoPos Perpendicular2");
    mylegend->AddEntry(htime, "perp2_( -dirY, dirX, 0.0 )", "l");
  }*/
//============================================================================================
  //TCanvas *ca = new TCanvas("ca","",500,900);
  //ca->Divide(1,3);
  //ca->cd();
  htime->Draw();
  //mylegend->Draw();
  //ca->cd(2);
  //hcone->Draw();
  //ca->cd(3);
  //hpenalty->Draw();
  TCanvas *ca2 = new TCanvas("ca2","",500,300);
  //ca2->cd();
  //ht->Draw();
  
}
