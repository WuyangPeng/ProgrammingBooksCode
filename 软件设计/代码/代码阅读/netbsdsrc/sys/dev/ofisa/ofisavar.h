/*	$NetBSD: ofisavar.h,v 1.1 1998/02/07 00:46:54 cgd Exp $	*/

/*
 * Copyright 1998
 * Digital Equipment Corporation. All rights reserved.
 *
 * This software is furnished under license and may be used and
 * copied only in accordance with the following terms and conditions.
 * Subject to these conditions, you may download, copy, install,
 * use, modify and distribute this software in source and/or binary
 * form. No title or ownership is transferred hereby.
 *
 * 1) Any source code used, modified or distributed must reproduce
 *    and retain this copyright notice and list of conditions as
 *    they appear in the source file.
 *
 * 2) No right is granted to use any trade name, trademark, or logo of
 *    Digital Equipment Corporation. Neither the "Digital Equipment
 *    Corporation" name nor any trademark or logo of Digital Equipment
 *    Corporation may be used to endorse or promote products derived
 *    from this software without the prior written permission of
 *    Digital Equipment Corporation.
 *
 * 3) This software is provided "AS-IS" and any express or implied
 *    warranties, including but not limited to, any implied warranties
 *    of merchantability, fitness for a particular purpose, or
 *    non-infringement are disclaimed. In no event shall DIGITAL be
 *    liable for any damages whatsoever, and in particular, DIGITAL
 *    shall not be liable for special, indirect, consequential, or
 *    incidental damages or damages for lost profits, loss of
 *    revenue or loss of use, whether such damages arise in contract,
 *    negligence, tort, under statute, in equity, at law or otherwise,
 *    even if advised of the possibility of such damage.
 */

#ifndef _DEV_OFISA_OFISAVAR_H_
#define	_DEV_OFISA_OFISAVAR_H_

struct ofisa_attach_args {
	struct ofprobe	ofp;		/* common */

	bus_space_tag_t	iot;		/* i/o space tag */
	bus_space_tag_t	memt;		/* mem space tag */
	bus_dma_tag_t	dmat;		/* DMA tag */
	isa_chipset_tag_t ic;		/* chipset tag (for intr, etc.) */
};

struct ofisa_reg_desc {
	int		type;		/* type.  XXX aliasing modifiers? */
	bus_addr_t	addr;		/* base address. */
	bus_size_t	len;		/* length. */
};

#define	OFISA_REG_TYPE_MEM	0	/* memory space */
#define	OFISA_REG_TYPE_IO	1	/* I/O space */

struct ofisa_intr_desc {
	int		share;		/* sharing type: IST_*. */
	int		irq;		/* IRQ. */
};

/*
 * Machine-dependent function/macro definitions.
 *
 * Machine-dependent code must implement at least:
 *
 *	int	ofisa_get_isabus_data(int phandle,
 *		    struct isabus_attach_args *iba);
 *
 *	int	ofisa_ignore_child(int pphandle, int cphandle);
 *
 * Individual ofisa attachments may want addition functions or
 * macros from this (or other) headers.  See those attachments'
 * files for more details.
 */
#if (arm32 != 1)
ERROR: COMPILING FOR UNSUPPORTED MACHINE, OR MORE THAN ONE.
#endif
#if arm32
#include <arm32/ofw/ofisa_machdep.h>
#endif

int	ofisa_reg_count __P((int));
int	ofisa_reg_get __P((int, struct ofisa_reg_desc *, int));
void	ofisa_reg_print __P((struct ofisa_reg_desc *, int));
int	ofisa_intr_count __P((int));
int	ofisa_intr_get __P((int, struct ofisa_intr_desc *, int));
void	ofisa_intr_print __P((struct ofisa_intr_desc *, int));

#endif /* _DEV_OFISA_OFISAVAR_H_ */
