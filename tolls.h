#include <iostream>
#include <vector>
#include "vehicle.h"

using namespace std;

#ifndef TOLLS_H
#define TOLLS_H

class toll
{
    private:
        vector<vehicle * >vehicle_array_of_toll ;

    public:
        toll(const unsigned int & seg_number,const unsigned int & number_of_segs);
        ~toll();
        void print(const int & index);
        unsigned int get_number_of_vehicles();
        void add_some_waiting_vehicles(const int & seg_number,const int & number_of_segs);
        vector<vehicle * >& get_vehicle_array_of_toll();
};

#endif
