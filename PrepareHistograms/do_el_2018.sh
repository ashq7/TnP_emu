# Makes histograms from data, MC
./Make.sh FinalSelection_el.cc

# Four cross-triggers (HLTMu23, 8, etc)
#-------------------string year----------------string input-----------------------------------------------------string output----------string sample--string discriminant
./FinalSelection_el.exe 2018 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/EGamma_Electron_Data_2018.root output_el_2018/EGamma_HLTMu23Ele12.root data_obs HLTMu23Ele12 #three different trigger paths
./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/DY.root output_el_2018/DY_HLTMu23Ele12.root DY HLTMu23Ele12

./FinalSelection_el.exe 2018 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/EGamma_Electron_Data_2018.root output_el_2018/EGamma_HLTMu8Ele23.root data_obs HLTMu8Ele23
./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/DY.root output_el_2018/DY_HLTMu8Ele23.root DY HLTMu8Ele23

./FinalSelection_el.exe 2018 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/EGamma_Electron_Data_2018.root output_el_2018/EGamma_HLTEle32.root data_obs HLTEle32
./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/DY.root output_el_2018/DY_HLTEle32.root DY HLTEle32

./FinalSelection_el.exe 2018 /eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CrabOutput/EGamma_Electron_Data_2018.root output_el_2018/EGamma_HLTEle24Tau30.root data_obs HLTEle24Tau30
./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/DY.root output_el_2018/DY_HLTEle24Tau30.root DY HLTEle24Tau30

#Ashling did NOT comment this out
#./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/EGamma.root output_el_2018/EGamma_antiiso.root data_obs antiiso
#./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/DY.root output_el_2018/DY_antiiso.root DY antiiso
#
#./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/EGamma.root output_el_2018/EGamma_MVAisoWPLoose.root data_obs MVAisoWPLoose
#./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/DY.root output_el_2018/DY_MVAisoWPLoose.root DY MVAisoWPLoose
