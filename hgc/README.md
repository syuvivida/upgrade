
## Instruction to perform 1-layer HGC test beam analysis
### Software set up

Go to a cms evironment enabled area(lxplus)

```
cmsrel CMSSW_8_0_1
cd CMSSW_8_0_1/src
cmsenv
git cms-init
git clone https://github.com/CMS-HGCAL/TestBeam HGCal/
cd HGCal
git checkout FNAL_TB_16Layers
git pull
rm -f RawToDigi/plugins/DigiPlotter_New.cc
cp ~rchatter/public/Ped_*Gain_L*.txt CondObjects/data
mkdir -p Reco/interface/
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layer_1/hgc/plugin/Layer_Sum_Analyzer.cc -o Reco/plugins/Layer_Sum_Analyzer.cc
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layer_1/hgc/interface/Clustering.h -o Reco/interface/Clustering.h
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layer_1/hgc/interface/ClusteringHelper.h -o Reco/interface/ClusteringHelper.h
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layer_1/hgc/interface/HGCalTBCluster2D.h -o DataFormats/interface/HGCalTBCluster2D.h 
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layer_1/hgc/interface/MyHGCalRecHit.h -o DataFormats/interface/MyHGCalRecHit.h
```

### Change default parameters

1) Open Reco/python/hgcaltbrechitproducer_cfi.py
Change the two pedestal files to Ped_LowGain_L1.txt and Ped_HighGain_L1.txt

2) Open Geometry/interface/HGCalTBGeometryParameters.h
---> Change MAXLAYERs to 1 and MAXSKIROCs to 2

3) Open Geometry/interface/HGCalTBSpillParameters.h
---> Change Spill to as many you wish to analyze(Number of events in the file should be < Events_Per_Spills*Number_Of_Spills)

 
### Compile 
cd ..
cmsenv
cd HGCal
scramv1 b clean
scram b -j32

### To run the job
```
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layer_1/hgc/python/test_cfg.py -o test_cfg.py
cmsRun test_cfg.py PARTICLE=electron ENERGY=250GeV RUNNUMBER=666
```
### If you want to run on many text files at the same time

```
cd CMSSW_8_0_1/src/
mkdir -p data/electron/250GeV
cd data/electron/250GeV
```
Now you could copy text files over to this area and go back to the original directory to launch your job

```
cd CMSSW_8_0_1/src/HGCal
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layer_1/hgc/python/runAll.py -o runAll.py
curl https://raw.githubusercontent.com/syuvivida/upgrade/HGCTB_Layer_1/hgc/shellscript/inputRuns.sh -o inputRuns.sh
chmod 755 inputRuns.sh
python runAll.py electron 250GeV
```

### Meaning of each analyzer

3 different types of analyzers are present switched via test_cfg.py

1) process.hgcaltbrechitsplotter_highgain_new ---> Produces event displays for all events

2) process.hgcaltbrechitsplotter_highgain_correlation_cm  ---> Produces Reco histograms for each channel as well as a scatter plot of the Reco per channel

3) process.LayerSumAnalyzer ---> Produces Clusters of Recos(7cells, 19cells and all cells(full hexagons only))

Can activate all 3 at the same time.

The output root file produced is HGC_Output_Reco.root
