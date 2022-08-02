/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _D3DHELPER_H
#define _D3DHELPER_H

#include <memory.h>

/**
 * This class takes care of the annoying gruntwork
 * of having to zero-out and set the size parameter
 * of our Windows and DirectX structures.
 */
template <class T>
struct sAutoZero : public T
{
	sAutoZero()
	{
		memset( this, 0, sizeof(T) );
		dwSize = sizeof(T);
	}
};


/**
 * The Right Way to release our COM interfaces.
 * If they're still valid, release them, then
 * invalidate them and null them.
 */
template <class T>
inline void SafeRelease( T& iface )
{
	if( iface )
	{
		iface->Release();
		iface = NULL;
	}
}

#endif // _D3DHELPER_H