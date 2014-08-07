#include "SandBoxStepper.hh"
#include "WCSimTrueLight.hh"
#include "WCSimWaterModel.hh"
#include "TObject.h"

ClassImp(SandBoxStepper)


  SandBoxStepper::SandBoxStepper(WCSimWaterModel* opticalmodel){;}
SandBoxStepper::~SandBoxStepper(){;}

WCSimTrueLight* SandBoxStepper::SpaceSteppingAction(WCSimTrueLight* initlight, Double_t spacestepsize)
{
  WCSimTrueLight *nextstep = new WCSimTrueLight(0,0,0,0,0,0,0,0,0);
  return nextstep;
}
WCSimTrueLight* SandBoxStepper::TimeSteppingAction(WCSimTrueLight* initlight, Double_t timestepsize)
{
  WCSimTrueLight *nextstep = new WCSimTrueLight(0,0,0,0,0,0,0,0,0);
  return nextstep;
}


