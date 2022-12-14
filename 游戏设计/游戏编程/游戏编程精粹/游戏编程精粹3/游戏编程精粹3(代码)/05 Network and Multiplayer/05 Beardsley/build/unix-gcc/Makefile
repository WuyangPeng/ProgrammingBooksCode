# Game Programming Gems 3
# Template-Based Object Serialization
# Author: Jason Beardsley

# Makefile - for GNU make only

VPATH = ../../src

LIB_SRCS = basetypes.cpp buffer.cpp byteorder.cpp \
	serdefs.cpp serializer.cpp

LIB_OBJS = $(LIB_SRCS:.cpp=.o)

TEST_SRCS = test0.cpp test1.cpp test2.cpp test3.cpp test4.cpp \
	test5.cpp test6.cpp test7.cpp test8.cpp test9.cpp \
	testmain.cpp

TEST_OBJS = $(TEST_SRCS:.cpp=.o)

ALL_SRCS = $(LIB_SRCS) $(TEST_SRCS)
ALL_OBJS = $(LIB_OBJS) $(TEST_OBJS)

# g++ v3 comes with a good STL
# g++ v2.9* - get the SGI STL and install it in ../../stl

ifdef GCC3
CXX = g++3
else
CXX = g++
STLINC = -I../../stl
endif

CXXFLAGS_BASE = -W -Wall $(STLINC)

# debug
CXXFLAGS = -g $(CXXFLAGS_BASE)
# release
#CXXFLAGS = -O $(CXXFLAGS_BASE)


all: depend lib test

gcc3-all:
	$(MAKE) GCC3=1 all


clean:
	rm -f $(ALL_OBJS) libserialize.a test .depend

lib: libserialize.a

depend: $(ALL_SRCS)
	$(CXX) -MM $^ > .depend

libserialize.a: $(LIB_OBJS)
	ar rc $@ $^
	ranlib $@

test: $(TEST_OBJS) libserialize.a
	$(CXX) -o $@ $^

-include .depend
