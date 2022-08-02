# Unix makefile. This version is compact and works fine with GNU make

# Using pthreads via the FSF pth library with pthread interface enabled
# http://www.fsf.org/software/pth/pth.html
#   ./configure --enable-pthread

# After building the IPP application using shared libraries, you need to
# modify your LD_LIBRARY_PATH so the system can find the libraries
# For bash shell:
#   export LD_LIBRARY_PATH=/opt/intel/ipp/sharedlib:$LD_LIBRARY_PATH

INTELROOT= /opt/intel/ipp

CXX=c++
DEBUG= -g
OPTFLAG=-O2 -DHasPTHREADS -DNEEDS_UINTPTR_T -pthread
WARNFLAG=-W
INCLUDEDIRS= -I../../../framework/include -I$(INTELROOT)/include

LIBDIRS=-L.
LIBS=-lm $(INTELROOT)/sharedlib/libippi.so


CXXFLAGS=$(OPTFLAG) $(WARNFLAG) $(DEBUG) $(INCLUDEDIRS) $(DEFINES)
LIBFLAGS=$(LIBDIRS) $(LIBS)

# VPATH points to other locations where source files can be found
VPATH = ../../../framework/common:../../../framework/image:../../../framework/unix

all: ipp

clean:
	rm ipp $(objects)


%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

objects = main.o imageTmpl.o imageStorage.o imageTypes.o imageTools.o geometry.o bstring.o timing.o lock.o fastTiming.o unitTest.o

ipp: $(objects)
	$(CXX) $(CXXFLAGS) -o ipp $(objects) $(LIBFLAGS)
