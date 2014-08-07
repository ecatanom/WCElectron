#include "TObject.h"
#include "TH1.h"
#include "TH3.h"
#include "TH3D.h"
#include "TFile.h"
#include "TVector3.h"
#include "TDirectory.h"

#include "WCSimParameters.hh"
#include "WCSimRecoDigit.hh"
#include "WCSimRecoObjectTable.hh"
#include "WCSimTResidPDF.hh"
#include "WCSimWaterModel.hh"

#include <cassert>
#include <iostream>
#include <vector>

#include "TStopwatch.h" // <----------

ClassImp(WCSimTResidPDF)

//......................................................................

static WCSimTResidPDF* fgTResidPDF = 0;

WCSimTResidPDF* WCSimTResidPDF::Instance()
{
  if( !fgTResidPDF ){
    fgTResidPDF = new WCSimTResidPDF();
  }

  if( !fgTResidPDF ){
    assert(fgTResidPDF);
  }

  if( fgTResidPDF ){

  }

  return fgTResidPDF;
}

//......................................................................

WCSimTResidPDF::~WCSimTResidPDF()
{
}

//......................................................................

WCSimTResidPDF::WCSimTResidPDF()
{
/*
  for (int i=0; i!= 500; i++) {
    for (int j=0; j!= 300; j++) {
    	for (int k=0; k!=60; k++) valueChrom[i][j][k] = 0.0;
    }
  }
  std::cout << "before making table....." << std::endl;
  WCSimTResidPDF::MakeTablePDF();
  std::cout << "chrom prob.table was made ....." << std::endl;
  */
  fileHisto = TFile::Open("/lbne/data/users/omanghel/chromHisto.root");
  gDirectory->GetObject("chromHist",hChromPDF3D);

  theDistanceHist = new TH1D("dishist","disthist",1000,-5000.,5000.);
  theLhist =  new TH1D("Lhist","Lhist",50,-397.5,602.5);
  
  minLambda = 200.0; 
  maxLambda = 700.0; //800.0; 
  stepLambda =1.0;//1.0, 2.5 or 5
  
}

//......................................................................

void WCSimTResidPDF::SetResolutionParameters(Double_t PMTRes)
{
  _pmtres=PMTRes;
  //_smearfactor=smearfactor;
}

//......................................................................

void WCSimTResidPDF::SetLandauGaussPDF(Double_t peakval, Double_t width, Double_t gauswidth){;}

//......................................................................

void WCSimTResidPDF::SetParamPDF(Double_t peakval, Double_t width, Double_t gauswidth){;}

//......................................................................
//old function from Matt
TH1D* WCSimTResidPDF::MakeChromPeakPDF(Double_t distance, Double_t res)
//void WCSimTResidPDF::MakeChromPeakPDF(TH1D* hTResidDist, Double_t distance, Double_t defaultN, Double_t res)
{
  //std::cout << "Inside MakeChromPeakPDF...." << std::endl;
  //Parameters: thedistance = photon distance, pmtres = time resolution
  Double_t thedistance = distance;
  Double_t pmtres = res;
  
  //get the index of refraction from WCSimParameters
  Double_t defaultN = WCSimParameters::RefractiveIndex(distance);

  //histo to store the time residuals for each wavelength 
  TH1D* hTResidDist = new TH1D("tresdist","Time Residual Distribution",2000,-10.,10.);

  //calculate the avgtransittime for light traveling thedistance
  Double_t defaulttransittime = thedistance*defaultN/(WCSimParameters::SpeedOfLight());
  
  //std::cout << "Inside MakeChromPeakPDF  2...." << std::endl;

  //loop over all possible wavelengths
  for (Double_t flmda = 200.; flmda < 700.; flmda = flmda + 100.0) {
  //std::cout << "Inside MakeChromPeakPDF  3...." << std::endl;

      // how much light of this particular color will make it accross thedistance, given an initial Cherenkov spectrum
      Double_t chromweight = WCSimWaterModel::Instance()->FinlSpect(flmda, thedistance);
      //std::cout << "Inside MakeChromPeakPDF  4...." << std::endl;
      
      //calculate the transit time for this color
      Double_t chromtransittime = thedistance/(WCSimWaterModel::Instance()->Vg(flmda));
      //std::cout << flmda << " Inside MakeChromPeakPDF  5...." << std::endl;
 
      //calculate the timingresidual between the transit time for that color and the average transit time
      Double_t tresidchrom = chromtransittime-defaulttransittime;

      //loop over possible gaussian smearings from pmt resolution (gaussian convolution)
      Double_t nsigma = 8.; //set the max number of sigmas for filling the histo
      Double_t gstepsize = 0.001;
      Double_t nsteps = (nsigma/2.0)/gstepsize;
      Double_t gsmearstep = 0.;

      for(int j = 0; j < nsteps; j++){

	hTResidDist->Fill((tresidchrom+gsmearstep), chromweight*(TMath::Gaus(gsmearstep,0.,pmtres)));
	if(gsmearstep > 0.) hTResidDist->Fill((tresidchrom-gsmearstep), chromweight*(TMath::Gaus(gsmearstep,0.,pmtres)));
	
	gsmearstep += gstepsize;

      }

    }
     //std::cout << "Inside MakeChromPeakPDF  6...." << std::endl;        
  Double_t norm = hTResidDist->Integral();    //normalisation factor
  if(norm != 0) hTResidDist->Scale(1/norm);

  return hTResidDist;
}

