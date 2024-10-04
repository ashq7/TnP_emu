from CRABClient.UserUtilities import config #, getUsernameFromCRIC

config = config()

config.General.requestName = "SingleMuon_Embedded_2018C"
config.General.workArea = "crab_projects"
config.General.transferLogs = True
config.General.transferOutputs = True

config.JobType.pluginName = "Analysis"
config.JobType.psetName = "run_Muon_Embedded_2018.py"
config.JobType.maxMemoryMB = 4000
#config.JobType.numCores = 8

config.section_("Data")
config.Data.inputDataset = '/EmbeddingRun2018C/ElMuFinalState-inputDoubleMu_106X_ULegacy_miniAOD-v1/USER'
config.Data.inputDBS     = 'phys03'
config.Data.splitting    = 'FileBased'
config.Data.unitsPerJob  = 1

#config.Data.inputDataset = "/SingleMuon/Run2018A-UL2018_MiniAODv2_GT36-v1/MINIAOD" 
config.Data.outLFNDirBase = "/store/user/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/"
config.Data.outputDatasetTag = "TnP_ntuples_embedded_mu2018C"
#config.Data.inputDBS = "global"
#config.Data.splitting = "LumiBased"
#config.Data.unitsPerJob = 500
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = "T3_CH_CERNBOX"
config.Site.whitelist = ["T2_*","T3_*"]
