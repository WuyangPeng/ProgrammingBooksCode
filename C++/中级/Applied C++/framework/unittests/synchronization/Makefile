# Generic Unix makefile. It may not be as streamlined as possible,
# but it is pretty readable.

COMPILER=c++
CFLAGS= -O2 -W -DHasPTHREADS -D_THREAD_SAFE -pthread

DEBUG= -g
LIBS=-lm

INCLUDEDIRS=-I../../../framework/include
LIBDIRS=-L. 

CC=$(COMPILER) $(CFLAGS) $(DEBUG) $(INCLUDEDIRS) $(DEFINES)
LINK=$(CC) $(LIBDIRS) $(LIBS)


all: synchronization

clean:
	rm *.o synchronization

main.o : main.cpp
	$(CC) -c -o main.o main.cpp

geometry.o : ../../../framework/common/geometry.cpp
	$(CC) -c -o geometry.o ../../../framework/common/geometry.cpp

bstring.o : ../../../framework/common/bstring.cpp
	$(CC) -c -o bstring.o ../../../framework/common/bstring.cpp

timing.o : ../../../framework/common/timing.cpp
	$(CC) -c -o timing.o ../../../framework/common/timing.cpp

lock.o : ../../../framework/unix/lock.cpp
	$(CC) -c -o lock.o ../../../framework/unix/lock.cpp

unitTest.o : ../../../framework/common/unitTest.cpp
	$(CC) -c -o unitTest.o ../../../framework/common/unitTest.cpp

synchronization: main.o geometry.o bstring.o timing.o lock.o unitTest.o
	$(CC) main.o geometry.o bstring.o timing.o lock.o unitTest.o -o synchronization $(LIBDIRS) $(LIBS)
