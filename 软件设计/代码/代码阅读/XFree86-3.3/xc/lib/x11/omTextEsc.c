/* $XConsortium: omTextEsc.c /main/4 1996/12/05 10:40:59 swick $ */
/*
 * Copyright 1992, 1993 by TOSHIBA Corp.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of TOSHIBA not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. TOSHIBA make no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * TOSHIBA DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * TOSHIBA BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *
 * Author: Katsuhisa Yano	TOSHIBA Corp.
 *			   	mopi@osa.ilab.toshiba.co.jp
 */
/*
 * Copyright 1995 by FUJITSU LIMITED
 * This is source code modified by FUJITSU LIMITED under the Joint
 * Development Agreement for the CDE/Motif PST.
 */

#include "Xlibint.h"
#include "XomGeneric.h"
#include <stdio.h>

/* For VW/UDC start */

#define	VMAP		0
#define	VROTATE		1
#define	FONTSCOPE	2

static int
is_rotate(oc, font)
    XOC         oc;
    XFontStruct *font;
{
    XOCGenericPart      *gen = XOC_GENERIC(oc);
    FontSet             font_set;
    VRotate             vrotate;
    int                 font_set_count;
    int                 vrotate_num;

    font_set = gen->font_set;
    font_set_count = gen->font_set_num;
    for( ; font_set_count-- ; font_set++) {
	if((font_set->vrotate_num > 0) && (font_set->vrotate != NULL)) {
	    vrotate = font_set->vrotate;
	    vrotate_num = font_set->vrotate_num;
	    for( ; vrotate_num-- ; vrotate++)
		if(vrotate->font == font)
		    return True;
	}
    }
    return False;
}

static int
is_codemap(oc, font)
    XOC         oc;
    XFontStruct *font;
{
    XOCGenericPart      *gen = XOC_GENERIC(oc);
    FontSet             font_set;
    FontData            vmap;
    int                 font_set_count;
    int                 vmap_num;

    font_set = gen->font_set;
    font_set_count = gen->font_set_num;
    for( ; font_set_count-- ; font_set++) {
	if(font_set->vmap_num > 0) {
	    vmap = font_set->vmap;
	    vmap_num = font_set->vmap_num;
	    for( ; vmap_num-- ; vmap++)
		if(vmap->font == font)
		    return True;
	}
    }
    return False;
}

static int
escapement_vertical(oc, font, is_xchar2b, text, length)
    XOC         oc;
    XFontStruct *font;
    Bool        is_xchar2b;
    XPointer    text;
    int         length;
{
    XChar2b	*buf2b;
    char	*buf;
    int		escapement = 0, i;

    if(is_xchar2b) {
	for(i = 0, buf2b = (XChar2b *) text ; i < length ; i++, buf2b++) {
	    if(is_rotate(oc, font) == True) {
		escapement += _XTextHeight16(font, buf2b, 1);
	    } else {
		escapement += (int) (font->max_bounds.ascent +
				     font->max_bounds.descent);
	    }
	}
    } else {
	for(i = 0, buf = (char *)text ; i < length && *buf ; i++, buf++) {
	    if(is_rotate(oc, font) == True) {
		escapement += _XTextHeight(font, buf, 1);
	    } else {
		escapement += (int) (font->max_bounds.ascent +
				     font->max_bounds.descent);
	    }
	}
    }
    return escapement;
}


extern FontData _XomGetFontDataFromFontSet();

