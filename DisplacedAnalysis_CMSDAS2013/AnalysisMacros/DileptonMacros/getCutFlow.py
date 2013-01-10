import os,sys,ROOT
from ROOT import gROOT

# Two arguments 
# [1] BKG, SIG, DATA
# [2] e or mu
if len(sys.argv)<3:
    print "ERROR: need to say what type of sample to produce cutflow for"
    print "#1 BKG, SIG or DATA"
    print "#2 channel e.g. 2muTrack (see analysisType.h)"
    sys.exit(1)

# Type of sample 
samples=sys.argv[1]
channel=sys.argv[2]

if not (samples=="BKG" or samples=="SIG" or samples=="DATA"):
    print "ERROR: Don't know what this sample is : ",samples
    print "Choose from BKG, SIG or DATA"
    sys.exit(1)
    
if not (channel.find("e")>=0 or channel.find("mu")>=0 or channel.find("Mu")>=0):
    print "ERROR : Won't understand this channel : ",channel
    print "Check in analysisType.h"
    sys.exit(1)
    
# Get input files
inputFiles=[]
if samples=="DATA":
    inputFiles.append("CombinedFiles/Data_combined_"+channel+".root")
    pass
elif samples=="BKG":
    inputFiles.append("CombinedFiles/DYJets_combined_"+channel+".root")
    inputFiles.append("CombinedFiles/TTJets_combined_"+channel+".root")
    inputFiles.append("CombinedFiles/WW_combined_"+channel+".root")
    inputFiles.append("CombinedFiles/WJets_combined_"+channel+".root")
    inputFiles.append("CombinedFiles/ZZ_combined_"+channel+".root")
    inputFiles.append("CombinedFiles/WZ_combined_"+channel+".root")
    inputFiles.append("CombinedFiles/QCD_combined_"+channel+".root")
    pass
elif samples=="SIG":
    inputFiles.append("WeightedFiles/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_analysis_20121101_weighted_"+channel+".root")
    pass

# Get all TProfiles
allCutFlows=[]
for file in inputFiles:
    histfile=ROOT.TFile.Open(file)
    cutFlow=histfile.Get("cutFlow")
    gROOT.cd()
    allCutFlows.append(cutFlow.Clone())
    histfile.Close()
    pass

# Add all together
finalCutFlow=allCutFlows[0]
if len(allCutFlows)>1:
    for index in range (1,len(allCutFlows)):
        finalCutFlow.Add(allCutFlows[index])
        pass
    pass


# Output cut flow to screen (or to a txt file?)
for bin in range(2,finalCutFlow.GetNbinsX()):
    if finalCutFlow.GetXaxis().GetBinLabel(bin) != "":
        if finalCutFlow.GetBinContent(bin-1)==0: print finalCutFlow.GetXaxis().GetBinLabel(bin),"\t\t\t","0.0"
        else : print finalCutFlow.GetXaxis().GetBinLabel(bin),"\t\t\t",(("%.2f") % (finalCutFlow.GetBinContent(bin)/finalCutFlow.GetBinContent(bin-1)*100) )
        pass
    pass
    
#canv=ROOT.TCanvas()
#canv.SetLogy()
#finalCutFlow.Draw()
#
#raw_input()
