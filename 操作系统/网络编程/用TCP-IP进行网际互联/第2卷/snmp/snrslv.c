/* snrslv.c - snrslv */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/* Set the error status and error index in a request descriptor. */
#define seterr(errval)		rqdp->err_stat = errval;	\
				rqdp->err_idx = i;

/*------------------------------------------------------------------------
 * snrslv - resolve the list of specified variable bindings
 *------------------------------------------------------------------------
 */
int
snrslv(struct req_desc *rqdp)
{
	struct 	snbentry *bl;
	struct 	mib_info *np;
	int	i, op, err;

	for (bl = rqdp->bindlf, i = 1; bl; bl = bl->sb_next, i++) {


		/* special case, getNext on 0 (or NULL) */
		/* returns getFirst on 1 */
		if (((bl->sb_oid.len == 0) ||
		     ((bl->sb_oid.len == 1) && (bl->sb_oid.id[0] == 0))) &&
		    (rqdp->reqtype == PDU_GETN)) {
		    bl->sb_oid.len = 1;
		    bl->sb_oid.id[0] = 1;
		} 

		/* use getmib to look up object id */
		if ((np = getmib(&bl->sb_oid)) == 0) {
			seterr(SERR_NO_SUCH);
		     	return SYSERR;
		}
		/* call function to apply specified operation		*/
		if (np->mi_func == 0) { /* objid is an aggregate	*/
			/* only getnext allows nonexistent names	*/
			if (rqdp->reqtype != PDU_GETN) {
				seterr(SERR_NO_SUCH);
				return SYSERR;
			}
			/* use getfirst for getnext on an aggregate */
			if ((err = ((*np->mi_next->mi_func)
				   (bl, np->mi_next, SOP_GETF)))) {
				seterr(err);
				return SYSERR;
			}
		} else { /* function in table ==> single item or table	*/
			switch (rqdp->reqtype) {
			case PDU_GET:	op = SOP_GET;	break;
			case PDU_GETN:	op = SOP_GETN;	break;
			case PDU_SET:	op = SOP_SET;	break;
		        default:
			  return(SYSERR);
			}
			/* use getfirst for getnext on table entry	*/
			if (oidequ(&bl->sb_oid, &np->mi_objid) &&
			    np->mi_vartype == T_TABLE) {
				if (op == SOP_GETN)
				    op = SOP_GETF;
			}
			if ((err = ((*np->mi_func)(bl, np, op)))) {
				seterr(err);
				return SYSERR;
			}
		}
	}
	return OK;
}
#endif	/* SNMP */
