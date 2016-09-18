#include <fstream>
#include <iostream>
#include <TH2.h>
#include <string>
#include <TFile.h>
#include <TSystem.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include "setNCUStyle.C"

using namespace std;


void plotScatter2D(string inputFile, string histoPrefix="HighGain_LowGain_2D_lct10100")
{
  setNCUStyle();
  TH2F* h2D;
  TFile *f1 = TFile::Open(inputFile.data());

  TString prefix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; test2=${test%%_HGC*}; echo \"${test2}\"",inputFile.data()));
  string prefix_string = prefix.Data();
  
  h2D = (TH2F*)(f1->FindObjectAny(Form("%s",histoPrefix.data())));
  gStyle->SetOptStat(0);

  TCanvas* c1 = new TCanvas("c1","",500,500);
  h2D->SetTitle(Form("%s, layer 1, skiroc 1, cell type 0",prefix.Data()));
  h2D->SetXTitle("Low-Gain ADC counts");
  h2D->SetYTitle("High-Gain ADC counts");
  h2D->SetTitleOffset(1.6,"Y");
  h2D->Draw();
  gSystem->mkdir("figures");
  string output= "figures/scatter2D_" + prefix_string + "_" + histoPrefix;
  string outputFile = output + ".pdf";
  c1->Print(outputFile.data());
  outputFile = output + ".gif";
  c1->Print(outputFile.data());


}
