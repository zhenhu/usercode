sampleDataSet = '/MuHad/Run2012B-22Jan2013-v1/AOD'
sampleNumEvents = 14148791 # according to DBS, as of 12 April 2013

# global tag needs to be chosen to match release, trigger menu and alignment conditions.
# see https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
sampleGlobalTag = 'FT_R_53_V18::All'
sampleHLTProcess = '*'

# data quality run/lumi section selection
sampleJSON = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Reprocessing/Cert_190456-203742_8TeV_22Jan2013ReReco_Collisions12_JSON.txt"

# restrict run range (mainly to get a sample with consistent trigger configuration)
sampleRunRange = [193833-196531]

# use checkAllFilesOpened whenever possible, and noDuplicateCheck when necessary
sampleDuplicateCheckMode = "checkAllFilesOpened"

# "DATA" or "MC"
sampleType = "DATA"

sampleRelease = "CMSSW_5_3_7_patch5" # original (i.e. RECO file) release,
                              # not the one we plan to process them with
                              
sampleProcessRelease = "CMSSW_5_3_8" # release used to create new files with