//......................................................................
//Ioana, Tian....the same funtion as TH1D* WCSimTresidPDF::MakeChromPeakPDF, but without filling the histogram
//this is used on June 19, 2012
Double_t WCSimTResidPDF::MakeChromPeakPDF(Double_t timeResid, Double_t thedistance, Double_t pmtres)
{
  
  TStopwatch swatch; // <----------
 
  Double_t probability = -999.0;
  
  //std::cout << "-----inside MakeChromPeakPDF...." << std::endl; 
  
  //get the index of refraction from WCSimParameters
  //Double_t defaultN = WCSimParameters::RefractiveIndex(distance);
  Double_t defaultN = WCSimParameters::Index0(); //...chrom1.34, 1.333;

  //calculate the avgtransittime for light traveling thedistance
  Double_t defaulttransittime = thedistance*defaultN/(WCSimParameters::SpeedOfLight());
  
  //store the value corresponding to the time residual
  Double_t timeResP = 0.0; 
  //sum of all weights
  Double_t sumweight= 0.0;
  Double_t gaussweight = 0.0;
  Double_t Nmid = 0.0;
  
  //calculate the number of iterations over the wavelengths
  int Niter = (maxLambda-minLambda)/stepLambda;
  
  //check if vectors are filled with values from TGraphs in WCSimWaterModel
  if (veloLg.empty()||initLg.empty()||absLg.empty()||sctLg.empty()) {
  	std::cout << "vectors are clear........." << std::endl;
  	veloLg.clear();
	initLg.clear();
	absLg.clear();
	sctLg.clear();
	qeLg.clear();
  	for (Int_t i = 0; i!=Niter; i++) {
        	veloLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'1'));
      		initLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'2'));
      		absLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'3'));
      		sctLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'4'));
		qeLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'5'));
  	}
  }
  
  //swatch.Start(); // <----------
	
  //loop over all possible wavelengths
  for (int i = 0; i!=Niter; i++) {
  
      WCSimWaterModel::waterM wm = WCSimWaterModel::Instance()->getParamsWM(veloLg.at(i),initLg.at(i),absLg.at(i),sctLg.at(i),qeLg.at(i),thedistance);
      
      //swatch.Start(); // <----------
      
      // how much light of this particular color will make it accross thedistance, given an initial Cherenkov spectrum
      //Double_t chromweight = WCSimWaterModel::Instance()->FinlSpect(flmda, thedistance);
      Double_t chromweight = wm.finalSpectrum;
      
      //std::cout << "finalSpectrum....WM = " << WCSimWaterModel::Instance()->FinlSpect(minLambda+i*stepLambda,thedistance) << ", vector = " << wm.finalSpectrum << std::endl;
      
      //swatch.Stop(); // <----------
      //std::cout << "FinlSpect: " << swatch.RealTime() << "\n"; // <----------
      //swatch.Start(); // <----------
      
      //calculate the transit time for this color

      //Double_t chromtransittime = thedistance/(WCSimWaterModel::Instance()->VgWCSim(flmda));
      Double_t chromtransittime = thedistance/wm.velocity;
      
      //std::cout << "velocity....WM = " << WCSimWaterModel::Instance()->VgWCSim(minLambda+i*stepLambda) << ", vector = " << wm.velocity << std::endl;
      
      //swatch.Stop(); // <----------
      //std::cout << "Vg: " << swatch.RealTime() << "\n"; // <----------
      
      //Double_t chromtransittime = thedistance/(WCSimWaterModel::Instance()->Vg(flmda));
     
      //Double_t Vlmda = WCSimWaterModel::Instance()->Vg(flmda); 
      /*Double_t theta_c = acos(Vlmda/24.0);
      Double_t mutime = thedistance*sin(theta_c - 0.733)/(sin(theta_c)*24.0);
      Double_t phottime = thedistance*0.669/(sin(theta_c)*Vlmda);
      Double_t chromtransittime = mutime + phottime;*/
      //Double_t chromtransittime = thedistance/Vlmda;
      
      //swatch.Start(); // <----------

      //calculate the timingresidual between the transit time for that color and the average transit time
      Double_t tresidchrom = chromtransittime-defaulttransittime; //tresidchrom = -tresidchrom; 

      Double_t haha = chromweight*(TMath::Gaus(timeResid-tresidchrom,0.0,pmtres,1));//or maybe (-tresidchrom)
      if( haha>=0.0 ) timeResP += haha;
      //std::cout << haha << " " << timeResP << std::endl;
      //timeResP += haha;
      
      if( chromweight>=0.0 ) sumweight += chromweight;      
      //gaussweight += TMath::Gaus(timeResid-tresidchrom,0.,pmtres);
      //gaussweight += exp(-((timeResid-tresidchrom)*(timeResid-tresidchrom)/(2*pmtres*pmtres)));
      
      //swatch.Stop(); // <----------
      //std::cout << "Gaus: " << swatch.RealTime() << "\n"; // <----------
  
  }//end loop over colors
  
  //swatch.Stop(); // <----------
  //std::cout << "for: " << swatch.RealTime() << "\n"; // <----------
  
  //std::cout << timeResP << " " << sumweight << std::endl;
  //normalization over the wavelength range = taken to be Gauss normalization for all space
  if (sumweight != 0) probability = timeResP/(sumweight);
  else probability = 0.0; 
  
  return probability;

  //return exp(-(timeResid*timeResid)/(2.0*pmtres*pmtres));

}

