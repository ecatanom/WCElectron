#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "TLatex.h"
#include "TMath.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TH2D.h"
#include "TF1.h"
#include "THStack.h"
#include "TAttFill.h"
#include "TAttAxis.h"
#include "TNamed.h"
#include "TColor.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

void reco_plots() {
  
  int start =0;
  int k = 2;
  
  Int_t Nsamples = 3;
  
  //string sampleN[6] = {"ntuple_Reco_muon_minus_000400MeV_200kton.0000","ntuple_Reco_muon_minus_001600MeV_200kton.0001","ntuple_Reco_muon_minus_002000MeV_200kton.0000","ntuple_Reco_muon_minus_002400MeV_200kton.0000","ntuple_Reco_muon_minus_002800MeV_200kton.0000","ntuple_Reco_muon_minus_003200MeV_200kton.0000"};
  /*string sampleN[10] = {"reco_muon_minus_000400MeV_200kton",
  			"reco_muon_minus_001600MeV_200kton",
  			"reco_muon_minus_002000MeV_200kton",
  			"reco_muon_minus_002400MeV_200kton",
  			"reco_muon_minus_002800MeV_200kton",
  			"reco_muon_minus_003200MeV_200kton",
			"reco_muon_minus_003600MeV_200kton",
			"reco_muon_minus_004000MeV_200kton",
			"reco_muon_minus_004400MeV_200kton",
			"reco_muon_minus_004800MeV_200kton"
			};*/
  //string sampleN[12] = {"reco_muon_plus_000400MeV_200kton",
  			//"reco_muon_plus_000800MeV_200kton",
  string sampleN[3] = {"ntuple_chrom_true_1000ev_1200MeV_DetDev_13percent_noMuSct_Plmu",
                        "ntuple_chrom_true_1000ev_1200MeV_DetDev_13percent_noMuSct_Plmu_0.25smear",
                        "ntuple_chrom_true_1000ev_1200MeV_DetDev_13percent_noMuSct_Plmu_2.0smear"};
                        //"sel6"};	
  			//"ntuple_chrom_digit_400ev_reco_muon_plus_001200MeV_200kton.0001_13percentbare_DetDev",
                        //"ntuple_chrom_true_50ev_muon_plus_001200MeV_200kton.0001_13percentbare_DetDev_noMuSct_Qmin-1_Nmin50",
  			//"Chrom_100evt_muonplus_1200MeV_13percent_50Nmin_0.95time_5early_150late_100soft_noDcut"};
  //string sampleN[2] = {"ntuple_chrom_250ev_reco_muon_plus_001200MeV_200kton.0001",
  //                     "ntuple_Andy_250ev_reco_muon_plus_001200MeV_200kton.0001"};			
			  
  //string sampleType[12] = {"400 MeV","800 MeV","1200 MeV","1600 MeV","2000 MeV","2400 MeV","2800 MeV","3200 MeV","3600 MeV","4000 MeV","4400 MeV","4800 MeV"};
  //int color[12] = {kMagenta,kMagenta+4,kMagenta-4,kBlue-5,kRed+1,kBlue,kGreen,kOrange,kYellow+1,kCyan+1,kGray,kViolet+1};
  string sampleType[3] = {"0.1 ns","0.25 ns","2.0 ns"};
  int color[3] = {kBlue,kGreen,kRed};
  //string sampleType[2] = {"chromPDF", "AndyPDF N(d)"};
  //int color[2] = {kRed, kBlue};
  
  TH2D* histo_PointVtxDistAlongTrue_vs_PerpDist[Nsamples];
  TH1D* histo_PointVtxDistAlongTrue[Nsamples];
  TH1D* histo_PointVtxFOM[Nsamples];
  
  TH2D* histo_ExtVtxDistAlongTrue_vs_PerpDist[Nsamples];
  TH1D* histo_ExtVtxDistAlongTrue[Nsamples];
  TH1D* histo_ExtVtxPerpDist[Nsamples];
  
  TH1D* histo_ExtVtxDistFromTrue[Nsamples];
  TH1D* histo_DirExtVtxTheta[Nsamples];
  
  TH1D* histo_ExtVtxFOM[Nsamples];

  //read histos from root files
  TFile *inFile[Nsamples];
  for (int i=0; i!=Nsamples; i++) {
	string fileName = "/lbne/app/users/txin/FitResult_root/"+sampleN[i]+"_plots.root";
	inFile[i] = TFile::Open(fileName.c_str());
	inFile[i]->cd();
				
	gDirectory->GetObject("hVtxPointPosition",histo_PointVtxDistAlongTrue_vs_PerpDist[i]);
	gDirectory->GetObject("hVtxPointPositionProf",histo_PointVtxDistAlongTrue[i]);
	gDirectory->GetObject("hVtxPointFOM",histo_PointVtxFOM[i]);
	gDirectory->GetObject("hVtxExtendedPosition",histo_ExtVtxDistAlongTrue_vs_PerpDist[i]);
	gDirectory->GetObject("hVtxExtendedPositionProf",histo_ExtVtxDistAlongTrue[i]);
	gDirectory->GetObject("hVtxExtendedPositionProf2",histo_ExtVtxPerpDist[i]);
	gDirectory->GetObject("hVtxExtendedDelta",histo_ExtVtxDistFromTrue[i]);
	gDirectory->GetObject("hDirExtendedTheta",histo_DirExtVtxTheta[i]);
	gDirectory->GetObject("hVtxExtendedFOM",histo_ExtVtxFOM[i]);
			
	//histo_PointVtxDistAlongTrue_vs_PerpDist[i]->Sumw2();
	//histo_PointVtxDistAlongTrue[i]->Sumw2();
	//histo_PointVtxFOM[i]->Sumw2();
	//histo_ExtVtxDistAlongTrue_vs_PerpDist[i]->Sumw2();
	//histo_ExtVtxDistAlongTrue[i]->Sumw2();
	//histo_ExtVtxPerpDist[i]->Sumw2();
	//histo_ExtVtxDistFromTrue[i]->Sumw2();
		
 	}//end loop over the samples to read the histograms from root files 
  //get the values for 68% of the histograms
  double extVtxDfromT[Nsamples];
  double extVtxTheta[Nsamples];
  for (int i=0; i!=Nsamples; i++) {
  	extVtxDfromT[i] = 0;
	extVtxTheta[i] = 0;
	for (int idist=1; idist != (histo_ExtVtxDistFromTrue[i]->GetNbinsX())+1; idist++) {
		double fracD = (histo_ExtVtxDistFromTrue[i]->Integral(1,idist+1))/(histo_ExtVtxDistFromTrue[i]->Integral());
		//std::cout << "Int"
		std::cout << "bin = " << idist << " , fracD = " << fracD << std::endl;
		if (0.68 < fracD) {extVtxDfromT[i] = idist; break;} 
	}
	for (int iangle=1; iangle != (histo_DirExtVtxTheta[i]->GetNbinsX())+1; iangle++) {
	
		double fracA = (histo_DirExtVtxTheta[i]->Integral(1,iangle+1))/(histo_DirExtVtxTheta[i]->Integral());
		std::cout << "bin = " << iangle << " , fracA = " << fracA << std::endl;
		if (0.68 < fracA) {extVtxTheta[i] = iangle; break;}
	}
   	std::cout << "sample = " << sampleType[i] << " , extVtxDfromT = " << extVtxDfromT[i]*(histo_ExtVtxDistFromTrue[i]->GetBinWidth(1)) << std::endl;
   	std::cout << "sample = " << sampleType[i] << " , extVtxTheta = " << extVtxTheta[i]*(histo_DirExtVtxTheta[i]->GetBinWidth(1)) << std::endl;
  }
  
  
  std::cout << " i am fine " << std::endl;
  //set histos characteristics
  for (int i=0; i!=Nsamples; i++) {
	histo_PointVtxDistAlongTrue_vs_PerpDist[i]->SetMarkerSize(0.7);		
	histo_PointVtxDistAlongTrue_vs_PerpDist[i]->SetMarkerStyle(8);			
	histo_PointVtxDistAlongTrue_vs_PerpDist[i]->SetMarkerColor(color[i]);
	histo_PointVtxDistAlongTrue_vs_PerpDist[i]->SetLineColor(color[i]);
	histo_PointVtxDistAlongTrue_vs_PerpDist[i]->SetStats(0);
	histo_PointVtxDistAlongTrue_vs_PerpDist[i]->SetFillColor(color[i]);		
	
	histo_PointVtxDistAlongTrue[i]->SetMarkerSize(0.7);		
	histo_PointVtxDistAlongTrue[i]->SetMarkerStyle(8);			
	histo_PointVtxDistAlongTrue[i]->SetMarkerColor(color[i]);
	histo_PointVtxDistAlongTrue[i]->SetLineColor(color[i]);
	histo_PointVtxDistAlongTrue[i]->SetStats(0);
	histo_PointVtxDistAlongTrue[i]->SetFillStyle(3004);
	histo_PointVtxDistAlongTrue[i]->SetFillColor(color[i]);
	
	histo_PointVtxFOM[i]->SetMarkerSize(0.7);		
	histo_PointVtxFOM[i]->SetMarkerStyle(8);			
	histo_PointVtxFOM[i]->SetMarkerColor(color[i]);
	histo_PointVtxFOM[i]->SetLineColor(color[i]);
	histo_PointVtxFOM[i]->SetStats(0);
	histo_PointVtxFOM[i]->SetFillStyle(3004);
	histo_PointVtxFOM[i]->SetFillColor(color[i]);
	
	histo_ExtVtxDistAlongTrue_vs_PerpDist[i]->SetMarkerSize(0.7);		
	histo_ExtVtxDistAlongTrue_vs_PerpDist[i]->SetMarkerStyle(8);			
	histo_ExtVtxDistAlongTrue_vs_PerpDist[i]->SetMarkerColor(color[i]);
	histo_ExtVtxDistAlongTrue_vs_PerpDist[i]->SetLineColor(color[i]);
	histo_ExtVtxDistAlongTrue_vs_PerpDist[i]->SetStats(0);
	histo_ExtVtxDistAlongTrue_vs_PerpDist[i]->SetFillColor(color[i]);
	
	histo_ExtVtxDistAlongTrue[i]->SetMarkerSize(0.7);		
	histo_ExtVtxDistAlongTrue[i]->SetMarkerStyle(8);			
	histo_ExtVtxDistAlongTrue[i]->SetMarkerColor(color[i]);
	histo_ExtVtxDistAlongTrue[i]->SetLineColor(color[i]);
	histo_ExtVtxDistAlongTrue[i]->SetStats(0);
	histo_ExtVtxDistAlongTrue[i]->SetFillStyle(3004);
	histo_ExtVtxDistAlongTrue[i]->SetFillColor(color[i]);
	
	histo_ExtVtxPerpDist[i]->SetMarkerSize(0.7);		
	histo_ExtVtxPerpDist[i]->SetMarkerStyle(8);			
	histo_ExtVtxPerpDist[i]->SetMarkerColor(color[i]);
	histo_ExtVtxPerpDist[i]->SetLineColor(color[i]);
	histo_ExtVtxPerpDist[i]->SetStats(0);
	histo_ExtVtxPerpDist[i]->SetFillStyle(3004);
	histo_ExtVtxPerpDist[i]->SetFillColor(color[i]);

	histo_ExtVtxDistFromTrue[i]->SetMarkerSize(0.7);		
	histo_ExtVtxDistFromTrue[i]->SetMarkerStyle(8);			
	histo_ExtVtxDistFromTrue[i]->SetMarkerColor(color[i]);
	histo_ExtVtxDistFromTrue[i]->SetLineColor(color[i]);
	histo_ExtVtxDistFromTrue[i]->SetStats(0);
	histo_ExtVtxDistFromTrue[i]->SetFillStyle(3004);
	histo_ExtVtxDistFromTrue[i]->SetFillColor(color[i]);
	
	histo_DirExtVtxTheta[i]->SetMarkerSize(0.7);		
	histo_DirExtVtxTheta[i]->SetMarkerStyle(8);			
	histo_DirExtVtxTheta[i]->SetMarkerColor(color[i]);
	histo_DirExtVtxTheta[i]->SetLineColor(color[i]);
	histo_DirExtVtxTheta[i]->SetStats(0);
	histo_DirExtVtxTheta[i]->SetFillStyle(3004);
	histo_DirExtVtxTheta[i]->SetFillColor(color[i]);
	
	histo_ExtVtxFOM[i]->SetMarkerSize(0.7);		
	histo_ExtVtxFOM[i]->SetMarkerStyle(8);			
	histo_ExtVtxFOM[i]->SetMarkerColor(color[i]);
	histo_ExtVtxFOM[i]->SetLineColor(color[i]);
	histo_ExtVtxFOM[i]->SetStats(0);
	histo_ExtVtxFOM[i]->SetFillStyle(3004);
	histo_ExtVtxFOM[i]->SetFillColor(color[i]);
  
  }//end loop over samples to set the histos characteristics
  
  
  /*TLatex *text0;
  if (jetBinStudy == "3incl") text4 = new TLatex(3.570061,23.08044,"#geq 3 jets, #geq 1 tag");
		if (jetBinStudy == "4jet") text4 = new TLatex(3.570061,23.08044,"#geq 4 jets, #geq 1 tag");
		if (jetBinStudy != "3incl" && jetBinStudy != "4jet") text4 = new TLatex(3.570061,23.08044,"");
		text4->SetNDC();
		text4->SetTextAlign(13);
		text4->SetX(0.700);
		text4->SetY(0.952);
		text4->SetTextFont(42);
		text4->SetTextSizePixels(24);*/
		
  ///////////////********PointVtx distance along True Direction vs Perpendicular Distance*********////////////
		
  TCanvas *canvas1 = new TCanvas("PointVtxDistAlongTrue_vs_PerpDist", "");
  canvas1->cd()->SetRightMargin(0.04);
		
  TH1F *htemp_PointVtxDistAlongTrue_vs_PerpDist = (TH1F*) histo_PointVtxDistAlongTrue_vs_PerpDist[Nsamples-1]->Clone("htemp_PointVtxDistAlongTrue_vs_PerpDist");
  htemp_PointVtxDistAlongTrue_vs_PerpDist->Reset();
  htemp_PointVtxDistAlongTrue_vs_PerpDist->Draw();
  //htemp_PointVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetRangeUser(10e-1,1.3*histo_PointVtxDistAlongTrue_vs_PerpDist[Nsamples-1]->GetMaximum());
  //htemp_PointVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetRangeUser(20,150);
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetTitle("Perpendicular distance [m]");
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetTitle("Point Vtx: Distance along True trajectory [m]");
		
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetTitleFont(42);
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetTitleSize(0.06);
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetTitleOffset(1.0);
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetLabelFont(42);
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetLabelSize(0.05);
		
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetTitleFont(42);
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetTitleSize(0.06);
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetTitleOffset(1.0);
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetLabelFont(42);
  htemp_PointVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetLabelSize(0.05);

  for (int i=0; i!=Nsamples; i++) {	
  //for (int i=start; i!=start+k; i++) {
  	histo_PointVtxDistAlongTrue_vs_PerpDist[i]->Draw("same");
  	}
  TLegend *legend1 = new TLegend(0.65, 0.68, 0.95, 0.88);
  legend1->AddEntry(histo_PointVtxDistAlongTrue_vs_PerpDist[0],"AndyPDF N=1.33","F");
  legend1->AddEntry(histo_PointVtxDistAlongTrue_vs_PerpDist[1],"simpleGauss","F");
  legend1->AddEntry(histo_PointVtxDistAlongTrue_vs_PerpDist[2],"simpleGauss","F");
  legend1->SetTextSize(0.04);
  legend1->Draw();
  legend1->SetFillColor(kWhite);
		
  //canvas1->SetLogy();
  string nameCanvas1 = "PointVtxDistAlongTrue_vs_PerpDist.pdf";
  canvas1->SaveAs(nameCanvas1.c_str());
  
  
  ///////////////********PointVtx distance along True Direction*********////////////
		
  TCanvas *canvas2 = new TCanvas("PointVtxDistAlongTrue", "");
  canvas2->cd()->SetRightMargin(0.04);
		
  TH1F *htemp_PointVtxDistAlongTrue = (TH1F*) histo_PointVtxDistAlongTrue[1]->Clone("htemp_PointVtxDistAlongTrue");
  htemp_PointVtxDistAlongTrue->Reset();
  htemp_PointVtxDistAlongTrue->Draw();
  htemp_PointVtxDistAlongTrue->GetYaxis()->SetRangeUser(10e-1,1.1*histo_PointVtxDistAlongTrue[1]->GetMaximum());
  //htemp_PointVtxDistAlongTrue->GetXaxis()->SetRangeUser(20,150);
  htemp_PointVtxDistAlongTrue->GetYaxis()->SetTitle("Entries");
  htemp_PointVtxDistAlongTrue->GetXaxis()->SetTitle("Point Vtx: Distance along True trajectory [m]");
		
  htemp_PointVtxDistAlongTrue->GetYaxis()->SetTitleFont(42);
  htemp_PointVtxDistAlongTrue->GetYaxis()->SetTitleSize(0.06);
  htemp_PointVtxDistAlongTrue->GetYaxis()->SetTitleOffset(1.0);
  htemp_PointVtxDistAlongTrue->GetYaxis()->SetLabelFont(42);
  htemp_PointVtxDistAlongTrue->GetYaxis()->SetLabelSize(0.05);
		
  htemp_PointVtxDistAlongTrue->GetXaxis()->SetTitleFont(42);
  htemp_PointVtxDistAlongTrue->GetXaxis()->SetTitleSize(0.06);
  htemp_PointVtxDistAlongTrue->GetXaxis()->SetTitleOffset(1.0);
  htemp_PointVtxDistAlongTrue->GetXaxis()->SetLabelFont(42);
  htemp_PointVtxDistAlongTrue->GetXaxis()->SetLabelSize(0.05);

  for (int i=0; i!=Nsamples; i++) {	
  //for (int i=start; i!=start+k; i++) {
  	histo_PointVtxDistAlongTrue[i]->Draw("same histo");
  	}
  TLegend *legend2 = new TLegend(0.65, 0.68, 0.95, 0.88);
  legend2->AddEntry(histo_PointVtxDistAlongTrue[0],"AndyPDF N=1.33","F");
  legend2->AddEntry(histo_PointVtxDistAlongTrue[1],"simpleGauss","F");
  legend2->AddEntry(histo_PointVtxDistAlongTrue[2],"simpleGauss","F");
  legend2->SetTextSize(0.04);
  legend2->Draw();
  legend2->SetFillColor(kWhite);
		
  //canvas2->SetLogy();
  string nameCanvas2 = "PointVtxDistAlongTrue.pdf";
  canvas2->SaveAs(nameCanvas2.c_str());
  
  ///////////////********PointVtx FOM*********////////////
		
  TCanvas *canvas3 = new TCanvas("PointVtxFOM", "");
  canvas3->cd()->SetRightMargin(0.04);
		
  TH1F *htemp_PointVtxFOM = (TH1F*) histo_PointVtxFOM[1]->Clone("htemp_PointVtxFOM");
  htemp_PointVtxFOM->Reset();
  htemp_PointVtxFOM->Draw();
  htemp_PointVtxFOM->GetYaxis()->SetRangeUser(10e-1,1.1*histo_PointVtxFOM[0]->GetMaximum());
  htemp_PointVtxFOM->GetXaxis()->SetRangeUser(0.3,0.8);
  htemp_PointVtxFOM->GetYaxis()->SetTitle("Entries");
  htemp_PointVtxFOM->GetXaxis()->SetTitle("Point Vertex FOM");
		
  htemp_PointVtxFOM->GetYaxis()->SetTitleFont(42);
  htemp_PointVtxFOM->GetYaxis()->SetTitleSize(0.06);
  htemp_PointVtxFOM->GetYaxis()->SetTitleOffset(1.0);
  htemp_PointVtxFOM->GetYaxis()->SetLabelFont(42);
  htemp_PointVtxFOM->GetYaxis()->SetLabelSize(0.05);
		
  htemp_PointVtxFOM->GetXaxis()->SetTitleFont(42);
  htemp_PointVtxFOM->GetXaxis()->SetTitleSize(0.06);
  htemp_PointVtxFOM->GetXaxis()->SetTitleOffset(1.0);
  htemp_PointVtxFOM->GetXaxis()->SetLabelFont(42);
  htemp_PointVtxFOM->GetXaxis()->SetLabelSize(0.05);

  for (int i=0; i!=Nsamples; i++) {	
  //for (int i=start; i!=start+k; i++) {
  	histo_PointVtxFOM[i]->Draw("same histo");
  	}
  TLegend *legend3 = new TLegend(0.65, 0.68, 0.95, 0.88);
  legend3->AddEntry(histo_PointVtxFOM[0],"AndyPDF N=1.33","F");
  legend3->AddEntry(histo_PointVtxFOM[1],"simpleGauss","F");
  legend3->AddEntry(histo_PointVtxFOM[2],"simpleGauss","F");
  legend3->SetTextSize(0.04);
  legend3->Draw();
  legend3->SetFillColor(kWhite);
		
  //canvas3->SetLogy();
  string nameCanvas3 = "PointVtxFOM.pdf";
  canvas3->SaveAs(nameCanvas3.c_str());
  
  ///////////////********ExtendedVtx distance along True Direction vs Perpendicular Distance*********////////////
		
  TCanvas *canvas4 = new TCanvas("ExtVtxDistAlongTrue_vs_PerpDist", "");
  canvas4->cd()->SetRightMargin(0.04);
		
  TH1F *htemp_ExtVtxDistAlongTrue_vs_PerpDist = (TH1F*) histo_ExtVtxDistAlongTrue_vs_PerpDist[1]->Clone("htemp_ExtVtxDistAlongTrue_vs_PerpDist");
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->Reset();
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->Draw();
  //htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetRangeUser(10e-1,1.1*histo_ExtVtxDistAlongTrue_vs_PerpDist[1]->GetMaximum());
  //htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetRangeUser(20,150);
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetTitle("Perperndicular distance [m]");
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetTitle("Extended Vtx: Distance along True trajectory [m]");
		
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetTitleFont(42);
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetTitleSize(0.06);
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetTitleOffset(1.0);
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetLabelFont(42);
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetYaxis()->SetLabelSize(0.05);
		
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetTitleFont(42);
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetTitleSize(0.06);
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetTitleOffset(1.0);
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetLabelFont(42);
  htemp_ExtVtxDistAlongTrue_vs_PerpDist->GetXaxis()->SetLabelSize(0.05);

  for (int i=0; i!=Nsamples; i++) {	
  //for (int i=start; i!=start+k; i++) {
  	histo_ExtVtxDistAlongTrue_vs_PerpDist[i]->Draw("same");
  	}
  TLegend *legend4 = new TLegend(0.65, 0.68, 0.95, 0.88);
  for (int i=0; i!= Nsamples; i++) {
	legend4->AddEntry(histo_ExtVtxDistAlongTrue_vs_PerpDist[i],sampleType[i].c_str(),"F");
	}
  legend4->SetTextSize(0.04);
  legend4->Draw();
  legend4->SetFillColor(kWhite);
		
  //canvas4->SetLogy();
  string nameCanvas4 = "ExtVtxDistAlongTrue_vs_PerpDist.pdf";
  canvas4->SaveAs(nameCanvas4.c_str());
  
  
  ///////////////********ExtendedVtx distance along True Direction*********////////////
		
  TCanvas *canvas5 = new TCanvas("ExtVtxDistAlongTrue", "");
  canvas5->cd()->SetRightMargin(0.04);
		
  TH1F *htemp_ExtVtxDistAlongTrue = (TH1F*) histo_ExtVtxDistAlongTrue[1]->Clone("htemp_ExtVtxDistAlongTrue");
  htemp_ExtVtxDistAlongTrue->Reset();
  htemp_ExtVtxDistAlongTrue->Draw();
  htemp_ExtVtxDistAlongTrue->GetYaxis()->SetRangeUser(10e-1,1.1*histo_ExtVtxDistAlongTrue[1]->GetMaximum());
  //htemp_ExtVtxDistAlongTrue->GetXaxis()->SetRangeUser(20,150);
  htemp_ExtVtxDistAlongTrue->GetYaxis()->SetTitle("Entries");
  htemp_ExtVtxDistAlongTrue->GetXaxis()->SetTitle("Extended Vtx: Distance along True trajectory [m]");
		
  htemp_ExtVtxDistAlongTrue->GetYaxis()->SetTitleFont(42);
  htemp_ExtVtxDistAlongTrue->GetYaxis()->SetTitleSize(0.06);
  htemp_ExtVtxDistAlongTrue->GetYaxis()->SetTitleOffset(1.0);
  htemp_ExtVtxDistAlongTrue->GetYaxis()->SetLabelFont(42);
  htemp_ExtVtxDistAlongTrue->GetYaxis()->SetLabelSize(0.05);
		
  htemp_ExtVtxDistAlongTrue->GetXaxis()->SetTitleFont(42);
  htemp_ExtVtxDistAlongTrue->GetXaxis()->SetTitleSize(0.06);
  htemp_ExtVtxDistAlongTrue->GetXaxis()->SetTitleOffset(1.0);
  htemp_ExtVtxDistAlongTrue->GetXaxis()->SetLabelFont(42);
  htemp_ExtVtxDistAlongTrue->GetXaxis()->SetLabelSize(0.05);

  for (int i=0; i!=Nsamples; i++) {	
  //for (int i=start; i!=start+k; i++) {
  	histo_ExtVtxDistAlongTrue[i]->Draw("same histo");
  	}
  TLegend *legend5 = new TLegend(0.65, 0.68, 0.95, 0.88);
  for (int i=0; i!= Nsamples; i++) {
	legend5->AddEntry(histo_ExtVtxDistAlongTrue[i],sampleType[i].c_str(),"F");
	}
  legend5->SetTextSize(0.04);
  legend5->Draw();
  legend5->SetFillColor(kWhite);
		
  //canvas5->SetLogy();
  string nameCanvas5 = "ExtVtxDistAlongTrue.pdf";
  canvas5->SaveAs(nameCanvas5.c_str());
  
  
  ///////////////********ExtendedVtx distance Perpendicular to True Direction*********////////////
		
  TCanvas *canvas9 = new TCanvas("ExtVtxPerpDist", "");
  canvas9->cd()->SetRightMargin(0.04);
		
  TH1F *htemp_ExtVtxPerpDist = (TH1F*) histo_ExtVtxPerpDist[1]->Clone("htemp_ExtVtxPerpDist");
  htemp_ExtVtxPerpDist->Reset();
  htemp_ExtVtxPerpDist->Draw();
  htemp_ExtVtxPerpDist->GetYaxis()->SetRangeUser(10e-1,1.1*histo_ExtVtxPerpDist[1]->GetMaximum());
  //htemp_ExtVtxPerpDist->GetXaxis()->SetRangeUser(20,150);
  htemp_ExtVtxPerpDist->GetYaxis()->SetTitle("Entries");
  htemp_ExtVtxPerpDist->GetXaxis()->SetTitle("Extended Vtx: Distance Perpendicular to True trajectory [m]");
		
  htemp_ExtVtxPerpDist->GetYaxis()->SetTitleFont(42);
  htemp_ExtVtxPerpDist->GetYaxis()->SetTitleSize(0.06);
  htemp_ExtVtxPerpDist->GetYaxis()->SetTitleOffset(1.0);
  htemp_ExtVtxPerpDist->GetYaxis()->SetLabelFont(42);
  htemp_ExtVtxPerpDist->GetYaxis()->SetLabelSize(0.05);
		
  htemp_ExtVtxPerpDist->GetXaxis()->SetTitleFont(42);
  htemp_ExtVtxPerpDist->GetXaxis()->SetTitleSize(0.06);
  htemp_ExtVtxPerpDist->GetXaxis()->SetTitleOffset(1.0);
  htemp_ExtVtxPerpDist->GetXaxis()->SetLabelFont(42);
  htemp_ExtVtxPerpDist->GetXaxis()->SetLabelSize(0.05);

  for (int i=0; i!=Nsamples; i++) {	
  //for (int i=start; i!=start+k; i++) {
  	histo_ExtVtxPerpDist[i]->Draw("same histo");
  	}
  TLegend *legend9 = new TLegend(0.65, 0.68, 0.95, 0.88);
  for (int i=0; i!= Nsamples; i++) {
	legend9->AddEntry(histo_ExtVtxPerpDist[i],sampleType[i].c_str(),"F");
	}
  legend9->SetTextSize(0.04);
  legend9->Draw();
  legend9->SetFillColor(kWhite);
		
  //canvas9->SetLogy();
  string nameCanvas9 = "ExtVtxPerpDist.pdf";
  canvas9->SaveAs(nameCanvas9.c_str());
  
  
  ///////////////********ExtendedVtx distance from the TrueVtx*********////////////
		
  TCanvas *canvas6 = new TCanvas("ExtVtxDistFromTrueVtx", "");
  canvas6->cd()->SetRightMargin(0.04);
		
  TH1F *htemp_histo_ExtVtxDistFromTrue = (TH1F*) histo_ExtVtxDistFromTrue[1]->Clone("htemp_histo_ExtVtxDistFromTrue");
  htemp_histo_ExtVtxDistFromTrue->Reset();
  htemp_histo_ExtVtxDistFromTrue->Draw();
  htemp_histo_ExtVtxDistFromTrue->GetYaxis()->SetRangeUser(10e-1,1.1*histo_ExtVtxDistFromTrue[1]->GetMaximum());
  //htemp_histo_ExtVtxDistFromTrue->GetXaxis()->SetRangeUser(20,150);
  htemp_histo_ExtVtxDistFromTrue->GetYaxis()->SetTitle("Entries");
  htemp_histo_ExtVtxDistFromTrue->GetXaxis()->SetTitle("Distance(ExtendedVtx,TrueVtx) [m]");
		
  htemp_histo_ExtVtxDistFromTrue->GetYaxis()->SetTitleFont(42);
  htemp_histo_ExtVtxDistFromTrue->GetYaxis()->SetTitleSize(0.06);
  htemp_histo_ExtVtxDistFromTrue->GetYaxis()->SetTitleOffset(1.0);
  htemp_histo_ExtVtxDistFromTrue->GetYaxis()->SetLabelFont(42);
  htemp_histo_ExtVtxDistFromTrue->GetYaxis()->SetLabelSize(0.05);
		
  htemp_histo_ExtVtxDistFromTrue->GetXaxis()->SetTitleFont(42);
  htemp_histo_ExtVtxDistFromTrue->GetXaxis()->SetTitleSize(0.06);
  htemp_histo_ExtVtxDistFromTrue->GetXaxis()->SetTitleOffset(1.0);
  htemp_histo_ExtVtxDistFromTrue->GetXaxis()->SetLabelFont(42);
  htemp_histo_ExtVtxDistFromTrue->GetXaxis()->SetLabelSize(0.05);

  for (int i=0; i!=Nsamples; i++) {	
  //for (int i=start; i!=start+k; i++) {
  	histo_ExtVtxDistFromTrue[i]->Draw("same histo");
  	}
  TLegend *legend6 = new TLegend(0.65, 0.68, 0.95, 0.88);
  for (int i=0; i!= Nsamples; i++) {
	legend6->AddEntry(histo_ExtVtxDistFromTrue[i],sampleType[i].c_str(),"F");
	}
  legend6->SetTextSize(0.04);
  legend6->Draw();
  legend6->SetFillColor(kWhite);
		
  //canvas6->SetLogy();
  string nameCanvas6 = "ExtVtxDistFromTrueVtx.pdf";
  canvas6->SaveAs(nameCanvas6.c_str());
  
  ///////////////********ExtendedVtx Theta angle wrt to True direction*********////////////
		
  TCanvas *canvas7 = new TCanvas("ExtVtxDirTheta", "");
  canvas7->cd()->SetRightMargin(0.04);
		
  TH1F *htemp_DirExtVtxTheta = (TH1F*) histo_DirExtVtxTheta[1]->Clone("htemp_histo_ExtVtxDistFromTrue");
  htemp_DirExtVtxTheta->Reset();
  htemp_DirExtVtxTheta->Draw();
  htemp_DirExtVtxTheta->GetYaxis()->SetRangeUser(10e-1,1.1*histo_DirExtVtxTheta[1]->GetMaximum());
  //htemp_DirExtVtxTheta->GetXaxis()->SetRangeUser(20,150);
  htemp_DirExtVtxTheta->GetYaxis()->SetTitle("Entries");
  htemp_DirExtVtxTheta->GetXaxis()->SetTitle("Extended Vtx: Angle wrt true trajectory [degrees]");
		
  htemp_DirExtVtxTheta->GetYaxis()->SetTitleFont(42);
  htemp_DirExtVtxTheta->GetYaxis()->SetTitleSize(0.06);
  htemp_DirExtVtxTheta->GetYaxis()->SetTitleOffset(1.0);
  htemp_DirExtVtxTheta->GetYaxis()->SetLabelFont(42);
  htemp_DirExtVtxTheta->GetYaxis()->SetLabelSize(0.05);
		
  htemp_DirExtVtxTheta->GetXaxis()->SetTitleFont(42);
  htemp_DirExtVtxTheta->GetXaxis()->SetTitleSize(0.06);
  htemp_DirExtVtxTheta->GetXaxis()->SetTitleOffset(1.0);
  htemp_DirExtVtxTheta->GetXaxis()->SetLabelFont(42);
  htemp_DirExtVtxTheta->GetXaxis()->SetLabelSize(0.05);

  for (int i=0; i!=Nsamples; i++) {	
  //for (int i=start; i!=start+k; i++) {
  	histo_DirExtVtxTheta[i]->Draw("same histo");
  	}
  TLegend *legend7 = new TLegend(0.65, 0.68, 0.95, 0.88);
  for (int i=0; i!= Nsamples; i++) {
	legend7->AddEntry(histo_DirExtVtxTheta[i],sampleType[i].c_str(),"F");
	}
  legend7->SetTextSize(0.04);
  legend7->Draw();
  legend7->SetFillColor(kWhite);
		
  //canvas7->SetLogy();
  string nameCanvas7 = "ExtVtxDirTheta.pdf";
  canvas7->SaveAs(nameCanvas7.c_str());
  
  ///////////////********ExtendedVtx FOM*********////////////
		
  TCanvas *canvas8 = new TCanvas("ExtendedVtxFOM", "");
  canvas8->cd()->SetRightMargin(0.04);
		
  TH1F *htemp_ExtVtxFOM = (TH1F*) histo_ExtVtxFOM[1]->Clone("htemp_ExtVtxFOM");
  htemp_ExtVtxFOM->Reset();
  htemp_ExtVtxFOM->Draw();
  htemp_ExtVtxFOM->GetYaxis()->SetRangeUser(10e-1,1.1*histo_ExtVtxFOM[0]->GetMaximum());
  htemp_ExtVtxFOM->GetXaxis()->SetRangeUser(0.3,0.8);
  htemp_ExtVtxFOM->GetYaxis()->SetTitle("Entries");
  htemp_ExtVtxFOM->GetXaxis()->SetTitle("Extended Vertex FOM");
		
  htemp_ExtVtxFOM->GetYaxis()->SetTitleFont(42);
  htemp_ExtVtxFOM->GetYaxis()->SetTitleSize(0.06);
  htemp_ExtVtxFOM->GetYaxis()->SetTitleOffset(1.0);
  htemp_ExtVtxFOM->GetYaxis()->SetLabelFont(42);
  htemp_ExtVtxFOM->GetYaxis()->SetLabelSize(0.05);
		
  htemp_ExtVtxFOM->GetXaxis()->SetTitleFont(42);
  htemp_ExtVtxFOM->GetXaxis()->SetTitleSize(0.06);
  htemp_ExtVtxFOM->GetXaxis()->SetTitleOffset(1.0);
  htemp_ExtVtxFOM->GetXaxis()->SetLabelFont(42);
  htemp_ExtVtxFOM->GetXaxis()->SetLabelSize(0.05);

  for (int i=0; i!=Nsamples; i++) {	
  //for (int i=start; i!=start+k; i++) {
  	histo_ExtVtxFOM[i]->Draw("same histo");
  	}
  TLegend *legend8 = new TLegend(0.65, 0.68, 0.95, 0.88);
  for (int i=0; i!= Nsamples; i++) {
  legend8->AddEntry(histo_ExtVtxFOM[i],sampleType[i].c_str(),"F");
  }
  legend8->SetTextSize(0.04);
  legend8->Draw();
  legend8->SetFillColor(kWhite);
		
  //canvas8->SetLogy();
  string nameCanvas8 = "ExtendedVtxFOM.pdf";
  canvas8->SaveAs(nameCanvas8.c_str());
  
  double converge = 0.0;
  converge = histo_PointVtxDistAlongTrue[2]->Integral();
  //converge = histo_ExtVtxDistFromTrue[2]->Integral();
  cout << "converge of " << sampleType[1] << ": " << (converge/100.0) << endl;
  int nentries = 0;
  for( int ii=0;ii<(histo_DirExtVtxTheta[2]->GetNbinsX());ii++ ){
    nentries += (histo_DirExtVtxTheta[2]->GetBinContent(ii));
  }
  cout << nentries << endl;

  }
