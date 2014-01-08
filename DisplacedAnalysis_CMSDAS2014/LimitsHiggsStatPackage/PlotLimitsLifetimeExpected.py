#========================================================================================
# This plots limits for H-->XX or squark --> neutralino.
#
# Where the script refers to Higgs mass, it can mean also Squark mass.
# Where it refers to X boson mass/lifetime, it can mean Neutralino mass/lifetime.
#=======================================================================================

import ROOT as r
import sys,os
import pickle
# Contains exotic masses, luminosity etc.
from SignalSampleInfo import *

r.gROOT.LoadMacro("tdrstyle.C")
r.setTDRStyle()

# Configurable parameters
logx = 1
logy = 1
drawExpected = 1
smooth = 1 # Smooth top of 95% expected limit band, which is most prone to fluctuations

if len(sys.argv) < 5:
	sys.exit('Usage: python PlotLimitsLifetime.py LeptonType Xlimits HiggsMass getSigmaBRacc \n',
	         'where LeptonType = Muons or Electrons\n',
		 '      Xlimits = True (for H-->XX) or False (for squark --> neutralino)\n',
		 '      HiggsMass to plot = 100, 400, 200 or 125. Not used for squark -> neutralino limits.\n',
		 '      getSigmaBRacc = True (limits on sigma*BR*A) or False (on sigma*BR)')

LeptonType = sys.argv[1]
Xlimits = int(sys.argv[2])
hmass = int(sys.argv[3])
getSigmaBRacc = int(sys.argv[4])
FileDir = LeptonType + "_txt"

# Get exotic masses, luminosity etc.
samples = getSignalSampleInfo()
jobOpt = JobOptions()
lumi = jobOpt.getLumi(LeptonType)

# Define class to contain limit curves for specified Higgs and X boson masses.
class graphs:
	def __init__(self, hmass_, xmass_):
		# Contains masses
		self.hmass = hmass_
		self.xmass = xmass_
		# Will contain graphs
		self.g = 0 # observed limit, valid for small branching ratio * efficiency
		self.g_br1 = 0 # observed limit, valid for 100% branching ratio. 
		self.gest1 = 0 # expected limit 1 sigma band, valid for small branching ratio * efficiency
		self.gest2 = 0 # expected limit 2 sigma band, valid for small branching ratio * efficiency

# Determine (Higgs, X boson) masses for which plots required.
plotsVec = []
for s in samples:
	if s.acceptance == 1: # We can choose either 1 or 2 here, but must choose one to avoid getting duplicate masses in the list. 
		if hmass == s.MH or not Xlimits:
			plotsVec.append( graphs(s.MH, s.MX) )

if Xlimits:
	# Set graph boundaries for long-lived X boson limits.
	ymin = 0
	if (hmass == 1000):
		xmin = 0.002
		xmax = 60000
		ymax = 30.
		if (logy == 1):
			if (getSigmaBRacc):
				ymin = 5.0e-5
				ymax = 300.0
			else:
				ymin = 5.0e-5
				ymax = 400.0
	elif (hmass == 400):
		xmin = 0.003
		xmax = 85000
		ymax = 30.
		if (logy == 1):
			if (getSigmaBRacc):
				ymin = 5.0e-5
				ymax = 200.0
			else:
				ymin = 5.0e-5
				ymax = 200.0
	elif (hmass == 200):
		xmin = 0.001
		xmax = 100000
		ymax = 30.
		if (logy == 1):
			if (getSigmaBRacc):
				ymin = 5.0e-5
				ymax = 80.0
			else:
				ymin = 2.0e-4
				ymax = 80.0
	elif (hmass == 125):
		xmin = 0.001
		xmax = 100000
		ymax = 30.
		if (logy == 1):
			if (getSigmaBRacc):
				ymin = 5.0e-5
				ymax = 11.0
			else:
				ymin = 5.0e-4
				ymax = 200.0
	else:
		print "Oops, requested Higgs mass = ",hmass," not recognized.",Xlimits
		sys.exit(1)

else:
	# Set graph boundaries for long-lived neutralino limits.
	xmin = 3.0e-2
	xmax = 3.0e3
	ymin = 0.
	ymax = 30.
	if (logy == 1):
		if getSigmaBRacc:
			ymin = 5.0e-5
			ymax = 1.0
		else:
			ymin = 1.0e-4
			ymax = 11.0

jcol  = 1
jpoly = 20

#r.gROOT.SetStyle("Plain")
r.gStyle.SetErrorX(0)
# have to restore the title though
r.gStyle.SetOptTitle(1)
r.gStyle.SetTitleBorderSize(0)
#r.gStyle.SetTitleFont(42, "")

