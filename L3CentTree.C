#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>
#include <iostream>
#include <iomanip>
#include <memory>
#include <TTree.h>
#include <string>
#include "../TriggerStudy/RunPreparation/TriggerStudy/Cent_plotTurnOn.h"

void L3CentTree(){

  TFile* l3t = new TFile("6v_L3.root", "update");
//  TFile* resl3 = new TFile("L3_result.root", "recreate");

  std::string reco = "/Users/soohwanlee/RunPreparation/store/Forest_HIMinimumBias2_run327237_merged.root";

  RecoReader recoInfo(reco, false);
  TTree* t1 =(TTree*) l3t->Get("l3pAnalyzer/L3Track");
  
  TTreeReader r1 = TTreeReader("l3pAnalyzer/L3Track", l3t);
  TTreeReaderValue<int> Run = {r1, "Run"};
  TTreeReaderValue<int> Event = {r1, "Event"};
  int centI;
  t1->Branch("hiBin", &centI, "hiBin/I");

  const auto nEntries = recoInfo.getEntries();
  long long count = 0 ;
  for (int iEntry=0; iEntry <nEntries; ++iEntry){
    if ((iEntry%100000)==0){std::cout << "Processing event " << iEntry << " / " << nEntries << std::endl;}
    recoInfo.setEntry(iEntry, false, true);
    std::pair<Long64_t, Long64_t> evtInfo = recoInfo.getEventNumber();
    if(evtInfo.second <151999999 || evtInfo.second > 153000000){continue;}

    count++;
    std::cout << "Event: " << evtInfo.second << std::endl;

    if(evtInfo.second == 152659048 ){std::cout<< "test"<< std::endl;}   

        while(r1.Next()){
	if( evtInfo.first == *Run && evtInfo.second == *Event ){
	  std::cout<< "Found hibin"<<", in Event(L3/reco): " << *Event<<" / " << evtInfo.second  << std::endl;
          const auto bObj = recoInfo.getCentrality();
          centI = (int) bObj;
          t1->Fill();
          break;
        }

      }

    r1.Restart();
    centI=0;

    }
    std::cout <<"Number of event: "<< count << std::endl;
    r1.Delete();
    t1->SetTitle("updated_track");
    l3t->Write();
    l3t->Close();

}
