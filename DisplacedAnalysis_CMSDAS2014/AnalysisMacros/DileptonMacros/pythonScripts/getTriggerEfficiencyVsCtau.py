import sys
import ROOT as r
from array import array

r.gROOT.Macro( 'tdrstyle.C' )
# r.gROOT.SetBatch(1)

# File containing samples to run over and lifetime reweighting factors
from samplesConfig import *

# Common functions between all these scripts which parse text files
# to get signal efficiencies, acceptances etc.
from parseTextFilesTools import *

def storeResult( ctau, effic, error, efficienciesAndErrors):
    
    # Look to see if ctau value is already in output vector
    for entry in efficienciesAndErrors:
        if entry[0]==ctau or abs(entry[0]-ctau) < 0.1:
            # This ctau is already filled
            # Check if stat error is smaller
            if entry[2]>error:
                efficienciesAndErrors[efficienciesAndErrors.index(entry)]=[ctau,effic,error]
                pass
            return
        pass
    
    # Not seen this ctau value before
    efficienciesAndErrors.append([ctau,effic,error])
    return

def sortOutput(outputEfficienciesAndErrors):
    sorted(outputEfficienciesAndErrors, key=lambda x: x[0])
    pass

def workOutBinning(outputEfficienciesAndErrors):
    binning=[]
    # Conversion of ctau from mm to cm here
    binning.append(outputEfficienciesAndErrors[0][0]/2/10)
    for entry in outputEfficienciesAndErrors:
        ctau = entry[0]/10
        if outputEfficienciesAndErrors.index(entry) == len(outputEfficienciesAndErrors)-1:
            binning.append(ctau*2)
            break
        nextCtau = outputEfficienciesAndErrors[outputEfficienciesAndErrors.index(entry)+1][0]/10
        binning.append(ctau+abs(nextCtau-ctau)/2)
        pass
    return binning

#===============================================================================
# START OF CODE
#===============================================================================


# Loop over different signal MC samples
for sample in massesAndCtau:
    # Get and store info on this sample
    sInfo = sampleInfo(sample)
    print '---> MH :',sInfo.MH,'MX :',sInfo.MX

    # Loop over different channels (e or mu)
    for channel in channels:
        print "----------------------------------------------------------------------------------------------------------------"
        print "Trigger Efficiencies for MH :",sInfo.MH," MX :",sInfo.MX," Central Ctau (mm) :",sInfo.ctauCentral," Channel :",channel
        print "----------------------------------------------------------------------------------------------------------------"
        
        # Only interested in n = 1 case
        n = 'one'
        
        # Get files
        allFile="EfficiencyFiles/rawFiles/effic_allExotics_"+channel+"_HTo2LongLivedTo4F_MH"+sInfo.MH+"_MFF"+sInfo.MX+"_CTau"+sInfo.ctauSmall+"To"+sInfo.ctauBig+"_"+n+"Decay.txt"

        # Open and read files
        allExo=[]
        getEfficiencyExoticsFromFile( allFile, allExo )
        
        # Storage for efficiency and stat error at each ctau value
        # If a ctau value is already filled, it will be over written if the stat error of the new possible entry is smaller
        outputEfficienciesAndErrors=[]
        
        outputEfficienciesMap = {
                                 '6001113':[],
                                 '6002113':[], 
                                 '6003113':[],
                             }
        outputHistMap = {
              '6001113':r.TH1F(),
              '6002113':r.TH1F(),
              '6003113':r.TH1F(),
              }
        
        for pdg in signalPdg:
            # Get efficiency for different lifetime exotics
            # Avoid signal pdgs which don't occur in sample
            if sInfo.signature=='C' and pdg!='1000022' : continue
            elif sInfo.signature=='H' and pdg=='1000022' : continue
            
            # Get ctau of this exotic
            originalCtau=getOriginalCtau(sInfo,pdg)
            
            print "+++> New exotic pdgid"
            print "Signal pdg :",pdg
            print "Original ctau of exotic (mm) : ",originalCtau,"\n"
            
            # And for different reweighted lifetimes
            for lifeTimeFact in lifeTimeFactors:
                
                newCtau=originalCtau*lifeTimeFact