c = r.TCanvas("c","c",600,600)
r.gPad.SetLeftMargin(0.15)
r.gPad.SetTopMargin(0.08)
r.gPad.SetRightMargin(0.04)
if (logx == 1):
	r.gPad.SetLogx()
if (logy == 1):
	r.gPad.SetLogy()
r.gStyle.SetTitleFont(42, "")
r.gStyle.SetTitleX(0.55)
r.gStyle.SetTitleY(0.99)
r.gStyle.SetTitleAlign(23)
r.gStyle.SetTitleSize(0.05, "XYZ");
r.gStyle.SetLabelSize(0.045, "XYZ");
fr = c.DrawFrame(xmin, ymin, xmax, ymax)
# Add text to plot with Higgs mass.
if Xlimits:
	if (logy == 1):
		yMHtext = ymax/3
	else:
		yMHtext = 0.9*ymax
	t1 = r.TLatex(xmax*0.75, yMHtext, "m_{H} = "+str(hmass)+ " GeV/c^{2}")
	t1.SetTextAlign(32)
	t1.SetTextFont(62)
	t1.SetTextSize(0.04)
	t1.Draw()

fr.SetTitle("CMS    #sqrt{s} = 8 TeV    L = %4.1f fb^{-1}"    %(lumi/1000.)  )

if (LeptonType == "Electrons"):
	leptName = "e"
elif (LeptonType == "Muons"):
	leptName = "#mu"
else:
	print "Unrecognised lepton"
	sys.exit(1)
# N.B. #kern[-0.7]{ } creates a narrow space
if getSigmaBRacc:
	accName = ".A"
else:
	accName = ""
if Xlimits:
	fr.GetYaxis().SetTitle("#sigma(H^{0}#rightarrow XX)#kern[-0.7]{ }B%s(X#rightarrow %s^{+}%s^{-}) [pb]"  %(accName, leptName, leptName) )
else:
	fr.GetYaxis().SetTitle("#sigma(#tilde{q}#bar{#tilde{q}}+#tilde{q}#tilde{q})#kern[-0.7]{ }B%s(#tilde{q}#rightarrow #chi^{0} #rightarrow %s^{+}%s^{-}#nu) [pb]"  %(accName, leptName, leptName) )

fr.GetXaxis().SetTitle("c#tau [cm]")
fr.GetXaxis().SetTitleOffset(1.05)
fr.GetYaxis().SetTitleOffset(1.40)
if Xlimits:
	leg = r.TLegend(0.16, 0.58, 0.62, 0.83)
else:
	leg = r.TLegend(0.16, 0.65, 0.62, 0.90)
leg.SetFillColor(0)
leg.SetBorderSize(0)
leg.SetTextFont(42)
dummy = r.TH1F("dummy", "dummy", 1, 1, 1)
dummy.SetLineColor(0)
dummy.SetMarkerColor(0)
dummy.SetFillColor(0) 
leg.AddEntry(dummy, "Observed 95% CL limits")

