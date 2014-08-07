// Comparison LMuon filter 300,350, 400, 500

{
  string namefile = "bigntuple";
  //string namefile = "070713bigntuple";
  //string namefile = "0724bigntuple";
  
  // True Quantities
  Int_t runNum;
  Int_t eventNum;
  Int_t triggerNum;

  Int_t truePDG;
  Double_t trueP;
  Double_t trueE;
  Double_t trueVtxX;
  Double_t trueVtxY;
  Double_t trueVtxZ;
  Double_t trueEndX;
  Double_t trueEndY;
  Double_t trueEndZ;
  Double_t trueDirX;
  Double_t trueDirY;
  Double_t trueDirZ;

  Int_t nDigits;
  Int_t nFilterDigits;
  Int_t foundVertex;
  Int_t foundDirection;

  Double_t recoVtxX;
  Double_t recoVtxY;
  Double_t recoVtxZ;
  Double_t recoVtxTime;
  Double_t recoVtxFOM;
  Double_t recoDirX;
  Double_t recoDirY;
  Double_t recoDirZ;


  // Testing Reconstruction
  //Double_t simpleVtxX;
  //Double_t simpleVtxY;
  //Double_t simpleVtxZ;
  Double_t pointVtxX;
  Double_t pointVtxY;
  Double_t pointVtxZ;
  Double_t pointVtxFOM;
  Int_t pointVtxSteps;
  Int_t pointVtxPass;
  //Double_t simpleDirX;
  //Double_t simpleDirY;
  //Double_t simpleDirZ;
  Double_t pointDirX;
  Double_t pointDirY;
  Double_t pointDirZ;
  //Double_t pointDirAngle;
  //Double_t pointDirFOM;
  //Int_t pointDirSteps;
  //Int_t pointDirPass;
  Double_t extendedVtxX;
  Double_t extendedVtxY;
  Double_t extendedVtxZ;
  Double_t extendedVtxFOM;
  Double_t extendedDirX;
  Double_t extendedDirY;
  Double_t extendedDirZ;
  //Double_t extendedDirAngle;
  Int_t extendedVtxSteps;
  Int_t extendedVtxPass;
  

  //Double_t simpleDirX_from_trueVtx;
  //Double_t simpleDirY_from_trueVtx;
  //Double_t simpleDirZ_from_trueVtx;
  //Double_t pointDirX_from_trueVtx;
  //Double_t pointDirY_from_trueVtx;
  //Double_t pointDirZ_from_trueVtx;
  //Double_t pointDirFOM_from_trueVtx;
  //Double_t extendedVtxX_from_trueVtx;
  //Double_t extendedVtxY_from_trueVtx;
  //Double_t extendedVtxZ_from_trueVtx;
  //Double_t extendedVtxFOM_from_trueVtx;

  TChain* RecoChain = new TChain("ntuple","chain");

  // cosmic muons
  //RecoChain->Add(("/lbne/data/users/gsdavies/reco/single/muminus/"+namefile+"*.root").c_str());
  //RecoChain->Add(("/lbne/data/users/gsdavies/reco/single/muplus/"+namefile+"*.root").c_str());
  //RecoChain->Add("/lbne/data/users/gsdavies/reco/single/muminus/reco_muon_minus_000400MeV_200kton*.root");
  //RecoChain->Add(("/lbne/data/users/omanghel/"+namefile+".root").c_str());
  RecoChain->Add(("/lbne/data/users/ecatanom/test/"+namefile+".root").c_str());
  //RecoChain->Add(("/lbne/app/users/txin/WCSimAnalysis_bkp20121019/plotroot/"+namefile+".root").c_str());

  RecoChain->SetBranchAddress("run",&runNum);
  RecoChain->SetBranchAddress("event",&eventNum);
  RecoChain->SetBranchAddress("trigger",&triggerNum);
  RecoChain->SetBranchAddress("truePDG",&truePDG);
  RecoChain->SetBranchAddress("trueP",&trueP);
  RecoChain->SetBranchAddress("trueE",&trueE);
  RecoChain->SetBranchAddress("trueVtxX",&trueVtxX);
  RecoChain->SetBranchAddress("trueVtxY",&trueVtxY);
  RecoChain->SetBranchAddress("trueVtxZ",&trueVtxZ);
  RecoChain->SetBranchAddress("trueEndX",&trueEndX);
  RecoChain->SetBranchAddress("trueEndY",&trueEndY);
  RecoChain->SetBranchAddress("trueEndZ",&trueEndZ);
  RecoChain->SetBranchAddress("trueDirX",&trueDirX);
  RecoChain->SetBranchAddress("trueDirY",&trueDirY);
  RecoChain->SetBranchAddress("trueDirZ",&trueDirZ);
  RecoChain->SetBranchAddress("nDigits",&nDigits);
  RecoChain->SetBranchAddress("nFilterDigits",&nFilterDigits);
  RecoChain->SetBranchAddress("foundVertex",&foundVertex);
  RecoChain->SetBranchAddress("foundDirection",&foundDirection);
  RecoChain->SetBranchAddress("recoVtxX",&recoVtxX);
  RecoChain->SetBranchAddress("recoVtxY",&recoVtxY);
  RecoChain->SetBranchAddress("recoVtxZ",&recoVtxZ);
  RecoChain->SetBranchAddress("recoVtxTime",&recoVtxTime);
  RecoChain->SetBranchAddress("recoVtxFOM",&recoVtxFOM);
  RecoChain->SetBranchAddress("recoDirX",&recoDirX);
  RecoChain->SetBranchAddress("recoDirY",&recoDirY);
  RecoChain->SetBranchAddress("recoDirZ",&recoDirZ);

  //RecoChain->SetBranchAddress("simpleVtxX",&simpleVtxX);
  //RecoChain->SetBranchAddress("simpleVtxY",&simpleVtxY);
  //RecoChain->SetBranchAddress("simpleVtxZ",&simpleVtxZ);
  RecoChain->SetBranchAddress("pointVtxX",&pointVtxX);
  RecoChain->SetBranchAddress("pointVtxY",&pointVtxY);
  RecoChain->SetBranchAddress("pointVtxZ",&pointVtxZ);
  RecoChain->SetBranchAddress("pointVtxFOM",&pointVtxFOM);
  RecoChain->SetBranchAddress("pointVtxSteps",&pointVtxSteps);
  RecoChain->SetBranchAddress("pointVtxPass",&pointVtxPass);
  //RecoChain->SetBranchAddress("simpleDirX",&simpleDirX);
  //RecoChain->SetBranchAddress("simpleDirY",&simpleDirY);
  //RecoChain->SetBranchAddress("simpleDirZ",&simpleDirZ);
  RecoChain->SetBranchAddress("pointDirX",&pointDirX);
  RecoChain->SetBranchAddress("pointDirY",&pointDirY);
  RecoChain->SetBranchAddress("pointDirZ",&pointDirZ);
  //RecoChain->SetBranchAddress("pointDirAngle",&pointDirAngle);
  //RecoChain->SetBranchAddress("pointDirFOM",&pointDirFOM);
  //RecoChain->SetBranchAddress("pointDirSteps",&pointDirSteps);
  //RecoChain->SetBranchAddress("pointDirPass",&pointDirPass);
  RecoChain->SetBranchAddress("extendedVtxX",&extendedVtxX);
  RecoChain->SetBranchAddress("extendedVtxY",&extendedVtxY);
  RecoChain->SetBranchAddress("extendedVtxZ",&extendedVtxZ);
  RecoChain->SetBranchAddress("extendedVtxFOM",&extendedVtxFOM);
  RecoChain->SetBranchAddress("extendedDirX",&extendedDirX);
  RecoChain->SetBranchAddress("extendedDirY",&extendedDirY);
  RecoChain->SetBranchAddress("extendedDirZ",&extendedDirZ);
  //RecoChain->SetBranchAddress("extendedDirAngle",&extendedDirAngle);
  RecoChain->SetBranchAddress("extendedVtxSteps",&extendedVtxSteps);
  RecoChain->SetBranchAddress("extendedVtxPass",&extendedVtxPass);


  Int_t nEvent = RecoChain->GetEntries();
  Double_t *ArrExtendedDelta = new Double_t[nEvent];
  Double_t *ArrExtendedAngle = new Double_t[nEvent];
  Double_t *ArrExtendedPara = new Double_t[nEvent];
  Double_t *ArrExtendedPerp = new Double_t[nEvent];
  Int_t *ArrIndex1 = new Int_t[nEvent];
  Int_t *ArrIndex2 = new Int_t[nEvent];
  Int_t *ArrIndex3 = new Int_t[nEvent];
  Int_t *ArrIndex4 = new Int_t[nEvent];
  for( Int_t l=0;l<nEvent;l++ ){
     ArrExtendedDelta[l]=0.0;
     ArrExtendedAngle[l]=0.0;
     ArrExtendedPara[l]=0.0;
     ArrExtendedPerp[l]=0.0;
     ArrIndex1[l]=l;
     ArrIndex2[l]=l;
     ArrIndex3[l]=l;
     ArrIndex4[l]=l;
  }
  const Int_t nbin = 5000;
  Double_t min = 0.0;
  Double_t max = 100.0;
  Double_t range = max - min;
  TH1D* testnonh = new TH1D("testnonh","",nbin,min,max);
  TH1D* testconh = new TH1D("testconh","",nbin,min,max);
  TH2D* test2conh = new TH2D("test2conh","",200,0.0,600.0,20,0.0,2.0);
  TH2D* test2nonh = new TH2D("test2nonh","",200,0.0,600.0,20,0.0,2.0);

  Int_t ElectronID = +11;
  Int_t MuonID = +13;

  Double_t phi = 0.0;
  Double_t sinth;

  Double_t fLimit = 0.999999;

  Double_t ctr_extended_fit = 0.0;
  Double_t ctr_extended_fit_pass = 0.0;
  Double_t ctr_extended_fit_pass_frac = 0.0;
 
  Double_t drmax = -999.9;
  Double_t radius = 3168.94; //3168.94 for 1200MeV, 3112.95 for 400MeV
  Double_t height = 3833.94; //3833.94 for 1200MeV, 3999.04 for 400MeV
  Int_t aaa = 0;
  Int_t bbb = 0;
  Int_t ccc = 0;


  //Erika
  TH2D* ParaPerpC = new TH2D("PPC","",200,0.0,600.0,200,0.0,250.0);
  TH2D* ParaPerpNC = new TH2D("PPNC","",200,0.0,600.0,200,0.0,250.0);
  TH1D* TotalDistC = new TH1D("DC","",200,0,800);
  TH1D* TotalDistNC = new TH1D("DNC","",200,0,800);
  TH1D* NFilterDigitsC = new TH1D("NFDC","",100,0,12000);
  TH1D* NFilterDigitsNC = new TH1D("NFDNC","",100,0,12000);



//   //Actual values of nfilterdigits
// TH1D* h0C = new TH1D("0C","",20,0,8000);
// TH1D* h0NC = new TH1D("0NC","",20,0,8000);

// TH1D* h500C = new TH1D("500C","",20,0,8000);
// TH1D* h500NC = new TH1D("500NC","",20,0,8000);

// TH1D* h450C = new TH1D("450C","",20,0,8000);
// TH1D* h450NC = new TH1D("450NC","",20,0,8000);

// TH1D* h400C = new TH1D("400C","",20,0,8000);
// TH1D* h400NC = new TH1D("400NC","",20,0,8000);

// TH1D* h350C = new TH1D("350C","",20,0,8000);
// TH1D* h350NC = new TH1D("350NC","",20,0,8000);

// TH1D* h300C = new TH1D("300C","",20,0,8000);
// TH1D* h300NC = new TH1D("300NC","",20,0,8000);


//percentages

TH1D* h0C = new TH1D("0C","",20,0,1);
TH1D* h0NC = new TH1D("0NC","",20,0,1);

TH1D* h500C = new TH1D("500C","",20,0,1);
TH1D* h500NC = new TH1D("500NC","",20,0,1);

TH1D* h450C = new TH1D("450C","",20,0,1);
TH1D* h450NC = new TH1D("450NC","",20,0,1);

TH1D* h400C = new TH1D("400C","",20,0,1);
TH1D* h400NC = new TH1D("400NC","",20,0,1);

TH1D* h350C = new TH1D("350C","",20,0,1);
TH1D* h350NC = new TH1D("350NC","",20,0,1);

TH1D* h300C = new TH1D("300C","",20,0,1);
TH1D* h300NC = new TH1D("300NC","",20,0,1);

  int ConvergedList[]={102, 103, 107, 10, 111, 114, 119, 120, 122, 127, 128, 130, 131, 133, 135, 136, 139, 141, 148, 14, 151, 156, 160, 161, 169, 170, 171, 172, 175, 176, 183, 184, 186, 188, 18, 191, 196, 200, 204, 205, 206, 20, 210, 213, 214, 215, 219, 21, 227, 229, 231, 233, 236, 238, 245, 247, 248, 249, 24, 253, 254, 255, 256, 258, 25, 260, 266, 274, 275, 277, 278, 279, 27, 282, 285, 287, 28, 295, 297, 299, 29, 302, 310, 320, 321, 329, 342, 347, 34, 357, 358, 359, 364, 365, 366, 368, 369, 370, 372, 373, 374, 377, 383, 389, 38, 393, 397, 411, 416, 41, 420, 421, 426, 42, 431, 437, 43, 441, 44, 452, 453, 454, 455, 456, 457, 464, 465, 473, 474, 481, 482, 483, 489, 490, 493, 497, 49, 501, 503, 508, 510, 516, 51, 528, 532, 534, 535, 536, 537, 538, 540, 547, 553, 555, 556, 558, 560, 570, 571, 575, 576, 579, 580, 581, 590, 591, 592, 598, 599, 59, 603, 605, 607, 610, 612, 614, 617, 619, 620, 621, 624, 627, 62, 631, 635, 638, 647, 648, 653, 658, 659, 668, 669, 670, 675, 676, 678, 680, 681, 685, 686, 687, 692, 699, 69, 6, 704, 705, 706, 708, 710, 715, 717, 720, 724, 726, 72, 736, 73, 740, 752, 759, 761, 762, 766, 767, 768, 769, 776, 777, 779, 781, 782, 784, 786, 793, 794, 797, 799, 79, 7, 800, 804, 809, 80, 813, 815, 816, 820, 821, 823, 824, 829, 82, 830, 836, 840, 848, 850, 853, 854, 856, 858, 860, 862, 863, 866, 86, 876, 878, 879, 880, 886, 890, 893, 894, 900, 902, 904, 906, 907, 909, 90, 912, 919, 925, 926, 933, 939, 941, 947, 948, 951, 957, 962, 963, 964, 965, 968, 970, 973, 979, 980, 985, 987, 988, 98, 991, 992, 993, 995};
int NotConvergedList[]={
100, 101, 104, 106, 109, 110, 112, 115, 118, 121, 132, 138, 13, 140, 145, 146, 147, 149, 150, 152, 154, 155, 157, 15, 164, 165, 16, 173, 174, 177, 178, 17, 182, 185, 187, 192, 195, 197, 199, 19, 201, 202, 208, 209, 212, 217, 222, 224, 225, 226, 228, 230, 234, 235, 237, 239, 23, 241, 242, 243, 246, 250, 259, 263, 264, 265, 267, 268, 269, 26, 273, 276, 281, 283, 284, 290, 294, 296, 300, 303, 304, 305, 30, 311, 312, 316, 317, 319, 322, 323, 324, 325, 326, 327, 330, 331, 336, 337, 338, 339, 343, 345, 346, 350, 353, 354, 356, 35, 360, 361, 362, 363, 371, 376, 37, 381, 382, 385, 387, 388, 391, 392, 396, 402, 403, 404, 405, 406, 40, 410, 412, 418, 422, 428, 430, 435, 439, 442, 444, 446, 447, 448, 450, 458, 459, 45, 460, 461, 463, 467, 468, 469, 471, 476, 478, 479, 47, 484, 485, 486, 487, 488, 48, 492, 495, 496, 498, 500, 502, 509, 512, 513, 514, 515, 517, 518, 521, 522, 524, 525, 526, 527, 530, 531, 533, 541, 542, 544, 545, 549, 54, 551, 552, 557, 563, 566, 568, 569, 572, 573, 574, 577, 578, 57, 582, 585, 586, 588,
589, 594, 595, 596, 597, 5, 600, 601, 608, 609, 60, 611, 613, 615, 616, 618, 623, 625, 628, 630, 633, 634, 636, 637, 641, 643, 644, 645, 646, 649, 650, 651, 654, 655, 656, 657, 660, 661, 663, 666, 673, 674, 682, 688, 689, 690, 694, 696, 697, 698, 700, 703, 712, 721, 722, 725, 727, 728, 730, 731, 732, 733, 734, 738, 739, 742, 746, 747, 750, 753, 755, 756, 757, 75, 760, 763, 764, 76, 770, 771, 775, 778, 77, 780, 783, 785, 787, 788, 78, 790, 791, 792, 802, 803, 807, 810, 811, 812, 817, 81, 822, 825, 826, 831, 838, 844, 845, 847, 857, 859, 85, 861, 865, 867, 869, 872, 875, 87, 882, 883, 884, 885, 887, 888, 889, 88, 892, 898, 89, 8, 903, 905, 908, 911, 915, 916, 91, 920, 921, 922, 927, 931, 936, 944, 945, 946, 94, 950, 953, 955, 958, 95, 96, 971, 972, 974, 975, 97, 981, 982, 983, 986, 994, 996, 997, 998};

//  RecoChain->GetEntry(109);
//  cout<<trueVtxX <<endl;
  

 //------------------------------------------
 gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");
 TString filename("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_MuSct_Ion.root");

 WCSimInterface::LoadData(filename);
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
      // get first entry
      Bool_t truehit = 1; // 1 is to use true hits
      Bool_t filtered = 1; // 1 is to use Andy's cut
      Bool_t Lmu = 0; // 1 is to use LMuon cut
      Double_t sigma0 = 0.1; //sigma0 = 0.1;
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
  
  int myeventnumber;
  int NCmax=sizeof(NotConvergedList)/sizeof(int);
  for(int ecounter=0;ecounter<NCmax;ecounter++){
    //for(int ecounter=0;ecounter<1;ecounter++){
  myeventnumber=NotConvergedList[ecounter];
  //myeventnumber=111;


  WCSimInterface::LoadEvent(myeventnumber);
  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
  WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
  haReco->RunFilter(recoEvent);
  
  myNdigits = recoEvent->GetNDigits();
  //myNFilterdigits = recoEvent->GetNFilterDigits();
      int tempi=0;
      do{RecoChain->GetEntry(tempi); tempi++;}while(eventNum!=myeventnumber)

      cout <<pointVtxX <<endl;
      cout <<eventNum <<endl;

 
      trueT = 0.0;
   

      WCSimWaterModel *wm2 = WCSimWaterModel::Instance();
      WCSimTResidPDF *pdf = WCSimTResidPDF::Instance();
   
      //------------------------------------------------------------------ 
     //FILL HISTOGRAM
      int ifilter = 0;
      int ifilter300 = 0;
      int ifilter350 = 0;
      int ifilter400 = 0;
      int ifilter450 = 0;
      int ifilter500 = 0;

      for(int i=0; i<myNdigits; i++){

	WCSimRecoDigit* adigit = recoEvent->GetDigit(i);
	if( adigit->IsFiltered() || !filtered ){ //if the hit passed the filter
	  double hitX = adigit->GetX();
	  double hitY = adigit->GetY();
	  double hitZ = adigit->GetZ();
	  double hitT = adigit->GetTime();
	  double qpes = adigit->GetQPEs();
	  double res = WCSimParameters::TimeResolution(qpes); 

  WCSimVertexGeometry::CalcTResid(pointVtxX,pointVtxY,pointVtxZ, trueT, pointDirX, pointDirY, pointDirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle); 

  //	  WCSimVertexGeometry::CalcTResid(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle); 
     
	  //h1->Fill(TResid);
	  //cout << i<< " "<< LMuon << endl;
	  if(LMuon<=300) { ifilter300++; } //h2->Fill(TResid);
	  if(LMuon<=350) { ifilter350++;}
	  if(LMuon<=400) { ifilter400++;}
	  if(LMuon<=450) { ifilter450++;}
	  if(LMuon<=500) { ifilter500++;}

	  ifilter++;
	} //loop of the filter
      } //loop over hits


      cout<< "NoFilter" << ifilter << endl;
      cout<< "500 " << ifilter500 << endl;
      cout<< "450" << ifilter450 << endl;
      cout<< "400 " << ifilter400 << endl;
      cout<< "350" << ifilter350 << endl; 
      cout<< "300 " << ifilter300 << endl;
    //   h0NC->Fill(ifilter);
//       h500NC->Fill(ifilter500);
//       h450NC->Fill(ifilter450);
//       h400NC->Fill(ifilter400);
//       h350NC->Fill(ifilter350);
//       h300NC->Fill(ifilter300);

      h0NC->Fill((double)ifilter/ifilter);
      h500NC->Fill((double)ifilter500/ifilter);
      h450NC->Fill((double)ifilter450/ifilter);
      h400NC->Fill((double)ifilter400/ifilter);
      h350NC->Fill((double)ifilter350/ifilter);
      h300NC->Fill((double)ifilter300/ifilter);
}

  ////////////////////////////////////////////////// 
  int Cmax=sizeof(ConvergedList)/sizeof(int);
  for(int ecounter=0;ecounter<Cmax;ecounter++){
    //for(int ecounter=0;ecounter<1;ecounter++){
     
  myeventnumber=ConvergedList[ecounter];
  //myeventnumber=111;


  WCSimInterface::LoadEvent(myeventnumber);
  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
  WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
  haReco->RunFilter(recoEvent);
  
   myNdigits = recoEvent->GetNDigits();
  //myNFilterdigits = recoEvent->GetNFilterDigits();
      int tempi=0;
      do{RecoChain->GetEntry(tempi); tempi++;}while(eventNum!=myeventnumber)

      cout <<pointVtxX <<endl;
      cout <<eventNum <<endl;

 
      trueT = 0.0;
   

      WCSimWaterModel *wm2 = WCSimWaterModel::Instance();
      WCSimTResidPDF *pdf = WCSimTResidPDF::Instance();
   
      //------------------------------------------------------------------ 
     //FILL HISTOGRAM
      int ifilter = 0;
      int ifilter300 = 0;
      int ifilter350 = 0;
      int ifilter400 = 0;
      int ifilter450 = 0;
      int ifilter500 = 0;

      for(int i=0; i<myNdigits; i++){

	WCSimRecoDigit* adigit = recoEvent->GetDigit(i);
	if( adigit->IsFiltered() || !filtered ){ //if the hit passed the filter
	  double hitX = adigit->GetX();
	  double hitY = adigit->GetY();
	  double hitZ = adigit->GetZ();
	  double hitT = adigit->GetTime();
	  double qpes = adigit->GetQPEs();
	  double res = WCSimParameters::TimeResolution(qpes); 

  WCSimVertexGeometry::CalcTResid(pointVtxX,pointVtxY,pointVtxZ, trueT, pointDirX, pointDirY, pointDirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle); 

  //	  WCSimVertexGeometry::CalcTResid(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle); 
     
	  //h1->Fill(TResid);
	  //cout << i<< " "<< LMuon << endl;
	  if(LMuon<=300) { ifilter300++; } //h2->Fill(TResid);
	  if(LMuon<=350) { ifilter350++;}
	  if(LMuon<=400) { ifilter400++;}
	  if(LMuon<=450) { ifilter450++;}
	  if(LMuon<=500) { ifilter500++;}

	  ifilter++;
	} //loop of the filter
      } //loop over hits


      cout<< "NoFilter" << ifilter << endl;
      cout<< "500 " << ifilter500 << endl;
      cout<< "450" << ifilter450 << endl;
      cout<< "400 " << ifilter400 << endl;
      cout<< "350" << ifilter350 << endl; 
      cout<< "300 " << ifilter300 << endl;

//       h0C->Fill(ifilter);
//       h500C->Fill(ifilter500);
//       h450C->Fill(ifilter450);
//       h400C->Fill(ifilter400);
//       h350C->Fill(ifilter350);
//       h300C->Fill(ifilter300);


      h0C->Fill((double)ifilter/ifilter);
      h500C->Fill((double)ifilter500/ifilter);
      h450C->Fill((double)ifilter450/ifilter);
      h400C->Fill((double)ifilter400/ifilter);
      h350C->Fill((double)ifilter350/ifilter);
      h300C->Fill((double)ifilter300/ifilter);

}   TCanvas *ca1 = new TCanvas("ca1","",800,600);
    // ca1.Divide(2,1);
    // ca1.cd(1); 
    (h0C->GetXaxis())->SetTitle("NFilterDigits");
    (h0C->GetYaxis())->SetTitle("NoEvents");


    h0C->SetLineColor(kBlack);
    h500C->SetLineColor(kBlue+3);
    h450C->SetLineColor(kBlue);
    h400C->SetLineColor(kAzure+5);
    h350C->SetLineColor(kCyan-6);
    h300C->SetLineColor(kSpring-1);
    h0NC->SetLineColor(kMagenta);
    h500NC->SetLineColor(kMagenta-9);
    h450NC->SetLineColor(kRed-9);
    h400NC->SetLineColor(kOrange-2);
    h350NC->SetLineColor(kOrange+7);
    h300NC->SetLineColor(kRed);

    h0C->Draw();
    h500C->Draw("same");
    h450C->Draw("same");
    h400C->Draw("same");
    h350C->Draw("same");
    h300C->Draw("same");
    
    h0NC->Draw("same");
    h500NC->Draw("same");
    h450NC->Draw("same");
    h400NC->Draw("same");
    h350NC->Draw("same");
    h300NC->Draw("same");
 
    //ca1.cd(2); 
    TCanvas *ca2 = new TCanvas("ca2","",400,600);
    leg=new TLegend(0.2,0.2,0.8,0.8,"");
  leg->AddEntry(   h0C,"0 Convergent","l");
  leg->AddEntry( h500C,"500 Convergent","l");
  leg->AddEntry( h450C,"450 Convergent","l");
  leg->AddEntry( h400C,"400 Convergent","l");
  leg->AddEntry( h350C,"350 Convergent","l");
  leg->AddEntry( h300C,"300 Convergent","l");


 leg->AddEntry(  h0NC,"0 Not Convergent","l");
 leg->AddEntry(h500NC,"500 Not Convergent","l");
 leg->AddEntry(h450NC,"450 Not Convergent","l");
 leg->AddEntry(h400NC,"400 Not Convergent","l");
leg->AddEntry(h350NC,"350 Not Convergent","l");
  leg->AddEntry(h300NC,"300 Not Convergent","l");

  leg->Draw();


   return;

















  for( Int_t i=0; i<RecoChain->GetEntries(); i++ ){
  //for( Int_t i=0; i<100; i++ ){
    RecoChain->GetEntry(i);

    // fill histograms
    // ===============
    if( 1 ){//fabs(truePDG)==MuonID ){

      // vertex angles
      // =============
      phi = 0.0;
      if( trueVtxX!=0.0 ){
        phi = atan(trueVtxY/trueVtxX);
      }
      if( trueVtxX<=0.0 ){
        if( trueVtxY>0.0 ) phi += TMath::Pi();
        if( trueVtxY<0.0 ) phi -= TMath::Pi();
      }
      phi *= 180.0/TMath::Pi();

      phi = 0.0;
      if( trueDirX!=0.0 ){
        phi = atan(trueDirY/trueDirX);
      }
      if( trueDirX<=0.0 ){
        if( trueDirY>0.0 ) phi += TMath::Pi();
        if( trueDirY<0.0 ) phi -= TMath::Pi();
      }
      phi *= 180.0/TMath::Pi();


      // compare reco with truth
      // =======================

      // truth
      Double_t dx0 = trueEndX - trueVtxX;
      Double_t dy0 = trueEndY - trueVtxY;
      Double_t dz0 = trueEndZ - trueVtxZ;
      Double_t ds0 = sqrt( dx0*dx0 + dy0*dy0 + dz0*dz0 );
      Double_t px0 = dx0/ds0;
      Double_t py0 = dy0/ds0;
      Double_t pz0 = dz0/ds0;
      
      Double_t midx = (trueEndX + trueVtxX)*0.5;
      Double_t midy = (trueEndY + trueVtxY)*0.5;
      Double_t midz = (trueEndZ + trueVtxZ)*0.5;

      Double_t costh0 = px0*trueDirX+py0*trueDirY+pz0*trueDirZ; if( costh0>fLimit ) costh0 = fLimit;
      Double_t sinth0 = sqrt(1.0-costh0*costh0);
      Double_t theta0 = (180.0/TMath::Pi())*acos(costh0);

      // simple vertex
      //Double_t dx1 = simpleVtxX - trueVtxX;
      //Double_t dy1 = simpleVtxY - trueVtxY;
      //Double_t dz1 = simpleVtxZ - trueVtxZ;
      //Double_t ds1 = sqrt( dx1*dx1 + dy1*dy1 + dz1*dz1 );
      //Double_t px1 = dx1/ds1;
      //Double_t py1 = dy1/ds1;
      //Double_t pz1 = dz1/ds1;

      //Double_t costh1 = px1*trueDirX+py1*trueDirY+pz1*trueDirZ; if( costh1>fLimit ) costh1 = fLimit;
      //Double_t sinth1 = sqrt(1.0-costh1*costh1);
      //Double_t theta1 = (180.0/TMath::Pi())*acos(costh1);

      // point vertex
      Double_t dx2 = pointVtxX - trueVtxX;
      Double_t dy2 = pointVtxY - trueVtxY;
      Double_t dz2 = pointVtxZ - trueVtxZ;
      Double_t ds2 = sqrt( dx2*dx2 + dy2*dy2 + dz2*dz2 );
      Double_t px2 = dx2/ds2;
      Double_t py2 = dy2/ds2;
      Double_t pz2 = dz2/ds2;

      Double_t costh2 = px2*trueDirX+py2*trueDirY+pz2*trueDirZ; if( costh2>fLimit ) costh2 = fLimit;
      Double_t sinth2 = sqrt(1.0-costh2*costh2);
      Double_t theta2 = (180.0/TMath::Pi())*acos(costh2);

      // simple direction (using truth)
      //Double_t px3 = simpleDirX_from_trueVtx;
      //Double_t py3 = simpleDirY_from_trueVtx;
      //Double_t pz3 = simpleDirZ_from_trueVtx;

      //Double_t costh3 = px3*trueDirX+py3*trueDirY+pz3*trueDirZ; if( costh3>fLimit ) costh3 = fLimit;
      //Double_t theta3 = (180.0/TMath::Pi())*acos(costh3);

      // point direction (using truth)
      //Double_t px4 = pointDirX_from_trueVtx;
      //Double_t py4 = pointDirY_from_trueVtx;
      //Double_t pz4 = pointDirZ_from_trueVtx;

      //Double_t costh4 = px4*trueDirX+py4*trueDirY+pz4*trueDirZ; if( costh4>fLimit ) costh4 = fLimit;
      //Double_t theta4 = (180.0/TMath::Pi())*acos(costh4);

/*      if( eventNum==227 ){
        extendedVtxX = 979.762;
        extendedVtxY = -749.921;
        extendedVtxZ = -503.521;
        recoDirX = 0.943583;
        recoDirY = 0.158726;
        recoDirZ = 0.290615;
      }
*/
      // extended vertex
      Double_t dx5 = extendedVtxX - trueVtxX;
      Double_t dy5 = extendedVtxY - trueVtxY;
      Double_t dz5 = extendedVtxZ - trueVtxZ;
      Double_t ds5 = sqrt( dx5*dx5 + dy5*dy5 + dz5*dz5 );
      Double_t px5 = dx5/ds5;
      Double_t py5 = dy5/ds5;
      Double_t pz5 = dz5/ds5;

      Double_t costh5 = px5*trueDirX+py5*trueDirY+pz5*trueDirZ; if( costh5>fLimit ) costh5 = fLimit;
      Double_t sinth5 = sqrt(1.0-costh5*costh5);
      Double_t theta5 = (180.0/TMath::Pi())*acos(costh5);
     
      // extended direction
      Double_t costh6 = recoDirX*trueDirX + recoDirY*trueDirY + recoDirZ*trueDirZ; 
      if( costh6>fLimit ) costh6 = fLimit;
      Double_t sinth6 = sqrt(1.0-costh6*costh6);
      Double_t theta6 = (180.0/TMath::Pi())*acos(costh6);

/*      if( eventNum == 227 ){
         cout << extendedVtxX << " " << extendedVtxY << " " << extendedVtxZ << endl;
         cout << recoDirX << " " << recoDirY << " " << recoDirZ << endl;
         cout << (ds5*sinth5) << " " << (ds5*costh5) << " " << theta6 << endl;
      }
*/
      Double_t dr0 = sqrt( trueVtxX*trueVtxX + trueVtxY*trueVtxY );
      Double_t dr2 = sqrt( pointVtxX*pointVtxX + pointVtxY*pointVtxY );
      Double_t dr1 = sqrt( trueEndX*trueEndX + trueEndY*trueEndY );
      Double_t dr5 = sqrt( extendedVtxX*extendedVtxX + extendedVtxY*extendedVtxY );
      Double_t DisttoWall = 0.0;
      Double_t DisttoWall2 = 0.0;
      Double_t DisttoWall5 = 0.0;
      Double_t Da = radius - dr0;
      Double_t Db = height - sqrt(trueVtxZ*trueVtxZ);
      Double_t Da2 = radius - dr2;
      Double_t Db2 = height - sqrt(pointVtxZ*pointVtxZ);
      Double_t Da5 = radius - dr5;
      Double_t Db5 = height - sqrt(extendedVtxZ*extendedVtxZ);
      if( Da>Db ) DisttoWall = Db;
      else DisttoWall = Da;
      if( Da2>Db2 ) DisttoWall2 = Db2;
      else DisttoWall2 = Da2;
      if( Da5>Db5 ) DisttoWall5 = Db5;
      else DisttoWall5 = Da5;

      //if( eventNum == 102 ) cout << "102: " << DisttoWall << " " << DisttoWall2 << " " << DisttoWall5 << endl;
      //if( eventNum == 126 ) cout << "126: " << DisttoWall << " " << DisttoWall2 << " " << DisttoWall5 << endl;
      //if( eventNum == 191 ) cout << "191: " << DisttoWall << " " << DisttoWall2 << " " << DisttoWall5 << endl;
      //if( eventNum == 179 ) cout << "179: " << DisttoWall << " " << DisttoWall2 << " " << DisttoWall5 << endl;

      //if( ds0!=0.0 ){
        //if( !foundVertex ) cout << eventNum << " ";//testconh->Fill(nFilterDigits);
        //else testnonh->Fill(ds0);
      //}
      //if( ds5*sqrt(costh5*costh5)>50.0 && extendedVtxPass ) cout << eventNum << " " ;//<< nDigits << " " << nFilterDigits << " " << ds0 << " " << DisttoWall << endl;
      if( drmax<dr1 ) drmax = dr1;
      
      if( !foundVertex && trueVtxZ>0.0 ) aaa++;
      else if( !extendedVtxPass ) bbb++;
      else ccc++;

      Double_t proZ = 0.0;
      Double_t proX = 0.0;
      Double_t proY = 0.0;
      if( trueDirZ>0.0 ) proZ = height;
      else proZ = -height;
      proY = trueVtxY + trueDirY*(proZ-trueVtxZ)/trueDirZ;
      proX = trueVtxX + trueDirX*(proZ-trueVtxZ)/trueDirZ;
      Double_t coss = 0.0;
      Int_t side = 0;
      if( (proX*proX + proY*proY)<(radius*radius) ){ side = 0; coss = sqrt(trueDirZ*trueDirZ); }
      else{
        //Double_t a = trueDirY/trueDirX;
        //Double_t b = trueVtxY*trueVtxX*trueDirY/trueDirX;
        //Double_t c = radius*radius;
        //if( trueDirX==0.0 ){
          //proX = trueVtxX;
          //if( trueDirY>0.0 ){ proY = sqrt(radius*radius-trueVtxX*trueVtxX); }
          //else{ proY = -1.0*sqrt(radius*radius-trueVtxX*trueVtxX); }
        //}
        //else{
          Double_t a = trueDirY/trueDirX;
          Double_t b = trueVtxY - trueVtxX*trueDirY/trueDirX;
          Double_t c = radius*radius;
          if( trueDirX>0.0 ){
            proX = (-2.0*b*a + sqrt(4.0*b*b*a*a - 4.0*(1.0+a*a)*(b*b-c)))/(2.0*(1.0+a*a)); }
          else{
            proX = (-2.0*b*a - sqrt(4.0*b*b*a*a - 4.0*(1.0+a*a)*(b*b-c)))/(2.0*(1.0+a*a)); }       
          proY = trueVtxY + (proX-trueVtxX)*trueDirY/trueDirX;
          proZ = trueVtxZ + (proX-trueVtxX)*trueDirZ/trueDirX; 
       // }
          coss = (proX*trueDirX + proY*trueDirY)/sqrt(proX*proX+proY*proY);
          side = 1;
      }
      coss = acos(coss);
      //cout << costh0 << " " << coss << " " << side << endl;
      // vertex finder
      // =============
      if( foundVertex && DisttoWall2>300.0 ){
      //if( foundVertex ){
        ctr_extended_fit += 1.0;

        if( extendedVtxPass==1 ){
          ctr_extended_fit_pass += 1.0;
          //ArrExtendedPara[i] = TMath::Abs(0.01*(costh5*ds5));
          //ArrExtendedPerp[i] = 0.01*(sinth5*ds5);
          //ArrExtendedAngle[i] = theta6;
          //ArrExtendedDelta[i] = 0.01*ds5;
          //if( ds5*sqrt(costh5*costh5)>25.0 ) testconh->Fill(coss);
          testconh->Fill(ds5*sinth5); 
	  // cout <<eventNum <<", ";
	 //  cout << "point"<<ctr_extended_fit << ". " <<eventNum 
// 	       << " para " <<ds2*(TMath::Abs(costh2)) 
// 	       << " perp " << ds2*sinth2<< endl;

	  ParaPerpC->Fill(ds2*(TMath::Abs(costh2)), ds2*sinth2);
	  TotalDistC->Fill(ds2); 
	  NFilterDigitsC->Fill(nFilterDigits);
	  
	  //cout << ctr_extended_fit << ". " <<eventNum 
	  //   << " para " << ds5*costh5 << " perp " << ds5*sinth5<< endl;
          //test2conh->Fill(DisttoWall,trueDirZ);
          //testh->Fill(0.01*(TMath::Abs(costh5*ds5)));
          //testh->Fill(0.01*ds5);
          //testh->Fill(theta6);
          //if( ds5*sqrt(costh5*costh5)<2.0 ) cout << eventNum << " ";
        }
        else{ testnonh->Fill(ds0);
	  ParaPerpNC->Fill(ds2*(TMath::Abs(costh2)), ds2*sinth2);
	  TotalDistNC->Fill(ds2);
	  NFilterDigitsNC->Fill(nFilterDigits);cout <<eventNum <<", ";
	}
        //else{ testnonh->Fill(coss); test2nonh->Fill(DisttoWall,trueDirZ); }
        //else cout << eventNum << " " << extendedVtxPass << " " << ds0 << " " << ds5*(TMath::Abs(costh5)) << endl; }
        //cout << eventNum << " " << extendedVtxPass << " " << ds0 << " " << ds5*(TMath::Abs(costh5)) << endl;
        //}
      }
   
    }

  }

  Double_t norm = testconh->Integral();
  //testconh->Scale(1/norm);
  norm = testnonh->Integral();
  //testnonh->Scale(1/norm);
  testconh->GetXaxis()->SetTitle("Ltrack [cm]");
  testconh->GetYaxis()->SetTitle("Events");
  testconh->SetLineWidth(2.0);
  testnonh->SetLineWidth(2.0);
  testnonh->SetLineColor(kRed);
  test2conh->GetXaxis()->SetTitle("Vtx to Wall [cm]");
  test2conh->GetYaxis()->SetTitle("Ltrack [cm]");
  test2conh->SetMarkerSize(0.5);
  test2nonh->SetMarkerSize(0.5);
  test2nonh->SetMarkerColor(kRed);
  testconh->Draw();
  //testnonh->Draw("Same");
  //testconh->Draw("Same");

  //cout << drmax << endl;
  //cout << aaa << " " << bbb << " " << ccc << endl; 

//============ calculate uncertainty =========================
  //Double_t lower = 0.32*ctr_extended_fit_pass;
  //Double_t mid = 0.5*ctr_extended_fit_pass;
  Double_t level = 0.68*ctr_extended_fit_pass;
  Double_t totalcontent = 0.0;
  Double_t totalerr = 0.0;
  Int_t iupper = 0;
  Int_t ilower = 0;
  Int_t imid = 0;

  Double_t content[nbin];
  Double_t binerr[nbin];
  testconh->Sumw2();
  for( Int_t j=0;j<nbin;j++ ){
    content[j] = testconh->GetBinContent(j);
    Double_t ierr = testconh->GetBinError(j);
    binerr[j] = ierr*ierr;
  }
   
  do{
    totalcontent += content[iupper];
    totalerr += binerr[iupper];
    iupper += 1; 
    //cout << iupper << " " << content << " " << binerr << " " << totalerr << endl;
  } while( (totalcontent-sqrt(totalerr)) < level );
  Double_t upper = (iupper - 1.0)*range/nbin + (range/nbin)*(level - totalcontent + sqrt(totalerr) + content[iupper-1])/content[iupper-1];
  
  totalcontent = 0.0;
  totalerr = 0.0;
  do{
    totalcontent += content[imid];
    totalerr += binerr[imid];
    imid += 1; 
    //cout << imid << " " << content << " " << binerr << " " << totalerr << endl;
  } while( (totalcontent) < level );
  Double_t mid = (imid - 1.0)*range/nbin + (range/nbin)*(level - totalcontent + content[imid-1])/content[imid-1];
  //cout << imid << " " << range/nbin << " " << content[imid-1] << " " << (level  - totalcontent + content[imid-1]) << endl;
  
  totalcontent = 0.0;
  totalerr = 0.0;
  do{
    totalcontent += content[ilower];
    totalerr += binerr[ilower];
    ilower += 1; 
    //cout << ilower << " " << content << " " << binerr << " " << totalerr << endl;
  } while( (totalcontent+sqrt(totalerr)) < level );
  Double_t lower = (ilower - 1.0)*range/nbin + (range/nbin)*(level - totalcontent - sqrt(totalerr) + content[ilower-1])/content[ilower-1];

  std::cout << "(" << mid << ", -" << mid-lower << ", +" << upper-mid << ")" << std::endl;

//======================================================================

  // Print Some Results
  if( ctr_extended_fit>0.0 ) ctr_extended_fit_pass_frac = ctr_extended_fit_pass/ctr_extended_fit;
  std::cout << " Number of fitted tracks [extended fit] = " << ctr_extended_fit << std::endl;
  std::cout << " Number of converged tracks [extended fit] = " << ctr_extended_fit_pass << std::endl;
  std::cout << "  Fraction of converged tracks [extended fit] = " << ctr_extended_fit_pass_frac << std::endl;
  

  (ParaPerpC->GetXaxis())->SetTitle("para");
  (ParaPerpC->GetYaxis())->SetTitle("perp");
  ParaPerpC->SetMarkerStyle(34);
  ParaPerpC->Draw(); 
  ParaPerpNC->SetMarkerStyle(24);
  ParaPerpNC->SetMarkerColor(kRed);
  ParaPerpNC->Draw("same");
  leg=new TLegend(0.65,0.75,0.9,0.9,"");
  leg->AddEntry(PPC,"Convergent","p");
  leg->AddEntry(PPNC,"Not Convergent","p");
  leg->Draw();


  TCanvas *ca2 = new TCanvas("ca2","",800,600); 
  (TotalDistC->GetXaxis())->SetTitle("Norm(true-point)");
  (TotalDistC->GetYaxis())->SetTitle("NoEvents");
  TotalDistC->Draw();
  TotalDistNC->SetLineColor(kRed);
  TotalDistNC->Draw("same");
  leg2=new TLegend(0.65,0.75,0.9,0.9,"");
  leg2->AddEntry(DC,"Convergent","l");
  leg2->AddEntry(DNC,"Not Convergent","l");
  leg2->Draw();


 TCanvas *ca3 = new TCanvas("ca3","ca3",800,600); 
 (NFilterDigitsC->GetXaxis())->SetTitle("NFilterDigits");
 (NFilterDigitsC->GetYaxis())->SetTitle("NoEvents");
 NFilterDigitsC->Draw();
 NFilterDigitsNC->SetLineColor(kRed);
 NFilterDigitsNC->Draw("same");

}
