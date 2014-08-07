{
  // Load libraries
  // ==============
  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot.so");
  gSystem->Load("libWCSimAnalysis.so");
  
  // Path to WCSim ROOT file
  // ======================= 
  
TString filename("/lbne/data/water/sim200kton_20111017/singleparticle/wcsimlc/muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_MuSct_Ion.root");
 


  // Load Data
  // =========
  WCSimInterface::LoadData(filename);

  // get first entry
  Bool_t truehit = 1; // 1 is to use true hits
  Bool_t filtered = 1; // 1 is to use Andy's cut
  Bool_t Lmu = 0; // 1 is to use LMuon cut
  Double_t sigma0 = 1.0; //sigma0 = 0.1; //1 ns
  if(truehit) {WCSimInterface::SetToUseTrueHits();
    WCSimInterface::Instance()->SmearTrueHits(sigma0);} //Smear sigma0=1ns, we are talking about MCP

  WCSimDataCleaner::Instance()->SetMinPulseHeight(-1.0);//there's no cut
  WCSimDataCleaner::Instance()->SetNeighbourRadius(300.0); //cm
  WCSimDataCleaner::Instance()->SetNeighbourDigits(50.0);//number of neighb
  WCSimDataCleaner::Instance()->SetClusterRadius(300.0);
  WCSimDataCleaner::Instance()->SetClusterDigits(50.0);//at least 50 clusters
  WCSimDataCleaner::Instance()->SetTimeWindowNeighbours(25.0);//ns window
  WCSimDataCleaner::Instance()->SetTimeWindowClusters(25.0);

  WCSimInterface::Instance()->SetToMCP();//
  //WCSimInterface::Instance()->SetToGated();//use PMT
  //both commented is using ungated PMT

  //for(Int_t a=0;a<1000;a++ ){
  WCSimInterface::LoadEvent(118);

  //cout << sin(90.0) << endl;
  Bool_t drawd = 1; // 1 is to draw the distance plot at the end
  if(drawd){//dist traveled by photon
    double mind = 0.0;
    double maxd = 900.0;
  }
  else{
    double mind = 1500.0;
    double maxd = 5500.0;
  }
  double mindmu = -500.0;//dist muon
  double maxdmu = 1500.0;
  int nbin = 20;
  TH1D* h1 = new TH1D("h1", "",500,-10.0,90.0);
  TH1D* h2 = new TH1D("h2", "",400,20.0,60.0);
  TH1D* h3 = new TH1D("h3", "",500,0.0,900.0);
  TH1D* h4 = new TH1D("h4", "",200,mindmu,maxdmu);
  TH1D* h5 = new TH1D("h5", "",200,mindmu,maxdmu);
  TH1D* Prob = new TH1D("Prob","",500,-10.0,40.0);
  TH1D* diff = new TH1D("diff","",1500,-50.,250.);
  TH1D *dphot = new TH1D("dphot", "",nbin,mind,maxd);
  TH1D *dphot2 = new TH1D("dphot2", "", 20, mind, maxd);
  TH2D *d = new TH2D("d","", 200, mindmu, maxdmu,400,20.0,60.0);
  TH2D *d2 = new TH2D("d2","", 400, 20.0, 60.0, 600, -10.0, 50.0);
  TH2D *d3 = new TH2D("d3","", 200, mindmu, maxdmu,600,-10.0,50.0);
  Double_t TResid, LPhot, LMuon, Oangle;
  double bdeltaT, rdeltaT;
  // build event
  // WCSimInterface::BuildEvent(myEvent);
  WCSimTrueEvent* trueEvent = WCSimInterface::TrueEvent();
  WCSimRecoEvent* recoEvent = WCSimInterface::RecoEvent();
  //
  WCSimRecoAB* haReco = new WCSimRecoAB(); //run filters
  if(filtered) haReco->RunFilter(recoEvent);

  int myNdigits = recoEvent->GetNDigits();
  int NFilterdigits = recoEvent->GetNFilterDigits();

  double *index1 = new double[NFilterdigits];
  double *index2 = new double[NFilterdigits];
  double *index3 = new double[NFilterdigits];
  double *index4 = new double[NFilterdigits];
  double *index5 = new double[NFilterdigits];
  // get true quantities
  Double_t trueX = trueEvent->GetVtxX();
  Double_t trueY = trueEvent->GetVtxY();
  Double_t trueZ = trueEvent->GetVtxZ(); 
  Double_t dirX = trueEvent->GetDirX();
  Double_t dirY = trueEvent->GetDirY();
  Double_t dirZ = trueEvent->GetDirZ();
  Double_t trueT = 0.0;
  double theta = (TMath::Pi())/2.0 - atan(dirZ/sqrt(dirX*dirX+dirY*dirY)); //theta = theta + 3.0/41.0;
  double phi = 0.0;
  if( dirX<0.0 ) phi = TMath::Pi() - asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY>0.0 ) phi = asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  else if( dirY<0.0 ) phi = 2.0*TMath::Pi() + asin(dirY/sqrt(dirX*dirX+dirY*dirY));
  //else( dirY=0.0 ) phi = 0.0;
  dirX = cos(phi)*sin(theta);
  dirY = sin(phi)*sin(theta);
  dirZ = cos(theta);
  //trueX = 1569.0;
  //double size = 500.0;
  //trueX = 1530.0;
  //trueY = trueY + size*dirY;
  //trueZ = trueZ + size*dirZ;
  //Double_t j = -5.0;
  //Double_t size = 50.0/21.0;
  //trueX = trueX + j*dirX*size;
  //trueY = trueY + j*dirY*size;
  //trueZ = trueZ + j*dirZ*size;


  //phenomenology... water model: class that contains index of refraction, attenuation (lambda), initial spectrum, etc. How photon travels through water
  WCSimWaterModel *wm2 = WCSimWaterModel::Instance();
  WCSimTResidPDF *pdf = WCSimTResidPDF::Instance();//dont use this :p

  Double_t Norm       = 10.0;
  Double_t softcutoff = 500.0;
  Double_t earlysigma = 2.0/sqrt(Norm); // P(l=-20cm)=0.01
  Double_t latesigma  = 5.0; latesigma = 25.0/(10.0*sqrt(Norm)); // P(l=525cm)=0.01
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);

  int ifilter = 0;
  for(int i=0; i<myNdigits; i++){

   WCSimRecoDigit* adigit = recoEvent->GetDigit(i);
   if( adigit->IsFiltered() || !filtered ){ //if the hit passed the filter
    double hitX = adigit->GetX();
    double hitY = adigit->GetY();
    double hitZ = adigit->GetZ();
    double hitT = adigit->GetTime();
    double qpes = adigit->GetQPEs();//charge
    double res = WCSimParameters::TimeResolution(qpes); 

     WCSimVertexGeometry::CalcTResid(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle); 
     //cout << TResid << " ";
     double Ptemp = pdf->MakeChromPeakPDF(TResid,LPhot,sigma0); 
     double Plmutmp = Norm;
     if( LMuon<0.0 ) Plmutmp = Norm/(1.0+(LMuon*LMuon)/(earlysigma*earlysigma));
     else if( LMuon<softcutoff ) Plmutmp=Norm;
     else Plmutmp=Norm/(1.0+((LMuon-softcutoff)*(LMuon-softcutoff)/(latesigma*latesigma)));
//     double dt = TResid + LPhot*1.333/29.9792;
//     double dtt = LPhot/29.9792;
//     double ds = sqrt(dt*dt - dtt*dtt);
//     cout << dt << " " << dtt << " " << ds << endl;
//     h3->Fill(ds);
//     h2->Fill(Oangle);
//     h5->Fill(LMuon);
//     h3->Fill(TResid, (Ptemp*Plmutmp));
//     d->Fill(LMuon,Oangle);
//     d2->Fill(Oangle,TResid);
//     d3->Fill(LMuon,TResid);

     double tmpLmuon = LMuon;
     double tmpLphot = LPhot;
     double tmpDeltat = TResid;
     double tmpChere = 0.73267;
     double Energy = 1200.0;
     for( int jj=0;jj<20;jj++ ){
       double color = 200.0 + (jj+0.5)*25.0;
       double velo = wm2->Vg(color);
       double vmu = 29.9792; 
       tmpChere = acos(velo/vmu);
       tmpLmuon = LMuon + LPhot*sin(tmpChere - 0.73267)/sin(tmpChere);
       tmpLphot = LPhot*sin(0.73267)/sin(tmpChere);
/*       for( int k=0;k<5;k++ ){
          vmu = 27.9792 + 2.0/(exp((tmpLmuon-200.0)/100.0)+1.0);
          tmpChere = acos(velo/vmu);
          tmpLmuon = LMuon + LPhot*sin(tmpChere - 0.73267)/sin(tmpChere);
          tmpLphot = LPhot*sin(0.73267)/sin(tmpChere);
          if( i==2374 && jj==4 ){
            cout << " Vmu: " << 29.9792 << " " << vmu << endl;
            cout << " Cangle: " << 0.7342 << " " << tmpChere << endl;
            cout << " Lmuon: " << LMuon << " " << tmpLmuon << endl;
          }
       }
*/
//       tmpChere = acos(velo/vmu);
//       tmpLmuon = LMuon + LPhot*sin(tmpChere - 0.73267)/sin(tmpChere);
//       tmpLphot = LPhot*sin(0.73267)/sin(tmpChere);
       tmpDeltat = TResid + (1.333*LPhot/29.9792 - LPhot/velo);
       double P2 = wm2->FinlSpect(color,LPhot); 
//       tmpDeltat = TResid + (1.333*LPhot/29.9792 - tmpLphot/velo);//+(LMuon/29.9792-tmpLmuon/vmu);
//       double P2 = pdf->MakeChromPeakPDF(tmpDeltat,tmpLphot,sigma0); 
       //double Plmu2 = Norm;
       //if( tmpLmuon<0.0 ) Plmu2 = Norm/(1.0+(tmpLmuon*tmpLmuon)/(earlysigma*earlysigma));
       //else if( tmpLmuon<softcutoff ) Plmu2=Norm;
       //else Plmu2=Norm/(1.0+((tmpLmuon-softcutoff)*(tmpLmuon-softcutoff)/(latesigma*latesigma)));
       h4->Fill(LMuon,P2);
       d->Fill(LMuon,Oangle, P2);
       d2->Fill(Oangle,tmpDeltat, P2);
       d3->Fill(LMuon,tmpDeltat, P2);
       h1->Fill(tmpDeltat);
       h2->Fill(Oangle);
       h5->Fill(LMuon);
       //d2->Fill(tmpLmuon,tmpDeltat,P2);
       //if( tmpLmuon<100.0 && TResid<1.0 ){
       //cout << color << " Cangle: " << 0.73267 << " " << tmpChere << endl;
       //cout << color << " Lphoto: " << LPhot << " " << tmpLphot <<endl;
       //cout << color << " LMuon:  " << LMuon << " " << tmpLmuon <<endl;
       //cout << color << " Deltat: " << TResid << " " << tmpDeltat <<endl;
       //}
     }
     
     ifilter++; 
    } //loop of the filter
  } //loop over hits
  //} // loop over events
  cout << "WCSim" << endl;
