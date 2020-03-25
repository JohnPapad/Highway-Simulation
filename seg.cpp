#include "seg.h"
#include <cstdlib>
#include <cmath>

seg::seg(const int & K,const unsigned int & number_of_segs,const double & pososto)
:percent(pososto)
{
    unsigned int i ;
    static int counter=1;  //ta segments arxizoun apo 1 mexri Nsegs
    seg_number=counter;
    counter++;
    cout<<"-> Please enter the capacity of highway segment #"<<seg_number<<endl;
    // cout<<"Dwste th megisth xwrhtikothta tou tmhmatos #"<<seg_number<<" ths attikhs odou"<<endl;
    cin>>capacity;
    unsigned int number_of_vehicles=rand()%capacity + 1;//[1,capacity]

    if(seg_number!=number_of_segs)
    {
        eisodos=new entrance(K,seg_number-1,number_of_segs);
    }
    else//an einai to teleutaio segment mhn dhmiourghseis eisodo me diodia
    {
        eisodos=new entrance(-1,seg_number-1);
    }

    unsigned int exit_number;
    vehicle_array.reserve(number_of_vehicles);
    for(i=1;i<=number_of_vehicles;i++)
    {
        if(seg_number==1)//an to oxhma einai sto prwto segment tote den mporei na e3el8ei apo to idio,afou apo t prwto pragmatopoieitai mono eisodos
        {
            exit_number=rand()%(number_of_segs-seg_number)+seg_number+1;
        }
        else
        {
            exit_number=rand()%(number_of_segs-seg_number+1)+seg_number;
        }
        vehicle * temp=new vehicle(seg_number,exit_number);
        vehicle_array.push_back(temp);
    }
}

seg::~seg()
{
    unsigned int i;
    delete eisodos ;
    for(i=0;i<vehicle_array.size();i++)
    {
        delete vehicle_array[i];
    }
    vehicle_array.clear();
}
void seg::print()
{
    unsigned int i;
    cout<<"This is segment number #"<<seg_number<<endl;
    cout<<percent<<" of the vehicles in this segment are ready to exit from Attiki Odo at every circle"<<endl;
    cout<<"Segment's capacity is "<<capacity<<endl;
    cout<<"This segment has "<<vehicle_array.size()<<" vehicles"<<endl;
    cout<<endl;
    cout<<"Now printing vehicles' info moving at this segment"<<endl;
    cout<<endl;
    for(i=0;i<vehicle_array.size();i++)
    {
        vehicle_array[i]->print(i+1);
        cout<<"---------------------------------------------------"<<endl;
    }
    /*cout<<"Now printing segment's entrance info"<<endl;
    cout<<endl;
    eisodos->print();
    cout<<"---------------------------------------------------"<<endl;*/
}


unsigned int seg::get_no_of_vehicles()
{
    return vehicle_array.size() ;
}


void seg::make_some_ready()//randomly
{
    int random_vehicle;
    unsigned int counter=0;
    unsigned int plithos;
    double temp_plithos=percent*vehicle_array.size();
    if(floor(temp_plithos)!=temp_plithos)
    {
        plithos=floor(temp_plithos)+1;
    }
    else
    {
        plithos=temp_plithos;
    }

    if(plithos>get_number_of_not_ready_to_exit())
    {
        plithos=get_number_of_not_ready_to_exit();
    }

    while(counter<plithos)
    {
        random_vehicle=rand()%vehicle_array.size(); //[0,number_of_vehicles-1]
        if(!vehicle_array[random_vehicle]->is_ready_to_exit())
        {
            vehicle_array[random_vehicle]->set_ready_to_exit(1);
            counter++;
        }
    }

}

void seg::exit()
{
    unsigned int i=0;
    for(i=0;i<vehicle_array.size();i++)
    {
        if((vehicle_array[i]->is_ready_to_exit())&&(vehicle_array[i]->get_exit_seg()==seg_number))
        {
            delete vehicle_array[i];
            vehicle_array.erase(vehicle_array.begin()+i);
        }
    }
}

