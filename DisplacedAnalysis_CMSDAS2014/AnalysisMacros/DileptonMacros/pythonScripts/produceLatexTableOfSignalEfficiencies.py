import os

class effic:
    def __init__(self,entries,channel,n):
        self.ctau=float(entries[1])
        self.effic=float(entries[3])
        self.statErr=float(entries[4])
        self.channel=channel
        self.n=n
        pass
    
massesAndCtau=[
               ['H',1000,350,350],
                ['H',1000,150,100],
                ['H',1000,50,40],
                ['H',1000,20,15],
                ['H',400,150,400],
                ['H',400,50,80],
             ['H',400,20,40],
             ['H',200,50,200],
             ['H',200,20,70],
             ['H',125,50,500],
            ['H',125,20,130],
             
            # Chi0 samples
            ['C',1500,494,160],
            ['C',1000,148,60],
            ['C',350,148,173],
            ['C',120,48,165],
               ]

channels=[
          "2eTrack",
          "2muTrack",
#         "2globalOrTrackerMu"
          ]
nExo=["one","two"]

types=[
    'eff',
    'effOverAcc'
      ]

# If you are considering collinearity method or not
# Alternative is original d0 signing analysis
useCollinearityMethod = True

methodSuffix = ''
if useCollinearityMethod : methodSuffix = '_coll'

# Loop over masses and ctau
for type in types:
    if type == 'eff':
        print '\n\n========= TABLE FOR SIGNAL EFFICIENCIES =========\n\n'
    elif type == 'effOverAcc':
        print '\n\n========= TABLE FOR SIGNAL EFFICIENCIES OVER ACCEPTANCE =========\n\n'
    else :
        print 'WARNING : UNKOWN TYPE'
        
    for sample in massesAndCtau:
        signature=sample[0]
        mH=sample[1]
        mX=sample[2]
        ctau=sample[3]
        
        efficCtauSmall=[]
        efficCtauCentral=[]
        efficCtauBig=[]
        
        
        for channel in channels:
            for n in nExo:
        
                # Get lines from efficiency file
                efficFile='blah'
                if signature is 'H' :
                    if type == 'eff':
                        efficFile='EfficiencyFiles/efficiencies'+methodSuffix+'_HTo2LongLivedTo4F_'+str(mH)+'_'+str(mX)+'_'+channel+'_'+n+'.txt'
                    elif type == 'effOverAcc':
                        efficFile='EfficiencyFiles/efficiencyOverAcceptance/efficienciesOverAcceptance'+methodSuffix+'_HTo2LongLivedTo4F_'+str(mH)+'_'+str(mX)+'_'+channel+'_'+n+'.txt'
                        pass
                    pass
                elif signature is 'C' :
                    if type == 'eff':
                        efficFile='EfficiencyFiles/efficiencies'+methodSuffix+'_Chi0ToNuLL_'+str(mH)+'_'+str(mX)+'_'+channel+'_'+n+'.txt'
                    elif type == 'effOverAcc':
                        efficFile='EfficiencyFiles/efficiencyOverAcceptance/efficienciesOverAcceptance'+methodSuffix+'_Chi0ToNuLL_'+str(mH)+'_'+str(mX)+'_'+channel+'_'+n+'.txt'
                        pass
                    pass            
                openFile=open(efficFile,"r")
                lines=openFile.readlines()
                openFile.close()
                
                for line in lines:
                    entries=line.split()
                    if entries[2] == "1":
                        e=effic(entries,channel,n)
                        
                        if e.ctau == ctau: efficCtauCentral.append(e)
                        elif e.ctau == float(ctau)/10: efficCtauSmall.append(e)
                        elif e.ctau == ctau*10: efficCtauBig.append(e)
                        else :
                            print "PANIC!"
                            print e.ctau
                            print mH
                            print mX
                            print float(ctau)/10
                        pass
                    pass
                pass
            pass
        pass
        
        # Now have vectors full of efficiencies for each ctau of this sample
        # Print latex table to screen
        firstOfSample=True
        ctauToPrint=float(ctau/100.)
        
        if signature is 'H':
            ctaus = [efficCtauSmall,efficCtauCentral,efficCtauBig]
        elif signature is 'C':
            ctaus = [efficCtauCentral]
            ctauToPrint = ctauToPrint * 10

        for ctauAndEffics in ctaus:
            lineToScreen=""
            if firstOfSample:
                lineToScreen+="\t"+str(mH)+"\t&\t"+str(mX)+"\t&\t"+str(ctauToPrint)
                firstOfSample=False
                pass
            else:
                lineToScreen+="\t\t&\t\t&\t"+str(ctauToPrint)
                pass
            
            ctauToPrint = ctauToPrint*10
            
            for eff in ctauAndEffics:
                lineToScreen+="\t&\t%.2g"%(eff.effic)
                pass
            lineToScreen += "\t\\\\\n"
            print lineToScreen
            pass
        print "\hline"
                    
