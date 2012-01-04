#! /usr/bin/env python

def doToyGen(ws, pars, nll = None):
    toyData = ws.data('data').emptyClone()

    if nll:
        pars.assignValueOnly(nll.randomizePars())

    Npp_bkg = Long(ws.var('nbkg_pp').getVal() + 0.5)
    Nhi_bkg = Long(ws.var('nbkg_hi').getVal() + 0.5)

    Npp_sig = int(ws.var("nsig1_pp").getVal() + \
                  ws.function("nsig2_pp").getVal() + \
                  ws.function("nsig3_pp").getVal() + 0.5)
    Nhi_sig = int(ws.var("nsig1_hi").getVal() + \
                  ws.function("nsig2_hi").getVal() + \
                  ws.function("nsig3_hi").getVal() + 0.5)
    newX23 = ws.var('f23_hi').getVal()/ws.var('f23_pp').getVal()
    newX2 = ws.var('f2_hi').getVal()/ws.var('f2_pp').getVal()

    if useKeys:
        toyData.append(genSameSignDatasets(ws))

    toyData.append(genOppositeSignBackground(ws, Nhi_bkg, Npp_bkg, False))
    toyData.append(genOppositeSignSignal(ws, Nhi_sig, Npp_sig, newX23, newX2))

    return toyData

def doToyFit(wsToy, simparamfile, useKeys):
    from ROOT import RooFit
    
    buildPdf(wsToy, True, useKeys)
    buildPdf(wsToy, False, useKeys)

    simPdf = buildSimPdf(wsToy, wsToy.cat('dataCat'))
    pars2 = simPdf.getParameters(wsToy.data('data'))
    pars2.readFromFile(simparamfile)

    #pars2.setRealValue("f23_hi", pars2.getRealValue("f23_pp"));
    #pars2.setRealValue("f2_hi", pars2.getRealValue("f2_pp"));

    data = wsToy.data('data').reduce('(QQsign==QQsign::PlusMinus)')

    mass = wsToy.var('invariantMass')

    mass.setRange("fitRange",7.,14.)
    mass.setRange(7., 14.)

    #ws.Print()
    data.Print()

    fr = simPdf.fitTo(data, RooFit.Extended(),
                      RooFit.Minos(False),
                      #RooFit.Range("fitRange"),
                      RooFit.PrintLevel(-1),
                      RooFit.Save(True))
    return fr
    
    
def doToyGenFit(ws, pars, nll, parFile, useKeys):

    pars.readFromFile(parFile)

##     print 'Starting Values'
##     pars.Print("v")

    toyData = doToyGen(ws, pars, nll)

##     print 'Generated Values'
##     pars.Print("v")

    wsToy = RooWorkspace("wsToy", "wsToy")
    getattr(wsToy, 'import')(toyData)

    fr = doToyFit(wsToy, parFile, useKeys)

    return fr

from optparse import OptionParser

parser = OptionParser()
parser.add_option('--pt', dest='pt', default=4.0, type='float',
                  help='pt to cut at')
parser.add_option('--params', '-p', default='nomSimFit.txt', dest='paramfile',
                  help='initial parameters file')
parser.add_option('--keys', action="store_true",default=False, dest='keys',
                  help='use keys pdf for background')
parser.add_option('--rand', '-r', default='', dest='randfile',
                  help='randomize parameters file')
parser.add_option('--seed', default=0, dest='seed', type='int',
                  help='random seed')
parser.add_option('--nexp', default=1, dest='nexp', type='int',
                  help='number of toy experiments')
parser.add_option('--output', '-o', default='toyValidation.asc', dest='output',
                  help='filename for output')
parser.add_option('--xrootd', action='store_true', default=False,
                  dest='xrootd', help='read files using xrootd from eos')
parser.add_option('-b', action='store_true', default=False, dest='b',
                  help='no x windows')

(opts, args) = parser.parse_args()

import pyroot_logon
from ROOT import gSystem
gSystem.Load('tardir/buildSimPdf_cc.so')
gSystem.Load('tardir/hiToys_cc.so')

