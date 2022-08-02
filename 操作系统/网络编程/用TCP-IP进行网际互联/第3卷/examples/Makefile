#
# Internetworking with TCP/IP, Volume III example code Makefile
#
#	David L Stevens, Internetworking Research Group at Purdue
#	Tue Sep 17 19:40:42 EST 1991
#

INCLUDE =

CLNTS = TCPecho TCPdaytime TCPtecho UDPecho UDPtime
SERVS = TCPdaytimed TCPechod TCPmechod UDPtimed daytimed
OTHER = superd TCPmtechod

DEFS = -D_BSD_SOURCE
CFLAGS = -W -pedantic -ansi -g ${DEFS} ${INCLUDE}

HDR =
CSRC = TCPecho.c TCPdaytime.c TCPtecho.c UDPecho.c UDPtime.c
CXSRC = connectTCP.c connectUDP.c connectsock.c errexit.c

SSRC = TCPdaytimed.c TCPechod.c TCPmechod.c TCPmtechod.c UDPtimed.c \
	daytimed.c superd.c
SXSRC = passiveTCP.c passiveUDP.c passivesock.c sv_funcs.c

CXOBJ = connectTCP.o connectUDP.o connectsock.o errexit.o
SXOBJ = passiveTCP.o passiveUDP.o passivesock.o errexit.o

PROGS = ${CLNTS} ${SERVS} ${OTHER}

all: ${PROGS}

${CLNTS}: ${CXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${CXOBJ}

${SERVS}: ${SXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${SXOBJ}

superd: ${SXOBJ} superd.o sv_funcs.o
	${CC} -o $@ ${CFLAGS} $@.o ${SXOBJ} sv_funcs.o

TCPmtechod: TCPmtechod.o ${SXOBJ}
	${CC} -o $@ ${CFLAGS} $@.o ${SXOBJ} -lpthread

clients: ${CLNTS}
servers: ${SERVS}

clean: FRC
	rm -f Makefile.bak a.out core errs lint.errs ${PROGS} *.o

depend: ${HDR} ${CSRC} ${SSRC} ${TNSRC} FRC
	maketd -a ${DEFS} ${INCLUDE} ${CSRC} ${SSRC} ${TNSRC}

install: all FRC
	@echo "Your installation instructions here."

lint: ${HDR} ${XSRC} ${CSRC} ${SSRC} FRC
	lint ${DEFS} ${INCLUDE} ${CSRC} ${SSRC} ${CXSRC} ${SXSRC}

print: Makefile ${SRC} FRC
	lpr Makefile ${CSRC} ${SSRC} ${CXSRC} ${SXSRC}

spotless: clean FRC
	rcsclean Makefile ${HDR} ${SRC}

tags: ${CSRC} ${SSRC} ${CXSRC} ${SXSRC}
	ctags ${CSRC} ${SSRC} ${CXSRC} ${SXSRC}

${HDR} ${CSRC} ${CXSRC} ${SSRC} ${SXSRC}:
	co $@

TCPecho: TCPecho.o
TCPdaytime: TCPdaytime.o
TCPtecho: TCPtecho.o
UDPecho: UDPecho.o
UDPtime: UDPtime.o
TCPdaytimed: TCPdaytimed.o
TCPechod: TCPechod.o
TCPmechod: TCPmechod.o
UDPtimed: UDPtimed.o
daytimed: daytimed.o
superd: superd.o

FRC:
	
# DO NOT DELETE THIS LINE - maketd DEPENDS ON IT
