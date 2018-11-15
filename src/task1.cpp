#include "../include/lumAnalyze.hpp"

#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TApplication.h>
#include <TString.h>
#include <iostream>
#include <fstream>

using namespace std;

# ifndef __CINT__


int main(){

    TApplication app("app", nullptr, nullptr);

    lumAnalyze a("merged_ZBAll_superscans.root",0);
    a.Loop();

    int nBXid[5];
    long long nMinScan[2];
    long long nMaxScan[2];

    nMinScan[0]= 1530412500;            nMinScan[1] = 1530427080;
    nMaxScan[0] = 1530412800;           nMaxScan[1] = 1530427440;
    nBXid[0] = 265;
    nBXid[1] = 865;
    nBXid[2] = 1780;
    nBXid[3] = 2192;
    nBXid[4] = 3380;

    int nbin = 100;
    int nScan1 = 0;
    int nScan2 = 0;


    int nValue = a.fChain->GetEntriesFast();

// For histos (name, Number of events, Minimum of histo, Maximum of histo, Bin of histo, input, Option logY ("yes" or anything else for no), Other part of name (title), Minimum of restriction, Maximum of restriction)

    a.intHisto("BXid", "BXid", "number of events", nValue, 0, 4000, nbin, a.BXidValue, "", "(1530412500<timeStamp<1530412800)", nMinScan[0], nMaxScan[0]);
    a.intHisto("BXid", "BXid", "number of events", nValue, 0, 4000, nbin, a.BXidValue, "", "(1530427080<timeStamp<1530427440)", nMinScan[1], nMaxScan[1]);

    double** nClusterAv = new double*[2]{0};
    double** nClusterStd = new double*[2]{0};
    for (int i = 0; i<2; i++){
        nClusterAv[i] = new double[5]{0};
        nClusterStd[i] = new double[5]{0};
    }
    double* nClusterAvTot = new double[2]{0};
    double* nClusterStdTot = new double[2]{0};

    for(int i=0; i<2; i++)
        for(int j=0; j<5; j++){
            nClusterAv[i][j] = a.nClusterAverageBX("nCluster", "nCluster", "number of events", "Mean", nValue, nbin, "log", nMinScan[i], nMaxScan[i], nBXid[j]);
            nClusterStd[i][j] = a.nClusterAverageBX("nCluster", "nCluster", "number of events", "StdDev", nValue, nbin, "log", nMinScan[i], nMaxScan[i], nBXid[j]);
        }

    for(int i=0; i<2; i++){
        nClusterAvTot[i] = a.nClusterAverage("nCluster", "nCluster", "number of events", "Mean", nValue, nbin, "log", nMinScan[i], nMaxScan[i]);
        nClusterStdTot[i] = a.nClusterAverage("nCluster", "nCluster", "number of events", "StdDev", nValue, nbin, "log", nMinScan[i], nMaxScan[i]);
    }

        double avCluster = a.nClusterAverageTot("totCluster", "nCluster", "number of events", "Mean", nValue, nbin, "log", nMinScan[0], nMaxScan[0], nMinScan[1], nMaxScan[1]);
        double stdCluster = a.nClusterAverageTot("totCluster", "nCluster", "number of events", "StdDev", nValue, nbin, "log", nMinScan[0], nMaxScan[0], nMinScan[1], nMaxScan[1]);

//    a.histoClustBX("ClusterAverageBXid", nValue, nClusterAv, nClusterStd);
    TH1F* h1 = a.timeHisto("timeStampAverageCluster", "time stamp", "< nCluster >",  10, nValue, nMinScan[0], nMaxScan[0]);
    TH1F* h2 = a.timeHisto("timeStampAverageCluster", "time stamp", "< nCluster >", 10, nValue, nMinScan[1], nMaxScan[1]);

//    a.timeHistoBX("timeStampAverageClusterBXid", "time stamp", "number of events", 20, nValue, 1530412000, 1530427080, nBXid);
//    a.timeHistoBX("timeStampAverageClusterBXid",  "time stamp","number of events", 20, nValue, nMinScan[1], nMaxScan[1], nBXid);


//    a.mixHisto("nClusterBin", h1, h2);

    lumAnalyze aVdm("merged_ZB1.root",0);
    aVdm.Loop();
    int nValueVdm = aVdm.fChain->GetEntriesFast();


    cout<<"ca arrive"<<endl;
/*
    TH1F* hist = aVdm.timeHisto("Signal", "timeStamp", "< nCluster >",100, nValueVdm, 1530406000, 1530412500);
    double maxLumino = 0;
    for(int i=0; i<100; i++)
        if(hist->GetBinContent(i+1)>maxLumino)
            maxLumino=hist->GetBinContent(i+1);


    cout<<maxLumino<<endl;
    cout<<endl;
*/
    ofstream f("data/task1Values.txt", ios::out);

    for(int i=0; i<2; i++){
        f<<"Restriction "<<i<<"  : "<<nMinScan[i]<<" < timeStamp < "<<nMaxScan[i]<<endl<<endl;
        f<<"Average : "<<" "<<endl<<endl;
        for(int j =0; j<5; j++)
            f<<"BXid = "<<nBXid[j]<<" : "<<nClusterAv[i][j]<<endl;
        f<<endl;
        f<<"total : "<<nClusterAvTot[i]<<endl<<endl;
        f<<"Mean Error : "<<" "<<endl<<endl;
        for(int j =0; j<5; j++)
            f<<"BXid = "<<nBXid[j]<<" : "<<nClusterStd[i][j]<<endl;
        f<<endl;
        f<<"total : "<<nClusterStdTot[i]<<endl<<endl;
    }
    f<<"Totale : "<<avCluster<<" +- "<<stdCluster<<endl;
//    f<<"Max signal : "<<maxLumino<<endl;
//    f<<"ratio max : "<<(avCluster/maxLumino)<<endl;

    f.close();

    cout<<"finish"<<endl;

    app.Run();
    return 0;
}

#endif
