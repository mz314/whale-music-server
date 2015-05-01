/*

Header for C socket abstraction layer for sake of protability and comfort ;)

*/

#ifndef SOCKETABSTRACT_H
#define SOCKETABSTRACT_H


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>


#include "../protocol.h"

#define WHALE_SUCCESS 1
#define WHALE_ERROR_SOCKET -1
#define WHALE_ERROR_NOHOST -2
#define WHALE_ERROR_NOCONNECT -3
#define WHALE_ERROR_NOHANDSHAKE -4
#define WHALE_ERROR_NOLOGIN -5
#define WHALE_ERROR_UNKNOWN -100


typedef int sock_type;
typedef size_t size_type;
typedef void *buff_type;



sock_type sock_make();
sock_type sock_connect(sock_type sock,char *host,int port);
sock_type sock_disconnect(sock_type sock);
size_type sock_read(sock_type sock,buff_type buff,size_data size);
size_type sock_write(sock_type sock,buff_type buff,size_data size);



#endif