from math import exp, fabs, sqrt

# Class to hold info on the sample you are considering
class sampleInfo:
    def __init__(self, massesAndCtau):
        self.signature=massesAndCtau[0]
        self.MH=str(massesAndCtau[1])
        self.MX=str(massesAndCtau[2])
        self.ctauCentral=str(massesAndCtau[3])
        self.ctauBig=str(massesAndCtau[3]*10)
        
        # Careful here as sometimes the small ctau is e.g. 1.5 which is 1p5 in the filename
        if ( float(massesAndCtau[3])/10 % 1 != 0 ) : 
            smallCtau = str( float(massesAndCtau[3])/10 )
            # Change decimal point to p
            smallCtau=smallCtau.replace( '.','p')
            self.ctauSmall=str(smallCtau)
            pass
        else:
            self.ctauSmall=str(massesAndCtau[3]/10)
        pass
    
    pass

# Class to hold info on exotic
class exo:
    def __init__(self, weight, ctau1, EoverPt1, pdg1, channel1, ctau2, EoverPt2, pdg2, channel2, run, lumi, event ):
        self.weight=float(weight)
        self.ctau1=float(ctau1)
        self.EoverPt1=float(EoverPt1)
        self.pdg1=pdg1
        self.channel1=channel1
        self.ctau2=float(ctau2)
        self.EoverPt2=float(EoverPt2)
        self.pdg2=pdg2
        self.channel2=channel2
        self.run=int(run)
        self.lumi=int(lumi)
        self.event=int(event)
        pass
    pass

# Class to hold info on exotics for signal efficiencies
class efficiencyExotic(exo) :
    def __init__(self, passTrigger, weight, weightPuDown, weightPuUp, withinAcceptance1, ctau1, EoverPt1, pdg1, channel1, withinAcceptance2, ctau2, EoverPt2, pdg2, channel2, run, lumi, event ):
        exo.__init__(self,weight, ctau1, EoverPt1, pdg1, channel1, ctau2, EoverPt2, pdg2, channel2, run, lumi, event)
        self.weightPuDown=weightPuDown
        self.weightPuUp=weightPuUp
        self.passTrigger=passTrigger
        
        self.withinAcceptance1=withinAcceptance1
        self.withinAcceptance2=withinAcceptance2
        pass
    pass



# Class to store info on sum of weights
class sumWeights:
    def __init__(self, s):
        if len(s)==2:
            self.s=s[0]
            self.s2=s[1]
            pass
        elif len(s)==9:
            self.s=s[0]
            self.sPuDown=s[1]
            self.sPuUp=s[2]
            self.s2=s[3]
            self.sTrunc=s[4]
            self.sTruncPuDown=s[5]
            self.sTruncPuUp=s[6]
            self.s2Trunc=s[7]
            self.scale=s[8]
            pass
        pass
    pass

def getOriginalCtau( sampleInfo, pdg ):
    originalCtau="-1"

    if sampleInfo.signature=='H':
        if ( pdg=="6001113"): 
            # Again careful as some values have 'p' in them
            if sampleInfo.ctauSmall.find('p') != -1:
                originalCtau=sampleInfo.ctauSmall.replace('p','.')
                pass
            else:
                originalCtau=sampleInfo.ctauSmall
                pass
        elif ( pdg=="6002113"): originalCtau=sampleInfo.ctauCentral
        elif ( pdg=="6003113"): originalCtau=sampleInfo.ctauBig
        else : print "----> ERROR"
    elif sampleInfo.signature=='C':
        originalCtau=sampleInfo.ctauCentral
        
    return float(originalCtau)

# Method to get stat error from numerator and denominator sumWeights class
def getStatError( swNum, swDen, trunc=False ):

    # Calculation from here http://root.cern.ch/root/htmldoc/src/TH1.cxx.html#2753
    # Based on how TH1::Divide calculates error when bin entries are weighted
    eff=swNum.s/swDen.s
    if trunc : eff = swNum.sTrunc/swDen.sTrunc
    
    if eff == 0: return 0
        
    w = eff
    e1 = sqrt(swNum.s2)
    e2 = sqrt(swDen.s2)
    b2 = swDen.s
    if trunc :
        e1 = sqrt(swNum.s2Trunc)
        e2 = sqrt(swDen.s2Trunc)
        b2 = swDen.sTrunc
    
    error2 = fabs( ( 1-2.*eff)*e1*e1 + eff*eff*e2*e2 ) / ( b2 * b2 ) 
    error = sqrt( error2 )

    return error

