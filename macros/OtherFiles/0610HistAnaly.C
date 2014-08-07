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
  TString hystoname4("");TString hystoname5("");

  //gStyle->SetOptStat("nemrksi");

  //double goodmean[108];
  //--------------------------------------------------------------------
  TH1D goodmean1("","",50,0.0,350.0);
  TH1D goodkurtosis1("","",50,-4.0,6.0);
  TH1D goodskewness1("","",50,-4.0,7.0);  TH1D goodRMS1("","",50,-10.0,100.0);
  TH1D goodmean2("","",50,0.0,15.0);
  TH1D goodkurtosis2("","",50,0.0,60.0);
  TH1D goodskewness2("","",50,0.0,6.0); TH1D goodRMS2("","",50,0.0,6.0);
  TH1D goodmean3("","",50,600.0,5500.0);
  TH1D goodkurtosis3("","",50,-2.0,4.0);
  TH1D goodskewness3("","",50,-1.0,2.5); TH1D goodRMS3("","",50,-100.0,1800.0);
  TH1D goodmean4("","",50,0.0,420.0);
  TH1D goodkurtosis4("","",50,-2.0,6.0);
  TH1D goodskewness4("","",50,-1.0,2.0); TH1D goodRMS4("","",50,50.0,600.0);
  TH1D goodmean5("","",50,30.0,45.0);
  TH1D goodkurtosis5("","",50,-2,5);
  TH1D goodskewness5("","",50,-1.6,0.7); TH1D goodRMS5("","",50,-1.0,10.0);

  for(int gcounter=0;gcounter<108;gcounter++){ 
    myeventnumber=goodevents[gcounter];
   
    hystoname1=("h1D_HT_");hystoname1+=myeventnumber;//hystoname1+=";1";
    hystoname2=("h1D_TR_");hystoname2+=myeventnumber;
    hystoname3=("h1D_LP_");hystoname3+=myeventnumber;
    hystoname4=("h1D_LM_");hystoname4+=myeventnumber;
    hystoname5=("h1D_OA_");hystoname5+=myeventnumber;

    TH1D *h1 = (TH1D*)fgood.Get(hystoname1);
    TH1D *h2 = (TH1D*)fgood.Get(hystoname2);
    TH1D *h3 = (TH1D*)fgood.Get(hystoname3);
    TH1D *h4 = (TH1D*)fgood.Get(hystoname4);
    TH1D *h5 = (TH1D*)fgood.Get(hystoname5);
    
    // cout<<myeventnumber<< " " <<h2.GetMean() << " " <<h2.GetMeanError()<< " " <<h2.GetKurtosis()  << " " <<h2.GetSkewness() << endl;
    //cout<<myeventnumber<< " " <<h3.GetMean() << " " <<h3.GetMeanError()<< " " <<h3.GetKurtosis()  << " " <<h3.GetSkewness() << endl;
    //cout<<myeventnumber<< " " <<h4.GetMean() << " " <<h4.GetMeanError()<< " " <<h4.GetKurtosis()  << " " <<h4.GetSkewness() << endl;
    //cout<<myeventnumber<< " " <<h5.GetMean() << " " <<h5.GetMeanError()<< " " <<h5.GetKurtosis()  << " " <<h5.GetSkewness() << endl;

   
    goodmean1.Fill(h1.GetMean());
    goodkurtosis1.Fill(h1.GetKurtosis());
    goodskewness1.Fill(h1.GetSkewness()); goodRMS1.Fill(h1.GetRMS());
    goodmean2.Fill(h2.GetMean());
    goodkurtosis2.Fill(h2.GetKurtosis());
    goodskewness2.Fill(h2.GetSkewness()); goodRMS2.Fill(h2.GetRMS());
    goodmean3.Fill(h3.GetMean());
    goodkurtosis3.Fill(h3.GetKurtosis());
    goodskewness3.Fill(h3.GetSkewness()); goodRMS3.Fill(h3.GetRMS());
    goodmean4.Fill(h4.GetMean());
    goodkurtosis4.Fill(h4.GetKurtosis());
    goodskewness4.Fill(h4.GetSkewness()); goodRMS4.Fill(h4.GetRMS());
    goodmean5.Fill(h5.GetMean());
    goodkurtosis5.Fill(h5.GetKurtosis());
    goodskewness5.Fill(h5.GetSkewness()); goodRMS5.Fill(h5.GetRMS());
   
    delete h1;
    delete h2;
    delete h3;
    delete h4;
    delete h5;
  }

  //return; 


