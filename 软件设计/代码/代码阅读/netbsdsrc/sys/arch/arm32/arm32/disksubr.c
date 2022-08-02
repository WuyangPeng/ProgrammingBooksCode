/* $NetBSD: disksubr.c,v 1.6 1996/11/23 03:56:44 mark Exp $ */

/*
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * Copyright (c) 1995 Mark Brinicombe
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)ufs_disksubr.c	7.16 (Berkeley) 5/4/91
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/dkbad.h>
#include <sys/disklabel.h>
#include <sys/syslog.h>
#include <sys/device.h>
#include <sys/disk.h>

#define	b_cylin	b_resid

/*
 * static int filecore_checksum(u_char *bootblock)
 *
 * Calculates the filecore boot block checksum. This is used to validate
 * a filecore boot block on the disk.  If a boot block is validated then
 * it is used to locate the partition table. If the boot block is not
 * validated, it is assumed that the whole disk is NetBSD.
 *
 * The basic algorithm is:
 *
 *	for (each byte in block, excluding checksum) {
 *		sum += byte;
 *		if (sum > 255)
 *			sum -= 255;
 *	}
 *
 * That's equivalent to summing all of the bytes in the block
 * (excluding the checksum byte, of course), then calculating the
 * checksum as "cksum = sum - ((sum - 1) / 255) * 255)".  That
 * expression may or may not yield a faster checksum function,
 * but it's easier to reason about.
 *
 * Note that if you have a block filled with bytes of a single
 * value "X" (regardless of that value!) and calculate the cksum
 * of the block (excluding the checksum byte), you will _always_
 * end up with a checksum of X.  (Do the math; that can be derived
 * from the checksum calculation function!)  That means that
 * blocks which contain bytes which all have the same value will
 * always checksum properly.  That's a _very_ unlikely occurence
 * (probably impossible, actually) for a valid filecore boot block,
 * so we treat such blocks as invalid.
 */
static int
filecore_checksum(bootblock)
	u_char *bootblock;
{
	u_char byte0, accum_diff;
	u_int sum;
	int i;
    
	sum = 0;
	accum_diff = 0;
	byte0 = bootblock[0];

	/*
	 * Sum the contents of the block, keeping track of whether
	 * or not all bytes are the same.  If 'accum_diff' ends up
	 * being zero, all of the bytes are, in fact, the same.
	 */
	for (i = 0; i < 511; ++i) {
		sum += bootblock[i];
		accum_diff |= bootblock[i] ^ byte0;
	}

	/*
	 * Check to see if the checksum byte is the same as the
	 * rest of the bytes, too.  (Note that if all of the bytes
	 * are the same except the checksum, a checksum compare
	 * won't succeed, but that's not our problem.)
	 */
	accum_diff |= bootblock[i] ^ byte0;

	/* All bytes in block are the same; call it invalid. */
	if (accum_diff == 0)
		return (-1);

	return (sum - ((sum - 1) / 255) * 255);
}


/*
 * Attempt to read a disk label from a device
 * using the indicated stategy routine.
 * The label must be partly set up before this:
 * secpercyl, secsize and anything required for a block i/o read
 * operation in the driver's strategy/start routines
 * must be filled in before calling us.
 *
 * If dos partition table requested, attempt to load it and
 * find disklabel inside a DOS partition. Also, if bad block
 * table needed, attempt to extract it as well. Return buffer
 * for use in signalling errors if requested.
 *
 * Returns null on success and an error string on failure.
 */

char *
readdisklabel(dev, strat, lp, osdep)
	dev_t dev;
	void (*strat)();
	struct disklabel *lp;
	struct cpu_disklabel *osdep;
{
	struct riscbsd_partition *rp = osdep->partitions;
	struct dkbad *bdp = &osdep->bad;
	register struct buf *bp;
	struct disklabel *dlp;
	char *msg = NULL;
	int cyl, riscbsdpartoff, i;

/*	printf("Reading disclabel for %04x\n", dev);*/

/* minimal requirements for archtypal disk label */

	if (lp->d_secsize == 0)
		lp->d_secsize = DEV_BSIZE;

	if (lp->d_secperunit == 0)
		lp->d_secperunit = 0x1fffffff;

	lp->d_npartitions = MAXPARTITIONS;
	for (i = 0; i < MAXPARTITIONS; i++) {
		if (i == RAW_PART) continue;
		lp->d_partitions[i].p_offset = 0;
		lp->d_partitions[i].p_fstype = FS_UNUSED;
		lp->d_partitions[i].p_size = 0;
	}

