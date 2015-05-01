#ifndef WENGINE_H
#define WENGINE_H


#include <iostream>
#include <string>
#include <vector>



extern "C" {
// #include <alsa/asoundlib.h>
};

#include "logs.h"
#include "protocol.h"
#include "user_state.hpp"

#include "gstreamer_io.hpp"

using namespace std;









class user_manager
{
  private:
    vector<user_state *> users;
    playlist_type playlist; //No nie wiem...
    user_manager();
    user_manager(const user_manager &x)
    {
    }
    static user_manager *me;
    void *state_data;
    size_t data_size;
    user_stateptr search_user(string &username,string &password);
    logs *log;
  public:
    static user_manager * get_instance();
    void enqueue(string fn);
    user_state * log_user(string username,string password);
    bool logout_user(user_state *user);
    playlist_type *get_playlist();
    ~user_manager();
    
    
};




#endif
