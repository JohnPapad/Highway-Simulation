#include <iostream>
#include <cstdlib>
#include <ctime>
#include "attiki_odos.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc!=5)
    {
        cout<<"-> ERROR: Wrong number of command line arguments given"<<endl;
        return -1;
    }

    srand(time(NULL));

    int i;

    int NSegs=atoi(argv[1]);
    int K=atoi(argv[2]);
    int N=atoi(argv[3]);
    double Percent=atof(argv[4]);

    cout<<"--> Command line arguments given <--"<<endl;
    cout<<"-> NSegs: "<<NSegs<<endl;
    cout<<"-> K: "<<K<<endl;
    cout<<"-> N: "<<N<<endl;
    cout<<"-> Percent: "<<Percent<<endl;
    cout<<"------------------------------"<<endl;

    attiki_odos test(NSegs,K,Percent);

    cout<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<"--> 'Attiki Odos' Highway is operating <--"<<endl;
    cout<<"------------------------------------------"<<endl;
    // cout<<endl;
    //test.print();
    for(i=0;i<N;i++)
    {
        test.operate();
    }
    //test.print();
    return 0;
}
