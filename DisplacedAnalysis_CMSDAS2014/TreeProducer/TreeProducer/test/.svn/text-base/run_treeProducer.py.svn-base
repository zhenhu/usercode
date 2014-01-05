#!/bin/env python

#################################
# GENERAL CHECKS AND PREPARATIONS
#################################

# check command line argument
import os,sys
print len(sys.argv)
if len(sys.argv)<3:
    print "ERROR: Need to provide a valid sample cff file and the run mode as arguments"
    print "Runmode: Choose from CERN, RAL, CRAB.  Others added once supported..."
    sys.exit(1)

from SampleFiles.Tools.AnalysisSample import *
sample=AnalysisSample(sys.argv[1])

runmode=sys.argv[2]
autoCreateAndSubmit=0

# Check runmode is supported
if not ( runmode=="CERN" or runmode=="RAL" or runmode=="FNAL" or runmode=="CRAB" ):
    print "ERROR: Can't run at this location/this way"
    print "Runmode: Choose from CERN, RAL, FNAL or CRAB.  Others added once supported..."
    sys.exit(1)

if runmode=="CRAB":
    if len(sys.argv)<4:
        print "If running on CRAB, must also specify whether to auto create and submit all jobs"
        sys.exit(1)
    else:
        autoCreateAndSubmit=sys.argv[3]
        pass
    pass

# check CMSSW version
if sample.sampleRelease>os.getenv("CMSSW_VERSION"):
    print "error: trying to analyse",sample.sampleRelease,"sample in a",\
          os.getenv("CMSSW_VERSION"),"release directory"
    sys.exit(1)

# do we have input?
if len(sample.samplePatFiles)==0:
    print "error: no samplePatFiles defined in",sample.cff
    sys.exit(1)
    
#filelist=sample.check_dir(sample.samplePatFiles,"input",1)
filelist=sample.samplePatFiles

##########################
# SET UP CMSSW CONFIG FILE
##########################

sample.create_work_dir("analysis")
# sample.create_work_dir_temp("analysis", "/uscmst1b_scratch/lpc1/3DayLifetime/"+os.environ["USER"])
infile=open(sample.cmssw_base+"/src/TreeProducer/TreeProducer/test/treeProducer_cfg.py","r")
sample.driverconf=sample.workdir+"/treeProducer_cfg.py"
outfile=open(sample.driverconf,"w")
written=0
pythonId=sample.packageNamePython
print "Looking for",pythonId
for line in infile.readlines():
    if line.find(pythonId+".Debug")>0:
        # replace original sample include line
        if written==0:
            written=1
            outfile.write("from "+pythonId+"."+sample.id+"_cff import *\n")
    else:
        outfile.write(line)
infile.close()
outfile.close()


##############
# RUN THE JOBS
##############

# now submit jobs
if runmode=="RAL" or runmode=="CERN" or runmode=="FNAL":
    print "Running jobs on local batch system"
    sample.run_batch_jobs(filelist,runmode)
elif runmode=="CRAB":
    print "Running job on CRAB"
    sample.setupCrabJobs("TREE")
    
    if autoCreateAndSubmit=="1":
        createCrabJob(sample.workdir+"/crab.cfg")
        submitCrabJob(sample.workdir+"/crabDir")
        pass
    else:
        print "---> To create crab job, do : "
        print "nohup crab -create -cfg "+sample.workdir+"/crab.cfg &> "+sample.workdir+"/out.crabCreate &"
        print ""
        print "---> To submit the job, do : "
        print "nohup crab -submit -c "+sample.workdir+"/crabDir/ &> "+sample.workdir+"/out.crabSubmit &"
        print ""
        pass

    print "---> To monitor crab job, do : "
    print "crab -status -c "+sample.workdir+"/crabDir/"
    print ""
    pass
else:
    print "Don't know this runmode.  No jobs submitted"
    pass
