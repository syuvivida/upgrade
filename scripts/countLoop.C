#define countLoop_cxx
#include "countLoop.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <string>

void countLoop::Loop()
{
  std::string title[2]={"Barrel","Endcap"};
  std::string subtitle[2]={"Layer","Disk"};
  TH1F* hcount_1d = new TH1F("hcount_1d","",5, 0.5,5.5);
  TH1F* htof = new TH1F("htof","",100,50,50);
  TH1F* h[2][15];
  TH1F* ht[2][15];
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

  TH2F* hcount = new TH2F("hcount","",15,0.5,15.5,5, 0.5,5.5);
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
  //nentries = 10;
  Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      std::cout<<" event "<<jentry<<std::endl;
      for(int i=0;i<10;i++)countB[i]=0;
      for(int i=0;i<15;i++)countE[i]=0;
      
      
      for(int i=0; i < hitSubDec->size(); i++){
	
	if(hitPID->at(i)!= -13)continue;
	Rentry = Rho((*hitEntryPointX)[i], (*hitEntryPointY)[i]);
	Rexit = Rho((*hitExitPointX)[i], (*hitExitPointY)[i]);
	int hitLayerIndex = hitLayer->at(i)-1;
	int hitDiskIndex = hitDisk->at(i)-1;

	std::cout<< hitSubDec->size()
		 <<"  "<<hitEntryPointX->size()
		 <<"  "<<hitExitPointX->size()
		 <<" hitGlobalEta = "<<(*hitGlobalEta)[i]
		 <<" hitGlobalPhi = "<<(*hitGlobalPhi)[i]
		 <<" X = "<<(*hitGlobalDirectionX)[i]
		 <<" Y = "<<(*hitGlobalDirectionY)[i]
		 <<" Z = "<<(*hitGlobalDirectionZ)[i]
		 <<" hitSubDec = "<<hitSubDec->at(i)
		 <<" hitPID = "<<hitPID->at(i)
	  //<<" Rentry = "<<Rentry
	  //	 <<" Rexit = "<<Rexit
		 <<" hitLayerIndex = "<<hitLayerIndex
		 <<" hitDiskIndex = "<<hitDiskIndex
		 <<std::endl;
	
	if(hitSubDec->at(i)==1) // for barrel 
	  {
	    if(Rentry < Rexit && countB[hitLayerIndex]>0)    std::cout<<" already one hit for this layer "<<hitLayerIndex<<"   "<<countB[hitLayerIndex]<<std::endl;
	    if(Rentry < Rexit && countB[hitLayerIndex]==0)   countB[hitLayerIndex]++;
	    if(Rentry > Rexit)   countB[hitLayerIndex]++;
	    
	    if(countB[hitLayerIndex]==1)
	      tofB[hitLayerIndex]= hitTof->at(i);
	    else if(countB[hitLayerIndex]>1)
	      ht[0][hitLayerIndex]->Fill(hitTof->at(i)-tofB[hitLayerIndex]);
	  }
	else
	  if(hitSubDec->at(i)==2) // for endcap
	    {
	      if(Rentry < Rexit && countE[hitDiskIndex]==0)   countE[hitDiskIndex]++;
	      if(Rentry < Rexit && countE[hitDiskIndex]>0)    std::cout<<" already one hit for this dosc endcap"<<std::endl;
	      if(Rentry > Rexit)   countE[hitDiskIndex]++;

	      //if((*hitEntryPointZ)[i]  < (*hitEntryPointZ)[i] && countE[hitDiskIndex]==0)   countE[hitDiskIndex]++;
	      //if((*hitEntryPointZ)[i]  < (*hitEntryPointZ)[i]  && countE[hitDiskIndex]>0)    std::cout<<" already one hit for this dosc endcap"<<std::endl;
	      //if((*hitEntryPointZ)[i]  > (*hitEntryPointZ)[i] )   countE[hitDiskIndex]++;
	      //countE[hitDiskIndex]++;
	      if(countE[hitDiskIndex]==1)
		tofE[hitDiskIndex]= hitTof->at(i);
	      else if(countE[hitDiskIndex]>1)
		ht[1][hitDiskIndex]->Fill(hitTof->at(i)-tofE[hitDiskIndex]);
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
    
            
   }

   hbarrel->Draw();
   hendcap->Draw();
   TFile* outFile = new TFile(outputfile_.data(),"recreate");       
   
   hbarrel->Write();
   hendcap->Write();
   for(int i=0;i<2;i++){
     for(int j=0; j<15;j++)
       {
	 h[i][j]->Write();
	 ht[i][j]->Write();
       }
   }

  outFile->Close();


}





double countLoop::Rho(double x, double y){
  double r = sqrt( (x*x) + (y*y) );
  return r;
}
