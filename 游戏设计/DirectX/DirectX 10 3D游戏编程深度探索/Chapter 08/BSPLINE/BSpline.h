/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _BSPLINE_H
#define _BSPLINE_H

#include <vector>
using std::vector;

class cBSpline  
{
	vector< point3 > m_ctrlPoints;

	static matrix4	m_baseMatrix;
public:

	void AddCtrlPoint( point3& pt )
	{
		m_ctrlPoints.push_back( pt );
	}

	point3 Calc( float t, int i0 );
	point3 CalcAbs( float t );

	int NumPoints()
	{
		return m_ctrlPoints.size();
	}
};

#endif //_BSPLINE_H
