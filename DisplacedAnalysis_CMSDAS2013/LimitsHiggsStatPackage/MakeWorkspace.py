import os
import sys
import subprocess
import ROOT as r
from FixROOT import *
from SignalSampleInfo import *

#from GetParameters import *

# THIS WORKSPACE IS FOR USE WITH THE HIGGS STATISTICS PACKAGE !

# Range of search in X boson masses [15,500] hard-coded below!

# return RooWorkspace given the mass hypothesis

def MakeWorkspace(signalInfo, LeptonType, tIndex, dump = True, plot = True):

        # signalInfo contains info about this mass point from SignalSampleInfo.py
	# LeptonType is "Muons" or "Electrons" depending on which species is being studied.
	# tIndex is integer index indicating which lifetime point this is in array signalInfo.ctauScale
	#                         (or in other arrays whose index corresponds to lifetime).
	# dump = True ? Print workspace to screen for debug purposes
	# plot = True ? Plot PDF and data for debug purposes 

	# Options
	signalPdfChoice = 1
	useRealData = True # As opposed to toy MC data

	width_vec = signalInfo.width[LeptonType]
	if signalInfo.loopOverCTau:
		width_use = width_vec[tIndex]
	else:
		# If not considering variation of exotic width with lifetime, to save CPU, take median width averaged over lifetimes.
		width_use = sorted(width_vec)[len(width_vec)/2]

	print "-- Producing Workspace for ",LeptonType, "Hmass=",signalInfo.MH, " Xmass=", signalInfo.MX, "Xwidth=",width_use

	w = r.RooWorkspace("w")

        w.factory("mass[15,500]")

        w.factory("dummyA[-9.9e9,9.9e9]")
        w.factory("dummyB[-9.9e9,9.9e9]")
	# These are the variables in the data file
	argListFile = r.RooArgList( w.var("mass"), w.var("dummyA"), w.var("dummyB") )
        # These are the subset of them that are interesting for limit setting.
	argListMass = r.RooArgList( w.var("mass") )

        #-- Define background PDFs

	# Represent Z0 peak with a BW.

	w.factory("RooBreitWigner::backgrZ0(mass, %f, %f)"
		  %(signalInfo.paramBWMean[LeptonType], signalInfo.paramBWWidth[LeptonType]) )
		  
	# Now decide how to represent non-Z0 background.


	if signalInfo.backgrPdfOption == 1:
		# Flat PDF
		w.factory("RooUniform::backgrOther(mass)")
	elif signalInfo.backgrPdfOption == 2:
	        # 1/mass^3 * turn-on function (related to efficiency)   

	        #--- The following fails because backgrOtherZ is a "function", not a "pdf", so the SUM doesn't find it.
                #w.factory("al[0.5,0.0,1.0]");
                #w.factory("ar[0.8,0.0,1.0]");
                #w.factory("expr::backgrOtherZ('1.0-al*al',al)");
		#w.factory("SUM::backgrOther(backgrOtherZ,backgrOtherZ)")

                #--- The following fails because factory fails to make a RooGenericPdf
	        #w.factory("RooGenericPdf::backgrOther('mass*mass')")
                backgrOther = r.RooGenericPdf("backgrOther", "(TMath::Erf((mass-%f)/%f)+1)/(mass*mass*mass)"  %(signalInfo.paramTurnOn[LeptonType], signalInfo.paramTurnOnWidth[LeptonType]), argListMass)
		w.Import(backgrOther)

	else:
		sys.exit("ERROR: Unknown background option %i"  %(signalInfo.backgrPdfOption) )

	#-- Define signal PDF (two possible choices)

	# Mass parameter MH can in principle be overridden with the "-m" option in "combine" command.
        # But it doesn't work, so don't use it.
	w.factory("MX[%f]"       %(signalInfo.MX) )

	w.factory("widthSys[1.0]"); # Scale factor on width to allow for systematic	
	w.factory("prod::width(%f,widthSys)"    %(width_use) ); # Assumed width of signal resonance, allowing for systematic uncertainty
	
	if (signalPdfChoice == 1):
		# Option (1) - gaussian signal PDF
		w.factory("Gaussian::signal(mass, MX, width)")

        else:
		# Option (2) Square signal pdf for easier debugging

		his2 = r.TH1F("a","a",10,0.,1)
		nBins = 1 + int((w.var("mass").getMax() - w.var("mass").getMin())/w.var("width").getVal());
		hisSignalShape = r.TH1F("hisSignalShape","", nBins, w.var("mass").getMin(), w.var("mass").getMax())
		hisSignalShape.Fill(w.var("MX").getVal())
		dhisSignalShape = r.RooDataHist("dhisSignalShape","", argListMass, hisSignalShape)
		# w.factory("RooHistPdf::signal(mass, dhisSignalShape)") -- doesn't work, so do the following ...
		signal = r.RooHistPdf("signal", "", w.argSet("mass"), dhisSignalShape)
		w.Import(signal)
		
	#-- Get data or generate toy data.

	if (useRealData):

		inputDataFile = getDataFile(LeptonType)
		if os.path.exists(inputDataFile):
			dataAll = r.RooDataSet.read(inputDataFile, argListFile)
			# This should work, but does not, so use subsequent line instead
                        #data = dataAll.reduce(SelectVars(r.RooArgSet(w.var("mass"))))
                        data    = r.RooDataSet("data", dataAll.GetTitle(), dataAll, w.argSet("mass"))
                        data.Print("v")
		else:
			sys.exit("ERROR: %s does not exist" %inputDataFile)

	else:

		# Make toy MC with parameters hardwired here.
		w.factory("nS[100]") # Generated signal events
		w.factory("nB_Z0[1]") # Generated background events from Z0
		w.factory("nB_Other[1]") # Generated background events from Other
		w.factory("SUM::model_splusb(nS*signal, nB_Z0*backgrZ0, nB_Other*backgrOther)")
		if w.var("nS").getVal() + w.var("nB_Z0").getVal() + w.var("nB_Other").getVal() > 0:
			data = w.pdf("model_splusb").generate(w.argSet("mass"), 0)
		else:
			# Create empty dataset
			data = r.RooDataSet("empty", "", w.argSet("mass"))

	w.Import(data, Rename("data_obs"))

	# Store workspace as .root file and also as plain text file.
	rootFile = "workspace.root"
        txtFile  = "workspace.txt"
	w.writeToFile(rootFile)
	wfile = open(txtFile, 'w', 0)
	oldout = os.dup( sys.stdout.fileno() )
	os.dup2( wfile.fileno(), sys.stdout.fileno() )
	w.Print('v')
	w.allVars().Print('v')
	os.dup2( oldout, sys.stdout.fileno() )
	wfile.close()
	print "Workspace written to ",rootFile," and also to ",txtFile
	if dump:
		subprocess.call("cat %s" %txtFile, shell=True)

	print "Number of data candidates = ", w.data("data_obs").numEntries()
	if (not useRealData):
		print "of which ",w.var("nS").getVal()," are signal"

	if plot:
		w.var("mass").setBins(49)
		frame = w.var("mass").frame()
		frame.SetTitle("%s: Xmass=%i"  %(LeptonType, signalInfo.MX) )
		data.plotOn(frame)
		w.pdf("signal").plotOn(frame)
		w.pdf("backgrZ0").plotOn(frame)
		w.pdf("backgrOther").plotOn(frame)
		frame.Draw()
		r.gPad.SetLogy(1)
		r.gPad.Update()
		print "Hit enter to continue ... \n"
		sys.stdin.read(1)

	return
