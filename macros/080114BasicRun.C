/*Este programa imprime event displays  
Aplica filtros simples

*/

{

  // Load libraries
  // ==============
  // gROOT->Reset();
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");
  
  // Path to WCSim ROOT file
  // =======================
  TString filename ("/lbne/data2/users/txin/Samples/eminus_400mev_50kton_10inch_13per_hqe_MuSct.root");  
// TString filename("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_MuSct_Ion.root");
  // TString filename("/lbne/data/users/ecatanom/samples/muplus_1200mev_500kton_10inch_5per_hqe.root");
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
  
  // Load Data
  // =========
  WCSimInterface::LoadData(filename);

  // get first entry
  Bool_t truehit = 1; // 1 is to use true hits
  Bool_t filtered = 1; // 1 is to use Andy's cut
  Bool_t Lmu = 0; // 1 is to use LMuon cut
  Double_t sigma0 = 0.1; //sigma0 = 0.1;
  if(truehit) {WCSimInterface::SetToUseTrueHits();
    WCSimInterface::Instance()->SmearTrueHits(sigma0);}

  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);
  WCSimDataCleaner::Instance()->SetNeighbourRadius(220.0); 
  WCSimDataCleaner::Instance()->SetNeighbourDigits(10.0);//a 50 b 70
  WCSimDataCleaner::Instance()->SetClusterRadius(300.0);
  WCSimDataCleaner::Instance()->SetClusterDigits(50.0);
  WCSimDataCleaner::Instance()->SetTimeWindowNeighbours(25.0);
  WCSimDataCleaner::Instance()->SetTimeWindowClusters(25.0);

  WCSimInterface::Instance()->SetToMCP();
  //WCSimInterface::Instance()->SetToGated();

  // =========================

  WCSimVertexFinder::UseTrueVertex(); // use true vertex
  //WCSimRingFinder::UseRecoVertex();  //comment for better ring 
  // WCSimVertexFinder::LMuonDoubleFilter(300);
   WCSimVertexFinder::PointFitOnly();

  WCSimDisplayAB* mydisplay=new WCSimDisplayAB();
  mydisplay->PrintGIF();
 

  //int thelist[]={1027,102,105,110,116,119,1033,1036,1054,1056};
  
  //int thelist[]={20,40,635,882,1200,140}; // 1200 eminus sample
for(int ecounter=0;ecounter<10;ecounter++){
  //myeventnumber=thelist[ecounter];
  myeventnumber=ecounter;
  WCSimInterface::LoadEvent(myeventnumber);
    
    WCSimRecoEvent* theRecoEvent;
    WCSimTrueEvent* theTrueEvent;
    theRecoEvent = WCSimInterface::RecoEvent();
    theTrueEvent = WCSimInterface::TrueEvent();
    WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
    haReco->RunFilter(theRecoEvent);
    //haReco->Run(theRecoEvent);
   
   
    
    mydisplay->DrawDisplay(theRecoEvent);
    //myfakedisplay->DrawTrueEvent(theTrueEvent);
    //myfakedisplay->DrawRecoEvent(theRecoEvent);
    mydisplay->PrintDisplay();
    cout <<"============================================="<<ecounter<<endl;
  }
  return;

  
 


  
}

