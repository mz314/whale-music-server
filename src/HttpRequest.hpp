#ifndef HTTPREQUEST_HPP
#define	HTTPREQUEST_HPP

#include <gtest/gtest.h>
#include <string>
#include <map>

using namespace std;

class HttpRequest {
protected:
    FRIEND_TEST(HttpRequest, HttpRequestTest);
    string request_body;
    void parseRequest();
    static map<string, string> parseParams(string params);
public:
    HttpRequest(string request_body);
    static string replaceEntities(string str);
};

#endif	

