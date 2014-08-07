#!/bin/tcsh

cd $1

setenv SCRAM_ARCH slc6_amd64_gcc472; eval `scramv1 runtime -csh`
set finalfile="file:step3_"$2".root"
echo $finalfile
set outfile="file:charged_output_"$2".root"
echo $outfile

cmsRun genOnly.py inputFiles=$finalfile outputFile=$outfile

