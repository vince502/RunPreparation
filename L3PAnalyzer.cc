//system include files
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "CondFormats/HcalObjects/interface/HcalRespCorrs.h"
#include "CondFormats/DataRecord/interface/HcalRespCorrsRcd.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"

#include "DataFormats/TrackReco/interface/TrackToTrackMap.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
//#include "DataFormats/RecoCandidate/interface/RecoChargedRefCandidateFwd.h"
//#include "DataFormats/RecoCandidate/interface/RecoChargedRefCandidateFwd.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "EventFilter/HcalRawToDigi/interface/HcalDCCHeader.h"

#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"


// class decclaration
class L3PAnalyzer : public edm::EDAnalyzer {
public:
  explicit L3PAnalyzer(const edm::ParameterSet&);
  ~L3PAnalyzer() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void beginJob() override;
  void endJob() override;
  void beginRun(const edm::Run& r, const edm::EventSetup& iSetup) override;
  void endRun(const edm::Run& r, const edm::EventSetup& iSetup) override;

private:

  edm::Service<TFileService> fs_;
  double timeCut_;
  TTree* myTree_;

  static const int Max_mu_size = 10000;

  TClonesArray* TrackProducer_hltIterL3OIMuCtfWithMaterialTracksPPOnAA = new TClonesArray("TLorentzVector", Max_mu_size);
  TClonesArray* TrackProducer_hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA= new TClonesArray("TLorentzVector", Max_mu_size);
  TClonesArray* TrackProducer_hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA= new TClonesArray("TLorentzVector", Max_mu_size);
  TClonesArray* TrackProducer_hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA= new TClonesArray("TLorentzVector", Max_mu_size);
  TClonesArray* TrackProducer_hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA= new TClonesArray("TLorentzVector", Max_mu_size);
  TClonesArray* TrackProducer_hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA= new TClonesArray("TLorentzVector", Max_mu_size);
  TClonesArray* TrackProducer_hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA= new TClonesArray("TLorentzVector", Max_mu_size);

  TClonesArray* L3MuonProducer_hltL3MuonsIterL3OIPPOnAA= new TClonesArray("TLorentzVector", Max_mu_size);
  TClonesArray* L3MuonProducer_hltL3MuonsIterL3IOPPOnAA= new TClonesArray("TLorentzVector", Max_mu_size);
  TClonesArray* L3MuonProducer_hltIterL3GlbMuonPPOnAA  = new TClonesArray("TLorentzVector", Max_mu_size);

  TClonesArray* L3MuonCandidateProducer_hltIterL3OIL3MuonCandidatesPPOnAA      = new TClonesArray("TLorentzVector", Max_mu_size);
  TClonesArray* L3MuonCandidateProducerFromMuons_hltIterL3MuonCandidatesPPOnAA = new TClonesArray("TLorentzVector", Max_mu_size);

  TClonesArray* ConcreteChargedCandidateProducer_hltIter3IterL3MuonL2CandidatesPPOnAA = new TClonesArray("TLorentzVector", Max_mu_size);

  int  irun;
  unsigned long long ievt;
  double ipt, ieta, iphi;
  edm::EDGetTokenT<reco::TrackCollection> token_hltIterL3OIMuCtfWithMaterialTracksPPOnAA_;
  edm::EDGetTokenT<reco::TrackCollection> token_hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA_;
  edm::EDGetTokenT<reco::TrackCollection> token_hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA_;
  edm::EDGetTokenT<reco::TrackCollection> token_hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA_;
  edm::EDGetTokenT<reco::TrackCollection> token_hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA_;
  edm::EDGetTokenT<reco::TrackCollection> token_hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA_;
  edm::EDGetTokenT<reco::TrackCollection> token_hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA_;

