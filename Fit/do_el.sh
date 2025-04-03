rm -rf plots_el_2018/*.png
rm -rf plots_el_2018/*.pdf

rm -rf plots_el_2017/*.png
rm -rf plots_el_2017/*.pdf

rm -rf plots_el_2016post/*.png
rm -rf plots_el_2016post/*.pdf

rm -rf plots_el_2016pre/*.png
rm -rf plots_el_2016pre/*.pdf

sh do_el_2016pre.sh
sh do_el_2016post.sh
sh do_el_2017.sh
sh do_el_2018.sh
