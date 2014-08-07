#ifndef __JET_TREE_H_
#define __JET_TREE_H_





#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DelPanj/TreeMaker/interface/utils.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DelPanj/TreeMaker/interface/baseTree.h"
#include "DelPanj/TreeMaker/interface/jetSelector.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include <boost/shared_ptr.hpp>


using namespace std;
using namespace edm;



class jetTree  : public baseTree{

 public:
  jetTree(std::string name, TTree* tree, const edm::ParameterSet& cfg);//name=patJetAk05
  ~jetTree();
  void Fill(const edm::Event& iEvent, edm::EventSetup const& iSetup) ; 
  void SetBranches();
  void Clear();
 
 private:
  jetTree();


  edm::InputTag JetLabel_;
  edm::InputTag PrunedJetLabel_;
  edm::InputTag rhoSrc_;
  edm::InputTag pvSrc_;



  jetSelector jet2012ID_;

 

  //Branches common to all the jets.
  Int_t nJet_;
  std::vector<Float_t> JetPt_;
  std::vector<Float_t> JetEta_;
  std::vector<Float_t> JetPhi_;
  std::vector<Float_t> JetM_;
  std::vector<Float_t> JetEn_;
  std::vector<Int_t>   JetPassID_;
  std::vector<Float_t> JetPrunedPt_;
  std::vector<Float_t> JetPrunedEta_;
  std::vector<Float_t> JetPrunedPhi_;
  std::vector<Float_t> JetPrunedM_;
  std::vector<Float_t> JetPrunedEn_;
  std::vector<Float_t> JetTau1_;
  std::vector<Float_t> JetTau2_;
  std::vector<Float_t> JetTau3_;
  std::vector<Float_t> JetTau4_;

};

#endif
