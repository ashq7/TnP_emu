./Make.sh FinalSelection_el.cc

./FinalSelection_el.exe 2016post /eos/cms/store/group/cmst3/group/taug2/TnP_el_2016post/SingleElectron_ntracks.root output_el_2016post/SingleElectron_HLTEle32_ntracksall.root data_obs HLTEle32
./FinalSelection_el.exe 2016post /eos/cms/store/group/cmst3/group/taug2/TnP_el_2016post/DY_ntracks.root output_el_2016post/DY_HLTEle32_ntracksall.root DY HLTEle32

./FinalSelection_el.exe 2016post /eos/cms/store/group/cmst3/group/taug2/TnP_el_2016post/SingleElectron_ntracks.root output_el_2016post/SingleElectron_MVAisoWP80_ntracksall.root data_obs MVAisoWP80
./FinalSelection_el.exe 2016post /eos/cms/store/group/cmst3/group/taug2/TnP_el_2016post/DY_ntracks.root output_el_2016post/DY_MVAisoWP80_ntracksall.root DY MVAisoWP80
