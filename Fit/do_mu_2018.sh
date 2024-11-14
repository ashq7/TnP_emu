./Make.sh Fit_mu.cc

./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/SingleMuon_HLTMu8Ele23.root output_Data_2018_HLTMu8Ele23.root Data HLTMu8Ele23
./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/DY_HLTMu8Ele23.root output_DY_2018_HLTMu8Ele23.root DY HLTMu8Ele23
./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/Embedded_HLTMu8Ele23.root output_Embedded_2018_HLTMu8Ele23.root Embedded HLTMu8Ele23
python ScaleFactors_mu.py --year=2018 --discriminant=HLTMu8Ele23

./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/SingleMuon_HLTMu23Ele12.root output_Data_2018_HLTMu23Ele12.root Data HLTMu23Ele12
./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/DY_HLTMu23Ele12.root output_DY_2018_HLTMu23Ele12.root DY HLTMu23Ele12
./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/Embedded_HLTMu8Ele23.root output_Embedded_2018_HLTMu8Ele23.root Embedded HLTMu8Ele23
python ScaleFactors_mu.py --year=2018 --discriminant=HLTMu23Ele12

# ./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/SingleMuon_HLTMu20Tau27.root output_Data_2018_HLTMu20Tau27.root Data HLTMu20Tau27
# ./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/DY_HLTMu20Tau27.root output_DY_2018_HLTMu20Tau27.root DY HLTMu20Tau27
# python ScaleFactors_mu.py --year=2018 --discriminant=HLTMu20Tau27

# ./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/SingleMuon_HLTIsoMu24.root output_Data_2018_HLTIsoMu24.root Data HLTIsoMu24
# ./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/DY_HLTIsoMu24.root output_DY_2018_HLTIsoMu24.root DY HLTIsoMu24
# python ScaleFactors_mu.py --year=2018 --discriminant=HLTIsoMu24

#./Make.sh Fit_mu_CMSShape.cc
#./Fit_mu_CMSShape.exe 2018 ../PrepareHistograms/output_mu_2018/SingleMuon_antiiso.root output_Data_2018_antiiso.root Data antiiso
#./Fit_mu_CMSShape.exe 2018 ../PrepareHistograms/output_mu_2018/DY_antiiso.root output_DY_2018_antiiso.root DY antiiso
#python ScaleFactors_mu.py --year=2018 --discriminant=antiiso
