#ifndef MS_PLUGINS_H
#define MS_PLUGINS_H


#include <string>
#include <vector>
#include <map>

#include <dlfcn.h>
#include <dirent.h>
#include <sys/types.h>
#include <cstring>

#include "logs.h"

using namespace std;




enum plugin_type
{
 PLUGIN_OUTPUT,
 PLUGIN_INPUT,
 PLUGIN_GENERAL,
 PLUGIN_OTHER,
};


class plugin
{
  protected:
    plugin_type type;
    string id; //jedyny sposób na jednoznaczną identyfikację
    void *handle; //zdecydowanie nie przenośne
  public:
    virtual void *get_handle();
    virtual void set_handle(void *);
    virtual string & get_id();
    virtual plugin_type get_type();
    
};


typedef plugin* (*create_plugin)();
typedef void (*destroy_plugin)(plugin *);


class loader //class for loading output and input plugins
{
  private:
    static loader *instance;
    logs *log;
    vector<plugin *> plugins; 
    map<plugin *,void *> plugin_handle;
    loader();
    loader(const loader &x)
    {
    }
  public:
    static loader *get_instance();
    int look_around(string dir); //katalog względny!!! zwraca ile załadował
    string find_id(string dir,string id); //zwraca plik o określonym id
    plugin *get_plugin(string id,plugin_type type); //zwraca plugin jeżeli został załadowany
    size_t get_plugins_by_type(vector <plugin *> *list,plugin_type type);
    bool load_plugin(string fn); //katalog względny/nazwa pliku
    int load_all(string dir); 
    ~loader();
    
};


#endif