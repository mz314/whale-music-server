#ifndef SOCKETS_ABSTRACT_HXX
#define	SOCKETS_ABSTRACT_HXX


#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>


#include "command.h"
#include "logs.h"
#include "protocol.h"
#include "musicserver.h"
#include "user_manager.h"
#include "gstreamer_io.hpp"
#include "xml.hpp"

using boost::asio::ip::tcp;
using namespace std;
#include "logs.h"

class tcp_server_abstract {
protected:
    bool exit;
    int port;
    logs *log;
public:
    tcp_server_abstract(int port, logs *log);

    void start();
    void stop();
};

class tcp_connection_abstract {
protected:
    tcp::socket *socket;
    logs *log;
    tcp_server_abstract *serv;
public:
    tcp_connection_abstract(tcp::socket *socket, logs *log, tcp_server_abstract *serv);
    ~tcp_connection_abstract();
};

#endif	

