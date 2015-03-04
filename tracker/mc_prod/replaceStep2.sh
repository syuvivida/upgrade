#!/bin/bash
scriptname=`basename $0`
EXPECTED_ARGS=1
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname inputPython"
echo "Example: ./$scriptname step2_DIGI_L1_DIGI2RAW.py"
exit 1
fi

outputfile=step2.py
rm -rf $outputfile
cat > $outputfile <<EOF
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')

options.register ('myOutputFile',
                    'file:step2.root',
                    VarParsing.multiplicity.singleton,
                    VarParsing.varType.string,
                    "outputFile")

options.parseArguments()
EOF

cat $1 >> $outputfile
sed -i -e 's/.*input.*/input = cms.untracked.int32(-1)/ ; s/fileNames = cms.untracked.vstring(\x27file:step1.root\x27)/fileNames = cms.untracked.vstring(options.inputFiles)/g;  s/fileName = cms.untracked.string(\x27file:step2.root\x27)/fileName = cms.untracked.string(options.myOutputFile)/g' $outputfile 

