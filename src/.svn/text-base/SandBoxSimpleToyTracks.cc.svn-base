#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TObject.h"
#include "WCSimRecoCluster.hh"
#include "WCSimWaterModel.hh"
#include "SandBoxSimpleToyTracks.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include "TRandom3.h"

using namespace std;

ClassImp(SandBoxSimpleToyTracks);

SandBoxSimpleToyTracks::SandBoxSimpleToyTracks(double tsmear, bool docsmear, char* fname)
{
  _timesmear=tsmear;
  _dochromsmear=docsmear;

  resultfile = new std::fstream(fname,std::ios::out); 
}

SandBoxSimpleToyTracks::~SandBoxSimpleToyTracks(){

  resultfile->close();
}

void SandBoxSimpleToyTracks::Reset()
{
}

TH2D* SandBoxSimpleToyTracks::makefile(char* fname)
{
  _theWM = WCSimWaterModel::Instance();
  //  cout<<myWM<<endl;
  _theWM->N_Index(222);
  

  TH1D* cherenkovspectrum = new TH1D("cspec","cspec",434,265.5,700.5);
  for(int i=266; i<700; i++){

    double wavelength = (double)i;
    double cwt = _theWM->InitSpect(wavelength);
    cherenkovspectrum->SetBinContent((i-265),cwt);
    //    cout<<cwt<<endl;
  }


  cout<<"C Spect: "<<cherenkovspectrum->Integral()<<endl;

  int ntrks=2;
  double smrmag=_timesmear;

  _n=1.34689;
  _c=299.792458;
  
  std::fstream* resultfile = new std::fstream(fname,std::ios::out);  

  TH2D* ring = new TH2D("ring","ring",100,-10000.,10000.,100,-10000.,10000.);
  //  TH1D* tdst = new TH1D("td","td",100,0.,20.);


  // double xEnd,yEnd,zEnd,tEnd,wt,tsmr;
  double tsmr;

  TRandom3* mr1 = new TRandom3(23433);
  TRandom3* mr2 = new TRandom3(44433);
  TRandom3* mr3 = new TRandom3(52433);
  TRandom3* mr4 = new TRandom3(12433);
  TRandom3* mr5 = new TRandom3(22233);

  TRandom3* pf1 = new TRandom3(21233);
  TRandom3* pf2 = new TRandom3(21883);




  TH1D* iofdist = new TH1D("iofhist","iofhist",100,1.,3.);

  for(int i=0; i<170000; i++){

    if(i%10000==0) cout<<i<<endl;
    tsmr=0;

    double theN;
    double randwavelength;
    if(_dochromsmear){
      randwavelength = cherenkovspectrum->GetRandom();
      theN = _theWM->N_Index(randwavelength);
    }
    else theN=_n;

    iofdist->Fill(theN);

    double s1a = 1000.*(mr1->Rndm());
    double mphia = (2*3.14159265)*(mr2->Rndm());
    double thetaa = -0.2*(mr3->Rndm());
    thetaa = 0.2;
    double conversionpointa = 100*(mr4->Rndm());
    //    conversionpointa = 0.;

    vector<double> hypvtx;
    hypvtx.push_back(0.); hypvtx.push_back(0.); hypvtx.push_back(0.); hypvtx.push_back(0.);
    vector<double> ra = calchitdetails(hypvtx,mphia,thetaa,s1a,1000.,theN);
    double xa=ra.at(0);
    double ya=ra.at(1);
    double za=ra.at(2);
    double ta=ra.at(3);
    double s2length=ra.at(4);
    //cout << setprecision(16);

    if(smrmag>0) tsmr = smrmag*(mr5->Gaus(0.,1.));

    if( s1a>conversionpointa ){
      ring->Fill(ya,za);
      double pass, attenuation; 
      if(_dochromsmear){
	attenuation = (_theWM->Atten(randwavelength,s2length));
	pass = (pf1->Rndm());
      }
      else{
	attenuation = 1.;
	pass=0;
      }
      // cout<<"pp "<<pass<<" "<<attenuation<<endl;
      if(pass<attenuation){
	(*resultfile)<<xa<<" "<<ya<<" "<<za<<" "<<(ta+(s1a/_c)+tsmr)<<" "<<theN<<endl;
      }
    }

    if(ntrks>1){

      double s1b = 1000.*(mr1->Rndm());
      double mphib = (2*3.14159265)*(mr2->Rndm());
      double thetab=thetaa+0.25;
      double conversionpointb = 150*(mr4->Rndm());
      //      conversionpointb = 200;

      vector<double> rb = calchitdetails(hypvtx,mphib,thetab,s1b,1000.,theN);
      double xb=rb.at(0);
      double yb=rb.at(1);
      double zb=rb.at(2);
      double tb=rb.at(3);
      double s2length=rb.at(4);

      if(smrmag>0) tsmr = smrmag*(mr5->Gaus(0.,1.));
      
      if( s1b>conversionpointb ){
	ring->Fill(yb,zb);
	double pass, attenuation; 
	if(_dochromsmear){
	  attenuation = (_theWM->Atten(randwavelength,s2length));
	  pass = (pf2->Rndm());
	}
	else{
	  attenuation = 1.;
	  pass=0;
	}

	if(pass<attenuation){
	  (*resultfile)<<xb<<" "<<yb<<" "<<zb<<" "<<(tb+(s1b/_c)+tsmr)<<" "<<theN<<endl;
	}
      }
    }
  }

  cout<<"avg index of refraction: "<<iofdist->GetMean()<<endl;
   
  //   gROOT->SetStyle("Plain"); 

  //   gStyle->SetPalette(1);
  return ring;
}






