#
#  Makefile for the Sun-3 version of Xinu.
#

DEFS = -DBSDURG
#CFLAGS = -O -W -traditional ${DEFS} ${INCLUDE}
CFLAGS = -nostdinc -O -W ${DEFS} ${INCLUDE}
INCLUDE = -I../h
AR = /usr/bin/ar
LIB = ../lib/libxc
BRELOC=0x110000
SDEFS=-DLOCORE -DSTANDALONE -DAT386 -I../h


SRCDIR = .  ../arp ../com ../kbm ../dgram ../icmp ../ip ../net ../netapp \
	../ospf ../rfs ../snmp ../sys ../tcp ../tcpd ../tty ../udp\
	../debug

COM =	comcntl.c	comgetc.c	comiin.c	cominit.c	\
	cominput.c	comoutput.c	comread.c	comintr.c

CON =	kbmcntl.c	kbmgetc.c	kbmiin.c	kbminit.c	\
	kbminput.c	kbmoutput.c	kbmread.c	kbscan.c

DEBUG =	arpdump.c	hexdump.c	icmpdump.c	igmpdump.c	\
	ipdump.c	ospfdump.c	pdump.c		tcpdump.c	\
	udpdump.c

DGRAM =	dgalloc.c	dgclose.c	dgcntl.c	dgdump.c	\
	dginit.c	dgmcntl.c	dgmopen.c	\
	dgread.c	dgwrite.c

ARP =	arp_in.c	arpadd.c	arpalloc.c	arpdq.c		\
	arpfind.c	arpinit.c	arpprint.c	arpqsend.c	\
	arpsend.c	arptimer.c

RT =	rtadd.c		rtdel.c		rtdump.c	rtfree.c	\
	rtget.c		rthash.c	rtinit.c	rtnew.c		\
	rttimer.c

IP =	ip_in.c		ipdbc.c		ipdoopts.c	ipdstopts.c	\
	ipfadd.c	ipfcons.c	ipfhcopy.c	ipfinit.c	\
	ipfjoin.c	ipfsend.c	ipftimer.c	ipgetp.c	\
	iph2net.c	ipnet2h.c	ipproc.c	ipputp.c	\
	ipreass.c	ipredirect.c	ipsend.c	\
	isbrc.c		${RT}

ICMP =	icerrok.c	icmp.c		icmp_in.c	icredirect.c	\
	icsetbuf.c	icsetdata.c	icsetsrc.c

IGMP =	hgadd.c		hgarpadd.c	hgarpdel.c	\
	hginit.c	hgjoin.c	\
	hgleave.c	igmp.c		igmp_in.c	hgprint.c	\
	hglookup.c	igmp_update.c	hgrand.c	igmp_settimers.c

TM =	tcptimer.c	tmclear.c	tmleft.c	tmset.c		\
	tqdump.c

TCP =	tcp_in.c	tcpabort.c	tcpacked.c	tcpackit.c	\
	tcpcksum.c	tcpclosed.c	tcpclosewait.c	tcpclosing.c	\
	tcpdata.c	tcpdemux.c	tcpdodat.c	tcpestablished.c\
	tcpfin1.c	tcpfin2.c	tcph2net.c	tcphowmuch.c	\
	tcpidle.c	tcpinp.c	tcpiss.c	tcpkick.c	\
	tcpkilltimers.c	tcplastack.c	tcplisten.c	tcpnet2h.c	\
	tcpok.c		tcpopts.c	tcpostate.c	tcpout.c	\
	tcppersist.c	tcpreset.c	tcprexmt.c	\
	tcprmss.c	tcprtt.c	tcprwindow.c	tcpsend.c	\
	tcpsmss.c	tcpsndlen.c	\
	tcpswindow.c	tcpswitch.c	tcpsync.c	tcpsynrcvd.c	\
	tcpsynsent.c	tcptimewait.c	tcpwait.c	tcpwakeup.c	\
	tcpwinit.c	tcpxmit.c	tfcoalesce.c	tfinsert.c	\
	${TM}

