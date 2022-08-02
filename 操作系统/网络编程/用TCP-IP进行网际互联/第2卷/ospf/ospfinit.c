/* ospfinit.c - ospfinit */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

void ospfifinit(int, unsigned);
int db_init(struct ospf_ar *);

/*------------------------------------------------------------------------
 * ospfinit - initialize OSPF data structures
 *------------------------------------------------------------------------
 */
void
ospfinit(void)
{
	struct ospf_ar	*par;
	int		ifn, arn;

	ospf_lspool = mkpool(sizeof(struct ospf_db), LSABUFS);

	for (arn=0; arn<NAREA; ++arn) {	/* init per-area data */
		par = &ospf_ar[arn];
		db_init(par);
	}
	for (ifn=0; ifn<NIF; ++ifn) {	/* init per-interface data */
		if (ifn == NI_LOCAL)
			continue;
		ospfifinit(0, ifn);
	}
}

struct ospf_ar	ospf_ar[NAREA];
int		ospf_lspool;
