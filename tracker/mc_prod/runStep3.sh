#!/bin/bash
scriptname=`basename $0`
EXPECTED_ARGS=2
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname workdirectory rootFileIndex"
echo "Example: ./$scriptname $PWD 1"
exit 1
fi

if [ ! -e $1/step3.py ]; then
 echo $1/"step3.py does not exist!"
exit 1
fi

tempfile=step2_$2.root
if [ ! -e $1/$tempfile ]; then
 echo $1/$tempfile " does not exist!"
exit 1
fi

cd $1

export SCRAM_ARCH=slc6_amd64_gcc472; eval `scramv1 runtime -sh`
infile="file:"$tempfile
echo $infile
finalfile=step3_$2.root
echo $finalfile
DQMfile=step3_DQM_$2.root
echo $DQMfile

cmsRun step3.py inputFiles=$infile myOutputFile=$finalfile myDQMFile=$DQMfile

