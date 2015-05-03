#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>

#include "HttpConnection.hpp"
#include "command.h"
#include "logs.h"
#include "protocol.h"
#include "musicserver.h"
#include "user_manager.h"
#include "gstreamer_io.hpp"
#include "xml.hpp"
#include "logs.h"

using boost::asio::ip::tcp;
using namespace std;using boost::asio::ip::tcp;
using namespace std;

class HttpServer {
protected:
    bool exit;
    int port;
    logs *log;
    boost::asio::io_service io_service;
public:
    HttpServer(int port, logs *log);
    void start();
    void stop();
};

#endif