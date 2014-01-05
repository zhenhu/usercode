import os,sys
import ROOT as r
from commonMethods import *
from array import array

r.gROOT.Macro( 'tdrstyle.C' )
r.gROOT.SetBatch()
r.gStyle.SetPadTopMargin(0.1);
r.gStyle.SetPadLeftMargin(0.15);
r.gStyle.SetPadRightMargin(0.05);
r.gStyle.SetErrorX(0.5)

doOriginalPlots = True
doFractionPlots = False

file="CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF150_CTau10To1000_combined_"
# file = "CombinedFiles/HTo2LongLivedTo4F_MH400_MFF50_CTau8To800_combined_"
# file = "CombinedFiles/HTo2LongLivedTo4F_MH200_MFF50_CTau20To2000_combined_"


iso = 'relIsolation'
# iso = 'isolation'
# iso = 'pt'
# iso = 'crossCheck' # This option takes the abs isolation and pt histograms and attempts to recreate the rel iso plot

channels=[
        '2eTrack',
        '2muTrack'
          ]

useCollinearityMethod = True


# Loop over files and get histograms
for channel in channels:
    fileName = file+channel+'.root'
    print "Processing ",fileName
    
    # Open file
    openFile=r.TFile.Open(fileName)
    
    if doOriginalPlots:
        
        if useCollinearityMethod :
            histos={
            'L' : 'nMinus1_'+iso+'LeptonL_vsPU_finalCollCuts_genMatched',
            'H' : 'nMinus1_'+iso+'LeptonH_vsPU_finalCollCuts_genMatched',
            }
            pass
        else :
            histos={
            'L' : 'nMinus1_'+iso+'LeptonL_vsPU_finalCuts_genMatched',
            'H' : 'nMinus1_'+iso+'LeptonH_vsPU_finalCuts_genMatched',
            }
            pass
        
        tprofs = {}
        
        for histo in histos:
            
            if iso.find('crossCheck') < 0:
                # Get histogram
                h = r.TH2F( openFile.Get(histos[histo]))
                
                # Make TProfile of histo
#                 prof = r.TProfile( h.ProfileY('_pfy',1,-1,'s') )
                prof = r.TProfile( h.ProfileY() )
#                 prof.Rebin( 2 )
    
                pass
            else :
                # Cross Check
                # Get histograms
                hPt = r.TH2F( openFile.Get('nMinus1_ptLepton'+histo+'_vsPU_finalCuts_genMatched') )
                hIso = r.TH2F( openFile.Get('nMinus1_isolationLepton'+histo+'_vsPU_finalCuts_genMatched') )

                # Make TProfiles
                profPt = r.TProfile( hPt.ProfileY() )
                profIso = r.TProfile( hIso.ProfileY() )
                profIso.Divide( profPt )
                prof = profIso.Clone()
                pass
    
            prof.SetMarkerStyle(20)
            prof.SetLineStyle(2)
    #         prof.SetLineWidth(2)
            if histo is 'H':
                prof.SetMarkerColor(2)
                prof.SetLineColor(2)
            elif histo is 'L':
                prof.SetMarkerColor(4)
                prof.SetLineColor(4)
            
            # Is this relative or absolute isolation?
            if iso.find('relIsolation') >= 0 :
                prof.GetYaxis().SetTitle('#Sigma p_{t}/p^{lepton '+histo+'}_{t}')
                prof.GetYaxis().SetRangeUser(0,0.1)
            elif iso.find('pt') >= 0 :
                prof.GetYaxis().SetTitle('p_{t}')
            else:
                prof.GetYaxis().SetTitle('#Sigma p_{t}')
                pass

            prof.GetXaxis().SetTitle('Number Reconstructed PV')
            prof.GetYaxis().SetLabelSize(0.035)
            prof.GetYaxis().SetTitleSize(0.035)
            prof.GetYaxis().SetTitleOffset(2.0)
                        
            tprofs[histo] = prof
            pass
    
    
        # Make canvas            
        canvas=r.TCanvas("canvas")
        
        # Make legend
        legend=r.TLegend(0.3,0.6,0.5,0.8)
        legend.SetFillStyle(0)
        legend.SetBorderSize(0)
        
    
        
        firstPlot = True
        option = 'P E1'
        if iso is 'crossCheck' : option ='P HIST'
        
        for prof in tprofs :
            if firstPlot :
                tprofs[prof].Draw(option)
                firstPlot = False
            else :
                tprofs[prof].Draw(option+' SAME')
                pass
            if prof is 'H':
                legend.AddEntry(tprofs[prof],'High P_{T} lepton','P')
            elif prof is 'L':
                legend.AddEntry(tprofs[prof],'Low P_{T} lepton','P')
            pass
                    
        # Add title
        T1 = r.TLatex()
        T1.SetNDC()
        T1.DrawLatex(0.2,0.93,"#scale[0.9]{CMS Simulation #sqrt{s} = 8 TeV}")
        
        # Draw legend
        legend.Draw()
        
        # Add channel
        addChannelLatex( channel, 0.35, 0.8 )
        
        canvas.Update()
        if useCollinearityMethod :
            outputFileName='output/pdfOutput/nMinus1_'+iso+'_vsPU_finalCollCuts_genMatched'+'_coll_'+channel+'.pdf'
            pass
        else :
            outputFileName='output/pdfOutput/nMinus1_'+iso+'_vsPU_finalCollCuts_genMatched'+'_'+channel+'.pdf'
        print 'Saving as :',outputFileName
        canvas.Print(outputFileName)
        raw_input("Press Enter to continue...")
        pass
    
    if doFractionPlots:
        # Get histos from file
        histosToDraw = {}
        
        rebin = 2
        
        for lepton in ['L','H'] :
            if useCollinearityMethod :
                hAll = r.TH1F( openFile.Get('nMinus1_fracRelIsoLepton'+lepton+'_vsPU_finalCollCuts_genMatched_all') )
                hPass = r.TH1F( openFile.Get('nMinus1_fracRelIsoLepton'+lepton+'_vsPU_finalCollCuts_genMatched_pass') )
                pass
            else :
                hAll = r.TH1F( openFile.Get('nMinus1_fracRelIsoLepton'+lepton+'_vsPU_finalCuts_genMatched_all') )
                hPass = r.TH1F( openFile.Get('nMinus1_fracRelIsoLepton'+lepton+'_vsPU_finalCuts_genMatched_pass') )
                pass
            
            # Normal rebin ?
