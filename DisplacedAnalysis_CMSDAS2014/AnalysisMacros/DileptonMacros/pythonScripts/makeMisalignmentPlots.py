import os,sys
import ROOT as r
from commonMethods import *

rereco = True

# dataset = 'Mu'
# dateTag = '20130909'

dataset = 'Photon'
dateTag = '20130910'

channels=[
        '2eTrack',
#         '2muTrack'
          ]

runBatch = True

doProfiles=False
do2DProfile=True
doFractionMaps=False
do1DD0SigPlot=False
d0PlotsVsRun=False

splitIntoRunRanges = True # If you want to make plots for each run range separately (A, B, C, D)
if d0PlotsVsRun: splitIntoRunRanges = False # Don't want to split up for these plots

r.gROOT.Macro( 'tdrstyle.C' )
if runBatch:
    r.gROOT.SetBatch()
r.gStyle.SetPadTopMargin(0.1)
r.gStyle.SetPadLeftMargin(0.15)
r.gStyle.SetPadRightMargin(0.05)
r.gROOT.Macro( 'tdrstyle.C' )


files = {}
if not splitIntoRunRanges :
    if rereco :
        files['All'] = ["CombinedFiles/Data22Jan_combined_"]
        pass
    else :
        files['All'] = ["CombinedFiles/Data_combined_"]
        pass
    pass
else :
    if rereco :
        files['A'] = ["WeightedFiles/Data_"+dataset+"_Run2012A22Jan_analysis_"+dateTag+"_weighted_"]
        files['B'] = ["WeightedFiles/Data_"+dataset+"_Run2012B22Jan_analysis_"+dateTag+"_weighted_"]
        files['C'] = [ "WeightedFiles/Data_"+dataset+"_Run2012C22Jan_analysis_"+dateTag+"_weighted_"]
        files['D'] = ["WeightedFiles/Data_"+dataset+"_Run2012D22Jan_analysis_"+dateTag+"_weighted_"]
        pass
    else :
        files['A'] = ["WeightedFiles/Data_"+dataset+"_Run2012A1_analysis_"+dateTag+"_weighted_",
                      "WeightedFiles/Data_"+dataset+"_Run2012A2_analysis_"+dateTag+"_weighted_"]
        files['B'] = ["WeightedFiles/Data_"+dataset+"_Run2012B1_analysis_"+dateTag+"_weighted_"]
        files['C'] = [
                    "WeightedFiles/Data_"+dataset+"_Run2012C1_analysis_"+dateTag+"_weighted_",
                      "WeightedFiles/Data_"+dataset+"_Run2012C2_analysis_"+dateTag+"_weighted_"]
        files['D'] = ["WeightedFiles/Data_"+dataset+"_Run2012D1_analysis_"+dateTag+"_weighted_"]
        pass
    pass

vars = [
        'phi',
        'theta'
        ]


