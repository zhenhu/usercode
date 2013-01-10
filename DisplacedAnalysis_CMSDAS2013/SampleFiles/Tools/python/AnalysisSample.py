import os,sys,time
import ROOT

class AnalysisSample:

    ############################################################
    # INITIALISATION: read and check sample description cff file
    ############################################################
    def __init__(self,cff_name):

        #=======================================================================
        # Check that the file exists and set cff file name
        #=======================================================================
        if not os.path.isfile(cff_name):
            print "error: file",cff_name,"not found"
            sys.exit(1)
            pass

        self.cff=os.path.abspath(cff_name)

        #=======================================================================
        # Check that CMSSW area is set up
        #=======================================================================
        self.cmssw_base=os.getenv("CMSSW_BASE","NONE")
        if self.cmssw_base=="NONE":
            print "error: need to run cmsenv beforehand"
            sys.exit(1)
            pass

        #======================================================================
        # Check that the cff file is actually in the CMSSW area
        #======================================================================
        if self.cff.find(self.cmssw_base)!=0:
            print "error: cff file is not in the release area currently set up"
            print self.cff
            print self.cmssw_base
            sys.exit(1)

        #=======================================================================
        # Initialise variables to be read from sample cff file
        #=======================================================================
        sampleDataSet=""
        sampleDbsUrl=''
        sampleJSON=""
        sampleRunRange=[]
        samplePatFiles=[]
        samplePatDBSName=""
        sampleCMSEnergy=0
        sampleXSec=0
        sampleGlobalTag=""
        sampleRelease=""
        sampleNumEvents=0
        sampleType=""
        sampleSignalPID=0
        sampleRequireCollision=1

        #=======================================================================
        # Read and interpret the file
        #=======================================================================
        exec(sample_cff_code(self.cff))

        #=======================================================================
        # Check that the mandatory information is there
        #=======================================================================
        if sampleDataSet=="":
            print "error: sampleDataSet not set in",self.cff
            sys.exit(1)
        if sampleGlobalTag=="":
            print "error: sampleGlobalTag not set in",self.cff
            sys.exit(1)
        if sampleRelease=="":
            print "error: sampleRelease not set in",self.cff
            sys.exit(1)
        if sampleNumEvents==0:
            print "error: sampleNumEvents not set in",self.cff
            sys.exit(1)
        if not (sampleType=="SIGNALMC" or sampleType=="BKGMC" or sampleType=="DATA"):
            print sampleType
            print "error: sampleType must be set to SIGNALMC or BKGMC or DATA in",self.cff
            sys.exit(1)

        #=======================================================================
        # Store cff information in class members
        #=======================================================================
        self.sampleDataSet=sampleDataSet
        self.sampleDbsUrl=sampleDbsUrl
        self.sampleJSON=sampleJSON
        self.sampleRunRange=sampleRunRange
        self.samplePatFiles=samplePatFiles
        self.samplePatDBSName=samplePatDBSName
        self.sampleCMSEnergy=sampleCMSEnergy
        self.sampleXSec=sampleXSec
        self.sampleGlobalTag=sampleGlobalTag
        self.sampleRelease=sampleRelease
        self.sampleNumEvents=sampleNumEvents
        self.sampleType=sampleType
        self.sampleSignalPID=sampleSignalPID
        self.sampleRequireCollision=sampleRequireCollision

        #=======================================================================
        # General initialisation 
        #=======================================================================
        self.workdir=""
        self.conf=""
        self.crabConf=""
        
        #=======================================================================
        # Create a unique sample ID and get the name of the CMSSW package 
        # to find the workdir
        # Note this is unique from different samples, not different samples
        # from different versions of PATtuple creation
        #=======================================================================
        self.id=self.cff.split("/")[-1].replace("_cff.py","")
        levels=self.cff.replace(self.cmssw_base,"").strip("/").split("/")
        self.packageName=levels[1]+"/"+levels[2]
        self.packageNamePython=self.packageName.replace("/",".")
       
    ############################################
    # CREATE A WORKING DIRECTORY
    # THIS IS WHERE ALL CRAB CFGS ETC. WILL GO
    ############################################
    def create_work_dir(self,process):
        # Check if the workdir already exists
        if self.workdir!="":
            print "ERROR: working directory already created"
            return
        
        # Define workdir
        workbasedir=self.cmssw_base+"/src/workdirs/"
        # Make it if it doesn't exist
        if not os.path.exists(workbasedir):
            os.system("mkdir -p "+workbasedir)
            
        # Set workdir to self
        self.workdir = workbasedir+self.id+"_"+process\
                       +time.strftime("_%Y%m%d")
        
        # Make sure it is unique
        # in case you are running this stage
        # more than once in any given day
        if os.path.exists(self.workdir):
            num=0
            while os.path.exists(self.workdir+"_"+str(num)): num+=1
            self.workdir+="_"+str(num)
            
        # Make this workdir
        os.system("mkdir -p "+self.workdir)
        # Copy sample config file over to now workdir
        os.system("cp -p "+self.cff+" "+self.workdir)
        print "working directory:",self.workdir,"\n"

    #########################
    # CREATE CRAB CONFIG FILE
    #########################
    def setupCrabJobs(self,runmode):
        
        #=======================================================================
        # Check runmode
        #=======================================================================
        if not ( runmode == "PAT" or runmode == "TREE" ):
            print "ERROR : Unrecognized runmode ",runmode
            print "Please choose from PAT (for making Pat tuples) or TREE (for making the trees)"
            sys.exit(1)
        
        #=======================================================================
        # Get template crab config file
        #=======================================================================
        # Open template crab file
        infile=open(self.cmssw_base+"/src/SampleFiles/Tools"\
                    +"/test/crabTemplate.cfg","r")
        
        # Find and open output conf
        if self.workdir=="":
            print "ERROR: need to create working dir before creating crab.cfg"
            sys.exit(1)
        self.crabConf=self.workdir+"/crab.cfg"
        outfile=open(self.crabConf,"w")

        #=======================================================================
        # Get data quality definition if applicable
        #=======================================================================
        if self.sampleJSON!="":
            os.system("cd "+self.workdir+"; wget --no-check-certificate -O json.txt "+self.sampleJSON)

        #==============================================================================
        # Change crab config file so it uses info from sample cff file from the workdir
        # Different options if this is PAT tuple or tree creation
        #==============================================================================
        pythonId=self.packageNamePython+".samples"
        for line in infile.readlines():
            
            if line.find("#")>=0: continue
            
            # Change location of CMSSW config
            if line.find("pset")>=0:
                if runmode=="PAT" : outfile.write("pset="+self.workdir+"/makePATtuple_cfg.py\n")
                elif runmode=="TREE" : outfile.write("pset="+self.workdir+"/treeProducer_cfg.py\n")
                
            # Change input dataset
            elif line.find("datasetpath")>=0:
                if runmode=="PAT" : 
                    outfile.write("datasetpath="+self.sampleDataSet+"\n")
                    # Add dbs url if this is private sample in DBS
                    if self.sampleDbsUrl != '':
                        outfile.write("dbs_url="+self.sampleDbsUrl+"\n")
                elif runmode=="TREE" : 
                    outfile.write("datasetpath="+self.samplePatDBSName+"\n")
                    # Always add dbs_url for tree producer
                    outfile.write("dbs_url=https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet\n")


            # Change working dir
            elif line.find("ui_working_dir")>=0:
                outfile.write("ui_working_dir="+self.workdir+"/crabDir\n")
            # Change remote dir
            elif line.find("user_remote_dir")>=0 and line.find("check_user_remote_dir")==-1:
                storePath = line.split("=")[1].strip()
                if storePath != "" and not storePath.endswith("/"):
                    storePath += "/"
                outfile.write("user_remote_dir="+storePath+self.workdir.split("/")[-1]+"\n")
            # Change publish option and name
            elif line.find("publish_data=")>=0 and runmode=="TREE": continue
            elif line.find("publish_data_name")>=0:
                if runmode == "PAT" : outfile.write("publish_data_name="+self.workdir.split("/")[-1]+"\n")
            # Change total number of lumis -> events for MC
            elif line.find("total_number_of_lumis")>=0 and self.sampleType.find("MC")>=0:
                outfile.write("total_number_of_events=-1\n")
            # Change number of jobs to something sensible
            elif line.find("number_of_jobs")>=0:
                nJobs = 0
                if runmode == "PAT":
                    eventsPerJob=10000
                    if self.sampleDataSet.find("QCD")>=0: eventsPerJob=50000
                    elif self.sampleDataSet.find("LongLived")>=0: eventsPerJob=2000
                    nJobs=self.sampleNumEvents/eventsPerJob
                    # Limit to 750 jobs
                    if nJobs > 750: nJobs=750
                    if nJobs==0: nJobs=1
                elif runmode == "TREE":
                    nJobs=50
                    if self.sampleDataSet.find("QCD")>=0: eventsPerJob=10
                    elif self.sampleDataSet.find("DYJetsToLL_M-50")>=0: eventsPerJob=150
                    elif self.sampleDataSet.find("LongLived")>=0: eventsPerJob=2000
                    
                outfile.write("number_of_jobs="+str(nJobs)+"\n")
            # Or if this is data
            elif line.find("lumi_mask")>=0:
                if self.sampleType=="DATA":
                    # get data quality definition if applicable
                    if self.sampleJSON!="":
                        os.system("cd "+self.workdir+"; wget --no-check-certificate -O json.txt "+self.sampleJSON)
                        outfile.write("lumi_mask="+self.workdir+"/json.txt\n")
                        pass
                    # Problem - this is data but no JSON provided?
                    else:
                        print "ERROR : This is a data sample, but no JSON file provided"
                        sys.exit(1)
                        pass
                    pass
                pass
            else:
                outfile.write(line)
        infile.close()
        outfile.close()
        pass
    pass        

    ######################
    # CREATE BATCH SCRIPTS
    ######################
    def run_batch_jobs(self,inputfiles,runmode):

        # Calculate number of jobs, limit to 40
        # Could do a better attempt here?
        numJobs=min(40,(len(inputfiles)/5)+1)
        
        if ( self.sampleDataSet.find("DYJetsToLL_M-50")>=0 ):
            # More jobs for DY
            numJobs=min(150,(len(inputfiles)/4)+1)
            pass
        elif ( self.sampleDataSet.find("QCD")>=0 ):
            # Less jobs for QCD
            numJobs=min(5,(len(inputfiles)/5)+1)
            pass
        
        # Number of input files per job
        nInputFiles = len(inputfiles)
        numFilesPerJob = nInputFiles/numJobs
        numFileFinalJob = nInputFiles%numJobs
        
        if numFilesPerJob * numJobs + numFileFinalJob != nInputFiles:
            print "ERROR : numFilesPerJob * numJobs + numFileFinalJob != nInputFiles"
            sys.exit(1)

        # Read original config file
        origconfigfile=open(self.cmssw_base+"/src/TreeProducer/TreeProducer/test/treeProducer_cfg.py","r")
        origconfig=origconfigfile.readlines()
        origconfigfile.close()
        # Create one script per job
        for i in range(numJobs+1):
            # Set up config file for this job
            # Essentially copy original one
            configfile=open(self.workdir+"/job"+str(i+1)+"_cfg.py","w")
            for line in origconfig:
                if line.find("fileNames = cms.untracked.vstring")>=0 :
                    configfile.write("fileNames = cms.untracked.vstring()\n")
                    pass
                elif line.find("fileName = cms.string")>=0 :
                    configfile.write('fileName = cms.string("")\n')
                    pass
                elif line.find("from SampleFiles.Samples.Debug_sample_cff import *")>=0 :
                    # Config needs to read correct input cff file
                    configfile.write("from SampleFiles.Samples.%s_cff import *\n" % (self.id))
                else :
                    configfile.write(line)
                    pass
                
