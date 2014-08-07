{
  
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
  Int_t foundRings;

  Double_t recoVtxX;
  Double_t recoVtxY;
  Double_t recoVtxZ;
  Double_t recoVtxTime;
  Double_t recoVtxFOM;
  Double_t recoDirX;
  Double_t recoDirY;
  Double_t recoDirZ;

  Double_t recoRingVtxX;
  Double_t recoRingVtxY;
  Double_t recoRingVtxZ;
  Double_t recoRingDirX;
  Double_t recoRingDirY;
  Double_t recoRingDirZ;
  Double_t recoRingAngle;
  Double_t recoRingHeight;
  Double_t recoRingHeightFrac;


  // Testing Reconstruction
  Double_t simpleVtxX;
  Double_t simpleVtxY;
  Double_t simpleVtxZ;
  Double_t pointVtxX;
  Double_t pointVtxY;
  Double_t pointVtxZ;
  Double_t pointVtxFOM;
  Int_t pointVtxSteps;
  Int_t pointVtxPass;
  Double_t simpleDirX;
  Double_t simpleDirY;
  Double_t simpleDirZ;
  Double_t pointDirX;
  Double_t pointDirY;
  Double_t pointDirZ;
  Double_t pointDirAngle;
  Double_t pointDirFOM;
  Int_t pointDirSteps;
  Int_t pointDirPass;
  Double_t extendedVtxX;
  Double_t extendedVtxY;
  Double_t extendedVtxZ;
  Double_t extendedVtxFOM;
  Double_t extendedDirX;
  Double_t extendedDirY;
  Double_t extendedDirZ;
  Double_t extendedDirAngle;
  Int_t extendedVtxSteps;
  Int_t extendedVtxPass;

  Double_t simpleDirX_from_trueVtx;
  Double_t simpleDirY_from_trueVtx;
  Double_t simpleDirZ_from_trueVtx;
  Double_t pointDirX_from_trueVtx;
  Double_t pointDirY_from_trueVtx;
  Double_t pointDirZ_from_trueVtx;
  Double_t pointDirFOM_from_trueVtx;
  Double_t extendedVtxX_from_trueVtx;
  Double_t extendedVtxY_from_trueVtx;
  Double_t extendedVtxZ_from_trueVtx;
  Double_t extendedVtxFOM_from_trueVtx;

  TChain* RecoChain = new TChain("ntuple","chain");

  /*
  RecoChain->Add("ntuple.test.1.root");
  RecoChain->Add("ntuple.test.2.root");
  */

  /* 
  // electrons
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_12001_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_12002_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_12003_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_12004_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_12005_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_12006_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_12007_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_12008_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_12009_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/electron_vtx_120010_reco.root");
  */

  /* 
  // muons
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_40001_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_40002_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_40003_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_40004_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_40005_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_40006_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_40007_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_40008_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_40009_reco.root");
  RecoChain->Add("/r01/lbne/water/wcreco_root_files/DUSEL_100kton_10inch_15perCent/muon_vtx_400010_reco.root");
  */

  // atmospheric neutrinos
  // RecoChain->Add("/r01/lbne/water/wcreco_root_files_atmos/DUSEL_100kton_10inch_15perCent/atmos_bartolmax_water_100kton*root");

  // cosmic muons
  RecoChain->Add("/r01/lbne/water/wcreco_root_files_cosmic/DUSEL_100kton_10inch_15perCent/cosmic_DUSEL_4850ft_fix_long_100kton*root");

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
  RecoChain->SetBranchAddress("foundRings",&foundRings);
  RecoChain->SetBranchAddress("recoVtxX",&recoVtxX);
  RecoChain->SetBranchAddress("recoVtxY",&recoVtxY);
  RecoChain->SetBranchAddress("recoVtxZ",&recoVtxZ);
  RecoChain->SetBranchAddress("recoVtxTime",&recoVtxTime);
  RecoChain->SetBranchAddress("recoVtxFOM",&recoVtxFOM);
  RecoChain->SetBranchAddress("recoDirX",&recoDirX);
  RecoChain->SetBranchAddress("recoDirY",&recoDirY);
  RecoChain->SetBranchAddress("recoDirZ",&recoDirZ);
  RecoChain->SetBranchAddress("recoRingVtxX",&recoRingVtxX);
  RecoChain->SetBranchAddress("recoRingVtxY",&recoRingVtxY);
  RecoChain->SetBranchAddress("recoRingVtxZ",&recoRingVtxZ);
  RecoChain->SetBranchAddress("recoRingDirX",&recoRingDirX);
  RecoChain->SetBranchAddress("recoRingDirY",&recoRingDirY);
  RecoChain->SetBranchAddress("recoRingDirZ",&recoRingDirZ);
  RecoChain->SetBranchAddress("recoRingAngle",&recoRingAngle);
  RecoChain->SetBranchAddress("recoRingHeight",&recoRingHeight);
  RecoChain->SetBranchAddress("recoRingHeightFrac",&recoRingHeightFrac);

  RecoChain->SetBranchAddress("simpleVtxX",&simpleVtxX);
  RecoChain->SetBranchAddress("simpleVtxY",&simpleVtxY);
  RecoChain->SetBranchAddress("simpleVtxZ",&simpleVtxZ);
  RecoChain->SetBranchAddress("pointVtxX",&pointVtxX);
  RecoChain->SetBranchAddress("pointVtxY",&pointVtxY);
  RecoChain->SetBranchAddress("pointVtxZ",&pointVtxZ);
  RecoChain->SetBranchAddress("pointVtxFOM",&pointVtxFOM);
  RecoChain->SetBranchAddress("pointVtxSteps",&pointVtxSteps);
  RecoChain->SetBranchAddress("pointVtxPass",&pointVtxPass);
  RecoChain->SetBranchAddress("simpleDirX",&simpleDirX);
  RecoChain->SetBranchAddress("simpleDirY",&simpleDirY);
  RecoChain->SetBranchAddress("simpleDirZ",&simpleDirZ);
  RecoChain->SetBranchAddress("pointDirX",&pointDirX);
  RecoChain->SetBranchAddress("pointDirY",&pointDirY);
  RecoChain->SetBranchAddress("pointDirZ",&pointDirZ);
  RecoChain->SetBranchAddress("pointDirAngle",&pointDirAngle);
  RecoChain->SetBranchAddress("pointDirFOM",&pointDirFOM);
  RecoChain->SetBranchAddress("pointDirSteps",&pointDirSteps);
  RecoChain->SetBranchAddress("pointDirPass",&pointDirPass);
  RecoChain->SetBranchAddress("extendedVtxX",&extendedVtxX);
  RecoChain->SetBranchAddress("extendedVtxY",&extendedVtxY);
  RecoChain->SetBranchAddress("extendedVtxZ",&extendedVtxZ);
  RecoChain->SetBranchAddress("extendedVtxFOM",&extendedVtxFOM);
  RecoChain->SetBranchAddress("extendedDirX",&extendedDirX);
  RecoChain->SetBranchAddress("extendedDirY",&extendedDirY);
  RecoChain->SetBranchAddress("extendedDirZ",&extendedDirZ);
  RecoChain->SetBranchAddress("extendedDirAngle",&extendedDirAngle);
  RecoChain->SetBranchAddress("extendedVtxSteps",&extendedVtxSteps);
  RecoChain->SetBranchAddress("extendedVtxPass",&extendedVtxPass);

  RecoChain->SetBranchAddress("simpleDirX_from_trueVtx",&simpleDirX_from_trueVtx);
  RecoChain->SetBranchAddress("simpleDirY_from_trueVtx",&simpleDirY_from_trueVtx);
  RecoChain->SetBranchAddress("simpleDirZ_from_trueVtx",&simpleDirZ_from_trueVtx);
  RecoChain->SetBranchAddress("pointDirX_from_trueVtx",&pointDirX_from_trueVtx);
  RecoChain->SetBranchAddress("pointDirY_from_trueVtx",&pointDirY_from_trueVtx);
  RecoChain->SetBranchAddress("pointDirZ_from_trueVtx",&pointDirZ_from_trueVtx);  
  RecoChain->SetBranchAddress("pointDirFOM_from_trueVtx",&pointDirFOM_from_trueVtx);
  RecoChain->SetBranchAddress("extendedVtxX_from_trueVtx",&extendedVtxX_from_trueVtx);
  RecoChain->SetBranchAddress("extendedVtxY_from_trueVtx",&extendedVtxY_from_trueVtx);
  RecoChain->SetBranchAddress("extendedVtxZ_from_trueVtx",&extendedVtxZ_from_trueVtx);
  RecoChain->SetBranchAddress("extendedVtxFOM_from_trueVtx",&extendedVtxFOM_from_trueVtx);

  TH1D* hDigits = new TH1D("hDigits","",84,0.0,42000.0);
  hDigits->SetLineWidth(2);
  hDigits->SetLineColor(kBlue+1);
  hDigits->SetFillColor(kBlue+1);
  hDigits->SetFillStyle(3004);
  hDigits->GetXaxis()->SetTitle("Number of Digits");
  hDigits->GetYaxis()->SetTitle("Events");
  hDigits->SetMinimum(0.0);

  TH1D* hDigitsZoom = new TH1D("hDigitsZoom","",80,0.0,20000.0);
  hDigitsZoom->SetLineWidth(2);
  hDigitsZoom->SetLineColor(kBlue+1);
  hDigitsZoom->SetFillColor(kBlue+1);
  hDigitsZoom->SetFillStyle(3004);
  hDigitsZoom->GetXaxis()->SetTitle("Number of Digits");
  hDigitsZoom->GetYaxis()->SetTitle("Events");
  hDigitsZoom->SetMinimum(0.0);

  TH1D* hVertexR2 = new TH1D("hVertexR2","",40,0.0,800.0);
  hVertexR2->GetXaxis()->SetTitle("Vertex R^{2} / m^{2}");
  hVertexR2->GetYaxis()->SetTitle("Events");
  hVertexR2->SetFillColor(kBlue+1);
  hVertexR2->SetLineColor(kBlue+1);
  hVertexR2->SetFillStyle(3004);
  hVertexR2->SetLineWidth(2);
  hVertexR2->SetMinimum(0.0);

  TH1D* hVertexPhi = new TH1D("hVertexPhi","",40,-200.0,200.0);
  hVertexPhi->GetXaxis()->SetTitle("Vertex #theta / degrees");
  hVertexPhi->GetYaxis()->SetTitle("Events");
  hVertexPhi->SetFillColor(kBlue+1);
  hVertexPhi->SetLineColor(kBlue+1);
  hVertexPhi->SetFillStyle(3004);
  hVertexPhi->SetLineWidth(2);
  hVertexPhi->SetMinimum(0.0);

  TH1D* hVertexZ = new TH1D("hVertexZ","",35,-35.0,+35.0);
  hVertexZ->GetXaxis()->SetTitle("Vertex Z / m");
  hVertexZ->GetYaxis()->SetTitle("Events");
  hVertexZ->SetFillColor(kBlue+1);
  hVertexZ->SetLineColor(kBlue+1);
  hVertexZ->SetFillStyle(3004);
  hVertexZ->SetLineWidth(2);
  hVertexZ->SetMinimum(0.0);

  TH1D* hDirCosTheta = new TH1D("hDirCosTheta","",50,-1.0,+1.0);
  hDirCosTheta->GetXaxis()->SetTitle("cos(#theta)");
  hDirCosTheta->GetYaxis()->SetTitle("Events");
  hDirCosTheta->SetFillColor(kBlue+1);
  hDirCosTheta->SetLineColor(kBlue+1);
  hDirCosTheta->SetFillStyle(3004);
  hDirCosTheta->SetLineWidth(2);  
  hDirCosTheta->SetMinimum(0.0);

  TH1D* hDirPhi = new TH1D("hDirPhi","",40,-200.0,+200.0);
  hDirPhi->GetXaxis()->SetTitle("#phi / degrees");
  hDirPhi->GetYaxis()->SetTitle("Events");
  hDirPhi->SetFillColor(kBlue+1);
  hDirPhi->SetLineColor(kBlue+1);
  hDirPhi->SetFillStyle(3004);
  hDirPhi->SetLineWidth(2);
  hDirPhi->SetMinimum(0.0);


  TH2D* hVtxSimplePosition = new TH2D("hVtxSimplePosition","",90,-1.0,+17.0,60,0.0,+12.0);
  hVtxSimplePosition->GetXaxis()->SetTitle("Distance along True Trajectory / m");
  hVtxSimplePosition->GetYaxis()->SetTitle("Perpendicular Distance / m");
  hVtxSimplePosition->GetYaxis()->SetTitleOffset(0.9);
  hVtxSimplePosition->SetMarkerSize(0.75);

  TH1D* hVtxSimplePositionR2 = new TH1D("hVtxSimplePositionR2","",40,0.0,800.0);
  hVtxSimplePositionR2->GetXaxis()->SetTitle("R^{2} / m^{2}");
  hVtxSimplePositionR2->GetYaxis()->SetTitle("Events");
  hVtxSimplePositionR2->GetYaxis()->SetTitleOffset(0.9);
  hVtxSimplePositionR2->SetMarkerSize(0.75);
  hVtxSimplePositionR2->SetLineWidth(2);
  hVtxSimplePositionR2->SetLineColor(kBlue+1);
  hVtxSimplePositionR2->SetFillColor(kBlue+1);
  hVtxSimplePositionR2->SetFillStyle(3004);
  hVtxSimplePositionR2->SetMinimum(0.0);

  TH2D* hVtxPointPosition = new TH2D("hVtxPointPosition","",90,-2.0,+7.0,60,0.0,+3.0);
  hVtxPointPosition->GetXaxis()->SetTitle("Distance along True Trajectory / m");
  hVtxPointPosition->GetYaxis()->SetTitle("Perpendicular Distance / m");
  hVtxPointPosition->GetYaxis()->SetTitleOffset(0.9);
  hVtxPointPosition->SetMarkerSize(0.75);  

  TH1D* hVtxPointPositionProf = new TH1D("hVtxPointPositionProf","",45,-2.0,+7.0);
  hVtxPointPositionProf->GetXaxis()->SetTitle("Distance along True Trajectory / m");
  hVtxPointPositionProf->GetYaxis()->SetTitle("Events");
  hVtxPointPositionProf->SetLineWidth(2);
  hVtxPointPositionProf->SetLineColor(kBlue+1);
  hVtxPointPositionProf->SetFillColor(kBlue+1);
  hVtxPointPositionProf->SetFillStyle(3004);
  hVtxPointPositionProf->GetYaxis()->SetTitleOffset(0.9);  
  hVtxPointPositionProf->SetMinimum(0.0);

  TH1D* hVtxPointSteps = new TH1D("hVtxPointSteps","",50,0.0,500);
  hVtxPointSteps->SetLineWidth(2);
  hVtxPointSteps->SetLineColor(kBlue+1);
  hVtxPointSteps->GetXaxis()->SetTitle("Number of Iterations");
  hVtxPointSteps->GetYaxis()->SetTitle("Events");
  hVtxPointSteps->GetYaxis()->SetTitleOffset(1.2);
  hVtxPointSteps->SetMinimum(0.0);

  TH1D* hVtxPointFOM = new TH1D("hVtxPointFOM","",50,0.0,1.0);
  hVtxPointFOM->SetLineWidth(2);
  hVtxPointFOM->SetLineColor(kBlue+1);
  hVtxPointFOM->SetFillColor(kBlue+1);
  hVtxPointFOM->SetFillStyle(3004);
  hVtxPointFOM->GetXaxis()->SetTitle("Goodness of Fit");
  hVtxPointFOM->GetYaxis()->SetTitle("Events");
  hVtxPointFOM->GetYaxis()->SetTitleOffset(1.2);  
  hVtxPointFOM->SetMinimum(0.0);
 

  TH1D* hDirSimpleTheta = new TH1D("hDirSimpleTheta","",60,0.0,+30.0);
  hDirSimpleTheta->SetLineWidth(2); 
  hDirSimpleTheta->SetLineColor(kBlue+1);
  hDirSimpleTheta->SetFillColor(kBlue+1);
  hDirSimpleTheta->SetFillStyle(3004);
  hDirSimpleTheta->GetXaxis()->SetTitle("Angle w.r.t True Trajectory");
  hDirSimpleTheta->GetYaxis()->SetTitle("Events");
  hDirSimpleTheta->GetYaxis()->SetTitleOffset(1.2);  
  hDirSimpleTheta->SetMinimum(0.0);

  TH1D* hDirPointTheta = new TH1D("hDirPointTheta","",60,0.0,+30.0);
  hDirPointTheta->SetLineWidth(2); 
  hDirPointTheta->SetLineColor(kBlue+1);
  hDirPointTheta->SetFillColor(kBlue+1);
  hDirPointTheta->SetFillStyle(3004);
  hDirPointTheta->GetXaxis()->SetTitle("Angle w.r.t True Trajectory");
  hDirPointTheta->GetYaxis()->SetTitle("Events");
  hDirPointTheta->GetYaxis()->SetTitleOffset(1.2);
  hDirPointTheta->SetMinimum(0.0);  

  TH1D* hDirPointThetaZoom = new TH1D("hDirPointThetaZoom","",25,0.0,+5.0);
  hDirPointThetaZoom->SetLineWidth(2); 
  hDirPointThetaZoom->SetLineColor(kBlue+1);
  hDirPointThetaZoom->SetFillColor(kBlue+1);
  hDirPointThetaZoom->SetFillStyle(3004);
  hDirPointThetaZoom->GetXaxis()->SetTitle("Angle w.r.t True Trajectory");
  hDirPointThetaZoom->GetYaxis()->SetTitle("Events");
  hDirPointThetaZoom->GetYaxis()->SetTitleOffset(1.2);
  hDirPointThetaZoom->SetMinimum(0.0);


  TH1D* hVtxExtendedFOM = new TH1D("hVtxExtendedFOM","",50,0.0,1.0);
  hVtxExtendedFOM->SetLineWidth(2);
  hVtxExtendedFOM->SetLineColor(kBlue+1);
  hVtxExtendedFOM->SetFillColor(kBlue+1);
  hVtxExtendedFOM->SetFillStyle(3004);
  hVtxExtendedFOM->GetXaxis()->SetTitle("Goodness of Fit");
  hVtxExtendedFOM->GetYaxis()->SetTitle("Events");
  hVtxExtendedFOM->GetYaxis()->SetTitleOffset(1.2);  
  hVtxExtendedFOM->SetMinimum(0.0);


  TH1D* hVtxExtendedZ = new TH1D("hVtxExtendedZ","",70,-35.0,+35.0);
  hVtxExtendedZ->GetXaxis()->SetTitle("Vertex Z / m");
  hVtxExtendedZ->GetYaxis()->SetTitle("Events");
  hVtxExtendedZ->SetFillColor(kBlue+1);
  hVtxExtendedZ->SetLineColor(kBlue+1);
  hVtxExtendedZ->SetFillStyle(3004);
  hVtxExtendedZ->SetLineWidth(2);
  hVtxExtendedZ->SetMinimum(0.0);

  TH1D* hVtxExtendedR2 = new TH1D("hVtxExtendedR2","",80,0.0,800.0);
  hVtxExtendedR2->GetXaxis()->SetTitle("Vertex R^{2} / m^{2}");
  hVtxExtendedR2->GetYaxis()->SetTitle("Events");
  hVtxExtendedR2->SetFillColor(kBlue+1);
  hVtxExtendedR2->SetLineColor(kBlue+1);
  hVtxExtendedR2->SetFillStyle(3004);
  hVtxExtendedR2->SetLineWidth(2);
  hVtxExtendedR2->SetMinimum(0.0);

  TH2D* hVtxExtendedPosition = new TH2D("hVtxExtendedPosition","",90,-2.0,+7.0,60,0.0,+3.0); 
  // TH2D* hVtxExtendedPosition = new TH2D("hVtxExtendedPosition","",120,-2.0,+4.0,40,0.0,+2.0);
  hVtxExtendedPosition->GetXaxis()->SetTitle("Distance along True Trajectory / m");
  hVtxExtendedPosition->GetYaxis()->SetTitle("Perpendicular Distance / m");
  hVtxExtendedPosition->GetYaxis()->SetTitleOffset(0.9);
  hVtxExtendedPosition->SetMarkerSize(0.75);      

  TH1D* hVtxExtendedPositionProf = new TH1D("hVtxExtendedPositionProf","",45,-2.0,+7.0);
  hVtxExtendedPositionProf->GetXaxis()->SetTitle("Distance along True Trajectory / m");
  hVtxExtendedPositionProf->GetYaxis()->SetTitle("Events");
  hVtxExtendedPositionProf->SetLineWidth(2);
  hVtxExtendedPositionProf->SetLineColor(kBlue+1);
  hVtxExtendedPositionProf->SetFillColor(kBlue+1);
  hVtxExtendedPositionProf->SetFillStyle(3004);
  hVtxExtendedPositionProf->GetYaxis()->SetTitleOffset(0.9);  
  hVtxExtendedPositionProf->SetMinimum(0.0);

  TH1D* hVtxExtendedPositionProfZoom = new TH1D("hVtxExtendedPositionProfZoom","",50,-2.5,+2.5);
  hVtxExtendedPositionProfZoom->GetXaxis()->SetTitle("Distance along True Trajectory / m");
  hVtxExtendedPositionProfZoom->GetYaxis()->SetTitle("Events");
  hVtxExtendedPositionProfZoom->SetLineWidth(2);
  hVtxExtendedPositionProfZoom->SetLineColor(kBlue+1);
  hVtxExtendedPositionProfZoom->SetFillColor(kBlue+1);
  hVtxExtendedPositionProfZoom->SetFillStyle(3004);
  hVtxExtendedPositionProfZoom->GetYaxis()->SetTitleOffset(0.9);  
  hVtxExtendedPositionProfZoom->SetMinimum(0.0);

  TH2D* hVtxExtendedPositionPass = new TH2D("hVtxExtendedPositionPass","",90,-2.0,+7.0,60,0.0,+3.0);
  hVtxExtendedPositionPass->GetXaxis()->SetTitle("Distance along True Trajectory / m");
  hVtxExtendedPositionPass->GetYaxis()->SetTitle("Perpendicular Distance / m");
  hVtxExtendedPositionPass->GetYaxis()->SetTitleOffset(0.9);
  hVtxExtendedPositionPass->SetMarkerSize(0.75);     

  TH1D* hVtxExtendedPositionPassProf = new TH1D("hVtxExtendedPositionPassProf","",45,-2.0,+7.0);
  hVtxExtendedPositionPassProf->GetXaxis()->SetTitle("Distance along True Trajectory / m");
  hVtxExtendedPositionPassProf->GetYaxis()->SetTitle("Events");
  hVtxExtendedPositionPassProf->SetLineWidth(2);
  hVtxExtendedPositionPassProf->SetLineColor(kBlue+1);
  hVtxExtendedPositionPassProf->SetFillColor(kBlue+1);
  hVtxExtendedPositionPassProf->SetFillStyle(3004);
  hVtxExtendedPositionPassProf->GetYaxis()->SetTitleOffset(0.9);  
  hVtxExtendedPositionPassProf->SetMinimum(0.0);

  TH1D* hDirExtendedTheta = new TH1D("hDirExtendedTheta","",40,0.0,+20.0);
  hDirExtendedTheta->SetLineWidth(2); 
  hDirExtendedTheta->SetLineColor(kBlue+1);
  hDirExtendedTheta->SetFillColor(kBlue+1);
  hDirExtendedTheta->SetFillStyle(3004);
  hDirExtendedTheta->GetXaxis()->SetTitle("Angle w.r.t True Trajectory");
  hDirExtendedTheta->GetYaxis()->SetTitle("Events");
  hDirExtendedTheta->GetYaxis()->SetTitleOffset(1.2);
  hDirExtendedTheta->SetMinimum(0.0);    

  TH1D* hVtxExtendedDelta = new TH1D("hVtxExtendedDelta","",50,0.0,+2.5.0);
  hVtxExtendedDelta->SetLineWidth(2); 
  hVtxExtendedDelta->SetLineColor(kBlue+1);
  hVtxExtendedDelta->SetFillColor(kBlue+1);
  hVtxExtendedDelta->SetFillStyle(3004);
  hVtxExtendedDelta->GetXaxis()->SetTitle("Distance from True Vertex / m");
  hVtxExtendedDelta->GetYaxis()->SetTitle("Events");
  hVtxExtendedDelta->GetYaxis()->SetTitleOffset(1.2);
  hVtxExtendedDelta->SetMinimum(0.0);  
 

  TH1D* hDirRingTheta = new TH1D("hDirRingTheta","",40,0.0,+60.0);
  hDirRingTheta->SetLineWidth(2); 
  hDirRingTheta->SetLineColor(kBlue+1);
  hDirRingTheta->SetFillColor(kBlue+1);
  hDirRingTheta->SetFillStyle(3004);
  hDirRingTheta->GetXaxis()->SetTitle("Angle w.r.t True Trajectory");
  hDirRingTheta->GetYaxis()->SetTitle("Events");
  hDirRingTheta->GetYaxis()->SetTitleOffset(1.2);
  hDirRingTheta->SetMinimum(0.0);    

  TH1D* hDirRingPulseHeightFrac = new TH1D("hDirRingPulseHeightFrac","",40,0.0,1.0);
  hDirRingPulseHeightFrac->SetLineWidth(2); 
  hDirRingPulseHeightFrac->SetLineColor(kBlue+1);
  hDirRingPulseHeightFrac->SetFillColor(kBlue+1);
  hDirRingPulseHeightFrac->SetFillStyle(3004);
  hDirRingPulseHeightFrac->GetXaxis()->SetTitle("Hough peak size");
  hDirRingPulseHeightFrac->GetYaxis()->SetTitle("Events");
  hDirRingPulseHeightFrac->SetTitleOffset(1.2);
  hDirRingPulseHeightFrac->SetMinimum(0.0);


  Int_t ElectronID = +11;
  Int_t MuonID = +13;

  Double_t phi = 0.0;
  Double_t sinth;

  Double_t fLimit = 0.999999;

  Double_t ctr_extended_fit = 0.0;
  Double_t ctr_extended_fit_pass = 0.0;
  Double_t ctr_extended_fit_pass_frac = 0.0;

  for( Int_t i=0; i<RecoChain->GetEntries(); i++ ){
    RecoChain->GetEntry(i);

    // fill histograms
    // ===============
    if( 1 ){//fabs(truePDG)==MuonID ){

      // basic distributions
      // ===================
      hDigits->Fill(nDigits);
      hDigitsZoom->Fill(nDigits);
      
      hVertexR2->Fill( 0.01*0.01*(trueVtxX*trueVtxX+trueVtxY*trueVtxY) );
      hVertexZ->Fill( 0.01*trueVtxZ );
      hDirCosTheta->Fill(trueDirZ );

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
      hVertexPhi->Fill(phi);

      phi = 0.0;
      if( trueDirX!=0.0 ){
        phi = atan(trueDirY/trueDirX);
      }
      if( trueDirX<=0.0 ){
        if( trueDirY>0.0 ) phi += TMath::Pi();
        if( trueDirY<0.0 ) phi -= TMath::Pi();
      }
      phi *= 180.0/TMath::Pi();
      hDirPhi->Fill(phi);


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

      Double_t costh0 = px0*trueDirX+py0*trueDirY+pz0*trueDirZ; if( costh0>fLimit ) costh0 = fLimit;
      Double_t sinth0 = sqrt(1.0-costh0*costh0);
      Double_t theta0 = (180.0/TMath::Pi())*acos(costh0);

      // simple vertex
      Double_t dx1 = simpleVtxX - trueVtxX;
      Double_t dy1 = simpleVtxY - trueVtxY;
      Double_t dz1 = simpleVtxZ - trueVtxZ;
      Double_t ds1 = sqrt( dx1*dx1 + dy1*dy1 + dz1*dz1 );
      Double_t px1 = dx1/ds1;
      Double_t py1 = dy1/ds1;
      Double_t pz1 = dz1/ds1;

      Double_t costh1 = px1*trueDirX+py1*trueDirY+pz1*trueDirZ; if( costh1>fLimit ) costh1 = fLimit;
      Double_t sinth1 = sqrt(1.0-costh1*costh1);
      Double_t theta1 = (180.0/TMath::Pi())*acos(costh1);

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
      Double_t px3 = simpleDirX_from_trueVtx;
      Double_t py3 = simpleDirY_from_trueVtx;
      Double_t pz3 = simpleDirZ_from_trueVtx;

      Double_t costh3 = px3*trueDirX+py3*trueDirY+pz3*trueDirZ; if( costh3>fLimit ) costh3 = fLimit;
      Double_t theta3 = (180.0/TMath::Pi())*acos(costh3);

      // point direction (using truth)
      Double_t px4 = pointDirX_from_trueVtx;
      Double_t py4 = pointDirY_from_trueVtx;
      Double_t pz4 = pointDirZ_from_trueVtx;

      Double_t costh4 = px4*trueDirX+py4*trueDirY+pz4*trueDirZ; if( costh4>fLimit ) costh4 = fLimit;
      Double_t theta4 = (180.0/TMath::Pi())*acos(costh4);

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

      // primary ring
      Double_t costh7 = recoRingDirX*trueDirX + recoRingDirY*trueDirY + recoRingDirZ*trueDirZ; 
      if( costh7>fLimit ) costh7 = fLimit;
      Double_t sinth7 = sqrt(1.0-costh7*costh7);
      Double_t theta7 = (180.0/TMath::Pi())*acos(costh7);


      // vertex finder
      // =============
      if( foundVertex ){

        hVtxSimplePosition->Fill(0.01*(costh1*ds1),0.01*(sinth1*ds1));
        hVtxSimplePositionR2->Fill( 0.01*0.01*(simpleVtxX*simpleVtxX+simpleVtxY*simpleVtxY) );

        if(pointVtxFOM>0.0){
          hVtxPointPosition->Fill(0.01*(costh2*ds2),0.01*(sinth2*ds2));
          hVtxPointPositionProf->Fill(0.01*(costh2*ds2));
          hVtxPointSteps->Fill(pointVtxSteps);
          hVtxPointFOM->Fill(0.01*pointVtxFOM);

          hDirSimpleTheta->Fill(theta3);
          hDirPointTheta->Fill(theta4);
          hDirPointThetaZoom->Fill(theta4);
        }   

        if(extendedVtxFOM>0.0){
          hVtxExtendedPosition->Fill(0.01*(costh5*ds5),0.01*(sinth5*ds5));
          hVtxExtendedPositionProf->Fill(0.01*(costh5*ds5));
          hVtxExtendedPositionProfZoom->Fill(0.01*(costh5*ds5));
          hVtxExtendedFOM->Fill(0.01*extendedVtxFOM);
          hDirExtendedTheta->Fill(theta6);
          hVtxExtendedDelta->Fill(0.01*ds5);

          if( extendedVtxPass==1 ){
            hVtxExtendedPositionPass->Fill(0.01*(costh5*ds5),0.01*(sinth5*ds5));
            hVtxExtendedPositionPassProf->Fill(0.01*(costh5*ds5));
	  }  
     
          if( 0.01*extendedVtxZ<+27.5 ){
            hVtxExtendedR2->Fill( 0.01*0.01*(extendedVtxX*extendedVtxX+extendedVtxY*extendedVtxY) );
	  }

          if( 0.01*0.01*(extendedVtxX*extendedVtxX+extendedVtxY*extendedVtxY)<24.0*24.0 ){
            hVtxExtendedZ->Fill( 0.01*extendedVtxZ );
	  }

          ctr_extended_fit += 1.0;
          if( extendedVtxPass==1 ) ctr_extended_fit_pass += 1.0;
        }
      }

      // ring finder
      // ===========
      if( foundVertex && foundRings ){
        
        hDirRingTheta->Fill(theta7);

        hDirRingPulseHeightFrac->Fill(recoRingHeightFrac);

      }


    }

  }

  // Print Some Results
  if( ctr_extended_fit>0.0 ) ctr_extended_fit_pass_frac = ctr_extended_fit_pass/ctr_extended_fit;
  std::cout << " Number of fitted tracks [extended fit] = " << ctr_extended_fit << std::endl;
  std::cout << " Number of converged tracks [extended fit] = " << ctr_extended_fit_pass << std::endl;
  std::cout << "  Fraction of converged tracks [extended fit] = " << ctr_extended_fit_pass_frac << std::endl;


  TCanvas* cDigits = new TCanvas("cDigits","cDigits",775,850);
  hDigits->Draw();

  TCanvas* cDigitsZoom = new TCanvas("cDigitsZoom","cDigitsZoom",775,850);
  hDigitsZoom->Draw();

  TCanvas* cVertexR2  = new TCanvas("cVertexR2","cVertexR2",775,850);
  hVertexR2->Draw();
   
  TCanvas* cVertexPhi  = new TCanvas("cVertexPhi","cVertexPhi",775,850);
  hVertexPhi->Draw();

  TCanvas* cVertexZ  = new TCanvas("cVertexZ","cVertexZ",775,850);
  hVertexZ->Draw();
 
  TCanvas* cDirCosTheta  = new TCanvas("cDirCosTheta","cDirCosTheta",775,850);
  hDirCosTheta->Draw();

  TCanvas* cDirPhi  = new TCanvas("cDirPhi","cDirPhi",775,850);
  hDirPhi->Draw();



  TCanvas* cVtxSimplePosition = new TCanvas("cVtxSimplePosition","cVtxSimplePosition",900,500);
  hVtxSimplePosition->Draw();

  TCanvas* cVtxSimplePositionR2 = new TCanvas("cVtxSimplePositionR2","cVtxSimplePositionR2",900,500);
  hVtxSimplePositionR2->Draw();



  TCanvas* cVtxPointPosition = new TCanvas("cVtxPointPosition","cVtxPointPosition",900,500);
  hVtxPointPosition->Draw();  

  TCanvas* cVtxPointPositionProf = new TCanvas("cVtxPointPositionProf","cVtxPointPositionProf",900,500);
  hVtxPointPositionProf->Draw();  

  TCanvas* cVtxPointSteps = new TCanvas("cVtxPointSteps","cVtxPointSteps",850,800);
  hVtxPointSteps->Draw();

  TCanvas* cVtxPointFOM = new TCanvas("cVtxPointFOM","cVtxPointFOM",850,800);
  hVtxPointFOM->Draw();



  TCanvas* cDirSimpleTheta = new TCanvas("cDirSimpleTheta","cDirSimpleTheta",850,800);
  hDirSimpleTheta->Draw(); 

  TCanvas* cDirPointTheta = new TCanvas("cDirPointTheta","cDirPointTheta",850,800);
  hDirPointTheta->Draw(); 

  TCanvas* cDirPointThetaZoom = new TCanvas("cDirPointThetaZoom","cDirPointThetaZoom",850,800);
  hDirPointThetaZoom->Draw(); 


  
  TCanvas* cVtxExtendedZ = new TCanvas("cVtxExtendedZ","cVtxExtendedZ",650.0,850.0);
  hVtxExtendedZ->Draw();

  TCanvas* cVtxExtendedR2 = new TCanvas("cVtxExtendedR2","cVtxExtendedR2",650.0,850.0);
  hVtxExtendedR2->Draw();


  TCanvas* cVtxExtendedPosition = new TCanvas("cVtxExtendedPosition","cVtxExtendedPosition",900,500);
  hVtxExtendedPosition->Draw();   

  TCanvas* cVtxExtendedPositionProf = new TCanvas("cVtxExtendedPositionProf","cVtxExtendedPositionProf",900,500);
  hVtxExtendedPositionProf->Draw();  

  TCanvas* cVtxExtendedPositionProfZoom = new TCanvas("cVtxExtendedPositionProfZoom","cVtxExtendedPositionProfZoom",900,600);
  hVtxExtendedPositionProfZoom->Draw();  

  TCanvas* cVtxExtendedPositionPass = new TCanvas("cVtxExtendedPositionPass","cVtxExtendedPositionPass",900,500);
  hVtxExtendedPositionPass->Draw();   

  TCanvas* cVtxExtendedPositionPassProf = new TCanvas("cVtxExtendedPositionPassProf","cVtxExtendedPositionPassProf",900,500);
  hVtxExtendedPositionPassProf->Draw();   

  TCanvas* cVtxExtendedFOM = new TCanvas("cVtxExtendedFOM","cVtxExtendedFOM",850,800);
  hVtxExtendedFOM->Draw();  

  TCanvas* cDirExtendedTheta = new TCanvas("cDirExtendedTheta","cDirExtendedTheta",850,800);
  hDirExtendedTheta->Draw(); 

  TCanvas* cVtxExtendedDelta = new TCanvas("cVtxExtendedDelta","cVtxExtendedDelta",800,850);
  hVtxExtendedDelta->Draw();



  TCanvas* cDirRingTheta = new TCanvas("cDirRingTheta","cDirRingTheta",800,850);
  hDirRingTheta->Draw();

  TCanvas* cDirRingPulseHeightFrac = new TCanvas("cDirRingPulseHeightFrac","cDirRingPulseHeightFrac",800,850);
  hDirRingPulseHeightFrac->Draw();

}
