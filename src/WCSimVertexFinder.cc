#include "WCSimVertexFinder.hh"
#include "WCSimVertexGeometry.hh"

#include "WCSimInterface.hh"
#include "SandBoxDigitizer.hh"
#include "WCSimGeometry.hh"
#include "WCSimParameters.hh"

#include "WCSimRecoDigit.hh"
#include "WCSimRecoEvent.hh"
#include "WCSimTrueEvent.hh"
#include "WCSimHistos.hh"

#include "TStopwatch.h" // <----------
#include "TMath.h"

#include <cmath>
#include <iostream>
#include <cassert>

ClassImp(WCSimVertexFinder)

static WCSimVertexFinder* fgVertexFinder = 0;

static void point_position_chi2(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{
  Bool_t printDebugMessages = 0;

  Double_t vtxX = par[0]; // centimetres
  Double_t vtxY = par[1]; // centimetres
  Double_t vtxZ = par[2]; // centimetres

  Double_t vtime  = 0.0;
  Double_t fom = 0.0;

  fgVertexFinder->point_position_itr();
  fgVertexFinder->PointPositionChi2(vtxX,vtxY,vtxZ,
                                    vtime,fom);

  f = -fom; // note: need to maximize this fom

  if( printDebugMessages ){
    std::cout << " [point_position_chi2] [" << fgVertexFinder->point_position_iterations() << "] (x,y,z)=(" << vtxX << "," << vtxY << "," << vtxZ << ") vtime=" << vtime << " fom=" << fom << std::endl;
  }

  return;
}

static void point_direction_chi2(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{
  Bool_t printDebugMessages = 0;
  
  Double_t vtxX = fgVertexFinder->fVtxX;
  Double_t vtxY = fgVertexFinder->fVtxY;
  Double_t vtxZ = fgVertexFinder->fVtxZ;

  Double_t dirTheta = par[0]; // radians
  Double_t dirPhi   = par[1]; // radians
  
  Double_t dirX = sin(dirTheta)*cos(dirPhi);
  Double_t dirY = sin(dirTheta)*sin(dirPhi);
  Double_t dirZ = cos(dirTheta);

  Double_t vangle = 0.0;
  Double_t fom = 0.0;

  fgVertexFinder->point_direction_itr();
  fgVertexFinder->PointDirectionChi2(vtxX,vtxY,vtxZ,
                                     dirX,dirY,dirZ,
                                     vangle,fom);

  f = -fom; // note: need to maximize this fom

  if( printDebugMessages ){
    std::cout << " [point_direction_chi2] [" << fgVertexFinder->point_direction_iterations() << "] (px,py,pz)=(" << dirX << "," << dirY << "," << dirZ << ") fom=" << fom << std::endl;
  }

  return; 
}

static void point_vertex_chi2(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{
  Bool_t printDebugMessages = 0;
  
  Double_t vtxX     = par[0]; // centimetres
  Double_t vtxY     = par[1]; // centimetres
  Double_t vtxZ     = par[2]; // centimetres  

  Double_t dirTheta = par[3]; // radians
  Double_t dirPhi   = par[4]; // radians

  Double_t dirX = sin(dirTheta)*cos(dirPhi);
  Double_t dirY = sin(dirTheta)*sin(dirPhi);
  Double_t dirZ = cos(dirTheta);

  Double_t vangle = 0.0;
  Double_t vtime  = 0.0;
  Double_t fom = 0.0;

  fgVertexFinder->point_vertex_itr();
  fgVertexFinder->PointVertexChi2(vtxX,vtxY,vtxZ,
                                  dirX,dirY,dirZ,
                                  vangle,vtime,fom);

  f = -fom; // note: need to maximize this fom

  if( printDebugMessages ){
    std::cout << " [point_vertex_chi2] [" << fgVertexFinder->point_vertex_iterations() << "] (x,y,z)=(" << vtxX << "," << vtxY << "," << vtxZ << ") (px,py,pz)=(" << dirX << "," << dirY << "," << dirZ << ") vtime=" << vtime << " fom=" << fom << std::endl;
  }

  return;
}

static void extended_vertex_chi2(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{
  Bool_t printDebugMessages = 0;
  
  Double_t vtxX     = par[0]; // centimetres
  Double_t vtxY     = par[1]; // centimetres
  Double_t vtxZ     = par[2]; // centimetres  

  Double_t dirTheta = par[3]; // radians
  Double_t dirPhi   = par[4]; // radians

  Double_t dirX = sin(dirTheta)*cos(dirPhi);
  Double_t dirY = sin(dirTheta)*sin(dirPhi);
  Double_t dirZ = cos(dirTheta);

  Double_t vangle = 0.0;
  Double_t vtime  = 0.0;
  Double_t fom = 0.0;

  fgVertexFinder->extended_vertex_itr();
  
  fgVertexFinder->ExtendedVertexChi2(vtxX,vtxY,vtxZ,
                                     dirX,dirY,dirZ,
                                     vangle,vtime,fom);

  f = -fom; // note: need to maximize this fom

  if( printDebugMessages ){
    std::cout << " [extended_vertex_chi2] [" << fgVertexFinder->extended_vertex_iterations() << "] (x,y,z)=(" << vtxX << "," << vtxY << "," << vtxZ << ") (px,py,pz)=(" << dirX << "," << dirY << "," << dirZ << ") vtime=" << vtime << " fom=" << fom << std::endl;  
  
  }

  return;
}

static void vertex_time_fom(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{   
  Double_t vtxTime = par[0]; // nanoseconds

  Double_t fom = 0.0;

  fgVertexFinder->TimePropertiesFoM(vtxTime,fom);

  f = -fom; // note: need to maximize this fom

  return;
}

static void vertex_time_lnl(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{  
  Bool_t printDebugMessages = 0;
  
  Double_t vtxTime = par[0]; // nanoseconds
  Double_t vtxParam0 = fgVertexFinder->fFixTimeParam0;

  if( fgVertexFinder->fFitTimeParams ){
    vtxParam0 = par[1]; 
  }

  Double_t fom = 0.0;

  fgVertexFinder->time_fit_itr();
  
  fgVertexFinder->TimePropertiesLnL(vtxTime,vtxParam0,fom);

  f = -fom; // note: need to maximize this fom

  if( printDebugMessages ){
    std::cout << "  [vertex_time_lnl] [" << fgVertexFinder->time_fit_iterations() << "] vtime=" << vtxTime << " vparam=" << vtxParam0 << " fom=" << fom << std::endl;
  }

  return;
}

static void vertex_time_lnl_chrom(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{
  Bool_t printDebugMessages = 0;
  
  Double_t vtxTime = par[0]; // nanoseconds
  Double_t vtxParam0 = fgVertexFinder->fFixTimeParam0;

  if( fgVertexFinder->fFitTimeParams ){
    vtxParam0 = par[1]; 
  }

  Double_t fom = 0.0;

  fgVertexFinder->time_fit_itr();
  
  fgVertexFinder->TimePropertiesLnLchrom(vtxTime,vtxParam0,fom);

  f = -fom; // note: need to maximize this fom

  if( printDebugMessages ){
    std::cout << "  [vertex_time_lnl_chrom] [" << fgVertexFinder->time_fit_iterations() << "] vtime=" << vtxTime << " vparam=" << vtxParam0 << " fom=" << fom << std::endl;
  }

  return;
}

static void vertex_cone_lnl(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{
  Bool_t printDebugMessages = 0;
  
  Double_t vtxParam0 = fgVertexFinder->fFixConeParam0;
  Double_t vtxParam1 = fgVertexFinder->fFixConeParam1;
  Double_t vtxParam2 = fgVertexFinder->fFixConeParam2;

  if( fgVertexFinder->fFitConeParams ){
    vtxParam0 = par[0];
    vtxParam1 = par[1];
    vtxParam2 = par[2];
  }
 
  Double_t vangle = 0.0;
  Double_t fom = 0.0;

  fgVertexFinder->cone_fit_itr();
  fgVertexFinder->ConePropertiesLnL(vtxParam0,vtxParam1,vtxParam2,vangle,fom);

  f = -fom; // note: need to maximize this fom

  if( printDebugMessages ){
    std::cout << "  [vertex_cone_lnl] [" << fgVertexFinder->cone_fit_iterations() << "] vparam0=" << vtxParam0 << " vparam1=" << vtxParam1 << " vtxParam2=" << vtxParam2 << " fom=" << fom << std::endl;
  }

  return;
}

WCSimVertexFinder* WCSimVertexFinder::Instance()
{
  if( !fgVertexFinder ){
    fgVertexFinder = new WCSimVertexFinder();
  }

  if( !fgVertexFinder ){
    assert(fgVertexFinder);
  }

  if( fgVertexFinder ){

  }

  return fgVertexFinder;
}

void WCSimVertexFinder::LMuonDoubleFilter(Double_t maxLMuon) //erika 070313
{
  WCSimVertexFinder::Instance()->SetMaxLMuon(maxLMuon);
}

void WCSimVertexFinder::PointFitOnly(Bool_t yesno)
{
  WCSimVertexFinder::Instance()->SetPointFitOnly(yesno);
}

void WCSimVertexFinder::UseTrueVertex(Bool_t yesno)
{
  WCSimVertexFinder::Instance()->UsingTrueVertex(yesno);
}

void WCSimVertexFinder::UseTruePosition(Bool_t yesno)
{
  WCSimVertexFinder::Instance()->UsingTruePosition(yesno);
}

void WCSimVertexFinder::UseTrueDirection(Bool_t yesno)
{
  WCSimVertexFinder::Instance()->UsingTrueDirection(yesno);
}

void WCSimVertexFinder::SeedWithTrueVertex(Bool_t yesno)
{
  WCSimVertexFinder::Instance()->SeedingWithTrueVertex(yesno);
}

void WCSimVertexFinder::SeedWithSimpleVertex(Bool_t yesno)
{
  WCSimVertexFinder::Instance()->SeedingWithSimpleVertex(yesno);
}

void WCSimVertexFinder::SeedWithQuadruples(Bool_t yesno)
{
  WCSimVertexFinder::Instance()->SeedingWithQuadruples(yesno);
}

void WCSimVertexFinder::NumSeeds(Int_t nseeds)
{
  WCSimVertexFinder::Instance()->SetNumSeeds(nseeds);
}

void WCSimVertexFinder::FitWeights(Double_t tw, Double_t cw)
{
  WCSimVertexFinder::Instance()->SetFitWeights(tw,cw);
}

void WCSimVertexFinder::FixTimeParams(Double_t param0)
{
  WCSimVertexFinder::Instance()->SetFixTimeParams(param0);
}

void WCSimVertexFinder::FitTimeParams()
{
  WCSimVertexFinder::Instance()->SetFitTimeParams();
}  

void WCSimVertexFinder::FixConeParams(Double_t param0, Double_t param1, Double_t param2)
{
  WCSimVertexFinder::Instance()->SetFixConeParams(param0,param1,param2);
}

void WCSimVertexFinder::FitConeParams()
{
  WCSimVertexFinder::Instance()->SetFitConeParams();
}  

void WCSimVertexFinder::FixVertexBias(Double_t bias)
{
  WCSimVertexFinder::Instance()->SetVertexBias(bias);
}

void WCSimVertexFinder::PrintParameters()
{
  WCSimVertexFinder::Instance()->RunPrintParameters();
}

WCSimVertexFinder::WCSimVertexFinder()
{
  //Ioana
  myfile = new TFile("myfile.root","RECREATE");//"NEW");
  histTimeRes = new TH1D("histTimeRes","",1000,-20.0,80.0);
  histPDF = new TH1D("histPDF","",1000,-20.0,80.0);
  histRes = new TH1D("histRes","",1000,-20.0,80.0);
  histFillLkl = new TH1D("histFillLkl","",2000,-1000.0,1000.0);
  
  //MWMWMW
  histFillLmu = new TH1D("histFillLmu","",50,-397.5,602.5);
  
  histPointTimeRes = new TH1D("histPointTimeRes","",1000,-20.0,80.0);
  histPointPDF = new TH1D("histPointPDF","",1000,-20.0,80.0);
  histPointRes = new TH1D("histPointRes","",1000,-20.0,80.0);
  histPointFillLkl = new TH1D("histPointFillLkl","",2000,-1000.0,1000.0);
  indexp = 0;

  currentEv = 0;
  
  // default configuration
  fBaseFOM = 100.0;
  fPointFitOnly = 0;
  fUseTrueVertex = 0; //0; 
  fUseTruePosition = 0;
  fUseTrueDirection = 0;
  fSeedWithTrueVertex = 0; //0;
  fSeedWithSimpleVertex = 0;
  fSeedWithQuadruples = 1; //1;
  fUseChrom = 0; //use 1 only if you want to use the chromaticPDF for both point and extended vertex  
  fUseChromPDFextFit = 1; //use 1 if you want to use ChromPDF to fit Extended vertex 
  
  fNumSeeds = 200;

  fFitTimeParams = 0;     // don't fit by default
  fFixTimeParam0 = 0.20;  // scattering parameter

  fFitConeParams = 1;     // do fit by default  
  fFixConeParam0 = 0.25;  // track length parameter
  fFixConeParam1 = 0.50;  // track length parameter
  fFixConeParam2 = 0.75;  // particle ID:  0.0[electron]->1.0[muon]

  fTimeFitWeight = 0.50;  // nominal time weight
  fConeFitWeight = 0.50;  // nominal cone weight

  fFixVertexBias = 1;     // fix vertex bias
  fVertexBias = 25.0;     // size of vertex bias [cm]

  fIntegralsDone = 0;

  fVtxX = 0.0;
  fVtxY = 0.0;
  fVtxZ = 0.0;
  fDirX = 0.0;
  fDirY = 0.0;
  fDirZ = 0.0;
  fVtxFOM = 0.0;

  fSimplePosition = 0;
  fSimpleDirection = 0;
  fPointPosition = 0;
  fPointDirection = 0;
  fPointVertex = 0;
  fExtendedVertex = 0;

  fMinuitPointPosition = new TMinuit();
  fMinuitPointPosition->SetPrintLevel(-1);
  fMinuitPointPosition->SetMaxIterations(5000);

  fMinuitPointDirection = new TMinuit();
  fMinuitPointDirection->SetPrintLevel(-1);
  fMinuitPointDirection->SetMaxIterations(5000);

  fMinuitPointVertex = new TMinuit();
  fMinuitPointVertex->SetPrintLevel(-1);
  fMinuitPointVertex->SetMaxIterations(5000);

  fMinuitExtendedVertex = new TMinuit();
  fMinuitExtendedVertex->SetPrintLevel(1);
  fMinuitExtendedVertex->SetMaxIterations(5000); 

  fMinuitTimeFit = new TMinuit();
  fMinuitTimeFit->SetPrintLevel(-1);
  fMinuitTimeFit->SetMaxIterations(5000);   

  fMinuitConeFit = new TMinuit();
  fMinuitConeFit->SetPrintLevel(-1);
  fMinuitConeFit->SetMaxIterations(5000);   

  fPass = 0;
  fItr = 0; 

  fTimeFitItr = 0;
  fConeFitItr = 0;
  fPointPosItr = 0;
  fPointDirItr = 0;
  fPointVtxItr = 0;
  fExtendedVtxItr = 0;  

  // --- debug ---
  fTimeParam0 = 0.0;
  fConeParam0 = 0.0;
  fConeParam1 = 0.0; 
  fConeParam2 = 0.0;
  
  //WCSimHistos::Instance()->MakeChrom3DHisto();

  fLMuonFilter=0;  //erika 070313
  
}

WCSimVertexFinder::~WCSimVertexFinder()
{
  // delete fitter
  // =============
  delete fMinuitPointPosition;
  delete fMinuitPointDirection;
  delete fMinuitPointVertex;
  delete fMinuitExtendedVertex;

  delete fMinuitTimeFit;
  delete fMinuitConeFit;

  // clear vertices
  // ==============
  for(UInt_t i=0; i<vVertexList.size(); i++ ){
    delete (WCSimRecoVertex*)(vVertexList.at(i));
  }

  vVertexList.clear();
  
}

void WCSimVertexFinder::RunPrintParameters()
{
  std::cout << " *** WCSimVertexFinder::PrintParameters() *** " << std::endl;

  std::cout << "  Vertex Finding Parameters: " << std::endl
            << "   PointFitOnly = " << fPointFitOnly << std::endl
            << "   UseTrueVertex = " << fUseTrueVertex << std::endl
            << "   UseTruePosition = " << fUseTruePosition << std::endl
            << "   UseTrueDirection = " << fUseTrueDirection << std::endl
            << "   SeedWithTrueVertex = " << fSeedWithTrueVertex << std::endl
            << "   SeedWithSimpleVertex = " << fSeedWithSimpleVertex << std::endl
	    << "   SeedWithQuadruples = " << fSeedWithQuadruples << std::endl
            << "   NumSeeds = " << fNumSeeds << std::endl
            << "  Vertex Fitting Parameters: " << std::endl
            << "   BaseFOM = " << fBaseFOM << std::endl
            << "   FitTimeParams = " << fFitTimeParams << " (" << fFixTimeParam0 << ") " << std::endl
            << "   FitConeParams = " << fFitConeParams << " (" << fFixConeParam0 << "," << fFixConeParam1 << "," << fFixConeParam2 << ") " << std::endl
            << "   Weights = (" << fTimeFitWeight << "," << fConeFitWeight << ") " << std::endl
            << "   FixVertexBias = " << fFixVertexBias << " (" << fVertexBias << ") " << std::endl;

  return;
}

void WCSimVertexFinder::Reset()
{
  return this->Clear();
}

void WCSimVertexFinder::Clear()
{
  // clear vertices
  // ==============
  for(UInt_t i=0; i<vVertexList.size(); i++ ){
    delete (WCSimRecoVertex*)(vVertexList.at(i));
  }

  vVertexList.clear();

  // clear vertices
  // ==============
  fSimplePosition = 0;
  fSimpleDirection = 0;
  fPointPosition = 0;
  fPointDirection = 0; 
  fPointVertex = 0;
  fExtendedVertex = 0;

  return;
}


WCSimRecoVertex* WCSimVertexFinder::Run(WCSimRecoEvent* myEvent)
{
  this->Clear();
  /*
  string::std outFile = "chromPDF.root";
  WCSimHistos *wchistos = WCSimHistos::Instance();
  for (int i=0; i!=10; i++) {
  for (int j=0; j!=6; j++) {
  	std::cout << "(i,j) = (" << i << "," << j << ")" << std::endl; 
  	wchistos->MakeChrom3DHisto(i,j,outFile);
  }
  }
  delete wchistos;
  */
  if( fLMuonFilter ){              //erika 070313
    return (WCSimRecoVertex*)(this->RunLMuonFit(myEvent));
  }
  else if( fPointFitOnly ){
    return (WCSimRecoVertex*)(this->RunPointFit(myEvent));
  }
  else{
    return (WCSimRecoVertex*)(this->RunExtendedFit(myEvent));
  }
}

WCSimRecoVertex* WCSimVertexFinder::RunPointFit(WCSimRecoEvent* myEvent)
{

  currentEv = myEvent;
  
  // return true vertex
  // ==================
  if( fUseTrueVertex ){
    return this->RunPointFitFromTruth(myEvent);
  }

  // load event
  // ==========
  WCSimVertexGeometry::Instance()->LoadEvent(myEvent);
  fUseChrom = 0;
  std::cout << " *** WCSimVertexFinder::RunPointFit(...) *** " << std::endl;

  // point positiobn fit
  // ===================
  WCSimRecoVertex* simplePos = (WCSimRecoVertex*)(this->FindSimplePosition());
 //return simplePos; 
 
  //indexp = 0;
 
  WCSimRecoVertex* pointPos  = (WCSimRecoVertex*)(this->FitPointPosition(simplePos));
  //return pointPos;


  // point direction fit
  // ===================
  WCSimRecoVertex* simpleDir = (WCSimRecoVertex*)(this->FindSimpleDirection(pointPos)); 
  WCSimRecoVertex* pointDir  = (WCSimRecoVertex*)(this->FitPointDirection(simpleDir)); 

  // point vertex fit
  // ================
  WCSimRecoVertex* pointVtx  = (WCSimRecoVertex*)(this->FitPointVertex(pointDir)); 

  // return vertex
  // =============
  return pointVtx;
 
}

WCSimRecoVertex* WCSimVertexFinder::RunExtendedFit(WCSimRecoEvent* myEvent)
{    
  // return true vertex
  // ==================
  if( fUseTrueVertex ){  
    return this->RunExtendedFitFromTruth(myEvent);
  }

  // point fit
  // =========
  
  WCSimRecoVertex* pointVtx = (WCSimRecoVertex*)(this->RunPointFit(myEvent));

  std::cout << " *** WCSimVertexFinder::RunExtendedFit(...) *** " << std::endl;

  // extended fit to vertex and direction
  // ====================================
  WCSimRecoVertex* extendedVtx = (WCSimRecoVertex*)(this->FitExtendedVertex(pointVtx));

  // correct bias in vertex and direction
  // ====================================
  WCSimRecoVertex* extendedVtxCorrected = (WCSimRecoVertex*)(this->CorrectExtendedVertex(extendedVtx));

  // return vertex
  // =============
  return extendedVtxCorrected;
}

WCSimRecoVertex* WCSimVertexFinder::RunLMuonFit(WCSimRecoEvent* myEvent)
{ 
std::cout << " *** WCSimVertexFinder::RunLMuonFit(...) *** " << std::endl;

  //point fit 
  WCSimRecoVertex* myVertex = (WCSimRecoVertex*)(this->RunPointFit(myEvent));
  
  std::cout <<"*** Point fit done. Ready to filter LMuon ***"<<std::endl;
 

  //LMuon filter

std::cout << "So far I had "<< myEvent->GetNFilterDigits() << " Filter Digits "<<std::endl;


 std::cout <<"*** LMuon max set to "<<fmaxLMuon<<std::endl;

//------------------
    int myNdigits = myEvent->GetNDigits();
    //int NFilterdigits = myEvent->GetNFilterDigits();
    int ifilter = 0;
 Bool_t filtered = 1;
    Double_t TResid, LPhot, LMuon, Oangle;


    //   WCSimTrueEvent* trueEvent = (WCSimTrueEvent*)(WCSimInterface::TrueEvent());
  
//     Double_t trueX = trueEvent->GetVtxX();
//     Double_t trueY = trueEvent->GetVtxY();
//     Double_t trueZ = trueEvent->GetVtxZ(); 
//     Double_t dirX = trueEvent->GetDirX();
//     Double_t dirY = trueEvent->GetDirY();
//     Double_t dirZ = trueEvent->GetDirZ();
//    Double_t trueT = 0.0;
   
    double trueT= myVertex->GetTime();
    double trueX= myVertex->GetX();
    double trueY= myVertex->GetY();
    double trueZ= myVertex->GetZ();
    double dirX= myVertex->GetDirX();
    double dirY= myVertex->GetDirY();
    double dirZ= myVertex->GetDirZ();
    
    //for(int i=0; i<30; i++){
   for(int i=0; i<myNdigits; i++){
      WCSimRecoDigit* adigit = myEvent->GetDigit(i);
      // if (i==28 || i==29) adigit->ResetFilter();
      if( adigit->IsFiltered() || !filtered ){ //if the hit passed the filter
	double hitX = adigit->GetX();
	double hitY = adigit->GetY();
	double hitZ = adigit->GetZ();
	double hitT = adigit->GetTime();
	//double qpes = adigit->GetQPEs();
	//double res = WCSimParameters::TimeResolution(qpes); 
	WCSimVertexGeometry::Instance()->LoadEvent(myEvent);
	WCSimVertexGeometry::Instance()->CalcTResid(trueX, trueY, trueZ, trueT, dirX, dirY, dirZ, hitX, hitY, hitZ, hitT, TResid, LPhot,LMuon, Oangle);
	
	if (LMuon>fmaxLMuon) adigit->ResetFilter();
	else {ifilter++;}
	
      } //loop of the filter
    } //loop over hits

   std::cout << "Now I have "<< myEvent->GetNFilterDigits()<< " Filter Digits "<<std::endl;

   std::cout<< "Reloading Vertex Geometry" << std::endl;
   WCSimVertexGeometry::Instance()->SetSameEventOverride(1);
   WCSimVertexGeometry::Instance()->LoadEvent(myEvent);

   std::cout <<"*** Ready to do second fit ***"<<std::endl;
  
 //Run Second Fit
   if( fPointFitOnly ){
    return (WCSimRecoVertex*)(this->RunPointFit(myEvent));
  }
 
 else{
 std::cout << " *** WCSimVertexFinder::RunExtendedFit(...) *** " << std::endl;
  WCSimRecoVertex* extendedVtx = (WCSimRecoVertex*)(this->FitExtendedVertex(myVertex));
  WCSimRecoVertex* extendedVtxCorrected = (WCSimRecoVertex*)(this->CorrectExtendedVertex(extendedVtx));
  return extendedVtxCorrected;

  }

}



WCSimRecoVertex* WCSimVertexFinder::RunPointFitFromTruth(WCSimRecoEvent* myEvent)
{
  std::cout << " *** WCSimVertexFinder::RunPointFit(...) *** " << std::endl;
  std::cout << "  --- reconstruct vertex from truth --- " << std::endl;
  
  WCSimTrueEvent* myTrueEvent = (WCSimTrueEvent*)(WCSimInterface::TrueEvent());

  if( myTrueEvent->GetNTracks()>0 ){
    Double_t vtxX = myTrueEvent->GetVtxX();
    Double_t vtxY = myTrueEvent->GetVtxY();
    Double_t vtxZ = myTrueEvent->GetVtxZ();
    Double_t dirX = myTrueEvent->GetDirX();
    Double_t dirY = myTrueEvent->GetDirY();
    Double_t dirZ = myTrueEvent->GetDirZ();

    return (WCSimRecoVertex*)(this->RunPointFit(myEvent, 
                                                 vtxX,vtxY,vtxZ, 
                                                  dirX,dirY,dirZ));
  }
  else{
    return (WCSimRecoVertex*)(this->BuildDummyVertex());
  }
}

WCSimRecoVertex* WCSimVertexFinder::RunExtendedFitFromTruth(WCSimRecoEvent* myEvent)
{
  std::cout << " *** WCSimVertexFinder::RunExtendedFit(...) *** " << std::endl;
  std::cout << "  --- reconstruct vertex from truth --- " << std::endl;
  
  WCSimTrueEvent* myTrueEvent = (WCSimTrueEvent*)(WCSimInterface::TrueEvent());

  if( myTrueEvent->GetNTracks()>0 ){
    Double_t vtxX = myTrueEvent->GetVtxX();
    Double_t vtxY = myTrueEvent->GetVtxY();
    Double_t vtxZ = myTrueEvent->GetVtxZ();
    Double_t dirX = myTrueEvent->GetDirX();
    Double_t dirY = myTrueEvent->GetDirY();
    Double_t dirZ = myTrueEvent->GetDirZ();

    return (WCSimRecoVertex*)(this->RunExtendedFit(myEvent, 
                                                    vtxX,vtxY,vtxZ, 
                                                     dirX,dirY,dirZ));
  }
  else{
    return (WCSimRecoVertex*)(this->BuildDummyVertex());
  }
}

WCSimRecoVertex* WCSimVertexFinder::Run(WCSimRecoEvent* myEvent, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ)
{
  this->Clear();

  if( fPointFitOnly ){
    return (WCSimRecoVertex*)(this->RunPointFit(myEvent, 
                                                 vtxX,vtxY,vtxZ, 
                                                  dirX,dirY,dirZ));
  }
  else{
    return (WCSimRecoVertex*)(this->RunExtendedFit(myEvent, 
                                                    vtxX,vtxY,vtxZ, 
                                                     dirX,dirY,dirZ));
  }
}

WCSimRecoVertex* WCSimVertexFinder::RunPointFit(WCSimRecoEvent* myEvent, Double_t vtxX, Double_t vtxY, Double_t vtxZ)
{   
  // load event
  // ==========
  WCSimVertexGeometry::Instance()->LoadEvent(myEvent);
 
  // fix point vertex
  // ================
  //WCSimRecoVertex* simpleVtx = (WCSimRecoVertex*)(this->FixSimplePosition(vtxX,vtxY,vtxZ)); // unused at present
  WCSimRecoVertex* pointPos = (WCSimRecoVertex*)(this->FixPointPosition(vtxX,vtxY,vtxZ));

  // return vertex
  // =============
  return pointPos;
}

WCSimRecoVertex* WCSimVertexFinder::RunPointFit(WCSimRecoEvent* myEvent, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ)
{   
  // fix point vertex
  // ================
  //WCSimRecoVertex* pointPos = (WCSimRecoVertex*)(this->RunPointFit(myEvent,vtxX,vtxY,vtxZ)); // unused at present

  // fix point direction
  // ===================
  //WCSimRecoVertex* simpleDir = (WCSimRecoVertex*)(this->FixSimpleDirection(vtxX,vtxY,vtxZ, dirX,dirY,dirZ)); // unused at present
  //WCSimRecoVertex* pointDir = (WCSimRecoVertex*)(this->FixPointDirection(vtxX,vtxY,vtxZ,dirX,dirY,dirZ)); // unused at present

  // fix point vertex
  // ================
  WCSimRecoVertex* pointVtx = (WCSimRecoVertex*)(this->FixPointVertex(vtxX,vtxY,vtxZ,
						                       dirX,dirY,dirZ));

  // return vertex
  // =============
  return pointVtx;
}

WCSimRecoVertex* WCSimVertexFinder::RunExtendedFit(WCSimRecoEvent* myEvent, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ)
{     
  // fix point direction
  // ===================
  //WCSimRecoVertex* pointVtx = (WCSimRecoVertex*)(this->RunPointFit(myEvent,vtxX,vtxY,vtxZ,dirX,dirY,dirZ)); // unused at present

  // fix extended vertex
  // ===================
  //WCSimVertexGeometry::Instance()->LoadEvent(myEvent);
  WCSimRecoVertex* extendedVtx = (WCSimRecoVertex*)(this->FixExtendedVertex(vtxX,vtxY,vtxZ,
						                             dirX,dirY,dirZ));

  // return vertex
  // =============
  return extendedVtx;
}

WCSimRecoVertex* WCSimVertexFinder::BuildTrueVertex()
{
  WCSimTrueEvent* myTrueEvent = (WCSimTrueEvent*)(WCSimInterface::TrueEvent());

  Double_t vtxX = myTrueEvent->GetVtxX();
  Double_t vtxY = myTrueEvent->GetVtxY();
  Double_t vtxZ = myTrueEvent->GetVtxZ();  

  return (WCSimRecoVertex*)(this->FixSimplePosition(vtxX,vtxY,vtxZ));
}

WCSimRecoVertex* WCSimVertexFinder::BuildDummyVertex()
{
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);

  fSimplePosition  = newVertex;
  fSimpleDirection = newVertex;
  fPointPosition   = newVertex;
  fPointDirection  = newVertex;
  fPointVertex     = newVertex;
  fExtendedVertex  = newVertex;

  std::cout << "  --- no true vertex, building dummy vertex --- " << std::endl;

  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FindSimplePosition()
{
  if( fSeedWithTrueVertex ){
    std::cout << "  --- seed vertex with truth --- " << std::endl;
    return (WCSimRecoVertex*)(this->BuildTrueVertex());
  }

  if( fSeedWithSimpleVertex ){
    fSimplePosition = (WCSimRecoVertex*)(WCSimVertexGeometry::Instance()->CalcSimpleVertex()); 
  }
  else if( fSeedWithQuadruples ){
    fSimplePosition = (WCSimRecoVertex*)(this->FindSeedPosition());
  }
  else{
    fSimplePosition = (WCSimRecoVertex*)(WCSimVertexGeometry::Instance()->CalcSimpleVertex());  
  }

  std::cout << "  simple vertex: " << std::endl
            << "    (vx,vy,vz)=(" << fSimplePosition->GetX() << "," << fSimplePosition->GetY() << "," << fSimplePosition->GetZ() << ") " << std::endl
            << "      vtime=" << fSimplePosition->GetTime() << " itr=" << fSimplePosition->GetIterations() << " fom=" << fSimplePosition->GetFOM() << std::endl;

  if( fSimplePosition->GetPass()==0 ) std::cout << "   <warning> simple vertex calculation failed! " << std::endl;

  return fSimplePosition;
}

WCSimRecoVertex* WCSimVertexFinder::FindSimpleDirection(WCSimRecoVertex* myVertex)
{
  fSimpleDirection = (WCSimRecoVertex*)(this->FindSeedDirection(myVertex));

  std::cout << "  simple direction: " << std::endl
            << "    (vx,vy,vz)=(" << fSimpleDirection->GetX() << "," << fSimpleDirection->GetY() << "," << fSimpleDirection->GetZ() << ") " << std::endl
            << "    (px,py,pz)=(" << fSimpleDirection->GetDirX() << "," << fSimpleDirection->GetDirY() << "," << fSimpleDirection->GetDirZ() << ") " << std::endl
            << "      vtime=" << fSimpleDirection->GetTime() << " itr=" << fSimpleDirection->GetIterations() << " fom=" << fSimpleDirection->GetFOM() << std::endl;

  if( fSimpleDirection->GetPass()==0 ) std::cout << "   <warning> simple direction calculation failed! " << std::endl;

  return fSimpleDirection;
}

WCSimRecoVertex* WCSimVertexFinder::FindSeedPosition()
{
  Double_t vtxX = 0.0;
  Double_t vtxY = 0.0;
  Double_t vtxZ = 0.0;
  Double_t vtxTime = 950.0;
  Double_t vtxFOM = 0.0;

  Int_t bestSeed = -1;
  Double_t bestFOM = -1.0;
  WCSimVertexGeometry::Instance()->CalcVertexSeeds(fNumSeeds);
  //UInt_t nlast = WCSimVertexGeometry::Instance()->GetNSeeds();
   UInt_t nlast = fNumSeeds;

  for( UInt_t n=0; n<nlast; n++ ){
    vtxX = WCSimVertexGeometry::Instance()->GetSeedVtxX(n);
    vtxY = WCSimVertexGeometry::Instance()->GetSeedVtxY(n);
    vtxZ = WCSimVertexGeometry::Instance()->GetSeedVtxZ(n);

    this->PointPositionChi2(vtxX,vtxY,vtxZ,
                            vtxTime,vtxFOM);

    if( vtxFOM>bestFOM ){
      bestSeed = n; 
      bestFOM = vtxFOM;
    }
  }
  
  if( bestSeed>=0 ){
    vtxX = WCSimVertexGeometry::Instance()->GetSeedVtxX(bestSeed);
    vtxY = WCSimVertexGeometry::Instance()->GetSeedVtxY(bestSeed);
    vtxZ = WCSimVertexGeometry::Instance()->GetSeedVtxZ(bestSeed);
  }
  
  std::cout << "[Find Seed Position] (vtxX,vtxY,vtxZ,vtxTime) = (" << vtxX <<","<<vtxY<<","<<vtxZ<<")" << std::endl;

  WCSimRecoVertex* newVertex = (WCSimRecoVertex*)(this->FixSimplePosition(vtxX,vtxY,vtxZ));
  newVertex->SetFOM(fBaseFOM,nlast,1); 

  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FindSeedDirection(WCSimRecoVertex* myVertex)
{
  WCSimRecoVertex* seedVertex = (WCSimRecoVertex*)(WCSimVertexGeometry::Instance()->CalcSimpleDirection(myVertex));  

  Double_t vtxX = seedVertex->GetX();
  Double_t vtxY = seedVertex->GetY();
  Double_t vtxZ = seedVertex->GetZ();

  Double_t dirX = seedVertex->GetDirX();
  Double_t dirY = seedVertex->GetDirY();
  Double_t dirZ = seedVertex->GetDirZ();

  WCSimRecoVertex* newVertex = (WCSimRecoVertex*)(this->FixSimpleDirection(vtxX,vtxY,vtxZ,
                                                                           dirX,dirY,dirZ));
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FitPointPosition(WCSimRecoVertex* myVertex)
{  
  return (WCSimRecoVertex*)(this->FitPointPositionWithMinuit(myVertex));
}

WCSimRecoVertex* WCSimVertexFinder::FitPointDirection(WCSimRecoVertex* myVertex)
{  
  return (WCSimRecoVertex*)(this->FitPointDirectionWithMinuit(myVertex));
}

WCSimRecoVertex* WCSimVertexFinder::FitPointVertex(WCSimRecoVertex* myVertex)
{      
  return (WCSimRecoVertex*)(this->FitPointVertexWithMinuit(myVertex));
}

WCSimRecoVertex* WCSimVertexFinder::FitExtendedVertex(WCSimRecoVertex* myVertex)
{
  return (WCSimRecoVertex*)(this->FitExtendedVertexWithMinuit(myVertex));
}

WCSimRecoVertex* WCSimVertexFinder::FixSimplePosition(Double_t vtxX, Double_t vtxY, Double_t vtxZ)
{  
  // initialization
  // ==============
  Double_t vtxTime = 950.0;
  Double_t vtxFOM = fBaseFOM;

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fSimplePosition = newVertex;

  // set vertex
  // ==========
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetFOM(vtxFOM,1,1); 
 
  // print vertex
  // ============
  std::cout << "  set simple position: " << std::endl
            << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "      vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;

  // return vertex
  // =============
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FixPointPosition(Double_t vtxX, Double_t vtxY, Double_t vtxZ)
{  
  // initialization
  // ==============
  Double_t vtxTime = 950.0;
  Double_t vtxFOM = 0.0;

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fPointPosition = newVertex;

  // calculate vertex
  // ================
  this->PointPositionChi2(vtxX,vtxY,vtxZ,
                          vtxTime,vtxFOM);

  // set vertex
  // ==========
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetFOM(vtxFOM,1,1);

  // set status
  // ==========
  newVertex->SetStatus(WCSimRecoVertex::kOK);

  // print vertex
  // ============
  std::cout << "  set point position: " << std::endl
            <<"     (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "      vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;

  // return vertex
  // =============
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FixSimpleDirection(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ)
{
  // initialization
  // ==============
  Double_t vtxTime = 950.0;
  Double_t dirFOM = fBaseFOM;

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fSimpleDirection = newVertex; 

  // set vertex
  // ==========
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetDirection(dirX,dirY,dirZ);  
  newVertex->SetFOM(dirFOM,1,1);

  // set status
  // ==========
  newVertex->SetStatus(WCSimRecoVertex::kOK);

  // print vertex
  // ============
  std::cout << "  set simple direction: " << std::endl
	    << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "    (px,py,pz)=(" << newVertex->GetDirX() << "," << newVertex->GetDirY() << "," << newVertex->GetDirZ() << ") " << std::endl
            << "      vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;

  // return vertex
  // =============
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FixPointDirection(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ)
{
  // initialization
  // ==============
  Double_t vtxTime = 950.0;
  Double_t vtxAngle = WCSimParameters::CherenkovAngle();
  Double_t vtxFOM = 0.0;
  Double_t dirFOM = 0.0;

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fPointDirection = newVertex;

  // figure of merit
  // ===============
  this->PointPositionChi2(vtxX,vtxY,vtxZ,
                          vtxTime,vtxFOM);

  this->PointDirectionChi2(vtxX,vtxY,vtxZ,
                           dirX,dirY,dirZ,
                           vtxAngle,dirFOM);

  // set vertex and direction
  // ========================
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetDirection(dirX,dirY,dirZ);
  newVertex->SetConeAngle(vtxAngle);
  newVertex->SetFOM(dirFOM,1,1);

  // set status
  // ==========
  newVertex->SetStatus(WCSimRecoVertex::kOK);

  // print vertex
  // ============
  std::cout << "  set point direction: " << std::endl
            << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "    (px,py,pz)=(" << newVertex->GetDirX() << "," << newVertex->GetDirY() << "," << newVertex->GetDirZ() << ") " << std::endl
            << "      angle=" << newVertex->GetConeAngle() << " vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;

  // return vertex
  // =============
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FixPointVertex(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ)
{
  // initialization
  // ==============
  Double_t vtxTime = 950.0;
  Double_t vtxAngle = WCSimParameters::CherenkovAngle();
  Double_t vtxFOM = 0.0;

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fPointVertex = newVertex;

  // figure of merit
  // ===============
  this->PointVertexChi2(vtxX,vtxY,vtxZ,
                        dirX,dirY,dirZ,
                        vtxAngle,vtxTime,vtxFOM);

  // set vertex and direction
  // ========================
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetDirection(dirX,dirY,dirZ);
  newVertex->SetConeAngle(vtxAngle);
  newVertex->SetFOM(vtxFOM,1,1);

  // set status
  // ==========
  newVertex->SetStatus(WCSimRecoVertex::kOK);

  // print vertex
  // ============
  std::cout << "  set point vertex: " << std::endl
            << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "    (px,py,pz)=(" << newVertex->GetDirX() << "," << newVertex->GetDirY() << "," << newVertex->GetDirZ() << ") " << std::endl
            << "      angle=" << newVertex->GetConeAngle() << " vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;
  
  // return vertex
  // =============
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FixExtendedVertex(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ)
{
  // initialization
  // ==============
  Double_t vtxTime = 950.0;
  Double_t vtxAngle = WCSimParameters::CherenkovAngle();
  Double_t vtxFOM = 0.0;

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fExtendedVertex = newVertex;

  // figure of merit
  // ===============
  this->ExtendedVertexChi2(vtxX,vtxY,vtxZ,
                           dirX,dirY,dirZ,
                           vtxAngle,vtxTime,vtxFOM); 


  // set vertex and direction
  // ========================
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetDirection(dirX,dirY,dirZ);
  newVertex->SetConeAngle(vtxAngle);
  newVertex->SetFOM(vtxFOM,1,1);

  // set status
  // ==========
  newVertex->SetStatus(WCSimRecoVertex::kOK);

  // print vertex
  // ============
  std::cout << "  set extended vertex: " << std::endl
            << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "    (px,py,pz)=(" << newVertex->GetDirX() << "," << newVertex->GetDirY() << "," << newVertex->GetDirZ() << ") " << std::endl
            << "      angle=" << newVertex->GetConeAngle() << " vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;
  
  // return vertex
  // =============
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::CorrectExtendedVertex(WCSimRecoVertex* myVertex)
{
  // get vertex and direction
  // ========================
  Double_t vtxX = myVertex->GetX();
  Double_t vtxY = myVertex->GetY();
  Double_t vtxZ = myVertex->GetZ();
  Double_t vtxTime = myVertex->GetTime();

  Double_t dirX = myVertex->GetDirX();
  Double_t dirY = myVertex->GetDirY();
  Double_t dirZ = myVertex->GetDirZ();

  // get other vertex parameters
  // ===========================
  Double_t angle = myVertex->GetConeAngle();
  Double_t length = myVertex->GetTrackLength();

  Double_t fom = myVertex->GetFOM();
  Int_t nsteps = myVertex->GetIterations();
  Bool_t pass = myVertex->GetPass();
  Int_t status = myVertex->GetStatus();

  // fix vertex bias
  // ===============
  if( fFixVertexBias ){
    vtxX -= fVertexBias*dirX;
    vtxY -= fVertexBias*dirY;
    vtxZ -= fVertexBias*dirZ;
    vtxTime -= fVertexBias/WCSimParameters::SpeedOfLight();
  }

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex(vtxX,vtxY,vtxZ,vtxTime,
                                                   dirX,dirY,dirZ,
                                                   angle,length,
                                                   fom,nsteps,pass,status);
  vVertexList.push_back(newVertex);
  fExtendedVertex = newVertex;

  // print vertex
  // ============
  if( fFixVertexBias ){
    std::cout << "  corrected extended vertex: " << std::endl
              << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
              << "    (px,py,pz)=(" << newVertex->GetDirX() << "," << newVertex->GetDirY() << "," << newVertex->GetDirZ() << ") " << std::endl
              << "      angle=" << newVertex->GetConeAngle() << " vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;
  }

  // return vertex
  // =============
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FitPointPositionWithMinuit(WCSimRecoVertex* myVertex)
{  
  // initialization
  // ==============
  Double_t vtxX = 0.0;
  Double_t vtxY = 0.0;
  Double_t vtxZ = 0.0;
  Double_t vtxTime = 950.0;

  Double_t dirX = 0.0;
  Double_t dirY = 0.0;
  Double_t dirZ = 0.0;

  Double_t vtxFOM = 0.0;

  // seed vertex
  // ===========
  Bool_t foundSeed = myVertex->FoundVertex();
  Double_t seedX = myVertex->GetX();
  Double_t seedY = myVertex->GetY();
  Double_t seedZ = myVertex->GetZ();

  // current status
  // ==============
  Int_t status = myVertex->GetStatus();

  // reset counter
  // =============
  point_position_reset_itr();

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fPointPosition = newVertex;

  // abort if necessary
  // ==================
  if( foundSeed==0 ){
    std::cout << "   <warning> point position fit failed to find input vertex " << std::endl;    
    status |= WCSimRecoVertex::kFailPointPosition;
    newVertex->SetStatus(status);
    return newVertex;
  }

  // run Minuit
  // ==========  
  // three-parameter fit to vertex coordinates

  Int_t err = 0;
  Int_t flag = 0;

  Double_t fitXpos = 0.0;
  Double_t fitYpos = 0.0;
  Double_t fitZpos = 0.0;

  Double_t fitXposErr = 0.0;
  Double_t fitYposErr = 0.0;
  Double_t fitZposErr = 0.0;

  Double_t* arglist = new Double_t[10];
  arglist[0]=1;  // 1: standard minimization
                 // 2: try to improve minimum

  // re-initialize everything...
  fMinuitPointPosition->mncler();
  fMinuitPointPosition->SetFCN(point_position_chi2);
  fMinuitPointPosition->mnexcm("SET STR",arglist,1,err);
  fMinuitPointPosition->mnparm(0,"x",seedX,250.0,-5000.0,+5000.0,err);
  fMinuitPointPosition->mnparm(1,"y",seedY,250.0,-5000.0,+5000.0,err);
  fMinuitPointPosition->mnparm(2,"z",seedZ,250.0,-5000.0,+5000.0,err);

  flag = fMinuitPointPosition->Migrad();
  fMinuitPointPosition->GetParameter(0,fitXpos,fitXposErr);
  fMinuitPointPosition->GetParameter(1,fitYpos,fitYposErr);
  fMinuitPointPosition->GetParameter(2,fitZpos,fitZposErr);

  delete [] arglist;

  // sort results
  // ============
  vtxX = fitXpos; 
  vtxY = fitYpos;
  vtxZ = fitZpos;
  vtxTime = 950.0;

  vtxFOM = 0.0;
  
  fPass = 0;               // flag = 0: normal termination
  if( flag==0 ) fPass = 1; // anything else: abnormal termination 

  fItr = point_position_iterations();

  // calculate vertex
  // ================
  this->PointPositionChi2(vtxX,vtxY,vtxZ,
                          vtxTime,vtxFOM);

  // set vertex and direction
  // ========================
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetDirection(dirX,dirY,dirZ);
  newVertex->SetFOM(vtxFOM,fItr,fPass);

  // set status
  // ==========
  if( !fPass ) status |= WCSimRecoVertex::kFailPointPosition;
  newVertex->SetStatus(status);

  // print vertex
  // ============
  std::cout << "  fitted point position: " << std::endl
            << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "      vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;

  if( !fPass ) std::cout << "   <warning> point position fit failed to converge! Error code: " << flag << std::endl;

  // return vertex
  // =============  
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FitPointDirectionWithMinuit(WCSimRecoVertex* myVertex)
{
  // initialization
  // ==============
  Bool_t foundSeed = ( myVertex->FoundVertex() 
                    && myVertex->FoundDirection() );
  
  Double_t vtxX = myVertex->GetX();
  Double_t vtxY = myVertex->GetY();
  Double_t vtxZ = myVertex->GetZ();
  Double_t vtxTime = myVertex->GetTime();

  Double_t dirX = 0.0;
  Double_t dirY = 0.0;
  Double_t dirZ = 0.0;  

  Double_t vtxAngle = WCSimParameters::CherenkovAngle();

  Double_t vtxFOM = 0.0;

  // seed direction
  // ==============
  Double_t seedDirX = myVertex->GetDirX();
  Double_t seedDirY = myVertex->GetDirY();
  Double_t seedDirZ = myVertex->GetDirZ();
  
  Double_t seedTheta = acos(seedDirZ);
  Double_t seedPhi = 0.0;

  if( seedDirX!=0.0 ){
    seedPhi = atan(seedDirY/seedDirX);
  }
  if( seedDirX<=0.0 ){
    if( seedDirY>0.0 ) seedPhi += TMath::Pi();
    if( seedDirY<0.0 ) seedPhi -= TMath::Pi();
  }  

  // current status
  // ==============
  Int_t status = myVertex->GetStatus();

  // set global vertex
  // =================
  fVtxX = vtxX;
  fVtxY = vtxY;
  fVtxZ = vtxZ;

  // reset counter
  // =============
  point_direction_reset_itr();

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fPointDirection = newVertex;

  // abort if necessary
  // ==================
  if( foundSeed==0 ){
    std::cout << "   <warning> point direction fit failed to find input vertex " << std::endl;
    status |= WCSimRecoVertex::kFailPointDirection;
    newVertex->SetStatus(status);
    return newVertex;
  }

  // run Minuit
  // ==========  
  // two-parameter fit to direction coordinates
  
  Int_t err = 0;
  Int_t flag = 0;

  Double_t dirTheta;
  Double_t dirPhi;

  Double_t dirThetaErr;
  Double_t dirPhiErr;

  Double_t* arglist = new Double_t[10];
  arglist[0]=1;  // 1: standard minimization
                 // 2: try to improve minimum

  // re-initialize everything...
  fMinuitPointDirection->mncler();
  fMinuitPointDirection->SetFCN(point_direction_chi2);
  fMinuitPointDirection->mnexcm("SET STR",arglist,1,err);
  fMinuitPointDirection->mnparm(0,"theta",seedTheta,0.125*TMath::Pi(),0.0,TMath::Pi(),err);
  fMinuitPointDirection->mnparm(1,"phi",seedPhi,0.25*TMath::Pi(),-1.0*TMath::Pi(),+3.0*TMath::Pi(),err);

  flag = fMinuitPointDirection->Migrad();
  fMinuitPointDirection->GetParameter(0,dirTheta,dirThetaErr);
  fMinuitPointDirection->GetParameter(1,dirPhi,dirPhiErr);

  delete [] arglist;

  // sort results
  // ============
  dirX = sin(dirTheta)*cos(dirPhi);
  dirY = sin(dirTheta)*sin(dirPhi);
  dirZ = cos(dirTheta);

  vtxFOM = 0.0;
  
  fPass = 0;               // flag = 0: normal termination
  if( flag==0 ) fPass = 1; // anything else: abnormal termination 
                           
  fItr = point_direction_iterations();

  // calculate vertex
  // ================
  this->PointDirectionChi2(vtxX,vtxY,vtxZ,
                           dirX,dirY,dirZ,
                           vtxAngle,vtxFOM);

  // set vertex and direction
  // ========================
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetDirection(dirX,dirY,dirZ);
  newVertex->SetConeAngle(vtxAngle);
  newVertex->SetFOM(vtxFOM,fItr,fPass);

  // set status
  // ==========
  if( !fPass ) status |= WCSimRecoVertex::kFailPointDirection;
  newVertex->SetStatus(status);

  // print vertex
  // ============
  std::cout << "  fitted point direction: " << std::endl
            << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "    (px,py,pz)=(" << newVertex->GetDirX() << "," << newVertex->GetDirY() << "," << newVertex->GetDirZ() << ") " << std::endl
            << "      angle=" << newVertex->GetConeAngle() << " vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;

  if( !fPass ) std::cout << "   <warning> point direction fit failed to converge! Error code: " << flag << std::endl;

  // return vertex
  // ============= 
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FitPointVertexWithMinuit(WCSimRecoVertex* myVertex)
{
  // initialization
  // ==============
  Double_t vtxX = 0.0;
  Double_t vtxY = 0.0;
  Double_t vtxZ = 0.0;
  Double_t vtxTime = 950.0;

  Double_t dirX = 0.0;
  Double_t dirY = 0.0;
  Double_t dirZ = 0.0;
    
  Double_t vtxAngle = WCSimParameters::CherenkovAngle();

  Double_t vtxFOM = 0.0;

  // seed vertex
  // ===========  
  Bool_t foundSeed = ( myVertex->FoundVertex() 
                    && myVertex->FoundDirection() );

  Double_t seedX = myVertex->GetX();
  Double_t seedY = myVertex->GetY();
  Double_t seedZ = myVertex->GetZ();

  Double_t seedDirX = myVertex->GetDirX();
  Double_t seedDirY = myVertex->GetDirY();
  Double_t seedDirZ = myVertex->GetDirZ();

  Double_t seedTheta = acos(seedDirZ);
  Double_t seedPhi = 0.0;

  if( seedDirX!=0.0 ){
    seedPhi = atan(seedDirY/seedDirX);
  }
  if( seedDirX<=0.0 ){
    if( seedDirY>0.0 ) seedPhi += TMath::Pi();
    if( seedDirY<0.0 ) seedPhi -= TMath::Pi();
  }  

  // current status
  // ==============
  Int_t status = myVertex->GetStatus();

  // reset counter
  // =============
  point_vertex_reset_itr();

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fPointVertex = newVertex;

  // abort if necessary
  // ==================
  if( foundSeed==0 ){
    std::cout << "   <warning> point vertex fit failed to find input vertex " << std::endl;   
    status |= WCSimRecoVertex::kFailPointVertex;
    newVertex->SetStatus(status);
    return newVertex;
  }

  // run Minuit
  // ==========  
  // five-parameter fit to vertex and direction

  Int_t err = 0;
  Int_t flag = 0;

  Double_t fitXpos = 0.0;
  Double_t fitYpos = 0.0;
  Double_t fitZpos = 0.0;
  Double_t fitTheta = 0.0;
  Double_t fitPhi = 0.0;

  Double_t fitXposErr = 0.0;
  Double_t fitYposErr = 0.0;
  Double_t fitZposErr = 0.0;
  Double_t fitThetaErr = 0.0;
  Double_t fitPhiErr = 0.0;

  Double_t* arglist = new Double_t[10];
  arglist[0]=2;  // 1: standard minimization
                 // 2: try to improve minimum
		 
  // re-initialize everything...
  fMinuitPointVertex->mncler();
  fMinuitPointVertex->SetFCN(point_vertex_chi2);
  fMinuitPointVertex->mnexcm("SET STR",arglist,1,err);
  fMinuitPointVertex->mnparm(0,"x",seedX,250.0,-5000.0,+5000.0,err);
  fMinuitPointVertex->mnparm(1,"y",seedY,250.0,-5000.0,+5000.0,err);
  fMinuitPointVertex->mnparm(2,"z",seedZ,250.0,-5000.0,+5000.0,err);
  fMinuitPointVertex->mnparm(3,"theta",seedTheta,0.125*TMath::Pi(),0.0,TMath::Pi(),err);
  fMinuitPointVertex->mnparm(4,"phi",seedPhi,0.25*TMath::Pi(),-1.0*TMath::Pi(),+3.0*TMath::Pi(),err);
  
  flag = fMinuitPointVertex->Migrad();
  fMinuitPointVertex->GetParameter(0,fitXpos,fitXposErr);
  fMinuitPointVertex->GetParameter(1,fitYpos,fitYposErr);
  fMinuitPointVertex->GetParameter(2,fitZpos,fitZposErr);
  fMinuitPointVertex->GetParameter(3,fitTheta,fitThetaErr);
  fMinuitPointVertex->GetParameter(4,fitPhi,fitPhiErr);
  
  delete [] arglist;

  // sort results
  // ============
  vtxX = fitXpos; 
  vtxY = fitYpos;
  vtxZ = fitZpos;
  vtxTime = 950.0;

  dirX = sin(fitTheta)*cos(fitPhi);
  dirY = sin(fitTheta)*sin(fitPhi);
  dirZ = cos(fitTheta);  

  vtxFOM = 0.0;
  
  fPass = 0;               // flag = 0: normal termination
  if( flag==0 ) fPass = 1; // anything else: abnormal termination 

  fItr = point_vertex_iterations();

  // calculate vertex
  // ================
  this->PointVertexChi2(vtxX,vtxY,vtxZ,
                        dirX,dirY,dirZ, 
			vtxAngle,vtxTime,vtxFOM);

  // set vertex and direction
  // ========================
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetDirection(dirX,dirY,dirZ);
  newVertex->SetConeAngle(vtxAngle);
  newVertex->SetFOM(vtxFOM,fItr,fPass);

  // set status
  // ==========
  if( !fPass ) status |= WCSimRecoVertex::kFailPointVertex;
  newVertex->SetStatus(status);

  // print vertex
  // ============
  std::cout << "  fitted point vertex: " << std::endl
            << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "    (px,py,pz)=(" << newVertex->GetDirX() << "," << newVertex->GetDirY() << "," << newVertex->GetDirZ() << ") " << std::endl
            << "      angle=" << newVertex->GetConeAngle() << " vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;

  if( !fPass ) std::cout << "   <warning> point vertex fit failed to converge! Error code: " << flag << std::endl;

  // return vertex
  // =============  
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinder::FitExtendedVertexWithMinuit(WCSimRecoVertex* myVertex)
{
  // initialization
  // ==============
  Double_t vtxX = 0.0;
  Double_t vtxY = 0.0;
  Double_t vtxZ = 0.0;
  Double_t vtxTime = 950.0;

  Double_t dirX = 0.0;
  Double_t dirY = 0.0;
  Double_t dirZ = 0.0;
  
  Double_t vtxAngle = WCSimParameters::CherenkovAngle();

  Double_t vtxFOM = 0.0;

  // seed vertex
  // ===========  
  Bool_t foundSeed = ( myVertex->FoundVertex() 
                    && myVertex->FoundDirection() );

  Double_t seedX = myVertex->GetX();
  Double_t seedY = myVertex->GetY();
  Double_t seedZ = myVertex->GetZ();

  Double_t seedDirX = myVertex->GetDirX();
  Double_t seedDirY = myVertex->GetDirY();
  Double_t seedDirZ = myVertex->GetDirZ();

  Double_t seedTheta = acos(seedDirZ);
  Double_t seedPhi = 0.0;

  if( seedDirX!=0.0 ){
    seedPhi = atan(seedDirY/seedDirX);
  }
  if( seedDirX<=0.0 ){
    if( seedDirY>0.0 ) seedPhi += TMath::Pi();
    if( seedDirY<0.0 ) seedPhi -= TMath::Pi();
  }  

  // current status
  // ==============
  Int_t status = myVertex->GetStatus();

  // reset counter
  // =============
  std::cout << "just before reseting iter counter... iter = " << extended_vertex_iterations() << std::endl;
  extended_vertex_reset_itr();

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fExtendedVertex = newVertex;

  // abort if necessary
  // ==================
  if( foundSeed==0 ){
    std::cout << "   <warning> extended vertex fit failed to find input vertex " << std::endl;   
    status |= WCSimRecoVertex::kFailExtendedVertex;
    newVertex->SetStatus(status);
    return newVertex;
  }

  // run Minuit
  // ==========  
  // five-parameter fit to vertex and direction

  Int_t err = 0;
  Int_t flag = 0;

  Double_t fitXpos = 0.0;
  Double_t fitYpos = 0.0;
  Double_t fitZpos = 0.0;
  Double_t fitTheta = 0.0;
  Double_t fitPhi = 0.0;

  Double_t fitXposErr = 0.0;
  Double_t fitYposErr = 0.0;
  Double_t fitZposErr = 0.0;
  Double_t fitThetaErr = 0.0;
  Double_t fitPhiErr = 0.0;

  Double_t* arglist = new Double_t[10];
  arglist[0]=3;  // 1: standard minimization
                 // 2: try to improve minimum

  // re-initialize everything...
  fMinuitExtendedVertex->mncler();
  fMinuitExtendedVertex->SetFCN(extended_vertex_chi2);
  fMinuitExtendedVertex->mnset();
  fMinuitExtendedVertex->mnexcm("SET PRI",arglist,1,err);
  //std::cout << fMinuitExtendedVertex->mnexcm("SET PRI",arglist,1,err) << std::endl;
  fMinuitExtendedVertex->mnparm(0,"x",seedX,250.0,seedX-5000.0,seedX+5000.0,err);  //initial : 250, +5000, -5000
  fMinuitExtendedVertex->mnparm(1,"y",seedY,250.0,seedY-5000.0,seedY+5000.0,err);
  fMinuitExtendedVertex->mnparm(2,"z",seedZ,250.0,seedZ-5000.0,seedZ+5000.0,err);
  fMinuitExtendedVertex->mnparm(3,"theta",seedTheta,0.125*TMath::Pi(),0.0,TMath::Pi(),err); //initial: 0.125*TMath::Pi(),0.0,TMath::Pi()
  fMinuitExtendedVertex->mnparm(4,"phi",seedPhi,0.25*TMath::Pi(),-1.0*TMath::Pi(),+3.0*TMath::Pi(),err); //initial: 0.25*TMath::Pi(),-1.0*TMath::Pi(),+3.0*TMath::Pi()
 
  flag = fMinuitExtendedVertex->Migrad();
/*  
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  fMinuitExtendedVertex->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
  std::cout << " Minimum chi square = " << amin << "\n";
  std::cout << " Estimated vert. distance to min. = " << edm << "\n";
  std::cout << " Number of variable parameters = " << nvpar << "\n";
  std::cout << " Highest number of parameters defined by user = " << nparx << "\n";
  std::cout << " Status of covariance matrix = " << icstat << "\n";
  fMinuitExtendedVertex->mnprin(3,amin); 
 */
  fMinuitExtendedVertex->GetParameter(0,fitXpos,fitXposErr);
  fMinuitExtendedVertex->GetParameter(1,fitYpos,fitYposErr);
  fMinuitExtendedVertex->GetParameter(2,fitZpos,fitZposErr);
  fMinuitExtendedVertex->GetParameter(3,fitTheta,fitThetaErr);
  fMinuitExtendedVertex->GetParameter(4,fitPhi,fitPhiErr);

  delete [] arglist;

  // sort results
  // ============
  vtxX = fitXpos; 
  vtxY = fitYpos;
  vtxZ = fitZpos;
  vtxTime = 950.0;

  dirX = sin(fitTheta)*cos(fitPhi);
  dirY = sin(fitTheta)*sin(fitPhi);
  dirZ = cos(fitTheta);  

  vtxFOM = 0.0;
  
  fPass = 0;               // flag = 0: normal termination
  if( flag==0 ) fPass = 1; // anything else: abnormal termination 

  fItr = extended_vertex_iterations();
  
  std::cout << "at the end............." << std::endl;

  // calculate vertex
  // ================
  this->ExtendedVertexChi2(vtxX,vtxY,vtxZ,
                           dirX,dirY,dirZ, 
                           vtxAngle,vtxTime,vtxFOM);

  // set vertex and direction
  // ========================
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetDirection(dirX,dirY,dirZ);
  newVertex->SetConeAngle(vtxAngle);
  newVertex->SetFOM(vtxFOM,fItr,fPass);

  // set status
  // ==========
  if( !fPass ) status |= WCSimRecoVertex::kFailExtendedVertex;
  newVertex->SetStatus(status);

  // print vertex
  // ============
  std::cout << "  fitted extended vertex: " << std::endl
            << "    (vx,vy,vz)=(" << newVertex->GetX() << "," << newVertex->GetY() << "," << newVertex->GetZ() << ") " << std::endl
            << "    (px,py,pz)=(" << newVertex->GetDirX() << "," << newVertex->GetDirY() << "," << newVertex->GetDirZ() << ") " << std::endl
            << "      angle=" << newVertex->GetConeAngle() << " vtime=" << newVertex->GetTime() << " itr=" << newVertex->GetIterations() << " fom=" << newVertex->GetFOM() << std::endl;

  if( !fPass ) std::cout << "   <warning> extended vertex fit failed to converge! Error code: " << flag << std::endl;

  // return vertex
  // =============  
  return newVertex;
}
  
void WCSimVertexFinder::PointPositionChi2(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t& vtxTime, Double_t& fom)
{  
  // figure of merit
  // ===============
  Double_t vtxFOM = 0.0;
  Double_t penaltyFOM = 0.0;
  Double_t fixPositionFOM = 0.0;

  // calculate residuals
  // ===================
  this->PointResiduals(vtxX,vtxY,vtxZ);

  // calculate figure of merit
  // =========================
  this->PointPositionChi2(vtxTime,vtxFOM);

  // calculate penalty
  // =================
  this->PenaltyChi2(vtxX,vtxY,vtxZ,penaltyFOM);

  // fix true position
  // =================
  if( fUseTruePosition ){
    this->FixPositionChi2(vtxX,vtxY,vtxZ,fixPositionFOM);
  }

  // calculate overall figure of merit
  // =================================
  fom = vtxFOM + penaltyFOM + fixPositionFOM;

  // truncate
  if( fom<-999.999*fBaseFOM ) fom = -999.999*fBaseFOM;
  
  indexp++;
  
  //for point fit
  std::ostringstream poss;
  //poss << fgVertexFinder->point_position_itr();
  poss << indexp;
  std::string iterSp = poss.str();
  std::string namepointLkl = "likelihood_"+iterSp;
  std::string namepointPDF = "PDF_"+iterSp;
  std::string namepointTRes = "timeRes_"+iterSp;
  std::string namepointFillLkl = "lklFill_"+iterSp;
  
  TH1D* pointhistoLkl = (TH1D*) histPointRes->Clone((namepointLkl+"_pointVtx").c_str());
  TH1D* pointhistoPDF = (TH1D*) histPointPDF->Clone((namepointPDF+"_pointVtx").c_str());
  TH1D* pointhistoTRes = (TH1D*) histPointTimeRes->Clone((namepointTRes+"_pointVtx").c_str());
  TH1D* pointhistFillLkl = (TH1D*) histPointFillLkl->Clone((namepointFillLkl+"_pointVtx").c_str());
  
  myfile->cd();
  pointhistoLkl->Write();
  pointhistoPDF->Write();
  pointhistoTRes->Write();
  pointhistFillLkl->Write();

  return;
}

void WCSimVertexFinder::PointDirectionChi2(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ, Double_t& vtxAngle, Double_t& fom)
{  
  // figure of merit
  // ===============
  Double_t vtxFOM = 0.0;
  Double_t fixPositionFOM = 0.0;
  Double_t fixDirectionFOM = 0.0;
  
  // calculate residuals
  // ===================
  this->PointResiduals(vtxX,vtxY,vtxZ,
                       dirX,dirY,dirZ);

  // calculate figure of merit
  // =========================
  this->PointDirectionChi2(vtxAngle,vtxFOM);

  // fix true position
  // =================
  if( fUseTruePosition ){
    this->FixPositionChi2(vtxX,vtxY,vtxZ,fixPositionFOM);
  }

  // fix true direction
  // ==================
  if( fUseTrueDirection ){
    this->FixDirectionChi2(dirX,dirY,dirZ,fixDirectionFOM);
  }

  // calculate overall figure of merit
  // =================================
  fom = vtxFOM + fixDirectionFOM;

  // truncate
  if( fom<-999.999*fBaseFOM ) fom = -999.999*fBaseFOM;

  return;
}

void WCSimVertexFinder::PointVertexChi2(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ, Double_t& vtxAngle, Double_t& vtxTime, Double_t& fom)
{  
  // figure of merit
  // ===============
  Double_t vtxFOM = 0.0;
  Double_t penaltyFOM = 0.0;
  Double_t fixPositionFOM = 0.0;
  Double_t fixDirectionFOM = 0.0;

  // calculate residuals
  // ===================
  this->PointResiduals(vtxX,vtxY,vtxZ,
                       dirX,dirY,dirZ);

  // calculate figure of merit
  // =========================
  this->PointVertexChi2(vtxAngle,vtxTime,vtxFOM);

  // calculate penalty
  // =================
  this->PenaltyChi2(vtxX,vtxY,vtxZ,penaltyFOM);

  // fix true position
  // =================
  if( fUseTruePosition ){
    this->FixPositionChi2(vtxX,vtxY,vtxZ,fixPositionFOM);
  }

  // fix true direction
  // ==================
  if( fUseTrueDirection ){
    this->FixDirectionChi2(dirX,dirY,dirZ,fixDirectionFOM);
  }

  // calculate overall figure of merit
  // =================================
  fom = vtxFOM + penaltyFOM + fixPositionFOM + fixDirectionFOM;

  // truncate
  if( fom<-999.999*fBaseFOM ) fom = -999.999*fBaseFOM;
  
  //for point fit
  std::ostringstream poss;
  poss << fgVertexFinder->point_vertex_iterations();
  std::string iterSp = poss.str();
  std::string namepointLkl = "likelihood_"+iterSp;
  std::string namepointPDF = "PDF_"+iterSp;
  std::string namepointTRes = "timeRes_"+iterSp;
  std::string namepointFillLkl = "lklFill_"+iterSp;
  
  TH1D* pointhistoLkl = (TH1D*) histPointRes->Clone((namepointLkl+"_pointVtx").c_str());
  TH1D* pointhistoPDF = (TH1D*) histPointPDF->Clone((namepointPDF+"_pointVtx").c_str());
  TH1D* pointhistoTRes = (TH1D*) histPointTimeRes->Clone((namepointTRes+"_pointVtx").c_str());
  TH1D* pointhistFillLkl = (TH1D*) histPointFillLkl->Clone((namepointFillLkl+"_pointVtx").c_str());
  
  myfile->cd();
  pointhistoLkl->Write();
  pointhistoPDF->Write();
  pointhistoTRes->Write();
  pointhistFillLkl->Write();

  return;
}

void WCSimVertexFinder::ExtendedVertexChi2(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ, Double_t& vtxAngle, Double_t& vtxTime, Double_t& fom)
{  
  // figure of merit
  // ===============
  Double_t vtxFOM = 0.0;
  Double_t penaltyFOM = 0.0;
  Double_t fixPositionFOM = 0.0;
  Double_t fixDirectionFOM = 0.0;

  // calculate residuals
  // ===================
  this->ExtendedResiduals(vtxX,vtxY,vtxZ,
                          dirX,dirY,dirZ);

  // calculate figure of merit
  // =========================
  this->ExtendedVertexChi2(vtxAngle,vtxTime,vtxFOM);

  // calculate penalty
  // =================
  this->PenaltyChi2(vtxX,vtxY,vtxZ,penaltyFOM);

  // fix true position
  // =================
  if( fUseTruePosition ){
    this->FixPositionChi2(vtxX,vtxY,vtxZ,fixPositionFOM);
  }

  // fix true direction
  // ==================
  if( fUseTrueDirection ){
    this->FixDirectionChi2(dirX,dirY,dirZ,fixDirectionFOM);
  }

  // calculate overall figure of merit
  // =================================
  fom = vtxFOM + penaltyFOM + fixPositionFOM + fixDirectionFOM;

  // truncate
  if( fom<-999.999*fBaseFOM ) fom = -999.999*fBaseFOM;
  
  //for extended fit
  //converts an int into string
  std::ostringstream oss;
  oss << fgVertexFinder->extended_vertex_iterations();
  std::string iterS = oss.str();
  std::string namemyLkl = "likelihood_"+iterS;
  std::string namemyPDF = "PDF_"+iterS;
  std::string namemyTRes = "timeRes_"+iterS;
  std::string namemyFillLkl = "lklFill_"+iterS;

  //MWMWMW
  std::string namemyFillLmu = "Lmu_"+iterS;
  
  TH1D* myhistoLkl = (TH1D*) histRes->Clone(namemyLkl.c_str());
  TH1D* myhistoPDF = (TH1D*) histPDF->Clone(namemyPDF.c_str());
  TH1D* myhistoTRes = (TH1D*) histTimeRes->Clone(namemyTRes.c_str());
  TH1D* myhistFillLkl = (TH1D*) histFillLkl->Clone(namemyFillLkl.c_str());

  //MWMWMW
  TH1D* myhistFillLmu = (TH1D*) histFillLmu->Clone(namemyFillLmu.c_str());
    
  myfile->cd();
  myhistoLkl->Write();
  myhistoPDF->Write();
  myhistoTRes->Write();
  myhistFillLkl->Write();
  myhistFillLmu->Write();
  
  //std::cout << " [ExtendedVertexChi2] [" << fgVertexFinder->extended_vertex_iterations() << "] (x,y,z)=(" << vtxX << "," << vtxY << "," << vtxZ << ") (px,py,pz)=(" << dirX << "," << dirY << "," << dirZ << ") vtxTime=" << vtxTime << " fom=" << fom << std::endl;

  return;
}

void WCSimVertexFinder::ExtendedVertexChi2(WCSimRecoEvent* myevent, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ, Double_t& timeFOM, Double_t& coneFOM, Double_t& newFOM, Double_t& vtxTime, Double_t& vtxAngle)
{  

  // calculate residuals
  // ===================
  WCSimVertexGeometry::Instance()->LoadEvent(myevent);
  this->ExtendedResiduals(vtxX,vtxY,vtxZ,
                          dirX,dirY,dirZ);

  // calculate figure of merit
  // =========================
  //this->ExtendedVertexChi2(vtxAngle,vtxTime,vtxFOM);
  //this->FitExtendedConePropertiesLnL(vtxAngle,coneFOM);
  this->FitExtendedTimePropertiesLnL(vtxTime,timeFOM);
  //  timeFOM=1.0;
  //this->newChi2(vtxTime,newFOM);

    
  //MWMWMW - NEW CODE IS HERE...UNCOMMENT...
  /*
  Double_t DetH = (WCSimGeometry::Instance()->GetCylFiducialLength())/2.;
  Double_t DetR = (WCSimGeometry::Instance()->GetCylFiducialRadius());
  TH1D* theDh = WCSimTResidPDF::Instance()->GetDistanceArray(1,vtxX/10,vtxY/10,vtxZ/10,dirX,dirY,dirZ,DetH,DetR);

  //  extended_vertex_itr();
  std::ostringstream oss;
  oss << fgVertexFinder->extended_vertex_iterations();
  std::string iterS = oss.str();
  std::string namemytheDh = "theDh_"+iterS;
  std::string namemyFillLmu = "theLmu_"+iterS;
  TH1D* mytheDh = (TH1D*) theDh->Clone(namemytheDh.c_str());
  TH1D* myhistFillLmu = (TH1D*) histFillLmu->Clone(namemyFillLmu.c_str());
    
  myfile->cd();
  mytheDh->Write();
  myhistFillLmu->Write();

  Int_t Nbins = theDh->GetNbinsX();
  Double_t uR = theDh->GetXaxis()->GetXmax();
  Double_t lR = theDh->GetXaxis()->GetXmin();
  Double_t tNorm = theDh->Integral();

  TH1D* hdistMuon = new TH1D("mudist","mudist",Nbins,lR,uR);
  //  std::cout<<"INTEGRAL "<<tNorm<<std::endl;

  Double_t delta,sigma,distPhoton,distMuon;
  Double_t theLhood=0;
  Double_t mdNorm = histFillLmu->Integral();

  theDh->Scale(mdNorm/tNorm);

  Double_t theChi2 = 0;
  for(int i=1; i<Nbins; i++){

    Double_t tempbc = (theDh->GetBinContent(i));
    Double_t mbc = (theDh->GetBinCenter(i));
    Double_t databc = (histFillLmu->GetBinContent(i));
   
    Double_t binerror;
    if( databc > 1 ) {
      binerror = sqrt(databc);
    } else {
      binerror = 1;
    }

    theChi2 += ((databc - tempbc)*(databc - tempbc))/(binerror*binerror);
  }
  
  coneFOM=(sqrt(theChi2))/(Nbins-1);
  //  std::cout<<coneFOM<<std::endl;
  */
  //MWMW Finish uncommenting here

  // calculate penalty
  // =================
  //this->PenaltyChi2(vtxX,vtxY,vtxZ,penaltyFOM);

  //std::cout << "fitted angle?= " << vtxAngle << " vtxTime= " << vtxTime << std::endl;
  return;
}

void WCSimVertexFinder::PointPositionChi2(Double_t& vtxTime, Double_t& fom)
{
  // calculate figure of merit
  // =========================
  this->FitPointTimePropertiesLnL(vtxTime,fom);

  return;
}

void WCSimVertexFinder::PointDirectionChi2(Double_t& vtxAngle, Double_t& fom)
{
  // calculate figure of merit
  // =========================  
  this->FitPointConePropertiesLnL(vtxAngle,fom);

  return;
}

void WCSimVertexFinder::PointVertexChi2(Double_t& vtxAngle, Double_t& vtxTime, Double_t& fom)
{
  // calculate figure of merit
  // =========================
  Double_t timeFOM = 0.0;
  Double_t coneFOM = 0.0;

  this->FitPointConePropertiesLnL(vtxAngle,coneFOM);
  this->FitPointTimePropertiesLnL(vtxTime,timeFOM);
  
  //std::cout << "coneFOM = " << coneFOM << ", timeFOM = " << timeFOM << std::endl;
  
  fom = (fTimeFitWeight*timeFOM+fConeFitWeight*coneFOM)/(fTimeFitWeight+fConeFitWeight);

  return;
}

void WCSimVertexFinder::ExtendedVertexChi2(Double_t& vtxAngle, Double_t& vtxTime, Double_t& fom)
{
  // calculate figure of merit
  // =========================
  Double_t timeFOM = 0.0;
  Double_t coneFOM = 0.0;

  //this->FitExtendedConePropertiesLnL(vtxAngle,coneFOM);

  this->FitExtendedTimePropertiesLnL(vtxTime,timeFOM);
  
  //fom = (fTimeFitWeight*timeFOM+fConeFitWeight*coneFOM)/(fTimeFitWeight+fConeFitWeight);
  fom = timeFOM;
  
  std::cout <<"coneFOM = " << coneFOM << ", timeFOM = " << timeFOM << ", fom = " << fom << std::endl;

  return;
}

void WCSimVertexFinder::PointResiduals(Double_t vtxX, Double_t vtxY, Double_t vtxZ)
{
  return WCSimVertexGeometry::Instance()->CalcPointResiduals(vtxX,vtxY,vtxZ,0.0, 
                                                              0.0, 0.0, 0.0);
}

void WCSimVertexFinder::PointResiduals(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ)
{  
  return WCSimVertexGeometry::Instance()->CalcPointResiduals(vtxX,vtxY,vtxZ,0.0,
                                                              dirX,dirY,dirZ);
}

void WCSimVertexFinder::ExtendedResiduals(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirX, Double_t dirY, Double_t dirZ)
{
  //std::cout << "I am alive2" << std::endl;
  return WCSimVertexGeometry::Instance()->CalcExtendedResiduals(vtxX,vtxY,vtxZ,0.0,
                                                                 dirX,dirY,dirZ);
}
/*
void WCSimVertexFinder::FitTimePropertiesFoM(Double_t& vtxTime, Double_t& vtxFOM)
{ 
  // calculate mean and rms
  // ====================== 
  Double_t meanTime = 950.0;

  this->FindSimpleTimeProperties(meanTime); 

  // reset counter
  // =============
  time_fit_reset_itr();

  // run Minuit
  // ==========  
  // one-parameter fit to vertex time

  Int_t err = 0;
  Int_t flag = 0;

  Double_t seedTime = meanTime;

  Double_t fitTime = 0.0;
  Double_t fitTimeErr = 0.0;
  
  Double_t* arglist = new Double_t[10];
  arglist[0]=1;  // 1: standard minimization
                 // 2: try to improve minimum

  // re-initialize everything...
  fMinuitTimeFit->mncler();
  fMinuitTimeFit->SetFCN(vertex_time_fom);
  fMinuitTimeFit->mnexcm("SET STR",arglist,1,err);
  fMinuitTimeFit->mnparm(0,"vtxTime",seedTime,50.0,0.0,2000.0,err);
  
  flag = fMinuitTimeFit->Migrad();
  fMinuitTimeFit->GetParameter(0,fitTime,fitTimeErr);
  
  delete [] arglist;


  // calculate figure of merit
  // =========================
  Double_t fom = -999.999*fBaseFOM;

  this->TimePropertiesFoM(fitTime,fom);  


  // return figure of merit
  // ======================
  vtxTime = fitTime;
  vtxFOM = fom;

  return;
}
*/
void WCSimVertexFinder::FitPointTimePropertiesLnL(Double_t& vtxTime, Double_t& vtxFOM)
{ 
  // calculate mean and rms
  // ====================== 
  Double_t meanTime = 950.0;

  this->FindSimpleTimeProperties(meanTime); 

  // reset counter
  // =============
  time_fit_reset_itr();

  // run Minuit
  // ==========  
  // one-parameter fit to time profile

  Int_t err = 0;
  Int_t flag = 0;

  Double_t seedTime = meanTime;

  Double_t fitParam = fFixTimeParam0;

  Double_t fitTime = 0.0;
  Double_t fitTimeErr = 0.0;  
  
  Double_t* arglist = new Double_t[10];
  arglist[0]=1;  // 1: standard minimization
                 // 2: try to improve minimum

  // re-initialize everything...
  fMinuitTimeFit->mncler();
  //remove these lines
  if( fUseChrom ) fMinuitTimeFit->SetFCN(vertex_time_lnl_chrom);
  if( !fUseChrom ) fMinuitTimeFit->SetFCN(vertex_time_lnl);
  //end
  fMinuitTimeFit->mnexcm("SET STR",arglist,1,err);
  fMinuitTimeFit->mnparm(0,"vtxTime",seedTime,50.0,0.0,2000.0,err);
  
  flag = fMinuitTimeFit->Migrad();
  fMinuitTimeFit->GetParameter(0,fitTime,fitTimeErr);
  
  //std::cout <<"fitTime = " << fitTime << ", fitTimeErr = " << fitTimeErr << std::endl; 
   
  delete [] arglist;


  // calculate figure of merit
  // =========================
  Double_t fom = -999.999*fBaseFOM;
  
  //remove these lines
  if( fUseChrom ) this->TimePropertiesLnLchrom(fitTime,fitParam,fom);
  if( !fUseChrom ) this->TimePropertiesLnL(fitTime,fitParam,fom);
  //end

  //
   //std::cout << "   TimeFit: itr=" << time_fit_iterations() << " seedTime=" << seedTime << " fitTime=" << fitTime << " fitParam=" << fitParam << " fom=" << fom << std::endl;
  //

  // --- debug ---
  fTimeParam0 = fitParam;

  // return figure of merit
  // ======================
  vtxTime = fitTime;
  vtxFOM = fom;

  return;
}

void WCSimVertexFinder::FitExtendedTimePropertiesLnL(Double_t& vtxTime, Double_t& vtxFOM)
{   
  //use chromPDF for extended Fit
  if (fUseChromPDFextFit) {fUseChrom = 1; fFitTimeParams = 1;}
  
/*  
  // return result from point fit
  // ============================
  if( fFitTimeParams==0 ){
    return this->FitPointTimePropertiesLnL(vtxTime,vtxFOM);
  }
  //std::cout << "i am alive" << std::endl;
*/
  // calculate mean and rms
  // ====================== 
  Double_t meanTime = 950.0;

  this->FindSimpleTimeProperties(meanTime); 

  // reset counter
  // =============
  time_fit_reset_itr();

  // run Minuit
  // ==========  
  // two-parameter fit to time profile

  Int_t err = 0;
  Int_t flag = 0;

  Double_t seedTime = meanTime;
  //Ioana from Tian============================
  Bool_t istruehits = (WCSimInterface::Instance())->IsTrueHits();
  //if( istruehits ) seedTime = 0.0;
  //==============================
  Double_t seedParam = fFixTimeParam0;

  Double_t fitTime = seedTime;
  Double_t fitTimeErr = 0.0;  

  Double_t fitParam = seedParam;
  Double_t fitParamErr = 0.0;
  
  Double_t* arglist = new Double_t[10];
  arglist[0]=1;  // 1: standard minimization
                 // 2: try to improve minimum
		 
  //std::cout << "seedTime = " << seedTime << std::endl;

  // re-initialize everything...
  fMinuitTimeFit->mncler();
  if( fUseChrom ) fMinuitTimeFit->SetFCN(vertex_time_lnl_chrom);
  //std::cout << "inside FitExtendedTimePropertiesLnL....." << std::endl;
  if( !fUseChrom ) fMinuitTimeFit->SetFCN(vertex_time_lnl);
  fMinuitTimeFit->mnexcm("SET STR",arglist,1,err);
  fMinuitTimeFit->mnparm(0,"vtxTime",seedTime,50.0,-1000.0,1000.0,err); //....TX
  fMinuitTimeFit->mnparm(1,"vtxParam",seedParam,0.05,0.0,1.0,err);
  
  flag = fMinuitTimeFit->Migrad();
  fMinuitTimeFit->GetParameter(0,fitTime,fitTimeErr);
  fMinuitTimeFit->GetParameter(1,fitParam,fitParamErr);
  
  delete [] arglist;


  // calculate figure of merit
  // =========================
  Double_t fom = -999.999*fBaseFOM;

  if( fUseChrom ) this->TimePropertiesLnLchrom(fitTime,fitParam,fom);
  if( !fUseChrom ) this->TimePropertiesLnL(fitTime,fitParam,fom);

   std::cout << "   TimeFit: itr=" << time_fit_iterations() << " seedTime=" << seedTime << " fitTime=" << fitTime << " fitParam=" << fitParam << " fom=" << fom << std::endl;

  // --- debug ---
  fTimeParam0 = fitParam;

  // return figure of merit
  // ======================
  vtxTime = fitTime;
  vtxFOM = fom;

  return;
}

void WCSimVertexFinder::FitConePropertiesFoM(Double_t& coneAngle, Double_t& coneFOM)
{
  coneAngle = WCSimParameters::CherenkovAngle(); //...chrom1.38 // nominal cone angle

  this->ConePropertiesFoM(coneFOM);

  return;
}

void WCSimVertexFinder::FitPointConePropertiesLnL(Double_t& coneAngle, Double_t& coneFOM)
{  
  coneAngle  = WCSimParameters::CherenkovAngle(); //...chrom1.38, nominal cone angle
    
  this->ConePropertiesLnL(fFixConeParam0,fFixConeParam1,fFixConeParam2,
                          coneAngle,coneFOM);  

  // --- debug ---
  fConeParam0 = fFixConeParam0;
  fConeParam1 = fFixConeParam1;
  fConeParam2 = fFixConeParam2;

  return;
}

void WCSimVertexFinder::FitExtendedConePropertiesLnL(Double_t& coneAngle, Double_t& coneFOM)
{  
  // return result from point fit
  // ============================
  if( fFitConeParams==0 ){
    return this->FitPointConePropertiesLnL(coneAngle,coneFOM);
  }

  // reset counter
  // =============
  cone_fit_reset_itr();

  // run Minuit
  // ==========  
  // one-parameter fit to angular distribution

  Int_t err = 0;
  Int_t flag = 0;

  Double_t seedParam0 = fFixConeParam0;
  Double_t seedParam1 = fFixConeParam1;
  Double_t seedParam2 = fFixConeParam2;

  Double_t fitParam0 = seedParam0;
  Double_t fitParam1 = seedParam1;
  Double_t fitParam2 = seedParam2;

  Double_t fitParam0Err = 0.0;
  Double_t fitParam1Err = 0.0; 
  Double_t fitParam2Err = 0.0;

  Double_t fitAngle  = WCSimParameters::CherenkovAngle();
  
  Double_t* arglist = new Double_t[10];
  arglist[0]=1;  // 1: standard minimization
                 // 2: try to improve minimum

  // re-initialize everything...
  fMinuitConeFit->mncler();
  fMinuitConeFit->SetFCN(vertex_cone_lnl);
  fMinuitConeFit->mnexcm("SET STR",arglist,1,err);
  fMinuitConeFit->mnparm(0,"vtxParam0",seedParam0,0.25,0.0,1.0,err);
  fMinuitConeFit->mnparm(1,"vtxParam1",seedParam1,0.25,0.0,1.0,err);
  fMinuitConeFit->mnparm(2,"vtxParam2",seedParam2,0.25,0.0,1.0,err);

  flag = fMinuitConeFit->Migrad();
  fMinuitConeFit->GetParameter(0,fitParam0,fitParam0Err);
  fMinuitConeFit->GetParameter(1,fitParam1,fitParam1Err);
  fMinuitConeFit->GetParameter(2,fitParam2,fitParam2Err);
  
  delete [] arglist;


  // calculate figure of merit
  // =========================
  Double_t fom = -999.999*fBaseFOM;
  
  this->ConePropertiesLnL(fitParam0,fitParam1,fitParam2,
                          fitAngle,fom);  

  //
  // std::cout << "   ConeFit: itr=" << cone_fit_iterations() << " fitParam0=" << fitParam0 << " fitParam1=" << fitParam1 << " fitParam2=" << fitParam2 << " fom=" << fom << std::endl;
  // 

  // --- debug ---
  fConeParam0 = fitParam0;
  fConeParam1 = fitParam1;
  fConeParam2 = fitParam2;

  // return figure of merit
  // ======================
  coneAngle = fitAngle;
  coneFOM = fom;

  return;
}

void WCSimVertexFinder::FindSimpleTimeProperties(Double_t& vtxTime)
{
  // reset mean and rms
  // ================== 
  Double_t meanTime = 950.0;

  // calculate mean and rms of hits inside cone
  // ==========================================
  Double_t Swx = 0.0;
  Double_t Sw = 0.0;

  Double_t delta = 0.0;
  Double_t sigma = 0.0;
  Double_t weight = 0.0;
  Double_t deweight = 0.0;
  Double_t deltaAngle = 0.0;

  Double_t myConeEdge = WCSimParameters::CherenkovAngle();      // [degrees]
  Double_t myConeEdgeSigma = 7.0;  // [degrees]

  for( Int_t idigit=0; idigit<WCSimVertexGeometry::Instance()->GetNDigits(); idigit++ ){

    if( WCSimVertexGeometry::Instance()->IsFiltered(idigit) ){
      delta = WCSimVertexGeometry::Instance()->GetDelta(idigit);
      sigma = WCSimVertexGeometry::Instance()->GetDeltaSigma(idigit);
      weight = 1.0/(sigma*sigma);

      // profile in angle
      deltaAngle = WCSimVertexGeometry::Instance()->GetAngle(idigit) - myConeEdge;
     
      // deweight hits outside cone
      if( deltaAngle<=0.0 ){
        deweight = 1.0;
      }
      else{
        deweight = 1.0/(1.0+(deltaAngle*deltaAngle)/(myConeEdgeSigma*myConeEdgeSigma));
      }

      // add to running total
      Swx += deweight*weight*delta;
      Sw  += deweight*weight;
    }
  }

  if( Sw>0.0 ){
    meanTime = Swx/Sw;
  }

  // return mean and rms
  // ===================
  vtxTime = meanTime;

  return;
}

void WCSimVertexFinder::TimePropertiesLnL(Double_t vtxTime, Double_t vtxParam, Double_t& vtxFOM)
{ 
  histPointTimeRes->Reset();
  histPointPDF->Reset();
  histPointRes->Reset();
  histPointFillLkl->Reset();

  // nuisance parameters
  // ===================
  Double_t scatter = vtxParam; 

  // internal variables
  // ==================
  Double_t delta = 0.0;       // time residual of each hit
  Double_t sigma = 0.0;       // time resolution of each hit

  Double_t sigmaEarly = 1.5;  // width of early light
  Double_t sigmaLate  = 3.5;  // width of late light
  Double_t deltaShort = 5.0;  // decay time for scattered light [short]
  Double_t deltaLong  = 10.0; // decay time for scattered light [long]

  Double_t alpha = scatter;   // size of scattering (Gaussian+Exponential)
  Double_t beta  = 0.15;      // size of late light (second Gaussian)
  Double_t gamma = 0.66;      // coefficeient for double-exponential

  Double_t A = 0.0;           // normalisation of first Gaussian
  Double_t Ascat = 0.0;       // normalisation of second Gaussian
  Double_t Bshort = 0.0;      // normalisation of scattering (Gaussian+Exponential)
  Double_t Blong = 0.0;       // normalisation of scattering (Gaussian+Exponential)

  Double_t Preal = 0.0;       // probability of real hit
  Double_t P = 0.0;           // probability of hit

  Double_t chi2 = 0.0;        // log-likelihood: chi2 = -2.0*log(L)
  Double_t ndof = 0.0;        // total number of hits
  Double_t fom = 0.0;         // figure of merit

  // tuning parameters
  // =================
  Double_t fTimeFitNoiseRate = 0.10;  // hits/ns [0.40 for electrons, 0.02 for muons]
  
  // add noise to model
  // ==================
  Double_t nFilterDigits = WCSimVertexGeometry::Instance()->GetNFilterDigits();
  Double_t Pnoise = fTimeFitNoiseRate/nFilterDigits;
  //Double_t nDigits = WCSimVertexGeometry::Instance()->GetNDigits();
  //Double_t Pnoise = fTimeFitNoiseRate/nDigits;
  //std::cout << nDigits << std::endl;
  
   Bool_t istruehits = (WCSimInterface::Instance())->IsTrueHits();

  // loop over digits
  // ================
  for( Int_t idigit=0; idigit<WCSimVertexGeometry::Instance()->GetNDigits(); idigit++ ){

    if( WCSimVertexGeometry::Instance()->IsFiltered(idigit) ){
      delta = WCSimVertexGeometry::Instance()->GetDelta(idigit) - vtxTime; 
      
      //set a larger sigma than the real resolution, as a function of # of photons per PMT
      //this is necessary to build a PDF with a larger RMS for true hits
      if (istruehits) {
      	sigma = 2.5; //erika change
	WCSimRecoDigit* recoDigit = (WCSimRecoDigit*)(currentEv->GetDigit(idigit));
	Double_t peTube = recoDigit->GetQPEs();
	if (2.5-(0.05*peTube) > WCSimVertexGeometry::Instance()->GetDeltaSigma(idigit)) sigma = 2.5 - (0.05*peTube); //erika change?? 2.0 to 2.5
	else sigma = 0.1;
      }
      else sigma = WCSimVertexGeometry::Instance()->GetDeltaSigma(idigit);
      
      //if (WCSimVertexGeometry::Instance()->GetDistPhoton(idigit) != 0) std::cout << idigit << ", GetDistPhoton = " << WCSimVertexGeometry::Instance()->GetDistPhoton(idigit) << std::endl;

      A      = 1.0 / ( 2.0*sigma*sqrt(0.5*TMath::Pi()) );
      Ascat  = 1.0 / ( (sigmaEarly+sigmaLate)*sqrt(0.5*TMath::Pi()) );
      Bshort = 1.0 / ( sigmaEarly*sqrt(0.5*TMath::Pi()) + (9.0/8.0)*deltaShort );
      Blong  = 1.0 / ( sigmaEarly*sqrt(0.5*TMath::Pi()) + (9.0/8.0)*deltaLong );
      
      if( delta<=0 ){
      Preal = A*exp(-(delta*delta)/(2.0*sigma*sigma));
      /*
        Preal = (1.0-beta)*(1.0-alpha)*A*exp(-(delta*delta)/(2.0*sigma*sigma));
                + beta*(1.0-alpha)*Ascat*exp(-(delta*delta)/(2.0*sigmaEarly*sigmaEarly))
		   + alpha*gamma*Bshort*exp(-(delta*delta)/(2.0*sigmaEarly*sigmaEarly))
               + alpha*(1.0-gamma)*Blong*exp(-(delta*delta)/(2.0*sigmaEarly*sigmaEarly));
	*/
        P = (1.0-Pnoise)*Preal + Pnoise;
      }
      else{
      Preal = A*exp(-(delta*delta)/(2.0*sigma*sigma));
      /*
        Preal = (1.0-beta)*(1.0-alpha)*A*exp(-(delta*delta)/(2.0*sigma*sigma)); 
	        + beta*(1.0-alpha)*Ascat*exp(-(delta*delta)/(2.0*sigmaLate*sigmaLate)) 
	        + alpha*gamma*Bshort*( (delta/deltaShort)/pow((1.0+4.0*(delta/deltaShort)*(delta/deltaShort)),2.0) + exp(-delta/deltaShort) ) 
	     + alpha*(1.0-gamma)*Blong*( (delta/deltaLong)/pow((1.0+4.0*(delta/deltaLong)*(delta/deltaLong)),2.0) + exp(-delta/deltaLong) );
       */ 
	P = (1.0-Pnoise)*Preal + Pnoise;
      }
      
      //fill the timing residual histo
      histPointTimeRes->Fill(delta);
      
       //fill the PDF  histo
      Int_t binPDF = histPointPDF->FindFixBin(delta);
      //std::cout << "delta = " << delta << ", binPDF = " << binPDF << ", histPointPDF->GetBinContent(binPDF) = " << histPointPDF->GetBinContent(binPDF) << std::endl; 
      histPointPDF->SetBinContent(binPDF,Preal+histPointPDF->GetBinContent(binPDF));
      
      chi2 += -2.0*log(P);
      ndof += 1.0;
      
      //fill the likelihood histo
      Int_t binLkl = histPointRes->FindFixBin(delta);
      //std::cout << "delta = " << delta << ", binLkl = " << binLkl << ", histPointRes->GetBinContent(binLkl) = " << histPointRes->GetBinContent(binLkl) << std::endl; 
      histPointRes->SetBinContent(binLkl,-2*log(P)+histPointRes->GetBinContent(binLkl));
      histPointFillLkl->Fill(-2*log(P));
    }
  }

  // calculate figure of merit
  if( ndof>0.0 ){
    fom = fBaseFOM - 5.0*chi2/ndof;
  }  

  // return figure of merit
  // ======================
  vtxFOM = fom;
  
  //std:: cout << "fom = " << fom << std::endl;

  return;
}

void WCSimVertexFinder::TimePropertiesLnLchrom(Double_t vtxTime, Double_t vtxParam, Double_t& vtxFOM)
{ 
  //  std::cout << "Ioana..... inside TimePropertiesLnLchrom" << std::endl;
  
  histTimeRes->Reset();
  histPDF->Reset();
  histRes->Reset();
  histFillLkl->Reset();
  
  //MWMWMW
  histFillLmu->Reset();
  
  //TStopwatch swatch; // <----------

  // nuisance parameters
  // ===================
  Double_t scatter = vtxParam; 

  // internal variables
  // ==================
  Double_t delta = 0.0;       // time residual of each hit
  Double_t sigma = 0.0;       // time resolution of each hit
  Double_t distPhoton = 0.0;  // photon flight distance 
  Double_t distMuon = 0.0;
  
  Double_t Preal = 0.0;       // probability of real hit
  Double_t Pgauss = 0.0;      // probability including chromatic effect convoluted with a gaussian
  Double_t P = 0.0;           // probability of hit

  Double_t chi2 = 0.0;        // log-likelihood: chi2 = -2.0*log(L)
  Double_t ndof = 0.0;        // total number of hits
  Double_t fom = 0.0;         // figure of merit
  
  //parameters for PLmuon function  //erika change the cut 500 t0 300 softcutofflatecut 
  /*
  Double_t Norm       = 10.0;
  Double_t softcutoff = 75;//200
  Double_t earlysigma = 2.0/sqrt(Norm); // P(l=-20cm)=0.01
  Double_t earlycut   = 0; //2.0*earlysigma; 
  Double_t latesigma  = 5.0; latesigma = 25.0/(10.0*sqrt(Norm)); // P(l=525cm)=0.01
  Double_t latecut    = softcutoff+25.0;
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  Double_t PLmu       = 0.0;
  */
  Double_t Norm       = 10.0;
  Double_t softcutoff = 1.0;
  Double_t earlysigma = 100.0/sqrt(Norm);//Ioana...originally = 50
  Double_t earlycut   = 1.0;  
  Double_t latesigma  = 100.0;//Ioana...originally = 50
  Double_t latecut    = 0;
  Double_t normF      = 1.0/((earlysigma+latesigma)*(TMath::Pi()/2.0)+softcutoff);
  Double_t PLmu       = 0.0;
  

  if(fLMuonFilter){
    softcutoff= fmaxLMuon;
    latesigma = (25)/(10.0*sqrt(Norm)); // P(l=525cm)=0.01
    latecut    = fmaxLMuon + 25.0;
  }
  // tuning parameters
  // =================
  Double_t fTimeFitNoiseRate = 0.10;  // hits/ns [0.40 for electrons, 0.02 for muons]
  
  // add noise to model
  // ==================
  Double_t nFilterDigits = WCSimVertexGeometry::Instance()->GetNFilterDigits();
  Double_t Pnoise = fTimeFitNoiseRate/nFilterDigits;
  

  // loop over digits
  // ================
  for( Int_t idigit=0; idigit<WCSimVertexGeometry::Instance()->GetNDigits(); idigit++ ){

    if( WCSimVertexGeometry::Instance()->IsFiltered(idigit) ){
    
      //swatch.Start(); // <----------
    
      delta = WCSimVertexGeometry::Instance()->GetDelta(idigit) - vtxTime;
      sigma = WCSimVertexGeometry::Instance()->GetDeltaSigma(idigit);
      distPhoton = WCSimVertexGeometry::Instance()->GetDistPhoton(idigit);
      distMuon = WCSimVertexGeometry::Instance()->GetDistTrack(idigit);
      
      if (distPhoton == 0) distPhoton = WCSimVertexGeometry::Instance()->GetDistPoint(idigit);
      
      //get chromatic P		
      Pgauss = WCSimTResidPDF::Instance()->MakeChromPeakPDF(delta,distPhoton,sigma);
      
      //get hit weight based on the muon distance  
      /*
      if( distMuon > (softcutoff-earlycut) ) PLmu = Norm/(1.0+((distMuon-softcutoff+earlycut)*(distMuon-softcutoff+earlycut)/(latesigma*latesigma)));
      else if ( distMuon > (-1.0*earlycut)) PLmu = Norm;
      else PLmu = Norm/(1.0+((distMuon+earlycut)*(distMuon+earlycut))/(earlysigma*earlysigma));//-1.0
      */
      if( distMuon > 1.0 ) PLmu = Norm/(1.0+((distMuon-softcutoff+earlycut)*(distMuon-softcutoff+earlycut)/(latesigma*latesigma)));
      else if ( distMuon > -1.0) PLmu = Norm;
      else PLmu = Norm/(1.0+((distMuon+earlycut)*(distMuon+earlycut))/(earlysigma*earlysigma));//-1.0
      
      
      //combine the weight and chrom P
      Preal = PLmu*Pgauss; //normalization already done in TResidPDF
      
//============ color-dependent cherenkov angle ==========================================
      //Pgauss = WCSimTResidPDF::Instance()->MakeChromPeakPDF(delta,distPhoton,sigma,distMuon);      
      //Preal = Pgauss;
//============================================
      //get the final P
      P = (1.0-Pnoise)*Preal+Pnoise;
      chi2 += -2.0*log(P);
      ndof += 1.0;
      
      
      ////////////fill histograms//////////
      //fill the timing residual histo
      histTimeRes->Fill(delta);
      
      //MWMWMW
      Double_t mbinwidth = histFillLmu->GetBinWidth(1);
      Double_t gwt,Dm;

      for(int kk=-4; kk<5; kk++){
	Double_t cutoff=1.0;
	Dm = distMuon + kk*(mbinwidth/2.);
	gwt = TMath::Gaus((distMuon-Dm),0.,(mbinwidth/2.));

	if(Dm>100.){
	  cutoff = exp((100-Dm)/10.);
	}
	histFillLmu->Fill(Dm,Pgauss*cutoff*gwt);
      }
      /*
      Double_t cutoff=1.0;
      if(distMuon>100.){
	cutoff = exp((100-distMuon)/10.);
      }
      //      histFillLmu->Fill(distMuon,cutoff);
      histFillLmu->Fill(distMuon,Pgauss*cutoff*gwt);
      */

      //fill the PDF  histo
      Int_t binPDF = histPDF->FindFixBin(delta); 
      histPDF->SetBinContent(binPDF,Pgauss+histPDF->GetBinContent(binPDF));
      
      //std::cout << "P = " << P << ", chi2 = " << chi2 << std::endl; 
      
      //fill the likelihood histo
      Int_t binLkl = histRes->FindFixBin(delta); 
      histRes->SetBinContent(binLkl,-2*log(P)+histRes->GetBinContent(binLkl));
      histFillLkl->Fill(-2*log(P));
      
      //swatch.Stop(); // <----------
      //std::cout << "for each digit in : TimePropertiesLnLchrom" << swatch.RealTime() << "\n"; // <----------
      
    }
  }

  // calculate figure of merit
  // =========================   
  if( ndof>0.0 ){
    fom = fBaseFOM - 5.0*chi2/ndof;
  }

  // return figure of merit
  // ======================
  vtxFOM = fom;
  
  return;
}

void WCSimVertexFinder::ConePropertiesLnL(Double_t coneParam0, Double_t coneParam1, Double_t coneParam2, Double_t& coneAngle, Double_t& coneFOM)
{  
  // nuisance parameters
  // ===================
  Double_t alpha  = coneParam0;
  Double_t alpha0 = coneParam1;
  Double_t beta   = coneParam2;

  // internal variables
  // ==================
  Double_t deltaAngle = 0.0;
  Double_t sigmaAngle = 7.0;
  Double_t Angle0 = WCSimParameters::CherenkovAngle();
  Double_t deltaAngle0 = Angle0*alpha0;
  
  Double_t digitQ = 0.0;
  Double_t sigmaQmin = 1.0;
  Double_t sigmaQmax = 10.0;
  Double_t sigmaQ = 0.0;

  Double_t A = 0.0;
  
  Double_t PconeA = 0.0;
  Double_t PconeB = 0.0;
  Double_t Pmu = 0.0;
  Double_t Pel = 0.0;

  Double_t Pcharge = 0.0;
  Double_t Pangle = 0.0;
  Double_t P = 0.0;

  Double_t chi2 = 0.0;
  Double_t ndof = 0.0;

  Double_t angle = 46.0;
  Double_t fom = 0.0;

  // hard-coded parameters: 200 kton (100 kton)
  // ==========================================
  Double_t lambdaMuShort = 0.5; //  0.5;
  Double_t lambdaMuLong  = 5.0; // 15.0;
  Double_t alphaMu =       1.0; //  4.5;

  Double_t lambdaElShort = 1.0; //  2.5;
  Double_t lambdaElLong =  7.5; // 15.0;
  Double_t alphaEl =       6.0; //  3.5;

  // numerical integrals
  // ===================
  fSconeA = 21.9938;  
  fSconeB =  0.0000;

  // inside cone
  Int_t nbinsInside = 420;
  for( Int_t n=0; n<nbinsInside; n++ ){
    deltaAngle = -Angle0 + (n+0.5)*(Angle0/(double)nbinsInside);
    fSconeB += 1.4944765*sin( (Angle0+deltaAngle)*(TMath::Pi()/180.0) )
                           *( 1.0/(1.0+(deltaAngle*deltaAngle)/(deltaAngle0*deltaAngle0)) )
                           *( Angle0/(double)nbinsInside );
  }

  // outside cone
  if( fIntegralsDone == 0 ){
    fSmu = 0.0;
    fSel = 0.0;

    Int_t nbinsOutside = 1380;
    for( Int_t n=0; n<nbinsOutside; n++ ){
      deltaAngle = 0.0 + (n+0.5)*(138.0/(double)nbinsOutside);

      fSmu += 1.4944765*sin( (Angle0+deltaAngle)*(TMath::Pi()/180.0) )
                          *( 1.0/(1.0+alphaMu*(lambdaMuShort/lambdaMuLong)) )*( 1.0/(1.0+(deltaAngle*deltaAngle)/(lambdaMuShort*lambdaMuShort)) 
	  			            + alphaMu*(lambdaMuShort/lambdaMuLong)/(1.0+(deltaAngle*deltaAngle)/(lambdaMuLong*lambdaMuLong)) )
                          *( 138.0/(double)nbinsOutside );

      fSel += 1.4944765*sin( (Angle0+deltaAngle)*(TMath::Pi()/180.0) )
                          *( 1.0/(1.0+alphaEl*(lambdaElShort/lambdaElLong)) )*( 1.0/(1.0+(deltaAngle*deltaAngle)/(lambdaElShort*lambdaElShort)) 
				          + alphaEl*(lambdaElShort/lambdaElLong)/(1.0+(deltaAngle*deltaAngle)/(lambdaElLong*lambdaElLong)) )
                          *( 138.0/(double)nbinsOutside );
    }

    std::cout << " --- calculating integrals: Smu=" << fSmu << " Sel=" << fSel << std::endl;

    fIntegralsDone = 1;
  }


  // loop over digits
  // ================
  for( Int_t idigit=0; idigit<WCSimVertexGeometry::Instance()->GetNDigits(); idigit++ ){

    if( WCSimVertexGeometry::Instance()->IsFiltered(idigit) ){
      digitQ = WCSimVertexGeometry::Instance()->GetDigitQ(idigit);
      deltaAngle = WCSimVertexGeometry::Instance()->GetAngle(idigit) - Angle0;

      // pulse height distribution
      // =========================
      if( deltaAngle<=0 ){
	sigmaQ = sigmaQmax;
      }
      else{
        sigmaQ = sigmaQmin + (sigmaQmax-sigmaQmin)/(1.0+(deltaAngle*deltaAngle)/(sigmaAngle*sigmaAngle));
      }

      A = 1.0/(log(2.0)+0.5*TMath::Pi()*sigmaQ);

      if( digitQ<1.0 ){
        Pcharge = 2.0*A*digitQ/(1.0+digitQ*digitQ);
      }
      else{
        Pcharge = A/(1.0+(digitQ-1.0)*(digitQ-1.0)/(sigmaQ*sigmaQ));
      }

      // angular distribution
      // ====================
      A = 1.0/( alpha*fSconeA + (1.0-alpha)*fSconeB 
               + beta*fSmu + (1.0-beta)*fSel ); // numerical integrals 

      if( deltaAngle<=0 ){

        // pdfs inside cone:
        PconeA = 1.4944765*sin( (Angle0+deltaAngle)*(TMath::Pi()/180.0) );
        PconeB = 1.4944765*sin( (Angle0+deltaAngle)*(TMath::Pi()/180.0) )
                          *( 1.0/(1.0+(deltaAngle*deltaAngle)/(deltaAngle0*deltaAngle0)) );

        Pangle = A*( alpha*PconeA+(1.0-alpha)*PconeB );
      }		
      else{

        // pdfs outside cone
        Pmu = 1.4944765*sin( (Angle0+deltaAngle)*(TMath::Pi()/180.0) )
                       *( 1.0/(1.0+alphaMu*(lambdaMuShort/lambdaMuLong)) )*( 1.0/(1.0+(deltaAngle*deltaAngle)/(lambdaMuShort*lambdaMuShort)) 
                                          + alphaMu*(lambdaMuShort/lambdaMuLong)/(1.0+(deltaAngle*deltaAngle)/(lambdaMuLong*lambdaMuLong)) );

        Pel = 1.4944765*sin( (Angle0+deltaAngle)*(TMath::Pi()/180.0) )
                       *( 1.0/(1.0+alphaEl*(lambdaElShort/lambdaElLong)) )*( 1.0/(1.0+(deltaAngle*deltaAngle)/(lambdaElShort*lambdaElShort)) 
                                          + alphaEl*(lambdaElShort/lambdaElLong)/(1.0+(deltaAngle*deltaAngle)/(lambdaElLong*lambdaElLong)) );

        Pangle = A*( beta*Pmu+(1.0-beta)*Pel );
      }

      // overall probability
      // ===================
      P = Pcharge*Pangle;
      
      chi2 += -2.0*log(P);
      ndof += 1.0;
    }
  }

  // calculate figure of merit
  // =========================   
  if( ndof>0.0 ){
    fom = fBaseFOM - 5.0*chi2/ndof;
    angle = beta*43.0 + (1.0-beta)*49.0;
  }

  //std::cout << "[ConePropertiesLnL] " << " fom = " << fom << std::endl;

  // return figure of merit
  // ======================
  coneAngle = angle;
  coneFOM = fom;

  return;
}

void WCSimVertexFinder::TimePropertiesFoM(Double_t vtxTime, Double_t& vtxFOM)
{ 
  // calculate figure of merit
  // =========================   
  Double_t Swx = 0.0;
  Double_t Sw = 0.0; 

  Double_t delta = 0.0;
  Double_t sigma = 0.0;

  Double_t weight = 0.0;
  Double_t deweight = 0.0;
  Double_t inweight = 0.0;
  Double_t outweight = 0.0;
  Double_t timeweight = 0.0;

  Double_t deltaAngle = 0.0;
  Double_t deltaEdge = 0;

  Double_t alpha = 0.0;
  Double_t penalty = 0.011; 
 
  // [ Weight = exp(-(delta*delta)/(2.0*sigma*sigma)) - Penalty,
  //   This drops below zero at Penalty = sqrt( 2.0*log(Weight) )
  //   To drop below zero at 2 sigma,   set Penalty = exp(-4/2)    = 0.135
  //   To drop below zero at 2.5 sigma, set Penalty = exp(-6.25/2) = 0.044
  //   To drop below zero at 3 sigma,   set Penalty = exp(-9/2)    = 0.011 ]
 
  Double_t sigmaRes = 2.0;         // time resolution
  Double_t sigmaLow = 2.0;         // time resolution inside cone
  Double_t sigmaHigh = 2.0;        // time resolution outside cone

                                                          // muons electrons
  Double_t myConeAngle = WCSimParameters::CherenkovAngle();     // cherenkov cone      // 42.0    42.0
  Double_t myConeAngleSigma = 2.0; //   [degrees]         //  2.0     2.0
                                                          
  Double_t myConeEdge = WCSimParameters::CherenkovAngle();      // overall window      // 42.0    48.0
  Double_t myConeEdgeSigma = 2.0;  //   [degrees]         //  2.0     8.0

  Double_t fom = 0.0;

  for( Int_t idigit=0; idigit<WCSimVertexGeometry::Instance()->GetNDigits(); idigit++ ){

    if( WCSimVertexGeometry::Instance()->IsFiltered(idigit) ){
      delta = WCSimVertexGeometry::Instance()->GetDelta(idigit) - vtxTime;
      sigma = WCSimVertexGeometry::Instance()->GetDeltaSigma(idigit);
      weight = 1.0/(sigma*sigma);

      deltaAngle = WCSimVertexGeometry::Instance()->GetAngle(idigit) - myConeAngle;
      deltaEdge  = WCSimVertexGeometry::Instance()->GetAngle(idigit) - myConeEdge;

      // time weights inside and outside cone
      inweight  = exp(-(delta*delta)/(2.0*sigmaRes*sigmaRes))-penalty;

      if( delta<=0 ){ 
        outweight = (2.0*sigmaRes/(sigmaLow+sigmaHigh))*(exp(-(delta*delta)/(2.0*sigmaLow*sigmaLow))-penalty);
      }
      else{
        outweight = (2.0*sigmaRes/(sigmaLow+sigmaHigh))*(exp(-(delta*delta)/(2.0*sigmaHigh*sigmaHigh))-penalty);
      }
      
      if( deltaAngle<=0 ){
        alpha = 1.0;
      }
      else{
        alpha = 1.0/(1.0+(deltaAngle*deltaAngle)/(myConeAngleSigma*myConeAngleSigma));
      }

      // deweight hits outside cone
      if( deltaEdge<=0.0 ){ 
        deweight = 1.0;
      } 
      else{
        deweight = 1.0/(1.0+(deltaEdge*deltaEdge)/(myConeEdgeSigma*myConeEdgeSigma));
      }

      // overall time weight
      timeweight = inweight*alpha + outweight*(1.0-alpha);

      // add to running total
      Swx += deweight*weight*timeweight;
      Sw  += deweight*weight;
    }
  }

  if( Sw>0.0 ){
    fom = fBaseFOM*Swx/Sw;
  }

  // return figure of merit
  // ======================
  vtxFOM = fom;

  return;
}

void WCSimVertexFinder::ConePropertiesFoM(Double_t& coneFOM)
{  
  // calculate figure of merit
  // =========================
  Double_t coneEdge = WCSimParameters::CherenkovAngle();     // nominal cone angle
  Double_t coneEdgeLow = 21.0;  // cone edge (low side)      
  Double_t coneEdgeHigh = 3.0;  // cone edge (high side)   [muons: 3.0, electrons: 7.0]

  Double_t deltaAngle = 0.0;
  Double_t digitCharge = 0.0;
 
  Double_t coneCharge = 0.0;
  Double_t allCharge = 0.0;

  Double_t fom = 0.0;

  for( Int_t idigit=0; idigit<WCSimVertexGeometry::Instance()->GetNDigits(); idigit++ ){

    if( WCSimVertexGeometry::Instance()->IsFiltered(idigit) ){
      deltaAngle = WCSimVertexGeometry::Instance()->GetAngle(idigit) - coneEdge;
      digitCharge = WCSimVertexGeometry::Instance()->GetDigitQ(idigit);

      if( deltaAngle<=0.0 ){ 
        coneCharge += digitCharge*( 0.75 + 0.25/( 1.0 + (deltaAngle*deltaAngle)/(coneEdgeLow*coneEdgeLow) ) );
      }
      else{ 
        coneCharge += digitCharge*( 0.00 + 1.00/( 1.0 + (deltaAngle*deltaAngle)/(coneEdgeHigh*coneEdgeHigh) ) );
      }

      allCharge += digitCharge;
    }
  }

  if( allCharge>0.0 ){
    fom = fBaseFOM*coneCharge/allCharge;
  }
  
  std::cout << "[ConePropertiesFOM] " << "fom = " << fom << std::endl; 

  // return figure of merit
  // ======================
  coneFOM = fom;

  return;
}

void WCSimVertexFinder::PenaltyChi2(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t& chi2)
{  
  // default penalty
  // ===============
  Double_t deltaChi2 = 0;

  // check vertex position
  // =====================
  Bool_t inDetector = WCSimGeometry::Instance()->InsideDetector(vtxX,vtxY,vtxZ);
  if( inDetector==0 ){
    
    Double_t deltaR = WCSimGeometry::Instance()->DistanceToEdge(vtxX,vtxY,vtxZ);  // [cm]
    Double_t deltaRbase = 500.0; // [cm]
 
    deltaChi2 += -fBaseFOM*(deltaR/deltaRbase)*(deltaR/deltaRbase);
  }

  // return penalty
  // ==============
  chi2 = deltaChi2;

  return;
}

void WCSimVertexFinder::FixPositionChi2(Double_t vx, Double_t vy, Double_t vz, Double_t& chi2)
{
  // default penalty
  // ===============
  Double_t deltaChi2 = 0;

  // get true event
  // ==============
  WCSimTrueEvent* myTrueEvent = (WCSimTrueEvent*)(WCSimInterface::TrueEvent());

  if( myTrueEvent->GetNTracks()>0 ){
    Double_t trueVtxX = myTrueEvent->GetVtxX();
    Double_t trueVtxY = myTrueEvent->GetVtxY();
    Double_t trueVtxZ = myTrueEvent->GetVtxZ();
  
    Double_t deltaRsq = (vx-trueVtxX)*(vx-trueVtxX)
                       +(vy-trueVtxY)*(vy-trueVtxY)
                       +(vz-trueVtxZ)*(vz-trueVtxZ);
    Double_t deltaRsqBase = 0.25*0.25; // [cm]

    deltaChi2 += -10.0*fBaseFOM*(1.0-1.0/(1.0+(deltaRsq/deltaRsqBase)));
  }

  // return penalty
  // ==============
  chi2 = deltaChi2;

  return;
}

void WCSimVertexFinder::FixDirectionChi2(Double_t px, Double_t py, Double_t pz, Double_t& chi2)
{
  // default penalty
  // ===============
  Double_t deltaChi2 = 0;

  // get true event
  // ==============
  WCSimTrueEvent* myTrueEvent = (WCSimTrueEvent*)(WCSimInterface::TrueEvent());

  if( myTrueEvent->GetNTracks()>0 ){
    Double_t trueDirX = myTrueEvent->GetDirX();
    Double_t trueDirY = myTrueEvent->GetDirY();
    Double_t trueDirZ = myTrueEvent->GetDirZ();
  
    Double_t deltaTheta = (180.0/TMath::Pi())*(TMath::ACos(px*trueDirX+py*trueDirY+pz*trueDirZ));
    Double_t deltaThetaBase = 0.5; // [degrees]

    deltaChi2 += -10.0*fBaseFOM*(1.0-1.0/(1.0+(deltaTheta/deltaThetaBase)*(deltaTheta/deltaThetaBase)));
  }

  // return penalty
  // ==============
  chi2 = deltaChi2;

  return;
}



