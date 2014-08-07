#include "WCSimDisplayAB.hh"

#include "WCSimRecoDigit.hh"
#include "WCSimRecoRing.hh"
#include "WCSimRecoEvent.hh"

#include "WCSimReco.hh" //this is new erika

#include "WCSimTrueEvent.hh"
#include "WCSimTrueTrack.hh"
#include "WCSimInterface.hh"

#include "WCSimGeometry.hh"
#include "WCSimVertexGeometry.hh"

#include "TCanvas.h"
#include "TPad.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"

#include "TLine.h"
#include "TBox.h"
#include "TEllipse.h"
#include "TMarker.h"
#include "TPolyMarker.h"
#include "TPolyLine.h"
#include "TLegend.h"

#include <iostream>
#include <cmath>

ClassImp(WCSimDisplayAB)

WCSimDisplayAB::WCSimDisplayAB() :  WCSimDisplay(),
  fGeoType(-1),
  fCylRadius(0.0),
  fCylLength(0.0),
  fCylDiagonal(0.0),
  fMailBoxX(0.0),
  fMailBoxY(0.0),
  fMailBoxZ(0.0),
  fMailBoxDiagonal(0.0),
  fScale(1.0),
  wcCanvas(0),
  wcDisplay(0),
  wcLegend(0),
  wcCylEdgeSide(0),
  wcCylEdgeTop(0),
  wcCylEdgeBottom(0),  
  wcBoxEdgeSide(0),
  wcBoxEdgeTop(0),
  wcBoxEdgeBottom(0),
  wcBoxEdgeLine1(0),
  wcBoxEdgeLine2(0),
  wcBoxEdgeLine3(0),
  wcBoxEdgeLine4(0),
  wcTimeCanvas(0),
  wcdTCanvas(0),
  wcTimeLegend(0),
  wcdTLegend(0),
  wcRecoLegend(0),
				    //erikaaa
				    fUseFakeInfo(0),
  wcLPCanvas(0), wcLPLegend(0),
  wcLMCanvas(0), wcLMLegend(0)
{
  std::cout << " *** WCSimDisplayAB::WCSimDisplayAB() *** " << std::endl;

  this->Initialize();
}

WCSimDisplayAB::~WCSimDisplayAB()
{
 
}

void WCSimDisplayAB::Initialize()
{
  std::cout << " *** WCSimDisplayAB::Initialize() *** " << std::endl;

  this->BuildGeometry();
}

void WCSimDisplayAB::Reset()
{
  std::cout << " *** WCSimDisplayAB::Reset() *** " << std::endl;
  
  if( wcCylEdgeSide )    delete wcCylEdgeSide;     wcCylEdgeSide = 0;
  if( wcCylEdgeTop )     delete wcCylEdgeTop;      wcCylEdgeTop = 0;
  if( wcCylEdgeBottom )  delete wcCylEdgeBottom;   wcCylEdgeBottom = 0;  
  if( wcBoxEdgeSide )    delete wcBoxEdgeSide;     wcBoxEdgeSide = 0;
  if( wcBoxEdgeTop )     delete wcBoxEdgeTop;      wcBoxEdgeTop = 0;
  if( wcBoxEdgeBottom )  delete wcBoxEdgeBottom;   wcBoxEdgeBottom = 0;
  if( wcBoxEdgeLine1 )   delete wcBoxEdgeLine1;    wcBoxEdgeLine1 = 0;
  if( wcBoxEdgeLine2 )   delete wcBoxEdgeLine2;    wcBoxEdgeLine2 = 0;    
  if( wcBoxEdgeLine3 )   delete wcBoxEdgeLine3;    wcBoxEdgeLine3 = 0;
  if( wcBoxEdgeLine4 )   delete wcBoxEdgeLine4;    wcBoxEdgeLine4 = 0;

  if( wcDisplay )     delete wcDisplay;      wcDisplay = 0;
  if( wcCanvas )      delete wcCanvas;       wcCanvas = 0;
  if( wcLegend )      delete wcLegend;       wcLegend = 0;
  if( wcTimeCanvas )  delete wcTimeCanvas;   wcTimeCanvas = 0;
  if( wcTimeLegend )  delete wcTimeLegend;   wcTimeLegend = 0;
  if( wcdTCanvas )  delete wcdTCanvas;   wcdTCanvas = 0;
  if( wcdTLegend )  delete wcdTLegend;   wcdTLegend = 0;
  if( wcRecoLegend )   delete wcRecoLegend;    wcRecoLegend = 0;
  if( wcLPCanvas )  delete wcLPCanvas;   wcLPCanvas = 0;
  if( wcLPLegend )  delete wcLPLegend;   wcLPLegend = 0;
  if( wcLMCanvas )  delete wcLMCanvas;   wcLMCanvas = 0;
  if( wcLMLegend )  delete wcLMLegend;   wcLMLegend = 0;
  
}

void WCSimDisplayAB::ResetDisplay()
{
  std::cout << "WCSimDisplayAB::ResetDisplay() " <<std::endl;
  // delete all digits
  for( UInt_t i=0; i<wcDigits.size(); i++ ){
    delete (TMarker*)(wcDigits.at(i));
  }
  wcDigits.clear();

  for( UInt_t i=0; i<wcTimeDigits.size(); i++ ){
    delete (TMarker*)(wcTimeDigits.at(i));
  }
  wcTimeDigits.clear();
  std::cout << " i am good after reset timedigits " << std::endl;
  
  for( UInt_t i=0; i<wcdTDigits.size(); i++ ){
    delete (TMarker*)(wcdTDigits.at(i));
  }
  wcdTDigits.clear();
  std::cout << " i am good after reset dtdigits " << std::endl;
  //if( (wcdTearlyDigits.size())!=0 ){
  //for( UInt_t i=0; i<wcdTearlyDigits.size(); i++ ){
    //delete (TMarker*)(wcdTearlyDigits.at(i));
  //}
  //}
  std::cout << " i am good after reset dtearlydigits delete" << std::endl;
  wcdTearlyDigits.clear();
  std::cout << " i am good after reset dtearlydigits " << std::endl;

  for( UInt_t i=0; i<wcCommonDigits.size(); i++ ){
    delete (TMarker*)(wcCommonDigits.at(i));
  }
  wcCommonDigits.clear();

  for( UInt_t i=0; i<wcLPDigits.size(); i++ ){
    delete (TMarker*)(wcLPDigits.at(i));  }
  wcLPDigits.clear();

  for( UInt_t i=0; i<wcLMDigits.size(); i++ ){
    delete (TMarker*)(wcLMDigits.at(i));  }
  wcLMDigits.clear();


  // delete all rings
  for( UInt_t i=0; i<wcRings.size(); i++ ){
    delete (TPolyMarker*)(wcRings.at(i));
  }
  wcRings.clear();

  // reset event info
  fRunNumber = -1;
  fEventNumber = -1;
  fTriggerNumber = -1;

  // update display
  std::cout << " i am good before drawnewdisplay " << std::endl;
  this->DrawNewDisplay();
  std::cout << " i am good after drawnewdisplay " << std::endl;
  
}

//erikaaaa
// void WCSimDisplayAB::UseFakeVertex(Bool_t fake){fUseFakeInfo=fake;
//   //std::cout<<"I am reading the use fake vertex option, i am soooooo clever" << std::endl;
// }

void WCSimDisplayAB::SetFakeVertex(Double_t fax0,Double_t fay0,Double_t faz0,Double_t fapx,Double_t fapy,Double_t fapz){
  fUseFakeInfo=1;
  fakex0=fax0;  fakey0=fay0;  fakez0=faz0;
 fakepx=fapx;  fakepy=fapy;  fakepz=fapz;
 std::cout <<"SetFakeVertex reporting for duty"<<std::endl;
}

