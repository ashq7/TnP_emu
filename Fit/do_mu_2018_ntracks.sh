./Make.sh Fit_mu.cc
./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/SingleMuon_HLTIsoMu24_ntracksall.root output_Data_2018_HLTIsoMu24.root Data HLTIsoMu24
./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/DY_HLTIsoMu24_ntracksall.root output_DY_2018_HLTIsoMu24.root DY HLTIsoMu24
python ScaleFactors_mu.py --year=2018 --discriminant=HLTIsoMu24
cp sf_mu_2018_HLTIsoMu24.root sf_mu_2018_HLTIsoMu24_ntracksall.root

./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/SingleMuon_mediumID_ntracksall.root output_Data_2018_mediumID.root Data mediumID
./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/DY_mediumID_ntracksall.root output_DY_2018_mediumID.root DY mediumID
python ScaleFactors_mu.py --year=2018 --discriminant=mediumID
cp sf_mu_2018_mediumID.root sf_mu_2018_mediumID_ntracksall.root

./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/SingleMuon_mediumIso_ntracksall.root output_Data_2018_mediumIso.root Data mediumIso
./Fit_mu.exe 2018 ../PrepareHistograms/output_mu_2018/DY_mediumIso_ntracksall.root output_DY_2018_mediumIso.root DY mediumIso
python ScaleFactors_mu.py --year=2018 --discriminant=mediumIso
cp sf_mu_2018_mediumIso.root sf_mu_2018_mediumIso_ntracksall.root

#./Make.sh Fit_mu_CMSShape.cc
#./Fit_mu_CMSShape.exe 2018 ../PrepareHistograms/output_mu_2018/SingleMuon_antiiso.root output_Data_2018_antiiso.root Data antiiso
#./Fit_mu_CMSShape.exe 2018 ../PrepareHistograms/output_mu_2018/DY_antiiso.root output_DY_2018_antiiso.root DY antiiso
#python ScaleFactors_mu.py --year=2018 --discriminant=antiiso
