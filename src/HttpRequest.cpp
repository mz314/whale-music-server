#include "HttpRequest.hpp"

HttpRequest::HttpRequest(string request_body) : request_body(request_body) {
    
}

map<string, string> HttpRequest::parseParams(string params) {
    map<string, string> results;
    string content = params;
    boost::replace_all(content, " ", "");
    boost::replace_all(content, "%20", " ");
    int p = 0, startp = 0, endp = 0;
    //cout << req.data << endl;
    do {
        p = content.find("=", p + 1);
        endp = content.find('&', endp + 1);
        string param = content.substr(startp, p - startp),
                val = content.substr(p + 1, endp - p - 1);
        //cout << "p: "<< param << ", v: " << val << endl;
        results.insert(make_pair(param, val));
        p = endp;
        startp = endp + 1;
    } while (p != string::npos);


    return results;
}
 
void HttpRequest::parseRequest() {
    
}