//-------------------------------------------------------------------- 
  TH1D badmean1("BadHT","",50,0.0,350.0);
  TH1D badkurtosis1("","",50,-4.0,6.0);
  TH1D badskewness1("","",50,-4.0,7.0);  TH1D badRMS1("","",50,-10.0,100.0);
  TH1D badmean2("BadTR","",50,0.0,15.0);
  TH1D badkurtosis2("","",50,0.0,60.0);
  TH1D badskewness2("","",50,0.0,6.0); TH1D badRMS2("","",50,0.0,6.0);
  TH1D badmean3("BadLP","",50,600.0,5500.0);
  TH1D badkurtosis3("","",50,-2.0,4.0);
  TH1D badskewness3("","",50,-1.0,2.5); TH1D badRMS3("","",50,-100.0,1800.0);
  TH1D badmean4("BadLM","",50,0.0,420.0);
  TH1D badkurtosis4("","",50,-2.0,6.0);
  TH1D badskewness4("","",50,-1.0,2.0); TH1D badRMS4("","",50,50.0,600.0);
  TH1D badmean5("BadOA","",50,30.0,45.0);
  TH1D badkurtosis5("","",50,-2,5);
  TH1D badskewness5("","",50,-1.6,0.7); TH1D badRMS5("","",50,-1.0,10.0);
 




  for(int gcounter=0;gcounter<87;gcounter++){ 
    myeventnumber=badevents[gcounter];
   
    hystoname1=("h1D_HT_");hystoname1+=myeventnumber;//hystoname1+=";1";
    hystoname2=("h1D_TR_");hystoname2+=myeventnumber;
    hystoname3=("h1D_LP_");hystoname3+=myeventnumber;
    hystoname4=("h1D_LM_");hystoname4+=myeventnumber;
    hystoname5=("h1D_OA_");hystoname5+=myeventnumber;

    TH1D *h1 = (TH1D*)fbad.Get(hystoname1);
    TH1D *h2 = (TH1D*)fbad.Get(hystoname2);
    TH1D *h3 = (TH1D*)fbad.Get(hystoname3);
    TH1D *h4 = (TH1D*)fbad.Get(hystoname4);
    TH1D *h5 = (TH1D*)fbad.Get(hystoname5);
    
    //cout<<myeventnumber<< " " <<h2.GetMean() << " " <<h2.GetMeanError()<< " " <<h2.GetKurtosis()  << " " <<h2.GetSkewness() << endl;
    //cout<<myeventnumber<< " " <<h3.GetMean() << " " <<h3.GetMeanError()<< " " <<h3.GetKurtosis()  << " " <<h3.GetSkewness() << endl;
    //cout<<myeventnumber<< " " <<h4.GetMean() << " " <<h4.GetMeanError()<< " " <<h4.GetKurtosis()  << " " <<h4.GetSkewness() << endl;
    //cout<<myeventnumber<< " " <<h5.GetMean() << " " <<h5.GetMeanError()<< " " <<h5.GetKurtosis()  << " " <<h5.GetSkewness() << endl;

   
    badmean1.Fill(h1.GetMean());
    badkurtosis1.Fill(h1.GetKurtosis());
    badskewness1.Fill(h1.GetSkewness());badRMS1.Fill(h1.GetRMS());
    badmean2.Fill(h2.GetMean());
    badkurtosis2.Fill(h2.GetKurtosis());
    badskewness2.Fill(h2.GetSkewness());badRMS2.Fill(h2.GetRMS());
    badmean3.Fill(h3.GetMean());
    badkurtosis3.Fill(h3.GetKurtosis());
    badskewness3.Fill(h3.GetSkewness());badRMS3.Fill(h3.GetRMS());
    badmean4.Fill(h4.GetMean());
    badkurtosis4.Fill(h4.GetKurtosis());
    badskewness4.Fill(h4.GetSkewness());badRMS4.Fill(h4.GetRMS());
    badmean5.Fill(h5.GetMean());
    badkurtosis5.Fill(h5.GetKurtosis());
    badskewness5.Fill(h5.GetSkewness());badRMS5.Fill(h5.GetRMS());
   
    delete h1;
    delete h2;
    delete h3;
    delete h4;
    delete h5;
  }
 
  //gStyle->SetOptStat("nmr");
  /*
 TCanvas *ca1 = new TCanvas("ca1","HT",800,600); 
  goodmean1->DrawNormalized();
  badmean1->SetLineColor(kRed);
  badmean1->DrawNormalized("same");

  TString goodinfo("G: ");goodinfo+=goodmean1.GetMean();goodinfo.Resize(9);
  goodinfo+="+-"; goodinfo+=goodmean1.GetRMS());goodinfo.Resize(16);
TString badinfo("B: ");badinfo+=badmean1.GetMean();badinfo.Resize(9);
  badinfo+="+-"; badinfo+=badmean1.GetRMS());badinfo.Resize(16);

  TLegend *mylegend = new TLegend(0.6,0.75,0.9,0.9,"");
  mylegend->AddEntry("","Mean-HitT Good", "l"); mylegend->AddEntry("",goodinfo,"");
  mylegend->AddEntry("BadHT","Mean-HitT Bad", "l");mylegend->AddEntry("",badinfo,"");

  mylegend->Draw();
*/

