#include "WCSimDisplayCustom.hh"

#include "WCSimDisplayFactory.hh"
#include "WCSimDisplay.hh"

#include "WCSimRecoFactory.hh"
#include "WCSimReco.hh"
#include "WCSimRecoEvent.hh"

#include "WCSimGeometry.hh"
#include "WCSimInterface.hh"

#include <iostream>
#include <string>
#include <cassert>

ClassImp(WCSimDisplayCustom)

WCSimDisplayCustom::WCSimDisplayCustom() :  
  fRootStyle(0),
 //  fControlCanvas(0),
 //  buttonStart(0),
//   buttonNext(0),
//   buttonPrevious(0),
//   buttonGoTo(0),
//   buttonPrint(0),
//   buttonQuit(0),
  fCounter(-1),
  fReco(0),
  fRecoEvent(0),
  fTrueEvent(0),
  fDisplayRecoClusters(0),
  fDisplayRecoEvent(0),
  fDisplayTrueEvent(0),
  fPulseHeightCut(0.0),
  fPrintGIF(0),
  fPrintEPS(0),
  fDisplayReady(0)
{
  this->Initialize(); 
}

WCSimDisplayViewer::~WCSimDisplayViewer()
{  
 //  if(fControlCanvas) delete fControlCanvas;
//   if(buttonStart) delete buttonStart;
//   if(buttonNext) delete buttonNext;
//   if(buttonPrevious) delete buttonPrevious;
//   if(buttonGoTo) delete buttonGoTo;
//   if(buttonPrint) delete buttonPrint;
//   if(buttonQuit) delete buttonQuit;

  if(fReco) delete fReco;
}

void WCSimDisplayViewer::RootStyle()
{
  if( fRootStyle ) return;

  std::cout << " *** WCSimDisplayCustom::ForceRootStyle() *** " << std::endl;

  // create new TStyle
  fRootStyle = new  TStyle("My Style", "");

  // set the background color to white
  fRootStyle->SetFillColor(10);
  fRootStyle->SetFrameFillColor(10);
  fRootStyle->SetCanvasColor(10);
  fRootStyle->SetPadColor(10);
  fRootStyle->SetTitleFillColor(0);
  fRootStyle->SetStatColor(10);

  // don't put a colored frame around the plots
  fRootStyle->SetFrameBorderMode(0);
  fRootStyle->SetCanvasBorderMode(0);
  fRootStyle->SetPadBorderMode(0);
  fRootStyle->SetLegendBorderSize(0);

  // use the primary color palette
  fRootStyle->SetPalette(1,0);

  // set the default line color for a histogram to be black
  fRootStyle->SetHistLineColor(kBlack);

  // set the default line color for a fit function to be red
  fRootStyle->SetFuncColor(kRed);

  // make the axis labels black
  fRootStyle->SetLabelColor(kBlack,"xyz");

  // set the default title color to be black
  fRootStyle->SetTitleColor(kBlack);

  // set the margins
  fRootStyle->SetPadBottomMargin(0.18);
  fRootStyle->SetPadTopMargin(0.08);
  fRootStyle->SetPadRightMargin(0.08);
  fRootStyle->SetPadLeftMargin(0.17);

  // set axis label and title text sizes
  fRootStyle->SetLabelFont(42,"xyz");
  fRootStyle->SetLabelSize(0.06,"xyz");
  fRootStyle->SetLabelOffset(0.015,"xyz");
  fRootStyle->SetTitleFont(42,"xyz");
  fRootStyle->SetTitleSize(0.07,"xyz");
  fRootStyle->SetTitleOffset(1.1,"yz");
  fRootStyle->SetTitleOffset(1.0,"x");
  fRootStyle->SetStatFont(42);
  fRootStyle->SetStatFontSize(0.07);
  fRootStyle->SetTitleBorderSize(0);
  fRootStyle->SetStatBorderSize(0);
  fRootStyle->SetTextFont(42);

  // set line widths
  fRootStyle->SetFrameLineWidth(2);
  fRootStyle->SetFuncWidth(2);

  // set the number of divisions to show
  fRootStyle->SetNdivisions(506, "xy");

  // turn off xy grids
  fRootStyle->SetPadGridX(0);
  fRootStyle->SetPadGridY(0);

  // set the tick mark style
  fRootStyle->SetPadTickX(1);
  fRootStyle->SetPadTickY(1);

  // turn off stats
  fRootStyle->SetOptStat(0);

  // marker settings
  fRootStyle->SetMarkerStyle(20);
  fRootStyle->SetMarkerSize(1.2);
  fRootStyle->SetLineWidth(1);

  // done
  fRootStyle->cd();
  gROOT->ForceStyle();
  gStyle->ls();

  return;
}