if do2DProfile or doProfiles or doFractionMaps or d0PlotsVsRun:
    for runRangeFiles in files:
        for channel in channels:
            
            openFiles = []
            for file in files[runRangeFiles]:
            
                fileName = file+channel+'.root'
                print "Processing ",fileName

                # Open files and store
                openFiles.append( r.TFile.Open(fileName) )
                
            if doProfiles:
                # First do 1D Profiles of mean vs phi or theta
                for var in vars :
                     
                    histsToCombine = []
                     
                    # Get histograms from all files and combine
                    for openFile in openFiles:
                        histsToCombine.append( r.TH2F( openFile.Get('singleLeptonD0Significance_vs_'+var)) )
                        pass
                    
                    if len(histsToCombine) is 1:
                        h = histsToCombine[0]
                        pass
                    else :
                        h = histsToCombine[0]
                        for hist in range(1,len(histsToCombine)):
                            h.Add( histsToCombine[hist])
                            pass
                     
                    # Make TProfile of histo
                    prof = r.TProfile( h.ProfileX('_pfx',1,-1,'s') )
                    
                    # Also plot RMS of entries
                    hRMS = r.TH1F('rms', 'rms', prof.GetNbinsX(), prof.GetBinLowEdge(0), prof.GetBinLowEdge(prof.GetNbinsX())+prof.GetBinWidth(prof.GetNbinsX()))
                    hRMS.SetMarkerStyle(20)
                    hRMS.SetMarkerColor(1)
                    hRMS.SetLineColor(1)
                    hRMS.GetYaxis().SetTitle('RMS')
    
                    for bin in range (1,prof.GetNbinsX()):
                        hRMS.SetBinContent(bin,prof.GetBinError(bin))
                        pass
                    
                    # Make canvas            
                    canvas=r.TCanvas("canvas","canvas",1000,500)
                    canvas.Divide(2)
                    canvas.cd(1)
                 
                    prof.SetMarkerStyle(20)
                    prof.SetMarkerColor(1)
                    prof.SetLineColor(1)
                     
                    prof.GetYaxis().SetTitle('d_{0}/#sigma_{d}')
                    if var is 'phi':
                        prof.GetXaxis().SetTitle('#phi')
                        hRMS.GetXaxis().SetTitle('#phi')
                    elif var is 'theta':
                        prof.GetXaxis().SetTitle('#theta')
                        hRMS.GetXaxis().SetTitle('#theta')
                        
                    prof.GetYaxis().SetLabelSize(0.035)
        #             prof.GetYaxis().SetRangeUser(-0.8,0.8)
                    if var is 'phi' :
                        prof.GetYaxis().SetRangeUser(-1.5,1.5)
                        hRMS.GetYaxis().SetRangeUser(0.5,1.5)
                        pass
                    elif var is 'theta' :
                        prof.GetYaxis().SetRangeUser(-1.5,1.5)
    #                     prof.GetYaxis().SetRangeUser(-0.2,0.2)
                        hRMS.GetYaxis().SetRangeUser(0.6,1.5)
                        pass
         
        #             prof.GetYaxis().SetTitleSize(0.035)
                    prof.GetYaxis().SetTitleOffset(2.0)
                    prof.Draw('P')
                     
                    addCMSTitle(0.2,0.96)    
                    addChannelLatex( channel )
                    addFileLabel(file)
                     
                    canvas.Update()
                    
                    canvas.cd(2)
                    hRMS.Draw('P')
                    canvas.Update()
                    outputFileName=''
                    if file.find('22Jan') >= 0 :
                        outputFileName='output/pdfOutput/singleLeptonD0Significance_vs_'+var+'_'+channel+'_22JanRereco_'+runRangeFiles+'.pdf'
                        pass
                    else:
                        outputFileName='output/pdfOutput/singleLeptonD0Significance_vs_'+var+'_'+channel+'_PromptAndReco_'+runRangeFiles+'.pdf'
                        pass
                    print 'Saving as :',outputFileName
                    canvas.Print(outputFileName)
                    pass
            
            if do2DProfile:
                set_palette()

                histNames = [
#                         'singleLeptonD0Significance_vs_phi_vs_theta',
#                         'singleLeptonD0SignificanceG2_vs_phi_vs_theta',
#                          'singleLeptonD0Significance_vs_phi_vs_theta_badRun',
#                          'singleLeptonD0Significance_vs_phi_vs_theta_noVertex',
#                          'singleLeptonD0Significance_vs_phi_vs_theta_badRun_noVertex',
#                         'singleLeptonD0Significance_vs_phi_vs_theta_pixel',
#                         'singleLeptonD0Significance_vs_phi_vs_theta_noPixel',
                        
                        'singleLeptonD0_vs_phi_vs_theta',
                        'singleLeptonD0_vs_phi_vs_theta_badRun',
                        'singleLeptonD0_vs_phi_vs_theta_noVertex',
                        'singleLeptonD0_vs_phi_vs_theta_badRun_noVertex',
                                                
                        'singleLeptonZ0_vs_phi_vs_theta',
                         'singleLeptonZ0_vs_phi_vs_theta_badRun',
                        'singleLeptonZ0_vs_phi_vs_theta_noVertex',
                         'singleLeptonZ0_vs_phi_vs_theta_badRun_noVertex',
                        'singleLeptonZ0_vs_phi_vs_theta_pixel',
                        'singleLeptonZ0_vs_phi_vs_theta_noPixel',
                         ]
                
                # Save resulting histograms in a root file as needed in DileptonAnalyzer.C
                if file.find('22Jan') >= 0 :
                    outputTFileName='misalignmentPlots/meanD0Significance_vs_phi_vs_theta_'+channel+'_22JanRereco_'+runRangeFiles+'.root'
                    pass
                else:
                    outputTFileName='misalignmentPlots/meanD0Significance_vs_phi_vs_theta_'+channel+'_PromptReco_'+runRangeFiles+'.root'
                    pass
                outputTFile = r.TFile(outputTFileName,'RECREATE')
                
                for histName in histNames:
                    # Now look at TH3F and get 2D profile of mean d0/sigma in phi-theta map

                    # Get histograms from all files and combine
                    histsToCombine = []
                    for openFile in openFiles:
                        histsToCombine.append( r.TH3F( openFile.Get(histName)) )
                        pass
                    
                    if len(histsToCombine) is 1:
                        h = histsToCombine[0]
                        pass
                    else :
                        h = histsToCombine[0]
                        for hist in range(1,len(histsToCombine)):
                            h.Add( histsToCombine[hist])
                            pass
                        
                    # Make 2D Profile
                    prof2D = r.TProfile2D( h.Project3DProfile('xy') )
    
                    # Make a copy of the profile and fill with errors
                    xAxis = prof2D.GetXaxis()
                    yAxis = prof2D.GetYaxis()
                    errorHist = r.TH2F( 'errorHist', 'errorHist', prof2D.GetNbinsX(), xAxis.GetBinLowEdge(1), xAxis.GetBinUpEdge(prof2D.GetNbinsX()), prof2D.GetNbinsY(), yAxis.GetBinLowEdge(1), yAxis.GetBinUpEdge(prof2D.GetNbinsY()) )
                    errorHist1D = r.TH1F( 'errorHist1D', 'errorHist1D', 30, 0, 3 )
                    errorHist1D.GetXaxis().SetTitle('Relative error')
                    errorHist1D.GetYaxis().SetTitle('Entries')
                    
                    for yBin in range (0, errorHist.GetNbinsY() ) :
                        for xBin in range (0, errorHist.GetNbinsX() ) :
                            binContent = abs(prof2D.GetBinContent( xBin, yBin ))
                            globalBin = prof2D.GetBin( xBin, yBin )
                            binEntries = prof2D.GetBinEntries( globalBin )
