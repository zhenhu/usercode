import os,sys

# For each sample cff file, this script will remove any duplicate PATfiles
# e.g. if PATtuple_39_1_Sif.root and PATtuple_39_2_TQf.root exist on the storage element at the same directory
# This may mean that crab aborted/failed on job 39 but most of the output file made it back to the SE
# After resubmitting and succeeding it produced another (larger) PAT file on the SE
# Need to remove these from being inputted to the TreeProducer to avoid double counting
# Also messes up lumiCalc as crab is not aware of these extra jobs being put into Tree Producer!

# Note: Above is a guess, but removing these extra files improved the agreement between data and MC in control plots

dir="/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/SampleFiles/Samples/python/"

sampleCffFiles=[#"Data_Photon_Run2012A1_cff.py",
                #"Data_Photon_Run2012A2_cff.py",
                #"Data_Photon_Run2012B1_cff.py",
                #"Data_Photon_Run2012C1_cff.py",
                #"Data_Photon_Run2012C2_cff.py",
                #"Data_Photon_Run2012D1_cff.py",
                #"Data_Mu_Run2012A1_cff.py",
                #"Data_Mu_Run2012A2_cff.py",
                #"Data_Mu_Run2012B1_cff.py",
                #"Data_Mu_Run2012C1_cff.py",
                #"Data_Mu_Run2012C2_cff.py",
                "Data_Mu_Run2012D1_cff.py",
]

for sample in sampleCffFiles:
    
    sampleCffFile=dir+sample
    
    # Read original file
    originalCff=open(sampleCffFile,"r")
    originalCffLines=originalCff.readlines()
    originalCff.close()
    
    # New file for output
    newCff=open(sampleCffFile+".new","w")
    
    # List of PAT file numbers
    PATfileNumbers=[]
    
    seen=[]
    duplicates=[]
    
    cleanedPATList=[]
    
    # Get list of PAT files
    for line in originalCffLines:
        if line.find('sampleBaseDir+"PATtuple_')>=0:
            # Store number of PAT files
            n = line.split('"')[1].split('_')[1]
#            print line,n
            if n not in seen:
                seen.append(n)
                cleanedPATList.append(line)
                pass
            else : duplicates.append(int(n))
            pass
        elif( line.find(']') >= 0 ) : continue
        else:
            newCff.write(line)
        pass
    
    # Got list of PAT duplicate numbers
    duplicates.sort()
    seen.sort()
    
    # Output info to screen
    print "Found ",len(duplicates),"duplicates in ",sample
    print "List of files : "
    for file in duplicates:
        print file
        pass
    print "\n"
    
    for line in cleanedPATList:
        newCff.write(line)
#        print line.strip()
        pass
    
    newCff.write("]")
    newCff.close()
    
    # Move files around
    os.system("mv "+sampleCffFile+" "+sampleCffFile+".old;")
    os.system("mv "+sampleCffFile+".new "+sampleCffFile+";")
    

