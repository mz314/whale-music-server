#ifndef RESPONSEXML_HPP
#define	RESPONSEXML_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <boost/algorithm/string/replace.hpp>

using namespace std;
using boost::property_tree::ptree;

typedef   map<string, string> reqParams;




class responseXML {
public:
    responseXML();
    void test();
    responseXML(const char * code,reqParams request);
    void setCode(string code);
    void content(string content);
    void addContent(ptree cont,const string &name);
    void userRequest(reqParams request);
    void setJson(bool json);
    void appendXSL(string name);
    bool isJson();
     ptree tree;
    void generate();
    void add(string loc,string data);
    ptree * getTree();
    operator  string();
    operator const char *();
protected:
    basic_stringbuf<char>  * sb;
    bool generated;
    string str,contentd,xsl,prepend_xml;
    stringstream data;
    reqParams request;
    string code,version;
   
    bool json;
};

#endif	

