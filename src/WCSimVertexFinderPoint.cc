#include "WCSimVertexFinderPoint.hh"

#include "WCSimGeometry.hh"
#include "WCSimParameters.hh"
#include "WCSimMathUtil.hh"

#include "WCSimRecoDigit.hh"
#include "WCSimRecoEvent.hh"
#include "WCSimRecoCluster.hh"

#include "TMath.h"
#include "TH1.h"
#include "TH3.h"

#include <cmath>
#include <iostream>
#include <cassert>

ClassImp(WCSimVertexFinderPoint)

static WCSimVertexFinderPoint* fgVertexFinder = 0;

//=================================================================================
//functions for TMinuit
static void point_vertex_chi2(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{
  Bool_t printDebugMessages = 0;

  Double_t vtxX = par[0]; // centimetres
  Double_t vtxY = par[1]; // centimetres
  Double_t vtxZ = par[2]; // centimetres

  Double_t vtime  = 0.0;
  Double_t fom = 0.0;

  fgVertexFinder->point_vertex_itr();
  fgVertexFinder->PointVertexChi2(vtxX,vtxY,vtxZ,
                                  vtime,fom);

  f = -fom; // note: maximizing fom
  //f = fom*fom;
  //std::cout << " [" << fgVertexFinder->point_vertex_iterations() << "] (x,y,z)=(" << vtxX << "," << vtxY << "," << vtxZ << ") vtime=" << vtime << " fom=" << fom << std::endl;

  if( printDebugMessages ){
    std::cout << "Bug: [" << fgVertexFinder->point_vertex_iterations() << "] (x,y,z)=(" << vtxX << "," << vtxY << "," << vtxZ << ") vtime=" << vtime << " fom=" << fom << std::endl;
  }

  return;
}

static void vertex_gaus_chi2(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{
  Bool_t printDebugMessages = 0;

  Double_t vtxX = par[0]; // centimetres
  Double_t vtxY = par[1]; // centimetres
  Double_t vtxZ = par[2]; // centimetres
  //Double_t vtxT = par[3];
  Double_t vtxT = 0.0; //for fixed vT fit

  //Double_t vtime  = 0.0;
  Double_t fom = 0.0;

  fgVertexFinder->vertex_gaus_itr();
  fgVertexFinder->AndyFOM(vtxX,vtxY,vtxZ,vtxT,fom);

  f = -fom; // note: maximizing fom
  //std::cout << " [" << fgVertexFinder->point_vertex_iterations() << "] (x,y,z)=(" << vtxX << "," << vtxY << "," << vtxZ << ") vtime=" << vtime << " fom=" << fom << std::endl;

  if( printDebugMessages ){
    std::cout << "Bug: [" << fgVertexFinder->vertex_gaus_iterations() << "] (x,y,z)=(" << vtxX << "," << vtxY << "," << vtxZ << ") vtime=" << vtxT << " fom=" << fom << std::endl;
  }

  return;
}

static void vertex_time_chi2(Int_t&, Double_t*, Double_t& f, Double_t* par, Int_t)
{
  Double_t vtxTime = par[0]; // nanoseconds
  Double_t fom = 0.0;

  fgVertexFinder->TimePropertiesChi2(vtxTime,fom);

  f = -fom; // note: maximizing fom
  return;
}

//============================================================
//basic functions
WCSimVertexFinderPoint* WCSimVertexFinderPoint::Instance()
{
  if( !fgVertexFinder ){
    fgVertexFinder = new WCSimVertexFinderPoint();
  }

  if( !fgVertexFinder ){
    assert(fgVertexFinder);
  }

  if( fgVertexFinder ){

  }

  return fgVertexFinder;
}

void WCSimVertexFinderPoint::PrintParameters()
{
  WCSimVertexFinderPoint::Instance()->RunPrintParameters();
}

WCSimVertexFinderPoint::WCSimVertexFinderPoint()
{
  std::cout << " *** WCSimVertexFinder::WCSimVertexFinder() *** " << std::endl;

  // default configuration
  fBaseFOM = 100.0;
  fConeEdgeDegrees = 2.0;

  fVtxX = 0.0;
  fVtxY = 0.0;
  fVtxZ = 0.0;

  fPass = 0;

  fNdigits = 0;
  fMeanQ = 0.0;
  fMeanRes = 2.0;
  
  fDigitX = 0;
  fDigitY = 0;
  fDigitZ = 0;
  fDigitT = 0;
  fDigitQ = 0;
  
  fDistAngle = 0;
  fDistPoint = 0;
  fDistTrack = 0;
  fDistPhoton = 0;

  fDeltaT = 0;
  fDeltaR = 0;
  fDeltaTrack = 0;
  fDeltaPhoton = 0;

  fDelta = 0;
  fDeltaAngle = 0;
  fDeltaWeight = 0;
  fDeltaDeweight = 0;

  fAngle = 0;
  fAngleWeight = 0;
  fAngleDeweight = 0;
  
  fSimpleVertex = 0;
  fSimpleDirection = 0;
  fPointVertex = 0;
  fPointDirection = 0;
  fExtendedVertex = 0;

  fMinuitPointVertex = new TMinuit();
  fMinuitPointVertex->SetPrintLevel(-1);
  fMinuitPointVertex->SetMaxIterations(5000);

  fMinuitPointDirection = new TMinuit();
  fMinuitPointDirection->SetPrintLevel(-1);
  fMinuitPointDirection->SetMaxIterations(5000);

  fMinuitExtendedVertex = new TMinuit();
  fMinuitExtendedVertex->SetPrintLevel(-1);
  fMinuitExtendedVertex->SetMaxIterations(5000); 

  fMinuitExtendedVertexNested = new TMinuit();
  fMinuitExtendedVertexNested->SetPrintLevel(-1);
  fMinuitExtendedVertexNested->SetMaxIterations(5000);

  fMinuitTimeFit = new TMinuit();
  fMinuitTimeFit->SetPrintLevel(-1);
  fMinuitTimeFit->SetMaxIterations(5000);

  fItr = 0;
}

WCSimVertexFinderPoint::~WCSimVertexFinderPoint()
{
  if( fDigitX ) delete [] fDigitX;
  if( fDigitY ) delete [] fDigitY;
  if( fDigitZ ) delete [] fDigitZ;
  if( fDigitT ) delete [] fDigitT;
  if( fDigitQ ) delete [] fDigitQ;

  if( fDistAngle ) delete [] fDistAngle;
  if( fDistPoint ) delete [] fDistPoint;
  if( fDistTrack ) delete [] fDistTrack;
  if( fDistPhoton ) delete [] fDistPhoton;

  if( fDeltaT ) delete [] fDeltaT;
  if( fDeltaR ) delete [] fDeltaR;
  if( fDeltaTrack ) delete [] fDeltaTrack;
  if( fDeltaPhoton ) delete [] fDeltaPhoton;
   
  if( fDelta  ) delete [] fDelta;
  if( fDeltaAngle  ) delete [] fDeltaAngle;
  if( fDeltaWeight ) delete [] fDeltaWeight;
  if( fDeltaDeweight ) delete [] fDeltaDeweight;

  if( fAngle ) delete [] fAngle;
  if( fAngleWeight ) delete fAngleWeight;
  if( fAngleDeweight ) delete fAngleDeweight;

  delete fMinuitPointVertex;
  delete fMinuitPointDirection;
  delete fMinuitExtendedVertex;
  delete fMinuitExtendedVertexNested;
  delete fMinuitTimeFit;

  vVertexList.clear();
}

void WCSimVertexFinderPoint::RunPrintParameters()
{
  std::cout << " *** WCSimVertexFinder::PrintParameters() *** " << std::endl;

  std::cout << "  Vertex Finder Parameters: " << std::endl
            << "   ConeEdgeDegrees = " << fConeEdgeDegrees << std::endl
            << "   BaseFOM = " << fBaseFOM << std::endl;

  return;
}

void WCSimVertexFinderPoint::Reset()
{
  this->Clear();

  return;
}

void WCSimVertexFinderPoint::Clear()
{
  // clear vertices
  // ==============
  for(UInt_t i=0; i<vVertexList.size(); i++ ){
    delete (WCSimRecoVertex*)(vVertexList.at(i));
  }

  fSimpleVertex = 0;
  fSimpleDirection = 0;
  fPointVertex = 0;
  fPointDirection = 0;
  fExtendedVertex = 0;

  vVertexList.clear();

  return;
}

WCSimRecoVertex* WCSimVertexFinderPoint::RunPointFit1(WCSimRecoEvent* myEvent, Double_t vtxX, Double_t vtxY, Double_t vtxZ)
{
  // get filter digit list
  // =====================
  WCSimRecoVertex* simpleVtx = (WCSimRecoVertex*)(this->FindSimpleVertex(vtxX, vtxY, vtxZ));
  simpleVtx = (WCSimRecoVertex*)(this->FindSimpleDirection(simpleVtx));
  WCSimRecoVertex* pointVtx  = (WCSimRecoVertex*)(this->FitPointVertex(myEvent,simpleVtx));
  
  // return vertex
  // =============
  return pointVtx;
}

/*WCSimRecoVertex* WCSimVertexFinderPoint::RunPointFit1(WCSimRecoEvent* myEvent, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t mysign)
{
  // get filter digit list
  // =====================
  fsign = mysign;
  WCSimRecoVertex* simpleVtx = (WCSimRecoVertex*)(this->FindSimpleVertex(vtxX, vtxY, vtxZ));
  WCSimRecoVertex* pointVtx  = (WCSimRecoVertex*)(this->FitPointVertex(myEvent,simpleVtx));
  
  // return vertex
  // =============
  return pointVtx;
}*/

/*WCSimRecoVertex* WCSimVertexFinderPoint::RunPointFit1(WCSimRecoEvent* myEvent, Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t dirx, Double_t diry, Double_t dirz)
{
  // get filter digit list
  // =====================
  fDirX = dirx;
  fDirY = diry;
  fDirZ = dirz;
  ffakex = vtxX - 100.0*dirx;
  ffakey = vtxY - 100.0*diry;
  ffakez = vtxZ - 100.0*dirz;
  WCSimRecoVertex* simpleVtx = (WCSimRecoVertex*)(this->FindSimpleVertex(vtxX, vtxY, vtxZ));
  WCSimRecoVertex* pointVtx  = (WCSimRecoVertex*)(this->FitPointVertex(myEvent,simpleVtx));
  
  // return vertex
  // =============
  return pointVtx;
}*/

WCSimRecoVertex* WCSimVertexFinderPoint::FindSimpleVertex(Double_t vX, Double_t vY, Double_t vZ)
{
  // simple vertex
  // =============
  // just calculate average position of digits

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fSimpleVertex = newVertex;

  Double_t vtxX = vX;
  Double_t vtxY = vY;
  Double_t vtxZ = vZ;
  Double_t vtxTime = 0.0;
  fItr = 1;
  fPass = 1;
  std::cout << "  simple vertex = (" << vtxX << "," << vtxY << "," << vtxZ << ") vtime=" << vtxTime << std::endl;

  // set vertex
  // ==========
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetFOM(fBaseFOM,fItr,fPass);  
  

  // set status
  // ==========
  Int_t status = WCSimRecoVertex::kOK;
  if( !fPass ) status |= WCSimRecoVertex::kFailSimpleVertex;
  newVertex->SetStatus(status);

  // return vertex
  // =============
  return newVertex;
}

WCSimRecoVertex* WCSimVertexFinderPoint::FindSimpleDirection(WCSimRecoVertex* myVertex)
{
  // load vertex
  // ===========
  Double_t vtxX = myVertex->GetX();
  Double_t vtxY = myVertex->GetY();
  Double_t vtxZ = myVertex->GetZ();
  Double_t vtxTime = myVertex->GetTime();
    
  // current status
  // ==============
  Int_t status = myVertex->GetStatus();

  // create new vertex
  // =================
  WCSimRecoVertex* newVertex = new WCSimRecoVertex();
  vVertexList.push_back(newVertex);
  fSimpleDirection = newVertex;

  // loop over digits
  // ================
  Double_t Swx = 0.0;
  Double_t Swy = 0.0;
  Double_t Swz = 0.0;
  Double_t Sw = 0.0;

  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    Double_t q = fDigitQ[idigit];

    Double_t dx = fDigitX[idigit] - vtxX;
    Double_t dy = fDigitY[idigit] - vtxY;
    Double_t dz = fDigitZ[idigit] - vtxZ;
    Double_t ds = sqrt(dx*dx+dy*dy+dz*dz);

    Double_t px = dx/ds;
    Double_t py = dy/ds;
    Double_t pz = dz/ds;

    Swx += q*px;
    Swy += q*py;
    Swz += q*pz;
    Sw += q;
  }

  // average direction
  // =================
  Double_t dirX = 0.0;
  Double_t dirY = 0.0;
  Double_t dirZ = 0.0;
  Double_t angle = 0.0;
  Double_t fom = 0.0;

  fItr = 0;
  fPass = 0; // pass/fail

  if( Sw>0.0 ){
    Double_t qx = Swx/Sw;
    Double_t qy = Swy/Sw;
    Double_t qz = Swz/Sw;
    Double_t qs = sqrt(qx*qx+qy*qy+qz*qz);

    dirX = qx/qs;
    dirY = qy/qs;
    dirZ = qz/qs;
    angle = 42.0;
    //fom = fBaseFOM;

    fItr = 1;
    fPass = 1; 
  }

  std::cout << "  simple direction = (" << dirX << "," << dirY << "," << dirZ << ") angle=" << angle << " fom=" << fom << std::endl;

  if( !fPass ) std::cout << "   <warning> simple direction calculation failed! " << std::endl;

  // set vertex and direction
  // ========================
  if( fPass ){
    newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
    //newVertex->SetDirection(dirX,dirY,dirZ,angle); // does not take 4 inputs now
    newVertex->SetDirection(dirX,dirY,dirZ);
    newVertex->SetFOM(fom,fItr,fPass);
  }

  // set status
  // ==========
  if( !fPass ) status |= WCSimRecoVertex::kFailSimpleDirection;
  newVertex->SetStatus(status);

  // return vertex
  // =============
  return newVertex;
}

/*WCSimRecoVertex* WCSimVertexFinderPoint::FitPointVertex(std::vector<WCSimRecoDigit*>* myDigitList, WCSimRecoVertex* myVertex)
{  
  // set up arrays
  // =============
  this->FillArrays(myDigitList);
  
  // reconstruct vertex
  // ==================
  return (WCSimRecoVertex*)(this->FitPointVertex(myVertex));
}*/

WCSimRecoVertex* WCSimVertexFinderPoint::FitPointVertex(WCSimRecoEvent* myEvent, WCSimRecoVertex* myVertex)
{  
  // set up arrays
  // =============
  this->FillArrays(myEvent);
  
  // reconstruct vertex
  // ==================
  return (WCSimRecoVertex*)(this->FitPointVertex(myVertex));
}

WCSimRecoVertex* WCSimVertexFinderPoint::FitPointVertex(WCSimRecoVertex* myVertex)
{
  //return (WCSimRecoVertex*)(this->FitPointVertexWithMinuit(myVertex)); //for old fom
  return (WCSimRecoVertex*)(this->FitPointVertexWithMinuitMatt(myVertex)); //for new fom
}

/*WCSimRecoVertex* WCSimVertexFinderPoint::FitPointVertexWithMinuit(WCSimRecoVertex* myVertex)
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
  Double_t angle = 0.0;

  Double_t vtxFOM = 0.0;

  // seed vertex
  // ===========
  Bool_t foundSeed = myVertex->FoundVertex();//check the vertex seed is existed?
  Double_t seedX = myVertex->GetX();
  Double_t seedY = myVertex->GetY();
  Double_t seedZ = myVertex->GetZ();

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
  // three-parameter fit to vertex coordinates

  Int_t err = 0;
  Int_t flag = 0;

  Double_t fitXpos = 0.0;
  Double_t fitYpos = 0.0;
  Double_t fitZpos = 0.0;

  Double_t fitXposErr = 0.0;
  Double_t fitYposErr = 0.0;
  Double_t fitZposErr = 0.0;
  //std::cout << "check the array is good: " << fDigitX[3] << std::endl; //array is good so far.

  Double_t* arglist = new Double_t[10];
  arglist[0]=1;  // 1: standard minimization
                 // 2: try to improve minimum

  // re-initialize everything...
  fMinuitPointVertex->mncler(); //call the minuit
  fMinuitPointVertex->SetFCN(point_vertex_chi2); //set the minimization function, what's this function, which is the function according to which data is fitted
  fMinuitPointVertex->mnexcm("SET STR",arglist,1,err); //don't understand...
  fMinuitPointVertex->mnparm(0,"x",seedX,20.0,-500.0,+500.0,err); //set the initial parameter of minimization
  fMinuitPointVertex->mnparm(1,"y",seedY,20.0,-500.0,+500.0,err);
  fMinuitPointVertex->mnparm(2,"z",seedZ,20.0,-500.0,+500.0,err);//whatever the problem will be at the end, the parameters here should be changed.  

  flag = fMinuitPointVertex->Migrad();
  fMinuitPointVertex->GetParameter(0,fitXpos,fitXposErr);
  fMinuitPointVertex->GetParameter(1,fitYpos,fitYposErr);
  fMinuitPointVertex->GetParameter(2,fitZpos,fitZposErr);

  delete [] arglist;

  // sort results
  // ============
  vtxX = fitXpos; 
  vtxY = fitYpos;
  vtxZ = fitZpos;
  vtxTime = 950.0;
  //std::cout << "fitted vtxX " << vtxX << "; seed vtxX: " << seedX << std::endl;

  vtxFOM = 0.0;
  
  fPass = 0;               // flag = 0: normal termination
  if( flag==0 ) fPass = 1; // anything else: abnormal termination 

  fItr = point_vertex_iterations();

  // calculate vertex?/fom?
  // ======================
  this->PointVertexChi2(vtxX,vtxY,vtxZ,
                        vtxTime,vtxFOM);

  std::cout << "  fitted point vertex = (" << vtxX << "," << vtxY << "," << vtxZ << ") vtime=" << vtxTime << " fom=" << vtxFOM << " number of iteration=" << fItr << std::endl;

  if( !fPass ) std::cout << "   <warning> point vertex fit failed to converge! Error code: " << flag << std::endl;

  // set vertex and direction
  // ========================
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  newVertex->SetDirection(dirX,dirY,dirZ,angle);
  newVertex->SetFOM(vtxFOM,fItr,fPass); //fItr is the number of steps? why is it important??

  // set status
  // ==========
  if( !fPass ) status |= WCSimRecoVertex::kFailPointVertex;
  newVertex->SetStatus(status);

  // return vertex
  // =============  
  return newVertex;
}*/

WCSimRecoVertex* WCSimVertexFinderPoint::FitPointVertexWithMinuitMatt(WCSimRecoVertex* myVertex)
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
  //Double_t angle = 0.0; // unused

  Double_t vtxFOM = 0.0;

  // seed vertex
  // ===========
  Bool_t foundSeed = myVertex->FoundVertex();//check the vertex seed is existed?
  Double_t seedX = myVertex->GetX();
  Double_t seedY = myVertex->GetY();
  Double_t seedZ = myVertex->GetZ();
  //Double_t seedT = myVertex->GetTime(); // unused

  fDirX = myVertex->GetDirX();
  fDirY = myVertex->GetDirY();
  fDirZ = myVertex->GetDirZ();
  ffakex = seedX - 100.0*fDirX;
  ffakey = seedY - 100.0*fDirY;
  ffakez = seedZ - 100.0*fDirZ;

  // current status
  // ==============
  Int_t status = myVertex->GetStatus();

  // reset counter
  // =============
  vertex_gaus_reset_itr(); 

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
  // three-parameter fit to vertex coordinates

  Int_t err = 0;
  Int_t flag = 0;

  Double_t fitXpos = 0.0;
  Double_t fitYpos = 0.0;
  Double_t fitZpos = 0.0;
  Double_t fitTime = 0.0;

  Double_t fitXposErr = 0.0;
  Double_t fitYposErr = 0.0;
  Double_t fitZposErr = 0.0;
  //Double_t fitTimeErr = 0.0; // unused
  //std::cout << "check the array is good: " << fDigitX[3] << std::endl; //array is good so far.

  Double_t* arglist = new Double_t[10];
  arglist[0]=1;  // 1: standard minimization
                 // 2: try to improve minimum

  // re-initialize everything...
  fMinuitPointVertex->mncler(); //call the minuit
  fMinuitPointVertex->SetFCN(vertex_gaus_chi2); //set the minimization function, what's this function, which is the function according to which data is fitted
  fMinuitPointVertex->mnexcm("SET STR",arglist,1,err); //don't understand...
  fMinuitPointVertex->mnparm(0,"x",seedX,2.0,(seedX-1000.0),(seedX+1000.0),err); //set the initial parameter of minimization
  fMinuitPointVertex->mnparm(1,"y",seedY,2.0,(seedY-1000.0),(seedY+1000.0),err);
  fMinuitPointVertex->mnparm(2,"z",seedZ,2.0,(seedZ-1000.0),(seedZ+1000.0),err);
  //fMinuitPointVertex->mnparm(3,"t",seedT,10,0.0,(seedT+200.0),err);

  flag = fMinuitPointVertex->Migrad();
  fMinuitPointVertex->GetParameter(0,fitXpos,fitXposErr);
  fMinuitPointVertex->GetParameter(1,fitYpos,fitYposErr);
  fMinuitPointVertex->GetParameter(2,fitZpos,fitZposErr);
  //fMinuitPointVertex->GetParameter(3,fitTime,fitTimeErr);

  delete [] arglist;

  // sort results
  // ============
  vtxX = fitXpos; 
  vtxY = fitYpos;
  vtxZ = fitZpos;
  vtxTime = fitTime;
  //std::cout << "fitted vtxX " << vtxX << "; seed vtxX: " << seedX << std::endl;

  vtxFOM = 0.0;
  
  fPass = 0;               // flag = 0: normal termination
  if( flag==0 ) fPass = 1; // anything else: abnormal termination 

  fItr = vertex_gaus_iterations();

  // calculate vertex?/fom?
  // ======================
  this->AndyFOM(vtxX,vtxY,vtxZ,vtxTime,vtxFOM);

  std::cout << "  fitted point vertex = (" << vtxX << "," << vtxY << "," << vtxZ << ") vtime=" << vtxTime << " fom=" << vtxFOM << " number of iteration=" << fItr << std::endl;

  if( !fPass ) std::cout << "   <warning> point vertex fit failed to converge! Error code: " << flag << std::endl;

  // set vertex and direction
  // ========================
  newVertex->SetVertex(vtxX,vtxY,vtxZ,vtxTime);
  //newVertex->SetDirection(dirX,dirY,dirZ,angle); // no longer passes in angle
  newVertex->SetDirection(dirX,dirY,dirZ); 

  newVertex->SetFOM(vtxFOM,fItr,fPass); //fItr is the number of steps? why is it important??

  // set status
  // ==========
  if( !fPass ) status |= WCSimRecoVertex::kFailPointVertex;
  newVertex->SetStatus(status);

  // return vertex
  // =============  
  return newVertex;
}
//===================================================================
//calculate the function with andy's fom function. haven't checked the performance
Double_t WCSimVertexFinderPoint::FOMCalc(WCSimRecoEvent* myEvent, Double_t vX, Double_t vY, Double_t vZ, Double_t vT, TH1D* myTimeRes)
{
  /*std::vector<WCSimRecoDigit*>* myDigitList = (std::vector<WCSimRecoDigit*>*)(myEvent->GetFilterDigitList());
  this->FillArrays(myDigitList);*/
  this->FillArrays(myEvent);
  return (Double_t)(this->AndyFOM(vX, vY, vZ, vT, myTimeRes));
  //std::cout << "digit2" << fDigitX[1] << " " << fDigitY[1] << " " << fDigitZ[1] << " " << fDigitT[1] << std::endl;
}

