./Make.sh FinalSelection_el.cc

./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/Data_Electron_2017.root output_el_2017/Data_HLTMu23Ele12.root data_obs HLTMu23Ele12 #three different trigger paths
./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/DY_Electron_2017.root output_el_2017/DY_HLTMu23Ele12.root DY HLTMu23Ele12
./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/Embedded_Electron_2017.root output_el_2017/Embedded_HLTMu23Ele12.root data_obs HLTMu23Ele12 

#./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/SingleElectron.root output_el_2017/SingleElectron_HLTMu23Ele12.root data_obs HLTMu23Ele12
#./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/DY.root output_el_2017/DY_HLTMu23Ele12.root DY HLTMu23Ele12

./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/Data_Electron_2017.root output_el_2017/Data_HLTMu8Ele23.root data_obs HLTMu8Ele23
./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/DY_Electron_2017.root output_el_2017/DY_HLTMu8Ele23.root DY HLTMu8Ele23
./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/Embedded_Electron_2017.root output_el_2017/Embedded_HLTMu8Ele23.root data_obs HLTMu8Ele23

#Don't need single/ tau cross triggers
# ./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/SingleElectron.root output_el_2017/SingleElectron_HLTEle32.root data_obs HLTEle32
# ./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/DY.root output_el_2017/DY_HLTEle32.root DY HLTEle32

# ./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/SingleElectron.root output_el_2017/SingleElectron_HLTEle24Tau30.root data_obs HLTEle24Tau30
# ./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/DY.root output_el_2017/DY_HLTEle24Tau30.root DY HLTEle24Tau30

#./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/SingleElectron.root output_el_2017/SingleElectron_antiiso.root data_obs antiiso
#./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/DY.root output_el_2017/DY_antiiso.root DY antiiso
#
#./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/SingleElectron.root output_el_2017/SingleElectron_MVAisoWPLoose.root data_obs MVAisoWPLoose
#./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/DY.root output_el_2017/DY_MVAisoWPLoose.root DY MVAisoWPLoose
