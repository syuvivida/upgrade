#!/bin/bash
scriptname=`basename $0`
EXPECTED_ARGS=1
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname inputPython"
echo "Example: ./$scriptname FourMuPt_1_200_cfi_GEN_SIM.py"
exit 1
fi

file=ntuple.py
rm -rf $file
sed '/Geometry/d' genOnly.py > $file
text=`grep -a Geometry $1`
echo "$text" >> $file