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
            
            # Get acceptance files for this channel
            if sInfo.signature=='H':
                allFile="EfficiencyFiles/rawFiles/effic_allExotics_"+channel+"_HTo2LongLivedTo4F_MH"+sInfo.MH+"_MFF"+sInfo.MX+"_CTau"+sInfo.ctauSmall+"To"+sInfo.ctauBig+"_"+n+"Decay.txt"
            elif sInfo.signature=='C':
                allFile="EfficiencyFiles/rawFiles/effic_allExotics_"+channel+"_Chi0ToNuLL_MSquark"+sInfo.MH+"_MChi"+sInfo.MX+"_"+n+"Decay.txt"
            else:
                print "WARNING : Do not recognise this signature : ",sInfo.signature
                sys.exit(1)
                
            methodSuffix = ''
            if useCollinearityMethod : methodSuffix = '_coll'
            
            selectionSuffix = ''
            if removedLifetimeSelection : selectionSuffix = '_removedLifetime'
        
            if sInfo.signature=='H':
                recoFile='EfficiencyFiles/rawFiles/effic_recoExotics'+methodSuffix+'_'+channel+'_HTo2LongLivedTo4F_MH'+sInfo.MH+'_MFF'+sInfo.MX+'_CTau'+sInfo.ctauSmall+'To'+sInfo.ctauBig+'_'+n+'Decay'+selectionSuffix+'.txt'
                recoFileNeg='EfficiencyFiles/rawFiles/effic_recoExotics'+methodSuffix+'_'+channel+'_HTo2LongLivedTo4F_MH'+sInfo.MH+'_MFF'+sInfo.MX+'_CTau'+sInfo.ctauSmall+'To'+sInfo.ctauBig+'_'+n+'Decay_negative.txt'
                outputFileName='EfficiencyFiles/efficiencyOverAcceptance/efficienciesOverAcceptance'+methodSuffix+'_HTo2LongLivedTo4F_'+sInfo.MH+'_'+sInfo.MX+'_'+channel+'_'+n+selectionSuffix+'.txt'
            elif sInfo.signature=='C':
                recoFile='EfficiencyFiles/rawFiles/effic_recoExotics'+methodSuffix+'_'+channel+'_Chi0ToNuLL_MSquark'+sInfo.MH+'_MChi'+sInfo.MX+'_'+n+'Decay.txt'
                recoFileNeg='EfficiencyFiles/rawFiles/effic_recoExotics'+methodSuffix+'_'+channel+'_Chi0ToNuLL_MSquark'+sInfo.MH+'_MChi'+sInfo.MX+'_'+n+'Decay_negative.txt'
                outputFileName='EfficiencyFiles/efficiencyOverAcceptance/efficienciesOverAcceptance'+methodSuffix+'_Chi0ToNuLL_'+sInfo.MH+'_'+sInfo.MX+'_'+channel+'_'+n+'.txt'
            else:
                print "WARNING : Do not recognise this signature : ",sInfo.signature
                sys.exit(1)
                
            # Open output file for writing
            outputFile = open(outputFileName,'w')
            outputFile.write('PDG\tCtau\tCtauScaleFactor\tEfficiencyOverAcceptance\tStatError\tRelativeStatError\tPuUpEffic\tPuDownEffic\tTruncEffic\tStatError\tPuUpTruncEffic\tPuDownTrunEffic\tEfficiencyNeg\tStatError\tRelativeStatError\tTrunEfficNeg\tStatError\n')
            
            # Open and read numerator file
            recoExo=[]
            recoExoNeg=[]
            getEfficiencyExoticsFromFile( recoFile, recoExo )
            getEfficiencyExoticsFromFile( recoFileNeg, recoExoNeg )
            
            # Open and read denominator file
            allExo=[]
            getEfficiencyExoticsFromFile( allFile, allExo )

            # Work out what the decay products pdg id are
            decayProducts = ''
            if channel == '2muTrack' :
                decayProducts='13'
            elif channel == '2eTrack' :
                decayProducts='11'                
                        
            # Get efficiency and acceptance for different lifetime exotics
            for pdg in signalPdg:
                
                # Avoid signal pdgs which don't occur in sample
                if sInfo.signature=='C' and pdg!='1000022' : continue
                elif sInfo.signature=='H' and pdg=='1000022' : continue
                
                originalCtau=getOriginalCtau(sInfo,pdg)
                
                # And for different reweighted lifetimes
                for lifeTimeFact in lifeTimeFactors:
                    
                    newCtau=originalCtau*lifeTimeFact

                    # Get sum of weights
                    fact=1
                    if n=="two" and not eventBasedEfficiencies:fact=2

                    swDenom=sumWeights( getEfficiencySumWeights( allExo, pdg, lifeTimeFact, originalCtau/10, decayProducts, 1, False, True, False, eventBasedEfficiencies ) )
                    swNum=sumWeights( getEfficiencySumWeights( recoExo, pdg, lifeTimeFact, originalCtau/10, decayProducts, 1, False, True, False, eventBasedEfficiencies ) )
                    swNumNeg=sumWeights( getEfficiencySumWeights( recoExoNeg, pdg, lifeTimeFact, originalCtau/10, decayProducts, 1, False, True, False, eventBasedEfficiencies ) )
                    
                    # Get efficiency over acceptance
                    effic = -1
                    efficTrunc = -1
                    efficPuUp = -1
                    efficPuDown = -1
                    efficTruncPuUp = -1
                    efficTruncPuDown = -1
                    statError = -1
                    relError = -1
                    statErrorTrunc = -1
                    relErrorTrunc = -1
                    efficNeg = -1
                    statErrorNeg = -1
                    relErrorNeg = -1
                    efficNegTrunc = -1
                    statErrorNegTrunc = -1
                    if swDenom.s > 0 : 
                        effic=swNum.s/swDenom.s
                        efficPuUp = swNum.sPuUp/swDenom.s
                        efficPuDown = swNum.sPuDown/swDenom.s
                        efficNeg = swNumNeg.s/swDenom.s
                        if swDenom.sTrunc > 0 :
                            efficTrunc=swNum.sTrunc/swDenom.sTrunc
                            efficTruncNeg=swNumNeg.sTrunc/swDenom.sTrunc
                            pass
                        efficTruncPuDown= swNum.sTruncPuDown/swDenom.sTruncPuDown
                        efficTruncPuUp= swNum.sTruncPuUp/swDenom.sTruncPuUp
                        # Get stat error
                        statError = getStatError( swNum, swDenom)
                        if effic > 0 : relError = statError/effic
                        if swDenom.sTrunc > 0 : statErrorTrunc = getStatError( swNum, swDenom, True )
                        if efficTrunc > 0 : relErrorTrunc = statErrorTrunc/efficTrunc
                        statErrorNeg = getStatError( swNumNeg, swDenom )
                        if efficNeg > 0 : relErrorNeg = statErrorNeg/efficNeg
                        if swDenom.sTrunc > 0 : statErrorNegTrunc = getStatError( swNumNeg, swDenom, True )*swNumNeg.scale
