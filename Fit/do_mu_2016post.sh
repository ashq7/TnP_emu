./Make.sh Fit_mu.cc
./Fit_mu.exe 2016post ../PrepareHistograms/output_mu_2016post/Data_HLTMu8Ele23.root output_mu_2016post/output_Data_2016post_HLTMu8Ele23.root Data HLTMu8Ele23
./Fit_mu.exe 2016post ../PrepareHistograms/output_mu_2016post/DY_HLTMu8Ele23.root output_mu_2016post/output_DY_2016post_HLTMu8Ele23.root DY HLTMu8Ele23
./Fit_mu.exe 2016post ../PrepareHistograms/output_mu_2016post/Embedded_HLTMu8Ele23.root output_mu_2016post/output_Embedded_2016post_HLTMu8Ele23.root Embedded HLTMu8Ele23
python ScaleFactors_mu.py --year=2016post --discriminant=HLTMu8Ele23

./Fit_mu.exe 2016post ../PrepareHistograms/output_mu_2016post/Data_HLTMu23Ele12.root output_mu_2016post/output_Data_2016post_HLTMu23Ele12.root Data HLTMu23Ele12
./Fit_mu.exe 2016post ../PrepareHistograms/output_mu_2016post/DY_HLTMu23Ele12.root output_mu_2016post/output_DY_2016post_HLTMu23Ele12.root DY HLTMu23Ele12
./Fit_mu.exe 2016post ../PrepareHistograms/output_mu_2016post/Embedded_HLTMu23Ele12.root output_mu_2016post/output_Embedded_2016post_HLTMu23Ele12.root Embedded HLTMu23Ele12
python ScaleFactors_mu.py --year=2016post --discriminant=HLTMu23Ele12

# ./Fit_mu.exe 2016post ../PrepareHistograms/output_mu_2016post/SingleMuon_HLTMu20Tau27.root output_Data_2016post_HLTMu20Tau27.root Data HLTMu20Tau27
# ./Fit_mu.exe 2016post ../PrepareHistograms/output_mu_2016post/DY_HLTMu20Tau27.root output_DY_2016post_HLTMu20Tau27.root DY HLTMu20Tau27
# python ScaleFactors_mu.py --year=2016post --discriminant=HLTMu20Tau27

#./Make.sh Fit_mu_CMSShape.cc
#./Fit_mu_CMSShape.exe 2016post ../PrepareHistograms/output_mu_2016post/SingleMuon_antiiso.root output_Data_2016post_antiiso.root Data antiiso
#./Fit_mu_CMSShape.exe 2016post ../PrepareHistograms/output_mu_2016post/DY_antiiso.root output_DY_2016post_antiiso.root DY antiiso
#python ScaleFactors_mu.py --year=2016post --discriminant=antiiso
