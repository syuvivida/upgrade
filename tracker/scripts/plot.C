#include <TH2.h>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TSystem.h>

using namespace std;
TFile* inf;
TCanvas* c1;

void plotHisto(std::string histoName, std::string xtitle)
{
  TH1F* h1 = (TH1F*)inf->FindObjectAny(histoName.data());
  h1->SetMinimum(0);
  h1->SetXTitle(xtitle.data());
  h1->SetMarkerColor(4);
  h1->SetMarkerStyle(8);
  h1->SetMarkerSize(1);
  h1->Draw();
  c1->Print(Form("fig/%s.pdf",histoName.data()));

}

void plot(std::string fin){

  inf = new TFile(fin.data());
  std::string remword = ".root";
  size_t pos  = fin.find(remword);
  std::string filename = fin;
  if(pos!= std::string::npos)
    filename.swap(filename.erase(pos,remword.length()));
  filename += ".pdf";
  cout << filename << endl;

  gSystem->mkdir("fig");
  c1 = new TCanvas("c1","",700,500);
  gStyle->SetOptStat(0);

  c1->cd();

  plotHisto("hoot_Barrel","Layer");
  c1->Print(Form("%s(",filename.data()));

  plotHisto("hoot_digi_Barrel","Layer");
  c1->Print(filename.data());
  
  plotHisto("hoot_digi_oot_Barrel","Layer");
  c1->Print(filename.data());

  plotHisto("hoot_Endcap","Disk");
  c1->Print(filename.data());
  
  plotHisto("hoot_digi_Endcap","Disk");
  c1->Print(filename.data());

  plotHisto("hoot_digi_oot_Endcap","Disk");
  c1->Print(Form("%s)",filename.data()));
  
  


}
