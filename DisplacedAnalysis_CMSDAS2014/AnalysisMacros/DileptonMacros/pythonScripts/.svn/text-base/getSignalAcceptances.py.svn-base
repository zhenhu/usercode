
# File containing samples to run over and lifetime reweighting factors
from samplesConfig import *

# Common functions between all these scripts which parse text files
# to get signal efficiencies, acceptances etc.
from parseTextFilesTools import *

def storeResult( ctau, effic, error, efficienciesAndErrors):
    
    # Look to see if ctau value is already in output vector
    for entry in efficienciesAndErrors:
        if entry[0]==ctau or abs(entry[0]-ctau) < 0.1:
            # This ctau is already filled
            # Check if stat error is smaller
            if entry[2]>error:
                efficienciesAndErrors[efficienciesAndErrors.index(entry)]=[ctau,effic,error]
                pass
            return
        pass
    
    # Not seen this ctau value before
    efficienciesAndErrors.append([ctau,effic,error])
    return

def sortOutput(outputEfficienciesAndErrors):
    sorted(outputEfficienciesAndErrors, key=lambda x: x[0])
    pass


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
        for n in nExo:
#             print "--------------------------------------------------------------------------------------------------------------------"
#             print "Signal Acceptances for MH :",sInfo.MH," MX :",sInfo.MX," Central Ctau (mm) :",sInfo.ctauCentral," Channel :",channel," n : ",n
#             print "--------------------------------------------------------------------------------------------------------------------"
            
            # Get files
            if sInfo.signature=='H':
                allFile="EfficiencyFiles/rawFiles/effic_allExotics_"+channel+"_HTo2LongLivedTo4F_MH"+sInfo.MH+"_MFF"+sInfo.MX+"_CTau"+sInfo.ctauSmall+"To"+sInfo.ctauBig+"_"+n+"Decay.txt"
                outputFileName="SignalAcceptances/acceptance_"+channel+"_HTo2LongLivedTo4F_MH"+sInfo.MH+"_MFF"+sInfo.MX+"_CTau"+sInfo.ctauSmall+"To"+sInfo.ctauBig+"_"+n+".txt"
            elif sInfo.signature=='C':
                allFile="EfficiencyFiles/rawFiles/effic_allExotics_"+channel+"_Chi0ToNuLL_MSquark"+sInfo.MH+"_MChi"+sInfo.MX+"_"+n+"Decay.txt"
                outputFileName="SignalAcceptances/acceptance_"+channel+"_Chi0ToNuLL_MSquark"+sInfo.MH+"_Chi"+sInfo.MX+"_"+n+".txt"
            else:
                print "WARNING : Do not recognise this signature : ",sInfo.signature
                sys.exit(1)
    
            outputFile = open(outputFileName,'w')
            outputFile.write("PDG\tCtau\tAcceptance\tStatError\n")
            
            allExo=[]
            getEfficiencyExoticsFromFile( allFile, allExo )
            
            # Storage for efficiency and stat error at each ctau value
            # If a ctau value is already filled, it will be over written if the stat error of the new possible entry is smaller
            outputAcceptance=[]
            
            # Get efficiency for different lifetime exotics
            for pdg in signalPdg:
                
                # Avoid signal pdgs which don't occur in sample
                if sInfo.signature=='C' and pdg!='1000022' : continue
                elif sInfo.signature=='H' and pdg=='1000022' : continue
        
                # Cast ctau to float
                originalCtau=getOriginalCtau(sInfo,pdg)
                
                # And for different reweighted lifetimes
                for lifeTimeFact in lifeTimeFactors:
                    
                    newCtau=originalCtau*lifeTimeFact
                    
                    # Get sum of weights
                    fact=1
                    if n=="two":fact=2
    
                    decayProducts = ''
                    if channel == '2muTrack' :
                        decayProducts='13'
                    elif channel == '2eTrack' :
                        decayProducts='11'
                        
                    # Get sum of weights
                    # Note that denom needs to *2 in case of n = 2
                    swDenom=sumWeights( getEfficiencySumWeights( allExo, pdg, lifeTimeFact, originalCtau/10, decayProducts, fact, False, False, False ) )
                    swNum=sumWeights( getEfficiencySumWeights( allExo, pdg, lifeTimeFact, originalCtau/10, decayProducts, 1, False, True, False ) )
                    
                    # Get acceptance
                    acceptance = -1
                    statError = -1
                    relError = -1
                    if swDenom.s > 0 : 
                        acceptance=swNum.s/swDenom.s
                        # Get stat error
                        if swNum.s > 0:
                            statError = getStatError( swNum, swDenom)
                            relError = statError/acceptance
#                     print 'Ctau : ',newCtau,'factor :',lifeTimeFact
                    print 'Numerator : ',swNum.s,' +/- ',sqrt(swNum.s2)
                    print 'Denominator : ',swDenom.s,' +/- ',sqrt(swDenom.s2)
                    print 'Acceptance :',acceptance,'+/-',statError
                    outputFile.write("%s\t%.4g\t%.4f\t\t%.4f\n" % ( pdg, newCtau, acceptance, statError) )
                    
    #                storeResult(newCtau, effic, statError, outputEfficienciesAndErrors)
                pass
            outputFile.close()
            pass
        pass
    pass
