/* ttfsm.c */

#include <sys/types.h>
#include <stdio.h>
#include "telnet.h"
#include "tnfsm.h"
#include "local.h"

extern int do_echo(FILE *,FILE *,int), do_noga(FILE *,FILE *,int),
	do_notsup(FILE *,FILE *,int), do_status(FILE *,FILE *,int),
	no_op(FILE *,FILE *,int), recopt(FILE *,FILE *,int),
	subend(FILE *,FILE *,int), subopt(FILE *,FILE *,int),
	tcdm(FILE *,FILE *,int), ttputc(FILE *,FILE *,int),
	will_notsup(FILE *,FILE *,int), will_termtype(FILE *,FILE *,int),
	will_txbinary(FILE *,FILE *,int), tnabort(FILE *,FILE *,int),
	do_txbinary(FILE *,FILE *,int);

struct fsm_trans ttstab[] = {
	/* State	Input		Next State	Action	*/
	/* ------	------		-----------	-------	*/
	{ TSDATA,	TCIAC,		TSIAC,		no_op		},
	{ TSDATA,	TCANY,		TSDATA,		ttputc 		},
	{ TSIAC,	TCIAC,		TSDATA,		ttputc		},
	{ TSIAC,	TCSB,		TSSUBNEG,	no_op		},
/* Telnet Commands */
	{ TSIAC,	TCNOP,		TSDATA,		no_op		},
	{ TSIAC,	TCDM,		TSDATA,		tcdm		},
/* Option Negotiation */
	{ TSIAC,	TCWILL,		TSWOPT,		recopt		},
	{ TSIAC,	TCWONT,		TSWOPT,		recopt		},
	{ TSIAC,	TCDO,		TSDOPT,		recopt		},
	{ TSIAC,	TCDONT,		TSDOPT,		recopt		},
	{ TSIAC,	TCANY,		TSDATA,		no_op		},
/* Option Subnegotion */
	{ TSSUBNEG,	TCIAC,		TSSUBIAC,	no_op		},
	{ TSSUBNEG,	TCANY,		TSSUBNEG,	subopt		},
	{ TSSUBIAC,	TCSE,		TSDATA,		subend		},
	{ TSSUBIAC,	TCANY,		TSSUBNEG,	subopt		},

	{ TSWOPT,	TOECHO,		TSDATA,		do_echo		},
	{ TSWOPT,	TONOGA,		TSDATA,		do_noga		},
	{ TSWOPT,	TOTXBINARY,	TSDATA,		do_txbinary	},
	{ TSWOPT,	TCANY,		TSDATA,		do_notsup	},

	{ TSDOPT,	TOTERMTYPE,	TSDATA,		will_termtype	},
	{ TSDOPT,	TOTXBINARY,	TSDATA,		will_txbinary	},
	{ TSDOPT,	TCANY,		TSDATA,		will_notsup	},

	{ FSINVALID,	TCANY,		FSINVALID,	tnabort		},
};

#define	NTRANS (sizeof(ttstab)/sizeof(ttstab[0]))

int	ttstate;
u_char	ttfsm[NTSTATES][NCHRS];
