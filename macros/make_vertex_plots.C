{
  
  Int_t run;
  Int_t event;
  Int_t trigger;
  Double_t vtxX;
  Double_t vtxY;
  Double_t vtxZ;
  Double_t vtxTime;
  Int_t index;
  Int_t last;
  Double_t digitX;
  Double_t digitY;
  Double_t digitZ;
  Double_t digitT;
  Double_t digitQ;
  Double_t deltaT;
  Double_t deltaR;
  Double_t deltaTrack;
  Double_t deltaPhoton;
  Double_t delta;
  Double_t deltaAngle;
  Double_t deltaWeight;
  Double_t deltaDeweight;

  TChain* fRecoChain = new TChain("ntuple","chain");
  fRecoChain->SetBranchAddress("run",&run);
  fRecoChain->SetBranchAddress("event",&event);
  fRecoChain->SetBranchAddress("trigger",&trigger);
  fRecoChain->SetBranchAddress("vtxX",&vtxX);
  fRecoChain->SetBranchAddress("vtxY",&vtxY);
  fRecoChain->SetBranchAddress("vtxZ",&vtxZ);
  fRecoChain->SetBranchAddress("vtxTime",&vtxTime);
  fRecoChain->SetBranchAddress("index",&index);
  fRecoChain->SetBranchAddress("last",&last);
  fRecoChain->SetBranchAddress("digitX",&digitX);
  fRecoChain->SetBranchAddress("digitY",&digitY);
  fRecoChain->SetBranchAddress("digitZ",&digitZ);
  fRecoChain->SetBranchAddress("digitT",&digitT);
  fRecoChain->SetBranchAddress("digitQ",&digitQ);
  fRecoChain->SetBranchAddress("deltaT",&deltaT);
  fRecoChain->SetBranchAddress("deltaR",&deltaR);
  fRecoChain->SetBranchAddress("deltaTrack",&deltaTrack);
  fRecoChain->SetBranchAddress("deltaPhoton",&deltaPhoton);
  fRecoChain->SetBranchAddress("delta",&delta);
  fRecoChain->SetBranchAddress("deltaAngle",&deltaAngle);
  fRecoChain->SetBranchAddress("deltaWeight",&deltaWeight);
  fRecoChain->SetBranchAddress("deltaDeweight",&deltaDeweight);


  /*
  fRecoChain->Add("ntuple.vertex.mu.1200.new.root");
  fRecoChain->Add("ntuple.vertex.mu.1600.new.root");
  fRecoChain->Add("ntuple.vertex.mu.2000.new.root");
  fRecoChain->Add("ntuple.vertex.mu.3200.new.root");
  */

  // TUNED MONTE CARLO
  // =================
  fRecoChain->Add("../ntuple.vertex.mu.1200.tuned.timing.root");
  fRecoChain->Add("../ntuple.vertex.mu.1600.tuned.timing.root");
  fRecoChain->Add("../ntuple.vertex.mu.2000.tuned.timing.root");
  fRecoChain->Add("../ntuple.vertex.mu.3200.tuned.timing.root");
  

  TH1D* hshort = new TH1D("hshort","",50,-9.0,+11.0);
  TH1D* hlong = new TH1D("hlong","",50,-9.0,+11.0);

  TH1D* h1 = new TH1D("h1","",35,3.0,73.0);
  TH1D* htot1 = new TH1D("htot1","",35,3.0,73.0);  

  TH1D* h1a = new TH1D("h1a","",40,2.0,22.0);
  TH1D* htot1a = new TH1D("htot1a","",40,2.0,22.0);  

  TH1D* h2 = new TH1D("h2","",35,3.0,38.0);
  TH1D* htot2 = new TH1D("htot2","",35,3.0,38.0);  

  TH1D* h3 = new TH1D("h3","",35,3.0,38.0);
  TH1D* htot3 = new TH1D("htot3","",35,3.0,38.0);

  Double_t refIndex = 1.33;
  Double_t refIndexNew = 1.33;

  Double_t theta = (TMath::Pi()/180.0)*42.0;
  Double_t thetaNew = (TMath::Pi()/180.0)*42.0;

  Double_t distTrack = 0.0;
  Double_t distPhoton = 0.0;

  Double_t distTrackNew = 0.0;
  Double_t distPhotonNew = 0.0;

  Double_t deltaTrackNew = 0.0;
  Double_t deltaPhotonNew = 0.0;

  Double_t deltaTnew = 0.0;
  Double_t deltaRnew = 0.0;

  Double_t deltaTslew = 0.0;

  // refractive index
  // ================
  TF1* f1 = new TF1("f1","[0] + [1]*(x-[2])",4.0,72.0);
  f1->SetParameter(0,1.33);
  f1->SetParameter(1,6.21e-04);
  f1->SetParameter(2,12.0);

  // time slew
  // =========
  TF1* f2 = new TF1("f2","[0] + [1]*log(x) + [2]*log(x)*log(x)",0.25,40.0);
  f2->SetParameter(0,+3.406);
  f2->SetParameter(1,-2.423);
  f2->SetParameter(2,+0.335);

  // time resolution
  // ===============
  TF1* f3 = new TF1("f3","[0] + [1]/sqrt(x) + [2]/x",0.25,40.0);
  f3->SetParameter(0,+0.271);
  f3->SetParameter(1,+3.037);   
  f3->SetParameter(2,+2.543);   

  for(Int_t i=0; i<fRecoChain->GetEntries(); i++){
    fRecoChain->GetEntry(i);

    distTrack = deltaTrack;
    distPhoton = deltaPhoton/refIndex;

    // --- recalculate distance and times --- 
    distPhotonNew = distPhoton*sin(theta)/sin(thetaNew);
    distTrackNew = distTrack + distPhoton*(cos(theta)-cos(thetaNew)*sin(theta)/sin(thetaNew));

    deltaTrackNew = distTrackNew;
    deltaPhotonNew = distPhotonNew*refIndexNew;

    deltaRnew = deltaTrackNew + deltaPhotonNew;

    deltaTslew = f2->Eval(digitQ);
    deltaTnew = deltaT; // - deltaTslew;
    // --------------------------------------

    // refractive index plots
    // ======================
    if( deltaDeweight>0.99
     && digitQ>3.0 && digitQ<150.0
     && digitT-vtxTime-deltaR>-25.0     
     && digitT-vtxTime-deltaR<+150.0 ){   

      if( distPhoton*0.3<10.0 ){
        hshort->Fill(deltaT-vtxTime-deltaTrack-deltaPhoton);
      }
      if( distPhoton*0.3>40.0 ){
        hlong->Fill(deltaT-vtxTime-deltaTrack-deltaPhoton);
      }

      if( deltaPhoton>0.0 ){
        h1->Fill(distPhoton*0.3,1.33*(deltaT-vtxTime-deltaTrack)/deltaPhoton);
        htot1->Fill(distPhoton*0.3,1.0);
      }

      if( deltaTrack>0.0 ){
        h1a->Fill(distTrack*0.3,deltaTrack/(deltaT-vtxTime-deltaPhoton));
        htot1a->Fill(distTrack*0.3,1.0);
      }

    }

    // timing plots
    // ============
    if( deltaDeweight>0.99
     && digitQ>3.0 && digitQ<150.0
     && digitT-vtxTime-deltaR>-7.5    
     && digitT-vtxTime-deltaR<+15.0 ){  

      h2->Fill(digitQ,deltaT-vtxTime-deltaR);
      htot2->Fill(digitQ);

      h3->Fill(digitQ,pow(deltaT-vtxTime-deltaR,2.0));
      htot3->Fill(digitQ);

    }

  }

  // normalise histograms
  // ====================
  hshort->Scale(hlong->Integral()/hshort->Integral());

  h1->Divide(htot1);
  h1a->Divide(htot1a);
  h2->Divide(htot2);
  h3->Divide(htot3);

  for( Int_t i=0; i<h3->GetXaxis()->GetNbins(); i++ ){
    Double_t sq_of_mean = h2->GetBinContent(i+1)*h2->GetBinContent(i+1);
    Double_t mean_of_sq = h3->GetBinContent(i+1);
    Double_t bincontent = -1.0;
    if( mean_of_sq - sq_of_mean > 0.0 ){
      bincontent = sqrt( mean_of_sq - sq_of_mean );
      h3->SetBinContent(i+1,bincontent);
    }
  }

  // Photon Propagation
  // ==================
  TCanvas* c0 = new TCanvas("cVtxTunePhoton","cVtxTunePhoton");

  hshort->GetXaxis()->SetTitle("Time Residual / ns");
  hshort->GetYaxis()->SetTitle("Digits");
  hshort->GetYaxis()->SetTitleOffset(1.3);

  hshort->SetLineColor(2);
  hshort->SetLineWidth(2);
  hlong->SetLineColor(4);
  hlong->SetLineWidth(2);

  hshort->Draw();
  hlong->Draw("same"); 
 
  TLegend* leg0 = new TLegend(0.65,0.70,0.85,0.85);
  leg0->AddEntry(hshort,"L_{#gamma}<10m","l");
  leg0->AddEntry(hlong,"L_{#gamma}>40m","l");
  leg0->SetLineColor(10);
  leg0->SetFillColor(10);
  leg0->SetFillStyle(0);
  leg0->Draw();


  // Refractive Index
  // ================
  TCanvas* c1 = new TCanvas("cVtxTuneIndex","cVtxTuneIndex");

  h1->GetXaxis()->SetTitle("Photon Propagation Distance / m");
  h1->GetYaxis()->SetTitle("Effective Refractive Index");

  h1->SetMinimum(1.25);
  h1->SetMaximum(1.45);

  h1->Draw("prof");    

  f1->Draw("same");

  TLegend* leg1 = new TLegend(0.25,0.65,0.45,0.85);
  leg1->AddEntry(h1,"Data","p");
  leg1->AddEntry(f1,"Fit","l");
  leg1->SetLineColor(10);
  leg1->SetFillColor(10);
  leg1->SetFillStyle(0);
  leg1->Draw();  


  // Track Velocity
  // ==============
  TCanvas* c1a = new TCanvas("cVtxTuneVelocity","cVtxTuneVelocity");

  h1a->GetXaxis()->SetTitle("Track Propagation Distance / m");
  h1a->GetYaxis()->SetTitle("Effective Velocity / c");

  h1a->SetMinimum(0.75);
  h1a->SetMaximum(1.15);

  h1a->Draw("prof");    

  TLegend* leg1a = new TLegend(0.65,0.65,0.85,0.85);
  leg1a->AddEntry(h1a,"Data","p");
  //leg1a->AddEntry(f1a,"Fit","l");
  leg1a->SetLineColor(10);
  leg1a->SetFillColor(10);
  leg1a->SetFillStyle(0);
  leg1a->Draw();


  // Draw Time Slew
  // ==============
  TCanvas* c2 = new TCanvas("cVtxTuneTimeSlew","cVtxTuneTimeSlew");

  h2->GetXaxis()->SetTitle("Pulse Height / PEs");
  h2->GetYaxis()->SetTitle("Mean Time Slew / ns");

  h2->SetMinimum(-1.5);
  h2->SetMaximum(+1.5);

  h2->Draw("prof");  

  f2->Draw("same");
  
  TLegend* leg2 = new TLegend(0.65,0.65,0.85,0.85);
  leg2->AddEntry(h2,"Data","p");
  leg2->AddEntry(f2,"Fit","l");
  leg2->SetLineColor(10);
  leg2->SetFillColor(10);
  leg2->SetFillStyle(0);
  leg2->Draw();


  // Draw Time Resolution
  // ====================
  TCanvas* c3 = new TCanvas("cVtxTuneTimeRes","cVtxTuneTimeRes");

  h3->GetXaxis()->SetTitle("Pulse Height / PEs");
  h3->GetYaxis()->SetTitle("Mean Time Resolution / ns");

  h3->SetMinimum(0.0);
  h3->SetMaximum(3.5);

  h3->Draw("prof"); 

  f3->Draw("same");   

  TLegend* leg2 = new TLegend(0.65,0.65,0.85,0.85);
  leg2->AddEntry(h2,"Data","p");
  leg2->AddEntry(f2,"Fit","l");
  leg2->SetLineColor(10);
  leg2->SetFillColor(10);
  leg2->SetFillStyle(0);
  leg2->Draw();

}
