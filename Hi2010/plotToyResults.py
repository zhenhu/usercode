#! /bin/env python

cols = {}

def createTree(fnames, altTrue = {}, cut = ''):
    from array import array
    from ROOT import TTree
    data = None
    line = 0
    for fname in fnames:
        # print 'opening',fname
        fin = open(fname, 'r')
        for currLine in fin:
            var = False
            err = False
            pull = False
            gen = False
            varName = 'nll'
            toks = currLine.split()
            doFill = True
            for key in cols:
                cols[key][0] = -9999.99
            for tok in toks:
                #print cols
                try:
                    #print varName,tok,var,err,pull
                    float(tok)
                    if (not var):
                        if (not (varName in cols)):
                            cols[varName] = array('d', [0.0])
                        cols[varName][0] = float(tok)
                        var = True
                    elif (not err):
                        if (not (varName + '_err' in cols)):
                            cols[varName + '_err'] = array('d', [0.0])
                        cols[varName + '_err'][0] = abs(float(tok))
                        err = True
                        ## if (float(tok) > 10000):
                        ##     doFill = False
                        ##     print 'bad error',varName + '_err',
                    elif (not pull):
                        #val = cols[varName][0]
                        #errval = cols[varName + '_err'][0]
                        if (not (varName + '_true' in cols)):
                            cols[varName + '_true'] = array('d', [0.0])
                        tval = float(tok)
                        if (varName in altTrue):
                            tval = altTrue[varName]
                        cols[varName + '_true'][0] = tval
                        pull = True
                        ## if abs((val - tval)/errval) > 1000:
                        ##     doFill = False
                    elif (not gen):
                        if (not (varName + '_gen' in cols)):
                            cols[varName + '_gen'] = array('d', [0.0])
                        cols[varName + '_gen'][0] = float(tok)
                except ValueError:
                    varName = tok.replace('-', '__').replace('.','_')
                    var = False
                    err = False
                    pull = False
            if (data == None):
                data = TTree('data', 'data')
                for key in cols.keys():
                    data.Branch(key, cols[key], key + '/D')

                #data.Print()
            for key in cols:
                if cols[key][0] == -9999.99:
                    print 'unfilled column',key,
                    doFill = False
            if (doFill):
                data.Fill()
            else:
                print 'rejecting event',line,':',cols
            line += 1
        # print 'completed',fname

    #data.Print()
    return data.CopyTree(cut)

