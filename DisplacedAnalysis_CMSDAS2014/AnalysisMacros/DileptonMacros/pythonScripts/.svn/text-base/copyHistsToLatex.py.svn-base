import os,sys

targetDir = '/home/ppd/bjo62667/DisplacedLeptons/Develop2012/Notes/notes/EXO-12-037/trunk/Figs2012/Selection/collinearity'
histoDir = '/home/ppd/bjo62667/DisplacedLeptons/Develop2012/CMSSW_5_3_8/src/AnalysisMacros/DileptonMacros/output/'

histoNames = [
            # Removed lifetime plots
            'Mass_removedLifetime_CollCuts',
            'Mass_removedLifetime_controlCollCuts',
            # Reco PV
            'nRecoPV_removedLifetimeCollCuts_withSyst',
            # d0/sigma before refit
            'minLeptonAbsD0Sig_PVnorefit_controlCollCuts',
            'minLeptonAbsD0Sig_deltaPhiG90_removedLifetimeCollCuts',
            # d0/sigma after refit
            'minLeptonAbsD0Sig_deltaPhiL90_removedLifetimeCollCuts',
            # d0/sigma for TOB/TEC tracks with no missing hits cut
            'minLeptonAbsD0Sig_deltaPhiG90_noMissingHits_algo10_removedLifetimeCollCuts',
               
            # Final Cuts
            'Mass_bestCand_finalCollCuts',
            'Lxy_bestCand_finalCollCuts',
              
            # nMinus1 Plots
            'nMinus1_cosine_looseCollCuts',
            'nMinus1_deltaR_looseCollCuts',
            'nMinus1_nHitsBeforeVertex_looseCollCuts',
            'nMinus1_nMissingHitsAfterVertex_looseCollCuts',
            'nMinus1_vertexChi2_looseCollCuts',
            'nMinus1_relIso_looseCollCuts',
            'deltaPhi_removedLifetimeCollCuts',
            
            'nMinus1_cosine_looseControlCollCuts',
            'nMinus1_deltaR_looseControlCollCuts',
            'nMinus1_nHitsBeforeVertex_looseControlCollCuts',
            'nMinus1_nMissingHitsAfterVertex_looseControlCollCuts',
            'nMinus1_vertexChi2_looseControlCollCuts',
            'nMinus1_relIso_looseControlCollCuts',
            'Mass_looseControlCollCuts',
               
            # Signal Efficiency Plots
            'efficiency_Vs_genLxy_one_coll',
              
            # Isolation vs PU
            'nMinus1_relIsolation_vsPU_finalCollCuts_genMatched_coll',
          
            # Trigger efficiency vs ctau
            'triggerEfficiencyVsCtau',
            
            # These tend to get over-written, so don't copy automatically!
#             # mean bias in theta,phi
#             'singleLeptonD0_vs_phi_vs_theta_noVertex_22JanRereco_D',
#             'singleLeptonZ0_vs_phi_vs_theta_noVertex_22JanRereco_D',
#             'singleLeptonD0_vs_run_22JanRereco',
#             'singleLeptonZ0_vs_run_22JanRereco',
#             'singleLeptonD0_vs_run_PromptReco',
#             'singleLeptonZ0_vs_run_PromptReco',
          ]

channels = [
            '2muTrack',
            '2eTrack'
            ]

formats = [
          'pdf'
          ]

# Check target dir exists
if not os.path.exists(targetDir):
    print 'ERROR : Target dir',targetDir,'doesn\'t exist'
    sys.exit(1)
    
for hist in histoNames:
    for channel in channels:
        for format in formats:
            
            originalDir=histoDir+'/'+format+'Output/'
            histoFile = originalDir+hist+'_'+channel+'.'+format
            command = 'cp '+histoFile+' '+targetDir+'/'+channel+'/'
            os.system(command)
            pass
        pass
    pass