from CRABClient.UserUtilities import config #, getUsernameFromCRIC

config = config()

config.General.requestName = "EGamma_embedded_2017B"
config.General.workArea = "crab_projects"
config.General.transferLogs = True
config.General.transferOutputs = True

config.JobType.pluginName = "Analysis"
config.JobType.psetName = "run_Electron_Embedded_2017.py"
config.JobType.maxMemoryMB = 4000
#config.JobType.numCores = 8

config.section_("Data")
config.Data.inputDataset = '/EmbeddingRun2017B/ElectronEmbedding-inputDoubleMu_106X_ULegacy_miniAOD-v1/USER'
config.Data.inputDBS     = 'phys03'
config.Data.splitting    = 'FileBased'
config.Data.unitsPerJob  = 1

#config.Data.inputDataset = "/EGamma/Run2018A-UL2018_MiniAODv2_GT36-v1/MINIAOD" 
config.Data.outLFNDirBase = "/store/user/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/2017_el_Embedded/"
config.Data.outputDatasetTag = "TnP_ntuples_embedded_DataB_el2017"
#config.Data.inputDBS = "global"
#config.Data.splitting = "LumiBased"
#config.Data.unitsPerJob = 500
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = "T3_CH_CERNBOX"
config.Site.whitelist = ["T2_*","T3_*"]
