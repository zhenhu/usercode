import os,sys,ROOT
from ROOT import gROOT

ROOT.gROOT.Macro( 'tdrstyle.C' )
ROOT.gStyle.SetPadTopMargin(0.1);
ROOT.gStyle.SetPadLeftMargin(0.15);
ROOT.gStyle.SetPadRightMargin(0.05);


files=[
"WeightedFiles/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_analysis_20121212_weighted_2eTrack.root",
#"WeightedFiles/HTo2LongLivedTo4F_MH1000_MFF50_CTau4To400_analysis_20121211_weighted_2eTrack.root",
"WeightedFiles/HTo2LongLivedTo4F_MH400_MFF150_CTau40To4000_analysis_20121217_weighted_2eTrack.root",
"WeightedFiles/HTo2LongLivedTo4F_MH400_MFF50_CTau40To4000_analysis_20121212_weighted_2eTrack.root",
#"WeightedFiles/HTo2LongLivedTo4F_MH400_MFF20_CTau40To4000_analysis_20121217_weighted_2eTrack.root",
"WeightedFiles/HTo2LongLivedTo4F_MH200_MFF50_CTau20To2000_analysis_20121212_weighted_2eTrack.root",
"WeightedFiles/HTo2LongLivedTo4F_MH120_MFF50_CTau50To5000_analysis_20121217_weighted_2eTrack.root",
       ]

varName="Lxy"
#varName="ctau"
units="cm"

plotsToDraw=[]
#for plot in range (len(files)): plotsToDraw.append( ROOT.TH1F() )

legend=ROOT.TLegend( 0.6, 0.6, 0.9, 0.8 )

# Loop over files and get histograms
for file in files:
    print "Processing ",file
    # Open file
    openFile=ROOT.TFile.Open(file)
    print "Getting histos..."
    # Get all and passed histograms
    histAll = ROOT.TH1F( openFile.Get("trig_"+varName+"_all") )
    histPass = ROOT.TH1F( openFile.Get("trig_"+varName+"_pass") )
    
    # Rebin if ctau
    if varName is "ctau":
        histAll.Rebin(5)
        histPass.Rebin(5)
        pass
    
    print "Integral of histAll :",histAll.Integral()
    print "Integral of histPass :",histPass.Integral()

    # Make trigger effic
    print "Making TEffic..."
    trigEffic=ROOT.TEfficiency(histPass,histAll)
    
    trigEffic.SetMarkerColor( files.index(file) + 2 )
    trigEffic.SetLineColor( files.index(file) + 2)
    
    plotsToDraw.append(trigEffic)
    
    startName=file.find("MH")
    endName=file.find("analysis")-1
    name=file[startName:endName]
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
    paintedGraph.GetYaxis().SetTitle("Efficiency")
    paintedGraph.GetXaxis().SetTitle(varName+" ["+units+"]")
    canvas.Update()

    firstPlot=False
    pass

# Draw legend
legend.Draw()
canvas.Update()
canvas.Print("triggerEfficiency_"+varName+".png")
canvas.Print("triggerEfficiency_"+varName+".pdf")

raw_input("Press Enter to continue...")