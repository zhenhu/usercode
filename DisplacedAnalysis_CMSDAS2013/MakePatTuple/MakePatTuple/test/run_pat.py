#!/bin/env python

import os,sys


#===============================================================================
# Function to work out what CMSSW release you are using
#===============================================================================
def cmssw_version(release):
    # tool to make sure CMSSW releases can be used in string comparison
    # despite different numbers of digits
    newrelease=""
    for part in release.split("_"):
        try:
            num=int(part)
            newrelease+="%03i"%num
        except:
            newrelease+=part
    return newrelease



#===============================================================================
# Check command line arguments 
#===============================================================================
if len(sys.argv)<3:
    print "ERROR: need to provide a valid sample cff file as argument"
    print "and whether to automatically create and submit crab jobs (1 or 0)"
    sys.exit(1)

# Try this first

# Filename 
filename=sys.argv[1]

# Do you want to automatically create and submit crab jobs?
# If not, the command to do so will be output to the screen
autoCreateAndSubmit=int(sys.argv[2])

if len(sys.argv)==4:
    if sys.argv[2].find(".py")>0: 
        filename=sys.argv[2]
        autoCreateAndSubmit=int(sys.argv[3])
    pass

print "Will set everything up for : ",filename
print "Will I automatically create and submit crab jobs?",autoCreateAndSubmit
print ""

#===============================================================================
# Import sample tools and create AnalysisSample
#===============================================================================
from SampleFiles.Tools.AnalysisSample import *
# Get all info from sample configuration file
sample=AnalysisSample(filename)

#===============================================================================
# Check CMSSW version
# This is just so that you don't try to analyze data/MC with version X of CMSSW
# with version Y of CMSSW, where X>Y
# EJC - Should put in a few exceptions here?  Sometimes have to process e.g. CMSSW_5_2_5_patch4 MC/data in CMSSW_5_2_5?
#===============================================================================
if cmssw_version(sample.sampleRelease)>cmssw_version(os.getenv("CMSSW_VERSION")):
    print "error: trying to read",sample.sampleRelease,"MC in a",os.getenv("CMSSW_VERSION"),\
          "release directory"
    sys.exit(1)


#===============================================================================
# Check there is a dataset to run on in sample cff file
#===============================================================================
if sample.sampleDataSet=="":
    print "error: sampleDataSet not defined in",sample.cff
    sys.exit(1)

#==============================================================================
# Create a new workdir
#==============================================================================
sample.create_work_dir("pat")

#===============================================================================
# Set up the CMSSW config
#===============================================================================
# Open config file
infile=open(sample.cmssw_base+"/src/MakePatTuple/MakePatTuple/test/"\
            +"makePATtuple_cfg.py","r")
# Find and open output conf
sample.conf=sample.workdir+"/makePATtuple_cfg.py"
outfile=open(sample.conf,"w")

# Change config file so it finds the sample cff file from the workdir 
written=0
pythonId=sample.packageNamePython+".SAMPLENAME"
for line in infile.readlines():
    if line.find(pythonId)>0:
        # replace original sample include line
        if written==0:
            written=1
            outfile.write("   from "+sample.packageNamePython+"."+sample.id+"_cff import *\n")
    else:
        outfile.write(line)
infile.close()
outfile.close()


#===============================================================================
# Set up jobs to run on the grid
# Will automatically create and submit jobs if you want
#===============================================================================

print "Setting up crab config files...\n"
sample.setupCrabJobs("PAT")

if autoCreateAndSubmit==1:
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

