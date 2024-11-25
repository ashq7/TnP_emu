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

file_data=ROOT.TFile("output_el_"+args.year+"/output_Data_"+args.year+"_"+args.discriminant+".root","r")
file_mc=ROOT.TFile("output_el_"+args.year+"/output_DY_"+args.year+"_"+args.discriminant+".root","r")
file_embedded=ROOT.TFile("output_el_"+args.year+"/output_Embedded_"+args.year+"_"+args.discriminant+".root","r")

eff2D_data=file_data.Get("eff")
eff2D_mc=file_mc.Get("eff")
eff2D_embedded=file_embedded.Get("eff")

file_out=ROOT.TFile("sf_el_"+args.year+"_"+args.discriminant+".root","recreate")
file_out.cd()

#create SF2D for Monte Carlo
sf2D_mc=eff2D_data.Clone()
sf2D_mc.Divide(eff2D_mc)
sf2D_mc.SetName("SF2D_mc")
sf2D_mc.SetTitle("SF2D_mc_"+args.discriminant)
sf2D_mc.GetXaxis().SetTitle("p_{T} (GeV)")
sf2D_mc.GetYaxis().SetTitle("\eta")
sf2D_mc.Write()

#create SF2D for embedded
sf2D_embedded=eff2D_data.Clone()
sf2D_embedded.Divide(eff2D_embedded)
sf2D_embedded.SetName("SF2D_embedded")
sf2D_embedded.SetTitle("SF2D_embedded"+args.discriminant)
sf2D_embedded.GetXaxis().SetTitle("p_{T} (GeV)")
sf2D_embedded.GetYaxis().SetTitle("\eta")
sf2D_embedded.Write()

#Create eff2D for data, MC, embedded
eff2D_data.SetName("eff_data")
eff2D_data.SetTitle("eff_data_"+args.discriminant)
eff2D_data.GetXaxis().SetTitle("p_{T} (GeV)")
eff2D_data.GetYaxis().SetTitle("\eta")
eff2D_mc.SetName("eff_mc")
eff2D_mc.SetTitle("eff_mc_"+args.discriminant)
eff2D_mc.GetXaxis().SetTitle("p_{T} (GeV)")
eff2D_mc.GetYaxis().SetTitle("\eta")
eff2D_embedded.SetName("eff_embedded")
eff2D_embedded.SetTitle("eff_embedded_"+args.discriminant)
eff2D_embedded.GetXaxis().SetTitle("p_{T} (GeV)")
eff2D_embedded.GetYaxis().SetTitle("\eta")
eff2D_data.Write()
eff2D_mc.Write()
eff2D_embedded.Write()

#bins_pt=[15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,35,40,50,60,70,80,90,100,120,150]
#nb_bins=27

bins_pt=[15,20,35,50,75,100,200]
nb_bins=6

bins_eta=[-2.5,-2.0,-1.5,-0.8,0.0,0.8,1.5,2.0,2.5]
nb_bins_eta=8

if args.discriminant=="HLTEle32": bins_pt[2]=33
if args.discriminant=="HLTEle24Tau30": bins_pt[1]=25
if args.discriminant=="HLTMu8Ele23": bins_pt[1]=24
if args.discriminant=="HLTEle25": bins_pt[1]=26

eff_data=[]
sf=[]

eff_data_eta=[]
sf_eta=[]

