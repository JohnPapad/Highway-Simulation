#include <iostream>
#include <vector>
#include "seg.h"
#include "vehicle.h"

using namespace std;

#ifndef ATTIKI_ODOS_H
#define ATTIKI_ODOS_H

class attiki_odos
{
    private:
        vector<seg * >segs_array ;

    public:
        attiki_odos(const unsigned int & Nsegs,const int & K,const double & percent);
        ~attiki_odos();
        void print();
        unsigned int get_total_number_of_vehicles();
        void operate();

};

#endif // ATTIKI_ODOS_H
