#
#  Make the Xinu version of the C run-time support library
#

DIR	=	/usr/Xinu
CFLAGS	=	-O -c -I../../h
SFLAGS	=	-I../../h
AR	=	/bin/ar
LIB	=	${DIR}/lib


.s.o:
		$(AS) -o $@ $(AFLAGS) $<

.c.o:
		$(CC) $(CFLAGS) $<

CFILES	=	abs.c atof.c atoi.c atol.c blkcopy.s bzero.c ctype_.c	\
		doprnt.c memcmp.c memset.c	\
		doscan.c ecvt.c fgets.c fprintf.c fputs.c gets.c	\
		index.c printf.c puts.c qsort.c rand.c rindex.c scanf.c	\
		sprintf.c strcat.c strcmp.c strcpy.c strlen.c strncat.c	\
		strncmp.c strncpy.c swab.c

OFILES	=	abs.o atof.o atoi.o atol.o blkcopy.o bzero.o ctype_.o	\
		doprnt.o memcmp.o memset.o	\
		doscan.o ecvt.o fgets.o fprintf.o fputs.o gets.o	\
		index.o printf.o puts.o qsort.o rand.o rindex.o scanf.o	\
		sprintf.o strcat.o strcmp.o strcpy.o strlen.o strncat.o	\
		strncmp.o strncpy.o swab.o

all:		libxc.a

libxc.a:	${OFILES}
		rm -f libxc.a
		ar cr libxc.a $(OFILES)
		ranlib libxc.a

install:	libxc.a
		cp libxc.a $(LIB)/libxc.a
		ranlib $(LIB)/libxc.a
		
clean:
		rm -f ${OFILES}
