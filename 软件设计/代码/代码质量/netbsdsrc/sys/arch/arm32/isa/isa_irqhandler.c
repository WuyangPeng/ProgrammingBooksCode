/* $NetBSD: irqhandler.c,v 1.13 1997/01/06 02:30:21 mark Exp $ */

/*
 * Copyright 1997
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

/*
 * Copyright (c) 1994-1996 Mark Brinicombe.
 * Copyright (c) 1994 Brini.
 * All rights reserved.
 *
 * This code is derived from software written for Brini by Mark Brinicombe
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
 *	This product includes software developed by Brini.
 * 4. The name of the company nor the name of the author may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BRINI ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL BRINI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * RiscBSD kernel project
 *
 * irqhandler.c
 *
 * IRQ/FIQ initialisation, claim, release and handler routines
 *
 * Created      : 30/09/94
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/syslog.h>
#include <sys/malloc.h>
#include <vm/vm.h>
#include <net/netisr.h>

#include <machine/irqhandler.h>
#include <machine/cpu.h>

irqhandler_t *irqhandlers[NIRQS];
fiqhandler_t *fiqhandlers;

int current_intr_depth = 0;
u_int irqmasks[IPL_LEVELS];
u_int current_mask;
u_int actual_mask;
u_int disabled_mask = 0;
u_int spl_mask;
u_int soft_interrupts;
extern u_int intrcnt[];

u_int irqblock[NIRQS];

typedef struct {
    vm_offset_t physical;
    vm_offset_t virtual;
} pv_addr_t;
             
extern pv_addr_t systempage;
extern char *_intrnames;

/* Prototypes */

extern void zero_page_readonly	__P((void));
extern void zero_page_readwrite	__P((void));
extern int fiq_setregs		__P((fiqhandler_t *));
extern int fiq_getregs		__P((fiqhandler_t *));
extern void set_spl_masks	__P((void));

extern void arpintr	__P((void));
extern void ipintr	__P((void));
extern void pppintr	__P((void));
extern void plipintr	__P((void));

void irq_calculatemasks __P((void));

#define WriteWord(a, b) \
*((volatile unsigned int *)(a)) = (b)

/*
 * void irq_init(void)
 *
 * Initialise the IRQ/FIQ sub system
 */

void
irq_init()
{
	int loop;

	/* Clear all the IRQ handlers and the irq block masks */

	for (loop = 0; loop < NIRQS; ++loop) {
		irqhandlers[loop] = NULL;
		irqblock[loop] = 0;
	}

	/* Clear the FIQ handler */

	fiqhandlers = NULL;

	/*
	 * Setup the irqmasks for the different Interrupt Priority Levels
	 * We will start with no bits set and these will be updated as handlers
	 * are installed at different IPL's.
	 */

	irqmasks[IPL_BIO]   = 0x00000000;
	irqmasks[IPL_NET]   = 0x00000000;
	irqmasks[IPL_TTY]   = 0x00000000;
	irqmasks[IPL_CLOCK] = 0x00000000;
	irqmasks[IPL_IMP]   = 0x00000000;
	irqmasks[IPL_NONE]   = 0x00000000;

	current_mask = 0x00000000;
	actual_mask = 0x00000000;
	spl_mask = 0x00000000;
	soft_interrupts = 0x00000000;

	set_spl_masks();

	/* Enable IRQ's and FIQ's */

	enable_interrupts(I32_bit | F32_bit); 
}


/*
 * int irq_claim(int irq, irqhandler_t *handler)
 *
 * Enable an IRQ and install a handler for it.
 */

int
irq_claim(irq, handler)
	int irq;
	irqhandler_t *handler;
{
	int level;
	int loop;

#ifdef DIAGNOSTIC
	/* Sanity check */
	if (handler == NULL)
		panic("NULL interrupt handler\n");
	if (handler->ih_func == NULL)
		panic("Interrupt handler does not have a function\n");
#endif	/* DIAGNOSTIC */

	/*
	 * IRQ_INSTRUCT indicates that we should get the irq number
	 * from the irq structure
	 */

	if (irq == IRQ_INSTRUCT)
		irq = handler->ih_num;
    
	/* Make sure the irq number is valid */

	if (irq < 0 || irq >= NIRQS)
		return(-1);

	/* Make sure the level is valid */

	if (handler->ih_level < 0 || handler->ih_level >= IPL_LEVELS)
    	        return(-1);

	/* Attach handler at top of chain */

	handler->ih_next = irqhandlers[irq];
	irqhandlers[irq] = handler;

	/*
	 * Reset the flags for this handler.
	 * As the handler is now in the chain mark it as active.
	 */
	handler->ih_flags = 0 | IRQ_FLAG_ACTIVE;

	/*
	 * Record the interrupt number for accounting.
	 * Done here as the accounting number may not be the same as the IRQ number
	 * though for the moment they are
	 */
 
	handler->ih_num = irq;

#ifdef IRQSTATS
	/* Get the interrupt name from the head of the list */

	if (handler->ih_name) {
		char *ptr = _intrnames + (irq * 14);
		strcpy(ptr, "             ");
		strncpy(ptr, handler->ih_name,
		    min(strlen(handler->ih_name), 13));
	} else {
		char *ptr = _intrnames + (irq * 14);
		sprintf(ptr, "irq %2d     ", irq);
	}
#endif	/* IRQSTATS */

	irq_calculatemasks();

	enable_irq(irq);
	set_spl_masks();
	return(0);
}


