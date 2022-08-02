/* lsr_check.c - lsr_check */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  lsr_check - return TRUE if head of LSR list is satisfied
 *------------------------------------------------------------------------
 */
int
lsr_check(struct ospf_nb *pnb)
{

#ifdef notdef
	plsr = (char *)po + po->ospf_len;
	plsr->lsr_type = plss->lss_type;
	plsr->lsr_lsid = plss->lss_lsid;
	plsr->lsr_rid = plss->lss_rid;
	po->ospf_len += LSRLEN;
	return pep;
#endif
	return 1;
}
