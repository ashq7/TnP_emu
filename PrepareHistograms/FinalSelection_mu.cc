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
    arbre->SetBranchAddress("tag_phi", &tag_phi);
    arbre->SetBranchAddress("tag_dxy", &tag_dxy);
    arbre->SetBranchAddress("tag_dz", &tag_dz);
    arbre->SetBranchAddress("tag_matchedToL1Tau", &tag_matchedToL1Tau);
    arbre->SetBranchAddress("probe_pt", &probe_pt);
    arbre->SetBranchAddress("probe_eta", &probe_eta);
    arbre->SetBranchAddress("probe_phi", &probe_phi);
    arbre->SetBranchAddress("probe_dxy", &probe_dxy);
    arbre->SetBranchAddress("probe_dz", &probe_dz);
    arbre->SetBranchAddress("probe_mediumID", &probe_mediumID);
    arbre->SetBranchAddress("probe_iso", &probe_iso);
    arbre->SetBranchAddress("probe_matchHLTIsoMu24", &probe_matchHLTIsoMu24);
    arbre->SetBranchAddress("probe_matchHLTMu20Tau27", &probe_matchHLTMu20Tau27);
    arbre->SetBranchAddress("probe_matchHLTMu20Tau27_2017B", &probe_matchHLTMu20Tau27_2017B);
    arbre->SetBranchAddress("probe_matchHLTMu23Ele12", &probe_matchHLTMu23Ele12);
    arbre->SetBranchAddress("probe_matchHLTMu8Ele23", &probe_matchHLTMu8Ele23);
    arbre->SetBranchAddress("trueNumInteractions", &trueNumInteractions);
    arbre->SetBranchAddress("puNumInteractions", &puNumInteractions);
    arbre->SetBranchAddress("ntracks", &ntracks);

   //int nb_pt=27;
   //float bins_pt[28]={15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,35,40,50,60,70,80,90,100,120,150};
   //TString sbins_pt[28]={"15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","35","40","50","60","70","80","90","100","120","150"};
   //

   int nb_pt=7;
   float bins_pt[8]={15,24,30,40,50,60,120,200};
   TString sbins_pt[8]={"15","24","30","40","50","60","120","200"};
   if (discriminant=="HLTIsoMu24"){bins_pt[1]=26; sbins_pt[1]="26";}
   if (discriminant=="HLTMu20Tau27"){bins_pt[1]=21; sbins_pt[1]="21";}
   if (discriminant=="HLTMu20Tau27_2017B"){bins_pt[1]=21; sbins_pt[1]="21";}

   std::vector<TH1F*> hpass_etalt0p9;
   std::vector<TH1F*> hfail_etalt0p9;
   std::vector<TH1F*> hpass_eta0p9to1p2;
   std::vector<TH1F*> hfail_eta0p9to1p2;
   std::vector<TH1F*> hpass_eta1p2to2p1;
   std::vector<TH1F*> hfail_eta1p2to2p1;
   std::vector<TH1F*> hpass_eta2p1to2p4;
   std::vector<TH1F*> hfail_eta2p1to2p4;
   for (int k=0; k<nb_pt; ++k){
        ostringstream HN0; HN0 << "h0" << k;
        hpass_etalt0p9.push_back(new TH1F (HN0.str().c_str(),"InvMa",60,70,130)); hpass_etalt0p9[k]->Sumw2();
        ostringstream HN1; HN1 << "h1" << k;
        hpass_eta0p9to1p2.push_back(new TH1F (HN1.str().c_str(),"InvMa",60,70,130)); hpass_eta0p9to1p2[k]->Sumw2();
        ostringstream HN2; HN2 << "h2" << k;
        hpass_eta1p2to2p1.push_back(new TH1F (HN2.str().c_str(),"InvMa",60,70,130)); hpass_eta1p2to2p1[k]->Sumw2();
        ostringstream HN3; HN3 << "h3" << k;
        hpass_eta2p1to2p4.push_back(new TH1F (HN3.str().c_str(),"InvMa",60,70,130)); hpass_eta2p1to2p4[k]->Sumw2();

        ostringstream HNF0; HNF0 << "hf0" << k;
        hfail_etalt0p9.push_back(new TH1F (HNF0.str().c_str(),"InvMa",60,70,130)); hfail_etalt0p9[k]->Sumw2();
        ostringstream HNF1; HNF1 << "hf1" << k;
        hfail_eta0p9to1p2.push_back(new TH1F (HNF1.str().c_str(),"InvMa",60,70,130)); hfail_eta0p9to1p2[k]->Sumw2();
        ostringstream HNF2; HNF2 << "hf2" << k;
        hfail_eta1p2to2p1.push_back(new TH1F (HNF2.str().c_str(),"InvMa",60,70,130)); hfail_eta1p2to2p1[k]->Sumw2();
        ostringstream HNF3; HNF3 << "hf3" << k;
        hfail_eta2p1to2p4.push_back(new TH1F (HNF3.str().c_str(),"InvMa",60,70,130)); hfail_eta2p1to2p4[k]->Sumw2();
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

	TLorentzVector my_tag;
	my_tag.SetPtEtaPhiM(tag_pt, tag_eta, tag_phi, 0);
        TLorentzVector my_probe;
        my_probe.SetPtEtaPhiM(probe_pt, probe_eta, probe_phi, 0);

        int is_pass=0;
        if (discriminant=="HLTIsoMu24") is_pass=probe_matchHLTIsoMu24;
        if (discriminant=="HLTMu20Tau27") is_pass=probe_matchHLTMu20Tau27;
        if (discriminant=="HLTMu20Tau27_2017B") is_pass=probe_matchHLTMu20Tau27_2017B;
        if (discriminant=="HLTMu23Ele12") is_pass=probe_matchHLTMu23Ele12;
        if (discriminant=="HLTMu8Ele23") is_pass=probe_matchHLTMu8Ele23;
        if (discriminant=="mediumID") is_pass=probe_mediumID;
        if (discriminant=="looseIso") is_pass=(probe_iso<0.25);
        if (discriminant=="mediumIso") is_pass=(probe_iso<0.20);
        if (discriminant=="tightIso") is_pass=(probe_iso<0.15);
        if (discriminant=="antiiso") is_pass=(probe_iso>0.20 and probe_iso<0.50);

        if (discriminant!="antiiso" and discriminant!="looseIso" and discriminant!="mediumIso" and discriminant!="tightIso" and discriminant!="mediumID" and (probe_iso>0.20 or probe_mediumID==0)) continue;
        if (discriminant=="antiiso" and probe_mediumID==0) continue;
        if (discriminant=="mediumIso" and probe_mediumID==0) continue;
        if (discriminant=="HLTMu20Tau27_2017B" and !tag_matchedToL1Tau) continue;
	if (tag_pt<26) continue;
	if (year=="2017" and tag_pt<29) continue;
	if (year=="2016pre" and fabs(my_tag.DeltaPhi(my_probe))<1.22 and ((my_tag.Eta()>1.5 and my_probe.Eta()<-1.5) or (my_tag.Eta()>1.5 and my_probe.Eta()<-1.5))) continue;

        float pu_weight=1.0;
        if (sample!="data_obs" and sample!="Data"){
            float dataw = datahist->GetBinContent(datahist->GetXaxis()->FindBin(trueNumInteractions))/datahist->Integral();
            float mcw   = mchist->GetBinContent(mchist->GetXaxis()->FindBin(trueNumInteractions))/mchist->Integral();
            if (mcw>0.){
              pu_weight = dataw/mcw;
              if (pu_weight>5.) pu_weight=5.;
	    }
	}

	if (is_pass){
	    if (fabs(my_probe.Eta())<0.9){
		for (int l=0; l<nb_pt; ++l){
		   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_etalt0p9[l]->Fill((my_tag+my_probe).M(),pu_weight);
		}
	    }
            else if (fabs(my_probe.Eta())>=0.9 and fabs(my_probe.Eta())<1.2){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_eta0p9to1p2[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(my_probe.Eta())>=1.2 and fabs(my_probe.Eta())<2.1){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_eta1p2to2p1[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(my_probe.Eta())>=2.1 and fabs(my_probe.Eta())<2.4){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hpass_eta2p1to2p4[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
	}
	else{
            if (fabs(my_probe.Eta())<0.9){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_etalt0p9[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(my_probe.Eta())>=0.9 and fabs(my_probe.Eta())<1.2){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_eta0p9to1p2[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(my_probe.Eta())>=1.2 and fabs(my_probe.Eta())<2.1){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_eta1p2to2p1[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
            else if (fabs(my_probe.Eta())>=2.1 and fabs(my_probe.Eta())<2.4){
                for (int l=0; l<nb_pt; ++l){
                   if (my_probe.Pt()>bins_pt[l] and my_probe.Pt()<=bins_pt[l+1]) hfail_eta2p1to2p4[l]->Fill((my_tag+my_probe).M(),pu_weight);
                }
            }
        }

    } // end of loop over events

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    for (int k=0; k<nb_pt; ++k){
       hpass_etalt0p9[k]->SetName("pass_"+discriminant+"_etalt0p9_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_etalt0p9[k]->Write();
       hfail_etalt0p9[k]->SetName("fail_"+discriminant+"_etalt0p9_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_etalt0p9[k]->Write();

       hpass_eta0p9to1p2[k]->SetName("pass_"+discriminant+"_eta0p9to1p2_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_eta0p9to1p2[k]->Write();
       hfail_eta0p9to1p2[k]->SetName("fail_"+discriminant+"_eta0p9to1p2_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_eta0p9to1p2[k]->Write();

       hpass_eta1p2to2p1[k]->SetName("pass_"+discriminant+"_eta1p2to2p1_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_eta1p2to2p1[k]->Write();
       hfail_eta1p2to2p1[k]->SetName("fail_"+discriminant+"_eta1p2to2p1_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_eta1p2to2p1[k]->Write();

       hpass_eta2p1to2p4[k]->SetName("pass_"+discriminant+"_eta2p1to2p4_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hpass_eta2p1to2p4[k]->Write();
       hfail_eta2p1to2p4[k]->SetName("fail_"+discriminant+"_eta2p1to2p4_pt"+sbins_pt[k]+"to"+sbins_pt[k+1]);
       hfail_eta2p1to2p4[k]->Write();
    }

    fout->Close();
} 


