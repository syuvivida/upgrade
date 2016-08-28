#include <string>
#include <fstream>
#include <TROOT.h>
#include "computeSaturation.C"
using namespace std;

void runHistosAll(string particle,string energy)
{

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
	computeSaturation(fileName);
    }


}

