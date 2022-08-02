# Unix makefile. It may not be as streamlined as possible, but it
# is pretty readable.

COMPILER=c++
CFLAGS= -O2 -W
DEBUG= -g
LIBS=-lm

INCLUDEDIRS=
LIBDIRS=-L. 


CC=$(COMPILER) $(CFLAGS) $(DEBUG) $(INCLUDEDIRS) $(DEFINES)
LINK=$(CC) $(LIBDIRS) $(LIBS)


all: testapplication

clean:
	rm *.o testapplication

main.o : main.cpp
	$(CC) -c -o main.o main.cpp

image.o : image.cpp
	$(CC) -c -o image.o image.cpp

thumbnail.o : thumbnail.cpp
	$(CC) -c -o thumbnail.o thumbnail.cpp

testapplication: main.o image.o thumbnail.o
	$(CC) main.o image.o thumbnail.o  -o testapplication $(LIBDIRS) $(LIBS)

