#include "SandBoxDigitizer.hh"
#include <vector>
// for memset
#include <math.h>
#include <cstring>
#include <iostream>
#include "WCSimGeometry.hh"

#include "WCSimRecoEvent.hh"
#include "WCSimRecoDigit.hh"

// changed from 940 (april 2005) by MF
// 960 is unsuitable

const double SandBoxDigitizer::offset = 950.0 ; // ns        // NOTE!!!!!! I AM NOT USING THIS OFFSET FOR NOW
//const double SandBoxDigitizer::offset = 950.0 ; // ns
const double SandBoxDigitizer::pmtgate = 200.0 ; // ns
const double SandBoxDigitizer::eventgateup = 950.0 ; // ns
const double SandBoxDigitizer::eventgatedown = -400.0 ; // ns
const double SandBoxDigitizer::LongTime = 100000.0 ; // ns
// value in skdetsim
const int SandBoxDigitizer::GlobalThreshold = 25 ; // # hit PMTs
//const int SandBoxDigitizer::GlobalThreshold = 12 ; // # hit PMTs
// try to trigger early to reduce the width. 
//const int SandBoxDigitizer::GlobalThreshold = 10 ; // # hit PMTs

// special version -- based on a suggestion by K. Okumura
// M F, april 05
// use skdetsim's 1pe distribution

const double SandBoxDigitizer::PMTDarkRate = 4.0; // kHz

