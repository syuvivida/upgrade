#ifndef DATAFORMATS_HGCALTBCLUSTER2D_H
#define DATAFORMATS_HGCALTBCLUSTER2D_H 1

#include "HGCal/DataFormats/interface/MyHGCalRecHit.h"
#include "CLHEP/Vector/ThreeVector.h"
#include <vector>
#include <utility>
#include <iostream>
/** \class HGCalTBCluster2D
 *
 * \author Arnaud Steen
 */

class HGCalTBCluster2D
{
 public:
  HGCalTBCluster2D(std::vector<MyHGCalRecHit*> &vec, bool useWeight=0);
  ~HGCalTBCluster2D(){hits.clear();}

  inline std::vector<MyHGCalRecHit*> &getHits() {return hits;}
  inline CLHEP::Hep3Vector getPosition() const {return clusterPosition;}
  inline int getLayerID(){return layerID;}
  inline float getHighGainEnergy() const {return energy_HG;}
  inline float getLowGainEnergy() const {return energy_LG;}
 protected:
  std::vector<MyHGCalRecHit*> hits;
  CLHEP::Hep3Vector clusterPosition;
  float energy_HG;
  float energy_LG;
  int layerID;
};

HGCalTBCluster2D::HGCalTBCluster2D(std::vector<MyHGCalRecHit*> &vec, bool useWeight) : hits(vec) , energy_HG(0.0) , energy_LG(0.0)
{
  for(std::vector<MyHGCalRecHit*>::iterator it=hits.begin(); it!=hits.end(); ++it){
    if( useWeight )
      clusterPosition += (*it)->getPosition()*(*it)->getLowGainEnergy() ;
    else 
      clusterPosition += (*it)->getPosition();
    energy_HG+=(*it)->getHighGainEnergy();
    energy_LG+=(*it)->getLowGainEnergy();
  }
  if( useWeight ) 
    clusterPosition /= (hits.size()*energy_LG);
  else 
    clusterPosition /=hits.size();
  
  layerID=hits.at(0)->getCellID()[2];
}
#endif
