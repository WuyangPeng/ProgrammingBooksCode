/* rfmkpac.c - rfmkpac */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*#define PRINTERRORS*/

static	struct	fpacket	packet;

/*------------------------------------------------------------------------
 *  rfmkpac  --  make a remote file request packet and send it
 *------------------------------------------------------------------------
 */
int
rfmkpac(int rop, char *rname, char *rpos, unsigned char *buff, unsigned len)
{
	struct	fphdr	*fptr;
	int	reqlen, rplylen;
#ifdef MIPS
	short	op;
#endif

	wait(Rf.rmutex);
	fptr = (struct fphdr *) &packet;
	fptr->f_op = hs2net(rop);
	fptr->f_pos = hl2net(*rpos);
	fptr->f_count = hs2net(len);
	strncpy(fptr->f_name, rname, RNAMLEN);
	reqlen = rplylen = FPHLEN + len;
	switch (rop) {

	    case FS_WRITE:
	    case FS_RENAME:
		if (len > RDATLEN) {
			signal(Rf.rmutex);
#if defined(DEBUG) || defined(PRINTERRORS)
			kprintf("rfmkpac(rename) ==> SYSERR, bad len %d\n",
				len);
#endif
			return(SYSERR);
			}	
		memcpy(packet.fpdata, buff, len);
		rplylen = FPHLEN;
		break;

	    case FS_CLOSE:
	    case FS_OPEN:
	    case FS_UNLINK:
	    case FS_MKDIR:
	    case FS_RMDIR:
	    case FS_ACCESS:
		rplylen = FPHLEN;
		/* fall through */
		
	    case FS_READ:
		if (len > RDATLEN) {
			signal(Rf.rmutex);
#if defined(DEBUG) || defined(PRINTERRORS)
			kprintf("rfmkpac ==> SYSERR, bad len %d\n", len);
#endif
			return(SYSERR);
		}
		reqlen = FPHLEN;
		break;

	    default:
	    	;
	}
	if (rfsend(fptr, reqlen, rplylen) == SYSERR ||
#ifdef MIPS   /* stupid MIPS compiler */
	    (op = net2hs(fptr->f_op)) == FS_ERROR) {
#else
	    net2hs(fptr->f_op) == (unsigned)FS_ERROR) {
#endif
		signal(Rf.rmutex);
#if defined(DEBUG) || defined(PRINTERRORS)
		kprintf("rfmkpac: returning SYSERR\n");
		if ((op = net2hs(fptr->f_op)) == FS_ERROR)
		    kprintf("rfmkpac: got FS_ERROR back, req:%d rep:%d\n",
			    reqlen, rplylen);
		    
#endif
		return(SYSERR);
	}
	switch (rop) {

	    case FS_READ:
		memcpy(buff, packet.fpdata, len);
		/* fall through */

	    case FS_WRITE:
		*rpos = net2hl(fptr->f_pos);
		len = net2hs(fptr->f_count);
		break;

	    default:
		len = OK;
	}
	signal(Rf.rmutex);
	return(len);
}
