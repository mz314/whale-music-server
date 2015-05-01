#ifndef MS_SERVER_MANAGER
#define MS_SERVER_MANAGER


#include <iostream>
#include <string>
#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


// #include "sockets.h"
#include "sockets_http.hpp"
#include "logs.h"

using namespace std;

class server_manager 
{
 
 public: 
  server_manager(int port,logs *log,bool daemon=false); 
  void daemonize(); 
 private:
  void log_message(string msg,log_type type);
  bool make_server(int port,bool daemon);
  void msg();
  static void signalHandler(int sig);
  static sockets_http *server;   
  logs *log;
  
};



#endif