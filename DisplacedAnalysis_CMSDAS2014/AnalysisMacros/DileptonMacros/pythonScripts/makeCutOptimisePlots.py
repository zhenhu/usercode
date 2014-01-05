import os,sys
import ROOT as r
from commonMethods import *

    
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
    inputFiles.append("CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF20_CTau1p5To150_combined_"+channel+".root")
    pass

# Get all TH2F's
allHists=[]
for file in inputFiles:
    histfile=r.TFile.Open(file)
    hist=histfile.Get("minD0SigCut_vs_LxySigCut")
    gROOT.cd()
    allHists.append(hist.Clone())
    histfile.Close()
    pass

lumi=1
if samples is not "DATA":
    lumiFile = "../LumiFiles/lumi_electron.txt"
    if channel.find("mu")>=0 :
        lumiFile = "../LumiFiles/lumi_muon.txt"
        pass
    # Extract lumi from file
    openFile=open(lumiFile,"r")
    lumi=float(openFile.readline().strip())
    openFile.close()
    print "Will normalise to ",lumi,"\\fb"
    pass

# Add all hists together
finalHist=allHists[0]
if len(allHists)>1:
    for index in range(1,len(allHists)):
        finalHist.Add(allHists[index])
        pass

canvas = r.TCanvas('can','can',800,800)
gStyle.SetOptStat(0)
gStyle.SetPaintTextFormat(".3g")
set_palette()
finalHist.Scale(lumi)
finalHist.GetXaxis().SetTitle('d_{0}/#sigma cut')
finalHist.GetYaxis().SetTitle('L_{xy}/#sigma cut')
finalHist.GetZaxis().SetRangeUser(0.01,7e5)
canvas.SetLogz()

finalHist.Draw("COLZTEXT")

raw_input()