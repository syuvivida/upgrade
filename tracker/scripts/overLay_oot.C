#include <TH2.h>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TSystem.h>

using namespace std;

TH1F* h[2];
int COLOR[3]={kBlue,kRed};
int MARKER[3]={8, 24};
int nCanvas=0;
TCanvas* c1;
std::string dataset[2]={"Electronics","Method 2"};
TFile* f;
TString endfix;
void plot(std::string histoName, std::string xtitle)
{
  nCanvas++;
  double x1NDC = (nCanvas%3==2)? 0.1322: 0.6264;
  double y1NDC = (nCanvas%3==2)? 0.6835: 0.1414;
  double x2NDC = (nCanvas%3==2)? 0.3822: 0.8764;
  double y2NDC = (nCanvas%3==2)? 0.8860: 0.3439;

  TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->SetBorderSize(0);

  std::string tempName[2];
  tempName[0]=histoName;
  TString endfix2=gSystem->GetFromPipe(Form("file=%s; echo \"${file##*hoot}\"",histoName.data()));
  tempName[1]=Form("hoot2%s",endfix2.Data());
  cout << tempName[1] << endl;
  for(int i=0; i< 2; i++){

    h[i] = (TH1F*)f->FindObjectAny(tempName[i].data());
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
  c1->Print(Form("fig/%s_%s.pdf",endfix.Data(),histoName.data()));
}


void overLay_oot(std::string fin){

  f= new TFile(fin.data());
  endfix=gSystem->GetFromPipe(Form("file=%s; test=${file##*histo_oot_}; echo \"${test%%_timeW03.root*}\"",fin.data()));

  std::string filename = Form("%s.pdf",endfix.Data());

  gSystem->mkdir("fig");
  
  c1 = new TCanvas("c1","",700,500);
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
