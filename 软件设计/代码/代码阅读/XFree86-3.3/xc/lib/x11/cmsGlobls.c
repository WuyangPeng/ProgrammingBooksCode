/*$XConsortium: cmsGlobls.c,v 1.10 93/07/05 11:44:05 rws Exp $ */

/*
 * Code and supporting documentation (c) Copyright 1990 1991 Tektronix, Inc.
 * 	All Rights Reserved
 * 
 * This file is a component of an X Window System-specific implementation
 * of Xcms based on the TekColor Color Management System.  Permission is
 * hereby granted to use, copy, modify, sell, and otherwise distribute this
 * software and its documentation for any purpose and without fee, provided
 * that this copyright, permission, and disclaimer notice is reproduced in
 * all copies of this software and in supporting documentation.  TekColor
 * is a trademark of Tektronix, Inc.
 * 
 * Tektronix makes no representation about the suitability of this software
 * for any purpose.  It is provided "as is" and with all faults.
 * 
 * TEKTRONIX DISCLAIMS ALL WARRANTIES APPLICABLE TO THIS SOFTWARE,
 * INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE.  IN NO EVENT SHALL TEKTRONIX BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA, OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR THE PERFORMANCE OF THIS SOFTWARE.
 *
 *
 *	NAME
 *		XcmsGlobls.c
 *
 *	DESCRIPTION
 *		Source file containing Xcms globals
 *
 *
 */

#include "Xlibint.h"
#include "Xcmsint.h"

/*
 *      EXTERNS
 *              External declarations required locally to this package
 *              that are not already declared in any of the included header
 *		files (external includes or internal includes).
 */
extern XcmsFunctionSet	XcmsLinearRGBFunctionSet;
#ifdef GRAY
extern XcmsFunctionSet	XcmsGrayFunctionSet;
#endif /* GRAY */

/* UNDEFINED Color Space */
extern XcmsColorSpace	XcmsUNDEFINEDColorSpace;

/* CIE XYZ Color Space */
extern XcmsColorSpace	XcmsCIEXYZColorSpace;

/* CIE uvY Color Space */
extern XcmsColorSpace	XcmsCIEuvYColorSpace;

/* CIE xyY Color Space */
extern XcmsColorSpace	XcmsCIExyYColorSpace;

/* CIE Lab Color Space */
extern XcmsColorSpace	XcmsCIELabColorSpace;

/* CIE Luv Color Space */
extern XcmsColorSpace	XcmsCIELuvColorSpace;

/* TekHVC Color Space */
extern XcmsColorSpace	XcmsTekHVCColorSpace;

/* Device Dependent Color Space Structures */
extern XcmsColorSpace	XcmsRGBiColorSpace;
extern XcmsColorSpace	XcmsRGBColorSpace;


/*
 *      GLOBALS
 *              Variables declared in this package that are allowed
 *		to be used globally.
 */

    /*
     * Initial array of Device Independent Color Spaces
     */
XcmsColorSpace *_XcmsDIColorSpacesInit[] = {
    &XcmsCIEXYZColorSpace,
    &XcmsCIEuvYColorSpace,
    &XcmsCIExyYColorSpace,
    &XcmsCIELabColorSpace,
    &XcmsCIELuvColorSpace,
    &XcmsTekHVCColorSpace,
    &XcmsUNDEFINEDColorSpace,
    NULL
};
    /*
     * Pointer to the array of pointers to XcmsColorSpace structures for
     * Device-Independent Color Spaces that are currently accessible by
     * the color management system.  End of list is indicated by a NULL pointer.
     */
XcmsColorSpace **_XcmsDIColorSpaces = _XcmsDIColorSpacesInit;

    /*
     * Initial array of Device Dependent Color Spaces
     */
XcmsColorSpace *_XcmsDDColorSpacesInit[] = {
    &XcmsRGBColorSpace,
    &XcmsRGBiColorSpace,
    NULL
};
    /*
     * Pointer to the array of pointers to XcmsColorSpace structures for
     * Device-Dependent Color Spaces that are currently accessible by
     * the color management system.  End of list is indicated by a NULL pointer.
     */
XcmsColorSpace **_XcmsDDColorSpaces = &_XcmsDDColorSpacesInit[0];

    /*
     * Initial array of Screen Color Characterization Function Sets
     */
XcmsFunctionSet	*_XcmsSCCFuncSetsInit[] = {
	&XcmsLinearRGBFunctionSet,
#ifdef GRAY
	&XcmsGrayFunctionSet,
#endif /* GRAY */
	NULL};
    /*
     * Pointer to the array of pointers to XcmsSCCFuncSet structures
     * (Screen Color Characterization Function Sets) that are currently
     * accessible by the color management system.  End of list is
     * indicated by a NULL pointer.
     */
XcmsFunctionSet **_XcmsSCCFuncSets = _XcmsSCCFuncSetsInit;

    /*
     * X Consortium Registered Device-Independent Color Spaces
     *	Note that prefix must be in lowercase.
     */
char	_XcmsCIEXYZ_prefix[] = "ciexyz";
char	_XcmsCIEuvY_prefix[] = "cieuvy";
char	_XcmsCIExyY_prefix[] = "ciexyy";
char	_XcmsCIELab_prefix[] = "cielab";
char 	_XcmsCIELuv_prefix[] = "cieluv";
char	_XcmsTekHVC_prefix[] = "tekhvc";
    /*
     * Registered Device-Dependent Color Spaces
     */
char	_XcmsRGBi_prefix[] = "rgbi";
char	_XcmsRGB_prefix[] = "rgb";

XcmsRegColorSpaceEntry _XcmsRegColorSpaces[] = {
    _XcmsCIEXYZ_prefix,	XcmsCIEXYZFormat,
    _XcmsCIEuvY_prefix,	XcmsCIEuvYFormat,
    _XcmsCIExyY_prefix,	XcmsCIExyYFormat,
    _XcmsCIELab_prefix,	XcmsCIELabFormat,
    _XcmsCIELuv_prefix,	XcmsCIELuvFormat,
    _XcmsTekHVC_prefix,	XcmsTekHVCFormat,
    _XcmsRGB_prefix,	XcmsRGBFormat,
    _XcmsRGBi_prefix,	XcmsRGBiFormat,
    NULL, 0
};