Double_t WCSimVertexFinderPoint::AndyFOM(Double_t vX, Double_t vY, Double_t vZ, Double_t vT, TH1D* myTimeRes)
{
  if( fDelta  ) delete [] fDelta;
  fDelta = new Double_t[fNdigits];
  myTimeRes->Reset();
  Double_t mean0 = 0.0;

  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    Double_t dx = fDigitX[idigit]-vX;
    Double_t dy = fDigitY[idigit]-vY;
    Double_t dz = fDigitZ[idigit]-vZ;
    Double_t ds = sqrt(dx*dx+dy*dy+dz*dz);
    Double_t phoT = 1.33*ds/(WCSimParameters::SpeedOfLight());
    fDelta[idigit] = fDigitT[idigit] - phoT - vT;
    myTimeRes->TH1::Fill(fDelta[idigit]);
    mean0 += fDelta[idigit];
  }
  mean0 = mean0/fNdigits;
  Double_t newfom = 0.;
  Double_t sigma0 = 2.0*8.75;
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    newfom += 0.25*exp(-((fDelta[idigit]-mean0)*(fDelta[idigit]-mean0))/(2*sigma0*sigma0));
  }
  Double_t penal = 0.0;
  //this->PenaltyChi2Matt(vX,vY,vZ,penal);
  this->PenaltyChi2Matt2(vX,vY,vZ,penal); //don't use penaltyFOM when checking timeresidual distribution
 
  Double_t chi2 = newfom + penal;

  return (chi2);
}

