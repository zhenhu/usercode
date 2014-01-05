import os,sys,ROOT
from ROOT import gROOT


# Different channels
channels=[
        '2eTrack',
        '2muTrack',
#          '2globalOrTrackerMu'
         ]

# Show different set of cuts if using collinearity method
useCollinearity=True

# Obtained in a convoluted way...
labelMap={
        'LeptonPt':'Lepton \pt',
        'CaloMatch':'Calo Matching',
        'PhotonMatch':'Photon Matching',
        'LeptonSCEt':'Photon \ET',
        'LeptonAbsEta':'Lepton $|\eta|$',
        'DileptonMass':'Dilepton Mass',
        'DileptonIsolation':'Lepton Relative Isolation',
        'DileptonOppositeCharge':'Opposite Charge',
        'DileptonB2BVeto':'cos(angle between leptons)',
        'DileptonDeltaR':'$\Delta$R',
        'DileptonTriggerMatch':'Trigger Match',
        'DileptonChi2':'Vertex $\chi^2$',
        'DileptonDeltaPhi':'$|\deltaPhi|$',
        'DileptonHitsBeforeVertex':'Hits Before the Vertex',
        'DileptonMissingHitsAfterVertex':'Missing Hits After Vertex',
        'LeptonD0Sig':'Lepton \dxysigma',
        'DileptonAbsLxySig':'OLD CUT',
        'PhotonID':'Photon ID requirements',
        'MuonID':'Muon ID requirements',
        'TrackQuality':'Track Quality Requirements',
        'SameSignD0':'Leptons \dxy have same sign'       
          }

vetoCutsMuon=[
'CaloMatch',
'PhotonMatch',
'LeptonSCEt',
'DileptonDeltaPhi',
'DileptonAbsLxySig',
'PhotonID',
'TrackQuality',
'MuonID'
              ]

vetoCutsElectron=[
'CaloMatch',
'DileptonB2BVeto',
'DileptonDeltaR',
'DileptonTriggerMatch',
'DileptonDeltaPhi',
'DileptonAbsLxySig',
'TrackQuality',
'MuonID',
'DileptonOppositeCharge'
              ]

vetoCutsData=[
'DileptonHitsBeforeVertex',
'DileptonMissingHitsAfterVertex',
'LeptonD0Sig',
# 'DileptonAbsLxySig',
              ]

if useCollinearity :
    vetoCutsMuon=[
    'CaloMatch',
    'PhotonMatch',
    'LeptonSCEt',
    'DileptonAbsLxySig',
    'PhotonID',
    'TrackQuality',
    'MuonID',
    'SameSignD0'
                  ]
    
    vetoCutsElectron=[
    'CaloMatch',
    'DileptonB2BVeto',
    'DileptonDeltaR',
    'DileptonTriggerMatch',
    'DileptonAbsLxySig',
    'TrackQuality',
    'MuonID',
    'SameSignD0',
    'DileptonOppositeCharge'
                  ]
    
    vetoCutsData=[
    'DileptonHitsBeforeVertex',
    'DileptonMissingHitsAfterVertex',
    'LeptonD0Sig',
    # 'DileptonAbsLxySig',
                  ]


