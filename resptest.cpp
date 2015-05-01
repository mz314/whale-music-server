#include <iostream>
#include "responseXML.hpp" 
#include "user_manager.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <string>
#include <map>

using namespace std;
using boost::property_tree::ptree;

using namespace std;

int main() { 
    reqParams rp;
    user_manager *manager=user_manager::get_instance();
    user_state *user=manager->log_user("x","x");
    cout << "Response test" << endl; 
    responseXML resp("0",rp);
    user->dir("/home/maciek",&resp);
     stringstream data;
    write_xml(data,*(resp.getTree()));
    cout << data.rdbuf();
}
