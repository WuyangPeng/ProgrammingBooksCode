/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _TRI_H
#define _TRI_H

template <class type>
struct tri 
{

    type v[3]; // Array access useful in for loops
	
	tri()
	{
		// nothing
	}

	tri( type v0, type v1, type v2 )
	{
		v[0] = v0;
		v[1] = v1;
		v[2] = v2;
	}
};

#endif //_TRI_H