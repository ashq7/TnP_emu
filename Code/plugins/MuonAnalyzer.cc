// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TLorentzVector.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/MuonReco/interface/MuonSimInfo.h"
#include "MuonAnalysis/MuonAssociators/interface/PropagateToMuon.h"

#include "DataFormats/L1Trigger/interface/L1Candidate.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "DataFormats/L1Trigger/interface/L1TObjComparison.h"
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/L1Trigger/interface/Tau.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

using namespace reco;
using namespace std;
using namespace edm;


class MuonAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit MuonAnalyzer(const edm::ParameterSet&);
      ~MuonAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      const bool isMC_;
      const int year_;

      // ----------member data ---------------------------

      EDGetTokenT<edm::TriggerResults> triggerBits_;
      EDGetTokenT<std::vector<pat::TriggerObjectStandAlone> > triggerObjects_;
      EDGetTokenT<pat::MuonCollection> muonToken_;
      EDGetTokenT<std::vector<reco::Vertex>> vtxToken_;
      EDGetTokenT<l1t::MuonBxCollection> l1muToken_;
      EDGetTokenT<l1t::TauBxCollection> l1tauToken_;
      EDGetTokenT<std::vector<PileupSummaryInfo>> pileupSummaryToken_;
      EDGetTokenT<pat::PackedCandidateCollection> pfToken_;

      // Declare the histograms
      TTree *tree;
      float tag_pt;
      float tag_eta;
      float tag_phi;
      float tag_dxy;
      float tag_dz;
      int tag_matchedToL1Tau;
      float probe_pt;
      float probe_eta;
      float probe_phi;
      float probe_dxy;
      float probe_dz;
      int probe_mediumID;
      float probe_iso;
      int probe_matchHLTIsoMu24;
      int probe_matchHLTMu20Tau27;
      int probe_matchHLTMu20Tau27_2017B;
      int probe_matchHLTMu23Ele12;
      int probe_matchHLTMu8Ele23;
      float trueNumInteractions;
      int puNumInteractions;
      int ntracks;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MuonAnalyzer::MuonAnalyzer(const edm::ParameterSet& iConfig):
    isMC_(iConfig.getParameter<bool>("isMC")),
    year_(iConfig.getParameter<int>("year")),
    triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
    triggerObjects_(consumes<std::vector<pat::TriggerObjectStandAlone> >(iConfig.getParameter<edm::InputTag>("objects"))),
    muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
    vtxToken_(consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("vertices"))),
    l1muToken_(consumes<l1t::MuonBxCollection>(iConfig.getParameter<edm::InputTag>("l1muons"))),
    l1tauToken_(consumes<l1t::TauBxCollection>(iConfig.getParameter<edm::InputTag>("l1taus"))),
    pileupSummaryToken_(consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("pileupInfo"))),
    pfToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfCands")))
{
   //now do what ever initialization is needed
   //give the binning of the histograms
   usesResource("TFileService");
   edm::Service<TFileService> fs;
   tree = fs->make<TTree>("tree","");
   tree->Branch("ntracks",&ntracks);
   tree->Branch("tag_pt",&tag_pt);
   tree->Branch("tag_eta",&tag_eta);
   tree->Branch("tag_phi",&tag_phi);
   tree->Branch("tag_dxy",&tag_dxy);
   tree->Branch("tag_dz",&tag_dz);
   tree->Branch("tag_matchedToL1Tau",&tag_matchedToL1Tau);
   tree->Branch("probe_pt",&probe_pt);
   tree->Branch("probe_eta",&probe_eta);
   tree->Branch("probe_phi",&probe_phi);
   tree->Branch("probe_dxy",&probe_dxy);
   tree->Branch("probe_dz",&probe_dz);
   tree->Branch("probe_mediumID",&probe_mediumID);
   tree->Branch("probe_iso",&probe_iso);
   tree->Branch("probe_matchHLTIsoMu24",&probe_matchHLTIsoMu24);
   tree->Branch("probe_matchHLTMu20Tau27",&probe_matchHLTMu20Tau27);
   tree->Branch("probe_matchHLTMu20Tau27_2017B",&probe_matchHLTMu20Tau27_2017B);
   tree->Branch("probe_matchHLTMu23Ele12",&probe_matchHLTMu23Ele12);
   tree->Branch("probe_matchHLTMu8Ele23",&probe_matchHLTMu8Ele23);
   tree->Branch("trueNumInteractions",&trueNumInteractions);
   tree->Branch("puNumInteractions",&puNumInteractions);

}


