#include <iostream>
#include <vector>
#include "vehicle.h"
#include "entrance.h"

using namespace std;

#ifndef SEG_H
#define SEG_H

class seg
{
    private:
        unsigned int capacity ; //of cars (maximum)
        double percent;
        unsigned int seg_number;
        entrance * eisodos ;
        vector<vehicle * >vehicle_array ;

    public:
        seg(const int & K,const unsigned int & number_of_segs,const double & pososto);
        ~seg();
        void print();
        unsigned int get_no_of_vehicles();
        void make_some_ready();
        void exit();
        int enter(const unsigned int & number_of_segs);
        int pass(seg * seg_ptr);
        unsigned int get_number_of_ready_to_exit();
        unsigned int get_number_of_not_ready_to_exit();
        unsigned int get_number_of_ready_to_pass();
        void operate(const int & index,const int & number_of_segs,seg * previous_seg);
};

#endif
