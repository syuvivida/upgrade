### Software set up

Go to a cms evironment enabled area(lxplus)

```
cmsrel CMSSW_8_0_1
cd CMSSW_8_0_1/src/
git clone git@github.com:CMS-HGCAL/TestBeam.git HGCal
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layers_8/hgc/plugin/Layer_Sum_Analyzer.cc -o HGCal/Reco/plugins/Layer_Sum_Analyzer.cc
```


### Compile 

scramv1 b -j 8

### To run the code

cd HGCalc
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layers_8/hgc/python/test_cfg.py -o test_cfg.py
cmsRun test_cfg.py nSpills=15 chainSequence=4 pedestalsHighGain=CondObjects/data/Ped_HighGain_L8.txt pedestalsLowGain=CondObjects/data/Ped_LowGain_L8.txt runNumber=1058 runType=HGCRun particle=electron energy=250GeV

### If you need to run many runs
Find out the beam type and beam energy your runs correspond to, for example, if it is an electrob beam with energy 250 GeV
create a directory under CMSSW_8_0_1/src

```
cd CMSSW_8_0_1/src/
mkdir -p data/electron/250GeV
cd data/electron/250GeV
ln -s xxxx .
```

where xxxx is the text files in the dataFolder "/afs/cern.ch/work/r/rslu/public/HGC_TB_data_Sep2016/"

Then you could run on all text files in the same directory via the following way

```
cd CMSSW_8_0_1/src/HGCal
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layers_8/hgc/python/runAll.py -o runAll.py
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layers_8/hgc/shellscript/inputRuns.sh -o inputRuns.sh
chmod 755 inputRuns.sh
python runAll.py electron 250GeV
```

### Meaning of each analyzer

3 different types of analyzers are present switched via test_cfg.py

1) process.hgcaltbrechitsplotter_highgain_new ---> Produces event displays for all events

2) process.hgcaltbrechitsplotter_highgain_correlation_cm  ---> Produces Reco histograms for each channel as well as a scatter plot of the Reco per channel

3) process.LayerSumAnalyzer ---> Produces Clusters of Recos(7cells, 19cells and all cells(full hexagons only))

Can activate all 3 at the same time.

For now, we only activate 3) to reduce the running time


