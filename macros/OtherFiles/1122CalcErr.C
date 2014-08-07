{
  
  string namefile = "500ktonpartial";
  //string namefile= "300k01nsntple";
  //string namefile = "01nsntuple";
  //string namefile = "200kton_01ns";

  Double_t radius = 3112.95; //3168.94 for 1200MeV, 3112.95 for 400MeV
  Double_t height = 3999.04; //3833.94 for 1200MeV, 3999.04 for 400MeV

  //radius = 1953.8 ; height = 6012.09/2; //50 kton
  //radius = 2413.36; height = 6898.09/2; //100 kton
  //radius = 3112.95; height = 7998.09/2; //200 kton
  //radius = 3612.76; height = 8898.09/2; //300 kton
  radius = 4202.59; height = 10412.1/2; //500 kton

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
  
  Double_t pointVtxX;
  Double_t pointVtxY;
  Double_t pointVtxZ;
  Double_t pointVtxFOM;
  Int_t pointVtxSteps;
  Int_t pointVtxPass;
  Double_t pointDirX;
  Double_t pointDirY;
  Double_t pointDirZ;
  Double_t extendedVtxX;
  Double_t extendedVtxY;
  Double_t extendedVtxZ;
  Double_t extendedVtxFOM;
  Double_t extendedDirX;
  Double_t extendedDirY;
  Double_t extendedDirZ;
  Int_t extendedVtxSteps;
  Int_t extendedVtxPass;
  

 

  TChain* RecoChain = new TChain("ntuple","chain");

  RecoChain->Add(("/lbne/data/users/ecatanom/oct13muonntuples/"+namefile+".root").c_str());

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
  Double_t max = 100.0;   //100 for parallell?
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
      //cout << costh0 << " " << coss << " " << side << endl;
      // vertex finder
      // =============
     // //  if( foundVertex && DisttoWall2>300.0 ){
// // 	//if( foundVertex ){
// //         ctr_extended_fit += 1.0;

// //         if( extendedVtxPass==1 ){
// //           ctr_extended_fit_pass += 1.0;

    

    
      //cout << dr2 << " " << pointVtxZ << endl;
      if((dr2<radius-300.0) && (sqrt(pointVtxZ*pointVtxZ)<height-300.0)){
	fiducial_in++;	
	if(foundVertex){
	  ctr_extended_fit+=1;
	  if(extendedVtxPass==1){
	    ctr_extended_fit_pass +=1;
	    //ArrExtendedPara[i] = TMath::Abs(0.01*(costh5*ds5));
	    //ArrExtendedPerp[i] = 0.01*(sinth5*ds5);
	    //ArrExtendedAngle[i] = theta6;
	    //ArrExtendedDelta[i] = 0.01*ds5;
	    //if( ds5*sqrt(costh5*costh5)>25.0 ) testconh->Fill(coss);
	    
	    //testconh->Fill(ds5*sinth5); 
	    //testconh->Fill(ds5*sqrt(costh5*costh5));
	    testconh->Fill(ds5);
	    //testconh->Fill(theta6);
	    

	  //cout << "point"<<ctr_extended_fit << ". " <<eventNum << " para " << ds2*costh2 << " perp " << ds2*sinth2<< endl;
	  //cout << ctr_extended_fit << ". " <<eventNum << " para " << ds5*sqrt(costh5*costh5) << " perp " << ds5*sinth5<<  " tot " << ds5<< endl;
          //test2conh->Fill(DisttoWall,trueDirZ);
          //testh->Fill(0.01*(TMath::Abs(costh5*ds5)));
          //testh->Fill(0.01*ds5);
          //testh->Fill(theta6);
          //if( ds5*sqrt(costh5*costh5)<2.0 ) cout << eventNum << " ";
	  }
	  else {testnonh->Fill(ds0);
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
  cout << "Not passed point but passed extended "<< help3 << endl << endl;

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
  

}
