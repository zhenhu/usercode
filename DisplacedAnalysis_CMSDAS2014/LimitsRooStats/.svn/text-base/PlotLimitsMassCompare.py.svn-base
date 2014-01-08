import ROOT as r
import sys,os
import pickle

lumiEle = "4.1"
lumiMu = "5.1"

r.gROOT.LoadMacro("tdrstyle.C")
r.setTDRStyle()

# A simple script to allow comparisons of the limits
# vs. mass with two separate scenarios.
# Set the directory names below after this function.

def GetGraph(LeptonType, FileDir):
	flist = []
	for filename in os.listdir(FileDir):
		if filename.find('.txt')>-1:
			flist.append(float(filename[:-4]))
	flist.sort()
	print flist
	flist = [str(a)+'.txt' for a in flist]

	# graph for limits:
	g = r.TGraphErrors(len(flist))
	gest = r.TGraphErrors(len(flist))
	i = 0
	for filename in flist:
		f = open(FileDir+"/"+filename)
		#items = [eval(a) for a in f.readline().split()]
		#m = items[0]
		#low = items[1]
		#up = items[2]

		q = pickle.load(f)
		m = q[0]
		up = q[1]
		est = q[2]
		est1p = q[3]
		est1m = q[4]
		est2p = q[5]
		est2m = q[6]

		# Now fix the numbers for the CLs:
		if (clmode == 1):
			if (LeptonType.find("Muon") > -1):
				up = 3.03029
				est1p = 6.43634
				est1m = 3.03029
			if (LeptonType.find("Electron") > -1):
				if (m == 90):
					up = 4.75039
				else:
					up = 3.03029
				if (m > 82.5 and m < 97.5):
					est1p = 6.43634
					est1m = 3.03029
				else:
					est1p = 3.03029
					est1m = 3.03029

		g.SetPoint(i,m,up)
		#g.SetPointError(i,0,0.5*(up-low))

		#gest.SetPoint(i, m, (est1p+est1m)/2)
		#gest.SetPointError(i, 0, (est1p-est1m)/2)
		gest.SetPoint(i, m, (est2p+est2m)/2)

		# Give the band a small width so that it's visible
		if (est2p-est2m) < 0.01:
			gest.SetPointError(i, 0, 0.01)
		else:
			gest.SetPointError(i, 0, (est2p-est2m)/2)

		i+=1

	# ROOT bug in plotting TGraphErrors (thank you ROOT)
	g.SetPoint(i,m,up)
	gest.SetPoint(i, m, (est1p+est1m)/2)
	gest.SetPointError(i, 0, (est1p-est1m)/2)

	if (LeptonType.find("Electron") > -1):
		g.SetTitle("Limit on signal events, electron channel")
	elif (LeptonType.find("Muon") > -1):
		g.SetTitle("Limit on signal events, muon channel")
	else:
		g.SetTitle("Limit")

	g.SetLineColor(r.kBlue)
	g.SetFillColor(0)
	g.SetMarkerColor(r.kBlue)
	g.SetMarkerStyle(r.kFullSquare)
	g.SetMarkerSize(1)
	g.SetLineWidth(2)

	g.GetXaxis().SetRangeUser(20,500)
	g.GetXaxis().SetTitle("Mass of X boson [GeV/c^{2}]")
	g.GetYaxis().SetTitle("Number of signal events (95% CL)")
	#g.GetYaxis().SetTitle("Number of signal events (2#sigma CL)")

	gest.SetLineColor(0)
	# harmonize with Ian
	#gest.SetFillColor(r.kRed)
	#gest.SetFillStyle(3005)
	gest.SetFillColor(r.kYellow)
	gest.SetFillStyle(1001)

	g.SetMinimum(0)
	g.SetMaximum(6)
	#gest.Draw("a3")
	#g.Draw("l same")

	return g

if len(sys.argv) < 2:
	sys.exit('Usage: python PlotLimitsMass.py LeptonType [CLs]')

LeptonType = sys.argv[1]

if len(sys.argv) > 2 and sys.argv[2] == "CLs":
	clmode = 1
	FileInfix = "CLsWinter"
else:
	clmode = 0
	FileInfix = "BayesianWinter"


#r.gROOT.SetStyle("Plain")
r.gStyle.SetErrorX(0)
# have to restore the title though
r.gStyle.SetOptTitle(1)
r.gStyle.SetTitleBorderSize(0)
#r.gStyle.SetTitleFont(42, "")

c = r.TCanvas("c","c",600,600)
r.gPad.SetTopMargin(0.10)
r.gPad.SetRightMargin(0.04)

g1 = GetGraph(LeptonType, LeptonType + "BayesianWinterMassFinal")
g2 = GetGraph(LeptonType, LeptonType + "BayesianWinterMassNewRes")

g1.SetLineColor(r.kRed)
g1.SetLineStyle(r.kDashed)
g1.Draw("al")
g2.Draw("l same")

leg = r.TLegend(0.4, 0.17, 0.88, 0.35)
leg.SetFillColor(0)
leg.SetBorderSize(0)
leg.AddEntry(g1, "Previous results")
leg.AddEntry(g2, "New results")
leg.SetTextFont(42)
leg.Draw()

if (LeptonType.find("Electron") > -1):
	g1.SetMinimum(1.5)
	g1.SetTitle("CMS #sqrt{s}=7 TeV L="+lumiEle+" fb^{-1}")
	if (clmode == 0):
		g1.SetMaximum(6.4)
		t1 = r.TLatex(30, 6.0, "e^{+}e^{-}")
	else:
		g1.SetMinimum(1)
		g1.SetMaximum(7)
		t1 = r.TLatex(30, 6.5, "e^{+}e^{-}")
	t1.Draw()
elif (LeptonType.find("Muon") > -1):
	g1.SetTitle("CMS #sqrt{s}=7 TeV L="+lumiMu+" fb^{-1}")
	if (clmode == 0):
		t1 = r.TLatex(30, 5.5, "#mu^{+}#mu^{-}")
	else:
		g1.SetMaximum(8)
		t1 = r.TLatex(30, 7.5, "#mu^{+}#mu^{-}")
	t1.Draw()
t1.SetTextFont(42)

c.Print("limits"+FileInfix+"Events"+LeptonType+"Compare.png")
#c.Print("limits"+FileInfix+"Events"+LeptonType+"Compare.pdf")

raw_input("Press ENTER to finish...")
