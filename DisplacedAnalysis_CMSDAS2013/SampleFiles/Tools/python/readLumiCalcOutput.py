#
# Run this on the output of lumicalc2.py
# e.g. : lumiCalc2.py recorded -i crabDir/res/lumiSummary.json --hltpath "HLT_L2DoubleMu23*" -o lumiCalcOutput.txt
#
# lumiSummary.json is the json file from crab -report (usually in the crab directory of the job)
# hltpath is the hltpath you are interested in.  Takes wildcards.
# lumiCalcOutput.txt will contain the output (which is input to this script)
#
# Below, interestingTrigger is the hlt path pattern you want to work out how much lumi has been recorded by it
#
# Note in 2012A, there were some runs where our usually unprescaled triggers were prescaled, so delivered may != recorded lumi
#

import os,sys

#lumiCSV=open("lumiCalcOutput.txt","r")
#lumiCSV=open("workdirs/Data_Mu_Run2012A1_pat_20120702/lumiCalcOutput.txt","r")
lumiCSV=open("workdirs/Data_Mu_Run2012B1_pat_20120718/lumiCalcOutput.txt","r")
#lumiCSV=open("workdirs/Data_Photon_Run2012A1_pat_20120702/lumiCalcOutput.txt","r")
#lumiCSV=open("workdirs/Data_Photon_Run2012B1_pat_20120702/lumiCalcOutput.txt","r")

interestingTrigger = "HLT_L2DoubleMu23_NoVertex_2Cha_Angle2p5_v"
#interestingTrigger = "HLT_DoublePhoton48_HEVT_v"

deliveredLumi = 0
recordedLumi = 0

for line in lumiCSV:
    
    # Remove random number of annoying commas in selected LS entry
    line=line.replace('], ',']')
    line=line.replace('"','')
    
    # Seprate entries
    line=line.split(",")

    trigger = line[3]
    
    # Accumulate delivered and recorded lumi for our interesting trigger
    if trigger.find(interestingTrigger)>=0:
        deliveredLumi += float(line[2])
        recordedLumi += float(line[-1])
        pass
    pass

# Results
print "==========================================================================="
print "=== For trigger name containing : ",interestingTrigger
print "---> Delivered Luminosity : ",deliveredLumi/1000000," /pb"
print "---> Recorded Luminosity : ",recordedLumi/1000000," /pb"
print "==========================================================================="
