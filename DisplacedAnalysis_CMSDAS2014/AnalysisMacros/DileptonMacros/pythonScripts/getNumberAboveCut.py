# Give a d0/sigma histogram and will tell you how many candidates there are above possible cut values (in -ve tail)

import ROOT as r
from math import sqrt, fabs
from commonMethods import getLumi

rereco = False
# rereco = True

channel = '2muTrack'
# channel = '2eTrack'

latexTable = True

recoSuffix = ''
if rereco :
    recoSuffix = '22Jan'
    pass

maxBinValue = 3 # Use if blinded above some value of cut on one side of distribution
if channel is '2eTrack' :
    maxBinValue = 5
    pass

maxCutValue = 15


lumi=1
bkgMC=False

# Map of files and histograms you want to use as input for the table
# hNames = {
#           'minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts' : 'CombinedFiles/Data'+recoSuffix+'_combined_'+channel+'.root',
#           'minLeptonD0Sig_signWrtPerpDilepton_d0CorrectedRunDependentNoVertex_removedLifetimeCuts' : 'CombinedFiles/Data'+recoSuffix+'_combined_'+channel+'.root',
#           'minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts_tipLipCorrected' : 'CombinedFiles/Data'+recoSuffix+'_tipLipCorrected_combined_'+channel+'.root',
#           'minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts' : 'CombinedFiles/Data'+recoSuffix+'_combined_'+channel+'.root',
#           'minLeptonD0Sig_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts' : 'CombinedFiles/Data'+recoSuffix+'_combined_'+channel+'.root',
#           'minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts_tipLipCorrected' : 'CombinedFiles/Data'+recoSuffix+'_tipLipCorrected_combined_'+channel+'.root',
#           }
#         
# hNamesOrder = [
#                 'minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts',
#                 'minLeptonD0Sig_signWrtPerpDilepton_NoCorrections_removedLifetimeCuts_tipLipCorrected',
#                 'minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts',
#                 'minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts_tipLipCorrected',
#                ]
#  
# hNamesBlind = [
#                'minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts',
#                'minLeptonD0Sig_d0CorrectedRunDependentNoVertex_forFittingData_removedLifetimeCuts',
#                'minLeptonD0Sig_NoCorrections_forFittingData_removedLifetimeCuts_tipLipCorrected',
#                ]

#
# Collinearity Method
#
# Map of files and histograms you want to use as input for the table
hNames = {
          'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts' : 'CombinedFiles/Data'+recoSuffix+'_combined_'+channel+'.root',
          'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts_tipLipCorrected' : 'CombinedFiles/Data'+recoSuffix+'_tipLipCorrected_combined_'+channel+'.root',
          'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts' : 'CombinedFiles/Data'+recoSuffix+'_combined_'+channel+'.root',
          'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts_tipLipCorrected' : 'CombinedFiles/Data'+recoSuffix+'_tipLipCorrected_combined_'+channel+'.root',
          }
         
hNamesOrder = [
                'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts',
                'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiPlusMinus_removedLifetimeCollCuts_tipLipCorrected',
                'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts',
                'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts_tipLipCorrected',
               ]
  
hNamesBlind = [
               'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts',
               'minLeptonAbsD0Sig_bestCand_signedWrtDeltaPhiGL90_forFittingData_removedLifetimeCollCuts_tipLipCorrected',
               ]


# #
# # Tau Bkg MC
# #
# hNames = { 
#           'minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts_tau' : 'CombinedFiles/Tau_combined_'+channel+'.root',
#           'minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts_tau' : 'CombinedFiles/Tau_combined_'+channel+'.root',
#           }  
# hNamesOrder = [ 
# #                 'minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts_tau',
#                 'minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts_tau',
#                ]   
# hNamesBlind = [
#                ]

# hNames = { 
#           'minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts' : 'CombinedFiles/DYJets_combined_'+channel+'.root',
#           'minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts' : 'CombinedFiles/DYJets_combined_'+channel+'.root',
#           }  
# hNamesOrder = [ 
#                 'minLeptonD0Sig_signedWrtDeltaPhiPerp_removedLifetimeCollCuts',
#                 'minLeptonD0Sig_signedWrtDeltaPhi_removedLifetimeCollCuts',
#                ]   
# hNamesBlind = [
#                ]
#  
# bkgMC=True
# if bkgMC:
#     if channel is '2eTrack':
#         lumi = getLumi(False)
#     else :
#         lumi = getLumi(True)
#         print lumi
#     pass


