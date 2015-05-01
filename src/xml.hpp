//Odpowiedzi

#include <string>
#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <vector>
#include <cstdlib>



// Dla katalogow:

#define xml_dir_list "\n<directories number=\"%i\">\n%s</directories>\n"
#define xml_dir_item "<item type=\"%s\" name=\"%s\">%s</item>\n" 

// Dla playlist:

#define xml_playlist_list "<playlist name=\"%s\" count=\"%s\">%s</playlist>"
#define xml_playlist_track "<track>%s</track>"

//Dla info. o utworze:

#define xml_current_track "<path>%s</path><filename>%s</filename><tags>%s</tags>"

#define XML_RESPONSE "<response>\n<code>%s</code>\n<content>%s</content>\n</response>"
#define xml_server_version_info "<version><program>0.1 Early development</program><protocol>1</protocol></version>"

#define RESPONSE_DIRLIST "DIR"
#define RESPONSE_PLAYLIST "PLAYLIST"
#define RESPONSE_CURRENT "CURRENT"
#define ERROR_PLAYLIST "PLAYLERR"
#define ERROR_DIR "DIRERR"

//Inne

#define RESPONSE_UNKNOWN "UNKNOWN"

//Zapytania

#define xml_request "<request>\n<code>%s</code>\n<content>%s</content>\n</request>"
#define xml_client_version_info "<client><name>%s</name><protocol>%s</protocol></client>"
#define xml_login_data "<username>%s</username><password>%s</password>"

#define REQUEST_PLAY "PLAY"

#include "playlist.hpp"

using namespace std;
using boost::format;




string make_enties(string &xml);
string make_xml_playlist(playlist_type &playlist);
string make_xml_trackinfo(string &track); //potem to zmienie