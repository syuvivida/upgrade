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

using namespace std;
void fractionClear(float & a,float & b)
{ 
a=-1;
b=-1;
}

void errmc(float nsig,float ntotal, float& eff, float& err ,TH1F* fHisto,int& j )
{
  cout << "nsig = " << nsig << " ntotal = " << ntotal << endl;
  if(ntotal<1e-6){eff=-1; err=-1; return;}
  eff = nsig/ntotal;
  err = sqrt( (1-eff)*eff/ntotal);
  if(eff>1e-6 && err>1e-6)
    {
     fHisto->SetBinContent(j+1,eff);
     fHisto->SetBinError(j+1,err);
    }
  fractionClear(eff,err);
  return;
}

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
  TH1F* hoot_digi[2];
  TH1F* hoot_digi_oot[2];
  TH1F* hoot2[2];
  TH1F* hoot_digi2[2];
  TH1F* hoot_digi_oot2[2];

  for(int k=0; k<2; k++)
    {
      hoot[k] = new TH1F(Form("hoot_%s",title[k].data()),Form("Fraction of Hits Not Digitized In-Time Relative to All Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi[k] = new TH1F(Form("hoot_digi_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Digitized Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi_oot[k] = new TH1F(Form("hoot_digi_oot_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits Not Digitized In-Time in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot2[k] = new TH1F(Form("hoot2_%s",title[k].data()),Form("Fraction of Hits Not Digitized In-Time Relative to All Hits in %s 2",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi2[k] = new TH1F(Form("hoot2_digi_%s ",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Digitized Hits in %s 2",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi_oot2[k] = new TH1F(Form("hoot2_digi_oot_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits Not Digitized In-Time in %s 2",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      
    }

  TH1I* htof     = new TH1I("htof","", 500,0, 500);
  TH1I* hetof    = new TH1I("hetof","", 100,0, 20);
  TH1I* hread    = new TH1I("hread","",nBunches,0,(float)(nBunches));
  TH1I* ht[2][15];
  TH1I* hdiff[2][15];
  TH1I* hdiff2[2][15];
  TH1I* het[2][15];
  TH1I* het2[2][15];
  TH1I* hr[2][15]; 
  TH1I* hr2[2][15];
  TH1I* hdiff_digi[2][15][nBunches];
  TH1I* hdiff_digi2[2][15][nBunches];
  TH1I* hpt_digi[2][15];
  TH1I* hpt_digi2[2][15];

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
      hdiff2[k][i]=(TH1I*)htof->Clone(Form("hdiff2%d%02i",k,i));
      hdiff2[k][i]->SetXTitle("Difference of TOF from expectation 2: ns");
      hdiff2[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
				 subtitle[k].data(),i+1));

      het[k][i]=(TH1I*)hetof->Clone(Form("het%d%02i",k,i));
      het[k][i]->SetXTitle("Expected time of flight: ns");
      het[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));
      het2[k][i]=(TH1I*)hetof->Clone(Form("het2%d%02i",k,i));
      het2[k][i]->SetXTitle("Expected time of flight 2: ns");
      het2[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));

      hr[k][i]=(TH1I*)hread->Clone(Form("hr%d%02i",k,i));
      hr[k][i]->SetXTitle("Number of bunch crossings");
      hr[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));
      hr2[k][i]=(TH1I*)hread->Clone(Form("hr2%d%02i",k,i));
      hr2[k][i]->SetXTitle("Number of bunch crossings 2");
      hr2[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));

      hpt_digi[k][i]=(TH1I*)hetof->Clone(Form("hpt_digi%d%02i",k,i));
      hpt_digi[k][i]->SetXTitle("p_{T} of corresponding tracks of Digitized OOT Hits");
      hpt_digi[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
				    subtitle[k].data(),i+1));

      hpt_digi2[k][i]=(TH1I*)hetof->Clone(Form("hpt2_digi%d%02i",k,i));
      hpt_digi2[k][i]->SetXTitle("p_{T} of corresponding tracks of Digitized OOT Hits");
      hpt_digi2[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
				    subtitle[k].data(),i+1));

     for(int b=0; b< nBunches; b++){

	hdiff_digi[k][i][b]=(TH1I*)htof->Clone(Form("hdiff_digi_%d%02i_%02i",k,i,b));
	hdiff_digi[k][i][b]->SetXTitle("Difference of TOF from expectation: ns");
	hdiff_digi[k][i][b]->SetTitle(Form("%s, %s %d in bunch %d",title[k].data(),
					   subtitle[k].data(),i+1,b));


        hdiff_digi2[k][i][b]=(TH1I*)htof->Clone(Form("hdiff2_digi_%d%02i_%02i",k,i,b));
	hdiff_digi2[k][i][b]->SetXTitle("Difference of TOF from expectation: ns");
	hdiff_digi2[k][i][b]->SetTitle(Form("%s, %s %d in bunch %d",title[k].data(),
					   subtitle[k].data(),i+1,b));
      }
      
    }
  }

  TreeReader data(infiles); // v5.3.12
  Long64_t nCount=0;
  Long64_t nCount2=0;

  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) {
    // print progress
    if (ev % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
    data.GetEntry(ev);
    
    Int_t  nHits = data.GetInt("nSimHits"); 
    Int_t* decID = data.GetPtrInt("hitSubDec");
    Int_t* PID   = data.GetPtrInt("hitPID");
    //     Int_t* proc  = data.GetPtrInt("hitProcessType");
    Int_t* layer = data.GetPtrInt("hitLayer");
    Int_t* disk  = data.GetPtrInt("hitDisk");

    Float_t* tof    = data.GetPtrFloat("hitTof");


    Float_t* gx    = data.GetPtrFloat("hitGlobalX");
    Float_t* gy    = data.GetPtrFloat("hitGlobalY");
    Float_t* gz    = data.GetPtrFloat("hitGlobalZ");
    Float_t* trkPt = data.GetPtrFloat("hitTrkPt");
    Float_t* trkPz = data.GetPtrFloat("hitTrkPz");
    Float_t* trkCharge = data.GetPtrFloat("hitTrkCharge");
 
 
   
    for(int i=0; i < nHits; i++){

      // remove neutral particles
      if(fabs(trkCharge[i])<1e-6)continue; 
      
      if(PID[i]== 22 || PID[i]== 12 || PID[i]== 14 || PID[i]== 16 
       	 || PID[i]== 130 || PID[i]== 310 || PID[i]== 311 || PID[i] == 2112 ||
      	 PID[i]== 3122)continue;

      int hitLayerIndex = layer[i]-1;
      int hitDiskIndex  = disk[i]-1;

   	
      Float_t calPt = trkPt[i];
      Float_t calPz = trkPz[i];
      Float_t calVz = sqrt(( calPz* calPz)/(calPz* calPz+0.01));
      Float_t calVt = sqrt(( calPt* calPt)/(calPt* calPt+0.01));
      //float calVt = 1;
      //cout<<"calVt="<<calVt<<endl;    
      Float_t gloXY = sqrt(gx[i]*gx[i]+gy[i]*gy[i]) ;
      Float_t BR = calPt*0.877; //=pt/qB
      Float_t sineAngle =gloXY/BR/200; 
      if(sineAngle>1)sineAngle=0;             
      Float_t arcsin =asin(sineAngle);       
      Float_t calR =arcsin*BR*2;       
      Float_t timeT = (calR*1000000000)/calVt/299792458;
      if(timeT==0)timeT=gloXY/30;
      Float_t timeZ =(abs(gz[i])*10000000)/calVz/299792458;
      if (timeZ>timeT)timeT=timeZ;
      

      Float_t pathlength = sqrt(gx[i]*gx[i] +
				gy[i]*gy[i] +
				gz[i]*gz[i]);
      Float_t expectedTime = pathlength/30;

      Float_t time = tof[i];

      Float_t tdiff = fabs(time-expectedTime);
      Float_t tdiff2 = fabs(time-timeT);
      Int_t decIndex = decID[i]-1;
	
      int subLayerIndex = decIndex==0? hitLayerIndex: hitDiskIndex;

      ht[decIndex][subLayerIndex]->Fill(time);
      het[decIndex][subLayerIndex]->Fill(expectedTime);
      het2[decIndex][subLayerIndex]->Fill(timeT);
      hdiff[decIndex][subLayerIndex]->Fill(tdiff);
      hdiff2[decIndex][subLayerIndex]->Fill(tdiff2);
      for(int k=0; k < nBunches; k++)
	{
	  if(fabs(tdiff-(Float_t)25*k)< readoutWindow){
	    if(decIndex==0 && subLayerIndex==0)nCount++;
	    hr[decIndex][subLayerIndex]->Fill(k);
	    hdiff_digi[decIndex][subLayerIndex][k]->Fill(tdiff);
	    if(k>0)
	        hpt_digi[decIndex][subLayerIndex]->Fill(trkPt[i]);
	    break;
	  }
   
	}


      for(int k=0; k < nBunches; k++)
          {
       	if(fabs(tdiff2-(Float_t)25*k)< readoutWindow){
             if(decIndex==0 && subLayerIndex==0)nCount2++;
            hr2[decIndex][subLayerIndex]->Fill(k);
            hdiff_digi2[decIndex][subLayerIndex][k]->Fill(tdiff2);
           if(k>0)
            hpt_digi2[decIndex][subLayerIndex]->Fill(trkPt[i]);
            break;
	     }

	  }


    } // loop over number of hits in each event
    

  } // event loop

  std::cout << "nCount = " << nCount << std::endl;
  std::cout << "nCount2 = " << nCount2 << std::endl;
  TFile* outFile = new TFile("histo_oot.root","recreate");       

  for(int i=0;i<2;i++){
    for(int j=0; j<nLayers[i] ;j++)
      {
	ht[i][j]->Write();
	hdiff[i][j]->Write();
        hdiff2[i][j]->Write();
	het[i][j]->Write();
        het2[i][j]->Write();
	hr[i][j]->Write();
	hr2[i][j]->Write();
	hpt_digi[i][j]->Write();
        hpt_digi2[i][j]->Write();
	for(int b=0; b< nBunches; b++){
	  hdiff_digi[i][j][b]->Write();
          hdiff_digi2[i][j][b]->Write();
         }
	// compute the fraction of OOT Hits in various ways

	// number of hits not digitized in the first bounch crossing
	Long64_t nOOT = hdiff[i][j]->GetEntries()-hr[i][j]->GetBinContent(1);

	float fraction=-1;
	float fraction_err=-1;
	errmc(nOOT,
	      hdiff[i][j]->GetEntries(),
	      fraction, fraction_err,hoot[i],j);
        errmc(nOOT,
	      hdiff2[i][j]->GetEntries(),
	      fraction, fraction_err,hoot2[i],j);
	
	int nBins = hr[i][j]->GetNbinsX();
	errmc(hr[i][j]->Integral(2,nBins+1),
	      hr[i][j]->GetEntries(),
	      fraction, fraction_err, hoot_digi[i],j);  
        errmc(hr2[i][j]->Integral(2,nBins+1),
	      hr2[i][j]->GetEntries(),
	      fraction, fraction_err, hoot_digi2[i],j);  	

	errmc(hr[i][j]->Integral(2,nBins+1),
	      nOOT,
	      fraction, fraction_err, hoot_digi_oot[i],j);  
        errmc(hr2[i][j]->Integral(2,nBins+1),
	      nOOT,
	      fraction, fraction_err, hoot_digi_oot2[i],j);  

      }// end of loop over layers
  }

 for(int i=0;i<2;i++){
    hoot[i]->Write();
    hoot2[i]->Write();
    hoot_digi[i]->Write();
    hoot_digi2[i]->Write();
    hoot_digi_oot[i]->Write();
    hoot_digi_oot2[i]->Write();
 }
  
  outFile->Close();
}
