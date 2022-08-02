#
# Makefile for Xinu shell and associated commands
#

.SUFFIXES:.o .c .s
DEFS =
INCLUDE = -I../h
CFLAGS	=  ${DEFS} ${INCLUDE} -O -W -c
AR	=	ar

.c.o:
		$(CC) $(CFLAGS)	$<
.s.o:
		$(CC) $(CFLAGS)	$<

CFILES=		addarg.c ascdate.c login.c lexan.c	\
		shell.c					\
		x_arp.c x_bpool.c x_cat.c x_close.c x_conf.c x_cp.c\
		x_create.c x_date.c x_devs.c x_dg.c x_dumper.c	\
		x_echo.c x_exit.c x_finger.c x_help.c x_igmp.c	\
		x_ifstat.c	\
		x_kill.c	\
		x_mem.c x_mount.c x_mv.c x_net.c x_ns.c	x_ospf.c \
		x_ping.c x_ps.c x_reboot.c x_rf.c x_rm.c x_rls.c	\
		x_route.c x_routes.c x_sleep.c x_snmp.c \
		x_sema.c x_stacktrace.c \
		x_timerq.c \
		x_unmou.c x_uptime.c x_who.c

XOFILES=	x_arp.o x_bpool.o x_cat.o x_close.o x_conf.o x_cp.o\
		x_create.o x_date.o x_devs.o x_dg.o x_dumper.o	\
		x_echo.o x_exit.o x_finger.o x_help.o x_igmp.o	\
		x_ifstat.o	\
		x_kill.o	\
		x_mem.o x_mount.o x_mv.o x_net.o x_ns.o	x_ospf.o \
		x_ping.o x_ps.o x_reboot.o x_rf.o x_rm.o x_rls.o	\
		x_route.o x_routes.o x_sleep.o x_snmp.o \
		x_sema.o x_stacktrace.o \
		x_timerq.o \
		x_unmou.o x_uptime.o x_who.o

HFILES=		shell.h cmd.h

all:		sh.o install

sh.o:		addarg.o ascdate.o login.o lexan.o	\
		shell.o libS.a Makefile
		$(LD) -r -o sh.o \
			addarg.o ascdate.o login.o	\
			lexan.o shell.o libS.a

libS.a:		$(XOFILES)
		rm -rf libS.a
		$(AR) cr libS.a $(XOFILES)
		ranlib libS.a

install:	sh.o
		cp sh.o ../compile

clean:
		-rm -rf *.o ,* .,* core make.out *.a

everything:	all lint sizes xref

lint:		,lint

,lint:		$(CFILES)
		lint -n -I../h $(CFILES) | Flint > ,lint

print:
		$(CPRINT) -c Cover *.h *.c

listings:	sizes xref
		$(CPRINT) -c Cover *.h *.c ,xref ,sizes ,ssizes Makefile

sizes:		,sizes ,ssizes

,sizes:		$(OFILES)
		$(SIZE) *.o > ,sizes

,ssizes:	$(CFILES) $(HFILES)
		./Dosizes

xref:		,xref

,xref:		,tags
		./Doxref

tags:		,tags

,tags:		$(CFILES) $(HFILES)
		ctags $(CFILES) $(HFILES)
		mv tags ,tags

.depend depend: FRC
	mkdep ${DEFS} ${INCLUDE} *.c

FRC:
	
