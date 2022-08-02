/* igmpdump.c - igmpdump */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <igmp.h>

/*------------------------------------------------------------------------
 * igmpdump - pretty-print an IGMP packet
 *------------------------------------------------------------------------
 */
int igmpdump(pig, dlen)
struct igmp	*pig;
int		dlen;
{
	int	hlen = sizeof(struct igmp);
	int	t;

	t = IG_TYP(pig);
	kprintf("IGMP:\tversion %d type %d (%s)\n", IG_VER(pig), t,
		(t == IGT_HQUERY)? "Query" : (t == IGT_HREPORT) ? "Report"
			: "Bogus");
	kprintf("IGMP: cksum %x\thga %X\n", pig->ig_cksum,
		*((int *)pig->ig_gaddr));
#ifdef notdef
	if (dlen - hlen) {
		kprintf("IGMP (bogus appended data)\n");
		hexdump(pig + hlen, dlen - hlen);
	}
#endif
}
