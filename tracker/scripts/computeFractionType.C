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
void fractionClear(float & a,float & b)
{ 
a=-1;
b=-1;
}

void errmc(float nsig,float ntotal, float& eff, float& err ,TH1F* fHisto,int& j )
{
  //cout << "nsig = " << nsig << " ntotal = " << ntotal << endl;
  if(ntotal<1e-6){eff=-1; err=-1; return;}
  eff = nsig/ntotal;
  err = sqrt( (1-eff)*eff/ntotal);
  if(eff>1e-6 && err>1e-6)
    {
     fHisto->SetBinContent(j+1,eff);
     fHisto->SetBinError(j+1,err);
    }
  fractionClear(eff,err);
  return;
}

void computeType2(TH1I* hinput,TH1F* houtput, int bin)
{
  float fraction=-1;
  float fraction_err=-1;
  errmc(hinput->GetBinContent(2),
	hinput->GetBinContent(1),
	fraction, fraction_err,houtput,bin);
}


void computeFractionType(std::string fin)
{

  const int nLayers[2] = {10,15};
  std::string title[2]={"Barrel","Endcaps"};


  TFile* f  = new TFile(fin.data());
  TH1F* hoot[2];
  TH1F* hall[2];
  TH1F* hdigi[2];
  TH1F* hnorm[2];

  for(int k=0; k<2; k++)
    {
      hnorm[k] = new TH1F(Form("hnorm_%s",title[k].data()),Form("Fraction of Primary vs Secondary Particles (%s)",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hnorm[k]->SetFillColor(kYellow-9);
      hnorm[k]->SetFillStyle(1001);

      hall[k] = new TH1F(Form("hall_%s",title[k].data()),Form("Fraction of Primary vs Secondary Particles: All Hits (%s)",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hall[k]->SetFillColor(kMagenta-9);
      hall[k]->SetFillStyle(3244);

      hoot[k] = new TH1F(Form("hoot_%s",title[k].data()),Form("Fraction of Primary vs Secondary Particles: OOT Hits (%s)",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot[k]->SetFillColor(kMagenta-9);
      hoot[k]->SetFillStyle(3244);

      hdigi[k] = new TH1F(Form("hdigi_%s",title[k].data()),Form("Fraction of Primary vs Secondary Particles: Digitized OOT Hits (%s)",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hdigi[k]->SetFillColor(kMagenta-9);
      hdigi[k]->SetFillStyle(3244);
    }
  TLegend* leg = new TLegend(0.6264,0.4835,0.8764,0.6860);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.05);
  leg->SetBorderSize(0);
  TFile* outFile = new TFile("minbias_fraction.root","recreate");       
  TCanvas* c1= new TCanvas("c1","",500,500);
  for(int i=0;i<2;i++){
    for(int j=0; j<nLayers[i] ;j++)
      {
	TH1I* h=(TH1I*)f->FindObjectAny(Form("halltype%d%02i",i,j));
	computeType2(h,hall[i],j);
	h=(TH1I*)f->FindObjectAny(Form("hoottype%d%02i",i,j));
	computeType2(h,hoot[i],j);
	h=(TH1I*)f->FindObjectAny(Form("hdigitype%d%02i",i,j));
	computeType2(h,hdigi[i],j);
        hnorm[i]->SetBinContent(j+1,1);
      }// end of loop over layers

    gStyle->SetOptStat(0);
    hnorm[i]->SetMaximum(1.1);
    hnorm[i]->SetMinimum(0);
    hnorm[i]->SetTitle(hall[i]->GetTitle());
    hnorm[i]->Draw("hist");
    hall[i]->Draw("histsame");
    leg->Clear();
    leg->AddEntry(hall[i],"Primary");
    leg->AddEntry(hnorm[i],"Secondary");
    leg->Draw("same");
    c1->Print(Form("typefraction_all_%s.pdf",title[i].data()));
    

    hnorm[i]->SetTitle(hoot[i]->GetTitle());
    hnorm[i]->Draw("hist");
    hoot[i]->Draw("histsame");
    leg->Clear();
    leg->AddEntry(hoot[i],"Primary");
    leg->AddEntry(hnorm[i],"Secondary");
    leg->Draw("same");
    c1->Print(Form("typefraction_oot_%s.pdf",title[i].data()));
     

    hnorm[i]->SetTitle(hdigi[i]->GetTitle());
    hnorm[i]->Draw("hist");
    hdigi[i]->Draw("histsame");
    leg->Clear();
    leg->AddEntry(hdigi[i],"Primary");
    leg->AddEntry(hnorm[i],"Secondary");
    leg->Draw("same");
    c1->Print(Form("typefraction_digi_%s.pdf",title[i].data()));

  }

 for(int i=0;i<2;i++){
    hnorm[i]->Write();
    hoot[i]->Write();
    hdigi[i]->Write();
    hall[i]->Write();
 }
  outFile->Close();



}
