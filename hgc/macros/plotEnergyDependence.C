#include <TGraphErrors.h>
#include <fstream>
#include <iostream>
#include <string>
#include <TCanvas.h>

using namespace std;


void plotEnergyDependence()
{
  const int NFILES=6;
  string LabelNames[NFILES]={"e 70GeV (p4)",
			"e 100GeV (p4)",
			"e 150GeV (p4)",
			"e 250GeV (p4)",
			"e 250GeV(p2)",
			"pi 125 GeV (p3)"};
  string inputNames[NFILES]={
    "electron70GeV",
    "electron100GeV",
    "electron150GeV",
    "electron250GeV",
    "electron250GeV_overnight_lead5cm",
    "pion125GeV"
  };


  std::vector<double> myLGs[5];
  std::vector<double> myLGErrs[5];
  std::vector<double> myHGs[5];
  std::vector<double> myHGErrs[5];
  std::vector<int> myRuns[5];
  
 
  for(int i=0;i<NFILES;i++){
    ifstream fin;
    fin.open(Form("output_data/%s_HighGain_LowGain_2D_type.dat",inputNames[i].data()));
    cout << "opening " << Form("output_data/%s_HighGain_LowGain_2D_type.dat",inputNames[i].data()) << endl;
    while(!fin.eof())
      {
	string run;
	int type;
	double lg, lgerr, hg, hgerr;
	fin >> run >> type >> lg >> lgerr >> hg >> hgerr;
	cout << run << endl;
      if(!fin.eof() && run=="all"){
	myRuns[type].push_back(i);
	myLGs[type].push_back(lg);
	myLGErrs[type].push_back(lgerr);
	myHGs[type].push_back(hg);
	myHGErrs[type].push_back(hgerr);	
      }
      
    }
  }

  TGraphErrors* graph_lg[5];
  TGraphErrors* graph_hg[5];

  TMultiGraph *mg = new TMultiGraph();
  TMultiGraph *mg_h = new TMultiGraph();
  int MARKERS[5]={20,21,22,23,24};
  int COLORS[5]={1,4,2,1,kGreen+1};
  
  // low gain
  for(int itype=0; itype<5; itype++)
    {
      if(myRuns[itype].size()==0)continue;
      const int nRuns = myRuns[itype].size();
      float x[nRuns];
      float ex[nRuns];
      float y[nRuns];
      float ey[nRuns];
      // low gain
      for(int ir=0; ir<nRuns; ir++)
	{
	  x[ir] = myRuns[itype][ir];
	  ex[ir] = 0.5;
	  y[ir] = myLGs[itype][ir];
	  ey[ir]= myLGErrs[itype][ir];
	}
      graph_lg[itype] = new TGraphErrors(nRuns,x,y,ex,ey);
      graph_lg[itype]->SetName(Form("gr_Mean_%d",itype));
      graph_lg[itype]->SetMarkerStyle(MARKERS[itype]);
      graph_lg[itype]->SetMarkerColor(COLORS[itype]);
      graph_lg[itype]->SetLineColor(COLORS[itype]);
      graph_lg[itype]->SetMarkerSize(1.2);
      
      mg->Add(graph_lg[itype]);

      // high gain
      for(int ir=0; ir<nRuns; ir++)
	{
	  x[ir] = myRuns[itype][ir];
	  ex[ir] = 0.5;
	  y[ir] = myHGs[itype][ir];
	  ey[ir]= myHGErrs[itype][ir];
	}
      graph_hg[itype] = new TGraphErrors(nRuns,x,y,ex,ey);
      graph_hg[itype]->SetName(Form("hg_gr_Mean_%d",itype));
      graph_hg[itype]->SetMarkerStyle(MARKERS[itype]);
      graph_hg[itype]->SetMarkerColor(COLORS[itype]);
      graph_hg[itype]->SetLineColor(COLORS[itype]);
      graph_hg[itype]->SetMarkerSize(1.2);
      
      mg_h->Add(graph_hg[itype]);

    }

  TCanvas* c1 = new TCanvas("c1");

  // low gain
  mg->Draw("AP");
  mg->GetXaxis()->SetTitle("");
  mg->GetYaxis()->SetRangeUser(150,250);
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetTitle("cutoff of Low-Gain ADC counts");

  
  TLegend* leg = new TLegend(0.148,0.634,0.397,0.877);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->SetBorderSize(0);

  for(int itype=0; itype<5; itype++)
    {
      if(myRuns[itype].size()==0)continue;      
      leg->AddEntry(Form("gr_Mean_%d",itype), Form("Cell type %d",itype),"p");  
    }

  leg->Draw("same");
  string outputFile="figures/LG_energyDependence";
  string final = outputFile + ".pdf";

  c1->Print(final.data());
  final = outputFile + ".gif";
  c1->Print(final.data());

  // high gain
  mg_h->Draw("AP");
  mg_h->GetXaxis()->SetTitle("");
  mg_h->GetYaxis()->SetRangeUser(1500,2500);
  mg_h->GetYaxis()->SetTitleOffset(1.4);
  mg_h->GetYaxis()->SetTitle("cutoff of High-Gain ADC counts");
  
  leg->Clear();

  for(int itype=0; itype<5; itype++)
    {
      if(myRuns[itype].size()==0)continue;      
      leg->AddEntry(Form("hg_gr_Mean_%d",itype), Form("Cell type %d",itype),"p");  
    }

  leg->Draw("same");

  outputFile="figures/HG_energyDependence";
  final = outputFile + ".pdf";

  c1->Print(final.data());
  final = outputFile + ".gif";
  c1->Print(final.data());




}
