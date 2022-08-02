/* arpprint - arpprint */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <io.h>

#define HDR1 \
"Intf.   IP address     Physical Address   HW  Proto   State       TTL\n"
#define HDR2 \
"----- ---------------  -----------------  --  -----  --------  ---------\n"

static int	printone(int, struct arpentry *);

/*------------------------------------------------------------------------
 * arpprint - print the ARP table on descriptor fd
 *------------------------------------------------------------------------
 */
int
arpprint(int fd)
{
	int	i;

	write(fd, HDR1, strlen(HDR1));
	write(fd, HDR2, strlen(HDR2));
	for (i = 0; i<ARP_TSIZE; ++i)
		if (arptable[i].ae_state != AS_FREE)
			printone(fd, &arptable[i]);
	return OK;
}

char	*index(const char *, char);

/*------------------------------------------------------------------------
 * printone - print one entry in the ARP table
 *------------------------------------------------------------------------
 */
static int
printone(int fd, struct arpentry *pae)
{
	char	line[128], *p;
	int	i;

	sprintf(line, " %2d    ", pae->ae_pni - &nif[0]);
	p = index(line, '\0');

	for (i=0; i<pae->ae_prlen-1; ++i) {
		sprintf(p, "%u.", pae->ae_pra[i] & 0xff);
		p = index(p, '\0');
	}
	sprintf(p, "%u", pae->ae_pra[i]);
	for (i=strlen(line); i<23; ++i)
		line[i] = ' ';
	p = &line[23];

	for (i=0; i<pae->ae_hwlen-1; ++i) {
		sprintf(p, "%02x:", pae->ae_hwa[i] & 0xff);
		p = index(p, '\0');
	}
	sprintf(p, "%02x  %2d   %04x  %8s  ", pae->ae_hwa[i] & 0xff,
		pae->ae_hwtype, pae->ae_prtype,
		(pae->ae_state == AS_RESOLVED) ? "RESOLVED" : "PENDING");
	p = index(p, '\0');

	if (pae->ae_ttl == ARP_INF)
		strcpy(p, "(permanent)\n");
	else
		sprintf(p, "%8d s\n", pae->ae_ttl);
	return write(fd, line, strlen(line));
}
