./Make.sh FinalSelection_el.cc

./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/Data_Electron_2017.root output_el_2017/Data_HLTMu23Ele12.root data_obs HLTMu23Ele12 #three different trigger paths
./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/DY_Electron_2017.root output_el_2017/DY_HLTMu23Ele12.root DY HLTMu23Ele12
./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/Embedded_Electron_2017_241120.root output_el_2017/Embedded_HLTMu23Ele12.root data_obs HLTMu23Ele12 

./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/Data_Electron_2017.root output_el_2017/Data_HLTMu8Ele23.root data_obs HLTMu8Ele23
./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/DY_Electron_2017.root output_el_2017/DY_HLTMu8Ele23.root DY HLTMu8Ele23
./FinalSelection_el.exe 2017 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/Embedded_Electron_2017_241120.root output_el_2017/Embedded_HLTMu8Ele23.root data_obs HLTMu8Ele23