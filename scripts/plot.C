#include <TH2.h>
#include <string>

using namespace std;

void plot(){

  TFile *inf = new TFile("histo-13.root");
  
  TCanvas* c1 = new TCanvas("c1","",500,500);
  std::string name="anti-muon";
  gSystem->Exec(Form("mkdir %s",name.data()));

  TH2F* h1 = (TH2F*)inf->FindObjectAny("hbarrel");
  h1->Draw("box");
  c1->Print(Form("%s/hbarrelMap.gif",name.data()));

  h1 = (TH2F*)inf->FindObjectAny("hendcap");
  h1->Draw("box");
  c1->Print(Form("%s/hendcapMap.gif",name.data()));
  for(int i=0;i<2;i++){
    int end=(i==0)?4:10;
    for(int k=0; k<end; k++)
      {
	c1->SetLogy(1);
	TH1F *h = (TH1F*)inf->FindObjectAny(Form("h%d%02i",i,k));
	h->Draw();
	cout << h->GetName() << endl;
	c1->Print(Form("%s/%s.gif",name.data(),h->GetName()));
      }
  }

  for(int i=0;i<2;i++){
    int end=(i==0)?4:10;
    for(int k=0; k<end; k++)
      {
	c1->SetLogy(1);
	TH1F *h = (TH1F*)inf->FindObjectAny(Form("ht%d%02i",i,k));
	h->Draw();
	cout << h->GetName() << endl;
	c1->Print(Form("%s/%s.gif",name.data(),h->GetName()));
      }
  }
  

}
