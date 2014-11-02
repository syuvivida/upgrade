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
   typedef std::map<unsigned int, unsigned int> mymap;
   mymap trkMaps;
   mymap::iterator it;

   for (std::vector<SimTrack>::iterator isimtk = theSimTracks.begin();
    	isimtk != theSimTracks.end(); ++isimtk){
     trkMaps.insert(std::pair<unsigned int,unsigned int>(isimtk->trackId(), nSimTrks_));
     
     nSimTrks_++;
     trkPhi_.push_back(isimtk->momentum().Phi());
     trkEta_.push_back(isimtk->momentum().Eta());
     trkPx_.push_back(isimtk->momentum().Px());
     trkPy_.push_back(isimtk->momentum().Py());
     trkPz_.push_back(isimtk->momentum().Pz());
     trkPt_.push_back(isimtk->momentum().Pt());
     trkE_.push_back(isimtk->momentum().E());
     trkCharge_.push_back(isimtk->charge());
     trkPID_.push_back(isimtk->type());
     trkGenIndex_.push_back(isimtk->genpartIndex());     
     trkNum_.push_back(isimtk->trackId());
     trkVtxIndex_.push_back(isimtk->vertIndex());

   }

   
   for (std::vector<SimVertex>::iterator isimvtx = theSimVertexes.begin();
	isimvtx != theSimVertexes.end(); ++isimvtx)
     {
       vtxX_.push_back(isimvtx->position().x());
       vtxY_.push_back(isimvtx->position().y());
       vtxZ_.push_back(isimvtx->position().z());
       nSimVtxs_++;
     }


   for (std::vector<PSimHit>::iterator isim = theTrackerHits.begin();
	isim != theTrackerHits.end(); ++isim){
    

     nSimHits_++;


     // create a DetId from the detUnitId
     DetId theDetUnitId(isim->detUnitId());
		
     // get the DetUnit via the DetUnitId and cast it to a StripGeomDetUnit
     const GeomDet * theDet = theTracker.idToDet(theDetUnitId);

  
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

     Local3DPoint entry3 = isim->entryPoint();
     GlobalPoint entry3_global = theDet->surface().toGlobal(entry3);

     hitEntryX_.push_back(entry3_global.x());
     hitEntryY_.push_back(entry3_global.y());
     hitEntryZ_.push_back(entry3_global.z());


     // relation with tracks
     it=trkMaps.find(isim->trackId());
     if(it!=trkMaps.end())
       hitTrkIndex_.push_back(it->second);
     else
       hitTrkIndex_.push_back(-1);
       
     hitTrkNum_.push_back(isim->trackId());

     Local3DPoint exit3  = isim->exitPoint();
     GlobalPoint exit3_global = theDet->surface().toGlobal(exit3);

     hitExitX_.push_back(exit3_global.x());
     hitExitY_.push_back(exit3_global.y());
     hitExitZ_.push_back(exit3_global.z());

     hitTof_.push_back(isim->timeOfFlight());
     hitEloss_.push_back(isim->energyLoss());

     hitPID_.push_back(isim->particleType());
     hitProcessType_.push_back(isim->processType());
 
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
  
  AddBranch(&hitGlobalX_,"hitGlobalX");
  AddBranch(&hitGlobalY_,"hitGlobalY");
  AddBranch(&hitGlobalZ_,"hitGlobalZ");
  AddBranch(&hitGlobalR_,"hitGlobalR");
  AddBranch(&hitGlobalPhi_,"hitGlobalPhi");
  AddBranch(&hitGlobalEta_,"hitGlobalEta");
  AddBranch(&hitGlobalDirectionX_,"hitGlobalDirectionX");
  AddBranch(&hitGlobalDirectionY_,"hitGlobalDirectionY");
  AddBranch(&hitGlobalDirectionZ_,"hitGlobalDirectionZ");

  AddBranch(&hitExitX_,"hitExitX");
  AddBranch(&hitExitY_,"hitExitY");
  AddBranch(&hitExitZ_,"hitExitZ");

  AddBranch(&hitEntryX_,"hitEntryX");
  AddBranch(&hitEntryY_,"hitEntryY");
  AddBranch(&hitEntryZ_,"hitEntryZ");

  AddBranch(&hitTof_,"hitTof");
  AddBranch(&hitEloss_,"hitEloss");

  AddBranch(&hitPID_,"hitPID");
  AddBranch(&hitProcessType_,"hitProcessType");
 
  AddBranch(&hitSubDec_,"hitSubDec");
  AddBranch(&hitLayer_,"hitLayer");  
  AddBranch(&hitLadder_,"hitLadder"); 
  AddBranch(&hitSide_,"hitSide");  
  AddBranch(&hitDisk_,"hitDisk"); 
  AddBranch(&hitBlade_,"hitBlade"); 
  AddBranch(&hitPanel_,"hitPanel"); 

  AddBranch(&hitModule_,"hitModule"); 
  AddBranch(&hitTrkIndex_,"hitTrkIndex"); 

  AddBranch(&hitTrkNum_,"hitTrkNum");


  AddBranch(&nSimTrks_,"nSimTrks"); 

  AddBranch(&trkE_,"trkE");
  AddBranch(&trkPx_,"trkPx");
  AddBranch(&trkPy_,"trkPy");
  AddBranch(&trkPz_,"trkPz");
  AddBranch(&trkPt_,"trkPt");
  AddBranch(&trkEta_,"trkEta");
  AddBranch(&trkPhi_,"trkPhi");
  AddBranch(&trkCharge_,"trkCharge");
  AddBranch(&trkPID_,"trkPID");

  AddBranch(&trkGenIndex_,"trkGenIndex");
  AddBranch(&trkNum_,"trkNum");
  AddBranch(&trkVtxIndex_,"trkVtxIndex");

  AddBranch(&nSimVtxs_,"nSimVtxs");
  AddBranch(&vtxX_,"vtxX");
  AddBranch(&vtxY_,"vtxY");
  AddBranch(&vtxZ_,"vtxZ");


}


void  
trkSimHitTree::Clear(){

  nSimHits_ = 0;
  
  hitGlobalX_.clear();
  hitGlobalY_.clear();
  hitGlobalZ_.clear();
  hitGlobalR_.clear();
  hitGlobalPhi_.clear();
  hitGlobalEta_.clear();
  hitGlobalDirectionX_.clear();
  hitGlobalDirectionY_.clear();
  hitGlobalDirectionZ_.clear();

  hitExitX_.clear();
  hitExitY_.clear();
  hitExitZ_.clear();

  hitEntryX_.clear();
  hitEntryY_.clear();
  hitEntryZ_.clear();

  hitTof_.clear();
  hitEloss_.clear();


  hitPID_.clear();
  hitProcessType_.clear();

  hitSubDec_.clear();
  hitLayer_.clear();  
  hitLadder_.clear(); 
  hitSide_.clear();  
  hitDisk_.clear(); 
  hitBlade_.clear(); 
  hitPanel_.clear(); 

  hitModule_.clear(); 

  hitTrkIndex_.clear();
  hitTrkNum_.clear();


  nSimTrks_ = 0;

  trkE_.clear();
  trkPx_.clear();
  trkPy_.clear();
  trkPz_.clear();
  trkPt_.clear();
  trkEta_.clear();
  trkPhi_.clear();
  trkCharge_.clear();

  trkPID_.clear();
  trkGenIndex_.clear();
  trkNum_.clear();
  trkVtxIndex_.clear();

  nSimVtxs_ = 0;
  vtxX_.clear();
  vtxY_.clear();
  vtxZ_.clear();


}