//Double_t WCSimVertexFinderPoint::FOMCalc(WCSimRecoEvent* myEvent, Double_t vX, Double_t vY, Double_t vZ, Double_t vT)
//{
  /*std::vector<WCSimRecoDigit*>* myDigitList = (std::vector<WCSimRecoDigit*>*)(myEvent->GetFilterDigitList());
  this->FillArrays(myDigitList);*/
  //this->FillArrays(myEvent);
  //return (Double_t)(this->AndyFOM(vX, vY, vZ, vT));
  //std::cout << "digit2" << fDigitX[1] << " " << fDigitY[1] << " " << fDigitZ[1] << " " << fDigitT[1] << std::endl;
//}

//===========================================================================================
//for TMinuit
void WCSimVertexFinderPoint::AndyFOM(Double_t vX, Double_t vY, Double_t vZ, Double_t vT, Double_t& chi2)
{
  if( fDelta  ) delete [] fDelta;
  fDelta = new Double_t[fNdigits];
  Double_t mean0 = 0.0;
  Double_t newfom = 0.0;
 
  //TH1D* myTimeRes = new TH1D;
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    Double_t dx = fDigitX[idigit]-vX;
    Double_t dy = fDigitY[idigit]-vY;
    Double_t dz = fDigitZ[idigit]-vZ;
    Double_t ds = sqrt(dx*dx+dy*dy+dz*dz);
    Double_t phoT = 1.33*ds/(WCSimParameters::SpeedOfLight());
    fDelta[idigit] = fDigitT[idigit] - phoT - vT;
    mean0 += fDelta[idigit];
  }
  //std::cout << "sumdelta" << mean0 << std::endl;
  //std::cout << "meandelta" << mean0 << std::endl;
  
  mean0 = mean0/fNdigits;
  Double_t sigma0 = 2.0*8.75;
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    //if( fDelta[idigit] >= 0 )
      newfom += 0.25*exp(-((fDelta[idigit]-mean0)*(fDelta[idigit]-mean0))/(2*sigma0*sigma0));
    //else newfom += -999999.9;
  }
  
  Double_t penal = 0.0;
  //this->PenaltyChi2Matt(vX,vY,vZ,penal);
  this->PenaltyChi2Matt2(vX,vY,vZ,penal);
 
  chi2 = newfom + penal;

  std::cout << "vertex: (" << vX << " " << vY << " " << vZ << " " << vT << ")= " << chi2 << " " << newfom << " " << penal << " " << fsign << std::endl;

  return;
}

