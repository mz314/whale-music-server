#include "responseXML.hpp"

responseXML::responseXML() {
    version = "0.7";
    generated = false;
}

responseXML::responseXML(const char * code, reqParams request) {
    setCode(code);
    userRequest(request);
    this->json = false;
    content("");
    generated = false;
    prepend_xml="";
}

void responseXML::content(string content) {
    this->contentd = content;
}

void responseXML::setJson(bool json) {
    this->json = json;
}

void responseXML::setCode(string code) {
    this->code = code;

}

void responseXML::addContent(ptree cont,const string &name) {
    string s="response.content.";
    s+=name;
    tree.add_child(s,cont);
}

void responseXML::userRequest(reqParams request) {
    this->request = request;
    // tree.add("response.request",request);
}

void responseXML::add(string loc, string data) {
    tree.add(loc, data);
    generate();
}

bool responseXML::isJson() {
    return this->json;
}

void responseXML::test() {
    stringstream ss;
    //  tree.put("response.code","test");
    write_xml(ss, tree);

    cout << ss.rdbuf();
}

ptree * responseXML::getTree() {
    return &this->tree;
}

void responseXML::appendXSL(string name) {
    xsl=name;
}

void responseXML::generate() {
    if (generated)
        return;
    generated = true;
    tree.add("response.code", code);
    if (contentd != "") {
        tree.add("response.content", contentd);
    }
    //tree.put("response.request",request);
    if (json) {
        write_json(data, tree);
    } else {
        write_xml(data, tree);
    }

    sb = data.rdbuf();
    str = sb->str();
    if (!json && xsl!="") {
        xsl="<?xml version=\"1.0\" encoding=\"utf-8\"?><?xml-stylesheet type=\"text/xsl\" href=\""+xsl+"\"?>";
        boost::replace_all(str, "<?xml version=\"1.0\" encoding=\"utf-8\"?>", 
                xsl);
    }
}

responseXML::operator string() {

    generate();
    return str;
}

responseXML::operator const char *() {
    generate();
    return str.c_str();
}