/* GC: original values from rn1pe.F (apdetsim) */ 
const Float_t qpe0[501] = {
    // 1
      0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000129, 0.000754, 0.004060, 0.028471,
    // 2
      0.068449, 0.115679, 0.164646, 0.203466, 0.235631,
      0.262351, 0.282064, 0.303341, 0.320618, 0.338317,
      0.357825, 0.371980, 0.385820, 0.398838, 0.413595,
      0.428590, 0.444387, 0.461685, 0.482383, 0.502369,
      0.520779, 0.540011, 0.559293, 0.579354, 0.599337,
      0.619580, 0.639859, 0.659807, 0.679810, 0.699620,
      0.718792, 0.737382, 0.755309, 0.772042, 0.788232,
      0.803316, 0.817861, 0.831148, 0.844339, 0.855532,
      0.866693, 0.876604, 0.886067, 0.894473, 0.902150,
      0.909515, 0.915983, 0.922050, 0.927418, 0.932492,
    // 3 
      0.936951, 0.940941, 0.944660, 0.948004, 0.951090,
      0.953833, 0.956576, 0.958886, 0.961134, 0.963116,
      0.964930, 0.966562, 0.968008, 0.969424, 0.970687,
      0.971783, 0.972867, 0.973903, 0.974906, 0.975784,
      0.976632, 0.977438, 0.978190, 0.978891, 0.979543,
      0.980124, 0.980666, 0.981255, 0.981770, 0.982227,
      0.982701, 0.983146, 0.983566, 0.983975, 0.984357,
      0.984713, 0.985094, 0.985404, 0.985739, 0.986049,
      0.986339, 0.986630, 0.986922, 0.987176, 0.987431,
      0.987655, 0.987922, 0.988173, 0.988414, 0.988639,
    // 4  
      0.988856, 0.989065, 0.989273, 0.989475, 0.989662,
      0.989828, 0.990007, 0.990172, 0.990327, 0.990497,
      0.990645, 0.990797, 0.990981, 0.991135, 0.991272,
      0.991413, 0.991550, 0.991673, 0.991805, 0.991928,
      0.992063, 0.992173, 0.992296, 0.992406, 0.992514,
      0.992632, 0.992733, 0.992837, 0.992954, 0.993046,
      0.993148, 0.993246, 0.993354, 0.993458, 0.993549,
      0.993656, 0.993744, 0.993836, 0.993936, 0.994033,
      0.994134, 0.994222, 0.994307, 0.994413, 0.994495,
      0.994572, 0.994659, 0.994739, 0.994816, 0.994886,
    // 5  
      0.994970, 0.995032, 0.995110, 0.995178, 0.995250,
      0.995321, 0.995383, 0.995464, 0.995532, 0.995609,
      0.995674, 0.995750, 0.995821, 0.995889, 0.995952,
      0.996010, 0.996071, 0.996153, 0.996218, 0.996283,
      0.996335, 0.996384, 0.996431, 0.996484, 0.996537,
      0.996597, 0.996655, 0.996701, 0.996745, 0.996802,
      0.996860, 0.996917, 0.996962, 0.997014, 0.997079,
      0.997114, 0.997165, 0.997204, 0.997250, 0.997295,
      0.997335, 0.997379, 0.997418, 0.997454, 0.997488,
      0.997530, 0.997573, 0.997606, 0.997648, 0.997685,
    // 6  
      0.997725, 0.997762, 0.997795, 0.997835, 0.997866,
      0.997898, 0.997941, 0.997966, 0.997997, 0.998039,
      0.998065, 0.998104, 0.998128, 0.998153, 0.998179,
      0.998205, 0.998223, 0.998254, 0.998293, 0.998319,
      0.998346, 0.998374, 0.998397, 0.998414, 0.998432,
      0.998456, 0.998482, 0.998511, 0.998532, 0.998553,
      0.998571, 0.998594, 0.998614, 0.998638, 0.998669,
      0.998693, 0.998715, 0.998743, 0.998762, 0.998793,
      0.998812, 0.998834, 0.998857, 0.998872, 0.998888,
      0.998904, 0.998926, 0.998946, 0.998963, 0.998983,
    // 7  
      0.999007, 0.999027, 0.999044, 0.999064, 0.999079,
      0.999096, 0.999120, 0.999133, 0.999152, 0.999160,
      0.999174, 0.999188, 0.999206, 0.999221, 0.999234,
      0.999248, 0.999263, 0.999276, 0.999286, 0.999300,
      0.999313, 0.999321, 0.999331, 0.999347, 0.999356,
      0.999369, 0.999381, 0.999394, 0.999402, 0.999415,
      0.999427, 0.999433, 0.999446, 0.999458, 0.999472,
      0.999484, 0.999499, 0.999513, 0.999522, 0.999532,
      0.999540, 0.999550, 0.999559, 0.999567, 0.999574,
      0.999588, 0.999599, 0.999613, 0.999618, 0.999627,
    // 8  
      0.999635, 0.999639, 0.999652, 0.999662, 0.999667,
      0.999671, 0.999678, 0.999682, 0.999688, 0.999693,
      0.999698, 0.999701, 0.999706, 0.999711, 0.999718,
      0.999722, 0.999727, 0.999732, 0.999737, 0.999740,
      0.999746, 0.999750, 0.999754, 0.999763, 0.999766,
      0.999769, 0.999774, 0.999780, 0.999784, 0.999788,
      0.999796, 0.999803, 0.999807, 0.999809, 0.999815,
      0.999820, 0.999827, 0.999830, 0.999833, 0.999833,
      0.999836, 0.999839, 0.999842, 0.999845, 0.999850,
      0.999853, 0.999857, 0.999860, 0.999865, 0.999870,
    // 9  
      0.999873, 0.999877, 0.999880, 0.999882, 0.999883,
      0.999886, 0.999888, 0.999889, 0.999895, 0.999896,
      0.999897, 0.999901, 0.999902, 0.999905, 0.999907,
      0.999907, 0.999909, 0.999911, 0.999911, 0.999912,
      0.999913, 0.999914, 0.999917, 0.999919, 0.999921,
      0.999923, 0.999927, 0.999929, 0.999931, 0.999933,
      0.999936, 0.999942, 0.999942, 0.999944, 0.999947,
      0.999947, 0.999948, 0.999949, 0.999952, 0.999955,
      0.999957, 0.999957, 0.999961, 0.999962, 0.999963,
      0.999963, 0.999963, 0.999964, 0.999965, 0.999965,
    // 10
      0.999965, 0.999965, 0.999966, 0.999968, 0.999969,
      0.999971, 0.999972, 0.999972, 0.999973, 0.999975,
      0.999975, 0.999975, 0.999975, 0.999975, 0.999975,
      0.999975, 0.999979, 0.999979, 0.999980, 0.999982,
      0.999983, 0.999985, 0.999986, 0.999987, 0.999987,
      0.999988, 0.999989, 0.999989, 0.999989, 0.999989,
      0.999990, 0.999990, 0.999992, 0.999993, 0.999994,
      0.999994, 0.999994, 0.999994, 0.999994, 0.999995,
      0.999995, 0.999995, 0.999996, 0.999996, 0.999996,
      0.999996, 0.999998, 0.999999, 1.000000, 1.000000,
    // Dummy element for noticing if the loop reached the end of the array
      0.0
};


// extern "C" void skrn1pe_(float* );
//extern "C" void rn1pe_(float* ); // 1Kton

