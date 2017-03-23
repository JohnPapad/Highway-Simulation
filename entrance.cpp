#include "entrance.h"
#include <cstdlib>

entrance::entrance(const int & K,const unsigned int & entrance_number,const unsigned int & number_of_segs)
:id(entrance_number),k(K)
{
    unsigned int number_of_tolls=rand()%2+2; //[2,3]
    unsigned int number_of_e_tolls=rand()%2+4; //[4,5]
    unsigned int i;
    //dhmiourgeitai tuxaios ari8mos diodiwn kai e-pass
    tolls_array.reserve(number_of_tolls);
    for(i=0;i<number_of_tolls;i++)
    {
        toll * temp=new toll(id+1,number_of_segs);
        tolls_array.push_back(temp);
    }

    e_tolls_array.reserve(number_of_e_tolls);
    for(i=0;i<number_of_e_tolls;i++)
    {
        e_toll * temp2=new e_toll(id+1,number_of_segs);
        e_tolls_array.push_back(temp2);
    }
}

entrance::entrance(const int & K,const unsigned int & entrance_number)
:id(entrance_number),k(K)
{}

entrance::~entrance()
{
    unsigned int i ;
    for(i=0;i<tolls_array.size();i++)
    {
        delete tolls_array[i];
    }
    tolls_array.clear();

    for(i=0;i<e_tolls_array.size();i++)
    {
        delete e_tolls_array[i];
    }
    e_tolls_array.clear();
}

int entrance::get_id()
{
    return id;
}

int entrance::get_k()
{
    return k;
}

void entrance::print()
{
    unsigned int i;

    cout<<"Entrance ID:"<<id<<endl;
    if(k==-1)
    {
        cout<<"Einai o teleutaios komvos kai den exei diodia eisodou"<<endl;
        cout<<"Apo to sugkekrimeno komvo progmatopoieitai mono e3odos oxhmatwn"<<endl;
    }
    else
    {
        cout<<"Entrance K:"<<k<<endl;
        cout<<"There are "<<tolls_array.size()<<" tolls at this entrance"<<endl;
        cout<<"There are "<<e_tolls_array.size()<<" e-tolls at this entrance"<<endl;
        cout<<endl;
        cout<<"Now printing tolls"<<endl;
        cout<<endl;
        for(i=0;i<tolls_array.size();i++)
        {
            tolls_array[i]->print(i+1);
            cout<<"---------------------------------------------------"<<endl;
        }
        cout<<"Now printing e-tools"<<endl;
        for(i=0;i<e_tolls_array.size();i++)
        {
            e_tolls_array[i]->print(i+1);
            cout<<"---------------------------------------------------"<<endl;
        }
    }
}

unsigned int entrance::get_number_of_tolls()
{
    return tolls_array.size();
}

unsigned int entrance::get_number_of_e_tolls()
{
    return e_tolls_array.size();
}

unsigned int entrance::get_number_of_waiting_vehicles_at_tolls()
{
    unsigned int i;
    unsigned int counter=0;
    for(i=0;i<tolls_array.size();i++)
    {
        counter+=tolls_array[i]->get_number_of_vehicles();
    }
    return counter;
}

unsigned int entrance::get_number_of_waiting_vehicles_at_e_tolls()
{
    unsigned int i;
    unsigned int counter=0;
    for(i=0;i<e_tolls_array.size();i++)
    {
        counter+=e_tolls_array[i]->get_number_of_vehicles();
    }
    return counter;
}

unsigned int entrance::get_number_of_waiting_vehicles()
{
    return get_number_of_waiting_vehicles_at_tolls()+get_number_of_waiting_vehicles_at_e_tolls();
}

void entrance::add_some_waiting_vehicles(const unsigned int & number_of_segs)
{
    unsigned int i;

    for(i=0;i<tolls_array.size();i++)
    {
        tolls_array[i]->add_some_waiting_vehicles(id+1,number_of_segs);
    }

    for(i=0;i<e_tolls_array.size();i++)
    {
        e_tolls_array[i]->add_some_waiting_vehicles(id+1,number_of_segs);
    }
}

