#ifndef HEAVYTASKS_H
#define HEAVYTASKS_H

#include <iostream>
#include <boost/thread/thread.hpp>

using namespace std;



typedef void *return_type;
typedef void *params_type;
typedef void * (*func_type)(params_type params,bool *abort);
typedef void (*finished_type)(return_type returned);

class heavy_task //?? dla czasochłonnych poleceń
{
  protected:
   func_type fun;
   params_type params;
   return_type ret;
   finished_type done;
   bool abort,finished;
  public:
   heavy_task();
   ~heavy_task();
   virtual void operator()();
   virtual void start(); //ta funkcja wywołuje operator() 
   virtual void setup(func_type fun,finished_type when_done,params_type params);
   virtual return_type returned();
   virtual void stop(bool wait=false);
    
};

#endif