void WCSimVertexFinderPoint::AndyFOM(WCSimRecoEvent* myEvent, Double_t vX, Double_t vY, Double_t vZ, Double_t vT, Double_t& chi2)
{
  this->FillArrays(myEvent);
  
  if( fDelta  ) delete [] fDelta;
  fDelta = new Double_t[fNdigits];
  Double_t mean0 = 0.0;
  Double_t newfom = 0.0;
 
  //TH1D* myTimeRes = new TH1D;
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    Double_t dx = fDigitX[idigit]-vX;
    Double_t dy = fDigitY[idigit]-vY;
    Double_t dz = fDigitZ[idigit]-vZ;
    Double_t ds = sqrt(dx*dx+dy*dy+dz*dz);
    Double_t phoT = 1.33*ds/(WCSimParameters::SpeedOfLight());
    fDelta[idigit] = fDigitT[idigit] - phoT - vT;
    mean0 += fDelta[idigit];
  }
  //std::cout << "sumdelta" << mean0 << std::endl;
  //std::cout << "meandelta" << mean0 << std::endl;
  
  mean0 = mean0/fNdigits;
  Double_t sigma0 = 2.0*9.0;
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    //if( fDelta[idigit] >= 0 )
      newfom += 0.25*exp(-((fDelta[idigit]-mean0)*(fDelta[idigit]-mean0))/(2*sigma0*sigma0));
    //else newfom += -999999.9;
  }

  chi2 = newfom;

  std::cout << "vertex: (" << vX << " " << vY << " " << vZ << " " << vT << ")= " << chi2 << std::endl;

  return;
}

