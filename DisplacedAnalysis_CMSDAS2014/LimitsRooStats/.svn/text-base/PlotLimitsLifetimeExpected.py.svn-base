import ROOT as r
import sys,os
import pickle

r.gROOT.LoadMacro("tdrstyle.C")
r.setTDRStyle()

# Configurable parameters
# Note that the output of mainSigma.py is simply sigma,
# so we have to add the BR back in

br = 0.01
logx = 1
logy = 1
drawExpected = 1
lumiEle = "4.1"
lumiMu = "5.1"

if len(sys.argv) < 3:
	sys.exit('Usage: python PlotLimitsLifetime.py LeptonType HiggsMass')

LeptonType = sys.argv[1]
hmass = int(sys.argv[2])
FileDir = LeptonType

if len(sys.argv) > 3 and sys.argv[3] == "CLs":
	clmode = 1
	FileDir += "CLs"
	FileInfix = "CLs"
	# br = 1 # don't need to add the BR back in in this case
elif len(sys.argv) > 3 and sys.argv[3] == "CLsIan":
	clmode = 2
	FileDir += "_txt"
	FileInfix = "CLs"
	br = 1 # don't need to add the BR back in in this case
else:
	clmode = 0
	FileInfix = "BayesianWinter"
	FileDir += "BayesianWinterFreeze"
# clmode == -1 is kept to deal with old behavior. Not supported any more.
	
#if (LeptonType.find("Electron") > -1 and clmode != 2):
#	drawExpected = 0

ymin = 0
if (hmass == 1000):
	xmasses = ["350", "150", "050", "020"]
	xmin = 0.04
	xmax = 1100
	ymax = 0.08
	if (logy == 1):
		if (LeptonType.find("Electron") > -1):
			ymin = 0.0003
			ymax = 500.0
		else:
			ymin = 0.0003
			ymax = 500.0
elif (hmass == 400):
	xmasses = ["150", "050", "020"]
	xmin = 0.1
	xmax = 1500
	ymax = 0.08
	if (logy == 1):
		if (LeptonType.find("Electron") > -1):
			ymin = 0.0003
			ymax = 500.0
		else:
			ymin = 0.0003
			ymax = 500.0
elif (hmass == 200):
	xmasses = ["050", "020"]
	xmin = 0.1
	xmax = 1000
	ymax = 1
	if (logy == 1):
		if (LeptonType.find("Electron") > -1):
			ymin = 0.0003
			ymax = 500.0
		else:
			ymin = 0.0003
			ymax = 500.0
elif (hmass == 125):
	xmasses = ["050", "020"]
	xmin = 0.3
	xmax = 2000
	if (LeptonType.find("Electron") > - 1):
		ymin = 0.01
		ymax = 200000.0
	else:
		ymin = 0.003
		ymax = 3000.0
elif (hmass == 120):
	xmasses = ["050", "020"]
	xmin = 0.1
	xmax = 2000
	ymax = 1
	if (logy == 1):
		if (LeptonType.find("Electron") > -1):
			ymin = 0.03
			ymax = 50000.0
		else:
			ymin = 0.03
			ymax = 100000.0
else:
	print "Oops, mass not recognized"

g = {}
gest1 = {}
gest2 = {}
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
r.gPad.SetTopMargin(0.10)
r.gPad.SetRightMargin(0.04)
fr = c.DrawFrame(xmin, ymin, xmax, ymax)
if (LeptonType.find("Electron") > -1):
	fr.SetTitle("CMS Preliminary #sqrt{s}=7 TeV L="+lumiEle+" fb^{-1}")
	t1 = r.TLatex(xmin*2, ymax/3, "e^{+}e^{-}")
	t1.Draw()
elif (LeptonType.find("Muon") > -1):
	fr.SetTitle("CMS Preliminary #sqrt{s}=7 TeV L="+lumiMu+" fb^{-1}")
	t1 = r.TLatex(xmin*2, ymax/3, "#mu^{+}#mu^{-}")
	t1.Draw()
t1.SetTextFont(42)

fr.GetXaxis().SetTitle("c#tau [cm]")
#fr.GetYaxis().SetTitle("Cross Section #times BR [pb] (95% CL)")
fr.GetYaxis().SetTitle("Cross Section #times BR [pb] (2#sigma CL)")
#fr.GetYaxis().SetTitleOffset(1.8)
fr.GetXaxis().SetTitleOffset(1.05)
if (logx == 1):
	r.gPad.SetLogx()
if (logy == 1):
	r.gPad.SetLogy()

leg = r.TLegend(0.4, 0.6, 0.88, 0.88)
leg.SetFillColor(0)
leg.SetBorderSize(0)
leg.SetTextFont(42)
dummy = r.TH1F("dummy", "dummy", 1, 1, 1)
dummy.SetLineColor(0)
dummy.SetMarkerColor(0)
dummy.SetFillColor(0)
leg.AddEntry(dummy, "m_{H} = "+str(hmass)+ " GeV/c^{2}")

