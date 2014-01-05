import os,sys,ROOT
from ROOT import gROOT

ROOT.gROOT.Macro( 'tdrstyle.C' )
ROOT.gStyle.SetPadTopMargin(0.1);
ROOT.gStyle.SetPadLeftMargin(0.15);
ROOT.gStyle.SetPadRightMargin(0.05);


files=[

"BackgroundStudiesFiles/minLeptonD0Sig_unsmeared_removedLifetimeCuts_2eTrack.root",
       ]

sample='BKG'

legend=ROOT.TLegend( 0.6, 0.6, 0.9, 0.8 )

# Loop over files and get histograms
for file in files:
    print "Processing ",file
    # Open file
    openFile=ROOT.TFile.Open(file)
    print "Getting histos..."
    # Get all and passed histograms
    
    histName=""
    if sample=="BKG":histName="Background MC"
    elif sample=="DATA":histName="Data"
    
    histPos = ROOT.TH1F( openFile.Get(histName) )
    nBins = histPos.GetNbinsX()
    maxRange= histPos.GetXaxis().GetBinUpEdge( nBins )
    minRange = histPos.GetXaxis().GetBinLowEdge( 1 )
    # Find bin for x=0
    firstBin = histPos.GetXaxis().FindBin( -1.0 * maxRange )
    binZero = histPos.GetXaxis().FindBin(0)
    print "nBins :",nBins,minRange,maxRange,binZero,firstBin

    # Make a new histogram for negative tail
    histNeg = ROOT.TH1F( "neg", "neg", binZero-firstBin, 0, maxRange)
    nBinsNeg = histNeg.GetNbinsX()
    
    # Fill histogram, but for mod(x) and only for negative tail
    print firstBin,binZero
    for bin in range (firstBin,binZero):
        print bin-firstBin
        histNeg.SetBinContent(bin-firstBin,histPos.GetBinContent(bin))
        pass
    
    canvas=ROOT.TCanvas("canvas")
    histPos.Draw()
    histPos.GetXaxis().SetRangeUser(0,maxRange)
    canvas.Update()
    raw_input("Press Enter to continue...")
    histNeg.Draw("SAME")
    canvas.Update()
    raw_input("Press Enter to continue...")
    openFile.Close()
    pass

# # Now draw histos
# canvas=ROOT.TCanvas("canvas")
# firstPlot=True
# print "Drawing histograms..."
# print "Number of plots to draw :",len(plotsToDraw)
# for plot in plotsToDraw:
#     
#     plot.SetMarkerStyle(21)
#     plot.SetMarkerSize(1)
# 
#     # Draw histo
#     if firstPlot:
#         plot.Draw()
#     else:
#         plot.Draw("SAME")
#         pass
# 
#     # Update canvas and set y axis limits    
#     canvas.Update()
#     paintedGraph=plot.GetPaintedGraph()
#     paintedGraph.SetMaximum(1)
#     paintedGraph.SetMinimum(0)
#     paintedGraph.GetYaxis().SetTitle("Efficiency")
#     paintedGraph.GetXaxis().SetTitle(varName+" ["+units+"]")
#     canvas.Update()
# 
#     firstPlot=False
#     pass
# 
# # Draw legend
# legend.Draw()
# canvas.Update()
# canvas.Print("triggerEfficiency_"+varName+".png")
# canvas.Print("triggerEfficiency_"+varName+".pdf")
# 
# raw_input("Press Enter to continue...")