for channel in channels:
        
    cutFlowMap = {
          'LABEL':[],
            'DATA':[],
            'BKG':[],
           'SIG1':[],
           'SIG2':[],
          }
    
    nCandsMap = {
          'LABEL':[],
           'DATA':[],
           'BKG':[],
           'SIG1':[],
           'SIG2':[],
          }
    
    nEventsInitial = {'SIG1' : 0, 'SIG2' : 0 }
    nExoticsInsideAcceptance = {'SIG1' : 0, 'SIG2' : 0 }
    nExoticsAfterTrigger = {'SIG1' : 0, 'SIG2' : 0 }
    nExoticsAfterPreselection =  {'SIG1' : 0, 'SIG2' : 0 }
    
    for key in cutFlowMap:
        if key=='LABEL':continue

        # Get input files
        inputFiles=[]
        if key=="DATA":
            inputFiles.append("CombinedFiles/Data22Jan_combined_"+channel+".root")
            pass
        elif key=="BKG":
            inputFiles.append("CombinedFiles/DYJets_combined_"+channel+".root")
            inputFiles.append("CombinedFiles/TTJets_combined_"+channel+".root")
            inputFiles.append("CombinedFiles/WW_combined_"+channel+".root")
            inputFiles.append("CombinedFiles/WJets_combined_"+channel+".root")
            inputFiles.append("CombinedFiles/ZZ_combined_"+channel+".root")
            inputFiles.append("CombinedFiles/WZ_combined_"+channel+".root")
            inputFiles.append("CombinedFiles/QCD_combined_"+channel+".root")
            pass
        elif key=="SIG1":
            inputFiles.append("CombinedFiles/HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500_combined_"+channel+".root")
            pass
        elif key=="SIG2":
            inputFiles.append("CombinedFiles/Chi0ToNuLL_MSquark1000_MChi148_combined_"+channel+".root")
            pass
        
        # Get all TProfiles
        allCutFlows=[]
        for file in inputFiles:
            histFile=ROOT.TFile.Open(file)
            
            if useCollinearity : cutFlow=histFile.Get("cutFlowColl")
            else : cutFlow=histFile.Get("cutFlow")
            gROOT.cd()
            allCutFlows.append(cutFlow.Clone())
            
            histFile.Close()
            pass

        
        # Get lumi
        # For scaling number of MC events
        lumi=1
        if key is not "DATA":
            lumiFile = "../LumiFiles/lumi_electron_22Jan.txt"
            if channel.find("mu")>=0 :
                lumiFile = "../LumiFiles/lumi_muon_22Jan.txt"
                pass
            # Extract lumi from file
            openFile=open(lumiFile,"r")
            lumi=float(openFile.readline().strip())
            openFile.close()
            pass
        

        
        # Add all cut flows together
        finalCutFlow=allCutFlows[0]
        if len(allCutFlows)>1:
            for index in range(1,len(allCutFlows)):
                finalCutFlow.Add(allCutFlows[index])
                pass
            pass
        
        
        # For signal MC, get preselection cut flow
        if key is 'SIG1' or key is 'SIG2' :
            histFile=ROOT.TFile.Open(file)
            if useCollinearity : cutFlow_pre = histFile.Get("cutFlowColl_preselection")
            nEventsInitial[key] = cutFlow_pre.GetBinContent(0)
            nExoticsInsideAcceptance[key] = cutFlow_pre.GetBinContent(1) * lumi / nEventsInitial[key]
            nExoticsAfterTrigger[key] = cutFlow_pre.GetBinContent(2) * lumi / nEventsInitial[key]
            nExoticsAfterPreselection[key] = cutFlow_pre.GetBinContent(3) * lumi / nEventsInitial[key]
            histFile.Close()
            pass
            
        # Output cut flow to screen (or to a txt file?)
        for bin in range(2,finalCutFlow.GetNbinsX()):
            if finalCutFlow.GetXaxis().GetBinLabel(bin) != "":
                binLabel=finalCutFlow.GetXaxis().GetBinLabel(bin)
                
                # Veto some cuts from appearing in cut flow
                if (channel=='2muTrack' or channel=='2globalOrTrackerMu') and binLabel in vetoCutsMuon:continue
                elif channel=='2eTrack' and binLabel in vetoCutsElectron:continue
                
                
                if key=="SIG1" : 
                    cutFlowMap['LABEL'].append(binLabel)
                    nCandsMap['LABEL'].append(binLabel)
                    pass
                
                if key.find('SIG') >= 0:
                    nCandsMap[key].append(finalCutFlow.GetBinContent(bin)*lumi/nEventsInitial[key])
                else:
                    nCandsMap[key].append(finalCutFlow.GetBinContent(bin)*lumi)
                
                if finalCutFlow.GetBinContent(bin-1)==0:
                    cutFlowMap[key].append(0.0)
                else :
                    cutFlowMap[key].append(finalCutFlow.GetBinContent(bin)/finalCutFlow.GetBinContent(bin-1)*100)
                pass
            pass
        pass
    
    # Now have all cut flows for this channel (data, bkg, sig) and label of each row
    print '=== Cut flow for channel',channel,'\n'
    print '=== For Signal MC, number exotics before preselection : ',nExoticsInsideAcceptance['SIG1'],nExoticsInsideAcceptance['SIG2']
    print '=== Rough efficiency : ',nCandsMap['SIG1'][-1]/nExoticsInsideAcceptance['SIG1'],nCandsMap['SIG2'][-1]/nExoticsInsideAcceptance['SIG2']

    trigEffic_SIG1 = nExoticsAfterTrigger['SIG1']/nExoticsInsideAcceptance['SIG1']*100
    trigNCands_SIG1 =nExoticsAfterTrigger['SIG1']
    preselectionEffic_SIG1 = nExoticsAfterPreselection['SIG1']/nExoticsAfterTrigger['SIG1']*100
    preselectionNCands_SIG1 = nExoticsAfterPreselection['SIG1']
    
    trigEffic_SIG2 = nExoticsAfterTrigger['SIG2']/nExoticsInsideAcceptance['SIG2']*100
    trigNCands_SIG2 =nExoticsAfterTrigger['SIG2']
    preselectionEffic_SIG2 = nExoticsAfterPreselection['SIG2']/nExoticsAfterTrigger['SIG2']*100
    preselectionNCands_SIG2 = nExoticsAfterPreselection['SIG2']
    
    print 'Trigger\t\t&\t-\t&\t-\t&\t-\t&\t-\t&\t%.1f\\%%\t&\t%.2e\t&\t%.1f\\%%\t&\t%.2e\t\\\\' % (trigEffic_SIG1,trigNCands_SIG1,trigEffic_SIG2,trigNCands_SIG2)
    print 'Preselection\t\t&\t-\t&\t-\t&\t-\t&\t-\t&\t%.1f\\%%\t&\t%.2e\t&\t%.1f\\%%\t&\t%.2e\t\\\\' % (preselectionEffic_SIG1,preselectionNCands_SIG1,preselectionEffic_SIG2,preselectionNCands_SIG2)
    
    for entry in cutFlowMap['LABEL']:
        index = cutFlowMap['LABEL'].index(entry)
        
        # Veto final data entries
        dataEntry='-'
        dataNcands='-'
        if entry not in vetoCutsData:
            dataEntry='%.1f'%(cutFlowMap['DATA'][index])
            dataNcands='%.2e'%(nCandsMap['DATA'][index])
            pass
        
