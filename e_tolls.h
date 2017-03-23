#include <iostream>
#include <vector>
#include "vehicle.h"

using namespace std;

#ifndef E_TOLLS_H
#define E_TOLLS_H

class e_toll
{
    private:
        vector<vehicle * > vehicle_array_of_e_toll ;

    public:
        e_toll(const unsigned int & seg_number,const unsigned int & number_of_segs);
        ~e_toll();
        void print(const int & index);
        unsigned int get_number_of_vehicles();
        void add_some_waiting_vehicles(const int & seg_number,const int & number_of_segs);
        vector<vehicle * >& get_vehicle_array_of_e_toll();

};

#endif

