import ROOT as r
import sys,os
import pickle

lumiEle = "19.5"
lumiMu = "20.5"

#r.gROOT.SetStyle("Plain")
r.gROOT.LoadMacro("tdrstyle.C")
r.setTDRStyle()
r.gStyle.SetErrorX(0)
# have to restore the title though
r.gStyle.SetOptTitle(1)
r.gStyle.SetTitleBorderSize(0)
r.gStyle.SetTitleFont(42, "")
r.gStyle.SetTitleFont(42, "X")
r.gStyle.SetTitleFont(42, "Y")
r.gStyle.SetTitleX(0.5)
r.gStyle.SetTitleAlign(23)
	
# This is a somewhat hacky script to plot the
# limits vs. mass. CLs limits are no longer
# supported, sorry.

if len(sys.argv) < 2:
	sys.exit('Usage: python PlotLimitsMass.py LeptonType')

LeptonType = sys.argv[1]
FileDir = "Results_" + LeptonType

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

if (LeptonType.find("2e") > -1):
	gest.SetTitle("Limit on signal events, electron channel")
elif (LeptonType.find("2mu") > -1):
	gest.SetTitle("Limit on signal events, muon channel")
else:
	gest.SetTitle("Limit")

g.SetLineColor(r.kBlue)
g.SetFillColor(0)
g.SetMarkerColor(r.kBlue)
g.SetMarkerStyle(r.kFullSquare)
g.SetMarkerSize(1)
g.SetLineWidth(2)

gest.GetXaxis().SetRangeUser(20,500)
gest.GetXaxis().SetTitle("Mass of X boson [GeV/c^{2}]")
gest.GetYaxis().SetTitle("Number of X bosons")
#gest.GetYaxis().SetTitle("Number of signal events (2#sigma CL)")

gest.SetLineColor(0)
# harmonize with Ian
#gest.SetFillColor(r.kRed)
#gest.SetFillStyle(3005)
gest.SetFillColor(r.kYellow)
gest.SetFillStyle(1001)

# plotting
#c = r.TCanvas("c","c",600,1200)
#c.Divide(1,2)
#c.cd(1)
#frame = mass.frame()
#frame.SetTitle("Data")
#data.plotOn(frame)
#bkgPdf.plotOn(frame)
#frame.Draw()
#c.cd(2)
c = r.TCanvas("c","c",600,600)
r.gPad.SetTopMargin(0.10)
r.gPad.SetRightMargin(0.04)

gest.SetMinimum(1.5)
gest.SetMaximum(7.0)
gest.Draw("a3")
gest.GetXaxis().SetNdivisions(50205)
g.Draw("l same")

leg = r.TLegend(0.2, 0.15, 0.88, 0.33)
leg.SetFillColor(0)
leg.SetBorderSize(0)
leg.AddEntry(g, "Observed 95% CL limits", "l")
leg.AddEntry(gest, "Expected 95% CL limits", "f")
leg.SetTextFont(42)
leg.Draw()

if (LeptonType.find("2e") > -1):
	lumi = lumiEle
	t1 = r.TLatex(50, 6.4, "e^{+}e^{-}")
	t1.Draw()

	# inset around mass peak -- not needed for the winter version
	if 0:
		p = r.TPad("p", "p", 0.40, 0.40, 0.88, 0.88)
		p.Draw()
		p.cd()
		ge1 = gest.Clone()
		ge1.SetMinimum(2)
		ge1.SetMaximum(6.5+0.5*clmode)
		ge1.SetTitle("")
		ge1.GetXaxis().SetTitle("")
		ge1.GetYaxis().SetTitle("")
		ge1.GetXaxis().SetRangeUser(85,95)
		ge1.Draw("a3")
		g1 = g.Clone()
		g1.Draw("lp same")
	
elif (LeptonType.find("2mu") > -1):
	lumi = lumiMu
	t1 = r.TLatex(50, 6.4, "#mu^{+}#mu^{-}")
	t1.Draw()
t1.SetTextFont(42)

gest.SetTitle("CMS Preliminary    #sqrt{s} = 8 TeV    L = "+lumi+" fb^{-1}")
c.Print("LimitsVsMass2012_"+LeptonType+".png")
c.Print("LimitsVsMass2012_"+LeptonType+".pdf")

#gest.SetTitle("CMS    #sqrt{s} = 8 TeV    L = "+lumi+" fb^{-1}")
#c.Print("limits"+FileInfix+"Events"+LeptonType+"Exp.png")
#c.Print("limits"+FileInfix+"Events"+LeptonType+"Exp.pdf")

raw_input("Press ENTER to finish...")
