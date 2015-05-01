CFLAGS=
EXECNAME=music_daemon
DAEMON_LDGLAGS=
SERVER_LDFLAGS=-lboost_system -lboost_thread -lboost_regex
DB_LDFLAGS=-lsqlite3


.PHONY: all install clean install_server

all: server 
	# cd ./clientlib; make lib
	mv ./server ./$(EXECNAME)

test: server.o
		

install_server: server
	echo "It would be useless now."

install: all install_server
	cd clientlib; make install


server: server.o  user_manager.o  manager.o logs.o  user_state.o gstreamer_io.o xml.o playlist.o socketshtpp.o socketsabs.o responsexml.o httpFiles.o fileUtils.o database.o
	g++ $^ `pkg-config --cflags --libs gstreamer-0.10` $(SERVER_LDFLAGS)  $(DB_LDFLAGS) -o $@

fileUtils.o: fileUtils.cpp
	g++  `pkg-config --cflags --libs gstreamer-0.10` -o $@  $(CFLAGS) -c $^

httpFiles.o: httpFiles.cpp
	g++  `pkg-config --cflags --libs gstreamer-0.10` -o $@  $(CFLAGS) -c $^

heavy_test: heavy_test.cpp heavy.o
	g++ $^ $(ALSA_LDFLAGS) -o $@

#heavy_test.o: heavy_test.cpp heavy.o
#	g++  -o $@  $(CFLAGS) $(SERVER_LDFLAGS) -c $^

#heavy.o: heavy_tasks.cpp
#	g++  -o $@  $(CFLAGS)  -c $^


user_manager.o: user_manager.cpp 
	g++  `pkg-config --cflags --libs gstreamer-0.10` -o $@  $(CFLAGS) -c $^

server.o: musicserver.cpp 
	g++  -c $^ `pkg-config --cflags --libs gstreamer-0.10`  -o $@  $(CFLAGS)   

manager.o: server_manager.cpp
	g++  `pkg-config --cflags --libs gstreamer-0.10` -o $@  $(CFLAGS) -c $^


#sockets.o: sockets.cpp 
#	g++   `pkg-config --cflags --libs gstreamer-0.10`  -o $@  $(CFLAGS) -c $^

logs.o: logs.cpp
	g++  -o $@  $(CFLAGS) -c $^

#logsh.o: logs.h 
#	g++  -o $@  $(CFLAGS)  -c $^

#command.o: command.cpp
#	g++  -o $@  $(CFLAGS)  -c $^


database.o: database.cpp
	g++  -o $@  $(CFLAGS)  -c $^

user_state.o: user_state.cpp
	g++  -o $@  $(CFLAGS)  -c $^


gstreamer_io.o: gstreamer_io.cpp
	g++  -o $@  `pkg-config --cflags --libs gstreamer-0.10` $(CFLAGS)  -c $^


#xml.o: xml.cpp
#	g++  -o $@  $(CFLAGS)  -c $^


playlist.o: playlist.cpp
	g++  -o $@  $(CFLAGS)  -c $^


socketsabs.o: sockets_abstract.cpp
	g++  `pkg-config --cflags --libs gstreamer-0.10` -o $@  $(CFLAGS)  -c $^
	
socketshtpp.o: sockets_http.cpp
	g++  `pkg-config --cflags --libs gstreamer-0.10` -o $@  $(CFLAGS)  -c $^


#httptest.o: httptest.cpp 
#	g++  -o $@  $(CFLAGS)  -c $^
	
#httptest: httptest.o socketshtpp.o logs.o socketsabs.o
#	g++ $^  $(SERVER_LDFLAGS)  -o $@

resptest: responsetest.o responsexml.o  gstreamer_io.o user_state.o user_manager.o logs.o
	g++ $^  $(SERVER_LDFLAGS) `pkg-config --cflags --libs gstreamer-0.10` -o $@

responsetest.o: resptest.cpp  gstreamer_io.o
	g++  -o $@  $(CFLAGS) $(SERVER_LDFLAGS) `pkg-config --cflags --libs gstreamer-0.10`  -c $^

responseabs.o: responseAbstract.cpp
	g++  -o $@  $(CFLAGS)  -c $^

responsexml.o: responseXML.cpp 
	g++  -o $@  $(CFLAGS)   -c $^

clean:  
	rm *.o
	#cd ./clientlib; make clean
	rm $(EXECNAME)