  edm::EDGetTokenT<reco::TrackCollection> token_hltL3MuonsIterL3OIPPOnAA_;
  edm::EDGetTokenT<reco::TrackCollection> token_hltL3MuonsIterL3IOPPOnAA_;
  edm::EDGetTokenT<reco::TrackCollection> token_hltIterL3GlbMuonPPOnAA_;

  edm::EDGetTokenT<reco::RecoChargedCandidateCollection> token_hltIterL3OIL3MuonCandidatesPPOnAA_;
  edm::EDGetTokenT<reco::RecoChargedCandidateCollection> token_hltIterL3MuonCandidatesPPOnAA_;

  edm::EDGetTokenT<reco::RecoChargedCandidateCollection> token_hltIter3IterL3MuonL2CandidatesPPOnAA_;
};

L3PAnalyzer::L3PAnalyzer(const edm::ParameterSet& iConfig) {
  token_hltIterL3OIMuCtfWithMaterialTracksPPOnAA_ = consumes<reco::TrackCollection>(edm::InputTag("hltIterL3OIMuCtfWithMaterialTracksPPOnAA"));
  token_hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA_= consumes<reco::TrackCollection>(edm::InputTag("hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA"));
  token_hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA_= consumes<reco::TrackCollection>(edm::InputTag("hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA"));
  token_hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA_= consumes<reco::TrackCollection>(edm::InputTag("hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA"));
  token_hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA_= consumes<reco::TrackCollection>(edm::InputTag("hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA"));
  token_hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA_= consumes<reco::TrackCollection>(edm::InputTag("hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA"));
  token_hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA_= consumes<reco::TrackCollection>(edm::InputTag("hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA"));

  token_hltL3MuonsIterL3OIPPOnAA_= consumes<reco::TrackCollection>(edm::InputTag("hltL3MuonsIterL3OIPPOnAA"));
  token_hltL3MuonsIterL3IOPPOnAA_= consumes<reco::TrackCollection>(edm::InputTag("hltL3MuonsIterL3IOPPOnAA"));
  token_hltIterL3GlbMuonPPOnAA_  = consumes<reco::TrackCollection>(edm::InputTag("hltIterL3GlbMuonPPOnAA"));

  token_hltIterL3OIL3MuonCandidatesPPOnAA_  = consumes<reco::RecoChargedCandidateCollection>(edm::InputTag("hltIterL3OIL3MuonCandidatesPPOnAA"));
  token_hltIterL3MuonCandidatesPPOnAA_      = consumes<reco::RecoChargedCandidateCollection>(edm::InputTag("hltIterL3MuonCandidatesPPOnAA"));

  token_hltIter3IterL3MuonL2CandidatesPPOnAA_ = consumes<reco::RecoChargedCandidateCollection>(edm::InputTag("hltIter3IterL3MuonL2CandidatesPPOnAA"));
}

L3PAnalyzer::~L3PAnalyzer(){
} 

void L3PAnalyzer::beginRun(const edm::Run& r, const edm::EventSetup& iSetup) {}


void L3PAnalyzer::endRun(const edm::Run& r, const edm::EventSetup& iSetup) {
return;}