last_mass = 0

ymax_seen = 0.
ymin_seen = 9.9e9
for xmass in xmasses:
	ixmass = int(xmass)
	if (clmode == 2):
		xmass = str(int(xmass)) # Remove leading 0.
	if clmode == -1 and xmass[0] == "0":
		xmass = xmass[1:]
	flist = []
	for filename in os.listdir(FileDir):
		if (filename.find('.txt')>-1 and filename.find(str(hmass)+"_"+str(xmass))==0 and
		    filename.find("BC")==-1 and filename.find("NLO")==-1):
			flist.append(filename[:-4])

	if len(flist) > 0:

		flist.sort(key=lambda str: float(str.split("_")[2]))
		print "Files found for " + str(xmass) + ": " + str(flist)
		flist = [str(a)+'.txt' for a in flist]

		# graph for limits:
		g[ixmass] = r.TGraph(2+len(flist))
		gest1[ixmass] = r.TGraphErrors(2+len(flist))
		gest2[ixmass] = r.TGraphErrors(2+len(flist))
		lmax=-1
		lmin=9999
		i = 1
	        expLimitFactor = 1
		for filename in flist:
			lt=float(filename[:-4].split("_")[2])
			# print "Lifetime in "+FileDir+"/"+filename+" is " + str(lt)
			if lt > lmax:
				lmax = lt
			if lt < lmin:
				lmin = lt

			f = open(FileDir+"/"+filename)

			if clmode != -1:
				#q = [eval(a) for a in f.readline().split()]
				#m = q[0]
				#up = q[2]
				#est = q[2]
				#est1 = 0
				#est2 = 0

				q = pickle.load(f)
				m = q[0]
				up = q[1]
				est = q[2]
				est1p = q[3]
				est1m = q[4]
				est2p = q[5]
				est2m = q[6]
				# print "CHECK ",filename," ",m," ",up, " ",est1p

				# Note: sometimes the Bayesian limit
				# fails to compute for whatever reason.
				# In this case we just use the ratio from
				# the events plot since it should be the same.

				if (clmode == 0):
					# Bayesian limits should be properly computed. But for
					# some reason sometimes they fail. In this case
					# just extrapolate using the same ratio from the previous
					# point (fortunately this seems to happen at high ctau).

					if (est1p == -1):
					    print "Limit calc failed in "+filename+", extrapolating..."
					    est = up
					    est1p = up*expLimitFactor
					    est1m = up
				        else:
					    expLimitFactor = est1p/up

					# Also widenify band a little bit, as for Ian's
					if abs(est1p - est) < 1.0e-1*est:
						est1p = (1 + 1.0e-1)*est
					if abs(est1m - est) < 1.0e-1*est:
						est1m = (1 - 1.0e-1)*est
					if abs(est2p - est) < 2.0e-1*est:
						est2p = (1 + 2.0e-1)*est
					if abs(est2m - est) < 2.0e-1*est:
						est2m = (1 - 2.0e-1)*est							

				elif (clmode == 1):
					# On the other hand, the CLs limits are hardcoded here
					est = up
					est1p = up*6.43634/3.03029
					est1m = up
				elif (clmode == 2):
					# Full CLs (Ian)
					# Band becomes unstable if too narrow.
					if abs(est1p - est) < 1.0e-1*est:
						est1p = (1 + 1.0e-1)*est
					if abs(est1m - est) < 1.0e-1*est:
						est1m = (1 - 1.0e-1)*est
					if abs(est2p - est) < 2.0e-1*est:
						est2p = (1 + 2.0e-1)*est
					if abs(est2m - est) < 2.0e-1*est:
						est2m = (1 - 2.0e-1)*est							

			else:
				# old CLs parsing code
				q = [eval(a) for a in f.readline().split()]
				m = q[0]
				up = q[1]
				est = q[1]   # a little bit of cheating here
				est1p = q[2] - q[1]
				est1m = q[1] - q[3]
				est1 = (est1p + est1m)/2

			# don't know why this is necessary, but it is
			if (clmode != 2 and est1m > up): est1m = up

			# Note min and max limit seen at any point on curve.
			ymax_seen = max(ymax_seen, up, est2p)
			ymin_seen = min(ymin_seen, up, est2m)

			g[ixmass].SetPoint(i,lt,up*br)

			gest1[ixmass].SetPoint(i,lt,br*(est1p+est1m)/2)
			gest1[ixmass].SetPointError(i,0,br*(est1p-est1m)/2)
			gest2[ixmass].SetPoint(i,lt,br*(est2p+est2m)/2)
			gest2[ixmass].SetPointError(i,0,br*(est2p-est2m)/2)

			# This is needed to ensure the curve extrapolates smoothly between the points.
			if i == 1:
				g[ixmass].SetPoint(0,lt,up*br)
				gest1[ixmass].SetPoint(0,lt,br*(est1p+est1m)/2)
				gest1[ixmass].SetPointError(0,0,br*(est1p-est1m)/2)
				gest2[ixmass].SetPoint(0,lt,br*(est2p+est2m)/2)
				gest2[ixmass].SetPointError(0,0,br*(est2p-est2m)/2)

			# print "PLOTTING ",filename," ",m," ",lt," ",est, " (1) ",est1p, "/", est1m, " (2) ",est2p, "/", est2m,"\n"

			i+=1

		# This is needed to ensure the curve extrapolates smoothly between the points.
		g[ixmass].SetPoint(i,lt,up*br)
		gest1[ixmass].SetPoint(i,lt,br*(est1p+est1m)/2)
		gest1[ixmass].SetPointError(i,0,br*(est1p-est1m)/2)
		gest2[ixmass].SetPoint(i,lt,br*(est2p+est2m)/2)
		gest2[ixmass].SetPointError(i,0,br*(est2p-est2m)/2)

		# Draw in order: +/- 2 sigma band, +/- 1 sigma band, actual

		gest2[ixmass].SetFillColor(r.kYellow)
