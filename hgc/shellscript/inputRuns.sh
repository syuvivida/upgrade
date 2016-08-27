#!/bin/bash

EXPECTED_ARGS=1

if [ $# -ne $EXPECTED_ARGS ]
then
    echo "Usage: ./`basename $0` DirName"
    echo "Example: ./`basename $0` ../../data/..." 
    exit 1
fi

dirName=$1

ls -1 $dirName/*txt | awk '{print $1}' > temp.txt

lastfile=`cat temp.txt | wc -l`
echo "There are "$lastfile" input files"

iteration=0
rm -rf runs
while [ $iteration -lt $lastfile ]; 
do
  iteration=$(( iteration + 1 ))
  temp=(`head -n $iteration temp.txt  | tail -1`)
  test=${temp##*/}
  echo $test >> runs  
done

sed -i -e 's/.txt//g' -e 's/HGCRun_Output_000//g' runs