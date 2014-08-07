//void wc_calibReco( Int_t ievent ) // this is to do calibReco for event # ievent
{
  
  // Clear global scope
  //gROOT->Reset();
  // Path to WCSim ROOT file
  // =======================
  //TString filename("/lbne/data/water/cosmic200kton20110518/rootfiles/cosmic_DUSEL_4850ft_surface_200kton.002.root");
  //TString filename("/lbne/data/water/atmos_cosmic6dec2010/cosmic_DUSEL_4850ft_fix_long_100kton.001.vec_0.root");
  
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
  /*#include "TRandom3.h"

  TRandom3 numberx(42484);
  TRandom3 numbery(7291);
  TRandom3 numberz(19472);  */
  
  // Load Geometry
  // =============
  //TChain* chainGeom = new TChain("wcsimGeoT","chainGeom");
  //WCSimRootGeom* myGeom = new WCSimRootGeom(); 
  //chainGeom->SetBranchAddress("wcsimrootgeom",&myGeom);
  //chainGeom->Add(filename.Data());
  
  // look at first entry (should only be one geometry...)
  //chainGeom->GetEntry(0);
  //Double_t numPMT = myGeom->GetWCNumPMT(); // number of PMTs
  
  // build geometry
  //WCSimGeometry::BuildGeometry(myGeom);
 
  // Load Data
  // =========
  //TChain* chain = new TChain("wcsimT","chain");
  
  //WCSimRootEvent* myEvent = new WCSimRootEvent();
  //chain->SetBranchAddress("wcsimrootevent",&myEvent);
  //chain->Add(filename.Data());

  //ios::ofstream risefile("result.txt",ios::app);
  
  // Lets set up my own output file

  /*TFile *MyFile = new TFile("test.root","RECREATE");
  if(MyFile->IsOpen()) std::cout <<" File opened successfully" << std::endl; 
  // Create an output TTree
  TTree *timeinfo = new TTree("timeinfo","Muon Track Information");*/

  // some truth information
  /*struct RecoVtxInfo
  {
    Double_t event;
    Double_t momentum;
    Double_t VtxX;
    Double_t VtxY;
    Double_t VtxZ;
    Double_t VtxT;
    Double_t theta;
    Double_t phi;
    Double_t DirX;
    Double_t DirY;
    Double_t DirZ;
  };

  RecoVtxInfo RecoVtx;
  timeinfo->Branch("Truth",&TruthBit,"event/D:momentum/D:VtxX/D:VtxY/D:VtxZ/D:theta/D:phi/D:DirX/D:DirY/D:DirZ/D");*/

  // interpolated locations for the detector assuming
  // a straight line from the truth vertex
  /*struct Detector
  {
    Double_t StartPointX;
    Double_t StartPointY;
    Double_t StartPointZ; // everything here is in cm
    Double_t StartPoint[3];
    Double_t EndPoint[3];
    Double_t EndPointX;
    Double_t EndPointY;
    Double_t EndPointZ;
    Double_t TrackLength;
    Double_t EventLength;
  };
  
  Detector DetBit;
  timeinfo->Branch("Detector",&DetBit,"StartPointX/D:StartPointY/D:StartPointZ/D:EndPointX/D:EndPointY/D:EndPointZ/D:TrackLength/D:EventLength/D");*/
  
  // some PMT information (
  
  /*struct PMTInfo
  {
    Double_t nPMT;
    Double_t totalQ;
    Double_t lowQ;
    Double_t highQ;
    Double_t firstT;
    Double_t lastT;
    Double_t nhits;     // number of cerenkov hits
    Double_t ndigihits; // number of PMTs with digitised hits
  };


  PMTInfo PMTbit;
  timeinfo->Branch("PMT",&PMTbit,"nPMT/D:totalQ/D:lowQ/D:highQ/D:firstT/D:lastT/D:nhits/D:ndigihits/D");*/

  // This is the output of my first pass reconstruction

  /*struct Reconstruction
  {
    Double_t tExitX;
    Double_t tExitY;
    Double_t tExitZ;
    Double_t ExitPhi;
    Double_t ExitT;
    Double_t theta;
    Double_t phi;
    Double_t residual;
    Double_t GoodHits;
    Double_t length;
  };
  
  Reconstruction Recobit;
  timeinfo->Branch("Reco",&Recobit,"tExitX/D:tExitY/D:tExitZ/D:ExitPhi/D:ExitT/D:theta/D:phi/D:residual/D:GoodHits/D:length/D");*/
  
  // muon truth info in ntuple form
  //TNtuple *ntuple = new TNtuple("ntuple","","x_vtx:y_vtx:z_vtx:x_end:y_end:z_end:dcosx:dcosy:dcosz");//outside the event loop the data are accumulated
  
  //TNtuple *ntuple2 = new TNtuple("ntuple2","","event:tube:x:y:z:phi:pe:distance:time");
  //TNtuple *ntuple5=new TNtuple("ntuple5","","event:theta:phi:good:bad:residual:trklength");

  Int_t startev = 0;
  Int_t endev = 200;
  
  Double_t hitX = 0.;
  Double_t hitY = 0.;
  Double_t hitZ = 0.;
  Double_t hitT = 0.;

  Double_t hitQ = 1.0;
  Int_t nhit = 0;

  Double_t trueX = 0.;
  Double_t trueY = 0.;
  Double_t trueZ = 0.;
  Double_t trueT = 0.;
  Double_t truethe = 0.;
  Double_t truephi = 0.;
  Double_t trueE = 0.;
  Int_t trueID = 0;

  Double_t recoX = 0.;
  Double_t recoY = 0.;
  Double_t recoZ = 0.;
  Double_t recoT = 0.;
  Double_t recothe = 0.;
  Double_t recophi = 0.;
  Double_t recoE = 0.;
  Int_t recoID = 0;

  Double_t vrtX = 0.;
  Double_t vrtY = 0.;
  Double_t vrtZ = 0.;
  Double_t vrtT = 0.;
  Double_t difFOM = 0.;

  Double_t devX, devY, devZ, devS;
  
  Double_t dx=0.0; dy=0.0; dz=0.0; ds=0.0; dt=0.0;
  TH1D *dX = new TH1D("dX","deviation of X", 100, -10., 10.);
  TH1D *dY = new TH1D("dY","deviation of Y", 100, -10., 5.5);
  TH1D *dZ = new TH1D("dZ","deviation of Z", 100, -10., 10.);
  TH1D *dT = new TH1D("dT","deviation of Time", 50, -1., 1.);
  TH1D *dS = new TH1D("dS","deviation of S", 100, 0., 20.);

  TH2D *dirXvsdX = new TH2D("dirXvsdX","dirX vs dX", 100, -1., 1., 100, -10., 10.);
  TH2D *dirYvsdY = new TH2D("dirYvsdY","dirY vs dY", 100, -1., 1., 100, -10., 10.);
  TH2D *dirZvsdZ = new TH2D("dirZvsdZ","dirZ vs dZ", 100, -1., 1., 100, -10., 10.);
  TH2D *devXvsL = new TH2D("DevXvsnB","deviation X vs nBottom",100,0.,50.,100,0.,40.);
  TH2D *devYvsL = new TH2D("DevYvsnB","deviation Y vs nBottom",100,0.,50.,100,0.,40.);
  TH2D *devZvsL = new TH2D("DevZvsnB","deviation Z vs nBottom",100,0.,50.,100,0.,40.);
  TH2D *devXYvsL = new TH2D("DevXYvsnB","deviation XY vs nBottom",100,0.,50.,100,0.,40);

  TH1D *Open = new TH1D("Open","openangle", 100, 0.,180.);
  TH1D *DistToTrk = new TH1D("DistToTrk","distance to track", 100, 0., 10.);
  TH1D *ToEdge = new TH1D("ToEdge","difference in distance to edge",100,-20.,20.);
  TH2D *DifFOM = new TH2D("DifFOM","difference in FOM",200,0.,40.,200,0.,10000.);
  TH1D *Tres = new TH1D("Tres","time residual",1000,-500.0,800.0);

  Double_t dirX = 0.;
  Double_t dirY = 0.;
  Double_t dirZ = 0.;
  
  Int_t nevent = 0;

  ofstream fitfname;
  fitfname.open("Fitted_Vertex_For_Matt.txt",ios::out);
  fitfname.close();

  char hitfname[250];
  char hitffname[250];

  ifstream hitf;
  ifstream fitf;
  ifstream eventf; 
  eventf.open("/lbne/app/users/wetstein/SamplesForTian/samples_fortian.txt",ios::in);
  //fitf.open("/lbne/app/users/txin/WCSimAnalysis/400Evt_Simple_True_Fit.txt",ios::in);

  for (Int_t i = 0; i < startev; i++) {

    eventf.getline(hitfname,250);
    //fitf >> trueX >> trueY >> trueZ >> vrtX >> vrtY >> vrtZ;
    //nevent ++;
  }

  for (Int_t ev = startev; ev < endev; ev++) {
    WCSimRecoEvent* mmevent = new WCSimRecoEvent;
 
    //fitf >> trueX >> trueY >> trueZ >> vrtX >> vrtY >> vrtZ;
    eventf.getline(hitfname,250,' ');
    eventf >> recoX >> recoY >> recoZ >> recoT >> recothe >> recophi >> recoE >> recoID >> trueX >> trueY >> trueZ >> trueT >> truethe >> truephi >> trueE >> trueID;	 
    trueX = trueX/10.;
    trueY = trueY/10.;
    trueZ = trueZ/10.;
    recoX = recoX/10.;
    recoY = recoY/10.;
    recoZ = recoZ/10.;
    
    dirX = cos(truethe)*cos(truephi);
    dirY = cos(truethe)*sin(truephi);
    dirZ = sin(truethe); 

    if(ev == startev) { for( Int_t iii = 0;iii<250;iii++ ) hitffname[iii] = hitfname[iii]; }
    else{ for( Int_t iii = 1;iii < 250;iii++ ) hitffname[iii-1] = hitfname[iii]; }
    hitf.open(hitffname, ios::in);  
    while(! hitf.eof()){
    hitf >> hitX >> hitY >> hitZ >> hitT;
    
    Int_t region = WCSimGeometry::kSide;
    WCSimRecoDigit* mmdigit = new WCSimRecoDigit(region, hitX/10., hitY/10., hitZ/10., hitT, 1., hitT, 1.);
    mmevent->AddDigit(mmdigit);
    mmevent->AddFilterDigit(mmdigit);
    }
    hitf.close();
       
    /*WCSimRecoDigit* testdigit = mmevent->GetFilterDigit(3);//for myevent test
    Double_t testX = testdigit->GetX();*/

    WCSimRootGeom* myGeom = new WCSimRootGeom();
    WCSimGeometry::BuildGeometry(myGeom);

    
    //Double_t prob = number.Rndm();
    /*dirX = -1.0+2.0*(numberx.Rndm());
    dirY = -1.0+2.0*(numbery.Rndm());
    dirZ = -1.0+2.0*(numberz.Rndm());
    Double_t ss = sqrt(dirX*dirX+dirY*dirY+dirZ*dirZ);
    dirX = dirX/ss;
    dirY = dirY/ss;
    dirZ = dirZ/ss;*/
    WCSimRecoVertex* mmVertex = WCSimVertexFinderPoint::Instance()->RunPointFit1(mmevent, recoX, recoY, recoZ);
    std::cout << "Am i still good" << std::endl;
    vrtX = mmVertex->GetX();
    vrtY = mmVertex->GetY();
    vrtZ = mmVertex->GetZ();
    vrtT = mmVertex->GetTime();
    Double_t ffom = mmVertex->GetFOM();

    Double_t test = WCSimVertexFinderPoint::Instance()->FOMCalc(mmevent,vrtX,vrtY,vrtZ,vrtT,Tres);
    Int_t nnn = 0;
    for( Int_t ii=0;ii<1000;ii++){
      nnn += Tres->GetBinContent(ii);
    }

    /*std::cout << "fitted one " << vrtX << " " << vrtY << " " << vrtZ << " " << vrtT << std::endl;
    std::cout << "guessed one " << recoX << " " << recoY << " " << recoZ << std::endl;
    std::cout << "true one " << trueX << " " << trueY << " " << trueZ << std::endl;
    std::cout << "old fit is: " << fitX << " " << fitY << " " << fitZ << " " << fitS << std::endl;*/
    //std::cout << "check if the fill is good: " << testX << std::endl;

  
  //std::cout << "refractive index: " << fN << std::endl;
  /*std::cout << hitX << " " << hitY << " " << hitZ << std::endl;
  std::cout << hitT << " " << trueT << " " << tmu << " " << tpho << " " << timeres << std::endl;*/

  /*TCanvas *hit = new TCanvas("hit", "hit information", 800, 1000);
  hit->Divide(2,2);
  hit->cd(1);
  HitX->Draw();      
  hit->cd(2);
  HitY->Draw();
  hit->cd(3);
  HitZ->Draw();*/

  /*TCanvas *vtx = new TCanvas("vtx", "vertex information", 800, 1000);
  vtx->Divide(2,2);
  vtx->cd(1);
  VtxX->Draw();
  vtx->cd(2);
  VtxY->Draw();
  vtx->cd(3);
  VtxZ->Draw();*/
  //std::cout << "check if the fill is good: " << testX << std::endl;
//===============================================================================
  /*if((vrtT - trueT)<=50.){
    dx = vrtX - trueX/10.; //cm
    dXg->Fill(dx/100.);
    dy = vrtY - trueY/10.;
    dYg->Fill(dy/100.);
    dz = vrtZ - trueZ/10.;
    dZg->Fill(dz/100.);
    dt = vrtT - trueT;
    dTg->Fill(dt);
    ds = sqrt(dx*dx+dy*dy+dz*dz);
    dSg->Fill(ds/100.);}
  else{
    dx = vrtX - trueX/10.; //cm
    dXb->Fill(dx/100.);
    dy = vrtY - trueY/10.;
    dYb->Fill(dy/100.);
    dz = vrtZ - trueZ/10.;
    dZb->Fill(dz/100.);
    dt = vrtT - trueT;
    dTb->Fill(dt);
  }*/

    dx = (vrtX - trueX); //cm
    dy = (vrtY - trueY);
    dz = (vrtZ - trueZ);
    dt = vrtT - trueT;
    ds = sqrt(dx*dx+dy*dy+dz*dz);
    dX->Fill(dx/100.);
    dY->Fill(dy/100.);
    dZ->Fill(dz/100.);
    dS->Fill(ds/100.);
    std::cout << "deviation is: " << dx/100. << " " << dy/100. << " " << dz/100. << " " << ds/100. << " " << nnn << std::endl;
    //dirXvsdX->Fill(dirX,dx/100.);
    //dirYvsdY->Fill(dirY,dy/100.);
    //dirZvsdZ->Fill(dirZ,dz/100.);

    /*Double_t trueDist = WCSimGeometry::Instance()->DistanceToEdgeMatt(trueX,trueY,trueZ);
    Double_t fitDist = WCSimGeometry::Instance()->DistanceToEdgeMatt(vrtX,vrtY,vrtZ);
    ToEdge->Fill((trueDist - fitDist)/100.);*/

    /*Double_t nbot = WCSimVertexFinderPoint::Instance()->BotFrac(mmevent);
    Double_t trkL = WCSimVertexFinderPoint::Instance()->TrackL(trueX, trueY, trueZ, dirX, dirY, dirZ);
    Double_t openA = WCSimVertexFinderPoint::Instance()->Openagl(trueX, trueY, trueZ, dirX, dirY, dirZ, mmevent);
    Double_t distH = WCSimVertexFinderPoint::Instance()->DistHit(trueX, trueY, trueZ, mmevent);
    Double_t truePos[3]={trueX/10.,trueY/10.,trueZ/10.};
    Double_t fitPos[3]={vrtX,vrtY,vrtZ};
    Double_t trueDir[3]={dirX,dirY,dirZ};
    Double_t openangle, D, d;
    WCSimVertexFinderPoint::Instance()->GlbPeakGeo(truePos,trueDir,fitPos,openangle,D,d);
    openangle = openangle*180.0/TMath::Pi();*/

    /*if( (trkL>=2500.) && (trkL<=2750.) && (openA>=37.5) && (openA<=40.) ){
    devXvsL->Fill(nbot,dx/(dirX*100.));
    devYvsL->Fill(nbot,dy/(dirY*100.));
    devZvsL->Fill(nbot,dz/(dirZ*100.));
    devXYvsL->Fill(nbot,sqrt(dx*dx+dy*dy)/(sqrt(dirX*dirX+dirY*dirY)*100.));}*/
    /*if( (nbot>=0.125) && (nbot<=0.15) && (openA>=37.5) && (openA<=40.) ){
    devXvsL->Fill(distH/100.,dx/(dirX*100.));
    devYvsL->Fill(distH/100.,dy/(dirY*100.));
    devZvsL->Fill(distH/100.,dz/(dirZ*100.));
    devXYvsL->Fill(distH/100.,sqrt(dx*dx+dy*dy)/(sqrt(dirX*dirX+dirY*dirY)*100.));*/

    fitfname.open("Fitted_Vertex_For_Matt.txt",ios::out|ios::app);
    //fitfname << hitfname << setiosflags(ios::left) << " " << trueX << " " << trueY << " " << trueZ << " " << dirX << " " << dirY << " " << dirZ << " " << vrtX << " " << vrtY << " " << vrtZ << " " << ffom << " " << D << " " << d << " " << (dx/(dirX*100.)) << " " << (dy/(dirY*100.)) << " " << (dz/(dirZ*100.)) << " " << openangle << " " << nbot << " " << trkL << " " << openA << " " << distH;
    fitfname << hitfname << trueX << " " << trueY << " " << trueZ << " " << vrtX << " " << vrtY << " " << vrtZ;
    //fitfname << sign << " ";
    fitfname.close();
    /*dS->Fill(D/100.);
    Open->Fill(openangle);
    DistToTrk->Fill(d/100.);*/
//===============================================================================
  } // end loop over events  

  //Tres->Draw();

  /*TCanvas *GlbGeo = new TCanvas("GlbGeo","geometry of global peak",800,800);
  GlbGeo->Divide(2,2);
  GlbGeo->cd(1);
  dS->Draw();
  GlbGeo->cd(2);
  Open->Draw();
  GlbGeo->cd(3);
  DistToTrk->Draw();*/

  TCanvas *devi = new TCanvas("devi","deviation of peak",800,800);
  devi->Divide(2,2);
  devi->cd(1);
  //devXvsL->Draw();
  dX->Draw();
  devi->cd(2);
  //devYvsL->Draw();
  dY->Draw();
  devi->cd(3);
  //devZvsL->Draw();
  dZ->Draw();
  devi->cd(4);
  //devXYvsL->Draw();
  dS->Draw();
  devi->SaveAs("200events.png");

  /*ntuple->Write();
  ntuple2->Write();
  ntuple5->Write();
  timeinfo->Write();
  MyFile->Close();*/ 
}
