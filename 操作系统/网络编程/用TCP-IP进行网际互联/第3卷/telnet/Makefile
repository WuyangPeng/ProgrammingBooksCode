#
# Internetworking with TCP/IP, Volume III telnet example Makefile
#
#	David L Stevens, Internetworking Research Group at Purdue
#	Fri Mar 20 21:13:40 EST 1992
#

INCLUDE =

PROG = telnet

DEFS = -D_POSIX_SOURCE
CFLAGS = -pedantic -ansi -g ${DEFS} ${INCLUDE}

HDR =
SRC =	cerrexit.c	connectTCP.c	connectUDP.c	connectsock.c	\
	dcon.c		do_echo.c	do_noga.c	do_notsup.c	\
	do_txbinary.c	errexit.c	fsmbuild.c	fsminit.c	\
	sonotsup.c	sofsm.c		tclient.c	recopt.c	\
	scrgetc.c	scrinit.c	scrwrap.c	soputc.c	\
	sowrite.c	status.c	subend.c	subfsm.c	\
	subopt.c	subtermtype.c	suspend.c	sync.c		\
	tcout.c		telnet.c	tnabort.c	ttfsm.c		\
	ttputc.c	ttysetup.c	ttwrite.c	unscript.c	\
	will_notsup.c	will_termtype.c	will_txbinary.c	xput.c
OBJ =	cerrexit.o	connectTCP.o	connectUDP.o	connectsock.o	\
	dcon.o		do_echo.o	do_noga.o	do_notsup.o	\
	do_txbinary.o	errexit.o	fsmbuild.o	fsminit.o	\
	sonotsup.o	sofsm.o		tclient.o	recopt.o	\
	scrgetc.o	scrinit.o	scrwrap.o	soputc.o	\
	sowrite.o	status.o	subend.o	subfsm.o	\
	subopt.o	subtermtype.o	suspend.o	sync.o		\
	tcout.o		telnet.o	tnabort.o	ttfsm.o		\
	ttputc.o	ttysetup.o	ttwrite.o	unscript.o	\
	will_notsup.o	will_termtype.o	will_txbinary.o	xput.o

all: ${PROG}

${PROG}: ${OBJ}
	${CC} -o $@ ${CFLAGS} ${OBJ} -ltermcap

clean: FRC
	rm -f Makefile.bak a.out core errs lint.errs ${PROG} *.o

depend: ${HDR} ${SRC} FRC
	maketd -a ${DEFS} ${INCLUDE} ${SRC}

install: all FRC
	@echo "Your installation instructions here."

lint: ${HDR} ${SRC} FRC
	lint ${DEFS} ${INCLUDE} ${SRC}

print: Makefile ${SRC} FRC
	lpr Makefile ${HDR} ${SRC}

spotless: clean FRC
	rcsclean Makefile ${HDR} ${SRC}

tags: ${SRC}
	ctags ${SRC}

${HDR} ${SRC}:
	co $@

FRC:
	
