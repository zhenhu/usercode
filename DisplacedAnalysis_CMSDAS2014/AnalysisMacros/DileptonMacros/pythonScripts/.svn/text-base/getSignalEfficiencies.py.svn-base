import sys

# File containing samples to run over and lifetime reweighting factors
from samplesConfig import *

# Common functions between all these scripts which parse text files
# to get signal efficiencies, acceptances etc.
from parseTextFilesTools import *

eventBasedEfficiencies=True

#===============================================================================
# START OF CODE
#===============================================================================

# Loop over different signal MC samples
for sample in massesAndCtau:
    # Get and store info on this sample
    sInfo = sampleInfo(sample)
    print '---> MH :',sInfo.MH,'MX :',sInfo.MX

    # Loop over different channels (e or mu)
    for channel in channels:
        # Loop over number of exotics in event decaying to channel (one or two)
        for n in nExo:

#             print "--------------------------------------------------------------------------------------------"
#             print "Efficiencies for MH :",sInfo.MH," MX :",sInfo.MX," Central Ctau (mm) :",sInfo.ctauCentral," Channel :",channel," nExo :",n
#             print "--------------------------------------------------------------------------------------------\n"
            
            # Get all and reco files
            # And output file name
            allFile=''
            recoFile=''
            recoFileNeg=''
            outputFileName=''

            methodSuffix = ''
            if useCollinearityMethod : methodSuffix = '_coll'
            
            selectionSuffix = ''
            if removedLifetimeSelection : selectionSuffix = '_removedLifetime'
            
            if sInfo.signature=='H':
                allFile='EfficiencyFiles/rawFiles/effic_allExotics_'+channel+'_HTo2LongLivedTo4F_MH'+sInfo.MH+'_MFF'+sInfo.MX+'_CTau'+sInfo.ctauSmall+'To'+sInfo.ctauBig+'_'+n+'Decay.txt'
                recoFile='EfficiencyFiles/rawFiles/effic_recoExotics'+methodSuffix+'_'+channel+'_HTo2LongLivedTo4F_MH'+sInfo.MH+'_MFF'+sInfo.MX+'_CTau'+sInfo.ctauSmall+'To'+sInfo.ctauBig+'_'+n+'Decay'+selectionSuffix+'.txt'
                recoFileNeg='EfficiencyFiles/rawFiles/effic_recoExotics'+methodSuffix+'_'+channel+'_HTo2LongLivedTo4F_MH'+sInfo.MH+'_MFF'+sInfo.MX+'_CTau'+sInfo.ctauSmall+'To'+sInfo.ctauBig+'_'+n+'Decay_negative.txt'
                outputFileName='EfficiencyFiles/efficiencies'+methodSuffix+'_HTo2LongLivedTo4F_'+sInfo.MH+'_'+sInfo.MX+'_'+channel+'_'+n+selectionSuffix+'.txt'
            elif sInfo.signature=='C':
                allFile='EfficiencyFiles/rawFiles/effic_allExotics_'+channel+'_Chi0ToNuLL_MSquark'+sInfo.MH+'_MChi'+sInfo.MX+'_'+n+'Decay.txt'
                recoFile='EfficiencyFiles/rawFiles/effic_recoExotics'+methodSuffix+'_'+channel+'_Chi0ToNuLL_MSquark'+sInfo.MH+'_MChi'+sInfo.MX+'_'+n+'Decay.txt'
                recoFileNeg='EfficiencyFiles/rawFiles/effic_recoExotics'+methodSuffix+'_'+channel+'_Chi0ToNuLL_MSquark'+sInfo.MH+'_MChi'+sInfo.MX+'_'+n+'Decay_negative.txt'
                outputFileName='EfficiencyFiles/efficiencies'+methodSuffix+'_Chi0ToNuLL_'+sInfo.MH+'_'+sInfo.MX+'_'+channel+'_'+n+'.txt'
            else:
                print "WARNING : Do not recognise this signature : ",sInfo.signature
                sys.exit(1)

            # Open output file for writing
            outputFile = open(outputFileName,'w')
            outputFile.write('PDG\tCtau\tCtauScaleFactor\tEfficiency\tStatError\tRelativeStatError\tPuUpEffic\tPuDownEffic\tTruncEffic\tStatError\tPuUpTrunEffic\tPuDownTruncEffic\tEfficiencyNeg\tStatError\tRelativeStatError\tTrunEfficNeg\tStatError\n')

            # Open and read files
            allExo=[]
            recoExo=[]
            recoExoNeg=[]
            getEfficiencyExoticsFromFile( allFile, allExo )
            getEfficiencyExoticsFromFile( recoFile, recoExo )
            getEfficiencyExoticsFromFile( recoFileNeg, recoExoNeg )
            
            # Get efficiency for different lifetime exotics
            for pdg in signalPdg:
                # Avoid signal pdgs which don't occur in sample
                if sInfo.signature=='C' and pdg!='1000022' : continue
                elif sInfo.signature=='H' and pdg=='1000022' : continue
                
                originalCtau=getOriginalCtau(sInfo,pdg)
            
#                 print "+++> New exotic pdgid"
#                 print "Signal pdg :",pdg
#                 print "Original ctau of exotic (mm) : ",originalCtau,"\n"
                
                # And for different reweighted lifetimes
                for lifeTimeFact in lifeTimeFactors:
                    
                    newCtau=originalCtau*lifeTimeFact
