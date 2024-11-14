./Make.sh Fit_el.cc
./Make.sh Fit_el_CMSShape.cc

./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/EGamma_HLTMu8Ele23.root output_Data_2018_HLTMu8Ele23.root Data HLTMu8Ele23
./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/DY_HLTMu8Ele23.root output_DY_2018_HLTMu8Ele23.root DY HLTMu8Ele23
./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/Embedded_HLTMu8Ele23.root output_Embedded_2018_HLTMu8Ele23.root Embedded HLTMu8Ele23
python ScaleFactors_el.py --year=2018 --discriminant=HLTMu8Ele23

./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/EGamma_HLTMu23Ele12.root output_Data_2018_HLTMu23Ele12.root Data HLTMu23Ele12
./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/DY_HLTMu23Ele12.root output_DY_2018_HLTMu23Ele12.root DY HLTMu23Ele12
./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/Embedded_HLTMu8Ele23.root output_Embedded_2018_HLTMu8Ele23.root Embedded HLTMu8Ele23
python ScaleFactors_el.py --year=2018 --discriminant=HLTMu23Ele12

#./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/EGamma_antiiso.root output_Data_2018_antiiso.root Data antiiso
#./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/DY_antiiso.root output_DY_2018_antiiso.root DY antiiso
#python ScaleFactors_el.py --year=2018 --discriminant=antiiso

# ./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/EGamma_HLTEle32.root output_Data_2018_HLTEle32.root Data HLTEle32
# ./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/DY_HLTEle32.root output_DY_2018_HLTEle32.root DY HLTEle32
# python ScaleFactors_el.py --year=2018 --discriminant=HLTEle32

# ./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/EGamma_HLTEle24Tau30.root output_Data_2018_HLTEle24Tau30.root Data HLTEle24Tau30
# ./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/DY_HLTEle24Tau30.root output_DY_2018_HLTEle24Tau30.root DY HLTEle24Tau30
# python ScaleFactors_el.py --year=2018 --discriminant=HLTEle24Tau30

#./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/EGamma_MVAisoWPLoose.root output_Data_2018_MVAisoWPLoose.root Data MVAisoWPLoose
#./Fit_el_CMSShape.exe 2018 ../PrepareHistograms/output_el_2018/DY_MVAisoWPLoose.root output_DY_2018_MVAisoWPLoose.root DY MVAisoWPLoose
#python ScaleFactors_el.py --year=2018 --discriminant=MVAisoWPLoose