	if (lp->d_partitions[RAW_PART].p_size == 0) {
		lp->d_partitions[RAW_PART].p_fstype = FS_UNUSED; 
		lp->d_partitions[RAW_PART].p_offset = 0; 
		lp->d_partitions[RAW_PART].p_size = 0x1fffffff;
	}

/* obtain buffer to probe drive with */
    
	bp = geteblk((int)lp->d_secsize);
	
/* request no partition relocation by driver on I/O operations */

	bp->b_dev = dev;

/* do riscbsd partitions in the process of getting disklabel? */

	riscbsdpartoff = 0;
	cyl = LABELSECTOR / lp->d_secpercyl;

	if (rp) {
		struct filecore_bootblock *bb;
		int heads;
		int sectors;

/* read the filecore boot block */

/*		printf("readdisclabel: Reading boot block\n");*/

		bp->b_blkno = FILECORE_BOOT_SECTOR;
		bp->b_bcount = lp->d_secsize;
		bp->b_flags = B_BUSY | B_READ;
		bp->b_cylin = bp->b_blkno / lp->d_secpercyl;
		(*strat)(bp);

/* if successful, validate boot block and locate parition table */

		if (biowait(bp)) {
			msg = "filecore boot block I/O error";
			goto done;
		}

		bb = (struct filecore_bootblock *)bp->b_data;

/* Validate boot block */
        
		if (bb->checksum != filecore_checksum((u_char *)bb)) {

/* Invalid boot block so lets assume the entire disc is RiscBSD */

/*			printf("readdisklabel: Invalid filecore boot block (incorrect checksum)\n");*/
			goto readlabel;
		}

/* Get some information from the boot block */

		cyl = bb->partition_cyl_low + (bb->partition_cyl_high << 8);

		heads = bb->heads;
		sectors = bb->secspertrack;
                        
/* Do we have a RiscBSD partition table ? */

		if (bb->partition_type == PARTITION_FORMAT_RISCBSD) {
/*			printf("heads = %d nsectors = %d\n", heads, sectors);*/

			riscbsdpartoff = cyl * heads * sectors;
		} else if (bb->partition_type == PARTITION_FORMAT_RISCIX) {
			struct riscix_partition_table *rpt;
			int loop;
			
/* We have a RISCiX partition table :-( groan */

/* Ok read the RISCiX partition table and see if there is a RiscBSD partition */

			bp->b_blkno = cyl * heads * sectors;
			printf("Found RiscIX partition table @ %08x\n", bp->b_blkno);
			bp->b_cylin = bp->b_blkno / lp->d_secpercyl;
			bp->b_bcount = lp->d_secsize;
			bp->b_flags = B_BUSY | B_READ;
			(*strat)(bp);

/* if successful, locate disk label within block and validate */

			if (biowait(bp)) {
				msg = "disk label I/O error";
				goto done;
			}

			rpt = (struct riscix_partition_table *)bp->b_data;
/*			for (loop = 0; loop < NRISCIX_PARTITIONS; ++loop)
				printf("p%d: %16s %08x %08x %08x\n", loop,
				    rpt->partitions[loop].rp_name,
				    rpt->partitions[loop].rp_start,
				    rpt->partitions[loop].rp_length,
				    rpt->partitions[loop].rp_type);
*/
			for (loop = 0; loop < NRISCIX_PARTITIONS; ++loop) {
				if (strcmp(rpt->partitions[loop].rp_name, "RiscBSD") == 0
				    || strcmp(rpt->partitions[loop].rp_name, "NetBSD") == 0
				    || strcmp(rpt->partitions[loop].rp_name, "Empty:") == 0) {
					riscbsdpartoff = rpt->partitions[loop].rp_start;
					break;
				}
			}
			if (loop == NRISCIX_PARTITIONS) {
				msg = "RiscBSD partition identifier string not found.";
				goto done;
			}
		} else {
			msg = "Invalid partition format";
			goto done;
		}
	}

/* next, dig out disk label */

readlabel:
/*	printf("Reading disklabel addr=%08x\n", riscbsdpartoff * DEV_BSIZE);*/
  
	bp->b_blkno = riscbsdpartoff + LABELSECTOR;
	bp->b_cylin = bp->b_blkno / lp->d_secpercyl;
	bp->b_bcount = lp->d_secsize;
	bp->b_flags = B_BUSY | B_READ;
	(*strat)(bp);

/* if successful, locate disk label within block and validate */