#            # Temporary directory for...
#            if runmode=="RAL":
#                tmp_dir="/scratch"
#            else:
#                tmp_dir="/tmp"
#                
#            tmp_dir+="/"+self.workdir.replace("/","_")
            
            # RAL specialities
            if runmode=="RAL": self.workdir = self.workdir.replace("/net/unixfsrv","/home")


            # Append file list for this job at end of config
            configfile.write("process.source.fileNames = [\n")
            for k in range(i*numFilesPerJob, min((i+1)*numFilesPerJob,nInputFiles)):
                configfile.write("  \""+inputfiles[k]+"\",\n")
                pass
            
            # Add few more files to final job
            if ( i==numJobs ) and ((i+1)*numFilesPerJob < nInputFiles ) and ( (i+2)*numFilesPerJob>nInputFiles ):
                for l in range ( (i+1)*numFilesPerJob, nInputFiles ):
                    configfile.write("  \""+inputfiles[l]+"\",\n")
                    pass
                pass
            
            configfile.write("]\n")
    
            # Specify histogram file name
            outputfilename="histograms_"+str(i+1)+".root"
            configfile.write("process.TFileService.fileName=\""\
                         +self.workdir+"/"+outputfilename+"\"\n")
            
            configfile.close()
            
            # Write submission script
            jobscript=open(self.workdir+"/job"+str(i+1)+".sh","w")
            jobscript.write("#!/bin/bash\n")
