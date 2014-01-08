import ROOT as r
import sys
import os
import pickle
from SignalSampleInfo import *

# Function convertLimits_rootToTxt is called by makePlot.py to convert .root files containing limits to .txt files in format expected by plotter.

def convertLimits_rootToTxt(sample, lepton, tIndex, obsLimitRootFile, expLimitRootFiles, acceptanceOption, subtractControl, txtDirName):

        #-----------------------------------------------------------------------------------------------------
	# sample contains info about this mass point from SignalSampleInfo.py
	# lepton is "Muons" or "Electrons" depending on which species is being studied.
	# tIndex is integer index indicating which lifetime point this is in array signalInfo.ctauScales
	#                         (or in other arrays whose index corresponds to lifetime).
	# obsLimitRootFile is a list containing the name of a ROOT file containing the observed limit.
	# expLimitRootFiles is a list containing the names of one or more ROOT files containing expected limits.
        # acceptanceOption is < 10 implies place limits on sigma*BR, or > 10  implies put limits on number
        #                  of signal events passing cuts.
	# subtractControl: If true, then the signal efficiency will be set equal to the different of the
	#                  efficiency in the signal region minus that in the control region.
	# txtDirName is the .txt file name to be created.
        #-----------------------------------------------------------------------------------------------------
	
	# Get job options.
        jobOpt = JobOptions()

	# "sample" contain efficiencies within acceptance or in the whole of phase space, depending on which
	# job option was used. Below, we will need efficiencies in the whole of phase space, so must
        # find the sample containing this.
	samples = getSignalSampleInfo()
	iFound = -999
	for index, s in enumerate(samples):
		if s.MH == sample.MH and s.MX == sample.MX and s.acceptance == 1:
			iFound = index

	if iFound != -999:
		sampleFull = samples[iFound]
	else:
		sys.exit("ERROR: Sample inside full phase space not found.")

	# Read limits from ROOT files.
	resultList = []
	# This uses the function defined later in this .py file, to return the observed limit and expected limit band.
	resultList += readLimitsFromRootFiles( obsLimitRootFile, False )
	resultList += readLimitsFromRootFiles( expLimitRootFiles, True )

	# If option loopOverCTau in SignalSampleInfo.py was set to true, then here we just need to calculate the limit for
	# the one specific lifetime value passed to this function (which will be set in an external loop over all lifetimes).
	# However, if loopOverCTau was false, then we must calculate the limit for all lifetimes here.

	if jobOpt.loopOverCTau:
		indexLoop = [ tIndex ]
	else:
		indexLoop = range ( len(sample.ctaus) )

	for index in indexLoop:
		t   = sample.ctaus[index]
		if subtractControl:
			# Signal contamination in background control region causes one to overestimate the background and so
			# underestimate the size of any signal seen. This is equivalent to a reduction in the effective
			# signal efficiency.
			eff = sample.effis[lepton][index] - sample.effis_control[lepton][index] 
		else:
			eff = sample.effis[lepton][index]

		# Also get efficiency in whole of phase space (which may be identical if eff is in whole of phase space).
		effFull = sampleFull.effis[lepton][index]
		#print "TEST ",eff," ",effFull," ",acceptanceOption," ",sample.MH," ",sample.MX,"\n"
		
		# Don't plot very small efficiencies or very large relative uncertainty efficiencies
		if eff > jobOpt.minPlotEff and sample.effi_relerrs[lepton][index] < jobOpt.maxPlotRelEffErr:
			outputTxtFile = '%s/%s_%s_%f.txt'   %(txtDirName, sample.MH, sample.MX, t)
			f = open(outputTxtFile, 'w')
			# Paul's plotter expects the Higgs mass as the first variable.
			resultListForPaul = [sample.MH]
			# Loop over observed + expected limits.
			for result in resultList:
				if result > 0:
					# Convert to limit on sigma*BR if requested.
					if  acceptanceOption < 10:
						# Get limit for small exotic branching ratios (lim0)
						# And for branching ratio = 1 (lim1).
						lim0 = result/(2 * eff * jobOpt.getLumi(lepton))
						# This is worsee, because some exotics end up in same event.
						lim1 = lim0/(1 - 0.5*effFull)
					else:
						lim0 = result
						lim1 = lim0
					# Check that original assumption used by CLs (not Bayesian) about maximum conceivable value of limit was correct.
					if jobOpt.limitMethod == "CLs" and result > 0.8 * jobOpt.maxPredictedLimit:
						sys.exit("ERROR: Parameter maxPredictedLimit = %f in SignalSampleInfo.py is too small. Please increase to at least %f"    %(jobOpt.maxPredictedLimit, 1.5*result) )
				else:
					# If result is not +ve, an error has occurred.
					print "WIERD limit calculation failed ",result,"\n"
					lim0 = -3.
					lim1 = lim0

				resultListForPaul.append(lim0)
				resultListForPaul.append(lim1)
				print "Limit on signal cands = ", result, " Limit on sigma*BR = ", lim0, "(",lim1,") for small (large) BR; effi = ", eff, "; lumi = ", jobOpt.getLumi(lepton)

			pickle.dump(resultListForPaul, f) 

def readLimitsFromRootFiles( rootFileList, getExpectedLimit ):
# This is just an internal utility function to read limits from ROOT files.

	resultList = []

	# Get job options.
        jobOpt = JobOptions()

	# If CLs expected limit, expected one file for each quantile requested. If Bayesian limit, expected just one file.
	if getExpectedLimit:
		if ( ( jobOpt.limitMethod == "CLs"      and len(rootFileList) != len(jobOpt.fracs) ) or
		     ( jobOpt.limitMethod == "Bayesian" and len(rootFileList) != 1 ) ):
			print "ERROR: expLimitRootFiles has wrong number of entries\n"
			exit(1)

	for rootFile in rootFileList:
		result = -999
		print 'Reading ',os.getcwd(),'/',rootFile
		f = r.TFile(rootFile)
		if f.IsOpen():
			r.gDirectory.ls()
			tree = r.TTree()
			f.GetObject("limit", tree)
			num = tree.GetEntries()
			if getExpectedLimit and jobOpt.limitMethod == "Bayesian" and num > 10: # Less than ten toys won't give accurate limits.
				# Entry is limit obtained from one toy MC sample.
				res = []
				for i in range(0, num):
					tree.GetEntry(i)
					leaf = tree.GetLeaf("limit")
					res.append( leaf.GetValue() )
				res.sort()
				for frac in jobOpt.fracs:
					pos = num * frac
					jposl = min(int(pos), num-1)
					jposh = min(jposl+1 , num-1)
					part = pos - jposl
					result = res[jposl]*frac + res[jposh]*(1.-frac)
					print "=== expected limit on number of cands for quantile ",frac," is ",result,"\n"
					resultList.append(result)
			elif num == 1:
				# Entry is observed limit or is expected limit at a specific quantile
				tree.GetEntry(0)
				leaf = tree.GetLeaf("limit")
				result = leaf.GetValue()
				if getExpectedLimit:
					print "=== expected limit on number of cands for quantile ",frac," is ",result,"\n"
				else:
					print "=== observed limit on number of cands is ",result,"\n"

			else:
				print "WIERD: Wrong number of entries in TTree ",num
				result = -1
		else:
			print "WIERD: Failed to open file ",
			result = -2

		resultList.append(result)

	return resultList
