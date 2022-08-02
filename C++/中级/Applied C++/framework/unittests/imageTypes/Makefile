# Generic Unix makefile. It may not be as streamlined as possible,
# but it is pretty readable.

# Using pthreads via the FSF pth library with pthread interface enabled
# http://www.fsf.org/software/pth/pth.html
#   ./configure --enable-pthread


COMPILER=c++
CFLAGS= -O2 -W -DHasPTHREADS -pthread
DEBUG= -g
LIBS=-lm

INCLUDEDIRS= -I../../../framework/include
LIBDIRS=-L.

CC=$(COMPILER) $(CFLAGS) $(DEBUG) $(INCLUDEDIRS) $(DEFINES)
LINK=$(CC) $(LIBDIRS) $(LIBS)


all: imageTypes

clean:
	rm imageTypes *.o


main.o : main.cpp
	$(CC) $(CCFLAGS) -c main.cpp

imageTypes.o : ../../../framework/image/imageTypes.cpp
	$(CC) $(CCFLAGS) -c ../../../framework/image/imageTypes.cpp

geometry.o : ../../../framework/common/geometry.cpp
	$(CC) $(CCFLAGS) -c ../../../framework/common/geometry.cpp

bstring.o : ../../../framework/common/bstring.cpp
	$(CC) $(CCFLAGS) -c ../../../framework/common/bstring.cpp

timing.o : ../../../framework/common/timing.cpp
	$(CC) $(CCFLAGS) -c ../../../framework/common/timing.cpp

unitTest.o : ../../../framework/common/unitTest.cpp
	$(CC) $(CCFLAGS) -c ../../../framework/common/unitTest.cpp


imageTypes: main.o imageTypes.o geometry.o bstring.o timing.o unitTest.o
	$(CC) main.o imageTypes.o geometry.o bstring.o timing.o unitTest.o -o imageTypes $(LIBDIRS) $(LIBS)
