# Unix makefile. It may not be as streamlined as possible, but it
# is pretty readable.

COMPILER=c++
CFLAGS= -O2 -W -DHasPTHREADS -pthread -DNEEDS_UINTPTR_T

DEBUG= -g
LIBS=-lm

INCLUDEDIRS=-I../../framework/include
LIBDIRS=-L. 


CC=$(COMPILER) $(CFLAGS) $(DEBUG) $(INCLUDEDIRS) $(DEFINES)
LINK=$(CC) $(LIBDIRS) $(LIBS)


all: prototype2

clean:
	rm *.o prototype2

main.o : main.cpp
	$(CC) -c -o main.o main.cpp

lock.o : ../../framework/unix/lock.cpp
	$(CC) -c -o lock.o ../../framework/unix/lock.cpp

timing.o : ../../framework/common/timing.cpp
	$(CC) -c -o timing.o ../../framework/common/timing.cpp

unitTest.o : ../../framework/common/unitTest.cpp
	$(CC) -c -o unitTest.o ../../framework/common/unitTest.cpp

prototype2: main.o lock.o timing.o unitTest.o
	$(CC) main.o lock.o timing.o unitTest.o -o prototype2 $(LIBDIRS) $(LIBS)

