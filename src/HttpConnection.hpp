#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#include <boost/algorithm/string/replace.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>

#include "responseXML.hpp"
#include "httpFiles.hpp"
#include "user_state.hpp"
#include "command.h"
#include "logs.h"
#include "protocol.h"
#include "musicserver.h"
#include "user_manager.h"
#include "gstreamer_io.hpp"
#include "xml.hpp"



#define MAX_HTTP_REQ_LENGTH 10024
#define MAX_RESPONSE_SIZE 1000024
#define HTTP_CONTENT_LENGTH "Content-Length: "
#define HTTP_RANGE "Range: bytes="

typedef char responseType[MAX_RESPONSE_SIZE];
typedef char clientReq[MAX_HTTP_REQ_LENGTH];


struct chunkedRange {
    int start,end;
};

struct parsedReq {
    reqParams post, get;
    string method, url;
    bool keepalive;
};

struct clientReqData {
    clientReq data;
    int length;
};

using boost::thread;
using namespace std;
using boost::asio::ip::tcp;
using namespace std;using boost::asio::ip::tcp;


class HttpConnection {
protected:
    reqParams post, get, request;
    chunkedRange range;
    string method, url;
    user_state * user;
    bool keepalive;
    void dumpRequest(clientReqData &req);
    void sendResponse(const char *content, const char *content_type = "text/plain", string status="200 OK");
    void sendChunkedResponse(const char *content, const char *content_type);
//    void sendResponse(const string &content, char *content_type = "text/plain", int code = 200);;
    void sendResponseString(const char *response);
    void sendResponseString(const stringstream & response);
    void replaceEntities(string &str);
    bool processRequest();
    clientReqData getRequest();
    void parseRequest(const clientReqData &req);
    reqParams parseParams(const string & params);
    reqParams parsePost(const clientReqData &req);
    void processDownload(bool chunked=false,string file_name="");
    tcp::socket *socket;
    logs *log;
    
    httpFile *file;
public:
    static int n;
    ~HttpConnection();
    HttpConnection(tcp::socket *socket, logs *log) : socket(socket), log(log)
    {

    };
    void operator()();

};

#endif