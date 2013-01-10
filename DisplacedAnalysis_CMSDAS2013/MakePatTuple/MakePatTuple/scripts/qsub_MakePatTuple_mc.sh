#!/bin/bash

eval `scram run -sh`

if [ $# != 3 ]; then
    echo "Usage: $0 fileTag nStart nEnd"
    exit 1
fi

package=MakePatTuple/MakePatTuple
base_dir=/uscmst1b_scratch/lpc1/3DayLifetime/${USER}/Local
condor_dir=${base_dir}/${package}/condor
log_dir=${base_dir}/${package}/log
output_dir=${base_dir}/${package}/output
fileTag=$1
jobNumBegin=$2
jobNumEnd=$3

# Check for the executable etc!
if [ ! -e ${condor_dir} ]; then
    echo "Warning! Could not find condor directory ${condor_dir} - creating."
    mkdir -p ${condor_dir}
    if [ ! -e ${condor_dir} ]; then
        echo "Failed to create directory, exiting script!"
        exit 1
    fi
fi
if [ ! -e ${log_dir} ]; then
    echo "Warning! Could not find log directory ${log_dir} - creating."
    mkdir -p ${log_dir}
    if [ ! -e ${log_dir} ]; then
        echo "Failed to create directory, exiting script!"
        exit 1
    fi
fi
if [ ! -e ${output_dir} ]; then
    echo "Warning! Could not find output directory ${output_dir} - creating."
    mkdir -p ${output_dir}
    if [ ! -e ${output_dir} ]; then
        echo "Failed to create directory, exiting script!"
        exit 1
    fi
fi

echo "Notifications will be sent to $USER@fnal.gov"

cd $output_dir

count=$jobNumBegin
while [ $count -le $jobNumEnd ]; do

   echo $count

   condor_file=MakePatTuple_${fileTag}_${count}_condor
   log_file_prefix=MakePatTuple_${fileTag}_${count}

   cat > ${condor_dir}/${condor_file} <<EOF
   universe = vanilla
   Executable = ${CMSSW_BASE}/src/${package}/scripts/qrun_MakePatTuple_mc.sh
   Requirements = Memory >= 199 &&OpSys == "LINUX"&& (Arch != "DUMMY" )
   ShouldTransferFiles = YES
   WhenToTransferOutput = ON_EXIT
   Output = ${log_dir}/${log_file_prefix}_\$(Cluster)_\$(Process).stdout
   Error = ${log_dir}/${log_file_prefix}_\$(Cluster)_\$(Process).stderr
   Log = ${log_dir}/${log_file_prefix}_\$(Cluster)_\$(Process).log
   notify_user = $USER@FNAL.GOV
   Arguments = $fileTag $count
   Queue 1
EOF

   condor_submit  ${condor_dir}/${condor_file}

   count=$[$count+1]
done

