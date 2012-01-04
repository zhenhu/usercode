#! /usr/bin/env python

from optparse import OptionParser

parser = OptionParser()
parser.add_option('--pt', dest='pt', default=4.0, type='float',
                  help='pt to cut at')
parser.add_option('--params', '-p', default='nomSimFit.txt', dest='paramfile',
                  help='initial parameters file')
parser.add_option('--keys', action="store_true",default=False, dest='keys',
                  help='use keys pdf for background')
parser.add_option('-b', action='store_true', default=False, dest='b',
                  help='no x windows')
(opts, args) = parser.parse_args()

import pyroot_logon
from ROOT import gROOT
gROOT.ProcessLine('.L buildSimPdf.cc+')

from ROOT import readData,computeRatio,computeRatioError,buildPdf,\
     mmin,mmax,\
     RooWorkspace,RooFit,TCanvas,kRed,kGreen,kDashed,buildSimPdf,RooArgSet,\
     RooRealVar,RooMsgService, TMath, TFile

RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)

hidatafile = 'data/dimuonTree_150mub.root'
ppdatafile = 'data/dimuonTree_2011_pp.root'

cuts = '(muPlusPt > %0.1f) && (muMinusPt > %0.1f) && (abs(upsRapidity)<2.4)' \
       % (opts.pt, opts.pt)
simparamfile = opts.paramfile
useKeys = opts.keys
## cuts = '(muPlusPt > 3.5) && (muMinusPt > 3.5) && (abs(upsRapidity)<2.4)'
## simparamfile = 'nom3.5SimFit.txt'

ws = RooWorkspace("ws","ws")

readData(ws, hidatafile, ppdatafile, cuts)

buildPdf(ws, True, useKeys, False)
buildPdf(ws, False, useKeys, False)
simPdf = buildSimPdf(ws, ws.cat('dataCat'))

mass = ws.var('invariantMass')
## data = ws.data('data').reduce('(QQsign==QQsign::PlusMinus)&&(%s>%0.1f)&&(%s<%0.1f)' % (mass.GetName(), mmin, mass.GetName(), mmax))
data = ws.data('data').reduce('(QQsign==QQsign::PlusMinus)')
mass.setRange("fitRange",7.,14.)
mass.setRange(7., 14.)
pars = simPdf.getParameters(data)

ws.Print()
data.Print()

pars.readFromFile(simparamfile)

fr = simPdf.fitTo(data, RooFit.Extended(),
                  RooFit.Minos(False),
                  #RooFit.Range("fitRange"),
                  RooFit.Save(True))

pars.writeToFile('lastSimFit.txt')

dataCat = ws.cat('dataCat')
catSet = RooArgSet(dataCat)

hican = TCanvas("hi", "hi")
dataCat.setLabel('hi')
mf_hi = mass.frame(7, 14, 70)
data.plotOn(mf_hi,
            # RooFit.CutRange('fitRange'),
            RooFit.Cut('dataCat==dataCat::hi'),
            RooFit.Name('data_hi'))
simPdf.plotOn(mf_hi, RooFit.Slice(catSet),
              # RooFit.Range('fitRange'),
              RooFit.ProjWData(catSet,data),
              RooFit.Name('fullFit')
              )
simPdf.plotOn(mf_hi, RooFit.Components('bkg*'),
              # RooFit.Range('fitRange'),
              RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data),
              RooFit.LineColor(kRed+2),
              RooFit.LineStyle(kDashed))
simPdf.plotOn(mf_hi, RooFit.Components('bkgPoly*'),
              # RooFit.Range('fitRange'),
              RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data),
              RooFit.LineColor(kGreen+2),
              RooFit.LineStyle(kDashed))
mf_hi.Draw()
pyroot_logon.cmsPrelimHI(hican, 70)
hican.Update()

ppcan = TCanvas("pp", "pp")
dataCat.setLabel('pp')
mf_pp = mass.frame(7., 14., 70)
data.plotOn(mf_pp,
            # RooFit.CutRange('fitRange'),
            RooFit.Cut('dataCat==dataCat::pp'),
            RooFit.Name('data_pp'))
simPdf.plotOn(mf_pp, RooFit.Slice(catSet),
              # RooFit.Range('fitRange'),
              RooFit.ProjWData(catSet,data),
              RooFit.Name('fullFit')
              )
simPdf.plotOn(mf_pp, RooFit.Components('bkg*'),
              # RooFit.Range('fitRange'),
              RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data),
              RooFit.LineColor(kRed+2),
              RooFit.LineStyle(kDashed))
simPdf.plotOn(mf_pp, RooFit.Components('bkgPoly*'),
              # RooFit.Range('fitRange'),
              RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data),
              RooFit.LineColor(kGreen+2),
              RooFit.LineStyle(kDashed))
mf_pp.Draw()
pyroot_logon.cmsPrelimPP(ppcan, 225)
ppcan.Update()

hican.Print('hiFitPt%0.1f.pdf' % (opts.pt))
hican.Print('hiFitPt%0.1f.png' % (opts.pt))
ppcan.Print('ppFitPt%0.1f.pdf' % (opts.pt))
ppcan.Print('ppFitPt%0.1f.png' % (opts.pt))

fr.Print('v')
devError = computeRatioError(ws.var('f23_hi'), ws.var('f23_pp'),
                             fr.correlation('f23_hi','f23_pp'))
print
print 'double ratios (hi/pp)'
print '---------------------'
print '(2S+3S)/1S : %0.3f +/- %0.3f' % (computeRatio(ws.var('f23_hi'),
                                                     ws.var('f23_pp')),
                                        devError)
print '%s : %0.3f +/- %0.3f' % (ws.var('f2_pp').GetTitle(),
                                computeRatio(ws.var('f2_hi'),
                                             ws.var('f2_pp')),
                                computeRatioError(ws.var('f2_hi'),
                                                  ws.var('f2_pp'),
                                                  fr.correlation('f2_hi','f2_pp')))
print '---------------------'
print

deviation = 1.0 - computeRatio(ws.var('f23_hi'),ws.var('f23_pp'))
print 'back of the envelope significance'
print '---------------------------------'
print '(2S+3S)/1S : %0.3f/%0.3f = %0.2f' % (deviation , devError,
                                            deviation/devError)
print '---------------------------------'
print

chi2_hi = mf_hi.chiSquare('fullFit', 'data_hi', 0)*70
chi2_pp = mf_pp.chiSquare('fullFit', 'data_pp', 0)*70

chi2 = chi2_hi+chi2_pp
ndf = 70*2 - fr.floatParsFinal().getSize()
print 'chi2/ndf = (%0.3f + %0.3f)/%i = %0.3f' % (chi2_hi, chi2_pp,
                                                 ndf, chi2/ndf)
print 'chi2 prob = %0.4f' % (TMath.Prob(chi2, ndf))

resultFile = TFile("lastSimFit.root", "recreate")
fr.Write("nll")
resultFile.Close()
