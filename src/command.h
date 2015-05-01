#ifndef MS_COMMAND_H
#define MS_COMMAND_H

#include <iostream>
#include <boost/thread/thread.hpp>



using namespace std;

class command //Ogólna klasa reprezentująca polecenie z użyciem wątków  (lub bez)
{
 public:
  command();
  virtual void operator()(); //Wywołanie poprzez operator() lub thread_start().
  virtual void thread_start();
  virtual void set_calback_data(void *data,size_t size);
  virtual void set_callback(void (*fun)(void *,size_t)); //FUNCTION POINTER, anyone??!
 protected: 
   size_t data_size;
   void (*callback)(void *,size_t);
   void *callback_data;
   boost::thread *_thread;
};

#endif
