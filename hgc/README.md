### Software set up

Go to a cms evironment enabled area(lxplus)

```
cmsrel CMSSW_8_0_1
cd CMSSW_8_0_1/src
git cms-init
git clone https://github.com/CMS-HGCAL/TestBeam HGCal/
cd HGCal
git checkout FNAL_TB_16Layers
git pull
rm -f RawToDigi/plugins/DigiPlotter_New.cc
cp ~rchatter/public/Ped_*Gain_L*.txt CondObjects/data
cp ~rchatter/public/Layer_Sum_Analyzer.cc Reco/plugins
cp ~rchatter/public/test_cfg.py .
```

### Change default parameters

1) Open Reco/python/hgcaltbrechitproducer_cfi.py
Change the two pedestal files to Ped_HighGain_L1.txt and Ped_LowGain_L1.txt

2) Open Geometry/interface/HGCalTBGeometryParameters.h
---> Change MAXLAYERs to 1 and MAXSKIROCs to 2

3) Open Geometry/interface/HGCalTBSpillParameters.h
---> Change Spill to as many you wish to analyze(Number of events in the file should be < Events_Per_Spills*Number_Of_Spills)

### Compile 

scram b -j32

### Meaning of each analyzer

3 different types of analyzers are present switched via test_cfg.py

1) process.hgcaltbrechitsplotter_highgain_new ---> Produces event displays for all events

2) process.hgcaltbrechitsplotter_highgain_correlation_cm  ---> Produces Reco histograms for each channel as well as a scatter plot of the Reco per channel

3) process.LayerSumAnalyzer ---> Produces Clusters of Recos(7cells, 19cells and all cells(full hexagons only))

Can activate all 3 at the same time.

The output root file produced is HGC_Output_Reco.root
