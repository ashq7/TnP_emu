#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFile.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooVoigtian.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include "RooCMSShape.h"

using namespace RooFit;

using namespace std;

int main(int argc, char** argv) {


    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);
    std::string discriminant = *(argv + 5);

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    TFile *fin = TFile::Open(input.c_str(), "READ");

    /*int nb_pt=27;
    float bins_pt[28]={15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,35,40,50,60,70,80,90,100,120,150};
    TString sbins_pt[28]={"15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","35","40","50","60","70","80","90","100","120","150"};*/
    int nb_pt=6;
    float bins_pt[7]={10,20,35,50,100,200,500};
    TString sbins_pt[7]={"10","20","35","50","100","200","500"};

    int  binnum_pt = sizeof(bins_pt)/sizeof(Float_t) - 1;

    int nb_eta=4;
    float bins_eta[]={0.0,0.8,1.5,2.0,2.5};
    int  binnum_eta = sizeof(bins_eta)/sizeof(Float_t) - 1;

    TH2F* eff2D = new TH2F("eff","eff",binnum_pt,bins_pt,binnum_eta,bins_eta);

    for (int j=0; j<nb_pt; ++j){
       for (int k=0; k<nb_eta; ++k){
          TH1F *h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_etalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          TH1F *h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_etalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
	  if (k==1){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_eta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_eta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
	  }
          else if (k==2){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_eta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_eta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          }
          else if (k==3){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_eta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_eta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          }

          RooRealVar Mmm("Mmm", "Mmm", 65, 115);
          RooDataHist dh_pass("dh_pass", "dh_pass", Mmm, Import(*h_pass));
          RooDataHist dh_fail("dh_fail", "dh_fail", Mmm, Import(*h_fail));

          RooPlot *frame = Mmm.frame(Title("Pass"));
          dh_pass.plotOn(frame);
          RooRealVar mean1P("mean1P", "mean1P", 90, 80, 100);
          RooRealVar mean2P("mean2P", "mean2P", 90, 80, 100);
          RooRealVar width("width", "width", 2.495,2.495,2.495);
          RooRealVar sigma1P("sigma1P", "sigma1P", 2,0,5);
          RooRealVar sigma2P("sigma2P", "sigma2P", 4,2,10);
          RooVoigtian voigt1P("voigt1P","voigt1P", Mmm, mean1P, width, sigma1P);
          RooVoigtian voigt2P("voigt2P","voigt2P", Mmm, mean2P, width, sigma2P);

          RooRealVar lpP("lpP", "lpP", -0.1, -1, 1.1);
          RooExponential expP("expP","expP",Mmm,lpP);
          //RooRealVar alphaP("alphaP", "alphaP", 60.0, 50.0, 80.0);
          //RooRealVar betaP("betaP", "betaP", 0.05, 0.01, 0.08);
          //RooRealVar gammaP("gammaP", "gammaP", 0.01, 0, 1);
          //RooRealVar peakP("peakP", "peakP", 90,90,90);
          //RooCMSShape expP("expP", "expP", Mmm, alphaP, betaP, gammaP, peakP);

          RooRealVar frac1P("frac1P", "frac1P", 1000000,0.0,10000000.0);
          RooRealVar frac2P("frac2P", "frac2P", 1000000,0.0,10000000.0);
          RooRealVar frac3P("frac3P", "frac3P", 1000,0.0,1000000.0);
          RooAddPdf modelP("sigmodelP","sigmodelP", {voigt1P,voigt2P,expP}, {frac1P,frac2P,frac3P});
          modelP.fitTo(dh_pass);
          modelP.plotOn(frame);
          modelP.plotOn(frame,Components("expP"), LineStyle(kDashed));

          RooPlot *frame2 = Mmm.frame(Title("Fail"));
          dh_fail.plotOn(frame2);
          RooRealVar mean1F("mean1F", "mean1F", 90, 80, 100);
          RooRealVar mean2F("mean2F", "mean2F", 85, 80, 90);
          RooRealVar sigma1F("sigma1F", "sigma1F", 2,0,5);
          RooRealVar sigma2F("sigma2F", "sigma2F", 4,2,10);
          RooVoigtian voigt1F("voigt1F","voigt1F", Mmm, mean1F, width, sigma1F);
          RooVoigtian voigt2F("voigt2F","voigt2F", Mmm, mean2F, width, sigma2F);

          RooRealVar lpF("lpF", "lpF", -0.1, -1, 1.1);
          RooExponential expF("expF","expF",Mmm,lpF);
          //RooRealVar alphaF("alphaF", "alphaF", alphaP.getVal(), 50.0, 80.0);
          //RooRealVar betaF("betaF", "betaF", betaP.getVal(), 0.01, 0.08);
          //RooRealVar gammaF("gammaF", "gammaF", gammaP.getVal(), 0, 1);
          //RooRealVar peakF("peakF", "peakF", 90,90,90);
          //RooCMSShape expF("expF", "expF", Mmm, alphaF, betaF, gammaF, peakF);

          RooRealVar frac1F("frac1F", "frac1F", 1000000,0.0,10000000.0);
          RooRealVar frac2F("frac2F", "frac2F", 1000000,0.0,10000000.0);
          RooRealVar frac3F("frac3F", "frac3F", 1000,0.0,1000000.0);
          RooAddPdf modelF("sigmodelF","sigmodelF", {voigt1F,voigt2F,expF}, {frac1F,frac2F,frac3F});
          modelF.fitTo(dh_fail);
          modelF.plotOn(frame2);
          modelF.plotOn(frame2,Components("expF"), LineStyle(kDashed));

          TCanvas *c = new TCanvas("rf102_dataimport", "rf102_dataimport", 1000, 800);
          c->Divide(2,1);
          c->cd(1);
          gPad->SetLeftMargin(0.15);
          frame->GetYaxis()->SetTitleOffset(1.4);
          frame->Draw();
          c->cd(2);
          gPad->SetLeftMargin(0.15);
          frame2->GetYaxis()->SetTitleOffset(1.4);
          frame2->Draw();

          cout<<"signal pass: "<<frac1P.getVal()+frac2P.getVal()<<endl;
          cout<<"signal fail: "<<frac1F.getVal()+frac2F.getVal()<<endl;
	  float efficiency=(frac1P.getVal()+frac2P.getVal())/(frac1P.getVal()+frac2P.getVal()+frac1F.getVal()+frac2F.getVal());
          cout<<"efficiency: "<<efficiency<<endl;
	  float err_efficiency=efficiency*(frac1P.getError()+frac2P.getError())/(frac1P.getVal()+frac2P.getVal());

          TPaveText categ  = TPaveText(0.35, 0.5+0.013, 0.83, 0.50+0.155, "NDC");
          categ.SetBorderSize(   0 );
          categ.SetFillStyle(    0 );
          categ.SetTextAlign(   12 );
          categ.SetTextSize ( 0.05 );
          categ.SetTextColor(    1 );
          categ.SetTextFont (   42 );
          //categ.AddText("eff = "+to_string(efficiency));
  	  //categ.Draw("same");

          if (k==0) c->SaveAs("plots_el_2018/fits_"+sample+"_"+discriminant+"_etalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==1) c->SaveAs("plots_el_2018/fits_"+sample+"_"+discriminant+"_eta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==2) c->SaveAs("plots_el_2018/fits_"+sample+"_"+discriminant+"_eta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==3) c->SaveAs("plots_el_2018/fits_"+sample+"_"+discriminant+"_eta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");


	  eff2D->SetBinContent(j+1,k+1,efficiency);
          eff2D->SetBinError(j+1,k+1,err_efficiency);
       }
    }

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    eff2D->Write();
    fout->Close();
} 


