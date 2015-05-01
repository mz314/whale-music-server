#include "database.hpp"

int database::select_callback(void *data, int argc, char **argv, char **azColName) {
    
}

database::database(const string & dbfile) : dbfile(dbfile) {
    
}

void database::select(const string & table,const string &collumn,const string &condition) {
   string sql = "select "+collumn+" from "+table;
   if(condition!="") {
       sql+=" where "+condition;
   }
   char *err=0;
   
   /* Execute SQL statement */
   int rc = sqlite3_exec(db, sql.c_str(), database::select_callback, (void*)this, &err);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", err);
      sqlite3_free(err);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }   
}

void database::dbOpen() {
     int rc = sqlite3_open("test.db", &db);
     if(rc) {
         string message=sqlite3_errmsg(db);
         throw(message);
     }
}

void database::dbClose() {
    if(db) {
        sqlite3_close(db);
    }
}

database::~database() {
 dbClose();   
}