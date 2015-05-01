/* 
 * File:   sockets_abstract.cpp
 * Author: maciek
 * 
 * Created on 10 styczeń 2014, 23:20
 */

#include "sockets_abstract.hpp"


//TCP Server

tcp_server_abstract::tcp_server_abstract(int port, logs *log) : log(log), port(port) {
    char f[]="Making server at port %i";
    char cmsg[255];
    sprintf(cmsg,f,port);
    this->exit=false;
    log->message(string(cmsg));
}

//TCP Connection
tcp_connection_abstract::tcp_connection_abstract(tcp::socket *socket,logs *log,tcp_server_abstract *serv) {
    this->log=log;
    this->serv=serv;
    this->socket=socket;
    
}

tcp_connection_abstract::~tcp_connection_abstract() {
    
}


     