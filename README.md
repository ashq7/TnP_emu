# TnP framework for electrons and muons

## Setup

```
cmsrel CMSSW_10_6_27
cd CMSSW_10_6_27/src
cmsenv
git cms-init
git clone https://github.com/cecilecaillol/TnP_emu.git
mv TnP_emu/* .
rm -rf TnP_emu
scram b -j 8
```

## Step 1: skim MiniAOD

## Step 2: make pass and fail histograms

## Step 3: fit pass and fail histograms


