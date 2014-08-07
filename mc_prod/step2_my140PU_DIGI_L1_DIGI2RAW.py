 # Auto generated configuration file
# using: 
# Revision: 1.20 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions DES23_62_V1::All -n 10 --eventcontent FEVTDEBUGHLT -s DIGI:pdigi_valid,L1,DIGI2RAW --datatier GEN-SIM-DIGI-RAW --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2023Muon --geometry Extended2023Muon,Extended2023MuonReco --magField 38T_PostLS1 --filein file:step1.root --fileout file:step2.root --no_exec --pileup AVE_140_BX_25ns --pileup_input dbs:/MinBias_TuneZ2star_14TeV-pythia6/Muon2023Upg14-DES23_62_V1-v1/GEN-SIM --python_filename=test.py
import FWCore.ParameterSet.Config as cms

process = cms.Process('DIGI2RAW')
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')

options.register ('myOutputFile',
                    'file:step1.root',
                    VarParsing.multiplicity.singleton,
                    VarParsing.varType.string,
                    "outputFile")

options.parseArguments()



# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mix_POISSON_average_cfi')
process.load('Configuration.Geometry.GeometryExtended2023MuonReco_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(options.inputFiles)
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.20 $'),
    annotation = cms.untracked.string('step2 nevts:10'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    fileName = cms.untracked.string(options.myOutputFile),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW')
    )
)

# Additional output definition

# Other statements
process.mix.input.nbPileupEvents.averageNumber = cms.double(140.000000)
process.mix.bunchspace = cms.int32(25)
process.mix.minBunch = cms.int32(-12)
process.mix.maxBunch = cms.int32(3)

readFiles = cms.untracked.vstring()
readFiles.extend( [
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_10_1_kpJ.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_11_1_Dp3.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_12_1_CDj.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_13_1_tww.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_16_1_t5F.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_17_1_5HE.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_18_1_2XL.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_1_1_hVC.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_21_1_szU.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_22_1_FX7.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_23_1_qxn.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_24_1_30v.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_27_1_0Mv.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_28_1_i8u.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_29_1_T6Z.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_2_1_Af6.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_30_1_7Cr.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_32_1_Uq0.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_34_1_nSG.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_36_1_mcC.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_37_1_b6G.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_39_1_kGa.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_3_1_i4M.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_40_1_Xps.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_41_1_kFB.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_42_1_zVm.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_43_1_UN2.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_44_1_ohP.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_45_1_U9r.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_47_1_Gm7.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_4_1_IMh.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_50_1_6q0.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_51_1_loW.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_52_1_7uX.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_53_1_QkY.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_54_1_rNX.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_55_1_XdY.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_56_1_yah.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_57_1_5RU.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_58_1_Zqm.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_59_1_Wbv.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_5_1_qzY.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_60_1_p8U.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_61_1_4Tf.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_62_1_aRx.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_63_1_jYy.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_64_1_9i8.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_65_1_feM.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_66_1_XBp.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_67_1_4W1.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_68_1_F4U.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_69_1_LCZ.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_6_1_Zc6.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_70_1_97J.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_71_1_kUG.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_72_1_GZo.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_73_1_xqu.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_74_1_NBL.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_75_1_Z0M.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_76_1_G0h.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_77_1_PBv.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_78_1_N3W.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_79_1_8Tt.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_7_1_UAU.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_80_1_tHV.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_81_1_wOV.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_82_1_1Ka.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_83_1_yKo.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_84_1_wvJ.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_85_1_8Q4.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_88_1_Whk.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_89_1_J3v.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_8_1_rAq.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_92_1_NO5.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_94_1_ILX.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_96_1_0Kz.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_97_1_abY.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_98_1_jvB.root',
       'root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/MinBias_TuneZ2star_14TeV-pythia6_Muon2023Upg14-DES23_62_v1/ef741f36cda48faa9eb2c0431e93c9fe/TRK-2023MuonUpg14_9_1_xtu.root' ] );

process.mix.input.fileNames = readFiles

process.mix.digitizers = cms.PSet(process.theDigitizersValid)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'DES23_62_V1::All', '')

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi_valid)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.combinedCustoms
from SLHCUpgradeSimulations.Configuration.combinedCustoms import cust_2023Muon 

#call to customisation function cust_2023Muon imported from SLHCUpgradeSimulations.Configuration.combinedCustoms
process = cust_2023Muon(process)

# End of customisation functions
