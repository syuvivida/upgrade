#include <TGraphErrors.h>
#include <fstream>
#include <iostream>
#include <string>
#include <TCanvas.h>

using namespace std;


void plotSlope_EnergyDependence(std::string histoName="HighGain_LowGain_2D_type")
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
  std::vector<int> myRuns[5];
  
 
  for(int i=0;i<NFILES;i++){
    ifstream fin;
    fin.open(Form("output_data/slope_%s_%s.dat",inputNames[i].data(),histoName.data()));
    while(!fin.eof())
      {
	string run;
	int type;
	double lg, lgerr;
	fin >> run >> type >> lg >> lgerr;
	cout << run << endl;
      if(!fin.eof() && run=="all"){
	myRuns[type].push_back(i);
	myLGs[type].push_back(lg);
	myLGErrs[type].push_back(lgerr);
      }
      
    }
  }

  TGraphErrors* graph_lg[5];


  TMultiGraph *mg = new TMultiGraph();
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

    }

  TCanvas* c1 = new TCanvas("c1");

  // low gain
  mg->Draw("AP");
  mg->GetXaxis()->SetTitle("");
  mg->GetYaxis()->SetRangeUser(8,12);
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetTitle("Slope of High-Gain vs. Low-Gain ADC counts");

  
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
  string outputFile="figures/slope_energyDependence";
  string final = outputFile + ".pdf";

  c1->Print(final.data());
  final = outputFile + ".gif";
  c1->Print(final.data());



}
