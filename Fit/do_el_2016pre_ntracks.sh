./Make.sh Fit_el_CMSShape.cc

./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/SingleElectron_HLTEle32_ntrackslt10.root output_Data_2016pre_HLTEle32.root Data HLTEle32
./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/DY_HLTEle32_ntrackslt10.root output_DY_2016pre_HLTEle32.root DY HLTEle32
python ScaleFactors_el.py --year=2016pre --discriminant=HLTEle32

cp sf_el_2016pre_HLTEle32.root sf_el_2016pre_HLTEle32_ntrackslt10.root

./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/SingleElectron_MVAisoWP80_ntrackslt10.root output_Data_2016pre_MVAisoWP80.root Data MVAisoWP80
./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/DY_MVAisoWP80_ntrackslt10.root output_DY_2016pre_MVAisoWP80.root DY MVAisoWP80
python ScaleFactors_el.py --year=2016pre --discriminant=MVAisoWP80

cp sf_el_2016pre_MVAisoWP80.root sf_el_2016pre_MVAisoWP80_ntrackslt10.root
