#!/bin/bash

# doxygen setup
export LBNE_WWW=/nusoft/app/web/htdoc/lbne/WCSimAnalysis/doxygen/
export LBNE_CODE=/lbne/app/users/gsdavies/WCSimAnalysis/

# lbne condor tools
export GROUP=lbne
source /grid/fermiapp/common/tools/setup_condor.sh

# root version 5.30
source /lbne/app/users/trj/wcsimsoft/ROOT/root/bin/thisroot.sh

# GEANT 4.9.4.p02
source /lbne/app/users/trj/wcsimsoft/GEANT4/geant4.9.4.p02/env.sh

# for shared libraries
# EDIT this for path to own WCSimAnalysis/lib
export LD_LIBRARY_PATH=/lbne/app/users/trj/wcsimsoft/WCSIM/trunk:/lbne/app/users/gsdavies/WCSimAnalysis/lib:$LD_LIBRARY_PATH

export G4WORKDIR=/lbne/app/users/trj/wcsimsoft/WCSIM/trunk

echo "G4WORKDIR is set to /lbne/app/users/trj/wcsimsoft/WCSIM/trunk"
echo "To build WCSIM or other Geant programs, please use your own"
echo "G4WORKDIR definition"

# EDIT this is to install your own WCSim
export WCSIM=/lbne/app/users/trj/wcsimsoft/WCSIM/trunk

# EDIT this for your own WCSimAnalysis/bin
export PATH=/lbne/app/users/gsdavies/WCSimAnalysis/bin:$PATH