//================ calculate chi2 ========================================
  //double rms = TMath::RMS(NFilterdigits,index1); cout << rms << " ";
  //double rms = TMath::RMS(NFilterdigits,index2); cout << rms << " ";
  //double rms = TMath::RMS(NFilterdigits,index3); cout << rms << " ";
  //double rms = TMath::RMS(NFilterdigits,index4); cout << rms << " ";
  //double rms = TMath::RMS(NFilterdigits,index5); cout << rms << endl;
//======================================================================================
//PDF
/*  if( !drawd ){

  Double_t delta, dist, distmu;
  Double_t Preal, Norm, weight, Pgauss,Plmu;
  for( Int_t jj=0;jj<500;jj++ ){
     delta = 0.2*(jj+0.5) - 10.0;
     Preal = 0.0; 
     Norm = 0.0;
     for( Int_t ii=0;ii<nbin;ii++ ){
        dist = (ii+0.5)*(maxd-mind)/nbin+mind;
          for( Int_t kk=0;kk<nbin;kk++ ){
             distmu = (kk+0.5)*(maxdmu-mindmu)/nbin + mindmu; //sigma0 = 0.4247*sigma0;
             Pgauss = pdf->MakeChromPeakPDF(delta,dist,sigma0); 
             //Pgauss = pdf->MakeChromPeakPDFEnergy(delta,dist,sigma0); 
             weight = (Double_t)d->GetBinContent(ii,kk);	
             //weight = (Double_t)dphot->GetBinContent(ii);	
	
	     if( distmu<0.0 ) Plmu=Norm/(1.0+(distmu*distmu)/(earlysigma*earlysigma));
	     else if( distmu<softcutoff ) Plmu=Norm;
	     else Plmu=Norm/(1.0+((distmu-softcutoff)*(distmu-softcutoff)/(latesigma*latesigma)));
             Norm += weight;
	     Preal += weight*Pgauss*Plmu;
          }
     }
     if( Norm != 0.0) Preal = Preal/Norm; 
     h2->Fill(delta, Preal);
  }
  }
  std::cout << "PDF" << std::endl;
*/
//============================================================================================
  double norm2 = h3->Integral();
  double norm1 = h1->Integral();
  //h2->Scale(norm1/norm2);
  //norm2 = h3->Integral();
  //h3->Scale(0.7*norm1/norm2);
  norm1 = h5->Integral();
  norm2 = h4->Integral();
  h4->Scale(norm1/norm2);
  norm1 = d->Integral();
  norm2 = d2->Integral();
  d->Scale(norm2/norm1);
  cout << norm1 << " " << norm2 << endl;
  /*Double_t haha = h1->Integral();
  h1->Scale(1.0/haha);
  Prob->Scale(jiji);
  for(int k=0;k<1000;k++){
    double t = 0.2*(k+0.5)-50.0;
    double tr = h1->GetBinContent(k);
    double pp = Prob->GetBinContent(k);
    double ndf = sqrt(tr);
    if(ndf != 0.0 ) diff->SetBinContent(k, (tr-pp)/ndf);
  }*/
