import sys,os

LeptonType = sys.argv[1]

for mass in range(15,501,1):

	jobfilename = str(mass)+"job"
	job = open(jobfilename,"write")
	job.write("source /afs/cern.ch/user/p/plujan/public/displacedfermions/trunk/LimitsRooStats/setup.sh\n")
	job.write("python mainMass.py "+str(mass)+ " " + LeptonType)
	os.system("chmod +x "+jobfilename)
	os.system("bsub -q cmscaf1nh  "+jobfilename)

