/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/



#ifndef _POLYGON3_H
#define _POLYGON3_H

template <class type>
struct polygon 
{
	int nElem; // number of elements in the polygon
	int maxElem;

	type *pList;

	polygon()
	{
		nElem = 0;
		maxElem = 0;
		pList = NULL;
	}

	polygon( int maxSize )
	{
		maxElem = maxSize;
		pList = new type[maxSize];
	}

	polygon( const polygon &in )
	{
		CloneData( in );
	}

	~polygon()
	{
		DestroyData();
	}

	void CloneData( const polygon &in )
	{
		if( !in.pList ) 
			return;

		pList = new type[in.maxElem];
		maxElem = in.maxElem;
		nElem = in.nElem;
		for( int i=0; i<in.nElem; i++ )
		{
			pList[i] = in.pList[i];
		}
	}

	void DestroyData( )
	{
		if( pList )
		{
			delete[] pList;
		}
		pList = NULL;
	}

	polygon& operator=( const polygon<type> &in )
	{
		if( &in != this )
		{
			DestroyData();

			CloneData( in );
		}
		
		return *this;
	}
};

#endif /*_POLYGON3_H*/