from ROOT import readData,computeRatio,computeRatioError,buildPdf,\
     mmin,mmax,\
     genSameSignDatasets,genOppositeSignBackground,genOppositeSignSignal,\
     RooWorkspace,RooFit,TCanvas,kRed,kGreen,kDashed,buildSimPdf,RooArgSet,\
     RooRealVar,RooMsgService,Long,TFile,RooRandom

RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)
RooRandom.randomGenerator().SetSeed(opts.seed)

if (opts.xrootd):
    hidatafile = 'root://cmssrv32.fnal.gov//store/user/andersj/hiTrees/'
else:
    hidatafile = 'data/'
ppdatafile = hidatafile
hidatafile += 'dimuonTree_150mub.root'
ppdatafile += 'dimuonTree_2011_pp.root'

cuts = '(muPlusPt > %0.1f) && (muMinusPt > %0.1f) && (abs(upsRapidity)<2.4)' \
       % (opts.pt, opts.pt)
simparamfile = opts.paramfile
useKeys = opts.keys

ws = RooWorkspace("ws","ws")

readData(ws, hidatafile, ppdatafile, cuts)

buildPdf(ws, True, useKeys)
buildPdf(ws, False, useKeys)
simPdf = buildSimPdf(ws, ws.cat('dataCat'))

pars = simPdf.getParameters(ws.data('data'))
pars.readFromFile(simparamfile)

data = ws.data('data').reduce('(QQsign==QQsign::PlusMinus)')
data.Print()

if len(opts.randfile) > 0:
    nllf = TFile(opts.randfile)
    nll = nllf.Get('nll')
    nllf.Close()
else:
    nll = simPdf.fitTo(data, RooFit.Extended(),
                       RooFit.Minos(False),
                       RooFit.PrintLevel(-1),
                       #RooFit.Range("fitRange"),
                       RooFit.Save(True))

nll.Print()

dataCat = ws.cat('dataCat')
QQsign = ws.cat('QQsign')
reducedCols = RooArgSet(dataCat,QQsign)

for signStr in ['ss', 'os']:
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

outf = open(opts.output, 'w')

for exp in range(0, opts.nexp):

    fr = doToyGenFit(ws, pars, nll, opts.paramfile, opts.keys)

    resultsString = 'nll %f edm %f covQual %i ' % (fr.minNll(), fr.edm(),
                                                  fr.covQual())
    #print resultsString
    for i in range(0, fr.floatParsFinal().getSize()):
        param = fr.floatParsFinal()[i]
        parString = '%s %f %f %f %f ' % \
                    (param.GetName(), param.getVal(),
                     param.getError(),
                     nll.floatParsFinal().find(param.GetName()).getVal(),
                     pars.getRealValue(param.GetName(), 0.))
        resultsString += parString
        #print parString

    parString = '%s %f %f %f %f ' % \
                ('x23', computeRatio(fr.floatParsFinal().find('f23_hi'),
                                     fr.floatParsFinal().find('f23_pp')),
                 computeRatioError(fr.floatParsFinal().find('f23_hi'),
                                   fr.floatParsFinal().find('f23_pp'),
                                   fr.correlation('f23_hi', 'f23_pp')),
                 computeRatio(nll.floatParsFinal().find('f23_hi'),
                              nll.floatParsFinal().find('f23_pp')),
                 computeRatio(pars.find('f23_hi'),
                              pars.find('f23_pp')))
    resultsString += parString
    parString = '%s %f %f %f %f ' % \
                ('x2', computeRatio(fr.floatParsFinal().find('f2_hi'),
                                     fr.floatParsFinal().find('f2_pp')),
                 computeRatioError(fr.floatParsFinal().find('f2_hi'),
                                   fr.floatParsFinal().find('f2_pp'),
                                   fr.correlation('f2_hi', 'f2_pp')),
                 computeRatio(nll.floatParsFinal().find('f2_hi'),
                              nll.floatParsFinal().find('f2_pp')),
                 computeRatio(pars.find('f2_hi'),
                              pars.find('f2_pp')))
    resultsString += parString

    outf.write(resultsString + '\n')

    ## print resultsString
    ## print 'Gen Pars'
    ## pars.Print("v")

    ## print 'true params'
    ## nll.Print()
    ## print 'fit params'
    ## fr.Print()

outf.close()
