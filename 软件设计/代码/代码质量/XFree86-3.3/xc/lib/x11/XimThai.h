/* $XConsortium: XimThai.h,v 1.4 94/04/17 20:21:39 rws Exp $ */
/***********************************************************

Copyright (c) 1993  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.


Copyright 1993 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
**++ 
**  FACILITY: 
** 
**      Xlib 
** 
**  ABSTRACT: 
** 
**      Definition file for Thai specific functions.  
** 
**  MODIFICATION HISTORY: 
** 
**/

#ifndef _XIMTHAI_H_
#define _XIMTHAI_H_

#include <X11/Xlib.h>

/* Classification of characters in TACTIS according to WTT */

#define CTRL    0   /* control chars */
#define NON     1   /* non composibles */
#define CONS    2   /* consonants */
#define LV      3   /* leading vowels */
#define FV1     4   /* following vowels */
#define FV2     5
#define FV3     6
#define BV1     7   /* below vowels */
#define BV2     8
#define BD      9   /* below diacritics */
#define TONE    10  /* tonemarks */
#define AD1     11  /* above diacritics */
#define AD2     12
#define AD3     13
#define AV1     14  /* above vowels */
#define AV2     15
#define AV3     16


/* extended classification */

#define DEAD    17  /* group of non-spacing characters */


/* display levels in display cell */

#define NONDISP 0   /* non displayable */
#define TOP     1
#define ABOVE   2
#define BASE    3
#define BELOW   4


/* Input Sequence Check modes */

#define WTT_ISC1        1   /* WTT default ISC mode */
#define WTT_ISC2        2   /* WTT strict ISC mode */
#define THAICAT_ISC     3   /* THAICAT ISC mode */
#define NOISC	      255   /* No ISC */


/* Function prototypes (thaisub.c) */

Private
int THAI_chtype (  		/* returns classification of a char */
#if NeedFunctionPrototypes
	unsigned char ch
#endif
);

Private
int THAI_chlevel (		/* returns the display level */
#if NeedFunctionPrototypes
	unsigned char ch
#endif
);

Private
Bool THAI_isdead ( 		/* return True if char is non-spacing */
#if NeedFunctionPrototypes
	unsigned char ch
#endif
);

Private
Bool THAI_iscons (		/* return True if char is consonant */
#if NeedFunctionPrototypes
	unsigned char ch
#endif
); 

Private
Bool THAI_isvowel ( 		/* return True if char is vowel */
#if NeedFunctionPrototypes
	unsigned char ch
#endif
);

Private
Bool THAI_istone ( 		/* return True if char is tonemark */
#if NeedFunctionPrototypes
	unsigned char ch
#endif
);

Private
Bool THAI_iscomposible (
#if NeedFunctionPrototypes
	unsigned char follow_ch, 
	unsigned char lead_ch
#endif
);

Private
Bool THAI_isaccepted (
#if NeedFunctionPrototypes
	unsigned char follow_ch, 
	unsigned char lead_ch, 
	unsigned char isc_mode
#endif
);

Private
void THAI_apply_write_rules (
#if NeedFunctionPrototypes
	unsigned char  *instr, 
	unsigned char  *outstr, 
	unsigned char  insert_ch, 
	int	       *num_insert_ch
#endif
);

Private
int THAI_find_chtype (
#if NeedFunctionPrototypes
	unsigned char  *instr, 
	int	       chtype
#endif
);

Private
int THAI_apply_scm (
#if NeedFunctionPrototypes
	unsigned char  	*instr, 
	unsigned char	*outstr, 
	unsigned char	spec_ch, 
	int		num_sp, 
	unsigned char	insert_ch
#endif
);

#endif /* _XIMTHAI_H_ */
