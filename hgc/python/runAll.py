
import sys


for arg in sys.argv: 
    print arg

import os

PARTICLE=sys.argv[1]
ENERGY=sys.argv[2]

inputDir="../../../data/"+PARTICLE+"/"+ENERGY
os.system("./inputRuns.sh "+inputDir)

os.system("awk '{print \"cmsRun test_cfg.py PARTICLE="+PARTICLE+" ENERGY="+ENERGY+" RUNNUMBER=\"$1}' runs | tcsh >& Log &")   
