#include "DelPanj/TreeMaker/interface/trkSimHitTree.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

trkSimHitTree::trkSimHitTree(std::string name, TTree* tree):
  baseTree(name,tree)
{
  SetBranches();
}


trkSimHitTree::~trkSimHitTree()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
trkSimHitTree::Fill(const edm::Event& iEvent,  const edm::EventSetup& iSetup )
{
  Clear();
  if(iEvent.isRealData())return;

  using namespace edm;

  std::string SimTkLabel="g4SimHits";
  std::string SimVtxLabel="g4SimHits";
  std::string SimHitLabel="g4SimHits";

  std::vector<PSimHit> theTrackerHits;
  std::vector<SimTrack> theSimTracks;
  std::vector<SimVertex> theSimVertexes;

  Handle<SimTrackContainer> SimTk;
  Handle<SimVertexContainer> SimVtx;
  Handle<PSimHitContainer> PixelBarrelHitsLowTof;
  Handle<PSimHitContainer> PixelBarrelHitsHighTof;
  Handle<PSimHitContainer> PixelEndcapHitsLowTof;
  Handle<PSimHitContainer> PixelEndcapHitsHighTof;
  Handle<PSimHitContainer> TIBHitsLowTof;
  Handle<PSimHitContainer> TIBHitsHighTof;
  Handle<PSimHitContainer> TIDHitsLowTof;
  Handle<PSimHitContainer> TIDHitsHighTof;
  Handle<PSimHitContainer> TOBHitsLowTof;
  Handle<PSimHitContainer> TOBHitsHighTof;
  Handle<PSimHitContainer> TECHitsLowTof;
  Handle<PSimHitContainer> TECHitsHighTof;


  if(iEvent.getByLabel(SimTkLabel,SimTk))
    theSimTracks.insert(theSimTracks.end(),SimTk->begin(),SimTk->end());
  if(iEvent.getByLabel(SimVtxLabel,SimVtx))
    theSimVertexes.insert(theSimVertexes.end(),SimVtx->begin(),SimVtx->end());

  if(iEvent.getByLabel(SimHitLabel,"TrackerHitsPixelBarrelLowTof", PixelBarrelHitsLowTof))
    theTrackerHits.insert(theTrackerHits.end(), PixelBarrelHitsLowTof->begin(), PixelBarrelHitsLowTof->end()); 
  if(iEvent.getByLabel(SimHitLabel,"TrackerHitsPixelBarrelHighTof", PixelBarrelHitsHighTof))
    theTrackerHits.insert(theTrackerHits.end(), PixelBarrelHitsHighTof->begin(), PixelBarrelHitsHighTof->end());
  if(iEvent.getByLabel(SimHitLabel,"TrackerHitsPixelEndcapLowTof", PixelEndcapHitsLowTof))
    theTrackerHits.insert(theTrackerHits.end(), PixelEndcapHitsLowTof->begin(), PixelEndcapHitsLowTof->end()); 
  if(iEvent.getByLabel(SimHitLabel,"TrackerHitsPixelEndcapHighTof", PixelEndcapHitsHighTof))
    theTrackerHits.insert(theTrackerHits.end(), PixelEndcapHitsHighTof->begin(), PixelEndcapHitsHighTof->end());
  if(iEvent.getByLabel(SimHitLabel,"TrackerHitsTIBLowTof", TIBHitsLowTof))
     theTrackerHits.insert(theTrackerHits.end(), TIBHitsLowTof->begin(), TIBHitsLowTof->end()); 
   if(iEvent.getByLabel(SimHitLabel,"TrackerHitsTIBHighTof", TIBHitsHighTof))
     theTrackerHits.insert(theTrackerHits.end(), TIBHitsHighTof->begin(), TIBHitsHighTof->end());
   if(iEvent.getByLabel(SimHitLabel,"TrackerHitsTIDLowTof", TIDHitsLowTof))
     theTrackerHits.insert(theTrackerHits.end(), TIDHitsLowTof->begin(), TIDHitsLowTof->end()); 
   if(iEvent.getByLabel(SimHitLabel,"TrackerHitsTIDHighTof", TIDHitsHighTof))
     theTrackerHits.insert(theTrackerHits.end(), TIDHitsHighTof->begin(), TIDHitsHighTof->end());
   if(iEvent.getByLabel(SimHitLabel,"TrackerHitsTOBLowTof", TOBHitsLowTof))
     theTrackerHits.insert(theTrackerHits.end(), TOBHitsLowTof->begin(), TOBHitsLowTof->end()); 
   if(iEvent.getByLabel(SimHitLabel,"TrackerHitsTOBHighTof", TOBHitsHighTof))
     theTrackerHits.insert(theTrackerHits.end(), TOBHitsHighTof->begin(), TOBHitsHighTof->end());
   if(iEvent.getByLabel(SimHitLabel,"TrackerHitsTECLowTof", TECHitsLowTof))
     theTrackerHits.insert(theTrackerHits.end(), TECHitsLowTof->begin(), TECHitsLowTof->end()); 
   if(iEvent.getByLabel(SimHitLabel,"TrackerHitsTECHighTof", TECHitsHighTof))
     theTrackerHits.insert(theTrackerHits.end(), TECHitsHighTof->begin(), TECHitsHighTof->end());

  // access the tracker
   edm::ESHandle<TrackerGeometry> theTrackerGeometry;
   iSetup.get<TrackerDigiGeometryRecord>().get(theTrackerGeometry);
   const TrackerGeometry& theTracker(*theTrackerGeometry);

  // the DetUnits
   TrackingGeometry::DetContainer theDetUnits = theTracker.dets();
   
   for (std::vector<SimTrack>::iterator isimtk = theSimTracks.begin();
	isimtk != theSimTracks.end(); ++isimtk){

     


     edm::LogInfo("SimHitTrackerAnalyzer")<<" Track momentum  x = "<<isimtk->momentum().x() <<" y = "<<isimtk->momentum().y() <<" z = "<< isimtk->momentum().z();
     edm::LogInfo("SimHitTrackerAnalyzer")<<" Track momentum Ptx = "<<std::sqrt(isimtk->momentum().perp2());
   }

   for (std::vector<SimVertex>::iterator isimvtx = theSimVertexes.begin();
	isimvtx != theSimVertexes.end(); ++isimvtx){
     edm::LogInfo("SimHitTrackerAnalyzer")<<" Vertex position  x = "<<isimvtx->position().x() <<" y = "<<isimvtx->position().y() <<" z = "<< isimvtx->position().z();
   }


   std::map<unsigned int, std::vector<PSimHit>,std::less<unsigned int> > SimHitMap;

   for (std::vector<PSimHit>::iterator isim = theTrackerHits.begin();
	isim != theTrackerHits.end(); ++isim){

     // int PID = abs(isim->particleType());
     // if(PID!=13)continue;
     
     // if(PID== 22 || PID== 12 || PID== 14 || PID== 16 
     //  	|| PID== 130 || PID== 310 || PID== 311 || PID == 2112 || PID== 3122)continue;


     if(isim->processType()!=2)continue;

     // std::cout << "Hit from Process " << isim->processType() << " PID " << isim->particleType() << " " 
     // 	       << "Track Id " << isim->trackId() << std::endl;

     nSimHits_++;
     SimHitMap[(*isim).detUnitId()].push_back((*isim));


     // create a DetId from the detUnitId
     DetId theDetUnitId(isim->detUnitId());
		
     // get the DetUnit via the DetUnitId and cast it to a StripGeomDetUnit
     const GeomDet * theDet = theTracker.idToDet(theDetUnitId);

     hitLocalX_.push_back(isim->localPosition().x());
     hitLocalY_.push_back(isim->localPosition().y());
     hitLocalZ_.push_back(isim->localPosition().z());


     hitLocalDirectionX_.push_back(isim->localDirection().x());
     hitLocalDirectionY_.push_back(isim->localDirection().y());
     hitLocalDirectionZ_.push_back(isim->localDirection().z());
  
     GlobalPoint g3 = theDet->surface().toGlobal(isim->localPosition());
     hitGlobalX_.push_back(g3.x());
     hitGlobalY_.push_back(g3.y());
     hitGlobalZ_.push_back(g3.z());
     hitGlobalR_.push_back(g3.perp());
     hitGlobalPhi_.push_back(g3.phi());
     hitGlobalEta_.push_back(g3.eta());
     hitGlobalDirectionX_.push_back(theDet->surface().toGlobal(isim->localDirection()).x());
     hitGlobalDirectionY_.push_back(theDet->surface().toGlobal(isim->localDirection()).y());
     hitGlobalDirectionZ_.push_back(theDet->surface().toGlobal(isim->localDirection()).z());

     
     
     GlobalPoint entryp = theDet->surface().toGlobal(isim->entryPoint());
     GlobalPoint exitp = theDet->surface().toGlobal(isim->exitPoint());
     
     hitEntryPointX_.push_back(entryp.x());
     hitEntryPointY_.push_back(entryp.y());
     hitEntryPointZ_.push_back(entryp.z());
     
     hitExitPointX_.push_back(exitp.x());
     hitExitPointY_.push_back(exitp.y());
     hitExitPointZ_.push_back(exitp.z());

     
     std::cout <<" entry = ("<<entryp.x()<<", "<<entryp.y()<<", "<<entryp.z()<<"), "<<entryp.perp()<<std::endl;
     std::cout<<" exit = ("<<exitp.x()<<", "<<exitp.y()<<", "<<exitp.z()<<") , "<<exitp.perp()<<std::endl;
     

     if(entryp.perp() > exitp.perp()) std::cout<<" YES !!! THIS IS A LOOPER"<<std::endl;
     

     hitTof_.push_back(isim->timeOfFlight());
     hitEloss_.push_back(isim->energyLoss());

     hitPID_.push_back(isim->particleType());
 
     hitSubDec_.push_back(theDetUnitId.subdetId());

     Int_t tmp_layer =-999;
     Int_t tmp_ladder=-999;
     Int_t tmp_side  =-999;
     Int_t tmp_disk  =-999;
     Int_t tmp_blade =-999;
     Int_t tmp_panel =-999;
     Int_t tmp_module=-999;


     switch (theDetUnitId.subdetId())
       {
       case (int) PixelSubdetector::PixelBarrel:
	 {
	   tmp_layer = PXBDetId(theDetUnitId).layer();
	   tmp_ladder= PXBDetId(theDetUnitId).ladder();
           tmp_module= PXBDetId(theDetUnitId).module();
	 }
	 break;
       case (int) PixelSubdetector::PixelEndcap:
	 {
	   tmp_side  = PXFDetId(theDetUnitId).side();
	   tmp_disk  = PXFDetId(theDetUnitId).disk();
	   tmp_blade = PXFDetId(theDetUnitId).blade();
	   tmp_panel = PXFDetId(theDetUnitId).panel();
	   tmp_module= PXFDetId(theDetUnitId).module();
	 }
	 break;

       }
     
     hitLayer_.push_back(tmp_layer);  
     hitLadder_.push_back(tmp_ladder); 
     hitSide_.push_back(tmp_side);  
     hitDisk_.push_back(tmp_disk); 
     hitBlade_.push_back(tmp_blade); 
     hitPanel_.push_back(tmp_panel); 
     hitModule_.push_back(tmp_module); 

   } // end of loop over simHits

   
}



