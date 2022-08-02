/* $XConsortium: AsmMacros.h /main/13 1996/10/25 11:33:12 kaleb $ */
/*
 * (c) Copyright 1993,1994 by David Wexelblat <dwex@xfree86.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL 
 * DAVID WEXELBLAT BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 * 
 * Except as contained in this notice, the name of David Wexelblat shall not be
 * used in advertising or otherwise to promote the sale, use or other dealings
 * in this Software without prior written authorization from David Wexelblat.
 *
 */
/*
 * Copyright 1997
 * Digital Equipment Corporation. All rights reserved.
 * This software is furnished under license and may be used and copied only in 
 * accordance with the following terms and conditions.  Subject to these 
 * conditions, you may download, copy, install, use, modify and distribute 
 * this software in source and/or binary form. No title or ownership is 
 * transferred hereby.
 * 1) Any source code used, modified or distributed must reproduce and retain 
 *    this copyright notice and list of conditions as they appear in the 
 *    source file.
 *
 * 2) No right is granted to use any trade name, trademark, or logo of Digital 
 *    Equipment Corporation. Neither the "Digital Equipment Corporation" name 
 *    nor any trademark or logo of Digital Equipment Corporation may be used 
 *    to endorse or promote products derived from this software without the 
 *    prior written permission of Digital Equipment Corporation.
 *
 * 3) This software is provided "AS-IS" and any express or implied warranties,
 *    including but not limited to, any implied warranties of merchantability,
 *    fitness for a particular purpose, or non-infringement are disclaimed. In
 *    no event shall DIGITAL be liable for any damages whatsoever, and in 
 *    particular, DIGITAL shall not be liable for special, indirect, 
 *    consequential, or incidental damages or damages for lost profits, loss 
 *    of revenue or loss of use, whether such damages arise in contract, 
 *    negligence, tort, under statute, in equity, at law or otherwise, even if
 *    advised of the possibility of such damage. 
 */
/* $XFree86: xc/programs/Xserver/hw/xfree86/SuperProbe/AsmMacros.h,v 3.10 1996/12/23 06:31:04 dawes Exp $ */

#if defined(__GNUC__)
#if defined(linux) && defined(__alpha__)
#define inb _inb
#define inw _inw
#define inl _inl
#define outb(p,v) _outb((v),(p))
#define outw(p,v) _outw((v),(p))
#define outl(p,v) _outl((v),(p))
#else
#ifdef __arm32__
unsigned int IOPortBase;  /* Memory mapped I/O port area */

static __inline__ void
outb(port, val)
     short port;
     char val;
{
	 if ((unsigned short)port >= 0x400) return;

	*(volatile unsigned char*)(((unsigned short)(port))+IOPortBase) = val;
}

static __inline__ void
outw(port, val)
     short port;
     short val;
{
	 if ((unsigned short)port >= 0x400) return;

	*(volatile unsigned short*)(((unsigned short)(port))+IOPortBase) = val;
}

static __inline__ void
outl(port, val)
     short port;
     int val;
{
	 if ((unsigned short)port >= 0x400) return;

	*(volatile unsigned long*)(((unsigned short)(port))+IOPortBase) = val;
}

static __inline__ unsigned int
inb(port)
     short port;
{
	 if ((unsigned short)port >= 0x400) return((unsigned int)-1);

	return(*(volatile unsigned char*)(((unsigned short)(port))+IOPortBase));
}

static __inline__ unsigned int
inw(port)
     short port;
{
	 if ((unsigned short)port >= 0x400) return((unsigned int)-1);

	return(*(volatile unsigned short*)(((unsigned short)(port))+IOPortBase));
}

static __inline__ unsigned int
inl(port)
     short port;
{
	 if ((unsigned short)port >= 0x400) return((unsigned int)-1);

	return(*(volatile unsigned long*)(((unsigned short)(port))+IOPortBase));
}
#else /* __arm32__ */
#ifdef GCCUSESGAS
static __inline__ void
outb(port, val)
short port;
char val;
{
   __asm__ __volatile__("outb %0,%1" : :"a" (val), "d" (port));
}

static __inline__ void
outw(port, val)
short port;
short val;
{
   __asm__ __volatile__("outw %0,%1" : :"a" (val), "d" (port));
}

static __inline__ void
outl(port, val)
short port;
unsigned int val;
{
   __asm__ __volatile__("outl %0,%1" : :"a" (val), "d" (port));
}

static __inline__ unsigned int
inb(port)
short port;
{
   unsigned char ret;
   __asm__ __volatile__("inb %1,%0" :
       "=a" (ret) :
       "d" (port));
   return ret;
}

static __inline__ unsigned int
inw(port)
short port;
{
   unsigned short ret;
   __asm__ __volatile__("inw %1,%0" :
       "=a" (ret) :
       "d" (port));
   return ret;
}

static __inline__ unsigned int
inl(port)
short port;
{
   unsigned int ret;
   __asm__ __volatile__("inl %1,%0" :
       "=a" (ret) :
       "d" (port));
   return ret;
}

#else /* GCCUSESGAS */

static __inline__ void
outb(port, val)
     short port;
     char val;
{
  __asm__ __volatile__("out%B0 (%1)" : :"a" (val), "d" (port));
}

static __inline__ void
outw(port, val)
     short port;
     short val;
{
  __asm__ __volatile__("out%W0 (%1)" : :"a" (val), "d" (port));
}

static __inline__ void
outl(port, val)
     short port;
     unsigned int val;
{
  __asm__ __volatile__("out%L0 (%1)" : :"a" (val), "d" (port));
}

static __inline__ unsigned int
inb(port)
     short port;
{
  unsigned int ret;
  __asm__ __volatile__("in%B0 (%1)" :
                   "=a" (ret) :
                   "d" (port));
  return ret;
}

static __inline__ unsigned int
inw(port)
     short port;
{
  unsigned int ret;
  __asm__ __volatile__("in%W0 (%1)" :
                   "=a" (ret) :
                   "d" (port));
  return ret;
}

static __inline__ unsigned int
inl(port)
     short port;
{
  unsigned int ret;
  __asm__ __volatile__("in%L0 (%1)" :
                   "=a" (ret) :
                   "d" (port));
  return ret;
}

#endif /* GCCUSESGAS */
#endif /* __arm32__ */
#endif /* linux && __alpha__ */

#if defined(linux) || defined(__arm32__)

#define intr_disable()
#define intr_enable()

#else /* !linux && !__arm32__ */

static __inline__ void
intr_disable()
{
  __asm__ __volatile__("cli");
}

static __inline__ void
intr_enable()
{
  __asm__ __volatile__("sti");
}

#endif /* else !linux && !__arm32__ */

#else /* __GNUC__ */

#if defined(_MINIX) && defined(_ACK)

/* inb, outb, inw and outw are defined in the library */
/* ... but I've no idea if the same is true for inl & outl */

u8_t inb(U16_t);
void outb(U16_t, U8_t);
u16_t inw(U16_t);
void outw(U16_t, U16_t);
u32_t inl(U16_t);
void outl(U16_t, U32_t);

#else /* not _MINIX and _ACK */

# if defined(__STDC__) && (__STDC__ == 1)
#  ifndef NCR
#  define asm __asm
#  endif
# endif
# ifdef SVR4
#  include <sys/types.h>
#  ifndef __USLC__
#   define __USLC__
#  endif
# endif
#ifndef SCO325
# include <sys/inline.h>
#else
# include "../common/scoasm.h"
#endif
#define intr_disable() asm("cli")
#define intr_enable()  asm("sti")

#endif /* _MINIX and _ACK */
#endif /* __GNUC__ */