#                             if binEntries > 0 and binContent > 0.55:
#                                 print binEntries, binContent
#                                 print xAxis.GetBinCenter( xBin ), yAxis.GetBinCenter( yBin )
#                                 pass
#                             if binContent > 0.8 :
#                                 print 'Large bias'
#                                 print binContent,prof2D.GetBinError( xBin, yBin )
#                                 print xAxis.GetBinLowEdge( xBin ), yAxis.GetBinLowEdge( yBin )
#                                 print xAxis.GetBinUpEdge( xBin ), yAxis.GetBinUpEdge( yBin )
#                                 print xAxis.GetBinCenter( xBin ), yAxis.GetBinCenter( yBin )
                            binError = prof2D.GetBinError( xBin, yBin )
                            if binContent != 0.:
                                errorHist.SetBinContent( xBin, yBin, binError/binContent )
                                errorHist1D.Fill( binError/binContent )
                            
#                             if prof2D.GetBinContent( xBin, yBin ) != 0 :
#                                 print 'Relative error :',abs(binError) / prof2D.GetBinContent( xBin, yBin )
#                             if binError > prof2D.GetBinContent( xBin, yBin ) * 0.2 :
#                                 print 'Large relative error :',prof2D.GetBinContent( xBin, yBin ),'+/-',binError
                            pass
                        pass
                    
                    
                    # Make canvas and draw etc          
                    canvas=r.TCanvas("canvas")
                    canvas.SetTopMargin(0.1)
                    canvas.SetRightMargin(0.25)
                    prof2D.Draw("COLZ")
                    prof2D.GetXaxis().SetTitle("#theta")
                    prof2D.GetXaxis().SetRangeUser(0.1,3)
                    prof2D.GetYaxis().SetTitle("#phi")
                    prof2D.GetYaxis().SetRangeUser(-3.4,3.4)
#                     prof2D.GetZaxis().SetRangeUser(-1.4,0.63)
#                     prof2D.GetZaxis().SetTitle('Mean d_{0}/#sigma_{d}')
                    prof2D.GetZaxis().SetTitle('Mean d_{0} [cm]')
                    prof2D.GetZaxis().SetTitleOffset(1.2)
#                     errorHist.GetZaxis().SetRangeUser(0,1)

                    addCMSTitle()
