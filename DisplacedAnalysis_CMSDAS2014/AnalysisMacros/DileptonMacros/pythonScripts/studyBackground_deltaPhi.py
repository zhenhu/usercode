import os,sys
import ROOT as r
from math import sqrt

# Open file
fileNameG = 'BackgroundStudiesFiles/minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCuts_2muTrack_promptReco.root'
fileNameL = 'BackgroundStudiesFiles/minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCuts_2muTrack_promptReco.root'

openFileG=r.TFile.Open(fileNameG)
openFileL=r.TFile.Open(fileNameL)

# 1D plots of single lepton d0/sigma
r.gROOT.cd()
hG=r.TH1F( openFileG.Get('Background MC') )
hL=r.TH1F( openFileL.Get('Background MC') )

hG.SetMarkerColor(r.kRed)
hG.SetMarkerSize(0.8)
hG.SetMarkerStyle(20)
hG.SetLineColor(r.kRed)
hG.GetXaxis().SetRangeUser(0,10)

hL.SetMarkerColor(r.kBlue)
hL.SetMarkerSize(0.8)
hL.SetMarkerStyle(20)
hL.SetLineColor(r.kBlue)

canvas=r.TCanvas("can")
up = r.TPad('u','u',0.01,0.25,0.99,0.99)
dp = r.TPad('d','d',0.01,0.01,0.99,0.25)
dp.Draw()
up.Draw()
up.cd()
up.SetLogy()
hG.Draw('PE')
hL.Draw('SAME PE')
print 'Integral > 90 :',hG.Integral()
print 'Integral < 90 :',hL.Integral()

# Make ratio plot
nbins = hL.GetNbinsX()
xmax = hL.GetBinLowEdge(nbins)+hL.GetBinWidth(nbins)
ratioPlot = r.TH1F( 'ratioPlot', 'ratioPlot', nbins, hL.GetBinLowEdge(1), xmax)

for bin in range(1,nbins):
    if hG.GetBinContent(bin) > 0. and hL.GetBinContent(bin) > 0.:
        ratio = float(hL.GetBinContent(bin))/float(hG.GetBinContent(bin))

        LError = hL.GetBinError(bin) * hL.GetBinError(bin)
        GError = hG.GetBinError(bin) * hG.GetBinError(bin)
        error = sqrt( LError/(hL.GetBinContent(bin)*hL.GetBinContent(bin)) + GError/(hG.GetBinContent(bin)*hG.GetBinContent(bin)) )* ratio 
    else :
        ratio = 0
        error =0
    ratioPlot.SetBinContent( bin, ratio )
    ratioPlot.SetBinError( bin, error )
    pass

dp.cd()
ratioPlot.Draw('PE')
ratioPlot.SetMarkerStyle(23)

ratioPlot.SetMarkerSize(0.8)
ratioPlot.GetXaxis().SetRangeUser(0,10)
ratioPlot.GetYaxis().SetRangeUser(0.8,1.2)
ratioPlot.GetYaxis().SetLabelSize(0.09);
ratioPlot.GetXaxis().SetLabelSize(0.09);
dp.Update()
canvas.Update()
raw_input("Waiting.....")