MuonAnalyzer::~MuonAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    int nMuons=0;
    int index_mu1=-1;
    int index_mu2=-1;
    edm::Handle<pat::MuonCollection> muons;
    iEvent.getByToken(muonToken_, muons);
    int i=-1;
    for (const pat::Muon &mu : *muons) {
	i++;
        //if (mu.pt() < 10 || !mu.isLooseMuon()) continue;
        if (mu.pt() < 10 || fabs(mu.eta())>2.4) continue;
	//nMuons++;
	if (index_mu1<0) {index_mu1=i; nMuons++;}
	else if (deltaR((*muons)[index_mu1].eta(), (*muons)[index_mu1].phi(), mu.eta(), mu.phi())>0.1) {index_mu2=i;nMuons++;}
	//else {index_mu2=i;nMuons++;}
    }

    int tmp_index;
    if (iEvent.id().event()%2==0){
       tmp_index=index_mu1;
       index_mu1=index_mu2;
       index_mu2=tmp_index;
    }

    if (nMuons==2){ 

      edm::Handle<reco::VertexCollection> vertices;
      iEvent.getByToken(vtxToken_, vertices);
      float pv_x=0; float pv_y=0; float pv_z=0;
      for (const reco::Vertex& vtx : *vertices) {
        if (vtx.isFake() || !vtx.isValid())
          continue;
        pv_x = vtx.x();
        pv_y = vtx.y();
        pv_z = vtx.z();
        break;
      }

      edm::Handle<l1t::MuonBxCollection> l1muons;
      iEvent.getByToken(l1muToken_, l1muons);

      edm::Handle<l1t::TauBxCollection> l1taus;
      iEvent.getByToken(l1tauToken_, l1taus);

      tag_pt=(*muons)[index_mu1].pt();
      tag_eta=(*muons)[index_mu1].eta();
      tag_phi=(*muons)[index_mu1].phi();
      if (!(*muons)[index_mu1].innerTrack().isNull()){ 
	 tag_dxy = (*muons)[index_mu1].innerTrack()->dxy(reco::TrackBase::Point(pv_x, pv_y, pv_z));
         tag_dz = (*muons)[index_mu1].innerTrack()->dz(reco::TrackBase::Point(pv_x, pv_y, pv_z));
      }
      else{
         tag_dxy = 0.0;
         tag_dz = 0.0;
      }

      probe_pt=(*muons)[index_mu2].pt();
      probe_eta=(*muons)[index_mu2].eta();
      probe_phi=(*muons)[index_mu2].phi();
      probe_iso=((*muons)[index_mu2].pfIsolationR04().sumChargedHadronPt + TMath::Max((*muons)[index_mu2].pfIsolationR04().sumNeutralHadronEt + (*muons)[index_mu2].pfIsolationR04().sumPhotonEt - (*muons)[index_mu2].pfIsolationR04().sumPUPt/2.0,0.0))/(*muons)[index_mu2].pt();
      if (!(*muons)[index_mu2].innerTrack().isNull()){
         probe_dxy = (*muons)[index_mu2].innerTrack()->dxy(reco::TrackBase::Point(pv_x, pv_y, pv_z));
         probe_dz = (*muons)[index_mu2].innerTrack()->dz(reco::TrackBase::Point(pv_x, pv_y, pv_z));
      }
      else{
         probe_dxy = 0.0;
         probe_dz = 0.0;
      }
      probe_mediumID = muon::isMediumMuon((*muons)[index_mu2]);

      float l1pt=-100000;
      for (const l1t::Muon &l1mu : *l1muons) {
         float l1dR = deltaR(probe_eta, probe_phi, l1mu.eta(), l1mu.phi());
	 if (l1dR<0.5 and fabs(l1mu.pt()-probe_pt)<fabs(l1pt-probe_pt)) l1pt=l1mu.pt();
      }

      tag_matchedToL1Tau=0;
      for (const l1t::Tau &l1tau : *l1taus) {
         float l1dR = deltaR(tag_eta, tag_phi, l1tau.eta(), l1tau.phi());
         if (l1tau.pt()>24 and l1dR<0.5) tag_matchedToL1Tau=1;
      }


      bool is_os=(((*muons)[index_mu1].charge()*(*muons)[index_mu2].charge())<0);

      Handle<edm::TriggerResults> triggerBits;
      iEvent.getByToken(triggerBits_, triggerBits);

      Handle<std::vector<pat::TriggerObjectStandAlone> > triggerObjects;
      iEvent.getByToken(triggerObjects_, triggerObjects);


       const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
       bool pass_IsoMu=false;
       bool tag_trgmatched=false;
       TString mypath="HLT_IsoMu24";
       if (year_==2017) mypath="HLT_IsoMu27";
       for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
	   TString TrigPath=names.triggerName(i);
	   if (triggerBits->accept(i) and TrigPath.Contains(mypath)) pass_IsoMu=true;
       }

       probe_matchHLTIsoMu24=0;
       probe_matchHLTMu20Tau27=0;
       probe_matchHLTMu20Tau27_2017B=0;
       probe_matchHLTMu23Ele12=0;
       probe_matchHLTMu8Ele23=0;
       for (pat::TriggerObjectStandAlone obj : *triggerObjects) { // note: not "const &" since we want to call unpackPathNames
           obj.unpackPathNames(names);
           obj.unpackNamesAndLabels(iEvent, *triggerBits);
	   float dR_tag = deltaR(tag_eta, tag_phi, obj.eta(), obj.phi());
           float dR_probe = deltaR(probe_eta, probe_phi, obj.eta(), obj.phi());
	   if (dR_tag<0.5){
	      for (unsigned h = 0; h < obj.filterLabels().size(); ++h){
	 	 TString filter = obj.filterLabels()[h];
		 if (filter.Contains("hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07")) tag_trgmatched=true;
                 if (filter.Contains("hltL3crIsoL1sMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p09")) tag_trgmatched=true;
	      }
	   }
           if (dR_probe<0.5){
              for (unsigned h = 0; h < obj.filterLabels().size(); ++h){
                 TString filter = obj.filterLabels()[h];
                 if (year_==2016 and filter.Contains("hltL3crIsoL1sMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p09")) probe_matchHLTIsoMu24=1;
		 if (year_==2017 and filter.Contains("hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07")) probe_matchHLTIsoMu24=1;
                 if (year_==2018 and filter.Contains("hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07")) probe_matchHLTIsoMu24=1;
                 if (year_==2018 and filter.Contains("hltL3crIsoL1sMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p09")) probe_matchHLTIsoMu24=1;


	         if (year_==2016 and filter.Contains("hltL3crIsoL1sSingleMu18erIorSingleMu20erL1f0L2f10QL3f19QL3trkIsoFiltered0p09")) probe_matchHLTMu20Tau27=1;
                 if (year_==2017 and filter.Contains("hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07")) probe_matchHLTMu20Tau27_2017B=1;
                 if (year_==2017 and filter.Contains("hltL3crIsoL1sDoubleMu18erL1f0L2f10QL3f20QL3trkIsoFiltered0p07")) probe_matchHLTMu20Tau27=1;
                 if (year_==2018 and filter.Contains("hltL3crIsoL1sDoubleMu18erL1f0L2f10QL3f20QL3trkIsoFiltered0p07"))probe_matchHLTMu20Tau27=1;



                 if (year_==2016 and l1pt>20 and obj.pt()>23 and filter.Contains("hltDiMuonGlb17Glb8RelTrkIsoFiltered0p4")) probe_matchHLTMu23Ele12=1;
	         if (year_==2016 and filter.Contains("hltDiMuonGlb17Glb8RelTrkIsoFiltered0p4")) probe_matchHLTMu8Ele23=1;
                 if (year_==2017 and l1pt>20 and obj.pt()>23 and filter.Contains("hltDiMuon178RelTrkIsoFiltered0p4")) probe_matchHLTMu23Ele12=1;
                 if (year_==2017 and filter.Contains("hltDiMuon178RelTrkIsoFiltered0p4")) probe_matchHLTMu8Ele23=1;
                 if (year_==2018 and l1pt>20 and obj.pt()>23 and filter.Contains("hltDiMuon178RelTrkIsoFiltered0p4")) probe_matchHLTMu23Ele12=1;
                 if (year_==2018 and filter.Contains("hltDiMuon178RelTrkIsoFiltered0p4")) probe_matchHLTMu8Ele23=1;

              }
           }
       } 
       /*std::cout << "\n TRIGGER OBJECTS " << std::endl;
       for (pat::TriggerObjectStandAlone obj : *triggerObjects) { // note: not "const &" since we want to call unpackPathNames
           obj.unpackPathNames(names);
	   obj.unpackNamesAndLabels(iEvent, *triggerBits);
           std::cout << "\tTrigger object:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << std::endl;
           // Print trigger object collection and type
           std::cout << "\t   Collection: " << obj.collection() << std::endl;
           std::cout << "\t   Type IDs:   ";
           for (unsigned h = 0; h < obj.filterIds().size(); ++h) std::cout << " " << obj.filterIds()[h] ;
           std::cout << std::endl;
           // Print associated trigger filters
           std::cout << "\t   Filters:    ";
           for (unsigned h = 0; h < obj.filterLabels().size(); ++h) std::cout << " " << obj.filterLabels()[h];
           std::cout << std::endl;
           std::vector pathNamesAll = obj.pathNames(false);
           std::vector pathNamesLast = obj.pathNames(true);
           // Print all trigger paths, for each one record also if the object is associated to a 'l3' filter (always true for the
           // definition used in the PAT trigger producer) and if it's associated to the last filter of a successfull path (which
           // means that this object did cause this trigger to succeed; however, it doesn't work on some multi-object triggers)
           std::cout << "\t   Paths (" << pathNamesAll.size()<<"/"<<pathNamesLast.size()<<"):    ";
           for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {
               bool isBoth = obj.hasPathName( pathNamesAll[h], true, true );
               bool isL3   = obj.hasPathName( pathNamesAll[h], false, true );
               bool isLF   = obj.hasPathName( pathNamesAll[h], true, false );
               bool isNone = obj.hasPathName( pathNamesAll[h], false, false );
               std::cout << "   " << pathNamesAll[h];
               if (isBoth) std::cout << "(L,3)";
               if (isL3 && !isBoth) std::cout << "(*,3)";
               if (isLF && !isBoth) std::cout << "(L,*)";
               if (isNone && !isBoth && !isL3 && !isLF) std::cout << "(*,*)";
           }
           std::cout << std::endl;
       }
       std::cout << std::endl;*/

      TLorentzVector mytag;
      mytag.SetPtEtaPhiM(tag_pt,tag_eta,tag_phi,0);
      TLorentzVector myprobe;
      myprobe.SetPtEtaPhiM(probe_pt,probe_eta,probe_phi,0);

      float tag_iso=((*muons)[index_mu1].pfIsolationR04().sumChargedHadronPt + TMath::Max((*muons)[index_mu1].pfIsolationR04().sumNeutralHadronEt + (*muons)[index_mu1].pfIsolationR04().sumPhotonEt - (*muons)[index_mu1].pfIsolationR04().sumPUPt/2.0,0.0))/(*muons)[index_mu1].pt();

      if (isMC_) {
         edm::Handle<std::vector<PileupSummaryInfo>> PupInfo;
         iEvent.getByToken(pileupSummaryToken_, PupInfo);
         for (auto PVI : *PupInfo) {
            int BX = PVI.getBunchCrossing();
            if (BX == 0) {
               trueNumInteractions = PVI.getTrueNumInteractions();
               puNumInteractions = PVI.getPU_NumInteractions();
               continue;
            }
         }
      }

