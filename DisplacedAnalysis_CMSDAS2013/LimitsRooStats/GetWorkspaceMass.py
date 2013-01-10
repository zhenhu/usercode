import ROOT as r
import math
from GetParameters import *

# Range of search [15,500] and maximal number of Signal Events [30] HardCoded Here!

# return RooWorkspace given the mass hypothesis

def GetWorkspaceMass(M,LeptonType):

	# GetParameters for mass hypothesis
	pars = GetParameters(M,"dataFile"+LeptonType)
	
	# Create RooRealVars for input parameters (hardcoded for now)
	Bkg = r.RooRealVar("Bkg","Bkg",pars['Bkg'])
	#BkgE = r.RooRealVar("BkgE","BkgE",pars['BkgE']) # for Gaussian
	BkgE = r.RooRealVar("BkgE","BkgE",1 + pars['BkgE']/pars['Bkg']) # for Lognormal
	SigWidth = r.RooRealVar("SigWidth","SigWidth",pars['SigWidth'])

	# Total error = error + systematic
	SigWidthE = pars['SigWidthE']
	SigWidthSyst = pars['SigWidthSyst']*pars['SigWidth']
	SigWidthTotE = math.sqrt(SigWidthE*SigWidthE+SigWidthSyst*SigWidthSyst)
	# Now include the systematic as well
	#SigWidthE = r.RooRealVar("SigWidthE","SigWidthE",SigWidthTotE) # for Gaussian 
	SigWidthE = r.RooRealVar("SigWidthE","SigWidthE",1 + SigWidthTotE/pars['SigWidth']) # for Lognormal

	# not actually used but needed for dummies
	SigEff = r.RooRealVar("SigEff","SigEff",1)
	#SigEffE = r.RooRealVar("SigEffE","SigEffE",0) # for Gaussian
	SigEffE = r.RooRealVar("SigEffE","SigEffE",1) # for Lognormal

	# observable 
	mass = r.RooRealVar("mass","mass",15,500)

	# some variables to work with, s, b, mean, sigWidth, sigEff
	s = r.RooRealVar("S","S",0,0,50)
	b = r.RooRealVar("B","B",Bkg.getVal(),max(0,Bkg.getVal()-10*BkgE.getVal()),Bkg.getVal()+10*BkgE.getVal())
	b.Print()
	mean = r.RooRealVar("mean","mean",M)
	sigWidth = r.RooRealVar("sigWidth","sigWidth",SigWidth.getVal(),max(0,SigWidth.getVal()-10*pars['SigWidthE']),SigWidth.getVal()+10*pars['SigWidthE'])
	sigEff = r.RooRealVar("sigEff","sigEff",SigEff.getVal(),0,1)
	seff = r.RooFormulaVar("seff","@0*@1",r.RooArgList(s,sigEff))

	# prior PDFs on nuisance parameters Gaussian or Lognormal -> Lognormal preffered by Stat Committee ( no jokes with them )
	#prior_sigWidth = r.RooGaussian("prior_sigWidth","prior_sigWidth",sigWidth,SigWidth,SigWidthE)
	prior_sigWidth = r.RooLognormal("prior_sigWidth","prior_sigWidth",sigWidth,SigWidth,SigWidthE)
	#prior_b = r.RooGaussian("prior_b","prior_b",b,Bkg,BkgE)
	prior_b = r.RooLognormal("prior_b","prior_b",b,Bkg,BkgE)
	#prior_sigEff = r.RooGaussian("prior_sigEff","prior_sigEFf",sigEff,SigEff,SigEffE)
	prior_sigEff = r.RooLognormal("prior_sigEff","prior_sigEFf",sigEff,SigEff,SigEffE)
	#prior_nuisance = r.RooProdPdf("prior_nuisance","prior_nuisance",r.RooArgList(prior_sigWidth,prior_b,prior_sigEff))
	prior_nuisance = r.RooProdPdf("prior_nuisance","prior_nuisance",r.RooArgList(prior_sigWidth,prior_b))

	# shapes of signal and background
	signalPdf = r.RooGaussian("signalPdf","signalPdf",mass,mean,sigWidth)

	weight = r.RooRealVar("weight","weight",1,0,50)

	if LeptonType.find("Electron") == 0:
		bkgdataTmp = r.RooDataSet.read("WinterSelection/masses_data_elecloose_1.txt",r.RooArgList(mass,weight))
	elif LeptonType.find("Muon") == 0:
		bkgdataTmp = r.RooDataSet.read("WinterSelection/masses_data_muloose_1.txt",r.RooArgList(mass,weight))
	else:
		print "Don't know how to construct background model for "+LeptonType

	bkgdata = r.RooDataSet(bkgdataTmp.GetName(),bkgdataTmp.GetTitle(),bkgdataTmp,bkgdataTmp.get(),"",weight.GetName())

	if (LeptonType.find("Electron") == 0):
		mean_bw = r.RooRealVar("mean_bw", "mean_bw", 91.20)
		width_bw = r.RooRealVar("width_bw", "width_bw", 3.60)
		c = r.RooRealVar("c", "c", 0.868)
		turnon = r.RooRealVar("turnon", "turnon", 120.8)
		turnon_width = r.RooRealVar("turnon_width", "turnon_width", 51.7)
	else:
		mean_bw = r.RooRealVar("mean_bw", "mean_bw", 90.98)
		width_bw = r.RooRealVar("width_bw", "width_bw", 4.16)
		c = r.RooRealVar("c", "c", 0.961)
		turnon = r.RooRealVar("turnon", "turnon", 124.1)
		turnon_width = r.RooRealVar("turnon_width", "turnon_width", 52.1)

	bkg_bw = r.RooBreitWigner("BW", "BW", mass, mean_bw, width_bw)
	bkg_m4 = r.RooGenericPdf("powerWithTurnOn", "(TMath::Erf((@0-@1)/@2)+1)/(@0*@0*@0)", r.RooArgList(mass, turnon, turnon_width))
	bkgPdf = r.RooAddPdf("bkgPdf", "bkgPdf", bkg_bw, bkg_m4, c)

	# model 
	#model_no_nuis = r.RooAddPdf("model_no_nuis","model_no_nuis",r.RooArgList(signalPdf,bkgPdf),r.RooArgList(seff,b))
	model_no_nuis = r.RooAddPdf("model_no_nuis","model_no_nuis",r.RooArgList(signalPdf,bkgPdf),r.RooArgList(s,b))
	model = r.RooProdPdf("model","model",model_no_nuis,prior_nuisance)

	# define parameter sets
	observables = r.RooArgSet(mass)
	#nuisanceParameters = r.RooArgSet(b,sigWidth,sigEff)
	nuisanceParameters = r.RooArgSet(b,sigWidth)
	POI = r.RooArgSet(s)

	# modelConfig
	w = r.RooWorkspace('WS'+str(int(M)))
	modelCfg = r.RooStats.ModelConfig('modelCfg',w)
	modelCfg.SetPdf(model)
	modelCfg.SetObservables(observables)
	modelCfg.SetNuisanceParameters(nuisanceParameters)
	modelCfg.SetParametersOfInterest(POI)

	w.Print()

	# Some debugging code -- uncomment to see plots
	if (0):
		# Plot PDFs and plot background data points
		c = r.TCanvas("c","c",600,1200)
		signalPdf.createHistogram("mass").Draw();
		c.Update()
		print "signal pdf"
		r.cin.get()
		bkgPdf.createHistogram("mass").Draw();
		c.Update()
		print "background pdf"
		r.cin.get()
		
		frame = mass.frame()
		
		frame.SetTitle("Background")
		bkgdata.plotOn(frame)
		frame.Draw()
		c.Update()
		print "background points"
		r.cin.get()

	return w
