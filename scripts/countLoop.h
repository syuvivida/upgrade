//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 11 18:14:43 2014 by ROOT version 5.34/07
// from TTree tree/tree
// found on file: output_gen.root
//////////////////////////////////////////////////////////

#ifndef countLoop_h
#define countLoop_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <string>

// Fixed size dimensions of array or collections stored in the TTree if any.

class countLoop {
public :
  std::string outputfile_;
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   
   Float_t Rentry;
   Float_t Rexit;
   // Declaration of leaf types
   Float_t         ptHat;
   Float_t         mcWeight;
   Int_t           nGenPar;
   vector<float>   *genParE;
   vector<float>   *genParPt;
   vector<float>   *genParEta;
   vector<float>   *genParPhi;
   vector<float>   *genParM;
   vector<int>     *genParQ;
   vector<int>     *genParId;
   vector<int>     *genParSt;
   vector<int>     *genMomParId;
   vector<int>     *genParIndex;
   vector<int>     *genNMo;
   vector<int>     *genNDa;
   vector<int>     *genMo1;
   vector<int>     *genMo2;
   vector<int>     *genDa1;
   vector<int>     *genDa2;
   Int_t           nGenJet;
   vector<float>   *genJetE;
   vector<float>   *genJetPt;
   vector<float>   *genJetEta;
   vector<float>   *genJetPhi;
   Int_t           nSimHits;
   vector<float>   *hitLocalX;
   vector<float>   *hitLocalY;
   vector<float>   *hitLocalZ;
   vector<float>   *hitLocalDirectionX;
   vector<float>   *hitLocalDirectionY;
   vector<float>   *hitLocalDirectionZ;
   vector<float>   *hitGlobalX;
   vector<float>   *hitGlobalY;
   vector<float>   *hitGlobalZ;
   vector<float>   *hitGlobalR;
   vector<float>   *hitGlobalPhi;
   vector<float>   *hitGlobalEta;
   vector<float>   *hitGlobalDirectionX;
   vector<float>   *hitGlobalDirectionY;
   vector<float>   *hitGlobalDirectionZ;
   vector<float>   *hitEntryPointX;
   vector<float>   *hitEntryPointY;
   vector<float>   *hitEntryPointZ;
   vector<float>   *hitExitPointX;
   vector<float>   *hitExitPointY;
   vector<float>   *hitExitPointZ;

   vector<float>   *hitTof;
   vector<float>   *hitEloss;
   vector<int>     *hitPID;
   vector<int>     *hitSubDec;
   vector<int>     *hitLayer;
   vector<int>     *hitLadder;
   vector<int>     *hitSide;
   vector<int>     *hitDisk;
   vector<int>     *hitBlade;
   vector<int>     *hitPanel;
   vector<int>     *hitModule;

   // List of branches
   TBranch        *b_ptHat;   //!
   TBranch        *b_mcWeight;   //!
   TBranch        *b_nGenPar;   //!
   TBranch        *b_genParE;   //!
   TBranch        *b_genParPt;   //!
   TBranch        *b_genParEta;   //!
   TBranch        *b_genParPhi;   //!
   TBranch        *b_genParM;   //!
   TBranch        *b_genParQ;   //!
   TBranch        *b_genParId;   //!
   TBranch        *b_genParSt;   //!
   TBranch        *b_genMomParId;   //!
   TBranch        *b_genParIndex;   //!
   TBranch        *b_genNMo;   //!
   TBranch        *b_genNDa;   //!
   TBranch        *b_genMo1;   //!
   TBranch        *b_genMo2;   //!
   TBranch        *b_genDa1;   //!
   TBranch        *b_genDa2;   //!
   TBranch        *b_nGenJet;   //!
   TBranch        *b_genJetE;   //!
   TBranch        *b_genJetPt;   //!
   TBranch        *b_genJetEta;   //!
   TBranch        *b_genJetPhi;   //!
   TBranch        *b_nSimHits;   //!
   TBranch        *b_hitLocalX;   //!
   TBranch        *b_hitLocalY;   //!
   TBranch        *b_hitLocalZ;   //!
   TBranch        *b_hitLocalDirectionX;   //!
   TBranch        *b_hitLocalDirectionY;   //!
   TBranch        *b_hitLocalDirectionZ;   //!
   TBranch        *b_hitGlobalX;   //!
   TBranch        *b_hitGlobalY;   //!
   TBranch        *b_hitGlobalZ;   //!
   TBranch        *b_hitGlobalR;   //!
   TBranch        *b_hitGlobalPhi;   //!
   TBranch        *b_hitGlobalEta;   //!
   TBranch        *b_hitGlobalDirectionX;   //!
   TBranch        *b_hitGlobalDirectionY;   //!
   TBranch        *b_hitGlobalDirectionZ;   //!
   TBranch        *b_hitEntryPointX;   //!         
   TBranch        *b_hitEntryPointY;   //!         
   TBranch        *b_hitEntryPointZ;   //!         
   TBranch        *b_hitExitPointX;   //!          
   TBranch        *b_hitExitPointY;   //!          
   TBranch        *b_hitExitPointZ;   //!          