for i in range(0,8):

   eff1D_data_eta=ROOT.TH1F("eff1_data_eta","eff1D_data_eta",nb_bins_eta,array('d',bins_eta))
   eff1D_mc_eta=ROOT.TH1F("eff1_mc_eta","eff1D_mc_eta",nb_bins_eta,array('d',bins_eta))

   for k in range(0,nb_bins_eta):
      eff1D_data_eta.SetBinContent(k+1,eff2D_data.GetBinContent(i+1,k+1))
      eff1D_mc_eta.SetBinContent(k+1,eff2D_mc.GetBinContent(i+1,k+1))
      eff1D_data_eta.SetBinError(k+1,eff2D_data.GetBinError(i+1,k+1))
      eff1D_mc_eta.SetBinError(k+1,eff2D_mc.GetBinError(i+1,k+1))

   eff1D_mc_eta.GetXaxis().SetTitle("")
   eff1D_mc_eta.GetXaxis().SetTitleSize(0)
   eff1D_mc_eta.GetXaxis().SetNdivisions(505)
   eff1D_mc_eta.GetYaxis().SetLabelFont(42)
   eff1D_mc_eta.GetYaxis().SetLabelOffset(0.01)
   eff1D_mc_eta.GetYaxis().SetLabelSize(0.06)
   eff1D_mc_eta.GetYaxis().SetTitleSize(0.075)
   eff1D_mc_eta.GetYaxis().SetTitleOffset(1.04)
   eff1D_mc_eta.SetTitle("")
   eff1D_mc_eta.GetYaxis().SetTitle("Events/bin")
   eff1D_mc_eta.SetLineColor(1)
   eff1D_mc_eta.SetLineWidth(3)

   eff1D_data_eta.SetLineColor(2)
   eff1D_data_eta.SetLineWidth(3)

   eff_data_eta.append(eff1D_data_eta.Clone())

   ratio_eta=eff1D_data_eta.Clone()
   ratio_eta.Sumw2()
   ratio_eta.Divide(eff1D_mc_eta)

   ratio_eta.SetTitle("")
   ratio_eta.GetXaxis().SetTitle("Supercluster #eta")
   ratio_eta.GetYaxis().SetTitle("SF")
   ratio_eta.GetXaxis().SetNdivisions(515)
   ratio_eta.GetYaxis().SetNdivisions(505)
   ratio_eta.GetXaxis().SetTitleSize(0.15)
   ratio_eta.GetYaxis().SetTitleSize(0.15)
   ratio_eta.GetYaxis().SetTitleOffset(0.56)
   ratio_eta.GetXaxis().SetTitleOffset(1.04)
   ratio_eta.GetXaxis().SetLabelSize(0.11)
   ratio_eta.GetYaxis().SetLabelSize(0.11)
   ratio_eta.GetXaxis().SetTitleFont(42)
   ratio_eta.GetYaxis().SetTitleFont(42)
   ratio_eta.SetMinimum(0.78)
   ratio_eta.SetMaximum(1.12)
   sf_eta.append(ratio_eta.Clone())

for i in range(0,8):
   
   eff1D_data=ROOT.TH1F("eff1_data","eff1D_data",nb_bins,array('d',bins_pt))
   eff1D_mc=ROOT.TH1F("eff1_mc","eff1D_mc",nb_bins,array('d',bins_pt))

   for k in range(0,nb_bins):
      eff1D_data.SetBinContent(k+1,eff2D_data.GetBinContent(k+1,i+1))
      eff1D_mc.SetBinContent(k+1,eff2D_mc.GetBinContent(k+1,i+1))
      eff1D_data.SetBinError(k+1,eff2D_data.GetBinError(k+1,i+1))
      eff1D_mc.SetBinError(k+1,eff2D_mc.GetBinError(k+1,i+1))

   eff1D_mc.GetXaxis().SetTitle("")
   eff1D_mc.GetXaxis().SetTitleSize(0)
   eff1D_mc.GetXaxis().SetNdivisions(505)
   eff1D_mc.GetYaxis().SetLabelFont(42)
   eff1D_mc.GetYaxis().SetLabelOffset(0.01)
   eff1D_mc.GetYaxis().SetLabelSize(0.06)
   eff1D_mc.GetYaxis().SetTitleSize(0.075)
   eff1D_mc.GetYaxis().SetTitleOffset(1.04)
   eff1D_mc.SetTitle("")
   eff1D_mc.GetYaxis().SetTitle("Events/bin")
   eff1D_mc.SetLineColor(1)
   eff1D_mc.SetLineWidth(3)

   eff1D_data.SetLineColor(2)
   eff1D_data.SetLineWidth(3)

   eff_data.append(eff1D_data.Clone())

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
   pad1.SetLogx()

   eff1D_mc.SetMinimum(0.2)
   eff1D_mc.SetMaximum(1.2)
   eff1D_mc.Draw("hist")
   eff1D_data.Draw("histsame")

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
   pad2.SetLogx()
   pad2.cd()

   ratio=eff1D_data.Clone()
   ratio.Sumw2()
   ratio.Divide(eff1D_mc)

   ratio.SetTitle("")
   ratio.GetXaxis().SetTitle("p_{T} (GeV)")
   ratio.GetYaxis().SetTitle("SF")
   ratio.GetXaxis().SetNdivisions(515)
   ratio.GetYaxis().SetNdivisions(505)
   ratio.GetXaxis().SetTitleSize(0.15)
   ratio.GetYaxis().SetTitleSize(0.15)
   ratio.GetYaxis().SetTitleOffset(0.56)
   ratio.GetXaxis().SetTitleOffset(1.04)
   ratio.GetXaxis().SetLabelSize(0.11)
   ratio.GetYaxis().SetLabelSize(0.11)
   ratio.GetXaxis().SetTitleFont(42)
   ratio.GetYaxis().SetTitleFont(42)
   ratio.SetMinimum(0.78)
   ratio.SetMaximum(1.12)

   ratio.Draw("hist")
   ratio.Draw("esame")
   
   sf.append(ratio.Clone())

   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("plots_el_"+args.year+"/sf_el_"+args.year+"_"+args.discriminant+"_etabin"+str(i)+".png")


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
pad1.SetLogx()