# Returns lifetime weight given the original ctau and factor you want to reweight by
def getLifetimeWeight( factor, oldCtau, ctau1 ):
    if factor==1.: return 1.
    return 1./factor * exp(ctau1*(factor-1.)/(factor*oldCtau))

# Method to extract acceptance conditions from file
def getAcceptanceConditions( fileName ):
    file=open(fileName,"r")
    acceptanceLines=[]
    # Read lines until you reach a blank line
    for line in file.readlines():
        if line=="\n":break
        else:acceptanceLines.append(line)
        pass
    file.close()
    return acceptanceLines

# Method to extract efficiency exotics from text file
def getEfficiencyExoticsFromFile( fileName, exotics ):
    file=open(fileName,"r")
    for line in file.readlines():
        line=line.split()
        exotics.append( efficiencyExotic( int(line[0]), float(line[1]), float(line[2]), float(line[3]), int(line[4]), line[5], line[6], line[7], line[8], int(line[9]), line[10], line[11], line[12], line[13], int(line[14]), int(line[15]), int(line[16]) ) )
        pass
    file.close()
    pass

def checkResults( eff ):
    if eff > 1 or eff < 0:
        print "WARNING WEIRD EFFICIENCY : ",eff
    pass

# Method to get sum of weights and sum of weights squared from list of exo
def getEfficiencySumWeights( exotics, signalPdg, lifeTimeFact, originalCtau, channel, fact, requirePassTrigger, requireWithinAcceptance, requireAtLeastOneInAcceptance, eventBasedEfficiencies ):

    if requireWithinAcceptance and fact != 1:
        print 'WARNING : In getEfficiencySumWeights.  You are requiring that the exotics are within acceptance and fact != 1.  You may get dodgy results.'
        pass
    sumWeights=0
    sumWeightsPuDown=0
    sumWeightsPuUp=0
    sumWeights2=0

    sumWeightsTrunc=0
    sumWeightsTruncPuUp=0
    sumWeightsTruncPuDown=0
    sumWeights2Trunc=0
    ctauCut = 6*originalCtau
    
    # Monitor average lifetime weight
    sum=0
    n=0
    maxLifetimeWeight=0;
    if len(exotics) > 0 : largeWeightExo=exotics[0]
    
    # Largest ctau
    maxCtau = 0
    
    # Fact passed in as argument may need to be changed
    finalFact = fact
    
    # Last run, lumi and event number
    lastRun = -1
    lastLumi = -1
    lastEvent = -1
    
    # Loop over exotics and sum weights
    for exotic in exotics:
        if ( signalPdg=="*" or signalPdg==exotic.pdg1 or signalPdg==exotic.pdg2 ):
            
            if requirePassTrigger and not exotic.passTrigger:
                    continue
                
#             Should remove this line
#             if requireAtLeastOneInAcceptance and not ( exotic.withinAcceptance1 or exotic.withinAcceptance2 ) : continue
            
            if requireWithinAcceptance:
                # Both exotics decayed to channel
                if exotic.channel1 == exotic.channel2 and exotic.channel1 == channel:
                    # If both exotics are within acceptance, need to double count entry
                    if exotic.withinAcceptance1 and exotic.withinAcceptance2:
                        finalFact = 1
                    else :
                        continue
                    pass
                else:
                    if exotic.channel1 == channel and exotic.withinAcceptance1 : finalFact = 1
                    elif exotic.channel2 == channel  and exotic.withinAcceptance2 : finalFact = 1
                    else : continue
                    pass
                pass
            
            # Now considering this exotic as input into sum of weights for denominator or numerator
            #  For event based efficiencies, only want to consider each event rather than each candidate
            if eventBasedEfficiencies:
                if exotic.run == lastRun and exotic.lumi == lastLumi and exotic.event == lastEvent:
                    # Already found one exotic reco'd in this event
