
#ifndef FILEUTILS_HPP
#define	FILEUTILS_HPP

#include <string>

#include <dirent.h>
#include <sys/types.h>

using namespace std;

class fileUtils {
public:
    fileUtils();
    static bool isDir(string file);
    ~fileUtils();
private:

};

#endif	/* FILEUTILS_HPP */