void WCSimDisplayAB::BuildGeometry()
{
  std::cout << " *** WCSimDisplayAB::BuildGeometry() *** " << std::endl;
  
  // Reset Display
  // =============
  this->Reset();

  // convert [cm] to [m]
  // ===================
  fScale = 0.01;

  // Look up Geometry
  // ================
  fGeoType = WCSimGeometry::Instance()->GetGeoType(); // assume cylindrical geometry    

  // Make TimeDisplay
  // ================
  fMakeTimeDisplay = 1; // find a way to pass this setting from outside
  fMakedTDisplay = 1; // find a way to pass this setting from outside
  fMakeLPDisplay = 1;
  fMakeLMDisplay = 1;

  // Cylindrical Detector
  // ====================
  if( fGeoType==WCSimGeometry::kCylinder ){

    // get detector dimensions from geometry tree
    fCylRadius = WCSimGeometry::Instance()->GetCylRadius();
    fCylLength = WCSimGeometry::Instance()->GetCylLength();
    fCylDiagonal = sqrt( fCylLength*fCylLength + 4.0*fCylRadius*fCylRadius );

    // calculate dimesions of event display
    fU = 2.0*TMath::Pi()*fCylRadius;
    fV = 2.0*fCylRadius + fCylLength + 2.0*fCylRadius;

    // calulate bin width for histogram
    binsWidth = 0.005*(fU+fV);
    binsU = (Int_t)(fU/binsWidth);
    binsV = (Int_t)(fV/binsWidth);

    // calculate dimensions of canvas
    canvasWidth = 800.0;
    canvasHeight = (fV/fU)*canvasWidth;
    canvasU = (Int_t)(canvasWidth);
    canvasV = (Int_t)(canvasHeight);

    // make canvas
    wcCanvas = new TCanvas("WCSimDisplay","WCSim Event Display",
                             canvasU, canvasV);

    // make histogram
    wcDisplay = new TH2D("wcDisplay","",binsU, -0.5*fU*fScale, +0.5*fU*fScale,
			                binsV, -0.5*fV*fScale, +0.5*fV*fScale);
    wcDisplay->GetXaxis()->SetTitle("r * #theta (m)");
    wcDisplay->GetYaxis()->SetTitle("z (m)");  

    wcDisplay->GetXaxis()->SetTitleSize(0.06);
    wcDisplay->GetYaxis()->SetTitleSize(0.06);  

    wcDisplay->GetXaxis()->SetLabelSize(0.05);
    wcDisplay->GetYaxis()->SetLabelSize(0.05);

    wcDisplay->GetXaxis()->SetNdivisions(1007);
    wcDisplay->GetYaxis()->SetNdivisions(1007);

    wcDisplay->GetXaxis()->CenterTitle();
    wcDisplay->GetYaxis()->CenterTitle();

    std::cout << " I AM GOOD!!!! " << std::endl;
    // outline for side of detector
    wcCylEdgeSide = new TBox( -TMath::Pi()*fCylRadius*fScale, -0.5*fCylLength*fScale,
                              +TMath::Pi()*fCylRadius*fScale, +0.5*fCylLength*fScale );
    wcCylEdgeSide->SetFillStyle(0);
    wcCylEdgeSide->SetLineColor(1);
    wcCylEdgeSide->SetLineWidth(2);

    // outline for top face of detector
    wcCylEdgeTop = new TEllipse(0.0, +0.5*fCylLength*fScale+fCylRadius*fScale, fCylRadius*fScale);
    wcCylEdgeTop->SetFillStyle(0);
    wcCylEdgeTop->SetLineColor(1);
    wcCylEdgeTop->SetLineWidth(2);

    // outline for bottom face of detector
    wcCylEdgeBottom = new TEllipse(0.0, -0.5*fCylLength*fScale-fCylRadius*fScale, fCylRadius*fScale);
    wcCylEdgeBottom->SetFillStyle(0);
    wcCylEdgeBottom->SetLineColor(1);
    wcCylEdgeBottom->SetLineWidth(2);

    // coordinates for title box
    titleU = -0.5*fU;
    titleV = +0.55*fV;    

    // make legend (reco/true)
    this->MakeLegendRECO();

    // make legend (pulse height)
    this->MakeLegendQPE(); 

    // make time display canvas
    if( fMakeTimeDisplay ){  
      wcTimeCanvas = new TCanvas("WCSimTimeDisplay","WCSim Timing Display",
                                   canvasU, canvasV);    

      // make legend (timing)
      this->MakeLegendTIME();
    }

    // make time residual display canvas
    if( fMakedTDisplay ){  
      wcdTCanvas = new TCanvas("WCSimdTDisplay","WCSim Time Residual Display",
                                   canvasU, canvasV);    

      // make legend (timing)
      this->MakeLegenddT();
    }



    //erika
    if( fMakeLPDisplay ){  
      wcLPCanvas = new TCanvas("WCSimLPDisplay","WCSim LPhoton Display",
			       canvasU, canvasV);    
      this->MakeLegendLP();}
    if( fMakeLMDisplay ){  
      wcLMCanvas = new TCanvas("WCSimLMDisplay","WCSim LMuon Display",
			       canvasU, canvasV);    
      this->MakeLegendLM();}
  }

  // MAILBOX GEOMETRY
  // ================
  if( fGeoType==WCSimGeometry::kMailBox ){

    // get detector dimensions from geometry tree
    fMailBoxX = WCSimGeometry::Instance()->GetMailBoxX();
    fMailBoxY = WCSimGeometry::Instance()->GetMailBoxY();
    fMailBoxZ = WCSimGeometry::Instance()->GetMailBoxZ();
    fMailBoxDiagonal = sqrt( fMailBoxX*fMailBoxX + fMailBoxY*fMailBoxY + fMailBoxZ*fMailBoxZ );

    // calculate dimesions of event display
    fU = 2.0*(fMailBoxX + fMailBoxY);
    fV = fMailBoxZ + 2.0*fMailBoxX;

    // calulate bin width for histogram
    binsWidth = 0.005*(fU+fV);
    binsU = (Int_t)(fU/binsWidth);
    binsV = (Int_t)(fV/binsWidth);

    // calculate dimensions of canvas
    canvasHeight = 800.0;
    canvasWidth = (fU/fV)*canvasHeight;
    canvasU = (Int_t)(canvasWidth);
    canvasV = (Int_t)(canvasHeight);

    // make canvas
    wcCanvas = new TCanvas("WCSimDisplay","WCSim Event Display",
                             canvasU, canvasV);

    // make histogram
    wcDisplay = new TH2D("wcDisplay","",binsU, -0.5*fU*fScale, +0.5*fU*fScale,
			                binsV, -0.5*fV*fScale, +0.5*fV*fScale);
    wcDisplay->GetXaxis()->SetTitle("x,y (m)");
    wcDisplay->GetYaxis()->SetTitle("z (m)");  

    wcDisplay->GetXaxis()->SetTitleSize(0.06);
    wcDisplay->GetYaxis()->SetTitleSize(0.06);  

    wcDisplay->GetXaxis()->SetLabelSize(0.05);
    wcDisplay->GetYaxis()->SetLabelSize(0.05);

    wcDisplay->GetXaxis()->SetNdivisions(1007);
    wcDisplay->GetYaxis()->SetNdivisions(1007);

    wcDisplay->GetXaxis()->CenterTitle();
    wcDisplay->GetYaxis()->CenterTitle();

    // outline for side of detector
    wcBoxEdgeSide = new TBox( -(fMailBoxX+fMailBoxY)*fScale, -0.5*fMailBoxZ*fScale,
                              +(fMailBoxX+fMailBoxY)*fScale, +0.5*fMailBoxZ*fScale );
    wcBoxEdgeSide->SetFillStyle(0);
    wcBoxEdgeSide->SetLineColor(1);
    wcBoxEdgeSide->SetLineWidth(2);

    // outline for top face of detector
    wcBoxEdgeTop = new TBox( -0.5*fMailBoxY*fScale, +0.5*fMailBoxZ*fScale,
                             +0.5*fMailBoxY*fScale, +(0.5*fMailBoxZ+fMailBoxX)*fScale );
    wcBoxEdgeTop->SetFillStyle(0);
    wcBoxEdgeTop->SetLineColor(1);
    wcBoxEdgeTop->SetLineWidth(2);

    // outline for bottom face of detector
    wcBoxEdgeBottom = new TBox( -0.5*fMailBoxY*fScale, -0.5*fMailBoxZ*fScale,
                                +0.5*fMailBoxY*fScale, -(0.5*fMailBoxZ+fMailBoxX)*fScale );
    wcBoxEdgeBottom->SetFillStyle(0);
    wcBoxEdgeBottom->SetLineColor(1);
    wcBoxEdgeBottom->SetLineWidth(2);

    // edges on side of detector
    wcBoxEdgeLine1 = new TLine( -(0.5*fMailBoxY+fMailBoxX)*fScale, -0.5*fMailBoxZ*fScale,
                                -(0.5*fMailBoxY+fMailBoxX)*fScale, +0.5*fMailBoxZ*fScale );
    wcBoxEdgeLine1->SetLineColor(1);
    wcBoxEdgeLine1->SetLineWidth(2);
    wcBoxEdgeLine1->SetLineStyle(7);

    wcBoxEdgeLine2 = new TLine( -0.5*fMailBoxY*fScale, -0.5*fMailBoxZ*fScale,
                                -0.5*fMailBoxY*fScale, +0.5*fMailBoxZ*fScale );
    wcBoxEdgeLine2->SetLineColor(1);
    wcBoxEdgeLine2->SetLineWidth(2);
    wcBoxEdgeLine2->SetLineStyle(7);

    wcBoxEdgeLine3 = new TLine( +0.5*fMailBoxY*fScale, -0.5*fMailBoxZ*fScale,
                                +0.5*fMailBoxY*fScale, +0.5*fMailBoxZ*fScale );
    wcBoxEdgeLine3->SetLineColor(1);
    wcBoxEdgeLine3->SetLineWidth(2);
    wcBoxEdgeLine3->SetLineStyle(7);

    wcBoxEdgeLine4 = new TLine( +(0.5*fMailBoxY+fMailBoxX)*fScale, -0.5*fMailBoxZ*fScale,
                                +(0.5*fMailBoxY+fMailBoxX)*fScale, +0.5*fMailBoxZ*fScale);
    wcBoxEdgeLine4->SetLineColor(1);
    wcBoxEdgeLine4->SetLineWidth(2);
    wcBoxEdgeLine4->SetLineStyle(7);

    // coordinates for title box
    titleU = -0.5*fU;
    titleV = +0.55*fV;    

    // make legend (reco/true)
    this->MakeLegendRECO();

    // make legend (pulse height)
    this->MakeLegendQPE();

    // make time display canvas
    if( fMakeTimeDisplay ){  
      wcTimeCanvas = new TCanvas("WCSimTimeDisplay","WCSim Timing Display",
                                   canvasU, canvasV);    

      // make legend (timing)
      this->MakeLegendTIME();
    }
    if( fMakedTDisplay ){  
      wcdTCanvas = new TCanvas("WCSimdTDisplay","WCSim Time Residual Display",
                                   canvasU, canvasV);    

      // make legend (timing)
      this->MakeLegenddT();
    }


    if( fMakeLPDisplay ){  
      wcLPCanvas = new TCanvas("WCSimLPDisplay","WCSim LPhoton Display",
			       canvasU, canvasV);    
      this->MakeLegendLP();
    }
 if( fMakeLMDisplay ){  
      wcLMCanvas = new TCanvas("WCSimLMDisplay","WCSim LMuon Display",
			       canvasU, canvasV);    
      this->MakeLegendLM();
    }



  }

  // Draw Everything
  // ===============

  // draw space display
  if( wcCanvas ){
    wcCanvas->cd();
    wcDisplay->Draw();
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcLegend->Draw();
    wcRecoLegend->Draw();
    wcCanvas->Update();
  }

  // draw time display
  if( wcTimeCanvas ){
    wcTimeCanvas->cd();
    wcDisplay->Draw();    
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();   
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcTimeLegend->Draw();
    wcRecoLegend->Draw();
    wcTimeCanvas->Update();
  }

  // draw time residual display
  if( wcdTCanvas ){
    wcdTCanvas->cd();
    wcDisplay->Draw();    
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();   
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcdTLegend->Draw();
    wcRecoLegend->Draw();
    wcdTCanvas->Update();
  }

  if( wcLPCanvas ){
    wcLPCanvas->cd();
    wcDisplay->Draw();    
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();   
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcLPLegend->Draw();
    wcRecoLegend->Draw();
    wcLPCanvas->Update();
  }

  if( wcLMCanvas ){
    wcLMCanvas->cd();
    wcDisplay->Draw();    
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();   
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcLMLegend->Draw();
    wcRecoLegend->Draw();
    wcLMCanvas->Update();
  }


  return;
}

