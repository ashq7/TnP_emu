./Make.sh Fit_mu.cc
./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/SingleMuon_HLTMu8Ele23.root output_mu_2017/output_Data_2017_HLTMu8Ele23.root Data HLTMu8Ele23
./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/DY_HLTMu8Ele23.root output_mu_2017/output_DY_2017_HLTMu8Ele23.root DY HLTMu8Ele23
./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/Embedded_HLTMu8Ele23.root output_mu_2017/output_Embedded_2017_HLTMu8Ele23.root Embedded HLTMu8Ele23
python ScaleFactors_mu.py --year=2017 --discriminant=HLTMu8Ele23

./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/SingleMuon_HLTMu23Ele12.root output_mu_2017/output_Data_2017_HLTMu23Ele12.root Data HLTMu23Ele12
./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/DY_HLTMu23Ele12.root output_mu_2017/output_DY_2017_HLTMu23Ele12.root DY HLTMu23Ele12
./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/Embedded_HLTMu23Ele12.root output_mu_2017/output_Embedded_2017_HLTMu23Ele12.root Embedded HLTMu23Ele12
python ScaleFactors_mu.py --year=2017 --discriminant=HLTMu23Ele12

# ./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/SingleMuon_HLTMu20Tau27.root output_Data_2017_HLTMu20Tau27.root Data HLTMu20Tau27
# ./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/DY_HLTMu20Tau27.root output_DY_2017_HLTMu20Tau27.root DY HLTMu20Tau27
# python ScaleFactors_mu.py --year=2017 --discriminant=HLTMu20Tau27

#./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/SingleMuon_HLTMu20Tau27_2017B.root output_Data_2017_HLTMu20Tau27_2017B.root Data HLTMu20Tau27_2017B
#./Fit_mu.exe 2017 ../PrepareHistograms/output_mu_2017/DY_HLTMu20Tau27_2017B.root output_DY_2017_HLTMu20Tau27_2017B.root DY HLTMu20Tau27_2017B
#python ScaleFactors_mu.py --year=2017 --discriminant=HLTMu20Tau27_2017B

#./Make.sh Fit_mu_CMSShape.cc
#./Fit_mu_CMSShape.exe 2017 ../PrepareHistograms/output_mu_2017/SingleMuon_antiiso.root output_Data_2017_antiiso.root Data antiiso
#./Fit_mu_CMSShape.exe 2017 ../PrepareHistograms/output_mu_2017/DY_antiiso.root output_DY_2017_antiiso.root DY antiiso
#python ScaleFactors_mu.py --year=2017 --discriminant=antiiso