   TBranch        *b_hitTof;   //!
   TBranch        *b_hitEloss;   //!
   TBranch        *b_hitPID;   //!
   TBranch        *b_hitSubDec;   //!
   TBranch        *b_hitLayer;   //!
   TBranch        *b_hitLadder;   //!
   TBranch        *b_hitSide;   //!
   TBranch        *b_hitDisk;   //!
   TBranch        *b_hitBlade;   //!
   TBranch        *b_hitPanel;   //!
   TBranch        *b_hitModule;   //!

   countLoop(std::string inputfile, std::string outputfile, TTree *tree=0);
   virtual ~countLoop();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   double Rho(double x, double y);
};

#endif

#ifdef countLoop_cxx
countLoop::countLoop(std::string inputfile, std::string outputfile, TTree *tree) : fChain(0) 
{
  outputfile_ = outputfile;
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(inputfile.data());
     if (!f || !f->IsOpen()) {
       f = new TFile(inputfile.data());
     }
     TDirectory * dir = (TDirectory*)f->Get(Form("%s:/tree",inputfile.data()));
     dir->GetObject("tree",tree);
     
   }
   Init(tree);
}

countLoop::~countLoop()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t countLoop::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t countLoop::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void countLoop::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   genParE = 0;
   genParPt = 0;
   genParEta = 0;
   genParPhi = 0;
   genParM = 0;
   genParQ = 0;
   genParId = 0;
   genParSt = 0;
   genMomParId = 0;
   genParIndex = 0;
   genNMo = 0;
   genNDa = 0;
   genMo1 = 0;
   genMo2 = 0;
   genDa1 = 0;
   genDa2 = 0;
   genJetE = 0;
   genJetPt = 0;
   genJetEta = 0;
   genJetPhi = 0;
   hitLocalX = 0;
   hitLocalY = 0;
   hitLocalZ = 0;
   hitLocalDirectionX = 0;
   hitLocalDirectionY = 0;
   hitLocalDirectionZ = 0;
   hitGlobalX = 0;
   hitGlobalY = 0;
   hitGlobalZ = 0;
   hitGlobalR = 0;
   hitGlobalPhi = 0;
   hitGlobalEta = 0;
   hitGlobalDirectionX = 0;
   hitGlobalDirectionY = 0;
   hitGlobalDirectionZ = 0;
   hitEntryPointX = 0;
   hitEntryPointY = 0;
   hitEntryPointZ = 0;
   hitExitPointX = 0;
   hitExitPointY = 0;
   hitExitPointZ = 0;

   hitTof = 0;
   hitEloss = 0;
   hitPID = 0;
   hitSubDec = 0;
   hitLayer = 0;
   hitLadder = 0;
   hitSide = 0;
   hitDisk = 0;
   hitBlade = 0;
   hitPanel = 0;
   hitModule = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ptHat", &ptHat, &b_ptHat);
   fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
   fChain->SetBranchAddress("nGenPar", &nGenPar, &b_nGenPar);
   fChain->SetBranchAddress("genParE", &genParE, &b_genParE);
   fChain->SetBranchAddress("genParPt", &genParPt, &b_genParPt);
   fChain->SetBranchAddress("genParEta", &genParEta, &b_genParEta);
   fChain->SetBranchAddress("genParPhi", &genParPhi, &b_genParPhi);
   fChain->SetBranchAddress("genParM", &genParM, &b_genParM);
   fChain->SetBranchAddress("genParQ", &genParQ, &b_genParQ);
   fChain->SetBranchAddress("genParId", &genParId, &b_genParId);
   fChain->SetBranchAddress("genParSt", &genParSt, &b_genParSt);
   fChain->SetBranchAddress("genMomParId", &genMomParId, &b_genMomParId);
   fChain->SetBranchAddress("genParIndex", &genParIndex, &b_genParIndex);
   fChain->SetBranchAddress("genNMo", &genNMo, &b_genNMo);
   fChain->SetBranchAddress("genNDa", &genNDa, &b_genNDa);
   fChain->SetBranchAddress("genMo1", &genMo1, &b_genMo1);
   fChain->SetBranchAddress("genMo2", &genMo2, &b_genMo2);
   fChain->SetBranchAddress("genDa1", &genDa1, &b_genDa1);
   fChain->SetBranchAddress("genDa2", &genDa2, &b_genDa2);
   fChain->SetBranchAddress("nGenJet", &nGenJet, &b_nGenJet);
   fChain->SetBranchAddress("genJetE", &genJetE, &b_genJetE);
   fChain->SetBranchAddress("genJetPt", &genJetPt, &b_genJetPt);
   fChain->SetBranchAddress("genJetEta", &genJetEta, &b_genJetEta);
   fChain->SetBranchAddress("genJetPhi", &genJetPhi, &b_genJetPhi);
   fChain->SetBranchAddress("nSimHits", &nSimHits, &b_nSimHits);
   fChain->SetBranchAddress("hitLocalX", &hitLocalX, &b_hitLocalX);
   fChain->SetBranchAddress("hitLocalY", &hitLocalY, &b_hitLocalY);
   fChain->SetBranchAddress("hitLocalZ", &hitLocalZ, &b_hitLocalZ);
   fChain->SetBranchAddress("hitLocalDirectionX", &hitLocalDirectionX, &b_hitLocalDirectionX);
   fChain->SetBranchAddress("hitLocalDirectionY", &hitLocalDirectionY, &b_hitLocalDirectionY);
   fChain->SetBranchAddress("hitLocalDirectionZ", &hitLocalDirectionZ, &b_hitLocalDirectionZ);
   fChain->SetBranchAddress("hitGlobalX", &hitGlobalX, &b_hitGlobalX);
   fChain->SetBranchAddress("hitGlobalY", &hitGlobalY, &b_hitGlobalY);
   fChain->SetBranchAddress("hitGlobalZ", &hitGlobalZ, &b_hitGlobalZ);
   fChain->SetBranchAddress("hitGlobalR", &hitGlobalR, &b_hitGlobalR);
   fChain->SetBranchAddress("hitGlobalPhi", &hitGlobalPhi, &b_hitGlobalPhi);
   fChain->SetBranchAddress("hitGlobalEta", &hitGlobalEta, &b_hitGlobalEta);
   fChain->SetBranchAddress("hitGlobalDirectionX", &hitGlobalDirectionX, &b_hitGlobalDirectionX);
   fChain->SetBranchAddress("hitGlobalDirectionY", &hitGlobalDirectionY, &b_hitGlobalDirectionY);
   fChain->SetBranchAddress("hitGlobalDirectionZ", &hitGlobalDirectionZ, &b_hitGlobalDirectionZ);
   fChain->SetBranchAddress("hitEntryPointX", &hitEntryPointX, &b_hitEntryPointX);
   fChain->SetBranchAddress("hitEntryPointY", &hitEntryPointY, &b_hitEntryPointY);
   fChain->SetBranchAddress("hitEntryPointZ", &hitEntryPointZ, &b_hitEntryPointZ);
   fChain->SetBranchAddress("hitExitPointX", &hitExitPointX, &b_hitExitPointX);
   fChain->SetBranchAddress("hitExitPointY", &hitExitPointY, &b_hitExitPointY);
   fChain->SetBranchAddress("hitExitPointZ", &hitExitPointZ, &b_hitExitPointZ);

   fChain->SetBranchAddress("hitTof", &hitTof, &b_hitTof);
   fChain->SetBranchAddress("hitEloss", &hitEloss, &b_hitEloss);
   fChain->SetBranchAddress("hitPID", &hitPID, &b_hitPID);
   fChain->SetBranchAddress("hitSubDec", &hitSubDec, &b_hitSubDec);
   fChain->SetBranchAddress("hitLayer", &hitLayer, &b_hitLayer);
   fChain->SetBranchAddress("hitLadder", &hitLadder, &b_hitLadder);
   fChain->SetBranchAddress("hitSide", &hitSide, &b_hitSide);
   fChain->SetBranchAddress("hitDisk", &hitDisk, &b_hitDisk);
   fChain->SetBranchAddress("hitBlade", &hitBlade, &b_hitBlade);
   fChain->SetBranchAddress("hitPanel", &hitPanel, &b_hitPanel);
   fChain->SetBranchAddress("hitModule", &hitModule, &b_hitModule);
   Notify();
}

Bool_t countLoop::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void countLoop::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t countLoop::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef countLoop_cxx
