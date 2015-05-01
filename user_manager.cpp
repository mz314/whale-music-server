#include "user_manager.h"


/*   user_manager */

user_manager *user_manager::me=0;

user_manager::user_manager()
{
 log=logs::get_instance();

}


user_stateptr user_manager::search_user(string &username,string &password)
{
 user_stateptr i;
 i=users.begin();
 while(i!=users.end())
 {
   user_state *ii;
   ii=*i;
   if (ii->get_username()==username && ii->get_password()==password)
    return i;
   i++;
 }
 return users.end();
}

user_state * user_manager::log_user(string username,string password)
{
  string msg="Trying to log user: ";
  log->message(msg+username,INFO);
  user_stateptr i=search_user(username,password);
  if (i==users.end())
  {
    log->message("Creatin'...",SUPADEBUG);
    user_state *user=new user_state(username.c_str(),password.c_str());
    users.push_back(user);
    return user;
  }
  else
  {
    log->message("Already logged",SUPADEBUG);
    return *i;
  }
}

void user_manager::enqueue(string fn)
{
 string msg="File: "+fn+" enqueued.";
 log->message(msg,DEBUG);
 //transistional
 track trk;
 trk.path=fn;
 playlist.push_back(trk);
}

bool user_manager::logout_user(user_state *user)
{
  user_stateptr i=find(users.begin(),users.end(),user);
  if (i!=users.end())
  { users.erase(i);
    return true; 
  }
  else 
    return false;
}



user_manager *user_manager::get_instance()
{
 if (!user_manager::me)
   user_manager::me=new user_manager();
 return user_manager::me;
}


playlist_type * user_manager::get_playlist()
{
 return &this->playlist;
}



/* user_manager END */