//......................................................................
//Tian, correct cherenkov angles
Double_t WCSimTResidPDF::MakeChromPeakPDF(Double_t timeResid, Double_t thedistance, Double_t pmtres, Double_t thedistancemu)
{
  
  TStopwatch swatch; // <----------
 
  Double_t probability = -999.0;
  
  Double_t defaultN = WCSimParameters::Index0();

  //calculate the avgtransittime for light traveling thedistance
  Double_t defaulttransittime = thedistance*defaultN/(WCSimParameters::SpeedOfLight());
  
  //store the value corresponding to the time residual
  Double_t timeResP = 0.0; 
  //sum of all weights
  Double_t sumweight= 0.0;
  Double_t gaussweight = 0.0;
  Double_t Nmid = 0.0;
  
  Double_t lphoton = thedistance;
  Double_t lmuon = thedistancemu;
  //calculate the number of iterations over the wavelengths
  int Niter = (maxLambda-minLambda)/stepLambda;
  Double_t fC = WCSimParameters::SpeedOfLight();
  //Double_t fVmu = 29.0;
  Double_t fVmu = 28.5 + 1.5/(1.0 + exp(0.04*(thedistancemu - 100.0)));

  Double_t PLmu1 = 0.0;
  Double_t Norm = 10.0;
  Double_t softcutoff = 500.0;
  Double_t earlysigma = 2.0/sqrt(Norm); //earlysigma = 5.0; // P(l=-20cm)=0.01
  Double_t latesigma = 5.0; latesigma = (525.0-softcutoff)/(10.0*sqrt(Norm)); //latesigma = 42.0;// P(l=525cm)=0.01
  Double_t AA = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  
  //check if vectors are filled with values from TGraphs in WCSimWaterModel
  if (veloLg.empty()||initLg.empty()||absLg.empty()||sctLg.empty()) {
  	std::cout << "vectors are clear........." << std::endl;
  	veloLg.clear();
	initLg.clear();
	absLg.clear();
	sctLg.clear();
	qeLg.clear();
  	for (Int_t i = 0; i!=Niter; i++) {
        	veloLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'1'));
      		initLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'2'));
      		absLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'3'));
      		sctLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'4'));
		qeLg.push_back(WCSimWaterModel::Instance()->evalGraphs(minLambda+i*stepLambda,'5'));
  	}
  }
  
  //swatch.Start(); // <----------
	
  //loop over all possible wavelengths
  for (int i = 0; i!=Niter; i++) {

//===================== calc angle ===============================================
      Double_t ChereC = 42.0;
      Double_t Chere0 = 3.14*WCSimParameters::CherenkovAngle()/180.0;
      ChereC = acos((veloLg.at(i))/fVmu);
      lmuon = thedistancemu + sin(ChereC-Chere0)*thedistance/sin(ChereC);
      lphoton = sin(Chere0)*thedistance/sin(ChereC);
      //Double_t vmuon = fC;
      //for( Int_t i=0;i<3;i++){
        //vmuon = wm.velocity+(fC-wm.velocity)/(1.0+exp(0.04*(lmuon-250.0)));
        //if( lmuon<=0.0 ) vmuon = fC;
        //if( lmuon<=525.0 ) vmuon = fC*sqrt(1.0-10000.0/((1200.0-2.0*lmuon)*(1200.0-2.0*lmuon)));
        //else vmuon = wm.velocity + 0.1;
        //ChereC = acos(wm.velocity/vmuon);
        //lmuon = thedistancemu + sin(ChereC-Chere0)*thedistance/sin(ChereC);
        //lphoton = sin(Chere0)*thedistance/sin(ChereC);
      ///}
//====================== calculate PLmuon =================================================
  
      WCSimWaterModel::waterM wm = WCSimWaterModel::Instance()->getParamsWM(veloLg.at(i),initLg.at(i),absLg.at(i),sctLg.at(i),qeLg.at(i),thedistance);
      
      //swatch.Start(); // <----------
      
      Double_t chromweight = wm.finalSpectrum;

      //WCSimVertexGeometry::Instance()->CorrectChereAngle(wm.velocity, lphoton, lmuon);

      //if( lmuon<=0.0 ) PLmu1 = AA/(1.0+(lmuon*lmuon)/(earlysigma*earlysigma));//-1.0;
      //else if( lmuon<=softcutoff ) PLmu1 = AA;
      //else PLmu1 = (AA/2.0)*(1.0+1.0/(1.0+((lmuon-softcutoff)*(lmuon-softcutoff)/(latesigma*latesigma))));
//====================== calculate PLmuon =================================================
      if( lmuon<=0.0 ) PLmu1 = Norm/(1.0+(lmuon*lmuon)/(earlysigma*earlysigma));//-1.0;
      else if( lmuon<=softcutoff ) PLmu1 = Norm;
      else PLmu1 = Norm/(1.0+((lmuon-softcutoff)*(lmuon-softcutoff)/(latesigma*latesigma)));
//=========================================================================================

      //swatch.Stop(); // <----------
      Double_t Tresidmuon = lmuon/fC - thedistancemu/fC; Tresidmuon = 0.0;
      //Double_t Tresidmuon = 2.0*lmuon/(vmuon+fC)-thedistancemu/fC;
      Double_t chromtransittime = thedistance/wm.velocity;
      Double_t tresidchrom = chromtransittime-defaulttransittime;

      Double_t haha = chromweight*(TMath::Gaus((timeResid-tresidchrom-Tresidmuon),0.0,pmtres,1));
      if( haha>=0.0 ) timeResP += PLmu1*haha;
      
      if( chromweight>=0.0 ) sumweight += chromweight;    
      //if( chromweight>=0.0002 ){  
      //std::cout << "color: " << i << " Probability: " << chromweight << std::endl;
      //std::cout << "delta T:    " << timeResid << " " << (timeResid - tresidchrom - Tresidmuon) << std::endl;
      //std::cout << "Angle:    " << Chere0 << " " << ChereC << std::endl;
      //std::cout << "Lmuon:    " << thedistancemu << " " << lmuon << std::endl;}

  }//end loop over colors
  //normalization over the wavelength range = taken to be Gauss normalization for all space
  if (sumweight != 0) probability = timeResP/(sumweight);
  else probability = 0.0; 
  
  return probability;

  //return exp(-(timeResid*timeResid)/(2.0*pmtres*pmtres));

}

//Tian...
Double_t WCSimTResidPDF::MakeChromPeakPDF(Double_t timeResid, Double_t distance, Double_t res, Double_t fmin, Double_t fmax)
{
  Double_t probability = -999.0;

  //Parameters: timeResid = time residual, thedistance = photon distance, pmtres = time resolution
  Double_t thedistance = distance;
  Double_t pmtres = res;

  
  //get the index of refraction from WCSimParameters
  //Double_t defaultN = WCSimParameters::RefractiveIndex(distance);
  Double_t defaultN = WCSimParameters::Index0(); //...chrom1.34, 1.333;

  //calculate the avgtransittime for light traveling thedistance
  Double_t defaulttransittime = thedistance*defaultN/(WCSimParameters::SpeedOfLight());
  
  //store the value corresponding to the time residual
  Double_t timeResP = 0.0; 
  //sum of all weights
  Double_t sumweight= 0.0;
  Double_t gaussweight = 0.0;
  Double_t Nmid = 0.0;
  
  //choose the range for the wavelengths
  Double_t minLambda = 200.0;
  Double_t maxLambda = 700.0;
	
  //loop over all possible wavelengths
  for (Double_t flmda = minLambda; flmda != maxLambda; flmda += 5.0) {
      
      // how much light of this particular color will make it accross thedistance, given an initial Cherenkov spectrum
      Double_t chromweight = WCSimWaterModel::Instance()->FinlSpect(flmda, thedistance);
      
      //calculate the transit time for this color
      Double_t Vlmda = WCSimWaterModel::Instance()->Vg(flmda); 
      Double_t chromtransittime = thedistance/(WCSimWaterModel::Instance()->Vg(flmda));
      //std::cout << Vlmda << " " << thedistance << std::endl;
      //calculate the timingresidual between the transit time for that color and the average transit time
      Double_t tresidchrom = chromtransittime-defaulttransittime; //tresidchrom = -tresidchrom;
      //std::cout << tresidchrom << " " << pmtres << std::endl;
      Double_t haha = chromweight*(TMath::Gaus(timeResid - tresidchrom,0.0,pmtres,1));
      if( haha>=0.0 && flmda>=fmin && flmda<fmax ) timeResP += haha;
      //std::cout << haha << " " << timeResP << std::endl;
      //timeResP += haha;
      
      if( chromweight>=0.0 ) sumweight += chromweight;      
      //gaussweight += TMath::Gaus(timeResid-tresidchrom,0.,pmtres);
      //gaussweight += exp(-((timeResid-tresidchrom)*(timeResid-tresidchrom)/(2*pmtres*pmtres)));
  
  }//end loop over colors
  
  //std::cout << timeResP << " " << sumweight << std::endl;
  //normalization over the wavelength range = taken to be Gauss normalization for all space
  if (sumweight != 0) probability = timeResP/(sumweight);
  else probability = 0.0; 
  
  return probability;
}
 

