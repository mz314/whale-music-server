/*
 Whale Music Daemon - draft version

 */


#include <iostream>
#include <string>
#include <cstdlib>



#include "musicserver.h"


#include "sockets.h"

#include "server_manager.h"

using namespace std;

params * parse_params(int argc, char **argv) //Chujowe... Może Bison++ ??
{
    params *ptr;
    string sw;
    ptr = new params;
    ptr->daemon = true;
    ptr->port = 6667;
    ptr->log_type=STDOUT;
    if (argc > 1) {

        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') { //switch
                sw = argv[i];
              
                if (sw == "-ND")
                    ptr->daemon = false;


            } else { //port
                ptr->port = atoi(argv[i]);
            }
        }


    }
 
    return ptr;
}

int main(int argc, char **argv) {
    params *prms = parse_params(argc, argv);
    int port;

    logs *log = logs::get_instance();
    server_manager server(prms->port, log, prms->daemon);


}