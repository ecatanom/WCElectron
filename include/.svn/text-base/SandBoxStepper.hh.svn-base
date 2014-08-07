#ifndef SANDBOXSTEPPER_HH
#define SANDBOXSTEPPER_HH

#include "TObject.h"
#include "WCSimTrueLight.hh"
#include "WCSimWaterModel.hh"

class SandBoxStepper : public TObject {

 public: 

  SandBoxStepper(WCSimWaterModel* opticalmodel);
  ~SandBoxStepper();

  WCSimTrueLight* SpaceSteppingAction(WCSimTrueLight* initlight, Double_t spacestepsize);
  WCSimTrueLight* TimeSteppingAction(WCSimTrueLight* initlight, Double_t timestepsize);

 private: 

  ClassDef(SandBoxStepper,0)
};

#endif