eff_data[0].Add(eff_data[7])
eff_data[1].Add(eff_data[6])
eff_data[2].Add(eff_data[5])
eff_data[3].Add(eff_data[4])
eff_data[0].Scale(0.5)
eff_data[1].Scale(0.5)
eff_data[2].Scale(0.5)
eff_data[3].Scale(0.5)
eff_data[3].SetLineColor(ROOT.kBlack)
eff_data[3].SetMarkerColor(ROOT.kBlack)
eff_data[3].SetMarkerStyle(20)
eff_data[3].SetLineWidth(3)
eff_data[2].SetLineColor(ROOT.kGray+1)
eff_data[2].SetMarkerColor(ROOT.kGray+1)
eff_data[2].SetMarkerStyle(20)
eff_data[2].SetLineWidth(3)
eff_data[1].SetLineColor(ROOT.kRed+1)
eff_data[1].SetMarkerColor(ROOT.kRed+1)
eff_data[1].SetMarkerStyle(20)
eff_data[1].SetLineWidth(3)
eff_data[0].SetLineColor(ROOT.kRed-2)
eff_data[0].SetMarkerColor(ROOT.kRed-2)
eff_data[0].SetMarkerStyle(20)
eff_data[0].SetLineWidth(3)

eff_data[0].SetTitle("")
eff_data[0].GetXaxis().SetTitleSize(0.0)
eff_data[0].GetYaxis().SetTitle("Data efficiency")
eff_data[0].GetYaxis().SetTitleSize(0.06)
eff_data[0].GetXaxis().SetLabelSize(0.0)
eff_data[0].SetMaximum(1.3)
eff_data[0].SetMinimum(0.2)
eff_data[0].Draw("ep")
eff_data[1].Draw("epsame")
eff_data[2].Draw("epsame")
eff_data[3].Draw("epsame")
eff_data[0].Draw("epsame")

legende=make_legend()
legende.AddEntry(eff_data[3],"0.000 < |#eta| < 0.800","ep")
legende.AddEntry(eff_data[2],"0.800 < |#eta| < 1.444","ep")
legende.AddEntry(eff_data[1],"1.566 < |#eta| < 2.000","ep")
legende.AddEntry(eff_data[0],"2.000 < |#eta| < 2.500","ep")
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
pad2.SetLogx()
pad2.cd()

sf[3].Add(sf[4])
sf[2].Add(sf[5])
sf[1].Add(sf[6])
sf[0].Add(sf[7])
sf[0].Scale(0.5)
sf[1].Scale(0.5)
sf[2].Scale(0.5)
sf[3].Scale(0.5)
sf[3].SetLineColor(ROOT.kBlack)
sf[3].SetMarkerColor(ROOT.kBlack)
sf[3].SetMarkerStyle(20)
sf[3].SetLineWidth(3)
sf[2].SetLineColor(ROOT.kGray+1)
sf[2].SetMarkerColor(ROOT.kGray+1)
sf[2].SetMarkerStyle(20)
sf[2].SetLineWidth(3)
sf[1].SetLineColor(ROOT.kRed+1)
sf[1].SetMarkerColor(ROOT.kRed+1)
sf[1].SetMarkerStyle(20)
sf[1].SetLineWidth(3)
sf[0].SetLineColor(ROOT.kRed-2)
sf[0].SetMarkerColor(ROOT.kRed-2)
sf[0].SetMarkerStyle(20)
sf[0].SetLineWidth(3)

