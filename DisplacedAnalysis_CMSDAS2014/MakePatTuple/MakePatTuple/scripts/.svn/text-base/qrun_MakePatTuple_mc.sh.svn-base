#!/bin/bash

# 5_3_3 run script for PATtuplizer on Condor.
# To use in your own area, change the path and (if necessary)
# the release version below.
#
# Usage: This script requires at least two arguments.
# The first is the type name (which determines the name
# of the input filelist and the output files)
# The second is the segment number, assuming 10k events per segment.

## Set release base and version
MY_RELEASE_BASE=/uscms_data/d3/plujan
CMSSW_VERSION=CMSSW_5_3_3

# Parse arguments. First two should be
# the type and the job number. Then the
# set number and HLT process name are optional.

if [ $# -lt 2 ]; then
   echo "Usage: $0 type jobNum"
   exit 1
fi

type=$1
jobNum=$2

## Set file names
sourceFile=${MY_RELEASE_BASE}/${CMSSW_VERSION}/src/archives/MakePatTuple.tgz

pythonFile=makePATtuple_${type}_${jobNum}_cfg.py
outputFile=PATtuple_${type}_${jobNum}.root
inputFile=filelist_${type}_cfi

# Configurable parameters
maxEvents=10000
skipEvents=$[($jobNum-1)*$maxEvents]

echo "Skipping $skipEvents events"

echo "Using CMSSW version:" ${CMSSW_VERSION}
echo "Making config file:" $pythonFile
echo "Writing to file:" $outputFile

## Check if we're running interactively or on the batch node.
## If the latter, build the release.
## In all cases, copy the template to our current directory.

if [ -z ${_CONDOR_SCRATCH_DIR} ]; then
    ## Are we in the test directory or somewhere else?
    ## If somewhere else, we'll still need to build the release.

    pwd=`pwd`

    if [ `basename $pwd` == "test" ]; then
	## We're in the test directory; no need to do anything
	## except make sure we're set up.
	echo "Running in current directory..."
	eval `scram run -sh`
	cp ../test/makePATtuple_cfg.py ./${pythonFile}
    else
	## Build release in 3DL area.
	echo "Building release in 3DL..."
	scratchdir=/uscmst1b_scratch/lpc1/3DayLifetime/${USER}
	rundir=${scratchdir}/Test/MakePatTuple
	
	if [ ! -e ${rundir} ]; then mkdir -p ${rundir}; fi
	cd $rundir || exit
	rm * -rvf

	source /uscmst1/prod/sw/cms/bashrc prod
	scram p CMSSW ${CMSSW_VERSION}
	cd ${CMSSW_VERSION}/src
	eval `scram run -sh`
	tar xzf ${sourceFile}
	find -name "*.pyc" -print | xargs rm
	scram b || exit 1
	
	cd $rundir
	cp ${MY_RELEASE_BASE}/${CMSSW_VERSION}/src/MakePatTuple/MakePatTuple/test/makePATtuple_cfg.py ./${pythonFile}
    fi
else
    ## Build release in condor scratch directory.

    cd ${_CONDOR_SCRATCH_DIR}

    source /uscmst1/prod/sw/cms/bashrc prod
    scram p CMSSW ${CMSSW_VERSION}
    cd ${CMSSW_VERSION}/src
    eval `scram run -sh`
    tar xzf ${sourceFile}
    find -name "*.pyc" -print | xargs rm
    scram b || exit 1

    cd ${_CONDOR_SCRATCH_DIR}

    cp ${CMSSW_VERSION}/src/MakePatTuple/MakePatTuple/test/makePATtuple_cfg.py ./${pythonFile}
fi    

# Fill in the blanks in the template...

perl -p -i -e "s/useCondor=False/useCondor=True/" $pythonFile
perl -p -i -e "s/MAX_EVENTS/$maxEvents/" $pythonFile
perl -p -i -e "s/SKIP_EVENTS/$skipEvents/" $pythonFile
perl -p -i -e "s/INPUTFILE/$inputFile/" $pythonFile
perl -p -i -e "s/OUTPUTFILE/$outputFile/" $pythonFile

# ... and we're ready to go! (hopefully)

cmsRun ${pythonFile}

# If running on condor, clean up the stuff so it doesn't get returned needlessly

if [ -z ${_CONDOR_SCRATCH_DIR} ]; then
    echo "Job finished"
else
    # Could also put in code to copy output directly to dcache here

    rm ${pythonFile}
    rm -rf ${CMSSW_VERSION}
fi

