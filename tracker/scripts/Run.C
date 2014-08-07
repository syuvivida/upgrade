#include "countLoop.h"
#include <vector>
#include <ctime>
#include <iostream>
using namespace std;
int main(int argc, char *argv[]){
  TString inputfile, outputfile;
  if(argc ==3){
    inputfile  = argv[1];
    outputfile = argv[2];
  }
  else {
    std::cout<<" provide sufficient inputs "<<std::endl;
    std::cout<<" run the code using >>>>>>>>>>>>>>>>>>>>>>>>>> "<<std::endl;
    std::cout<<" ./run.exe inputfilename.root outputfilename.root"<<std::endl;
    return -1;
  }
  time_t start, end ;
  double timeConsumed ;
  time(&start) ;
  TTree *tree=0;
  countLoop *a = new countLoop(inputfile, outputfile, tree);
  a->Loop();
  a->countLoop::~countLoop() ;
  time(&end) ;
  timeConsumed = difftime (end,start) ;
  std::cout << " time for processing job : " << timeConsumed << " seconds " << std::endl ;
  return 1;
}
