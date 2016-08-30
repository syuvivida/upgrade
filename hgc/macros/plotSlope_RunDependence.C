#include <TGraphErrors.h>
#include <fstream>
#include <iostream>
#include <string>
#include <TCanvas.h>

using namespace std;


void plotSlope_RunDependence(string inputTextFile)
{

  ifstream fin;
  fin.open(inputTextFile.data());

  std::vector<int> myRuns[5];
  std::vector<double> myLGs[5];
  std::vector<double> myLGErrs[5];


  TString prefix;
  if(inputTextFile.find("over")!=std::string::npos)
    prefix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; test2=${test%%_over*}; echo \"${test2}\"",inputTextFile.data()));
  else
    prefix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; test2=${test%%_High*}; echo \"${test2}\"",inputTextFile.data()));


  while(!fin.eof())
    {
      string run;
      int type;
      double lg, lgerr;
      fin >> run >> type >> lg >> lgerr;

      if(!fin.eof() && run!="all"){
	myRuns[type].push_back(atoi(run.c_str()));
	myLGs[type].push_back(lg);
	myLGErrs[type].push_back(lgerr);
      }

    }

  TGraphErrors* graph_lg[5];

  const int nRuns = myRuns[0].size();
  TMultiGraph *mg = new TMultiGraph();
  int MARKERS[5]={20,21,22,23,24};
  int COLORS[5]={1,4,2,1,kGreen+1};
  
  // low gain
  for(int itype=0; itype<5; itype++)
    {
      if(myRuns[itype].size()==0)continue;
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
  mg->GetXaxis()->SetTitle("Run number");
  mg->GetYaxis()->SetRangeUser(8,12);
  mg->GetYaxis()->SetTitleOffset(1.4);
  mg->GetYaxis()->SetTitle("Slope of High-Gain vs Low-Gain ADC counts");

  
  TLegend* leg = new TLegend(0.148,0.634,0.397,0.877);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->SetBorderSize(0);
  TString position;
  if(inputTextFile.find("pion")!=std::string::npos)
    position = "position2";
  else if(inputTextFile.find("overnight")!=std::string::npos)
    position = "position3";
  else if(inputTextFile.find("electron")!=std::string::npos)
    position = "position4";
  
  TString legprefix = prefix + " ( " + position + " )";
  leg->SetHeader(legprefix.Data());
  for(int itype=0; itype<5; itype++)
    {
      if(myRuns[itype].size()==0)continue;      
      leg->AddEntry(Form("gr_Mean_%d",itype), Form("Cell type %d",itype),"p");  
    }

  leg->Draw("same");
  string temp = prefix.Data();
  string outputFile="figures/slope_" + temp + "_" + position.Data() + "_runDependence";
  string final = outputFile + ".pdf";

  c1->Print(final.data());
  final = outputFile + ".gif";
  c1->Print(final.data());



}