void  
trkSimHitTree::SetBranches(){

  AddBranch(&nSimHits_,"nSimHits"); 
  AddBranch(&hitLocalX_,"hitLocalX");
  AddBranch(&hitLocalY_,"hitLocalY");
  AddBranch(&hitLocalZ_,"hitLocalZ");
  AddBranch(&hitLocalDirectionX_,"hitLocalDirectionX");
  AddBranch(&hitLocalDirectionY_,"hitLocalDirectionY");
  AddBranch(&hitLocalDirectionZ_,"hitLocalDirectionZ");
  
  AddBranch(&hitGlobalX_,"hitGlobalX");
  AddBranch(&hitGlobalY_,"hitGlobalY");
  AddBranch(&hitGlobalZ_,"hitGlobalZ");
  AddBranch(&hitGlobalR_,"hitGlobalR");
  AddBranch(&hitGlobalPhi_,"hitGlobalPhi");
  AddBranch(&hitGlobalEta_,"hitGlobalEta");
  AddBranch(&hitGlobalDirectionX_,"hitGlobalDirectionX");
  AddBranch(&hitGlobalDirectionY_,"hitGlobalDirectionY");
  AddBranch(&hitGlobalDirectionZ_,"hitGlobalDirectionZ");

  AddBranch(&hitEntryPointX_,"hitEntryPointX");
  AddBranch(&hitEntryPointY_,"hitEntryPointY");
  AddBranch(&hitEntryPointZ_,"hitEntryPointZ");

  AddBranch(&hitExitPointX_,"hitExitPointX");
  AddBranch(&hitExitPointY_,"hitExitPointY");
  AddBranch(&hitExitPointZ_,"hitExitPointZ");


  AddBranch(&hitTof_,"hitTof");
  AddBranch(&hitEloss_,"hitEloss");

  AddBranch(&hitPID_,"hitPID");
 
  AddBranch(&hitSubDec_,"hitSubDec");
  AddBranch(&hitLayer_,"hitLayer");  
  AddBranch(&hitLadder_,"hitLadder"); 
  AddBranch(&hitSide_,"hitSide");  
  AddBranch(&hitDisk_,"hitDisk"); 
  AddBranch(&hitBlade_,"hitBlade"); 
  AddBranch(&hitPanel_,"hitPanel"); 

  AddBranch(&hitModule_,"hitModule"); 


}


void  
trkSimHitTree::Clear(){

  nSimHits_ = 0;
  hitLocalX_.clear();
  hitLocalY_.clear();
  hitLocalZ_.clear();
  hitLocalDirectionX_.clear();
  hitLocalDirectionY_.clear();
  hitLocalDirectionZ_.clear();
  
  hitGlobalX_.clear();
  hitGlobalY_.clear();
  hitGlobalZ_.clear();
  hitGlobalR_.clear();
  hitGlobalPhi_.clear();
  hitGlobalEta_.clear();
  hitGlobalDirectionX_.clear();
  hitGlobalDirectionY_.clear();
  hitGlobalDirectionZ_.clear();

  hitEntryPointX_.clear();
  hitEntryPointY_.clear();
  hitEntryPointZ_.clear();
  
  hitExitPointX_.clear();
  hitExitPointY_.clear();
  hitExitPointZ_.clear();

  hitTof_.clear();
  hitEloss_.clear();

  hitPID_.clear();


  hitSubDec_.clear();
  hitLayer_.clear();  
  hitLadder_.clear(); 
  hitSide_.clear();  
  hitDisk_.clear(); 
  hitBlade_.clear(); 
  hitPanel_.clear(); 

  hitModule_.clear(); 

}



