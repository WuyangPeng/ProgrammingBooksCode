/* tcpinit.c - tcpinit */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mark.h>

static MARKER tcpmark;

/*------------------------------------------------------------------------
 *  tcpinit  -  initialize TCP slave pseudo device marking it free
 *------------------------------------------------------------------------
 */
int
tcpinit(struct devsw *pdev)
{
	struct	tcb	*tcb;

	if (unmarked(tcpmark)) {
		mark(tcpmark);
		tcps_tmutex = screate(1);
		tcps_lqsize = 5;	/* default listen Q size	*/
	}
	pdev->dvioblk = (char *) (tcb = &tcbtab[pdev->dvminor]);
	tcb->tcb_dvnum = pdev->dvnum;
	tcb->tcb_state = TCPS_FREE;
	return OK;
}

#ifdef	Ntcp
struct	tcb	tcbtab[Ntcp];		/* tcp device control blocks	*/
#endif
