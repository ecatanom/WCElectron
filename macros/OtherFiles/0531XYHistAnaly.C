{
  gROOT->Reset();
  // #include <TFile.h> 
    //  gSystem->Load("libGeom");
  //   gSystem->Load("libEve");
  //   gSystem->Load("libMinuit");
  //   gSystem->Load("libCintex"); 
  // gSystem->Load("libWCSimRootDict");
  //   gSystem->Load("libWCSimRoot.so");
  //   gSystem->Load("libWCSimAnalysis.so");
  //cout<<"done00"<<endl;

  TFile fgood("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Good/goodhistos.root");
   TFile fbad("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Bad/badhistos.root");
  cout<<"done000"<<endl;
  int badevents[]={0, 109, 111, 116, 118, 127, 178, 188, 214, 227, 230, 236, 243, 250, 267, 275, 276, 277, 295, 303, 312, 322, 326, 330, 331, 345, 353, 359, 369, 370, 377, 379, 38, 403, 404, 405, 408, 411, 416, 432, 439, 441, 446, 447, 486, 493, 495, 532, 534, 541, 566, 578, 589, 599, 610, 616, 635, 636, 641, 643, 646, 653, 660, 663, 673, 674, 704, 705, 730, 75, 764, 780, 790, 799, 81, 824, 82, 831, 838, 857, 911, 91, 925, 957, 95, 985, 992}; ///bad events!!!!!
  
  int goodevents[]={100, 114, 122, 145, 146, 156, 161, 165, 173, 175, 184, 185, 196, 197, 198, 205, 206, 210, 213, 219, 21, 222, 226, 249, 258, 263, 265, 274, 279, 283, 284, 296, 29, 302, 304, 30, 320, 325, 329, 336, 338, 339, 34, 357, 362, 363, 381, 391, 392, 406, 418, 443, 452, 459, 468, 485, 492, 501, 514, 516, 521, 54, 558, 569, 57, 582, 586, 592, 601, 619, 622, 624, 647, 661, 710, 724, 72, 738, 739, 746, 750, 757, 771, 775, 779, 794, 810, 812, 822, 853, 859, 85, 860, 862, 866, 878, 893, 904, 909, 919, 922, 926, 945, 964, 96, 975, 97, 981};

  //int  myngood = sizeof(goodevents)/sizeof(goodevents[0]);
  //int mynbad = sizeof(badevents)/sizeof(badevents[0]);
  //cout<<"good"<<myngood;
  //return;  
  int myeventnumber=0;
  TString hystoname1("");TString hystoname2("");TString hystoname3("");
  TString hystoname4("");TString hystoname5("");TString hystoname6("");

 //*****************************************************************************************************************************
  //double goodmean[108];
  //--------------------------------------------------------------------

  TH1D goodmean1("","",50,-5000.0,5000.0); 
  TH1D goodmean2("","",50,0.-5000,5000.0);
  TH1D goodmean3("","",50,-5000.0,5000.0); 
  TH1D goodmean4("","",50,0.-5000,5000.0);
  TH1D goodmean5("","",50,-5000.0,5000.0); 
  TH1D goodmean6("","",50,0.-5000,5000.0);



  for(int gcounter=0;gcounter<108;gcounter++){ 
    myeventnumber=goodevents[gcounter];
   
    hystoname1=("h1D_TX_");hystoname1+=myeventnumber;//hystoname1+=";1";
    hystoname2=("h1D_TY_");hystoname2+=myeventnumber;
    hystoname3=("h1D_TZ_");hystoname3+=myeventnumber;
    hystoname4=("h1D_HX_");hystoname4+=myeventnumber;
    hystoname5=("h1D_HY_");hystoname5+=myeventnumber;
    hystoname6=("h1D_HZ_");hystoname6+=myeventnumber;

    TH1D *h1 = (TH1D*)fgood.Get(hystoname1);
    TH1D *h2 = (TH1D*)fgood.Get(hystoname2);
    TH1D *h3 = (TH1D*)fgood.Get(hystoname3);
    TH1D *h4 = (TH1D*)fgood.Get(hystoname4);
    TH1D *h5 = (TH1D*)fgood.Get(hystoname5);
    TH1D *h6 = (TH1D*)fgood.Get(hystoname6);
    
   
   
    goodmean1.Fill(h1.GetMean());
    goodmean2.Fill(h2.GetMean());
    goodmean3.Fill(h3.GetMean());
    goodmean4.Fill(h4.GetMean());
    goodmean5.Fill(h5.GetMean());
    goodmean6.Fill(h6.GetMean());
   
   
    delete h1;delete h2;
    delete h3;
    delete h4;
    delete h5;   delete h6;
  }

  //--------------------------------------------------------------------

  TH1D badmean1("","",50,-5000.0,5000.0); 
  TH1D badmean2("","",50,0.-5000,5000.0);
  TH1D badmean3("","",50,-5000.0,5000.0); 
  TH1D badmean4("","",50,0.-5000,5000.0);
  TH1D badmean5("","",50,-5000.0,5000.0); 
  TH1D badmean6("","",50,0.-5000,5000.0);



  for(int gcounter=0;gcounter<87;gcounter++){ 
    myeventnumber=badevents[gcounter];
   
    hystoname1=("h1D_TX_");hystoname1+=myeventnumber;//hystoname1+=";1";
    hystoname2=("h1D_TY_");hystoname2+=myeventnumber;
    hystoname3=("h1D_TZ_");hystoname3+=myeventnumber;
    hystoname4=("h1D_HX_");hystoname4+=myeventnumber;
    hystoname5=("h1D_HY_");hystoname5+=myeventnumber;
    hystoname6=("h1D_HZ_");hystoname6+=myeventnumber;

    TH1D *h1 = (TH1D*)fbad.Get(hystoname1);
    TH1D *h2 = (TH1D*)fbad.Get(hystoname2);
    TH1D *h3 = (TH1D*)fbad.Get(hystoname3);
    TH1D *h4 = (TH1D*)fbad.Get(hystoname4);
    TH1D *h5 = (TH1D*)fbad.Get(hystoname5);
    TH1D *h6 = (TH1D*)fbad.Get(hystoname6);
    
   
   
    badmean1.Fill(h1.GetMean());
    badmean2.Fill(h2.GetMean());
    badmean3.Fill(h3.GetMean());
    badmean4.Fill(h4.GetMean());
    badmean5.Fill(h5.GetMean());
    badmean6.Fill(h6.GetMean());
   
   
    delete h1;delete h2;
    delete h3;
    delete h4;
    delete h5;   delete h6;
  }
 



 
  gStyle->SetOptStat("n");
  //  (h1->GetXaxis())->SetTitle("hitT [ns]");
  //   (h1->GetYaxis())->SetTitle("Hits"); 
  //   h1->SetStats(1); 
  TCanvas *ca1 = new TCanvas("ca1","XYZ",1200,600); 
  ca1->Divide(3,2);
  ca1->cd(1);
  goodmean1->DrawNormalized();
  badmean1->SetLineColor(kRed);
  badmean1->DrawNormalized("same");
  ca1->cd(2);
  goodmean2->DrawNormalized();
  badmean2->SetLineColor(kRed);
  badmean2->DrawNormalized("same");
  ca1->cd(3);
  goodmean3->DrawNormalized();
  badmean3->SetLineColor(kRed);
  badmean3->DrawNormalized("same");
  ca1->cd(4);
  goodmean4->DrawNormalized();
  badmean4->SetLineColor(kRed);
  badmean4->DrawNormalized("same");
  ca1->cd(5);
  goodmean5->DrawNormalized();
  badmean5->SetLineColor(kRed);
  badmean5->DrawNormalized("same");
  ca1->cd(6);
  goodmean6->DrawNormalized();
  badmean6->SetLineColor(kRed);
  badmean6->DrawNormalized("same");

  
 TImage *img1 = TImage::Create();
 img1->FromPad(ca1);
 img1->WriteImage("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Stats/XYZMean_Stats01.png");



 delete img1;  
 //*****************************************************************************************************************************


 //*****************************************************************************************************************************
  //double goodRMS[108];
  //--------------------------------------------------------------------

  TH1D goodRMS1("","",50,0.0,3000.0); 
  TH1D goodRMS2("","",50,0.0,3000.0);
  TH1D goodRMS3("","",50,0.0,3000.0); 
  TH1D goodRMS4("","",50,0.0,3000.0);
  TH1D goodRMS5("","",50,0.0,3000.0); 
  TH1D goodRMS6("","",50,0.0,3000.0);



  for(int gcounter=0;gcounter<108;gcounter++){ 
    myeventnumber=goodevents[gcounter];
   
    hystoname1=("h1D_TX_");hystoname1+=myeventnumber;//hystoname1+=";1";
    hystoname2=("h1D_TY_");hystoname2+=myeventnumber;
    hystoname3=("h1D_TZ_");hystoname3+=myeventnumber;
    hystoname4=("h1D_HX_");hystoname4+=myeventnumber;
    hystoname5=("h1D_HY_");hystoname5+=myeventnumber;
    hystoname6=("h1D_HZ_");hystoname6+=myeventnumber;

    TH1D *h1 = (TH1D*)fgood.Get(hystoname1);
    TH1D *h2 = (TH1D*)fgood.Get(hystoname2);
    TH1D *h3 = (TH1D*)fgood.Get(hystoname3);
    TH1D *h4 = (TH1D*)fgood.Get(hystoname4);
    TH1D *h5 = (TH1D*)fgood.Get(hystoname5);
    TH1D *h6 = (TH1D*)fgood.Get(hystoname6);
    
   
   
    goodRMS1.Fill(h1.GetRMS());
    goodRMS2.Fill(h2.GetRMS());
    goodRMS3.Fill(h3.GetRMS());
    goodRMS4.Fill(h4.GetRMS());
    goodRMS5.Fill(h5.GetRMS());
    goodRMS6.Fill(h6.GetRMS());
   
   
    delete h1;delete h2;
    delete h3;
    delete h4;
    delete h5;   delete h6;
  }

  //--------------------------------------------------------------------

  TH1D badRMS1("","",50,0.0,3000.0); 
  TH1D badRMS2("","",50,0.0,3000.0);
  TH1D badRMS3("","",50,0.0,3000.0); 
  TH1D badRMS4("","",50,0.0,3000.0);
  TH1D badRMS5("","",50,0.0,3000.0); 
  TH1D badRMS6("","",50,0.0,3000.0);



  for(int gcounter=0;gcounter<87;gcounter++){ 
    myeventnumber=badevents[gcounter];
   
    hystoname1=("h1D_TX_");hystoname1+=myeventnumber;//hystoname1+=";1";
    hystoname2=("h1D_TY_");hystoname2+=myeventnumber;
    hystoname3=("h1D_TZ_");hystoname3+=myeventnumber;
    hystoname4=("h1D_HX_");hystoname4+=myeventnumber;
    hystoname5=("h1D_HY_");hystoname5+=myeventnumber;
    hystoname6=("h1D_HZ_");hystoname6+=myeventnumber;

    TH1D *h1 = (TH1D*)fbad.Get(hystoname1);
    TH1D *h2 = (TH1D*)fbad.Get(hystoname2);
    TH1D *h3 = (TH1D*)fbad.Get(hystoname3);
    TH1D *h4 = (TH1D*)fbad.Get(hystoname4);
    TH1D *h5 = (TH1D*)fbad.Get(hystoname5);
    TH1D *h6 = (TH1D*)fbad.Get(hystoname6);
    
   
   
    badRMS1.Fill(h1.GetRMS());
    badRMS2.Fill(h2.GetRMS());
    badRMS3.Fill(h3.GetRMS());
    badRMS4.Fill(h4.GetRMS());
    badRMS5.Fill(h5.GetRMS());
    badRMS6.Fill(h6.GetRMS());
   
   
    delete h1;delete h2;
    delete h3;
    delete h4;
    delete h5;   delete h6;
  }
 



 
  gStyle->SetOptStat("n");
  //  (h1->GetXaxis())->SetTitle("hitT [ns]");
  //   (h1->GetYaxis())->SetTitle("Hits"); 
  //   h1->SetStats(1); 
  TCanvas *ca1 = new TCanvas("ca1","XYZ",1200,300); 
  ca1->Divide(3,1);
  // ca1->cd(1);
//   goodRMS1->DrawNormalized();
//   badRMS1->SetLineColor(kRed);
//   badRMS1->DrawNormalized("same");
//   ca1->cd(2);
//   goodRMS2->DrawNormalized();
//   badRMS2->SetLineColor(kRed);
//   badRMS2->DrawNormalized("same");
//   ca1->cd(3);
//   goodRMS3->DrawNormalized();
//   badRMS3->SetLineColor(kRed);
//   badRMS3->DrawNormalized("same");
  ca1->cd(1);
  goodRMS4->DrawNormalized();
  badRMS4->SetLineColor(kRed);
  badRMS4->DrawNormalized("same");
  ca1->cd(2);
  goodRMS5->DrawNormalized();
  badRMS5->SetLineColor(kRed);
  badRMS5->DrawNormalized("same");
  ca1->cd(3);
  goodRMS6->DrawNormalized();
  badRMS6->SetLineColor(kRed);
  badRMS6->DrawNormalized("same");

  
 TImage *img1 = TImage::Create();
 img1->FromPad(ca1);
 img1->WriteImage("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Stats/XYZRMS_Stats01.png");



 delete img1;  
 //*****************************************************************************************************************************

}
