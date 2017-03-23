#include <iostream>
#include <vector>
#include "tolls.h"
#include "e_tolls.h"
#include "vehicle.h"

using namespace std;


#ifndef ENTRANCE_H
#define ENTRANCE_H

class entrance
{
    private:
       unsigned int id ;
       int k;
       vector<toll * >tolls_array;
       vector<e_toll * >e_tolls_array;

    public:
        entrance(const int & K,const unsigned int & entrance_number,const unsigned int & number_of_segs);
        entrance(const int & K,const unsigned int & entrance_number);
        ~entrance();
        int get_id();
        int get_k();
        void print();
        unsigned int get_number_of_tolls();
        unsigned int get_number_of_e_tolls();
        unsigned int get_number_of_waiting_vehicles_at_tolls();
        unsigned int get_number_of_waiting_vehicles_at_e_tolls();
        unsigned int get_number_of_waiting_vehicles();
        void add_some_waiting_vehicles(const unsigned int & number_of_segs);
        int operate(vector<vehicle * >& vehicle_array_of_seg,const unsigned int & free_space,const int & number_of_segs);

};


#endif
