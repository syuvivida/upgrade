#include <fstream>
#include <iostream>
#include <TH2.h>
#include <TF1.h>
#include <string>
#include <TFitResult.h>
#include <TMatrixD.h>
#include <TFile.h>
#include <TSystem.h>

using namespace std;


void cutoff(double* locutoff, double* hicutoff, const TFitResult& low, const TFitResult& hi);

void cutoff(double* locutoff, double* hicutoff, const TFitResult& low, const TFitResult& hi)
{
  double a=low.GetParams()[0];
  double b=low.GetParams()[1];

  TMatrixD cov_lo= low.GetCovarianceMatrix();
  double aerr2 = cov_lo[0][0];
  double aberr = cov_lo[0][1];
  double berr2 = cov_lo[1][1];

  double c=hi.GetParams()[0];
  double d=hi.GetParams()[1];

  TMatrixD cov_hi= hi.GetCovarianceMatrix();
  double cerr2 = cov_hi[0][0];
  double cderr = cov_hi[0][1];
  double derr2 = cov_hi[1][1];

  //  cout << aerr2 << " " << aberr << " " << berr2 << endl;
  //  cout << cerr2 << " " << cderr << " " << derr2 << endl;


  if(fabs(a-c)<1e-6)
    {
      locutoff[0]=-999;
      locutoff[1]=-999;
      hicutoff[0]=-999;
      hicutoff[1]=-999;
      return;
    }
  else{
    locutoff[0]= (d-b)/(a-c);
    
    double deriv_c =  (d-b)/(a-c)/(a-c);
    double deriv_a = -deriv_c;
    double deriv_d =  1./(a-c);
    double deriv_b = -deriv_d;

    double err2 = pow(deriv_a,2)*aerr2 + pow(deriv_b,2)*berr2+ 2*deriv_a*deriv_b*aberr +
      pow(deriv_c,2)*cerr2 + pow(deriv_d,2)*derr2 + 2*deriv_c*deriv_d*cderr;

    locutoff[1]= sqrt(err2);

    hicutoff[0]= (a*d-b*c)/(a-c);
    deriv_a = -c*(d-b)/(a-c)/(a-c);
    deriv_b = -c/(a-c);
    deriv_c = a*(d-b)/(a-c)/(a-c);
    deriv_d = a/(a-c);

    err2 = pow(deriv_a,2)*aerr2 + pow(deriv_b,2)*berr2+ 2*deriv_a*deriv_b*aberr +
      pow(deriv_c,2)*cerr2 + pow(deriv_d,2)*derr2 + 2*deriv_c*deriv_d*cderr;


    hicutoff[1]= sqrt(err2);


    return;
  }
}


void computeSaturation(string inputFile, string histoPrefix="HighGain_LowGain_2D_type")
{
  bool hasType=false;
  if(histoPrefix.find("type"))hasType=true;
  const int NTYPES= hasType? 5:1;

  TH2F* h2D[NTYPES];
  TFile *f1 = TFile::Open(inputFile.data());

  TF1* flo = new TF1("flo","[0]*x+[1]");
  TF1* fhi = new TF1("fhi","[0]*x+[1]");
  TString prefix=gSystem->GetFromPipe(Form("file=%s; test=${file##*/}; test2=${test%%_HGC*}; echo \"${test2}\"",inputFile.data()));

  TString runNumber=gSystem->GetFromPipe(Form("file=%s; test=${file##*_}; test2=${test%%.root*}; echo \"${test2}\"",inputFile.data()));

  ofstream fout;
  fout.open(Form("%s_%s.dat",prefix.Data(),histoPrefix.data()),ios::out | ios::app);

  for(int it=0; it< NTYPES; it++)
    {  
      if(it==2 || it==3)continue;
      h2D[it] = (TH2F*)(f1->FindObjectAny(Form("%s%d",histoPrefix.data(),it)));
      h2D[it] ->SetName(Form("h2D%d",it));
      double par[4];
      double parerr[4];
      TFitResultPtr fitptr_lo=h2D[it] ->Fit("flo","S","",0,150); 
      TFitResult fitresult_lo = (*fitptr_lo);

      TFitResultPtr fitptr_hi=h2D[it] ->Fit("fhi","S","",250,400); 
      TFitResult fitresult_hi = (*fitptr_hi);
      double LG_cutoff[2], HG_cutoff[2];
      cutoff(LG_cutoff, HG_cutoff,fitresult_lo, fitresult_hi);
      cout << "LG cut off = " << LG_cutoff[0] << " +- " << LG_cutoff[1] << endl;
      cout << "HG cut off = " << HG_cutoff[0] << " +- " << HG_cutoff[1] << endl;

      fout << runNumber << " " << it << " " << LG_cutoff[0] << " " << LG_cutoff[1] << " " << HG_cutoff[0] << " " << HG_cutoff[1] << endl;

    } // loop over number of cell types
  fout.close();
}