OSPF =	ospf_hin.c	ospf_hsend.c	ospf_in.c	fcksum.c	\
	ospfcheck.c	if_elect.c	ospfhello.c	ospfhtmpl.c	\
	ospfifinit.c	ospfinit.c	ospf.c		ospfnet2h.c	\
	ospftimer.c	nb_add.c	nb_switch.c	nb_reform.c	\
	nb_aok.c	dd_queue.c	dd_xmit.c	lss_build.c	\
	ospf_ddin.c	ospfddtmpl.c	nb_rexmt.c	nb_clearl.c	\
	nb_makel.c	nb_mismatch.c	lsa_xmit.c	if_elect1.c	\
	ddi_exstart.c	ddi_exchng.c	lsr_in.c	db_lookup.c	\
	db_update.c	ddi_full.c	db_new.c	db_init.c	\
	lsa_add.c	lsa_send.c	ospflstmpl.c	lsu_in.c	\
	lsack_in.c	db_nlink.c	db_rlink.c	db_resync.c	\
	lsr_queue.c	lsr_add.c	lsr_xmit.c	ospflsrtmpl.c	\
	lsr_check.c

UDP =	udp_in.c	udpcksum.c	udph2net.c	udpnet2h.c	\
	udpnxtp.c	udpsend.c	upalloc.c	

NET =	dnparse.c	dot2ip.c	ethmatch.c	\
	getiaddr.c	\
	getname.c	getnet.c	getutim.c	initgate.c	\
	inithost.c	ip2dot.c	ip2name.c	local_out.c	\
	name2ip.c	netdump.c	netmask.c	netmatch.c	\
	netnum.c	netstart.c	netwrite.c	ni_in.c		\
	othinit.c	othwrite.c	rarp_in.c	rarpsend.c	\
	setmask.c	slowtimer.c	ethmcast.c

NA =	echod.c		egp.c		fingerd.c	lfing.c		\
	ripadd.c	ripcheck.c	ripifset.c	ripin.c		\
	ripmetric.c	ripok.c		ripout.c	riprecv.c	\
	riprepl.c	ripsend.c	ripstart.c	rwho.c		\
	rwhod.c		rwhoind.c	snmpd.c		udpecho.c

RFS =	mount.c		rfalloc.c	rfclose.c	rfcntl.c	\
	rfdump.c	rfgetc.c	rfinit.c	rfio.c		\
	rfmkpac.c	rfopen.c	rfputc.c	rfread.c	\
	rfseek.c	rfsend.c	rfwrite.c	unmount.c	

SYS =	autostart.c	\
	chprio.c	ckmode.c	clkinit.c	close.c		\
	conf.c		control.c	create.c	\
	dotrace.c	evec.c		freebuf.c	freemem.c	\
	getbuf.c	getc.c		getdmem.c	getitem.c	\
	getmem.c	getpid.c	getprio.c	getstk.c	\
	gettime.c	gpq.c		i386.c		init.c		\
	insert.c	insertd.c	ioerr.c		\
	ionull.c	kill.c		kprintf.c	stacktrace.c	\
	kputc.c		mark.c		mkdpool.c	mkpool.c	\
	naminit.c	nammap.c	namopen.c	namrepl.c	\
	newqueue.c	open.c		panic.c		pcount.c	\
	pcreate.c	pdelete.c	pinit.c		poolinit.c	\
	preceive.c	preset.c	printq.c	psend.c		\
	ptclear.c	putc.c		queue.c		read.c		\
	ready.c		receive.c	recvclr.c	recvtim.c	\
	remove.c	rename.c	resched.c	resume.c	\
	scount.c	screate.c	sdelete.c	seek.c		\
	send.c		sendf.c		setdev.c	setnok.c	\
	signal.c	signaln.c	sleep.c		sleep10.c	\
	sleep100.c	sreset.c	ssclock.c	suspend.c	\
	unsleep.c	userret.c	wait.c		wakeup.c	\
	write.c		xdone.c		syslog.c	getuser.c	\
	getuid.c	noclose.c	nocntl.c	nogetc.c	\
	noopen.c	noputc.c	noread.c	noseek.c	\
	nowrite.c	noiint.c	nooint.c

