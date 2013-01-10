import os,sys,math
from ROOT import TH1F, TCanvas, TF1

# Class to hold info on the sample you are considering
class sampleInfo:
    def __init__(self, massesAndCtau):
        self.MH=str(massesAndCtau[0])
        self.MX=str(massesAndCtau[1])
        self.ctauCentral=str(massesAndCtau[2])
        self.ctauSmall=str(massesAndCtau[2]/10)
        self.ctauBig=str(massesAndCtau[2]*10)
        pass

# Class to hold info on each exotic
class exo:
    def __init__(self, weight, ctau1, pdg1, ctau2, pdg2 ):
        self.weight=weight
        self.ctau1=ctau1
        self.pdg1=pdg1
        self.ctau2=ctau2
        self.pdg2=pdg2
        pass
    pass

# Class to store info on sum of weights
class sumWeights:
    def __init__(self, s):
        self.s=s[0]
        self.s2=s[1]
        pass
    pass

# Method to extract exotics from text file
def getExoticsFromFile( fileName, exotics ):
    file=open(fileName,"r")
    for line in file.readlines():
        line=line.split()
        exotics.append( exo( float(line[0]), line[1], line[2], line[3], line[4] ) )
        pass
    file.close()
    pass

# Method to get sum of weights and sum of weights squared from list of exo
def getSumWeights( exotics, signalPdg="*", lifeTimeFact=1, originalCtau=0, fact=1, plot=False ):
    sumWeights=0
    sumWeights2=0
    firstEntry=True
    
    # Monitor average lifetime weight
    sum=0
    n=0
    maxLifetimeWeight=0;
    largeWeightExo=exotics[0]
    
#    # Plot ctau
##    can=TCanvas("can","can",700,800)
#    hist=TH1F("ctau","ctau",20,0,originalCtau*4)
#    hist.Sumw2()

    # Loop over exotics and sum weights
    for exotic in exotics:
        if ( signalPdg=="*" or signalPdg==exotic.pdg1 or signalPdg==exotic.pdg2 ):
            # Get lifetime weight
            lifeTimeWeight = getLifetimeWeight( lifeTimeFact,originalCtau,float(exotic.ctau1),float(exotic.ctau2))
            
            # For monitoring average lifetime weight
            sum += lifeTimeWeight
            n += 1
            
            if lifeTimeWeight > maxLifetimeWeight : 
                largeWeightExo=exotic
                maxLifetimeWeight = lifeTimeWeight

            # Sum weights and sum weights squared
            weightOfExo = exotic.weight * lifeTimeWeight*fact
            
#            hist.Fill(float(exotic.ctau1),weightOfExo)
#            hist.Fill(float(exotic.ctau2),weightOfExo)

            sumWeights += weightOfExo
            sumWeights2 += weightOfExo * weightOfExo
            pass
        pass
    
#    if plot:
#        # Extract new ctau from hist
#        hist.Fit("expo","QEI")
##        hist.Draw()
##        raw_input("Press Enter to continue...")
#        fit = TF1( hist.GetFunction("expo") )
#        slope=-1.0*fit.GetParameter(1)
#        ctau = 1/slope
#        integral = hist.Integral()
#
#        fit.Delete()
#        hist.Delete()
#        if ( abs( ( ctau - (originalCtau*lifeTimeFact) )/(originalCtau*lifeTimeFact) ) > 0.1 ) :
#            print "==============================="
#            print "WARNING IN LIFETIME REWEIGHTING"
#            print "Target ctau and measured ctau differ by more than 10%"
#            print "==============================="
#            print "Measured ctau :",ctau
#            print "Original ctau :",originalCtau
#            print "Lifetime fact :",lifeTimeFact
#            print "New ctau :",originalCtau*lifeTimeFact
#            print "==============================="
#            print "==============================="
#            pass
#        print "+++"
#        print "Info on lifetime reweighting"
#        print "Original ctau (cm) :",originalCtau
#        print "New ctau (cm) :",originalCtau*lifeTimeFact
#        print "Measured Ctau of sample (cm) :",1/slope
#        print "Average lifetime weight :",sum/n
#        print "Integral :",integral
#        print "Largest lifetime weight :",maxLifetimeWeight
#        print "Original weight :",largeWeightExo.weight
#        print "Ctau1 :",largeWeightExo.ctau1
#        print "Ctau2 :",largeWeightExo.ctau2
#        print "+++\n"
#    
#        if (sum/n>1.1 or sum/n<0.9):
#            print "==============================="
#            print "WARNING IN LIFETIME REWEIGHTING"
#            print "Large/Small average lifetime weight"
#            print "Average lifetime weight :",sum/n
#            print "==============================="
#            pass
#        pass
    return [sumWeights, sumWeights2 ]

