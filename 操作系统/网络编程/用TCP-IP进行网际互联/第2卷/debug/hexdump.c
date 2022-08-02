/* hexdump.c - hexdump */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#define	OPL	16		/* octets printed per line	*/

/*------------------------------------------------------------------------
 * hexdump - pretty-print a buffer in hexidecimal
 *------------------------------------------------------------------------
 */
int hexdump(buf, dlen)
unsigned char	*buf;
int		dlen;
{
	char	c[OPL+1];
	int	i, ct;

	if (dlen < 0) {
		kprintf("WARNING: computed dlen %d\n", dlen);
		dlen = 0;
	}
	for (i=0; i<dlen; ++i) {
		if (i == 0)
			kprintf("DATA: ", c);
		else if ((i % OPL) == 0) {
			c[OPL] = '\0';
			kprintf("\t\"%s\"\nDATA: ", c);
		}
		ct = buf[i] & 0xff;
		c[i % OPL] = (ct >= ' ' && ct <= '~') ? ct : '.';
		kprintf("%02x ", ct);
	}
	c[i%OPL] = '\0';
	for (; i % OPL; ++i)
		kprintf("   ");
	kprintf("\t\"%s\"\n\n", c);
}