#                     canvas.SetLogz()
#                     errorHist.Draw("COLZ")
#                     errorHist1D.Draw()
                    canvas.Update()
                    if not runBatch : raw_input()
                  
                    print 'Z min,max :',prof2D.GetMinimum(),prof2D.GetMaximum()
                    
                    if file.find('22Jan') >= 0 :
                        if channel is '2muTrack':
                            if histName is 'singleLeptonD0_vs_phi_vs_theta' :
                                canvas.SetRightMargin(0.23)
#                                 prof2D.GetZaxis().SetRangeUser(-0.00025,0.00025)
                            else:
#                                 prof2D.GetZaxis().SetRangeUser(-0.16,0.16)
                                pass
                            pass
                        else : 
#                             prof2D.GetZaxis().SetRangeUser(-2.0,2.0)
                            pass
                        outputFileName='output/pdfOutput/'+histName+'_22JanRereco_'+runRangeFiles+'_'+channel+'.pdf'
                        pass
                    else:
                        if channel is '2muTrack':
                            if histName is 'singleLeptonD0_vs_phi_vs_theta' :
#                                 prof2D.GetZaxis().SetRangeUser(-0.0012,0.0012)
                                canvas.SetRightMargin(0.23)
                                pass
                            else:
#                                     prof2D.GetZaxis().SetRangeUser(-0.9,0.9)
                                pass
                            pass
                        else : 
#                             prof2D.GetZaxis().SetRangeUser(-1.6,1.6)
                            pass
                        outputFileName='output/pdfOutput/'+histName+'_'+channel+'_PromptAndReco_'+runRangeFiles+'.pdf'
                        pass
                    print 'Saving as :',outputFileName
                    canvas.Print(outputFileName)
                  
                    # Now check cut version
    #                 prof2DCut.Draw("COLZ")
    #                 prof2DCut.GetXaxis().SetTitle("#theta")
    #                 prof2DCut.GetXaxis().SetRangeUser(0.2,3)
    #                 prof2DCut.GetYaxis().SetTitle("#phi")
    #                 prof2DCut.GetYaxis().SetRangeUser(-3.2,3.2)
                    canvas.Update()
#                     raw_input("Press Enter to continue...")
                    

                    outputTFile.cd()
                    prof2D.Write(histName)
                    if histName is 'singleLeptonD0Significance_vs_phi_vs_theta':
                        h.Write('OriginalHist')
                        canvas.Write()
                        pass
                    pass
                outputTFile.Close()

            if doFractionMaps:
                # Now do 2D maps in phi-theta of fraction of tracks with large d0/sigma
                set_palette()
                hAll = r.TH2F( openFile.Get('leptonD0SigFractionMap_all'))
                hPass = r.TH2F( openFile.Get('leptonD0SigFractionMap_pass'))
                hPass.Divide( hAll )
                hPass.GetZaxis().SetRangeUser(0,0.012)
                # Make canvas and draw etc          
                canvas=r.TCanvas("canvas")
                canvas.SetRightMargin(0.15)
#                 canvas.SetLogz()
                hPass.GetXaxis().SetTitle("#theta")
                hPass.GetYaxis().SetTitle("#phi")
                hPass.Draw("COLZ")
                
                if file.find('22Jan') >= 0 :
                    outputFileName='output/pdfOutput/singleLeptonD0SigFractionMap_'+channel+'_22JanRereco_'+runRangeFiles+'.pdf'
                    pass
                else:
                    outputFileName='output/pdfOutput/singleLeptonD0SigFractionMap_'+channel+'_PromptAndReco_'+runRangeFiles+'.pdf'
                    pass
                print 'Saving as :',outputFileName
                canvas.Print(outputFileName)
                if not runBatch : raw_input("Press Enter to continue...")
                pass
            
            if d0PlotsVsRun:
                # Should only be one file
                openFile=openFiles[0]
                # Do plots of bias vs run
                h = r.TH2F( openFile.Get('singleLeptonD0_vs_run'))
                # Make TProfile of histo
                prof = r.TProfile( h.ProfileX('_pfx',1,-1,'') )                
                prof.SetMarkerStyle(23)
                prof.SetMarkerColor(r.kBlue)
                prof.SetLineColor(r.kBlue)
