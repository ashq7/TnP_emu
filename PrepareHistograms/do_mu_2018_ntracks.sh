./Make.sh FinalSelection_mu.cc

./FinalSelection_mu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/SingleMuon_ntracks.root output_mu_2018/SingleMuon_HLTIsoMu24_ntracksall.root data_obs HLTIsoMu24
./FinalSelection_mu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/DY_ntracks.root output_mu_2018/DY_HLTIsoMu24_ntracksall.root DY HLTIsoMu24

./FinalSelection_mu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/SingleMuon_ntracks.root output_mu_2018/SingleMuon_mediumIso_ntracksall.root data_obs mediumIso
./FinalSelection_mu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/DY_ntracks.root output_mu_2018/DY_mediumIso_ntracksall.root DY mediumIso

./FinalSelection_mu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/SingleMuon_ntracks.root output_mu_2018/SingleMuon_mediumID_ntracksall.root data_obs mediumID
./FinalSelection_mu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/DY_ntracks.root output_mu_2018/DY_mediumID_ntracksall.root DY mediumID