int entrance::operate(vector<vehicle * >& vehicle_array_of_seg,const unsigned int & free_space,const int & number_of_segs)
{
    unsigned const int toll_max_limit=k;
    unsigned const int e_toll_max_limit=2*k;
    unsigned const int overall_max_limit=3*k;
    unsigned int going_to_enter=0 ;
    unsigned int normal_toll_counter=0;
    unsigned int e_toll_counter=0;
    unsigned int overall_counter=0;
    unsigned int toll_or_e_toll;
    unsigned int random_toll;
    unsigned int temp_random;
    unsigned int i;
    unsigned int remaining ;
    unsigned int number_of_waiting_vehicles_at_tolls=get_number_of_waiting_vehicles_at_tolls();
    unsigned int number_of_waiting_vehicles_at_e_tolls=get_number_of_waiting_vehicles_at_e_tolls();
    unsigned int total_number_of_wainting_vehicles=get_number_of_waiting_vehicles();

    if(free_space<overall_max_limit)
    {
        going_to_enter=free_space;
    }
    else
    {
        going_to_enter=overall_max_limit;
    }

    if(going_to_enter>total_number_of_wainting_vehicles)
    {
        going_to_enter=total_number_of_wainting_vehicles;
    }

    vector<unsigned int>available_tolls;//exoun ta indexes twn kanonikwn diodiwn sta opoia uparxoun dia8esmia oxhmata gia eisodo

    for(i=0;i<tolls_array.size();i++)
    {
        if(tolls_array[i]->get_vehicle_array_of_toll().size()!=0)
        {
            available_tolls.push_back(i);
        }
    }

   vector<unsigned int>available_e_tolls;//exoun ta indexes twn e-pass sta opoia uparxoun dia8esmia oxhmata gia eisodo

    for(i=0;i<e_tolls_array.size();i++)
    {
        if(e_tolls_array[i]->get_vehicle_array_of_e_toll().size()!=0)
        {
            available_e_tolls.push_back(i);
        }
    }

    while(overall_counter<going_to_enter)
    {
        if(((normal_toll_counter>=toll_max_limit)&&(get_number_of_waiting_vehicles_at_e_tolls()==0))||((e_toll_counter>=e_toll_max_limit)&&(get_number_of_waiting_vehicles_at_tolls()==0)))
        {
            break;
        }

        if((normal_toll_counter>=toll_max_limit)||(normal_toll_counter>=number_of_waiting_vehicles_at_tolls)||(get_number_of_waiting_vehicles_at_tolls()==0))
        {
            toll_or_e_toll=1;
        }
        else if((e_toll_counter>=e_toll_max_limit)||(e_toll_counter>=number_of_waiting_vehicles_at_e_tolls)||(get_number_of_waiting_vehicles_at_e_tolls()==0))
        {
            toll_or_e_toll=0;
        }
        else//tuxaia epilogh
        {
            toll_or_e_toll=rand()%2 ;//[0,1]
        }

        if(toll_or_e_toll==0) //an er8ei 0 epele3e kapoio apo ta kanonika diodia
        {

            temp_random=rand()%available_tolls.size();//epele3e ena tuxaio kanoniko tool apo ta dia8esima (apo auta dld pou exoun toylaxiston ena oxhma)
            random_toll=available_tolls[temp_random];

            if(tolls_array[random_toll]->get_vehicle_array_of_toll().size()!=0)//exei toulaxiston ena oxhma (logika 8a exei)
            {
                tolls_array[random_toll]->get_vehicle_array_of_toll()[0]->set_current_seg(id+1);//to autokinhto molis bhke sto entrance+1 segment
                tolls_array[random_toll]->get_vehicle_array_of_toll()[0]->set_ready_to_exit(0);// molis mpainei den einai etoimo na vgei
                vehicle_array_of_seg.push_back(tolls_array[random_toll]->get_vehicle_array_of_toll()[0]);//pros8etoume to autokinhto pou molis mphke, sto pinaka me ta autokinhta pou exei to sugkekrimeno segment
                tolls_array[random_toll]->get_vehicle_array_of_toll().erase(tolls_array[random_toll]->get_vehicle_array_of_toll().begin()+0);//diagrafoume to autokinhto pou molis mphke,apo to pinaka me ta autokinhta pou exei to diodio
                overall_counter++;
                normal_toll_counter++;
                if(tolls_array[random_toll]->get_vehicle_array_of_toll().size()==0)
                {
                    for(i=0;i<available_tolls.size();i++)
                    {
                        if(available_tolls[i]==random_toll)
                        {
                            available_tolls.erase(available_tolls.begin()+i);
                            break;
                        }
                    }
                }
            }
        }
        else//an er8ei 1 panomoitupa me ta kanonika diodia
        {

            temp_random=rand()%available_e_tolls.size();//epele3e ena tuxaio e-tool
            random_toll=available_e_tolls[temp_random];

            if(e_tolls_array[random_toll]->get_vehicle_array_of_e_toll().size()!=0)
            {
                e_tolls_array[random_toll]->get_vehicle_array_of_e_toll()[0]->set_current_seg(id+1);
                e_tolls_array[random_toll]->get_vehicle_array_of_e_toll()[0]->set_ready_to_exit(0);
                vehicle_array_of_seg.push_back(e_tolls_array[random_toll]->get_vehicle_array_of_e_toll()[0]);
                e_tolls_array[random_toll]->get_vehicle_array_of_e_toll().erase(e_tolls_array[random_toll]->get_vehicle_array_of_e_toll().begin()+0);
                overall_counter++;
                e_toll_counter++;
                if(e_tolls_array[random_toll]->get_vehicle_array_of_e_toll().size()==0)
                {
                    for(i=0;i<available_e_tolls.size();i++)
                    {
                        if(available_e_tolls[i]==random_toll)
                        {
                            available_e_tolls.erase(available_e_tolls.begin()+i);
                            break;
                        }
                    }
                }
            }
        }
    }

    if((normal_toll_counter==toll_max_limit)&&(e_toll_counter==e_toll_max_limit))
    {
        k++; // mphke o megistos ari8mos oxhmatwn
    }
    else
    {
        k--;
    }

    add_some_waiting_vehicles(number_of_segs); //pros8etoume merika akoma oxhmata sta diodia

    remaining=total_number_of_wainting_vehicles-overall_counter;
    if(remaining>0) //an ta oxhmata pou perimenan arxika einai perissotera apo auta pou eishl8an
    { //dld estw kai an uparxei kai ena oxhma pou perimene kai den katafere na eisel8ei
        return 1; //ektupwse mhnuma gia ka8usterhsh
    }
    else
    {
        return 0;
    }
}