#                 print "Reweighting by factor : ",lifeTimeFact,'to',newCtau
                
                decayProducts = ''
                if channel == '2muTrack' or channel == "2globalOrTrackerMu" :
                    decayProducts='13'
                elif channel == '2eTrack' :
                    decayProducts='11'

                swDenom=sumWeights( getEfficiencySumWeights( allExo, pdg, lifeTimeFact, originalCtau/10, decayProducts, 1, False, True, False ) )
                swNum=sumWeights( getEfficiencySumWeights( allExo, pdg, lifeTimeFact, originalCtau/10, decayProducts, 1, True, True, False ) )
                 
                # Get trigger efficiency
                effic = -1
                statError = -1
                relError = -1
                if swDenom.s > 0 : 
                    effic=swNum.s/swDenom.s
                    # Get stat error
                    if swNum.s > 0:
                        statError = getStatError( swNum, swDenom)
                        relError = statError/effic
             
                if relError > 0.1 : continue
                # Output to screen for now
                print "Central efficiency for ctau %.3g : %.3g +/- %.3g" % (newCtau,effic,statError)
                 
                storeResult(newCtau, effic, statError, outputEfficienciesAndErrors)
                
                # Also store all results (for one channel only, for now)
#                 if channel is '2muTrack':
                outputEfficienciesMap[pdg].append([newCtau,effic,statError])
#                     pass
                pass
    
        # Sort output
        sortOutput(outputEfficienciesAndErrors)
        
        # Book & fill histogram
        # Get binning
        # Need number of bins and low edges of each bin
        binning=workOutBinning(outputEfficienciesAndErrors)
        binArray = array("d",binning)
        h_trigEffic = r.TH1F("h_trigEffic","Trigger efficiency vs ctau",len(binning)-1,binArray)
         
        # Fill histogram
        print "Filling histo"
        for entry in outputEfficienciesAndErrors:
            index=outputEfficienciesAndErrors.index(entry)
            h_trigEffic.SetBinContent( index+1, entry[1] )
            h_trigEffic.SetBinError( index+1, entry[2] )
            pass
         
        can=r.TCanvas("can","can",700,800)
        can.SetLogx()
        
        # Decorate plot etc.
        r.gStyle.SetErrorX(0.5) # Override default in tdrstyle.C
        yMax = h_trigEffic.GetMaximum()*1.05
        if yMax > 1 : yMax = 1
        h_trigEffic.SetMinimum(h_trigEffic.GetMinimum()*0.95)
        h_trigEffic.SetMaximum(yMax)
        h_trigEffic.SetMarkerColor(1)
        h_trigEffic.SetLineColor(1)
        h_trigEffic.GetXaxis().SetTitle('Mean c#tau (cm)')
        h_trigEffic.GetYaxis().SetTitle('Trigger Efficiency')
        # Set x range
        xmin=0.01
        xmax=50000
        h_trigEffic.GetXaxis().SetRangeUser(xmin,xmax)
        h_trigEffic.Draw('E1')
        can.Update()
        
        # Add title
        T1 = r.TLatex()
        T1.SetNDC()
        T1.DrawLatex(0.2,0.96,"#scale[0.9]{CMS Simulation #sqrt{s} = 8 TeV}")
        
        latexText = "#mu^{+}#mu^{-}"
        if channel is "2eTrack":
            latexText = "e^{+}e^{-}"
            pass
    
        channelLatex = r.TLatex()
        channelLatex.SetNDC()
        channelLatex.DrawLatex(0.22,0.85,latexText);
        can.Update()
        
        outputFileName='output/pdfOutput/triggerEfficiencyVsCtau_'+channel+'.pdf'
        print 'Saving as :',outputFileName
        can.Print(outputFileName)
        print "Done"

        # Mainly for debugging
        # Plot trigger efficiency for different exotics on one set of axes
        canMu=r.TCanvas("canMu","canMu",700,800)
        canMu.SetLogx()
        stack = r.THStack("stack","stack");
     
        # Fill histograms
        for key in outputEfficienciesMap:
            newBinning=workOutBinning(outputEfficienciesMap[key])
            newBinArray = array("d",newBinning)
            outputHistMap[key] = r.TH1F(key,key,len(newBinning)-1,newBinArray)
              
            for entry in outputEfficienciesMap[key]:
                index=outputEfficienciesMap[key].index(entry)
                outputHistMap[key].SetBinContent( index+1, entry[1] )
                outputHistMap[key].SetBinError( index+1, entry[2] )
                pass
     
            pass
    
        canMu.cd()
        axesExist=False
        colourOffset=0
        yMax=0
        yMin=1
        for key in outputHistMap:
            h=outputHistMap[key]
            h.SetLineColor(2+colourOffset)
            h.SetMarkerColor(2+colourOffset)
              
            if h.GetMaximum()*1.2 > yMax : yMax = h.GetMaximum()*1.05
            if h.GetMinimum()*0.8 < yMin : yMin = h.GetMinimum()*0.95
              
            colourOffset = colourOffset + 1
            stack.Add(h)
            pass
        if yMax > 1 : yMax = 1
        stack.SetMaximum(yMax)
        stack.SetMinimum(yMin)
        stack.Draw('nostack')
        canMu.Update()
        raw_input("Press Enter to continue...")


    