/*
* Whale Music Daemon lib
*
*
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include "whalelib.h"

sock_type whale_connect(char *host,int port)
{
 sock_type sock;
 sock=sock_make();
 sock=sock_connect(sock,host,port);
}  

int send_data(sock_type sock,void *data,size_data size)
{
 
}

int whale_log_user(int sock,char *username,char *password)
{
 //Handshake
 char buffer[10];
 string_data user_buff,pass_buff;
 int size_answer=strlen(HANDSHAKE_A)+1,wrote,size;
 sock_read(sock,buffer,strlen(HANDSHAKE_Q)+1);
 if(strcmp(buffer,HANDSHAKE_Q)!=0)
   return WHALE_ERROR_NOHANDSHAKE;
 strcpy(buffer,HANDSHAKE_A);
 wrote=sock_write(sock,buffer,size_answer);
 if (wrote!=size_answer)
   return WHALE_ERROR_NOHANDSHAKE;
 //Log in
 struct request req;
 req.type=LOG;
 req.incoming_string=1;
 strcpy(user_buff,username);
 strcpy(pass_buff,password);
 sock_write(sock,&req,sizeof(req));
 wrote=sock_write(sock,user_buff,STRING_SIZE);
 if (wrote!=STRING_SIZE)
   return WHALE_ERROR_UNKNOWN;
 wrote=sock_write(sock,pass_buff,STRING_SIZE);
 if (wrote!=STRING_SIZE)  
  return WHALE_ERROR_UNKNOWN;
 return WHALE_SUCCESS;
}

char * whale_get_playlist(sock_type sock)
{
  char *response;
  size_data size;
  struct request req;
  req.type=GET_PLAYLIST;
  req.incoming_string=1;
  sock_write(sock,(void *)&req,sizeof(req));
  sock_read(sock,&size,sizeof(size_data));
  response=malloc(size+1);
  response[size]=0;
  sock_read(sock,(void *)response,size);
  // printf(response);
  // fflush(stdout);
  return response;
 
  
}

char * whale_get_current(sock_type sock)
{
  char *response;
  size_data size;
  struct request req;
  req.type=GET_CURRENT;
  req.incoming_string=1;
  sock_write(sock,(void *)&req,sizeof(req));
  sock_read(sock,&size,sizeof(size_data));
  response=malloc(size+1);
  response[size]=0;
  sock_read(sock,(void *)response,size);
  return response;
}

char * whale_get_dir(sock_type sock,char *path) //tylko tego typu zapytania z uzyciem XML
{
 char *response;
 size_data size;
 struct request req;
 req.type=LIST_DIR;
 req.incoming_string=1;
 sock_write(sock,(void *)&req,sizeof(req));
 sock_write(sock,(void *)path,STRING_SIZE);
 sock_read(sock,&size,sizeof(size_data));
 response=malloc(size+1);
 response[size]=0;
 sock_read(sock,(void *)response,size);
 // printf(response);
 // fflush(stdout);
 return response;
}

int stop_playback(sock_type sock) {
    
}

int pause_playback(sock_type sock) {
    
}

void whale_dispose_dir_data(dir_data *dir)
{
 int i;
 if (!dir || !dir->items)
   return;
 for(i=0; i<dir->n; i++)
  free(dir->items[i].name);
 free(dir->items);
 free(dir);
 
}


int whale_play_file(sock_type sock,char *filename)
{
 struct request req;
 req.type=PLAY;
 req.incoming_string=1;
 sock_write(sock,(void *)&req,sizeof(req));
 sock_write(sock,(void *)filename,STRING_SIZE);
}

int whale_enqueue_file(sock_type sock,char *filename)
{
 struct request req;
 req.type=ENQUEUE;
 req.incoming_string=1;
 sock_write(sock,(void *)&req,sizeof(req));
 sock_write(sock,(void *)filename,STRING_SIZE);
}

size_type get_data(sock_type sock,void *data)
{
 size_data size;
 sock_read(sock,&size,sizeof(size_data));
 sock_read(sock,data,size);
}

int whale_logout(sock_type sock)
{
 struct request req;
 req.type=LOGOUT;
 req.incoming_string=0;
 size_type wrote=0;
 wrote=sock_write(sock,&req,sizeof(req));
 if (wrote!=sizeof(req))
   return WHALE_ERROR_UNKNOWN;
 return WHALE_SUCCESS;
}

int whale_next_file(sock_type sock,int n)
{
 struct request req;
 req.type=TRACK_FORWARD;
 req.incoming_string=0;
 sock_write(sock,&req,sizeof(req));
}

int whale_prev_file(sock_type sock,int n)
{
 struct request req;
 req.type=TRACK_REWIND;
 req.incoming_string=0;
 sock_write(sock,&req,sizeof(req));
}

int whale_disconnect(sock_type sock)
{
 sock_disconnect(sock);
 return WHALE_SUCCESS;
}