void WCSimDisplayAB::DrawNewDisplay()
{
  // Draw Everything
  // ===============
  std::cout << "DrawNewDisplay()" << std::endl;

  // sanity check
  if( wcCanvas==0 ) return;

  // run/event info
  wcTitleString="";
  
  if( fRunNumber>=0 ){  
    wcTitleString.Append("Run: "); 
    wcTitleString+=fRunNumber;
    wcTitleString.Append("  ");
    wcTitleString.Append("Event: "); 
    wcTitleString+=fEventNumber;
    wcTitleString.Append("  ");
    wcTitleString.Append("SubEvent: "); 
    wcTitleString+=fTriggerNumber;

    wcTitleLatex.SetTextFont(42);
    wcTitleLatex.SetTextSize(0.04);
    wcTitleLatex.SetTextAlign(13);
  }

  // draw space display
  if( wcCanvas ){
    wcCanvas->cd();
    wcDisplay->Draw();    
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();   
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcLegend->Draw();
    wcRecoLegend->Draw();
    wcTitleLatex.DrawLatex(titleU*fScale,
                           titleV*fScale,
                           wcTitleString.Data());
    wcCanvas->Update();
  }

  // draw time display
  if( wcTimeCanvas ){
    wcTimeCanvas->cd();
    wcDisplay->Draw();
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();   
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcTimeLegend->Draw();
    wcRecoLegend->Draw();
    wcTitleLatex.DrawLatex(titleU*fScale,
                           titleV*fScale,
                           wcTitleString.Data());
    wcTimeCanvas->Update();
  }
  if( wcdTCanvas ){
    wcdTCanvas->cd();
    wcDisplay->Draw();
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();   
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcdTLegend->Draw();
    wcRecoLegend->Draw();
    wcTitleLatex.DrawLatex(titleU*fScale,
                           titleV*fScale,
                           wcTitleString.Data());
    wcdTCanvas->Update();
  }


  //erika
  if( wcLPCanvas ){
    wcLPCanvas->cd();
    wcDisplay->Draw();
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();   
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcLPLegend->Draw();
    wcRecoLegend->Draw();
    wcTitleLatex.DrawLatex(titleU*fScale,
                           titleV*fScale,
                           wcTitleString.Data());
    wcLPCanvas->Update();
  }
  if( wcLMCanvas ){
    wcLMCanvas->cd();
    wcDisplay->Draw();
    if( wcCylEdgeSide )   wcCylEdgeSide->Draw();
    if( wcCylEdgeTop )    wcCylEdgeTop->Draw();
    if( wcCylEdgeBottom ) wcCylEdgeBottom->Draw();    
    if( wcBoxEdgeSide )   wcBoxEdgeSide->Draw();
    if( wcBoxEdgeTop )    wcBoxEdgeTop->Draw();
    if( wcBoxEdgeBottom ) wcBoxEdgeBottom->Draw();   
    if( wcBoxEdgeLine1 )  wcBoxEdgeLine1->Draw();
    if( wcBoxEdgeLine2 )  wcBoxEdgeLine2->Draw();
    if( wcBoxEdgeLine3 )  wcBoxEdgeLine3->Draw();
    if( wcBoxEdgeLine4 )  wcBoxEdgeLine4->Draw();
    wcLMLegend->Draw();
    wcRecoLegend->Draw();
    wcTitleLatex.DrawLatex(titleU*fScale,
                           titleV*fScale,
                           wcTitleString.Data());
    wcLMCanvas->Update();
  }






}

