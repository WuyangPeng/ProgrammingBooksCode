/* x_ospf.c - x_ospf */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#ifdef OSPF
#include <ospf.h>
#endif /* OSPF */

char	str[120];

#ifdef OSPF
static	int	noarg(), aarg(), darg(), iarg(), narg();
#endif /* OSPF */

/*------------------------------------------------------------------------
 *  x_ospf  -  (command ospf) print ospf status information
 *------------------------------------------------------------------------
 */
COMMAND
x_ospf(int stdin, int stdout, int stderr, int nargs, char *args[])
{
#ifdef	OSPF
	if (nargs == 1)
		return noarg(stdout, stderr);
	if (nargs > 2 || *args[1] != '-') {
		write(stderr, "usage: ospf -[adin]\n", 19);
		return 1;
	}
	switch (args[1][1]) {
	case	'a':	return aarg(stdout, stderr);
	case	'd':	return darg(stdout, stderr);
	case	'i':	return iarg(stdout, stderr);
	case	'n':	return narg(stdout, stderr);
	default:
		write(stderr, "usage: ospf -[adin]\n", 19);
		return 1;
	}
#else	/* OSPF */
	write(stderr, "ospf: no OSPF support installed\n", 32);
#endif	/* OSPF */
}

#ifdef OSPF
static	int
noarg(int stdout, int stderr)
{
}

static	int
aarg(int stdout, int stderr)
{
	struct ospf_ar	*par = &ospf_ar[0];
	int		i;

	for (i=0; i<NAREA; ++i, ++par) {
		sprintf(str, "Area %d: authype %d", par->ar_id,
			par->ar_authtype);
		write(stdout, str, strlen(str));
		if (par->ar_authtype == AU_PASSWD) {
			sprintf(str, "password \"%s\"\n", par->ar_auth);
			write(stdout, str, strlen(str));
		} else
			putc(stdout, '\n');
	}
}

#define IH1 \
"ifn    State   Prio    RID      DRID     BRID\n"
#define IH2 \
"---- --------- ----  -------- -------- --------\n"
static char *ifsnames[] = { "DOWN", "LOOP", "WAITING", "PT2PT", "DROTHER", 
	"BACKUP", "DESIGNATE" };

static	int
iarg(int stdout, int stderr)
{
	struct ospf_if	*pif = &ospf_if[0];
	int		ifn;

	write(stdout, IH1, sizeof(IH1));
	write(stdout, IH2, sizeof(IH2));
	for (ifn=0; ifn<NIF; ++ifn, ++pif) {
		sprintf(str, "%4d %9s %4d", ifn,
			ifsnames[pif->if_state], pif->if_prio);
		write(stdout, str, strlen(str));
		if (pif->if_state != IFS_DOWN) {
			sprintf(str, "  %08X %08X %08X",
				net2hl(pif->if_rid),
				net2hl(pif->if_drid),
				net2hl(pif->if_brid));
			write (stdout, str, strlen(str));
		}
		putc(stdout, '\n');
	}
}

char	*nbsnames[] = { "DOWN", "ATTEMPT", "INIT", "TWOWAY", "EXSTART",
			"EXCHANGE", "LOADING", "FULL" };

#define	NH1 \
"Intf.    State  Sequence    RID     DRID      BRID     prio  opts timeleft\n"
#define NH2 \
"-----  -------- --------- -------- --------  --------  ----  ---- --------\n"

static	int
narg(int stdout, int stderr)
{
	char	ipa[16];	/* "XXX.XXX.XXX.XXX\0" */
	struct ospf_nb	*pnb;
	int	i, ifn;

	write(stdout, NH1, strlen(NH1));
	write(stdout, NH2, strlen(NH2));
	for (ifn=0; ifn<NIF; ++ifn) {
		struct ospf_if	*pif = &ospf_if[ifn];

		if (pif->if_state == IFS_DOWN)
			continue;
		pnb = &pif->if_nbtab[1];
		for (i=0; i<MAXNBR; ++i, ++pnb) {
			if (pnb->nb_state == NBS_DOWN)
				continue;
			sprintf(str,
			    "%4d %9s  %8X  %08X %08X  %08X %5d %c%c%c%11d\n",
			    ifn, nbsnames[pnb->nb_state], pnb->nb_seq,
			    net2hl(pnb->nb_rid), net2hl(pnb->nb_drid),
			    net2hl(pnb->nb_brid),
			    pnb->nb_prio, pnb->nb_opts & NBO_T ? 'T' : ' ',
			    pnb->nb_opts & NBO_E ? 'E' : ' ',
			    pnb->nb_master ? 'M' : ' ', pnb->nb_lastheard);
			write(stdout, str, strlen(str));
		}
	}
	return(OK);
}

#define	DBH1 \
"  LSID      RID    Type    Seq     Age\n"
#define	DBH2 \
"-------- --------  ---- --------  ----\n"

static int dbprint1();

static	int
darg(int stdout, int stderr)
{
	struct ospf_ar	*par;
	struct ospf_db	*pdb;
	int		arn;

	for (arn=0; arn<NAREA; ++arn) {
		par = &ospf_ar[arn];
		sprintf(str, "Area %d\n----------\n", arn);
		write(stdout, str, strlen(str));
		write(stdout, DBH1, sizeof(DBH1));
		write(stdout, DBH2, sizeof(DBH2));
		wait(par->ar_dbmutex);
		for (pdb=par->ar_dblhead; pdb; pdb=pdb->db_lnext)
			dbprint1(stdout, pdb);
		signal(par->ar_dbmutex);
		
	}
}

static int
dbprint1(int stdout, struct ospf_db *pdb)
{
	struct ospf_lsa	*plsa = &pdb->db_lsa;

	sprintf(str, "%08X %08X %4d  %08X %3d\n",
		net2hl(plsa->lsa_lsid), net2hl(plsa->lsa_rid), plsa->lsa_type,
		plsa->lsa_seq, net2hs(plsa->lsa_age));
	write(stdout, str, strlen(str));
}
#endif	/* OSPF */
