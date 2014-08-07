#ifndef SANDBOXSIMPLETOYTRACKS_HH
#define SANDBOXSIMPLETOYTRACKS_HH

#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TObject.h"
#include "WCSimRecoCluster.hh"
#include "WCSimWaterModel.hh"
#include <iostream>
#include <vector>

class SandBoxSimpleToyTracks : public TObject {
  
public: 
  
  SandBoxSimpleToyTracks(double tsmear, bool chromsmear, char* fname);
  ~SandBoxSimpleToyTracks();
  
  void makeSingleTrack(std::vector<double> vtx, double trkthet, double tracklength, double startlight, double Dscale, double photsperlength);
  TH2D* makefile(char* fname);
  std::vector<double> calchitdetails(std::vector<double> vtx, double mp,double tht,double s1,double dist, double lN);
  std::vector<double> intersectionpoint(std::vector<double> vtx, double tht, double mp, double s1, double Cangle, double dist, double lN);
  
    void Reset();
  
private: 
  
  WCSimWaterModel *_theWM;
  double _n,_c;
  bool _dochromsmear;
  double _timesmear;
  std::fstream* resultfile;
  ClassDef(SandBoxSimpleToyTracks,0)
    
};

#endif
