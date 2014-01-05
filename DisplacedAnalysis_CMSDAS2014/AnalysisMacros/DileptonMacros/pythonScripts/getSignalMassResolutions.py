import sys,os,ROOT as r
from ROOT import gSystem
gSystem.Load('libRooFit')

r.gROOT.SetBatch()
r.gStyle.SetOptStat(111)
r.gStyle.SetOptFit(1111)

pTypes = ['muons','electrons']

massDir='SignalMassResolutionFiles'

higgs='HTo2LongLivedTo4F_'
chi='Chi0ToNuLL_'

ctau_map={
        higgs+'MH1000_MFF20':1.5,
        higgs+'MH1000_MFF50':4,
        higgs+'MH1000_MFF150':10,
        higgs+'MH1000_MFF350':35,
        higgs+'MH400_MFF20':4,
        higgs+'MH400_MFF50':8,
        higgs+'MH400_MFF150':40,
        higgs+'MH200_MFF20':7,
        higgs+'MH200_MFF50':20,
        higgs+'MH125_MFF50':50,
        higgs+'MH125_MFF20':13,
#          chi+'MSquark1500_MChi494':35,
#          chi+'MSquark1000_MChi148':10,chi+'MSquark350_MChi48':8,chi+'MSquark120_MChi48':50
}

res_map = {higgs+'MH1000_MFF20':[],higgs+'MH1000_MFF50':[],higgs+'MH1000_MFF150':[],higgs+'MH1000_MFF350':[],
           higgs+'MH400_MFF20':[],higgs+'MH400_MFF50':[],higgs+'MH400_MFF150':[],
           higgs+'MH200_MFF20':[],higgs+'MH200_MFF50':[],
           higgs+'MH125_MFF20':[],higgs+'MH125_MFF50':[],
           chi+'MSquark1500_MChi494':[],chi+'MSquark1000_MChi148':[],chi+'MSquark350_MChi48':[],chi+'MSquark120_MChi48':[]}

exoticPdg_map = {'6001113':0.1,'6002113':1.,'6003113':10.,'1000022':1}

# This should be the same as what is used in getSignalEfficiencies.py
from samplesConfig import lifeTimeFactors as ctfact_list
# ctfact_list=[0.1,0.2,0.3,0.4,0.5,1.,2.,3.,4,5]
#ctfact_list = [1]

c = r.TCanvas()

def weight(t,t0,t_new):
    import math
    return t0/float(t_new) * math.exp(-t*(1./float(t_new) -1./float(t0) ))

