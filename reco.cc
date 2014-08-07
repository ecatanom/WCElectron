#include "WCSimInterface.hh"
#include "WCSimNtupleWriter.hh"
#include "WCSimDataCleaner.hh"
#include "WCSimRingFinder.hh"
#include "WCSimVertexFinder.hh"
#include "WCSimRecoObjectTable.hh"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  
  // Configuration
  WCSimRingFinder::UseRecoVertex(); // suppress ring finder

  // Print parameters
  WCSimDataCleaner::PrintParameters();
  WCSimVertexFinder::PrintParameters();
  WCSimRingFinder::PrintParameters();

  // Load Data
  //WCSimInterface::LoadData("/lbne/data/water/beamevents15pcthqe/beamevents9.root");
  WCSimInterface::LoadData(argv[1]);
  // create ntuple writer
  WCSimNtupleWriter* recoana = new WCSimNtupleWriter();
  
  // type of ntuple
  recoana->UseNtuple("Reco");

  // set output file name
  recoana->SetFileName(argv[2]);

  // loop over n events, leave blank to run all entries
  recoana->Run();

  WCSimRecoObjectTable::Instance()->Print();

}
