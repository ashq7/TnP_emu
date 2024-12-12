import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run2_2016_HIPM_cff import Run2_2016_HIPM
from Configuration.Eras.Modifier_run2_nanoAOD_106Xv2_cff import run2_nanoAOD_106Xv2

process = cms.Process('NANO',Run2_2016_HIPM,run2_nanoAOD_106Xv2)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('PhysicsTools.NanoAOD.nano_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_dataRun2_v35', '')

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# Choose the file you want to run on
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/data/Run2016C/SingleElectron/MINIAOD/HIPM_UL2016_MiniAODv2-v2/130000/147AB257-ABD6-454D-8BB2-48368C539290.root',
	#'/store/mc/RunIISummer20UL18MiniAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/100000/4E295BA9-D9F7-6643-B993-57789E70C0CB.root',
	#'/store/mc/RunIISummer16MiniAODv2/SUSYGluGluToHToAA_AToBB_AToTauTau_M-40_TuneCUETP8M1_13TeV_madgraph_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/70000/1E524614-FDDB-E611-894B-001E67457DFA.root'

	#'file:/eos/cms/store/user/ccaillol/DPS_all_miniAOD/fullsim_miniAOD_merge0.root',
    )
)

process.source.duplicateCheckMode = cms.untracked.string("noDuplicateCheck")

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("histo.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.demo = cms.EDAnalyzer('ElectronAnalyzer',
    isMC=cms.bool(False),
    year=cms.int32(2016),
    bits = cms.InputTag("TriggerResults","","SIMembeddingHLT"),
    objects = cms.InputTag("slimmedPatTrigger"),
    electrons = cms.InputTag("slimmedElectrons"),
    vertices=cms.InputTag("offlineSlimmedPrimaryVertices"),
    l1electrons=cms.InputTag("caloStage2Digis","EGamma"),
    l1taus=cms.InputTag("caloStage2Digis","Tau"),
    pileupInfo=cms.InputTag('slimmedAddPileupInfo'),
    pfCands = cms.InputTag("packedPFCandidates"),
)

process.p = cms.Path(process.demo)
