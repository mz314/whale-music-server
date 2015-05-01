#ifndef WHALE_GSTREAMER
#define WHALE_GSTREAMER


#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <gst/gst.h>

#include <iostream>
#include <string>


#include "playlist.hpp"

using namespace std;
using boost::asio::ip::tcp;



enum playback_state
{
 PLAYBACK_IDLE=0,
 PLAYBACK_PLAY=1,
 PLAYBACK_PLAYING=2,
 PLAYBACK_STOP=3,
 PLAYBACK_PAUSE=4
};

class gstreamer_io //singleton
{
 private:
   static GMainLoop *loop;
   static GstElement *pipeline;
   static playlist_type *playlist;
   static GstBus *bus;
   gstreamer_io();
   static gstreamer_io *me;
   playback_state state;
   static void playing_loop();
   static gboolean bus_call(GstBus *bus, GstMessage *msg, void *user_data);
   static bool exit;
   static string current; 
   static playlist_iterator current_i;
   static int n;
 public:
   static gstreamer_io * get_instance(); //WARNING: To nie musi byc singleton wlasciwie. (?)
   static string & get_current();
   static void set_playlist(playlist_type *p);
   static void play();
   static bool is_loaded(); //Sprawdza, czy jakis plik jest odtwarzany lub zpalzowany
   static void stop_playback();
   static void next_track();
   static void prev_track();
  
};

#endif