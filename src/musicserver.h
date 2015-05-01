#ifndef MUSICSERVER_H
#define MUSICSERVER_H

#include <string>


// #include "logs.h"

using namespace std;



#include "logs.h"

/*class whale_engine  
{
  public:
    static whale_engine* get_instance();
    bool log_user(string &username,string &password);
    bool play_song(string path);
    int move_time(int amount); //negative for backward
    int change_track(int amount); //negative for previous
    bool set_playlist(); //TODO:
    //void operator()();
  private:
    static whale_engine * instance;
    string username;
    static logs *log;
    //whale_engine(const whale_engine &);
    //void operator=(const whale_engine &);
    whale_engine()
    {
    }
    

};
*/





struct params
{
 int port;
 bool daemon;
 output_type log_type;
};


#endif