void L3PAnalyzer::beginJob(){
  myTree_ = fs_->make<TTree>("L3Track", "L3Track Tree");
  myTree_->Branch("Run", &irun, "Run/I");
  myTree_->Branch("Event", &ievt, "Event/I");
  myTree_->Branch("TrackProducer_hltIterL3OIMuCtfWithMaterialTracksPPOnAA","TClonesArray" , &TrackProducer_hltIterL3OIMuCtfWithMaterialTracksPPOnAA, 32000, 0);
  myTree_->Branch("TrackProducer_hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA","TClonesArray" , &TrackProducer_hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA, 32000, 0);
  myTree_->Branch("TrackProducer_hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA","TClonesArray" , &TrackProducer_hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA, 32000, 0);
  myTree_->Branch("TrackProducer_hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA","TClonesArray" , &TrackProducer_hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA, 32000, 0);
  myTree_->Branch("TrackProducer_hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA","TClonesArray" , &TrackProducer_hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA, 32000, 0);
  myTree_->Branch("TrackProducer_hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA","TClonesArray" , &TrackProducer_hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA, 32000, 0);
  myTree_->Branch("TrackProducer_hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA","TClonesArray" , &TrackProducer_hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA, 32000, 0);

  myTree_->Branch("L3MuonProducer_hltL3MuonsIterL3OIPPOnAA","TClonesArray" , &L3MuonProducer_hltL3MuonsIterL3OIPPOnAA, 32000, 0);
  myTree_->Branch("L3MuonProducer_hltL3MuonsIterL3IOPPOnAA","TClonesArray" , &L3MuonProducer_hltL3MuonsIterL3IOPPOnAA, 32000, 0);
  myTree_->Branch("L3MuonProducer_hltIterL3GlbMuonPPOnAA","TClonesArray" , &L3MuonProducer_hltIterL3GlbMuonPPOnAA  , 32000, 0);

  myTree_->Branch("L3MuonCandidateProducer_hltIterL3OIL3MuonCandidatesPPOnAA","TClonesArray" , &L3MuonCandidateProducer_hltIterL3OIL3MuonCandidatesPPOnAA , 32000, 0);
  myTree_->Branch("L3MuonCandidateProducerFromMuons_hltIterL3MuonCandidatesPPOnAA"   ,"TClonesArray" , &L3MuonCandidateProducerFromMuons_hltIterL3MuonCandidatesPPOnAA, 32000, 0);

  myTree_->Branch("ConcreteChargedCandidateProducer_hltIter3IterL3MuonL2CandidatesPPOnAA"   ,"TClonesArray" , &ConcreteChargedCandidateProducer_hltIter3IterL3MuonL2CandidatesPPOnAA, 32000, 0);

  std::cout << "Begin Job" << std::endl;
}

