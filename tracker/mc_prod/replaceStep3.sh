#!/bin/bash
scriptname=`basename $0`
EXPECTED_ARGS=1
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname inputPython"
echo "Example: ./$scriptname step3_RAW2DIGI_L1Reco_RECO_VALIDATION_DQM.py"
exit 1
fi

outputfile=step3.py
rm -rf $outputfile
cat > $outputfile <<EOF
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')

options.register ('myOutputFile',
                    'file:step3.root',
                    VarParsing.multiplicity.singleton,
                    VarParsing.varType.string,
                    "outputFile")


options.register ('myDQMFile',
                    'file:step3_DQM.root',
                    VarParsing.multiplicity.singleton,
                    VarParsing.varType.string,
                    "outputFile")

options.parseArguments()

EOF

cat $1 >> $outputfile
sed -i -e 's/.*input.*/input = cms.untracked.int32(-1)/ ; s/fileNames = cms.untracked.vstring(\x27file:step2.root\x27)/fileNames = cms.untracked.vstring(options.inputFiles)/g;  s/fileName = cms.untracked.string(\x27file:step3.root\x27)/fileName = cms.untracked.string(options.myOutputFile)/g; s/fileName = cms.untracked.string(\x27file:step3_inDQM.root\x27)/fileName = cms.untracked.string(options.myDQMFile)/g' $outputfile 

