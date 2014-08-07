#include "WCSimTResidPDF.hh"
#include "WCSimHistos.hh"

#include <cassert>
#include <iostream>
#include <string>

ClassImp(WCSimHistos)

//......................................................................
static WCSimHistos* fgHistos = 0;

WCSimHistos* WCSimHistos::Instance()
{
  if( !fgHistos ){
  //std::cout <<"test 0 " << std::endl;
    fgHistos = new WCSimHistos();
  }

  if( !fgHistos ){
    assert(fgHistos);
  }

  if( fgHistos ){

  }

  return fgHistos;
}

//......................................................................

WCSimHistos::WCSimHistos()
{

  hChromHist = new TH3D("chromHist","",1000,0.,100.,1200,-10.,50.,60,0.,3.);

}

//......................................................................

WCSimHistos::~WCSimHistos()
{
  
}

//......................................................................

//.....................................................................
//Ioana...make a table to store the chromaticPDF values
void WCSimHistos::MakeChrom3DHisto(Int_t Ndist,Int_t Ntime,std::string outFile)
{

  std::string addNameD[10] = {"0","1","2","3","4","5","6","7","8","9"};
  std::string addNameT[6] = {"0","1","2","3","4","5"};

  rootfile = new TFile(outFile.c_str(),"UPDATE");

  //loop over the distances
  for (Double_t i=Ndist*10; i<(Ndist+1)*10.; i+=0.1){//distances (in m)
      //loop over the time residual
      for (Double_t j=-10.+(Ntime*10); j<-10+(Ntime+1)*10.; j+=0.01) {//time residual
         //loop over the resolution   
	for (Double_t k=0; k<3.; k+=0.05) {//PMT resolution (in ns)
			
		Int_t x = hChromHist->GetXaxis()->FindFixBin(i);
		Int_t y = hChromHist->GetYaxis()->FindFixBin(j);
		Int_t z = hChromHist->GetZaxis()->FindFixBin(k); 
		
		//!!!! make sure distance is in cm !!!
		hChromHist -> SetBinContent(hChromHist->GetBin(x,y,z),WCSimTResidPDF::Instance()->MakeChromPeakPDF(j,i*100,k));
		
	}//end loop over PMT resolutions
      }//end loop over time residuals
      
      std::cout << "distance iteration = " << i << std::endl;
	
  }//end loop over distances
  
  std::string histName = "chromHist_"+addNameD[Ndist]+"_"+addNameT[Ntime];
  hChromHist->SetName(histName.c_str());
  
  rootfile->cd();
  hChromHist->Write();
  rootfile->Close();
}

//////////////////////////////////////////////////////////////////////////////////

