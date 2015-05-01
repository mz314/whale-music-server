DAEMON_LDGLAGS=
MAD_LDFLAGS=-lmad -lasound
SERVER_LDFLAGS=-lboost_system-mt -lboost_thread-mt


gstest: gstest.c
	gcc -Wall gstest.c -o gstest `pkg-config --cflags --libs gstreamer-0.10`

mad_staging: madmp3.c
	gcc $^ $(MAD_LDFLAGS) -o $@

server_staging: musicserver_staging.cpp
	g++ $^  $(SERVER_LDFLAGS) -o $@


db_staging: db_staging.o ../database.o
	g++ $^ -lsqlite3 -o $@

db_staging.o: db_staging.cpp
	g++  -o $@  $(CFLAGS)  -c $^

alsa_run: alsa
	./alsa


client_staging: client_staging.cpp
	g++ $^  $(SERVER_LDFLAGS) -o $@



daemon: daemon.c
	gcc $^ $(DAEMON_LDFLAGS) -o $@

alsa: alsa.c
	gcc $^ $(LDFLAGS) -o $@

alsa_clean:
	rm ./alsa

daemon_clean:
	rm ./daemon

clean_server_staging:
	rm ./server_staging
	rm ./client_staging
  