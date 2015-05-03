#include "HttpServer.hpp"

HttpServer::HttpServer(int port, logs *log) : log(log), port(port) {
    httpFile::initMime();
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
    tcp::socket *socket;
    HttpConnection *conn;
    while (exit == false) {
        socket = new tcp::socket(io_service);
        log->message("Waiting for a connection...", INFO, "SERVER");
        acceptor.accept(*socket);
        log->message("New connection accepted.", DEBUG);
        conn = new HttpConnection(socket, log);
        boost::thread(boost::ref(*conn));
        //(*conn)();


    }
}