void WCSimDisplayAB::UpdateDisplay()
{
  // draw new display
  this->DrawNewDisplay();

  // space display
  if( wcCanvas ){
    wcCanvas->cd();
  
    for( UInt_t n=0; n<wcDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcDigits.at(n));
      marker->Draw();
    }

   for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcRings.size(); n++ ){
      TPolyMarker* polymarker = (TPolyMarker*)(wcRings.at(n));
      polymarker->Draw("C");
    }

    wcCanvas->Update();
  }

  // time display
  if( wcTimeCanvas ){
    wcTimeCanvas->cd();

    for( UInt_t n=0; n<wcTimeDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcTimeDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcRings.size(); n++ ){
      TPolyMarker* polymarker = (TPolyMarker*)(wcRings.at(n));
      polymarker->Draw("C");
    }

    wcTimeCanvas->Update();
  }

  if( wcdTCanvas ){
    wcdTCanvas->cd();

    for( UInt_t n=0; n<wcdTDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcdTDigits.at(n));
      marker->Draw();
    }
    for( UInt_t n=0; n<wcdTearlyDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcdTearlyDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcRings.size(); n++ ){
      TPolyMarker* polymarker = (TPolyMarker*)(wcRings.at(n));
      polymarker->Draw("C");
    }

    wcdTCanvas->Update();
  }

  //erika
  if( wcLPCanvas ){
    wcLPCanvas->cd();
    for( UInt_t n=0; n<wcLPDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcLPDigits.at(n));
      marker->Draw();}
    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();}
    for( UInt_t n=0; n<wcRings.size(); n++ ){
      TPolyMarker* polymarker = (TPolyMarker*)(wcRings.at(n));
      polymarker->Draw("C");}
    wcLPCanvas->Update();}

  if( wcLMCanvas ){
    wcLMCanvas->cd();
    for( UInt_t n=0; n<wcLMDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcLMDigits.at(n));
      marker->Draw();}
    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();}
    for( UInt_t n=0; n<wcRings.size(); n++ ){
      TPolyMarker* polymarker = (TPolyMarker*)(wcRings.at(n));
      polymarker->Draw("C");}
    wcLMCanvas->Update();}





}

void WCSimDisplayAB::DrawDisplay(WCSimRecoEvent* myRecoEvent)
{
  std::cout << " before DrawDisplay " << std::endl;
  // Reset Display
  // =============
  this->ResetDisplay();
 
  std::cout << " I AM GOOD!!!! " << std::endl;
  // Check for Event  
  // ===============
  if( myRecoEvent==0 ) return;

  // Get Event Info
  // ==============
  fRunNumber = myRecoEvent->GetRun();
  fEventNumber = myRecoEvent->GetEvent();
  fTriggerNumber = myRecoEvent->GetTrigger();
  std::cout << " I AM GOOD after triggernumber!!!! " << std::endl;

//===================== true info.
  WCSimTrueEvent* myTrueEvent = WCSimInterface::TrueEvent();
  Double_t x0 = myTrueEvent->GetVtxX();
  Double_t y0 = myTrueEvent->GetVtxY();
  Double_t z0 = myTrueEvent->GetVtxZ();
  Double_t px = myTrueEvent->GetDirX();
  Double_t py = myTrueEvent->GetDirY();
  Double_t pz = myTrueEvent->GetDirZ();
  Double_t t0 = 0.0;
  std::cout << " I AM GOOD after true event!!!! " << std::endl;


  //erika fake info
 if(fUseFakeInfo){std::cout<<"I really want to use fake info"<<std::endl;
   x0=fakex0; y0=fakey0; z0=fakez0;
   px=fakepx; py=fakepy; pz=fakepz;
}

  // Draw all digits
  // ================
  for( Int_t nDigit=0; nDigit<myRecoEvent->GetNDigits(); nDigit++ ){
    WCSimRecoDigit* myDigit = (WCSimRecoDigit*)(myRecoEvent->GetDigit(nDigit));

    if( myDigit->IsFiltered() ){

    Double_t Q = myDigit->GetQPEs();
    Double_t T = myDigit->GetTime();
    
    if( Q<GetPulseHeightCut() ) continue;

    Int_t region = myDigit->GetRegion(); //std::cout << region << std::endl;
    Double_t x = myDigit->GetX();
    Double_t y = myDigit->GetY();
    Double_t z = myDigit->GetZ();

    Double_t u = -99999.9;
    Double_t v = -99999.9;

    // convert XYZ to UV
    WCSimGeometry::Instance()->XYZtoUV( region,
                                        x, y, z,
                                        u, v );

    // create markers
    // ==============
    TMarker* marker = 0;      
    Int_t colourCode = 0;

    // create marker for space display
    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.2);
    colourCode = this->QPEtoCOL(Q);
    marker->SetMarkerColor(colourCode);      
    wcDigits.push_back(marker);

    // create marker for time display
    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.2);
    colourCode = this->TIMEtoCOL(T);
    marker->SetMarkerColor(colourCode);
    wcTimeDigits.push_back(marker);

    // create marker for time residual display
//============================...TX, calculate TResid =========================
    Double_t dT = 0.0;
    Double_t lm = 0.0;
    Double_t lp = 0.0;
    WCSimVertexGeometry::Instance()->CalcTResid(x0, y0, z0, t0, px, py, pz, x, y, z, T, dT, lp, lm);
    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.2);
    colourCode = this->dTtoCOL(dT);
    marker->SetMarkerColor(colourCode);
    wcdTDigits.push_back(marker);
    if( dT<2.0 ) wcdTearlyDigits.push_back(marker);
//-----------------------------------------------------------------------

   //erika
    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.2);
    colourCode = this->LPtoCOL(lp);
    marker->SetMarkerColor(colourCode);
    wcLPDigits.push_back(marker);

    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.2);
    colourCode = this->LMtoCOL(lm);
    marker->SetMarkerColor(colourCode);
    wcLMDigits.push_back(marker);
    
    

    }
  }
  std::cout << " I AM GOOD after fill digit vectors!!!! " << std::endl;

  // Draw Display
  // ============
  this->DrawNewDisplay();

  // space display
  if( wcCanvas ){
    wcCanvas->cd();

    for( UInt_t n=0; n<wcDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();
    }

    wcCanvas->Update();
  }
  std::cout << " I AM GOOD after drawing wcCanvas!!!! " << std::endl;

  // time display
  if( wcTimeCanvas ){
    wcTimeCanvas->cd();

    for( UInt_t n=0; n<wcTimeDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcTimeDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();
    }

    wcTimeCanvas->Update();
  }
  std::cout << " I AM GOOD after drawing Time Canvas!!!! " << std::endl;

  // time residual display
  if( wcdTCanvas ){
    wcdTCanvas->cd();

    for( UInt_t n=0; n<wcdTDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcdTDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcdTearlyDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcdTearlyDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();
    }

    wcdTCanvas->Update();
  }
  std::cout << " I AM GOOD after drawing dTCanvas!!!! " << std::endl;

  //erika

 if( wcLPCanvas ){
    wcLPCanvas->cd();
    for( UInt_t n=0; n<wcLPDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcLPDigits.at(n));
      marker->Draw();}
    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();}
    wcLPCanvas->Update();}

 if( wcLMCanvas ){
    wcLMCanvas->cd();
    for( UInt_t n=0; n<wcLMDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcLMDigits.at(n));
      marker->Draw();}
    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();}
    wcLMCanvas->Update();}


  return;
}

