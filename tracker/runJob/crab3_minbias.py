from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutput = True
config.General.requestName = 'MINBIAS'
config.section_('JobType')
config.JobType.psetName = 'gencrab.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['minbias.root']
config.section_('Data')
config.Data.inputDataset = '/MinBias_TuneZ2star_14TeV-pythia6/Muon2023Upg14-DES23_62_V1-v1/GEN-SIM'
config.Data.unitsPerJob = 10
config.Data.dbsUrl = 'global'
config.Data.splitting = 'FileBased'
config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
