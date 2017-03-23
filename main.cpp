#include <iostream>
#include <cstdlib>
#include <ctime>
#include "attiki_odos.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc!=5)
    {
        cout<<"Wrong number of arguments in main function is given"<<endl;
        return -1;
    }

    srand(time(NULL));

    int i;

    int NSegs=atoi(argv[1]);
    int K=atoi(argv[2]);
    int N=atoi(argv[3]);
    double Percent=atof(argv[4]);

    cout<<"Number of segments is:"<<NSegs<<endl;
    cout<<"K is:"<<K<<endl;
    cout<<"Kukloi leitourgias (N) is:"<<N<<endl;
    cout<<"Percent is:"<<Percent<<endl;

    attiki_odos test(NSegs,K,Percent);

    cout<<endl;
    cout<<"Autokinhtodromos se leitourgia"<<endl;
    cout<<endl;
    //test.print();
    for(i=0;i<N;i++)
    {
        test.operate();
    }
    //test.print();
    return 0;
}
