/* rwhod.c - rwhod */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <rwho.h>
#include <shell.h>
#include <sleep.h>
#include <date.h>

/*------------------------------------------------------------------------
 *  rwhod  -  Periodically clean cache and (optionally) send rwho packets
 *------------------------------------------------------------------------
 */
PROCESS
rwhod(void)
{
	STATWORD ps;    
	char	*p;
	int	i, j;
	struct	rwent	*rwptr;
	struct	rwent	*myptr;
	struct	rwhopac	*rpacptr;
	struct	rw_who	*rwwptr;
	struct	ep	*pep;
	u_long	now;
	int	len;

	/* Initialize rwho information */

	Rwho.rwnent = 1;
	Rwho.rwsend = TRUE;
	getutim(&Rwho.rwbtime);
	myptr = &Rwho.rwcache[0];

	myptr->rwboot = myptr->rwlast = myptr->rwslast = Rwho.rwbtime;
	for (i=0 ; i<3 ; i++)
		myptr->rwload[i] = 0L;
	myptr->rwusers = 1;

	for( ; TRUE ; sleep(RWDELAY) ) {
		if (getname(myptr->rwmach) == SYSERR)
			continue;
		if (p = index(myptr->rwmach, '.'))
			*p = '\0';
		getutim(&now);
		myptr->rwlast = myptr->rwslast = now;
		disable(ps);
		for (i=0 ; i<Rwho.rwnent ; i++) {
			rwptr = &Rwho.rwcache[i];
			if (now - rwptr->rwlast > RWMAXDT) {
				Rwho.rwnent--;
				for (j=i-- ; j<Rwho.rwnent ; j++)
				    Rwho.rwcache[j] = Rwho.rwcache[j+1];
			}
		}
		restore(ps);
		if (!Rwho.rwsend)
			continue;
		pep = (struct ep *)getbuf(Net.netpool);
		rpacptr = (struct rwhopac *)
			((struct udp *)
			(((struct ip *)pep->ep_data)->ip_data))->u_data;
		rpacptr->rw_vers = RWVERSION;
		rpacptr->rw_type= RWSTATUS;
		rpacptr->rw_sndtim = hl2net(now);
		rpacptr->rw_rtim = 0L;
		getname(rpacptr->rw_host);
		if (p = index(rpacptr->rw_host, '.'))
			*p = '\0';
		for (j=0 ; j<RWNLOAD ; j++)
			rpacptr->rw_load[j] = 0L;
		rpacptr->rw_btim = hl2net(Rwho.rwbtime);
		len = RWMINP;
		if ( marked(Shl.shmark) && Shl.shused ) {
			rwwptr = &rpacptr->rw_rww[0];
			strcpy (rwwptr->rw_tty, "Console");
			strncpy(rwwptr->rw_nam, Shl.shuser, RWNLEN);
			rwwptr->rw_ton = hl2net(Shl.shlogon);
			rwwptr->rw_idle = hl2net(now - Shl.shlast);
			len += sizeof(struct rw_who);
		}
		for (i=0; i<(Net.nif-1); ++i) {
			struct	ep	*pep2;

			if (i == NI_LOCAL)
				continue;
			if (nif[i].ni_state != NIS_UP)
				continue;
			pep2 = (struct ep *)getbuf(Net.netpool);
			if (pep2 == (struct ep *)SYSERR)
				break;
			memcpy(pep2, pep, EP_HLEN+IP_ALEN+len);
			udpsend(nif[i].ni_brc, UP_RWHO, UP_RWHO,
				pep2, len, 1);
		}
		udpsend(nif[i].ni_brc, UP_RWHO, UP_RWHO, pep,
			len, 1);
	}
}
