./Make.sh FinalSelection_el.cc

./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/SingleElectron_ntracks.root output_el_2017/SingleElectron_HLTEle32_ntrackslt10.root data_obs HLTEle32
./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/DY_ntracks.root output_el_2017/DY_HLTEle32_ntrackslt10.root DY HLTEle32

./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/SingleElectron_ntracks.root output_el_2017/SingleElectron_MVAisoWP80_ntrackslt10.root data_obs MVAisoWP80
./FinalSelection_el.exe 2017 /eos/cms/store/group/cmst3/group/taug2/TnP_el_2017/DY_ntracks.root output_el_2017/DY_MVAisoWP80_ntrackslt10.root DY MVAisoWP80
