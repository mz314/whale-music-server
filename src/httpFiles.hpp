#ifndef HTTPFILES_HPP
#define	HTTPFILES_HPP

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <map>

#include "fileUtils.hpp"

using namespace std;


class httpFile {
protected:
    FILE *f;
    string fn,ext;
    char *bytes;
    size_t size;
    static map<string,string> mimes;
public:
    static void initMime();
    httpFile(string fn);
    void list();
    string getMime(); 
    char * readFile();
    ~httpFile(); 
};

#endif	/* HTTPFILES_HPP */

