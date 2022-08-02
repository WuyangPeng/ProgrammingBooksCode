# Generic Unix makefile. It may not be as streamlined as possible,
# but it is pretty readable.

# Using pthreads via the FSF pth library with pthread interface enabled
# http://www.fsf.org/software/pth/pth.html
#   ./configure --enable-pthread


CXX=c++
DEBUG= -g
OPTFLAG=-O2 -DHasPTHREADS -pthread
WARNFLAG=-W
INCLUDEDIRS= -I../../../framework/include
LIBDIRS=-L.
LIBS=-lm

CXXFLAGS=$(OPTFLAG) $(WARNFLAG) $(DEBUG) $(INCLUDEDIRS) $(DEFINES)
LIBFLAGS=$(LIBDIRS) $(LIBS)


all: resourceMgr

clean:
	rm resourceMgr $(objects)

objects = main.o wideTools.o xmlTools.o resourceMgr.o debugStream.o timing.o unitTest.o

resourceMgr: $(objects)
	$(CXX) -o resourceMgr $(objects) $(LIBFLAGS)


main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

wideTools.o : ../../../framework/common/wideTools.cpp
	$(CXX) $(CXXFLAGS) -c ../../../framework/common/wideTools.cpp

xmlTools.o : ../../../framework/common/xmlTools.cpp
	$(CXX) $(CXXFLAGS) -c ../../../framework/common/xmlTools.cpp

resourceMgr.o : ../../../framework/common/resourceMgr.cpp
	$(CXX) $(CXXFLAGS) -c ../../../framework/common/resourceMgr.cpp

debugStream.o : ../../../framework/common/debugStream.cpp
	$(CXX) $(CXXFLAGS) -c ../../../framework/common/debugStream.cpp

timing.o : ../../../framework/common/timing.cpp
	$(CXX) $(CXXFLAGS) -c ../../../framework/common/timing.cpp

unitTest.o : ../../../framework/common/unitTest.cpp
	$(CXX) $(CXXFLAGS) -c ../../../framework/common/unitTest.cpp


