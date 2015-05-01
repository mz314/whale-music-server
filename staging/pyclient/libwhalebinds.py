import ctypes
from ctypes import *

"""Bindings only. More abstract stuff elsewere"""

class items (ctypes.Structure):
  _fields_=[
	    ("is_file",c_ubyte),
	    ("name",c_char_p)
	   ]

class ddata (ctypes.Structure):
  _fields_=[("n",c_int),
	    ("items",POINTER(items))
	   ] 


whale=ctypes.cdll.LoadLibrary("libwhaleclient.so")
whale_connect=whale.whale_connect
whale_disconnect=whale.whale_disconnect
whale_log_user=whale.whale_log_user
whale_play_file=whale.whale_play_file
whale_get_dir=whale.whale_get_dir
whale_get_playlist=whale.whale_get_playlist
whale_get_current=whale.whale_get_current
whale_dispose_dir_data=whale.whale_dispose_dir_data
whale_enqueue_file=whale.whale_enqueue_file
whale_next_file=whale.whale_next_file
whale_prev_file=whale.whale_prev_file

whale_get_dir.restype=c_char_p
whale_get_playlist.restype=c_char_p
whale_get_current.restype=c_char_p
#