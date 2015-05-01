#include "server_manager.h"

sockets_http * server_manager::server = 0;

void server_manager::daemonize() {
    pid_t pid, sid;
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    signal(SIGHUP, server_manager::signalHandler);

    signal(SIGTERM, server_manager::signalHandler);

}

server_manager::server_manager(int port, logs *log, bool daemon) {
    this->log = log;
    this->make_server(port, daemon);
};

bool server_manager::make_server(int port, bool daemon) {
    if (daemon)
        daemonize();
    else
        signal(SIGINT, server_manager::signalHandler);
    char port_str[128];
    sprintf(port_str, "Starting server at port: %i", port);
    log->message(port_str, INFO);
    server = new sockets_http(port, log);

}

void server_manager::signalHandler(int sig) //replace case with separate handlers
{
    logs *log = logs::get_instance();
    switch (sig) {
        case SIGHUP:
            log->message("HUP handling not implemented.", INFO);
            break;
        case SIGINT:
        case SIGTERM:
            log->message("Term signal catched.", INFO);
            log->message("Cleaning up server...", INFO);
            log->message("Bye", INFO);
            exit(0);
            break;
    }
}