//=================================================================================
void WCSimVertexFinderPoint::PointVertexChi2(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t& vtxTime, Double_t& fom)
{  
  // check vertex position
  // =====================
  // moved to PenaltyChi2(...)

  // figure of merit
  // ===============
  Double_t vtxFOM = 0.0;
  Double_t penaltyFOM = 0.0;

  // calculate residuals
  // ===================
  this->PointResiduals(vtxX,vtxY,vtxZ);

  // calculate figure of merit
  // =========================
  this->PointVertexChi2(vtxTime,vtxFOM);

  // calculate penalty
  // =================
  //this->PenaltyChi2(vtxX,vtxY,vtxZ,penaltyFOM); //general case
  this->PenaltyChi2Matt(vtxX,vtxY,vtxZ,penaltyFOM); //just for Matt's samples
 
  penaltyFOM = 0.0; //only for modified Andy's fom function
  // calculate overall figure of merit
  // =================================
  fom = vtxFOM + penaltyFOM;

  // truncate
  if( fom<-99999.9 ) fom = -99999.9;

  return;
}

void WCSimVertexFinderPoint::PointVertexChi2(Double_t& vtxTime, Double_t& fom) //Fit the vertex time?
{
  // just return RMS of distribution
  // ===============================
  // this->FindSimpleTimeProperties(vtxTime,fom); fom = -fom;

  // improved figure of merit
  // ========================
  this->FitTimeProperties(vtxTime,fom);

  return;
}