TCanvas *ca1 = new TCanvas("ca1","LP",800,600); 
  goodmean3->DrawNormalized();
  badmean3->SetLineColor(kRed);
  badmean3->DrawNormalized("same");

  TString goodinfo("G: ");goodinfo+=goodmean3.GetMean();goodinfo.Resize(9);
  goodinfo+="+-"; goodinfo+=goodmean3.GetRMS());goodinfo.Resize(16);
TString badinfo("B: ");badinfo+=badmean3.GetMean();badinfo.Resize(9);
  badinfo+="+-"; badinfo+=badmean3.GetRMS());badinfo.Resize(16);

  TLegend *mylegend = new TLegend(0.65,0.75,0.9,0.9,"");
  mylegend->AddEntry("","Mean-LPhoton Good", "l"); mylegend->AddEntry("",goodinfo,"");
  mylegend->AddEntry("BadLP","Mean-LPhoton Bad", "l");mylegend->AddEntry("",badinfo,"");

  mylegend->Draw();

  //  (h1->GetXaxis())->SetTitle("hitT [ns]");
  //   (h1->GetYaxis())->SetTitle("Hits"); 
  //   h1->SetStats(1); 
 //  TCanvas *ca1 = new TCanvas("ca1","HT",800,600); 
//   ca1->Divide(2,2);
//   ca1->cd(1);
//   goodmean1->SetFillColor(16);goodmean1->SetFillStyle(4050);
//   goodmean1->DrawNormalized();
//   badmean1->SetLineColor(kRed);
//   badmean1->SetFillColor(42);badmean1->SetFillStyle(4050);
//   badmean1->DrawNormalized("same");
//   ca1->cd(2);
//   goodkurtosis1->DrawNormalized();
//   badkurtosis1->SetLineColor(kRed);
//   badkurtosis1->DrawNormalized("same");
//   ca1->cd(3);
//   goodskewness1->DrawNormalized();
//   badskewness1->SetLineColor(kRed);
//   badskewness1->DrawNormalized("same");
//   ca1->cd(4);
//   goodRMS1->DrawNormalized();
//   badRMS1->SetLineColor(kRed);
//   badRMS1->DrawNormalized("same");

