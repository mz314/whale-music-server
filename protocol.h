

#ifndef PROTOCOL_H
#define PROTOCOL_H

#define HANDSHAKE_Q "DIG?"
#define HANDSHAKE_A "DIG!"

#define STRING_SIZE 512 //To marnotwarwstwo na dłuższą metę.


#include "stdlib.h"

typedef char string_data[STRING_SIZE];
typedef unsigned int size_data; 
typedef unsigned char byte_data;






typedef struct
{
 byte_data is_file;
 char *name;
} dir_item;

typedef struct 
{
 size_data n;
 dir_item *items;
} dir_data ;

typedef enum 
{
 PLAY=1,
 STOP=2,
 PAUSE=3,
 FORWARD=4,
 REWIND=5,
 TRACK_FORWARD=6,
 TRACK_REWIND=7,
 UPDATE_DB=8,
 LIST_DIR=9,
 LOG=10,
 LOGOUT=11,
 ENQUEUE=12, //czemy nie wpadłem na to wcześniej ?!
 GET_PLAYLIST=13,
 GET_CURRENT=14,
 START_PLAYLIST=15, //uruchamia playliste
 BYE=100 //wylogowanie i zapisanie danych
} request_type;


typedef enum //TODO: Wprowadzić to w życie!!!
{
 OK=1,
 ERROR=2,
 DENIED=3
} return_code;



struct request
{
 request_type type;
 unsigned char incoming_string;
};

#endif
