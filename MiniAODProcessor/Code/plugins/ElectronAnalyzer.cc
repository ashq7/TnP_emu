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

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/L1Trigger/interface/L1Candidate.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "DataFormats/L1Trigger/interface/L1TObjComparison.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Tau.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

using namespace reco;
using namespace std;
using namespace edm;


class ElectronAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit ElectronAnalyzer(const edm::ParameterSet&);
      ~ElectronAnalyzer();

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
      EDGetTokenT<pat::ElectronCollection> electronToken_;
      EDGetTokenT<std::vector<reco::Vertex>> vtxToken_;
      EDGetTokenT<l1t::EGammaBxCollection> l1elToken_;
      EDGetTokenT<l1t::TauBxCollection> l1tauToken_;
      EDGetTokenT<std::vector<PileupSummaryInfo>> pileupSummaryToken_;
      EDGetTokenT<pat::PackedCandidateCollection> pfToken_;

      // Declare the histograms
      TTree *tree;
      int ntracks;
      float tag_pt;
      float tag_eta;
      float tag_sceta;
      float tag_phi;
      float tag_dxy;
      float tag_dz;
      int tag_matchedToL1Tau;
      float probe_pt;
      float probe_eta;
      float probe_sceta;
      float probe_phi;
      float probe_dxy;
      float probe_dz;
      int probe_MVAisoWP90;
      int probe_MVAisoWP80;
      int probe_MVAisoWPLoose;
      int probe_matchHLTEle25;
      int probe_matchHLTEle27;
      int probe_matchHLTEle32;
      int probe_matchHLTEle35;
      int probe_matchHLTEle24Tau30;
      int probe_matchHLTMu23Ele12;
      int probe_matchHLTMu8Ele23;
      float trueNumInteractions;
      int puNumInteractions;
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
ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& iConfig):
    isMC_(iConfig.getParameter<bool>("isMC")),
    year_(iConfig.getParameter<int>("year")),
    triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
    triggerObjects_(consumes<std::vector<pat::TriggerObjectStandAlone> >(iConfig.getParameter<edm::InputTag>("objects"))),
    electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
    vtxToken_(consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("vertices"))),
    l1elToken_(consumes<l1t::EGammaBxCollection>(iConfig.getParameter<edm::InputTag>("l1electrons"))),
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
   tree->Branch("tag_sceta",&tag_sceta);
   tree->Branch("tag_phi",&tag_phi);
   tree->Branch("tag_dxy",&tag_dxy);
   tree->Branch("tag_dz",&tag_dz);
   tree->Branch("tag_matchedToL1Tau",&tag_matchedToL1Tau);
   tree->Branch("probe_pt",&probe_pt);
   tree->Branch("probe_eta",&probe_eta);
   tree->Branch("probe_sceta",&probe_sceta);
   tree->Branch("probe_phi",&probe_phi);
   tree->Branch("probe_dxy",&probe_dxy);
   tree->Branch("probe_dz",&probe_dz);
   tree->Branch("probe_MVAisoWP90",&probe_MVAisoWP90);
   tree->Branch("probe_MVAisoWP80",&probe_MVAisoWP80);
   tree->Branch("probe_MVAisoWPLoose",&probe_MVAisoWPLoose);
   tree->Branch("probe_matchHLTEle25",&probe_matchHLTEle25);
   tree->Branch("probe_matchHLTEle27",&probe_matchHLTEle27);
   tree->Branch("probe_matchHLTEle32",&probe_matchHLTEle32);
   tree->Branch("probe_matchHLTEle35",&probe_matchHLTEle35);
   tree->Branch("probe_matchHLTEle24Tau30",&probe_matchHLTEle24Tau30);
   tree->Branch("probe_matchHLTMu23Ele12",&probe_matchHLTMu23Ele12);
   tree->Branch("probe_matchHLTMu8Ele23",&probe_matchHLTMu8Ele23);
   tree->Branch("trueNumInteractions",&trueNumInteractions);
   tree->Branch("puNumInteractions",&puNumInteractions);

}