SandBoxDigitizer::SandBoxDigitizer(WCSimRootTrigger* mTrigger, TString name)
{
  WCSimRecoEvent::Instance()->Reset();
  
  //DigitsCollection = new std::vector<WCSimRecoDigit*>; //....TX

  _isPMT=true;
  _isGated=true;
  _smearCharge=true;
  _smearTimeMCP=true;

  _simpleTimeResolution=1.0;

  timehist = new TH1D("th","th", 1000, 1., 5000.);
  tdiffhist = new TH1D("td","td",1500, -10.,20.);
  sdiffhist = new TH1D("sd","sd",1000, -100.,100.);
  qhist = new TH1D("qd","qd",1000,0.,10.);

  //  TString colName = "WCDigitizedCollection";
  //  collectionName.push_back(colName);  
  DigiHitMap.clear();
  _theTrigger=mTrigger;
  _theRand = new TRandom3(12313);
}

SandBoxDigitizer::~SandBoxDigitizer() 
{
  //delete DigitsCollection; 
  //this->ResetRecoEvent();
  ;
}

/*void SandBoxDigitizer::ResetRecoEvent()
{
  // Reset 
  // =====
  WCSimRecoEvent::Instance()->Reset();

  // delete list of digits
  // =====================
  for( UInt_t i=0; i<DigitsCollection->size(); i++ ){
    delete (WCSimRecoDigit*)(DigitsCollection->at(i));
  }

  // clear list of digits
  // ====================
  DigitsCollection->clear();

  return;
}*/

TH1D* SandBoxDigitizer::getdiagnostic(Int_t i)
{
  if(i==0){
    return timehist;
  } else if(i==1){
    return tdiffhist;
  } else if(i==2){
    return sdiffhist;
  } else if(i==3){
    return qhist;
  }
  
}

Double_t SandBoxDigitizer::rn1pe(){
  Double_t random = _theRand->Rndm();
  Double_t random2 = _theRand->Rndm();
  Int_t i;
  for(i = 0; i < 501; i++){
    if (random <= qpe0[i]) break;
  }
  if(i==500)
    random = _theRand->Rndm();

  return (Double_t(i-50) + random2)/22.83;
} 


void SandBoxDigitizer::SetPMT(Double_t tres, Double_t gate, Bool_t smearQ, Bool_t isgated)
{  
  _isPMT=true;
  _simpleTimeResolution=tres;
  _smearCharge = smearQ;
  _isGated = isgated;

}

void SandBoxDigitizer::SetMCP(Double_t tres, Double_t sres)
{
  _isPMT=false;

  _simpleTimeResolution=tres;
  if(tres==0.0){
    _smearTimeMCP=true;
  }
  _simpleSpaceResolution=sres;
  if(sres==0.0){
    _smearSpaceMCP=true;
  }
}

void SandBoxDigitizer::Digitize()
{
   
  if(_isPMT){
   
    if(_isGated){
      MakeHitsHistogram();  // This is only used by DigitizeGatePMT()..
			    // This function makes a histogram (and Map) of the number of hits as a function of time (5nsec bins)
      //FindNumberOfGates(); //get list of t0 and number of triggers.
      FindNumberOfGatesFast(); //get list of t0 and number of triggers. This is only used by DigitizeGatePMT()..
			       //essentially (but not literally) you loop over all the bins int the HitsHisto, until you get to a point 
			       // where the number of hits between your current bini and bini+39 is above the threshold. Then the time
			       // of bini is stored in and array of trigger times and we look for a new trigger condition starting at
			       // bin0 = bini+39. The key deliverables are (1) the number of gates (2) the start time of each gate/
			       // For the gated PMT operation, only the first photon within this *global gate* is used in the timing
			       // for each PMT. But, the smearing resolution for that first photon is proportional to the total number
			       // of photons on the PMT for that gate. 
      
      for ( int i = 0 ; i < this->NumberOfGatesInThisEvent(); i++)
	{
	  DigitizeGatePMT(i);	// this is the one function taken from WCSimDigitizer
	}
    } else {
      DigitizeUngatedPMT();
    }
  } else {
    DigitizeMCP();	
  }


  //  return DigitsCollection;
}

WCSimRecoEvent* SandBoxDigitizer::RecoEvent()
{
  return WCSimRecoEvent::Instance();
}