void WCSimVertexFinderPoint::FillArrays(std::vector<WCSimRecoDigit*>* myDigitList)
{
  // clear arrays
  // ============
  if( fDigitX ) delete [] fDigitX;
  if( fDigitY ) delete [] fDigitY;
  if( fDigitZ ) delete [] fDigitZ;
  if( fDigitT ) delete [] fDigitT;
  if( fDigitQ ) delete [] fDigitQ;

  if( myDigitList->size()==0 ){
    std::cout << "   <warning> vertex finder found no digits! " << std::endl;
  }

  fNdigits = myDigitList->size();
  fDigitX = new Double_t[fNdigits];
  fDigitY = new Double_t[fNdigits];
  fDigitZ = new Double_t[fNdigits];
  fDigitT = new Double_t[fNdigits];
  fDigitQ = new Double_t[fNdigits];

  fMeanQ = 0.0;
  fMeanRes = 2.5;

  Double_t Swx = 0.0;
  Double_t Sw = 0.0;
  
  // store digit data
  // ================
  for( UInt_t idigit=0; idigit<myDigitList->size(); idigit++ ){
    WCSimRecoDigit* recoDigit = (WCSimRecoDigit*)(myDigitList->at(idigit));    
    fDigitX[idigit] = recoDigit->GetX();
    fDigitY[idigit] = recoDigit->GetY();
    fDigitZ[idigit] = recoDigit->GetZ();
    fDigitT[idigit] = recoDigit->GetTime();
    fDigitQ[idigit] = recoDigit->GetQPEs();

    Swx += recoDigit->GetQPEs();
    Sw += 1.0;
  }

  if( Sw>0.0 ){
    fMeanQ = Swx/Sw;
    fMeanRes = WCSimParameters::TimeResolution(fMeanQ);
  }

  return;
}  

void WCSimVertexFinderPoint::FillArrays(WCSimRecoEvent* myEvent)
{
  // clear arrays
  // ============
  if( fDigitX ) delete [] fDigitX;
  if( fDigitY ) delete [] fDigitY;
  if( fDigitZ ) delete [] fDigitZ;
  if( fDigitT ) delete [] fDigitT;
  if( fDigitQ ) delete [] fDigitQ;

  if( myEvent->GetNFilterDigits()==0 ){
    std::cout << "   <warning> vertex finder found no digits! " << std::endl;
  }

  fNdigits = myEvent->GetNFilterDigits();
  fDigitX = new Double_t[fNdigits];
  fDigitY = new Double_t[fNdigits];
  fDigitZ = new Double_t[fNdigits];
  fDigitT = new Double_t[fNdigits];
  fDigitQ = new Double_t[fNdigits];

  fMeanQ = 0.0;
  fMeanRes = 2.5;

  Double_t Swx = 0.0;
  Double_t Sw = 0.0;
  Int_t ifilter = 0;

  // store digit data
  // ================
  for( Int_t idigit=0; idigit<myEvent->GetNDigits(); idigit++ ){
    WCSimRecoDigit* recoDigit = (WCSimRecoDigit*)(myEvent->GetDigit(idigit));   

    if( recoDigit->IsFiltered() && ifilter<fNdigits ){
      fDigitX[ifilter] = recoDigit->GetX();
      fDigitY[ifilter] = recoDigit->GetY();
      fDigitZ[ifilter] = recoDigit->GetZ();
      fDigitT[ifilter] = recoDigit->GetTime();
      fDigitQ[ifilter] = recoDigit->GetQPEs();

      Swx += recoDigit->GetQPEs();
      Sw += 1.0;
      ifilter++;
    }
  }

  if( Sw>0.0 ){
    fMeanQ = Swx/Sw;
    fMeanRes = WCSimParameters::TimeResolution(fMeanQ);
  }

  return;
}  

void WCSimVertexFinderPoint::PointResiduals(Double_t vtxX, Double_t vtxY, Double_t vtxZ)
{
  // clear arrays
  // ============
  if( fDelta  ) delete [] fDelta;
  if( fDeltaAngle  ) delete [] fDeltaAngle;
  if( fDeltaWeight ) delete [] fDeltaWeight;
  if( fDeltaDeweight ) delete [] fDeltaDeweight;

  if( fDeltaT ) delete [] fDeltaT;
  if( fDeltaR ) delete [] fDeltaR;
  if( fDeltaTrack ) delete [] fDeltaTrack;
  if( fDeltaPhoton ) delete [] fDeltaPhoton;

  // make new arrays
  // ===============
  fDelta = new Double_t[fNdigits];
  fDeltaAngle = new Double_t[fNdigits];
  fDeltaWeight = new Double_t[fNdigits];
  fDeltaDeweight = new Double_t[fNdigits];

  fDeltaT = new Double_t[fNdigits];
  fDeltaR = new Double_t[fNdigits];
  fDeltaTrack = new Double_t[fNdigits];
  fDeltaPhoton = new Double_t[fNdigits];

  // calculate residuals (assuming point vertex)
  // ===========================================
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    Double_t dx = fDigitX[idigit]-vtxX;
    Double_t dy = fDigitY[idigit]-vtxY;
    Double_t dz = fDigitZ[idigit]-vtxZ;
    Double_t ds = sqrt(dx*dx+dy*dy+dz*dz);       

    Double_t Lphoton = ds;//the length of photon as well as the wavelength of the photon, why??

    Double_t fC = WCSimParameters::SpeedOfLight();
    Double_t fN = WCSimParameters::RefractiveIndex(Lphoton);//the index looks not right

    Double_t dt = fDigitT[idigit];
    Double_t delta = dt - Lphoton/(fC/fN);

    Double_t qpes = fDigitQ[idigit];
    Double_t res = WCSimParameters::TimeResolution(qpes);
    Double_t weight = 1.0/(res*res);

    fDeltaT[idigit] = dt;
    fDeltaR[idigit] = Lphoton/(fC/fN);
    fDeltaTrack[idigit] = 0.0;
    fDeltaPhoton[idigit] = Lphoton/(fC/fN);

    fDelta[idigit] = delta;
    fDeltaAngle[idigit] = -45.0;
    fDeltaWeight[idigit] = weight;   
    fDeltaDeweight[idigit] = 1.0;   
    //std::cout << "refractive index: " << fN << std::endl;
  }       
  
  return;
}