#            jobscript.write("mkdir -p "+tmp_dir+"\n")
            jobscript.write("cd "+self.cmssw_base+"/src\n")
            jobscript.write("export SCRAM_ARCH=slc5_amd64_gcc462\n") # For CMSSW_5+
            jobscript.write("eval `scramv1 runtime -sh`\n")
            jobscript.write("cmsRun "+self.workdir+"/job"+str(i+1)+"_cfg.py\n")
#            jobscript.write("cp "+tmp_dir+"/histograms_"+str(i+1)+".root "+self.workdir)
            
            jobscript.close()

                
            # Make submission script executable
            os.system("chmod u+x "+self.workdir+"/job"+str(i+1)+".sh")
            
            # Submit batch jobs
            if runmode=="CERN":
                batchcommand="cd "+self.workdir+"; bsub -q 1nd job"+str(i+1)+".sh"
            elif runmode=="RAL":
                batchcommand="cd "+self.workdir+"; qsub -q prod -l cput=8:00:00,walltime=12:00:00,mem=1gb job"+str(i+1)+".sh"
            else:
                print "ERROR: No idea how to run jobs at",runmode,"....yet"
                sys.exit(1)

            result=os.popen(batchcommand).readlines()
            
            # Keep track of list of jobs
            joblist=open(self.workdir+"/joblist","a")
            for line in result:
                joblist.write(line)
                print line,
            joblist.close()
            pass
        pass
    



