./Make.sh Fit_el_CMSShape.cc

./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/SingleElectron_HLTEle32_ntracksall.root output_Data_2017_HLTEle32.root Data HLTEle32
./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/DY_HLTEle32_ntracksall.root output_DY_2017_HLTEle32.root DY HLTEle32
python ScaleFactors_el.py --year=2017 --discriminant=HLTEle32

cp sf_el_2017_HLTEle32.root sf_el_2017_HLTEle32_ntracksall.root

./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/SingleElectron_MVAisoWP80_ntracksall.root output_Data_2017_MVAisoWP80.root Data MVAisoWP80
./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/DY_MVAisoWP80_ntracksall.root output_DY_2017_MVAisoWP80.root DY MVAisoWP80
python ScaleFactors_el.py --year=2017 --discriminant=MVAisoWP80

cp sf_el_2017_MVAisoWP80.root sf_el_2017_MVAisoWP80_ntracksall.root
