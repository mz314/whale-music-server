#include "user_state.hpp"

string user_state::resolve_dir(string &path) {
    string resolved = "";
    size_t pos = 0, pos2;
    string wanted = "/../";
    resolved = path;
    if (path == wanted)
        return "/"; //podobnie jak poniższe
    while (pos != string::npos && pos + wanted.length() < resolved.length()) //drugi warunek to prowizorka na wypadek prośby przejścia do  /..
    {
        pos = resolved.find(wanted);
        if (pos != string::npos) {
            pos2 = resolved.find_last_of("/", pos - 1);
            if (pos2 != string::npos)
                resolved.replace(pos2, pos + wanted.length(), "/");
        }
    }
    return resolved;
}


void user_state::setResponse(responseXML *response) {
 this->response=response;    
}

user_state::user_state(const char *username, const char *password) {
    this->response=response;
    this->username = username;
    this->password = password;
    this->path = "/home/maciek/"; //WARNING!!!
    //this->dir(path);
    log = logs::get_instance();
    log->message("LOGGED", INFO);
}

string user_state::get_working_dir() {
    return "/home/maciek/mp3/";
}

string & user_state::get_username() {
    return this->username;
}

string & user_state::get_password() {
    return this->password;
}

static int one(const struct dirent *unused) {
    return 1;
}



bool user_state::dir(const string & path,responseXML *resp) {
    
    //log->message("test");
   //return NULL;
    //log->message(path);
    DIR *dp;
    struct dirent **e, *de;
    int n;
   
    //string wd = this->get_working_dir();
    //chdir(wd.c_str());
    //path = resolve_dir(path);
   
    n = scandir(path.c_str(), &e, one, alphasort);
    
    if (n == -1) return false;
    
    dirEntity *ents=new dirEntity[n];
     ptree nd,dirn,itm;
     //dir.put("directory");
    
    string pt="response.content.directory";
    
    
     for (int i = 0; i < n; i++) {
        string item;
        string name;
        int is_file = 0;
        //DIR *dir = 0;
        string p = path + "/" + e[i]->d_name;
        //dir = opendir(p.c_str());
        if (fileUtils::isDir(p))
            is_file = 0;
        else
            is_file = 1;
        name = e[i]->d_name;
        
        nd.put("path",p);
        nd.put("file",is_file);
        nd.put("name",name);
        //itm.add_child("item",nd);
        if(resp->isJson()) {
        dirn.push_back(make_pair("",nd));
        } else {
            dirn.add_child("item",nd);
        }
        //dirn.push_back(make_pair("",itm));
        //dirn.add_child("directory",nd);
       
        //cout << name << endl;
        ents[i].is_file=is_file;
        ents[i].name=name;
        ents[i].path=p;
        //cout << name << endl;
    }
    resp->tree.add("response.content.dir_items",n);
    resp->tree.add_child("response.content.directory",dirn);
    //dirListing * dl=new dirListing(ents);
    return true;
}

//string user_state::dir(string path) {
//    DIR *dp;
//    struct dirent **e, *de;
//    int n;
//    dir_data *ddata = new dir_data;
//    string wd = this->get_working_dir();
//    chdir(wd.c_str());
//    path = resolve_dir(path);
//    n = scandir(path.c_str(), &e, one, alphasort);
//    string result;
//    result = str(format(xml_dir_list) % n % "%s");
//    if (n == 0) return "";
//    for (int i = 0; i < n; i++) {
//        string item;
//        string name;
//        int is_file = 0;
//        DIR *dir = 0;
//        string p = path + e[i]->d_name;
//        dir = opendir(p.c_str());
//        if (dir == NULL)
//            is_file = 1;
//        else
//            is_file = 0;
//        name = p;
//        item = str(format(xml_dir_item) % is_file % (e[i]->d_name) % (name));
//        if (i < n - 1) item += "%s";
//        result = str(format(result) % item);
//        closedir(dir);
//    }
//    result = make_enties(result);
//    return result;
//}




//// Dir listing ////

dirListing::dirListing(dirEntity *entities) {
    this->entities = entities;
}

dirListing::~dirListing() {
    if (this->entities) {
        delete this->entities;
    }
}