#             hAll.Rebin( rebin )
#             hPass.Rebin( rebin )
            
            # Or rebin into variable bin sizes?
            binning = []
            
#             for bin in range (1,hAll.GetNbinsX()) :
#                 print 'Bin edge :',hAll.GetBinCenter(bin),'Entries :',hAll.GetBinContent(bin)
            
            maxBin = 50
            nBins = 0
            bin = 0
            while bin <= maxBin:
                binning.append(bin)
                nBins = nBins + 1
                
                totalContent = hAll.GetBinContent( bin )
                while totalContent < 1E-4 :
                    bin = bin + 1
                    if bin > maxBin :
                        binning.append(maxBin)
                        break
                    totalContent = totalContent + hAll.GetBinContent( bin )
                    pass
                if bin > maxBin :
                    break
                bin = bin + 1
                pass
            
            binArray = array("d",binning)
            hAllRebin = hAll.Rebin(nBins,'hAllRebin',binArray)
            hPassRebin = hPass.Rebin(nBins,'hPassRebin',binArray)
             
            hAll = hAllRebin
            hPass = hPassRebin
            
            # Divide hPass by hAll
            hPass.Divide(hPass,hAll,1,1,'B')

            hPass.GetYaxis().SetTitle('Fraction passing relIso cut')
            hPass.GetXaxis().SetTitle('# reco PV')
            hPass.GetYaxis().SetLabelSize(0.035)
            hPass.GetYaxis().SetTitleSize(0.035)
            hPass.GetYaxis().SetTitleOffset(2.0)
            hPass.GetYaxis().SetRangeUser(0.7,1.01)
            
            hPass.SetMarkerStyle(20)
            hPass.SetLineStyle(2)
            if lepton is 'H':
                hPass.SetMarkerColor(2)
                hPass.SetLineColor(2)
            elif lepton is 'L':
                hPass.SetMarkerColor(4)
                hPass.SetLineColor(4)
                pass
                      
            histosToDraw[lepton] = hPass
            pass
        
        # Draw histograms
        canvas=r.TCanvas("canvas")
        
        firstPlot = True
        for h in histosToDraw:
            if firstPlot :
                histosToDraw[h].Draw('E1 P')
                firstPlot = False
            else :
                histosToDraw[h].Draw('SAME E1 P')
                pass
            pass
        
        # Add channel
        addChannelLatex( channel, 0.2, 0.5 )
        canvas.Update()
        
        raw_input('Waiting...')


            
        
        
        
        
        