//Tian... switch between TGraph and the function. TGraph recommended
//not the function for PDF in VertexFinder
Double_t WCSimTResidPDF::MakeChromPeakPDF(Double_t timeResid, Double_t distance, Double_t res, Int_t op1, Int_t op2, Int_t op3)
{
  WCSimWaterModel::Instance()->SetOPabsl(op1);
  WCSimWaterModel::Instance()->SetOPphotv(op2);
  WCSimWaterModel::Instance()->SetOPindex(op3);
  Double_t probability = -999.0;

  //Parameters: timeResid = time residual, thedistance = photon distance, pmtres = time resolution
  Double_t thedistance = distance;
  Double_t pmtres = res;
  
  //get the index of refraction from WCSimParameters
  Double_t defaultN = WCSimParameters::RefractiveIndex(distance);
  //Double_t defaultN = 1.333;

  //calculate the avgtransittime for light traveling thedistance
  Double_t defaulttransittime = thedistance*defaultN/(WCSimParameters::SpeedOfLight());
  
  //store the value corresponding to the time residual
  Double_t timeResP = 0.0; 
  //sum of all weights
  Double_t sumweight= 0.0;
  Double_t gaussweight = 0.0;
  Double_t Nmid = 0.0;
  
  //choose the range for the wavelengths
  Double_t minLambda = 300.0;
  Double_t maxLambda = 600.0;
	
  //loop over all possible wavelengths
  for (Double_t flmda = minLambda; flmda != maxLambda; flmda += 5.0) {
      
      // how much light of this particular color will make it accross thedistance, given an initial Cherenkov spectrum
      Double_t chromweight = WCSimWaterModel::Instance()->FinlSpect(flmda, thedistance);
      
      //calculate the transit time for this color
      //Double_t chromtransittime = thedistance/(WCSimWaterModel::Instance()->VgWCSim(flmda));
      Double_t chromtransittime = thedistance/(WCSimWaterModel::Instance()->Vg(flmda));
 
      //calculate the timingresidual between the transit time for that color and the average transit time
      Double_t tresidchrom = chromtransittime-defaulttransittime; //tresidchrom = -tresidchrom;
 
      Double_t haha = chromweight*(TMath::Gaus(timeResid+tresidchrom,0.0,pmtres,1));
      if( haha>=0.0 ) timeResP += haha;
      //timeResP += haha;
      
      if( chromweight>=0.0 ) sumweight += chromweight;      
      //gaussweight += TMath::Gaus(timeResid-tresidchrom,0.,pmtres);
      //gaussweight += exp(-((timeResid-tresidchrom)*(timeResid-tresidchrom)/(2*pmtres*pmtres)));
  
  }//end loop over colors
  
  //std::cout << timeResP << " " << sumweight << std::endl;
  //normalization over the wavelength range = taken to be Gauss normalization for all space
  if (sumweight != 0) probability = timeResP/(sumweight);
  else probability = 0.0; 
  
  return probability;
  
}

//.....................................................................
//Ioana...make a table to store the chromaticPDF values
void WCSimTResidPDF::MakeTablePDF()
{
  Int_t a = -1;
  //loop over the distances
  for (int i=0; i!=500; i++){//distances
      for (int j=0; j!=300; j++) {//time residual
        //std::cout << "distance = " << i << ", time = " << j << std::endl;
	for (int k=0; k!=60; k++) {//PMT resolution
	//std::cout << "distance = " << i << ", time = " << j << ", resolution = " << k << std::endl;
      		valueChrom[i][j][k] = MakeChromPeakPDF(j/5+0.2,i*20-50,k*0.05);
	}
      }
      Int_t b = i/100;
      if (b!=a) {
      	std::cout << "distance iteration = " << i << std::endl;
	a = b;
      }
  }
}

//......................................................................
//Ioana...function to look for the Pgauss value in the table
Double_t WCSimTResidPDF::GetChromProbTable(Double_t timeResid, Double_t distance, Double_t resolution)
{
  //get the corresponding time, distance and resolution from the table
  Int_t timeBin = 0;
  if(timeResid < 0) timeBin = 49+timeResid/0.2;
  else timeBin = 50+timeResid/0.2;
  Int_t distBin = distance/20;
  Int_t resBin = resolution/0.05;
  
  Int_t intTime = timeResid/0.2;
  Int_t intDist = distance/20;
  Int_t intRes = resolution/0.001;
  Double_t restTime = timeResid/0.2 - intTime;
  Double_t restDist = distance/20 - intDist;
  Double_t restRes = resolution/0.05 - intRes;
  
  Double_t probability = (1-restTime)*(1-restDist)*valueChrom[distBin][timeBin][resBin]+
  			 (1-restTime)*restDist*valueChrom[distBin+1][timeBin][resBin]+
			 restTime*(1-restDist)*valueChrom[distBin][timeBin+1][resBin]+
			 restTime*restDist*valueChrom[distBin+1][timeBin+1][resBin];
  
  std::cout <<"table... probability = " << probability << std::endl;
  std::cout <<"MakeChromPeakPDF(timeResid,distance,_pmtres) = " << MakeChromPeakPDF(timeResid,distance,resolution) << std::endl;
  std::cout <<"table... valueChrom[distBin][timeBin][resBin] = " << valueChrom[distBin][timeBin][resBin] << std::endl;
  
  return probability;
  
}

