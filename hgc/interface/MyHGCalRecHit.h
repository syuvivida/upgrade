#ifndef DATAFORMATS_MYHGCALRECHIT_H
#define DATAFORMATS_MYHGCALRECHIT_H 1

#include <iostream>
#include <CLHEP/Vector/ThreeVector.h>
/** \class MyHGCalRecHit
 *
 * \author Arnaud Steen
 */

class MyHGCalRecHit
  {
  public:
    MyHGCalRecHit(int* cellID, CLHEP::Hep3Vector vec,
		  float energyLG, float energyHG, 
		  float time);
    ~MyHGCalRecHit(){;}

    inline const CLHEP::Hep3Vector getPosition(){return _hitPosition;}
    inline const int* getCellID(){return _cellID;}
    inline const float getLowGainEnergy(){return _energyLG;}
    inline const float getHighGainEnergy(){return _energyHG;}
    inline const float getTime(){return _time;}


  private:
    int _cellID[3];
    CLHEP::Hep3Vector _hitPosition;
    float _energyLG;
    float _energyHG;
    float _time;
};

MyHGCalRecHit::MyHGCalRecHit(int* cellID, CLHEP::Hep3Vector vec, float energyLG, float energyHG, float time)
{
  for(int i=0; i<3; i++)
    _cellID[i]=cellID[i];
  _hitPosition=vec;
  _energyLG=energyLG;
  _energyHG=energyHG;
  _time=time;
}

#endif
