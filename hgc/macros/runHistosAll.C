#include <string>
#include <fstream>
#include <TROOT.h>
#include "computeSaturation.C"
using namespace std;

void runHistosAll(string particle,string energy, bool profile=false)
{
  string textFileName = profile? "profile_"+particle+energy+"_HighGain_LowGain_2D_type.dat":
    particle+energy+"_HighGain_LowGain_2D_type.dat";
  
  gSystem->Exec(Form("rm -rf %s",textFileName.data()));
  
  string inputDir="rootfiles/"+particle+"/"+energy;
  gSystem->Exec("rm -rf inputrootfiles.dat");
  string name = "ls -1 "+inputDir+"/*root > inputrootfiles.dat";
  gSystem->Exec(name.data());

  ifstream fin;
  fin.open("inputrootfiles.dat");

  gROOT->ProcessLine(".L computeSaturation.C++");

  while(!fin.eof())
    {
      string fileName;
      fin >> fileName;
      if(!fin.eof())
	computeSaturation(fileName,profile);
    }


}