//......................................................................
//Ioana...function to look for the Pgauss value in the 3D histo
Double_t WCSimTResidPDF::GetChromProbHist(Double_t timeResid, Double_t distance, Double_t resolution)
{
/*
  //get the corresponding time, distance and resolution from the table
  Int_t timeBin = 0;
  if(timeResid < 0) timeBin = 100+timeResid/0.1;
  else timeBin = 101+timeResid/0.1;
  Int_t distBin = distance/20;
  Int_t resBin = resolution/0.05;
  
  Int_t intTime = timeResid/0.1;
  Int_t intDist = distance/20;
  Int_t intRes = resolution/0.001;
  Double_t restTime = timeResid/0.1 - intTime;
  Double_t restDist = distance/20 - intDist;
  Double_t restRes = resolution/0.05 - intRes;
  
  Double_t probability = (1-restTime)*(1-restDist)*(1-resBin)*hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin,resBin))+
  			 (1-restTime)*restDist*(1-resBin)*hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin,resBin))+
			 restTime*(1-restDist)*(1-resBin)*hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin+1,resBin))+
			 (1-restTime)*(1-restDist)*resBin*hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin,resBin+1))+
			 (1-restTime)*restDist*resBin*hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin,resBin+1))+
			 restTime*(1-restDist)*resBin*hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin+1,resBin+1))+
			 restTime*restDist*(1-resBin)*hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin+1,resBin))+
			 restTime*restDist*resBin*hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin+1,resBin+1));
 
  std::cout << "distance = " << distance << ", timeResid = " << timeResid << ", resolution = " << resolution << std::endl;
  std::cout << "in histo: distBin = " << distBin << ", timeBin = " << timeBin << ", resBin = " << resBin << std::endl;
  std::cout << "i = " << distance/20 << ", j = " << timeResid/0.1+100 << ", k = " << resolution/0.05 << std::endl;
  std::cout <<"histo... probability = " << probability << std::endl;
  std::cout <<"MakeChromPeakPDF(timeResid,distance,resolution) = " << MakeChromPeakPDF(timeResid,distance,resolution) << std::endl;
  std::cout <<"MakeChromPeakPDF((timeBin-100)*0.1,(0*100+distBin)*20,resBin*0.05) = " << MakeChromPeakPDF((timeBin-100)*0.1,(0*100+distBin)*20,resBin*0.05) << std::endl;
  std::cout <<"MakeChromPeakPDF((timeBin-100)*0.1,(0*100+distBin)*20,resolution) = " << MakeChromPeakPDF((timeBin-100)*0.1,(0*100+distBin)*20,resolution) << std::endl;
  std::cout <<"MakeChromPeakPDF((timeBin-100)*0.1,distance,resolution) = " << MakeChromPeakPDF((timeBin-100)*0.1,distance,resolution) << std::endl;
  std::cout <<"MakeChromPeakPDF(timeResid,(0*100+distBin)*20,resolution) = " << MakeChromPeakPDF(timeResid,(0*100+distBin)*20,resolution) << std::endl;
  std::cout <<"MakeChromPeakPDF(timeResid,(0*100+distBin)*20,resBin*0.05) = " << MakeChromPeakPDF(timeResid,(0*100+distBin)*20,resBin*0.05) << std::endl;
  std::cout <<"histo... valueChrom[distBin][timeBin][resBin] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin,resBin)) << std::endl;
  
  std::cout <<"histo... valueChrom[distBin+1][timeBin][resBin] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin,resBin)) << std::endl;
  std::cout <<"histo... valueChrom[distBin][timeBin+1][resBin] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin+1,resBin)) << std::endl;
  std::cout <<"histo... valueChrom[distBin][timeBin][resBin+1] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin,resBin+1)) << std::endl;
  std::cout <<"histo... valueChrom[distBin+1][timeBin+1][resBin] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin+1,resBin)) << std::endl;
  std::cout <<"histo... valueChrom[distBin+1][timeBin][resBin+1] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin,resBin+1)) << std::endl;
  std::cout <<"histo... valueChrom[distBin][timeBin+1][resBin+1] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin+1,resBin+1)) << std::endl;
  std::cout <<"histo... valueChrom[distBin+1][timeBin+1][resBin+1] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin+1,resBin+1)) << std::endl;

  std::cout <<"histo... valueChrom[distBin-1][timeBin][resBin] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin,resBin)) << std::endl;
  std::cout <<"histo... valueChrom[distBin][timeBin-1][resBin] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin+1,resBin)) << std::endl;
  std::cout <<"histo... valueChrom[distBin][timeBin][resBin-1] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin,resBin+1)) << std::endl;
  std::cout <<"histo... valueChrom[distBin-1][timeBin-1][resBin] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin+1,resBin)) << std::endl;
  std::cout <<"histo... valueChrom[distBin-1][timeBin][resBin-1] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin,resBin+1)) << std::endl;
  std::cout <<"histo... valueChrom[distBin][timeBin-1][resBin-1] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin,timeBin+1,resBin+1)) << std::endl;
  std::cout <<"histo... valueChrom[distBin-1][timeBin-1][resBin-1] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin-1,timeBin-1,resBin-1)) << std::endl;
  
  std::cout <<"histo... valueChrom[distBin+2][timeBin+2][resBin+2] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+2,timeBin+2,resBin+2)) << std::endl;  


  //return probability;
  return hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(distBin+1,timeBin+1,resBin+1));
 */
 
 Int_t binD = hChromPDF3D->GetXaxis()->FindFixBin(distance/100.); //in m
 Int_t binT = hChromPDF3D->GetYaxis()->FindFixBin(timeResid);
 Int_t binR = hChromPDF3D->GetZaxis()->FindFixBin(resolution);
 /*
 if (distance < 1000 && timeResid < 10) {
 std::cout << "distance = " << distance << ", timeResid = " << timeResid << ", resolution = " << resolution << std::endl;
 std::cout << "binD = " << binD << ", binT = " << binT << ", binR = " << binR << std::endl;
 std::cout <<"histo... valueChrom[binD][binT][binR] = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(binD,binT,binR)) << std::endl;
 std::cout <<"MakeChromPeakPDF(timeResid,distance,resolution) = " << MakeChromPeakPDF(timeResid,distance,resolution) << std::endl;
 
 }
 */
 
 Double_t interpR;
 if (distance/100. < 0 || distance/100. > 100. || timeResid < -10. || timeResid > 50. || resolution < 0. || resolution > 3.0) {
 	//std::cout << "distance/100. = " << distance/100. << ", timeResid = " << timeResid << ", resolution = " << resolution << std::endl;
	//std::cout <<"MakeChromPeakPDF(timeResid,distance,resolution) = " << MakeChromPeakPDF(timeResid,distance,resolution) << std::endl;
 	interpR = 0;
 }
 else interpR = hChromPDF3D->Interpolate(distance/100.,timeResid,resolution);
 
 //std::cout << "interpolation = " << interpR << ", binContent = " << hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(binD,binT,binR)) << ", chromP = " <<  MakeChromPeakPDF(timeResid,distance,resolution) << std::endl;
 
 //return hChromPDF3D->GetBinContent(hChromPDF3D->GetBin(binD,binT,binR));
 return interpR;
  
}

