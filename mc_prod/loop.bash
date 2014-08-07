#!/bin/bash


iteration=0
lastfile=20
while [ $iteration -lt $lastfile ]; 
do
  iteration=$(( iteration + 1 ))
  echo $iteration
  bsub -R "type=SLC6_64" -q 2nd $PWD/runJob.sh $PWD $iteration

#  $PWD/runJob.sh $PWD $iteration
done
