import os,sys
from ROOT import gROOT

def setup():
    gROOT.ProcessLine('.include '+os.getcwd()[:os.getcwd().find('src')+4])
    gROOT.ProcessLine('.L ../CommonMacros/analysisType.h')
    gROOT.ProcessLine('.L ../CommonMacros/fullCombination.C+')
    pass

if len(sys.argv)<2:
    print "ERROR : Please provide anaType"
    print '0 ---> _2eTrack'
    print '1 ---> _2muTrack'
    print '2 ---> _2globalOrTrackerMu'
    print '3 ---> _2globalMu'
    print '4 ---> _2trackerMu\n'
    sys.exit(1)
    
gROOT.SetBatch()
anaType=sys.argv[1]

setup()
gROOT.ProcessLine('analysisType a='+anaType)
gROOT.ProcessLine('fullCombination(a)')
