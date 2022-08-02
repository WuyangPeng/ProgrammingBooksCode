# Unix/Linux Makefile
# This file has not been tested extensively, but it is hoped that it will be useful.
# It is assumed that OGRE, OIS, and OpenAL were installed through the package manager,
# and that OgreAL was compiled from source and installed to /usr/local (the default).

# get correct include and link flags for OGRE/OIS/OgreAL
LIB_CFLAGS := $(shell pkg-config --cflags OGRE OIS OgreAL)
LIB_LDFLAGS := $(shell pkg-config --libs OGRE OIS OgreAL)

# OGRE uses hash_{,multi}{map,set}, and g++ complains about it being deprecated.
# We can't fix it, and it makes things noisy, so remove the warnings.
# Also, enable debug symbols.
CFLAGS = -Wno-deprecated -g

OBJS = Ball.o Paddle.o Pong.o PongMain.o
HEADERS = Ball.h Paddle.h Pong.h # not optimal, but simple and good enough

.PHONY : clean

pong : $(OBJS)
	g++ -o pong $^ $(LIB_LDFLAGS) $(LDFLAGS)

%.o : %.cpp $(HEADERS)
	g++ -c $< $(LIB_CFLAGS) $(CFLAGS)

clean :
	rm -f $(OBJS) pong