void SandBoxSimpleToyTracks::makeSingleTrack(vector<double> vtx, double trkthet, double tracklength, double startlight, double Dscale, double photsperlength)
{
  int Nphot = (int)(tracklength*photsperlength);

  _theWM = WCSimWaterModel::Instance();
  //  cout<<myWM<<endl;
  _theWM->N_Index(222);
  

  TH1D* cherenkovspectrum = new TH1D("cspec","cspec",434,265.5,700.5);
  for(int i=266; i<700; i++){

    double wavelength = (double)i;
    double cwt = _theWM->InitSpect(wavelength);
    cherenkovspectrum->SetBinContent((i-265),cwt);
    //    cout<<cwt<<endl;
  }

  cout<<"C Spect: "<<cherenkovspectrum->Integral()<<endl;

  double smrmag=_timesmear;

  _n=1.34689;
  _c=299.792458;
  
  // TH2D* ring = new TH2D("ring","ring",100,-10000.,10000.,100,-10000.,10000.);
  //  TH1D* tdst = new TH1D("td","td",100,0.,20.);


  //  double xEnd,yEnd,zEnd,tEnd,wt,tsmr;
  double tsmr;

  TRandom3* mr1 = new TRandom3(23433);
  TRandom3* mr2 = new TRandom3(44433);
  //  TRandom3* mr3 = new TRandom3(52433);
  //  TRandom3* mr4 = new TRandom3(12433);
  TRandom3* mr5 = new TRandom3(22233);

  TRandom3* pf1 = new TRandom3(21233);
  //  TRandom3* pf2 = new TRandom3(21883);

  TH1D* iofdist = new TH1D("iofhist","iofhist",100,1.,3.);

  for(int i=0; i<Nphot; i++){

    if(i%10000==0) cout<<i<<endl;
    tsmr=0;

    double theN;
    double randwavelength;
    if(_dochromsmear){
      randwavelength = cherenkovspectrum->GetRandom();
      theN = _theWM->N_Index(randwavelength);
    }
    else theN=_n;

    iofdist->Fill(theN);

    double s1a = tracklength*(mr1->Rndm());
    double mphia = (2*3.14159265)*(mr2->Rndm());
    double thetaa = trkthet;
    double conversionpointa = startlight;
    //    double conversionpointa = 100*(mr4->Rndm());
    //    conversionpointa = 0.;

    vector<double> ra = calchitdetails(vtx, mphia,thetaa,s1a,Dscale,theN);
 

    double xa=ra.at(0);
    double ya=ra.at(1);
    double za=ra.at(2);
    double ta=ra.at(3);
    double s2length=ra.at(4);
    //cout << setprecision(16);

    if(smrmag>0) tsmr = smrmag*(mr5->Gaus(0.,1.));

    if( s1a>conversionpointa ){
      //      ring->Fill(ya,za);
      double pass, attenuation; 
      if(_dochromsmear){
	attenuation = (_theWM->Atten(randwavelength,s2length));
	pass = (pf1->Rndm());
      }
      else{
	attenuation = 1.;
	pass=0;
      }
      // cout<<"pp "<<pass<<" "<<attenuation<<endl;
      if(pass<attenuation){
	(*resultfile)<<xa<<" "<<ya<<" "<<za<<" "<<(vtx.at(3)+ta+(s1a/_c)+tsmr)<<" "<<theN<<endl;
      }
    }
  }


  cout<<"avg index of refraction: "<<iofdist->GetMean()<<endl;
   
  //  gROOT->SetStyle("Plain"); 
  //  gStyle->SetPalette(1);
  //  return ring;
}






