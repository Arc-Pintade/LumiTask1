#define lumAnalyze_cxx
#include "../include/lumAnalyze.hpp"
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>

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

//_____________________________________________ Histos _______________________________________//

double lumAnalyze::nClusterAverage(TString s, TString nature, int n, int nbin, TString log, long long minRes, long long maxRes){
    double foo;
    TString minResString = Form("%d", minRes);
    TString maxResString = Form("%d", maxRes);

    TCanvas* c = new TCanvas(s+"("+minRes+"<timeStamp<"+maxRes+")","", 200,10,800,600);
    TH1F* h = new TH1F("","", nbin, 0, 10000);
    for(int i=0; i<n; i++){
        if(timeStampValue[i] > minRes && timeStampValue[i] < maxRes)
            h->Fill(nClusterValue[i]);
    }
    h->SetTitle(s+" "+"("+minRes+"<timeStamp<"+maxRes);
    h->GetYaxis()->SetTitle(s);

    h->SetStats(0);

    h->Draw();
    h->SetLineWidth(2);        h->SetLineColor(kBlue);

    if(log=="log")
        c->SetLogy();
    c->SaveAs("results/"+s+"("+minRes+"<timeStamp<"+maxRes+")"+".png");

    if(nature == "Mean")
        foo = h->GetMean(1);
    else if(nature == "StdDev")
        foo = h->GetStdDev(1);
    else
        std::cout<<"error with nature"<<std::endl;
    return foo;
}

double lumAnalyze::nClusterAverageBX(TString s, TString nature, int n, int nbin, TString log, long long minRes, long long maxRes, int nBX){
    double foo;
    TString BXval = Form("%d", nBX);
    TString minResString = Form("%d", minRes);
    TString maxResString = Form("%d", maxRes);

    TCanvas* c = new TCanvas(s+"("+minRes+"<timeStamp<"+maxRes+")"+BXval,"", 200,10,800,600);
    TH1F* h = new TH1F("","", nbin, 0, 10000);

    for(int i=0; i<n; i++){
        if(timeStampValue[i] > minRes && timeStampValue[i] < maxRes)
            if(BXidValue[i] == nBX)
                h->Fill(nClusterValue[i]);
    }

    h->SetTitle(s+" "+"("+minRes+"<timeStamp<"+maxRes+")"+"BXid"+BXval);
    h->GetYaxis()->SetTitle(s);


    h->Draw();
    h->SetLineWidth(2);        h->SetLineColor(kBlue);

    if(log=="log")
        c->SetLogy();
    c->SaveAs("results/"+s+"("+minRes+"<timeStamp<"+maxRes+")"+"BXid"+BXval+".png");

    if(nature == "Mean")
        foo = h->GetMean(1);
    else if(nature == "StdDev")
        foo = h->GetStdDev(1);
    else
        std::cout<<"error with nature"<<std::endl;
    return foo;
}

void lumAnalyze::histoClustBX(TString s, int n, double** nCluAv, double** nCluStd){
    TCanvas* c = new TCanvas(s,"", 200,10,800,600);
    double k[2][5] = {0};
    TH1F** h = new TH1F*[2];
    h[0] = new TH1F("Restriction 1","", 5, 0, 3500);
    h[1] = new TH1F("Restriction 2","", 5, 0, 3500);

    for(int a=0; a<n; a++){
        if(timeStampValue[a] > 1530412500 && timeStampValue[a] < 1530412800)
            if(BXidValue[a] == 265)
                k[0][0]++;
            else if(BXidValue[a] == 865)
                k[0][1]++;
            else if(BXidValue[a] == 1780)
                k[0][2]++;
            else if(BXidValue[a] == 2192)
                k[0][3]++;
            else if(BXidValue[a] == 3380)
                k[0][4]++;
        if(timeStampValue[a] > 1530427080 && timeStampValue[a] < 1530427440)
            if(BXidValue[a] == 265)
                k[1][0]++;
            else if(BXidValue[a] == 865)
                k[1][1]++;
            else if(BXidValue[a] == 1780)
                k[1][2]++;
            else if(BXidValue[a] == 2192)
                k[1][3]++;
            else if(BXidValue[a] == 3380)
                k[1][4]++;
    }

    for(int i = 0; i<2; i++)
        for(int j = 0; j<5; j++){
            h[i]->SetBinContent(j+1, nCluAv[i][j]);
            h[i]->SetBinError(j+1, (nCluStd[i][j])/sqrt(k[i][j]));
        }

    h[0]->SetTitle(s);
    h[0]->SetMaximum(0.2);
    h[0]->SetMinimum(0);
    h[0]->GetYaxis()->SetTitle("Cluster Average");
    h[0]->GetXaxis()->SetTitle("BXid");
    h[0]->SetStats(0);

    h[0]->Draw();               h[1]->Draw("SAME");
    h[0]->SetLineWidth(2);      h[0]->SetLineColor(kBlue);
    h[1]->SetLineWidth(2);      h[1]->SetLineColor(kRed);

    TLegend* legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->AddEntry(h[0],"(1530412500<timeStamp<1530412800)","l");
    legend->AddEntry(h[1],"(1530427080<timeStamp<1530427440)","l");
    legend->Draw();

    c->SaveAs("results/"+s+".png");

}

