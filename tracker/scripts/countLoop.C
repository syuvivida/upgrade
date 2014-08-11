#define countLoop_cxx
#include "countLoop.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <string>
#include <iostream>
#include "TProfile.h"
#define vel_of_light 0.3  // speed of light in m/ns

using namespace std;
void countLoop::Loop()
{
  bool debug = false;
  bool onlyMuons = false; // true : save information of muons only 
                          // false : save information of all the particles in the tree
  
  int nhits_[2][15][7];
  
  // clear vectors
  pdgid_.clear();
  
  
  pdgid_.push_back(11);    // electron
  pdgid_.push_back(13);    // muon
  pdgid_.push_back(22);    // photon
  pdgid_.push_back(211);   // pion
  pdgid_.push_back(321);   // kaon
  pdgid_.push_back(2112);  // neutron
  pdgid_.push_back(2212);  // proton
  
  
  std::string title[2]={"Barrel","Endcap"};
  std::string subtitle[2]={"Layer","Disk"};
  TH1F* hcount_1d = new TH1F("hcount_1d","",100, 0.5,100.5);
  TH1F* htof      = new TH1F("htof","",1000,0.1,100);
  TProfile* hdistance = new TProfile("hdistance","hdistance",15, 0, 15,0,500);
  TH1F* hrho      = new TH1F("hrho","hrho",300, 0.5, 300.5);
  
  TH2F* hZ_vs_R   = new TH2F("hZ_vs_R","hZ_vs_R", 600, -300, 300, 120, 0, 120);
  TH2F* hX_vs_Y   = new TH2F("hX_vs_Y","hX_vs_Y",1000, -500, 500, 1000, -500, 500);

  TH1F* h[2][15];
  TH1F* ht[2][15];
  const int pdgidSize = pdgid_.size();
  TProfile* hDistance[2][pdgidSize];
  for(int k=0;k<2; k++){
    for(int i=0;i<(int)pdgid_.size();i++){
      hDistance[k][i] = (TProfile*)hdistance->Clone(Form("hDistance_%s_%d",title[k].data(), pdgid_[i]));
      hDistance[k][i]->SetXTitle("layer/disk number");
      hDistance[k][i]->SetTitle(Form("distance for particle %d",pdgid_[i]));
    }
  }
  for(int k=0;k<2; k++){
    for(int i=0;i<15;i++){

      h[k][i]=(TH1F*)hcount_1d->Clone(Form("h%d%02i",k,i));
      h[k][i]->SetXTitle("Number of crossings per particle");
      h[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			     subtitle[k].data(),i+1));

      ht[k][i]=(TH1F*)htof->Clone(Form("ht%d%02i",k,i));
      ht[k][i]->SetXTitle("Difference of TOF from the first hit: ns");
      ht[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));

    }
  }

  TH2F* hcount = new TH2F("hcount","",15,0.5,15.5,100, 0.5,100.5);
  TH2F* hbarrel = (TH2F*)hcount->Clone("hbarrel");
  hbarrel->SetTitle("Barrel");
  hbarrel->SetXTitle("Layer");
  hbarrel->SetYTitle("Number of crossings per particle");
  TH2F* hendcap = (TH2F*)hcount->Clone("hendcap");
  hendcap->SetTitle("Endcaps");
  hendcap->SetXTitle("Disk");
  hendcap->SetYTitle("Number of crossings per particle");

  int countB[10]={0};
  int countE[15]={0};
  float tofB[10]={0.};
  float tofE[15]={0.};
  

  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  //nentries = 20;
  Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      std::cout<<" event "<<jentry<<std::endl;
      for(int i=0;i<10;i++)countB[i]=0;
      for(int i=0;i<15;i++)countE[i]=0;
      for(int i=0;i<2;i++){
	for(int j=0;j<15;j++){
	  for(int k=0;k<7;k++){
	    nhits_[i][j][k]=0;
	  }}}
      
      
      for(int i=0; i < hitSubDec->size(); i++){
	
	if(onlyMuons && hitPID->at(i)!= -13) continue;
	
	hZ_vs_R->Fill((*hitGlobalZ)[i], Rho((*hitGlobalX)[i], (*hitGlobalY)[i]));

	if((*hitSubDec)[i]==1) hX_vs_Y->Fill((*hitGlobalX)[i], (*hitGlobalY)[i]);
	
	int index = std::find(pdgid_.begin(), pdgid_.end(),  abs(hitPID->at(i))) - pdgid_.begin();
	if(debug) std::cout<<" pdgid = "<<hitPID->at(i)<<"  index = "<<index<<std::endl;
	if(index != pdgid_.size() ){
	  int subdet = (*hitSubDec)[i] -1;
	  int layer  = (*hitLayer)[i] -1;
	  int disk   = (*hitDisk)[i] -1;
	  if(debug) std::cout<<" subdet = "<<subdet
		   <<" layer = "<<layer
		   <<" disk = "<<disk
		   <<std::endl;
	  if(subdet==0)  nhits_[0][layer][index]++;
	  if(subdet==1)  nhits_[1][disk][index]++;
	}
	
	Rentry = Rho((*hitEntryPointX)[i], (*hitEntryPointY)[i]);
	Rexit = Rho((*hitExitPointX)[i], (*hitExitPointY)[i]);
	int hitLayerIndex = hitLayer->at(i)-1;
	int hitDiskIndex = hitDisk->at(i)-1;
	
	if(debug)
	  std::cout<<" Eta = "<<(*hitGlobalEta)[i]
		   <<" Phi = "<<(*hitGlobalPhi)[i]
		   <<" X = "<<(*hitGlobalX)[i]
		   <<" Y = "<<(*hitGlobalY)[i]
		   <<" Z = "<<(*hitGlobalZ)[i]
		   <<" rho = "<<Rho((*hitGlobalX)[i],(*hitGlobalY)[i])
		   <<" X = "<<(*hitGlobalDirectionX)[i]
		   <<" Y = "<<(*hitGlobalDirectionY)[i]
		   <<" Z = "<<(*hitGlobalDirectionZ)[i]
		   <<" hitLayerIndex = "<<hitLayerIndex
		   <<" hitDiskIndex = "<<hitDiskIndex
		   <<" tof = "<<hitTof->at(i)
		   <<std::endl;
	
	if(hitSubDec->at(i)==1) // for barrel 
	  {
	    countB[hitLayerIndex]++;
	    double R = Rho( (*hitGlobalR)[i], (*hitGlobalZ)[i]);
	    double tof_ = hitTof->at(i) - ( R / vel_of_light ) ;
	    //ht[0][hitLayerIndex]->Fill(hitTof->at(i));
	    ht[0][hitLayerIndex]->Fill(tof_);
	    
	  }
	else
	  if(hitSubDec->at(i)==2) // for endcap
	    {
	      countE[hitDiskIndex]++;
	      double R = Rho( (*hitGlobalR)[i], (*hitGlobalZ)[i]);
	      double tof_ = hitTof->at(i) - ( R / vel_of_light ) ;
	      ht[1][hitDiskIndex]->Fill(tof_);
	    }
      }
   
      
      for(int i=0;i<10;i++){
	hbarrel->Fill(i+1,countB[i]);
	h[0][i]->Fill(countB[i]);
	std::cout<<" countB = "<<countB[i]<<std::endl;

      }
      for(int i=0;i<15;i++){
	hendcap->Fill(i+1,countE[i]);
	h[1][i]->Fill(countE[i]);
	std::cout<<" countE = "<<countE[i]<<std::endl;
      }
   
            
      for(int i=0;i<2;i++){
	for(int j=0;j<15;j++){
	  for(int k=0;k<7;k++){
	    hDistance[i][k]->Fill(j,nhits_[i][j][k]);
	  }}}
   
   }
   
   hbarrel->Draw();
   hendcap->Draw();
   TFile* outFile = new TFile(outputfile_,"recreate");       
   
   hbarrel->Write();
   hendcap->Write();
   for(int i=0;i<2;i++){
     for(int j=0; j<15;j++)
       {
	 h[i][j]->Write();
	 ht[i][j]->Write();
       }
   }
   for(int k=0;k<2;k++){
     for(int i=0;i<(int)pdgid_.size();i++){
       hDistance[k][i]->Write();
     }
   }
   hZ_vs_R->Write();
   hX_vs_Y->Write();
   outFile->Close();


}





double countLoop::Rho(double x, double y){
  double r = TMath::Sqrt( (x*x) + (y*y) );
  return r;
}
