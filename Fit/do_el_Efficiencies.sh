# Running modified scale factors to get data efficiency plots 
YEAR="2016pre"
TIMESTAMP=""
wwwdir="/eos/user/a/aquinn/www/Ha1a2bbtautau/Fit/plots_el_2016pre/DataEfficiencies"
python ScaleFactors_el_modified.py --year=${YEAR} --discriminant=HLTMu8Ele23 --time=${TIME}
python ScaleFactors_el_modified.py --year=${YEAR} --discriminant=HLTMu23Ele12 --time=${TIME}
cp plots_el_${YEAR}${TIME}/sf*_mc.png ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_mc.pdf ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_embedded.png ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_embedded.pdf ${wwwdir}/

YEAR="2016post"
wwwdir="/eos/user/a/aquinn/www/Ha1a2bbtautau/Fit/plots_el_2016post_2025-04-17-04h12m/DataEfficiencies"
TIMESTAMP="_2025-04-17-04h12m"
python ScaleFactors_el_modified.py --year=${YEAR} --discriminant=HLTMu8Ele23 --time=${TIME}
python ScaleFactors_el_modified.py --year=${YEAR} --discriminant=HLTMu23Ele12 --time=${TIME}
cp plots_el_${YEAR}${TIME}/sf*_mc.png ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_mc.pdf ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_embedded.png ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_embedded.pdf ${wwwdir}/

YEAR="2017"
TIMESTAMP=""
wwwdir="/eos/user/a/aquinn/www/Ha1a2bbtautau/Fit/plots_el_2017/DataEfficiencies"
python ScaleFactors_el_modified.py --year=${YEAR} --discriminant=HLTMu8Ele23 --time=${TIME}
python ScaleFactors_el_modified.py --year=${YEAR} --discriminant=HLTMu23Ele12 --time=${TIME}
cp plots_el_${YEAR}${TIME}/sf*_mc.png ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_mc.pdf ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_embedded.png ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_embedded.pdf ${wwwdir}/

YEAR="2018"
TIMESTAMP="_2025-04-08-21h02m"
wwwdir="/eos/user/a/aquinn/www/Ha1a2bbtautau/Fit/plots_el_2018_2025-04-08-21h02m/DataEfficiencies"
python ScaleFactors_el_modified.py --year=${YEAR} --discriminant=HLTMu8Ele23 --time=${TIME}
python ScaleFactors_el_modified.py --year=${YEAR} --discriminant=HLTMu23Ele12 --time=${TIME}
cp plots_el_${YEAR}${TIME}/sf*_mc.png ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_mc.pdf ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_embedded.png ${wwwdir}/
cp plots_el_${YEAR}${TIME}/sf*_embedded.pdf ${wwwdir}/