def configureTipLipCorrections( process, dataSet, analysis ):
    if dataSet.find('22Jan')>=0 :
        if dataSet.find('Run2012A22Jan')>=0 :
            process.tiplipCorrectionFile = 'AnalysisMacros/DileptonMacros/misalignmentPlots/meanD0Significance_vs_phi_vs_theta_2muTrack_22JanRereco_A.root'
            process.badRangeMin = 999999
            process.badRangeMax = 999999
            pass
        elif dataSet.find('Run2012B22Jan') >= 0 :
            process.tiplipCorrectionFile = 'AnalysisMacros/DileptonMacros/misalignmentPlots/meanD0Significance_vs_phi_vs_theta_2muTrack_22JanRereco_B.root'
            process.badRangeMin = 194350
            process.badRangeMax = 196600
            pass
        elif dataSet.find('Run2012C22Jan')>=0 or dataSet.find('Run2012C2') >= 0:
            process.tiplipCorrectionFile = 'AnalysisMacros/DileptonMacros/misalignmentPlots/meanD0Significance_vs_phi_vs_theta_2muTrack_22JanRereco_C.root'
            process.badRangeMin = 200300
            process.badRangeMax = 203750
            pass
        elif dataSet.find('Run2012D22Jan') >= 0 :
            process.tiplipCorrectionFile = 'AnalysisMacros/DileptonMacros/misalignmentPlots/meanD0Significance_vs_phi_vs_theta_2muTrack_22JanRereco_D.root'
            process.badRangeMin = 207883
            process.badRangeMax = 208307
            pass
        pass
    else :
        if dataSet.find('Run2012A1')>=0 or dataSet.find('Run2012A2') >= 0:
            process.tiplipCorrectionFile = 'AnalysisMacros/DileptonMacros/misalignmentPlots/meanD0Significance_vs_phi_vs_theta_2muTrack_PromptReco_A.root'
            process.badRangeMin = 999999
            process.badRangeMax = 999999
            pass
        elif dataSet.find('Run2012B1') >= 0 :
            process.tiplipCorrectionFile = 'AnalysisMacros/DileptonMacros/misalignmentPlots/meanD0Significance_vs_phi_vs_theta_2muTrack_PromptReco_B.root'
            process.badRangeMin = 194350
            process.badRangeMax = 196600
            pass
        elif dataSet.find('Run2012C1')>=0 or dataSet.find('Run2012C2') >= 0:
            process.tiplipCorrectionFile = 'AnalysisMacros/DileptonMacros/misalignmentPlots/meanD0Significance_vs_phi_vs_theta_2muTrack_PromptReco_C.root'
            process.badRangeMin = 200300
            process.badRangeMax = 203750
            pass
        elif dataSet.find('Run2012D1') >= 0 :
            process.tiplipCorrectionFile = 'AnalysisMacros/DileptonMacros/misalignmentPlots/meanD0Significance_vs_phi_vs_theta_2muTrack_PromptReco_D.root'
            process.badRangeMin = 207883
            process.badRangeMax = 208307
            pass
        pass
    pass

