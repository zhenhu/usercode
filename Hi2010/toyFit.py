#! /usr/bin/env python

from optparse import OptionParser

parser = OptionParser()
parser.add_option('--pt', dest='pt', default=4.0, type='float',
                  help='pt to cut at')
parser.add_option('--params', '-p', default='nomSimFit.txt', dest='paramfile',
                  help='initial parameters file')
parser.add_option('--keys', action="store_true",default=False, dest='keys',
                  help='use keys pdf for background')
(opts, args) = parser.parse_args()

import pyroot_logon
from ROOT import gROOT
gROOT.ProcessLine('.L buildSimPdf.cc+')
gROOT.ProcessLine('.L hiToys.cc+')

from ROOT import readData,computeRatio,computeRatioError,buildPdf,\
     genSameSignDatasets,genOppositeSignBackground,genOppositeSignSignal,\
     RooWorkspace,RooFit,TCanvas,kRed,kGreen,kDashed,buildSimPdf,RooArgSet,\
     RooRealVar,RooMsgService,Long

RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)

hidatafile = 'data/dimuonTree_150mub.root'
# hidatafile = 'data/dimuonTree_181912-182609.root'
ppdatafile = 'data/dimuonTree_2011_pp.root'

cuts = '(muPlusPt > %0.1f) && (muMinusPt > %0.1f) && (abs(upsRapidity)<2.4) && (vProb > 0.05)' \
       % (opts.pt, opts.pt)
simparamfile = opts.paramfile
useKeys = opts.keys

ws = RooWorkspace("ws","ws")

readData(ws, hidatafile, ppdatafile, cuts)

buildPdf(ws, False, 1, True)
buildPdf(ws, True, 0, True)
simPdf = buildSimPdf(ws, ws.cat('dataCat'))

pars = simPdf.getParameters(ws.data('data'))
pars.readFromFile(simparamfile)

Npp_tot = Long(ws.var("nsig1_pp").getVal() + \
               ws.function("nsig2_pp").getVal() + \
               ws.function("nsig3_pp").getVal() + \
               ws.var("nbkg_pp").getVal() + 0.5)
Nhi_tot = Long(ws.var("nsig1_hi").getVal() + \
               ws.function("nsig2_hi").getVal() + \
               ws.function("nsig3_hi").getVal() + \
               ws.var("nbkg_hi").getVal() + 0.5)
dataCat = ws.cat('dataCat')
QQsign = ws.cat('QQsign')
reducedCols = RooArgSet(dataCat,QQsign)

dsToGen = ['os']
if useKeys:
    dsToGen.insert(0, 'ss')

for signStr in dsToGen:
    for dataStr in ['hi', 'pp']:
        theCut = '(dataCat == dataCat::%s)' % (dataStr)
        if (signStr == 'ss'):
            theCut += '&&(QQsign != QQsign::PlusMinus)'
        else:
            theCut += '&&(QQsign == QQsign::PlusMinus)'
        tmpData = ws.data('data').reduce(RooFit.SelectVars(reducedCols),
                                         RooFit.Name('data_%s_%s' % (signStr, dataStr)),
                                         RooFit.Cut(theCut))
        getattr(ws, 'import')(tmpData)

print "N_hi:",Nhi_tot,"N_pp:",Npp_tot,"total:",Nhi_tot+Npp_tot

toyData = ws.data('data').emptyClone()

Npp_bkg = Long(ws.var('nbkg_pp').getVal() + 0.5)
Nhi_bkg = Long(ws.var('nbkg_hi').getVal() + 0.5)

ws.Print()

if useKeys:
    toyData.append(genSameSignDatasets(ws))

toyData.append(genOppositeSignBackground(ws, Nhi_bkg, Npp_bkg))
toyData.append(genOppositeSignSignal(ws, int(Nhi_tot-Nhi_bkg), int(Npp_tot-Npp_bkg)))

toyData.Print()

wsToy = RooWorkspace("wsToy", "wsToy")
wsToyNull = RooWorkspace("wsToyNull", "wsToyNull")
getattr(wsToy, 'import')(toyData)
getattr(wsToyNull, 'import')(toyData)

buildPdf(wsToy, False, 1, True)
buildPdf(wsToy, True, 0, True)

simPdf = buildSimPdf(wsToy, wsToy.cat('dataCat'))
pars2 = simPdf.getParameters(wsToy.data('data'))
pars2.readFromFile(simparamfile)

data = wsToy.data('data').reduce('(QQsign==QQsign::PlusMinus)')

mass = wsToy.var('invariantMass')

mass.setRange("fitRange",7.,14.)
mass.setRange(7., 14.)

#ws.Print()
data.Print()

fr = simPdf.fitTo(data, RooFit.Extended(),
                  RooFit.Minos(False),
                  #RooFit.Range("fitRange"),
                  RooFit.Save(True))

pars.writeToFile('lastToyFit.txt')

dataCat = wsToy.cat('dataCat')
catSet = RooArgSet(dataCat)

hican = TCanvas("hi", "hi")
dataCat.setLabel('hi')
mf_hi = mass.frame(7, 14, 70)
data.plotOn(mf_hi,
            # RooFit.CutRange('fitRange'),
            RooFit.Cut('dataCat==dataCat::hi'))
simPdf.plotOn(mf_hi, RooFit.Slice(catSet),
              # RooFit.Range('fitRange'),
              RooFit.ProjWData(catSet,data)
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
hican.Update()

ppcan = TCanvas("pp", "pp")
dataCat.setLabel('pp')
mf_pp = mass.frame(7., 14., 70)
data.plotOn(mf_pp,
            # RooFit.CutRange('fitRange'),
            RooFit.Cut('dataCat==dataCat::pp'))
simPdf.plotOn(mf_pp, RooFit.Slice(catSet),
              # RooFit.Range('fitRange'),
              RooFit.ProjWData(catSet,data)
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
ppcan.Update()

fr.Print('v')
