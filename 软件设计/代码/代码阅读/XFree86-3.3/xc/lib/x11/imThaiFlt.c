/* $XConsortium: imThaiFlt.c /main/9 1995/11/18 16:08:25 kaleb $ */
/* $XFree86: xc/lib/X11/imThaiFlt.c,v 3.0 1996/05/06 05:54:12 dawes Exp $ */
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
**	Thai specific functions.
**	Handles character classifications, composibility checking,
**	Input sequence check and other Thai specific requirements
**	according to WTT specification and DEC extensions.
** 
**  MODIFICATION HISTORY: 
** 
**/

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xmd.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include "Xlibint.h"
#include "Xlcint.h"
#include "Ximint.h"
#include "XimThai.h"

#define SPACE   32

/* character classification table */
#define TACTIS_CHARS 256
Private
char tactis_chtype[TACTIS_CHARS] = {
    CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,  /*  0 -  7 */
    CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,  /*  8 - 15 */
    CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,  /* 16 - 23 */
    CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,  /* 24 - 31 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 32 - 39 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 40 - 47 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 48 - 55 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 56 - 63 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 64 - 71 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 72 - 79 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 80 - 87 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 88 - 95 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 96 - 103 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 104 - 111 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 112 - 119 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  CTRL,  /* 120 - 127 */
    CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,  /* 128 - 135 */
    CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,  /* 136 - 143 */
    CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,  /* 144 - 151 */
    CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL,  /* 152 - 159 */
    NON,  CONS, CONS, CONS, CONS, CONS, CONS, CONS,  /* 160 - 167 */
    CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS,  /* 168 - 175 */
    CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS,  /* 176 - 183 */
    CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS,  /* 184 - 191 */
    CONS, CONS, CONS, CONS,  FV3, CONS,  FV3, CONS,  /* 192 - 199 */
    CONS, CONS, CONS, CONS, CONS, CONS, CONS, NON,   /* 200 - 207 */
    FV1,  AV2,  FV1,  FV1,  AV1,  AV3,  AV2,  AV3,   /* 208 - 215 */
    BV1,  BV2,  BD,   NON,  NON,  NON,  NON,  NON,   /* 216 - 223 */
    LV,   LV,   LV,   LV,   LV,   FV2,  NON,  AD2,   /* 224 - 231 */
    TONE, TONE, TONE, TONE, AD1,  AD1,  AD3,  NON,   /* 232 - 239 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,   /* 240 - 247 */
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  CTRL   /* 248 - 255 */
};

/* Composibility checking tables */
#define NC  0   /* NOT COMPOSIBLE - following char displays in next cell */
#define CP  1   /* COMPOSIBLE - following char is displayed in the same cell
                                as leading char, also implies ACCEPT */
#define XC  3   /* Non-display */
#define AC  4   /* ACCEPT - display the following char in the next cell */
#define RJ  5   /* REJECT - discard that following char, ignore it */

#define CH_CLASSES      17  /* 17 classes of chars */