xmax_seen = 0.
xmin_seen = 9.9e9
ymax_seen = 0.
ymin_seen = 9.9e9
for index, plots in enumerate(plotsVec):
	flist = []
	for filename in os.listdir(FileDir):
		if filename.find('.txt')>-1 and filename.find(str(plots.hmass)+"_"+str(plots.xmass))==0:
			flist.append(filename[:-4])

	if len(flist) > 0:

		flist.sort(key=lambda str: float(str.split("_")[2]))
		print "Files found for (",plots.hmass,",",plots.xmass,") = " + str(flist)
		flist = [str(a)+'.txt' for a in flist]

		# graph for limits, with specified number of lifetime points in each:
		plots.g = r.TGraph(2+len(flist))
		plots.g_br1 = r.TGraph(2+len(flist))
		plots.gest1 = r.TGraphErrors(2+len(flist))
		plots.gest2 = r.TGraphErrors(2+len(flist))
		lmax=-1
		lmin=9999
		i = 1
	        expLimitFactor = 1
		ltLast = -999.
		est2mLast = -999.
		est2pLast = -999.
		est2pBeforeLast = -999.
		
		for filename in flist:
			lt=float(filename[:-4].split("_")[2])
			print "Lifetime in "+FileDir+"/"+filename+" is " + str(lt)

			# Note min and max lifetime seen at any point on curve.
			xmax_seen = max(xmax_seen, lt)
			xmin_seen = min(xmin_seen, lt)

			if lt > lmax:
				lmax = lt
			if lt < lmin:
				lmin = lt

			f = open(FileDir+"/"+filename)

			q = pickle.load(f)
			m = q[0]
			# Limits valid for small branching ratio * efficiency.
			up_br0 = q[1]
			est_br0 = q[3]
			est1p_br0 = q[5]
			est1m_br0 = q[7]
			est2p_br0 = q[9]
			est2m_br0 = q[11]
			# Limits valid for 100% branching ratio.
			up_br1 = q[2]
			est_br1 = q[4]
			est1p_br1 = q[6]
			est1m_br1 = q[8]
			est2p_br1 = q[10]
			est2m_br1 = q[12]
			# print "CHECK ",filename," ",m," ",up_br0, " ",est1p_br0

			# Band becomes unstable if too narrow.
			#if abs(est1p_br0 - est1m_br0) < 1.0e-1*est_br0:
			#	est1p_br0 = (1 + 1.0e-1)*est_br0
			#if abs(est2p_br0 - est2m_br0) < 2.0e-1*est_br0:
			#	est2p_br0 = (1 + 2.0e-1)*est_br0
			# Note min and max limit seen at any point on curve.

			# Do not expect a limit to be weaker than its two neighbouring points on the c*tau curve.
			# So optionally reduce wiggles in the limit curve by preventing this (but not if it exceeds its
			# neighbours by more than 20%, suggesting it is a real effect).
			# Only necessary for 2*sigma expected upper limit, which has largest fluctuations.
			if smooth and i >= 3:
				if est2pLast > max(est2pBeforeLast, est2p_br0) and est2pLast < 1.2*max(est2pBeforeLast, est2p_br0):
					print "WARNING: SMOOTHING +2*sigma expected band point ",i-1,"(",ltLast,") : ", est2pBeforeLast, " ", est2pLast, " ", est2p_br0, "\n"
					est2pLast = max(est2pBeforeLast, est2p_br0)
					plots.gest2.SetPoint(i-1,ltLast,(est2pLast+est2mLast)/2)
					plots.gest2.SetPointError(i-1,ltLast,(est2pLast-est2mLast)/2)
				
			est2pBeforeLast = est2pLast
			est2pLast = est2p_br0
			est2mLast = est2m_br0
			ltLast = lt

			ymax_seen = max(ymax_seen, up_br0, est2p_br0)
			ymin_seen = min(ymin_seen, up_br0, est2m_br0)

			plots.g.SetPoint(i,lt,up_br0)
			plots.g_br1.SetPoint(i,lt,up_br1)

			plots.gest1.SetPoint(i,lt,(est1p_br0+est1m_br0)/2)
			plots.gest1.SetPointError(i,0,(est1p_br0-est1m_br0)/2)
			plots.gest2.SetPoint(i,lt,(est2p_br0+est2m_br0)/2)
			plots.gest2.SetPointError(i,0,(est2p_br0-est2m_br0)/2)

			# This is needed to ensure the curve extrapolates smoothly between the points.
			# i.e. Avoids "bouncing" mentioned in http://root.cern.ch/root/html/TGraphPainter.html
			if i == 1:
				plots.g.SetPoint(0,lt,up_br0)
				plots.g_br1.SetPoint(0,lt,up_br1)
				plots.gest1.SetPoint(0,lt,(est1p_br0+est1m_br0)/2)
				plots.gest1.SetPointError(0,0,(est1p_br0-est1m_br0)/2)
				plots.gest2.SetPoint(0,lt,(est2p_br0+est2m_br0)/2)
				plots.gest2.SetPointError(0,0,(est2p_br0-est2m_br0)/2)

			print "PLOTTING ",filename," m=",m," tau=",lt," obs=",up_br0," est=",est_br0, " (1) ",est1p_br0, "/", est1m_br0, " (2) ",est2p_br0, "/", est2m_br0,"\n"

			i+=1

		# This is needed to ensure the curve extrapolates smoothly between the points.
		# i.e. Avoids "bouncing" mentioned in http://root.cern.ch/root/html/TGraphPainter.html
		plots.g.SetPoint(i,lt,up_br0)
		plots.g_br1.SetPoint(i,lt,up_br1)
		plots.gest1.SetPoint(i,lt,(est1p_br0+est1m_br0)/2)
		plots.gest1.SetPointError(i,0,(est1p_br0-est1m_br0)/2)
		plots.gest2.SetPoint(i,lt,(est2p_br0+est2m_br0)/2)
		plots.gest2.SetPointError(i,0,(est2p_br0-est2m_br0)/2)

		# Draw in order: +/- 2 sigma band, +/- 1 sigma band, actual

		plots.gest2.SetFillColor(r.kGreen)
#		plots.gest2.SetFillStyle(3005)
		plots.gest2.SetFillStyle(1001)
		plots.gest2.SetMarkerStyle(0)
		plots.gest2.SetMarkerColor(0)
		plots.gest2.SetLineColor(0)
		plots.gest1.SetFillColor(r.kYellow)