#		gest2[ixmass].SetFillStyle(3005)
		gest2[ixmass].SetFillStyle(1001)
		gest2[ixmass].SetMarkerStyle(0)
		gest2[ixmass].SetMarkerColor(0)
		gest2[ixmass].SetLineColor(0)
		gest1[ixmass].SetFillColor(r.kGreen)
#		gest1[ixmass].SetFillStyle(3005)
		gest1[ixmass].SetFillStyle(1001)
		gest1[ixmass].SetMarkerStyle(0)
		gest1[ixmass].SetMarkerColor(0)
		gest1[ixmass].SetLineColor(0)
		if (drawExpected):
			last_mass = ixmass
			gest2[ixmass].Draw("4 same")
#			gest1[ixmass].Draw("4 same")


		g[ixmass].SetLineColor(jcol)
		g[ixmass].SetFillColor(0)
		g[ixmass].SetMarkerColor(jcol)
		g[ixmass].SetMarkerStyle(jpoly)
		g[ixmass].SetMarkerSize(1.5)
		g[ixmass].SetLineWidth(2)

	        # Plot all observed limit curves later, outside the loop, since otherwise
		# they can be covered by the expected limit curve.
		#g[ixmass].Draw("lp same")
		#leg.AddEntry(g[ixmass], "m_{X} = " + str(int(xmass)) + " GeV/c^{2}")

		#g[ixmass].Fit("pol3", "", "", lmin, lmax)
		#f1 = g[ixmass].GetFunction("pol3")
		#f1 = r.TF1("f"+str(xmass), "1/([0]+[1]/x + [2]/(x*x) + [3]/(x*x*x))", lmin, lmax)
		#g[ixmass].Fit(f1, "", "", lmin, lmax)
		#f1.SetLineColor(jcol)

		jpoly += 1 # Change polymarker
		jcol += 1 # Change line color
		if (jcol == 3 or jcol == 5) :
			jcol += 1 # Don't want light green or yellow

# Plot observed limits (do after expected limits, to ensure not covered up)
for mass in sorted(g):
		g[mass].Draw("lp same")
		leg.AddEntry(g[mass], "m_{X} = " + str(int(mass)) + " GeV/c^{2}")

# Only want one expected limit entry in key, so add it now outside mass loop.
if last_mass > 0:
  # leg.AddEntry(gest1[last_mass], "Expected limit (68%)")
  # leg.AddEntry(gest2[last_mass], "Expected limit (95%)", "f")
  leg.AddEntry(gest2[last_mass], "Expected limit (2#sigma CL)", "f")

leg.Draw()
c.Update()

print "y-range seen = %s - %s" %(ymin_seen, ymax_seen)
#if ymin_seen < ymin or ymax_seen > ymax:
#	sys.exit("ERROR: Either ymax is too small or ymin too large. TGraphErrors may plot error bands incorrectly unless you adjust them: %f/%f %f/%f" %(ymin, ymin_seen, ymax, ymax_seen))

suffix = ""
if (logx == 1):
	if (logy == 1):
		suffix = "LogXY"
	else:
		suffix = "LogX"
else:
	if (logy == 1):
		suffix = "LogY"

#f = r.TFile("limits"+FileInfix+"Lifetime"+LeptonType+str(hmass)+suffix+".root", "RECREATE")
#for xmass in xmasses:
#	g[ixmass].Write()
#	gest1[ixmass].Write()
#f.Close()

# In this version, the "LogXYExp" is removed -- the names are getting awfully long
# and they're always present in these versions anyway
c.Print("limits"+FileInfix+"Lifetime"+LeptonType+"MH"+str(hmass)+".png")
c.Print("limits"+FileInfix+"Lifetime"+LeptonType+"MH"+str(hmass)+".pdf")
raw_input("Press ENTER to finish...")
