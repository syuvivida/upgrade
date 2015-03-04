import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.parseArguments()

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.Geometry.GeometryExtended2023MuonReco_cff')
process.load('Configuration.Geometry.GeometryExtended2023Muon_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')

process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring(options.inputFiles)
)

jecLevels = [
    'START53_V23_L1FastJet_AK7PFchs.txt',
    'START53_V23_L2Relative_AK7PFchs.txt',
    'START53_V23_L3Absolute_AK7PFchs.txt'
    ]

from DelPanj.TreeMaker.eSelXZh_cff import *
from DelPanj.TreeMaker.muSelXZh_global_cff import *
from DelPanj.TreeMaker.muSelXZh_tracker_cff import *



process.tree = cms.EDAnalyzer(
	'TreeMaker',
        fillPUweightInfo_ = cms.bool(False),
        fillEventInfo_ = cms.bool(False),
        fillGenInfo_   = cms.bool(True),
        fillTrkSimHitInfo_= cms.bool(True),
        fillMuonInfo_  = cms.bool(False),
        fillElecInfo_  = cms.bool(False),
        fillJetInfo_   = cms.bool(False),
        fillMetInfo_   = cms.bool(False),
        fillTrigInfo_  = cms.bool(False),
        fillPhotInfo_  = cms.bool(False),
        genPartLabel=cms.InputTag("genParticles"),
        patMuons=cms.InputTag("patMuonsWithTrigger"),
        patElectrons = cms.InputTag("patElectronsWithTrigger"),
        Jets=cms.InputTag("selectedPatJetsCA8CHSwithQJetsForBoostedTaus"),
        PrunedJets=cms.InputTag("selectedPatJetsCA8CHSprunedForBoostedTaus"),
        rhoSrc = cms.InputTag('kt6PFJets', 'rho'),
        pvSrc  = cms.InputTag('goodOfflinePrimaryVertices'),
        jecPayloadNames = cms.vstring( jecLevels ),
        jecUncName = cms.string('START53_V23_Uncertainty_AK7PFchs.txt'),    
        e2012IDSet  =  eSelXZh,
        globalMuonIDSet = muSelXZh_global,
        trackerMuonIDSet = muSelXZh_tracker,
        eleRhoIso = cms.InputTag("kt6PFJets","rho"),
        patMet=cms.InputTag("patMETs"),
        outFileName=cms.string('outputFileName.root')

	)

process.TFileService = cms.Service("TFileService",
        fileName = cms.string(options.outputFile)
)

process.p = cms.Path(process.tree)
#process.p = cms.Path(process.demo)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
