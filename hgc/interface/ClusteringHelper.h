#ifndef CLUSTERINGHELPER_HH
#define CLUSTERINGHELPER_HH

#include "HGCal/Reco/interface/Clustering.h"
#include "HGCal/DataFormats/interface/MyHGCalRecHit.h"
#include <limits>
#include <algorithm>

template <typename T, typename S>
  class SortClusterByLayer
{
 public : 
  SortClusterByLayer(){;}
  ~SortClusterByLayer(){;}
    
  static bool sort(T* t, S* s){ return t->getLayerID() < s->getLayerID(); }
};

template <typename T, typename S>
  class SortClusterBySize
{
 public : 
  SortClusterBySize(){;}
  ~SortClusterBySize(){;}
    
  static bool sort(T* t, S* s){ return t->getHits().size() > s->getHits().size(); }
};

template <typename T, typename S>
  class SortClusterByEnergy
{
 public : 
  SortClusterByEnergy(){;}
  ~SortClusterByEnergy(){;}
    
  static bool sort(T* t, S* s){ return t->getHighGainEnergy() > s->getHighGainEnergy(); }
};

template <typename T, typename S>
  class DistanceBetweenCluster
{
 public : 
  DistanceBetweenCluster(){;}
  ~DistanceBetweenCluster(){;}
    
  float getDistance(T* t, S* s)
  {
    float minimum = std::numeric_limits<float>::max();
    for( std::vector<MyHGCalRecHit*>::iterator it=t->getHits().begin(); it!=t->getHits().end(); ++it ) 
      for( std::vector<MyHGCalRecHit*>::iterator jt=s->getHits().begin(); jt!=s->getHits().end(); ++jt ) {
    	minimum = std::min( minimum, (float)((*it)->getPosition()-(*jt)->getPosition()).mag() ); 
      }
    return minimum;
  }
};
#endif
