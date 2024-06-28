#!/usr/bin/env python
import ROOT
import re  
import argparse
from array import array

is_datadriven=1

def add_lumi(year):
    lowX=0.55
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    if (year=="2018"): lumi.AddText("2018, 60 fb^{-1} (13 TeV)")
    if (year=="2017"): lumi.AddText("2017, 41 fb^{-1} (13 TeV)")
    if (year=="2016"): lumi.AddText("2016, 36 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.21
    lowY=0.70
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.21
    lowY=0.63
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.5, 0.65, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

ROOT.gStyle.SetOptStat(0)

parser = argparse.ArgumentParser()
parser.add_argument('--year', '-y', default=None, help='Output name')
parser.add_argument('--discriminant', '-d', default=None)
args = parser.parse_args()


c=ROOT.TCanvas("canvas","",0,0,800,800)
c.cd()

file_data_lt10=ROOT.TFile("output_Data_"+args.year+"_"+args.discriminant+"_ntrackslt10.root","r")
file_mc_lt10=ROOT.TFile("output_DY_"+args.year+"_"+args.discriminant+"_ntrackslt10.root","r")


eff2D_data_lt10=file_data_lt10.Get("eff")
eff2D_mc_lt10=file_mc_lt10.Get("eff")

sf2D_lt10=eff2D_data_lt10.Clone()
sf2D_lt10.Divide(eff2D_mc)
sf2D_lt10.SetName("SF2D")
eff2D_data_lt10.SetName("eff_data")
eff2D_mc_lt10.SetName("eff_mc")


bins_pt=[15,20,35,50,75,100,200]
nb_bins=6

bins_eta=[-2.5,-2.0,-1.5,-0.8,0.0,0.8,1.5,2.0,2.5]
nb_bins_eta=8


eff1D_data_eta_lt10=ROOT.TH1F("eff1_data_eta_lt10","eff1D_data_eta_lt10",nb_bins_eta,array('d',bins_eta))
eff1D_mc_eta_lt10=ROOT.TH1F("eff1_mc_eta_lt10","eff1D_mc_eta_lt10",nb_bins_eta,array('d',bins_eta))

for k in range(0,nb_bins_eta):
   eff1D_data_eta_lt10.SetBinContent(k+1,eff2D_data.GetBinContent(i+1,k+1))
   eff1D_mc_eta_lt10.SetBinContent(k+1,eff2D_mc.GetBinContent(i+1,k+1))
   eff1D_data_eta_lt10.SetBinError(k+1,eff2D_data.GetBinError(i+1,k+1))
   eff1D_mc_eta_lt10.SetBinError(k+1,eff2D_mc.GetBinError(i+1,k+1))

eff1D_mc_eta_lt10.GetXaxis().SetTitle("")
eff1D_mc_eta_lt10.GetXaxis().SetTitleSize(0)
eff1D_mc_eta_lt10.GetXaxis().SetNdivisions(505)
eff1D_mc_eta_lt10.GetYaxis().SetLabelFont(42)
eff1D_mc_eta_lt10.GetYaxis().SetLabelOffset(0.01)
eff1D_mc_eta_lt10.GetYaxis().SetLabelSize(0.06)
eff1D_mc_eta_lt10.GetYaxis().SetTitleSize(0.075)
eff1D_mc_eta_lt10.GetYaxis().SetTitleOffset(1.04)
eff1D_mc_eta_lt10.SetTitle("")
eff1D_mc_eta_lt10.GetYaxis().SetTitle("Events/bin")
eff1D_mc_eta_lt10.SetLineColor(1)
eff1D_mc_eta_lt10.SetLineWidth(3)

eff1D_data_eta_lt10.SetLineColor(2)
eff1D_data_eta_lt10.SetLineWidth(3)

eff_data_eta_lt10.append(eff1D_data_eta_lt10.Clone())

ratio_eta_lt10=eff1D_data_eta_lt10.Clone()
ratio_eta_lt10.Sumw2()
ratio_eta_lt10.Divide(eff1D_mc_eta_lt10)

ratio_eta_lt10.SetTitle("")
ratio_eta_lt10.GetXaxis().SetTitle("Supercluster #eta")
ratio_eta_lt10.GetYaxis().SetTitle("SF")
ratio_eta_lt10.GetXaxis().SetNdivisions(515)
ratio_eta_lt10.GetYaxis().SetNdivisions(505)
ratio_eta_lt10.GetXaxis().SetTitleSize(0.15)
ratio_eta_lt10.GetYaxis().SetTitleSize(0.15)
ratio_eta_lt10.GetYaxis().SetTitleOffset(0.56)
ratio_eta_lt10.GetXaxis().SetTitleOffset(1.04)
ratio_eta_lt10.GetXaxis().SetLabelSize(0.11)
ratio_eta_lt10.GetYaxis().SetLabelSize(0.11)
ratio_eta_lt10.GetXaxis().SetTitleFont(42)
ratio_eta_lt10.GetYaxis().SetTitleFont(42)
ratio_eta_lt10.SetMinimum(0.78)
ratio_eta_lt10.SetMaximum(1.12)
sf_eta_lt10.append(ratio_eta_lt10.Clone())

pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
pad1.Draw()
pad1.cd()
pad1.SetFillColor(0)
pad1.SetBorderMode(0)
pad1.SetBorderSize(10)
pad1.SetTickx(1)
pad1.SetTicky(1)
pad1.SetLeftMargin(0.18)
pad1.SetRightMargin(0.05)
pad1.SetTopMargin(0.122)
pad1.SetBottomMargin(0.026)
pad1.SetFrameFillStyle(0)
pad1.SetFrameLineStyle(0)
pad1.SetFrameBorderMode(0)
pad1.SetFrameBorderSize(10)

eff_data_eta_lt10.SetLineColor(ROOT.kGreen+1)
eff_data_eta_lt10.SetMarkerColor(ROOT.kGreen+1)
eff_data_eta_lt10.SetMarkerStyle(20)
eff_data_eta_lt10.SetLineWidth(3)
eff_data_eta_lt10.SetTitle("")
eff_data_eta_lt10.GetXaxis().SetTitleSize(0.0)
eff_data_eta_lt10.GetYaxis().SetTitle("Data efficiency")
eff_data_eta_lt10.GetYaxis().SetTitleSize(0.06)
eff_data_eta_lt10.GetXaxis().SetLabelSize(0.0)
eff_data_eta_lt10.SetMaximum(1.3)
eff_data_eta_lt10.SetMinimum(0.2)
eff_data_eta_lt10.Draw("ep")

legende=make_legend()
  legende.AddEntry(eff_data_eta_lt10,"26 < p_{T} < 35 GeV","ep")
legende.Draw("same")

c.cd()
pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
pad2.SetTopMargin(0.05);
pad2.SetBottomMargin(0.35);
pad2.SetLeftMargin(0.18);
pad2.SetRightMargin(0.05);
pad2.SetTickx(1)
pad2.SetTicky(1)
pad2.SetGridx()
pad2.SetGridy()
pad2.Draw()
pad2.cd()

sf_eta_lt10.SetLineColor(ROOT.kGreen+1)
sf_eta_lt10.SetMarkerColor(ROOT.kGreen+1)
sf_eta_lt10.SetMarkerStyle(20)
sf_eta_lt10.SetLineWidth(3)

sf_eta_lt10.SetMaximum(1.12)
sf_eta_lt10.SetMinimum(0.78)
sf_eta_lt10.Draw("ep")

c.cd()
pad1.Draw()
ROOT.gPad.RedrawAxis()
c.Modified()
c.SaveAs("plots_el_"+args.year+"/sf_el_eta_"+args.year+"_"+args.discriminant+"_ntrackslt10.png")

