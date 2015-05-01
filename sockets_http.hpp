/*
 New version of protocol - on top of http
 */

#ifndef SOCKETS_HTTP_HPP
#define	SOCKETS_HTTP_HPP

#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#include <boost/algorithm/string/replace.hpp>

#include "sockets_abstract.hpp"
#include "responseXML.hpp"
#include "httpFiles.hpp"

using boost::thread;
using namespace std;

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

class sockets_http : public tcp_server_abstract {
protected:
    boost::asio::io_service io_service;

public:

    sockets_http(int port, logs *log);
};

class connection_http : public tcp_connection_abstract {
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
    
    httpFile *file;
public:
    static int n;
    ~connection_http();
    connection_http(tcp::socket *socket, logs *log, tcp_server_abstract *serv)
    : tcp_connection_abstract(socket, log, serv) {

    };
    void operator()();

};

#endif	

