#!/bin/bash

scriptname=`basename $0`
EXPECTED_ARGS=2
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname workdirectory rootFileIndex"
echo "Example: ./$scriptname $PWD 1"
exit 1
fi

tempfile=step3_$2.root
if [ ! -e $1/$tempfile ]; then
 echo $1/$tempfile " does not exist!"
exit 1
fi


cd $1

export SCRAM_ARCH=slc6_amd64_gcc472; eval `scramv1 runtime -sh`
finalfile="file:"$tempfile
echo $finalfile
outfile=charged_output_$2.root
echo $outfile
rm -rf $outfile
cmsRun ntuple.py inputFiles=$finalfile outputFile=$outfile

