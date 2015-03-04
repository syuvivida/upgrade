#!/bin/bash
scriptname=`basename $0`
EXPECTED_ARGS=1
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname script"
echo "Example: ./$scriptname runStep1.sh"
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
  bsub -q 2nd $PWD/$1 $PWD $iteration

done
