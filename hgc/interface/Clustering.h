#ifndef CLUSTERING_HH
#define CLUSTERING_HH

#include "HGCal/DataFormats/interface/MyHGCalRecHit.h"
#include "HGCal/DataFormats/interface/HGCalTBCluster2D.h"
#include <algorithm>

struct clusteringParameterSetting{
  int maxTransverse;
  bool useDistanceInsteadCellID;
  float maxTransverseDistance;
  bool useEnergyToWeightPosition;
  clusteringParameterSetting() : maxTransverse(1) ,
    useDistanceInsteadCellID(false),
    maxTransverseDistance(11.0),
    useEnergyToWeightPosition(false)
  {;}
};

class Clustering
{
public:
  Clustering(){;}
  ~Clustering(){;}    
  void Run(std::vector<MyHGCalRecHit*> &hits, std::vector<HGCalTBCluster2D*> &outClusterVec);
  inline void SetClusteringParameterSetting(clusteringParameterSetting val){settings=val;}

private:
  void BuildCluster(std::vector<MyHGCalRecHit*> &temp,
		    std::vector<MyHGCalRecHit*> &calohit,
		    MyHGCalRecHit* hit);

  std::vector<MyHGCalRecHit*> _clusterHitList;
    
  clusteringParameterSetting settings;
};

void Clustering::Run(std::vector<MyHGCalRecHit*> &hits,std::vector<HGCalTBCluster2D*> &outClusterVec)
{
  std::vector<MyHGCalRecHit*> temp;
  for( std::vector<MyHGCalRecHit*>::iterator it=hits.begin(); it!=hits.end(); ++it){
    if( std::find(temp.begin(),temp.end(),(*it))!=temp.end() ) continue;
    _clusterHitList.push_back(*it);
    temp.push_back(*it);
    BuildCluster(temp,hits,(*it));
    HGCalTBCluster2D* calocluster=new HGCalTBCluster2D(_clusterHitList, settings.useEnergyToWeightPosition );
    outClusterVec.push_back(calocluster);
    _clusterHitList.clear();
  }
  temp.clear();
}
  
void Clustering::BuildCluster(std::vector<MyHGCalRecHit*> &temp, std::vector<MyHGCalRecHit*> &hits,MyHGCalRecHit* hit)
{
  for(std::vector<MyHGCalRecHit*>::iterator it=hits.begin(); it!=hits.end(); ++it){
  
    // test if (*it) is already in one cluster
    if(std::find(temp.begin(), temp.end(), (*it) )!=temp.end() )
      continue;
      
    // test if (*it) and hit are in the same layer
    if( hit->getCellID()[2] != (*it)->getCellID()[2] )
      continue;
    
    if(!settings.useDistanceInsteadCellID){
      if( std::fabs( hit->getCellID()[0]-(*it)->getCellID()[0] )<=settings.maxTransverse &&
  	  std::fabs( hit->getCellID()[1]-(*it)->getCellID()[1] )<=settings.maxTransverse && 
	  std::fabs( (hit->getCellID()[0]-(*it)->getCellID()[0]) + (hit->getCellID()[1]-(*it)->getCellID()[1]) )<=settings.maxTransverse ){
  	_clusterHitList.push_back(*it);
  	temp.push_back(*it);
  	this->BuildCluster(temp,hits,*it);
      }
    }
    else{
      if( (hit->getPosition()-(*it)->getPosition()).mag() <= settings.maxTransverseDistance ){
  	_clusterHitList.push_back(*it);
  	temp.push_back(*it);
  	this->BuildCluster(temp,hits,*it);
      }
    }
  }
}

#endif