void SandBoxDigitizer::MakeHitsHistogram()
{
  // Maximilien Fechner, april 2005
  // add an individual integration gate for each PMT
  // + a global gate for the event
  // define t0 as in SKdetsim : t0 = 960 - (time after which 25 hits have been observed), see 'dshigh.F'
  // if ever a laser sudy is done it seems (see K2K1KT meetings of Jan 5th
  // 2005, laser_simulation.ppt) that this is not good, and the offset should be constant.
  // updates aug 2006 by MF to deal with subevents.

    std::memset(triggerhisto,0,20000*sizeof(Int_t));
    GateMap.clear();
    MinTime = SandBoxDigitizer::LongTime;

    Float_t tc;

    TClonesArray *WCHitCoorsArray = _theTrigger->GetCherenkovHitCoordinates(); // = "WCHitsArray"
    TClonesArray *WCHitsArray = _theTrigger->GetCherenkovHits(); // = "wcsimrootcherenkovhit array"

    Int_t ncherenkovhits = _theTrigger->GetNcherenkovhits(); //="Ncherenkovhits"
    TRandom3 tRand;

    for (int i=0; i< ncherenkovhits; i++)
      { 
	WCSimRootCherenkovHit *wcsimrootcherenkovhit = (WCSimRootCherenkovHit*)(WCHitsArray->At(i));
	Int_t timeArrayIndex = wcsimrootcherenkovhit->GetTotalPe(0);
	Int_t peForTube = wcsimrootcherenkovhit->GetTotalPe(1);
	for (int j = timeArrayIndex; j < timeArrayIndex + peForTube; j++)
	  {
	    WCSimRootCherenkovHitCoordinate* HitCoordinate = (WCSimRootCherenkovHitCoordinate*)(WCHitCoorsArray->At(j));	  
	    tc = (HitCoordinate->GetTrueHit()).at(0);
	    if ( tc < SandBoxDigitizer::LongTime)
	    { 
	      //triggerhisto[int(floor(tc/5.0))]++;
	      GateMap[ int(floor(tc/5.0)) ]++;

	    }  
	  }	
      }

    // the map must end with a value below trigger threshold
    // otherwise we will be stuck in infinite loops -- Maximilien Fechner, feb 22, 2007
    GateMap[20001]=0;
}


void SandBoxDigitizer::FindNumberOfGatesFast()
{
//GateMap is indexed by time histogram bin, and
//references elements of the timing histogram

    Int_t acc = 0; // accumulated # hits within time window...
    std::map< Int_t, Int_t>::iterator _mGateKeeper, _mNextGate;

    for( _mGateKeeper = GateMap.begin() ; _mGateKeeper != GateMap.end() ; _mGateKeeper++)
    {   
	acc = 0;
	_mNextGate = _mGateKeeper;
        RealOffset = 0.0; 				// will need to add the offset later
							// this is the starting point for the gate time
									// 40 means + 200ns
									// so check 39 bins ahead in the histogram..
	while ( _mNextGate != GateMap.lower_bound( _mGateKeeper->first + 39) 
	     && _mNextGate->first <= _mGateKeeper->first + 39 		// but not more than 200ns away though!
	      )
	{

	  acc += _mNextGate->second;
          if ( acc > SandBoxDigitizer::GlobalThreshold )   //if the number of hits withing 39 time bins of the starting point of the gate is > threshold
	  {
	    //RealOffset = _mGateKeeper->first*5.0;
	    RealOffset = _mNextGate->first*5.0; //(each bin is 5 nseconds)
	    TriggerTimes.push_back(RealOffset); // the start time of the gate is store in the "triggertimes" array and then we look if there
						// are any other windows after this gate with more hits than the GlobalThreshold
	    std::cerr << "found a trigger..." << RealOffset/5.0  <<"\n";
	    _mGateKeeper = GateMap.lower_bound( _mNextGate->first + Int_t(SandBoxDigitizer::eventgateup )/5. ); 
	    std::cerr.flush();
	    break;
          }		  
	  _mNextGate++;							// look at the next time bin with hits
	}
    }

    std::cout<<"************&&&&&&&&&&&&&&&&********************"<<std::endl;
    std::cout<<TriggerTimes.size()<<std::endl;

    for(int i=0; i<TriggerTimes.size(); i++){
      std::cout<<"tt"<<i<<": "<<TriggerTimes.at(i)<<std::endl;
    }

}


