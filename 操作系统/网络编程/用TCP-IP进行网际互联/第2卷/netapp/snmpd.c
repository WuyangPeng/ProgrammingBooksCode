/* snmpd.c - snmpd */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mem.h>
#include <io.h>

#ifdef	SNMP

#include <snmp.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * snmpd - open the SNMP port and handle incoming queries
 *------------------------------------------------------------------------
 */
int snmpd()
{
	int 		snmpdev, len;
	struct xgram	*query;
	struct req_desc	rqd;
	int reqtype;

	sninit();
	rqd.bindlf = (void *)NULL;
	query = (struct xgram *) getmem(sizeof (struct xgram));
	/* open the SNMP server port */
	if ((snmpdev = open(UDP, ANYFPORT, (void *)SNMPPORT)) == SYSERR)
		return SYSERR;
	while (TRUE) {
		/*
		 * In this mode, give read the size of xgram, it returns
		 * number of bytes of *data* in xgram.
		 */
		len = read(snmpdev, query, sizeof(struct xgram));
		++snmpInPkts;
		/* parse the packet into the request desc. structure */
		if (snparse(&rqd, (u_char *)query->xg_data, len) == SYSERR) {
			snfreebl(&rqd.bindlf);
			continue;
		}
		/* convert ASN.1 representations to internal forms */
		if (sna2b(&rqd) == SYSERR) {
			snfreebl(&rqd.bindlf);
			++snmpInASNParseErrs;
			continue;
		}
		if (snrslv(&rqd) == SYSERR) {
		        /* canberra bugfix, mksnmp cleans up dynamic */
		        /* memory that would otherwise be lost */
			query->xg_data[rqd.err_stat_pos] = rqd.err_stat;
			query->xg_data[rqd.err_idx_pos] = rqd.err_idx;
		        len = mksnmp(&rqd, (u_char *)query->xg_data, PDU_RESP);
			++snmpOutPkts;
			if (rqd.err_stat == SERR_TOO_BIG)
			    ++snmpOutTooBigs;
			if (rqd.err_stat == SERR_NO_SUCH)
			    ++snmpOutNoSuchNames;
			if (rqd.err_stat == SERR_BAD_VALUE)
			    ++snmpOutBadValues;
			if (write(snmpdev, query, len) == SYSERR)
				return SYSERR;
			snfreebl(&rqd.bindlf);
			continue;
		}
		reqtype = rqd.reqtype;
		len = mksnmp(&rqd, (u_char *)query->xg_data, PDU_RESP);
		if (len == SYSERR) {
			query->xg_data[rqd.pdutype_pos] = (u_char)PDU_RESP;
			query->xg_data[rqd.err_stat_pos] = rqd.err_stat;
			query->xg_data[rqd.err_idx_pos] = rqd.err_idx;
			++snmpOutPkts;
			if (rqd.err_stat == SERR_TOO_BIG)
			    ++snmpOutTooBigs;
			if (rqd.err_stat == SERR_NO_SUCH)
			    ++snmpOutNoSuchNames;
			if (rqd.err_stat == SERR_BAD_VALUE)
			    ++snmpOutBadValues;
			if (write(snmpdev, query, len) == SYSERR)
				return SYSERR;
			snfreebl(&rqd.bindlf);
			continue;	
		}
		++snmpOutPkts;
		switch (reqtype) {
		  case PDU_GETN:
		    ++snmpInTotalReqVars;
		    ++snmpInGetNexts;
		    break;
		  case PDU_GET:
		    ++snmpInTotalReqVars;
		    ++snmpInGetRequests;
		    break;
		  case PDU_SET:
		    ++snmpInTotalSetVars;
		    ++snmpInSetRequests;
		    break;
		}
		if (write(snmpdev, query, len) == SYSERR) {
			return SYSERR;
		}
		snfreebl(&rqd.bindlf);
	}
}
#endif	/* SNMP */