sf[3].SetMaximum(1.12)
sf[3].SetMinimum(0.78)
sf[3].Draw("ep")
sf[1].Draw("epsame")
sf[2].Draw("epsame")
sf[3].Draw("epsame")
sf[0].Draw("epsame")

c.cd()
pad1.Draw()
ROOT.gPad.RedrawAxis()
c.Modified()
c.SaveAs("plots_el_"+args.year+"/sf_el_"+args.year+"_"+args.discriminant+".png")



########################################
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

eff_data_eta[5].SetLineColor(ROOT.kGreen+1)
eff_data_eta[5].SetMarkerColor(ROOT.kGreen+1)
eff_data_eta[5].SetMarkerStyle(20)
eff_data_eta[5].SetLineWidth(3)
eff_data_eta[4].SetLineColor(ROOT.kOrange+1)
eff_data_eta[4].SetMarkerColor(ROOT.kOrange+1)
eff_data_eta[4].SetMarkerStyle(20)
eff_data_eta[4].SetLineWidth(3)
eff_data_eta[3].SetLineColor(ROOT.kBlack)
eff_data_eta[3].SetMarkerColor(ROOT.kBlack)
eff_data_eta[3].SetMarkerStyle(20)
eff_data_eta[3].SetLineWidth(3)
eff_data_eta[2].SetLineColor(ROOT.kGray+1)
eff_data_eta[2].SetMarkerColor(ROOT.kGray+1)
eff_data_eta[2].SetMarkerStyle(20)
eff_data_eta[2].SetLineWidth(3)
eff_data_eta[1].SetLineColor(ROOT.kRed+1)
eff_data_eta[1].SetMarkerColor(ROOT.kRed+1)
eff_data_eta[1].SetMarkerStyle(20)
eff_data_eta[1].SetLineWidth(3)
eff_data_eta[0].SetLineColor(ROOT.kRed-2)
eff_data_eta[0].SetMarkerColor(ROOT.kRed-2)
eff_data_eta[0].SetMarkerStyle(20)
eff_data_eta[0].SetLineWidth(3)

eff_data_eta[2].SetTitle("")
eff_data_eta[2].GetXaxis().SetTitleSize(0.0)
eff_data_eta[2].GetYaxis().SetTitle("Data efficiency")
eff_data_eta[2].GetYaxis().SetTitleSize(0.06)
eff_data_eta[2].GetXaxis().SetLabelSize(0.0)
eff_data_eta[2].SetMaximum(1.3)
eff_data_eta[2].SetMinimum(0.2)
eff_data_eta[2].Draw("ep")
if args.discriminant=="HLTEle25" or args.discriminant=="HLTEle24Tau30" or args.discriminant=="HLTMu8Ele23" or args.discriminant=="HLTMu23Ele12" or args.discriminant=="MVAisoWP80":
   eff_data_eta[1].Draw("epsame")
if args.discriminant=="HLTMu23Ele12" or args.discriminant=="MVAisoWP80":
   eff_data_eta[0].Draw("epsame")
eff_data_eta[3].Draw("epsame")
eff_data_eta[4].Draw("epsame")
eff_data_eta[5].Draw("epsame")
eff_data_eta[2].Draw("epsame")

file_out.cd()
eff_data_eta[0].SetName("eff_eta_pt15to20")
eff_data_eta[1].SetName("eff_eta_pt20to35")
eff_data_eta[2].SetName("eff_eta_pt35to50")
eff_data_eta[3].SetName("eff_eta_pt50to75")
eff_data_eta[4].SetName("eff_eta_pt75to100")
eff_data_eta[5].SetName("eff_eta_pt100to200")
eff_data_eta[0].Write()
eff_data_eta[1].Write()
eff_data_eta[2].Write()
eff_data_eta[3].Write()
eff_data_eta[4].Write()
eff_data_eta[5].Write()


legende=make_legend()
if args.discriminant=="HLTEle25":
  legende.AddEntry(eff_data_eta[1],"26 < p_{T} < 35 GeV","ep")
  legende.AddEntry(eff_data_eta[2],"35 < p_{T} < 50 GeV","ep")
if args.discriminant=="HLTEle24Tau30":
  legende.AddEntry(eff_data_eta[1],"25 < p_{T} < 35 GeV","ep")
  legende.AddEntry(eff_data_eta[2],"35 < p_{T} < 50 GeV","ep")
