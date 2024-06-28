./Make.sh Fit_mu.cc
./Fit_mu.exe 2016pre ../PrepareHistograms/output_mu_2016pre/SingleMuon_HLTMu8Ele23.root output_Data_2016pre_HLTMu8Ele23.root Data HLTMu8Ele23
./Fit_mu.exe 2016pre ../PrepareHistograms/output_mu_2016pre/DY_HLTMu8Ele23.root output_DY_2016pre_HLTMu8Ele23.root DY HLTMu8Ele23
python ScaleFactors_mu.py --year=2016pre --discriminant=HLTMu8Ele23

./Fit_mu.exe 2016pre ../PrepareHistograms/output_mu_2016pre/SingleMuon_HLTMu23Ele12.root output_Data_2016pre_HLTMu23Ele12.root Data HLTMu23Ele12
./Fit_mu.exe 2016pre ../PrepareHistograms/output_mu_2016pre/DY_HLTMu23Ele12.root output_DY_2016pre_HLTMu23Ele12.root DY HLTMu23Ele12
python ScaleFactors_mu.py --year=2016pre --discriminant=HLTMu23Ele12

./Fit_mu.exe 2016pre ../PrepareHistograms/output_mu_2016pre/SingleMuon_HLTMu20Tau27.root output_Data_2016pre_HLTMu20Tau27.root Data HLTMu20Tau27
./Fit_mu.exe 2016pre ../PrepareHistograms/output_mu_2016pre/DY_HLTMu20Tau27.root output_DY_2016pre_HLTMu20Tau27.root DY HLTMu20Tau27
python ScaleFactors_mu.py --year=2016pre --discriminant=HLTMu20Tau27

#./Make.sh Fit_mu_CMSShape.cc
#./Fit_mu_CMSShape.exe 2016pre ../PrepareHistograms/output_mu_2016pre/SingleMuon_antiiso.root output_Data_2016pre_antiiso.root Data antiiso
#./Fit_mu_CMSShape.exe 2016pre ../PrepareHistograms/output_mu_2016pre/DY_antiiso.root output_DY_2016pre_antiiso.root DY antiiso
#python ScaleFactors_mu.py --year=2016pre --discriminant=antiiso