#                     print "---> Reweighting by factor : ",lifeTimeFact
#                    print "Target ctau of exotic (mm) : ",newCtau,"\n"

                    # Get sum of weights
                    # Note that denom needs to *2 in case of n = 2
                    # Only for candidate based efficiencies
                    fact=1
                    if n=="two" and not eventBasedEfficiencies:fact=2
                    
                    decayProducts = ''
                    if channel == '2muTrack' or channel == "2globalOrTrackerMu" :
                        decayProducts='13'
                    elif channel == '2eTrack' :
                        decayProducts='11'
                        
                    swDenom=sumWeights( getEfficiencySumWeights( allExo, pdg, lifeTimeFact, originalCtau/10, decayProducts, fact, False, False, False, eventBasedEfficiencies ) )
                    swNum=sumWeights( getEfficiencySumWeights( recoExo, pdg, lifeTimeFact, originalCtau/10, decayProducts, 1, False, False, False, eventBasedEfficiencies ) )
                    swNumNeg=sumWeights( getEfficiencySumWeights( recoExoNeg, pdg, lifeTimeFact, originalCtau/10, decayProducts, 1, False, False, False, eventBasedEfficiencies ) )

                    # Also get unreweighted denominator - shouldn't change after reweighting
#                     swDenomNominal=sumWeights( getEfficiencySumWeights( allExo, pdg, 1, originalCtau/10, decayProducts, fact, False, False, False ) )

                    # Get efficiency
                    effic = -1
                    efficTrunc = -1
                    efficNominalDenom = -1
                    efficPuUp = -1
                    efficPuDown = -1
                    efficTruncPuUp = -1
                    efficTruncPuDown = -1
                    statError = -1
                    relError = -1
                    statErrorTrunc = -1
                    relErrorTrunc = -1
                    statErrorNominalDenom = -1
                    relErrorNominalDenom = -1
                    efficNeg = -1
                    statErrorNeg = -1
                    relErrorNeg = -1
                    efficNegTrunc = -1
                    statErrorNegTrunc = -1
                    if swDenom.s > 0 : 
                        effic=swNum.s/swDenom.s
                        efficNeg = swNumNeg.s/swDenom.s
                        if swDenom.sTrunc > 0 :
                            efficTrunc=swNum.sTrunc/swDenom.sTrunc*swNum.scale
                            efficTruncNeg=swNumNeg.sTrunc/swDenom.sTrunc*swNumNeg.scale
                            pass
#                         if swDenomNominal.s > 0 :
#                             efficNominalDenom = swNum.s/swDenomNominal.s
#                             pass
                        efficPuDown=swNum.sPuDown/swDenom.sPuDown
                        efficTruncPuDown= swNum.sTruncPuDown/swDenom.sTruncPuDown*swNum.scale
                        efficPuUp=swNum.sPuUp/swDenom.sPuUp
                        efficTruncPuUp= swNum.sTruncPuUp/swDenom.sTruncPuUp*swNum.scale
                        # Get stat error
                        statError = getStatError( swNum, swDenom)
                        if effic > 0 : relError = statError/effic
                        if swDenom.sTrunc > 0 : statErrorTrunc = getStatError( swNum, swDenom, True )*swNum.scale
                        if efficTrunc > 0 : relErrorTrunc = statErrorTrunc/efficTrunc

                        statErrorNeg = getStatError( swNumNeg, swDenom )
                        if efficNeg > 0 :relErrorNeg = statErrorNeg/efficNeg
                        if swDenom.sTrunc > 0 : statErrorNegTrunc = getStatError( swNumNeg, swDenom, True )*swNumNeg.scale
                        pass
                
#                     # Output to screen for now
#                     print 'Ctau :',newCtau
#                     print 'Life time factor :',lifeTimeFact
#                     print 'Numerator : ',swNum.s,'+/-',sqrt(swNum.s2)
#                     print 'Denominator : ',swDenom.s,'+/-',sqrt(swDenom.s2)
#                     print "Central efficiency : %f +/- %f" % (effic,statError)
#                     print "Pu up efficiency : %f" %(efficPuUp)
#                     print "Pu down efficiency : %f" %(efficPuDown)
#                     print "Relative stat error : %f" % relError
#                     print '--- Trunc Effic ---'
#                     print "Nume trunc :",swNum.sTrunc,'+/-',sqrt(swNum.s2Trunc)
#                     print "Denom trunc :",swDenom.sTrunc,'+/-',sqrt(swDenom.s2Trunc)
#                     print 'Effic trunc:',efficTrunc,'+/-',statErrorTrunc
#                     print "Pu up efficiency : %f" %(efficTruncPuUp)
#                     print "Pu down efficiency : %f" %(efficTruncPuDown),'\n'
#                     print 'Relative stat error :',relErrorTrunc
#                     print 'Scale :',swNum.scale

#                     print '%f \pm %f' % (effic,statError)

                    # Simple checks
                    checkResults( effic )
                    
                    # Output to file
                    outputFile.write(pdg+'\t%.3g\t%.2g\t\t%.4g\t\t%.6f\t\t%.6f\t\t%.6f\t\t%.6f\t\t%.6f\t\t%.6f\t\t%.6f\t\t%.8f\t\t%.4g\t\t%.6f\t\t%.6f\t\t%.4g\t\t%.6f\n' % (newCtau,lifeTimeFact,effic,statError,relError,efficPuUp,efficPuDown,efficTrunc,statErrorTrunc,efficTruncPuUp,efficTruncPuDown,efficNeg,statErrorNeg,relErrorNeg,efficTruncNeg,statErrorNegTrunc) )
                    pass
                pass
            # Close output file
            outputFile.close()
        pass
    pass