void SandBoxDigitizer::DigitizeMCP()
{
  //======Write Header, .....TX=================================
  Int_t runNum = _theTrigger->GetHeader()->GetRun();
  Int_t eventNum = _theTrigger->GetHeader()->GetEvtNum();
  Int_t triggerNum = _theTrigger->GetHeader()->GetSubEvtNumber();

  WCSimRecoEvent::Instance()->SetHeader(runNum,eventNum,triggerNum);

  TClonesArray *WCHitCoorsArray = _theTrigger->GetCherenkovHitCoordinates(); // = "WCHitsArray"
  TClonesArray *WCHitsArray = _theTrigger->GetCherenkovHits(); // = "wcsimrootcherenkovhit array"
  
  Int_t ncherenkovhits = _theTrigger->GetNcherenkovhits(); //="Ncherenkovhits"
  TRandom3 tRand;
  
  std::cout<<"really top: "<<ncherenkovhits<<std::endl;
  
  Int_t region;
  Double_t rawQ,rawT,calcQ,calcT,x,y,z;
  TRandom3 timeRand;
  
  for (int i=0; i< ncherenkovhits; i++)
    { 
      
      WCSimRootCherenkovHit *wcsimrootcherenkovhit = (WCSimRootCherenkovHit*)(WCHitsArray->At(i));
      Int_t tube = wcsimrootcherenkovhit->GetTubeID();
      Int_t timeArrayIndex = wcsimrootcherenkovhit->GetTotalPe(0);
      Int_t peForTube = wcsimrootcherenkovhit->GetTotalPe(1);

      Float_t firstHitTime = 999999.;

      qhist->Fill(peForTube);

      for (int j = timeArrayIndex; j < timeArrayIndex + peForTube; j++)
	{
	  WCSimRootCherenkovHitCoordinate* HitCoordinate = (WCSimRootCherenkovHitCoordinate*)(WCHitCoorsArray->At(j));	
	  
	  Double_t digihittime = (HitCoordinate->GetTrueHit()).at(0)
	    + timeRand.Gaus(0.0,_simpleTimeResolution);

	  timehist->Fill(digihittime);
	  tdiffhist->Fill( (HitCoordinate->GetTrueHit()).at(0)-digihittime );

	  x = ((HitCoordinate->GetTrueHit()).at(1))/10.0;
	  y = ((HitCoordinate->GetTrueHit()).at(2))/10.0;
	  z = ((HitCoordinate->GetTrueHit()).at(3))/10.0;
	  rawQ=1.0;
	  calcQ=1.0;
	  rawT=digihittime;
	  calcT=digihittime;	  

	  // Need to modify this...///////////////////////////////////
	  //region=1;
	  region = (WCSimGeometry::Instance())->GetRegion(tube);  //...TX
	  ////////////////////////////////////////////////////////////

	  WCSimRecoDigit* recoDigit = new WCSimRecoDigit(region,
							 x, y, z,
							 rawT, rawQ, peForTube,
							 calcT, calcQ);
	  

	  WCSimRecoEvent::Instance()->AddDigit(tube,recoDigit);
	  DigitsCollection.push_back(recoDigit);
	}
    }
}



