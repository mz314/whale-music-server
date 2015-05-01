#include "logs.h"



logs *logs::me = 0;

logs::logs() {
    this->set_debug(true);
    setLogFile("daemon.log");
    setOut(STDOUT);
    
}

logs::~logs() {
    //
}

void setLogFile(string logfile) {
    
}

void logs::message(string msg, log_type type, string subsystem) {
    string type_str, subsystem_str;
    switch (type) {
        case DEBUG: type_str = "DEBUG: ";
            break;
        case INFO: type_str = "INFO: ";
            break;
        case WARNING: type_str = "WARNING: ";
            break;
        case SUPADEBUG: type_str = "SUPADEBUG: ";
            break;
    }
    //if (type==DEBUG && this->debug==false) //Obsluda wiadomosci debugowania
    //return;
    if (subsystem != "")
        subsystem_str = "SUBSYSTEM: " + subsystem + ": ";
    else
        subsystem_str = "";
    string message = type_str + subsystem_str + msg + "\n";
    output(message);
    //cout << 
}

void logs::set_debug(bool debug) {
    this->debug = debug;
}

void logs::setOut(output_type ot) {
    this->ot = ot;
}

void logs::output(string o) {
    switch (this->ot) {
        case STDOUT:
        {
            cout << o;
            break;
        }
        case SYSLOG:
        {
            setlogmask(LOG_UPTO(LOG_NOTICE));
            openlog("Music Daemon", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
            syslog(LOG_NOTICE, o.c_str());
            closelog();
            break;
        }
        case LOGFILE:
        {
          //  cout << logfile;
           FILE *f=fopen(logfile.c_str(),"w+");
          fprintf(f,o.c_str());
          fclose(f);
        }
    }
}


 void logs::setLogFile(string logfile) {
     this->logfile=logfile;
 }