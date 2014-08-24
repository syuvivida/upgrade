#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <TH2.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <cmath>
#include "untuplizer.h"
#include "print.h"

using namespace std;

void chchen_oot(std::string fin, float readoutWindow=3){ // readoutWindow default = +-3ns

  std::vector<string> infiles;

  bool readOneFile=true;
  if(fin.find(".txt")!= std::string::npos)
    readOneFile=false;
  
  if(readOneFile)
    {
      infiles.push_back(fin);
    }
  
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

  std::string title[2]={"Barrel","Endcap"};
  std::string subtitle[2]={"Layer","Disk"};

  const int nBunches = 20;
  const int nLayers[2] = {10,15};
  TH1F* hoot[2];
  for(int k=0; k<2; k++)
    {
      hoot[k] = new TH1F(Form("hoot_%s",title[k].data()),"Fraction of digitized OOT hits",nLayers[k],0.5,(float)(nLayers[k]+0.5));
      
    }
  TH1F* hcount_1d = new TH1F("hcount_1d","",5, 0.5,5.5);
  TH1F* htof = new TH1F("htof","",100,-0.5,0.5);
  TH1F* ftof = new TH1F("ftof","",200,0.0,20.0);
  TH1F* dtof = new TH1F("dtof","",200,-10.0,10.0);
  TH1F* dtofb = new TH1F("dtof","",200,-5.0,5.0);
  TH1F* ftofCal = new TH1F("ftofCal","",200,0.0,20.0);
  TH1F* hread    = new TH1F("hread","",nBunches,0,(float)(nBunches));
  TH1F* h[2][15];
  TH1F* ht[2][15];
  TH1F* f[2][15];
  TH1F* fc[2][15];
  TH1F* d[2][15];
  TH1F* hr[2][15];
  for(int k=0;k<2; k++){
    for(int i=0;i<15;i++){

      h[k][i]=(TH1F*)hcount_1d->Clone(Form("h%d%02i",k,i+1));
      h[k][i]->SetXTitle("Number of crossings per particle");
      h[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));
      ht[k][i]=(TH1F*)htof->Clone(Form("ht%d%02i",k,i+1));
      ht[k][i]->SetXTitle("Difference of TOF from the first hit: ns");
      ht[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));
      
      f[k][i]=(TH1F*)ftof->Clone(Form("f%d%02i",k,i+1));
      f[k][i]->SetXTitle("Simulated time of flight: ns");
      f[k][i]->SetTitle(Form("%s, %s %d",title[k].data(), 
                               subtitle[k].data(),i+1));
    

      fc[k][i]=(TH1F*)ftofCal->Clone(Form("fc%d%02i",k,i+1));
      fc[k][i]->SetXTitle("Expected time of flight: ns");
      fc[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));

      if (k==1) d[k][i]=(TH1F*)dtof->Clone(Form("d%d%02i",k,i+1));
      if (k==0) d[k][i]=(TH1F*)dtofb->Clone(Form("d%d%02i",k,i+1));
      d[k][i]->SetXTitle("Difference of TOF from expectation: ns");
      d[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));
      

      hr[k][i]=(TH1F*)hread->Clone(Form("hr%d%02i",k,i+1));
      hr[k][i]->SetXTitle("Number of bunch crossings");
      hr[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
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


  TreeReader data(infiles); // v5.3.12
    

  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) {
    // print progress
    if (ev % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
    data.GetEntry(ev);
    for(int i=0;i<10;i++){countB[i]=0; backB[i]=0; tofB[i]=-1.;}
    for(int i=0;i<15;i++){countE[i]=0; backE[i]=0; tofE[i]=-1.;}

     //variable
    Int_t gensize= data.GetInt("nGenPar");
    Int_t  nHits = data.GetInt("nSimHits");
    Float_t* gParE =data.GetPtrFloat("genParE"); 
    Float_t* gParPt =data.GetPtrFloat("genParPt"); 
    //cout<<"nHits="<<nHits<<endl;
    Int_t* PID   = data.GetPtrInt("hitPID");
    Int_t* gPID   = data.GetPtrInt("genParId");
    Int_t* decID = data.GetPtrInt("hitSubDec");
    Int_t* layer = data.GetPtrInt("hitLayer");
    Int_t* disk  = data.GetPtrInt("hitDisk");
    Float_t* hGlobalX =data.GetPtrFloat("hitGlobalX"); 
    Float_t* hGlobalY =data.GetPtrFloat("hitGlobalY"); 
    Float_t* hGlobalZ =data.GetPtrFloat("hitGlobalZ"); 
    Float_t* hTof =data.GetPtrFloat("hitTof");


    int gsize=gensize;
    for(int j=0;j<gsize;j++){
    if(gPID[j]!= +13)continue;
      for(int i=0; i < nHits; i++){
 
      if(PID[i]== 22 || PID[i]== 12 || PID[i]== 14 || PID[i]== 16 
	 || PID[i]== 130 || PID[i]== 310 || PID[i]== 311 || PID[i] == 2112 ||
	 PID[i]== 3122)continue;

   
      int hitLayerIndex = layer[i]-1;
      int hitDiskIndex  = disk[i]-1;

      Float_t calE = gParE[j] ;    
      //cout<<"calE="<<calE<<endl;     
      //cin>>calE;	
      Float_t calPt = gParPt[j];
      //cout<<"calPt="<<calPt<<endl;
      Float_t calPz = sqrt(calE*calE-calPt*calPt-0.01);
      //cout<<"calPz="<<calPz<<endl;
      Float_t calVz = sqrt(( calPz* calPz)/(calPz* calPz+0.01));
      Float_t calVt = sqrt(( calPt* calPt)/(calPt* calPt+0.01));
      //float calVt = 1;
      //cout<<"calVt="<<calVt<<endl;       
      Float_t gloXY = sqrt(hGlobalX[i]*hGlobalX[i]+hGlobalY[i]*hGlobalY[i]) ;
      Float_t BR = calPt*0.877; //=pt/qB
      Float_t angle =gloXY/BR/200;              
      Float_t arcsin =asin(angle);       
      Float_t calR =arcsin*BR*2;       
      Float_t timeT = (calR*1000000000)/calVt/299792458;
      Float_t timeZ =(abs(hGlobalZ[i])*10000000)/calVz/299792458;
      if (timeZ>timeT)timeT=timeZ;
     
       
      //cout<<"gloXY="<<gloXY<<endl;  
      //cout<<"angle="<<angle<<endl;
      //cout<<"arcsin="<<arcsin<<endl;
      //cout<<"calR="<<calR<<endl;
      //cout<<"timeT="<<timeT<<endl;
      //cin>>calE;


     if(decID[i]==1)
	  { 
           
	    countB[hitLayerIndex]++;
	    if(countB[hitLayerIndex]==1){
	      tofB[hitLayerIndex]= hTof[i];
              f[0][hitLayerIndex]->Fill(tofB[hitLayerIndex]);
              //z[0][hitLayerIndex]->Fill(calPz);
              fc[0][hitLayerIndex]->Fill(timeT);
              Float_t tdiff=tofB[hitLayerIndex]-timeT;
              d[0][hitLayerIndex]->Fill(tdiff);
              tdiff=abs(tdiff);
              for(int k=0; k < nBunches; k++){
	        if(tdiff< (Float_t)(25*k+ readoutWindow) && tdiff  >= (Float_t)(25*k)){
	        hr[0][hitLayerIndex]->Fill(k);
	        break;
	        }
              }   
            }
	    else if(countB[hitLayerIndex]>1)
	      ht[0][hitLayerIndex]->Fill(hTof[i]-tofB[hitLayerIndex]);
	  }
	else
	  if(decID[i]==2)
	    {
             

	      countE[hitDiskIndex]++;
	      if(countE[hitDiskIndex]==1){ 
               
		tofE[hitDiskIndex]= hTof[i];
                f[1][hitDiskIndex]->Fill(tofE[hitDiskIndex]);
                //z[1][hitDiskIndex]->Fill(calPz);
                fc[1][hitDiskIndex]->Fill(timeT);
                Float_t tdiff=tofE[hitDiskIndex]-timeT;
                d[1][hitDiskIndex]->Fill(tdiff);
                tdiff=abs(tdiff);
                for(int k=0; k < nBunches; k++){
	          if(tdiff< (Float_t)(25*k+ readoutWindow) && tdiff  >= (Float_t)(25*k)){
	          hr[1][hitDiskIndex]->Fill(k);
	          break;
	          }
                }
              }
	      else if(countE[hitDiskIndex]>1)
		ht[1][hitDiskIndex]->Fill(hTof[i]-tofE[hitDiskIndex]);
	    }

     

      
      } // loop over number of hits in each event
    
    } //end of nGarPar


     for(int i=0;i<10;i++){
	hbarrel->Fill(i+1,countB[i]);
	h[0][i]->Fill(countB[i]);
      }
      for(int i=0;i<15;i++){
	hendcap->Fill(i+1,countE[i]);
	h[1][i]->Fill(countE[i]);
      }


  } // event loop
    
     




  TFile* outFile = new TFile("histo_oot.root","recreate");       
  hbarrel->Write();
  hendcap->Write();
  for(int i=0;i<2;i++){
    for(int j=0; j<nLayers[i] ;j++)
      {

	hr[i][j]->Write();
        h[i][j]->Write();
        d[i][j]->Write();
	ht[i][j]->Write();
        f[i][j]->Write();
        fc[i][j]->Write();
	if(hr[i][j]->GetEntries() > 0 ){
	  float fraction = (float)(hr[i][j]->GetEntries()-hr[i][j]->GetBinContent(1))/(float)(hr[i][j]->GetEntries());
	  float fraction_err =  fraction*(1-fraction)/(float)(hr[i][j]->GetEntries());
	  hoot[i]->SetBinContent(j+1,fraction);
	  hoot[i]->SetBinError(j+1,fraction_err);
	}

      }// end of loop over layers
    hoot[i]->Write();
  }

  
  outFile->Close();
}
