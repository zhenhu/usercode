#!/bin/env python

"""
...
"""

import os,sys

data = [
    "Data_Mu_Run2012A1",
    "Data_Mu_Run2012A2", 
    "Data_Mu_Run2012B1",
    "Data_Mu_Run2012C1", 
    "Data_Mu_Run2012C2",
    "Data_Mu_Run2012D1", 
    "Data_Photon_Run2012A1",
    "Data_Photon_Run2012A2", 
    "Data_Photon_Run2012B1",
    "Data_Photon_Run2012C1", 
    "Data_Photon_Run2012C2",
    "Data_Photon_Run2012D1", 
    ] 

data22Jan = [
    "Data_Mu_Run2012A22Jan",
    "Data_Mu_Run2012B22Jan",
    "Data_Mu_Run2012C22Jan", 
#     "Data_Mu_Run2012D22Jan", 
    "Data_Photon_Run2012A22Jan",
    "Data_Photon_Run2012B22Jan",
    "Data_Photon_Run2012C22Jan", 
#     "Data_Photon_Run2012D22Jan", 
    ] 

mc_signal = [
"HTo2LongLivedTo4F_MH1000_MFF150_CTau10To1000",
"HTo2LongLivedTo4F_MH1000_MFF20_CTau1p5To150",
"HTo2LongLivedTo4F_MH1000_MFF350_CTau35To3500",
"HTo2LongLivedTo4F_MH1000_MFF50_CTau4To400",
"HTo2LongLivedTo4F_MH120_MFF20_CTau13To1300",
"HTo2LongLivedTo4F_MH125_MFF50_CTau50To5000",
"HTo2LongLivedTo4F_MH125_MFF20_CTau13To1300",
"HTo2LongLivedTo4F_MH200_MFF20_CTau7To700",
"HTo2LongLivedTo4F_MH200_MFF50_CTau20To2000",
"HTo2LongLivedTo4F_MH400_MFF150_CTau40To4000",
"HTo2LongLivedTo4F_MH400_MFF20_CTau4To400",
"HTo2LongLivedTo4F_MH400_MFF50_CTau8To800",
 "Chi0ToNuLL_MSquark1000_MChi148",  
 "Chi0ToNuLL_MSquark1500_MChi494",
 "Chi0ToNuLL_MSquark120_MChi48",
 "Chi0ToNuLL_MSquark350_MChi148",
    ]

mc_vv = [
#   "TTJets_FullLept",
#   "WJetsToLNu", 
#   "WW", 
#   "WZ", 
#   "ZZ", 
   "DYJets10",
   "DYJets50",
   #"DisplacedE_50GeV_stdRECO", 
   #"DisplacedMu_50GeV_stdRECO", 
    ]

mc_qcd = [
         "QCDem20",
         "QCDem30",
         "QCDem80",
         "QCDem170",
         "QCDem250",
         "QCDem350" ,
         "QCDmu15", 
#         "QCDmu20", 
    ]

mc_benchmark = [
   # "DisplacedMu_50GeV_stdRECO",
   # "DisplacedE_50GeV_stdRECO"
    ]

mc_background = []
mc_background += mc_vv
mc_background += mc_qcd

sample_test = [ "DisplacedMu_50GeV_stdRECO", "Zmumu", "Data_Mu_Run2011A1", "Data_Photon_Run2011A1", "Signal_1000_350F"]

sample_list = []

nn = "enter one of:\n\tdata \n\tsignal \n\tbackground \n\tqcd \n\tvectorboson \n\tall \n\ttest\n\n and specify runmode" 
if (len(sys.argv)!=3 or sys.argv[2]=="CRAB") and not (sys.argv[2]=="CRAB" and len(sys.argv)==4):
    print nn
    sys.exit(1)

if sys.argv[1] == "all" :
    sample_list += data
    sample_list += mc_signal
    sample_list += mc_background
    sample_list += mc_benchmark
elif sys.argv[1] == "data" :
    sample_list += data
elif sys.argv[1] == "data22Jan" :
    sample_list += data22Jan
elif sys.argv[1] == "signal" :
    sample_list += mc_signal
elif sys.argv[1] == "background" :
    sample_list += mc_background
elif sys.argv[1] == "qcd" :
    sample_list += mc_qcd
elif sys.argv[1] == "vectorboson" :
    sample_list += mc_vv
elif sys.argv[1] == "test" :
    sample_list += sample_test
else :
    print "invalid input >>", sys.argv[1], ">> try again!"
    print nn
    sys.exit(1)

runmode=sys.argv[2]

print "processing:", sample_list

    
ldir = os.environ['LOCALRT'] + "/src/SampleFiles/Samples/python/"
sdir = os.environ['LOCALRT'] + "/src/TreeProducer/TreeProducer/test/"

for fn in sample_list :
    cmd = sdir + "run_treeProducer.py " + ldir + fn + "_cff.py " + runmode
    if sys.argv[2]=="CRAB" :
        cmd = cmd + " " + sys.argv[3]
    print cmd
    os.system(cmd)


print "Done submitting."

