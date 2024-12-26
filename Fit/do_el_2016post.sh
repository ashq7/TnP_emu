./Make.sh Fit_el.cc
./Make.sh Fit_el_CMSShape.cc

./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/Data_HLTMu8Ele23.root output_el_2016post/Data_2016post_HLTMu8Ele23.root Data HLTMu8Ele23
./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/DY_HLTMu8Ele23.root output_el_2016post/DY_2016post_HLTMu8Ele23.root DY HLTMu8Ele23
./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/Embedded_HLTMu8Ele23.root output_el_2016post/output_Embedded_2016post_HLTMu8Ele23.root Embedded HLTMu8Ele23
python ScaleFactors_el.py --year=2016post --discriminant=HLTMu8Ele23

./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/Data_HLTMu23Ele12.root output_el_2016post/output_Data_2016post_HLTMu23Ele12.root Data HLTMu23Ele12
./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/DY_HLTMu23Ele12.root output_el_2016post/output_DY_2016post_HLTMu23Ele12.root DY HLTMu23Ele12
./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/Embedded_HLTMu23Ele12.root output_el_2016post/output_Embedded_2016post_HLTMu23Ele12.root Embedded HLTMu23Ele12
python ScaleFactors_el.py --year=2016post --discriminant=HLTMu23Ele12

#./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/SingleElectron_antiiso.root output_Data_2016post_antiiso.root Data antiiso
#./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/DY_antiiso.root output_DY_2016post_antiiso.root DY antiiso
#python ScaleFactors_el.py --year=2016post --discriminant=antiiso

# ./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/SingleElectron_HLTEle25.root output_Data_2016post_HLTEle25.root Data HLTEle25
# ./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/DY_HLTEle25.root output_DY_2016post_HLTEle25.root DY HLTEle25
# python ScaleFactors_el.py --year=2016post --discriminant=HLTEle25

#./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/SingleElectron_MVAisoWPLoose.root output_Data_2016post_MVAisoWPLoose.root Data MVAisoWPLoose
#./Fit_el_CMSShape.exe 2016post ../PrepareHistograms/output_el_2016post/DY_MVAisoWPLoose.root output_DY_2016post_MVAisoWPLoose.root DY MVAisoWPLoose
#python ScaleFactors_el.py --year=2016post --discriminant=MVAisoWPLoose
