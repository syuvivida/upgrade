#ifndef __MUON_TREE_H_
#define __MUON_TREE_H_

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DelPanj/TreeMaker/interface/utils.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DelPanj/TreeMaker/interface/muSelector.h"
#include "DelPanj/TreeMaker/interface/baseTree.h"

using namespace std;
using namespace edm;

class patMuonTree : public baseTree {


 public:
  patMuonTree(std::string name, TTree* tree, const edm::ParameterSet& cfg);
  ~patMuonTree();
  void Fill(const edm::Event& iEvent);
  void SetBranches();
  void Clear();

 private:
//TTree* tree_;
  //Dont Allow User to Call the Default Constructor.
  patMuonTree();

  muSelector globalMuonID_;
  muSelector trackerMuonID_;
  edm::InputTag patMuonLabel_;



  std::vector<Int_t> patMuonType;
 //pt, eta, phi, M : Enough to caluclate
  //px,py,pz etc.==>No need to store later

  Int_t nMu_;
  std::vector<std::string> patMuonType_; 
  std::vector<Float_t> patMuonPt_;
  std::vector<Float_t> patMuonEta_;
  std::vector<Float_t> patMuonPhi_;
  std::vector<Float_t> patMuonM_;
  std::vector<Float_t> patMuonSumTrkPt_;
  std::vector<Float_t> patMuonTrkIso_;
  std::vector<Float_t> patMuonHcalIso_;
  std::vector<Float_t> patMuonEcalIso_;
  std::vector<Float_t> patMuonCorrTrkIso_;
  std::vector<Float_t> patMuonCharge_;


  std::vector<Float_t> patMuonChHadIso_;
  std::vector<Float_t> patMuonNeHadIso_;
  std::vector<Float_t> patMuonGamIso_;
  std::vector<Float_t> patMuonPUPt_;
  std::vector<Float_t> patMuonCorrPfIso_;
  std::vector<Float_t> patMuonTauCorrPfIso_;

  std::vector<Int_t> patMuonPassID_;


};

#endif

