#include "Grafo.h"
#include "functions.cc"
using namespace std;

int main(){
    Grafo graf;
    graph(graf);

    string nt="";
    cout<<"Enter the number of times you want to try MNPs: "<<endl; cin>>nt; cout<<endl;
    int ntInt=stoi(nt);
    int casesCounter=0;

    for(int g=0; g<ntInt; g++){
        casesCounter=g;
        mnpCases(graf,casesCounter);
    }
}