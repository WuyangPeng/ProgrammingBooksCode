/* sofsm.c */

#include <sys/types.h>

#include <stdio.h>

#include "telnet.h"
#include "tnfsm.h"

/* Special chars: */
char	t_flushc, t_intrc, t_quitc, sg_erase, sg_kill;

extern int	soputc(FILE *,FILE *,int), scrinit(FILE *,FILE *,int),
		scrgetc(FILE *,FILE *,int), scrwrap(FILE *,FILE *,int),
		unscript(FILE *,FILE *,int), dcon(FILE *,FILE *,int),
		suspend(FILE *,FILE *,int), status(FILE *,FILE *,int),
		sonotsup(FILE *,FILE *,int), no_op(FILE *, FILE *, int),
		tnabort(FILE *,FILE *,int);

struct fsm_trans sostab[] = {
        /* State        Input           Next State      Action  */
        /* ------       ------          -----------     ------- */
/* Data Input */
	{ KSREMOTE,	KCESCAPE,	KSLOCAL,	no_op		},
	{ KSREMOTE,	KCANY,		KSREMOTE,	soputc		},
/* Local Escape Commands */
	{ KSLOCAL,	KCSCRIPT,	KSCOLLECT,	scrinit		},
	{ KSLOCAL,	KCUNSCRIPT,	KSREMOTE,	unscript	},
	{ KSLOCAL,	KCESCAPE,	KSREMOTE,	soputc		},
	{ KSLOCAL,	KCDCON,		KSREMOTE,	dcon		},
	{ KSLOCAL,	KCSUSP,		KSREMOTE,	suspend		},
	{ KSLOCAL,	KCSTATUS,	KSREMOTE,	status		},
	{ KSLOCAL,	KCANY,		KSREMOTE,	sonotsup	},
/* Script Filename Gathering */
	{ KSCOLLECT,	KCNL,		KSREMOTE,	scrwrap		},
	{ KSCOLLECT,	KCANY,		KSCOLLECT,	scrgetc		},

	{ FSINVALID,	KCANY,		FSINVALID,	tnabort		},
};

#define	NTRANS	(sizeof(sostab)/sizeof(sostab[0]))

int	sostate;
u_char	sofsm[NKSTATES][NCHRS];
