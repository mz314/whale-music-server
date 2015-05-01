#ifndef WHALE_LIB_H
#define WHALE_LIB_H


#include "../protocol.h"

#include "sockabstract.h"


sock_type whale_connect(char *host,int port);
int whale_log_user(sock_type,char *username,char *password);
int whale_logout(sock_type sock);
int whale_disconnect(sock_type sock);
int whale_play_file(sock_type sock,char *filename);
int whale_enqueue_file(sock_type sock,char *filename);
int whale_next_file(sock_type sock,int n); //n = ile w przód, nie wiem, czy tego użyje
int whale_prev_file(sock_type sock,int n); //n = ile w tył
int stop_playback(sock_type sock);
int pause_playback(sock_type sock);
char * whale_get_playlist(sock_type sock); //na raze jeden parametr
char * whale_get_current(sock_type sock);
char * whale_get_dir(sock_type sock,char *path);
void whale_dispose_dir_data(dir_data *dir);
size_type get_data(sock_type sock,void *data);
int send_data(sock_type sock,void *data,size_data size);

//na później:

// void send_request()
// get_response;

//size_data whale_get_dir_contents();


#endif
