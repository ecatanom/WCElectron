#include "WCSimCherenkovGeo.hh"
#include "WCSimMathUtil.hh"
#include "WCSimRootGeom.hh"
#include "WCSimParameters.hh"
#include "WCSimWaterModel.hh"

#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TMath.h"

#include <iostream>
#include <cmath>
#include <cassert>

ClassImp(WCSimCherenkovGeo)

void WCSimCherenkovGeo::MuonDistance(Double_t *start, Double_t *dir, Double_t *pos, Double_t phlmda, Double_t *fintersect, Double_t &fopenangle, Double_t &fdistmu, Double_t &fdistpho, Double_t &ftimemu, Double_t &ftimepho, Double_t &fD)
{ 
  Double_t ctc = WCSimParameters::CosThetaC();
  Double_t c = WCSimParameters::SpeedOfLight();
  Double_t Sub1[3];
  WCSimWaterModel *water = WCSimWaterModel::Instance();
  fspeed = water->Vg(phlmda);

  WCSimMathUtil::SubtractVec(pos,start,Sub1);
  Double_t prod1 = WCSimMathUtil::DotProduct(dir,Sub1);
  Double_t prod2 = WCSimMathUtil::DotProduct(Sub1,Sub1);
  Double_t prod3 = 1-WCSimMathUtil::sqr(ctc);
  fopenangle = acos(prod1/sqrt(prod2))*180/TMath::Pi();
  fD = WCSimMathUtil::Magnitude(start,pos);

  if (fopenangle < 42) 
   {
     Double_t arg_a = 1-WCSimMathUtil::sqr(ctc);
     Double_t arg_b = -2*prod1*prod3;
     Double_t arg_c = prod1*prod1 - prod2*ctc*ctc;

     Double_t firstSol;
     Double_t secondSol;
     Double_t det = WCSimMathUtil::Determinant(arg_a, arg_b, arg_c);
     WCSimMathUtil::RealRoots(arg_a, arg_b, sqrt(det), firstSol, secondSol);  

     if ((firstSol >= 0. && secondSol < 0.) || (firstSol >= 0. && secondSol >= firstSol)) 
       { 
         fdistmu = firstSol;
         for (Int_t ii=0; ii<3; ii++) fintersect[ii] = start[ii] + dir[ii]*firstSol;
         ftimemu = fdistmu/c;
         fdistpho = WCSimMathUtil::Magnitude(fintersect,pos);
         ftimepho = fdistpho/fspeed;
         std::cout << ftimepho << std::endl;
       }
     else if ((firstSol < 0. && secondSol >= 0.) || (secondSol >= 0. && firstSol >= secondSol)) 
       {
         fdistmu = secondSol;
         for (Int_t ii=0; ii<3; ii++) fintersect[ii] = start[ii] + dir[ii]*secondSol;
         ftimemu = secondSol/c;
         fdistpho = WCSimMathUtil::Magnitude(fintersect,pos); 
         ftimepho = fdistpho/fspeed;
         std::cout << ftimepho << std::endl;
       } 
     else { std::cout << "wrong; " << std::endl; }
     }
  else {std::cout << "wrong; " << std::endl;}
}