//std::cout<<tag_trgmatched<<" "<<pass_IsoMu<<" "<<tag_iso<<" "<<muon::isMediumMuon((*muons)[index_mu1])<<" "<<mytag.DeltaR(myprobe)<<" "<<(mytag+myprobe).M()<<" "<<is_os<<std::endl;
      ntracks=-2;
      Handle<pat::PackedCandidateCollection> pfs;
      iEvent.getByToken(pfToken_, pfs);
      float dimu_dz=0.5*(tag_dz+probe_dz);
      for (unsigned int i = 0, n = pfs->size(); i < n; ++i) {
          const pat::PackedCandidate &pf = (*pfs)[i];
	  if (fabs(pf.eta())<2.5 and pf.pt()>0.5 and pf.charge()!=0 and fabs(pf.dz()-dimu_dz)<0.05) ntracks++;
      }

      if (tag_trgmatched and pass_IsoMu and tag_iso<0.15 and muon::isMediumMuon((*muons)[index_mu1]) and mytag.DeltaR(myprobe)>0.5 and (mytag+myprobe).M()>50 and (mytag+myprobe).M()<150 and is_os) tree->Fill();
   }
}

// ------------ method called once each job just before starting event loop  ------------
void 
MuonAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MuonAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MuonAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonAnalyzer);
