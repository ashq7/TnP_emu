# TnP framework for electrons and muons

## Setup

```
cmsrel CMSSW_10_6_27
cd CMSSW_10_6_27/src
cmsenv
git cms-init
git clone https://github.com/ashq7/TnP_emu.git
scram b -j 8
```

## Step 1: skim MiniAOD
cmssw-el7
Test analyzer using cmsRun TnP_emu/MiniAODProcessorCode/test/run_*.py (sub in el/mu and given year for *)
Then run crab jobs using crab submit -c submit_crab_*.py (sub in el/mu and given year for *)

Changes Ashling made from Cecile's were editing ElectronAnalyzer.cc to access noIso branches for electrons.
Ashling ran these specifically:
cmsRun TnP_emu/MiniAODProcessorCode/test/run_Electron_Data_2018.py
cmsRun TnP_emu/MiniAODProcessorCode/test/run_Electron_MC.py

submit -c submit_crab_el_DataA_2018.py
submit -c submit_crab_el_DY_2018.py

## Step 2: make pass and fail histograms
sh TnP_emu/PrepareHistograms/do_*.sh (sub in el/mu and given year for *)

Ashling ran these specifically: sh do_el_2018.sh 

## Step 3: fit pass and fail histograms
cmssw-el7
sh TnP_emu/Fit/do_*.sh (sub in el/mu and given year for *)

Ashling ran these specifically: do_el_2018.sh

## Step 4: Plot 2D SF Histos
root -l TnP_emu/Fit/sf_el_2018_*.root (sub in given cross-trigger for *)
SF2D->Draw()
SF2D->Draw(“TEXT45 SAME”)
c1->SaveAs("SF2D_[given trigger].png")
