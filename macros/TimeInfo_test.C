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

  ifstream hitf;

  TFile *MyFile = new TFile("test.root","RECREATE");
  if(MyFile->IsOpen()) std::cout <<" File opened successfully" << std::endl; 
  // Create an output TTree
  TTree *timeinfo = new TTree("timeinfo","Muon Track Information");
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

  Int_t startev = 3;
  Int_t endev = 4;
  
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

  Double_t dirX = 0.;
  Double_t dirY = 0.;
  Double_t dirZ = 0.;
  WCSimRecoCluster* digitlist = new WCSimRecoCluster;
  WCSimRecoEvent* myevent = new WCSimRecoEvent;
  myevent->SetHeader(0,0,0);

  char hitfname[250];
  ifstream eventf; 
  eventf.open("/lbne/app/users/wetstein/SamplesForTian/samples_fortian.txt",ios::in);

  for (Int_t i = 0; i < startev; i++) {

    //if (eventf) {std::cout << "open succe" << std::endl;}
    //if (!eventf) {std::cout<< "open wrong" << std::endl;}
    eventf.getline(hitfname,250);
  }
  //std::cout << hitfname << std::endl;
    
  for (Int_t ev = startev; ev < endev; ev++) {
    //digitlist->Reset();
    myevent->Reset();
    eventf.getline(hitfname,250,' ');
    eventf >> recoX >> recoY >> recoZ >> recoT >> recothe >> recophi >> recoE >> recoID >> trueX >> trueY >> trueZ >> trueT >> truethe >> truephi >> trueE >> trueID;	 
    dirX = sin(recothe)*cos(recophi);
    dirY = sin(recothe)*sin(recophi);
    dirZ = cos(recothe); 
    //std::cout << hitfname << std::endl;
    std::cout << recoX << " " << recoY << " " << trueID << std::endl;

    hitf.open(hitfname, ios::in);  
    while(! hitf.eof()){
    hitf >> hitX >> hitY >> hitZ >> hitT;
    WCSimRecoDigit* digit = new WCSimRecoDigit(1, hitX, hitY, hitZ, hitT, 1.0, hitT, 1.0);
    std::cout << hitX << std::endl; 
    digitlist->AddDigit(digit);
    myevent->AddDigit(digit);
    myevent->AddFilterDigit(digit);
    //digitlist->AddFilterDigit(digit);
  }

    nhit = digitlist->GetNDigits();
    //std::cout << nhit << std::endl;
    
    std::cout << hitX << hitT << std::endl;
    //WCSimRecoVertex *myvtx = new WCSimRecoVertex(recoX, recoY, recoZ, recoT, dirX, dirY, dirZ, recothe, 1.0, 1, 1, 1);

// test code to see if the call of function is right
/*    std::vector<WCSimRecoDigit*>* test = new std::vector<WCSimRecoDigit*>;
    WCSimRecoDigit* testunit = new WCSimRecoDigit(1, 1., 1., 1., 1., 1., 1., 1.);
    test->push_back(testunit);*/

  //nhit = digitlish.size();
  std::cout << "I am good so far" << std::endl;
  //WCSimVertexFinder* findit = WCSimVertexFinder::Instance();
  WCSimRootGeom* myGeom = new WCSimRootGeom();
  WCSimGeometry::BuildGeometry(myGeom); 
  
  WCSimRecoVertex* myVertex = WCSimVertexFinder::Instance()->RunPointFit(myevent);
  std::cout << "Am i still good" << std::endl;
  vrtX = myVertex->GetX();
  //vrtY = (findit->FitPointVertex(digitlist, myvtx))->GetY();
  //vrtZ = (findit->FitPointVertex(digitlist, myvtx))->GetZ();
  //vrtT = (findit->FitPointVertex(digitlist, myvtx))->GetTime();
  
  std::cout << vrtX << " " << vrtY << " " << vrtZ << " " << std::endl;
  
  } // end loop over events          
  /*ntuple->Write();
  ntuple2->Write();
  ntuple5->Write();
  timeinfo->Write();
  MyFile->Close();*/ 
}