if __name__ == '__main__':
    def drawAndPrint(var, altname = ''):
        if len(altname) < 1:
            altname = var
        qualCut = '(covQual==3) && (edm <= 1e-1) &&(%s != -9999.99)' % (var)
        data.Draw(var + '>>' + altname + '(30)', qualCut, 'PE');
        h = gDirectory.Get(altname)
        h.SetMarkerStyle(20)
        if ((altname[-5:] == '_bias') or (altname[-8:] == '_biasgen')) and \
               (altname[0] == 'n'):
            print altname,'mean:',h.GetMean()
        if ((altname[-5:] == '_pull') or altname[-8:] == '_pullgen') and \
               (opts.fitPull):
            data.Draw(var + '>>{0}(50, -5., 5.)'.format(altname),
                      qualCut, 'PE');
            h = gDirectory.Get(altname)
            h.SetMarkerStyle(20)
            h.Fit("gaus", "", "", -2.4, 2.4)
        h.SetXTitle(var)
        c.Modified()
        sums = ''
        errs = ''
        errstr = ''
        trues = ''
        if ((altname[:4] == 'nsig') or (altname[:4] == 'nbkg')) and \
               (altname[-4:] != '_err') and (altname[-5:] != '_pull') and \
               (altname[-5:] != '_bais') and (altname[-8:] != '_pullgen') and \
               (altname[-8:] != '_baisgen'):
            mean = h.GetMean()
            rms = h.GetRMS()
            errstr = '%s mean: %5.3f rms: %5.3f fractional err: %6.4f' % (altname, mean, rms, rms/mean)
            #print errstr
            #if (var == altname):
            sums = altname + '+'
            errs = (altname + '_err*')*2
            errs = errs[:-1] + '+'
            trues = altname + '_true+'
        c.Update()
        c.Print(opts.plotdir + '/' + altname + '.png')
        c.Print(opts.plotdir + '/' + altname + '.pdf')
        return errstr,sums,errs,trues

    def mean(var, altname = ''):
        if len(altname) < 1:
            altname = var
        data.Draw(var, '', 'goff')
        return TMath.Mean(data.GetSelectedRows(), data.GetV1())

    from optparse import OptionParser

    parser = OptionParser(usage='usage: %prog [options] INPUTFILENAME')
    parser.add_option('--plotdir', dest='plotdir', metavar='PLOTDIR',
                      help='directory to create the plots defaults to ' + \
                      'the current directory, (default: \"%default\")',
                      default='.')
    parser.add_option('-p', '--pulls', action='store_true', dest='fitPull',
                      help='fit a Gaussian to the pull distributions',
                      default=False)
    parser.add_option('-f', '--fracErrs', action='store_true', dest='fracErrs',
                      help='print fractional errors on yield, rms/mean.',
                      default=False)
    parser.add_option('--sums', action='store_true', dest='doSums',
                      help='sum up bins for 1S, 2S, and 3S',
                      default=False)
    parser.add_option('-b', action='store_true', dest='batch',
                      help='run in batch mode without graphics',
                      default=False)

    (opts,args) = parser.parse_args()

    from ROOT import gROOT, TCanvas, TFile, TTree, gStyle, gDirectory, TH1F, \
         TF1, TLatex, TMath

    gROOT.SetStyle('Plain')
    gStyle.SetOptStat('iouRMe')
    gStyle.SetOptFit(1112)
    gStyle.SetPalette(1)
    gStyle.SetPadTickX(1)
    gStyle.SetPadTickY(1)
    gStyle.SetOptTitle(0)

    #altTrue = {'nsig1':7800*3.33206, 'nsig2':2200*2.84212,
    #'nsig3':1300*2.62833, 'nbkgd':56000*1.4305}
    #altTrue = {'nsig1':25139.7, 'nsig2':6090.0, 'nsig3':3366.2, 'nbkgd':80538.9}

    fhold = TFile('%s/lastToyResult.root' % (opts.plotdir), 'recreate')

    #altTrue = {'nsig1':7800*3.33206, 'nsig2':2200*2.84212,
    #'nsig3':1300*2.62833, 'nbkgd':56000*1.4305}
    #altTrue = {'nsig1':25139.7, 'nsig2':6090.0, 'nsig3':3366.2, 'nbkgd':80538.9
    altTrue = {}
    
    data = createTree(args)
    ferrs = []
    c = TCanvas('c', 'c', 600, 600)
    sigSum = ['','','','']
    errSum = ['','','','']
    trueSum = ['','','','']
    altNames = ['nsig1', 'nsig2', 'nsig3', 'nbkgd']

    for key in cols.keys():
        aname = ''
        f = key
        if (key[-5:] == '_true'):
            aname = key.replace('true', 'pull')
            avgTrue = mean(key)
            f = '(' + key.replace('_true', '') + '-' + key + ')/' + \
                key.replace('true', 'err')
            drawAndPrint(key.replace('_true', '') + '-' +  str(avgTrue),
                         key.replace('_true', '_bias'))
        if (key[-4:] == '_gen'):
            aname = key.replace('gen', 'pullgen')
            f = '(' + key.replace('_gen', '') + '-' + key + ')/' + \
                key.replace('gen', 'err')
            drawAndPrint(key.replace('_gen', '') + '-' + key,
                         key.replace('_gen', '_biasgen'))
        errstr,sums,errs,trues = drawAndPrint(f,aname)
        if (opts.fracErrs) and (len(errstr) > 0):
            ferrs.append(errstr)
        if (opts.doSums) and (len(sums) > 0):
            notFound = True
            idx = 0
            while (idx < 4) and (notFound):
                if (key[:len(altNames[idx])] == altNames[idx]):
                    notFound = False
                else:
                    idx += 1
            if (not notFound):
                sigSum[idx] += sums
                errSum[idx] += errs
                trueSum[idx] += trues

    if (opts.doSums):
        for idx in range(0,4):
            print sigSum[idx][:-1]
            print errSum[idx][:-1]
            print trueSum[idx][:-1]
            errstr,sums,errs,diffs = drawAndPrint(sigSum[idx][:-1], altNames[idx])
            if (len(errstr) > 0):
                ferrs.append(errstr)
            drawAndPrint('sqrt(' + errSum[idx][:-1] + ')',
                         altNames[idx] + '_err')
            if altNames[idx] in altTrue:
                drawAndPrint('(' + sigSum[idx][:-1] + '-(' + \
                             str(altTrue[altNames[idx]]) + '))/sqrt(' + \
                             errSum[idx][:-1] + ')',
                             altNames[idx] + '_pull')
            else:
                avgTrue = mean(trueSum[idx][:-1], altNames[idx] + '_true')
                print altNames[idx],'avg true yield:',avgTrue
                drawAndPrint('(' + sigSum[idx][:-1] + '-(' + str(avgTrue) + \
                             '))/sqrt(' + \
                             errSum[idx][:-1] + ')', altNames[idx] + '_pull')
                drawAndPrint('1-(' + trueSum[idx][:-1] + ')/(' + \
                             sigSum[idx][:-1] + ')', altNames[idx] + '_bias')

    if (opts.fracErrs):
        ferrs.sort(key=str.lower)
        for errstr in ferrs:
            print errstr

    fhold.Write()
    fhold.Close()
