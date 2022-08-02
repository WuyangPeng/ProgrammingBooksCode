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


all: debugging

clean:
	rm *.o debugging

main.o : main.cpp
	$(CC) -c -o main.o main.cpp

objectMgr.o : ../../../framework/common/objectMgr.cpp
	$(CC) -c -o objectMgr.o ../../../framework/common/objectMgr.cpp

debugging.o : ../../../framework/common/debugging.cpp
	$(CC) -c -o debugging.o ../../../framework/common/debugging.cpp

debugStream.o : ../../../framework/common/debugStream.cpp
	$(CC) -c -o debugStream.o ../../../framework/common/debugStream.cpp

stringTools.o : ../../../framework/common/stringTools.cpp
	$(CC) -c -o stringTools.o ../../../framework/common/stringTools.cpp


bstring.o : ../../../framework/common/bstring.cpp
	$(CC) -c -o bstring.o ../../../framework/common/bstring.cpp

geometry.o : ../../../framework/common/geometry.cpp
	$(CC) -c -o geometry.o ../../../framework/common/geometry.cpp

timing.o : ../../../framework/common/timing.cpp
	$(CC) -c -o timing.o ../../../framework/common/timing.cpp

unitTest.o : ../../../framework/common/unitTest.cpp
	$(CC) -c -o unitTest.o ../../../framework/common/unitTest.cpp

debugging: main.o debugging.o debugStream.o stringTools.o objectMgr.o bstring.o geometry.o timing.o unitTest.o
	$(CC) main.o debugging.o debugStream.o stringTools.o objectMgr.o bstring.o geometry.o timing.o unitTest.o -o debugging $(LIBDIRS) $(LIBS)

