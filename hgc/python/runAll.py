
import sys


for arg in sys.argv: 
    print arg

import os

PARTICLE=sys.argv[1]
ENERGY=sys.argv[2]

inputDir="../../../data/"+PARTICLE+"/"+ENERGY
os.system("./inputRuns.sh "+inputDir)

name = "awk '{print \"cmsRun test_cfg.py nSpills=15 chainSequence=4 pedestalsHighGain=CondObjects/data/Ped_HighGain_L8.txt pedestalsLowGain=CondObjects/data/Ped_LowGain_L8.txt runType=HGCRun particle="+PARTICLE+" energy="+ENERGY+" runNumber=\"$1}' runs | tcsh >& Log &"
os.system(name)   

