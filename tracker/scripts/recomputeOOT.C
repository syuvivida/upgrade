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

Long64_t computeNOOT(TH1I* hinput,TH1F* houtput, int bin)
{
  float fraction=-1;
  float fraction_err=-1;
  // Long64_t nOOT = hinput->Integral(23,501);
  Long64_t nOOT = hinput->Integral(148,501);
  errmc(nOOT,
	hinput->GetEntries(),
	fraction, fraction_err,houtput,bin);
  return nOOT;
}

void computeDigi(TH1I* hinput, TH1F* houtput, Long64_t nOOT, int bin)
{
  float fraction=-1;
  float fraction_err=-1;

  // errmc(hinput->Integral(2,21),
  errmc(hinput->Integral(7,21),
	nOOT,
	fraction, fraction_err,houtput,bin);

}

void computeOOTDigi(TH1I* hinput1, TH1I* hinput2, TH1F* houtput,int bin)
{
  float fraction=-1;
  float fraction_err=-1;

  errmc(hinput1->Integral(2,21),
	hinput2->GetEntries(),
	fraction, fraction_err,houtput,bin);

}

void computeOOTLost(TH1I* hinput1, TH1I* hinput2, TH1F* houtput,int bin)
{
  float fraction=-1;
  float fraction_err=-1;

  errmc(hinput2->GetEntries()-hinput1->GetEntries(),
	hinput2->GetEntries(),
	fraction, fraction_err,houtput,bin);

}

void recomputeOOT(std::string fin)
{
  TString endfix=gSystem->GetFromPipe(Form("file=%s; echo \"${file##*histo_oot_}\"",fin.data()));
  // std::string filename = Form("histo_oot2_%s",endfix.Data());
  std::string filename = Form("histo_oot3_%s",endfix.Data());
  cout << filename << endl;

  const int nLayers[2] = {10,15};
  std::string title[2]={"Barrel","Endcap"};


  TFile* f  = new TFile(fin.data());
  TH1F* hoot[2];
  TH1F* hoot_digi_oot[2];
  TH1F* hdigi[2];
  TH1F* hlost[2];

  TH1F* hoot2[2];
  TH1F* hoot_digi_oot2[2];
  TH1F* hdigi2[2];
  TH1F* hlost2[2];

  TH1F* hoot3[2];
  TH1F* hoot_digi_oot3[2];
  TH1F* hdigi3[2];
  TH1F* hlost3[3];

  for(int k=0; k<2; k++)
    {
      hoot[k] = new TH1F(Form("hoot_%s",title[k].data()),Form("Fraction of Hits Not Digitized In-Time Relative to All Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi_oot[k] = new TH1F(Form("hoot_digi_oot_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits Not Digitized In-Time in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hdigi[k] = new TH1F(Form("hdigi_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hlost[k] = new TH1F(Form("hlost_%s",title[k].data()),Form("Fraction of Non-digitized Hits Relative to All Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));


      hoot2[k] = new TH1F(Form("hoot2_%s",title[k].data()),Form("Fraction of Hits Not Digitized In-Time Relative to All Hits in %s 2",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi_oot2[k] = new TH1F(Form("hoot2_digi_oot_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits Not Digitized In-Time in %s 2",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hdigi2[k] = new TH1F(Form("hdigi2_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hlost2[k] = new TH1F(Form("hlost2_%s",title[k].data()),Form("Fraction of Non-digitized Hits Relative to All Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));

      hoot3[k] = new TH1F(Form("hoot3_%s",title[k].data()),Form("Fraction of Hits Not Digitized In-Time Relative to All Hits in %s 3",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hoot_digi_oot3[k] = new TH1F(Form("hoot3_digi_oot_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits Not Digitized In-Time in %s 3",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hdigi3[k] = new TH1F(Form("hdigi3_%s",title[k].data()),Form("Fraction of Digitized OOT Hits Relative to All Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      hlost3[k] = new TH1F(Form("hlost3_%s",title[k].data()),Form("Fraction of Non-digitized Hits Relative to All Hits in %s",title[k].data()),nLayers[k],0.5,(float)(nLayers[k]+0.5));
      

      

    }

  TFile* outFile = new TFile(filename.data(),"recreate");       
  for(int i=0;i<2;i++){
    for(int j=0; j<nLayers[i] ;j++)
      {
	TH1I* hdiff=(TH1I*)f->FindObjectAny(Form("hdiff%d%02i",i,j));
	Long64_t nOOT  = computeNOOT(hdiff,hoot[i],j);
	TH1I* hr=(TH1I*)f->FindObjectAny(Form("hr%d%02i",i,j));
	computeDigi(hr,hoot_digi_oot[i],nOOT,j);

	computeOOTDigi(hr,hdiff,hdigi[i],j);
	computeOOTLost(hr,hdiff,hlost[i],j);

	hdiff=(TH1I*)f->FindObjectAny(Form("hdiff2%d%02i",i,j));
	Long64_t nOOT2 = computeNOOT(hdiff,hoot2[i],j);
	hr=(TH1I*)f->FindObjectAny(Form("hr2%d%02i",i,j));
	computeDigi(hr,hoot_digi_oot2[i],nOOT2,j);

	computeOOTDigi(hr,hdiff,hdigi2[i],j);
	computeOOTLost(hr,hdiff,hlost2[i],j);

	hdiff=(TH1I*)f->FindObjectAny(Form("hdiff3%d%02i",i,j));
	Long64_t nOOT3 = computeNOOT(hdiff,hoot3[i],j);
	hr=(TH1I*)f->FindObjectAny(Form("hr3%d%02i",i,j));
	computeDigi(hr,hoot_digi_oot3[i],nOOT3,j);

	computeOOTDigi(hr,hdiff,hdigi3[i],j);
	computeOOTLost(hr,hdiff,hlost3[i],j);



      }// end of loop over layers
  }

 for(int i=0;i<2;i++){
    hoot[i]->Write();
    hoot2[i]->Write();
    hoot3[i]->Write();
    hdigi[i]->Write();
    hdigi2[i]->Write();
    hdigi3[i]->Write();

    hlost[i]->Write();
    hlost2[i]->Write();
    hlost3[i]->Write();


    hoot_digi_oot[i]->Write();
    hoot_digi_oot2[i]->Write();
    hoot_digi_oot3[i]->Write();
 }
  outFile->Close();



}