def resolutions(factor,exotic,sample):
    t0 = ctau_map[sample] * exoticPdg_map[exotic]
    # ctau = eval(str(round(t0*factor,2)))
    ctau = eval(str(round(t0*factor,3)))
    sigma_mu = 0
    sigma_mu_e = 0
    sigma_e = 0
    sigma_e_e = 0
    
    truemass = None
    massString = sample.split('_')[2]
    offset=3
    if massString[1]=="C": offset=4
    
    if massString[offset]=="0":     
        truemass = eval(massString[offset+1:])
    else:
        truemass = eval(massString[offset:])
    
    print "=============", truemass
    print "=============",t0


    for pType in pTypes:
        for file in os.listdir(massDir+'/'+pType):
            if file.find(sample)>-1: break
            
        filecontent = open(massDir+'/'+pType+'/'+file).readlines()
        hmass = r.TH1F()

        upperBound=0
        lowerBound=0
        if pType == "electrons":
            if exotic=="1000022" :
                upperBound=1.10*truemass
                lowerBound=0.2*truemass
            else :
                upperBound=1.15*truemass
                lowerBound=0.85*truemass
        else:
            if exotic=="1000022" :
                upperBound=1.10*truemass
                lowerBound=0.6*truemass
            else :
                upperBound=1.30*truemass
                lowerBound=0.7*truemass
                
        hmass = r.TH1F('mass','mass',15,lowerBound,upperBound)              
        hweight = r.TH1F('weights','weights',50,0,-1)

        for line in filecontent[1:]:
            line = line.strip()
            data = [eval(a) for a in line.split()]
            if str(data[2]) != exotic : continue
            mass = 0
            if exotic=="1000022" : mass = data[1]
            else : mass = data[0]
            t = data[3]
            w = weight(t,t0,ctau)
            hmass.Fill(mass,w)
            hweight.Fill(w)
            pass
        
        hmass.SetTitle(sample+' '+exotic+' ctau: '+str(t0)+'cm weighted to '+str(ctau)+'cm '+pType)
        hweight.SetTitle(sample+' '+exotic+' ctau: '+str(t0)+'cm weighted to '+str(ctau)+'cm weights '+pType)
        hmass.Draw()

        if hmass.Integral() == 0: 
            # If no events survived final cuts, don't try to fit distribution...
            if pType == "electrons":
                sigma_e = -1
                sigma_e_e = -1
            else:
                sigma_mu = -1
                sigma_mu_e = -1
            pass
        else:
            mass = r.RooRealVar("mass","Reconstructed Candidate Mass",0.0,800.0,"GeV")
            arglist = r.RooArgList( mass )
            data = r.RooDataHist("data","data",arglist,hmass)
            fitFunction = r.RooGenericPdf()
            fitResults = r.RooFitResult()
            normalFit = r.TF1()
                
            if exotic=="1000022" :
                # Fit crystal ball to chi->ll+nu
                # Have to use roofit
                if pType == 'electrons' :
                    mean =  r.RooRealVar("mean","CB Mean",lowerBound,upperBound,"GeV")
                    sigma = r.RooRealVar("sigma","CB Sigma",1.0,50.0,"GeV")
                    n = r.RooRealVar("n", "n", 0, 5);
                    alpha = r.RooRealVar("alpha", "alpha", 0, 100);
                    cb = r.RooCBShape("CB","Crystal Ball",mass,mean,sigma,n,alpha)
                else :
                    mean =  r.RooRealVar("mean","CB Mean",lowerBound,upperBound,"GeV")
                    sigma = r.RooRealVar("sigma","CB Sigma",0.0,20.0,"GeV")
                    n = r.RooRealVar("n", "n", 0, 3);
                    alpha = r.RooRealVar("alpha", "alpha", 0, 2);
                    cb = r.RooCBShape("CB","Crystal Ball",mass,mean,sigma,n,alpha)
                fitFunction = cb
                fitResults = fitFunction.fitTo(data, r.RooFit.Save())
                fitResults.Print('v')
                frame = r.RooPlot()
                frame = mass.frame(lowerBound,upperBound)
                frame.SetTitle(sample+' '+exotic+' ctau: '+str(t0)+'cm weighted to '+str(ctau)+'cm '+pType)
                data.plotOn(frame)
                fitFunction.plotOn(frame)
                fitFunction.paramOn(frame,r.RooFit.Layout(0.12,0.5,0.9))
                frame.Draw();
                c.Update()
                c.SaveAs(massDir+'/'+sample+'_'+exotic+'.pdf(')
            else:
                # Do normal root fit
                hmass.Fit("gaus","Q")
                normalFit = hmass.GetFunction('gaus')
            
            hmass.Draw('E')
            c.SaveAs(massDir+'/'+sample+'_'+exotic+'.pdf(')
            c.SetLogy(1)
            hweight.Draw()
            c.SaveAs(massDir+'/'+sample+'_'+exotic+'.pdf(')
            c.SetLogy(0)
            
            if exotic=="1000022" :
                if pType == "electrons":
                    sigma_e = abs(sigma.getVal())
                    sigma_e_e = abs(sigma.getError())
                else:
                    sigma_mu = abs(sigma.getVal())
                    sigma_mu_e = abs(sigma.getError())
            else :
                if pType == "electrons":
                    sigma_e = abs(normalFit.GetParameter(2))
                    sigma_e_e = abs(normalFit.GetParError(2))
                else:
                    sigma_mu = abs(normalFit.GetParameter(2))
                    sigma_mu_e = abs(normalFit.GetParError(2))
                    pass
                pass
            pass
        pass

    result = res_map[sample]
    result.append([ctau,exotic,factor,sigma_mu,sigma_mu_e,sigma_e,sigma_e_e])
    res_map.update({sample:result})

for key in ctau_map:
    for exotic in exoticPdg_map:
        if key.find("Squark")>=0 and exotic != '1000022' : continue
        elif key.find("H")>=0 and exotic == '1000022' : continue
        for factor in ctfact_list:
            resolutions(factor,exotic,key)
        c.SaveAs(massDir+'/'+key+'_'+exotic+'.pdf)')

import pickle
pickle.dump(res_map, open(massDir+'/results.pkl','wb'))

# Output to text file
# Also output to latex table format
outputFile=open(massDir+'/massResolutions.txt','w')
outputLatexFile=open(massDir+'/latexMassResolutions.txt','w')
for key in sorted(res_map.keys()):
    firstEntryForThisPoint = True
    
    # Output signal point
    print key
    outputFile.write(key+'\n')
    
    # Output header
    print "PDG    ctau    factor    res_mu    err    res_e    err"
    outputFile.write("PDG    ctau    factor    res_mu    err    res_e    err\n")
    
    # Output resolution for each lifetime
    results = res_map[key]
    if len(results) > 0 :
        for result in results:
            print ('%s\t%.4g\t%.4g\t%.4g\t%.4g\t%.4g\t%.4g' % (result[1],result[0],result[2],result[3],result[4],result[5],result[6]) )
            outputFile.write('%s\t%.4g\t%.4g\t%.4g\t%.4g\t%.4g\t%.4g\n' % (result[1],result[0],result[2],result[3],result[4],result[5],result[6]))
    
            # Only output mass resolutions for nominal lifetimes
            if result[2] == 1:
                if firstEntryForThisPoint :
                    hMass = key.split('_')[1][2:]
                    xMass = key.split('_')[2][3:]
                    outputLatexFile.write('\t%s\t&\t%s\t&\t%.1f\t&\t%.2f\t&\t%.2f\t\\\\\n' % (hMass,xMass,result[0],result[5],result[3]) )
                    firstEntryForThisPoint=False
                    pass
                else :
                    outputLatexFile.write('\t&\t&\t%.1f\t&\t%.2f\t&\t%.2f\t\\\\\n' % (result[0],result[5],result[3]) )
                    pass
                pass
            pass
        # Add emtpy line
        outputFile.write('\n')
        outputLatexFile.write('\\hline\n')
        pass
    print
    pass