void WCSimDisplayAB::DrawCleanDisplay(WCSimRecoEvent* myRecoEvent)
{std::cout<<"Looooooooook : I want to use true info 1"<<std::endl;
  // Reset Display
  // =============
  this->ResetDisplay();

  // Check for Event  
  // ===============
  if( myRecoEvent==0 ) return;

  // Get Event Info
  // ==============
  fRunNumber = myRecoEvent->GetRun();
  fEventNumber = myRecoEvent->GetEvent();
  fTriggerNumber = myRecoEvent->GetTrigger();
  

//===================== true info.
  WCSimTrueEvent* myTrueEvent = WCSimInterface::TrueEvent();
  Double_t x0 = myTrueEvent->GetVtxX();
  Double_t y0 = myTrueEvent->GetVtxY();
  Double_t z0 = myTrueEvent->GetVtxZ();
  Double_t px = myTrueEvent->GetDirX();
  Double_t py = myTrueEvent->GetDirY();
  Double_t pz = myTrueEvent->GetDirZ();
  Double_t t0 = 0.0;

std::cout<<"Looooooooook : I want to use true info"<<std::endl;

 //Erikaaaaa fake info
  if(fUseFakeInfo){std::cout<<"I want to use fake info"<<std::endl;}




  // Draw all digits
  // ===============
  for( Int_t nDigit=0; nDigit<myRecoEvent->GetNDigits(); nDigit++ ){
    WCSimRecoDigit* myDigit = (WCSimRecoDigit*)(myRecoEvent->GetDigit(nDigit));

    Double_t Q = myDigit->GetQPEs();
    Double_t T = myDigit->GetTime();

    if( Q<GetPulseHeightCut() ) continue;

    Int_t region = myDigit->GetRegion();
    Double_t x = myDigit->GetX();
    Double_t y = myDigit->GetY();
    Double_t z = myDigit->GetZ();

    Double_t u = -99999.9;
    Double_t v = -99999.9;
      
    // convert XYZ to UV
    WCSimGeometry::Instance()->XYZtoUV( region,
                                        x, y, z,
                                        u, v );
    // create marker
    // =============
    TMarker* marker = 0;

    // create marker for space display
    marker = new TMarker(u*fScale,v*fScale,24); // 24: open circles
    marker->SetMarkerSize(0.75);
    marker->SetMarkerColor(kGray);   
    wcDigits.push_back(marker);

    // create marker for time display
    marker = new TMarker(u*fScale,v*fScale,24); // 24: open circles
    marker->SetMarkerSize(0.75);
    marker->SetMarkerColor(kGray);
    wcTimeDigits.push_back(marker);

    // create marker for time residual display
    marker = new TMarker(u*fScale,v*fScale,24); // 24: open circles
    marker->SetMarkerSize(0.75);
    marker->SetMarkerColor(kGray);
    wcdTDigits.push_back(marker);

    //erika
    marker = new TMarker(u*fScale,v*fScale,24); // 24: open circles
    marker->SetMarkerSize(0.75);
    marker->SetMarkerColor(kGray);
    wcLPDigits.push_back(marker);

    marker = new TMarker(u*fScale,v*fScale,24); // 24: open circles
    marker->SetMarkerSize(0.75);
    marker->SetMarkerColor(kGray);
    wcLMDigits.push_back(marker);


    // create marker for time residual early display
    //marker = new TMarker(u*fScale,v*fScale,24); // 24: open circles
    //marker->SetMarkerSize(0.75);
    //marker->SetMarkerColor(kGray);
    //wcdTearlyDigits.push_back(marker);
  
    // Draw filtered digits
    // ====================
    if( myDigit->IsFiltered()==0 ) continue;

    // create markers
    // ==============
    Int_t colourCode = 0;

    // create marker for space display
    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.75);
     
    colourCode = this->QPEtoCOL(Q);
    marker->SetMarkerColor(colourCode);
      
    wcDigits.push_back(marker);

    // create marker for time display
    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.75);

    colourCode = this->TIMEtoCOL(T);
    marker->SetMarkerColor(colourCode);
      
    wcTimeDigits.push_back(marker);

    // create marker for time residual display
//============================...TX, calculate TResid =========================
    Double_t dT = 0.0;
    Double_t lm = 0.0;
    Double_t lp = 0.0;
    WCSimVertexGeometry::Instance()->CalcTResid(x0, y0, z0, t0, px, py, pz, x, y, z, T, dT, lm, lp);
    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.2);
    colourCode = this->dTtoCOL(dT);
    marker->SetMarkerColor(colourCode);
    wcdTDigits.push_back(marker);
    if( dT<1.0 ) wcdTearlyDigits.push_back(marker);
//-----------------------------------------------------------------------------


//erika

    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.2);
    colourCode = this->LPtoCOL(lp);
    wcLPDigits.push_back(marker);
    marker = new TMarker(u*fScale,v*fScale,20); // 20: closed circles
    marker->SetMarkerSize(0.2);
    colourCode = this->LMtoCOL(lm);
    wcLMDigits.push_back(marker);
  }

  // Draw Display
  // ============
  this->DrawNewDisplay();

  // space display
  if( wcCanvas ){
    wcCanvas->cd();

    for( UInt_t n=0; n<wcDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();
    }

    wcCanvas->Update();
  }

  // time display
  if( wcTimeCanvas ){
    wcTimeCanvas->cd();

    for( UInt_t n=0; n<wcTimeDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcTimeDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();
    }

    wcTimeCanvas->Update();
  }
  // time residual display
  if( wcdTCanvas ){
    wcdTCanvas->cd();

    for( UInt_t n=0; n<wcdTDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcdTDigits.at(n));
      marker->Draw();
    }
    for( UInt_t n=0; n<wcdTearlyDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcdTearlyDigits.at(n));
      marker->Draw();
    }

    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();
    }

    wcdTCanvas->Update();
  }
  // time residual realy display



  //erika
 if( wcLPCanvas ){
   wcLPCanvas->cd();
    for( UInt_t n=0; n<wcLPDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcLPDigits.at(n));
      marker->Draw();}
    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();}
    wcLPCanvas->Update();}

 if( wcLMCanvas ){
   wcLMCanvas->cd();
    for( UInt_t n=0; n<wcLMDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcLMDigits.at(n));
      marker->Draw();}
    for( UInt_t n=0; n<wcCommonDigits.size(); n++ ){
      TMarker* marker = (TMarker*)(wcCommonDigits.at(n));
      marker->Draw();}
    wcLMCanvas->Update();}


  return;
}

void WCSimDisplayAB::DrawTrueEvent(WCSimTrueEvent* myTrueEvent)
{ 
  // Check for Event  
  // ===============
  if( myTrueEvent==0 
   || myTrueEvent->GetNTracks()==0 ) return;
    
  // True Event
  // ==========
  Double_t evt_x0 = myTrueEvent->GetVtxX();
  Double_t evt_y0 = myTrueEvent->GetVtxY();
  Double_t evt_z0 = myTrueEvent->GetVtxZ();
        
  Double_t evt_px = myTrueEvent->GetDirX();
  Double_t evt_py = myTrueEvent->GetDirY();
  Double_t evt_pz = myTrueEvent->GetDirZ();
    
  // colour code (truth)
  Int_t evt_colourcode = 2; // red

  // draw true vertex
  this->DrawVertex(evt_x0, evt_y0, evt_z0,
                   evt_px, evt_py, evt_pz,
                   evt_colourcode);


  // Loop over True Tracks
  // =====================
  for( Int_t nTrack=0; nTrack<myTrueEvent->GetNTracks(); nTrack++ ){
    WCSimTrueTrack* myTrack = (WCSimTrueTrack*)(myTrueEvent->GetTrack(nTrack));

    // true vertex and direction
    Double_t x0 = myTrack->GetVtxX();
    Double_t y0 = myTrack->GetVtxY();
    Double_t z0 = myTrack->GetVtxZ();
        
    Double_t px = myTrack->GetDirX();
    Double_t py = myTrack->GetDirY();
    Double_t pz = myTrack->GetDirZ();

    Double_t angle = 42.0;

    // colour code (truth)
    Int_t colourcode = 2; // red

    // draw true ring
    this->DrawRing(x0, y0, z0,
                   px, py, pz,
                   angle, colourcode);
  }

  return;
}
   
