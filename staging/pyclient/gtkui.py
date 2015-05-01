import pygtk
import gtk
from libwhalebinds import *
import struct
from ctypes import *
from copy import *
from xml.etree.ElementTree import *
from xml.sax.saxutils import *

from settings import *

class window (object):
  def destroy(self, widget, data=None):
    pass
  def delete_event(self, widget, event, data=None):
    return False
  def gladefile(self):
    return "ui.glade"; #This will probably change to window name. Since all windows in the same file.
  def specific_init(self):
    #Window - specific initialisations
    pass
  def __init__(self):
    self.gtkbuilder=gtk.Builder();
    self.gtkbuilder.add_from_file(self.gladefile());
    self.gtkbuilder.connect_signals(self,None);
    self.specific_init()
  def __del__(self):
    pass
 

 

class main_window (window):
  def destroy(self, widget, data=None):
    whale_disconnect(self.socket)
    gtk.main_quit()
  def get_dir(self,path):
    dirdata=whale_get_dir(self.socket,path)
    print (dirdata)
    tree=fromstring(dirdata);
    for item in tree.getiterator("item"):
      self.files_model.append((item.attrib['name'],item.text,int(item.attrib['type'])));
  def about_close(self,x):
    self.about_win.hide()
  def about(self,x):
    self.about_win.show()
  
  def preferences_ok(self,x):
    print("OK");
    #self.new_settings.activate_enqueue=True;
    #self.settings=copy(self.new_settings)
    self.preferences_win.hide()
  
  def preferences_cancel(self,x):
    self.preferences_win.hide();
    print ("Yeah? Fuck you too!")
  
  def preferences_setcurrent(self):
    self.toggle_enq.set_active(self.settings.activate_enqueue)
  def preferences_setnew(self):
    self.new_settings.activate_enqueue=self.toggle_enq.get_active();
  
  def preferences(self,x):
    self.preferences_win.show()
    self.preferences_setcurrent()
  
  def prev(self,x):
   print ("Previous")
   whale_prev_file(self.socket,0)
  def next(self,x):
    whale_next_file(self.socket,0)
  
  def row_activated(self,treeview, path, viewcol, user_data=None):
    itr=self.files_model.get_iter(path)
    is_file=self.files_model.get_value(itr,2)
    name=self.files_model.get_value(itr,1)
    if is_file==0:
      self.files_model.clear()
      print ("Changing dir to: ", name)
      self.get_dir(name+"/")
    else:
      if self.settings.getSetting('enqueue')=='1':
       print ("Enqueuing song: ",name)
       name=unicode(name)
       name=name.encode()
       whale_enqueue_file(self.socket,name)
       self.get_playlist()
       """
       if get_now_playing==none:
           whale_play_playlist
       """
      else:
       print ("Sending request for song: ", name)
       name=unicode(name);
       name=name.encode()
       whale_play_file(self.socket,name);
      self.get_now_playing()
  def show(self):
    self.get_dir("/home/maciek")
  def get_widgets(self):
    self.files_model=self.gtkbuilder.get_object("files_model")
    self.playlist_model=self.gtkbuilder.get_object("playlist_model")
    self.files_view=self.gtkbuilder.get_object("files_view")
    self.preferences_win=self.gtkbuilder.get_object("preferences_win")
    self.toggle_enq=self.gtkbuilder.get_object("toggle_enq")
    self.about_win=self.gtkbuilder.get_object("about")
    self.now_playing=self.gtkbuilder.get_object("now_playing")
  def get_now_playing(self):
    data=whale_get_current(self.socket)
    print (data)
    tree=fromstring(data);
    path=tree.getiterator("path")
    path=path[0]
    self.now_playing.set_text(path.text)
    
  def get_playlist(self):
    data=whale_get_playlist(self.socket)
    print (data)
    tree=fromstring(data);
    self.playlist_model.clear()
    for item in tree.getiterator("track"):
      self.playlist_model.append((item.text,'',''))
  def specific_init(self): 
    self.settings=settings() #replace with xmlsettings
    self.new_settings=settings()
    print ("Connecting...")
    self.get_widgets()
    self.socket=whale_connect(self.settings.getSetting('host'),int(self.settings.getSetting('port')))
    print ("Logging...")
    whale_log_user(self.socket,"maciek","xxx")
    print ("Getting dir...")
    self.get_dir("/home/maciek/mp3/")
    #print ("Getting playlist...");
    #self.get_playlist();
    #print ("Getting now playing...");
    #self.get_now_playing()
    gtk.main()
  