static int
TextWidthWithFontSet(font_set, oc, text, length)
    FontSet	font_set;
    XOC		oc;
    XPointer    text;
    int         length;
{
    FontData		fd;
    XFontStruct		*font;
    unsigned char	*ptr = (unsigned char *)text;
    Bool        	is_xchar2b;
    int			ptr_len = length;
    int			escapement = 0, char_len = 0;

    if(font_set == (FontSet) NULL)
	return escapement;

    is_xchar2b = font_set->is_xchar2b;

    while(length > 0) {
	fd = _XomGetFontDataFromFontSet(font_set, ptr, length, &ptr_len,
					       is_xchar2b, FONTSCOPE);
	if(ptr_len <= 0)
	    break;
	if(fd == (FontData) NULL ||
	   (font = fd->font) == (XFontStruct *) NULL) {

	    if((font = font_set->font) == (XFontStruct *) NULL)
		break;
	}

	switch(oc->core.orientation) {
	  case XOMOrientation_LTR_TTB:
	  case XOMOrientation_RTL_TTB:
	    if (is_xchar2b) {
		char_len = ptr_len / sizeof(XChar2b);
		escapement += XTextWidth16(font, (XChar2b *)ptr, char_len);
	    } else {
		char_len = ptr_len;
		escapement += XTextWidth(font, (char *)ptr, char_len);
	    }
	    break;

	  case XOMOrientation_TTB_LTR:
	  case XOMOrientation_TTB_RTL:
	    if(font_set->font == font) {
		fd = _XomGetFontDataFromFontSet(font_set, ptr, length, &ptr_len,
						is_xchar2b, VMAP);
		if(ptr_len <= 0)
		    break;
		if(fd == (FontData) NULL ||
		   (font = fd->font) == (XFontStruct *) NULL)
		    break;

		if(is_codemap(oc, fd->font) == False) {
		    fd = _XomGetFontDataFromFontSet(font_set, ptr, length,
						    &ptr_len, is_xchar2b,
						    VROTATE);
		    if(ptr_len <= 0)
			break;
		    if(fd == (FontData) NULL ||
		       (font = fd->font) == (XFontStruct *) NULL)
			break;
		}
	    }

	    if(is_xchar2b)
		char_len = ptr_len / sizeof(XChar2b);
	    else
		char_len = ptr_len;
	    escapement += escapement_vertical(oc, font, is_xchar2b,
					      (XPointer) ptr, char_len);
	}

	if(char_len <= 0)
	    break;

	length -= char_len;
	ptr += ptr_len;
    }

    return escapement;
}

/* For VW/UDC end */

static int
_XomGenericTextEscapement(oc, type, text, length)
    XOC oc;
    XOMTextType type;
    XPointer text;
    int length;
{
    XlcConv conv;
    XFontStruct *font;
    Bool is_xchar2b;
/* VW/UDC */
    XPointer args[3];
    FontSet font_set;
/* VW/UDC */
    XChar2b xchar2b_buf[BUFSIZ], *buf;
    int escapement = 0;
    int buf_len = 0, left = 0;

    conv = _XomInitConverter(oc, type);
    if (conv == NULL)
	return escapement;
    
    args[0] = (XPointer) &font;
    args[1] = (XPointer) &is_xchar2b;
    args[2] = (XPointer) &font_set;

    while (length > 0) {
	buf = xchar2b_buf;
	left = buf_len = BUFSIZ;

	if (_XomConvert(oc, conv, (XPointer *) &text, &length,
			(XPointer *) &buf, &left, args, 3) < 0)
	    break;
	buf_len -= left;

/* VW/UDC */
	escapement += TextWidthWithFontSet(font_set, oc,
					   (XPointer) xchar2b_buf, buf_len);
/* VW/UDC */
    }

    return escapement;
}

int
#if NeedFunctionPrototypes
_XmbGenericTextEscapement(XOC oc, _Xconst char *text, int length)
#else
_XmbGenericTextEscapement(oc, text, length)
    XOC oc;
    char *text;
    int length;
#endif
{
    return _XomGenericTextEscapement(oc, XOMMultiByte, (XPointer) text, length);
}

int
#if NeedFunctionPrototypes
_XwcGenericTextEscapement(XOC oc, _Xconst wchar_t *text, int length)
#else
_XwcGenericTextEscapement(oc, text, length)
    XOC oc;
    wchar_t *text;
    int length;
#endif
{
    return _XomGenericTextEscapement(oc, XOMWideChar, (XPointer) text, length);
}