void WCSimDisplayAB::DrawRecoEvent(WCSimRecoEvent* myRecoEvent)
{  
  // Check for Event  
  // ===============
  if( myRecoEvent==0 
   || myRecoEvent->FoundVertex()==0
      || myRecoEvent->FoundDirection()==0 ) {
    std::cout<<"I couldnt find a damn thing"<<std::endl;
return;}

  // Reconstructed Event
  // ===================
   Double_t evt_x0 = myRecoEvent->GetVtxX();
   Double_t evt_y0 = myRecoEvent->GetVtxY();
   Double_t evt_z0 = myRecoEvent->GetVtxZ();

   Double_t evt_px = myRecoEvent->GetDirX();
   Double_t evt_py = myRecoEvent->GetDirY();
   Double_t evt_pz = myRecoEvent->GetDirZ();   

   // colour code (reco)
   Int_t evt_colourcode = 1; // black
     
   // draw reconstructed vertex
   this->DrawVertex(evt_x0, evt_y0, evt_z0,
                    evt_px, evt_py, evt_pz,
                    evt_colourcode);     

  // Loop over Rings
  // ===============
  for( Int_t nRing=0; nRing<myRecoEvent->GetNRings(); nRing++ ){
    WCSimRecoRing* myRing = (WCSimRecoRing*)(myRecoEvent->GetRing(nRing));

    // reconstructed vertex and direction
    Double_t x0 = myRing->GetVtxX();
    Double_t y0 = myRing->GetVtxY();
    Double_t z0 = myRing->GetVtxZ();

    Double_t px = myRing->GetDirX();
    Double_t py = myRing->GetDirY();
    Double_t pz = myRing->GetDirZ();

    Double_t angle = myRing->GetAngle();

    // colour code (reco)
    Int_t colourcode = 1; // black

    // draw reconstructed ring
    this->DrawRing(x0, y0, z0,
                   px, py, pz,
                   angle, colourcode);
  }

  return;

}

void WCSimDisplayAB::DrawVertex(Double_t vx, Double_t vy, Double_t vz, Double_t px, Double_t py, Double_t pz, Int_t colourcode )
{
  // draw reco/true vertex
  Double_t x = 0.0;
  Double_t y = 0.0;
  Double_t z = 0.0;
  Double_t u = -99999.9;
  Double_t v = -99999.9;

  Int_t region = -1;

  // project reconstructed vertex onto detector
  WCSimGeometry::Instance()->ProjectToFarEdge( vx, vy, vz,
                                               px, py, pz,
                                               x, y, z, 
                                               region );

  // convert XYZ to UV
  WCSimGeometry::Instance()->XYZtoUV( region,
                                      x, y, z,
                                      u, v );

  // create marker for vertex
  TMarker* marker = new TMarker(u*fScale,v*fScale,29);
  marker->SetMarkerSize(2.5);
  marker->SetMarkerColor(colourcode);
  
  // store marker
  wcCommonDigits.push_back(marker);

  // Draw on display
  if( wcCanvas ){
    wcCanvas->cd();
    marker->Draw();
    wcCanvas->Update();
  }

  // Draw on display
  if( wcTimeCanvas ){
    wcTimeCanvas->cd();
    marker->Draw();
    wcTimeCanvas->Update();
  }
  // Draw on display
  if( wcdTCanvas ){
    wcdTCanvas->cd();
    marker->Draw();
    wcdTCanvas->Update();
  }

  //erika
  if( wcLPCanvas ){
    wcLPCanvas->cd();
    marker->Draw();
    wcLPCanvas->Update();}
 if( wcLMCanvas ){
    wcLMCanvas->cd();
    marker->Draw();
    wcLMCanvas->Update();}



  return;
}

void WCSimDisplayAB::DrawRing(Double_t vx, Double_t vy, Double_t vz, Double_t px, Double_t py, Double_t pz, Double_t angle, Int_t colourcode)
{
  // draw ring
  Double_t xproj = 0.0;
  Double_t yproj = 0.0;
  Double_t zproj = 0.0;

  Double_t xring = 0.0;
  Double_t yring = 0.0;
  Double_t zring = 0.0;

  Double_t x = 0.0;
  Double_t y = 0.0;
  Double_t z = 0.0;

  Double_t nx = 0.0;
  Double_t ny = 0.0;
  Double_t nz = 0.0;

  Double_t u = -99999.9;
  Double_t v = -99999.9;

  Double_t radius = 0.0;

  Int_t region = -1;

  // project vertex onto edge of detector
  WCSimGeometry::Instance()->ProjectToFarEdge( vx, vy, vz,
                                               px, py, pz,
                                               xproj, yproj, zproj, 
                                               region );

  // draw ring from many markers...
  Int_t n_ring = 360;

  Double_t* u_ring = new Double_t[n_ring];
  Double_t* v_ring = new Double_t[n_ring];

  Double_t cone_angle = angle; // 42.0;        // both angles
  Double_t delta_omega = 360.0/double(n_ring); // in degrees

  for( Int_t n=0; n<n_ring; n++ ){

    WCSimGeometry::FindCircle( xproj, yproj, zproj,
                               vx, vy, vz,
                               cone_angle, n*delta_omega,
                               xring, yring, zring,
                               nx, ny, nz,
                               radius );

    WCSimGeometry::Instance()->ProjectToFarEdge( vx, vy, vz,
                                                 nx, ny, nz,
                                                 x, y, z,
                                                 region );

    WCSimGeometry::Instance()->XYZtoUV( region,
                                        x, y, z,
                                        u, v );
    u_ring[n] = u*fScale;
    v_ring[n] = v*fScale;
  }

  // create polymarker
  TPolyMarker* polymarker = new TPolyMarker(n_ring,u_ring,v_ring);
  polymarker->SetMarkerSize(0.25); 
  polymarker->SetMarkerColor(colourcode);
  
  // store polymarker
  wcRings.push_back(polymarker);

  // draw on display
  if( wcCanvas ){
    wcCanvas->cd();
    polymarker->Draw("");
    wcCanvas->Update();
  }  

  // draw on display
  if( wcTimeCanvas ){
    wcTimeCanvas->cd();
    polymarker->Draw("");
    wcTimeCanvas->Update();
  }
  // draw on display
  if( wcdTCanvas ){
    wcdTCanvas->cd();
    polymarker->Draw("");
    wcdTCanvas->Update();
  }
  //erika
  if( wcLPCanvas ){
    wcLPCanvas->cd();
    polymarker->Draw("");
    wcLPCanvas->Update();}

  if( wcLMCanvas ){
    wcLMCanvas->cd();
    polymarker->Draw("");
    wcLMCanvas->Update();}

  delete [] u_ring;
  delete [] v_ring;

  return;
}
 
void WCSimDisplayAB::MakeLegendRECO()
{  
  if( wcRecoLegend ) return;

  wcRecoLegend = new TLegend(0.19,0.20,0.41,0.37);
  wcRecoLegend->SetLineColor(kWhite);
  wcRecoLegend->SetFillColor(kWhite);
  wcRecoLegend->SetFillStyle(0);

  TLegend* legend = wcRecoLegend;
  TMarker* marker = 0;
  TLine* line = 0;

  // true vertex
  marker = new TMarker(0.0,0.0,29);
  marker->SetMarkerSize(2.5);
  marker->SetMarkerColor(2); 
  legend->AddEntry(marker,"True Vertex","p");
  legDigits.push_back(marker);

  // reconstructed vertex
  marker = new TMarker(0.0,0.0,29);
  marker->SetMarkerSize(2.5);
  marker->SetMarkerColor(1); 
  legend->AddEntry(marker,"Reco Vertex","p");
  legDigits.push_back(marker);

  // true line
  line = new TLine(0.0,0.0,1.0,1.0);
  line->SetLineColor(2);
  line->SetLineWidth(3);
  legend->AddEntry(line,"True Ring","l");
  legRings.push_back(line);

  // reconstructed line
  line = new TLine(0.0,0.0,1.0,1.0);
  line->SetLineColor(1);
  line->SetLineWidth(3);
  legend->AddEntry(line,"Reco Ring","l");
  legRings.push_back(line);

  return;
}

