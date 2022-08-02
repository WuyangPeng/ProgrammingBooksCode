# Unix makefile. It may not be as streamlined as possible, but it
# is pretty readable.

# Using pthreads via the FSF pth library with pthread interface enabled
# http://www.fsf.org/software/pth/pth.html
#   ./configure --enable-pthread


COMPILER=c++
CFLAGS= -O2 -W -DHasPTHREADS -DNEEDS_UINTPTR_T -pthread
DEBUG= -g
LIBS=-lm -ljpeg -ltiff

# Fix these paths to the platform specific versions
INCLUDEDIRS= -I../../include -I../../thirdparty/include/linux
LIBDIRS=-L. -L../../thirdparty/lib/linux

CC=$(COMPILER) $(CFLAGS) $(DEBUG) $(INCLUDEDIRS) $(DEFINES)
LINK=$(CC) $(LIBDIRS) $(LIBS)


all: filedelegates

clean:
	rm *.o filedelegates

main.o : main.cpp
	$(CC) -c -o main.o main.cpp

imageTmpl.o : ../../../framework/image/imageTmpl.cpp
	$(CC) -c -o imageTmpl.o ../../../framework/image/imageTmpl.cpp

imageStorage.o : ../../../framework/image/imageStorage.cpp
	$(CC) -c -o imageStorage.o ../../../framework/image/imageStorage.cpp

imageTools.o : ../../../framework/image/imageTools.cpp
	$(CC) -c -o imageTools.o ../../../framework/image/imageTools.cpp

imageTypes.o : ../../../framework/image/imageTypes.cpp
	$(CC) -c -o imageTypes.o ../../../framework/image/imageTypes.cpp

io.o : ../../../framework/delegates/io.cpp
	$(CC) -c -o io.o ../../../framework/delegates/io.cpp

jpeg.o : ../../../framework/delegates/jpeg.cpp
	$(CC) -c -o jpeg.o ../../../framework/delegates/jpeg.cpp

tiff.o : ../../../framework/delegates/tiff.cpp
	$(CC) -c -o tiff.o ../../../framework/delegates/tiff.cpp

iap.o : ../../../framework/delegates/iap.cpp
	$(CC) -c -o iap.o ../../../framework/delegates/iap.cpp

geometry.o : ../../../framework/common/geometry.cpp
	$(CC) -c -o geometry.o ../../../framework/common/geometry.cpp

bstring.o : ../../../framework/common/bstring.cpp
	$(CC) -c -o bstring.o ../../../framework/common/bstring.cpp

timing.o : ../../../framework/common/timing.cpp
	$(CC) -c -o timing.o ../../../framework/common/timing.cpp

lock.o : ../../../framework/unix/lock.cpp
	$(CC) -c -o lock.o ../../../framework/unix/lock.cpp

unittest.o : ../../../framework/common/unitTest.cpp
	$(CC) -c -o unittest.o ../../../framework/common/unitTest.cpp

filedelegates: main.o imageTmpl.o imageStorage.o imageTools.o imageTypes.o io.o jpeg.o tiff.o iap.o geometry.o bstring.o timing.o lock.o unittest.o
	$(CC) main.o imageTmpl.o imageStorage.o imageTools.o imageTypes.o io.o jpeg.o tiff.o iap.o geometry.o bstring.o timing.o lock.o unittest.o -o filedelegates $(LIBDIRS) $(LIBS)
