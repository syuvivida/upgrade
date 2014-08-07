#!/bin/tcsh

cd $1

setenv SCRAM_ARCH slc6_amd64_gcc472; eval `scramv1 runtime -csh`
set file="file:step1_"$2".root"
echo $file
set outfile="file:step2_"$2".root"
echo $outfile
set finalfile="file:step3_"$2".root"
echo $finalfile
set DQMfile="file:step3_DQM_"$2".root"
echo $DQMfile
set i=`date '+%s'`
echo $i
set a = `ksh 'echo $RANDOM'`
echo $a
@ i = $i / $a
echo $i
#@ i = ( $i / 1000 )
#echo $i
#cmsRun SingleMuPt10_cfi_GEN_SIM.py myOutputFile=$file seed=$i maxEvents=10
cmsRun step2_my140PU_DIGI_L1_DIGI2RAW.py inputFiles=$file myOutputFile=$outfile
#cmsRun step3_140PU_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM.py inputFiles=$outfile myOutputFile=$finalfile myDQMFile=$DQMfile

