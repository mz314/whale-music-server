#ifndef HTTPREQUEST_HPP
#define	HTTPREQUEST_HPP

#include <string>
#include <map>

using namespace std;

class HttpRequest {
protected:
    string request_body;
    void parseRequest();
    static map<string, string> parseParams(string params);
public:
    HttpRequest(string request_body);
    static string replaceEntities(string str);
};

#endif	