/*
 * int irq_release(int irq, irqhandler_t *handler)
 *
 * Disable an IRQ and remove a handler for it.
 */

int
irq_release(irq, handler)
	int irq;
	irqhandler_t *handler;
{
	int level;
	int loop;
	irqhandler_t *irqhand;
	irqhandler_t **prehand;
	extern char *_intrnames;

	/*
	 * IRQ_INSTRUCT indicates that we should get the irq number
	 * from the irq structure
	 */

	if (irq == IRQ_INSTRUCT)
		irq = handler->ih_num;

	/* Make sure the irq number is valid */

	if (irq < 0 || irq >= NIRQS)
		return(-1);


	/* Locate the handler */

	irqhand = irqhandlers[irq];
	prehand = &irqhandlers[irq];
    
	while (irqhand && handler != irqhand) {
		prehand = &irqhand;
		irqhand = irqhand->ih_next;
	}

	/* Remove the handler if located */
      
	if (irqhand)
		*prehand = irqhand->ih_next;
	else
		return(-1);


	/* Now the handler has been removed from the chain mark is as inactive */

	irqhand->ih_flags &= ~IRQ_FLAG_ACTIVE;

	/* Make sure the head of the handler list is active */

	if (irqhandlers[irq])
		irqhandlers[irq]->ih_flags |= IRQ_FLAG_ACTIVE;

#ifdef IRQSTATS
	/* Get the interrupt name from the head of the list */
	if (irqhandlers[irq] && irqhandlers[irq]->ih_name) {
		char *ptr = _intrnames + (irq * 14);
		strcpy(ptr, "             ");
		strncpy(ptr, irqhandlers[irq]->ih_name,
		    min(strlen(irqhandlers[irq]->ih_name), 13));
	} else {
		char *ptr = _intrnames + (irq * 14);
		sprintf(ptr, "irq %2d     ", irq);
	}
#endif	/* IRQSTATS */

	irq_calculatemasks();

	/*
	 * Disable the appropriate mask bit if there are no handlers left for
	 * this IRQ.
	 */

	if (irqhandlers[irq] == NULL)
		disable_irq(irq);

	set_spl_masks();
      
	return(0);
}

/* adapted from .../i386/isa/isa_machdep.c */
/*
 * Recalculate the interrupt masks from scratch.
 * We could code special registry and deregistry versions of this function that
 * would be faster, but the code would be nastier, and we don't expect this to
 * happen very much anyway.
 */
void
irq_calculatemasks()
{
	int          irq, level;
	irqhandler_t *ptr;
	int          irqlevel[NIRQS];

	/* First, figure out which levels each IRQ uses. */
	for (irq = 0; irq < NIRQS; irq++) {
		register int levels = 0;
		for (ptr = irqhandlers[irq]; ptr; ptr = ptr->ih_next)
			levels |= 1 << ptr->ih_level;
		irqlevel[irq] = levels;
	}

	/* Then figure out which IRQs use each level. */
	for (level = 0; level < IPL_LEVELS; level++) {
		register int irqs = 0;
		for (irq = 0; irq < NIRQS; irq++)
			if (irqlevel[irq] & (1 << level))
				irqs |= 1 << irq;
		irqmasks[level] = ~(irqs | IRQMASK_ALLSOFT);
	}

	/*
	 * Since run queues may be manipulated by both the statclock and tty,
	 * network, and disk drivers, statclock > (tty | net | bio).
	 */
	irqmasks[IPL_CLOCK] &= (irqmasks[IPL_TTY] & irqmasks[IPL_NET] & 
				irqmasks[IPL_BIO]);

	/*
	 * There are tty, network and disk drivers that use free() at interrupt
	 * time, so imp > (tty | net | bio).
	 */
	irqmasks[IPL_IMP] &= (irqmasks[IPL_TTY] & irqmasks[IPL_NET] & 
			      irqmasks[IPL_BIO]);

	/*
	 * Enforce a hierarchy that gives slow devices a better chance at not
	 * dropping data.
	 */
	irqmasks[IPL_TTY] &= irqmasks[IPL_NET] & irqmasks[IPL_BIO];
	irqmasks[IPL_NET] &= irqmasks[IPL_BIO];

#include "sl.h"
#include "ppp.h"
#if NSL > 0 || NPPP > 0
/* In the presence of SLIP or PPP, splimp > spltty. */
	irqmasks[IPL_NET] &= irqmasks[IPL_TTY];
#endif

	/*
	 * We now need to update the irqblock array. This array indicates
	 * what other interrupts should be blocked when interrupt is asserted
	 * This basically emulates hardware interrupt priorities e.g. by blocking
	 * all other IPL_BIO interrupts with an IPL_BIO interrupt is asserted.
	 * For each interrupt we find the highest IPL and set the block mask to
	 * the interrupt mask for that level.
	 */

	/* And eventually calculate the complete masks. */
	for (irq = 0; irq < NIRQS; irq++) {
		register int irqs = 1 << irq;
		for (ptr = irqhandlers[irq]; ptr; ptr = ptr->ih_next)
			irqs |= ~(irqmasks[ptr->ih_level]);
		irqblock[irq] = irqs | IRQMASK_ALLSOFT;
	}
}