void SandBoxDigitizer::DigitizeUngatedPMT()
{
  Int_t runNum = _theTrigger->GetHeader()->GetRun();
  Int_t eventNum = _theTrigger->GetHeader()->GetEvtNum();
  Int_t triggerNum = _theTrigger->GetHeader()->GetSubEvtNumber();

  WCSimRecoEvent::Instance()->SetHeader(runNum,eventNum,triggerNum);

  TClonesArray *WCHitCoorsArray = _theTrigger->GetCherenkovHitCoordinates(); // = "WCHitsArray"
  TClonesArray *WCHitsArray = _theTrigger->GetCherenkovHits(); // = "wcsimrootcherenkovhit array"
  
  Int_t ncherenkovhits = _theTrigger->GetNcherenkovhits(); //="Ncherenkovhits"
  TRandom3 tRand;
  
  std::cout<<"really top: "<<ncherenkovhits<<std::endl;
  
  Int_t region;
  Double_t rawQ,rawT,calcQ,calcT,x,y,z;

  TRandom3 timeRand;
  
  for (int i=0; i< ncherenkovhits; i++)
    { 
      
      WCSimRootCherenkovHit *wcsimrootcherenkovhit = (WCSimRootCherenkovHit*)(WCHitsArray->At(i));
      Int_t tube = wcsimrootcherenkovhit->GetTubeID();
      Int_t timeArrayIndex = wcsimrootcherenkovhit->GetTotalPe(0);
      Int_t peForTube = wcsimrootcherenkovhit->GetTotalPe(1);

      Float_t firstHitTime = 999999.;

      qhist->Fill(peForTube);

      for (int j = timeArrayIndex; j < timeArrayIndex + peForTube; j++)
	{
	  WCSimRootCherenkovHitCoordinate* HitCoordinate = (WCSimRootCherenkovHitCoordinate*)(WCHitCoorsArray->At(j));	

	  Double_t digihittime = (HitCoordinate->GetTrueHit()).at(0)
	    + timeRand.Gaus(0.0,_simpleTimeResolution);

	  timehist->Fill(digihittime);	  
	  tdiffhist->Fill((HitCoordinate->GetTrueHit()).at(0) - digihittime);

	  x = WCSimGeometry::Instance()->GetX(tube);
	  y = WCSimGeometry::Instance()->GetY(tube);
	  z = WCSimGeometry::Instance()->GetZ(tube);
	  rawQ=1.0;
	  calcQ=1.0;
	  rawT=digihittime;
	  calcT=digihittime;	  

	  // Need to modify this...///////////////////////////////////
	  //region=1;
	  region = (WCSimGeometry::Instance())->GetRegion(tube); //.....TX
	  ////////////////////////////////////////////////////////////

	  WCSimRecoDigit* recoDigit = new WCSimRecoDigit(region,
							 x, y, z,
							 rawT, rawQ, peForTube,
							 calcT, calcQ);
	  

	  WCSimRecoEvent::Instance()->AddDigit(tube,recoDigit);
	  DigitsCollection.push_back(recoDigit);
	}
    }

}


