#include <string>
#include <fstream>
#include <TROOT.h>
#include "computeSaturation.C"

using namespace std;

void runHistosAll(string particle,string energy)
{
  string textFileName = particle+energy+"_HighGain_LowGain_2D_type.dat";
  
  gSystem->Exec(Form("rm -rf %s",textFileName.data()));
  gSystem->Exec(Form("rm -rf slope_%s",textFileName.data()));

  gSystem->Exec(Form("rm -rf profile_%s",textFileName.data()));
  gSystem->Exec(Form("rm -rf slope_profile_%s",textFileName.data()));
  

  textFileName = particle+energy+"_HighGain_LowGain_2D_commonmode_subtracted_type.dat";

  gSystem->Exec(Form("rm -rf %s",textFileName.data()));
  gSystem->Exec(Form("rm -rf slope_%s",textFileName.data()));

  gSystem->Exec(Form("rm -rf profile_%s",textFileName.data()));
  gSystem->Exec(Form("rm -rf slope_profile_%s",textFileName.data()));


  string inputDir="rootfiles/"+particle+"/"+energy;
  gSystem->Exec("rm -rf inputrootfiles.dat");
  string name = "ls -1 "+inputDir+"/*root > inputrootfiles.dat";
  gSystem->Exec(name.data());

  ifstream fin;
  fin.open("inputrootfiles.dat");

  while(!fin.eof())
    {
      string fileName;
      fin >> fileName;
      if(!fin.eof())
	{
	  // default histograms with only pedestal subtraction
	  computeSaturation(fileName,false);
	  computeSaturation(fileName,true);
	  // add histograms that subtract common mode noise
	  computeSaturation(fileName,false,"HighGain_LowGain_2D_commonmode_subtracted_type");
	  computeSaturation(fileName,true,"HighGain_LowGain_2D_commonmode_subtracted_type");

	}
    }


}