	if (biowait(bp)) {
		msg = "disk label I/O error";
		goto done;
	}
	for (dlp = (struct disklabel *)bp->b_data;
	    dlp <= (struct disklabel *)(bp->b_data + lp->d_secsize - sizeof(*dlp));
	    dlp = (struct disklabel *)((char *)dlp + sizeof(long))) {
		if (dlp->d_magic != DISKMAGIC || dlp->d_magic2 != DISKMAGIC) {
			if (msg == NULL)
				msg = "no disk label";
		} else if (dlp->d_npartitions > MAXPARTITIONS ||
			   dkcksum(dlp) != 0)
			msg = "disk label corrupted";
		else {
			*lp = *dlp;
			msg = NULL;
			break;
		}
	}

	if (msg)
		goto done;

	/* obtain bad sector table if requested and present */
	if (bdp && (lp->d_flags & D_BADSECT)) {
		struct dkbad *db;

		i = 0;
		do {
			/* read a bad sector table */
			bp->b_flags = B_BUSY | B_READ;
			bp->b_blkno = lp->d_secperunit - lp->d_nsectors + i;
			if (lp->d_secsize > DEV_BSIZE)
				bp->b_blkno *= lp->d_secsize / DEV_BSIZE;
			else
				bp->b_blkno /= DEV_BSIZE / lp->d_secsize;
			bp->b_bcount = lp->d_secsize;
			bp->b_cylin = lp->d_ncylinders - 1;
			(*strat)(bp);

			/* if successful, validate, otherwise try another */
			if (biowait(bp)) {
				msg = "bad sector table I/O error";
			} else {
				db = (struct dkbad *)(bp->b_data);
#define DKBAD_MAGIC 0x4321
				if (db->bt_mbz == 0
					&& db->bt_flag == DKBAD_MAGIC) {
					msg = NULL;
					*bdp = *db;
					break;
				} else
					msg = "bad sector table corrupted";
			}
		} while ((bp->b_flags & B_ERROR) && (i += 2) < 10 &&
			i < lp->d_nsectors);
	}

done:
	bp->b_flags = B_INVAL | B_AGE | B_READ;
	brelse(bp);
	return (msg);
}


/*
 * Check new disk label for sensibility
 * before setting it.
 */

int
setdisklabel(olp, nlp, openmask, osdep)
	struct disklabel *olp;
	struct disklabel *nlp;
	u_long openmask;
	struct cpu_disklabel *osdep;
{
	register i;
	register struct partition *opp, *npp;

/* sanity clause */

	if (nlp->d_secpercyl == 0 || nlp->d_secsize == 0
	    || (nlp->d_secsize % DEV_BSIZE) != 0)
		return(EINVAL);

/* special case to allow disklabel to be invalidated */

	if (nlp->d_magic == 0xffffffff) {
		*olp = *nlp;
		return (0);
	}

	if (nlp->d_magic != DISKMAGIC || nlp->d_magic2 != DISKMAGIC
	    || dkcksum(nlp) != 0)
		return (EINVAL);

/* XXX missing check if other dos partitions will be overwritten */

	while (openmask != 0) {
		i = ffs(openmask) - 1;
		openmask &= ~(1 << i);
		if (nlp->d_npartitions <= i)
			return (EBUSY);
		opp = &olp->d_partitions[i];
		npp = &nlp->d_partitions[i];
		if (npp->p_offset != opp->p_offset || npp->p_size < opp->p_size)
			return (EBUSY);
		/*
		 * Copy internally-set partition information
		 * if new label doesn't include it.		XXX
		 */
		if (npp->p_fstype == FS_UNUSED && opp->p_fstype != FS_UNUSED) {
			npp->p_fstype = opp->p_fstype;
			npp->p_fsize = opp->p_fsize;
			npp->p_frag = opp->p_frag;
			npp->p_cpg = opp->p_cpg;
		}
	}

	nlp->d_checksum = 0;
	nlp->d_checksum = dkcksum(nlp);
	*olp = *nlp;
	return (0);
}


/*
 * Write disk label back to device after modification.
 */
 
int
writedisklabel(dev, strat, lp, osdep)
	dev_t dev;
	void (*strat)();
	struct disklabel *lp;
	struct cpu_disklabel *osdep;
{
	struct riscbsd_partition *rp = osdep->partitions;
	register struct buf *bp;
	struct disklabel *dlp;
	int cyl, riscbsdpartoff;
	int error = 0;

/* get a buffer and initialize it */

	bp = geteblk((int)lp->d_secsize);
	bp->b_dev = dev;

/* do riscbsd partitions in the process of getting disklabel? */

	riscbsdpartoff = 0;
	cyl = LABELSECTOR / lp->d_secpercyl;

