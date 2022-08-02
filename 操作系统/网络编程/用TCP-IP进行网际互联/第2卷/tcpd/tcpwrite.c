/* tcpwrite.c - tcpwrite */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpwrite  -  write one buffer from a TCP pseudo-device
 *------------------------------------------------------------------------
 */
int
tcpwrite(struct devsw *pdev, unsigned char *pch, unsigned len)
{
	return tcpwr(pdev, pch, len, TWF_NORMAL);
}
