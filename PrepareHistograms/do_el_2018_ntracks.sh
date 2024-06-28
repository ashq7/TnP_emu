./Make.sh FinalSelection_el.cc

./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/EGamma_ntracks.root output_el_2018/EGamma_HLTEle32_ntracksall.root data_obs HLTEle32
./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/DY_ntracks.root output_el_2018/DY_HLTEle32_ntracksall.root DY HLTEle32

./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/EGamma_ntracks.root output_el_2018/EGamma_MVAisoWP80_ntracksall.root data_obs MVAisoWP80
./FinalSelection_el.exe 2018 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2018/DY_ntracks.root output_el_2018/DY_MVAisoWP80_ntracksall.root DY MVAisoWP80
