import os,sys,ROOT
from ROOT import gROOT

ROOT.gROOT.Macro( 'tdrstyle.C' )
ROOT.gStyle.SetPadTopMargin(0.1);
ROOT.gStyle.SetPadLeftMargin(0.15);
ROOT.gStyle.SetPadRightMargin(0.05);


files=[
#"WeightedFiles/HTo2LongLivedTo4F_MH400_MFF150_CTau40To4000_analysis_20130129_1_weighted_2muTrack.root",
#"../../../../../PPDCheck/CMSSW_6_1_0/src/AnalysisMacros/DileptonMacros/WeightedFiles/PPD_MH400_MFF150_CTau40To4000_analysis_20130130_weighted_2muTrack.root",

#"WeightedFiles/HTo2LongLivedTo4F_MH125_MFF50_CTau50To5000_analysis_20130130_weighted_2muTrack.root",
"CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_combined_2muTrack.root",
       ]

varName="d0"
units="cm"

plotsToDraw=[]

legend=ROOT.TLegend( 0.6, 0.6, 0.9, 0.8 )

# Loop over files and get histograms
for file in files:
    print "Processing ",file
    # Open file
    openFile=ROOT.TFile.Open(file)
    print "Getting histos..."
    # Get all and passed histograms
    histAll = ROOT.TH1F( openFile.Get("all_"+varName) )
    histPass = ROOT.TH1F( openFile.Get("reco_"+varName) )
    
    print "Integral of histAll :",histAll.Integral()
    print "Integral of histPass :",histPass.Integral()

    # Make trigger effic
    print "Making TEffic..."
    trigEffic=ROOT.TEfficiency(histPass,histAll)
    
    trigEffic.SetMarkerColor( files.index(file) + 2 )
    trigEffic.SetLineColor( files.index(file) + 2 )
    
    plotsToDraw.append(trigEffic)
    
    startName=file.find("MH")
    endName=file.find("analysis")-1
    name=file[startName:endName]
    if file.find("PPD") >=0: name = "610_"+name
    legend.AddEntry( trigEffic, name, "p")
    
    openFile.Close()
    pass

# Now draw histos
canvas=ROOT.TCanvas("canvas")
firstPlot=True
print "Drawing histograms..."
print "Number of plots to draw :",len(plotsToDraw)
for plot in plotsToDraw:
    
    plot.SetMarkerStyle(21)
    plot.SetMarkerSize(1)

    # Draw histo
    if firstPlot:
        plot.Draw()
    else:
        plot.Draw("SAME")
        pass

    # Update canvas and set y axis limits    
    canvas.Update()
    paintedGraph=plot.GetPaintedGraph()
    paintedGraph.SetMaximum(1)
    paintedGraph.SetMinimum(0)
    paintedGraph.GetXaxis().SetRangeUser(0,100)
    paintedGraph.GetYaxis().SetTitle("Efficiency")
    paintedGraph.GetXaxis().SetTitle(varName+" ["+units+"]")
    canvas.Update()

    firstPlot=False
    pass

# Draw legend
legend.Draw()
canvas.Update()
canvas.Print("trackingEfficiency_538_"+varName+".png")
canvas.Print("trackingEfficiency_538_"+varName+".pdf")

raw_input("Press Enter to continue...")