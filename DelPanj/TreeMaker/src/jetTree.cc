#include "DelPanj/TreeMaker/interface/jetTree.h"
#include <CLHEP/Vector/LorentzVector.h>
#include "FWCore/Framework/interface/ESHandle.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "TMath.h"
#include "Math/VectorUtil.h"

typedef math::XYZTLorentzVector LorentzVector;

jetTree::jetTree(std::string desc, TTree* tree, const edm::ParameterSet& iConfig):
  baseTree(desc, tree),
  JetLabel_(iConfig.getParameter<edm::InputTag>("Jets")),
  PrunedJetLabel_ ( iConfig.getParameter<edm::InputTag>("PrunedJets")),
  rhoSrc_   (iConfig.getParameter<edm::InputTag>("rhoSrc") ),                     
  pvSrc_    (iConfig.getParameter<edm::InputTag>("pvSrc") ),                      
  jet2012ID_()
{

  SetBranches();


}


jetTree::~jetTree(){

}


void
jetTree::Fill(const edm::Event& iEvent, edm::EventSetup const& iSetup){
  Clear();

  // Get the mean pt per unit area ("rho")                                     
  edm::Handle< double > h_rho;
  iEvent.getByLabel( rhoSrc_, h_rho );

  // Get the primary vertex collection                                         
  edm::Handle< std::vector<reco::Vertex> > h_pv;
  iEvent.getByLabel( pvSrc_, h_pv );


  edm::Handle<std::vector<pat::Jet> > JetHandle;
  iEvent.getByLabel(JetLabel_,JetHandle);

  if(not iEvent.getByLabel(JetLabel_,JetHandle)){
    std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "
	     <<JetLabel_<<std::endl; exit(0);}

  edm::Handle<std::vector<pat::Jet> > PrunedJetHandle;
  iEvent.getByLabel(PrunedJetLabel_,PrunedJetHandle);

  if(not iEvent.getByLabel(PrunedJetLabel_,PrunedJetHandle)){
    std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "
 	     <<PrunedJetLabel_<<std::endl; exit(0);}

  const std::vector<pat::Jet>* jets = JetHandle.product();
  std::vector<pat::Jet>::const_iterator jet =jets->begin();


  for(;jet!=jets->end();jet++){
    nJet_++;
    //Stuff common for all jets.

    JetTau1_.push_back(jet->userFloat("tau1"));
    JetTau2_.push_back(jet->userFloat("tau2"));
    JetTau3_.push_back(jet->userFloat("tau3"));
    JetTau4_.push_back(jet->userFloat("tau4"));

    // now making correction of jet energy


    JetPt_.push_back(jet->pt());
    JetEta_.push_back(jet->eta());
    JetPhi_.push_back(jet->phi());
    JetM_.push_back(jet->mass());
    JetEn_.push_back(jet->energy());

    std::map<std::string, bool> Pass = jet2012ID_.MergedJetCut(*jet);
    Int_t passOrNot = PassAll(Pass); 
    JetPassID_.push_back(passOrNot);
    
    // look for pruned jet

    Float_t dRmin = 99999.0;
    Float_t prunedpt =0;
    Float_t prunedeta=0;
    Float_t prunedphi=0;
    Float_t prunedm  =0;
    Float_t pruneden =0;


    //     reco::Candidate::LorentzVector uncorrPrunedJet(0,0,0,0);
    if(iEvent.getByLabel(PrunedJetLabel_,PrunedJetHandle)){
      for(pat::JetCollection::const_iterator jetPruned = PrunedJetHandle->begin(); 
	  jetPruned != PrunedJetHandle->end(); ++jetPruned) {
	Float_t dRtmp = ROOT::Math::VectorUtil::DeltaR(jet->p4(),jetPruned->p4());

	if(dRtmp<dRmin && dRtmp<0.8 ){//matching failed if greater than jet radius
	  dRmin=dRtmp;
	  prunedpt  =jetPruned->pt(); 
	  prunedeta =jetPruned->eta(); 
	  prunedphi =jetPruned->phi(); 
	  prunedm   =jetPruned->mass();
	  pruneden  =jetPruned->energy();
	}
      } // end of loop over PrunedJets
    } // if one could find CA8PrunedJet
      
    JetPrunedPt_.push_back(prunedpt);
    JetPrunedEta_.push_back(prunedeta);
    JetPrunedPhi_.push_back(prunedphi);
    JetPrunedM_.push_back(prunedm);
    JetPrunedEn_.push_back(pruneden);

    
  } // end of loop over jets


}



void
jetTree::SetBranches(){
  
  AddBranch(&nJet_, "nJet");
  AddBranch(&JetPt_, "jetPt");
  AddBranch(&JetEta_, "jetEta");
  AddBranch(&JetPhi_, "jetPhi");
  AddBranch(&JetM_, "jetMass");
  AddBranch(&JetEn_, "jetEn");
  AddBranch(&JetPassID_, "jetPassID");
  AddBranch(&JetPrunedPt_, "jetPrunedPt");
  AddBranch(&JetPrunedEta_, "jetPrunedEta");
  AddBranch(&JetPrunedPhi_, "jetPrunedPhi");
  AddBranch(&JetPrunedM_, "jetPrunedMass");
  AddBranch(&JetPrunedEn_, "jetPrunedEn");
  AddBranch(&JetTau1_,"jetTau1");
  AddBranch(&JetTau2_,"jetTau2");
  AddBranch(&JetTau3_,"jetTau3");
  AddBranch(&JetTau4_,"jetTau4");
}


void
jetTree::Clear(){
  nJet_ = 0;
  JetPt_.clear();
  JetEta_.clear();
  JetPhi_.clear();
  JetM_.clear();
  JetEn_.clear();
  JetPassID_.clear();
  JetPrunedPt_.clear();
  JetPrunedEta_.clear();
  JetPrunedPhi_.clear();
  JetPrunedM_.clear();
  JetPrunedEn_.clear();
  JetTau1_.clear();
  JetTau2_.clear();
  JetTau3_.clear();
  JetTau4_.clear();


}