# Method to get stat error from numerator and denominator sumWeights class
def getStatError( swNum, swDen ):
    statNum=math.sqrt(swNum.s2)/swNum.s
    statDen=math.sqrt(swDen.s2)/swDen.s
    
    eff=swNum.s/swDen.s
    
    return eff * math.sqrt( statNum*statNum + statDen*statDen )

# Returns lifetime weight given the original ctau and factor you want to reweight by
def getLifetimeWeight( factor, oldCtau, ctau1, ctau2 ):
    if factor==1.: return 1.
    return 1./factor * math.exp(ctau1*(factor-1.)/(factor*oldCtau)) * 1./factor * math.exp(ctau2*(factor-1.)/(factor*oldCtau))

# Different combination of channels, number of exotics, pdg is of exotics, factors to reweight lifetime by
massesAndCtau=[[1000,350,350],
               [1000,150,100],
               [1000,50,40],
#               [1000,20,15],
               [400,150,400],
               [400,50,80],
               [400,20,40],
               [200,50,200],
#               [200,20,70]
#               [125,50,500],
#               [120,50,500]
               ]

## ALL SAMPLES
channels=["2eTrack","2muTrack"]
nExo=["one","two"]
signalPdg=["6001113","6002113","6003113"]
lifeTimeFactors=[0.1,0.4,0.3,0.5,1.,2.,3.,4.,5.,10.]

## DEBUG
#channels=["2muTrack"]
#nExo=["two"]
#signalPdg=["6001113","6002113"]
#lifeTimeFactors=[0.5,1.,4.]

# Loop over different signal MC samples
for sample in massesAndCtau:
    # Get and store info on this sample
    sInfo = sampleInfo(sample)
    # Loop over different channels (e or mu)
    for channel in channels:
        # Loop over number of exotics in event decaying to channel (one or two)
        for n in nExo:

            # Open output file for this sample
            outputFile = open('EfficiencyFiles/efficiencies_'+sInfo.MH+'_'+sInfo.MX+'_'+channel+'_'+n+'.txt','w')
            
            print "--------------------------------------------------------------------------------------------"
            print "Efficiencies for MH :",sInfo.MH," MX :",sInfo.MX," Central Ctau (mm) :",sInfo.ctauCentral," Channel :",channel," nExo :",n
            print "--------------------------------------------------------------------------------------------\n"
            
            # Get all and reco files
            allFile="EfficiencyFiles/rawFiles/effic_allExotics_"+channel+"_MH"+sInfo.MH+"_MFF"+sInfo.MX+"_CTau"+sInfo.ctauSmall+"To"+sInfo.ctauBig+"_"+n+"Decay.txt"
            recoFile="EfficiencyFiles/rawFiles/effic_recoExotics_"+channel+"_MH"+sInfo.MH+"_MFF"+sInfo.MX+"_CTau"+sInfo.ctauSmall+"To"+sInfo.ctauBig+"_"+n+"Decay.txt"
            
            # Open and read files
            allExo=[]
            recoExo=[]
            getExoticsFromFile( allFile, allExo )
            getExoticsFromFile( recoFile, recoExo )
            
            # Get efficiency for different lifetime exotics
            for pdg in signalPdg:
                
                originalCtau="-1"
                if ( pdg=="6001113"): originalCtau=sInfo.ctauSmall
                elif ( pdg=="6002113"): originalCtau=sInfo.ctauCentral
                elif ( pdg=="6003113"): originalCtau=sInfo.ctauBig
                else : print "----> ERROR"
                
                # Cast ctau to float
                originalCtau=float(originalCtau)
                print "+++> New exotic pdgid"
                print "Signal pdg :",pdg
                print "Original ctau of exotic (mm) : ",originalCtau,"\n"
                
                # And for different reweighted lifetimes
                for lifeTimeFact in lifeTimeFactors:
                    
                    newCtau=originalCtau*lifeTimeFact
                    print "---> Reweighting by factor : ",lifeTimeFact
                    print "Target ctau of exotic (mm) : ",newCtau,"\n"

                    # Get sum of weights
                    # Note that denom needs to *2 in case of n = 2
                    fact=1
                    if n=="two":fact=2
                    swDenom=sumWeights( getSumWeights( allExo, pdg, lifeTimeFact, originalCtau/10, fact, True ) )
                    swNum=sumWeights( getSumWeights( recoExo, pdg, lifeTimeFact, originalCtau/10 ) )
                    
                    # Get efficiency
                    effic=swNum.s/swDenom.s
                    
                    # Get stat error
                    statError = getStatError( swNum, swDenom)
                    relError = statError/effic*100
                
                    # Output to screen for now
                    print "Central efficiency : %f" % (effic)
                    print "Stat error : %f" % (statError)
                    print "Relative stat error : %f" % relError,"\n"
                
                    # Output to file
                    outputFile.write(pdg+' %.5g %.4g %.4g %.4g\n' % (newCtau,effic,statError,relError) )
                    pass
                pass
            # Close output file
            outputFile.close()
        pass
    pass