TCPD =	tcballoc.c	tcbdealloc.c	tcpbind.c	\
	tcpclose.c	tcpcntl.c	tcpcon.c	tcpgetc.c	\
	tcpgetdata.c	tcpgetspace.c	tcpinit.c	tcplq.c		\
	tcpmcntl.c	tcpmopen.c	tcpnxtp.c	tcpputc.c	\
	tcpread.c	tcpserver.c	\
	tcpstat.c	tcpuopt.c	tcpwr.c		tcpwrite.c

TTY =	ttyalloc.c	ttycntl.c	ttygetc.c	ttyiin.c	\
	ttyinit.c	ttynew.c	ttyopen.c	ttyputc.c	\
	ttyread.c	ttywrite.c	ttyoin.c

SNMP =	a1rwint.c	a1rwlen.c	a1rwoid.c	a1rwval.c	\
	mksnmp.c	sae_findn.c	sae_get.c	sae_getf.c	\
	sae_getn.c	sae_match.c	sae_set.c	sat_findn.c	\
	sat_get.c	sat_getf.c	sat_getn.c	sat_match.c	\
	sat_set.c	sif_get.c	sif_getf.c	sif_getn.c	\
	sif_match.c	sif_set.c	sna2b.c		snb2a.c		\
	snclient.c	snerr.c		snfreebl.c	snhash.c	\
	sninit.c	snleaf.c	snmib.c		snoip.c		\
	snparse.c	snprint.c	snrslv.c	sntable.c	\
	srt_findn.c	srt_get.c	srt_getf.c	srt_getn.c	\
	srt_match.c	srt_set.c	stc_findn.c	stc_get.c	\
	stc_getf.c	stc_getn.c	stc_match.c	stc_set.c	\
	snm_get.c	snm_getf.c	snm_getn.c	snm_match.c	\
	snm_set.c	sud_get.c	sud_getf.c	sud_getn.c	\
	sud_match.c	sud_set.c	sud_findn.c	snm_findn.c

ETH =	ue_intr.c	ue_write.c	ue_init.c	ue_cntl.c	\
	ue_demux.c	ue_wstrt.c	\
	ee_intr.c	ee_write.c	ee_init.c	ee_cntl.c	\
	ee_demux.c	ee_wstrt.c	ee_rom.c	ee_cmd.c	\
	ee_mcast.c

SRC = ${ARP} ${COM} ${CON} ${DGRAM} ${ICMP} ${IGMP} ${IP} ${NA} 	\
	${NET}	${RFS} ${SNMP} ${SYS} ${TCPD} ${TCP} ${TTY} ${UDP}	\
	${DEBUG} ${OSPF}

COMOBJ = comcntl.o	comgetc.o	comiin.o	cominit.o	\
	cominput.o	comoutput.o	comread.o	comint.o	\
	comintr.o

CONOBJ = kbmcntl.o	kbmgetc.o	kbmiin.o	kbminit.o	\
	kbminput.o	kbmoutput.o	kbmread.o	kbscan.o	\
	kbmint.o

DEBUGOBJ = arpdump.o	hexdump.o	icmpdump.o	igmpdump.o	\
	ipdump.o	ospfdump.o	pdump.o		tcpdump.o	\
	udpdump.o

DGRAMOBJ = dgalloc.o	dgclose.o	dgcntl.o	dgdump.o	\
	dginit.o	dgmcntl.o	dgmopen.o	\
	dgread.o	dgwrite.o

ARPOBJ = arp_in.o	arpadd.o	arpalloc.o	arpdq.o		\
	arpfind.o	arpinit.o	arpprint.o	arpqsend.o	\
	arpsend.o	arptimer.o

