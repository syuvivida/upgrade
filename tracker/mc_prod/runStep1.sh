#!/bin/bash
scriptname=`basename $0`
EXPECTED_ARGS=2
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname workdirectory rootFileIndex"
echo "Example: ./$scriptname $PWD 1"
exit 1
fi

if [ ! -e $1/step1.py ]; then
 echo $1/"step1.py does not exist!"
exit 1
fi


cd $1

export SCRAM_ARCH=slc6_amd64_gcc472; eval `scramv1 runtime -sh`
file=step1_$2.root
echo $file
i=`date '+%s'`
echo $i
a=`ksh 'echo $RANDOM'`
echo $a
z=$((i / a))
echo $z
rm -rf $file
cmsRun step1.py myOutputFile=$file seed=$z maxEvents=2000
