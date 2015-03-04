#!/bin/bash
scriptname=`basename $0`
EXPECTED_ARGS=2
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname script queue"
echo "Example: ./$scriptname runStep1.sh 2nd"
exit 1
fi

if [ ! -e $PWD/$1 ]; then
 echo $PWD/$1 " does not exist!"
exit 1
fi


if [ ! -e $PWD/step1.py ]; then
 echo $PWD/"step1.py does not exist!"
exit 1
fi

if [ ! -e $PWD/step2.py ]; then
 echo $PWD/"step2.py does not exist!"
exit 1
fi

if [ ! -e $PWD/step3.py ]; then
 echo $PWD/"step3.py does not exist!"
exit 1
fi

iteration=0
lastfile=20

while [ $iteration -lt $lastfile ]; 
do
  iteration=$(( iteration + 1 ))
  echo $iteration
  bsub -q $2 $PWD/$1 $PWD $iteration

done
