//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov  5 15:47:41 2018 by ROOT version 6.14/04
// from TTree pccminitree/pcc vdm scan data
// found on file: merged_ZBAll_superscans.root
//////////////////////////////////////////////////////////

#ifndef lumAnalyze_h
#define lumAnalyze_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.

class lumAnalyze {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           LS;
   UInt_t          event;
   UInt_t          timeStamp;
   Int_t           BXid;
   Double_t        nCluster;
   Double_t        nClusterPerLayer[5];
   Double_t        nVtx;
   Double_t        nPU;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_LS;   //!
   TBranch        *b_event;   //!
   TBranch        *b_timeStamp;   //!
   TBranch        *b_BXid;   //!
   TBranch        *b_nCluster;   //!
   TBranch        *b_nClusterPerLayer;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_nPU;   //!

    long long* timeStampValue;
    double* nClusterValue;
    int* BXidValue;

   lumAnalyze(TTree *tree=0);
   virtual ~lumAnalyze();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

    double nClusterAverage(TString s, TString axeX, TString axeY, TString nature, int n, int nbin, TString log, long long minRes, long long maxRes);
    double nClusterAverageBX(TString s, TString axeX, TString axeY, TString nature, int n, int nbin, TString log, long long minRes, long long maxRes, int nBX);
    double nClusterAverageTot(TString s, TString axeX, TString axeY, TString nature, int n, int nbin, TString log, long long min1, long long max1, long long min2, long long max2);

    void histoClustBX(TString s, TString axeX, TString axeY, int n, double** nCluAv, double** nCluStd);
    TH1F* timeHisto(TString s, TString axeX, TString axeY, int div, int n, long long minRes, long long maxRes);
    void timeHistoBX(TString s, TString axeX, TString axeY, int div, int n, long long minRes, long long maxRes, int* nBX);
    void mixHisto(TString s, TH1F* h1, TH1F* h2);

    void intHisto(TString s, TString axeX, TString axeY, int n, int min, int max, int nbin, int* values, TString log, TString res, long long minRes, long long maxRes);

    double maxLum(int n);

};

#endif

#ifdef lumAnalyze_cxx
lumAnalyze::lumAnalyze(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data/merged_ZBAll_superscans.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("data/merged_ZBAll_superscans.root");
      }
      f->GetObject("pccminitree",tree);

   }
   Init(tree);
}

lumAnalyze::~lumAnalyze()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t lumAnalyze::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t lumAnalyze::LoadTree(Long64_t entry)
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

void lumAnalyze::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("LS", &LS, &b_LS);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("timeStamp", &timeStamp, &b_timeStamp);
   fChain->SetBranchAddress("BXid", &BXid, &b_BXid);
   fChain->SetBranchAddress("nCluster", &nCluster, &b_nCluster);
   fChain->SetBranchAddress("nClusterPerLayer", nClusterPerLayer, &b_nClusterPerLayer);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("nPU", &nPU, &b_nPU);
   Notify();
}

Bool_t lumAnalyze::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void lumAnalyze::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t lumAnalyze::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef lumAnalyze_cxx
