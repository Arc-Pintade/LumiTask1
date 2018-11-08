#include "../include/lumAnalyze.hpp"

#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TApplication.h>
#include <TString.h>
#include <iostream>

using namespace std;

# ifndef __CINT__

int main(){

    TApplication app("app", nullptr, nullptr);

    lumAnalyze a;
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
/*
    a.intHisto("BXid", nValue, 0, 4000, nbin, a.BXidValue, "", "(1530412500<timeStamp<1530412800)", nMinScan[0], nMaxScan[0]);
    a.intHisto("BXid", nValue, 0, 4000, nbin, a.BXidValue, "", "(1530427080<timeStamp<1530427440)", nMinScan[1], nMaxScan[1]);

    double** nClusterAv = new double*[2]{0};
    double** nClusterStd = new double*[2]{0};
    for (int i = 0; i<2; i++){
        nClusterAv[i] = new double[5]{0};
        nClusterStd[i] = new double[5]{0};
    }

    for(int i=0; i<2; i++)
        for(int j=0; j<5; j++){
            nClusterAv[i][j] = a.nClusterAverageBX("nCluster", "Mean", nValue, nbin, "log", nMinScan[i], nMaxScan[i], nBXid[j]);
            nClusterStd[i][j] = a.nClusterAverageBX("nCluster", "StdDev", nValue, nbin, "log", nMinScan[i], nMaxScan[i], nBXid[j]);
        }

    cout<<" 265 Res1 = "<<nClusterAv[0][0]<<endl;
    cout<<" 865 Res1 = "<<nClusterAv[0][1]<<endl;
    cout<<" 1780 Res1 = "<<nClusterAv[0][2]<<endl;
    cout<<" 2192 Res1 = "<<nClusterAv[0][3]<<endl;
    cout<<" 3380 Res1 = "<<nClusterAv[0][4]<<endl;
    cout<<" 265 Res2 = "<<nClusterAv[1][0]<<endl;
    cout<<" 865 Res2 = "<<nClusterAv[1][1]<<endl;
    cout<<" 1780 Res2 = "<<nClusterAv[1][2]<<endl;
    cout<<" 2192 Res2 = "<<nClusterAv[1][3]<<endl;
    cout<<" 3380 Res2 = "<<nClusterAv[1][4]<<endl;

*/
//    a.histoClustBX("ClusterAverageBXid", nValue, nClusterAv, nClusterStd);
    a.timeHisto("timeStampAverageCluster", 10, nValue, nMinScan[0], nMaxScan[0]);
    a.timeHisto("timeStampAverageCluster", 10, nValue, nMinScan[1], nMaxScan[1]);

    a.timeHistoBX("timeStampAverageClusterBXid", 10, nValue, nMinScan[0], nMaxScan[0], nBXid);
    a.timeHistoBX("timeStampAverageClusterBXid", 10, nValue, nMinScan[1], nMaxScan[1], nBXid);

    for(int i=0; i<nValue; i++){
        if(a.timeStampValue[i] > nMinScan[0] && a.timeStampValue[i] < nMaxScan[0])
            nScan1++;
    }
    cout<<"Scan1 : "<<nScan1<<endl;
    cout<<endl;
    for(int i=0; i<nValue; i++){
        if(a.timeStampValue[i] > nMinScan[1] && a.timeStampValue[i] < nMaxScan[1])
            nScan2++;
    }
    cout<<"Scan2 : "<<nScan2<<endl;

    app.Run();
    return 0;
}

#endif
