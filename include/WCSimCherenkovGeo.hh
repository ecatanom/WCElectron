//the class contains some geometric calculation of cherenkov radiation. 
//By Tian Xin, ISU, txin@iastate.edu

#ifndef WCSIMCHERENKOVGEO_HH
#define WCSIMCHERENKOVGEO_HH

#include <cmath>
#include "TMath.h"

#include "TObject.h"

class WCSimCherenkovGeo : public TObject {

  public:
    WCSimCherenkovGeo(){}
    ~WCSimCherenkovGeo(){}

    void MuonDistance(Double_t *start, Double_t *dir, Double_t *pos, Double_t phlmda, Double_t *fintersect, Double_t &fopenangle, Double_t &fdistmu, Double_t &fdistpho, Double_t &ftimemu, Double_t &ftimepho, Double_t &fD);


  private:
    Double_t fspeed;

    ClassDef(WCSimCherenkovGeo,0)

};

#endif