void L3PAnalyzer::endJob() {
 std::cout << "End Event"<< std::endl;
 edm::LogInfo("AnalyzerMu") << "next event";
}
void L3PAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup&) {
  edm::LogInfo("L3MuAnalzer") << " Start L3PAnalyzer::analyze " << iEvent.id().run() << ":" << iEvent.id().event();
  ievt = iEvent.id().event();
  irun = iEvent.id().run();
  std::cout << "Run/Event : " << irun << "/" << ievt << std::endl;
 /* for (const auto& n : pdM){
    const auto mname = n.first.first;
    const auto pname = n.first.second;
    const auto tname = "token_"+mname+"_";

    for (const auto& h : n.second){
//      const TString var = h;*/
//
      edm::Handle<reco::TrackCollection> hltIterL3OIMuCtfWithMaterialTracksPPOnAA;
      edm::Handle<reco::TrackCollection> hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA       ;
      edm::Handle<reco::TrackCollection> hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA       ;
      edm::Handle<reco::TrackCollection> hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA       ;
      edm::Handle<reco::TrackCollection> hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA ;
      edm::Handle<reco::TrackCollection> hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA ;
      edm::Handle<reco::TrackCollection> hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA ;
      edm::Handle<reco::TrackCollection> hltL3MuonsIterL3OIPPOnAA;
      edm::Handle<reco::TrackCollection> hltL3MuonsIterL3IOPPOnAA;
      edm::Handle<reco::TrackCollection> hltIterL3GlbMuonPPOnAA  ;
      edm::Handle<reco::RecoChargedCandidateCollection> hltIterL3OIL3MuonCandidatesPPOnAA;
      edm::Handle<reco::RecoChargedCandidateCollection> hltIterL3MuonCandidatesPPOnAA;
      edm::Handle<reco::RecoChargedCandidateCollection> hltIter3IterL3MuonL2CandidatesPPOnAA; 



     // std::cout <<"Handler initialize" << std::endl;
      iEvent.getByToken(token_hltIterL3OIMuCtfWithMaterialTracksPPOnAA_, hltIterL3OIMuCtfWithMaterialTracksPPOnAA);
      iEvent.getByToken(token_hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA_      , hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA      );
      iEvent.getByToken(token_hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA_      , hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA      );
      iEvent.getByToken(token_hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA_      , hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA      );
      iEvent.getByToken(token_hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA_, hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA);
      iEvent.getByToken(token_hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA_, hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA);
      iEvent.getByToken(token_hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA_, hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA);

      iEvent.getByToken(token_hltL3MuonsIterL3OIPPOnAA_, hltL3MuonsIterL3OIPPOnAA);
      iEvent.getByToken(token_hltL3MuonsIterL3IOPPOnAA_, hltL3MuonsIterL3IOPPOnAA);
      iEvent.getByToken(token_hltIterL3GlbMuonPPOnAA_, hltIterL3GlbMuonPPOnAA  );

      iEvent.getByToken(token_hltIterL3OIL3MuonCandidatesPPOnAA_, hltIterL3OIL3MuonCandidatesPPOnAA);
      iEvent.getByToken(token_hltIterL3MuonCandidatesPPOnAA_, hltIterL3MuonCandidatesPPOnAA);

      iEvent.getByToken(token_hltIter3IterL3MuonL2CandidatesPPOnAA_, hltIter3IterL3MuonL2CandidatesPPOnAA);




      if(hltIter3IterL3MuonL2CandidatesPPOnAA.isValid()){ 
      
      ConcreteChargedCandidateProducer_hltIter3IterL3MuonL2CandidatesPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      for(std::vector<reco::RecoChargedCandidate>::const_iterator idx = hltIter3IterL3MuonL2CandidatesPPOnAA->begin(); idx != hltIter3IterL3MuonL2CandidatesPPOnAA->end(); ++idx){

//        if((size%100)==0) std::cout << "hltIter3IterL3MuonL2CandidatesPPOnAA Track num: " << size << std::endl;
        auto pt  = idx->p4().pt();
        auto eta = idx->p4().eta();
        auto phi = idx->p4().phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*ConcreteChargedCandidateProducer_hltIter3IterL3MuonL2CandidatesPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }
  
  
      if(hltIterL3OIL3MuonCandidatesPPOnAA.isValid()){ 
      
      L3MuonCandidateProducer_hltIterL3OIL3MuonCandidatesPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(std::vector<reco::RecoChargedCandidate>::const_iterator idx = hltIterL3OIL3MuonCandidatesPPOnAA->begin(); idx != hltIterL3OIL3MuonCandidatesPPOnAA->end(); ++idx){
//        if((size%100)==0) std::cout << "hltIterL3OIL3MuonCandidatesPPOnAA Track num: " << size << std::endl;
        auto pt  = idx->p4().pt();
        auto eta = idx->p4().eta();
        auto phi = idx->p4().phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*L3MuonCandidateProducer_hltIterL3OIL3MuonCandidatesPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }
  
      if(hltIterL3MuonCandidatesPPOnAA.isValid()){ 
      
      L3MuonCandidateProducerFromMuons_hltIterL3MuonCandidatesPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(std::vector<reco::RecoChargedCandidate>::const_iterator idx = hltIterL3MuonCandidatesPPOnAA->begin(); idx != hltIterL3MuonCandidatesPPOnAA->end(); ++idx){
//        if((size%100)==0) std::cout << "hltIterL3MuonCandidatesPPOnAA Track num: " << size << std::endl;
        auto pt  = idx->p4().pt();
        auto eta = idx->p4().eta();
        auto phi = idx->p4().phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*L3MuonCandidateProducerFromMuons_hltIterL3MuonCandidatesPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }
  
  
      if(hltIterL3OIMuCtfWithMaterialTracksPPOnAA.isValid()){ 
    
      TrackProducer_hltIterL3OIMuCtfWithMaterialTracksPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltIterL3OIMuCtfWithMaterialTracksPPOnAA->size();idx++){
//        if((size%100)==0) std::cout << "hltIterL3OIMuCtfWithMaterialTracksPPOnAA Track num: " << size << std::endl;
        const reco::TrackRef track(hltIterL3OIMuCtfWithMaterialTracksPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*TrackProducer_hltIterL3OIMuCtfWithMaterialTracksPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }
  


      if(hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA.isValid()){ 
    
      TrackProducer_hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA->size();idx++){
//        if((size%100)==0) std::cout << "hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA Track num: " << size << std::endl;
        const reco::TrackRef track(hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*TrackProducer_hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }
      if(hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA.isValid()){ 
    
      TrackProducer_hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA->size();idx++){
//        if((size%100)==0) std::cout << "hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA Track num: " << size << std::endl;
        const reco::TrackRef track(hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*TrackProducer_hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }

      if(hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA.isValid()){ 
    
      TrackProducer_hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA->size();idx++){
//        if((size%100)==0) std::cout << "hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA Track num: " << size << std::endl;
        const reco::TrackRef track(hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*TrackProducer_hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }

      if(hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA.isValid()){ 
    
      TrackProducer_hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA->size();idx++){
//        if((size%100)==0) std::cout << "hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA Track num: " << size << std::endl;
        const reco::TrackRef track(hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*TrackProducer_hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }

      if(hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA.isValid()){ 
    
      TrackProducer_hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA->size();idx++){
//        if((size%100)==0) std::cout <<"hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA Track num: " << size << std::endl;
        const reco::TrackRef track(hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*TrackProducer_hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }

      if(hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA.isValid()){ 
    
      TrackProducer_hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA->size();idx++){
//        if((size%100)==0) std::cout << "hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA Track num: " << size << std::endl;
        const reco::TrackRef track(hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*TrackProducer_hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }


      if(hltL3MuonsIterL3OIPPOnAA.isValid()){ 
    
      L3MuonProducer_hltL3MuonsIterL3OIPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltL3MuonsIterL3OIPPOnAA->size();idx++){
//        if((size%100)==0) std::cout << "hltL3MuonsIterL3OIPPOnAA Track num: " << size << std::endl;
        const reco::TrackRef track(hltL3MuonsIterL3OIPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*L3MuonProducer_hltL3MuonsIterL3OIPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }

      if(hltL3MuonsIterL3IOPPOnAA.isValid()){ 
    
      L3MuonProducer_hltL3MuonsIterL3IOPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltL3MuonsIterL3IOPPOnAA->size();idx++){
//        if((size%100)==0) std::cout << "hltL3MuonsIterL3IOPPOnAA Track num: " << size << std::endl;
        const reco::TrackRef track(hltL3MuonsIterL3IOPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*L3MuonProducer_hltL3MuonsIterL3IOPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }

      if(hltIterL3GlbMuonPPOnAA.isValid()){ 
    
      L3MuonProducer_hltIterL3GlbMuonPPOnAA->Clear();
      int size = 0;
      TLorentzVector vMuon;
      //muon mass 0.1056583745 GeV
      
      for(unsigned int idx=0; idx<hltIterL3GlbMuonPPOnAA->size();idx++){
//        if((size%100)==0) std::cout << "hltIterL3GlbMuonPPOnAATrack num: " << size << std::endl;
        const reco::TrackRef track(hltIterL3GlbMuonPPOnAA, idx);
        auto pt = track->pt();
        auto eta =track->eta();
        auto phi = track->phi();
        vMuon.SetPtEtaPhiM(pt,eta,phi,0.1056583745);
        new((*L3MuonProducer_hltIterL3GlbMuonPPOnAA)[size])TLorentzVector(vMuon);

        size++;
      }

    }
    myTree_->Fill();
  }


#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(L3PAnalyzer);
