#ifndef _TRK_SIMHIT_TREE_H_
#define _TRK_SIMHIT_TREE_H_

#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DelPanj/TreeMaker/interface/baseTree.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"

//
// class declaration
//
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DetectorDescription/Core/interface/DDCompactView.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/TrackerNumberingBuilder/interface/GeometricDet.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h" 
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h" 
#include "DataFormats/DetId/interface/DetId.h" 
#include "DataFormats/SiStripDetId/interface/StripSubdetector.h"
#include "DataFormats/SiStripDetId/interface/SiStripDetId.h"
#include "DataFormats/SiStripDetId/interface/TIDDetId.h"
#include "DataFormats/SiStripDetId/interface/TECDetId.h"
#include "DataFormats/SiStripDetId/interface/TIBDetId.h"
#include "DataFormats/SiStripDetId/interface/TOBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"



#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"


using namespace std;

class trkSimHitTree : public baseTree{

 public:
  trkSimHitTree(std::string name, TTree* tree);
  ~trkSimHitTree();
  void Fill(const edm::Event& iEvent, edm::EventSetup const& iSetup) ; 
  void SetBranches();
  void Clear();
  

  Int_t nSimHits_;
  std::vector<Float_t> hitLocalX_;
  std::vector<Float_t> hitLocalY_;
  std::vector<Float_t> hitLocalZ_;
  std::vector<Float_t> hitLocalDirectionX_;
  std::vector<Float_t> hitLocalDirectionY_;
  std::vector<Float_t> hitLocalDirectionZ_;

  std::vector<Float_t> hitGlobalX_;
  std::vector<Float_t> hitGlobalY_;
  std::vector<Float_t> hitGlobalZ_;
  std::vector<Float_t> hitGlobalR_;
  std::vector<Float_t> hitGlobalPhi_;
  std::vector<Float_t> hitGlobalEta_;
  std::vector<Float_t> hitGlobalDirectionX_;
  std::vector<Float_t> hitGlobalDirectionY_;
  std::vector<Float_t> hitGlobalDirectionZ_;

  // global information
  std::vector<Float_t> hitExitX_;
  std::vector<Float_t> hitExitY_;
  std::vector<Float_t> hitExitZ_;
  std::vector<Float_t> hitExitR_;

  std::vector<Float_t> hitEntryX_;
  std::vector<Float_t> hitEntryY_;
  std::vector<Float_t> hitEntryZ_;
  std::vector<Float_t> hitEntryR_;

  std::vector<Float_t> hitTof_;
  std::vector<Float_t> hitEloss_;

  std::vector<Int_t>   hitPID_;
  std::vector<Int_t>   hitProcessType_;

  std::vector<Int_t>   hitSubDec_;
  // variables for barrel
  std::vector<Int_t>   hitLayer_;  
  std::vector<Int_t>   hitLadder_; 
  // variables for endcap
  std::vector<Int_t>   hitSide_;  
  std::vector<Int_t>   hitDisk_; 
  std::vector<Int_t>   hitBlade_; 
  std::vector<Int_t>   hitPanel_; 
  
  // for both barrel and endcap
  std::vector<Int_t>   hitModule_; 

};

#endif
