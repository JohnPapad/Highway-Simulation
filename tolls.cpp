#include "tolls.h"
#include <cstdlib>

toll::toll(const unsigned int & seg_number,const unsigned int & number_of_segs)
{
    unsigned int number_of_vehicles=rand()%5 +1 ;//[1,5]
    unsigned int i ;
    unsigned int exit_number;

    vehicle_array_of_toll.reserve(number_of_vehicles);
    for(i=0;i<number_of_vehicles;i++)
    {
        if(seg_number==1)
        {
            exit_number=rand()%(number_of_segs-seg_number)+seg_number+1;//an ta oxhmata vriskontai sto prwto segment tote den mporoun na e3el8oun apo to idio, afou sto prwto segment ginetai mono eisodos kai oxi e3odos
        }
        else
        {
            exit_number=rand()%(number_of_segs-seg_number+1)+seg_number;
        }
        vehicle * temp=new vehicle(-1,exit_number,0);
        vehicle_array_of_toll.push_back(temp);
    }
}

toll::~toll()
{
    unsigned int i;
    for(i=0;i<vehicle_array_of_toll.size();i++)
    {
        delete vehicle_array_of_toll[i];
    }
    vehicle_array_of_toll.clear();
}

void toll::print(const int & index)
{
    unsigned int i;
    cout<<"This is toll number #"<<index<<endl;
    cout<<"This toll has "<<vehicle_array_of_toll.size()<<" vehicles"<<endl;
    cout<<endl;
    cout<<"Now printing vehicles from first to last one"<<endl;
    cout<<endl;
    for(i=0;i<vehicle_array_of_toll.size();i++)
    {
        vehicle_array_of_toll[i]->print(i+1);
        cout<<"---------------------------------------------------"<<endl;
    }
}

unsigned int toll::get_number_of_vehicles()
{
    return vehicle_array_of_toll.size() ;
}

void toll::add_some_waiting_vehicles(const int & seg_number,const int & number_of_segs)//pros8etei 0,1 h 2 vehicles sto telos tou vector
{
    unsigned int i ;
    unsigned int number_of_adding_vehicles=rand()%3 +0  ;//[0,2]
    unsigned int exit_number;
    //ka8e diodio exei tuxaio ari8mo autokinhtwv
    for(i=0;i<number_of_adding_vehicles;i++)
    {
        exit_number=rand()%(number_of_segs-seg_number+1)+seg_number;
        vehicle * temp=new vehicle(-1,exit_number,0);
        vehicle_array_of_toll.push_back(temp);
    }
}


vector<vehicle * >& toll::get_vehicle_array_of_toll()
{
    return vehicle_array_of_toll ;
}

