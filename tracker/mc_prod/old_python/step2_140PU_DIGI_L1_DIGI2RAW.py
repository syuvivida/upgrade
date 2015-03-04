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
process.mix.input.fileNames = cms.untracked.vstring(['/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/001013BF-FCCC-E311-B864-002618943978.root', '/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/003C734C-1ACD-E311-B531-002590D9D8BE.root', '/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/0040A24A-FDCC-E311-AFDC-90B11C1863B6.root', '/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/0063879C-EECC-E311-8126-90B11C27E5BE.root', '/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/0070BA61-0CCD-E311-B2B0-0025904A9430.root', '/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/007437E0-F3CC-E311-BB02-001E4F1BC1D4.root', '/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/00826EF8-FFCC-E311-8BD8-008CFA1C6564.root', '/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/00CA4F32-FCCC-E311-9C2F-0025905A60A0.root', '/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/00D2744B-38CD-E311-8EAB-008CFA0A570C.root', '/store/mc/Muon2023Upg14/MinBias_TuneZ2star_14TeV-pythia6/GEN-SIM/DES23_62_V1-v1/00000/0216447D-05CD-E311-990D-C8CBB8C5E4B4.root'])
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