if args.discriminant=="HLTMu8Ele23":
  legende.AddEntry(eff_data_eta[1],"24 < p_{T} < 35 GeV","ep")
  legende.AddEntry(eff_data_eta[2],"35 < p_{T} < 50 GeV","ep")
if args.discriminant=="HLTMu23Ele12" or args.discriminant=="MVAisoWP80":
  legende.AddEntry(eff_data_eta[0],"15 < p_{T} < 20 GeV","ep")
  legende.AddEntry(eff_data_eta[1],"20 < p_{T} < 35 GeV","ep")
  legende.AddEntry(eff_data_eta[2],"35 < p_{T} < 50 GeV","ep")
if args.discriminant=="HLTEle32": 
  legende.AddEntry(eff_data_eta[2],"33 < p_{T} < 50 GeV","ep")
legende.AddEntry(eff_data_eta[3],"50 < p_{T} < 75 GeV","ep")
legende.AddEntry(eff_data_eta[4],"75 < p_{T} < 100 GeV","ep")
legende.AddEntry(eff_data_eta[5],"100 < p_{T} < 200 GeV","ep")
legende.Draw("same")

bins_pt=[15,20,35,50,75,100,200]
if args.discriminant=="HLTEle32": bins_pt[2]=33
if args.discriminant=="HLTEle24Tau30": bins_pt[1]=25
if args.discriminant=="HLTMu8Ele23": bins_pt[1]=24
if args.discriminant=="HLTEle25": bins_pt[1]=26


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

sf_eta[5].SetLineColor(ROOT.kGreen+1)
sf_eta[5].SetMarkerColor(ROOT.kGreen+1)
sf_eta[5].SetMarkerStyle(20)
sf_eta[5].SetLineWidth(3)
sf_eta[4].SetLineColor(ROOT.kOrange+1)
sf_eta[4].SetMarkerColor(ROOT.kOrange+1)
sf_eta[4].SetMarkerStyle(20)
sf_eta[4].SetLineWidth(3)
sf_eta[3].SetLineColor(ROOT.kBlack)
sf_eta[3].SetMarkerColor(ROOT.kBlack)
sf_eta[3].SetMarkerStyle(20)
sf_eta[3].SetLineWidth(3)
sf_eta[2].SetLineColor(ROOT.kGray+1)
sf_eta[2].SetMarkerColor(ROOT.kGray+1)
sf_eta[2].SetMarkerStyle(20)
sf_eta[2].SetLineWidth(3)
sf_eta[1].SetLineColor(ROOT.kRed+1)
sf_eta[1].SetMarkerColor(ROOT.kRed+1)
sf_eta[1].SetMarkerStyle(20)
sf_eta[1].SetLineWidth(3)
sf_eta[0].SetLineColor(ROOT.kRed-2)
sf_eta[0].SetMarkerColor(ROOT.kRed-2)
sf_eta[0].SetMarkerStyle(20)
sf_eta[0].SetLineWidth(3)

file_out.cd()
sf_eta[0].SetName("sf_eta_pt15to20")
sf_eta[1].SetName("sf_eta_pt20to35")
sf_eta[2].SetName("sf_eta_pt35to50")
sf_eta[3].SetName("sf_eta_pt50to75")
sf_eta[4].SetName("sf_eta_pt75to100")
sf_eta[5].SetName("sf_eta_pt100to200")
sf_eta[0].Write()
sf_eta[1].Write()
sf_eta[2].Write()
sf_eta[3].Write()
sf_eta[4].Write()
sf_eta[5].Write()

sf_eta[3].SetMaximum(1.12)
sf_eta[3].SetMinimum(0.78)
sf_eta[3].Draw("ep")
sf_eta[5].Draw("epsame")
sf_eta[4].Draw("epsame")
if args.discriminant=="HLTEle25" or args.discriminant=="HLTEle24Tau30" or args.discriminant=="HLTMu8Ele23" or args.discriminant=="HLTMu23Ele12" or args.discriminant=="MVAisoWP80":
   sf_eta[1].Draw("epsame")
if args.discriminant=="HLTMu23Ele12" or args.discriminant=="MVAisoWP80":
   sf_eta[0].Draw("epsame")
sf_eta[2].Draw("epsame")
sf_eta[3].Draw("epsame")

c.cd()
pad1.Draw()
ROOT.gPad.RedrawAxis()
c.Modified()
c.SaveAs("plots_el_"+args.year+"/sf_el_eta_"+args.year+"_"+args.discriminant+".png")

