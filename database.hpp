#ifndef WHALE_DATABASE_H
#define WHALE_DATABASE_H

#include <cstdio>
#include <string>
#include <sqlite3.h>

using namespace std;

class database {
protected:
     sqlite3 *db;
     int handle;
     string dbfile;
    static int select_callback(void *data, int argc, char **argv, char **azColName);
public:
    database(const string & dbfile="db.sql");
    void dbOpen();
    void dbClose();
    void select(const string & table,const string &collumn,const string &condition="");
    ~database();  
};


#endif

//test
