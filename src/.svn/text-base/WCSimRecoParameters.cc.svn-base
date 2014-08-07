#include "WCSimRecoParameters.hh"

#include "WCSimGeometry.hh"

#include <cmath>
#include <iostream>
#include <cassert>

ClassImp(WCSimRecoParameters)

static WCSimRecoParameters* fgRecoParameters = 0;

WCSimRecoParameters* WCSimRecoParameters::Instance()
{
  if( !fgRecoParameters ){
    fgRecoParameters = new WCSimRecoParameters();
  }

  if( !fgRecoParameters ){
    assert(fgRecoParameters);
  }

  if( fgRecoParameters ){

  }

  return fgRecoParameters;
}
  
WCSimRecoParameters::WCSimRecoParameters()
{
  std::cout << " *** WCSimRecoParameters::WCSimRecoParameters() *** " << std::endl;

  fUseSimpleTimeResolution = 0;
  fUseSimpleTimeSlew = 0;
  fUseSimpleRefractiveIndex = 0;
}

WCSimRecoParameters::~WCSimRecoParameters()
{

}
  
void WCSimRecoParameters::UseSimpleParameters()
{
  WCSimRecoParameters::UseSimpleTimeResolution();
  WCSimRecoParameters::UseSimpleTimeSlew();
  WCSimRecoParameters::UseSimpleRefractiveIndex();
}

void WCSimRecoParameters::UseSimpleTimeResolution()
{
  WCSimRecoParameters::Instance()->SetSimpleTimeResolution();
}

void WCSimRecoParameters::UseSimpleTimeSlew()
{
  WCSimRecoParameters::Instance()->SetSimpleTimeSlew();
}

void WCSimRecoParameters::UseSimpleRefractiveIndex()
{
  WCSimRecoParameters::Instance()->SetSimpleRefractiveIndex();
}

Double_t WCSimRecoParameters::TimeResolution(Double_t Q)
{
  if( WCSimRecoParameters::Instance()->SimpleTimeResolution() ){
    return WCSimRecoParameters::Instance()->GetSimpleTimeResolution(Q);
  }
  else {
    return WCSimRecoParameters::Instance()->GetTimeResolution(Q);
  }
}

Double_t WCSimRecoParameters::TimeSlew(Double_t Q)
{
  if( WCSimRecoParameters::Instance()->SimpleTimeSlew() ){
    return WCSimRecoParameters::Instance()->GetSimpleTimeSlew();
  }
  else{
    return WCSimRecoParameters::Instance()->GetTimeSlew(Q);
  }
}

Double_t WCSimRecoParameters::RefractiveIndex(Double_t L)
{
  if( WCSimRecoParameters::Instance()->SimpleRefractiveIndex() ){
    return WCSimRecoParameters::Instance()->GetSimpleRefractiveIndex();
  }
  else{
    return WCSimRecoParameters::Instance()->GetRefractiveIndex(L);
  }
}

void WCSimRecoParameters::PrintParameters()
{
  WCSimRecoParameters::Instance()->RunPrintParameters();
}

void WCSimRecoParameters::RunPrintParameters()
{
  std::cout << " *** WCSimRecoParameters::PrintParameters() *** " << std::endl;

  std::cout << "  Reco Parameters: " << std::endl
            << "   UseSimpleTimeResolution = " << fUseSimpleTimeResolution << std::endl
            << "   UseSimpleTimeSlew = " << fUseSimpleTimeSlew << std::endl
            << "   UseSimpleRefractiveIndex = " << fUseSimpleRefractiveIndex << std::endl;

  return;
}

Double_t WCSimRecoParameters::GetTimeResolution(Double_t Q)
{  
  /*
   // Old Parameterisation (lifted from WCSim)
   // ========================================
   Double_t qpes = Q;
   if( qpes<0.5 ) qpes = 0.5;
   if( qpes>32.0 ) qpes = 32.0;
   Double_t res = 0.33 + sqrt(2.0/qpes);  
  */

  Double_t qpes = Q;
  if( qpes<0.25 ) qpes = 0.25;
  if( qpes>40.0 ) qpes = 40.0;

  Double_t c0 = +0.271;
  Double_t c1 = +3.037;
  Double_t c2 = +2.543;

  Double_t res = c0 
               + c1/sqrt(qpes) 
               + c2/qpes;
  
  return res;
}

Double_t WCSimRecoParameters::GetTimeSlew(Double_t Q)
{
  Double_t qpes = Q;
  if( qpes<0.25 ) qpes = 0.25;
  if( qpes>40.0 ) qpes = 40.0;

  Double_t c0 = +3.406;
  Double_t c1 = -2.423;
  Double_t c2 = +0.335;

  Double_t dt = c0 
              + c1*log(qpes) 
              + c2*log(qpes)*log(qpes);

  return dt;
}

Double_t WCSimRecoParameters::GetRefractiveIndex(Double_t r)
{
  Double_t c = 29.98;
  Double_t n0 = WCSimParameters::Index0(); //...chrom1.38
  Double_t L0 = 40.0;
  Double_t dndx = 0.00014;

  Double_t L = r/c;

  Double_t n = n0*(1.0+dndx*(L-L0));;
  
  return n;
}

Double_t WCSimRecoParameters::GetSimpleTimeResolution(Double_t Q)
{  
  Double_t qpes = Q;
  if( qpes<0.25 ) qpes = 0.25;
  if( qpes>64.0 ) qpes = 64.0;

  Double_t res = 2.0/sqrt(qpes);

  return res;
}
