#!/bin/bash
scriptname=`basename $0`
EXPECTED_ARGS=2
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname inputPython outputPython"
echo "Example: ./$scriptname FourMuPt_1_200_cfi_GEN_SIM.py ntuple.py"
exit 1
fi

rm -rf $2
sed '/Geometry/d' genOnly.py > $2
text=`grep -a Geometry $1`
echo "$text" >> $2