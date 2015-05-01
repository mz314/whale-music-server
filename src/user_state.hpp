#ifndef WHALE_USERSTATE_H
#define WHALE_USERSTATE_H


#include <vector>

#include <dirent.h>
#include <sys/types.h>
#include <cstring>
#include <boost/format.hpp>





#include "logs.h"
#include "protocol.h"
#include "xml.hpp"
#include "responseXML.hpp"
#include "fileUtils.hpp"


using namespace std;
using boost::format;
using boost::str;

struct dirEntity {
    string name, path;
    bool is_file;
};

class dirListing {
protected:
    dirEntity *entities;
public:
    dirListing(dirEntity *entities);
    ~dirListing();
};

class user_state {
private:
    string username, password;
    string path;
    int rank; //<--
    logs *log;
    //heavy_task dirtask; //nie wiem, co z tym zrobić...
    static void * dir_callback(void *args, size_t size, bool *abort);
    responseXML * response;
    static string resolve_dir(string &path); //może być zależne od platformy w przyszłości. dobre unieszkodliwianie złośliwych zapytań.
public:
    void setResponse(responseXML *response); //TODO: find other solution
    user_state(const char *, const char *);
    string & get_username();
    string & get_password();
    bool log_user(string &username, string &password);
    bool dir(const string & path,responseXML *resp);
    //string dir(string path);
    string get_working_dir();

    void play_file(string fn); //??
    bool save_state();
    int move_time(int amount); //negative for backward
    int change_track(int amount); //negative for previous
    bool set_playlist(); //TODO:*/
};


typedef vector <user_state *>::iterator user_stateptr;

#endif