RTOBJ = rtadd.o		rtdel.o		rtdump.o	rtfree.o	\
	rtget.o		rthash.o	rtinit.o	rtnew.o		\
	rttimer.o

IPOBJ = ip_in.o		ipdbc.o		ipdoopts.o	ipdstopts.o	\
	ipfadd.o	ipfcons.o	ipfhcopy.o	ipfinit.o	\
	ipfjoin.o	ipfsend.o	ipftimer.o	ipgetp.o	\
	iph2net.o	ipnet2h.o	ipproc.o	ipputp.o	\
	ipreass.o	ipredirect.o	ipsend.o	\
	isbrc.o		${RTOBJ}

ICOBJ = icerrok.o	icmp.o		icmp_in.o	icredirect.o	\
	icsetbuf.o	icsetdata.o	icsetsrc.o

IGOBJ =	hgadd.o		hgarpadd.o	hgarpdel.o	\
	hginit.o	hgjoin.o	\
	hgleave.o	igmp.o		igmp_in.o	hgprint.o	\
	hglookup.o	igmp_update.o	hgrand.o	igmp_settimers.o \

TMOBJ = tcptimer.o	tmclear.o	tmleft.o	tmset.o		\
	tqdump.o

TCPOBJ = tcp_in.o	tcpabort.o	tcpacked.o	tcpackit.o	\
	tcpcksum.o	tcpclosed.o	tcpclosewait.o	tcpclosing.o	\
	tcpdata.o	tcpdemux.o	tcpdodat.o	tcpestablished.o\
	tcpfin1.o	tcpfin2.o	tcph2net.o	tcphowmuch.o	\
	tcpidle.o	tcpinp.o	tcpiss.o	tcpkick.o	\
	tcpkilltimers.o	tcplastack.o	tcplisten.o	tcpnet2h.o	\
	tcpok.o		tcpopts.o	tcpostate.o	tcpout.o	\
	tcppersist.o	tcpreset.o	tcprexmt.o	\
	tcprmss.o	tcprtt.o	tcprwindow.o	tcpsend.o	\
	tcpsmss.o	tcpsndlen.o	\
	tcpswindow.o	tcpswitch.o	tcpsync.o	tcpsynrcvd.o	\
	tcpsynsent.o	tcptimewait.o	tcpwait.o	tcpwakeup.o	\
	tcpwinit.o	tcpxmit.o	tfcoalesce.o	tfinsert.o	\
	${TMOBJ}

OSPFOBJ = ospf_hin.o	ospf_hsend.o	ospf_in.o	fcksum.o	\
	ospfcheck.o	if_elect.o	ospfhello.o	ospfhtmpl.o	\
	ospfifinit.o	ospfinit.o	ospf.o		ospfnet2h.o	\
	ospftimer.o	nb_add.o	nb_switch.o	nb_reform.o	\
	nb_aok.o	dd_queue.o	dd_xmit.o	lss_build.o	\
	ospf_ddin.o	ospfddtmpl.o	nb_rexmt.o	nb_clearl.o	\
	nb_makel.o	lsa_xmit.o	nb_mismatch.o	if_elect1.o	\
	ddi_exstart.o	ddi_exchng.o	lsr_in.o	db_lookup.o	\
	db_update.o	ddi_full.o	db_new.o	db_init.o	\
	lsa_add.o	lsa_send.o	ospflstmpl.o	lsu_in.o	\
	lsack_in.o	db_nlink.o	db_rlink.o	db_resync.o	\
	lsr_queue.o	lsr_add.o	lsr_xmit.o	ospflsrtmpl.o	\
	lsr_check.o

UDPOBJ = udp_in.o	udpcksum.o	udph2net.o	udpnet2h.o	\
	udpnxtp.o	udpsend.o	upalloc.o	