#############################################
#############################################
#############################################
#############################################
### END OF AnalysisSample
#############################################
#############################################
#############################################
#############################################

#############################################
### SCAN SAMPLE DESCRIPTION FILE
#############################################

def sample_cff_code(file):
    # is this a file or a directory?
    if not file.find("_cff.py")>0 or not os.path.exists(file):
        print "ERROR: no sample description file",file
        sys.exit(1)
        pass

    samplefile=open(file,"r")
    content=""
    for line in samplefile.readlines():
        content+=line
        pass
    samplefile.close()
    code=compile(content,"<string>","exec")
    return code


#===============================================================================
# Crab Job Tools
#===============================================================================
def createCrabJob(crabCfg):
    if crabCfg=="":
        print "ERROR: No crab cfg provided - cannot create crab job"
        sys.exit(1)
        pass

    # Create job
    print "Creating crab job for :",crabCfg
    print ""
    os.system("crab -create -cfg "+crabCfg)
    
    print "Job created"
    print ""
    pass

def submitCrabJob(crabDir):
    if crabDir=="":
        print "ERROR: No crab directory provided - cannot submit crab job"
        sys.exit(1)
        pass

    # Submit job
    print "Submitting crab job for :",crabDir
    print ""
    os.system("crab -submit -c "+crabDir)
    
    print "Job submitted"
    print ""
    pass