//......................................................................
//Ioana...account for the tail...the chromatic effect is convoluted with a particluar function
Double_t WCSimTResidPDF::MakeChromFuncPDF(Double_t timeResid, Double_t distance, Double_t decayTime)
{
  Double_t probability = -999.0;

  //Parameters: timeResid = time residual, thedistance = photon distance, decayTime = decay time for scattered light
  Double_t thedistance = distance;
  Double_t decayT = decayTime;
  
  //get the index of refraction from WCSimParameters
  Double_t defaultN = WCSimParameters::RefractiveIndex(distance);

  //calculate the avgtransittime for light traveling thedistance
  Double_t defaulttransittime = thedistance*defaultN/(WCSimParameters::SpeedOfLight());
  
  //store the value corresponding to the time residual
  Double_t timeResP = 0.0;
  
  //sum of all weights
  Double_t sumweight = 0.0;
  Double_t funcweight = 0.0;
  
  //choose the range for the wavelengths
  Double_t minLambda = 200.0;
  Double_t maxLambda = 700.0;
  
  //loop over all possible wavelengths
  for (Double_t flmda = minLambda; flmda != maxLambda; flmda += 10.0) {
      
      // how much light of this particular color will make it accross thedistance, given an initial Cherenkov spectrum
      Double_t chromweight = WCSimWaterModel::Instance()->FinlSpect(flmda, thedistance);
      //std::cout << chromweight << std::endl;
      
      //calculate the transit time for this color
      Double_t chromtransittime = thedistance/(WCSimWaterModel::Instance()->Vg(flmda));
      //Double_t chromtransittime = thedistance*1.333/30.0;
      
      //calculate the timingresidual between the transit time for that color and the average transit time
      Double_t tresidchrom = chromtransittime-defaulttransittime;
      //Double_t tresidchrom = 0.0;
      
      //compute the function whihc needs to be evaluated for each wavelength
      Double_t function = (timeResid-tresidchrom)/(decayT*pow(1+4*pow((timeResid-tresidchrom)/decayT,2),2)) + exp(-(timeResid-tresidchrom)/decayT); 
      
      if( (chromweight*function)>=0.00000000001 ) timeResP += chromweight*function;
      if( chromweight>=0.00000000001 ) sumweight += chromweight;
      funcweight += function;
  
  }//end loop over colors
  //std::cout << sumweight << " " << timeResP << std::endl;
  
  //normalization over the wavelength range for the function "function"
  /*Double_t a = (timeResid -((thedistance/(WCSimWaterModel::Instance()->Vg(minLambda))) - defaulttransittime))/decayT;
  Double_t b = (timeResid -((thedistance/(WCSimWaterModel::Instance()->Vg(maxLambda))) - defaulttransittime))/decayT;
  Double_t funcNormalization = exp(-a) - exp(-b) + (1/8)*(1/(1+4*pow(a,2)) - 1/(1+4*pow(b,2)));*/
  Double_t funcNormalization = 8.0/(9.0*decayT); 
  
  
  //std::cout << "timeResP = " << timeResP << std::endl;
  //std::cout << "thedistance= " << thedistance << std::endl;
  //std::cout <<"thedistance/(WCSimWaterModel::Instance()->Vg(minLambda)) = " << thedistance/(WCSimWaterModel::Instance()->Vg(minLambda)) << ", thedistance/(WCSimWaterModel::Instance()->Vg(maxLambda)) = " << thedistance/(WCSimWaterModel::Instance()->Vg(maxLambda)) << std::endl;
  //std::cout << "a= " << a << ", b = " << b << ", funcNormalization = " << funcNormalization << std::endl; 
  
  if (funcNormalization != 0 && sumweight != 0) 
    probability = (timeResP*funcNormalization)/(sumweight);
    //std::cout << timeResP << " " << funcNormalization << " " << sumweight << " " << probability << std::endl;}
  //probability = timeResP/(sumweight*funcweight);
  else probability = timeResP;

  return probability;
  
}

//Tian... replace Gaussian with the landau distr.
//not used for the moment
Double_t WCSimTResidPDF::MakeChromLandauPDF(Double_t timeResid, Double_t distance, Double_t res)
{
  Double_t probability = -999.0;

  //Parameters: timeResid = time residual, thedistance = photon distance, pmtres = time resolution
  Double_t thedistance = distance;
  Double_t pmtres = res;
  
  //get the index of refraction from WCSimParameters
  Double_t defaultN = WCSimParameters::RefractiveIndex(distance);

  //calculate the avgtransittime for light traveling thedistance
  Double_t defaulttransittime = thedistance*defaultN/(WCSimParameters::SpeedOfLight());
  
  //store the value corresponding to the time residual
  Double_t timeResP = 0.0; 
  //sum of all weights
  Double_t sumweight= 0.0;
  Double_t gaussweight = 0.0;
  Double_t Nmid = 0.0;
  
  //choose the range for the wavelengths
  Double_t minLambda = 200.0;
  Double_t maxLambda = 700.0;
	
  //loop over all possible wavelengths
  for (Double_t flmda = minLambda; flmda != maxLambda; flmda += 50.0) {
      
      // how much light of this particular color will make it accross thedistance, given an initial Cherenkov spectrum
      Double_t chromweight = WCSimWaterModel::Instance()->FinlSpect(flmda, thedistance);
      
      //calculate the transit time for this color
      Double_t chromtransittime = thedistance/(WCSimWaterModel::Instance()->Vg(flmda));
 
      //calculate the timingresidual between the transit time for that color and the average transit time
      Double_t tresidchrom = chromtransittime-defaulttransittime;
 
      Double_t haha = chromweight*(TMath::Landau(timeResid-tresidchrom,0.0,pmtres,1));
      if( haha>= 0.00000000001 ) timeResP += haha;
      if( chromweight>0.00000000001 ) sumweight += chromweight;      
      gaussweight += TMath::Landau(timeResid-tresidchrom,0.0,pmtres,1);

      Nmid += WCSimWaterModel::Instance()->N_Index(flmda);
  }//end loop over colors
  
  //normalization over the wavelength range = taken to be Gauss normalization for all space
  if (sumweight != 0) {
     probability = timeResP/(sumweight*pmtres*sqrt(2*TMath::Pi()));
  }
  else {probability = timeResP; 
  }
  
  return probability;
  
}


