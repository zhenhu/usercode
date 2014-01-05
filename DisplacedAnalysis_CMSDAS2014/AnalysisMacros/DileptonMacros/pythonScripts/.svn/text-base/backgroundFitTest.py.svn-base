import ROOT as r
r.gSystem.Load('libRooFit')

d0Sigma = r.RooRealVar("d0Sigma","Candidate minimum d0/sigma",-20,20)

# channel = '2eTrack'
channel = '2muTrack'

# reco = 'promptReco'
reco = 'rereco'

# Get histogram from file
file = r.TFile()
if channel is '2eTrack' :
    file = r.TFile('BackgroundStudiesFiles/minLeptonD0Sig_unsmeared_removedLifetimeCuts_2eTrack_'+reco+'.root')
elif channel is '2muTrack' :
    file = r.TFile('BackgroundStudiesFiles/minLeptonD0Sig_unsmeared_removedLifetimeCuts_2muTrack_'+reco+'.root')
    pass

# Get a TH1F histogram called data.
h = file.Get('Data')
dataHist = r.RooDataHist( 'data', '', r.RooArgList(d0Sigma), h )
dataIntegral = dataHist.sum(False)
print "Data hist integral :",dataIntegral

# Set up shapes and initial parameters of pdf
if channel is '2muTrack':
    # Gaussian 1
    mean1 =  r.RooRealVar("mean1","Mean1",0.,-0.5,0.5)
    sigma1 = r.RooRealVar("sigma1","Width1",0.8,0.5,1)
    gauss1 = r.RooGaussian("gauss1","Gaussian Peak Model 1",d0Sigma,mean1,sigma1)
    
    # Gaussian 2
    mean2 =  r.RooRealVar("mean2","Mean1",0.,-0.1,0.1)
    sigma2 = r.RooRealVar("sigma2","Width1",1,1.,5.)
    gauss2 = r.RooGaussian("gauss2","Gaussian Peak Model 2",d0Sigma,mean2,sigma2)
    
    # Gaussian 3
    mean3 =  r.RooRealVar("mean3","Mean3",0.,-0.1,0.1)
    sigma3 = r.RooRealVar("sigma3","Width3",0.8,0.2,1)
    gauss3 = r.RooGaussian("gauss3","Gaussian Peak Model 3",d0Sigma,mean3,sigma3)
    
    gauss1Norm = r.RooRealVar("gauss1Norm", "gauss1Norm", 10000000, 1000000, 100000000)
    gauss2Norm = r.RooRealVar("gauss2Norm", "gauss2Norm", 1, 1, 5000)
    gauss3Norm = r.RooRealVar("gauss3Norm", "gauss3Norm", 500000, 10000, 5000000)
    pass
elif channel is '2eTrack':
   # Gaussian 1
    mean1 =  r.RooRealVar("mean1","Mean1",0.,-0.5,0.5)
    sigma1 = r.RooRealVar("sigma1","Width1",1.5,0.4,2)
    gauss1 = r.RooGaussian("gauss1","Gaussian Peak Model 1",d0Sigma,mean1,sigma1)
    
    # Gaussian 2
    mean2 =  r.RooRealVar("mean2","Mean1",0.,-0.1,0.1)
    sigma2 = r.RooRealVar("sigma2","Width1",1,1,2.5)
    gauss2 = r.RooGaussian("gauss2","Gaussian Peak Model 2",d0Sigma,mean2,sigma2)
    
    # Gaussian 3
    mean3 =  r.RooRealVar("mean3","Mean3",0.,-0.1,0.1)
    sigma3 = r.RooRealVar("sigma3","Width3",1.5,0.5,2.)
    gauss3 = r.RooGaussian("gauss3","Gaussian Peak Model 3",d0Sigma,mean3,sigma3)
    
    gauss1Norm = r.RooRealVar("gauss1Norm", "gauss1Norm", 10000000, 100000, 100000000)
    gauss2Norm = r.RooRealVar("gauss2Norm", "gauss2Norm", 1000, 500, 30000)
    gauss3Norm = r.RooRealVar("gauss3Norm", "gauss3Norm", 100000, 10000, 10000000) 

mean1.setConstant(r.kFALSE)
sigma1.setConstant(r.kFALSE)
mean2.setConstant(r.kFALSE)
sigma2.setConstant(r.kFALSE)
mean2.setConstant(r.kFALSE)
sigma3.setConstant(r.kFALSE)
gauss1Norm.setConstant(r.kFALSE)
gauss2Norm.setConstant(r.kFALSE)
gauss3Norm.setConstant(r.kFALSE)

finalShape = r.RooAddPdf('finalShape', 'Final Shape', r.RooArgList(gauss1, gauss2, gauss3), r.RooArgList(gauss1Norm, gauss2Norm, gauss3Norm) )


# Restrict range of fit
if channel is '2muTrack' :
    d0Sigma.setRange('fitRange',-20,4)
elif channel is '2eTrack' :
    d0Sigma.setRange('fitRange',-20,6)
    pass
fr = finalShape.fitTo(dataHist, r.RooFit.Extended(), r.RooFit.Range('fitRange'), r.RooFit.Save()) 

frame = d0Sigma.frame()
dataHist.plotOn(frame)
# finalShape.plotOn(frame, r.RooFit.VisualizeError( fr,1), r.RooFit.FillColor(r.kOrange))
argSet = r.RooArgSet(gauss1)
finalShape.plotOn(frame, r.RooFit.Components(argSet),r.RooFit.LineStyle(r.kDashed),r.RooFit.LineColor(r.kRed))
argSet = r.RooArgSet(gauss2)
finalShape.plotOn(frame, r.RooFit.Components(argSet),r.RooFit.LineStyle(r.kDashed),r.RooFit.LineColor(r.kGreen))
argSet = r.RooArgSet(gauss3)
finalShape.plotOn(frame, r.RooFit.Components(argSet),r.RooFit.LineStyle(r.kDashed),r.RooFit.LineColor(r.kMagenta))
finalShape.plotOn(frame, r.RooFit.LineColor(r.kBlue))
frame.SetMaximum(1000000)
frame.SetMinimum(0.1)
frame.Draw()
frame.Print("v")
r.gPad.SetLogy()

# Get chi2/ndf between histogram and last curve plotted, assuming specified no. of fit params.
print 'Chi^2 / ndf : ',frame.chiSquare(9)

# Get integral in signal region
if channel is '2muTrack' :
    d0Sigma.setRange('signal',-20,-6)
elif channel is '2eTrack' :
    d0Sigma.setRange('signal',-20,-7)
    pass

argset = r.RooArgSet( d0Sigma ) # pyroot issues
totalIntegral = finalShape.createIntegral( argset, r.RooFit.NormSet( argset ), r.RooFit.Range("fitRange") )
integral = finalShape.createIntegral( argset, r.RooFit.NormSet( argset ), r.RooFit.Range("signal") )

# Get errors on integrals
totalIntegralError = totalIntegral.getPropagatedError( fr )
integralError = integral.getPropagatedError( fr )

print 'Total integral :',totalIntegral.getVal() * dataIntegral,'+/-',totalIntegralError * dataIntegral
print 'Integral in signal region :',integral.getVal() * dataIntegral,'+/-',integralError * dataIntegral

raw_input('Waiting...')
