from CRABClient.UserUtilities import config #, getUsernameFromCRIC

config = config()

config.General.requestName = "EGamma_2018A"
config.General.workArea = "crab_projects"
config.General.transferLogs = True
config.General.transferOutputs = True

config.JobType.pluginName = "Analysis"
config.JobType.psetName = "run_Electron_Data_2018.py"
config.JobType.maxMemoryMB = 4000
#config.JobType.numCores = 8

config.section_("Data")
config.Data.inputDataset = '/EmbeddingRun2018D/skkwan-EmbeddingRun2018D_MuTau_106X_UL18_MiniAODv1_NanoAODv9-00000000000000000000000000000000/USER'
config.Data.inputDBS     = 'phys03'
config.Data.splitting    = 'FileBased'
config.Data.unitsPerJob  = 1

#config.Data.inputDataset = "/EGamma/Run2018A-UL2018_MiniAODv2_GT36-v1/MINIAOD" 
config.Data.outLFNDirBase = "/store/user/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/"
config.Data.outputDatasetTag = "TnP_ntuples_el2018"
#config.Data.inputDBS = "global"
#config.Data.splitting = "LumiBased"
#config.Data.unitsPerJob = 500
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = "T3_CH_CERNBOX"
config.Site.whitelist = ["T2_*","T3_*"]
