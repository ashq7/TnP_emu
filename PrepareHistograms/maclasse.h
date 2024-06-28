//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar  7 12:02:42 2023 by ROOT version 6.14/09
// from TTree tree/
// found on file: /eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/DY.root
//////////////////////////////////////////////////////////

#ifndef maclasse_h
#define maclasse_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class maclasse {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         tag_pt;
   Float_t         tag_eta;
   Float_t         tag_phi;
   Float_t         tag_dxy;
   Float_t         tag_dz;
   Float_t         probe_pt;
   Float_t         probe_eta;
   Float_t         probe_phi;
   Float_t         probe_dxy;
   Float_t         probe_dz;
   Int_t           probe_mediumID;
   Float_t         probe_iso;
   Int_t           probe_matchHLTIsoMu24;
   Int_t           probe_matchHLTMu20Tau27;
   Int_t           probe_matchHLTMu23Ele12;
   Int_t           probe_matchHLTMu8Ele23;
   Float_t         trueNumInteractions;
   Int_t           puNumInteractions;

   // List of branches
   TBranch        *b_tag_pt;   //!
   TBranch        *b_tag_eta;   //!
   TBranch        *b_tag_phi;   //!
   TBranch        *b_tag_dxy;   //!
   TBranch        *b_tag_dz;   //!
   TBranch        *b_probe_pt;   //!
   TBranch        *b_probe_eta;   //!
   TBranch        *b_probe_phi;   //!
   TBranch        *b_probe_dxy;   //!
   TBranch        *b_probe_dz;   //!
   TBranch        *b_probe_mediumID;   //!
   TBranch        *b_probe_iso;   //!
   TBranch        *b_probe_matchHLTIsoMu24;   //!
   TBranch        *b_probe_matchHLTMu20Tau27;   //!
   TBranch        *b_probe_matchHLTMu23Ele12;   //!
   TBranch        *b_probe_matchHLTMu8Ele23;   //!
   TBranch        *b_trueNumInteractions;   //!
   TBranch        *b_puNumInteractions;   //!

   maclasse(TTree *tree=0);
   virtual ~maclasse();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef maclasse_cxx
maclasse::maclasse(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/DY.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/DY.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/eos/cms/store/group/cmst3/group/taug2/TnP_mu_2018/DY.root:/demo");
      dir->GetObject("tree",tree);

   }
   Init(tree);
}

maclasse::~maclasse()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t maclasse::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t maclasse::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void maclasse::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("tag_pt", &tag_pt, &b_tag_pt);
   fChain->SetBranchAddress("tag_eta", &tag_eta, &b_tag_eta);
   fChain->SetBranchAddress("tag_phi", &tag_phi, &b_tag_phi);
   fChain->SetBranchAddress("tag_dxy", &tag_dxy, &b_tag_dxy);
   fChain->SetBranchAddress("tag_dz", &tag_dz, &b_tag_dz);
   fChain->SetBranchAddress("probe_pt", &probe_pt, &b_probe_pt);
   fChain->SetBranchAddress("probe_eta", &probe_eta, &b_probe_eta);
   fChain->SetBranchAddress("probe_phi", &probe_phi, &b_probe_phi);
   fChain->SetBranchAddress("probe_dxy", &probe_dxy, &b_probe_dxy);
   fChain->SetBranchAddress("probe_dz", &probe_dz, &b_probe_dz);
   fChain->SetBranchAddress("probe_mediumID", &probe_mediumID, &b_probe_mediumID);
   fChain->SetBranchAddress("probe_iso", &probe_iso, &b_probe_iso);
   fChain->SetBranchAddress("probe_matchHLTIsoMu24", &probe_matchHLTIsoMu24, &b_probe_matchHLTIsoMu24);
   fChain->SetBranchAddress("probe_matchHLTMu20Tau27", &probe_matchHLTMu20Tau27, &b_probe_matchHLTMu20Tau27);
   fChain->SetBranchAddress("probe_matchHLTMu23Ele12", &probe_matchHLTMu23Ele12, &b_probe_matchHLTMu23Ele12);
   fChain->SetBranchAddress("probe_matchHLTMu8Ele23", &probe_matchHLTMu8Ele23, &b_probe_matchHLTMu8Ele23);
   fChain->SetBranchAddress("trueNumInteractions", &trueNumInteractions, &b_trueNumInteractions);
   fChain->SetBranchAddress("puNumInteractions", &puNumInteractions, &b_puNumInteractions);
   Notify();
}

Bool_t maclasse::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void maclasse::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t maclasse::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef maclasse_cxx
