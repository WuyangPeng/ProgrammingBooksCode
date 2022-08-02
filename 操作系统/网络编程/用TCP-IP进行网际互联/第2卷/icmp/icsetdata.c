/* icsetdata.c - icsetdata */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/* ECHOMAX must be an even number */
#define	ECHOMAX(pip)	(MAXLRGBUF-IC_HLEN-IP_HLEN(pip)-EP_HLEN-EP_CRC)

/*------------------------------------------------------------------------
 *  icsetdata -  set the data section. Return value is data length
 *------------------------------------------------------------------------
 */
int
icsetdata(int type, struct ip *pip, void *pa2)
{
	struct	icmp	*pic = (struct icmp *)pip->ip_data;
	int		i, len;

	switch (type) {
	case ICT_ECHORP:
		len = pip->ip_len - IP_HLEN(pip) - IC_HLEN;
		if (isodd(len))
			pic->ic_data[len] = 0;	/* so cksum works */
		return len;
	case ICT_DESTUR:
	case ICT_SRCQ:
	case ICT_TIMEX:
		pic->ic_mbz = 0;		/* must be 0 */
		break;
	case ICT_REDIRECT:
		pic->ic_gw = (IPaddr)pa2;
		break;
	case ICT_PARAMP:
		pic->ic_ptr = (u_char) ((unsigned)pa2 & 0xff);
		for (i=0; i<IC_PADLEN; ++i)
			pic->ic_pad[i] = 0;
		break;
	case ICT_MASKRP:
		memcpy(pic->ic_data, &pa2, IP_ALEN);
		break;
	case ICT_ECHORQ:
		if ((int)pa2 > ECHOMAX(pip))
			pa2 = (void *)ECHOMAX(pip);
		for (i=0; i<(int)pa2; ++i)
			pic->ic_data[i] = i;
		return (int)pa2;
	case ICT_MASKRQ:
		memcpy(pic->ic_data, &ip_anyaddr, IP_ALEN);
		return IP_ALEN;
	}
	return 0;
}