//Matt function..extract distance array from a Cherenkov Ring from a point d away from the vertex, at a given lamda of light.

TH1D* WCSimTResidPDF::GetDistanceArray(Double_t thebeta, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ,  Double_t DetH, Double_t DetR){

  theLhist->Reset();
  theDistanceHist->Reset();

  Int_t Nsteps = 45;
  Double_t StepSize = 2*3.14159265358979323846/((Double_t) Nsteps);

  Double_t Ltrack = 0.;
 
  for(int i=0; i<200; i++){

    Double_t PhiLoop = 0.;
    
    for(int j=0; j<Nsteps; j++){

      Double_t flamda = 300.;
      Double_t Lamdaprob=0;

      Double_t distarray[150];
      Double_t wtarray[150];

      Double_t Cangle_default = (WCSimParameters::CherenkovAngle())*(TMath::Pi()/180.0);;

      for(int k=0; k<150; k++){

	Double_t theNdex =  WCSimWaterModel::Instance()->N_Index(flamda);

	Double_t Cangle = acos(1/(thebeta*theNdex));

	Double_t theD = GetDistanceFromWall(Cangle, Ltrack, PhiLoop, vtxX, vtxY, vtxZ, dirX, dirY, dirZ, DetH, DetR);

	//	std::cout<<theD<<" "<<DetH<<" "<<DetR<<" "<<vtxX<<" "<<vtxY<<" "<<vtxZ<<std::endl;

	Double_t Rreal = theD*sin(Cangle);
	Double_t Rreco = Rreal*( (tan(Cangle))/(tan(Cangle_default)) );
	Double_t delta_L = Rreal-Rreco;

	Double_t colweight = ((WCSimWaterModel::Instance()->FinlSpect(flamda,10*theD)));
	Double_t QEweight = WCSimWaterModel::Instance()->QE(flamda);

	Double_t cutoff=1.0;
	if((delta_L+Ltrack)>100.){
	  cutoff = exp((100-(delta_L+Ltrack))/10.);
	}

     	Double_t dres = 2.0;
	Double_t trueT = theD*theNdex/(WCSimParameters::SpeedOfLight());
	Double_t Dpred = theD*(sin(Cangle)/sin(Cangle_default));
	Double_t Ndefault = WCSimParameters::Index0(); //...chrom1.34, 1.333;
	Double_t predT = Dpred*Ndefault/(WCSimParameters::SpeedOfLight());
	Double_t timewt = (1/(dres*sqrt(2*3.141592653589793)))*exp( -((trueT-predT)*(trueT-predT))/(2*dres*dres) );

	theDistanceHist->Fill(theD);
	
	theLhist->Fill(delta_L + Ltrack,(colweight*QEweight*cutoff));

	flamda = flamda + 2;		
      }
      PhiLoop+=StepSize;
    }
    //    if(i%10==0) std::cout<<Ltrack<<std::endl;
    Ltrack = Ltrack + 5;
  }

  //  return theDistanceHist;
  return theLhist;
}



//Matt function...extract distance of Cherenkov ring from a point along the track, as a function of angle around the track

Double_t WCSimTResidPDF::GetDistanceFromWall(Double_t Cangle, Double_t Ltrack, Double_t thephi, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ,  Double_t DetH, Double_t DetR){

  TVector3 Dvect(dirX,dirY,dirZ);
  Double_t Dmag = Dvect.Mag();
  TVector3 paradir = (1/Dmag)*Dvect;
  TVector3 Ydir(0.0,1.0,0.0);
  TVector3 Zdir(0.0,0.0,1.0);
  TVector3 pdu = (paradir.Cross(Ydir));
  if( (paradir.X()==0.0) && (paradir.Z()==0.0) ) {pdu = (paradir.Cross(Zdir));}
  else{pdu = (paradir.Cross(Ydir));}
  Double_t Pmag = pdu.Mag();
  TVector3 perpdir = (1/Pmag)*pdu;

  Double_t P0x = vtxX + Ltrack*(paradir.X());
  Double_t P0y = vtxY + Ltrack*(paradir.Y());
  Double_t P0z = vtxZ + Ltrack*(paradir.Z());
  TVector3 EmissionPoint(P0x,P0y,P0z);
  
  // calculate the pointing of this particular ray of Cherenkov light
  TVector3 CherenkRay = cos(Cangle)*paradir - sin(Cangle)*cos(thephi)*perpdir + sin(Cangle)*sin(thephi)*perpdir;
  // now we determine where the ray intersects with the wall of the detector

  Double_t crNorm = CherenkRay.Mag();
  CherenkRay = (1/crNorm)*CherenkRay;

  TVector3 CapIntersect;

  Double_t ta = CherenkRay.X()*CherenkRay.X() + CherenkRay.Y()*CherenkRay.Y();
  Double_t tb = 2*(CherenkRay.X()*EmissionPoint.X() + CherenkRay.Y()*EmissionPoint.Y());
  Double_t tc = EmissionPoint.X()*EmissionPoint.X() + EmissionPoint.Y()*EmissionPoint.Y() - DetR*DetR;

  Double_t scale_p = (-tb + sqrt(tb*tb - 4*ta*tc))/(2*ta);
  Double_t scale_m = (-tb - sqrt(tb*tb - 4*ta*tc))/(2*ta);

  TVector3 BarrelIntersect = EmissionPoint + scale_p*CherenkRay;
  TVector3 BarrelIntersect2 = EmissionPoint + scale_m*CherenkRay;

  //Is the intersection point on the end cap?

  TVector3 DetIntersect = BarrelIntersect;

  if(BarrelIntersect.Z()>DetH){
    Double_t capscale = (DetH-EmissionPoint.Z())/(CherenkRay.Z());
    TVector3 CapIntersect = EmissionPoint + capscale*CherenkRay;
    DetIntersect = CapIntersect;
  }

  if(BarrelIntersect.Z()<-DetH){
    Double_t capscale = (EmissionPoint.Z() + DetH)/(CherenkRay.Z());
    TVector3 CapIntersect = EmissionPoint + capscale*CherenkRay;
    DetIntersect = CapIntersect;
  }

  Double_t theDist = (DetIntersect - EmissionPoint).Mag();    
  return theDist;
}