	if (rp) {
		struct filecore_bootblock *bb;
		int heads;
		int sectors;

/* read the filecore boot block */

		printf("writedisklabel: Reading boot block\n");

		bp->b_blkno = FILECORE_BOOT_SECTOR;
		bp->b_bcount = lp->d_secsize;
		bp->b_flags = B_BUSY | B_READ;
		bp->b_cylin = bp->b_blkno / lp->d_secpercyl;
		(*strat)(bp);

/* if successful, validate boot block and locate parition table */

		if (biowait(bp)) {
			printf("writedisklabel: filecore boot block I/O error\n");
			goto done;
		}

		bb = (struct filecore_bootblock *)bp->b_data;

/* Validate boot block */
        
		if (bb->checksum != filecore_checksum((u_char *)bb)) {
/* Invalid boot block so lets assume the entire disc is RiscBSD */

			printf("writedisklabel: Invalid filecore boot block (incorrect checksum)\n");
			goto writelabel;
		}

/* Do we have a RiscBSD partition ? */

		if (bb->partition_type != PARTITION_FORMAT_RISCBSD) {
			printf("writedisklabel: Invalid partition format\n");
			goto done;
		}

		cyl = bb->partition_cyl_low + (bb->partition_cyl_high << 8);

		heads = bb->heads;
		sectors = bb->secspertrack;
                        
		/*printf("heads = %d nsectors = %d\n", heads, sectors);*/

		riscbsdpartoff = cyl * heads * sectors;
	}

writelabel:

/*	printf("writedisklabel: Reading disklabel addr=%08x\n", riscbsdpartoff * DEV_BSIZE);*/

/* next, dig out disk label */

	bp->b_blkno = riscbsdpartoff + LABELSECTOR;
	bp->b_cylin = cyl;
	bp->b_bcount = lp->d_secsize;
	bp->b_flags = B_BUSY | B_READ;
	(*strat)(bp);

/* if successful, locate disk label within block and validate */

	if ((error = biowait(bp)))
		goto done;
	for (dlp = (struct disklabel *)bp->b_data;
	    dlp <= (struct disklabel *)(bp->b_data + lp->d_secsize - sizeof(*dlp));
	    dlp = (struct disklabel *)((char *)dlp + sizeof(long))) {
		if (dlp->d_magic == DISKMAGIC && dlp->d_magic2 == DISKMAGIC &&
		    dkcksum(dlp) == 0) {
			*dlp = *lp;
			bp->b_flags = B_BUSY | B_WRITE;
			(*strat)(bp);
			error = biowait(bp);
			goto done;
		}
	}

	error = ESRCH;

done:
	bp->b_flags |= B_INVAL;
	brelse(bp);
	return (error);
}


/*
 * Determine the size of the transfer, and make sure it is
 * within the boundaries of the partition. Adjust transfer
 * if needed, and signal errors or early completion.
 */
int
bounds_check_with_label(bp, lp, wlabel)
	struct buf *bp;
	struct disklabel *lp;
	int wlabel;
{
	struct partition *p = lp->d_partitions + DISKPART(bp->b_dev);
	int labelsector = lp->d_partitions[0].p_offset + LABELSECTOR;
	int sz;

	sz = howmany(bp->b_bcount, lp->d_secsize);

	if (bp->b_blkno + sz > p->p_size) {
		sz = p->p_size - bp->b_blkno;
		if (sz == 0) {
			/* If exactly at end of disk, return EOF. */
			bp->b_resid = bp->b_bcount;
			goto done;
		}
		if (sz < 0) {
			/* If past end of disk, return EINVAL. */
			bp->b_error = EINVAL;
			goto bad;
		}
		/* Otherwise, truncate request. */
		bp->b_bcount = sz << DEV_BSHIFT;
	}

	/* Overwriting disk label? */
	if (bp->b_blkno + p->p_offset <= labelsector &&
#if LABELSECTOR != 0
	    bp->b_blkno + p->p_offset + sz > labelsector &&
#endif
	    (bp->b_flags & B_READ) == 0 && !wlabel) {
		bp->b_error = EROFS;
		goto bad;
	}

	/* calculate cylinder for disksort to order transfers with */
	bp->b_cylin = (bp->b_blkno + p->p_offset) /
	    (lp->d_secsize / DEV_BSIZE) / lp->d_secpercyl;
	return (1);

bad:
	bp->b_flags |= B_ERROR;
done:
	return (0);
}


void
dk_establish(dk, dev)
	struct disk *dk;
	struct device *dev;
{
	return;
}

/* End of disksubr.c */
