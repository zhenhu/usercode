import ROOT as r
import sys
import os
import pickle
from SignalSampleInfo import *

# Called by makePlot.py to convert .root files containing limits to .txt files in format expected by plotter.

def convertLimits_rootToTxt(sample, lepton, tIndex, rootFileList, txtDirName):

	# sample contains info about this mass point from SignalSampleInfo.py
	# lepton is "Muons" or "Electrons" depending on which species is being studied.
	# tIndex is integer index indicating which lifetime point this is in array signalInfo.ctauScale
	#                         (or in other arrays whose index corresponds to lifetime).
	# rootFileList is contains the results of the observed and expected limits
	# txtDirName is the .txt file name to be created.

	resultList = []
	
	for rootFile in rootFileList:
		result = -999
		print 'Reading ',os.getcwd(),'/',rootFile
		f = r.TFile(rootFile)
		if f.IsOpen():
			r.gDirectory.ls()
			tree = r.TTree()
			f.GetObject("limit", tree)
			num = tree.GetEntries()
			if num == 1:
				tree.GetEntry(0)
				leaf = tree.GetLeaf("limit")
				result = leaf.GetValue()
			else:
				print "WIERD: Wrong number of entries in TTree ",num
				result = -1
		else:
			print "WIERD: Failed to open file ",
			result = -2

		resultList.append(result)

	# If option loopOverCTau in SignalSampleInfo.py was set to true, then here we just need to calculate the limit for
	# the one specific lifetime value passed to this function (which will be set in an external loop over all lifetimes).
	# However, if loopOverCTau was false, then we must calculate the limit for all lifetimes here.

	if sample.loopOverCTau:
		indexLoop = [ tIndex ]
	else:
		indexLoop = range ( len(sample.ctau) )
		
	for index in indexLoop:
		t   = sample.ctau[index]
		eff = sample.effi[lepton][index]
		# Don't plot very small efficiencies or very large relative uncertainty efficiencies
		if eff > sample.minPlotEff and sample.effi_relerr[lepton][index] < sample.maxPlotRelEffErr:
			outputTxtFile = '%s/%s_%s_%f.txt'   %(txtDirName, sample.MH, sample.MX, t)
			f = open(outputTxtFile, 'w')
			# Paul's plotter expects the Higgs mass as the first variable.
			resultListForPaul = [sample.MH]
			for result in resultList:
				if result > 0:
					# Convert to limit on sigma*BR
					lim = result/(2 * eff * getLumi(lepton))
					# Check that original assumption about maximum conceivable value of limit was correct.
					if result > 0.9 * sample.maxPredictedLimit:
						sys.exit("ERROR: Parameter maxLimit = %f in SignalSampleInfo.py is too small. Please increase to at least %f"    %(sample.maxLimit, 1.5*result) )
				else:
					# If result is -ve, an error has occurred.
					lim = result
				resultListForPaul.append(lim)
				print "Limit on signal cands = ", result, " Limit on sigma*BR = ", lim, "effi = ", eff, "lumi = ", getLumi(lepton)

			pickle.dump(resultListForPaul, f) 
