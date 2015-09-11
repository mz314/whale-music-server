#include "plugins.h"

loader *loader::instance=0;

loader *loader::get_instance()
{
 if (loader::instance==0)
   loader::instance=new loader;
 return loader::instance;
}

static int one (const struct dirent *unused)
{
       return 1;
}


loader::loader()
{
 log=logs::get_instance();
}

int loader::look_around(string dir)
{
 struct dirent **e;
 destroy_plugin destroy;
 create_plugin create;
 void *handle;
 int count=0;
 int n=scandir (dir.c_str(), &e, one, alphasort);
 if (n>=0)
 {
  for (int i=0; i<n; i++)
  {
   if (strcmp(e[i]->d_name,"..")==0 || strcmp(e[i]->d_name,".")==0)
     continue;
   string fn;
   fn=dir+"/"+e[i]->d_name;
   log->message("Trying to load plugin: "+fn,DEBUG);
   
   handle=dlopen(fn.c_str(),RTLD_LAZY);
   if (!handle)
   {
    log->message("Plugin loading error!",DEBUG);
    cout << dlerror() << endl;
    continue;
   }
   create=(create_plugin)dlsym(handle,"create");
   destroy=(destroy_plugin)dlsym(handle,"destroy");
   if (!create || !destroy)
   {
    log->message("Plugin is messy!",DEBUG);
    continue;
   }
   plugin *p=create();
   p->set_handle(handle); //WARNING: Nie usuwać!
   if (p)
   { 
     log->message("Loaded plugin: " + p->get_id(),INFO);
     plugins.push_back(p); 
     plugin_handle.insert(pair<plugin *,void *>(p,handle));
     count++;
   }
   else
     log->message("Weird...",DEBUG);
   
   
  }
 }
 return count;
}

plugin * loader::get_plugin(string id,plugin_type type)
{
 vector<plugin *>::iterator i;
 plugin *p;
 i=plugins.begin();
 while(i!=plugins.end())
 {
   p=*i;
   string gid=p->get_id();
   plugin_type t=p->get_type();
   if (id==gid && t==type)
   {
     i=plugins.begin();
     break;
   }
   i++;
 }
 if (i==plugins.end() && i!=plugins.begin())
 {cout << "NO!\n"; return NULL;}
 else return p;
}

size_t loader::get_plugins_by_type(vector <plugin *> *list,plugin_type type)
{
 vector <plugin *>::iterator i=plugins.begin();
 size_t c=0;
 do
 {
   plugin *p=*i;
   if (p->get_type()==type)
   {list->push_back(p); c++; }
   i++;
 }while(i!=plugins.end());
 return c;
}

loader::~loader()
{
 vector<plugin *>::iterator i;
 plugin *p;
 void *handle;
 destroy_plugin destroy;
 i=plugins.begin();
 while(i!=plugins.end())
 {
   p=*i;
   handle=p->get_handle();
   destroy=(destroy_plugin)dlsym(handle,"destroy");
   destroy(p);
   i++;
 }
  
}

// PLUGIN ABSTRACT CLASS //

void * plugin::get_handle()
{
 return this->handle;
}

void plugin::set_handle(void *handle)
{
 this->handle=handle;
}


string & plugin::get_id()
{
  return this->id;
}
    
plugin_type plugin::get_type()
{
 return this->type;
}
// PLUGIN END //