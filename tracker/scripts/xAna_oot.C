#include <vector>
#include <iostream>
#include <fstream>
#include <TH2.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "untuplizer.h"

using namespace std;

void xAna_oot(std::string fin, float readoutWindow=3){ // readoutWindow default = +-3ns

  std::string title[2]={"Barrel","Endcap"};
  std::string subtitle[2]={"Layer","Disk"};

  const int nBunches = 20;
  TH1F* htof     = new TH1F("htof","", 500,0, 500);
  TH1F* hetof    = new TH1F("hetof","", 100,0, 20);
  TH1F* hread    = new TH1F("hread","",nBunches,0,(float)(nBunches));
  TH1F* ht[2][15];
  TH1F* hdiff[2][15];
  TH1F* het[2][15];
  TH1F* hr[2][15];
  for(int k=0;k<2; k++){
    for(int i=0;i<15;i++){

     
      ht[k][i]=(TH1F*)htof->Clone(Form("ht%d%02i",k,i));
      ht[k][i]->SetXTitle("Simulated time of flight: ns");
      ht[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));

      hdiff[k][i]=(TH1F*)htof->Clone(Form("hdiff%d%02i",k,i));
      hdiff[k][i]->SetXTitle("Difference of TOF from expectation: ns");
      hdiff[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));

      het[k][i]=(TH1F*)hetof->Clone(Form("het%d%02i",k,i));
      het[k][i]->SetXTitle("Expected time of flight: ns");
      het[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));

      hr[k][i]=(TH1F*)hread->Clone(Form("hr%d%02i",k,i));
      hr[k][i]->SetXTitle("Number of bunch crossings");
      hr[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));
      
    }
  }

  // get TTree from file ...
  TreeReader data(fin.data()); // v5.3.12

  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) {
    // print progress
    if (ev % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
    data.GetEntry(ev);

    Int_t  nHits = data.GetInt("nSimHits");
    Int_t* decID = data.GetPtrInt("hitSubDec");
    Int_t* PID   = data.GetPtrInt("hitPID");
    Int_t* proc  = data.GetPtrInt("hitProcessType");
    Int_t* layer = data.GetPtrInt("hitLayer");
    Int_t* disk  = data.GetPtrInt("hitDisk");

    Float_t* tof    = data.GetPtrFloat("hitTof");


    Float_t* gx    = data.GetPtrFloat("hitGlobalX");
    Float_t* gy    = data.GetPtrFloat("hitGlobalY");
    Float_t* gz    = data.GetPtrFloat("hitGlobalZ");

 
    for(int i=0; i < nHits; i++){

      int hitLayerIndex = layer[i]-1;
      int hitDiskIndex  = disk[i]-1;

      Float_t pathlength = sqrt(gx[i]*gx[i] +
				gy[i]*gy[i] +
				gz[i]*gz[i]);
      Float_t expectedTime = pathlength/30;

      Float_t time = tof[i];

      Float_t tdiff = fabs(time-expectedTime);

      Int_t decIndex = decID[i]-1;
	
      int subLayerIndex = decIndex==0? hitLayerIndex: hitDiskIndex;

      ht[decIndex][subLayerIndex]->Fill(time);
      het[decIndex][subLayerIndex]->Fill(expectedTime);
      hdiff[decIndex][subLayerIndex]->Fill(tdiff);

      for(int k=0; k < nBunches; k++)
	{
	  if(tdiff< 25*k+ readoutWindow){
	    hr[decIndex][subLayerIndex]->Fill(k);
	    break;
	  }
	}


      
    } // loop over number of hits in each event
    
      
  } // event loop

  TFile* outFile = new TFile("histo_oot.root","recreate");       
   
  for(int i=0;i<2;i++){
    for(int j=0; j<15;j++)
      {
	ht[i][j]->Write();
	hdiff[i][j]->Write();
	het[i][j]->Write();
	hr[i][j]->Write();
      }
  }

  outFile->Close();
}