NETOBJ = cksum.o	dnparse.o	dot2ip.o	\
	getiaddr.o	ethmatch.o	\
	getname.o	getnet.o	getutim.o	initgate.o	\
	inithost.o	ip2dot.o	ip2name.o	local_out.o	\
	name2ip.o	netdump.o	netmask.o	netmatch.o	\
	netnum.o	netstart.o	netwrite.o	ni_in.o		\
	othinit.o	othwrite.o	rarp_in.o	rarpsend.o	\
	setmask.o	slowtimer.o	ethmcast.o

NAOBJ = echod.o		egp.o		fingerd.o	lfing.o		\
	ripadd.o	ripcheck.o	ripifset.o	ripin.o		\
	ripmetric.o	ripok.o		ripout.o	riprecv.o	\
	riprepl.o	ripsend.o	ripstart.o	rwho.o		\
	rwhod.o		rwhoind.o	snmpd.o		udpecho.o

RFSOBJ = mount.o	rfalloc.o	rfclose.o	rfcntl.o	\
	rfdump.o	rfgetc.o	rfinit.o	rfio.o		\
	rfmkpac.o	rfopen.o	rfputc.o	rfread.o	\
	rfseek.o	rfsend.o	rfwrite.o	unmount.o	

SYSOBJ = autostart.o	\
	chprio.o	ckmode.o	clkinit.o	close.o		\
	conf.o		control.o	create.o	\
	dotrace.o	evec.o		freebuf.o	freemem.o	\
	getbuf.o	getc.o		getdmem.o	getitem.o	\
	getmem.o	getpid.o	getprio.o	getstk.o	\
	gettime.o	gpq.o		i386.o		init.o		\
	insert.o	insertd.o	ioerr.o		\
	ionull.o	kill.o		kprintf.o	stacktrace.o	\
	kputc.o		mark.o		mkdpool.o	mkpool.o	\
	naminit.o	nammap.o	namopen.o	namrepl.o	\
	newqueue.o	open.o		panic.o		pcount.o	\
	pcreate.o	pdelete.o	pinit.o		poolinit.o	\
	preceive.o	preset.o	printq.o	psend.o		\
	ptclear.o	putc.o		queue.o		read.o		\
	ready.o		receive.o	recvclr.o	recvtim.o	\
	remove.o	rename.o	resched.o	resume.o	\
	scount.o	screate.o	sdelete.o	seek.o		\
	send.o		sendf.o		setdev.o	setnok.o	\
	signal.o	signaln.o	sleep.o		sleep10.o	\
	sleep100.o	sreset.o	ssclock.o	suspend.o	\
	unsleep.o	userret.o	wait.o		wakeup.o	\
	write.o		xdone.o		syslog.o	getuid.o	\
	getuser.o	noclose.o	nocntl.o	nogetc.o	\
	noopen.o	noputc.o	noread.o	noseek.o	\
	nowrite.o	noiint.o	nooint.o

TCPDOBJ = tcballoc.o	tcbdealloc.o	tcpbind.o	\
	tcpclose.o	tcpcntl.o	tcpcon.o	tcpgetc.o	\
	tcpgetdata.o	tcpgetspace.o	tcpinit.o	tcplq.o		\
	tcpmcntl.o	tcpmopen.o	tcpnxtp.o	tcpputc.o	\
	tcpread.o	tcpserver.o	\
	tcpstat.o	tcpuopt.o	tcpwr.o		tcpwrite.o

TTYOBJ = ttyalloc.o	ttycntl.o	ttygetc.o	ttyiin.o	\
	ttyinit.o	ttynew.o	ttyopen.o	ttyputc.o	\
	ttyread.o	ttywrite.o	ttyoin.o