void WCSimVertexFinderPoint::FindSimpleTimeProperties(Double_t& vtxTime, Double_t& vtxTimeRms)
{
  // reset mean and rms
  // ================== 
  Double_t meanTime = 950.0;
  Double_t rmsTime = -99999.9;

  // calculate rms time
  // ==================
  Double_t Swx2 = 0.0;
  Double_t Swx = 0.0;
  Double_t Sw = 0.0;

  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    Double_t delta = fDelta[idigit];
    Double_t weight = fDeltaWeight[idigit];
    Double_t deweight = fDeltaDeweight[idigit];

    Swx2 += deweight*weight*delta*delta;
    Swx += deweight*weight*delta;
    Sw += deweight*weight;
  }

  if( Sw>0.0 ){
    meanTime = Swx/Sw;
    rmsTime = sqrt( (Swx2/Sw)-(Swx/Sw)*(Swx/Sw) );
  }

  // return mean and rms
  // ===================
  vtxTime = meanTime;
  vtxTimeRms = rmsTime;

  return;
}

void WCSimVertexFinderPoint::FitTimeProperties(Double_t& vtxTime, Double_t& vtxFOM)
{ 
  // calculate mean and rms
  // ====================== 
  Double_t meanTime = 950.0;
  Double_t rmsTime = -99999.9;

  this->FindSimpleTimeProperties(meanTime,rmsTime); 
  //std::cout << "vtxTime before fit " << meanTime << std::endl;

  // run Minuit
  // ==========  
  // three-parameter fit to vertex coordinates

  Int_t err = 0;
  Int_t flag = 0;

  Double_t seedTime = meanTime;
  seedTime = 50.453;
  Double_t fitTime = 0.0;
  Double_t fitTimeErr = 0.0;
  
  Double_t* arglist = new Double_t[10];
  arglist[0]=1;  // 1: standard minimization
                 // 2: try to improve minimum

  // re-initialize everything...
  fMinuitTimeFit->mncler();
  fMinuitTimeFit->SetFCN(vertex_time_chi2);
  fMinuitTimeFit->mnexcm("SET STR",arglist,1,err);
  fMinuitTimeFit->mnparm(0,"vtxTime",seedTime,50.0,0.0,2000.0,err);
  
  flag = fMinuitTimeFit->Migrad();
  fMinuitTimeFit->GetParameter(0,fitTime,fitTimeErr);
  // fitTime = meanTime; 
  // fitTimeErr = 0.0;
 
  delete [] arglist;


  // calculate figure of merit
  // =========================
  Double_t fom = -99999.9;
  //std::cout << "the fitted time got from FitTimeProperties: " << fitTime << std::endl;
  this->TimePropertiesChi2(fitTime,fom);  


  // return figure of merit
  // ======================
  vtxTime = fitTime;
  vtxFOM = fom;

  return;
}

void WCSimVertexFinderPoint::TimePropertiesChi2(Double_t vtxTime, Double_t& vtxFOM)
{ 
  // calculate figure of merit
  // =========================
  //Double_t Swx = 0.0; // unused
  //Double_t Sw = 0.0;  // unused
  //Double_t S = 0.0;   // unused

  Double_t delta = 0.0;
  Double_t sumdelta = 0.0;
  Double_t delta0 = 0.0;
  Double_t weight = 0.0;
  Double_t deweight = 0.0;
  //Double_t penalty = 0.05; // unused
  Double_t sigma = 0.;

  Double_t fom = 0.0;
//==========================================================================
//original fom
    /*Double_t meanres = 2.5;       // nominal timing resolution (ns)
    Double_t sigma = 1.5*meanres; // could also use fMeanRes = TimeResolution(fMeanQ) (ns)
    for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    delta = fDelta[idigit] - vtxTime;
    weight = fDeltaWeight[idigit];
    deweight = fDeltaDeweight[idigit];
 
    Swx += deweight*weight*(exp(-(delta*delta)/(2.0*sigma*sigma))-penalty);
    Sw  += deweight*weight;
    S   += weight;
  }

  if( Sw>0.0 ){
    fom += 0.9*fBaseFOM*Swx/Sw; // from timing, how is the baseFOM defined
  }

  if( S>0.0 ){
    fom += 0.1*fBaseFOM*Sw/S;   // from direction
  }*/

//==========================================================================
//modified Andy's fom
  sigma = 3.6;
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    sumdelta += fDelta[idigit] - vtxTime;
  }
  delta0 = sumdelta/fNdigits;


  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
    delta = fDelta[idigit] - vtxTime;
    weight = fDeltaWeight[idigit];
    deweight = fDeltaDeweight[idigit];
 
    fom += 0.25*(exp(-((delta-delta0)*(delta-delta0))/(2.0*sigma*sigma)));
  }
  // return figure of merit
  // ======================
  vtxFOM = fom;
}

