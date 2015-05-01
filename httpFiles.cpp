#include "httpFiles.hpp"

map<string,string> httpFile::mimes;

void httpFile::initMime() {
    FILE *f=fopen("mime","rb");
    char *bytes;
    char ext[3],mime[25];
    while(!feof(f)) {
    fscanf(f,"%s %s",ext,mime);
    mimes[ext]=mime;
    }
    fclose(f);
}

string httpFile::getMime() {
    if (mimes.find(ext)!=mimes.end()) {
        return mimes[ext];
    } else {
        return "application/octet-stream";
    }
}

httpFile::httpFile(string fn) : fn(fn) , size(0) {
    this->f = fopen(this->fn.c_str(), "rb");
    
    if (!this->f || fileUtils::isDir(fn)) {
        throw string(this->fn);
        return;
    }
    size_t dotpos=fn.find_last_of(".");
    ext=fn.substr(dotpos+1,fn.size()-1);
}

void httpFile::list() {
    cout << size;
    
    string bs(bytes);
    bs+="\0";
    cout << bs;
    cout.flush();
}

char * httpFile::readFile() {
    fseek(f, 0L, SEEK_END);
    size = ftell(f);
    fseek(f,0,SEEK_SET);
    bytes=(char *)calloc(size,size);
    fread(bytes,1,size,f);
    return bytes;
}

httpFile::~httpFile() {
    if(bytes) {
        free(bytes);
    }
    if (this->f) {
        fclose(this->f);
    }
}

