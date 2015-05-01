#ifndef LOGS_H
#define LOGS_H

#include <iostream>
#include <string>
#include <cstdio>
#include <sys/syslog.h>


using namespace std;

enum log_type
{
 DEBUG,
 INFO,
 WARNING,
 SUPADEBUG
};

enum output_type {
 STDOUT,
 SYSLOG,
 LOGFILE
};


typedef int (* out_function_type )(string) ;

class logs
{
 private:
  static logs *me;
  bool debug;
  //out_function_type of;
  output_type ot;
  string logfile;
  void output(string o);
  
 public:
  logs();
  static logs *get_instance()
  {
   if (!logs::me)
     logs::me=new logs();
   return logs::me;
  }
  //void setOut(out_function_type of);
  void setOut(output_type ot);
  void setLogFile(string logfile);
  void signalHandler(int sig);
  void message(string msg,log_type type=DEBUG,string subsytem="");
  void set_debug(bool debug);
  ~logs();
    
};

out_function_type console(string o);
out_function_type syslog(string o);



#endif