./Make.sh Fit_el.cc
./Make.sh Fit_el_CMSShape.cc

./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/Data_HLTMu8Ele23.root output_Data_2017_HLTMu8Ele23.root Data HLTMu8Ele23
./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/DY_HLTMu8Ele23.root output_DY_2017_HLTMu8Ele23.root DY HLTMu8Ele23
./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/Embedded_HLTMu8Ele23.root output_Embedded_2017_HLTMu8Ele23.root Embedded HLTMu8Ele23
python ScaleFactors_el.py --year=2017 --discriminant=HLTMu8Ele23

#./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/SingleElectron_antiiso.root output_Data_2017_antiiso.root Data antiiso
#./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/DY_antiiso.root output_DY_2017_antiiso.root DY antiiso
#python ScaleFactors_el.py --year=2017 --discriminant=antiiso

./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/Data_HLTMu23Ele12.root output_Data_2017_HLTMu23Ele12.root Data HLTMu23Ele12
./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/DY_HLTMu23Ele12.root output_DY_2017_HLTMu23Ele12.root DY HLTMu23Ele12
./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/Embedded_HLTMu23Ele12.root output_Embedded_2017_HLTMu23Ele12.root Embedded HLTMu23Ele12
python ScaleFactors_el.py --year=2017 --discriminant=HLTMu23Ele12

# ./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/SingleElectron_HLTEle32.root output_Data_2017_HLTEle32.root Data HLTEle32
# ./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/DY_HLTEle32.root output_DY_2017_HLTEle32.root DY HLTEle32
# python ScaleFactors_el.py --year=2017 --discriminant=HLTEle32

# ./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/SingleElectron_HLTEle24Tau30.root output_Data_2017_HLTEle24Tau30.root Data HLTEle24Tau30
# ./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/DY_HLTEle24Tau30.root output_DY_2017_HLTEle24Tau30.root DY HLTEle24Tau30
# python ScaleFactors_el.py --year=2017 --discriminant=HLTEle24Tau30

#./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/SingleElectron_MVAisoWPLoose.root output_Data_2017_MVAisoWPLoose.root Data MVAisoWPLoose
#./Fit_el_CMSShape.exe 2017 ../PrepareHistograms/output_el_2017/DY_MVAisoWPLoose.root output_DY_2017_MVAisoWPLoose.root DY MVAisoWPLoose
#python ScaleFactors_el.py --year=2017 --discriminant=MVAisoWPLoose
