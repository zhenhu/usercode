#!/bin/bash                                          

function command(){                                  
    echo ">>>" $@
    eval $@
}

workDir=$PWD  
                                                                       
logDir=${workDir}"/BATCHJOBS/MC.h2/"
command "mkdir -p $logDir"

castorDirIn="/castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v9/Skims/UpsilonPt03A/"
castorDirOut="/castor/cern.ch/user/z/zhenhu/HeavyIons/Onia/MC/v9/Skims/UpsilonPt03A/"
command "rfmkdir -p  $castorDirOut"

inputfiles=""
j=0
jobNb=""

for files in `nsls $castorDirIn | grep onia2MuMuPAT`
do
	inputfiles="inputFiles=rfio:"$castorDirIn$files;
	echo $inputfiles;
	jobNb=${j};
	let j=${j}+1;
	name="OniaSkim_ReReco_03A_${jobNb}"
	outfilename="Histos_${name}.root"
	secoutfilename="DataSet_${name}.root"

#Start to write the script
	cat > job_${name}.sh << EOF
#!/bin/sh

function command(){                                  
     echo ">>>" \$@                                   
     eval \$@                                         
}

workDir=$PWD  
logDir="${logDir}"
castorDirOut="${castorDirOut}"


cd /afs/cern.ch/user/z/zhenhu/scratch0/HiTnp//CMSSW_3_9_9_patch1/src/
eval \`scramv1 runtime -sh\`
cd -
cp /afs/cern.ch/user/z/zhenhu/scratch0/HiTnp/CMSSW_3_9_9_patch1/src/HiAnalysis/HiOnia/test/hioniaanalyzer_cfg.py .
echo "before running cmsRun"
ls -l

command "cmsRun hioniaanalyzer_cfg.py ${inputfiles} outputFile=${outfilename} secondaryOutputFile=${secoutfilename} print 2>&1 | tee -a $logDir${name}.log"
echo "after running cmsRun"
ls -l
command "rfcp ${outfilename} $castorDirOut"
command "gzip -f $logDir${name}.log"
rm -f hioniaanalyzerpat_cfg.py

EOF

	chmod 755 job_${name}.sh
	
	bsub -q 2nw -J $name /afs/cern.ch/user/z/zhenhu/scratch0/HiTnp/CMSSW_3_9_9_patch1/src/HiAnalysis/HiOnia/test/job_${name}.sh


done


