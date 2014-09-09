#include <TH2.h>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>

using namespace std;

TFile* f[3];
TH1F* h[3];
int COLOR[3]={kRed, kBlack, kBlue};
int MARKER[3]={8, 24, 34};
int nCanvas=0;

std::string dataset[3]={"QCD+140PU","QCD","MinBias"};


void plot(std::string histoName, std::string xtitle)
{
  nCanvas++;
  double x1NDC = (nCanvas%2==0)? 0.6264 : 0.1322;
  double y1NDC = 0.6835;
  double x2NDC = (nCanvas%2==0)? 0.8764 : 0.3822;
  double y2NDC = 0.8860;

  TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->SetBorderSize(0);


  for(int i=0; i< 3; i++){

    h[i] = (TH1F*)f[i]->FindObjectAny(histoName.data());
    h[i]->SetXTitle(xtitle.data());
    h[i]->SetLineColor(COLOR[i]);
    h[i]->SetMarkerColor(COLOR[i]);
    h[i]->SetMarkerSize(1);
    h[i]->SetMarkerStyle(MARKER[i]);
    h[i]->SetMinimum(0);
    if(i==0)
      h[i]->Draw("e");
    else
      h[i]->Draw("esame");

    leg->AddEntry(h[i],dataset[i].data());
    
  }
  leg->Draw("same");

}


void overLay(){


  f[0]  = new TFile("histo_oot_140PU_QCD.root");
  f[1] = new TFile("histo_oot_QCD.root");
  f[2] = new TFile("histo_oot_minBias.root");


  std::string filename = "all.pdf";

  
  
  TCanvas* c1 = new TCanvas("c1","",700,500);
  gStyle->SetOptStat(0);

  c1->cd();
  
  plot("hoot_Barrel","Layer");
  c1->Print(Form("%s(",filename.data()));

  plot("hoot_digi_Barrel","Layer");
  c1->Print(filename.data());

  plot("hoot_digi_oot_Barrel","Layer");
  c1->Print(filename.data());


  plot("hoot_Endcap","Disk");
  c1->Print(filename.data());

  plot("hoot_digi_Endcap","Disk");
  c1->Print(filename.data());

  plot("hoot_digi_oot_Endcap","Disk");
  c1->Print(Form("%s)",filename.data()));
  
  


}
