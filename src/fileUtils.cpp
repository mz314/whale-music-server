

#include "fileUtils.hpp"

fileUtils::fileUtils() {
}

bool fileUtils::isDir(string file) {
    DIR *dir = opendir(file.c_str());
    bool isdir;
    if (dir == NULL)
        isdir = false;
    else
        isdir = true;
    closedir(dir);
    return isdir;
}

fileUtils::~fileUtils() {
}

