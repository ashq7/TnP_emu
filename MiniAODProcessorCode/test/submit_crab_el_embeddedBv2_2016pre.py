from CRABClient.UserUtilities import config #, getUsernameFromCRIC

config = config()

config.General.requestName = "Electron_embedded_2016preB_ver2"
config.General.workArea = "crab_projects"
config.General.transferLogs = True
config.General.transferOutputs = True

config.JobType.pluginName = "Analysis"
config.JobType.psetName = "run_Electron_Embedded_2016pre.py"
config.JobType.maxMemoryMB = 4000
#config.JobType.numCores = 8

config.section_("Data")
config.Data.inputDataset = '/EmbeddingRun2016-HIPM_B_ver2/ElectronEmbedding-inputDoubleMu_106X_ULegacy_miniAOD-v1/USER'
config.Data.inputDBS     = 'phys03'
config.Data.splitting    = 'FileBased'
config.Data.unitsPerJob  = 1

#config.Data.inputDataset = "/EGamma/Run2018A-UL2018_MiniAODv2_GT36-v1/MINIAOD" 
config.Data.outLFNDirBase = "/store/user/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/2016pre_el_Embedded/"
config.Data.outputDatasetTag = "TnP_ntuples_embedded_DataBv2_el2016pre"
#config.Data.inputDBS = "global"
#config.Data.splitting = "LumiBased"
#config.Data.unitsPerJob = 500
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = "T3_CH_CERNBOX"
config.Site.whitelist = ["T2_*","T3_*"]
