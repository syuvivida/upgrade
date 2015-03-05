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
#include "TCanvas.h"
#include "TLine.h"
#include "untuplizer.h"
#include "TMarker.h"




void geo(std::string fin){
  std::vector<string> infiles;
  //TString outputFileName;
  bool readOneFile=true;
  if(fin.find(".txt")!= std::string::npos)
    {
      readOneFile=false;
      TString endfix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; echo \"${test%%.txt*}\"",fin.data()));
      //outputFileName = Form("histo_oot_%s_%d_timeW%02i.root",endfix.Data(),processType,(int)readoutWindow);
      //cout << "Output file = " << outputFileName << endl;
    }

  if(readOneFile)
    {
      infiles.push_back(fin);
      TString endfix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; echo \"${test%%.root*}\"",fin.data()));
      //outputFileName = Form("absHisto_oot_%s_%d_timeW%02i.root",endfix.Data(),processType,(int)readoutWindow);
      //cout << "Output file = " << outputFileName << endl;
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

  TCanvas *c1 = new TCanvas("c1","Examples",10,10,1500,750);
  TreeReader data(infiles); // v5.3.12

  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) {
    // print progress
    if (ev % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", ev + 1, data.GetEntriesFast());
    data.GetEntry(ev);

  int axisXMax=290,axisXMin=-290,axisYMax=120,axisYMin=0;
  c1->Range(axisXMin,axisYMin,axisXMax,axisYMax);
  TLine *beamPath =new TLine(axisXMin,0,axisXMax,0);
  beamPath-> SetLineColor(3);
  beamPath->Draw();

    Float_t* gx    = data.GetPtrFloat("hitGlobalX");
    Float_t* gy    = data.GetPtrFloat("hitGlobalY");
    Float_t* gz    = data.GetPtrFloat("hitGlobalZ");
   Int_t  nHits = data.GetInt("nSimHits");


   for(int i=0; i < nHits; i++){
    Float_t gr    = sqrt(gx[i]*gx[i]+gy[i]*gy[i]);
    TMarker *m1 =new TMarker(gz[i],gr,7);
    m1->Draw() ;
   }


  }


TFile* outFile = new TFile("geo.root","recreate");
 c1->Write();
outFile->Close();


}
