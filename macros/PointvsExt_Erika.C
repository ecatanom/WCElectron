{
  //Electron 
 
  // string namefile = "eminus_200kton_13per_MuSct_0p1";
  //string namefile = "addedFiles_electron_200kton_13percCov_0p25ns";
  //string namefile="031914_eminus_200kton_13per_05ns";
  //string namefile = "addedFiles_electron_200kton_13percCov_1p0ns";
  //string namefile = "addedFiles_electron_200kton_13percCov_1p5ns";
  //string namefile="032414_eminus_200kton_13per_2ns";

  //string namefile = "muon_400MeV_50kton_13percCov_0p1ns_Lmu_200cm_goodR";
  //string namefile = "addedFiles_electron_400MeV_200kton_13percCov_0p1ns";
  string namefile = "temp0";

  Double_t radius = 4202.59; Double_t height = 10412.1/2; //500 kton
  radius = 3112.95; height = 7998.09/2; //200 kton
  
  // True Quantities
  Int_t runNum;    Int_t eventNum;    Int_t triggerNum;

  Int_t truePDG;Double_t trueP;Double_t trueE;
  Double_t trueVtxX;Double_t trueVtxY;Double_t trueVtxZ;
  Double_t trueEndX;Double_t trueEndY;Double_t trueEndZ;
  Double_t trueDirX;Double_t trueDirY;Double_t trueDirZ;

  Int_t nDigits;Int_t nFilterDigits;Int_t foundVertex;Int_t foundDirection;

  Double_t recoVtxX;Double_t recoVtxY;Double_t recoVtxZ;
  Double_t recoVtxTime;Double_t recoVtxFOM;
  Double_t recoDirX;Double_t recoDirY;Double_t recoDirZ;

  // Testing Reconstruction
  
  Double_t pointVtxX;Double_t pointVtxY;Double_t pointVtxZ;
  Double_t pointVtxFOM;Int_t pointVtxSteps;Int_t pointVtxPass;
  Double_t pointDirX;Double_t pointDirY;Double_t pointDirZ;
  Double_t extendedVtxX;Double_t extendedVtxY;Double_t extendedVtxZ;
  Double_t extendedVtxFOM;Int_t extendedVtxSteps;Int_t extendedVtxPass;
  Double_t extendedDirX;Double_t extendedDirY;Double_t extendedDirZ;
  
  
  TChain* RecoChain = new TChain("ntuple","chain");

  //RecoChain->Add(("/lbne/data2/users/omanghel/electron_400MeV_200kton_13percCov_0p1ns/"+namefile+".root").c_str());
  //RecoChain->Add(("/lbne/data2/users/omanghel/muon_400MeV_200kton_13percCov_0p1ns/"+namefile+".root").c_str());
  RecoChain->Add(("/lbne/data2/users/omanghel/muon_400MeV_50kton_13percCov_0p1ns/"+namefile+".root").c_str());

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

 
  RecoChain->SetBranchAddress("pointVtxX",&pointVtxX);
  RecoChain->SetBranchAddress("pointVtxY",&pointVtxY);
  RecoChain->SetBranchAddress("pointVtxZ",&pointVtxZ);
  RecoChain->SetBranchAddress("pointVtxFOM",&pointVtxFOM);
  RecoChain->SetBranchAddress("pointVtxSteps",&pointVtxSteps);
  RecoChain->SetBranchAddress("pointVtxPass",&pointVtxPass);
 
  RecoChain->SetBranchAddress("pointDirX",&pointDirX);
  RecoChain->SetBranchAddress("pointDirY",&pointDirY);
  RecoChain->SetBranchAddress("pointDirZ",&pointDirZ);
 
  RecoChain->SetBranchAddress("extendedVtxX",&extendedVtxX);
  RecoChain->SetBranchAddress("extendedVtxY",&extendedVtxY);
  RecoChain->SetBranchAddress("extendedVtxZ",&extendedVtxZ);
  RecoChain->SetBranchAddress("extendedVtxFOM",&extendedVtxFOM);
  RecoChain->SetBranchAddress("extendedDirX",&extendedDirX);
  RecoChain->SetBranchAddress("extendedDirY",&extendedDirY);
  RecoChain->SetBranchAddress("extendedDirZ",&extendedDirZ);

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
  Double_t max = 300.0;   //100 for parallell?
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
  Double_t fiducial_in = 0.0; 
 
  Double_t drmax = -999.9;
 
  Int_t aaa = 0;
  Int_t bbb = 0;
  Int_t ccc = 0;

//Erika defined
  int temp_total=0;
  int passed_found=0;
  int passed_fiducial=0;
  int passed_point=0;
  int passed_extended=0;
  int help1=0;
  int help2=0;
  int help3=0;
  int WorseExtC=0; int WorseExtNC=0;

 //Erika
  TH2D* ParaPerpC = new TH2D("PPC","",200,0.0,600.0,200,0.0,250.0);
  TH2D* ParaPerpNC = new TH2D("PPNC","",200,0.0,600.0,200,0.0,250.0);
  //TH2D* ParaPerpNC = new TH2D("PPNC","",200,0.0,600.0,200,0.0,250.0);
  TH1D* TotalDistC = new TH1D("DC","",200,0,800);
  TH1D* TotalDistNC = new TH1D("DNC","",200,0,800);
  TH1D* NFilterDigitsC = new TH1D("NFDC","",100,0,12000);
  TH1D* NFilterDigitsNC = new TH1D("NFDNC","",100,0,12000);
  TH1D* NDigitsC = new TH1D("NDC","",100,0,12000);
  TH1D* NDigitsNC = new TH1D("NDNC","",100,0,12000);
  TH1D* PercFilteredC= new TH1D ("PerC","",100,0,100);
 TH1D* PercFilteredNC= new TH1D ("PerNC","",100,0,100);

 TH2D* DistPvEC = new TH2D ("DistPvEC","",200,0,3000.,200,0,3000.);
 TH2D* DistPvENC = new TH2D ("DistPvENC","",200,0,3000.,200,0,3000.);

 TH1D* ExtStepsC = new TH1D ("StepsC","",200,0.,1000.);
 TH1D* ExtStepsNC = new TH1D ("StepsNC","",200,0.,1000.);


  for( Int_t i=0; i<RecoChain->GetEntries(); i++ ){
    //for( Int_t i=0; i<100; i++ ){
    RecoChain->GetEntry(i);

    // fill histograms
    // ===============
    if( 1 ){

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

     

      //if( ds0!=0.0 ){
      //if( !foundVertex ) cout << eventNum << " ";//testconh->Fill(nFilterDigits);
      //else testnonh->Fill(ds0);
      //}
      //if( ds5*sqrt(costh5*costh5)>50.0 && extendedVtxPass ) cout << eventNum << " " ;//<< nDigits << " " << nFilterDigits << " " << ds0 << " " << DisttoWall << endl;
      if( drmax<dr1 ) drmax = dr1;
      
      if( !foundVertex && trueVtxZ>300.0 ) aaa++;
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
      
      if((dr2<radius-300.0) && (sqrt(pointVtxZ*pointVtxZ)<height-300.0)){
	fiducial_in++;	
	if(foundVertex){
	  ctr_extended_fit+=1;
	  if(extendedVtxPass==1){
	    ctr_extended_fit_pass +=1;
	   
	   //###############################################################################################
	   //##############Ioana.... change this to get the results for each direction#####################
	   //###############################################################################################
	   //testconh->Fill(ds5*sinth5); //perpendicular
	   testconh->Fill(ds5*sqrt(costh5*costh5)); //parallel
	    //testconh->Fill(ds5); //total
	    //testconh->Fill(theta6); //angular

	    //if(ds5*sinth5 < 1.0) cout << eventNum << " "; //goood results
	    

	    // ParaPerpC->Fill(ds2*(TMath::Abs(costh2)), ds2*sinth2);
	    //TotalDistC->Fill(ds2); 
	    ParaPerpC->Fill(ds5*(TMath::Abs(costh5)), ds5*sinth5);
	    TotalDistC->Fill(ds5);
	    //TotalDistC->Fill(ds5*sinth5); //perpendicular 030114
	    NFilterDigitsC->Fill(nFilterDigits);
	    NDigitsC->Fill(nDigits);
	    PercFilteredC->Fill((double)nFilterDigits/nDigits*100.);
	    DistPvEC->Fill(ds2,ds5);
	    ExtStepsC->Fill(extendedVtxSteps);
	    if (ds2<ds5) {//cout << "Extended worse than point but converged num "<< eventNum << "; " << ds2 << "; " << ds5 << endl;
	      WorseExtC++;}
	    //cout <<(double)nFilterDigits/nDigits*100. <<endl;
	    //cout << "point"<<ctr_extended_fit << ". " <<eventNum << " para " << ds2*costh2 << " perp " << ds2*sinth2<< endl;
	    //cout << ctr_extended_fit << ". " <<eventNum << " para " << ds5*sqrt(costh5*costh5) << " perp " << ds5*sinth5<<  " tot " << ds5<< endl;
	    //test2conh->Fill(DisttoWall,trueDirZ);
	    //testh->Fill(0.01*(TMath::Abs(costh5*ds5)));
	    //testh->Fill(0.01*ds5);
	    //testh->Fill(theta6);
          //if( ds5*sqrt(costh5*costh5)<2.0 ) cout << eventNum << " ";
	  }

	  
	  else {testnonh->Fill(ds0);
	    //ParaPerpNC->Fill(ds2*(TMath::Abs(costh2)), ds2*sinth2);
	    //TotalDistNC->Fill(ds2); 
	    ParaPerpNC->Fill(ds5*(TMath::Abs(costh5)), ds5*sinth5);
	    TotalDistNC->Fill(ds5);
	    //TotalDistNC->Fill(ds5*sinth5); //perpendicular 030114
	    NFilterDigitsNC->Fill(nFilterDigits);
	    NDigitsNC->Fill(nDigits);
	    PercFilteredNC->Fill((double)nFilterDigits/nDigits*100.);
	    DistPvENC->Fill(ds2,ds5);
	    ExtStepsNC->Fill(extendedVtxSteps);
	    if (ds2<ds5) {
	      // cout << "Extended worse than point not converged num "<< eventNum << "; " << ds2 << "; " << ds5 << endl; 
	      WorseExtNC++;}
	    if(1==1){

	      // cout <<eventNum <<" " ;

	       //cout << "else if(fCurrentEventN=="<<eventNum <<"){seedX=" <<extendedVtxX<<";seedY="<< extendedVtxY<<";seedZ=" <<extendedVtxZ<<"; seedDirX= "<<extendedDirX<<"; seedDirY= "<<extendedDirY<<"; seedDirZ= "<<extendedDirZ<<";} " << endl<<endl;
 }


	    //cout << "Failed" << eventNum << " " ;	
	  }
	  //else{ testnonh->Fill(coss); test2nonh->Fill(DisttoWall,trueDirZ); }
	  //else cout << eventNum << " " << extendedVtxPass << " " << ds0 << " " << ds5*(TMath::Abs(costh5)) << endl; }
	  //cout << eventNum << " " << extendedVtxPass << " " << ds0 << " " << ds5*(TMath::Abs(costh5)) << endl;
	  //}
	}
      }
      temp_total++;
      if (foundVertex) passed_found++;
      if (foundVertex && DisttoWall2>300) passed_fiducial++;
      if (!foundVertex && pointVtxPass) help1++;
      if (pointVtxPass && DisttoWall2>300) passed_point++;
      if (!foundVertex && extendedVtxPass) help2++;
      if (!pointVtxPass && extendedVtxPass) help3++;
      if (extendedVtxPass && DisttoWall2>300) passed_extended++;
    }

  }


  cout << endl << "**************************************" << endl;
   cout << "For " << namefile << endl;
  cout << "**************************************" << endl;
   cout << "Total events " << temp_total << endl;
  cout << "Found Vertex " << passed_found << endl;
  cout << "Found Vertex & Dist2>300 " << passed_fiducial << endl;  // Dist 2 refers to distance to the wall from point fit 
  cout << "Passed Point & Dist2>300 " << passed_point << endl; 
  cout << "Passed Exten & Dist2>300 " << passed_extended << endl;
  cout << "**************************************" << endl;
  cout << "Not passed found but passed point " << help1 << endl;
  cout << "Not passed found but passed extended " << help2 << endl;
  cout << "Not passed point but passed extended "<< help3 << endl;
  cout << "**************************************" << endl;
  cout << "Extended was worse than point but converged " << WorseExtC << endl;
  cout << "Extended was worse than point not converged " << WorseExtNC << endl;
  cout << "**************************************" << endl<<endl;

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
  //testconh->Draw();
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
  
  return;


// (ParaPerpC->GetXaxis())->SetTitle("para");
//   (ParaPerpC->GetYaxis())->SetTitle("perp");
//   ParaPerpC->SetMarkerStyle(24);
//   ParaPerpC->Draw(); 
//   ParaPerpNC->SetMarkerStyle(31);
//   ParaPerpNC->SetMarkerColor(kRed);
//   ParaPerpNC->Draw("same");
//   leg=new TLegend(0.65,0.75,0.9,0.9,"");
//   leg->AddEntry(PPC,"Convergent","p");
//   leg->AddEntry(PPNC,"Not Convergent","p");
//   leg->Draw();


//   TCanvas *ca2 = new TCanvas("ca2","",800,600); 
//   (TotalDistC->GetXaxis())->SetTitle("Norm(true-ext)");
//   (TotalDistC->GetYaxis())->SetTitle("NoEvents");
//   TotalDistC->Draw();
//   TotalDistNC->SetLineColor(kRed);
//   TotalDistNC->Draw("same");
//   leg2=new TLegend(0.65,0.75,0.9,0.9,"");
//   leg2->AddEntry(DC,"Convergent","l");
//   leg2->AddEntry(DNC,"Not Convergent","l");
//   leg2->Draw();

   Double_t xbins[9]={0.,5.,10,20,30,50,100,200,800};
  
  TCanvas *ca2 = new TCanvas("ca2","",800,600); 
  (TotalDistC->GetXaxis())->SetTitle("Norm(true-ext)");
  (TotalDistC->GetYaxis())->SetTitle("NoEvents");
  TotalDistC->DrawNormalized();
  TotalDistNC->SetLineColor(kRed);
  //TotalDistNC->Rebin(10);
  TotalDistNC->DrawNormalized("same");
  
  leg2=new TLegend(0.65,0.75,0.9,0.9,"");
  leg2->AddEntry(DC,"Convergent","l");
  leg2->AddEntry(DNC,"Not Convergent","l");
  leg2->Draw();

//  TCanvas *ca3 = new TCanvas("ca3","ca3",800,600); 
//  (NFilterDigitsC->GetXaxis())->SetTitle("NFilterDigits");
//  (NFilterDigitsC->GetYaxis())->SetTitle("NoEvents");
//  NFilterDigitsC->Draw();
//  NFilterDigitsNC->SetLineColor(kRed);
//  NFilterDigitsNC->Draw("same");

//  TCanvas *ca4 = new TCanvas("ca4","ca4",800,600); 
//  (NDigitsC->GetXaxis())->SetTitle("NDigits");
//  (NDigitsC->GetYaxis())->SetTitle("NoEvents");
//  NDigitsC->Draw();
//  NDigitsNC->SetLineColor(kRed);
//  NDigitsNC->Draw("same");

//  TCanvas *ca5 = new TCanvas("ca5","ca5",800,600); 
//  (PercFilteredC->GetXaxis())->SetTitle("PercentageFiltered");
//  (PercFilteredC->GetYaxis())->SetTitle("NoEvents");
//  PercFilteredC->Draw();
//  PercFilteredNC->SetLineColor(kRed);
//  PercFilteredNC->Draw("same");

 TCanvas *ca6 = new TCanvas("ca6","ca6",800,600); 
(DistPvEC->GetXaxis())->SetTitle("Dist to true, PointVtx");
  (DistPvEC->GetYaxis())->SetTitle("Dist to True, ExtVtx");
  DistPvEC->SetMarkerStyle(24);
  DistPvEC->Draw(); 
  DistPvENC->SetMarkerStyle(31);
  DistPvENC->SetMarkerColor(kRed);
  DistPvENC->Draw("same");

  leg=new TLegend(0.65,0.75,0.9,0.9,"");
  leg->AddEntry(DistPvEC,"Convergent","p");
  leg->AddEntry(DistPvENC,"Not Convergent","p");
  leg->Draw();
TLine *line =new TLine (0,0,3000,3000);
line->SetLineColor(kBlue);
 line->SetLineWidth(2);
  line->Draw();




  

 TCanvas *ca7 = new TCanvas("ca7","ca7",800,600); 
  TotalDistC->Rebin(8,"newhC",xbins);
  TotalDistNC->Rebin(8,"newhNC",xbins);
  
  TH1D * thenewh = new TH1D("thenew","",8,0,8);
  TH1D * thenewhNC = new TH1D("thenewNC","",8,0,8);
  for (int kk=1;kk<10;kk++)
    { thenewh ->SetBinContent(kk,newhC->GetBinContent(kk));
      thenewhNC ->SetBinContent(kk,newhNC->GetBinContent(kk));
    }
 (thenewh->GetXaxis())->SetBinLabel(1,"0-5");
(thenewh->GetXaxis())->SetBinLabel(2,"5-10");
(thenewh->GetXaxis())->SetBinLabel(3,"10-20");
(thenewh->GetXaxis())->SetBinLabel(4,"20-30");
(thenewh->GetXaxis())->SetBinLabel(5,"30-50");
(thenewh->GetXaxis())->SetBinLabel(6,"50-100");
(thenewh->GetXaxis())->SetBinLabel(7,"100-200");
(thenewh->GetXaxis())->SetBinLabel(8,"200+");
 
(thenewh->GetXaxis())->SetTitle("Vertex Resolution, Total [cm]");
// (thenewh->GetXaxis())->SetTitle("Vertex Resolution, Perpendicular [cm]"); //030114
 (thenewh->GetYaxis())->SetTitle("No Events");
  thenewhNC->SetLineColor(kRed);
    thenewh->Draw();
   thenewhNC->Draw("same");

//  (thenewh->GetYaxis())->SetTitle("Fraction of events");
//  thenewh->DrawNormalized();
//  thenewhNC->DrawNormalized("same");//


//  TCanvas *ca8 = new TCanvas("ca8","ca8",800,600); 
//  (ExtStepsC->GetXaxis())->SetTitle("Steps");
//  (ExtStepsC->GetYaxis())->SetTitle("NoEvents");
//  ExtStepsC->Draw();
//  ExtStepsNC->SetLineColor(kRed);
//  ExtStepsNC->Draw("same");





}


