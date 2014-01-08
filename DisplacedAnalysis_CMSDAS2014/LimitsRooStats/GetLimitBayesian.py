import ROOT as r
import sys,os.path
from GetParameters import *

def GetLimitBayesian(w,LeptonType,fileName):
	print("Output will be written to " +fileName)

	M = w.var("mean").getVal()
	nuisanceParameters = w.set('modelCfg_NuisParams')
	observables = w.set('modelCfg_Observables')
	POI = w.set('modelCfg_POI')
	#w.Print()

	mass = w.arg("mass")

	# these files are merged versions of the files in the svn repository -- would
	# be nice to have this a bit more organized
	if LeptonType.find("2eTrack") == 0:
		data = r.RooDataSet.read("./masses_data_electron.txt",r.RooArgList(mass)) 
	elif LeptonType.find("2muTrack") == 0:
		data = r.RooDataSet.read("./masses_data_muon.txt",r.RooArgList(mass))
	else:
		print "Don't know where to find data for "+LeptonType

	frame = mass.frame()
	data.plotOn(frame)

	bkgpdf = w.pdf("bkgPdf")
	bkgpdf.plotOn(frame)
	frame.Draw()

	modelCfg = r.RooStats.ModelConfig('modelCfg',w)
	modelCfg.SetPdf(w.pdf("model"))
	modelCfg.SetNuisanceParameters(nuisanceParameters)
	modelCfg.SetObservables(observables)
	modelCfg.SetParametersOfInterest(POI)
	
	# Get the result

	prior_S = r.RooUniform("prior_S","prior_S",r.RooArgSet(w.var("S")))
	w.var("S").Print()
	modelCfg.SetPriorPdf(prior_S)
	bc = r.RooStats.BayesianCalculator(data,modelCfg)
	bc.SetConfidenceLevel(0.95)
	bc.SetLeftSideTailFraction(0.0)
	Int = bc.GetInterval()

	print w.var("B").getVal()

	# Use RooStats to get the expected limit
	# Note -- this assumes that the lumi and efficiency errors
	# are set up for lognormal. If you switch GetWorkspace back
	# to Gaussian you'll need to change this code here.

	## Whoa is this a hacky way to determine if we're getting
	## limits on the number of events or on the cross-section!
	limitCrossSection = 0
	if (fileName.find("/") > -1):
		limitCrossSection = 1
		# Limit on cross-section, use actual eff and lumi
		eff = w.obj("SigEff").getVal()
		efferr = (w.obj("SigEffE").getVal()-1)*eff
		lum = w.obj("Lumi").getVal()
		lumerr = (w.obj("LumiE").getVal()-1)*lum
	else:
		# Limit on number of events, use dummy eff and lumi
		eff = 1
		efferr = 0
		lum = 1
		lumerr = 0

	# Use background estimate from fits.
	# Two ways of doing this:
	# 1) Take the maximally conservative approach of using
	# the full background in every bin.
	# 2) Take the minimally conservative approach of
	# using the background distributed according to the PDF.

	pars = GetParameters(M,"dataFile"+LeptonType)
	bkg = pars['Bkg']
	bkgerr = pars['BkgE']
	
	# For method 1, we're done now. For method 2, use this as
	# the normalization of the PDF. Note: no error on PDF is included here.

	if 1:
		mass.setVal(M)
		pdfval = bkgpdf.getVal(r.RooArgSet(mass))
		print "Value of background pdf at " + str(mass.getVal()) + ": " + str(pdfval)
		bkg *= pdfval
		bkgerr *= pdfval

		
	print "Background value for expected estimation is " + str(bkg) + " +/- " + str(bkgerr)
	# print "Invoking roostats_cl95  " + str(lum) + " " + str(lumerr)+ " "  + str(eff)+ " "  + str(efferr)+ " "  + str(bkg)+ " "  + str(bkgerr)

	# roostats_cl95 has problems if bkgerr > 5.0*bkg. So we impose a hard upper
	# cap to prevent this.
	if (bkgerr > 5.0*bkg and limitCrossSection):
		bkgerr = 4.95*bkg

	# Similarly for the efficiency error. A hard cap here has a rather large effect
	# on the very high values. I've picked 200% as what is hopefully a reasonable
	# compromise.
	if (efferr > 2.0*eff):
		efferr = 2.0*eff

        r.gROOT.LoadMacro("roostats_cl95.C+")
	limit_result = r.roostats_clm(lum, lumerr, eff, efferr, bkg, bkgerr, 1000, 1)

	q = [0]*9
        q[0] = M
        q[1] = Int.UpperLimit()
	q[2] = limit_result.GetExpectedLimit()
	q[3] = limit_result.GetOneSigmaHighRange()
	q[4] = limit_result.GetOneSigmaLowRange()
	q[5] = limit_result.GetTwoSigmaHighRange()
	q[6] = limit_result.GetTwoSigmaLowRange()
	q[7] = limit_result.GetThreeSigmaHighRange()
	q[8] = limit_result.GetThreeSigmaLowRange()

	outf = open(fileName+'.txt','write')
	import pickle
	pickle.dump(q,outf)