void SandBoxDigitizer::DigitizeGatePMT(Int_t G)
{

  Int_t runNum = _theTrigger->GetHeader()->GetRun();
  Int_t eventNum = _theTrigger->GetHeader()->GetEvtNum();
  Int_t triggerNum = _theTrigger->GetHeader()->GetSubEvtNumber();

  WCSimRecoEvent::Instance()->SetHeader(runNum,eventNum,triggerNum);

  std::cout<<"digitize gate is called"<<std::endl;

  Float_t timingConstant = 0.0;
  timingConstant = 2.0;


  // Figure out how to do this in SandBoxDigitizer ////////////////////////////////////////

  /*
  if (round(PMTSize) == 0.254*m)      // 20 inch tube
    //timingConstant = 3.0;      // sqrt(3.0ns) @1pe + 1ns = 2.7 ns  
    // M Fechner : essai 
    //      timingConstant = 8.3885;

    timingConstant = 10.0;  //actual value is 13 nanoseconds

  else if (round(PMTSize) == 0.1016*m) // 8 inch tube
    //      timingConstant = .58;      // sqrt(.58ns) @1pe + 1ns = 1.76 ns  
    timingConstant = 1.890; // same scaling, M Fechner
  else if (round(PMTSize) == 0.127*m) //10 inch tube
    timingConstant = 2.0; // (JF) Need real value
  else if (round(PMTSize) == round(0.1524*m)) //12 inch tube
    timingConstant = 2.0;// (JF) Need the real value
  else
    {
      cout << "Sorry.  Resolution for " << PMTSize/cm 
	     << "cm PMTs is unknown.  Exiting program. " 
	     << endl;
      exit(-1);
    }
  */


  // Will need to modify this for SandBox Digitizer ///////////////////////////////////////

 
  Double_t EvtG8Down = SandBoxDigitizer::eventgatedown;
  Double_t EvtG8Up = SandBoxDigitizer::eventgateup;  // this is a negative number...
  
	// The "TiggerTime" is determined as corresponding to the first bin where more than "Threshold" hits
	// fall between that bin and that bin + 39. If that condition is met, the full size of the time window
	// used for that gate is expanded *beyond* the 40 bin window to go from TriggerTime - EvtG8Down to
	// TriggerTime - EvtG8Up (which covers a > 1 microsecond time span.	

 
	// If I have multiple triggers, the 40 bin, smaller windows cannot overlap. However, if these 40 bin
	// windows are close together, the expanded gate window may overlap. The conditional statement below
	// is designed not to let that happen.
  Double_t lowerbound;
  if (G==0) lowerbound = TriggerTimes[G]+EvtG8Down; // if it's the first trigger, take Trigger time(0)
  else {                                            // otherwise, if tigger time + 
    lowerbound = ( TriggerTimes[G]+EvtG8Down >= TriggerTimes[G-1] + EvtG8Up ) ?  TriggerTimes[G]+EvtG8Down : TriggerTimes[G-1] + EvtG8Up;
  }
  Double_t upperbound = TriggerTimes[G]+EvtG8Up;
  
  std::cout<<"Gatebounds: "<<EvtG8Down<<" "<<EvtG8Up<<" "<<lowerbound<<" "<<upperbound<<std::endl;

  TClonesArray *WCHitCoorsArray = _theTrigger->GetCherenkovHitCoordinates(); // = "WCHitsArray"
  TClonesArray *WCHitsArray = _theTrigger->GetCherenkovHits(); // = "wcsimrootcherenkovhit array"
  
  Int_t ncherenkovhits = _theTrigger->GetNcherenkovhits(); //="Ncherenkovhits"
  TRandom3 tRand;
  
  std::cout<<"really top: "<<ncherenkovhits<<std::endl;

  for (int i=0; i< ncherenkovhits; i++) // loop over all phototubes with hits
    { 

      //      Double_t peCutOff =0.3;
      // MF, based on S.Mine's suggestion : global scaling factor applied to
      // all the smeared charges.
      // means that we need to increase the collected light by 
      // (efficiency-1)*100% to 
      // match K2K 1KT data  : maybe due to PMT curvature ?

      Double_t efficiency = 0.985; // with skrn1pe (AP tuning) & 30% QE increase in stacking action


      WCSimRootCherenkovHit *wcsimrootcherenkovhit = (WCSimRootCherenkovHit*)(WCHitsArray->At(i));
      Int_t tube = wcsimrootcherenkovhit->GetTubeID();
      Int_t timeArrayIndex = wcsimrootcherenkovhit->GetTotalPe(0);
      Int_t peForTube = wcsimrootcherenkovhit->GetTotalPe(1);

      // for this particular phototube, search for the first hit time to fall within the gate
      Float_t firstHitTime = 999999.;
      for (int j = timeArrayIndex; j < timeArrayIndex + peForTube; j++) 
	{
	  WCSimRootCherenkovHitCoordinate* HitCoordinate = (WCSimRootCherenkovHitCoordinate*)(WCHitCoorsArray->At(j));	
	  	  

	  if(   ((HitCoordinate->GetTrueHit()).at(0)>lowerbound) && ((HitCoordinate->GetTrueHit()).at(0)<upperbound) && ((HitCoordinate->GetTrueHit()).at(0) < firstHitTime) ){
            
	    firstHitTime = (HitCoordinate->GetTrueHit()).at(0);
	  }
	}

      if (firstHitTime==999999.) firstHitTime=-1.;

      if (firstHitTime < 0.) { //PMT not hit in this gate
	//	G4cout << "skipped this hit\n";
	continue; // move on to the next Hit PMT
      }
      
      double bound1 = firstHitTime+SandBoxDigitizer::pmtgate;  
      Double_t peSmeared;
      //float qtmp = 0.;
      peSmeared = 0.0;  // getting ready to calculate the total charge

      Int_t region;
      Double_t rawQ,rawT,calcQ,calcT,x,y,z;

      //loop over all hits. For each hit, choose a random variable from the charge distribution
      // in rn1pe...and add up the total charge...I think there is a bug here. I think I should only do this
      // if the hit time falls within the gate window. It does not appear to be the case...
      for (int j = timeArrayIndex; j < timeArrayIndex + peForTube; j++) 
	{

	  //qtmp=0.0;
	  // MF : note : if you use skrn1pe, you'll need to increase the
	  // charge /number of generated photons by ~4%
	  //	  skrn1pe_(&qtmp);
	  //rn1pe_(&qtmp);
	  //peSmeared += qtmp;
          
	  if(_smearCharge){
	    peSmeared += rn1pe();   
	  } else{
	    peSmeared += 1.0;
	  }
	}
    
      int iflag;
      SandBoxDigitizer::Threshold(peSmeared,iflag);
      peSmeared *= efficiency; // MC tuning correction
    
      qhist->Fill(peSmeared);

      std::cout<<"In PMT loop: "<<peSmeared<<" "<<iflag<<" "<<firstHitTime<<" "<<bound1<<" "<<SandBoxDigitizer::pmtgate<<std::endl;
  
        
      if ( iflag==0 )
	//	if ( peSmeared > peCutOff )
	{
          // warning the times are still absolute G4 times.
	  // need to take care of offsets here !!
	  
          // MF : reorganized the algorithm. Because of the offset, very early
          // hits can appear to be negative (if the t0 is triggered much later)
          // they have to be removed otherwise nothing will work.
          
          // MF : found 'by hand', fits SK PMT resolution (2002 values ?)
          // Add cutoffs 

	  // MattW - Now that we have the time of the first photon to hit the PMT in the global gate *and* we have the total charge
	  // the smeared time for the PMT equals firstHitTime + aRandomGaussianNumber(Sigma=parameterizedvalue_as_a_functionof_charge)
	
	  float Q = (peSmeared > 0.5) ? peSmeared : 0.5;
	  float timingResolution = 0.33 + sqrt(timingConstant/Q);  // here is where we get parameterizedvalue_as_a_functionof_charge
	  // looking at SK's jitter function for 20" tubes
	  if (timingResolution < 0.58) timingResolution=0.58;
	  
	  /*
	  Double_t digihittime = -TriggerTimes[G]
	    + SandBoxDigitizer::offset
	    + firstHitTime
	    + tRand.Gaus(0.0,timingResolution);
	  */
	  Double_t digihittime = firstHitTime
	    + tRand.Gaus(0.0,timingResolution);
	  
	  timehist->Fill(digihittime); // for diagnostics
	  
	  for (int j = timeArrayIndex; j < timeArrayIndex + peForTube; j++)
	    {
	      WCSimRootCherenkovHitCoordinate* HitCoordinate = (WCSimRootCherenkovHitCoordinate*)(WCHitCoorsArray->At(j));		  
	      tdiffhist->Fill( (HitCoordinate->GetTrueHit()).at(0) - digihittime );
	      sdiffhist->Fill( sqrt(((HitCoordinate->GetTrueHit()).at(1) - WCSimGeometry::Instance()->GetX(tube))*((HitCoordinate->GetTrueHit()).at(1) - WCSimGeometry::Instance()->GetX(tube)) + ((HitCoordinate->GetTrueHit()).at(2) - WCSimGeometry::Instance()->GetY(tube))*((HitCoordinate->GetTrueHit()).at(2) - WCSimGeometry::Instance()->GetY(tube)) + ((HitCoordinate->GetTrueHit()).at(3) - WCSimGeometry::Instance()->GetZ(tube))*((HitCoordinate->GetTrueHit()).at(3) - WCSimGeometry::Instance()->GetZ(tube))) );
	    }

	  std::cout<<"smeared T: "<<digihittime<<" "<<firstHitTime<<std::endl;

	  if ( digihittime > 0.0 && peSmeared>0.0) 
	    {	  
	      if ( DigiHitMap[tube] == 0) {
		//G4cout << tube << " " << G << "  " << TriggerTimes[G] << " " << digihittime 
		//       << "  " <<   peSmeared <<" ";

		x = WCSimGeometry::Instance()->GetX(tube);
		y = WCSimGeometry::Instance()->GetY(tube);
		z = WCSimGeometry::Instance()->GetZ(tube);
		rawQ=peSmeared;
		calcQ=peSmeared;
		rawT=digihittime;
		calcT=digihittime;

		//		std::cout<<x<<" "<<rawT<<" "<<rawQ<<std::endl;

		// Need to modify this...///////////////////////////////////
		//region=1;
		region = (WCSimGeometry::Instance())->GetRegion(tube);   //....TX 
	 	////////////////////////////////////////////////////////////

		// We fill the reco digit with x,y,z=PMTcenter time=smearedtime, and Q=smearedQ

		WCSimRecoDigit* recoDigit = new WCSimRecoDigit(region,
							       x, y, z,
							       rawT, rawQ, rawQ,
							       calcT, calcQ);


		WCSimRecoEvent::Instance()->AddDigit(tube,recoDigit);
		DigitsCollection.push_back(recoDigit);
	      }
	      else { 
		//G4cout << "deja vu " << tube << " " << G << "  " << TriggerTimes[G] << " " << digihittime 
		//     << "  " <<   peSmeared <<" ";
		/*
		  (*DigitsCollection)[DigiHitMap[tube]-1]->AddGate(G,TriggerTimes[G]);
		  (*DigitsCollection)[DigiHitMap[tube]-1]->SetPe(G,peSmeared);
		  (*DigitsCollection)[DigiHitMap[tube]-1]->SetTime(G,digihittime);
		*/
	      }
	    }
	  else {}// std::cout << "discarded negative time hit\n";}	
	}
    }  
}
 

