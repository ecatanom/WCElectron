 
#!/bin/bash

export LBNE_CODE=/lbne/app/users/ecatanom/elecIoana/

# lbne condor tools
export GROUP=lbne
#source /grid/fermiapp/common/tools/setup_condor.sh
#source /grid/fermiapp/products/$GROUP/etc/setups.sh
source /grid/fermiapp/products/$GROUP/setup
#export PRODUCTS=$PRODUCTS:/grid/fermiapp/products/$GROUP/db
export PRODUCTS=$PRODUCTS:/grid/fermiapp/products/common/db
setup jobsub_tools

# root version 5.30
source /lbne/app/users/trj/wcsimsoft/ROOT/root/bin/thisroot.sh

# GEANT 4.9.4.p02
source /lbne/app/users/trj/wcsimsoft/GEANT4/geant4.9.4.p02/env.sh

# for shared libraries
#export LD_LIBRARY_PATH=/lbne/app/users/trj/wcsimsoft/WCSIM/trunk:/lbne/app/users/omanghel/WCSimAnalysis/lib:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=/lbne/app/users/wetstein/WCSim/branches/dev/DetectorDevelopment:/lbne/app/users/wetstein/WCSimAnalysis/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/lbne/app/users/omanghel/WCSim/branches/dev/DetectorDevelopment:/lbne/app/users/ecatanom/elecIoana/lib:$LD_LIBRARY_PATH

#export G4WORKDIR=/lbne/app/users/trj/wcsimsoft/WCSIM/trunk
#export G4WORKDIR=/lbne/app/users/wetstein/WCSim/branches/dev/DetectorDevelopment
export G4WORKDIR=/lbne/app/users/omanghel/WCSim/branches/dev/DetectorDevelopment

echo "G4WORKDIR is set to /lbne/app/users/trj/wcsimsoft/WCSIM/trunk"
echo "To build WCSIM or other Geant programs, please use your own"
echo "G4WORKDIR definition"

# My old version of WCSim that was built against geant v4.9.3?
#export WCSIM=/lbne/app/users/omanghel/garpi/projects/interim/Simulation/WCSimPackage


#export WCSIM=/lbne/app/users/trj/wcsimsoft/WCSIM/trunk/
#export WCSIM=/lbne/app/users/wetstein/WCSim/branches/dev/DetectorDevelopment/
export WCSIM=/lbne/app/users/omanghel/WCSim/branches/dev/DetectorDevelopment/

export PATH=/lbne/app/users/ecatanom/elecIoana/bin:$PATH

#doxygen
export LBNE_WWW=/nusoft/app/web/htdoc/lbne/WCSimAnalysis/doxygen/


#WCSmAnalsis we use objects defined in WCSim; currently we keep ioana's code