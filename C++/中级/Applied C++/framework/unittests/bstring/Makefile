# Generic Unix makefile. It may not be as streamlined as possible,
# but it is pretty readable.

COMPILER=c++
CFLAGS= -O2 -W
DEBUG= -g
LIBS=-lm

INCLUDEDIRS=-I../../../framework/include
LIBDIRS=-L. 


CC=$(COMPILER) $(CFLAGS) $(DEBUG) $(INCLUDEDIRS) $(DEFINES)
LINK=$(CC) $(LIBDIRS) $(LIBS)


all: bstring

clean:
	rm *.o bstring

main.o : main.cpp
	$(CC) -c -o main.o main.cpp

bstring.o : ../../../framework/common/bstring.cpp
	$(CC) -c -o bstring.o ../../../framework/common/bstring.cpp

geometry.o : ../../../framework/common/geometry.cpp
	$(CC) -c -o geometry.o ../../../framework/common/geometry.cpp

timing.o : ../../../framework/common/timing.cpp
	$(CC) -c -o timing.o ../../../framework/common/timing.cpp

unitTest.o : ../../../framework/common/unitTest.cpp
	$(CC) -c -o unitTest.o ../../../framework/common/unitTest.cpp

bstring: main.o bstring.o geometry.o timing.o unitTest.o
	$(CC) main.o bstring.o geometry.o timing.o unitTest.o -o bstring $(LIBDIRS) $(LIBS)