#                 prof.GetYaxis().SetTitle('Mean d_{0}/#sigma_{d}')
                prof.GetYaxis().SetTitle('Mean d_{0}')
                prof.GetXaxis().SetTitle('Run')
                prof.GetYaxis().SetLabelSize(0.035)
                prof.GetYaxis().SetTitleOffset(2.0)
                prof.GetYaxis().SetRangeUser(-0.2,0.2)
                canvas=r.TCanvas("canvas","canvas",1000,500)
                prof.Draw('P')
                addCMSTitle(0.2,0.96)    
                addChannelLatex( channel )
                addFileLabel(file)
                canvas.Update()
                outputFileName=''
                if file.find('22Jan') >= 0 :
                    outputFileName='output/pdfOutput/singleLeptonD0Significance_vs_run_'+channel+'_22JanRereco_'+runRangeFiles+'.pdf'
                    pass
                else:
                    outputFileName='output/pdfOutput/singleLeptonD0Significance_vs_run_'+channel+'_PromptAndReco_'+runRangeFiles+'.pdf'
                    pass
                print 'Saving as :',outputFileName
                canvas.Print(outputFileName)
                if not runBatch : raw_input("Press Enter to continue...")
                
#                 # Plot of fraction of high d0/sigma leptons vs run
#                 hAll = r.TH1F( openFile.Get('leptonD0SigFraction_vs_run_all'))
#                 hPass = r.TH1F( openFile.Get('leptonD0SigFraction_vs_run_pass'))
#                 hPass.Divide( hAll )
#                 hPass.SetMarkerStyle(23)
#                 hPass.SetMarkerSize(0.8)
#                 hPass.SetMarkerColor(r.kRed)
#                 hPass.SetLineColor(r.kRed)
#                 hPass.Draw()
#                 addChannelLatex( channel )
#                 addFileLabel(file)
#                 canvas.Update()
#                 outputFileName=''
#                 if file.find('22Jan') >= 0 :
#                     outputFileName='output/pdfOutput/singleLeptonD0SignificanceFraction_vs_run_'+channel+'_22JanRereco.pdf'
#                     pass
#                 else:
#                     outputFileName='output/pdfOutput/singleLeptonD0SignificanceFraction_vs_run_'+channel+'_PromptAndReco.pdf'
#                     pass
#                 print 'Saving as :',outputFileName
#                 canvas.Print(outputFileName)
#                 raw_input("Press Enter to continue...")
                pass
                
                # Close files
                for openFile in openFiles:
                    openFile.Close()
                    pass
                pass
            pass
        pass


# # A little different as want to plot prompt and 22Jan rereco on same axes  
# if do1DD0SigPlot:
#     for channel in channels:
#         canvas=r.TCanvas("can")
#         canvas.SetLogy()
#         
#         leg=r.TLegend(0.2,0.7,0.4,0.9)
#         leg.SetFillStyle(0)
#         leg.SetBorderSize(0)
# 
#         # Open file
#         fileNamePrompt = files[0]+channel+'.root'
#         fileNameRereco = files[1]+channel+'.root'
#         print "Processing ",fileNamePrompt,fileNameRereco
#         
#         openFilePrompt=r.TFile.Open(fileNamePrompt)
#         openFileRereco=r.TFile.Open(fileNameRereco)
#        
#         # 1D plots of single lepton d0/sigma
#         r.gROOT.cd()
#         hPrompt=r.TH1F( openFilePrompt.Get('singleLeptonD0Significance') )
#         hRereco=r.TH1F( openFileRereco.Get('singleLeptonD0Significance') )
# 
#         hPrompt.GetXaxis().SetTitle('d_{0}/#sigma_{d}')
#         hPrompt.GetYaxis().SetTitle('Entries')
#         hPrompt.SetMarkerStyle(20)
#         hPrompt.SetMarkerSize(1)
#         hPrompt.SetMarkerColor(r.kRed)
#         hRereco.SetMarkerStyle(20)
#         hRereco.SetMarkerSize(1)
#         hRereco.SetMarkerColor(r.kBlue)
#         
#         leg.AddEntry(hPrompt,"Prompt Reco",'p')
#         leg.AddEntry(hRereco,"Rereco",'p')
#         
#         canvas.cd()
#         hPrompt.Draw('PE')
#         hRereco.Draw("SAME PE")
#         leg.Draw()
#         canvas.Update()
#         
#         outputFileName='output/pdfOutput/singleLeptonD0Significance_'+channel+'.pdf'
#         print 'Saving as :',outputFileName
#         canvas.Print(outputFileName)
#                     
#         #raw_input("Press Enter to continue...")
#         pass
#     pass