SNOBJ = a1rwint.o	a1rwlen.o	a1rwoid.o	a1rwval.o	\
	mksnmp.o	sae_findn.o	sae_get.o	sae_getf.o	\
	sae_getn.o	sae_match.o	sae_set.o	sat_findn.o	\
	sat_get.o	sat_getf.o	sat_getn.o	sat_match.o	\
	sat_set.o	sif_get.o	sif_getf.o	sif_getn.o	\
	sif_match.o	sif_set.o	sna2b.o		snb2a.o		\
	snclient.o	snerr.o		snfreebl.o	snhash.o	\
	sninit.o	snleaf.o	snmib.o		snoip.o		\
	snparse.o	snprint.o	snrslv.o	sntable.o	\
	srt_findn.o	srt_get.o	srt_getf.o	srt_getn.o	\
	srt_match.o	srt_set.o	stc_findn.o	stc_get.o	\
	stc_getf.o	stc_getn.o	stc_match.o	stc_set.o	\
	snm_get.o	snm_getf.o	snm_getn.o	snm_match.o	\
	snm_set.o	sud_get.o	sud_getf.o	sud_getn.o	\
	sud_match.o	sud_set.o	sud_findn.o	snm_findn.o

ETHOBJ = ue_intr.o	ue_write.o	ue_init.o	ue_cntl.o	\
	ue_int.o	ue_demux.o	ue_wstrt.o	\
	ee_intr.o	ee_write.o	ee_init.o	ee_cntl.o	\
	ee_int.o	ee_demux.o	ee_wstrt.o	ee_mcast.o	\
	ee_rom.o	ee_cmd.o

XOBJ = startup.o intr.o initialize.o clkint.o ctxsw.o

OBJ = ${ARPOBJ} ${COMOBJ} ${CONOBJ} ${DGRAMOBJ} ${ICOBJ} ${IGOBJ}	\
	${IPOBJ} ${NAOBJ} ${NETOBJ} ${RFSOBJ} ${SNOBJ}		\
	${SYSOBJ} ${TCPDOBJ} ${TCPOBJ} ${TTYOBJ} ${UDPOBJ} ${DEBUGOBJ}	\
	${OSPFOBJ} ${ETHOBJ} conf.o

all: xinu FRC

xinu: libx.a ${XOBJ} user.o sh.o Makefile
	ld -Bstatic -Z -o xinu -e _start -X ${XOBJ} libx.a user.o libx.a sh.o ${LIB}/libxc.a \
		libx.a

arp:	${ARPOBJ}
con:	${CONOBJ}
dgram:	${DGRAMOBJ}
icmp:	${ICOBJ}
igmp:	${IGOBJ}
ip:	${IPOBJ}
net:	${NETOBJ}
netapp:	${NAOBJ}
rfs:	${RFSOBJ}
snmp:	${SNOBJ}
sys:	${SYSOBJ}
tcp:	${TCPOBJ}
tcpd:	${TCPDOBJ}
tty:	${TTYOBJ}
udp:	${UDPOBJ}
ospf:	${OSPFOBJ}

install: xinu FRC
	cp xinu /floppy/xinu

clean: FRC
	-rm -rf *.o *.ln *.errs Makefile.bak *.a a.out core errs pm.out	\
		conf.c ../h/conf.h tags xinu typescript* version
	(cd ../shell; make clean)

