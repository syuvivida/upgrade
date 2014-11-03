#include <TH2.h>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TSystem.h>
#include <TString.h>
using namespace std;

int COLOR[]={kRed, kBlue, kOrange, kGreen};
const int nBunches=20;

void overLay_digi(std::string fin)
{
  TString endfix=gSystem->GetFromPipe(Form("file=%s; test=${file##*histo_oot_}; echo \"${test%%_timeW03.root*}\"",fin.data()));
  std::string filename = Form("diffdigi_%s_allbunches.pdf",endfix.Data());

  std::string filename2 = "zoomIn_" + filename;

  TFile* f  = new TFile(fin.data());
  gSystem->mkdir("fig");

  TCanvas* c1 = new TCanvas("c1","",1400,500);
  c1->Divide(2,1);
  int nLayers[2]={10,15};
  int count=0;
  for(int i=0; i<2; i++){
    for(int k=0; k< nLayers[i]; k++){

      c1->cd(1);
      gPad->SetLogy(1);
      TH1I* hall = (TH1I*)f->FindObjectAny(Form("hdiff%d%02i",i,k));
      hall->SetLineWidth(2);
      hall->SetLineColor(1);
      hall->GetXaxis()->SetTitleSize(0.05);

      // // normal figures
      hall->Draw("hist");
    
      for(int b=0; b < nBunches; b++){
	
       	TH1I* hb = (TH1I*)f->FindObjectAny(Form("hdiff_digi_%d%02i_%02i",i,k,b));
       	hb->SetLineWidth(2);
       	hb->SetLineColor(COLOR[int(b%4)]);
       	hb->Draw("histsame");
	
      }


      c1->cd(2);
      gPad->SetLogy(1);
      TH1I* hall2 = (TH1I*)f->FindObjectAny(Form("hdiff2%d%02i",i,k));
      hall2->SetLineWidth(2);
      hall2->SetLineColor(1);
      hall2->GetXaxis()->SetTitleSize(0.05);

      // // normal figures
      hall2->Draw("hist");
    
      for(int b=0; b < nBunches; b++){
	
       	TH1I* hb2 = (TH1I*)f->FindObjectAny(Form("hdiff2_digi_%d%02i_%02i",i,k,b));
       	hb2->SetLineWidth(2);
       	hb2->SetLineColor(COLOR[int(b%4)]);
       	hb2->Draw("histsame");
	
      }

      if(count==0)
       	c1->Print(Form("%s(",filename.data()));
      else if(i==1 && k== nLayers[i]-1)
      	c1->Print(Form("%s)",filename.data()));
      else
       	c1->Print(filename.data());



      // // zoom-in figures
      c1->cd(1);
      hall->GetXaxis()->SetRangeUser(0,100);
      hall->Draw("hist");
    
      for(int b=0; b < nBunches; b++){
	
       	TH1I* hb = (TH1I*)f->FindObjectAny(Form("hdiff_digi_%d%02i_%02i",i,k,b));
       	hb->SetLineWidth(2);
	hb->SetLineColor(COLOR[int(b%4)]);
       	hb->GetXaxis()->SetRangeUser(0,100);
       	hb->Draw("histsame");
	
      }

      c1->cd(2);
      hall2->GetXaxis()->SetRangeUser(0,100);
      hall2->Draw("hist");
    
      for(int b=0; b < nBunches; b++){
	
       	TH1I* hb2 = (TH1I*)f->FindObjectAny(Form("hdiff2_digi_%d%02i_%02i",i,k,b));
       	hb2->SetLineWidth(2);
	hb2->SetLineColor(COLOR[int(b%4)]);
       	hb2->GetXaxis()->SetRangeUser(0,100);
       	hb2->Draw("histsame");
	
      }

      if(count==0)
       	c1->Print(Form("%s(",filename2.data()));
      else if(i==1 && k== nLayers[i]-1)
       	c1->Print(Form("%s)",filename2.data()));
      else
       	c1->Print(filename2.data());

      count++;

    } // end of loop over layers
  } // end of loop over detectors

  



}
