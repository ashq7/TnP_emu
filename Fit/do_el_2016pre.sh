./Make.sh Fit_el.cc
./Make.sh Fit_el_CMSShape.cc
./Make.sh Fit_el_CMSShape_2016pre.cc

./Fit_el_CMSShape_2016pre.exe 2016pre ../PrepareHistograms/output_el_2016pre/Data_HLTMu8Ele23.root output_el_2016pre/output_Data_2016pre_HLTMu8Ele23.root Data HLTMu8Ele23
./Fit_el_CMSShape_2016pre.exe 2016pre ../PrepareHistograms/output_el_2016pre/DY_HLTMu8Ele23.root output_el_2016pre/output_DY_2016pre_HLTMu8Ele23.root DY HLTMu8Ele23
./Fit_el_CMSShape_2016pre.exe 2016pre ../PrepareHistograms/output_el_2016pre/Embedded_HLTMu8Ele23.root output_el_2016pre/output_Embedded_2016pre_HLTMu8Ele23.root Embedded HLTMu8Ele23
python ScaleFactors_el.py --year=2016pre --discriminant=HLTMu8Ele23

./Fit_el_CMSShape_2016pre.exe 2016pre ../PrepareHistograms/output_el_2016pre/Data_HLTMu23Ele12.root output_el_2016pre/output_Data_2016pre_HLTMu23Ele12.root Data HLTMu23Ele12
./Fit_el_CMSShape_2016pre.exe 2016pre ../PrepareHistograms/output_el_2016pre/DY_HLTMu23Ele12.root output_el_2016pre/output_DY_2016pre_HLTMu23Ele12.root DY HLTMu23Ele12
./Fit_el_CMSShape_2016pre.exe 2016pre ../PrepareHistograms/output_el_2016pre/Embedded_HLTMu23Ele12.root output_el_2016pre/output_Embedded_2016pre_HLTMu23Ele12.root Embedded HLTMu23Ele12
python ScaleFactors_el.py --year=2016pre --discriminant=HLTMu23Ele12

# ./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/SingleElectron_HLTEle25.root output_Data_2016pre_HLTEle25.root Data HLTEle25
# ./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/DY_HLTEle25.root output_DY_2016pre_HLTEle25.root DY HLTEle25
# python ScaleFactors_el.py --year=2016pre --discriminant=HLTEle25

#./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/SingleElectron_antiiso.root output_Data_2016pre_antiiso.root Data antiiso
#./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/DY_antiiso.root output_DY_2016pre_antiiso.root DY antiiso
#python ScaleFactors_el.py --year=2016pre --discriminant=antiiso

#./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/SingleElectron_MVAisoWPLoose.root output_Data_2016pre_MVAisoWPLoose.root Data MVAisoWPLoose
#./Fit_el_CMSShape.exe 2016pre ../PrepareHistograms/output_el_2016pre/DY_MVAisoWPLoose.root output_DY_2016pre_MVAisoWPLoose.root DY MVAisoWPLoose
#python ScaleFactors_el.py --year=2016pre --discriminant=MVAisoWPLoose
