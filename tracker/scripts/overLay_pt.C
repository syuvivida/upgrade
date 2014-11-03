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

void overLay_pt(std::string fin)
{
  
  TString endfix=gSystem->GetFromPipe(Form("file=%s; test=${file##*histo_oot_charged_}; echo \"${test%%_timeW03.root*}\"",fin.data()));
  std::string filename = Form("pt_%s_5bunches.pdf",endfix.Data());
  cout << "Output file = " << filename << endl;


  TFile* f  = new TFile(fin.data());
  gSystem->mkdir("fig");

  TCanvas* c1 = new TCanvas("c1","",700,500);
  c1->cd();
  c1->SetLogy(1);
  int nLayers[2]={10,15};
  int count=0;
  for(int i=0; i<2; i++){
    for(int k=0; k< nLayers[i]; k++){
      TH1I* hpt = (TH1I*)f->FindObjectAny(Form("hpt_digi%d%02i_00",i,k));
      hpt->SetLineWidth(3);
      hpt->SetLineColor(1);
      TH1I* hpt_oot[4];
      for(int ib=0; ib<4; ib++){
	hpt_oot[ib]
	  = (TH1I*)f->FindObjectAny(Form("hpt_digi%d%02i_%02i",i,k,ib+1));
	hpt_oot[ib]->SetLineWidth(3);
	hpt_oot[ib]->SetLineColor(COLOR[ib]);
	double scale = (double)hpt->Integral()/(double)hpt_oot[ib]->Integral();
	hpt_oot[ib]->Scale(scale);
	cout << hpt->Integral() << "\t" << hpt_oot[ib]->Integral() << endl;
      }

      hpt_oot[0]->Draw();
      hpt->Draw("same");
      for(int ib=0; ib<4; ib++)hpt_oot[ib]->Draw("same");
	

      gStyle->SetOptStat(0);

      double x1NDC = 0.523;
      double y1NDC = 0.555;
      double x2NDC = 0.654;
      double y2NDC = 0.876;

      TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
      leg->SetFillColor(0);
      leg->SetFillStyle(0);
      leg->SetTextSize(0.05);
      leg->SetBorderSize(0);
      leg->AddEntry(hpt,"In-Time Digitized");
      for(int ib=0;ib<4;ib++)
	leg->AddEntry(hpt_oot[ib],Form("OOT Digitized in BX %d",ib+1));
      leg->Draw("same");
      if(count==0)
	{
	  c1->Print(Form("fig/%s(",filename.data()));
	  c1->Print("fig/example_pt.pdf");
	  c1->Print("fig/example_pt.eps");
	  c1->Print("fig/example_pt.fig");
	}
      else if(i==1 && k== nLayers[i]-1)
 	c1->Print(Form("fig/%s)",filename.data()));
      else
 	c1->Print(Form("fig/%s",filename.data()));
    

      count++;

    } // end of loop over layers
  } // end of loop over detectors



}