//Andy function... old version
Double_t WCSimTResidPDF::MakeChromDecayPDF(Double_t timeResid, Double_t distance, Double_t res)
{
  Double_t probability = -999.0;

  //Parameters: timeResid = time residual, thedistance = photon distance, pmtres = time resolution
  Double_t thedistance = distance;
  Double_t pmtres = res;
  
  //get the index of refraction from WCSimParameters
  Double_t defaultN = WCSimParameters::RefractiveIndex(distance);

  //calculate the avgtransittime for light traveling thedistance
  Double_t defaulttransittime = thedistance*defaultN/(WCSimParameters::SpeedOfLight());
  
  //store the value corresponding to the time residual
  Double_t timeResP = 0.0; 
  //sum of all weights
  Double_t sumweight= 0.0;
  Double_t gaussweight = 0.0;
  Double_t Nmid = 0.0;
  
  //choose the range for the wavelengths
  Double_t minLambda = 200.0;
  Double_t maxLambda = 700.0;
	
  //loop over all possible wavelengths
  for (Double_t flmda = minLambda; flmda != maxLambda; flmda += 50.0) {
      
      // how much light of this particular color will make it accross thedistance, given an initial Cherenkov spectrum
      Double_t chromweight = WCSimWaterModel::Instance()->FinlSpect(flmda, thedistance);
      
      //calculate the transit time for this color
      Double_t chromtransittime = thedistance/(WCSimWaterModel::Instance()->Vg(flmda));
 
      //calculate the timingresidual between the transit time for that color and the average transit time
      Double_t tresidchrom = chromtransittime-defaulttransittime;
 
      //uble_t haha = chromweight*(TMath::Landau(timeResid-tresidchrom,0.0,pmtres,1));
      Double_t haha = 0.0;
      if( (timeResid-tresidchrom)>=0.0 ) haha = chromweight*(TMath::Exp((timeResid-tresidchrom)/pmtres)/pmtres);
      if( haha>= 0.00000000001 ) timeResP += haha;
      if( chromweight>0.00000000001 ) sumweight += chromweight;      
      gaussweight += TMath::Landau(timeResid-tresidchrom,0.0,pmtres,1);
      gaussweight += exp(-(timeResid-tresidchrom)/pmtres)/pmtres;

      Nmid += WCSimWaterModel::Instance()->N_Index(flmda);
  }//end loop over colors
  
  //normalization over the wavelength range = taken to be Gauss normalization for all space
  if (sumweight != 0) {
     probability = timeResP/(sumweight*pmtres*sqrt(2*TMath::Pi()));
  }
  else {probability = timeResP; 
  }
  
  return probability;
  
}

//......................................................................

//Andy function... old version
void WCSimTResidPDF::MakeGaussPeakPDF(Double_t pmtres)
{
  TH1D* hTResidDist = new TH1D("tresdist","Time Residual Distribution",2000,-10.,10.);

  Double_t nsigma = 8.;
  Double_t gstepsize = 0.001;
  Double_t nsteps = (nsigma/2.0)/gstepsize;
  Double_t gsmearstep = 0.;

  for(int j = 0; j < nsteps; j++){

    hTResidDist->Fill(gsmearstep, (TMath::Gaus(gsmearstep,0.,pmtres)));
    if(gsmearstep > 0.) hTResidDist->Fill(-gsmearstep,(TMath::Gaus(gsmearstep,0.,pmtres)));
    
    gsmearstep += gstepsize;
    
  }

  Double_t norm = hTResidDist->Integral();
  if(norm != 0.) hTResidDist->Scale(1/norm);
  
  hPeakPDF = hTResidDist;
}

//......................................................................
//Andy function... old version
void WCSimTResidPDF::MakeNoisePDF()
{
  TH1D* hTResidDist = new TH1D("trd","trd",2000,-10.,10.);

  for(int j = 0; j < ((hTResidDist->GetNbinsX())+1); j++){
  
    hTResidDist->SetBinContent((j+1),1.);
  }

  Double_t norm = hTResidDist->Integral();
  if(norm != 0) hTResidDist->Scale(1/norm);
  
  hNoisePDF = hTResidDist;
}

//......................................................................
//Andy
TH1D* WCSimTResidPDF::GetPDFhist(int which)
{
  if(which==0) return hPeakPDF;
  if(which==1) return hNoisePDF;
  if(which==2) return hScatPDF;
  return hTotalPDF;
}

//......................................................................
//Andy
void WCSimTResidPDF::MakeTotalPDF(Double_t peakfrac, Double_t noisefrac, Double_t scatfrac)
{

  //  hTotalPDF = peakfrac*hPeakPDF + noisefrac*hNoisePDF + scatfrac*hFracPDF;
  hTotalPDF = hPeakPDF;
}

//......................................................................

Double_t WCSimTResidPDF::EvalTResidPDF(Double_t tresidval)
{
  return hTotalPDF->Interpolate(tresidval);
}

//......................................................................
//Andy
Double_t WCSimTResidPDF::DoSimpleComparison(Double_t tresid)
{
  Double_t FOM=0;
  return FOM;
}

//......................................................................
//Andy
Double_t WCSimTResidPDF::DoParamComparison(Double_t tresid)
{
  Double_t FOM=0;
  return FOM;
}

//......................................................................
//Andy
Double_t WCSimTResidPDF::DoLandauGaussComparison(Double_t tresid)
{
  Double_t FOM=0;
  return FOM;
}

//......................................................................
//Andy
Double_t  WCSimTResidPDF::DoFullComparison(Double_t tresid)
{
  Double_t FOM=0;
  return FOM;
}

//////////////////////////////////////////////////////////////////////////////////

