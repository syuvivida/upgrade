#ifndef PhysicsTools_TagAndProbe_TriggerCandProducer_h
#define PhysicsTools_TagAndProbe_TriggerCandProducer_h

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/ShallowCloneCandidate.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "PhysicsTools/TagAndProbe/interface/TriggerCandProducer.h"

#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "FWCore/Common/interface/TriggerNames.h" 
#include "DataFormats/PatCandidates/interface/Muon.h"

// forward declarations
template<class object>
class TriggerCandProducer : public edm::EDProducer 
{
 public:
  explicit TriggerCandProducer(const edm::ParameterSet&);
  ~TriggerCandProducer();

 private:
  virtual void beginRun(edm::Run& iRun, edm::EventSetup const& iSetup);
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data --------------------------
    
  edm::InputTag _inputProducer;
  edm::InputTag triggerEventTag_;
  edm::InputTag triggerResultsTag_;
  std::vector<edm::InputTag> hltTags_;
  edm::InputTag theRightHLTTag_;
  double delRMatchingCut_;
  std::string filterName_;
  bool storeRefCollection_;
  double objEtMin_;
  double objEtaMax_;
  bool isTriggerOR_;
  bool isFilter_;
  bool antiSelect_;
  bool noHltFiring_;
  bool printIndex_;
  bool changed_;
  HLTConfigProvider hltConfig_;
  bool skipEvent_;
  bool matchUnprescaledTriggerOnly_;
};
#include "PhysicsTools/TagAndProbe//src/TriggerCandProducer.icc"
#endif