//   TCanvas *ca2 = new TCanvas("ca2","TR",800,600); 
//   ca2->Divide(2,2);
//   ca2->cd(1);
//   goodmean2->DrawNormalized();
//   badmean2->SetLineColor(kRed);
//   badmean2->DrawNormalized("same");
//   ca2->cd(2);
//   goodkurtosis2->DrawNormalized();
//   badkurtosis2->SetLineColor(kRed);
//   badkurtosis2->DrawNormalized("same");
//   ca2->cd(3);
//   goodskewness2->DrawNormalized();
//   badskewness2->SetLineColor(kRed);
//   badskewness2->DrawNormalized("same");
//   ca2->cd(4);
//   goodRMS2->DrawNormalized();
//   badRMS2->SetLineColor(kRed);
//   badRMS2->DrawNormalized("same");

//   TCanvas *ca3 = new TCanvas("ca3","LP",800,600); 
//   ca3->Divide(2,2);
//   ca3->cd(1);
//   goodmean3->DrawNormalized();
//   badmean3->SetLineColor(kRed);
//   badmean3->DrawNormalized("same");
//   ca3->cd(2);
//   goodkurtosis3->DrawNormalized();
//   badkurtosis3->SetLineColor(kRed);
//   badkurtosis3->DrawNormalized("same");
//   ca3->cd(3);
//   goodskewness3->DrawNormalized();
//   badskewness3->SetLineColor(kRed);
//   badskewness3->DrawNormalized("same");
//   ca3->cd(4);
//   goodRMS3->DrawNormalized();
//   badRMS3->SetLineColor(kRed);
//   badRMS3->DrawNormalized("same");

//   TCanvas *ca4 = new TCanvas("ca4","LM",800,600); 
//   ca4->Divide(2,2);
//   ca4->cd(1);
//   goodmean4->DrawNormalized();
//   badmean4->SetLineColor(kRed);
//   badmean4->DrawNormalized("same");
//   ca4->cd(2);
//   goodkurtosis4->DrawNormalized();
//   badkurtosis4->SetLineColor(kRed);
//   badkurtosis4->DrawNormalized("same");
//   ca4->cd(3);
//   goodskewness4->DrawNormalized();
//   badskewness4->SetLineColor(kRed);
//   badskewness4->DrawNormalized("same");
//   ca4->cd(4);
//   goodRMS4->DrawNormalized();
//   badRMS4->SetLineColor(kRed);
//   badRMS4->DrawNormalized("same");


//   TCanvas *ca5 = new TCanvas("ca5","OA",800,600); 
//   ca5->Divide(2,2);
//   ca5->cd(1);
//   goodmean5->DrawNormalized();
//   badmean5->SetLineColor(kRed);
//   badmean5->DrawNormalized("same");
//   ca5->cd(2);
//   goodkurtosis5->DrawNormalized();
//   badkurtosis5->SetLineColor(kRed);
//   badkurtosis5->DrawNormalized("same");
//   ca5->cd(3);
//   goodskewness5->DrawNormalized();
//   badskewness5->SetLineColor(kRed);
//   badskewness5->DrawNormalized("same");
//   ca5->cd(4);
//   goodRMS5->DrawNormalized();
//   badRMS5->SetLineColor(kRed);
//   badRMS5->DrawNormalized("same"); 
// //return;
//   //  fgood.Close();
//   //   fbad.Close();
//   //delete h1;
//   // cout<<"WTF"<<endl;
//   //return 0;

//  TImage *img1 = TImage::Create();
//  img1->FromPad(ca1);
//  img1->WriteImage("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Stats/HT_Stats01.png");

//  TImage *img2 = TImage::Create();
//  img2->FromPad(ca2);
//  img2->WriteImage("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Stats/TR_Stats01.png");

//  TImage *img3 = TImage::Create();
//  img3->FromPad(ca3);
//  img3->WriteImage("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Stats/LP_Stats01.png");

//  TImage *img4 = TImage::Create();
//  img4->FromPad(ca4);
//  img4->WriteImage("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Stats/LM_Stats01.png");

//  TImage *img5 = TImage::Create();
//  img5->FromPad(ca5);
//  img5->WriteImage("/lbne/app/users/ecatanom/WCSimAnalysis/macros/052813files/Stats/OA_Stats01.png");

//  cout << "Bad events hitT mean: " <<badmean1.GetMean()<< " , "<<badmean1.GetRMS()<<endl;


//  delete img1;   delete img2;   delete img3; delete img4; delete img5;

}