void WCSimDisplayAB::PrintDisplay()
{
  // print GIF
  if( fPrintGIF ) this->PrintDisplayGIF();

  // print EPS
  if( fPrintEPS ) this->PrintDisplayEPS();
}

void WCSimDisplayAB::PrintDisplayEPS()
{
  // print space display
  if( wcCanvas ){
    TString outfile("wcdisplay");
    outfile.Append(".");
    outfile+=fRunNumber;
    outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".eps");
    wcCanvas->SaveAs(outfile.Data());
  }  

  // print time display
  if( wcTimeCanvas ){
    TString outfile("wcdisplay");
    outfile.Append(".");
    outfile+=fRunNumber;
    outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".timing.eps");
    wcTimeCanvas->SaveAs(outfile.Data());
  }
  // print time residual display
  if( wcdTCanvas ){
    TString outfile("wcdisplay");
    outfile.Append(".");
    outfile+=fRunNumber;
    outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".timing.eps");
    wcdTCanvas->SaveAs(outfile.Data());
  }
  //erika
  if( wcLPCanvas ){
    TString outfile("wcdisplay"); outfile.Append(".");
    outfile+=fRunNumber; outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".photon.eps");
    wcLPCanvas->SaveAs(outfile.Data());
  }
  if( wcLMCanvas ){
    TString outfile("wcdisplay"); outfile.Append(".");
    outfile+=fRunNumber; outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".muon.eps");
    wcLMCanvas->SaveAs(outfile.Data());
  }



}

void WCSimDisplayAB::PrintDisplayGIF()
{
  // print space display
  if( wcCanvas ){
    TString outfile("wcdisplay");
    outfile.Append(".");
    outfile+=fRunNumber;
    outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".gif");
    wcCanvas->SaveAs(outfile.Data());
  }  

  // print time display
  if( wcTimeCanvas ){
    TString outfile("wcdisplay");
    outfile.Append(".");
    outfile+=fRunNumber;
    outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".time.gif");
    wcTimeCanvas->SaveAs(outfile.Data());
  }
  // print time residual display
  if( wcdTCanvas ){
    TString outfile("wcdisplay");
    outfile.Append(".");
    outfile+=fRunNumber;
    outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".timeResisual.gif");
    wcdTCanvas->SaveAs(outfile.Data());
  }

 //erika
  if( wcLPCanvas ){
    TString outfile("wcdisplay"); outfile.Append(".");
    outfile+=fRunNumber; outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".photon.gif");
    wcLPCanvas->SaveAs(outfile.Data());
  }
  if( wcLMCanvas ){
    TString outfile("wcdisplay"); outfile.Append(".");
    outfile+=fRunNumber; outfile.Append(".");
    outfile+=fEventNumber;
    outfile.Append(".muon.gif");
    wcLMCanvas->SaveAs(outfile.Data());
  }






}

Int_t WCSimDisplayAB::QPEtoCOL(Double_t Q)
{
  Int_t colourCode = kWhite; 

  if( Q<0.8 )             colourCode = kYellow-7;
  if( Q>=0.8 && Q<1.5 )   colourCode = kCyan-7;
  if( Q>=1.5 && Q<2.5 )   colourCode = kCyan+1;
  if( Q>=2.5 && Q<5.0 )   colourCode = kBlue-4;
  if( Q>=5.0 && Q<10.0 )  colourCode = kBlue+1;
  if( Q>=10.0 && Q<15.0 ) colourCode = kMagenta+1;
  if( Q>=15.0 && Q<20.0 ) colourCode = kMagenta+2;
  if( Q>=20.0 && Q<30.0 ) colourCode = kRed-4;
  if( Q>=30.0 )           colourCode = kRed;

  return colourCode;
}

void WCSimDisplayAB::MakeLegendQPE()
{
  if( wcLegend ) return;

  wcLegend = new TLegend(0.19,0.70,0.40,0.90);
  wcLegend->SetLineColor(kWhite);
  wcLegend->SetFillColor(kWhite);
  wcLegend->SetFillStyle(0);

  TLegend* legend = wcLegend;
  TMarker* marker = 0;
  Int_t colourCode = 0;

  colourCode = kYellow-7;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.75);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"<0.8 PEs","p");
  legDigits.push_back(marker);

  colourCode = kCyan-7;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.75);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"0.8 - 1.5 PEs","p");
  legDigits.push_back(marker);

  colourCode = kCyan+1;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.75);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"1.5 - 2.5 PEs","p");  
  legDigits.push_back(marker);

  colourCode = kBlue-4;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.75);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"2.5 - 5.0 PEs","p");  
  legDigits.push_back(marker);

  colourCode = kBlue+1;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.75);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"5.0 - 10.0 PEs","p");  
  legDigits.push_back(marker);

  colourCode = kMagenta+1;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.75);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"10.0 - 15.0 PEs","p");
  legDigits.push_back(marker);

  colourCode = kMagenta+2;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.75);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"15.0 - 20.0 PEs","p");  
  legDigits.push_back(marker);

  colourCode = kRed-4;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.75);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"20.0 - 30.0 PEs","p");  
  legDigits.push_back(marker);

  colourCode = kRed;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.75);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,">30.0 PEs","p");
  legDigits.push_back(marker);

  return;
}

Int_t WCSimDisplayAB::TIMEtoCOL(Double_t T)
{
  Int_t colourCode = kWhite; 

  Double_t fBaseT = 0.0;

  if( T-fBaseT<-10.0 )                      colourCode = 98;
  if( T-fBaseT>=-10.0  && T-fBaseT<10.0 )   colourCode = 98;
  if( T-fBaseT>=10.0   && T-fBaseT<30.0 )   colourCode = 94;
  if( T-fBaseT>=30.0   && T-fBaseT<50.0 )   colourCode = 89;
  if( T-fBaseT>=50.0   && T-fBaseT<100.0 )  colourCode = 85;
  if( T-fBaseT>=100.0  && T-fBaseT<150.0 )  colourCode = 80;
  if( T-fBaseT>=150.0  && T-fBaseT<200.0 )  colourCode = 75;
  if( T-fBaseT>=200.0  && T-fBaseT<300.0 )  colourCode = 70;
  if( T-fBaseT>=300.0  && T-fBaseT<450.0 )  colourCode = 65;
  if( T-fBaseT>=450.0  && T-fBaseT<650.0 )  colourCode = 55;
  if( T-fBaseT>=650.0 )                     colourCode = 55; 
  
  return colourCode;
}

Int_t WCSimDisplayAB::dTtoCOL(Double_t T)
{
  Int_t colourCode = kWhite; 

  Double_t fBaseT = 0.0;

  if( T-fBaseT<-10.0 )                      colourCode = 98;
  if( T-fBaseT>=-5.0  && T-fBaseT<0.0 )   colourCode = 98;
  if( T-fBaseT>=0.0   && T-fBaseT<0.5 )   colourCode = 94;
  if( T-fBaseT>=0.5   && T-fBaseT<1.0 )   colourCode = 89;
  if( T-fBaseT>=1.0   && T-fBaseT<2.0 )  colourCode = 85;
  if( T-fBaseT>=2.0  && T-fBaseT<5.0 )  colourCode = 80;
  if( T-fBaseT>=5.0  && T-fBaseT<10.0 )  colourCode = 75;
  if( T-fBaseT>=10.0  && T-fBaseT<18.0 )  colourCode = 70;
  if( T-fBaseT>=18.0  && T-fBaseT<31.0 )  colourCode = 65;
  if( T-fBaseT>=31.0  && T-fBaseT<50.0 )  colourCode = 55;
  if( T-fBaseT>=50.0 )                     colourCode = 55; 
  
  return colourCode;
}