outputTable = {}
outputTable[0] = 'Cut'

firstHist = True
lastHist = False

for hName in hNamesOrder :
    fName = hNames[hName]
    
    # Check if this is the last histogram
    # Useful for formatting table
    if hName is hNamesOrder[-1] :
        lastHist = True
        pass
    
    # Open file and get histogram
    file = r.TFile.Open(fName)
    
    h = file.Get(hName)
    
    # N bins along x
    nXbins = h.GetNbinsX()
    
    # x axis
    xaxis = h.GetXaxis()
    
    maxBinPos = nXbins
    maxBinNeg = 1
    blindHist = False
    lineOffset = 0
    if hName in hNamesBlind:
        blindHist = True
        if maxBinValue > 0 :
            maxBinPos = h.FindBin( maxBinValue )
#             maxBinNeg = h.FindBin( -maxBinValue )
#             lineOffset = maxBinNeg - 1
            pass
        pass
    
    # Bin containing zero
    binZero = h.FindBin( 0 )
    
#     print 'Cut\tNeg\tPos\tDiff'

    if latexTable :
        outputTable[0] = outputTable[0] + '\t&\tNeg\t&\tPos\t&\tDiff\t&\tSignificance\t'
        if lastHist :
            outputTable[0] = outputTable[0] + '\\\\'
        pass
    else :
        outputTable[0] = outputTable[0] + '\tNeg\tPos\tDiff\tSignificance'
        pass
    line = 1
    
    for bin in range (maxBinNeg,binZero) :
        cutValue = xaxis.GetBinUpEdge(bin)
        
        if fabs(cutValue)%1 != 0 : continue

        if fabs(cutValue) > maxCutValue : continue
        numberPassingNeg = h.Integral(maxBinNeg,bin)

        if bkgMC : numberPassingNeg = numberPassingNeg * lumi

        if blindHist and fabs(cutValue) > maxBinValue :
            numberPassingPos = -1
            difference =  -1
            pass
        else :
            numberPassingPos = h.Integral(nXbins-bin+1, maxBinPos)
            if bkgMC : numberPassingPos = numberPassingPos * lumi
            if not blindHist :
                difference =  numberPassingNeg - numberPassingPos 
                pass
            else :
                # If this is a blinded hist, we want the difference between +ve and -ve
                # sides to only consider the not blinded regions either side of the distribution
                maxBinNegTemp = h.FindBin( -maxBinValue )-1
                difference = h.Integral(maxBinNegTemp,bin) - numberPassingPos

        sig = 0
        if numberPassingNeg + numberPassingPos > 0 and numberPassingPos>=0 : sig = float(difference) / float(sqrt( fabs(numberPassingNeg) + fabs(numberPassingPos)))
        if firstHist :
            if latexTable :
                outputTable[line] = '%.3g\t&\t%.0f\t&\t%.0f\t&\t%.0f\t&\t%.1f' % ( fabs(cutValue), numberPassingNeg, numberPassingPos, difference, sig)
                pass
            else :
                outputTable[line] = '%.3g\t%.0f\t%.0f\t%.0f\t%.1f' % ( fabs(cutValue), numberPassingNeg, numberPassingPos, difference, sig )
                pass
            line = line+1
            pass
        else : 
            if latexTable :
                outputTable[line] = outputTable[line] + '\t&\t%.0f\t&\t%.0f\t&\t%.0f\t&\t%.1f' % ( numberPassingNeg, numberPassingPos, difference, sig )
                pass
            else :
                outputTable[line] = outputTable[line] + '\t%.0f\t%.0f\t%.0f\t%.2g' % ( numberPassingNeg, numberPassingPos, difference, sig )
                pass
            line = line + 1
        
        if lastHist :
#             print "Is last hist"
            if latexTable :
                outputTable[line-1] = outputTable[line-1] + '\t\\\\'
                pass
        pass
    
    # c1 = r.TCanvas()
    # h.Draw()
    # c1.SetLogy()
    # c1.Update()
    # raw_input('Waiting...')
    file.Close()
    
    firstHist=False
    pass

for line in outputTable :
    print outputTable[line]