depend: conf.c FRC
	mkdep ${DEFS} ${INCLUDE} ../arp/*.c ../com/*.c ../kbm/*.c	\
	../dgram/*.c    \
        *.c ../icmp/*.c ../igmp/*.c ../ip/*.c ../net/*.c \
	../netapp/*.c  \
        ../rfs/*.c ../snmp/*.c ../sys/*.c ../tcp/*.c ../tcpd/*.c        \
        ../tty/*.c ../udp/*.c ../ospf/*.c ../debug/*.c ../ether/ue/*.c	\
	../ether/ee/*.c
	(cd ../shell; make depend)

#
# the directory list below should match the "SRCDIR" list below, + ../h
#
tags: FRC
	ctags ${SRC}

../h/conf.h conf.c: Configuration
	../config/config; rm -f ../sys/conf.c;ln -s ../compile/conf.c ../sys/conf.c

sh.o: FRC
	(cd ../shell; make install)

libx.a: $(OBJ) 
	/bin/rm -f  libx.a
	$(AR) cr libx.a	`lorder $(OBJ) | tsort`
	ranlib libx.a

intr.o: ../sys/intr.s
	${CPP} ${SDEFS} ../sys/intr.s | ${AS} -o intr.o

cksum.o: ../net/cksum.s
	${CPP} ${SDEFS} ../net/cksum.s | ${AS} -o cksum.o

clkint.o: ../sys/clkint.s
	${CPP} ${SDEFS} ../sys/clkint.s | ${AS} -o clkint.o

ctxsw.o: ../sys/ctxsw.s
	${CPP} ${SDEFS} ../sys/ctxsw.s | ${AS} -o ctxsw.o

startup.o: ../sys/startup.s
	${CPP} ${SDEFS} -DBRELOC=${BRELOC} -DREL ../sys/startup.s | ${AS} -o startup.o

comint.o: ../com/comint.s
	${CPP} ${SDEFS} ../com/comint.s | ${AS} -o comint.o

kbmint.o: ../kbm/kbmint.s
	${CPP} ${SDEFS} ../kbm/kbmint.s | ${AS} -o kbmint.o

ue_int.o: ../ether/ue/ue_int.s
	${CPP} ${SDEFS} ../ether/ue/ue_int.s | ${AS} -o ue_int.o

ee_int.o: ../ether/ee/ee_int.s
	${CPP} ${SDEFS} ../ether/ee/ee_int.s | ${AS} -o ee_int.o

xinu.o: $(XOBJ)
	ld -r $(XOBJ) -o xinu.o

initialize.o: libx.a startup.o 
	sh mkvers.sh
	${CC} -c ${CFLAGS} -DVERSION=\""`cat version`"\" -DREVISION="`cat rn`" \
		../sys/initialize.c

#${ARPOBJ}:
#	 ${CC} ${CFLAGS} ../arp/`basename $@ .o`.[cs]
#${COMOBJ}:
#	 ${CC} ${CFLAGS} ../com/`basename $@ .o`.[cs]
#${CONOBJ}:
#	 ${CC} ${CFLAGS} ../kbm/`basename $@ .o`.[cs]
#${DEBUGOBJ}:
#	 ${CC} ${CFLAGS} ../debug/`basename $@ .o`.[cs]
#${DGRAMOBJ}:
#	 ${CC} ${CFLAGS} ../dgram/`basename $@ .o`.[cs]
#${ICOBJ}:
#	 ${CC} ${CFLAGS} ../icmp/`basename $@ .o`.[cs]
#${IGOBJ}:
#	 ${CC} ${CFLAGS} ../igmp/`basename $@ .o`.[cs]
#${IPOBJ}:
#	 ${CC} ${CFLAGS} ../ip/`basename $@ .o`.[cs]
#${NAOBJ}:
#	 ${CC} ${CFLAGS} ../netapp/`basename $@ .o`.[cs]
#${NETOBJ}:
#	 ${CC} ${CFLAGS} ../net/`basename $@ .o`.[cs]
#${OSPFOBJ}:
#	 ${CC} ${CFLAGS} ../ospf/`basename $@ .o`.[cs]
#${RFSOBJ}:
#	 ${CC} ${CFLAGS} ../rfs/`basename $@ .o`.[cs]
#${SNOBJ}:
#	 ${CC} ${CFLAGS} ../snmp/`basename $@ .o`.[cs]
#${SYSOBJ} intialize.o startup.o:
#	 ${CC} ${CFLAGS} ../sys/`basename $@ .o`.[cs]
#${TCPDOBJ}:
#	 ${CC} ${CFLAGS} ../tcpd/`basename $@ .o`.[cs]
#${TCPOBJ}:
#	 ${CC} ${CFLAGS} ../tcp/`basename $@ .o`.[cs]
#${TTYOBJ}:
#	 ${CC} ${CFLAGS} ../tty/`basename $@ .o`.[cs]
#${UDPOBJ}:
#	 ${CC} ${CFLAGS} ../udp/`basename $@ .o`.[cs]

startup.o: ../sys/startup.s

intr.s: ../sys/intr.s

FRC:
