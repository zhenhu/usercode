import os,sys
from SampleFiles.Tools.AnalysisSample import *

#===============================================================================
# Check command line arguments
#===============================================================================

if len(sys.argv) < 4:
    print "ERROR: need to provide a valid sample workdir as argument"
    print "and where the PAT files are put (directory to your space on eos? e.g. /store/caf/user/ejclemen/),"
    print "though if the dir doesn't exist, this is OK.  Script will not"
    print "produce list of files"
    print "And whether to publish output files or not (this will also update the cff file with the name of the published dataset"
    sys.exit(1)
        
# A sample's workdir
sampleWorkdir=sys.argv[1]
# Where the output PAT files are
# If garbage or doesn't exist will not provide the lsit of PAT files
# Also, baseDirPrefix depends on where you are running...
baseDirPrefix="dcap://dcap.pp.rl.ac.uk/"
#baseDirPrefix="root://eoscms//eos/cms/"
baseDir=sys.argv[2]

publishPATtuples=sys.argv[3]

if len(sys.argv)==5:
    if sys.argv[2].find(".py")>0: 
        sampleWorkdir=sys.argv[2]
        baseDir=sys.argv[3]
        publishPATtuples=sys.argv[4]
    pass

print "Will I publish these PAT tuples?",publishPATtuples

if sampleWorkdir[-1] != "/": sampleWorkdir=sampleWorkdir+"/"
if baseDir[-1] != "/": baseDir=baseDir+"/"

#===============================================================================
# Import sample tools and create AnalysisSample - from workdir
#===============================================================================
# Get all info from sample configuration file
workdirContents=os.listdir(sampleWorkdir)
sampleCffFile=""
for file in workdirContents:
    if file.find("_cff.py")>=0:
        sampleCffFile=sampleWorkdir+"/"+file
        pass
    pass

sample=AnalysisSample(sampleCffFile)

#===============================================================================
# Run getoutput first
#===============================================================================
getOutputCrabJob(sampleWorkdir+"/crabDir")

#===============================================================================
# For a data sample, run crab -report, lumiCalc2.py and pileupCalc
#===============================================================================
if sample.sampleType=="DATA":
    # Run crab - report
    reportCrabJob(sampleWorkdir+"/crabDir")
    
    # Analyse lumi info
    analyseLumi(sampleWorkdir,sample)
    
    # Get PU info
    getPUInfo(sampleWorkdir,sample)
    pass

#===============================================================================
# Get list of PAT files to put into sample cff file
#===============================================================================
# List directory
fileDir=""

if baseDir.find("/store/caf/") != -1:
    fileDir=baseDir+"/"+sampleWorkdir.split("/")[-2]+"/"+baseDir.split("/")[-2]+"/"+sample.sampleDataSet.split("/")[1]+"/"+sampleWorkdir.split("/")[-2]
    os.system('cmsLs '+fileDir+' | awk \'{print $5}\' > fileDir.txt')
    dirContent = open("fileDir.txt").readlines()
    dirContent = dirContent[0].rstrip('\n')
else:
    fileDir=baseDir+"/"+sample.sampleDataSet.split("/")[1]+"/"+sampleWorkdir.split("/")[-2]
    dirContent=os.listdir(fileDir)

fileDir=fileDir+"/"+dirContent[0]

# Get actual list of files now that I have the correct directory
if baseDir.find("/store/caf/") != -1:
    os.system('cmsLs '+dirContent+' > fileDir.txt')
    os.system('cat fileDir.txt | grep ".root" | awk \'{print $5}\' | awk -F"/" \'{print $NF}\'> fileList.txt')
    fileDir = dirContent
    dirContent = open("fileList.txt").readlines()
else:
    dirContent=os.listdir(fileDir)

#===============================================================================
# Got list of files, output to dir
#===============================================================================

outputFileList=open(sampleWorkdir+"/listOfPatFiles.txt","w")

outputFileList.write('sampleBaseDir="'+baseDirPrefix+'/'+fileDir+'/"\n')
outputFileList.write("samplePatFiles = [\n")

for file in dirContent:
    outputFileList.write('sampleBaseDir+"'+file.rstrip("\n")+'",\n')
    pass

outputFileList.write("]\n")

outputFileList.close()

#===============================================================================
# Optionally publish files
#===============================================================================
publishedDatasetName=""
if publishPATtuples=="1":
    # Publish PAT tuples
    publishedDatasetName=publishPATOutput(sampleWorkdir+"/crabDir")
    print "Published dataset name :",publishedDatasetName
    pass

#===============================================================================
# Append file list to original sample cff file
# And optionally add published dataset name to sample cff file
#===============================================================================

# Find original cff file in SampleFiles/Samples/python
sampleCffFile=sampleCffFile.split("/")[-1]
sampleCffFile=sample.cmssw_base+"/src/SampleFiles/Samples/python/"+sampleCffFile

# Read original file
originalCff=open(sampleCffFile,"r")
originalCffLines=originalCff.readlines()
originalCff.close()

newCffFile=open(sampleCffFile+".new","w")

writeLine=False
for line in originalCffLines:
    # Do not write out published DBS name of new PAT tuples
    if line.find("samplePatDBSName")>=0:
        continue
    # Remove all lines after this
    if line.find("sampleBaseDir")>=0:
        break

    newCffFile.write(line)
    pass


# Add published DBS name of PAT tuples
newCffFile.write('samplePatDBSName="'+publishedDatasetName+'"\n\n')

# Have new file, but missing pat file list at bottom.  Same as before
newCffFile.write('sampleBaseDir="'+baseDirPrefix+'/'+fileDir+'/"\n')
newCffFile.write("samplePatFiles = [\n")

for file in dirContent:
    newCffFile.write('sampleBaseDir+"'+file.rstrip("\n")+'",\n')
    pass

newCffFile.write("]\n")

newCffFile.close()

os.system("mv "+sampleCffFile+" "+sampleCffFile+".old")
os.system("mv "+sampleCffFile+".new "+sampleCffFile)

