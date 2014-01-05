import ROOT as r
from ROOT import TMath
from commonMethods import *
from math import sqrt

# Cut values defining ABCD regions
cutL = 3
cutH = 3

r.gStyle.SetOptStat(0)
set_palette()

# Get histogram from file
file = r.TFile('CombinedFiles/DYJets_combined_2muTrack.root')

# h = file.Get('l_vs_h_leptonD0Sig_unsmeared_removedLifetimeCuts')
# h = file.Get('l_vs_h_leptonD0Sig_unsmeared_removedLifetimeCutsNoVertex')
# h = file.Get('l_vs_h_leptonD0Sig_unsmeared_unvertexedCands_removedLifetimeCutsNoVertex')
# h = file.Get('l_vs_h_leptonD0Sig_unsmeared_largePVDisplacement_removedLifetimeCutsNoVertex')

# DEBUG HISTOGRAM
f = r.TF2('f2', "0.5 * Gaus(x,0,1) * Gaus(y,0,2)",0,10,0,10)
h = r.TH2F('h','h',100,0,10,100,0,10)
h.FillRandom('f2',10000000)

# Get bins corresponding to regions edges
binCutL = h.GetXaxis().FindBin( cutL )
nBinsX = h.GetNbinsX()
lastBinX = h.GetXaxis().GetBinUpEdge( nBinsX )
binCutH = h.GetYaxis().FindBin( cutH )
nBinsY = h.GetNbinsY()
lastBinY = h.GetXaxis().GetBinUpEdge( nBinsY )

print 'Bins of cut : ',binCutL,binCutH
print 'N bins : ',nBinsX,nBinsY

# Get luminosity
lumi = getLumi( True )
print 'Luminosity :',lumi,'\\fb'

# Get integral in different regions

aError = r.Double(0)
bError = r.Double(0)
cError = r.Double(0)
dError = r.Double(0)
a = h.IntegralAndError( 0, binCutL-1, 0, binCutH-1, aError )*lumi
b = h.IntegralAndError( 0, binCutL-1, binCutH, nBinsY+1, bError )*lumi
c = h.IntegralAndError( binCutL,nBinsX+1, 0, binCutH-1, cError )*lumi

# SIGNAL REGION!
d = h.IntegralAndError( binCutL, nBinsX+1, binCutH, nBinsY+1, dError )*lumi

aError = aError * lumi
bError = bError * lumi
cError = cError * lumi
dError = dError * lumi

# BC/A
bcOverA = b * c / a
bcOverAError = bcOverA * sqrt( aError * aError / ( a * a ) + bError * bError / ( b * b ) + cError * cError / ( c * c ) )
print 'Correlation factor :',h.GetCorrelationFactor()

print '-------- ABCD --------'
print 'A :',a,'+/-',aError
print 'B :',b,'+/-',bError
print 'C :',c,'+/-',cError
print '----'
print 'BC/A :',bcOverA,'+/-',bcOverAError
print 'D :',d,'+/-',dError
print '----------------------'

# Draw things
canvas = r.TCanvas('canvas')
canvas.SetRightMargin(2)
canvas.SetLogz()
h.Scale(lumi)
# h.GetZaxis().SetRangeUser()
h.Draw('COLZ')
canvas.Update()
# Draw lines at cut values to show regions
cutLineL = r.TLine( cutL, 0, cutL, lastBinY)
cutLineH = r.TLine( 0, cutH, lastBinX, cutH)

cutLineL.SetLineStyle(2)
cutLineL.SetLineColor(13)
cutLineL.SetLineWidth(2)
cutLineL.Draw()

cutLineH.SetLineStyle(2)
cutLineH.SetLineColor(13)
cutLineH.SetLineWidth(2)
cutLineH.Draw()

# Cross check
# h1D = file.Get('minLeptonAbsD0Sig_unsmeared_removedLifetimeNoVertex')
# h1D = file.Get('minLeptonD0Sig_unsmeared_removedLifetimeNoVertex')
# h1D = file.Get('nMinus1_leptonD0Sig_unsmeared_finalCuts')
# integralPlus = h1D.Integral( h1D.GetXaxis().FindBin( cutL ), h1D.GetNbinsX() )
# integralMinus = h1D.Integral( 1, h1D.GetXaxis().FindBin( -1.0 * cutL ) -1 )
# print integralPlus*lumi,integralMinus*lumi
# print h1D.GetXaxis().FindBin( -1.0 * cutL )-1,h1D.GetXaxis().FindBin( cutL ), h1D.GetNbinsX()
# print ( integralPlus + integralMinus ) *lumi

raw_input("Waiting...")