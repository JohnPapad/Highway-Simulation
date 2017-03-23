#include "vehicle.h"
#include <cstdlib>

vehicle::vehicle(const int & seg_number,const unsigned int & exit_number,const bool ready)
:exit_seg(exit_number),current_seg(seg_number),ready_to_exit(ready)
{}

vehicle::vehicle(const int & seg_number,const unsigned int & exit_number)
:exit_seg(exit_number),current_seg(seg_number)
{
    ready_to_exit=rand()%2 ;//[0,1]
}

void vehicle::print(const int & index)
{
    cout<<"This is vehicle number #"<<index<<endl;
    cout<<"ExitSegment:"<<exit_seg<<endl;
    cout<<"CurrentSegment:"<<current_seg<<endl;
    if(ready_to_exit)
    {
        cout<<"The vehicle is ready to exit"<<endl;
    }
    else
    {
        cout<<"The vehicle is NOT ready to exit"<<endl;
    }
}

unsigned int vehicle::get_exit_seg()
{
    return exit_seg;
}

int vehicle::get_current_seg()
{
    return current_seg;
}

bool vehicle::is_ready_to_exit()
{
    return ready_to_exit;
}

void vehicle::set_current_seg(const int & x)
{
    current_seg=x;
}

void vehicle::set_ready_to_exit(const bool & x)
{
    ready_to_exit=x;
}
