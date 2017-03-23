#include <iostream>

using namespace std;

#ifndef VEHICLE_H
#define VEHICLE_H

class vehicle
{
    private:
        unsigned int exit_seg ; //apo poio segment 8a vgei
        int current_seg ; //se poio segment vrisketai ka8e kuklo leitourgias
        bool ready_to_exit;//from current segment

    public:
        vehicle(const int & seg_number,const unsigned int & exit_number);
        vehicle(const int & seg_number,const unsigned int & exit_number,const bool ready);
        unsigned int get_exit_seg();
        int get_current_seg();
        bool is_ready_to_exit();
        void print(const int & index);
        void set_current_seg(const int & x);
        void set_ready_to_exit(const bool & x);

};

#endif