int seg::enter(const unsigned int & number_of_segs)
{
    unsigned int free_space=capacity-vehicle_array.size();
    int x=eisodos->operate(vehicle_array,free_space,number_of_segs);
    if(x==1)
    {
        cout<<"//////////////////////////////////////////////////"<<endl;
        // cout<<"Ka8usterhseis sthn eisodo tou komvou #"<<seg_number-1<<endl;
        cout<<"-> Delays on entrance of interchange #"<<seg_number-1<<endl; 
        // cout<<"//////////////////////////////////////////////////"<<endl;
    }
    return x;
}

int seg::pass(seg * previous_seg)//seg_ptr : to prohgoumeno tmhma ths attikhs odou
{
    unsigned int i;
    unsigned int could_not_pass;
    unsigned int free_space=capacity-vehicle_array.size();
    unsigned int counter=0; //metraei posa oxhmata apo ta prohgoumeno tmhma perasan sto twrino
    unsigned int number_of_ready_to_pass=previous_seg->get_number_of_ready_to_pass();

    while((counter<free_space)&&(counter<number_of_ready_to_pass))
    {
        i=rand()%previous_seg->vehicle_array.size(); //i:random vehicle from previous segment
        if((previous_seg->vehicle_array[i]->is_ready_to_exit())&&(previous_seg->vehicle_array[i]->get_exit_seg()>=seg_number))
        {
            counter++;
            previous_seg->vehicle_array[i]->set_current_seg(seg_number);
            previous_seg->vehicle_array[i]->set_ready_to_exit(0);
            vehicle_array.push_back(previous_seg->vehicle_array[i]);
            previous_seg->vehicle_array.erase(previous_seg->vehicle_array.begin()+i);
        }
    }

    could_not_pass=number_of_ready_to_pass-counter;

    if(could_not_pass>0)//an uparxei estw kai ena pou htan etoimo na perasei kai den mporese
    {   
        cout<<"//////////////////////////////////////////////////"<<endl;
        // cout<<"Ka8usterhseis meta ton komvo #"<<seg_number-1<<endl;
        cout<<"-> Delays after interchange #"<<seg_number-1<<endl;
        // cout<<"//////////////////////////////////////////////////"<<endl;
        return 1; //exei ektupw8ei mhnuma gia ka8usterhsh
    }
    else
    {
        return 0;
    }
}

unsigned int seg::get_number_of_ready_to_exit()//from attiki odos
{
    unsigned int i;
    unsigned int counter=0;
    for(i=0;i<vehicle_array.size();i++)
    {
        if((vehicle_array[i]->is_ready_to_exit())&&(vehicle_array[i]->get_exit_seg()==seg_number))
        {
            counter++;
        }
    }
    return counter;
}

unsigned int seg::get_number_of_not_ready_to_exit()
{
    unsigned int i;
    unsigned int counter=0;
    for(i=0;i<vehicle_array.size();i++)
    {
        if(!vehicle_array[i]->is_ready_to_exit())
        {
            counter++;
        }
    }
    return counter;
}

unsigned int seg::get_number_of_ready_to_pass()
{
    unsigned int i;
    unsigned int counter=0;
    for(i=0;i<vehicle_array.size();i++)
    {
        if((vehicle_array[i]->is_ready_to_exit())&&(vehicle_array[i]->get_exit_seg()>seg_number))
        {
            counter++;
        }
    }
    return counter;
}

void seg::operate(const int & index,const int & number_of_segs,seg * previous_seg)
{
    int enter_flag=0;
    int pass_flag=0;

    if(index!=0) //den pragmatopoieitai e3odos oute perasma oxhmatwn sto prwto komvo
    {
        exit();
        pass_flag=pass(previous_seg);
    }
    if(index<=number_of_segs-2) // den pragmatopoieitai eisodos oxhmatwn sto teleutaio komvo
    {
        enter_flag=enter(number_of_segs);
    }
    make_some_ready();

    if((enter_flag==0)&&(pass_flag==0))
    {
        cout<<"//////////////////////////////////////////////////"<<endl;
        cout<<"-> Keep a safe distance in the segment after interchange #"<<seg_number-1<<endl;
        // cout<<"Threiste tis apostaseis asfaleias meta ton komvo #"<<seg_number-1<<endl;
        // cout<<"//////////////////////////////////////////////////"<<endl;
    }
}
