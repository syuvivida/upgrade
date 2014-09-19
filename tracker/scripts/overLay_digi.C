#include <TH2.h>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TSystem.h>
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
  filename += "_allbunches.pdf";
  cout << filename << endl;

  std::string filename2 = "zoomIn_" + filename;

  TFile* f  = new TFile(fin.data());
  gSystem->mkdir("fig");

  TCanvas* c1 = new TCanvas("c1","",700,500);
  c1->cd();
  c1->SetLogy(1);
  int nLayers[2]={10,15};
  string title[2]={"barrel","endcap"};
  string xtitle[2]={"Layer","Disk"};
  int count=0;
  for(int i=0; i<2; i++){
    for(int k=0; k< nLayers[i]; k++){
      TH1I* hpt = (TH1I*)f->FindObjectAny(Form("hpt_ootdigi%d%02i",i,k));
      hpt->SetLineWidth(2);
      hpt->SetLineColor(1);
      hpt->Draw();
      TH1I* hp2 = (TH1I*)f->FindObjectAny(Form("hpt_intdigi%d%02i",i,k));
      hp2->SetLineWidth(2);
      hp2->SetLineColor(4);
      double scale = (double)hpt->Integral()/(double)hp2->Integral();
      hp2->Scale(scale);
      cout << hpt->Integral() << "\t" << hp2->Integral() << endl;
      hp2->Draw("same");
      gStyle->SetOptStat(0);

      double x1NDC = 0.603;
      double y1NDC = 0.732;
      double x2NDC = 0.735;
      double y2NDC = 0.877;

      TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
      leg->SetFillColor(0);
      leg->SetFillStyle(0);
      leg->SetTextSize(0.05);
      leg->SetBorderSize(0);
      leg->AddEntry(hp2,"In-Time Digitized");
      leg->AddEntry(hpt,"OOT Digitized");
      leg->Draw("same");
      if(count==0)
 	c1->Print(Form("fig/pt_%s(",filename.data()));
      else if(i==1 && k== nLayers[i]-1)
 	c1->Print(Form("fig/pt_%s)",filename.data()));
      else
 	c1->Print(Form("fig/pt_%s",filename.data()));
    
      // TH1I* hall = (TH1I*)f->FindObjectAny(Form("hdiff%d%02i",i,k));
      // hall->SetLineWidth(2);
      // hall->SetLineColor(1);

      // // normal figures
      // hall->Draw("hist");
    
      // for(int b=0; b < nBunches; b++){
	
      // 	TH1I* hb = (TH1I*)f->FindObjectAny(Form("hdiff_digi_%d%02i_%02i",i,k,b));
      // 	hb->SetLineWidth(2);
      // 	hb->SetLineColor(COLOR[int(b%4)]);
      // 	hb->Draw("histsame");
	
      // }

      // if(count==0)
      // 	c1->Print(Form("%s(",filename.data()));
      // else if(i==1 && k== nLayers[i]-1)
      // 	c1->Print(Form("%s)",filename.data()));
      // else
      // 	c1->Print(filename.data());



      // // zoom-in figures
      // c1->Clear();
      // hall->GetXaxis()->SetRangeUser(0,100);
      // hall->Draw("hist");
    
      // for(int b=0; b < nBunches; b++){
	
      // 	TH1I* hb = (TH1I*)f->FindObjectAny(Form("hdiff_digi_%d%02i_%02i",i,k,b));
      // 	hb->SetLineWidth(2);
      // 	hb->SetLineColor(COLOR[int(b%4)]);
      // 	hb->GetXaxis()->SetRangeUser(0,100);
      // 	hb->Draw("histsame");
	
      // }
      // c1->Print(Form("fig/digi_%d_%02i.pdf",i,k));
      // if(count==0)
      // 	c1->Print(Form("%s(",filename2.data()));
      // else if(i==1 && k== nLayers[i]-1)
      // 	c1->Print(Form("%s)",filename2.data()));
      // else
      // 	c1->Print(filename2.data());

      count++;

    } // end of loop over layers
  } // end of loop over detectors

  

  //   // normalize to all entries
  // TH1I* htemp[15];
  // gStyle->SetOptStat(0);
  // for(int i=0; i<2; i++){

  //   double x1NDC = 0.697;
  //   double y1NDC = i==1? 0.3565: 0.483;
  //   double x2NDC = 0.901;
  //   double y2NDC = 0.895;

  //   TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
  //   leg->SetFillColor(0);
  //   leg->SetFillStyle(0);
  //   leg->SetTextSize(0.05);
  //   leg->SetBorderSize(0);


  //   for(int k=0; k< nLayers[i]; k++){
      
  //     htemp[k] = (TH1I*)f->FindObjectAny(Form("hdiff%d%02i",i,k));
  //     htemp[k]->SetLineWidth(2);
  //     htemp[k]->SetLineColor((k==nLayers[i]-1) ? 1: kViolet-k*3);
  //     double scale = htemp[0]->GetEntries()/htemp[k]->GetEntries();
  //     cout << "Scale = " << scale << endl;
  //     htemp[k]->Scale(scale);
  //     cout << htemp[k]->Integral() << endl;
  //     htemp[k]->GetXaxis()->SetRangeUser(0,25);
  //     htemp[k]->SetTitle(title[i].data());
  //     // normal figures
  //     if(k==0)
  // 	htemp[k]->Draw("hist");
  //     else
  // 	htemp[k]->Draw("hist,same");
  //     leg->AddEntry(htemp[k],Form("%s %d",xtitle[i].data(),k+1));

  //   }
  //   leg->Draw("same");
  //   c1->Print(Form("alllayersNormalizeAll_%s.pdf",title[i].data()));
    

  // }
      

  // // normalize to beyond 25 ns

  // for(int i=0; i<2; i++){

  //   double x1NDC = 0.697;
  //   double y1NDC = i==1? 0.3565: 0.483;
  //   double x2NDC = 0.901;
  //   double y2NDC = 0.895;

  //   TLegend* leg = new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
  //   leg->SetFillColor(0);
  //   leg->SetFillStyle(0);
  //   leg->SetTextSize(0.05);
  //   leg->SetBorderSize(0);


  //   for(int k=0; k< nLayers[i]; k++){
      
  //     htemp[k] = (TH1I*)f->FindObjectAny(Form("hdiff%d%02i",i,k));
  //     htemp[k]->SetLineWidth(2);
  //     htemp[k]->SetLineColor((k==nLayers[i]-1) ? 1: kViolet-k*3);
  //     double scale = htemp[0]->Integral(25,500)/htemp[k]->Integral(25,500);
  //     cout << "Scale = " << scale << endl;
  //     htemp[k]->Scale(scale);
  //     cout << htemp[k]->Integral() << endl;
  //     htemp[k]->GetXaxis()->SetRangeUser(25,100);
  //     htemp[k]->SetTitle(title[i].data());
  //     // normal figures
  //     if(k==0)
  // 	htemp[k]->Draw("hist");
  //     else
  // 	htemp[k]->Draw("hist,same");
  //     leg->AddEntry(htemp[k],Form("%s %d",xtitle[i].data(),k+1));

  //   }
  //   leg->Draw("same");
  //   c1->Print(Form("alllayersNormalizeTail_%s.pdf",title[i].data()));
    

  // }
      



}