#                     print 'Already found something in this event. Skipping.'
                    continue
                else :
                    # Take note of this event
                    lastRun = exotic.run
                    lastLumi = exotic.lumi
                    lastEvent = exotic.event
                    pass
                pass

            # Get lifetime weight
            lifeTimeWeight = 0
            exoticCtau1 = -1
            exoticCtau2 = -1

            if exotic.channel1 == exotic.channel2:
                # Reweight using both exotics
                lifeTimeWeight = getLifetimeWeight( lifeTimeFact,originalCtau,float(exotic.ctau1) ) * getLifetimeWeight( lifeTimeFact,originalCtau,float(exotic.ctau2) )
                if exotic.ctau1 > maxCtau : maxCtau = exotic.ctau1
                if exotic.ctau2 > maxCtau : maxCtau = exotic.ctau2
                exoticCtau1 = exotic.ctau1
                exoticCtau2 = exotic.ctau2
            else:
                # Only reweight using exotic that decayed to channel
                if exotic.channel1 == channel :
                    lifeTimeWeight = getLifetimeWeight( lifeTimeFact,originalCtau,float(exotic.ctau1) )
                    exoticCtau1 = exotic.ctau1
                    if exotic.ctau1 > maxCtau : maxCtau = exotic.ctau1
                    pass
                elif exotic.channel2 == channel :
                    lifeTimeWeight = getLifetimeWeight( lifeTimeFact,originalCtau,float(exotic.ctau2) )
                    exoticCtau2 = exotic.ctau2
                    if exotic.ctau2 > maxCtau : maxCtau = exotic.ctau2
                    pass

            # For monitoring average lifetime weight
            sum += lifeTimeWeight
            n += 1

            if lifeTimeWeight > maxLifetimeWeight : 
                largeWeightExo=exotic
                maxLifetimeWeight = lifeTimeWeight

            # Sum weights and sum weights squared
            weightOfExo = exotic.weight * lifeTimeWeight
            weightOfExoPuUp = exotic.weightPuUp * lifeTimeWeight
            weightOfExoPuDown = exotic.weightPuDown * lifeTimeWeight

            sumWeights += weightOfExo * finalFact
            sumWeightsPuDown += weightOfExoPuDown * finalFact
            sumWeightsPuUp += weightOfExoPuUp * finalFact
            sumWeights2 += weightOfExo * weightOfExo * finalFact * finalFact
            
            if exoticCtau1 < ctauCut and exoticCtau1 != -1:
                sumWeightsTrunc += weightOfExo * finalFact
                sumWeightsTruncPuUp += weightOfExoPuUp * finalFact
                sumWeightsTruncPuDown += weightOfExoPuDown * finalFact
                sumWeights2Trunc += weightOfExo * weightOfExo * finalFact * finalFact
#             elif exoticCtau1 != -1 : print "Chucking out this exotic"
#             elif exoticCtau1 != -1:
#                 # Above cut value.  What is Lxy?
#                 print "Cut values :",ctauCut,ctauCut / exotic.EoverPt1
#                 print "Ctau of exotic :",exoticCtau1
#                 print "Lxy of exotic :",exoticCtau1 / exotic.EoverPt1,'\n'
            if exoticCtau2 < ctauCut and exoticCtau2 != -1 :
                sumWeightsTrunc += weightOfExo * finalFact
                sumWeightsTruncPuUp += weightOfExoPuUp * finalFact
                sumWeightsTruncPuDown += weightOfExoPuDown * finalFact
                sumWeights2Trunc += weightOfExo * weightOfExo * finalFact * finalFact
#             elif exoticCtau2 != -1 : print "Chucking out this exotic"
#             elif exoticCtau2 != -1:
#                 # Above cut value.  What is Lxy?
#                 print "Cut values :",ctauCut,ctauCut / exotic.EoverPt2
#                 print "Ctau of exotic :",exoticCtau2
#                 print "Lxy of exotic :",exoticCtau2 / exotic.EoverPt2,'\n'
            pass
        pass

    #===========================================================================
    # These scales do nothing, as the same scale gets applied to numerator and denominator
    #===========================================================================
#     sumWeightsTrunc = sumWeightsTrunc * 1/(1-exp(-ctauCut/(originalCtau*lifeTimeFact))) / 1/(1-exp(-ctauCut/originalCtau))
#     sumWeights2Trunc = sumWeights2Trunc * 1/(1-exp(-ctauCut/(originalCtau*lifeTimeFact))) * 1/(1-exp(-ctauCut/(originalCtau*lifeTimeFact))) \
#                                         / 1/(1-exp(-ctauCut/originalCtau)) / 1/(1-exp(-ctauCut/originalCtau))

#     scale = 1
#     scale = (1-exp(-ctauCut/(originalCtau*lifeTimeFact ))) / ( 1-exp(-ctauCut/(originalCtau )) )
    scale = (1-exp(-ctauCut/(originalCtau*lifeTimeFact )))
#     scale = (1-exp(-ctauCut/(originalCtau )))
#     scale = (1-exp(-ctauCut/(originalCtau*lifeTimeFact ))) * ( 1-exp(-ctauCut/(originalCtau )) )


    return [sumWeights, sumWeightsPuDown, sumWeightsPuUp, sumWeights2, sumWeightsTrunc, sumWeightsTruncPuDown, sumWeightsTruncPuUp, sumWeights2Trunc, scale ]
