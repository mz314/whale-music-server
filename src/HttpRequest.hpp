#ifndef HTTPREQUEST_HPP
#define	HTTPREQUEST_HPP

#include <string>

using namespace std;

class HttpRequest {
protected:
    string request_body;
    reqParams parseRequest();
    static void parseParams(string params);
public:
    HttpRequest(string request_body);
    static string replaceEntities(string str);
};

#endif	

