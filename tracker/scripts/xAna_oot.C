#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <TH2.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TString.h>
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
  //cout << "nsig = " << nsig << " ntotal = " << ntotal << endl;
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

// processType = -1 means taking all particles, = -2 means taking all but primary particles, readoutWindow default = +-3ns 
void xAna_oot(std::string fin, int processType=-1, float readoutWindow=3){ 

  std::vector<string> infiles;
  TString outputFileName;
  bool readOneFile=true;
  if(fin.find(".txt")!= std::string::npos)
    {
      readOneFile=false;
      TString endfix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; echo \"${test%%.txt*}\"",fin.data()));
      outputFileName = Form("histo_oot_%s_%d_timeW%02i.root",endfix.Data(),processType,(int)readoutWindow);
      cout << "Output file = " << outputFileName << endl;
    }
  
  if(readOneFile)
    {
      infiles.push_back(fin);
      TString endfix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; echo \"${test%%.root*}\"",fin.data()));
      outputFileName = Form("histo_oot_%s_%d_timeW%02i.root",endfix.Data(),processType,(int)readoutWindow);
      cout << "Output file = " << outputFileName << endl;
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

  std::string titletrk[2]={"|#eta| < 1.0", "|#eta| > 1.0"};
  std::string subtitletrk[2]={"primary", "secondary"};

  const int nBunches = 20;
  const int nLayers[2] = {10,15};
  TH1F* hoot[2];
  TH1F* hoot_digi[2];
  TH1F* hoot_digi_oot[2];

  TH1F* hoot2[2];
  TH1F* hoot_digi2[2];
  TH1F* hoot_digi_oot2[2];

  TH1F* hoot3[2];
  TH1F* hoot_digi3[2];
  TH1F* hoot_digi_oot3[2];

  for(int k=0; k<2; k++)
    {
      hoot[k] = new TH1F(Form("hoot_%s",title[k].data()),Form("Fraction of Hits Not Digitized In-Time Relative to All Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi[k] = new TH1F(Form("hoot_digi_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Digitized Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi_oot[k] = new TH1F(Form("hoot_digi_oot_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits Not Digitized In-Time in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot2[k] = new TH1F(Form("hoot2_%s",title[k].data()),Form("Fraction of Hits Not Digitized In-Time Relative to All Hits in %s 2",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi2[k] = new TH1F(Form("hoot2_digi_%s ",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Digitized Hits in %s 2",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi_oot2[k] = new TH1F(Form("hoot2_digi_oot_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits Not Digitized In-Time in %s 2",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));

      hoot3[k] = new TH1F(Form("hoot3_%s",title[k].data()),Form("Fraction of Hits Not Digitized In-Time Relative to All Hits in %s 3",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi3[k] = new TH1F(Form("hoot3_digi_%s ",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Digitized Hits in %s 3",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi_oot3[k] = new TH1F(Form("hoot3_digi_oot_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits Not Digitized In-Time in %s 3",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      
    }

  TH1I* htof_diff= new TH1I("htof_diff","", 400,-10,10);

  TH1I* htof     = new TH1I("htof","", 500,0, 500);
  TH1I* hetof    = new TH1I("hetof","", 100,0, 20);
  TH1I* hread    = new TH1I("hread","",nBunches,0,(float)(nBunches));

  TH1I* ht[2][15];
  TH1I* hdiff[2][15];
  TH1I* hdiff2[2][15];
  TH1I* hdiff3[2][15];
  TH1I* het[2][15];
  TH1I* het2[2][15];
  TH1I* het3[2][15];
  TH1I* hr[2][15]; 
  TH1I* hr2[2][15];
  TH1I* hr3[2][15];
  TH1I* hdiff_digi[2][15][nBunches];
  TH1I* hdiff_digi2[2][15][nBunches];
  TH1I* hdiff_digi3[2][15][nBunches];
  TH1I* hpt_digi[2][15][nBunches];
  TH1I* hpt_digi2[2][15][nBunches];
  TH1I* hpt_digi3[2][15][nBunches];

  TH1I* htrkpt[2][2]; // [0]: |eta| < 1.0, [1]: |eta| > 1.0
  TH1I* htrketa[2][2];

  for(int k=0;k<2; k++){

    for(int ik=0; ik<2; ik++){
      htrkpt[k][ik] = (TH1I*)hetof->Clone(Form("htrkpt%d_%s",k,subtitletrk[ik].data()));
      htrkpt[k][ik]->SetXTitle("Track p_{T} [GeV]");
      htrkpt[k][ik]->SetTitle(Form("%s, %s particles",titletrk[k].data(),subtitletrk[ik].data()));

      htrketa[k][ik] = (TH1I*)htof_diff->Clone(Form("htrketa%d_%s",k,subtitletrk[ik].data()));
      htrketa[k][ik]->SetXTitle("Track #eta");
      htrketa[k][ik]->SetTitle(Form("%s, %s particles",titletrk[k].data(),subtitletrk[ik].data()));
      
    }

    for(int i=0;i<15;i++){

     
      ht[k][i]=(TH1I*)hetof->Clone(Form("ht%d%02i",k,i));
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

      hdiff3[k][i]=(TH1I*)htof->Clone(Form("hdiff3%d%02i",k,i));
      hdiff3[k][i]->SetXTitle("Difference of TOF from expectation 3: ns");
      hdiff3[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
				 subtitle[k].data(),i+1));

      het[k][i]=(TH1I*)hetof->Clone(Form("het%d%02i",k,i));
      het[k][i]->SetXTitle("Expected time of flight: ns");
      het[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));
      het2[k][i]=(TH1I*)hetof->Clone(Form("het2%d%02i",k,i));
      het2[k][i]->SetXTitle("Expected time of flight 2: ns");
      het2[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));
      het3[k][i]=(TH1I*)hetof->Clone(Form("het3%d%02i",k,i));
      het3[k][i]->SetXTitle("Expected time of flight 3: ns");
      het3[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));

      hr[k][i]=(TH1I*)hread->Clone(Form("hr%d%02i",k,i));
      hr[k][i]->SetXTitle("Number of bunch crossings");
      hr[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));
      hr2[k][i]=(TH1I*)hread->Clone(Form("hr2%d%02i",k,i));
      hr2[k][i]->SetXTitle("Number of bunch crossings 2");
      hr2[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));
      hr3[k][i]=(TH1I*)hread->Clone(Form("hr3%d%02i",k,i));
      hr3[k][i]->SetXTitle("Number of bunch crossings 3");
      hr3[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			      subtitle[k].data(),i+1));


     for(int b=0; b< nBunches; b++){

	hdiff_digi[k][i][b]=(TH1I*)htof->Clone(Form("hdiff_digi_%d%02i_%02i",k,i,b));
	hdiff_digi[k][i][b]->SetXTitle("Difference of TOF from expectation: ns");
	hdiff_digi[k][i][b]->SetTitle(Form("%s, %s %d in bunch %d",title[k].data(),
					   subtitle[k].data(),i+1,b));


        hdiff_digi2[k][i][b]=(TH1I*)htof->Clone(Form("hdiff2_digi_%d%02i_%02i",k,i,b));
	hdiff_digi2[k][i][b]->SetXTitle("Difference of TOF from expectation 2: ns");
	hdiff_digi2[k][i][b]->SetTitle(Form("%s, %s %d in bunch %d",title[k].data(),
					   subtitle[k].data(),i+1,b));

        hdiff_digi3[k][i][b]=(TH1I*)htof->Clone(Form("hdiff3_digi_%d%02i_%02i",k,i,b));
	hdiff_digi3[k][i][b]->SetXTitle("Difference of TOF from expectation 3: ns");
	hdiff_digi3[k][i][b]->SetTitle(Form("%s, %s %d in bunch %d",title[k].data(),
					   subtitle[k].data(),i+1,b));
	
	hpt_digi[k][i][b]=(TH1I*)hetof->Clone(Form("hpt_digi%d%02i_%02i",k,i,b));
	hpt_digi[k][i][b]->SetXTitle("p_{T} of corresponding tracks of Digitized OOT Hits");
	hpt_digi[k][i][b]->SetTitle(Form("%s, %s %d in bunch %d",title[k].data(),
					 subtitle[k].data(),i+1,b));

	
	hpt_digi2[k][i][b]=(TH1I*)hetof->Clone(Form("hpt2_digi%d%02i_%02i",k,i,b));
	hpt_digi2[k][i][b]->SetXTitle("p_{T} of corresponding tracks of Digitized OOT Hits");
	hpt_digi2[k][i][b]->SetTitle(Form("%s, %s %d in bunch %d",title[k].data(),
					 subtitle[k].data(),i+1,b));

	hpt_digi3[k][i][b]=(TH1I*)hetof->Clone(Form("hpt3_digi%d%02i_%02i",k,i,b));
	hpt_digi3[k][i][b]->SetXTitle("p_{T} of corresponding tracks of Digitized OOT Hits");
	hpt_digi3[k][i][b]->SetTitle(Form("%s, %s %d in bunch %d",title[k].data(),
					 subtitle[k].data(),i+1,b));
	

      }
      
    }
  }

  TreeReader data(infiles); // v5.3.12

  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) {
    // print progress
    if (ev % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
    data.GetEntry(ev);
    
    Int_t  nTrks = data.GetInt("nSimTrks");
    Float_t* trkPt  = data.GetPtrFloat("trkPt");
    Float_t* trkPz  = data.GetPtrFloat("trkPz");
    Float_t* trkE   = data.GetPtrFloat("trkE");
    Float_t* trkEta = data.GetPtrFloat("trkEta");
    Float_t* trkCharge = data.GetPtrFloat("trkCharge");

    Int_t* trkGenIndex = data.GetPtrInt("trkGenIndex");
    // Int_t* trkPID = data.GetPtrInt("trkPID");
    Int_t* trkVtxIndex = data.GetPtrInt("trkVtxIndex");


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
    

    Int_t* trkIndex = data.GetPtrInt("hitTrkIndex");

    Int_t nVtxs = data.GetInt("nSimVtxs");
    Float_t* vx = data.GetPtrFloat("vtxX");
    Float_t* vy = data.GetPtrFloat("vtxY");
    Float_t* vz = data.GetPtrFloat("vtxZ");
    
    Float_t primvx=0, primvy=0, primvz=0;
    if(nVtxs>0)
      {
	primvx=vx[0];
	primvy=vy[0];
	primvz=vz[0];
      }
    

    for(int j=0; j < nTrks; j++){

      if(fabs(trkCharge[j])<1e-6)continue; 
      Float_t eta = trkEta[j];
      Float_t pt  = trkPt[j];

      Int_t dec = fabs(eta)<1.0? 0: 1;
      Int_t type = trkGenIndex[j]<0? 1:0;

      htrkpt[dec][type]->Fill(pt);
      htrketa[dec][type]->Fill(eta);

    }

    for(int i=0; i < nHits; i++){

      if(processType>=0 && proc[i]!=processType)continue; 
      else if(processType== -2 && proc[i]==2)continue; 

      // note if processType==2, a matched track could definitely be found
      int itrk=trkIndex[i];

      // remove neutral particles if a matched track is found
      //      if(itrk>=0 && fabs(trkCharge[itrk])<1e-6)continue; 
      

      if(PID[i]== 22 || PID[i]== 12 || PID[i]== 14 || PID[i]== 16 || PID[i]==111
       	 || PID[i]== 130 || PID[i]== 310 || PID[i]== 311 || PID[i] == 2112 ||
      	 PID[i]== 3122)continue;


      int hitLayerIndex = layer[i]-1;
      int hitDiskIndex  = disk[i]-1;
      Int_t decIndex = decID[i]-1;
      int subLayerIndex = decIndex==0? hitLayerIndex: hitDiskIndex;
      Float_t time = tof[i];


     // more accurate way of computation if a matched track is found and 
      // a pt could be retrieved
      if(itrk>=0){
       Float_t calPz = trkPz[itrk];
       Float_t calE  = trkE[itrk];
       Float_t calVz = calPz/calE *299792458*1e-7;
       Float_t timeZ = abs((gz[i]-primvz)/calVz);
       Float_t tdiff2 = (time-timeZ);

       het2[decIndex][subLayerIndex]->Fill(timeZ);
       hdiff2[decIndex][subLayerIndex]->Fill(fabs(tdiff2));

      for(int k=0; k < nBunches; k++)
          {
	    if(fabs(tdiff2-(Float_t)25*k)< readoutWindow){
	      hr2[decIndex][subLayerIndex]->Fill(k);
	      hdiff_digi2[decIndex][subLayerIndex][k]->Fill(fabs(tdiff2));
 	      hpt_digi2[decIndex][subLayerIndex][k]->Fill(trkPt[itrk]);
	      break;
	    }

	  }
      
      // even consider the case when the matched track is not from the primary vertex
      Int_t vtxIndex = trkVtxIndex[itrk];
      Float_t time_second = abs((gz[i]-vz[vtxIndex])/calVz);
      Float_t tdiff3 = (time-time_second);

      het3[decIndex][subLayerIndex]->Fill(time_second);
      hdiff3[decIndex][subLayerIndex]->Fill(fabs(tdiff3));
      for(int k=0; k < nBunches; k++)
          {
	    if(fabs(tdiff3-(Float_t)25*k)< readoutWindow){
	      hr3[decIndex][subLayerIndex]->Fill(k);
	      hdiff_digi3[decIndex][subLayerIndex][k]->Fill(fabs(tdiff3));
 	      hpt_digi3[decIndex][subLayerIndex][k]->Fill(trkPt[itrk]);
	      break;
	    }

	  }


      } // if a matched track is found
      Float_t pathlength = sqrt(pow(gx[i],2) +
				pow(gy[i],2) +
				pow(gz[i],2));
      Float_t expectedTime = pathlength/30;
      Float_t tdiff = (time-expectedTime);

      ht[decIndex][subLayerIndex]->Fill(time);
      het[decIndex][subLayerIndex]->Fill(expectedTime);
      hdiff[decIndex][subLayerIndex]->Fill(fabs(tdiff));
      for(int k=0; k < nBunches; k++) 
	{
	  if(fabs(fabs(tdiff)-(Float_t)25*k)< readoutWindow){
	    hr[decIndex][subLayerIndex]->Fill(k);
	    hdiff_digi[decIndex][subLayerIndex][k]->Fill(fabs(tdiff));
 	    if(itrk>=0)hpt_digi[decIndex][subLayerIndex][k]->Fill(trkPt[itrk]);
	    break;
	  }
	}


    } // loop over number of hits in each event
    

  } // event loop

  TFile* outFile = new TFile(outputFileName.Data(),"recreate");       

  for(int i=0;i<2;i++){

    for(int ik=0; ik<2; ik++){
      htrkpt[i][ik]->Write();
      htrketa[i][ik]->Write();
    }

    for(int j=0; j<nLayers[i] ;j++)
      {
	ht[i][j]->Write();

	hdiff[i][j]->Write();
        hdiff2[i][j]->Write();
        hdiff3[i][j]->Write();

	het[i][j]->Write();
        het2[i][j]->Write();
        het3[i][j]->Write();

	hr[i][j]->Write();
	hr2[i][j]->Write();
	hr3[i][j]->Write();

	for(int b=0; b< nBunches; b++){
	  hdiff_digi[i][j][b]->Write();
          hdiff_digi2[i][j][b]->Write();
          hdiff_digi3[i][j][b]->Write();
	  hpt_digi[i][j][b]->Write();
	  hpt_digi2[i][j][b]->Write();
	  hpt_digi3[i][j][b]->Write();

         }
	// compute the fraction of OOT Hits in various ways

	// number of hits not digitized in the first bounch crossing
	float fraction=-1;
	float fraction_err=-1;

	Long64_t nOOT = hdiff[i][j]->GetEntries()-hr[i][j]->GetBinContent(1);
	errmc(nOOT,
	      hdiff[i][j]->GetEntries(),
	      fraction, fraction_err,hoot[i],j);

	Long64_t nOOT2 = hdiff2[i][j]->GetEntries()-hr2[i][j]->GetBinContent(1);
        errmc(nOOT2,
	      hdiff2[i][j]->GetEntries(),
	      fraction, fraction_err,hoot2[i],j);

	Long64_t nOOT3 = hdiff3[i][j]->GetEntries()-hr3[i][j]->GetBinContent(1);
        errmc(nOOT3,
	      hdiff3[i][j]->GetEntries(),
	      fraction, fraction_err,hoot3[i],j);
	
	int nBins = hr[i][j]->GetNbinsX();
	errmc(hr[i][j]->Integral(2,nBins+1),
	      hr[i][j]->GetEntries(),
	      fraction, fraction_err, hoot_digi[i],j);  
        errmc(hr2[i][j]->Integral(2,nBins+1),
	      hr2[i][j]->GetEntries(),
	      fraction, fraction_err, hoot_digi2[i],j);  	
        errmc(hr3[i][j]->Integral(2,nBins+1),
	      hr3[i][j]->GetEntries(),
	      fraction, fraction_err, hoot_digi3[i],j);  	

	errmc(hr[i][j]->Integral(2,nBins+1),
	      nOOT,
	      fraction, fraction_err, hoot_digi_oot[i],j);  
        errmc(hr2[i][j]->Integral(2,nBins+1),
	      nOOT2,
	      fraction, fraction_err, hoot_digi_oot2[i],j);  
        errmc(hr3[i][j]->Integral(2,nBins+1),
	      nOOT3,
	      fraction, fraction_err, hoot_digi_oot3[i],j);  

      }// end of loop over layers
  }

 for(int i=0;i<2;i++){
    hoot[i]->Write();
    hoot2[i]->Write();
    hoot3[i]->Write();
    hoot_digi[i]->Write();
    hoot_digi2[i]->Write();
    hoot_digi3[i]->Write();
    hoot_digi_oot[i]->Write();
    hoot_digi_oot2[i]->Write();
    hoot_digi_oot3[i]->Write();
 }
  outFile->Close();
}
