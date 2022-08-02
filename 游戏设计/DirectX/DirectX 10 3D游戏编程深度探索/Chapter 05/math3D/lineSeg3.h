/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _LINESEG3_H
#define _LINESEG3_H

#include "point3.h"

struct lineSeg3 {
	point3 v0,v1;

	lineSeg3( const point3 &a, const point3 &b ){
		v0 = a; v1 = b;
	}
	lineSeg3(){}
};

#endif//_LINESEG3_H