#		plots.gest1.SetFillStyle(3005)
		plots.gest1.SetFillStyle(1001)
		plots.gest1.SetMarkerStyle(0)
		plots.gest1.SetMarkerColor(0)
		plots.gest1.SetLineColor(0)
		if drawExpected:
			plots.gest2.Draw("4 same")
# 			plots.gest1.Draw("4 same")


		plots.g.SetLineColor(jcol)
		plots.g.SetFillColor(0)
		plots.g.SetMarkerColor(jcol)
		plots.g.SetMarkerStyle(jpoly)
		plots.g.SetMarkerSize(1.5)
		plots.g.SetLineWidth(2)

		plots.g_br1.SetLineColor(jcol)
		plots.g_br1.SetFillColor(0)
		plots.g_br1.SetMarkerColor(jcol)
		plots.g_br1.SetMarkerStyle(jpoly)
		plots.g_br1.SetMarkerSize(1.5)
		plots.g_br1.SetLineWidth(2)
		plots.g_br1.SetLineStyle(2)

	        # Plot all observed limit curves later, outside the loop, since otherwise
		# they can be covered by the expected limit curve.

		#plots.g.Fit("pol3", "", "", lmin, lmax)
		#f1 = plots.g.GetFunction("pol3")
		#f1 = r.TF1("f"+str(xmass), "1/([0]+[1]/x + [2]/(x*x) + [3]/(x*x*x))", lmin, lmax)
		#plots.g.Fit(f1, "", "", lmin, lmax)
		#f1.SetLineColor(jcol)

		jpoly += 1 # Change polymarker
		jcol += 1 # Change line color
		if (jcol == 3 or jcol == 5) :
			jcol += 1 # Don't want light green or yellow

# Plot observed limits (do after expected limits, to ensure not covered up)
for plots in plotsVec:
	if plots.g:
		plots.g.Draw("lp same") # valid for small BR*efficiency
		plots.g_br1.Draw("l same") # valid for 100% BR
		if Xlimits:
			leg.AddEntry(plots.g, "m_{X} = " + str(int(plots.xmass)) + " GeV/c^{2}")
		else:
			leg.AddEntry(plots.g, "m_{#tilde{q}} / m_{#chi} = " + str(int(plots.hmass)) + " / " + str(int(plots.xmass)) + " GeV/c^{2}")


# Add key to legend for expected limit band.
if drawExpected:
	for plots in plotsVec:
		if plots.gest2:
			# leg.AddEntry(gest1[last_mass], "Expected limit (68%)", "f")
			leg.AddEntry(plots.gest2, "Expected 95% CL limits", "f")
			# Only want one expected limit entry in key
			break

leg.Draw()
c.Update()

print "x-range seen = %s - %s" %(xmin_seen, xmax_seen)
print "y-range seen = %s - %s" %(ymin_seen, ymax_seen)
rangeError = False

if xmin_seen < xmin or xmax_seen > xmax:
	rangeError = True
	print "ERROR PlotLimitsLifetimeExpected MH=%f: Either xmax is too small or xmin too large. TGraphErrors may plot error bands incorrectly unless you adjust them: xmax %f -> %f; xmin %f -> %f"    %(hmass, xmax, xmax_seen, xmin, xmin_seen)

if ymin_seen < ymin or ymax_seen > ymax:
	rangeError = True
	print "ERROR PlotLimitsLifetimeExpected MH=%f: Either ymax is too small or ymin too large. TGraphErrors may plot error bands incorrectly unless you adjust them: ymax %f -> %f; ymin %f -> %f"    %(hmass, ymax, ymax_seen, ymin, ymin_seen)

if rangeError:
	exit(1)

suffix = ""
if (logx == 1):
	if (logy == 1):
		suffix = "LogXY"
	else:
		suffix = "LogX"
else:
	if (logy == 1):
		suffix = "LogY"

#f = r.TFile("limits"+FileInfix+"Lifetime"+LeptonType+str(hmass)+suffix+"Exp2.png", "RECREATE")
#for plots in plotsVec:
#	plots.g.Write()
#	plots.gest1.Write()
#f.Close()

if Xlimits:
	c.Print("limitsLifetime"+LeptonType+"MH"+str(hmass)+".png")
	c.Print("limitsLifetime"+LeptonType+"MH"+str(hmass)+".pdf")
else:
	c.Print("limitsLifetime"+LeptonType+"_neutralino.png")
	c.Print("limitsLifetime"+LeptonType+"_neutralino.pdf")

#raw_input("Press ENTER to finish...")
#sys.stdin.read(1)
