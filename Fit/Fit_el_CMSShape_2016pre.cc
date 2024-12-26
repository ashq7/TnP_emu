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

   //corresponds to executable parameters in do_el*
    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);
    std::string discriminant = *(argv + 5);

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    TFile *fin = TFile::Open(input.c_str(), "READ");

    int nb_pt=6;
    float bins_pt[7]={15,20,35,50,75,100,200};
    TString sbins_pt[7]={"15","20","35","50","75","100","200"};
    //modifying some bin boundaries based on trigger path
    if (discriminant=="HLTEle32"){bins_pt[2]=33; sbins_pt[2]="33";}
    if (discriminant=="HLTEle24Tau30"){bins_pt[1]=25; sbins_pt[1]="25";}
    if (discriminant=="HLTMu8Ele23"){bins_pt[1]=24; sbins_pt[1]="24";}
    if (discriminant=="HLTEle25"){bins_pt[1]=26; sbins_pt[1]="26";}

    int  binnum_pt = sizeof(bins_pt)/sizeof(Float_t) - 1;

    int nb_eta=8;
    float bins_eta[]={-2.5,-2.0,-1.5,-0.8,0.0,0.8,1.5,2.0,2.5};
    int  binnum_eta = sizeof(bins_eta)/sizeof(Float_t) - 1;


    /*int nb_pt=1;
    float bins_pt[2]={50,100};
    TString sbins_pt[2]={"50","100"};
    int  binnum_pt = sizeof(bins_pt)/sizeof(Float_t) - 1;

    int nb_eta=1;
    float bins_eta[]={0.8,1.5};
    int  binnum_eta = sizeof(bins_eta)/sizeof(Float_t) - 1;*/

    TH2F* eff2D = new TH2F("eff","eff",binnum_pt,bins_pt,binnum_eta,bins_eta);

   //j goes through pt bins
    for (int j=0; j<nb_pt; ++j){
       //k goes through eta bins
       for (int k=0; k<nb_eta; ++k){
          TH1F *h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_meta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          TH1F *h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_meta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          if (k==1){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_meta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_meta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          }
          else if (k==2){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_meta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_meta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          }
          else if (k==3){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_metalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_metalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          }
          else if (k==4){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_etalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_etalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
	       }
          else if (k==5){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_eta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_eta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          }
          else if (k==6){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_eta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_eta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          }
          else if (k==7){
             h_pass = (TH1F*) fin->Get("pass_"+discriminant+"_eta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
             h_fail = (TH1F*) fin->Get("fail_"+discriminant+"_eta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]);
          }

          //Mmm: Mass of ___? - maybe holdover from mu mu
          RooRealVar Mmm("Mmm", "Mmm", 65, 115);
          RooDataHist dh_pass("dh_pass", "dh_pass", Mmm, Import(*h_pass));
          RooDataHist dh_fail("dh_fail", "dh_fail", Mmm, Import(*h_fail));

          RooPlot *frame = Mmm.frame(Title("Pass"));
          dh_pass.plotOn(frame);

          //Declaring functions and initial parameter values
          float minmeanP=80;
          float maxmeanP=105;
          float nommeanP1=90;
          float nommeanP2=90;
          if (k==2 && bins_pt[j]==100 and bins_pt[j+1]==200){ nommeanP1=82; }
          RooRealVar mean1P("mean1P", "mean1P", nommeanP1, minmeanP, maxmeanP);
          RooRealVar mean2P("mean2P", "mean2P", nommeanP2, minmeanP, maxmeanP);
          RooRealVar width("width", "width", 2.495,2.495,2.495);
          RooRealVar sigma1P("sigma1P", "sigma1P", 2,0,5);
          RooRealVar sigma2P("sigma2P", "sigma2P", 4,2,10);
          RooVoigtian voigt1P("voigt1P","voigt1P", Mmm, mean1P, width, sigma1P);
          RooVoigtian voigt2P("voigt2P","voigt2P", Mmm, mean2P, width, sigma2P);
          RooRealVar fracSP("fracSP", "fracSP", 0.5,0.0,1.0);
	  RooAddPdf signalP("signalP","signalP", {voigt1P,voigt2P}, fracSP);
          RooRealVar normSP("normSP", "normSP", 100000. ,0.0,100000000.0);
 	  float max3P=1000000.0;
          if (bins_pt[j]>=75 and bins_pt[j]<5000){ max3P=1000.;}
          RooRealVar frac3P("frac3P", "frac3P", 0. ,0.0,max3P);

	  if (bins_pt[j]>=10 and bins_pt[j]<5000){
             RooRealVar lpP("lpP", "lpP", 0.0, -1, 1.1);
             RooExponential expP("expP","expP",Mmm,lpP);
             RooAddPdf modelP("sigmodelP","sigmodelP", {signalP,expP}, {normSP,frac3P});
             modelP.fitTo(dh_pass);
             modelP.plotOn(frame);
             modelP.plotOn(frame,Components("expP"), LineStyle(kDashed));
   	  }
	  else{
             float initial_alphaP=50.0; float initial_betaP=0.01; float initial_gammaP=0.0; float initial_frac3P=1000.0;float max_alphaP=160.0;
	     if (bins_pt[j]==50){ initial_alphaP=90; initial_betaP=0.091; initial_gammaP=0.10; max_alphaP=95.0;}
             if (bins_pt[j]>=20 and bins_pt[j]<30){ initial_alphaP=80; initial_betaP=0.1; initial_gammaP=0.30;}
             if (bins_pt[j]>=20 and bins_pt[j]<30){ initial_frac3P=0;}
             RooRealVar alphaP("alphaP", "alphaP", initial_alphaP, 60.0, max_alphaP);
             RooRealVar betaP("betaP", "betaP", initial_betaP, 0.05, 0.2);
             RooRealVar gammaP("gammaP", "gammaP", initial_gammaP,-1,  2);
             RooRealVar peakP("peakP", "peakP", 90,90,90);
             RooCMSShape expP("expP", "expP", Mmm, alphaP, betaP, gammaP, peakP);
	     RooAddPdf modelP("sigmodelP","sigmodelP", {signalP,expP}, {normSP,frac3P});
             modelP.fitTo(dh_pass);
             modelP.plotOn(frame);
             modelP.plotOn(frame,Components("expP"), LineStyle(kDashed));
 	  }

          RooPlot *frame2 = Mmm.frame(Title("Fail"));
          dh_fail.plotOn(frame2);
          float minmean=80;
          float maxmean=105;
          float nommean1=90;
          float nommean2=90;
          if (k==7 && bins_pt[j]==15 and bins_pt[j+1]==24){ nommean1=93; }
          if (k==4 && bins_pt[j]==35 and bins_pt[j+1]==50){ nommean1=85; }
          if (bins_pt[j]==25 and bins_pt[j+1]==35){ minmean=85; }
          if (bins_pt[j]==100) { minmean=88; maxmean=92;}
          if (bins_pt[j]==50) { nommean1=89; nommean2=100; minmean=85; maxmean=105;}
	  RooRealVar mean1F("mean1F", "mean1F", nommean1, minmean, maxmean);
          RooRealVar mean2F("mean2F", "mean2F", nommean2, minmean, maxmean);
          RooRealVar sigma1F("sigma1F", "sigma1F", 1.0,0,5);
          RooRealVar sigma2F("sigma2F", "sigma2F", 3.5,2,10);
          RooVoigtian voigt1F("voigt1F","voigt1F", Mmm, mean1F, width, sigma1F);
          RooVoigtian voigt2F("voigt2F","voigt2F", Mmm, mean2F, width, sigma2F);
          RooRealVar fracSF("fracSF", "fracSF", 0.5,0.0,1.0);
          RooAddPdf signalF("signalF","signalF", {voigt1F,voigt2F}, fracSF);

          float nom_norm=100000.;
          if (bins_pt[j]==100) { nom_norm=100.0;}
          RooRealVar normSF("normSF", "normSF", nom_norm ,0.0,100000000.0);
          RooRealVar frac3F("frac3F", "frac3F", 0. ,0.0,1000000.0);
          float minalpha=50;
          float maxalpha=160;
          float nomalpha=100;
          float nomgamma=0.01;
          float maxgamma=1.0;
          float nombeta=0.1;
          float maxbeta=0.2;
          if (bins_pt[j]>=50 and bins_pt[j]<100){minalpha=60; maxalpha=110; nomalpha=80;}
          if (bins_pt[j]==25 and bins_pt[j+1]==35){minalpha=60; maxalpha=160; nomalpha=120; nomgamma=0.8;}
          if (bins_pt[j]==50){ nomalpha=90; maxalpha=95.0;}
          if (bins_pt[j]==100){ minalpha=110; nomalpha=125; maxalpha=160.0; nomgamma=1.4; maxgamma=2.0; nombeta=0.3, maxbeta=1.0;}

          if (bins_pt[j]>=10 and bins_pt[j]<5000){
             RooRealVar lpF("lpF", "lpF", -0.1, -1, 1.1);
             RooExponential expF("expF","expF",Mmm,lpF);
             RooAddPdf modelF("sigmodelF","sigmodelF", {signalF,expF}, {normSF,frac3F});
             modelF.fitTo(dh_fail);
             modelF.plotOn(frame2);
             modelF.plotOn(frame2,Components("expF"), LineStyle(kDashed));
	  }
	  else{
             RooRealVar alphaF("alphaF", "alphaF", nomalpha, minalpha, maxalpha);
             RooRealVar betaF("betaF", "betaF", nombeta, 0.05, maxbeta);
             RooRealVar gammaF("gammaF", "gammaF", nomgamma, -2, maxgamma);
             RooRealVar peakF("peakF", "peakF", 90,90,90);
             RooCMSShape expF("expF", "expF", Mmm, alphaF, betaF, gammaF, peakF);
             RooAddPdf modelF("sigmodelF","sigmodelF", {signalF,expF}, {normSF,frac3F});
             modelF.fitTo(dh_fail);
             modelF.plotOn(frame2);
             modelF.plotOn(frame2,Components("expF"), LineStyle(kDashed));
	  }

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
          //frame2->Draw("TEXT45");

          cout<<"signal pass: "<<normSP.getVal()<<endl;
          cout<<"signal fail: "<<normSF.getVal()<<endl;
	  float efficiency=(normSP.getVal())/(normSP.getVal()+normSF.getVal());
          cout<<"efficiency: "<<efficiency<<endl;
	  float err_efficiency=efficiency*(normSP.getError())/(normSP.getVal());
	  cout<<"err efficiency: "<<err_efficiency<<endl;

          TPaveText categ  = TPaveText(0.05, 0.84+0.013, 0.95, 0.84+0.155, "NDC");
          categ.SetBorderSize(   0 );
          categ.SetFillStyle(    0 );
          categ.SetTextAlign(   12 );
          categ.SetTextSize ( 0.035 );
          categ.SetTextColor(    1 );
          categ.SetTextFont (   42 );
	  if (k==4) categ.AddText(sample+", trg: "+discriminant+", 0 < #eta < 0.8, pt: "+sbins_pt[j]+"-"+sbins_pt[j+1]+" GeV");
          if (k==5) categ.AddText(sample+", trg: "+discriminant+", 0.8 < #eta < 1.5, pt: "+sbins_pt[j]+"-"+sbins_pt[j+1]+" GeV");
          if (k==6) categ.AddText(sample+", trg: "+discriminant+", 1.5 < #eta < 2.0, pt: "+sbins_pt[j]+"-"+sbins_pt[j+1]+" GeV");
          if (k==7) categ.AddText(sample+", trg: "+discriminant+", 2.0 < #eta < 2.5, pt: "+sbins_pt[j]+"-"+sbins_pt[j+1]+" GeV");
          if (k==3) categ.AddText(sample+", trg: "+discriminant+", -0.8 < #eta < 0.0, pt: "+sbins_pt[j]+"-"+sbins_pt[j+1]+" GeV");
          if (k==2) categ.AddText(sample+", trg: "+discriminant+", -1.5 < #eta < -0.8, pt: "+sbins_pt[j]+"-"+sbins_pt[j+1]+" GeV");
          if (k==1) categ.AddText(sample+", trg: "+discriminant+", -2.1 < #eta < -1.5, pt: "+sbins_pt[j]+"-"+sbins_pt[j+1]+" GeV");
          if (k==0) categ.AddText(sample+", trg: "+discriminant+", -2.5 < #eta < -2.1, pt: "+sbins_pt[j]+"-"+sbins_pt[j+1]+" GeV");
         
          c->cd();
          categ.Draw("same");
          //categ.Draw("TEXT45");
          //categ.AddText("eff = "+to_string(efficiency));
          //categ.Draw("same");

          if (k==4) c->SaveAs("plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_etalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==5) c->SaveAs("plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_eta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==6) c->SaveAs("plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_eta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==7) c->SaveAs("plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_eta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==3) c->SaveAs("plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_metalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==2) c->SaveAs("plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_meta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==1) c->SaveAs("plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_meta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");
          else if (k==0) c->SaveAs("plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_meta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png");

          if (k==4) cout<<"plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_etalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png"<<endl;
          if (k==5) cout<<"plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_eta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png"<<endl;
          if (k==6) cout<<"plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_eta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png"<<endl;
          if (k==7) cout<<"plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_eta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png"<<endl;
          if (k==3) cout<<"plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_metalt0p8_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png"<<endl;
          if (k==2) cout<<"plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_meta0p8to1p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png"<<endl;
          if (k==1) cout<<"plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_meta1p5to2p0_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png"<<endl;
          if (k==0) cout<<"plots_el_"+year+"/fits_"+sample+"_"+discriminant+"_meta2p0to2p5_pt"+sbins_pt[j]+"to"+sbins_pt[j+1]+".png"<<endl;

	  eff2D->SetBinContent(j+1,k+1,efficiency);
          eff2D->SetBinError(j+1,k+1,err_efficiency);
       }
    }

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    eff2D->Write();
    fout->Close();
} 