vector<double> SandBoxSimpleToyTracks::calchitdetails(vector<double> vtx, double mp,double tht,double s1,double dist, double lN)
{
    vector<double> hd;

    double nx,ny,nz,t2,s2;

    if( (((s1*sin(tht))+vtx.at(2))>dist) || (((s1*cos(tht))+vtx.at(0))>dist) ){

      nx=-555555.;
      ny=-555555.;
      nz=-555555.;
      t2=-555555.;
      s2=-555555.;
    }
    else{
 
      double Cangle = acos(1/lN);
      vector<double> hp = this->intersectionpoint(vtx, tht, mp, s1, Cangle, dist, lN);
      
      if( (hp.at(1)<dist) && (hp.at(2)<dist) ){
	nx = hp.at(0);
	ny = hp.at(1);
	nz = hp.at(2);
	t2 = hp.at(3);
	s2 = hp.at(4);
      }
	
      if( (hp.at(1)>dist) && (hp.at(2)<dist) ){

      }


      if( (hp.at(1)<dist) && (hp.at(2)>dist) ){

      }

      if( (hp.at(1)<dist) && (hp.at(2)>dist) && (hp.at(1)>hp.at(2)) ){
 
      
      }

     if( (hp.at(1)<dist) && (hp.at(2)>dist) && (hp.at(1)>hp.at(2)) ){
 
      
      }




    }

    hd.push_back(nx);
    hd.push_back(ny);
    hd.push_back(nz);
    hd.push_back(t2);
    hd.push_back(s2);
      
    return hd;
}


vector<double> SandBoxSimpleToyTracks::intersectionpoint(vector<double> vtx, double tht, double mp, double s1, double Cangle, double dist, double lN){

      double thetceff = atan( (tan(Cangle))*cos(mp) );
      double dx = (dist - (s1*cos(tht)) - vtx.at(0));
      //      double dh = ( ((dist-vtx.at(0))/(cos(tht))) - s1 );
      
      double dy = dx*(tan(Cangle))*sin(mp);
      double dz = (dx*(tan(tht + thetceff)));

      double Dx;
      double Dy = dy;
      double Dz = dz + (s1*sin(tht));
      
      double s2 = sqrt( dx*dx + dy*dy + dz*dz );
      double t2 = (s2*lN)/_c;
      double nx = dist;
      double ny = Dy + vtx.at(1);
      double nz = Dz + vtx.at(2);

      if( (fabs(ny)>dist) && (fabs(nz)<=dist) ){
	dy=dist-vtx.at(1);
	if(((tan(Cangle))*sin(mp))>0) dx=dy/((tan(Cangle))*sin(mp));
	else dx=0;
	dz=(dx*(tan(tht + thetceff))); 

	Dx = dx + (s1*cos(tht));
	Dz = dz + (s1*sin(tht));

	s2 = sqrt( dx*dx + dy*dy + dz*dz );
	t2 = (s2*lN)/_c;
	nx = Dx + vtx.at(0);
	if(ny>0)	ny = dist;
	else ny=-dist;
	nz = Dz + vtx.at(2);
      }

      if( (fabs(ny)<=dist) && (fabs(nz)>dist) ){

	dz=dist-vtx.at(1)-s1*sin(tht);
	if((tan(tht + thetceff))>0) dx=dz/(tan(tht + thetceff));
	else dx=0;
	dy = dx*(tan(Cangle))*sin(mp);

	Dx = dx + (s1*cos(tht));
	Dy = dy;

	s2 = sqrt( dx*dx + dy*dy + dz*dz );
	t2 = (s2*lN)/_c;
	nx = Dx + vtx.at(0);
	ny = Dy + vtx.at(1);
	if(nz>0) nz = dist;
	else nz=-dist;
      }

      if( (fabs(ny)>dist) && (fabs(nz)>dist) && (fabs(ny)>fabs(nz)) ){

	dz=dist-vtx.at(1)-s1*sin(tht);
	if((tan(tht + thetceff))>0) dx=dz/(tan(tht + thetceff));
	else dx=0;
	dy = dx*(tan(Cangle))*sin(mp);

	Dx = dx + (s1*cos(tht));
	Dy = dy;

	s2 = sqrt( dx*dx + dy*dy + dz*dz );
	t2 = (s2*lN)/_c;
	nx = Dx + vtx.at(0);
	ny = Dy + vtx.at(1);
	if(nz>0) nz = dist;
	else nz=-dist;
      }


      if( (fabs(ny)>dist) && (fabs(nz)>dist) && (fabs(ny)<fabs(nz)) ){

	dy=dist-vtx.at(1);
	if(((tan(Cangle))*sin(mp))>0) dx=dy/((tan(Cangle))*sin(mp));
	else dx=0;
	dz=(dx*(tan(tht + thetceff))); 

	Dx = dx + (s1*cos(tht));
	Dz = dz + (s1*sin(tht));

	s2 = sqrt( dx*dx + dy*dy + dz*dz );
	t2 = (s2*lN)/_c;
	nx = Dx + vtx.at(0);
	if(ny>0)	ny = dist;
	else ny=-dist;
	nz = Dz + vtx.at(2);
      }

      vector<double> hitpoint;
      hitpoint.push_back(nx);
      hitpoint.push_back(ny);
      hitpoint.push_back(nz);
      hitpoint.push_back(t2);
      hitpoint.push_back(s2);
      
      return hitpoint;
}