#        print labelMap[entry],'\t\t&\t%s\\%%\t&\t%.1f\\%%\t&\t%.1f\\%%\t\\\\' % (dataEntry,cutFlowMap['BKG'][index],cutFlowMap['SIG'][index])
#        print labelMap[entry],'\t\t&\t%s\\%%\t&\t%.2e\\%%\t&\t%.2e\\%%\t\\\\' % (dataEntry,nCandsMap['BKG'][index],nCandsMap['SIG'][index])

        print labelMap[entry],'\t\t&\t%s\\%%\t&\t%s\t&\t%.1f\\%%\t&\t%.2e\t&\t%.1f\\%%\t&\t%.2e\t&\t%.1f\\%%\t&\t%.2e\t\\\\' % (dataEntry,dataNcands,cutFlowMap['BKG'][index],nCandsMap['BKG'][index],cutFlowMap['SIG1'][index],nCandsMap['SIG1'][index],cutFlowMap['SIG2'][index],nCandsMap['SIG2'][index])
#         print labelMap[entry],'\t\t&\t%.1f\\%%\t&\t%.2e\t\\\\' % (cutFlowMap['SIG1'][index],nCandsMap['SIG1'][index])

#         print labelMap[entry],'\t\t&\t%s\\%%\t&\t%s\t&\t%.1f\\%%\t&\t%.2e\t&\t%.1f\\%%\t&\t%.2e\t\\\\' % (dataEntry,dataNcands,-1,-1,cutFlowMap['SIG'][index],nCandsMap['SIG'][index])


        pass
    print '\n'
    
