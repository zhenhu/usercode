#! /usr/bin/env python

from optparse import OptionParser

parser = OptionParser()
parser.add_option('--pt', dest='pt', default=4.0, type='float',
                  help='pt to cut at')
parser.add_option('--params', '-p', default='nomSimFit.txt', dest='paramfile',
                  help='initial parameters file')
(opts, args) = parser.parse_args()

import pyroot_logon
from ROOT import gROOT
gROOT.ProcessLine('.L buildSimPdf.cc+')

from ROOT import readData,computeRatio,computeRatioError,buildPdf,\
     RooWorkspace,RooFit,TCanvas,kRed,kGreen,kDashed,buildSimPdf,RooArgSet,\
     RooRealVar,RooMsgService

RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)

hidatafile = 'data/dimuonTree_181912-182609.root'
ppdatafile = 'data/MassTree_NewCuts_pp_HIrereco.root'

cuts = '(muPlusPt > %0.1f) && (muMinusPt > %0.1f) && (abs(upsRapidity)<2.4)' \
       % (opts.pt, opts.pt)
simparamfile = opts.paramfile

## cuts = '(muPlusPt > 3.5) && (muMinusPt > 3.5) && (abs(upsRapidity)<2.4)'
## simparamfile = 'nom3.5SimFit.txt'

ws = RooWorkspace("ws","ws")

readData(ws, hidatafile, ppdatafile, cuts)

buildPdf(ws, True)
buildPdf(ws, False)
simPdf = buildSimPdf(ws, ws.cat('dataCat'))

data = ws.data('data').reduce('(QQsign == QQsign::PlusMinus)')
pars = simPdf.getParameters(data)

data.Print()

pars.readFromFile(simparamfile)

fr = simPdf.fitTo(data, RooFit.Extended(),
                  RooFit.Minos(False),
                  RooFit.Save(True))

pars.writeToFile('lastSimFit.txt')

mass = ws.var('invariantMass')
dataCat = ws.cat('dataCat')
catSet = RooArgSet(dataCat)

hican = TCanvas("hi", "hi")
dataCat.setLabel('hi')
mf_hi = mass.frame(7., 14., 70)
data.plotOn(mf_hi, RooFit.Cut('dataCat==dataCat::hi'))
simPdf.plotOn(mf_hi, RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data)
              )
simPdf.plotOn(mf_hi, RooFit.Components('bkg*'),
              RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data),
              RooFit.LineColor(kRed+2),
              RooFit.LineStyle(kDashed))
simPdf.plotOn(mf_hi, RooFit.Components('bkg_hi'),
              RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data),
              RooFit.LineColor(kGreen+2),
              RooFit.LineStyle(kDashed))
mf_hi.Draw()
hican.Update()

ppcan = TCanvas("pp", "pp")
dataCat.setLabel('pp')
mf_pp = mass.frame(7., 14., 70)
data.plotOn(mf_pp, RooFit.Cut('dataCat==dataCat::pp'))
simPdf.plotOn(mf_pp, RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data)
              )
simPdf.plotOn(mf_pp, RooFit.Components('bkg*'),
              RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data),
              RooFit.LineColor(kRed+2),
              RooFit.LineStyle(kDashed))
simPdf.plotOn(mf_pp, RooFit.Components('bkg_pp'),
              RooFit.Slice(catSet),
              RooFit.ProjWData(catSet,data),
              RooFit.LineColor(kGreen+2),
              RooFit.LineStyle(kDashed))
mf_pp.Draw()
ppcan.Update()

fr.Print('v')
devError = computeRatioError(ws.var('f23_hi'), ws.var('f23_pp'))
print '\ndouble ratios (hi/pp)\n',\
      '---------------------\n',\
      '(2S+3S)/1S : %0.3f +/- %0.3f\n' % (computeRatio(ws.var('f23_hi'),
                                                       ws.var('f23_pp')),
                                          devError),
print '%s : %0.3f +/- %0.3f\n' % (ws.var('f2_pp').GetTitle(),
                                  computeRatio(ws.var('f2_hi'),
                                               ws.var('f2_pp')),
                                  computeRatioError(ws.var('f2_hi'),
                                                    ws.var('f2_pp'))),
print '---------------------\n'

deviation = 1.0 - computeRatio(ws.var('f23_hi'),ws.var('f23_pp'))
print 'back of the envelope significane'
print '--------------------------------'
print '(2S+3S)/1S : %0.3f/%0.3f = %0.2f' % (deviation , devError,
                                            deviation/devError)
print '--------------------------------\n'
