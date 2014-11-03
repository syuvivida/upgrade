#include <TH2.h>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TString.h>
#include <TLegend.h>

using namespace std;

void plotAllDiff(TString fin, TString histoName="hdiff"){

  TFile* inf = new TFile(fin.Data());
  TString endfix=gSystem->GetFromPipe(Form("file=%s; test=${file##*histo_oot_charged_}; echo \"${test%%_timeW03.root*}\"",fin.Data()));
  TString filename = Form("all%s_%s.pdf",histoName.Data(),endfix.Data());
  cout << "Output file = " << filename << endl;

  TCanvas* c1 = new TCanvas("c1","",700,500);
  // c1->SetLogy(1);
  gStyle->SetOptStat(0);
  const int nLayers[2] = {10,15};
  c1->cd();

  TLegend* leg = new TLegend(0.6264,0.6835,0.8764,0.8860);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->SetBorderSize(0);
  for(int i=0; i<2; i++){
    for(int j=0; j< nLayers[i]; j++){

      leg->Clear();
      TH1F* h1 = (TH1F*)inf->FindObjectAny(Form("%s2%d%02i",histoName.Data(),i,j));
      h1->SetMinimum(0);
      h1->SetLineWidth(3);
      h1->SetLineColor(2);
      h1->GetXaxis()->SetRangeUser(-5,5);
      h1->GetXaxis()->SetTitleSize(0.05);
      h1->GetXaxis()->SetTitle("Difference of TOF from the expectation [ns]");
      h1->Draw();

      TH1F* h2 = (TH1F*)inf->FindObjectAny(Form("%s%d%02i",histoName.Data(),i,j));
      h2->SetMinimum(0);
      h2->SetLineWidth(3);
      h2->SetLineColor(4);
      h2->GetXaxis()->SetRangeUser(-5,5);
      h2->Draw("same");

      leg->AddEntry(h2,"Electronics");
      leg->AddEntry(h1,"Method 2");
      leg->Draw();

      if(i==0 && j==0)
	c1->Print(Form("%s(",filename.Data()));
      else if(i==1 && j== nLayers[i]-1)
      c1->Print(Form("%s)",filename.Data()));
      else
	c1->Print(filename.Data());
  
    }
  }
  


}