void WCSimDisplayCustom::Initialize()
{
  std::cout << " *** WCSimDisplayCustom::Initialize() *** " << std::endl;
  // ROOT style
  this->RootStyle();
}


void WCSimDisplayCustom::SetPulseHeightCut(Double_t cut)
{
  fPulseHeightCut = cut;

  for( UInt_t n=0; n<fDisplayList.size(); n++ ){
    WCSimDisplay* myDisplay = (WCSimDisplay*)(fDisplayList.at(n));
    myDisplay->SetPulseHeightCut(fPulseHeightCut);
  }
  return;
}
  
void WCSimDisplayCustom::PrintGIF(Bool_t yesno)
{ 
  fPrintGIF = yesno; 
  for( UInt_t n=0; n<fDisplayList.size(); n++ ){
    WCSimDisplay* myDisplay = (WCSimDisplay*)(fDisplayList.at(n));
    myDisplay->PrintGIF(fPrintGIF);
  }
  return;
}
  
void WCSimDisplayCustom::PrintEPS(Bool_t yesno)
{ 
  fPrintEPS = yesno; 
  for( UInt_t n=0; n<fDisplayList.size(); n++ ){
    WCSimDisplay* myDisplay = (WCSimDisplay*)(fDisplayList.at(n));
    myDisplay->PrintEPS(fPrintEPS);
  }
  return;
}

void WCSimDisplayCustom::BuildDisplay()
{
  std::cout << " *** WCSimDisplayCustom::BuildDisplay() *** " << std::endl;
  // Building Displays
       

WCSimDisplay* myDisplay = WCSimDisplayFactory::Instance()->MakeDisplay(displayname);

      if( myDisplay ){
        myDisplay->SetPulseHeightCut(fPulseHeightCut);
        myDisplay->PrintGIF(fPrintGIF);
        myDisplay->PrintEPS(fPrintEPS);
        fDisplayList.push_back(myDisplay);
        fDisplayReady = 1;
      }
      else{
        std::cout << " --- no displays available: EXIT --- " << std::endl;
        assert(myDisplay);
      }
    }
  }

  // Building Reconstruction
  if( !fReco ){
    fReco = WCSimRecoFactory::Instance()->MakeReco();  
  }

  return;
}

void WCSimDisplayCustom::DisplayEvent(Int_t entry)
{ 
  if( !fDisplayReady ){
    std::cout << " --- starting display --- " << std::endl;
    this->BuildDisplay();
  }

  if( fDisplayReady ){
    this->UpdateDisplay(entry);
  }
}

void WCSimDisplayCustom::UpdateDisplay(Int_t entry)
{
  std::cout << " --- new event --- " << std::endl;

  WCSimInterface::LoadEvent(entry);

  if( WCSimInterface::TouchEvent() ){
    
    // create new event    
    fRecoEvent = WCSimInterface::RecoEvent();
    fTrueEvent = WCSimInterface::TrueEvent();

    // get run/event/trigger
    fRunNum = fRecoEvent->GetRun();
    fEventNum = fRecoEvent->GetEvent();
    fTriggerNum = fRecoEvent->GetTrigger();

    // run reconstruction
    if( fDisplayRecoClusters
     || fDisplayRecoEvent ){
      fReco->RunFilter(fRecoEvent);
    }

    if( fDisplayRecoEvent ){
      fReco->RunRecoVertex(fRecoEvent);
      fReco->RunRecoRings(fRecoEvent);
    } 
    
    if( fApplyCuts ){
      fReco->RunFilter(fRecoEvent);
    }

    // run displays  
    std::cout << " *** WCSimDisplayCustom::UpdateDisplay(...) *** " << std::endl;
    std::cout << "  Displaying Entry [" << entry << "] " << std::endl;
    std::cout << "  Displaying Event: " << fRunNum << "/" << fEventNum << "/" << fTriggerNum << std::endl;
    for( UInt_t n=0; n<fDisplayList.size(); n++ ){
      WCSimDisplay* myDisplay = (WCSimDisplay*)(fDisplayList.at(n));

      if( fDisplayRecoClusters ){
        myDisplay->DrawCleanDisplay(fRecoEvent);
      }
      else{
        myDisplay->DrawDisplay(fRecoEvent);
      }

      if( fDisplayTrueEvent ){
        myDisplay->DrawTrueEvent(fTrueEvent);
      }     

      if( fDisplayRecoEvent ){
        myDisplay->DrawRecoEvent(fRecoEvent);
      }
    }

    std::cout << "  Displaying Entry [" << entry << "]  DONE! " << std::endl; 
  }

  return;

}

