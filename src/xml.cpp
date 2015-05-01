#include "xml.hpp"

string make_enties(string &xml)
{
 boost::regex exp("&");
 string fmt("&amp;"),ret;
 ret=boost::regex_replace(xml,exp,fmt);
 return ret;
}


string make_xml_playlist(playlist_type &playlist) //TODO: tak samo zrobić z playlista
{
  
  playlist_type::iterator i;
  string result;
  int count=playlist.size();
  char scount[256];
  sprintf(scount,"%i",count);
  string content=str(format(xml_playlist_list) % "playlist" % scount % "%s" );
  //result=str(format(xml_response) % );
  i=playlist.begin();
  while(i!=playlist.end())
  {
   string track;
   track=str(format(xml_playlist_track) % i->path);
   track+="%s";
   content=str(format (content) % track);
   
   i++;
  }
 return content;
}

string make_xml_trackinfo(string &track)
{
 string content;
 content=str(format(xml_current_track) % track % "" % "");
 return content;
}