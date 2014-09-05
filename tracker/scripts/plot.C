#include <TH2.h>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>

using namespace std;

void plot(std::string fin){

  TFile *inf = new TFile(fin.data());
  std::string remword = ".root";
  size_t pos  = fin.find(remword);
  std::string filename = fin;
  if(pos!= std::string::npos)
    filename.swap(filename.erase(pos,remword.length()));
  filename += ".pdf";
  cout << filename << endl;

  
  TCanvas* c1 = new TCanvas("c1","",700,500);
  gStyle->SetOptStat(0);

  c1->cd();

  TH1F* h1 = (TH1F*)inf->FindObjectAny("hoot_Barrel");
  h1->SetMinimum(0);
  h1->SetXTitle("Layer");
  h1->Draw();
  c1->Print(Form("%s(",filename.data()));

  TH1F* h3 = (TH1F*)inf->FindObjectAny("hoot_digi_Barrel");
  h3->SetMinimum(0);
  h3->SetXTitle("Layer");
  h3->Draw();
  c1->Print(filename.data());

  TH1F* h4 = (TH1F*)inf->FindObjectAny("hoot_digi_oot_Barrel");
  h4->SetMinimum(0);
  h4->SetXTitle("Layer");
  h4->Draw();
  c1->Print(filename.data());


  TH1F* h5 = (TH1F*)inf->FindObjectAny("hoot_Endcap");
  h5->SetMinimum(0);
  h5->SetXTitle("Disk");
  h5->Draw();
  c1->Print(filename.data());

  TH1F* h7 = (TH1F*)inf->FindObjectAny("hoot_digi_Endcap");
  h7->SetMinimum(0);
  h7->SetXTitle("Disk");
  h7->Draw();
  c1->Print(filename.data());

  TH1F* h8 = (TH1F*)inf->FindObjectAny("hoot_digi_oot_Endcap");
  h8->SetMinimum(0);
  h8->SetXTitle("Disk");
  h8->Draw();
  c1->Print(Form("%s)",filename.data()));
  
  


}
