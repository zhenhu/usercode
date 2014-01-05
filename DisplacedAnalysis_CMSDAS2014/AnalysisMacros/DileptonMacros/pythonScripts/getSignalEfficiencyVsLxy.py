import os,sys,ROOT
from ROOT import gROOT
from commonMethods import *
  
ROOT.gROOT.Macro( 'tdrstyle.C' )
ROOT.gStyle.SetPadTopMargin(0.1);
ROOT.gStyle.SetPadLeftMargin(0.15);
ROOT.gStyle.SetPadRightMargin(0.05);
# ROOT.gROOT.SetBatch()
ROOT.gStyle.SetLineWidth(3)

orderedSamples = [
                  '1000_350',
#                   '1000_150',
#                   '1000_20',
#                   '400_150',
                  '400_50',
                  '1000_148',
                  ]
                 
files={
       '1000_350' : 'CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_combined_',
#        '1000_150' : 'CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF150_CTau10To1000_combined_',
#        '1000_20' : 'CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF20_CTau1p5To150_combined_',
#        '400_150' : 'CombinedFiles/HTo2LongLivedTo4F_MH400_MFF150_CTau40To4000_combined_',
     '400_50' : 'CombinedFiles/HTo2LongLivedTo4F_MH400_MFF50_CTau8To800_combined_',
    '1000_148' : 'CombinedFiles/Chi0ToNuLL_MSquark1000_MChi148_combined_',
       }

legendEntries={
       '1000_350' : 'm_{H}=1000 GeV, m_{X}=350 GeV',
       '1000_150' : 'm_{H}=1000 GeV, m_{X}=150 GeV',
       '1000_20' : 'm_{H}=1000 GeV, m_{X}=20 GeV',
       '400_150' : 'm_{H}=400 GeV, m_{X}=150 GeV',
       '400_50' : 'm_{H}=400 GeV, m_{X}=50 GeV',
       '1000_148' : 'm_{#tilde{q}} = 1000 GeV, m_{#tilde{#Chi}^{0}_{1}} = 148 GeV'
       }

nExo=[
      "one",
#     "two"
      ]
channels=[
        '2muTrack',
        '2eTrack'
          ]

useCollinearityMethod = True


varName="genLxy"
units="L_{xy} [cm]"
rebinFactor=4
xmin=0
xmax=60
ymin=0.
ymax=2
logY=True
legend=ROOT.TLegend(0.15,0.15,0.55,0.53)


#varName="nRecoPV"
#units="#"
#rebinFactor=4

# varName="XPt"
# units="X p_{T} [GeV]"
# rebinFactor=3
# xmin=1
# xmax=800
# ymin=0
# ymax=1.2
# logY = False
# legend=ROOT.TLegend(0.3,0.5,0.7,0.9)


for channel in channels:
    
    nOneHists = {}
    nTwoHists = {}
    
    for file in files:
        # Open file
        openFile=ROOT.TFile.Open(files[file]+channel+'.root')
    
        for n in nExo:
            print "Producing efficiency plot for",n,channel
            print "Getting histos..."
            print files[file]+channel+'.root'
            
            # Clear legend
            legend.Clear()
            # Get all and passed histograms
            histAll = ROOT.TH1F( openFile.Get("allExotics_"+n+"_"+varName) )
            histPass = ROOT.TH1F()
            if useCollinearityMethod:
                histPass = ROOT.TH1F( openFile.Get("recoExotics_coll_"+n+"_"+varName) )
            else :
                histPass = ROOT.TH1F( openFile.Get("recoExotics_"+n+"_"+varName) )
                pass
            
            histAll.Sumw2()
            histPass.Sumw2()
            
            if rebinFactor > 1 :
                histAll.Rebin(rebinFactor)
                histPass.Rebin(rebinFactor)
            
            print "Integral of histAll :",histAll.Integral()
            print "Integral of histPass :",histPass.Integral()
            print "Integrated efficiency :",histPass.Integral()/histAll.Integral()
            
            # Make trigger effic
            print "Making TEffic..."
            recoEffic=ROOT.TGraphAsymmErrors()
            recoEffic.Divide( histPass, histAll, "n" )
            recoEffic.GetXaxis().SetLimits(xmin,xmax)
            
            if n is 'one' :
                nOneHists[file] = recoEffic
            elif n is 'two' :
                nTwoHists[file] = recoEffic
                pass
            pass

        openFile.Close()
        pass
        
    # Draw all plots
    canvas=ROOT.TCanvas("canvas")
#     legend=ROOT.TLegend(0.65,0.65,0.9,0.87)
    legend.SetFillStyle(0)
    legend.SetBorderSize(0)
    firstPlot = True
    colour = 2
    for hist in orderedSamples :
        if firstPlot :
            nOneHists[hist].Draw("AP")
            legend.AddEntry(nOneHists[hist],legendEntries[hist],'PL')
            firstPlot = False
            pass
        else :
            nOneHists[hist].Draw("P")
            legend.AddEntry(nOneHists[hist],legendEntries[hist],'PL')
            pass
        
        nOneHists[hist].SetMarkerColor( colour )
        nOneHists[hist].SetLineColor( colour )
        colour = colour + 1
        if colour is 5 : colour = colour + 1
        nOneHists[hist].SetMaximum(ymax)
        nOneHists[hist].SetMinimum(ymin)
        nOneHists[hist].GetYaxis().SetTitle("Efficiency")
        nOneHists[hist].GetXaxis().SetTitle(units)
        canvas.Update()
        pass
    

    # Add title
    T1 = ROOT.TLatex()
    T1.SetNDC()
    T1.DrawLatex(0.2,0.96,"#scale[0.9]{CMS Simulation #sqrt{s} = 8 TeV}")
    
    # Draw legend
    legend.Draw()
    
    # Add channel latex
    addChannelLatex(channel, 0.2, 0.8)
    
    if logY : canvas.SetLogy()

    canvas.Update()
    if useCollinearityMethod :
        outputFileName='output/pdfOutput/efficiency_Vs_'+varName+'_'+n+'_coll_'+channel+'.pdf'
        pass
    else :
        outputFileName='output/pdfOutput/efficiency_Vs_'+varName+'_'+n+'_'+channel+'.pdf'
        pass
    print 'Saving as :',outputFileName
    canvas.Print(outputFileName)
    raw_input("Press Enter to continue...")
    pass
        
