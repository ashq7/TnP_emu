./Make.sh Fit_el_CMSShape.cc

./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/EGamma_HLTEle32_ntrackslt10.root output_Data_2018_HLTEle32.root Data HLTEle32
./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/DY_HLTEle32_ntrackslt10.root output_DY_2018_HLTEle32.root DY HLTEle32
python ScaleFactors_el.py --year=2018 --discriminant=HLTEle32

cp sf_el_2018_HLTEle32.root sf_el_2018_HLTEle32_ntrackslt10.root

./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/EGamma_MVAisoWP80_ntrackslt10.root output_Data_2018_MVAisoWP80.root Data MVAisoWP80
./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/DY_MVAisoWP80_ntrackslt10.root output_DY_2018_MVAisoWP80.root DY MVAisoWP80
python ScaleFactors_el.py --year=2018 --discriminant=MVAisoWP80

cp sf_el_2018_MVAisoWP80.root sf_el_2018_MVAisoWP80_ntrackslt10.root