void lumAnalyze::timeHisto(TString s, int div, int n, long long minRes, long long maxRes){
    TString minResString = Form("%d", minRes);
    TString maxResString = Form("%d", maxRes);
    int step = (maxRes-minRes)/((double)div);
    double moyClust[div];
    double stdClust[div];
    int nb[div] = {0};
    for(int i=0; i<div; i++){
        for(int j=0; j<n; j++){
            if((minRes+i*step) < timeStampValue[j] && timeStampValue[j] < (minRes+(i+1)*step)){
                moyClust[i] += nClusterValue[j];
                nb[i]++;
            }
        }
        moyClust[i] /= (double)nb[i];
        for(int j=0; j<n; j++){
            if((minRes+i*step) < timeStampValue[j] && timeStampValue[j] < (minRes+(i+1)*step))
                stdClust[i] += nClusterValue[j]*nClusterValue[j] - 2*nClusterValue[j]*moyClust[i] + moyClust[i]*moyClust[i];
        }
        stdClust[i] /= (double)nb[i];
        stdClust[i] = sqrt(stdClust[i]);
    }

    TCanvas* c = new TCanvas(s+"("+minRes+"<timeStamp<"+maxRes+")","", 200,10,800,600);
    TH1F* h = new TH1F("","", div, minRes, maxRes);
    for(int i=0; i<div; i++){
        h->SetBinContent(i+1, moyClust[i]);
        h->SetBinError(i+1, (stdClust[i])/(sqrt(nb[i])));
    }

    h->SetMaximum(0.3);
    h->SetMinimum(0);
    h->SetTitle(s+" "+"("+minRes+"<timeStamp<"+maxRes+")");
    h->GetYaxis()->SetTitle(s);

    h->SetStats(0);

    h->Draw();
    h->SetLineWidth(2);        h->SetLineColor(kBlue);

    c->SaveAs("results/"+s+"("+minRes+"<timeStamp<"+maxRes+")"+".png");
}

void lumAnalyze::timeHistoBX(TString s, int div, int n, long long minRes, long long maxRes, int* nBX){
    TString minResString = Form("%d", minRes);
    TString maxResString = Form("%d", maxRes);
    int step = (maxRes-minRes)/((double)div);
    double moyClust[div][5];
    double stdClust[div][5];
    int nb[div][5] = {10};
    for(int i=0; i<div; i++){
        for(int j=0; j<n; j++){
            if((minRes+i*step) < timeStampValue[j] && timeStampValue[j] < (minRes+(i+1)*step)){
                for(int o=0; o<5; o++){
                    if(BXidValue[i] == nBX[o]){
                        moyClust[i][o] += nClusterValue[j];
                        nb[i][o]++;
                    }
                }
            }
        }
        for(int o=0; o<5; o++)
            moyClust[i][o] /= (double)nb[i][o];
            for(int j=0; j<n; j++){
                if((minRes+i*step) < timeStampValue[j] && timeStampValue[j] < (minRes+(i+1)*step))
                    for(int o=0; o<5; o++){
                        if(BXidValue[i] == nBX[o]){
                            stdClust[i][o] += nClusterValue[j]*nClusterValue[j] - 2*nClusterValue[j]*moyClust[i][o] + moyClust[i][o]*moyClust[i][o];
                        }
                    }
                }
                for(int o=0; o<5; o++){
                    stdClust[i][o] /= (double)nb[i][o];
                    stdClust[i][o] = sqrt(stdClust[i][o]);
                }
    std::cout<<moyClust[i][0]<<std::endl<<moyClust[i][1]<<std::endl<<moyClust[i][2]<<std::endl;
    }

    TCanvas* c = new TCanvas(s+"("+minRes+"<timeStamp<"+maxRes+")","", 200,10,800,600);
    TH1F** h;

    h[0] = new TH1F("","", div, minRes, maxRes);
    h[1] = new TH1F("","", div, minRes, maxRes);
    h[2] = new TH1F("","", div, minRes, maxRes);
    h[3] = new TH1F("","", div, minRes, maxRes);
    h[4] = new TH1F("","", div, minRes, maxRes);

    for(int a=0; a<5; a++){
        for(int i=0; i<div; i++){
            //h[a]->SetBinContent(i+1, moyClust[i][a]);
            //h[a]->SetBinError(i+1, (stdClust[i][a])/(sqrt(nb[i][a])));
        }
    }

    h[0]->SetMaximum(0.3);
    h[0]->SetMinimum(0);
    h[0]->SetTitle(s+" "+"("+minRes+"<timeStamp<"+maxRes+")");
    h[0]->GetYaxis()->SetTitle(s);

    h[0]->SetStats(0);

    h[0]->Draw();
    for(int i=1; i<5; i++)
        h[i]->Draw("SAME");
    h[0]->SetLineWidth(2);    h[1]->SetLineWidth(2);    h[2]->SetLineWidth(2);    h[3]->SetLineWidth(2);    h[4]->SetLineWidth(2);
    h[0]->SetLineColor(kBlue);    h[1]->SetLineColor(kRed);    h[2]->SetLineColor(kMagenta);    h[3]->SetLineColor(kYellow);    h[4]->SetLineColor(kGreen);

    c->SaveAs("results/"+s+"("+minRes+"<timeStamp<"+maxRes+")"+".png");
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

