import FWCore.ParameterSet.Config as cms

#if varOptions.GT == "auto":
#  if options['isMC']:
#    if options['era'] == 'UL2016preVFP':  options['GLOBALTAG'] = '106X_mcRun2_asymptotic_preVFP_v9'
#    if options['era'] == 'UL2016postVFP': options['GLOBALTAG'] = '106X_mcRun2_asymptotic_v15'
#    if options['era'] == 'UL2017': options['GLOBALTAG'] = '106X_dataRun2_v28'
#    if options['era'] == 'UL2018': options['GLOBALTAG'] = '106X_dataRun2_v28'
#  else:
#    if options['era'] == 'UL2016preVFP':  options['GLOBALTAG'] = '106X_dataRun2_v32'
#    if options['era'] == 'UL2016postVFP': options['GLOBALTAG'] = '106X_dataRun2_v32'
#    if options['era'] == 'UL2017': options['GLOBALTAG'] = '106X_mc2017_realistic_v7'
#    if options['era'] == 'UL2018': options['GLOBALTAG'] = '106X_upgrade2018_realistic_v11_L1v1'
#else:
#  options['GLOBALTAG'] = varOptions.GT


process = cms.Process("Demo")


process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mcRun2_asymptotic_v17', '')

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# Choose the file you want to run on
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
	'/store/mc/RunIISummer20UL18MiniAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/100000/4E295BA9-D9F7-6643-B993-57789E70C0CB.root',
	#'/store/mc/RunIISummer16MiniAODv2/SUSYGluGluToHToAA_AToBB_AToTauTau_M-40_TuneCUETP8M1_13TeV_madgraph_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/70000/1E524614-FDDB-E611-894B-001E67457DFA.root'

	#'file:/eos/cms/store/user/ccaillol/DPS_all_miniAOD/fullsim_miniAOD_merge0.root',
    )
)

process.source.duplicateCheckMode = cms.untracked.string("noDuplicateCheck")

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("histo.root"),
      closeFileFast = cms.untracked.bool(True)
  )

process.demo = cms.EDAnalyzer('MuonAnalyzer',
    isMC=cms.bool(True),
    year=cms.int32(2016),
    bits = cms.InputTag("TriggerResults","","HLT"),
    objects = cms.InputTag("slimmedPatTrigger"),
    muons = cms.InputTag("slimmedMuons"),
    vertices=cms.InputTag("offlineSlimmedPrimaryVertices"),
    l1muons=cms.InputTag("gmtStage2Digis","Muon"),
    l1taus=cms.InputTag("caloStage2Digis","Tau"),
    pileupInfo=cms.InputTag('slimmedAddPileupInfo'),
    pfCands = cms.InputTag("packedPFCandidates"),
)

process.p = cms.Path(process.demo)
