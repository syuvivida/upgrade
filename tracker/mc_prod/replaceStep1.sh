#!/bin/bash
scriptname=`basename $0`
EXPECTED_ARGS=1
if [ $# -ne $EXPECTED_ARGS ]
then
echo "Usage: $scriptname inputPython"
echo "Example: ./$scriptname FourMuPt_1_200_cfi_GEN_SIM.py"
exit 1
fi

outputfile=step1.py
rm -rf $outputfile
cat > $outputfile <<EOF
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')

options.register ('myOutputFile',
                    'file:step1.root',
                    VarParsing.multiplicity.singleton,
                    VarParsing.varType.string,
                    "outputFile")

options.register ('seed',
                    0,
                    VarParsing.multiplicity.singleton,
                    VarParsing.varType.int,
                    "seed for generator")
options.parseArguments()
EOF

cat $1 >> $outputfile
sed -i -e 's/.*input.*/input = cms.untracked.int32(options.maxEvents)/ ; s/fileName = cms.untracked.string(\x27file:step1.root\x27)/fileName = cms.untracked.string(options.myOutputFile)/g' $outputfile 
echo "process.RandomNumberGeneratorService.externalLHEProducer.initialSeed =options.seed" >> $outputfile