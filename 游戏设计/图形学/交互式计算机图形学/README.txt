This directory contains program that support Interactive Computer Graphics (Fifth Edition).
They are organized by chapter. Each directory contains the source code relevant to that
chapter. All programs in Appendix A are in these directory. I have also added some programs
referred to in the book but not in the appendices and some others that I use to create
some of the illustrations.

Because the GLUT header files are stored in the GLUT include rather than GL as on other systems,
I have added the following compiler directive to each program so each should compile without
modification on all architectures

#ifdef __APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

If you compile and link your code from a command line, then the following Makefile should
work on most linux systems. Use the LDLIBS line that fits your X11 installation.

C = gcc 

#LDLIBS = -lglut -lGL -lGLU -lXmu -lX11  -lm 
LDLIBS = -lglut -lGL -lXmu -lX11  -lm -L/usr/X11R6/lib -I/usr/X11R6/include

.c:
	$(CC)  $@.c $(LDLIBS) -o $@


For Mac OS X, the following is a minimal Makefile for Mac OS X

GCC_OPTIONS=-Wall -pedantic
GL_OPTIONS=-framework OpenGL -framework GLUT
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


.c: 
	gcc $@.c $(OPTIONS) -o $@  


Using the proper makefile, you should be able to comile a single program myprogram.c by

make myprogram

For Windows platforms, if you write your own shaders, you will also have to install the
GLEW libraries from sourceforge.com. Then add the include

#include <GL/glew.h>

and the intialization

glewInit();

after the glutInitWindow call.