void *
intr_claim(irq, level, name, ih_func, ih_arg)
	int irq;
	int level;
	const char *name;
	int (*ih_func) __P((void *));
	void *ih_arg;
{
	irqhandler_t *ih;

	ih = malloc(sizeof(*ih), M_DEVBUF, M_NOWAIT);
	if (!ih)
		panic("intr_claim(): Cannot malloc handler memory\n");

	ih->ih_level = level;
	ih->ih_name = name;
	ih->ih_func = ih_func;
	ih->ih_arg = ih_arg;
	ih->ih_flags = 0;

	if (irq_claim(irq, ih) != 0)
		return(NULL);
	return(ih);
}

int
intr_release(arg)
	void *arg;
{
	irqhandler_t *ih = (irqhandler_t *)arg;

	if (irq_release(ih->ih_num, ih) == 0) {
		free(ih, M_DEVBUF);
		return(0);
	}
	return(1);
}


/*
 * void disable_irq(int irq)
 *
 * Disables a specific irq. The irq is removed from the master irq mask
 */

void
disable_irq(irq)
	int irq;
{
	register int oldirqstate; 

	oldirqstate = disable_interrupts(I32_bit);
	current_mask &= ~(1 << irq);
	irq_setmasks();
	restore_interrupts(oldirqstate);
}  


/*
 * void enable_irq(int irq)
 *
 * Enables a specific irq. The irq is added to the master irq mask
 * This routine should be used with caution. A handler should already
 * be installed.
 */

void
enable_irq(irq)
	int irq;
{
	register u_int oldirqstate; 

	oldirqstate = disable_interrupts(I32_bit);

	current_mask |= (1 << irq);
	irq_setmasks();
	restore_interrupts(oldirqstate);
}  


/*
 * void stray_irqhandler(u_int mask)
 *
 * Handler for stray interrupts. This gets called if a handler cannot be
 * found for an interrupt.
 */

void
stray_irqhandler(mask)
	u_int mask;
{
	static u_int stray_irqs = 0;

	if (++stray_irqs <= 8)
		log(LOG_ERR, "Stray interrupt %08x%s\n", mask,
		    stray_irqs >= 8 ? ": stopped logging" : "");
}


/*
 * int fiq_claim(fiqhandler_t *handler)
 *
 * Claim FIQ's and install a handler for them.
 */

int
fiq_claim(handler)
	fiqhandler_t *handler;
{
	/* Fail if the FIQ's are already claimed */

	if (fiqhandlers)
		return(-1);

	if (handler->fh_size > 0xc0)
		return(-1);

	/* Install the handler */

	fiqhandlers = handler;

	/* Now we have to actually install the FIQ handler */

	/* Eventually we will copy this down but for the moment ... */

	zero_page_readwrite();

	WriteWord(0x0000003c, (u_int) handler->fh_func);
    
	zero_page_readonly();
	cpu_cache_syncI();

	/* We must now set up the FIQ registers */

	fiq_setregs(handler);

	/* Make sure that the FIQ's are enabled */
    
	enable_interrupts(F32_bit);

	return(0);
}


/*
 * int fiq_release(fiqhandler_t *handler)
 *
 * Release FIQ's and remove a handler for them.
 */

int
fiq_release(handler)
	fiqhandler_t *handler;
{
	/* Fail if the handler is wrong */

	if (fiqhandlers != handler)
		return(-1);

	/* Disable FIQ interrupts */
      
	disable_interrupts(F32_bit);

	/* Retrieve the FIQ registers */

	fiq_getregs(handler);

	/* Remove the handler */

	fiqhandlers = NULL;
	return(0);
}

/* End of irqhandler.c */