Private
char write_rules_lookup[CH_CLASSES][CH_CLASSES] = {
        /* Table 0: writing/outputing rules */
        /* row: leading char,  column: following char */
/* CTRL NON CONS LV FV1 FV2 FV3 BV1 BV2 BD TONE AD1 AD2 AD3 AV1 AV2 AV3 */
   {XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*CTRL*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*NON*/
  ,{XC, NC, NC, NC, NC, NC, NC, CP, CP, CP, CP, CP, CP, CP, CP, CP, CP}/*CONS*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*LV*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*FV1*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*FV2*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*FV3*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, CP, CP, NC, NC, NC, NC, NC}/*BV1*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, CP, NC, NC, NC, NC, NC, NC}/*BV2*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*BD*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*TONE*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*AD1*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*AD2*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC, NC}/*AD3*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, CP, CP, NC, NC, NC, NC, NC}/*AV1*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, CP, NC, NC, NC, NC, NC, NC}/*AV2*/
  ,{XC, NC, NC, NC, NC, NC, NC, NC, NC, NC, CP, NC, CP, NC, NC, NC, NC}/*AV3*/
};

Private
char wtt_isc1_lookup[CH_CLASSES][CH_CLASSES] = {
      /* Table 1: WTT default input sequence check rules */
      /* row: leading char,  column: following char */
/* CTRL NON CONS LV FV1 FV2 FV3 BV1 BV2 BD TONE AD1 AD2 AD3 AV1 AV2 AV3 */
   {XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*CTRL*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*NON*/
  ,{XC, AC, AC, AC, AC, AC, AC, CP, CP, CP, CP, CP, CP, CP, CP, CP, CP}/*CONS*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*LV*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*FV1*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*FV2*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*FV3*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, CP, RJ, RJ, RJ, RJ, RJ}/*BV1*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, RJ, RJ, RJ, RJ, RJ, RJ}/*BV2*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*BD*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*TONE*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*AD1*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*AD2*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*AD3*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, CP, RJ, RJ, RJ, RJ, RJ}/*AV1*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, RJ, RJ, RJ, RJ, RJ, RJ}/*AV2*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, RJ, CP, RJ, RJ, RJ, RJ}/*AV3*/
};

Private
char wtt_isc2_lookup[CH_CLASSES][CH_CLASSES] = {
      /* Table 2: WTT strict input sequence check rules */
      /* row: leading char,  column: following char */
/* CTRL NON CONS LV FV1 FV2 FV3 BV1 BV2 BD TONE AD1 AD2 AD3 AV1 AV2 AV3 */
   {XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*CTRL*/
  ,{XC, AC, AC, AC, RJ, RJ, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*NON*/
  ,{XC, AC, AC, AC, AC, RJ, AC, CP, CP, CP, CP, CP, CP, CP, CP, CP, CP}/*CONS*/
  ,{XC, RJ, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*LV*/
  ,{XC, AC, AC, AC, AC, RJ, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*FV1*/
  ,{XC, AC, AC, AC, AC, RJ, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*FV2*/
  ,{XC, AC, AC, AC, RJ, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*FV3*/
  ,{XC, AC, AC, AC, AC, RJ, AC, RJ, RJ, RJ, CP, CP, RJ, RJ, RJ, RJ, RJ}/*BV1*/
  ,{XC, AC, AC, AC, RJ, RJ, AC, RJ, RJ, RJ, CP, RJ, RJ, RJ, RJ, RJ, RJ}/*BV2*/
  ,{XC, AC, AC, AC, RJ, RJ, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*BD*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*TONE*/
  ,{XC, AC, AC, AC, RJ, RJ, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*AD1*/
  ,{XC, AC, AC, AC, RJ, RJ, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*AD2*/
  ,{XC, AC, AC, AC, RJ, RJ, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*AD3*/
  ,{XC, AC, AC, AC, RJ, RJ, AC, RJ, RJ, RJ, CP, CP, RJ, RJ, RJ, RJ, RJ}/*AV1*/
  ,{XC, AC, AC, AC, RJ, RJ, AC, RJ, RJ, RJ, CP, RJ, RJ, RJ, RJ, RJ, RJ}/*AV2*/
  ,{XC, AC, AC, AC, RJ, RJ, AC, RJ, RJ, RJ, CP, RJ, CP, RJ, RJ, RJ, RJ}/*AV3*/
};

Private
char thaicat_isc_lookup[CH_CLASSES][CH_CLASSES] = {
      /* Table 3: Thaicat input sequence check rules */
      /* row: leading char,  column: following char */
/* CTRL NON CONS LV FV1 FV2 FV3 BV1 BV2 BD TONE AD1 AD2 AD3 AV1 AV2 AV3 */
   {XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*CTRL*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*NON*/
  ,{XC, AC, AC, AC, AC, AC, AC, CP, CP, CP, CP, CP, CP, CP, CP, CP, CP}/*CONS*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*LV*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*FV1*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*FV2*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ} /*FV3*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, CP, RJ, RJ, RJ, RJ, RJ}/*BV1*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, RJ, RJ, RJ, RJ, RJ, RJ}/*BV2*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*BD*/
  ,{XC, AC, AC, AC, AC, AC, AC, CP, CP, RJ, RJ, RJ, RJ, RJ, CP, CP, CP}/*TONE*/
  ,{XC, AC, AC, AC, AC, AC, AC, CP, RJ, RJ, RJ, RJ, RJ, RJ, CP, RJ, RJ}/*AD1*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, CP}/*AD2*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ, RJ}/*AD3*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, CP, RJ, RJ, RJ, RJ, RJ}/*AV1*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, RJ, RJ, RJ, RJ, RJ, RJ}/*AV2*/
  ,{XC, AC, AC, AC, AC, AC, AC, RJ, RJ, RJ, CP, RJ, CP, RJ, RJ, RJ, RJ}/*AV3*/
};


/* returns classification of a char */
Private int
#if NeedFunctionPrototypes
THAI_chtype (unsigned char	ch)
#else
THAI_chtype (ch)
    unsigned char	ch;
#endif
{
    return tactis_chtype[ch];
}


/* returns the display level */
Private int
#if NeedFunctionPrototypes
THAI_chlevel (unsigned char	ch)
#else
THAI_chlevel (ch)
    unsigned char	ch;
#endif
{
    int     chlevel;

    switch (tactis_chtype[ch])
    {
        case CTRL:
            chlevel = NON;
            break;
        case BV1:
        case BV2:
        case BD:
            chlevel = BELOW;
            break;
        case TONE:
        case AD1:
        case AD2:
            chlevel = TOP;
            break;
        case AV1:
        case AV2:
        case AV3:
        case AD3:
            chlevel = ABOVE;
            break;
        case NON:
        case CONS:
        case LV:
        case FV1:
        case FV2:
        case FV3:
        default: /* if tactis_chtype is invalid */
            chlevel = BASE;
            break;
    }
    return chlevel;
}


/* return True if char is non-spacing */
Private Bool
#if NeedFunctionPrototypes
THAI_isdead (unsigned char	ch)
#else
THAI_isdead (ch)
    unsigned char	ch;
#endif
{
    return ((tactis_chtype[ch] == CTRL) || (tactis_chtype[ch] == BV1) ||
            (tactis_chtype[ch] == BV2)  || (tactis_chtype[ch] == BD)  ||
            (tactis_chtype[ch] == TONE) || (tactis_chtype[ch] == AD1) ||
            (tactis_chtype[ch] == AD2)  || (tactis_chtype[ch] == AD3) ||
            (tactis_chtype[ch] == AV1)  || (tactis_chtype[ch] == AV2) ||
            (tactis_chtype[ch] == AV3));
}


/* return True if char is consonant */
Private Bool
#if NeedFunctionPrototypes
THAI_iscons (unsigned char	ch)
#else
THAI_iscons (ch)
    unsigned char	ch;
#endif
{
    return (tactis_chtype[ch] == CONS);
}


/* return True if char is vowel */
Private Bool
#if NeedFunctionPrototypes
THAI_isvowel (unsigned char	ch)
#else
THAI_isvowel (ch)
    unsigned char	ch;
#endif
{
    return ((tactis_chtype[ch] == LV)  || (tactis_chtype[ch] == FV1) ||
            (tactis_chtype[ch] == FV2) || (tactis_chtype[ch] == FV3) ||
            (tactis_chtype[ch] == BV1) || (tactis_chtype[ch] == BV2) ||
            (tactis_chtype[ch] == AV1) || (tactis_chtype[ch] == AV2) ||
            (tactis_chtype[ch] == AV3));
}


/* return True if char is tonemark */
Private Bool
#if NeedFunctionPrototypes
THAI_istone (unsigned char	ch)
#else
THAI_istone (ch)
    unsigned char	ch;
#endif
{
    return (tactis_chtype[ch] == TONE);
}


Private Bool
#if NeedFunctionPrototypes
THAI_iscomposible (
    unsigned char	follow_ch, 
    unsigned char	lead_ch)
#else
THAI_iscomposible (follow_ch, lead_ch)
    unsigned char	follow_ch;
    unsigned char	lead_ch;
#endif
{/* "Can follow_ch be put in the same display cell as lead_ch?" */

    return (write_rules_lookup[THAI_chtype(lead_ch)][THAI_chtype(follow_ch)] 
            == CP);
}

Private Bool
#if NeedFunctionPrototypes
THAI_isaccepted (
    unsigned char	follow_ch, 
    unsigned char	lead_ch,
    unsigned char	mode)
#else
THAI_isaccepted (follow_ch, lead_ch, mode)
    unsigned char	follow_ch;
    unsigned char	lead_ch;
    unsigned char	mode;
#endif
{
    Bool iskeyvalid; /*  means "Can follow_ch be keyed in after lead_ch?" */

    switch (mode)
    {
        case WTT_ISC1:
            iskeyvalid = 
          (wtt_isc1_lookup[THAI_chtype(lead_ch)][THAI_chtype(follow_ch)] != RJ);
            break;
        case WTT_ISC2:
            iskeyvalid = 
          (wtt_isc2_lookup[THAI_chtype(lead_ch)][THAI_chtype(follow_ch)] != RJ);
            break;
        case THAICAT_ISC:
            iskeyvalid =
       (thaicat_isc_lookup[THAI_chtype(lead_ch)][THAI_chtype(follow_ch)] != RJ);
            break;
        default:
            iskeyvalid = True;
            break;
    }

    return iskeyvalid;
}

Private void 
#if NeedFunctionPrototypes
THAI_apply_write_rules(
    unsigned char	*instr, 
    unsigned char	*outstr, 
    unsigned char	insert_ch, 
    int 		*num_insert_ch)
#else
THAI_apply_write_rules(instr, outstr, insert_ch, num_insert_ch)
    unsigned char	*instr;
    unsigned char	*outstr;
    unsigned char	insert_ch;
    int 		*num_insert_ch;
#endif
{
/*
Input parameters: 
    instr - input string
    insert_ch specify what char to be added when invalid composition is found
Output parameters:
    outstr - output string after input string has been applied the rules
    num_insert_ch - number of insert_ch added to outstr.
*/
    unsigned char   *lead_ch = NULL, *follow_ch = NULL, *out_ch = NULL;

    *num_insert_ch = 0;
    lead_ch = follow_ch = instr;
    out_ch = outstr;
    if ((*lead_ch == '\0') || !(THAI_find_chtype(instr,DEAD)))
    {   /* Empty string or can't find any non-spacing char*/
        strcpy((char *)outstr, (char *)instr);
    } else { /* String of length >= 1, keep looking */
        follow_ch++;
        if (THAI_isdead(*lead_ch)) { /* is first char non-spacing? */
            *out_ch++ = SPACE;
            (*num_insert_ch)++;
        }
        *out_ch++ = *lead_ch;
        while (*follow_ch != '\0')  /* more char in string to check */
        {
            if (THAI_isdead(*follow_ch) && 
                 !THAI_iscomposible(*follow_ch,*lead_ch)) 
            {
                *out_ch++ = SPACE;
                (*num_insert_ch)++;
            }
            *out_ch++ = *follow_ch;
            lead_ch = follow_ch;
            follow_ch++;
        }
        *out_ch = '\0';
    }
}

Private int 
#if NeedFunctionPrototypes
THAI_find_chtype (
    unsigned char	*instr, 
    int		chtype)
#else
THAI_find_chtype (instr, chtype)
    unsigned char	*instr;
    int		chtype;
#endif
{
/*
Input parameters:
    instr - input string
    chtype - type of character to look for
Output parameters:
    function returns first position of character with matched chtype
    function returns -1 if it does not find.
*/
    int i = 0, position = -1;

    switch (chtype)
    {
        case DEAD:
            for (i = 0; *instr != '\0' && THAI_isdead(*instr); i++, instr++)
		;
            if (*instr != '\0') position = i; 
            break;
        default:
            break;
    }
    return position;
}


Private int 
#if NeedFunctionPrototypes
THAI_apply_scm(
    unsigned char	*instr, 
    unsigned char	*outstr, 
    unsigned char	spec_ch, 
    int		num_sp, 
    unsigned char	insert_ch)
#else
THAI_apply_scm(instr, outstr, spec_ch, num_sp, insert_ch)
    unsigned char	*instr;
    unsigned char	*outstr;
    unsigned char	spec_ch;
    int		num_sp;
    unsigned char	insert_ch;
#endif
{
    unsigned char   *scan, *outch;
    int             i, dead_count, found_count;
    Bool            isconsecutive;

    scan = instr;
    outch = outstr;
    dead_count = found_count = 0;
    isconsecutive = False;
    while (*scan != '\0') {
        if (THAI_isdead(*scan))
            dead_count++;       /* count number of non-spacing char */
        if (*scan == spec_ch)
            if (!isconsecutive) 
                found_count++;      /* count number consecutive spec char found */
        *outch++ = *scan++;
        if (found_count == num_sp) {
            for (i = 0; i < dead_count; i++)
                *outch++ = insert_ch;
            dead_count = found_count = 0;
        }
    }
    /* what to return? */
    return 0; /* probably not right but better than returning garbage */
}

/* The following functions are copied from XKeyBind.c */

Private void ComputeMaskFromKeytrans();
Private int IsCancelComposeKey();
Private void SetLed();
Private CARD8 FindKeyCode();

/* The following functions are specific to this module */ 

Private int XThaiTranslateKey();
Private int XThaiTranslateKeySym();

Private KeySym HexIMNormalKey();
Private KeySym HexIMFirstComposeKey();
Private KeySym HexIMSecondComposeKey();
Private KeySym HexIMComposeSequence();
Private void InitIscMode();
Private Bool ThaiComposeConvert();

/*
 * Definitions
 */

#define BellVolume 		0

/*
 * Macros to save and recall last input character in XIC
 */
#define IC_SavePreviousChar(ic,ch) \
		*((ic)->private.local.context->mb) = (char) (ch)
#define IC_GetPreviousChar(ic,ch) \
		(ch) = (unsigned char) *((ic)->private.local.context->mb)
/*
 * Input sequence check mode in XIC
 */
#define IC_IscMode(ic)		((ic)->private.local.thai.input_mode)

/*
 * Max. size of string handled by the two String Lookup functions.
 */
#define STR_LKUP_BUF_SIZE	256

/*
 * Size of buffer to contain previous locale name.
 */
#define SAV_LOCALE_NAME_SIZE	256

/*
 * Size of buffer to contain the IM modifier.
 */
#define MAXTHAIIMMODLEN 20

#define AllMods (ShiftMask|LockMask|ControlMask| \
		 Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask)


#define IsISOControlKey(ks) ((ks) >= XK_2 && (ks) <= XK_8)

#define IsValidControlKey(ks)   (((ks)>=XK_A && (ks)<=XK_asciitilde || \
                (ks)==XK_space || (ks)==XK_Delete) && \
                ((ks)!=0))

#define COMPOSE_LED 2

typedef KeySym (*StateProc)();

/*
 * macros to classify XKeyEvent state field
 */

#define IsShift(state) (((state) & ShiftMask) != 0)
#define IsLock(state) (((state) & LockMask) != 0)
#define IsControl(state) (((state) & ControlMask) != 0)
#define IsMod1(state) (((state) & Mod1Mask) != 0)
#define IsMod2(state) (((state) & Mod2Mask) != 0)
#define IsMod3(state) (((state) & Mod3Mask) != 0)
#define IsMod4(state) (((state) & Mod4Mask) != 0)
#define IsMod5(state) (((state) & Mod5Mask) != 0)

/*
 * key starts Thai compose sequence (Hex input method) if :
 */

#define IsComposeKey(ks, event)  \
	(( ks==XK_Alt_L && 	\
	   IsControl((event)->state) &&	\
	   !IsShift((event)->state))	\
	 ? True : False)

/*
 *  State handler to implement the Thai hex input method.
 */

Private int nstate_handlers = 3;
Private StateProc state_handler[] = {
	HexIMNormalKey,
	HexIMFirstComposeKey,
	HexIMSecondComposeKey
};

/*
 *  Table for 'Thai Compose' character input.
 *  The current implementation uses latin-1 keysyms.
 */
struct _XMapThaiKey {
	KeySym from;
	KeySym to;
};

Private struct _XMapThaiKey ThaiComposeTable[] = {
	{ /* 0xa4 */ XK_currency,	/* 0xa5 */ XK_yen },
	{ /* 0xa2 */ XK_cent,		/* 0xa3 */ XK_sterling },
	{ /* 0xe6 */ XK_ae,		/* 0xef */ XK_idiaeresis },
	{ /* 0xd3 */ XK_Oacute,		/* 0xee */ XK_icircumflex },
	{ /* 0xb9 */ XK_onesuperior,	/* 0xfa */ XK_uacute },
	{ /* 0xd2 */ XK_Ograve,		/* 0xe5 */ XK_aring },
	{ /* 0xbc */ XK_onequarter,	/* 0xfb */ XK_ucircumflex },
	{	     XK_VoidSymbol,		   XK_VoidSymbol }
};

struct _XKeytrans {
	struct _XKeytrans *next;/* next on list */
	char *string;		/* string to return when the time comes */
	int len;		/* length of string (since NULL is legit)*/
	KeySym key;		/* keysym rebound */
	unsigned int state;	/* modifier state */
	KeySym *modifiers;	/* modifier keysyms you want */
	int mlen;		/* length of modifier list */
};

/* Convert keysym to 'Thai Compose' keysym */
/* The current implementation use latin-1 keysyms */
Private Bool
ThaiComposeConvert(dpy, insym, outsym ,lower, upper)
    Display *dpy;
    KeySym insym;
    KeySym *outsym,*lower,*upper;
{
    struct _XMapThaiKey *table_entry = ThaiComposeTable;

    while (table_entry->from != XK_VoidSymbol) {
	if (table_entry->from == insym) {
	    *outsym = table_entry->to;
	    *lower = *outsym;
	    *upper = *outsym;
	    return True;
	}
	table_entry++;
    }
    return False;
}

Private int
XThaiTranslateKey(dpy, keycode, modifiers, modifiers_return, keysym_return,
	      lsym_return, usym_return)
    register Display *dpy;
    KeyCode keycode;
    register unsigned int modifiers;
    unsigned int *modifiers_return;
    KeySym *keysym_return,*lsym_return,*usym_return;
{
    int per;
    register KeySym *syms;
    KeySym sym = 0, lsym = 0, usym = 0;

    if ((! dpy->keysyms) && (! _XKeyInitialize(dpy)))
	return 0;
    *modifiers_return = (ShiftMask|LockMask) | dpy->mode_switch;
    if (((int)keycode < dpy->min_keycode) || ((int)keycode > dpy->max_keycode))
    {
	*keysym_return = NoSymbol;
	return 1;
    }
    per = dpy->keysyms_per_keycode;
    syms = &dpy->keysyms[(keycode - dpy->min_keycode) * per];
    while ((per > 2) && (syms[per - 1] == NoSymbol))
	per--;
    if ((per > 2) && (modifiers & dpy->mode_switch)) {
	syms += 2;
	per -= 2;
    }
    if (!(modifiers & ShiftMask) &&
	(!(modifiers & LockMask) || (dpy->lock_meaning == NoSymbol))) {
	if ((per == 1) || (syms[1] == NoSymbol))
	    XConvertCase(syms[0], keysym_return, &usym);
	else {
	    XConvertCase(syms[0], &lsym, &usym);
	    *keysym_return = syms[0];
	}
    } else if (!(modifiers & LockMask) ||
	       (dpy->lock_meaning != XK_Caps_Lock)) {
	if ((per == 1) || ((usym = syms[1]) == NoSymbol))
	    XConvertCase(syms[0], &lsym, &usym);
	*keysym_return = usym;
    } else {
	if ((per == 1) || ((sym = syms[1]) == NoSymbol))
	    sym = syms[0];
	XConvertCase(sym, &lsym, &usym);
	if (!(modifiers & ShiftMask) && (sym != syms[0]) &&
	    ((sym != usym) || (lsym == usym)))
	    XConvertCase(syms[0], &lsym, &usym);
	*keysym_return = usym;
    }
    /*
     * ThaiCat keyboard support :
     * When the Shift and Thai keys are hold for some keys a 'Thai Compose'  
     * character code is generated which is different from column 3 and
     * 4 of the keymap. 
     * Since we don't know whether ThaiCat keyboard or WTT keyboard is
     * in use, the same mapping is done for all Thai input.
     * We just arbitary choose to use column 3 keysyms as the indices of 
     * this mapping.
     * When the control key is also hold, this mapping has no effect.
     */
    if ((modifiers & Mod1Mask) &&
	(modifiers & ShiftMask) &&
	!(modifiers & ControlMask)) {
	if (ThaiComposeConvert(dpy, syms[0], &sym, &lsym, &usym))
	    *keysym_return = sym;
    }

    if (*keysym_return == XK_VoidSymbol)
	*keysym_return = NoSymbol;
    *lsym_return = lsym;
    *usym_return = usym;
    return 1;
}

/* 
 * XThaiTranslateKeySym
 *
 * Translate KeySym to TACTIS code output.
 * The current implementation uses ISO latin-1 keysym.
 * Should be changed to TACTIS keysyms when they are defined by the
 * standard.
 */
Private int
XThaiTranslateKeySym(dpy, symbol, lsym, usym, modifiers, buffer, nbytes)
    Display *dpy;
    register KeySym symbol, lsym, usym;
    unsigned int modifiers;
    unsigned char *buffer;
    int nbytes;
{
    KeySym ckey;
    register struct _XKeytrans *p; 
    int length;
    unsigned long hiBytes;
    register unsigned char c;

    /*
     * initialize length = 1 ;
     */
    length = 1;

    if (!symbol)
	return 0;
    /* see if symbol rebound, if so, return that string. */
    for (p = dpy->key_bindings; p; p = p->next) {
	if (((modifiers & AllMods) == p->state) && (symbol == p->key)) {
	    length = p->len;
	    if (length > nbytes) length = nbytes;
	    memcpy (buffer, p->string, length);
	    return length;
	}
    }
    /* try to convert to TACTIS, handling control */
    hiBytes = symbol >> 8;
    if (!(nbytes &&
	  ((hiBytes == 0) ||
	   ((hiBytes == 0xFF) &&
	    (((symbol >= XK_BackSpace) && (symbol <= XK_Clear)) ||
	     (symbol == XK_Return) ||
	     (symbol == XK_Escape) ||
	     (symbol == XK_KP_Space) ||
	     (symbol == XK_KP_Tab) ||
	     (symbol == XK_KP_Enter) ||
	     ((symbol >= XK_KP_Multiply) && (symbol <= XK_KP_9)) ||
	     (symbol == XK_KP_Equal) ||
             (symbol == XK_Scroll_Lock) ||
#ifdef DXK_PRIVATE /* DEC private keysyms */
             (symbol == DXK_Remove) ||
#endif
             (symbol == NoSymbol) ||
	     (symbol == XK_Delete))))))
	return 0;

    /* if X keysym, convert to ascii by grabbing low 7 bits */
    if (symbol == XK_KP_Space)
	c = XK_space & 0x7F; /* patch encoding botch */
/* not for Thai
    else if (symbol == XK_hyphen)
	c = XK_minus & 0xFF; */ /* map to equiv character */
    else if (hiBytes == 0xFF)
	c = symbol & 0x7F;
    else
	c = symbol & 0xFF;
    /* only apply Control key if it makes sense, else ignore it */
    if (modifiers & ControlMask) {
    if (!(IsKeypadKey(lsym) || lsym==XK_Return || lsym==XK_Tab)) {
        if (IsISOControlKey(lsym)) ckey = lsym;
        else if (IsISOControlKey(usym)) ckey = usym;
        else if (lsym == XK_question) ckey = lsym;
        else if (usym == XK_question) ckey = usym;
        else if (IsValidControlKey(lsym)) ckey = lsym;
        else if (IsValidControlKey(usym)) ckey = usym;
        else length = 0;

        if (length != 0) {
        if (ckey == XK_2) c = '\000';
        else if (ckey >= XK_3 && ckey <= XK_7)
            c = (char)(ckey-('3'-'\033'));
        else if (ckey == XK_8) c = '\177';
        else if (ckey == XK_Delete) c = '\030';
        else if (ckey == XK_question) c = '\037';
        else if (ckey == XK_quoteleft) c = '\036';  /* KLee 1/24/91 */
        else c = (char)(ckey & 0x1f);
        }
    }
    }
    /*
     *  ThaiCat has a key that generates two TACTIS codes D1 & E9.
     *  It is represented by the latin-1 keysym XK_thorn (0xfe). 
     *  If c is XK_thorn, this key is pressed and it is converted to  
     *  0xd1 0xe9.
     */
    if (c == XK_thorn) {
	buffer[0] = 0xd1;
	buffer[1] = 0xe9;
	buffer[2] = '\0';
	return 2;
    }
    else {
	/* Normal case */
        buffer[0] = c;
	buffer[1] = '\0';
        return 1;
    }
}

/*
 * given a KeySym, returns the first keycode containing it, if any.
 */
Private CARD8
FindKeyCode(dpy, code)
    register Display *dpy;
    register KeySym code;
{

    register KeySym *kmax = dpy->keysyms + 
	(dpy->max_keycode - dpy->min_keycode + 1) * dpy->keysyms_per_keycode;
    register KeySym *k = dpy->keysyms;
    while (k < kmax) {
	if (*k == code)
	    return (((k - dpy->keysyms) / dpy->keysyms_per_keycode) +
		    dpy->min_keycode);
	k += 1;
	}
    return 0;
}

	
/*
 * given a list of modifiers, computes the mask necessary for later matching.
 * This routine must lookup the key in the Keymap and then search to see
 * what modifier it is bound to, if any.  Sets the AnyModifier bit if it
 * can't map some keysym to a modifier.
 */
Private void
ComputeMaskFromKeytrans(dpy, p)
    Display *dpy;
    register struct _XKeytrans *p;
{
    register int i;
    register CARD8 code;
    register XModifierKeymap *m = dpy->modifiermap;

    p->state = AnyModifier;
    for (i = 0; i < p->mlen; i++) {
	/* if not found, then not on current keyboard */
	if ((code = FindKeyCode(dpy, p->modifiers[i])) == 0)
		return;
	/* code is now the keycode for the modifier you want */
	{
	    register int j = m->max_keypermod<<3;

	    while ((--j >= 0) && (code != m->modifiermap[j]))
		;
	    if (j < 0)
		return;
	    p->state |= (1<<(j/m->max_keypermod));
	}
    }
    p->state &= AllMods;
}


/************************************************************************
 *
 *
 * Compose handling routines - compose handlers 0,1,2
 * 
 * 
 ************************************************************************/

#define NORMAL_KEY_STATE 0
#define FIRST_COMPOSE_KEY_STATE 1
#define SECOND_COMPOSE_KEY_STATE 2

Private
KeySym HexIMNormalKey (thai_part, symbol, event)
    XicThaiPart *thai_part;
    KeySym symbol;
    XKeyEvent *event;

{
    if (IsComposeKey (symbol, event))	/* start compose sequence	*/
	{
	SetLed (event->display,COMPOSE_LED, LedModeOn);
	thai_part->comp_state = FIRST_COMPOSE_KEY_STATE;
	return NoSymbol;
	}
    return symbol;
}


Private
KeySym HexIMFirstComposeKey (thai_part, symbol, event)	
    XicThaiPart *thai_part;
    KeySym symbol;
    XKeyEvent *event;

{
    if (IsModifierKey (symbol)) return symbol; /* ignore shift etc. */
    if (IsCancelComposeKey (&symbol, event))	/* cancel sequence */
	{
	SetLed (event->display,COMPOSE_LED, LedModeOff);
	thai_part->comp_state = NORMAL_KEY_STATE;
	return symbol;
	}
    if (IsComposeKey (symbol, event))		/* restart sequence ?? */
	{
	return NoSymbol;			/* no state change necessary */
	}

    thai_part->keysym = symbol;		/* save key pressed */
    thai_part->comp_state = SECOND_COMPOSE_KEY_STATE;
    return NoSymbol;
}

Private
KeySym HexIMSecondComposeKey (thai_part, symbol, event)
    XicThaiPart *thai_part;
    KeySym symbol;
    XKeyEvent *event;

{
    if (IsModifierKey (symbol)) return symbol;	/* ignore shift etc. */
    if (IsComposeKey (symbol, event))		/* restart sequence ? */
	{
	thai_part->comp_state =FIRST_COMPOSE_KEY_STATE;
	return NoSymbol;
	}
    SetLed (event->display,COMPOSE_LED, LedModeOff);
    if (IsCancelComposeKey (&symbol, event))	/* cancel sequence ? */
	{
	thai_part->comp_state = NORMAL_KEY_STATE;
	return symbol;
	}

    if ((symbol = HexIMComposeSequence (thai_part->keysym, symbol))
								==NoSymbol)
	{ /* invalid compose sequence */
	XBell(event->display, BellVolume);
	}
    thai_part->comp_state = NORMAL_KEY_STATE; /* reset to normal state */
    return symbol;
}


/*
 * Interprets two keysyms entered as hex digits and return the Thai keysym
 * correspond to the TACTIS code formed.
 * The current implementation of this routine returns ISO Latin Keysyms.
 */

Private
KeySym HexIMComposeSequence (ks1, ks2)

KeySym ks1, ks2;
{
int	hi_digit;
int	lo_digit;
int	tactis_code;

    if ((ks1 >= XK_0) && (ks1 <= XK_9))
	hi_digit = ks1 - XK_0;
    else if ((ks1 >= XK_A) && (ks1 <= XK_F))
	hi_digit = ks1 - XK_A + 10;
    else if ((ks1 >= XK_a) && (ks1 <= XK_f))
	hi_digit = ks1 - XK_a + 10;
    else	/* out of range */
	return NoSymbol;
	    
    if ((ks2 >= XK_0) && (ks2 <= XK_9))
	lo_digit = ks2 - XK_0;
    else if ((ks2 >= XK_A) && (ks2 <= XK_F))
	lo_digit = ks2 - XK_A + 10;
    else if ((ks2 >= XK_a) && (ks2 <= XK_f))
	lo_digit = ks2 - XK_a + 10;
    else	/* out of range */
	return NoSymbol;

    tactis_code = hi_digit * 0x10 + lo_digit ;

    return (KeySym)tactis_code;

}

/*
 * routine determines
 *	1) whether key event should cancel a compose sequence
 *	2) whether cancelling key event should be processed or ignored
 */

Private
int IsCancelComposeKey(symbol, event)
    KeySym *symbol;
    XKeyEvent *event;
{
    if (*symbol==XK_Delete && !IsControl(event->state) &&
						!IsMod1(event->state)) {
	*symbol=NoSymbol;  /* cancel compose sequence, and ignore key */
	return True;
    }
    if (IsComposeKey(*symbol, event)) return False;
    return (
	IsControl (event->state) ||
	IsMod1(event->state) ||
	IsKeypadKey (*symbol) ||
	IsFunctionKey (*symbol) ||
	IsMiscFunctionKey (*symbol) ||
#ifdef DXK_PRIVATE /* DEC private keysyms */
	*symbol == DXK_Remove ||
#endif
	IsPFKey (*symbol) ||
	IsCursorKey (*symbol) ||
	*symbol >= XK_Tab && *symbol < XK_Multi_key
		? True : False);	/* cancel compose sequence and pass */
					/* cancelling key through	    */
}


/*
 *	set specified keyboard LED on or off
 */

Private
void SetLed (dpy, num, state)
    Display *dpy;
    int num;
    int state;
{
    XKeyboardControl led_control;

    led_control.led_mode = state;
    led_control.led = num;
    XChangeKeyboardControl (dpy, KBLed | KBLedMode,	&led_control);
}


/*
 * Initialize ISC mode from im modifier 
 */
Private void InitIscMode(ic)
Xic ic;
{
    Xim im;
    char *im_modifier_name;

    /* If already defined, just return */

    if (IC_IscMode(ic)) return;

    /* Get IM modifier */

    im = (Xim) XIMOfIC((XIC)ic);
    im_modifier_name = im->core.im_name;

    /* Match with predefined value, default is Basic Check */

    if (!strncmp(im_modifier_name,"BasicCheck",MAXTHAIIMMODLEN+1))
	IC_IscMode(ic) = WTT_ISC1;
    else if (!strncmp(im_modifier_name,"Strict",MAXTHAIIMMODLEN+1))
	IC_IscMode(ic) = WTT_ISC2;
    else if (!strncmp(im_modifier_name,"Thaicat",MAXTHAIIMMODLEN+1))
	IC_IscMode(ic) = THAICAT_ISC;
    else if (!strncmp(im_modifier_name,"Passthrough",MAXTHAIIMMODLEN+1))
	IC_IscMode(ic) = NOISC;
    else
	IC_IscMode(ic) = WTT_ISC1;

    return;
}
    
/*
 * Filter function for TACTIS
 */
Bool
_XimThaiFilter(d, w, ev, client_data)
Display		*d;
Window		w;
XEvent		*ev;
XPointer	client_data;
{
    Xic		    ic = (Xic)client_data;
    unsigned int    modifiers;
    KeySym 	    symbol;
    KeySym	    lsym,usym;
    int 	    count;
    int 	    isc_mode; /* Thai Input Sequence Check mode */
    unsigned char   previous_char; /* Last inputted Thai char */
    int		    state;
    XicThaiPart     *thai_part;
    char	    buf[10];
    int	            i;

    if ((ev->type != KeyPress)
        || (ev->xkey.keycode == 0))
        return False;

    if (!IC_IscMode(ic)) InitIscMode(ic);

    if (! XThaiTranslateKey(ev->xkey.display, ev->xkey.keycode, ev->xkey.state,
	 		&modifiers, &symbol, &lsym, &usym))
	return False;

    /*
     *  Hex input method processing 
     */

    thai_part = &ic->private.local.thai;
    state = thai_part->comp_state;
    if (state >= 0 && state < nstate_handlers) /* call handler for state */
    {
        symbol = (* state_handler[state])(thai_part, symbol, (XKeyEvent *)ev);
    }

    /*
     *  Translate KeySym into mb.
     */
    count = XThaiTranslateKeySym(ev->xkey.display, symbol, lsym,
				usym, ev->xkey.state, buf, 10);

    if (!symbol && !count)
	return True;

    /* Return symbol if cannot convert to character */
    if (!count)
	return False;

    /*
     *  Thai Input sequence check
     */
    isc_mode = IC_IscMode(ic);
    if (IC_GetPreviousChar(ic, previous_char)) {
	if (!THAI_isaccepted(buf[0],previous_char, isc_mode)) {
	    /* reject character */
            XBell(ev->xkey.display, BellVolume);
    	    return True;
        }
    }
    /* Remember the last character inputted. */
    IC_SavePreviousChar(ic, buf[count-1]);
    for (i=0; i<count; i++)
        ic->private.local.composed->mb[i] = buf[i];
    ic->private.local.composed->mb[count] = '\0';

    i = _Xlcmbstowcs(ic->core.im->core.lcd, ic->private.local.composed->wc,
			ic->private.local.composed->mb, count);
    
    if (!((buf[0] > 0 && buf[0] <= 0x1f) || (buf[0] == 0) || (buf[0] == 0x7f)))
        ic->private.local.composed->keysym = NoSymbol;
    else
        ic->private.local.composed->keysym = symbol;
    ev->xkey.keycode = 0;
    XPutBackEvent(d, ev);
    return True;
}
