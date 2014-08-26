#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <TH2.h>
#include <TRandom3.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "untuplizer.h"

using namespace std;

std::string title[2]={"Barrel","Endcap"};
std::string subtitle[2]={"Layer","Disk"};

const int nBunches = 20;
const int nLayers[2] = {10,15};
TH1F* hoot[2];
TH1I* ht[2][15];
TH1I* hdiff[2][15];
TH1I* het[2][15];
TH1I* hr[2][15];

void fillHisto(TreeReader& data, float readoutWindow)
{
  Int_t  nHits = data.GetInt("nSimHits");
  Int_t* decID = data.GetPtrInt("hitSubDec");
  Int_t* PID   = data.GetPtrInt("hitPID");
  Int_t* layer = data.GetPtrInt("hitLayer");
  Int_t* disk  = data.GetPtrInt("hitDisk");

  Float_t* tof    = data.GetPtrFloat("hitTof");


  Float_t* gx    = data.GetPtrFloat("hitGlobalX");
  Float_t* gy    = data.GetPtrFloat("hitGlobalY");
  Float_t* gz    = data.GetPtrFloat("hitGlobalZ");

 
  for(int i=0; i < nHits; i++){

    if(PID[i]== 22 || PID[i]== 12 || PID[i]== 14 || PID[i]== 16 
       || PID[i]== 130 || PID[i]== 310 || PID[i]== 311 || PID[i] == 2112 ||
       PID[i]== 3122)continue;

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
	if(tdiff< (Float_t)(25*k+ readoutWindow) && tdiff  >= (Float_t)(25*k)){
	  hr[decIndex][subLayerIndex]->Fill(k);
	  break;
	}
      }


      
  } // loop over number of hits in each event
    
  return;
}

void xAna_oot_140PU(std::string fin, std::string mbfin="minbias.txt", float readoutWindow=3){ // readoutWindow default = +-3ns

  TRandom3* gRandom = new TRandom3();
  // reading QCD files
  std::vector<string> infiles;

  bool readOneFile=true;
  if(fin.find(".txt")!= std::string::npos)
    readOneFile=false;
  
  if(readOneFile)
    infiles.push_back(fin);
  else{
    FILE *fTable = fopen(fin.data(),"r");
    int flag=1;
    int nfile=0;

    while (flag!=-1){
      char filename[300];
      flag=fscanf(fTable,"%s",filename);
      // first reading input file
      if(flag!=-1){
	std::string tempFile = filename;    
	infiles.push_back(tempFile);
	nfile++;
      }
    }

    cout << "nfiles = " << nfile << endl;
  }

  // reading minbias files for producing pileups
  std::vector<string> mb_files;
  readOneFile=true;
  if(mbfin.find(".txt")!= std::string::npos)
    readOneFile=false;
  
  if(readOneFile)
    mb_files.push_back(mbfin);
  else{
    FILE *fTable = fopen(mbfin.data(),"r");
    int flag=1;
    int nfile=0;

    while (flag!=-1){
      char filename[300];
      flag=fscanf(fTable,"%s",filename);
      // first reading input file
      if(flag!=-1){
	std::string tempFile = filename;    
	mb_files.push_back(tempFile);
	nfile++;
      }
    }

    cout << "n mb files = " << nfile << endl;
  }

  // defining histograms
  for(int k=0; k<2; k++)
    {
      hoot[k] = new TH1F(Form("hoot_%s",title[k].data()),Form("Fraction of Digitized OOT Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      
    }
  TH1I* htof     = new TH1I("htof","", 500,0, 500);
  TH1I* hetof    = new TH1I("hetof","", 100,0, 20);
  TH1I* hread    = new TH1I("hread","",nBunches,0,(float)(nBunches));
  for(int k=0;k<2; k++){
    for(int i=0;i<15;i++){
      ht[k][i]=(TH1I*)htof->Clone(Form("ht%d%02i",k,i));
      ht[k][i]->SetXTitle("Simulated time of flight: ns");
      ht[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));

      hdiff[k][i]=(TH1I*)htof->Clone(Form("hdiff%d%02i",k,i));
      hdiff[k][i]->SetXTitle("Difference of TOF from expectation: ns");
      hdiff[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
				 subtitle[k].data(),i+1));

      het[k][i]=(TH1I*)hetof->Clone(Form("het%d%02i",k,i));
      het[k][i]->SetXTitle("Expected time of flight: ns");
      het[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));

      hr[k][i]=(TH1I*)hread->Clone(Form("hr%d%02i",k,i));
      hr[k][i]->SetXTitle("Number of bunch crossings");
      hr[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));
    }
  }

  TH1I* hPU = new TH1I("hPU","",1000,-0.5,999.5);

  TreeReader qcd(infiles); // v5.3.12    
  TreeReader pu(mb_files);

  Long64_t nQCDEntries = qcd.GetEntriesFast();
  Long64_t nMBEntries  = pu.GetEntriesFast();

  std::cout << "nQCDEntries = " << nQCDEntries << "\t nMBEntries = " << nMBEntries << std::endl;

  Long64_t nQCDInput   = (Long64_t)(nMBEntries/140)  > nQCDEntries ? nQCDEntries: nMBEntries/140;
  Long64_t nMBInput    = (Long64_t)(nMBEntries/140)  > nQCDEntries ? (nQCDEntries*140) : (nQCDInput*140);

  Long64_t nCount=0;

  std::cout << "nQCDInput = " << nQCDInput << "\t nMBInput = " << nMBInput << std::endl;

  for (Long64_t ev = 0; ev < nQCDInput; ev++) {
    // print progress
    if (ev % 50000 == 0)
      fprintf(stderr, "Processing QCD event %lli of %lli\n", ev + 1, nQCDInput);
    qcd.GetEntry(ev);
    fillHisto(qcd,readoutWindow);
    Int_t thisNPU = gRandom->Poisson(140);
    hPU->Fill(thisNPU);
    nCount+= thisNPU;
  } // event loop for QCD Events
  
  std::cout << "nCount = " << nCount << std::endl;
  nMBInput = nCount;

  for (Long64_t ev = 0; ev < nMBInput; ev++) {
    // print progress
    if (ev % 50000 == 0)
      fprintf(stderr, "Processing PU event %lli of %lli\n", ev + 1, nMBInput);
     pu.GetEntry(ev);
     fillHisto(qcd,readoutWindow);
  } // event loop for pileup Events
  
  

  TFile* outFile = new TFile("histo_oot_140PU.root","recreate");       

  for(int i=0;i<2;i++){
    for(int j=0; j<nLayers[i] ;j++)
      {
	ht[i][j]->Write();
	hdiff[i][j]->Write();
	het[i][j]->Write();
	hr[i][j]->Write();

	float ntotal = hr[i][j]->Integral();

	if(ntotal > 0 ){
	  float fraction = (float)(ntotal-hr[i][j]->GetBinContent(1))/ntotal;
	  float fraction_err =  fraction*(1-fraction)/ntotal;
	  hoot[i]->SetBinContent(j+1,fraction);
	  hoot[i]->SetBinError(j+1,fraction_err);
	}

      }// end of loop over layers
    hoot[i]->Write();
  }
  hPU->Write();

  outFile->Close();
}
