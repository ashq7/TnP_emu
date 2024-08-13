#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "TTree.h"
#include "tr_Tree.h"

using namespace std;

int main(int argc, char** argv) {


    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);
    std::string discriminant = *(argv + 5);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("demo/tree");


    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("tag_pt", &tag_pt);
    arbre->SetBranchAddress("tag_eta", &tag_eta);
    arbre->SetBranchAddress("tag_sceta", &tag_sceta);
    arbre->SetBranchAddress("tag_phi", &tag_phi);
    arbre->SetBranchAddress("tag_dxy", &tag_dxy);
    arbre->SetBranchAddress("tag_dz", &tag_dz);
    arbre->SetBranchAddress("tag_matchedToL1Tau", &tag_matchedToL1Tau);
    arbre->SetBranchAddress("probe_pt", &probe_pt);
    arbre->SetBranchAddress("probe_eta", &probe_eta);
    arbre->SetBranchAddress("probe_sceta", &probe_sceta);
    arbre->SetBranchAddress("probe_phi", &probe_phi);
    arbre->SetBranchAddress("probe_dxy", &probe_dxy);
    arbre->SetBranchAddress("probe_dz", &probe_dz);
    arbre->SetBranchAddress("probe_MVAisoWP90", &probe_MVAisoWP90);
    arbre->SetBranchAddress("probe_MVAisoWP80", &probe_MVAisoWP80);
    arbre->SetBranchAddress("probe_MVAisoWPLoose", &probe_MVAisoWPLoose);
    arbre->SetBranchAddress("probe_MVAnoIsoWP90", &probe_MVAnoIsoWP90);
    arbre->SetBranchAddress("probe_MVAnoIsoWP80", &probe_MVAnoIsoWP80);
    arbre->SetBranchAddress("probe_MVAnoIsoWPLoose", &probe_MVAnoIsoWPLoose);
    arbre->SetBranchAddress("probe_matchHLTEle25", &probe_matchHLTEle25);
    arbre->SetBranchAddress("probe_matchHLTEle27", &probe_matchHLTEle27);
    arbre->SetBranchAddress("probe_matchHLTEle32", &probe_matchHLTEle32);
    arbre->SetBranchAddress("probe_matchHLTEle35", &probe_matchHLTEle35);
    arbre->SetBranchAddress("probe_matchHLTEle24Tau30", &probe_matchHLTEle24Tau30);
    arbre->SetBranchAddress("probe_matchHLTMu23Ele12", &probe_matchHLTMu23Ele12);
    arbre->SetBranchAddress("probe_matchHLTMu8Ele23", &probe_matchHLTMu8Ele23);
    arbre->SetBranchAddress("trueNumInteractions", &trueNumInteractions);
    arbre->SetBranchAddress("puNumInteractions", &puNumInteractions);
    arbre->SetBranchAddress("ntracks", &ntracks);

   /*int nb_pt=27;
   float bins_pt[28]={15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,35,40,50,60,70,80,90,100,120,150};
   TString sbins_pt[28]={"15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","35","40","50","60","70","80","90","100","120","150"};*/

   int nb_pt=7;
   float bins_pt[8]={15,20,35,50,75,100,200,500};
   TString sbins_pt[8]={"15","20","35","50","75","100","200","500"};
   if (discriminant=="HLTEle32"){bins_pt[2]=33; sbins_pt[2]="33";}
   if (discriminant=="HLTEle24Tau30"){bins_pt[1]=25; sbins_pt[1]="25";}
   if (discriminant=="HLTMu8Ele23"){bins_pt[1]=24; sbins_pt[1]="24";}
   if (discriminant=="HLTEle25"){bins_pt[1]=26; sbins_pt[1]="26";}

   std::vector<TH1F*> hpass_etalt0p8;
   std::vector<TH1F*> hfail_etalt0p8;
   std::vector<TH1F*> hpass_eta0p8to1p5;
   std::vector<TH1F*> hfail_eta0p8to1p5;
   std::vector<TH1F*> hpass_eta1p5to2p0;
   std::vector<TH1F*> hfail_eta1p5to2p0;
   std::vector<TH1F*> hpass_eta2p0to2p5;
   std::vector<TH1F*> hfail_eta2p0to2p5;
   std::vector<TH1F*> hpass_metalt0p8;
   std::vector<TH1F*> hfail_metalt0p8;
   std::vector<TH1F*> hpass_meta0p8to1p5;
   std::vector<TH1F*> hfail_meta0p8to1p5;
   std::vector<TH1F*> hpass_meta1p5to2p0;
   std::vector<TH1F*> hfail_meta1p5to2p0;
   std::vector<TH1F*> hpass_meta2p0to2p5;
   std::vector<TH1F*> hfail_meta2p0to2p5;
   for (int k=0; k<nb_pt; ++k){
        ostringstream HN0; HN0 << "h0" << k;
        hpass_etalt0p8.push_back(new TH1F (HN0.str().c_str(),"InvMa",60,60,120)); hpass_etalt0p8[k]->Sumw2();
        ostringstream HN1; HN1 << "h1" << k;
        hpass_eta0p8to1p5.push_back(new TH1F (HN1.str().c_str(),"InvMa",60,60,120)); hpass_eta0p8to1p5[k]->Sumw2();
        ostringstream HN2; HN2 << "h2" << k;
        hpass_eta1p5to2p0.push_back(new TH1F (HN2.str().c_str(),"InvMa",60,60,120)); hpass_eta1p5to2p0[k]->Sumw2();
        ostringstream HN3; HN3 << "h3" << k;
        hpass_eta2p0to2p5.push_back(new TH1F (HN3.str().c_str(),"InvMa",60,60,120)); hpass_eta2p0to2p5[k]->Sumw2();

        ostringstream HNF0; HNF0 << "hf0" << k;
        hfail_etalt0p8.push_back(new TH1F (HNF0.str().c_str(),"InvMa",60,60,120)); hfail_etalt0p8[k]->Sumw2();
        ostringstream HNF1; HNF1 << "hf1" << k;
        hfail_eta0p8to1p5.push_back(new TH1F (HNF1.str().c_str(),"InvMa",60,60,120)); hfail_eta0p8to1p5[k]->Sumw2();
        ostringstream HNF2; HNF2 << "hf2" << k;
        hfail_eta1p5to2p0.push_back(new TH1F (HNF2.str().c_str(),"InvMa",60,60,120)); hfail_eta1p5to2p0[k]->Sumw2();
        ostringstream HNF3; HNF3 << "hf3" << k;
        hfail_eta2p0to2p5.push_back(new TH1F (HNF3.str().c_str(),"InvMa",60,60,120)); hfail_eta2p0to2p5[k]->Sumw2();

        ostringstream HM0; HM0 << "hm0" << k;
        hpass_metalt0p8.push_back(new TH1F (HM0.str().c_str(),"InvMa",60,60,120)); hpass_metalt0p8[k]->Sumw2();
        ostringstream HM1; HM1 << "hm1" << k;
        hpass_meta0p8to1p5.push_back(new TH1F (HM1.str().c_str(),"InvMa",60,60,120)); hpass_meta0p8to1p5[k]->Sumw2();
        ostringstream HM2; HM2 << "hm2" << k;
        hpass_meta1p5to2p0.push_back(new TH1F (HM2.str().c_str(),"InvMa",60,60,120)); hpass_meta1p5to2p0[k]->Sumw2();
        ostringstream HM3; HM3 << "hm3" << k;
        hpass_meta2p0to2p5.push_back(new TH1F (HM3.str().c_str(),"InvMa",60,60,120)); hpass_meta2p0to2p5[k]->Sumw2();

        ostringstream HMF0; HMF0 << "hmf0" << k;
        hfail_metalt0p8.push_back(new TH1F (HMF0.str().c_str(),"InvMa",60,60,120)); hfail_metalt0p8[k]->Sumw2();
        ostringstream HMF1; HMF1 << "hmf1" << k;
        hfail_meta0p8to1p5.push_back(new TH1F (HMF1.str().c_str(),"InvMa",60,60,120)); hfail_meta0p8to1p5[k]->Sumw2();
        ostringstream HMF2; HMF2 << "hmf2" << k;
        hfail_meta1p5to2p0.push_back(new TH1F (HMF2.str().c_str(),"InvMa",60,60,120)); hfail_meta1p5to2p0[k]->Sumw2();
        ostringstream HMF3; HMF3 << "hmf3" << k;
        hfail_meta2p0to2p5.push_back(new TH1F (HMF3.str().c_str(),"InvMa",60,60,120)); hfail_meta2p0to2p5[k]->Sumw2();
   }

   TFile *mcfile= new TFile("MC_PileUp_UL2018.root","read");
   TH1F *mchist = (TH1F*) mcfile->Get("pileup");
   TFile *datafile= new TFile("Data_PileUp_UL2018_69p2.root","read");
   TH1F *datahist = (TH1F*) datafile->Get("pileup");

   if (year=="2017"){
      TFile *mcfile= new TFile("MC_PileUp_UL2017.root","read");
      mchist = (TH1F*) mcfile->Get("pileup");
      TFile *datafile= new TFile("Data_PileUp_UL2017_69p2.root","read");
      datahist = (TH1F*) datafile->Get("pileup");
   }
   else if (year=="2016post"){
      TFile *mcfile= new TFile("MC_PileUp_UL2016_postVFP.root","read");
      mchist = (TH1F*) mcfile->Get("pileup");
      TFile *datafile= new TFile("Data_PileUp_UL2016_69p2.root","read");
      datahist = (TH1F*) datafile->Get("pileup");
   }
   else if (year=="2016pre"){
      TFile *mcfile= new TFile("MC_PileUp_UL2016_preVFP.root","read");
      mchist = (TH1F*) mcfile->Get("pileup");
      TFile *datafile= new TFile("Data_PileUp_UL2016_69p2.root","read");
      datahist = (TH1F*) datafile->Get("pileup");
   }

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 100000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	//if (ntracks<30) continue; //FIXME

	if (tag_pt<35 or fabs(tag_sceta)>2.17) continue;

	TLorentzVector my_tag;
	my_tag.SetPtEtaPhiM(tag_pt, tag_eta, tag_phi, 0);
        TLorentzVector my_probe;
        my_probe.SetPtEtaPhiM(probe_pt, probe_eta, probe_phi, 0);

	int is_pass=0;
	if (discriminant=="HLTEle25") is_pass=probe_matchHLTEle25;
        if (discriminant=="HLTEle27") is_pass=probe_matchHLTEle27;
        if (discriminant=="HLTEle32") is_pass=probe_matchHLTEle32;
        if (discriminant=="HLTEle35") is_pass=probe_matchHLTEle35;
        if (discriminant=="HLTEle24Tau30") is_pass=probe_matchHLTEle24Tau30;
        if (discriminant=="HLTMu23Ele12") is_pass=probe_matchHLTMu23Ele12;
        if (discriminant=="HLTMu8Ele23") is_pass=probe_matchHLTMu8Ele23;
        if (discriminant=="MVAisoWPLoose") is_pass=probe_MVAisoWPLoose;
        if (discriminant=="MVAisoWP80") is_pass=probe_MVAisoWP80;
        if (discriminant=="MVAisoWP90") is_pass=probe_MVAisoWP90;
        if (discriminant=="antiiso") is_pass=(probe_MVAisoWPLoose and !probe_MVAisoWP80);
        if (discriminant=="MVAnoIsoWPLoose") is_pass=probe_MVAnoIsoWPLoose;
        if (discriminant=="MVAnoIsoWP80") is_pass=probe_MVAnoIsoWP80;
        if (discriminant=="MVAnoIsoWP90") is_pass=probe_MVAnoIsoWP90;
        if (discriminant=="antinoIso") is_pass=(probe_MVAnoIsoWPLoose and !probe_MVAnoIsoWP80);

	if (discriminant!="antiiso" and discriminant!="MVAnoIsoWPLoose" and discriminant!="MVAnoIsoWP80" and discriminant!="MVAnoIsoWP90" and probe_MVAnoIsoWP80==0) continue;

        if (discriminant=="HLTEle24Tau30" and tag_matchedToL1Tau==0) continue;
        if ((discriminant=="HLTEle25" or discriminant=="HLTEle24Tau30") and (fabs(probe_sceta)>2.1 or fabs(probe_eta)>2.1)) continue;

        float pu_weight=1.0;
        if (sample!="data_obs" and sample!="Data"){
            float dataw = datahist->GetBinContent(datahist->GetXaxis()->FindBin(trueNumInteractions))/datahist->Integral();
            float mcw   = mchist->GetBinContent(mchist->GetXaxis()->FindBin(trueNumInteractions))/mchist->Integral();
            if (mcw>0.){
              pu_weight = dataw/mcw;
              if (pu_weight>5.) pu_weight=5.;
            }
        }

        if (probe_sceta>0){
	  if (is_pass){
	    if (fabs(probe_sceta)<0.8){
		for (int l=0; l<nb_pt; ++l){
		   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_etalt0p8[l]->Fill((my_tag+my_probe).M(),pu_weight);
		}
	    }
            else if (fabs(probe_sceta)>=0.8 and fabs(probe_sceta)<1.444){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_eta0p8to1p5[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=1.566 and fabs(probe_sceta)<2.0){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_eta1p5to2p0[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=2.0 and fabs(probe_sceta)<2.5){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_eta2p0to2p5[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
	}
	else{
            if (fabs(probe_sceta)<0.8){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_etalt0p8[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=0.8 and fabs(probe_sceta)<1.444){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_eta0p8to1p5[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=1.566 and fabs(probe_sceta)<2.0){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_eta1p5to2p0[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=2.0 and fabs(probe_sceta)<2.5){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_eta2p0to2p5[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
          }
	}
	else{
          if (is_pass){
            if (fabs(probe_sceta)<0.8){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_metalt0p8[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=0.8 and fabs(probe_sceta)<1.444){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_meta0p8to1p5[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=1.566 and fabs(probe_sceta)<2.0){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_meta1p5to2p0[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=2.0 and fabs(probe_sceta)<2.5){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_meta2p0to2p5[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
        }
        else{
            if (fabs(probe_sceta)<0.8){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_metalt0p8[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=0.8 and fabs(probe_sceta)<1.444){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_meta0p8to1p5[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=1.566 and fabs(probe_sceta)<2.0){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_meta1p5to2p0[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(probe_sceta)>=2.0 and fabs(probe_sceta)<2.5){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_meta2p0to2p5[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
          }
	}

    } // end of loop over events

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    for (int k=0; k<nb_pt; ++k){
       hpass_etalt0p8[k]->SetName("pass_"+discriminant+"_etalt0p8_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_etalt0p8[k]->Write();
       hfail_etalt0p8[k]->SetName("fail_"+discriminant+"_etalt0p8_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_etalt0p8[k]->Write();

       hpass_eta0p8to1p5[k]->SetName("pass_"+discriminant+"_eta0p8to1p5_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_eta0p8to1p5[k]->Write();
       hfail_eta0p8to1p5[k]->SetName("fail_"+discriminant+"_eta0p8to1p5_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_eta0p8to1p5[k]->Write();

       hpass_eta1p5to2p0[k]->SetName("pass_"+discriminant+"_eta1p5to2p0_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_eta1p5to2p0[k]->Write();
       hfail_eta1p5to2p0[k]->SetName("fail_"+discriminant+"_eta1p5to2p0_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_eta1p5to2p0[k]->Write();

       hpass_eta2p0to2p5[k]->SetName("pass_"+discriminant+"_eta2p0to2p5_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_eta2p0to2p5[k]->Write();
       hfail_eta2p0to2p5[k]->SetName("fail_"+discriminant+"_eta2p0to2p5_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_eta2p0to2p5[k]->Write();

       hpass_metalt0p8[k]->SetName("pass_"+discriminant+"_metalt0p8_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_metalt0p8[k]->Write();
       hfail_metalt0p8[k]->SetName("fail_"+discriminant+"_metalt0p8_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_metalt0p8[k]->Write();

       hpass_meta0p8to1p5[k]->SetName("pass_"+discriminant+"_meta0p8to1p5_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_meta0p8to1p5[k]->Write();
       hfail_meta0p8to1p5[k]->SetName("fail_"+discriminant+"_meta0p8to1p5_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_meta0p8to1p5[k]->Write();

       hpass_meta1p5to2p0[k]->SetName("pass_"+discriminant+"_meta1p5to2p0_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_meta1p5to2p0[k]->Write();
       hfail_meta1p5to2p0[k]->SetName("fail_"+discriminant+"_meta1p5to2p0_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_meta1p5to2p0[k]->Write();

       hpass_meta2p0to2p5[k]->SetName("pass_"+discriminant+"_meta2p0to2p5_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_meta2p0to2p5[k]->Write();
       hfail_meta2p0to2p5[k]->SetName("fail_"+discriminant+"_meta2p0to2p5_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_meta2p0to2p5[k]->Write();
    }

    fout->Close();
} 


