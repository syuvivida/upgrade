### Software set up

Go to a cms evironment enabled area(lxplus)

```
cmsrel CMSSW_8_0_1
cd CMSSW_8_0_1/src/
git clone git@github.com:CMS-HGCAL/TestBeam.git HGCal
```


### Compile 

scramv1 b -j 8

### To run the code

cd HGCalc

msRun test_cfg.py nSpills=15 chainSequence=4 pedestalsHighGain=CondObjects/data/Ped_HighGain_L8.txt pedestalsLowGain=CondObjects/data/Ped_LowGain_L8.txt runNumber=1058 runType=HGCRun particle=electron energy=250GeV

### Meaning of each analyzer

3 different types of analyzers are present switched via test_cfg.py

1) process.hgcaltbrechitsplotter_highgain_new ---> Produces event displays for all events

2) process.hgcaltbrechitsplotter_highgain_correlation_cm  ---> Produces Reco histograms for each channel as well as a scatter plot of the Reco per channel

3) process.LayerSumAnalyzer ---> Produces Clusters of Recos(7cells, 19cells and all cells(full hexagons only))

Can activate all 3 at the same time.

For now, we only activate 3) to reduce the running time