void WCSimVertexFinderPoint::PenaltyChi2(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t& chi2)
{  
  // default penalty
  // ===============
  Double_t deltaChi2 = 0;
  Double_t deltaR = 0.;

  // check vertex position
  // =====================
  WCSimGeometry* fGeometryHandle = WCSimGeometry::Instance();
  Bool_t inDetector = fGeometryHandle->InsideDetector(vtxX,vtxY,vtxZ);//should it be inside the loop or outside the loop?
  if( inDetector==0 ){
    
    deltaR = fGeometryHandle->DistanceToEdge(vtxX,vtxY,vtxZ);  // [cm]
    Double_t deltaRbase = 500.0; // [cm]
 
    deltaChi2 += -fBaseFOM*(deltaR/deltaRbase)*(deltaR/deltaRbase);
  }
  //std::cout << "distancetoedge: " << deltaR << "; deltaChi2: " << deltaChi2 << std::endl;
  
  // return penalty
  // ==============
  chi2 = deltaChi2;

  return;
}

void WCSimVertexFinderPoint::PenaltyChi2Matt(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t& chi2)
{  
  // default penalty
  // ===============
  Double_t deltaChi2 = 0;
  Double_t deltaR = 0.;
//  Double_t coef = 0.0;
  Double_t coef = 0.000000030;

  // check vertex position
  // =====================
  WCSimGeometry* fGeometryHandle = WCSimGeometry::Instance();

  deltaR = fGeometryHandle->DistanceToEdge(vtxX,vtxY,vtxZ);  // [cm] (DistanceToEdgeMatt does not exist
  //Double_t deltaRbase = 500.0; // [cm] unused
 
  deltaChi2 += -fsign*fBaseFOM*coef*deltaR*deltaR;
  //std::cout << "distancetoedge: " << deltaR << "; deltaChi2: " << deltaChi2 << std::endl;
  
  // return penalty
  // ==============
  chi2 = deltaChi2;

  return;
}

void WCSimVertexFinderPoint::PenaltyChi2Matt2(Double_t vtxX, Double_t vtxY, Double_t vtxZ, Double_t& chi2)
{  
  // default penalty
  // ===============
  Double_t deltaChi2 = 0.;
  Double_t devx = 0.;
  Double_t devy = 0.;
  Double_t devz = 0.;
  if( fDirX>=0. && fDirX<=0.3 ) devx = fDirX*666.7;
  else devx = fDirX*171.4;
  if( fDirY>=0. && fDirY<=0.3 ) devy = fDirX*666.7;
  else devy = fDirY*171.4;
  if( fDirZ>=0. && fDirZ<=0.3 ) devz = fDirZ*333.4;
  else { if( fDirZ>0.3 && fDirZ<=0.4 ) devz = fDirZ*500.0;
         else devz = fDirZ*1000.0;}
  Double_t fBASE = 16.0;

  deltaChi2 += -fBASE*( ((vtxX-ffakex)*(vtxX-ffakex))/(devx*devx) + ((vtxY-ffakey)*(vtxY-ffakey))/(devy*devy) + ((vtxZ-ffakez)*(vtxZ-ffakez))/(devz*devz) );
  
  // return penalty
  // ==============
  chi2 = deltaChi2;

  return;
}

void WCSimVertexFinderPoint::GlbPeakGeo(Double_t *trV, Double_t *dir, Double_t *ftV, Double_t &fopenangle, Double_t &fD, Double_t &fd)
{
  Double_t Sub1[3];
  WCSimMathUtil::SubtractVec(ftV,trV,Sub1);
  Double_t prod1 = WCSimMathUtil::DotProduct(dir,Sub1);
  Double_t prod2 = WCSimMathUtil::DotProduct(Sub1,Sub1);
  fopenangle = acos(prod1/sqrt(prod2));
  fD = WCSimMathUtil::Magnitude(ftV,trV);
  fd = fD*sin(fopenangle);

  return;

}

Double_t WCSimVertexFinderPoint::TrackL(Double_t vx, Double_t vy, Double_t vz, Double_t dirx, Double_t diry, Double_t dirz)
{  
  Double_t ftrkL = 0.0;
  Double_t newX = vx;
  Double_t newY = vy;
  Double_t newZ = vz;
  while( ((sqrt(newX*newX+newY*newY))<2750.) && (newZ<3200.) && (newZ>-3200.) ){
    newX += dirx;
    newY += diry;
    newZ += dirz;
    ftrkL += 1.0;
  }
  return ftrkL;

}

Double_t WCSimVertexFinderPoint::Openagl(Double_t vx, Double_t vy, Double_t vz, Double_t dirx, Double_t diry, Double_t dirz, WCSimRecoEvent* myEvent)
{ 
  this->FillArrays(myEvent);
  Double_t fangle = 0.0;
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
  
  Double_t dx = fDigitX[idigit]-vx;
  Double_t dy = fDigitY[idigit]-vy;
  Double_t dz = fDigitZ[idigit]-vz;
  Double_t ds = sqrt(dx*dx+dy*dy+dz*dz);
  fangle += acos((dirx*dx + diry*dy + dirz*dz)/ds);
  }
  fangle = fangle*180/(TMath::Pi()*fNdigits);
  return (fangle);

}

Double_t WCSimVertexFinderPoint::DistHit(Double_t vx, Double_t vy, Double_t vz, WCSimRecoEvent* myEvent)
{
  this->FillArrays(myEvent);
  Double_t fhitdist = 0.0;
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
  
  Double_t dx = fDigitX[idigit]-vx;
  Double_t dy = fDigitY[idigit]-vy;
  Double_t dz = fDigitZ[idigit]-vz;
  Double_t ds = sqrt(dx*dx+dy*dy+dz*dz);
  fhitdist += ds;
  }
  fhitdist = fhitdist/fNdigits;
  return fhitdist;
}

Double_t WCSimVertexFinderPoint::BotFrac(WCSimRecoEvent* myEvent)
{
  this->FillArrays(myEvent);

  Double_t NBot = 0.;
  for( Int_t idigit=0; idigit<fNdigits; idigit++ ){
  if ( (fDigitZ[idigit]>=3150.)||(fDigitZ[idigit]<-3150.) ) NBot+=1.0;
  }
  Double_t ffrac = NBot/fNdigits;
  //std::cout << NBot << "/" << fNdigits << " " << ffrac << std::endl;
  return ffrac;
}
