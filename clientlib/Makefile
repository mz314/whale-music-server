CFLAGS=
LDFLAGS=
SONAME=libwhaleclient.so



.PHONY: all install clean

all: libwtest lib

install:
	cp $(SONAME) /usr/lib
	ldconfig

libwtest: ../staging/librarytest.cpp
	g++ $^ -L./ -lwhaleclient -o $@

lib: lib.o sockabs.o
	gcc -shared -Wl,-soname,$(SONAME) -o $(SONAME)   $^


	


lib.o: whalelib.c 
	gcc -fPIC  $(LDFLAGS) -c $^ -o $@
	

sockabs.o: sockabstract.c
	gcc -fPIC -o $@  -c $^  

clean:
	rm *.o
	rm *.so
	