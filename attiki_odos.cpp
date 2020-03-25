#include "attiki_odos.h"

using namespace std;

attiki_odos::attiki_odos(const unsigned int & Nsegs,const int & K,const double & percent)
{
    unsigned int i;
    segs_array.reserve(Nsegs);
    for(i=1;i<=Nsegs;i++)
    {
        seg * temp=new seg(K,Nsegs,percent);
        segs_array.push_back(temp);
    }
}

attiki_odos::~attiki_odos()
{
    unsigned int i;
    for(i=0;i<segs_array.size();i++)
    {
        delete segs_array[i] ;
    }
    segs_array.clear();
}

void attiki_odos::print()
{
    unsigned int i;
    cout<<"Printing Attiki Odos info"<<endl;
    cout<<"Attiki Odos has "<<segs_array.size()<<" segments"<<endl;
    cout<<"Attiki Odos has "<<get_total_number_of_vehicles()<<" vehicles moving in it"<<endl;
    cout<<endl;
    cout<<"Now printing  Attiki Odos segments' info"<<endl;
    cout<<endl;
    for(i=0;i<segs_array.size();i++)
    {
        segs_array[i]->print();
        cout<<"---------------------------------------------------"<<endl;
    }
}

unsigned int attiki_odos::get_total_number_of_vehicles()
{
    unsigned int i ;
    unsigned int counter=0;
    for(i=0;i<segs_array.size();i++)
    {
        counter+=segs_array[i]->get_no_of_vehicles();
    }
    return counter;
}


void attiki_odos::operate()
{
    int i;
    cout<<endl;
    cout<<"---------------------------------------------------"<<endl;
    cout<<"-> Total number of vehicles moving in the highway: "<<get_total_number_of_vehicles()<<endl;
    // cout<<"Kinountai sunolika "<<get_total_number_of_vehicles()<<" oxhmata sthn Attiki Odo"<<endl;
    cout<<"---------------------------------------------------"<<endl;
    cout<<endl;
    for(i=segs_array.size()-1;i>=0;i--)//gia ola ta tmhmata ths attikhs odou arxizontas apo to teleutaio
    {
        segs_array[i]->operate(i,segs_array.size(),segs_array[i-1]);
    }
}

