#include "gstreamer_io.hpp"


playlist_type p;

gstreamer_io *gstreamer_io::me=0;
GMainLoop *gstreamer_io::loop=0;
GstElement *gstreamer_io::pipeline=0;
GstBus *gstreamer_io::bus=0;
bool gstreamer_io::exit=false;
playlist_type *gstreamer_io::playlist=0;
string gstreamer_io::current="none";
playlist_iterator gstreamer_io::current_i=p.begin();
int gstreamer_io::n=0;


gstreamer_io * gstreamer_io::get_instance()
{
 if (me==NULL)
  me=new gstreamer_io();
 return me;
  
}


string & gstreamer_io::get_current()
{
 return gstreamer_io::current;
}


bool gstreamer_io::is_loaded()
{
  GstState state; 
  gst_element_get_state(GST_ELEMENT(pipeline),&state,NULL,GST_CLOCK_TIME_NONE);
  if (state==GST_STATE_PLAYING || state==GST_STATE_PAUSED)
    return true; else return false;

  
}

gstreamer_io::gstreamer_io()
{
 gst_init(NULL, NULL);
 loop = g_main_loop_new(NULL, FALSE); 
  pipeline = gst_element_factory_make("playbin", "player"); //WARNING
 this->exit=false;
}

gboolean gstreamer_io::bus_call(GstBus *bus, GstMessage *msg, void *user_data)
{
 switch (GST_MESSAGE_TYPE(msg))
 {
 case GST_MESSAGE_EOS: 
   {
    g_message("End-of-stream"); //WARNING: Moze uzyc tego zamiast logow?
    g_main_loop_quit(loop);
    break;
   } //case
 case GST_MESSAGE_ERROR: 
   {
    GError *err;
    gst_message_parse_error(msg, &err, NULL);
    g_error("%s", err->message);
    g_error_free(err);
    g_main_loop_quit(loop);
    break;
  }
 }
  
}

void gstreamer_io::playing_loop()
{
  
  playlist_iterator i;
  i=playlist->begin();
  n=0;
  
  while (playlist->begin()+n!=playlist->end() && !exit)
  {
   string fn;
   i=playlist->begin()+n; //WARNING: trochę prowizoryczne obejscie problemow z watkami :/
   current=i->path;
   current_i=i;
   fn="file://"+current;
   g_object_set(G_OBJECT(pipeline), "uri", fn.c_str(), NULL);
   bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
   gst_bus_add_watch(bus, bus_call, NULL);
   gst_object_unref(bus);
   gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
   g_main_loop_run(loop);
   gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
   n++;
  }
 
}

void gstreamer_io::stop_playback()
{
  //gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
  //gst_object_unref(GST_OBJECT(pipeline));
  g_main_loop_quit(loop);
  exit=true;
}

void gstreamer_io::play()
{
  exit=false;
  boost::thread(boost::ref(gstreamer_io::playing_loop));
}

void gstreamer_io::next_track()
{
 g_main_loop_quit(loop);
}

void gstreamer_io::prev_track()
{
 n-=2; 
 g_main_loop_quit(loop);
}

void gstreamer_io::set_playlist(playlist_type *p)
{
 playlist=p;
}
