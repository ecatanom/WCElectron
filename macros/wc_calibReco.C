void wc_calibReco( TString filename, TString outFile ) // this is to do calibReco for event # ievent
{
  
  // Clear global scope
  //gROOT->Reset();
  // Path to WCSim ROOT file
  // =======================
  TString filename("/lbne/data/water/cosmic200kton20110518/rootfiles/cosmic_DUSEL_4850ft_surface_200kton.001.root");
  //TString filename("/lbne/data/water/atmos_cosmic6dec2010/cosmic_DUSEL_4850ft_fix_long_100kton.001.vec_0.root");
  //TString filename("/r01/lbne/water/wcsim_root_files_cosmic/DUSEL_200kton/cosmic_DUSEL_4850ft_surface_200kton.000.root");

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
  
  
  // Load Data
  // =========
  WCSimInterface::LoadData(filename.Data());


  // Lets set up my own output file
  //TFile *MyFile = new TFile("/lbne/app/users/gsdavies/calibReco_test.root","RECREATE");
  TFile *MyFile = new TFile(outFile,"RECREATE");
  if(MyFile->IsOpen()) std::cout <<" File opened successfully" << std::endl; 
  // Create an output TTree
  TTree *trkinfo = new TTree("trkinfo","Muon Track Information");
  // some truth information
  struct TruthInfo
  {
    Double_t event;
    Double_t momentum;
    Double_t trueVtxX;
    Double_t trueVtxY;
    Double_t trueVtxZ;
    Double_t trueVtxR;
    Double_t trueEndX;
    Double_t trueEndY;
    Double_t trueEndZ;
    Double_t trueDirX;
    Double_t trueDirY;
    Double_t trueDirZ;
    Double_t theta;
    Double_t phi;
  };

  TruthInfo TruthBit;
  trkinfo->Branch("Truth",&TruthBit,"event/D:momentum/D:trueVtxX/D:trueVtxY/D:trueVtxZ/D:trueR/D:trueEndX/D:trueEndY/D:trueEndZ/D:trueDirX/D:trueDirY/D:trueDirZ/D:theta/D:phi");
  
  // some PMT information  
  struct PMTInfo
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
  trkinfo->Branch("PMT",&PMTbit,"nPMT/D:totalQ/D:lowQ/D:highQ/D:firstT/D:lastT/D:nhits/D:ndigihits/D");

  // This is the output of my first pass reconstruction
  struct Reconstruction
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
  trkinfo->Branch("Reco",&Recobit,"tExitX/D:tExitY/D:tExitZ/D:ExitPhi/D:ExitT/D:theta/D:phi/D:residual/D:GoodHits/D:length/D");
  
  // muon truth info in ntuple form
  TNtuple *ntuple = new TNtuple("ntuple","","x_vtx:y_vtx:z_vtx:r_vtx:x_end:y_end:z_end:dcosx:dcosy:dcosz");
  
  //sorry I forgot to identify these, should be self explantory from the code
  TNtuple *ntuple2 = new TNtuple("ntuple2","","event:tube:x:y:z:phi:pe:distance:time");
  TNtuple *ntuple5=new TNtuple("ntuple5","","event:theta:phi:good:bad:residual:trklength");
  /*
    TNtuple *ntuple6 = new TNtuple("ntuple6","","event:x:y:z:pe:pe2:deltaT:deltaD");
    TNtuple *ntuple7 = new TNtuple("ntuple7","","event:x:y:z:pe:time:GoodHits");
*/  
  // Initialize Reconstruction
  // =========================
  WCSimReco* myReco = WCSimRecoFactory::Instance()->MakeReco();
  
  
  // Reconstruct Event
  // =================
  
  // get n'th entry
  //chain->GetEntry(ievent);
  Int_t nevent = WCSimInterface::GetNumEvents();
  // get first entry
  for (Int_t ev = 0; ev < nevent; ev++) {

    // load event 
    WCSimInterface::LoadEvent(ev); 
    WCSimRootEvent* myEvent = WCSimInterface::WCSimEvent();
    WCSimRootTrigger* myTrigger = WCSimInterface::WCSimTrigger();
    
    WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
    WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
    
    Int_t ncherenkovhits = myTrigger->GetNcherenkovhits();
    std::cout << "ncherenkovhits " << ncherenkovhits << std::endl;

    // run reconstruction
    myReco->Run(recoEvent);
    
    // get reconstructed quantities
    Double_t recoVtxX = recoEvent->GetVtxX();
    Double_t recoVtxY = recoEvent->GetVtxY();
    Double_t recoVtxZ = recoEvent->GetVtxZ();
    Double_t recoVtxR = WCSimMathUtil::pythag(recoEvent->GetVtxX(),recoEvent->GetVtxY());
    Double_t recoDirX = recoEvent->GetDirX();
    Double_t recoDirY = recoEvent->GetDirY();
    Double_t recoDirZ = recoEvent->GetDirZ();
    
    //ntuple->Fill( recoVtxX,recoVtxY,recoVtxZ,recoEndX,recoEndY,recoEndZ,recoDirX,recoDirY,recoDirZ )
    ntuple->Fill( recoVtxX,recoVtxY,recoVtxZ,recoVtxR,0.,0.,0.,recoDirX,recoDirY,recoDirZ );
    
    // Interface to MC Truth
    //======================
    
    // get true quantities
    TruthBit.trueVtxX = trueEvent->GetVtxX();
    TruthBit.trueVtxY = trueEvent->GetVtxY();
    TruthBit.trueVtxZ = trueEvent->GetVtxZ();
    TruthBit.trueVtxR = WCSimMathUtil::pythag(trueEvent->GetVtxX(),trueEvent->GetVtxY());
    TruthBit.trueEndX = trueEvent->GetEndX();
    TruthBit.trueEndY = trueEvent->GetEndY();
    TruthBit.trueEndZ = trueEvent->GetEndZ();  
    TruthBit.trueDirX = trueEvent->GetDirX();
    TruthBit.trueDirY = trueEvent->GetDirY();
    TruthBit.trueDirZ = trueEvent->GetDirZ();
    
    // want direction muon is coming from so do this calculation
    TruthBit.theta=acos(-TruthBit.trueDirZ)*180.0/TMath::Pi();
    TruthBit.phi=atan2(-TruthBit.trueDirY,-TruthBit.trueDirX)*180/TMath::Pi();
    if(TruthBit.phi<0) TruthBit.phi+=360;
    
    TruthBit.momentum=trueEvent->GetMomentum()/1000.0; // Convert to GeV
    std::cout <<" Track momentum is " << TruthBit.momentum << std::endl;
    
    std::cout << "  recoVtx=(" << recoVtxX << ", " << recoVtxY << ", " << recoVtxZ << std::endl
	      << "           " << recoDirX << ", " << recoDirY << ", " << recoDirZ << ") " << std::endl;
    
    std::cout << "  trueVtx=(" << TruthBit.trueVtxX << ", " << TruthBit.trueVtxY << ", " << TruthBit.trueVtxZ << ")" << std::endl
    	      << "  trueEnd=(" << TruthBit.trueEndX << ", " << TruthBit.trueEndY << ", " << TruthBit.trueEndZ << ")" << std::endl
	      << "  trueDir=(" << TruthBit.trueDirX << ", " << TruthBit.trueDirY << ", " << TruthBit.trueDirZ << ") and trueR = " << TruthBit.trueVtxR << std::endl;
    std::cout<<" Truth Theta: "<< TruthBit.theta << ", phi: " << TruthBit.phi << std::endl;
    //}
 
    //---------------------------------------------------------------------------------------
    // Get the number of Cherenkov hits.     
    
    WCSimGeometry* fGeometryHandle = WCSimGeometry::Instance();
    
    TClonesArray* fHitArray = (TClonesArray*)(myTrigger->GetCherenkovHits());
    //TClonesArray* fDigiHitArray = (TClonesArray*)(myTrigger->GetCherenkovDigiHits());
    
    // Grab the big arrays of times and parent IDs
    TClonesArray *fTimeArray = (TClonesArray*)(myTrigger->GetCherenkovHitTimes());
    
    PMTbit.nhits     = myTrigger->GetNcherenkovhits();
    std::cout << " NHITS " << PMTbit.nhits << std::endl;
    PMTbit.ndigihits = myTrigger->GetNcherenkovdigihits(); 
    
    Double_t TubesPosition[3];
    Double_t TubePosition[51199][3];
    Double_t IntersectionPoint[3];
    Double_t totalQ = 0.;
    Double_t totalPE = 0.;
    Double_t MaxPE = 0.;
    Double_t MaxPEaftCut = 0.;
    Double_t MaxQ   = 0.;
    PMTbit.lowQ = 10000.;
    PMTbit.highQ = 0.;
    PMTbit.firstT = 1000000.;
    PMTbit.lastT = 1000000.;
    Recobit.tExitX = -999.;
    Recobit.tExitY = -999.;
    Recobit.tExitZ = -999.;
    Recobit.ExitPhi = -999.;
    Recobit.ExitT = -999.;
    Int_t timeArrayIndex = 0;
    Int_t tubePE = 0;
    Double_t TubeTime[51199];
    
    
    
    // loop over Hits
    // ================
    Double_t EventStartT = 100000;
    Int_t HottestTube = 0;
    Int_t NTubeHits   = 0;
    
    //for( Int_t nDigit=0; nDigit<1+fDigiHitArray->GetLast(); nDigit++ ){
    for( Int_t nHit=0; nHit<PMTbit.nhits; nHit++ ){
      //WCSimRootCherenkovDigiHit* myDigit = (WCSimRootCherenkovDigiHit*)(fDigiHitArray->At(nDigit));
      WCSimRootCherenkovHit* myHit = (WCSimRootCherenkovHit*)(fHitArray->At(nHit));
      timeArrayIndex = myHit->GetTotalPe(0);
      tubePE         = myHit->GetTotalPe(1);
      //Double_t rawQ = myDigit->GetQ();
      //Double_t rawT = myDigit->GetT(); // can also use calQ, calT
      
      //Int_t tube = myDigit->GetTubeId();
      Int_t tube = myHit->GetTubeID();
      Int_t region = fGeometryHandle->GetRegion(tube);
      Double_t tubePosX = fGeometryHandle->GetX(tube);
      Double_t tubePosY = fGeometryHandle->GetY(tube);
      Double_t tubePosZ = fGeometryHandle->GetZ(tube);
      TubesPosition[0] = tubePosX;
      TubesPosition[1] = tubePosY;
      TubesPosition[2] = tubePosZ;
      
      
      Double_t phi = atan2(tubePosY,tubePosX);
      if(phi < 0. ) phi = (2*TMath::Pi())+phi;
      
      //Float_t EstimatedDistance = fGeometryHandle->DistanceToIntersectLine(TubesPosition,DetBit.StartPoint,DetBit.EndPoint,IntersectionPoint);
      //std::cout << "EstimatedDistance: " << EstimatedDistance << std::endl;
      // now we need to determine how far from the line it was
      // this is the "True case " 
      WCSimRootCherenkovHitTime*  myTime = (WCSimRootCherenkovHitTime*)(fTimeArray->At(timeArrayIndex));
      
      Double_t TrueT = myTime->GetTruetime();
      //      std::cout << "EventStartT, TrueT " << EventStartT << ", " << TrueT << std::endl;
      //std::cout << "TubePe: " << tubePE << std::endl; 
      if( (tubePE > 5.0) && (TrueT < EventStartT) ) EventStartT = TrueT;

      totalPE += tubePE;
      //std::cout << "lowQ, highQ " << PMTbit.lowQ << ", " << PMTbit.highQ << std::endl;
      if(tubePE < PMTbit.lowQ)  PMTbit.lowQ  = tubePE;
      if(tubePE > PMTbit.highQ) PMTbit.highQ  = tubePE;
      //std::cout << "lastT, firstT " << PMTbit.lastT << ", " << PMTbit.firstT << std::endl;
      TrueT = myTime->GetTruetime();
      if(TrueT > PMTbit.lastT)  PMTbit.lastT  = TrueT;
      if(TrueT < PMTbit.firstT) PMTbit.firstT = TrueT;
      if((tubePE > MaxPE) && ((TrueT - EventStartT) > 20)) {
	MaxPE           = tubePE;
	Recobit.tExitX  = tubePosX;
	Recobit.tExitY  = tubePosY;
	Recobit.tExitZ  = tubePosZ;
	Recobit.ExitPhi = phi;
	Recobit.ExitT   = TrueT;
      }
      // exit point is hit position (tube) with max energy deposition - want to use a weighted average
      
      
      //ntuple2->Fill(ev,tube,TubesPosition[0],TubesPosition[1],TubesPosition[2],phi,rawQ,EstimatedDistance,EstimatedT); // fill it before we change the TubesPosition values
      ntuple2->Fill(ev,tube,TubesPosition[0],TubesPosition[1],TubesPosition[2],phi,tubePE,0,TrueT); // fill it before we change the TubesPosition values
      //if(rawQ > 10.) { // data cleaning would remove this requirement
      
      
      if(tubePE > 5.) { // data cleaning would remove this requirement
	TubePosition[NTubeHits][0] = tubePosX;
	TubePosition[NTubeHits][1] = tubePosY;
	TubePosition[NTubeHits][2] = tubePosZ;
	//Double_t TrueTcut = 0.;
	TubeTime[NTubeHits] = myTime->GetTruetime();
	//if((rawQ > MaxQ) && ((TrueTcut - EventStartT) > 20)) {
        //MaxQ = rawQ;
	if((tubePE > MaxPEaftCut) && (fabs(TubeTime[NTubeHits] - EventStartT) > 20)) {
	  //MaxQ = rawQ;  
	  MaxPEaftCut = tubePE;
	  HottestTube = NTubeHits;
	  //HottestTube = tube;
	  std::cout << "HottestTube " << HottestTube << std::endl;
	}
	NTubeHits++;      
      } // tubePE > 10   
    } // end loop over digi hits
    //Double_t ToHotSpot = WCSimMathUtil::pythag((Recobit.tExitX - tubePosX),
	//				       (Recobit.tExitY - tubePosY),
	//				       (Recobit.tExitZ - tubePosZ));
    //t << "Distance to Hot Spot: " << ToHotSpot << std::endl;
    std::cout <<"Total Relevant Tubes = " << NTubeHits << std::endl;
    Recobit.theta = -9999;
    Recobit.phi   = -9999;
    Recobit.residual = 9999;
    Recobit.GoodHits = 0;
    std::cout << "Maximum PE: " << MaxPE << " (after cut: " << MaxPEaftCut << ") occurs at (" << Recobit.tExitX << "," << Recobit.tExitY << "," << Recobit.tExitZ << ")" << " at time " << Recobit.ExitT << std::endl;
    PMTbit.nPMT = NTubeHits;
    PMTbit.totalQ = totalPE;
    std::cout << "This event really begins at time: " << EventStartT << std::endl;
    //std::cout << "Enters  detector at " << LengthOf(TruthBit.trueVtxX,DetBit.StartPoint)/3E10 << std::endl;
    //std::cout << "Leaves detector at " << LengthOf(TruthBit.tVtx,DetBit.EndPoint)/3E10 << std::endl;
    
    //--------------------------------------------------------------------------------------------
    Double_t EndX, EndY, EndZ, StartX, StartY, StartZ;
    Double_t EndPos[3],StartPos[3];
    //EndX = fGeometryHandle->GetX(HottestTube);
    //EndY = fGeometryHandle->GetY(HottestTube);
    //EndZ = fGeometryHandle->GetZ(HottestTube);
    EndX = Recobit.tExitX;
    EndY = Recobit.tExitY;
    EndZ = Recobit.tExitZ;
    std::cout << "HottestTube " << HottestTube << std::endl;
    std::cout << "Setting End position to (" << EndX << "," << EndY << "," << EndZ << ")" << std::endl;
    
    // ---------------------------------------
    // now lets step over the theta and phi positions and see where that leads us
    // will get dcosx,dcosy,dcosz of the muon
    //
    // The minimization routine doesn't take into account how many PMTs are hit outside
    // the cerenkov cone...that would be useful info to include
    Double_t dcosx,dcosy,dcosz,dcosr;
    Double_t StartPhi   = 0.,EndPhi   = 360.;
    Double_t StartTheta = 0.,EndTheta = 90.;
    Double_t BestTheta  = 0.,BestPhi  = 0.,BestResidual = 0.,BestPMTs = 0.,BestTrkLength = 0.;
    // It is an iterative proces, first step over the data in a course manner
    // and then gradually zoom in..... this is what takes the longest time in the code
    // there has got to be some way to streamline or mathemitze it.
    
    
    for(Int_t iter = 0; iter < 1; iter++){
      Double_t StepPhi;
      Double_t StepTheta;
      if(iter==0) StepPhi = 2.0; StepTheta = 2.0;
      if(iter==1) StepPhi = 1.0;
      if(iter==2) StepPhi = 0.1;
      Double_t MinResidual = 1E10;
      
      for(Double_t phi = StartPhi; phi <= EndPhi; phi += StepPhi){
	//for(Double_t phi = StartPhi; phi <= 10; phi += StepSize){
	if(phi < 0.)   phi = 360. + phi;
	if(phi > 360.) phi = 360. - phi;
	// 0 degrees is straight down, 180 degrees is straight up
	if(StartTheta < 0) StartTheta = 0.;
	if(EndTheta > 180) EndTheta   = 180.;
	for(Double_t theta = StartTheta; theta <= EndTheta; theta += StepTheta){
	  // need to calculate directionality of this muon direction
	  dcosz = -cos(theta*TMath::Pi()/180.);
	  dcosr = sin(theta*TMath::Pi()/180.);
	  dcosx = -dcosr*cos(phi*TMath::Pi()/180.);
	  dcosy = -dcosr*sin(phi*TMath::Pi()/180.);
	  Bool_t InDetector=true;
	  // now we need to find point where it enters detector
	  StartX = -999;
	  StartY = -999;
	  StartZ = -999;
	  Double_t ThisPosX;
          Double_t ThisPosY;
          Double_t ThisPosZ;
	  ThisPosX = EndX;
	  ThisPosY = EndY;
	  ThisPosZ = EndZ;

	  // Brute force method to find the track entrance point
	  // can definately streamline this step to use pure maths
	  // 
	  while(true)
	    {
	      ThisPosX += (-dcosx);
	      ThisPosY += (-dcosy);
	      ThisPosZ += (-dcosz);
	      //std::cout << "x: " << ThisPosX << " y: " << ThisPosY << " z: " << ThisPosZ << std::endl;
	      // 200kton Height = 79.96m, 62.21m
	      if(fGeometryHandle->InsideDetector(ThisPosX, ThisPosY, ThisPosZ)==false) break;
	    }	    
	  StartX = ThisPosX;
	  StartY = ThisPosY;
	  StartZ = ThisPosZ;
	  //	  std::cout << "Startx: " << ThisPosX << " Starty: " << ThisPosY << " Startz: " << ThisPosZ << std::endl;	  
	  // a Track Length of 5 m should be enough to get useful information
	  // Assuming the Exit point calculation is correct, one can go through and calculate
	  // the timing residual of all hit PMTs (that project back to muon) 
	  StartPos[0] = StartX;
	  StartPos[1] = StartY;
	  StartPos[2] = StartZ;
	  EndPos[0]   = EndX;
	  EndPos[1]   = EndY;
	  EndPos[2]   = EndZ;
	  //std::cout << "StartX: " << StartX << "StartY: " << StartY << "StartZ: " << StartZ <<std::endl;
	  //	  std::cout << "EndX: " << EndX << "EndY: " << EndY << "EndZ: " << EndZ <<std::endl;
	  Double_t trkLength = WCSimMathUtil::pythag(StartX,StartY,StartZ,EndX,EndY,EndZ);
	  //	  std::cout << "Track length: " << trkLength << std::endl;
	  //std::cout << "I got here!!!!!!!!!!!!!!! "<<std::endl; 
	  if(trkLength > 500.){
	    // Now lets step over the valid tubes and see what I get
	    Int_t BadPoints  = 0;
	    Int_t GoodPoints = 0;
	    Double_t RunningResidual = 0.;
	    
	    for(Int_t pmt = 0; pmt < NTubeHits; pmt++){
	    //std::cout << "NTUBEHITS " << NTubeHits << std::endl;
	      Double_t Intersection[3];
	      Double_t PMTtoLine = fGeometryHandle->DistanceToIntersectLine(TubePosition[pmt],StartPos,EndPos,Intersection);
              //Double_t PMTtoLine = WCSimGeometry::DistanceToIntersectLine(TubesPosition[pmt][0],TubesPosition[pmt][1],TubesPosition[pmt][2],StartPos[0],StartPos[1],StartPos[2],EndPos[0],EndPos[1],EndPos[2],Intersection[0],Intersection[1],Intersection[2]);
	      //std::cout << "PMTtoLine " << PMTtoLine << std::endl;
	      if(PMTtoLine < 0.) BadPoints++;
	       
	      //Bool_t InsideCone = false;
	      Double_t Vector1[3];
	      Double_t Vector2[3];
	      WCSimMathUtil::SubtractVec(TubePosition[pmt],StartPos,Vector1);
	      WCSimMathUtil::SubtractVec(EndPos,StartPos,Vector2);
	      
	      Double_t dotty = WCSimMathUtil::DotProduct(Vector1,Vector2)/((WCSimMathUtil::pythag(StartX,StartY,StartZ,TubePosition[pmt][0],TubePosition[pmt][1],TubePosition[pmt][2]))*WCSimMathUtil::pythag(StartX,StartY,StartZ,EndX,EndY,EndZ));
	      //std::cout << "dotty " << dotty << std::endl;
	      if(dotty >= 0.9999) dotty = 0.99999;
	      Double_t PMTangle = (acos(dotty)*180)/TMath::Pi();
	      //std::cout << "PMTangle " << PMTangle << std::endl;
	      if((PMTtoLine > 0.) && (PMTangle < 50.) && (dotty > 0.)){
		Double_t MuonDistance = WCSimMathUtil::Magnitude(Intersection,TubePosition[HottestTube]);
		// convert to nanoseconds, note distances are in cm
		Double_t MuonTime = (MuonDistance/WCSimParameters::SpeedOfLight);
		Double_t PhotonTime = ((PMTtoLine*1.333)/WCSimParameters::SpeedOfLight);
		RunningResidual += fabs((MuonTime - PhotonTime) - (TubeTime[HottestTube] - TubeTime[pmt]));
		//std::cout << "RunningResidual " << RunningResidual << std::endl;
		//std::cout << "GoodPoints " << GoodPoints << std::endl;
		GoodPoints++;
	      }
	    } //for pmt
	    //std::cout << "BadPoints " << BadPoints << std::endl;
	    // identify direction with minimual residual
	    if((GoodPoints > 250) && (RunningResidual/GoodPoints < MinResidual) ){
	      MinResidual  = RunningResidual/GoodPoints;
	      BestTheta    = theta; 
	      BestPhi      = phi;
	      BestResidual = RunningResidual;
	      BestPMTs     = GoodPoints;
	      BestTrkLength = trkLength;	
	    }
	      ntuple5->Fill(ev,theta,phi,GoodPoints,BadPoints,RunningResidual,trkLength);
	  } //trklength cut
	}//theta
      }// phi
      std::cout << "Current best guess is: Theta = " << BestTheta << ", Phi = " << BestPhi << ", Track Length = " << BestTrkLength
		<< ". Good points = " << BestPMTs << std::endl;
	// reset the step size and bounds for the next loop
	
	if(iter==0){
	  StartTheta = BestTheta - 10.0;
	  EndTheta   = BestTheta + 10.0;
	  StartPhi   = BestPhi   - 10.0;
	  EndPhi     = BestPhi   + 10.0;
	  }
	  if(iter==1){
	  StartTheta = BestTheta - 1.0;
	  EndTheta   = BestTheta + 1.0;
	  StartPhi   = BestPhi   - 1.0;
	  EndPhi     = BestPhi   + 1.0;
	  }	  
    }// iter
      
      
      //save best fit info
    if(BestPMTs > 0){
      Recobit.residual = BestResidual;
      Recobit.GoodHits = BestPMTs;
      Recobit.theta    = BestTheta;
      Recobit.phi      = BestPhi;
      Recobit.length= BestTrkLength;
      std::cout <<"Best Fit Values of theta/phi " << BestTheta << " " << BestPhi 
		<< ", Track length: " << BestTrkLength << ", Residuals " << BestResidual/BestPMTs << std::endl;
    }
      // invert the muon direction to find exit point
      
      // require track to be longer than XX m ?
    trkinfo->Fill();
  } // end loop over events          
  ntuple->Write();
  ntuple2->Write();
  ntuple5->Write();
  trkinfo->Write();
  MyFile->Close(); 
}