# Run crab -report for this crab directory
def reportCrabJob(crabDir):
    if crabDir=="":
        print "ERROR: No crab directory provided - cannot report crab job"
        sys.exit(1)
        pass

    # Run crab -report
    print "Running crab -report for :",crabDir
    print ""
    os.system("crab -report -c "+crabDir)
    
    print "Done"
    print ""
    pass

# Run crab -getoutput for this crab directory
def getOutputCrabJob(crabDir):
    if crabDir=="":
        print "ERROR: No crab directory provided - cannot get crab output"
        sys.exit(1)
        pass

    # Run crab -getoutput
    print "Running crab -getoutput for :",crabDir
    print ""
    os.system("crab -getoutput -c "+crabDir)
    
    print "Done"
    print ""
    pass

# Publish PAT tuples for this crab directory
# And try to return published name in DBS
def publishPATOutput(crabDir):
    if crabDir=="":
        print "ERROR: No crab directory provided - cannot publish PAT tuples"
        sys.exit(1)
        pass

    print "Publishing PAT tuples for :",crabDir
    print ""
    result=os.popen("crab -publish -c "+crabDir).readlines()

    # Attempt to find published DBS name
    publishedDBSName=""
    goodLine=""
    interestingText=" in dataset: "
    for line in result:
        if line.find(interestingText)>=0:
            goodLine=line
        pass
    
    publishedDBSName=goodLine[goodLine.find(interestingText)+len(interestingText):].strip()
    
    print "Published dataset name : ",publishedDBSName
    print "Done\n"
    return publishedDBSName

# Run lumiCalc2.py and store output
def runLumiCalc(jsonFile,trigger,output):
    if jsonFile=="":
        print "ERROR: No json file provided - cannot run lumiCalc"
        sys.exit(1)
        pass
    
    if trigger=="":
        print "ERROR: No trigger provided."
        print "If you really want to run lumiCalc2.py -recorded for all hltpaths (takes a long time), pass * as the trigger"
        sys.exit(1)
        pass
    
    if output=="":
        print "ERROR: No output file provided for lumiCalc2.py"
        sys.exit(1)
        pass
    
    # Run lumiCalc2.py
    print "Running lumiCalc2.py for trigger :",trigger," and json file : ",jsonFile
    os.system("lumiCalc2.py recorded -i "+jsonFile+" --hltpath "+trigger+" -o "+output)
    
    print "Done"
    print ""
    pass

# Read the output of lumiCalc and return delivered and recorded lumi
def readLumiCalcOutput(lumiCalcOutput,interestingTrigger):
    if lumiCalcOutput=="":
        print "ERROR: No lumiCalc2.py output to read."
        sys.exit(1)
        pass
    if interestingTrigger=="":
        print "ERROR: No trigger provided to readLumiCalc."
        sys.exit(1)
        pass
    
    lumiCSV=open(lumiCalcOutput,"r")
    deliveredLumi = 0
    recordedLumi = 0
    
    for line in lumiCSV:
        # Remove random number of annoying commas in selected LS entry
        line=line.replace('], ',']')
        line=line.replace('"','')
    
        # Separate entries
        line=line.split(",")

        trigger = line[3]
    
        # Accumulate delivered and recorded lumi for our interesting trigger
        if trigger.find(interestingTrigger)>=0:
            deliveredLumi += float(line[2])
            recordedLumi += float(line[-1])
            pass
        pass
    return [deliveredLumi,recordedLumi]

