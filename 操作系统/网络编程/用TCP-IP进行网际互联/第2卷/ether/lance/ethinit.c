/* ethinit.c - ethinit */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <idprom.h>
#include <q.h>

struct idprom idprom;

/* local header trimmed version */
#undef	EP_MAXLEN
#define	EP_MAXLEN	(14+EP_DLEN+EP_CRC)	/* ether hdr,data,crc	*/

int ethint();

/*------------------------------------------------------------------------
 *  ethinit  -  initialize ethernet I/O device and buffers
 *------------------------------------------------------------------------
 */
ethinit(devptr)
struct	devsw	*devptr;
{
    struct	etblk	*etptr;
    struct	le_device *le;
    struct	le_init_block *ib;
    struct	le_md	(*pmdrecv)[];
    struct	le_md	*pmdxmit;
    struct	le_md	*pmd;
    struct	bre	*pbre;
    int		i;
    char	*pbufr;
    char	*pbuft;

kprintf("ethinit\n");
return;
#ifdef DEBUG
    kprintf("ethinit(dev) called\n");
#endif
    etptr = &eth[devptr->dvminor];

#ifdef notdef
    /* read the ID prom */
    getidprom(&idprom,sizeof (struct idprom));
    if (idprom.id_format != 1) {
	panic("Can't read ID prom\n");
    }
#endif

    le = (struct le_device *) devptr->dvcsr;
    ib = (struct le_init_block *) getdmem(sizeof(struct le_init_block));

    /* allocate the ring buffers */
    /* we fudge, because these MUST be on a 4 word boundry */
    pmdrecv = (struct le_md (*)[])
      ((getdmem(7+sizeof(struct le_md)*EP_NUMRCV)+7)&~(unsigned long) 7);
    pmdxmit = (struct le_md *)
      ((getdmem(7+sizeof(struct le_md))+7) & ~(unsigned long) 7);

    /* allocate the LANCE buffers */
    pbufr = (char *) getdmem(EP_NUMRCV*EP_MAXLEN);
    pbuft = (char *) getdmem(EP_MAXLEN);

    /* zero-out the init block and ring pointers */
    bzero(ib,sizeof(struct le_init_block));
    for (i=0; i<EP_NUMRCV; ++i)
      bzero(&(*pmdrecv)[i],sizeof(struct le_md));
    bzero(pmdxmit,sizeof(struct le_md));

    /* set the physical address for this machine */
    ib->ib_padr[0] = idprom.id_ether[1]; /* must byte swap */
    ib->ib_padr[1] = idprom.id_ether[0];
    ib->ib_padr[2] = idprom.id_ether[3];
    ib->ib_padr[3] = idprom.id_ether[2];
    ib->ib_padr[4] = idprom.id_ether[5];
    ib->ib_padr[5] = idprom.id_ether[4];

    etptr->etdescr = "SMI, Sun 3";
    /* set the etblk structure addresses */
    blkcopy(etptr->etpaddr, idprom.id_ether, EP_ALEN);
    blkcopy(etptr->etbcast, EP_BRC, EP_ALEN);

    /* initialize the logical address filter */
    blkcopy(etptr->etfilter, "\0\0\0\0\0\0\0\0", 8);
    blkcopy(ib->ib_ladrf, "\0\0\0\0\0\0\0\0", 8);


#if	Noth > 0
    /* zero etoth pointers */
    for (i=0; i<Noth; ++i)
	etptr->etoth[i] = 0;
#endif	/* Noth > 0 */

    /* set up receive ring */
    ib->ib_rdrp.drp_len = EP_NUMRCVL2;
    ib->ib_rdrp.drp_laddr = low16((long)pmdrecv&DMA_MASK);
    ib->ib_rdrp.drp_haddr = hi8((long)pmdrecv&DMA_MASK);

    /* set up xmit ring */
    ib->ib_tdrp.drp_len = 0;	/* 0 means 2^^0 == 1 buffer in ring */
    ib->ib_tdrp.drp_laddr = low16((long)pmdxmit&DMA_MASK);
    ib->ib_tdrp.drp_haddr = hi8((long)pmdxmit&DMA_MASK);

    /* set up the receive ring buffers */
    for (i=0; i<EP_NUMRCV; ++i) {
	/* set up the LANCE info */
	pmd = &(*pmdrecv)[i];
	pmd->lmd_ladr = low16((long)pbufr&DMA_MASK);
	pmd->lmd_hadr = hi8((long)pbufr&DMA_MASK);
	pmd->lmd_bcnt = -EP_MAXLEN+EP_CRC;	/* CRC not included	*/
	pmd->lmd_mcnt = 0;
	pmd->lmd_flags = LMD_OWN;

	/* set up the XINU info */
	pbre = &(etptr->etbrr[i]);
	pbre->pmd = pmd;
	pbre->buf = pbufr;
	pbre->flags = 0;

	pbufr += EP_MAXLEN;
    }

    /* set up the xmit ring buffers */
    /* set up the LANCE info */
    pmd = pmdxmit;
    pmd->lmd_ladr = low16((long)pbuft&DMA_MASK);
    pmd->lmd_hadr = hi8((long)pbuft&DMA_MASK);
    pmd->lmd_bcnt = -EP_MAXLEN+EP_CRC;		/* CRC not included	*/
    pmd->lmd_mcnt = 0;
    pmd->lmd_flags = 0;

    /* set up the XINU info */
    pbre = &etptr->etbrt[0];
    pbre->pmd = pmd;
    pbre->buf = pbuft;
    pbre->flags = 0;


#ifdef DEBUG
    kprintf("Lance device at address 0x%x\n",(unsigned long) le);
    kprintf("Interrupt vector: 0x%x\n",devptr->dvivec);
    kprintf("Init block at 0x%lx\n",(unsigned long) ib);
    kprintf("recv ring at 0x%lx\n",(unsigned long) pmdrecv);
    kprintf("xmit ring at 0x%lx\n",(unsigned long) pmdxmit);
    for (i=0; i<EP_NUMRCV; ++i)
      kprintf("buf %d  pmd: 0x%x  buf: 0x%x-0x%x   flags: %d\n",
	      i,
	      etptr->etbrr[i].pmd,
	      etptr->etbrr[i].buf,
	      (long)etptr->etbrr[i].buf+EP_MAXLEN-1,
	      etptr->etbrr[i].flags);
      kprintf(" tbuf  pmd: 0x%x  buf: 0x%x-0x%x   flags: %d\n",
	      etptr->etbrt[0].pmd,
	      etptr->etbrt[0].buf,
	      (long)etptr->etbrr[i].buf+EP_MAXLEN-1,
	      etptr->etbrt[0].flags);

    kprintf("\n");
#endif

    /* set up global information */
    devptr->dvioblk = (char *) etptr;
    etptr->etle   = le;
    etptr->etib   = ib;
    etptr->etdev  = devptr;
    etptr->etnextbuf = 0;
    etptr->etoutq = newq(ETOUTQSZ, QF_NOWAIT);
    etptr->etintf = -1;

    ethstrt(etptr);

    return OK;

}

#ifdef	Neth
struct	etblk	eth[Neth];
#endif


printcsr0(le,msg)
     struct le_device *le;
     char *msg;
{
    register short status;

    le->le_rap = LE_CSR0;
    status = le->le_rdp;

    kprintf("%s:  (%04b %04b %04b %04b)\n",
	    msg,
	    (int) ((status >>12) & 0x0f),
	    (int) ((status >>8) & 0x0f),
	    (int) ((status >>4) & 0x0f),
	    (int) (status & 0x0f)
	    );
}
