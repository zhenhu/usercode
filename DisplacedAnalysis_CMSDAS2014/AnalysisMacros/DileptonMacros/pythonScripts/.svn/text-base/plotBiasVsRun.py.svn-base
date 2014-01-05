import ROOT as r
from commonMethods import *

# r.gROOT.SetBatch()
r.gROOT.Macro( 'tdrstyle.C' )
r.gStyle.SetPadLeftMargin(0.15)
r.gStyle.SetPadRightMargin(0.05)
r.gStyle.SetPadTopMargin(0.1)

inputFile = 'CombinedFiles/Data_combined_2muTrack.root'

# hName = 'singleLeptonD0Significance_vs_run'
hName = 'singleLeptonD0_vs_run'
# hName = 'singleLeptonZ0_vs_run'

# Open file and get histogram (TH2F)
file = r.TFile.Open(inputFile)

h = file.Get(hName)

# Make profile
hProf = h.ProfileX()

# Draw and make it look nice
canvas=r.TCanvas("canvas","canvas",1000,500)
canvas.SetGridy()


hProf.SetMarkerSize(0.5)
hProf.SetMarkerStyle(24)
hProf.SetMarkerColor(1)
hProf.SetLineColor(1)
hProf.Draw('E1')

hProf.GetXaxis().SetTitle("Run number")
# hProf.GetYaxis().SetTitle("Mean d_{0}/#sigma")
if hName.find('Z0')>=0:
    hProf.GetYaxis().SetTitle("Mean z_{0}")
    hProf.GetYaxis().SetRangeUser(-0.01,0.01)
    pass
else :
    hProf.GetYaxis().SetTitle("Mean d_{0}")
    hProf.GetYaxis().SetRangeUser(-0.15,0.15)
    pass
hProf.GetYaxis().SetTitleOffset(0.7)
# hProf.GetYaxis().SetRangeUser(-0.5,0.3)


addCMSTitle()
addChannelLatex('2muTrack', 0.2, 0.8)
addFileLabel(inputFile,0.5,0.8)
canvas.Update()

# Save it
outputFileName=''
if inputFile.find('22Jan') >= 0 :
    if hName.find('Z0')>=0:
        outputFileName='output/pdfOutput/singleLeptonZ0_vs_run_22JanRereco_2muTrack.pdf'
        pass
    else :
        outputFileName='output/pdfOutput/singleLeptonD0_vs_run_22JanRereco_2muTrack.pdf'
        pass
    pass
else:
    if hName.find('Z0')>=0:
        outputFileName='output/pdfOutput/singleLeptonZ0_vs_run_PromptReco_2muTrack.pdf'
        pass
    else :
        outputFileName='output/pdfOutput/singleLeptonD0_vs_run_PromptReco_2muTrack.pdf'
        pass
    pass

canvas.Print(outputFileName)
raw_input('Waiting...')