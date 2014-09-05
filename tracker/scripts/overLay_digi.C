#include <TH2.h>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>

using namespace std;

int COLOR[]={kRed, kBlue, kOrange, kGreen};
const int nBunches=20;

void overLay_digi(std::string fin)
{
  
  std::string remword = ".root";
  size_t pos  = fin.find(remword);
  std::string filename = fin;
  if(pos!= std::string::npos)
    filename.swap(filename.erase(pos,remword.length()));
  filename += ".pdf";
  cout << filename << endl;

  std::string filename2 = "zoomIn_" + filename;

  TFile* f  = new TFile(fin.data());

  TCanvas* c1 = new TCanvas("c1","",700,500);

  c1->cd();
  c1->SetLogy(1);
  int nLayers[2]={10,15};
  int count=0;
  for(int i=0; i<2; i++){
    for(int k=0; k< nLayers[i]; k++){
      TH1I* hall = (TH1I*)f->FindObjectAny(Form("hdiff%d%02i",i,k));
      hall->SetLineWidth(2);
      hall->SetLineColor(1);

      // normal figures
      hall->Draw("hist");
      
      for(int b=0; b < nBunches; b++){
	
	TH1I* hb = (TH1I*)f->FindObjectAny(Form("hdiff_digi_%d%02i_%02i",i,k,b));
	hb->SetLineWidth(2);
	hb->SetLineColor(COLOR[int(b%4)]);
	hb->Draw("histsame");
	
      }

      if(count==0)
	c1->Print(Form("%s(",filename.data()));
      else if(i==1 && k== nLayers[i]-1)
	c1->Print(Form("%s)",filename.data()));
      else
	c1->Print(filename.data());



      // zoom-in figures
      c1->Clear();
      hall->GetXaxis()->SetRange(0,100);
      hall->Draw("hist");
      
      for(int b=0; b < nBunches; b++){
	
	TH1I* hb = (TH1I*)f->FindObjectAny(Form("hdiff_digi_%d%02i_%02i",i,k,b));
	hb->SetLineWidth(2);
	hb->SetLineColor(COLOR[int(b%4)]);
	hb->GetXaxis()->SetRange(0,100);
	hb->Draw("histsame");
	
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
