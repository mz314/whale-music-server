#include "command.h"

command::command()
{

}

void command::operator()()
{
 this->callback(this->callback_data,this->data_size);
}

void command::thread_start()
{
 boost::thread(boost::ref(*this)); 
}

void command::set_callback(void (*fun)(void *,size_t))
{
 this->callback=fun;
}

void command::set_calback_data(void *data,size_t size)
{
 this->data_size=size;
 this->callback_data=data;
}