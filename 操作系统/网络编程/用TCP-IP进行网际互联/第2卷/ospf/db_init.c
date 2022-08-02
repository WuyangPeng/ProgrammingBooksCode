/* db_init.c - db_init */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mem.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  db_init - initialize an area's topological database
 *------------------------------------------------------------------------
 */
int
db_init(struct ospf_ar *par)
{
	int	i;

	par->ar_dbmutex = screate(1);
	par->ar_hmod = DBHTMOD;
	par->ar_htable = (struct ospf_db **)getmem(par->ar_hmod *
	    sizeof(struct ospf_db *));
	for (i=0; i<par->ar_hmod; ++i)
		par->ar_htable[i] = 0;
	par->ar_dblhead = 0;
}
