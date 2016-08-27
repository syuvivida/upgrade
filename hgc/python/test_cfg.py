import FWCore.ParameterSet.Config as cms


from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.register ('RUNNUMBER',
                  '395',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "RUNNUMBER")


options.register ('PARTICLE',
                  'electron',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "PARTICLE")


options.register ('ENERGY',
                  '20GeV',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "ENERGY")

options.parseArguments()


process = cms.Process("unpack")
process.load('HGCal.RawToDigi.hgcaltbdigis_cfi')
process.load('HGCal.RawToDigi.hgcaltbdigisplotter_cfi')
process.load('HGCal.Reco.hgcaltbrechitproducer_cfi')
process.load('HGCal.Reco.hgcaltbrechitplotter_cfi')



import os
   
directory=options.PARTICLE
if not os.path.exists(directory):
    os.makedirs(directory)

directory=options.PARTICLE+"/"+options.ENERGY
if not os.path.exists(directory):
    os.makedirs(directory)


process.source = cms.Source("HGCalTBTextSource",
                            run=cms.untracked.int32(1),####provide file name below
                            fileNames=cms.untracked.vstring(
        "file:/afs/cern.ch/work/s/syu/hgcal/data/"+options.PARTICLE+"/"+options.ENERGY+"/HGCRun_Output_000"+options.RUNNUMBER+".txt") 



##
# here a vector is provided, but in the .cc only the first one is used TO BE FIXED
#                            fileNames=cms.untracked.vstring("file:/afs/cern.ch/work/r/rslu/public/HGC_TB_data_Aug2016/PED_Output_000111.txt")
)

process.dumpRaw = cms.EDAnalyzer("DumpFEDRawDataProduct",
                              dumpPayload=cms.untracked.bool(True))

process.dumpDigi = cms.EDAnalyzer("HGCalDigiDump")


process.output = cms.OutputModule("PoolOutputModule",
			fileName = cms.untracked.string("output_"+options.RUNNUMBER+".root")
                                  )

#process.TFileService = cms.Service("TFileService", fileName = cms.string("HGC_Output_Cluster_"+RUNNUMBER+".root")) ### Analyzed output file with histograms
#process.TFileService = cms.Service("TFileService", fileName = cms.string("HGC_Output_Reco_352.root")) ### Analyzed output file with histograms
process.TFileService = cms.Service("TFileService", fileName = cms.string(directory+"/"+options.PARTICLE+options.ENERGY+"_HGC_Output_EventDisplay_"+options.RUNNUMBER+".root")) ### Analyzed output file with histograms

process.LayerSumAnalyzer.particleType = cms.string(options.PARTICLE)

########Activate this to produce event displays#########################################
#process.p =cms.Path(process.hgcaltbdigis*process.hgcaltbrechits*process.hgcaltbrechitsplotter_highgain_new)

################Not needed for DQM purposes, produces digi histograms for each channel, and the pedestal txt file needed for Digi->Reco
#process.p =cms.Path(process.hgcaltbdigis*process.hgcaltbdigisplotter)

################Produces Reco histograms for each channel as well as a scatter plot of the Reco per channel#############
#process.p =cms.Path(process.hgcaltbdigis*process.hgcaltbrechits*process.hgcaltbrechitsplotter_highgain_correlation_cm)

#################Produces Clusters of Recos(7cells, 19cells and all cells(full hexagons only))################
process.p =cms.Path(process.hgcaltbdigis*process.hgcaltbrechits*process.LayerSumAnalyzer)


#process.end = cms.EndPath(process.output)
