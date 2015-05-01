#include "heavy_tasks.hpp"


void heavy_task::operator()()
{
  finished=false;
  this->ret=fun(this->params,&abort);
  finished=true;
  if (done) done(this->ret);
}

heavy_task::heavy_task()
{
 this->ret=NULL;
}

heavy_task::~heavy_task()
{
 this->stop();
}

void heavy_task::stop(bool wait) 
{
 this->abort=true;
 if (wait)  //WARNING: Tu może być problem
 {
   while (!finished) {}
 
 }
}

void heavy_task::start()
{
 this->abort=false;
 this->finished=false;
 boost::thread(boost::ref(*this));
 
}

void heavy_task::setup(func_type fun,finished_type when_finished,params_type params)
{
 this->fun=fun;
 this->params=params;
 this->done=when_finished;
}

return_type heavy_task::returned()
{
 return ret;
}