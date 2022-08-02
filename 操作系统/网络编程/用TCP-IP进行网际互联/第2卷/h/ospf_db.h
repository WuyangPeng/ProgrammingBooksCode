/* ospf_db.h */

#define	LSABUFS		100	/* Number of LSA Buffers for Top. DBs	*/
#define	DBHTMOD		63	/* Database Hash Table Modulus		*/

#define	DBHASH(lsid)	((lsid) % DBHTMOD)

/* An Entry in the Topological Database */

struct ospf_db {
	struct ospf_lsa	 db_lsa;
	struct ospf_db	*db_hnext;	/* Next Entry in Hash Table	*/
	struct ospf_db	*db_lnext;	/* Next Entry in a Full Scan	*/
};

struct ospf_db *db_lookup(struct ospf_ar *, u_long, u_long);
struct ospf_db *db_new(struct ospf_ar *, struct ospf_lsa *);
int db_update(struct ospf_ar *, struct ospf_lsa *);
void db_nlink(struct ospf_if *), db_rlink(struct ospf_if *);