# Analyse lumi info
# Run lumiCalc2.py and read output
def analyseLumi(workdir,analysisSample):
    # Work out which trigger to pass to lumiCalc2.py
    trigger=""
    if workdir.find("Mu") != -1:
        trigger="HLT_L2DoubleMu*"
        pass
    else:
        trigger="HLT_DoublePhoton*HEVT*"
        pass
    
    # Run lumiCalc2.py
    runLumiCalc(workdir+"/crabDir/res/lumiSummary.json ",trigger,workdir+"/lumiCalcOutput.txt")
    deliveredLumi = 0
    recordedLumi = 0
    
    # Work out which trigger to pass to readLumiCalc
    # More exact than and slightly different format to that specified lumiCalc2.py
    trigger=""
    if workdir.find("Mu") != -1:
        trigger="HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v"
        pass
    else:
        trigger="HLT_DoublePhoton48_HEVT_v"
        pass
    # Read lumi calc output
    [deliveredLumi, recordedLumi] = readLumiCalcOutput(workdir+"/lumiCalcOutput.txt",trigger)
    
    print "==========================================================================="
    print "=== For dataset : ",analysisSample.id
    print "=== For trigger name containing : ",trigger
    print "---> Delivered Luminosity : ",deliveredLumi/1000000," /pb"
    print "---> Recorded Luminosity : ",recordedLumi/1000000," /pb"
    print "==========================================================================="
    
    # Save this result to a file in AnalysisMacros directory for later
    analysisMacroDir=analysisSample.cmssw_base+"/src/AnalysisMacros/LumiFiles/"
    lumiFile=analysisMacroDir+"lumi_"+analysisSample.id+".txt"
    # Check if file exists, move it if it does
    checkAndMoveOldFile(lumiFile)
    
    # Write new file
    writeLumiFile=open(lumiFile,"w")
    writeLumiFile.write( workdir.split("/")[-2]+"\n" )
    writeLumiFile.write( "Delivered Lumi : "+str(deliveredLumi)+"\n" )
    writeLumiFile.write( "Recorded Lumi : "+str(recordedLumi)+"\n" )
    writeLumiFile.close()
    pass
    
def runPileUpCalc(workdir,lumiJson,output):
    if workdir=="":
        print "ERROR: No workdir provided"
        sys.exit(1)
        pass
    if lumiJson=="":
        print "ERROR: No lumi json file provided - cannot run pileupCalc.py"
        sys.exit(1)
        pass
    if output=="":
        print "ERROR: No output file provided for pileupCalc.py"
        sys.exit(1)
        pass
    
    # Get pileup json file
    print "Getting pileup json file"
    os.system("cd "+workdir+"; cp /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/PileUp/pileup_JSON_DCSONLY_190389-206448_corr.txt pileupJson.txt")
#    os.system("cd "+workdir+"; cp /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions12/8TeV/PileUp/pileup_JSON_DCSONLY_190389-200041_pixelcorr.txt pileupJson.txt")

    
    # Run pileup calc
    print "Running pileupCalc.py"
    os.system("pileupCalc.py -i "+lumiJson+" --inputLumiJSON "+workdir+"/pileupJson.txt --calcMode true --minBiasXsec 69400  --maxPileupBin 60 --numPileupBins 300 "+output)
    pass

def getPUInfo(workdir,analysisSample):
    # Run pileupCalc.py
    runPileUpCalc(workdir,workdir+"/crabDir/res/lumiSummary.json ",workdir+"/pileup.root")

    # Store results of pileupCalc in AnalysisMacro directory for later
    analysisMacroDir=analysisSample.cmssw_base+"/src/AnalysisMacros/PileupFiles/"
    pileupFile=analysisMacroDir+"pileup_"+analysisSample.id+".root"
    # Move old version first
    checkAndMoveOldFile(pileupFile)

    # Copy in new version
    os.system("cp "+workdir+"/pileup.root "+pileupFile)
    pass

# Check if file exists.  If it does, move it to file.old
def checkAndMoveOldFile(file):
    if os.path.exists(file):
        os.system("mv "+file+" "+file+".old")
        pass
    pass


