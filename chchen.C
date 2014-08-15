#define chchen_cxx
#include "chchen.h"
#include "print.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <string>
#include <iostream>
#include <cmath>
#include "TPad.h"
void chchen::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L chchen.C
//      Root > chchen t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  
//declear histogram and variable
  std::string title[2]={"Barrel","Endcap"};
  std::string subtitle[2]={"Layer","Disk"};
  TH1F* hcount_1d = new TH1F("hcount_1d","",5, 0.5,5.5);
  TH1F* htof = new TH1F("htof","",100,-0.5,0.5);
  TH1F* ftof = new TH1F("ftof","",200,0.0,20.0);
  TH1F* dtof = new TH1F("dtof","",200,-10.0,10.0);
  TH1F* dtofb = new TH1F("dtof","",200,-5.0,5.0);
  //TH1F* pz = new TH1F("pz","",100,0.0,5.0);
  TH1F* ftofCal = new TH1F("ftofCal","",200,0.0,20.0);
  TH1F* h[2][15];
  TH1F* ht[2][15];
  TH1F* f[2][15];
  //TH1F* z[2][15];
  TH1F* fc[2][15];
  TH1F* d[2][15];
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
      f[k][i]->SetXTitle("Time of Flight Distrubution");
      f[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));
      //z[k][i]=(TH1F*)pz->Clone(Form("z%d%02i",k,i+1));
      //z[k][i]->SetXTitle("pz distrubution");
      //z[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),subtitle[k].data(),i+1));

      fc[k][i]=(TH1F*)ftofCal->Clone(Form("fc%d%02i",k,i+1));
      fc[k][i]->SetXTitle("Calculated Time of Flight Distrubution");
      fc[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
			       subtitle[k].data(),i+1));

      if (k==1) d[k][i]=(TH1F*)dtof->Clone(Form("d%d%02i",k,i+1));
      if (k==0) d[k][i]=(TH1F*)dtofb->Clone(Form("d%d%02i",k,i+1));
      d[k][i]->SetXTitle("difference of measured time and expected time");
      d[k][i]->SetTitle(Form("%s, %s %d",title[k].data(),
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

  Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      for(int i=0;i<10;i++)countB[i]=0;
      for(int i=0;i<15;i++)countE[i]=0;
      int gsize=(genParE->size());
      for(int j=0;j<gsize;j++){
	 if(genParId->at(j)!= +13)continue;
          for(int i=0; i < hitSubDec->size(); i++){

        if(hitPID->at(i)!= +13)continue;
        int hitLayerIndex = hitLayer->at(i)-1;
        int hitDiskIndex = hitDisk->at(i)-1; 
        float calE = genParE ->at(j) ;
        //float calE2 = genParE ->at(1) ;
        //cout<<genParE->size();
        //cout<<"calE="<<calE<<endl
        //cout<<calE2;
        //cin>>calE;
        float calPt = genParPt ->at(j);
        //cout<<"calPt="<<calPt<<endl;
        float calPz = sqrt(calE*calE-calPt*calPt-0.01);
        //cout<<"calPz="<<calPz<<endl;
        float calVz = sqrt(( calPz* calPz)/(calPz* calPz+0.01));
        float calVt = sqrt(( calPt* calPt)/(calPt* calPt+0.01));
        //float calVt = 1;
        //cout<<"calVt="<<calVt<<endl;       
        float gloXY = sqrt(hitGlobalX->at(i)*hitGlobalX->at(i)+hitGlobalY->at(i)*hitGlobalY->at(i)) ;     
        float BR = calPt*0.877; //=pt/qB
        float angle =gloXY/BR/200;              
        float arcsin =asin(angle);       
        float calR =arcsin*BR*2;       
        float timeT = (calR*1000000000)/calVt/299792458;
        float timeZ =(abs(hitGlobalZ->at(i))*10000000)/calVz/299792458;
        if (timeZ>timeT)timeT=timeZ;
       
       
        //cout<<"gloXY="<<gloXY<<endl;  
        //cout<<"angle="<<angle<<endl;
        //cout<<"arcsin="<<arcsin<<endl;
        //cout<<"calR="<<calR<<endl;
        //cout<<"timeT="<<timeT<<endl;
        //cin>>calE;
	if(hitSubDec->at(i)==1)
	  {
	    countB[hitLayerIndex]++;
	    if(countB[hitLayerIndex]==1){
	      tofB[hitLayerIndex]= hitTof->at(i);
              f[0][hitLayerIndex]->Fill(tofB[hitLayerIndex]);
              //z[0][hitLayerIndex]->Fill(calPz);
              fc[0][hitLayerIndex]->Fill(timeT);
              d[0][hitLayerIndex]->Fill(tofB[hitLayerIndex]-timeT);
                  }
	    else if(countB[hitLayerIndex]>1)
	      ht[0][hitLayerIndex]->Fill(hitTof->at(i)-tofB[hitLayerIndex]);
	  }
	else
	  if(hitSubDec->at(i)==2)
	    {
	      countE[hitDiskIndex]++;
	      if(countE[hitDiskIndex]==1){
               
		tofE[hitDiskIndex]= hitTof->at(i);
                f[1][hitDiskIndex]->Fill(tofE[hitDiskIndex]);
                //z[1][hitDiskIndex]->Fill(calPz);
                fc[1][hitDiskIndex]->Fill(timeT);
                d[1][hitDiskIndex]->Fill(tofE[hitDiskIndex]-timeT);
                 }
	      else if(countE[hitDiskIndex]>1)
		ht[1][hitDiskIndex]->Fill(hitTof->at(i)-tofE[hitDiskIndex]);
	    }
	  }
      }
   
      
      for(int i=0;i<10;i++){
	hbarrel->Fill(i+1,countB[i]);
	h[0][i]->Fill(countB[i]);
      }
      for(int i=0;i<15;i++){
	hendcap->Fill(i+1,countE[i]);
	h[1][i]->Fill(countE[i]);
      }
      
      
   }

   //hbarrel->Draw();
   //hendcap->Draw();
   TFile* outFile = new TFile("histo.root","recreate");       
   
   hbarrel->Write();
   hendcap->Write();
   for(int i=0;i<2;i++){
     for(int j=0; j<15;j++)
       {
	 h[i][j]->Write();
	 ht[i][j]->Write();
         f[i][j]->Write();
    
       }
   }

  outFile->Close();

  
  //output ps
  
  for(int i=0;i<2;i++){
     for(int j=0; j<15;j++)
       {
	 /*   TCanvas* c1 = new TCanvas("c1"); 
         f[i][j]->Draw();
         gStyle->SetOptFit(1111);
         c1->SaveAs(Form("time_%d%02i.jpg",i,j));
         c1->~TCanvas();
         */
         //Print(f[i][j],Form("time_%d%02i.jpg",i,j+1)); 
         //Print(fc[i][j],Form("ctime_%d%02i.jpg",i,j+1));  
         Print(d[i][j],Form("dtime_%d%02i.jpg",i,j+1));  
       }
   }

 
}
