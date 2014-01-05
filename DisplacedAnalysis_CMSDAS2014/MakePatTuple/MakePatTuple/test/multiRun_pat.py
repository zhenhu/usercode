#===============================================================================
#===============================================================================
# This script looks at all sample cff files in the provided directory
# Or can select which set of samples to run on ("All","EData","MuData","QCDEm","QCDMu","Diboson","DY","Signal")
# It runs run_pat.py, which sets up the workdir for that sample file
# And sets up the crab config
# The crab commands to run the jobs are printed to screen
#===============================================================================
#===============================================================================

#!/bin/env python

import os,sys,subprocess

# Debug option - puts Debug_cff.py as only file
debug = False

#===============================================================================
# Need to pass location of sample cff files as argument
#===============================================================================
if len(sys.argv)<4:
    print "ERROR: need to provide location of sample cff file as argument"
    print "which samples to process (EData, MuData, QCD, Diboson, DY, Signal) "
    print "and whether to automatically create and submit crab jobs"
    sys.exit(1)

# Try this first
locationOfScript=sys.argv[0]
sampleDir=sys.argv[1]
#Which samples
whichSamples=sys.argv[2]
# Do you want to automatically create and submit crab jobs?
# If not, the command to do so will be output to the screen
autoCreateAndSubmit=int(sys.argv[3])

if len(sys.argv)==4:
    if sys.argv[2].find(".py")>0:
        locationOfScript=sys.argv[1]
        sampleDir=sys.argv[2]
        whichSamples=sys.argv[3]
        autoCreateAndSubmit=int(sys.argv[4])
        pass
    pass

if not (whichSamples == "All" or whichSamples == "EData" or whichSamples == "MuData" or whichSamples == "QCDEm" or whichSamples == "QCDMu" or whichSamples == "Diboson" or whichSamples == "DY" or whichSamples == "Signal"):
    print "ERROR: Unkown sample group"
    print "Please choose from : All, EData, MuData, QCDEm, QCDMu, Diboson, DY, Signal"
    sys.exit(1)

print "\n========================================================"
print "Will set everything up for sample files in :",sampleDir
print "Which group of samples?",whichSamples
print "Will I automatically create and submit crab jobs?",autoCreateAndSubmit
print "========================================================\n"

#===============================================================================
# Make note of all available sample cff files in provided directory
#===============================================================================
process=subprocess.Popen(["ls",sampleDir], stdout=subprocess.PIPE)
out,err=process.communicate()

if err != None:
    print "ERROR : Problem with finding sample cff files in ",sampleDir
    sys.exit(1)
    pass

allFileList=out.split("\n")

#===============================================================================
# Clean the list of files to remove unwanted files
#===============================================================================
fileList=[]
for file in allFileList:
    
    processThisFile=False
    
    # Only consider the .py files
    if not file[-3:]==".py": continue;
    # Don't consider the Debug_cff file or __init__.py if it happens to be there
    if file.find("Debug")>=0 or file.find("__init__")>=0: continue

    if whichSamples=="All":processThisFile=True
    elif whichSamples=="EData":
        if file.find("Data_Photon")>=0:processThisFile=True
        pass
    elif whichSamples=="MuData":
        if file.find("Data_Mu_")>=0:processThisFile=True
        pass
    elif whichSamples=="QCDEm":
        if file.find("QCDem")>=0:processThisFile=True
        pass
    elif whichSamples=="QCDMu":
        if file.find("QCDMu")>=0:processThisFile=True
        pass
    elif whichSamples=="Diboson":
        if file.find("WW")>=0 or file.find("WZ")>=0 or file.find("ZZ")>=0 or file.find("TT")>=0:processThisFile=True
        pass
    elif whichSamples=="DY":
        if file.find("DY")>=0:processThisFile=True
        pass
    elif whichSamples=="Signal":
        if file.find("LongLived")>=0 or file.find("Chi0")>=0:processThisFile=True
        pass
    else:
        print "ERROR : Unkown sample group - should have been caught earlier?"
        sys.exit(1)
    
    if processThisFile: fileList.append(file)
    pass

if debug:
    fileList=["Debug_sample_cff.py"]

#===============================================================================
# For each file, run run_pat and take note of the crab commands outputed to screen
#===============================================================================

# List of the crab commands
crabCreate=[]
crabSubmit=[]
crabStatus=[]

# Need to know exact location of run_pat
# Luckily, it is in the same place as multiRun_pat.py
locationOfScript=locationOfScript[:locationOfScript.find("multiRun_pat")]

for file in fileList:
    # run run_pat.py for each cff file and extract crab commands
    print "- Running run_pat.py for",file,"\n"
    process=subprocess.Popen(["python","%s/run_pat.py" % locationOfScript, "%s/%s" % (sampleDir,file),"%s" % (autoCreateAndSubmit)], stdout=subprocess.PIPE)
    out,err=process.communicate()
    
    if err != None:
        print "ERROR : Problem with running run_pat for ",file
        sys.exit(1)
        pass  

    out=out.split("\n")

    for line in out:
        if line.find("-create")>=0: crabCreate.append(line)
        if line.find("-submit")>=0: crabSubmit.append(line)
        if line.find("-status")>=0: crabStatus.append(line)
        pass
    pass


#===============================================================================
# Now have list of crab commands
# Print to screen for user to make use of
#===============================================================================
if autoCreateAndSubmit != 1:
    
    print "---> To create all crab jobs : "
    
    # Store these in a file aswell
    createFile=open("crabCreate.txt","w")
    
    for createCommand in crabCreate:
        print createCommand
        createFile.write(createCommand+'\n')
        pass
    
    createFile.close()
    
    print "\n---> To submit all crab jobs : "
    
    submitFile=open("crabSubmit.txt","w")
    
    for submitCommand in crabSubmit:
        print submitCommand
        submitFile.write(submitCommand+'\n')
        pass
    
    submitFile.close()

print "\n---> To monitor jobs : "
for statusCommand in crabStatus:
    print statusCommand
    pass