ElectronAnalyzer::~ElectronAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ElectronAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    int nElectrons=0;
    int index_el1=-1;
    int index_el2=-1;
    edm::Handle<pat::ElectronCollection> electrons;
    iEvent.getByToken(electronToken_, electrons);
    int i=-1;
    for (const pat::Electron &el : *electrons) {
	i++;
        if (el.pt() < 10 || fabs(el.eta())>2.5) continue;
	nElectrons++;
	if (index_el1<0) index_el1=i;
	else index_el2=i;
    }

    int tmp_index;
    if (iEvent.id().event()%2==0){
       tmp_index=index_el1;
       index_el1=index_el2;
       index_el2=tmp_index;
    }

    if (nElectrons==2){ 

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

      edm::Handle<l1t::EGammaBxCollection> l1electrons;
      iEvent.getByToken(l1elToken_, l1electrons);

      edm::Handle<l1t::TauBxCollection> l1taus;
      iEvent.getByToken(l1tauToken_, l1taus);

      tag_pt=(*electrons)[index_el1].pt();
      tag_eta=(*electrons)[index_el1].eta();
      tag_sceta=(*electrons)[index_el1].superCluster()->eta();
      tag_phi=(*electrons)[index_el1].phi();
      if (!(*electrons)[index_el1].gsfTrack().isNull()){ 
	 tag_dxy = (*electrons)[index_el1].gsfTrack()->dxy(reco::TrackBase::Point(pv_x, pv_y, pv_z));
         tag_dz = (*electrons)[index_el1].gsfTrack()->dz(reco::TrackBase::Point(pv_x, pv_y, pv_z));
      }
      else{
         tag_dxy = 0.0;
         tag_dz = 0.0;
      }

      probe_pt=(*electrons)[index_el2].pt();
      probe_eta=(*electrons)[index_el2].eta();
      probe_sceta=(*electrons)[index_el2].superCluster()->eta();
      probe_phi=(*electrons)[index_el2].phi();
      if (!(*electrons)[index_el2].gsfTrack().isNull()){
         probe_dxy = (*electrons)[index_el2].gsfTrack()->dxy(reco::TrackBase::Point(pv_x, pv_y, pv_z));
         probe_dz = (*electrons)[index_el2].gsfTrack()->dz(reco::TrackBase::Point(pv_x, pv_y, pv_z));
      }
      else{
         probe_dxy = 0.0;
         probe_dz = 0.0;
      }
      probe_MVAisoWP90=(*electrons)[index_el2].electronID("mvaEleID-Fall17-iso-V2-wp90");
      probe_MVAisoWP80=(*electrons)[index_el2].electronID("mvaEleID-Fall17-iso-V2-wp80");
      probe_MVAisoWPLoose=(*electrons)[index_el2].electronID("mvaEleID-Fall17-iso-V2-wpLoose");

      float l1pt=-100000;
      for (const l1t::EGamma &l1el : *l1electrons) {
         float l1dR = deltaR(probe_eta, probe_phi, l1el.eta(), l1el.phi());
	 if (l1dR<0.5 and fabs(l1el.pt()-probe_pt)<fabs(l1pt-probe_pt)) l1pt=l1el.pt();
      }

      tag_matchedToL1Tau=0;
      for (const l1t::Tau &l1tau : *l1taus) {
         float l1dR = deltaR(tag_eta, tag_phi, l1tau.eta(), l1tau.phi());
         if (l1tau.pt()>26 and l1dR<0.5) tag_matchedToL1Tau=1;
      }

      bool is_os=(((*electrons)[index_el1].charge()*(*electrons)[index_el2].charge())<0);

      Handle<edm::TriggerResults> triggerBits;
      iEvent.getByToken(triggerBits_, triggerBits);

      Handle<std::vector<pat::TriggerObjectStandAlone> > triggerObjects;
      iEvent.getByToken(triggerObjects_, triggerObjects);


       const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
       bool pass_trigger=false;
       bool tag_trgmatched=false;
       TString mypath="HLT_Ele32_WPTight_Gsf";
       if (year_==2016) mypath="HLT_Ele25_eta2p1_WPTight_Gsf";
       else if (year_==2017) mypath="HLT_Ele32_WPTight_Gsf";
       for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
	   TString TrigPath=names.triggerName(i);
	   if (triggerBits->accept(i) and TrigPath.Contains(mypath)) pass_trigger=true;
       }

       probe_matchHLTEle25=0;
       probe_matchHLTEle27=0;
       probe_matchHLTEle32=0;
       probe_matchHLTEle35=0;
       probe_matchHLTEle24Tau30=0;
       probe_matchHLTMu23Ele12=0;
       probe_matchHLTMu8Ele23=0;
       bool tag_extral1_2017=false;
       bool extral1_2017=false;
       for (pat::TriggerObjectStandAlone obj : *triggerObjects) { // note: not "const &" since we want to call unpackPathNames
           obj.unpackPathNames(names);
           obj.unpackNamesAndLabels(iEvent, *triggerBits);
	   float dR_tag = deltaR(tag_eta, tag_phi, obj.eta(), obj.phi());
           float dR_probe = deltaR(probe_eta, probe_phi, obj.eta(), obj.phi());
	   if (dR_tag<0.5){
	      for (unsigned h = 0; h < obj.filterLabels().size(); ++h){
	 	 TString filter = obj.filterLabels()[h];
		 if (year_==2018 and filter.Contains("hltEle32WPTightGsfTrackIsoFilter")) tag_trgmatched=true;
                 else if (year_==2017 and filter.Contains("hltEle32WPTightGsfTrackIsoFilter")) tag_trgmatched=true;
                 else if (year_==2016 and filter.Contains("hltEle25erWPTightGsfTrackIsoFilter")) tag_trgmatched=true;
                 if (year_==2017 and (filter.Contains("hltEGL1SingleEGOrFilter") or filter.Contains("hltL1sSingleEGor"))) tag_extral1_2017=true;
	      }
	   }
	   if (year_==2017 and !tag_extral1_2017) tag_trgmatched=false;

           if (dR_probe<0.5){
              for (unsigned h = 0; h < obj.filterLabels().size(); ++h){
                 TString filter = obj.filterLabels()[h];
                 if (year_==2016 and filter.Contains("hltEle25erWPTightGsfTrackIsoFilter")) probe_matchHLTEle25=1;
                 if (year_==2016 and filter.Contains("hltEle27WPTightGsfTrackIsoFilter")) probe_matchHLTEle27=1;
                 if ((year_==2017 or year_==2018) and filter.Contains("hltEle32WPTightGsfTrackIsoFilter")) probe_matchHLTEle32=1;
		 if (year_==2017 and filter.Contains("hltEle32L1DoubleEGWPTightGsfTrackIsoFilter")) probe_matchHLTEle32=1;
                 if (year_==2017 and (filter.Contains("hltEGL1SingleEGOrFilter") or filter.Contains("hltL1sSingleEGor"))) extral1_2017=true;
                 //if (filter.Contains("hltEle35noerWPTightGsfTrackIsoFilter")) probe_matchHLTEle35=1;
                 if ((year_==2017 or year_==2018) and filter.Contains("hltEle24erWPTightClusterShapeFilterForTau")) probe_matchHLTEle24Tau30=1;
                 if (l1pt>10 and filter.Contains("hltEle23Ele12CaloIdLTrackIdLIsoVLTrackIsoLeg2Filter")) probe_matchHLTMu23Ele12=1;
                 if (l1pt>20 and filter.Contains("hltEle23Ele12CaloIdLTrackIdLIsoVLTrackIsoLeg1Filter")) probe_matchHLTMu8Ele23=1;
              }
           }
       }
       if (year_==2017 and !extral1_2017) probe_matchHLTEle32=0; 

      TLorentzVector mytag;
      mytag.SetPtEtaPhiM(tag_pt,tag_eta,tag_phi,0);
      TLorentzVector myprobe;
      myprobe.SetPtEtaPhiM(probe_pt,probe_eta,probe_phi,0);

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

      ntracks=-2;
      Handle<pat::PackedCandidateCollection> pfs;
      iEvent.getByToken(pfToken_, pfs);
      float diele_dz=0.5*(tag_dz+probe_dz);
      for (unsigned int i = 0, n = pfs->size(); i < n; ++i) {
          const pat::PackedCandidate &pf = (*pfs)[i];
          if (fabs(pf.eta())<2.5 and pf.pt()>0.5 and pf.charge()!=0 and fabs(pf.dz()-diele_dz)<0.05) ntracks++;
      }

      float mvis=(mytag+myprobe).M();
      if ((*electrons)[index_el1].electronID("mvaEleID-Fall17-iso-V2-wp80") and tag_trgmatched and pass_trigger and mytag.DeltaR(myprobe)>0.5 and mvis>50 and mvis<150 and is_os) tree->Fill();
   }
}

// ------------ method called once each job just before starting event loop  ------------
void 
ElectronAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ElectronAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ElectronAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ElectronAnalyzer);