#                     # Output to screen for now
#                     print 'Lifetime factor',lifeTimeFact,n,channel,pdg
#                     print 'Numerator : ',swNum.s,'+/-',sqrt(swNum.s2)
#                     print 'Denominator : ',swDenom.s,'+/-',sqrt(swDenom.s2)
#                     print "Central efficiency : %f +/- %f" % (effic,statError)
#                     print "Stat error : %f" % (statError)
#                     print "Relative stat error : %f" % relError
#                     print "Pu up efficiency : %f" %(efficPuUp)
#                     print "Pu down efficiency : %f" %(efficPuDown)
#                     print '--- Trunc Effic ---'
#                     print "Nume trunc :",swNum.sTrunc,'+/-',sqrt(swNum.s2Trunc)
#                     print "Denom trunc :",swDenom.sTrunc,'+/-',sqrt(swDenom.s2Trunc)
#                     print 'Effic :%f +/- %f' % (efficTrunc,statErrorTrunc)
#                     print 'Relative stat error :',relErrorTrunc
#                     print 'Scale :',swNum.scale,swDenom.scale,"\n"
#                     print "Pu up efficiency : %f" %(efficTruncPuUp)
#                     print "Pu down efficiency : %f" %(efficTruncPuDown)
#                     print

                    # Simple checks
                    checkResults( effic )

                    # Output to file
                    outputFile.write(pdg+'\t%.3g\t%.2g\t\t%.4g\t\t%.6f\t\t%.6f\t\t%.6f\t\t%.6f\t\t%.4f\t\t%.6f\t\t%.6f\t\t%.6f\t\t%.4g\t\t%.6f\t\t%.6f\t\t%.4g\t\t%.6f\n' % (newCtau,lifeTimeFact,effic,statError,relError,efficPuUp,efficPuDown,efficTrunc,statErrorTrunc,efficTruncPuUp,efficTruncPuDown,efficNeg,statErrorNeg,relErrorNeg,efficTruncNeg,statErrorNegTrunc) )