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

void overLay_shape(std::string fin)
{
  TString endfix=gSystem->GetFromPipe(Form("file=%s; test=${file##*histo_oot_}; echo \"${test%%_timeW03.root*}\"",fin.data()));
  std::string filename = Form("shapediff_%s_alllayers.pdf",endfix.Data());
  cout << "Output file = " << filename << endl;


  TFile* f  = new TFile(fin.data());

  // normalize to all entries
  string title[2]={"Barrel","Endcaps"};
  string xtitle[2]={"Layer","Disk"};
  int nLayers[2]={10,15};
  TCanvas* c1 = new TCanvas("c1","",1400,500);
  c1->Divide(2,1);

  TH1I* htemp[15];
  TH1I* htemp2[15];
  gStyle->SetOptStat(0);
  for(int i=0; i<2; i++){

    double x1NDC = 0.697;
    double y1NDC = i==1? 0.3565: 0.483;
    double x2NDC = 0.901;
    double y2NDC = 0.895;

    c1->cd(1);
    gPad->SetLogy(1);

    TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.05);
    leg->SetBorderSize(0);


    for(int k=0; k< nLayers[i]; k++){
      
      htemp[k] = (TH1I*)f->FindObjectAny(Form("hdiff%d%02i",i,k));
      htemp[k]->SetLineWidth(2);
      htemp[k]->SetLineColor((k==nLayers[i]-1) ? 1: kViolet-k*3);
      double scale = htemp[0]->GetEntries()/htemp[k]->GetEntries();
      cout << "Scale = " << scale << endl;
      htemp[k]->Scale(scale);
      cout << htemp[k]->Integral() << endl;
      htemp[k]->GetXaxis()->SetRangeUser(0,25);
      htemp[k]->SetTitle(title[i].data());
      // normal figures
      if(k==0)
	htemp[k]->Draw("hist");
      else
	htemp[k]->Draw("hist,same");
      leg->AddEntry(htemp[k],Form("%s %d",xtitle[i].data(),k+1));

    }
    leg->Draw("same");

    c1->cd(2);
    gPad->SetLogy(1);

    TLegend* leg2 = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
    leg2->SetFillColor(0);
    leg2->SetFillStyle(0);
    leg2->SetTextSize(0.05);
    leg2->SetBorderSize(0);


    for(int k=0; k< nLayers[i]; k++){
      
      htemp2[k] = (TH1I*)f->FindObjectAny(Form("hdiff2%d%02i",i,k));
      htemp2[k]->SetLineWidth(2);
      htemp2[k]->SetLineColor((k==nLayers[i]-1) ? 1: kViolet-k*3);
      double scale = htemp2[0]->GetEntries()/htemp2[k]->GetEntries();
      cout << "Scale = " << scale << endl;
      htemp2[k]->Scale(scale);
      cout << htemp2[k]->Integral() << endl;
      htemp2[k]->GetXaxis()->SetRangeUser(0,25);
      htemp2[k]->SetTitle(title[i].data());
      // normal figures
      if(k==0)
	htemp2[k]->Draw("hist");
      else
	htemp2[k]->Draw("hist,same");
      leg2->AddEntry(htemp2[k],Form("%s %d",xtitle[i].data(),k+1));

    }
    leg2->Draw("same");

    if(i==0)
	c1->Print(Form("%s(",filename.data()));
    else
	c1->Print(Form("%s)",filename.data()));
    
    

  }
      




}