void WCSimDisplayAB::MakeLegendTIME()
{
  if( wcTimeLegend ) return;

  wcTimeLegend = new TLegend(0.19,0.70,0.40,0.90);
  wcTimeLegend->SetLineColor(kWhite);
  wcTimeLegend->SetFillColor(kWhite);
  wcTimeLegend->SetFillStyle(0);

  TLegend* legend = wcTimeLegend;
  TMarker* marker = 0;
  Int_t colourCode = 0;

  colourCode = 98;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"<10 ns","p");
  legDigits.push_back(marker);

  colourCode = 94;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"10 - 20 ns","p");
  legDigits.push_back(marker);

  colourCode = 89;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"20 - 40 ns","p");
  legDigits.push_back(marker);

  colourCode = 85;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"40 - 90 ns","p");
  legDigits.push_back(marker);

  colourCode = 80;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"90 - 140 ns","p");
  legDigits.push_back(marker);

  colourCode = 75;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"140 - 190 ns","p");
  legDigits.push_back(marker);

  colourCode = 70;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"190 - 290 ns","p");
  legDigits.push_back(marker);

  colourCode = 65;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"290 - 440 ns","p");
  legDigits.push_back(marker);

  colourCode = 55;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,">440 ns","p");
  legDigits.push_back(marker);

  return;
}

void WCSimDisplayAB::MakeLegenddT() //......TX
{
  if( wcdTLegend ) return;

  wcdTLegend = new TLegend(0.19,0.70,0.40,0.90);
  wcdTLegend->SetLineColor(kWhite);
  wcdTLegend->SetFillColor(kWhite);
  wcdTLegend->SetFillStyle(0);

  TLegend* legend = wcdTLegend;
  TMarker* marker = 0;
  Int_t colourCode = 0;

  colourCode = 98;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"<0 ns","p");
  legDigits.push_back(marker);

  colourCode = 94;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"0 - 0.5 ns","p");
  legDigits.push_back(marker);

  colourCode = 89;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"0.5 - 1.0 ns","p");
  legDigits.push_back(marker);

  colourCode = 85;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"1.0 - 2.0 ns","p");
  legDigits.push_back(marker);

  colourCode = 80;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"2.0 - 5.0 ns","p");
  legDigits.push_back(marker);

  colourCode = 75;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"5.0 - 10.0 ns","p");
  legDigits.push_back(marker);

  colourCode = 70;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"10.0 - 18.0 ns","p");
  legDigits.push_back(marker);

  colourCode = 65;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"18.0 - 31.0 ns","p");
  legDigits.push_back(marker);

  colourCode = 55;
  marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,">31.0 ns","p");
  legDigits.push_back(marker);

  return;
}



//erika

Int_t WCSimDisplayAB::LPtoCOL(Double_t T)
{
  Int_t colourCode = kWhite; 

  Double_t fBaseT = 0.0;

  if( T-fBaseT<-10.0 )                      colourCode = 98;
  if( T-fBaseT>=-10.0  && T-fBaseT<550.0 )   colourCode = 98;
  if( T-fBaseT>=550.0   && T-fBaseT<1100.0 )   colourCode = 94;
  if( T-fBaseT>=1100.0   && T-fBaseT<1650.0 )   colourCode = 89;
  if( T-fBaseT>=1650.0   && T-fBaseT<2200.0 )  colourCode = 85;
  if( T-fBaseT>=2200.0  && T-fBaseT<2750.0 )  colourCode = 80;
  if( T-fBaseT>=2750.0  && T-fBaseT<3300.0 )  colourCode = 75;
  if( T-fBaseT>=3300.0  && T-fBaseT<3850.0 )  colourCode = 70;
  if( T-fBaseT>=3850.0  && T-fBaseT<4400.0 )  colourCode = 65;
  if( T-fBaseT>=4400.0  && T-fBaseT<4950.0 )  colourCode = 55;
  if( T-fBaseT>=4950.0 )                     colourCode = 55; 
  
  return colourCode;
}
Int_t WCSimDisplayAB::LMtoCOL(Double_t T)
{
  Int_t colourCode = kWhite; 

  Double_t fBaseT = 0.0;

  if( T-fBaseT<-500.0 )                      colourCode = 98;
  if( T-fBaseT>=-500.0  && T-fBaseT<-250.0 )   colourCode = 98;
  if( T-fBaseT>=-250.0   && T-fBaseT<0.0 )   colourCode = 94;
  if( T-fBaseT>=0.0   && T-fBaseT<100.0 )   colourCode = 89;
  if( T-fBaseT>=100.0   && T-fBaseT<200.0 )  colourCode = 85;
  if( T-fBaseT>=200.0  && T-fBaseT<300.0 )  colourCode = 80;
  if( T-fBaseT>=300.0  && T-fBaseT<400.0 )  colourCode = 75;
  if( T-fBaseT>=400.0  && T-fBaseT<500.0 )  colourCode = 70;
  if( T-fBaseT>=500.0  && T-fBaseT<750.0 )  colourCode = 65;
  if( T-fBaseT>=750.0  && T-fBaseT<1000.0 )  colourCode = 55;
  if( T-fBaseT>=1000.0 )                     colourCode = 55; 
  
  return colourCode;
}



void WCSimDisplayAB::MakeLegendLP()
{
  if( wcLPLegend ) return;
  wcLPLegend = new TLegend(0.19,0.70,0.40,0.90);
  wcLPLegend->SetLineColor(kWhite);
  wcLPLegend->SetFillColor(kWhite);
  wcLPLegend->SetFillStyle(0);

  TLegend* legend = wcLPLegend;
  TMarker* marker = 0;
  Int_t colourCode = 0;

  colourCode = 98; marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"<550 cm","p");legDigits.push_back(marker);
  colourCode = 94;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"550 - 1100 cm","p");legDigits.push_back(marker);
  colourCode = 89;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"1100 - 1650 cm","p");legDigits.push_back(marker);
  colourCode = 85;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"1650 - 2200 cm","p");legDigits.push_back(marker);
  colourCode = 80;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"2200 - 2750 cm","p");legDigits.push_back(marker);
  colourCode = 75;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"2750 - 3300 cm","p");legDigits.push_back(marker);
  colourCode = 70;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"3300 - 3850 cm","p");legDigits.push_back(marker);
  colourCode = 65;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"3850 - 4400 cm","p");legDigits.push_back(marker);
  colourCode = 55;marker = new TMarker(0.0,0.0,20);marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,">4400 cm","p");legDigits.push_back(marker);

  return;
}




void WCSimDisplayAB::MakeLegendLM()
{
  if( wcLMLegend ) return;
  wcLMLegend = new TLegend(0.19,0.70,0.40,0.90);
  wcLMLegend->SetLineColor(kWhite);
  wcLMLegend->SetFillColor(kWhite);
  wcLMLegend->SetFillStyle(0);

  TLegend* legend = wcLMLegend;
  TMarker* marker = 0;
  Int_t colourCode = 0;

  colourCode = 98; marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"<-250 cm","p");legDigits.push_back(marker);
  colourCode = 94;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"-250 - 0 cm","p");legDigits.push_back(marker);
  colourCode = 89;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"0 - 100 cm","p");legDigits.push_back(marker);
  colourCode = 85;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"100 - 200 cm","p");legDigits.push_back(marker);
  colourCode = 80;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"200 - 300 cm","p");legDigits.push_back(marker);
  colourCode = 75;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"300 - 400 cm","p");legDigits.push_back(marker);
  colourCode = 70;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"400 - 500 cm","p");legDigits.push_back(marker);
  colourCode = 65;marker = new TMarker(0.0,0.0,20);
  marker->SetMarkerSize(0.5);marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,"500 - 750 cm","p");legDigits.push_back(marker);
  colourCode = 55;marker = new TMarker(0.0,0.0,20);marker->SetMarkerSize(0.5);
  marker->SetMarkerColor(colourCode); 
  legend->AddEntry(marker,">750 cm","p");legDigits.push_back(marker);

  return;
}
