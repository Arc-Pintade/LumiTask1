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

    long long nMinScan1 = 1530412500;
    long long nMaxScan1 = 1530412800;
    long long nMinScan2 = 1530427080;
    long long nMaxScan2 = 1530427440;
    int nbin = 100;
    int nScan1 = 0;
    int nScan2 = 0;


    int nValue = a.fChain->GetEntriesFast();

// For histos (name, Number of events, Minimum of histo, Maximum of histo, Bin of histo, input, Option logY ("yes" or anything else for no), Other part of name (title), Minimum of restriction, Maximum of restriction)

    a.doubleHisto("nCluster", nValue, 0, 10000, nbin, a.nClusterValue, "log", "(1530412500<timeStamp<1530412800)", nMinScan1, nMaxScan1);
    a.doubleHisto("nCluster", nValue, 0, 10000, nbin, a.nClusterValue, "log", "(1530427080<timeStamp<1530427440)", nMinScan2, nMaxScan2);
    a.intHisto("BXid", nValue, 0, 4000, nbin, a.BXidValue, "", "(1530412500<timeStamp<1530412800)", nMinScan1, nMaxScan1);
    a.intHisto("BXid", nValue, 0, 4000, nbin, a.BXidValue, "", "(1530427080<timeStamp<1530427440)", nMinScan2, nMaxScan2);

    a.doubleHistoBX("nCluster", nValue, 0, 10000, nbin, a.nClusterValue, "log", "(1530412500<timeStamp<1530412800)", nMinScan1, nMaxScan1, 265);
    a.doubleHistoBX("nCluster", nValue, 0, 10000, nbin, a.nClusterValue, "log", "(1530412500<timeStamp<1530412800)", nMinScan1, nMaxScan1, 865);
    a.doubleHistoBX("nCluster", nValue, 0, 10000, nbin, a.nClusterValue, "log", "(1530412500<timeStamp<1530412800)", nMinScan1, nMaxScan1, 1780);
    a.doubleHistoBX("nCluster", nValue, 0, 10000, nbin, a.nClusterValue, "log", "(1530412500<timeStamp<1530412800)", nMinScan1, nMaxScan1, 2192);
    a.doubleHistoBX("nCluster", nValue, 0, 10000, nbin, a.nClusterValue, "log", "(1530412500<timeStamp<1530412800)", nMinScan1, nMaxScan1, 3380);

    for(int i=0; i<nValue; i++){
        if(a.timeStampValue[i] > nMinScan1 && a.timeStampValue[i] < nMaxScan1)
            nScan1++;
    }
    cout<<"Scan1 : "<<nScan1<<endl;
    cout<<endl;
    for(int i=0; i<nValue; i++){
        if(a.timeStampValue[i] > nMinScan2 && a.timeStampValue[i] < nMaxScan2)
            nScan2++;
    }
    cout<<"Scan2 : "<<nScan2<<endl;

    app.Run();
    return 0;
}

#endif
