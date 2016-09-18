#include <TGraphErrors.h>
#include <fstream>
#include <iostream>
#include <string>
#include <TCanvas.h>
#include <TSystem.h>
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


void plotSlope_EnergyDependence(std::string histoName="HighGain_LowGain_2D_lct")
{
  const int NFILES=5;
  string LabelNames[NFILES]={"e 70GeV",
			"e 100GeV",
			"e 150GeV",
			"e 250GeV",
			"pi 125 GeV"};
  string inputNames[NFILES]={
    "electron70GeV",
    "electron100GeV",
    "electron150GeV",
    "electron250GeV",
    "pion125GeV"
  };

  const int NTYPES=6; // changed to 64 for channel dependences                                                                                                                   
  const int NLAYERS=8;
  const int NCHIPS=2;


  std::vector<double> myLGs[NLAYERS][NCHIPS][NTYPES];
  std::vector<double> myLGErrs[NLAYERS][NCHIPS][NTYPES];
  std::vector<double> myHGs[NLAYERS][NCHIPS][NTYPES];
  std::vector<double> myHGErrs[NLAYERS][NCHIPS][NTYPES];
  std::vector<int> myRuns[NLAYERS][NCHIPS][NTYPES];
  
  std::map<int,RunInfo> myRunInfos[NLAYERS][NCHIPS][NTYPES];

  for(int i=0;i<NFILES;i++){
    ifstream fin;
    fin.open(Form("output_data/slope_profile_%s_%s.dat",inputNames[i].data(),histoName.data()));
    while(!fin.eof())
      {
	string run;
 	int layer;
	int skiroc;
	int type;
	double lg, lgerr;
	fin >> run >> layer >> skiroc >> type >> lg >> lgerr;
	cout << run << endl;
	if(!fin.eof() && run=="all"){
	  RunInfo temp;
	  temp.slope_central= lg;
	  temp.slope_error  = lgerr;
	  myRunInfos[layer-1][skiroc-1][type].insert(pair<int, RunInfo>(i, temp));
	}
	
      }
  } // end loop over files

  int MARKERS[NTYPES]={20,21,22,23,24,28};
  int COLORS[NTYPES]={1,4,2,1,kGreen+1,kOrange};

  gSystem->mkdir("figures");
  for(int il=0; il < NLAYERS; il++){
    for(int ic=0; ic < NCHIPS; ic++){

      TGraphErrors* graph_lg[NTYPES];
      TGraphErrors* graph_hg[NTYPES];
      
      TMultiGraph *mg = new TMultiGraph();
      TMultiGraph *mg_h = new TMultiGraph();


      const int nRuns = myRunInfos[il][ic][0].size();

  // low gain
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
      mg->GetXaxis()->SetTitle("");
      mg->GetYaxis()->SetRangeUser(mg_ymin,mg_ymax);
      mg->GetYaxis()->SetTitleOffset(1.4);
      mg->GetYaxis()->SetTitle("Slope of High-Gain vs Low-Gain ADC counts");
      
  
      TLegend* leg = new TLegend(0.148,0.634,0.397,0.877);
      leg->SetFillColor(0);
      leg->SetFillStyle(0);
      leg->SetTextSize(0.05);
      leg->SetBorderSize(0);
      leg->SetHeader(Form("Layer %d, skiroc %d",il+1,ic+1));
      
      for(int itype=0; itype<NTYPES; itype++)
	{
	  if(myRunInfos[il][ic][itype].size()==0)continue;
	  leg->AddEntry(Form("gr_Mean_%d",itype), Form("Cell type %d",itype),"p");  
	}

      leg->Draw("same");
      string temp = Form("layer%d_skiroc%d",il+1,ic+1);
      string outputFile = "figures/slope_" + temp + "_energyDependence";
      string final = outputFile + ".pdf";

      c1->Print(final.data());
      final = outputFile + ".gif";
      c1->Print(final.data());

    } // end of loop over chips
  } // end of loop of layers

}
