#include <TGraphErrors.h>
#include <TSystem.h>
#include <fstream>
#include <iostream>
#include <string>
#include <TLegend.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <map>

using namespace std;

struct RunInfo
{
  double slope_central;
  double slope_error;
};

void plotSlope_RunDependence(string inputTextFile)
{

  const int NTYPES=6; // changed to 64 for channel dependences
  const int NLAYERS=8;
  const int NCHIPS=2;


  ifstream fin;
  fin.open(inputTextFile.data());

  std::map<int,RunInfo> myRunInfos[NLAYERS][NCHIPS][NTYPES];

  TString prefix;
  if(inputTextFile.find("over")!=std::string::npos)
    prefix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; test2=${test%%_over*}; echo \"${test2}\"",inputTextFile.data()));
  else
    prefix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; test2=${test%%_High*}; echo \"${test2}\"",inputTextFile.data()));


  while(!fin.eof())
    {
      string run;
      int layer;
      int skiroc;
      int type;
      double lg, lgerr;
      fin >> run >> layer >> skiroc >> type >> lg >> lgerr;

      if(!fin.eof() && run!="all"){

	RunInfo temp;
	int runNumber = atoi(run.c_str());
	temp.slope_central= lg;
	temp.slope_error  = lgerr;

	myRunInfos[layer-1][skiroc-1][type].insert(pair<int, RunInfo>(runNumber, temp));
      }

    }

  int MARKERS[NTYPES]={20,21,22,23,24,28};
  int COLORS[NTYPES]={1,4,2,1,kGreen+1,kOrange};

  gSystem->mkdir("figures");
  for(int il=0; il < NLAYERS; il++){
    for(int ic=0; ic < NCHIPS; ic++){

      TGraphErrors* graph_lg[NTYPES];
      
      TMultiGraph *mg = new TMultiGraph();


      const int nRuns = myRunInfos[il][ic][0].size();

  // slope
      for(int itype=0; itype<NTYPES; itype++)
	{

	  const int nRunsThis = myRunInfos[il][ic][itype].size();
	  if(nRunsThis==0)continue;
	  float x[nRuns];
	  float ex[nRuns];
	  float y[nRuns];
	  float ey[nRuns];

	  typedef std::map<int,RunInfo>::iterator it_type;
	  int ir=0;
	  for(it_type iterator = myRunInfos[il][ic][0].begin(); iterator != myRunInfos[il][ic][0].end(); iterator++){

	    x[ir] = iterator->first;	       
	    ex[ir] = 0.5;
	    it_type iter = myRunInfos[il][ic][itype].find(x[ir]);
	    if(iter != myRunInfos[il][ic][itype].end()){
	      y[ir] = iter->second.slope_central;
	      ey[ir]= iter->second.slope_error;
	    }
	    else{
	      y[ir] = -1;
	      ey[ir]= 0.001;
	    }
	    ir++;
	  }
	  graph_lg[itype] = new TGraphErrors(nRuns,x,y,ex,ey);
	  graph_lg[itype]->SetName(Form("gr_Mean_%d",itype));
	  graph_lg[itype]->SetMarkerStyle(MARKERS[itype]);
	  graph_lg[itype]->SetMarkerColor(COLORS[itype]);
	  graph_lg[itype]->SetLineColor(COLORS[itype]);
	  graph_lg[itype]->SetMarkerSize(1.2);
      
	  mg->Add(graph_lg[itype]);


	} // end of loop over types

      if(nRuns==0)continue; 
      TCanvas* c1 = new TCanvas("c1");

      // low gain tgraphs
      const float mg_ymin = 8;
      const float mg_ymax = 12;
      mg->Draw("AP");
      mg->GetXaxis()->SetTitle("Run number");
      mg->GetYaxis()->SetRangeUser(mg_ymin,mg_ymax);
      mg->GetYaxis()->SetTitleOffset(1.4);
      mg->GetYaxis()->SetTitle("Slope of High-Gain vs Low-Gain ADC counts");

  
      TLegend* leg = new TLegend(0.148,0.634,0.397,0.877);
      leg->SetFillColor(0);
      leg->SetFillStyle(0);
      leg->SetTextSize(0.05);
      leg->SetBorderSize(0);
      
      TString legprefix = prefix + " ( " + Form("Layer %d, skiroc %d",il+1,ic+1) + " )";
      leg->SetHeader(legprefix.Data());
      for(int itype=0; itype<NTYPES; itype++)
	{
	  if(myRunInfos[il][ic][itype].size()==0)continue;
	  leg->AddEntry(Form("gr_Mean_%d",itype), Form("Cell type %d",itype),"p");  
	}

      leg->Draw("same");
      string temp = prefix.Data();
      string temp2 = Form("layer%d_skiroc%d",il+1,ic+1);
      string outputFile="figures/slope_" + temp + "_" + temp2 + "_runDependence";
      string final = outputFile + ".pdf";

      c1->Print(final.data());
      final = outputFile + ".gif";
      c1->Print(final.data());

    } // end of loop over chips
  } // end of loop of layers





}
