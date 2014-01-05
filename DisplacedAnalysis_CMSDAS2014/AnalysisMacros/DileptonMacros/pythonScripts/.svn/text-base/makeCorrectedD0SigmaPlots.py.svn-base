import os,sys
import ROOT as r
from math import sqrt
from commonMethods import *

r.gROOT.Macro( 'tdrstyle.C' )


fileNames = [
#              'CombinedFiles/Data22Jan_combined_',
             'CombinedFiles/Data_combined_'
             ]

channels=[
#         '2eTrack',
        '2muTrack'
          ]

for channel in channels:
    for fileName in fileNames:
        openFile=r.TFile.Open(fileName+channel+'.root')

        # Get lepton d0/sigma plots
        r.gROOT.cd()
#         h=r.TH1F( openFile.Get('minLeptonD0Sig_d0NoCorrections_forFittingData_removedLifetimeCuts') )
        h=r.TH1F( openFile.Get('minLeptonD0Sig_d0NoCorrections_removedLifetimeCuts') )
        # Normal correction
#         hCorr=r.TH1F( openFile.Get('minLeptonD0Sig_d0Corrected_forFittingData_removedLifetimeCuts') )
        hCorr=r.TH1F( openFile.Get('minLeptonD0Sig_d0Corrected_removedLifetimeCuts') )

        # Different corrections for tracks with/without pixel hits
        hCorrPixel=r.TH1F( openFile.Get('minLeptonD0Sig_d0CorrectedPixel_removedLifetimeCuts') )
        # Corrections derived on bias in d0 (rather than d0/sigma)
        hCorrD0=r.TH1F( openFile.Get('minLeptonD0Sig_d0CorrectedIP_forFittingData_removedLifetimeCuts') )
        
        # TEMP - save corrected as root file
        if fileName.find('22Jan') >= 0 :
            outputTFile = r.TFile("BackgroundStudiesFiles/minLeptonD0Sig_d0Corrected_"+channel+"_Rereco.root","RECREATE");
            h.Write('Data')
            hCorr.Write('DataCorr')
            hCorrPixel.Write('DataCorrPixel')
            hCorrD0.Write('DataCorrD0')
            outputTFile.Close()
        else :
            outputTFile = r.TFile("BackgroundStudiesFiles/minLeptonD0Sig_d0Corrected_"+channel+"_Prompt.root","RECREATE");
            h.Write('Data')
            hCorr.Write('DataCorr')
            hCorrPixel.Write('DataCorrPixel')
            hCorrD0.Write('DataCorrD0')
            outputTFile.Close()
            pass
        
        h.SetMarkerColor(r.kRed)
        h.SetMarkerSize(0.8)
        h.SetMarkerStyle(26)
        h.SetLineStyle(2)
        h.SetLineColor(r.kRed)
        
        hCorr.SetMarkerColor(r.kBlue)
        hCorr.SetMarkerSize(0.8)
        hCorr.SetMarkerStyle(25)
        hCorr.SetLineStyle(2)
        hCorr.SetLineColor(r.kBlue)

        hCorrPixel.SetMarkerColor(r.kMagenta)
        hCorrPixel.SetMarkerSize(0.8)
        hCorrPixel.SetMarkerStyle(24)
        hCorrPixel.SetLineStyle(2)
        hCorrPixel.SetLineColor(r.kMagenta)

        hCorrD0.SetMarkerColor(r.kGreen)
        hCorrD0.SetMarkerSize(0.8)
        hCorrD0.SetMarkerStyle(28)
        hCorrD0.SetLineStyle(2)
        hCorrD0.SetLineColor(r.kGreen)
                        
        canvas=r.TCanvas("can")
        canvas.SetLogy()
        # up = r.TPad('u','u',0.01,0.25,0.99,0.99)
        # dp = r.TPad('d','d',0.01,0.01,0.99,0.25)
        # dp.Draw()
        # up.Draw()
        # up.cd()
        # up.SetLogy()
        h.Draw('PE')
        hCorr.Draw('SAME PE')
        hCorrPixel.Draw('SAME PE')
        hCorrD0.Draw('SAME PE')
        
        # Add a legend
        leg=r.TLegend(0.2,0.5,0.4,0.75)
        leg.SetFillStyle(0)
        leg.SetBorderSize(0)
        leg.AddEntry(h,'Original d0/#sigma_{d}','P')
        leg.AddEntry(hCorr,'Corrected d0/#sigma_{d}','P')
        leg.AddEntry(hCorrPixel,'Corrected d0/#sigma_{d} (pixel)','P')
        leg.AddEntry(hCorrD0,'Corrected d0/#sigma_{d} (d0)','P')
        leg.Draw()
        
        addCMSTitle(0.2,0.96)    
        addChannelLatex( channel, 0.2, 0.86  )
        addFileLabel(fileName,0.2,0.8 )

        canvas.Update()
        
        # Save canvas
        if fileName.find('22Jan') >= 0 :
            outputFileName='output/pdfOutput/correctedD0Sigma_'+channel+'_22JanRereco.pdf'
            pass
        else:
            outputFileName='output/pdfOutput/correctedD0Sigma_'+channel+'_PromptAndReco.pdf'
            pass
        print 'Saving as :',outputFileName
        canvas.Print(outputFileName)

        raw_input("Waiting.....")
        pass
    pass
