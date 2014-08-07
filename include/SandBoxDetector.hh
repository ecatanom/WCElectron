#ifndef SANDBOXDETECTOR_HH
#define SANDBOXDETECTOR_HH

#include "TObject.h"
#include "TObject.h"
#include "WCSimRecoDigit.hh"
#include "WCSimGeometry.hh"
#include "SandBoxPhotoTubeModel.hh"
#include "SandBoxPhotoTubeGeo.hh"
#include "WCSimRecoObjectTable.hh"
#include "WCSimRecoDigit.hh"
#include "WCSimRecoCluster.hh"
#include "WCSimTrueLightCluster.hh"
#include "WCSimTrueLight.hh"
#include <vector>


class SandBoxDetector : public TObject {

 public: 

  SandBoxDetector();
  SandBoxDetector(WCSimGeometry* thegeo, SandBoxPhotoTubeGeo* photodet);
  SandBoxDetector(WCSimGeometry* thegeo);

  ~SandBoxDetector();

  void SetDetectorGeometry(WCSimGeometry* thegeo);
  void SetDetectorGeometry(int type, double d1, double d2, double d3, double clearance);
  void SetPMTarrays(SandBoxPhotoTubeGeo* pmtgeo, double coverage);

  WCSimRecoCluster* GetTruePMTHits(WCSimRecoCluster* theHits);
  WCSimRecoCluster* GetTruePMTHits(WCSimTrueLightCluster* theHits);
  //  WCSimRecoCluster* GetTruePMTHits(WCSimTrueLightCluster* theHits, SandBoxStepper* stepfunction);
 
  WCSimRecoCluster* GetSmearedPMTHits(WCSimRecoCluster* theHits, SandBoxPhotoTubeModel* pmtmodel);
  WCSimRecoCluster* GetSmearedPMTHits(WCSimTrueLightCluster* theHits, SandBoxPhotoTubeModel* pmtmodel);
  //  WCSimRecoCluster* GetSmearedPMTHits(WCSimTrueLightCluster* theHits, SandBoxPhotoTubeModel* pmtmodel, SandBoxStepper* stepfunction);

  int GetPMTnumber(int hitnumber);
  int GetPMThitcount(int pmtnumber);

 private: 

  //booleans to keep track of what's been done
  bool _initiatedDetectorGeo;
  bool _createdPMTarray;
  bool _pmtsapplied;
  bool _spatialresolving;
  bool _timeresolving;

  //detector geometry parameters
  int _detectortype;
  double _d1; // diameter if cylindrical
  double _d2;
  double _d3; // only used for mailbox geometry
  double _clearance;

  //parameters to model individual PMTs

  SandBoxPhotoTubeGeo* _pmtgeo;

  //parameters for PMT Array
  double _spatialcoverage;
  double _zspacing,_pspacing,_capspacing; //for cylindrical geometry
  double _d1spacing,_d2spacing,_d3spacing; //for mailbox geometry
  double corner[6];
  int **topCapMap,**botCapMap,**BarMap; // for cylindrical geometry
  int **topMap,**botMap,**frontMap,**backMap,**leftMap,**rightMap; // for mailbox geometry
  int _NPMTs;
  vector< vector<double> > PMTcenters;
  vector< vector<double> > PMThits;
  vector<double> PMThitcount;
  vector<int> isOnPMT;
  vector<int> PMTnumber;

  //the main data structures
  vector< vector<double> > theHits;

  ClassDef(SandBoxDetector,0)

};

#endif
