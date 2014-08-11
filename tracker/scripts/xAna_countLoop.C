#include <vector>
#include <iostream>
#include <fstream>
#include <TH2.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "untuplizer.h"

using namespace std;

void xAna_countLoop(std::string fin){

  std::string title[2]={"Barrel","Endcap"};
  std::string subtitle[2]={"Layer","Disk"};
  TH1F* hcount_1d = new TH1F("hcount_1d","",5, 0.5,5.5);
  TH1F* htof = new TH1F("htof","",100,-5,5);
  TH1F* h[2][15];
  TH1F* ht[2][15];
  for(int k=0;k<2; k++){
    for(int i=0;i<15;i++){
      
      h[k][i]=(TH1F*)hcount_1d->Clone(Form("h%d%02i",k,i));
      h[k][i]->SetXTitle("Number of crossings per particle");
      h[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			     subtitle[k].data(),i+1));

      ht[k][i]=(TH1F*)htof->Clone(Form("ht%d%02i",k,i));
      ht[k][i]->SetXTitle("Difference of TOF from the neighbouring layer: ns");
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
  int backB[10]={0};
  int backE[15]={0};
  float tofB[10]={-1};
  float tofE[15]={-1};

  // get TTree from file ...
  TreeReader data(fin.data()); // v5.3.12

  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) {
    // print progress
    if (ev % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
    data.GetEntry(ev);
    for(int i=0;i<10;i++){countB[i]=0; backB[i]=0; tofB[i]=-1.;}
    for(int i=0;i<15;i++){countE[i]=0; backE[i]=0; tofE[i]=-1.;}

    Int_t  nHits = data.GetInt("nSimHits");
    Int_t* decID = data.GetPtrInt("hitSubDec");
    Int_t* PID   = data.GetPtrInt("hitPID");
    Int_t* proc  = data.GetPtrInt("hitProcessType");
    Int_t* layer = data.GetPtrInt("hitLayer");
    Int_t* disk  = data.GetPtrInt("hitDisk");

    Float_t* exitR = data.GetPtrFloat("hitExitR");
    Float_t* entryR = data.GetPtrFloat("hitEntryR");
    Float_t* tof    = data.GetPtrFloat("hitTof");
 
    for(int i=0; i < nHits; i++){

      if(PID[i]!= +13) continue;
      if(proc[i]!= 2) continue;
      int hitLayerIndex = layer[i]-1;
      int hitDiskIndex  = disk[i]-1;
      
      int status = 0; // 0: undefined, -1: ingoing, 1: outgoing
	
      if(exitR[i] > entryR[i])status=1;
      else status=-1;

      if(decID[i]==1)
	{
	  countB[hitLayerIndex]++;
	  if(status==-1)backB[hitLayerIndex]++;
	  if(countB[hitLayerIndex]==1 && status==1)
	    tofB[hitLayerIndex]= tof[i];
	}
      else if(decID[i]==2)
	{
	  countE[hitDiskIndex]++;
	  if(status==-1)backE[hitDiskIndex]++;
	  if(countE[hitDiskIndex]==1 && status==1)
	    tofE[hitDiskIndex]= tof[i];
	}
      
    } // loop over number of hits in each event
    
    for(int i=0;i<10;i++){
      if(backB[i]>0)countB[i]=1+backB[i];
      else countB[i]=1;
      hbarrel->Fill(i+1,countB[i]);
      h[0][i]->Fill(countB[i]);
      if(i!=9 && tofB[i]>1e-6 && tofB[i+1]>1e-6)
	ht[0][i]->Fill(tofB[i+1]-tofB[i]);

    }
    for(int i=0;i<15;i++){
      if(backE[i]>0)countE[i]=1+backE[i];
      else countE[i]=1;
      hendcap->Fill(i+1,countE[i]);
      h[1][i]->Fill(countE[i]);
      if(i!=14 && tofE[i]>1e-6 && tofE[i+1]>1e-6)
	ht[1][i]->Fill(tofE[i+1]-tofE[i]);

    }
      
      
  } // event loop

  TFile* outFile = new TFile("histo.root","recreate");       
   
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
