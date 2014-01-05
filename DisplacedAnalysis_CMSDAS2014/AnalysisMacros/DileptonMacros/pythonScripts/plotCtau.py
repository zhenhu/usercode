import sys
from ROOT import TH1F, TFitResultPtr, TCanvas, Double, TH1, gROOT
from math import exp

gROOT.SetBatch(1)

# Common functions between all these scripts which parse text files
# to get signal efficiencies, acceptances etc.
from parseTextFilesTools import *

sample=[
#         'H',1000,350,350
#         'H',1000,150,100
#     'H',400,50,80
#       'H',125,50,500,
    'C',1500,494,160,
#     'C',1000,148,60
#     'C',350,148,173
#     'C',120,48,165
               ]


## ALL SAMPLES
channel="2muTrack"
n="two"
# signalPdg="6002113"
signalPdg="1000022"
lifeTimeFactors=[1.]
# lifeTimeFactors=[1.,2.,3.,4.]
#lifeTimeFactors=[0.1,0.2,0.4,0.6,1.,5.]

sInfo = sampleInfo(sample)

allFile=''
if sInfo.signature=='H':
    allFile="EfficiencyFiles/rawFiles/effic_allExotics_"+channel+"_HTo2LongLivedTo4F_MH"+sInfo.MH+"_MFF"+sInfo.MX+"_CTau"+sInfo.ctauSmall+"To"+sInfo.ctauBig+"_"+n+"Decay.txt"
elif sInfo.signature=='C':
    allFile="EfficiencyFiles/rawFiles/effic_allExotics_"+channel+"_Chi0ToNuLL_MSquark"+sInfo.MH+"_MChi"+sInfo.MX+"_"+n+"Decay.txt"

allExo=[]
getEfficiencyExoticsFromFile( allFile, allExo )

originalCtau = float(sInfo.ctauCentral) / 10

can = TCanvas('can','can',900,700)
can.Divide(2)
can.cd(1)

for factor in lifeTimeFactors:
    print "Lifetime factor : ",factor
    h = TH1F( 'CtauHist', 'Ctau histo', 100, 0, 400 )
    h.Sumw2()
    
    h_trunk = TH1F( 'CtauHistTrunk', 'Ctau histo truncated', 100, 0, 400)
    h_trunk.Sumw2()

    for exotic in allExo:
        interestingLepton = ''
        if channel == "2muTrack" : interestingLepton = '13'
        elif channel == "2eTrack" : interestingLepton = '11'
        # Exotic 1
        if exotic.pdg1 == signalPdg and exotic.channel1 == interestingLepton:
            # Get event weight
            weight = getLifetimeWeight( factor,originalCtau,float(exotic.ctau1) )
            h.Fill( exotic.ctau1, weight )
            if exotic.ctau1 < originalCtau*3:
                h_trunk.Fill( exotic.ctau1, weight )
            
        # Exotic 2
        if exotic.pdg2 == signalPdg and exotic.channel2 == interestingLepton:
            # Get event weight
            weight = getLifetimeWeight( factor,originalCtau,float(exotic.ctau2) )            
            h.Fill( exotic.ctau2, weight )
            if exotic.ctau2 < originalCtau*3:
                h_trunk.Fill( exotic.ctau2, weight )
            pass
        
    h.Draw('PE')
    fit = TFitResultPtr(h.Fit('expo','s'))
    slope = fit.Parameter(1)
    integral=-1
    error= Double(-1)
    integral = h.IntegralAndError(0,101,error)
    print 'Integral :',integral,'+/-',error
    print "Ctau : ",-1.0/slope,'cm'
    
    can.cd(2)
    
    h_trunk.Draw('PE')
    integral = h_trunk.IntegralAndError(0,101,error)
    print 'Integral of truncated :',integral,'+/-',error
    print 'Scaled up :',integral*1/(1-exp(-3/factor)),'+/-',error*1/(1-exp(-3/factor))
    can.Update()
    can.cd(1)
    raw_input("Press enter...")
    pass
