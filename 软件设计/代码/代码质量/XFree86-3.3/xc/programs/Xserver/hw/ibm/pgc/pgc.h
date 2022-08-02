/*
 * $XConsortium: pgc.h,v 1.2 91/07/16 13:11:40 jap Exp $
 *
 * Copyright IBM Corporation 1987,1988,1989,1990,1991
 *
 * All Rights Reserved
 *
 * License to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of IBM not be
 * used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS, AND 
 * NONINFRINGEMENT OF THIRD PARTY RIGHTS, IN NO EVENT SHALL
 * IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *
*/

#ifndef PGC_H
#define PGC_H

/* standalone ppc screen proc */

typedef struct {
	ColormapPtr	InstalledColormap ;
	void		(* blit)() ;
	void		(* solidFill)() ;
	void		(* tileFill)() ;
	void		(* stipFill)() ;
	void		(* opstipFill)() ;
	void		(* imageFill)() ;
	void		(* imageRead)() ;
	void		(* lineBres)() ;
	void		(* lineHorz)() ;
	void		(* lineVert)() ;
	void		(* setColor)() ;
	void		(* RecolorCursor)() ;
	void		(* monoFill)() ;     /* 32 bit padded */
	void		(* glyphFill)() ;    /* GLYPHPADBYTES*8 bit padded */
	unsigned long *((* planeRead)()) ;   /* for XYformat getImage() */
	void		(* replicateArea)() ;/* Accelerator for Tile & Stipple*/
} pgcScreenRec, *pgcScreenPtr ;

#endif /* PGC_H */