//============================================================================================
  /*Prob->SetLineColor(kBlue); Prob->SetLineWidth(2.5);
  (diff->GetXaxis())->SetTitle("Time Residual (ns)");
  (diff->GetYaxis())->SetTitle("(TResid-PDF)/sqrt(TResid)");*/
  //TCanvas* can2 = new TCanvas("can2","",500,800);
  //can2->Divide(1,2);
  //can2->cd(1);
  //TLegend *mylegend3 = new TLegend(0.6,0.7,0.9,0.9,"");
  //mylegend3->AddEntry(Prob, "ChromPDF", "l");
  //mylegend3->Draw();
  d->SetMarkerSize(0.3); //d->Draw();
  (d->GetXaxis())->SetTitle("muon distance [cm]");
  (d->GetYaxis())->SetTitle("open angle [degree]");
  //(d->GetYaxis())->SetTitle("time residual [ns]");
  d2->SetMarkerSize(0.3);
  (d2->GetXaxis())->SetTitle("open angle [degree]");
  (d2->GetYaxis())->SetTitle("time residual [ns]");
  d3->SetMarkerSize(0.3); 
  (d3->GetXaxis())->SetTitle("muon distance [cm]");
  (d3->GetYaxis())->SetTitle("time residual [ns]");
  (h5->GetYaxis())->SetTitle("Events");
  (h5->GetXaxis())->SetTitle("muon distance [cm]");
  //h1->SetLineColor(kRed); 
  h1->SetLineWidth(1.5); 
  (h1->GetXaxis())->SetTitle("time residual [ns]");
  (h1->GetYaxis())->SetTitle("Events");
  h2->SetLineColor(kBlue); 
  h2->SetLineWidth(1.5);
  (h2->GetXaxis())->SetTitle("open angle [degree]");
  (h2->GetYaxis())->SetTitle("Events");
  h3->SetLineColor(kRed); h3->SetLineWidth(1.5);
  h4->SetLineColor(kBlue); h4->SetLineWidth(2.0);
  h5->SetLineColor(kRed+1); 
  h5->SetLineWidth(1.5);
  //dphot->Draw();

  TCanvas *ca1 = new TCanvas("ca1","",400,900);
  ca1->Divide(1,3);
  ca1->cd(1);
  h1->Draw(); 
  ca1->cd(2);
  h2->Draw();
  ca1->cd(3);
  h5->Draw();
  //if( drawd ){ d->Draw(); }
  //else{ h1->Draw(); Prob->Draw("Same"); }//h3->Draw("Same"); //h4->Draw("Same"); h5->Draw("Same"); }
  //else{ h1->Draw(); h2->Draw("Same"); h3->Draw("Same");}

  TCanvas *ca5 = new TCanvas("ca5","",400,900);
  ca5->Divide(1,3);
  ca5->cd(1);
  d->Draw("col"); 
  ca5->cd(2);
  d2->Draw("col");
  ca5->cd(3);
  d3->Draw("col");

  TCanvas *ca2 = new TCanvas("ca2","",400,300);
  ca2->cd();
  h3->Draw(); //h3->Draw("Same");
  //h2->Draw();

  TCanvas *ca3 = new TCanvas("ca3","",400,300);
  ca3->cd();
  d->Draw("col");

  TCanvas *ca4 = new TCanvas("ca4","",400,300);
  ca4->cd();
  d2->Draw("col");

  TLegend *mylegend = new TLegend(0.5,0.75,0.9,0.9,"");
  mylegend->AddEntry(h1, "time residual spectrum", "l");
  mylegend->AddEntry(h2, "PDF", "l");
  mylegend->AddEntry(h3, "likelihood distribution", "l");
  mylegend->Draw();
  cout << "digits: " << myNdigits << " filter digits: " << NFilterdigits << endl;


  //if(drawd){ dphot2->SetLineColor(kRed); dphot->SetLineWidth(2.0); dphot2->SetLineWidth(2.0); dphot->Draw(); dphot2->Draw("Same"); mylegend3->Draw(); }
  
 
}
