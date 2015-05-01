#ifndef MS_SOCKETS_H
#define MS_SOCKETS_H


#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <cstring> //TODO: pozbyć się tego

#include "command.h"
#include "logs.h"
#include "protocol.h"
#include "musicserver.h"
#include "user_manager.h"
#include "gstreamer_io.hpp"
#include "xml.hpp"



using namespace std;
using boost::asio::ip::tcp;




class tcp_command : public command // No nie wiem...
{
  public:
    tcp_command()
    { /* //////////////// */ };
    tcp_command(void *buffer);
    virtual void operator()();
    void set_write(void *buffer,size_t size);
    void set_read(void *buffer,size_t size);
  private:
    size_t write();
    size_t read();
    void *write_buffer,*read_buffer;
    
};



class tcp_server;

class tcp_connection
{
 public:
  tcp_connection(tcp::socket *socket,logs *log,tcp_server *serv);
  tcp_connection(const tcp_connection &source);
  void operator()();
  ~tcp_connection();
 private:
   bool handshake();
   bool exit;
   static char *response_xml; //odpowiedzi w xml
   request *get_request();
   void processReq(request *req);
   bool get_string_data(const request * const req,string_data &data);
   bool send_response(const string &code,const string &content);
   bool send_dir_list(dir_data *dd);
   bool send(void *data,size_data size);
   bool send_data(void *data,size_data size);
   tcp::socket *socket;
   tcp::acceptor *acceptor;
   logs *log;
   tcp_server *serv;
};


class tcp_server
{
  public:
    tcp_server(int port,logs *log); 
    void start();
    void stop();
    void dispose_connection(tcp_connection *conn);
  private:
    vector <tcp_connection *> connections; //TODO: UŻYĆ TEGO
    void pool_connections();   
    int port;
    logs *log;
    bool exit;
    boost::asio::io_service io_service;
    boost::thread *pool_connections_thread; //DEPRECATED
};


#endif