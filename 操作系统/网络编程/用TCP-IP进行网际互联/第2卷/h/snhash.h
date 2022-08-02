/* snhash.h */

struct snhnode {			/* hash table node structure	*/
	struct mib_info *sh_mip;	/* points to a mib record	*/
	struct snhnode *sh_next;	/* next node in this hash bucket*/
};

#define S_HTABSIZ	101		/* hash table size - a prime #	*/
#define S_HTRADIX	21		/* hash table radix		*/

#define S_NUMTABS	7		/* number of table objects	*/

extern	struct	snhnode *snhtab[];	/* the hash table		*/
