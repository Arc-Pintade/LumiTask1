#define lumAnalyze_cxx
#include "../include/lumAnalyze.hpp"
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>


void lumAnalyze::Loop()
{
//   In a ROOT session, you can do:
//      root> .L lumAnalyze.C
//      root> lumAnalyze t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

    timeStampValue      = new long long[nentries];
    nClusterValue       = new double[nentries];
    BXidValue       = new int[nentries];

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      timeStampValue[jentry] = timeStamp;
      nClusterValue[jentry] = nCluster;
      BXidValue[jentry] = BXid;
   }
}

void lumAnalyze::doubleHisto(TString s, int n, int min, int max, int nbin, double* values, TString log, TString res, long long minRes, long long maxRes){
    TCanvas* c = new TCanvas(s+res,"", 200,10,800,600);
    TH1F* h = new TH1F("","", nbin, min, max);
    for(int i=0; i<n; i++){
        if(timeStampValue[i] > minRes && timeStampValue[i] < maxRes)
            h->Fill(values[i]);
    }

    h->SetTitle(s+" "+res);
    h->GetYaxis()->SetTitle(s);

    h->SetStats(0);

    h->Draw();
    h->SetLineWidth(2);        h->SetLineColor(kBlue);

    if(log=="log")
        c->SetLogy();
    c->SaveAs("results/"+s+res+".png");

}

void lumAnalyze::intHisto(TString s, int n, int min, int max, int nbin, int* values, TString log, TString res, long long minRes, long long maxRes){
    TCanvas* c = new TCanvas(s+res,"", 200,10,800,600);
    TH1F* h = new TH1F("","", nbin, min, max);
    for(int i=0; i<n; i++){
        if(timeStampValue[i] > minRes && timeStampValue[i] < maxRes)
            h->Fill(values[i]);
    }

    h->SetTitle(s+" "+res);
    h->GetYaxis()->SetTitle(s);

    h->SetStats(0);

    h->Draw();
    h->SetLineWidth(2);        h->SetLineColor(kBlue);

    if(log=="log")
        c->SetLogy();
    c->SaveAs("results/"+s+res+".png");
}

void lumAnalyze::doubleHistoBX(TString s, int n, int min, int max, int nbin, double* values, TString log, TString res, long long minRes, long long maxRes, int nBX){
    TCanvas* c = new TCanvas(s+res,"", 200,10,800,600);
    TH1F* h = new TH1F("","", nbin, min, max);
    TString BXval = Form("%d", nBX);

    for(int i=0; i<n; i++){
        if(timeStampValue[i] > minRes && timeStampValue[i] < maxRes)
            if(BXidValue[i] == nBX)
                h->Fill(values[i]);
    }

    h->SetTitle(s+" "+res+"BXid"+BXval);
    h->GetYaxis()->SetTitle(s);

    h->SetStats(0);

    h->Draw();
    h->SetLineWidth(2);        h->SetLineColor(kBlue);

    if(log=="log")
        c->SetLogy();
    c->SaveAs("results/"+s+res+"BXid"+BXval+".png");

}

