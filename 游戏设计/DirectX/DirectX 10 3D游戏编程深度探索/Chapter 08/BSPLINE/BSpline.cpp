/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "BSpline.h"

/**
 * The b-spline basis matrix
 */
matrix4	cBSpline::m_baseMatrix = matrix4(
	-1,  3, -3,  1,
 	 3, -6,  3,  0,
	-3,  0,  3,  0,
	 1,  4,  1,  0);

point3 cBSpline::Calc( float t, int i0 )
{
	assert(i0+3 < (int)m_ctrlPoints.size() );
	assert(t>=0.f && t<=1.f );
	point4 tVec( t*t*t, t*t, t, 1 );

	point4 xVec( m_ctrlPoints[i0].x, m_ctrlPoints[i0+1].x, m_ctrlPoints[i0+2].x, m_ctrlPoints[i0+3].x );
	point4 yVec( m_ctrlPoints[i0].y, m_ctrlPoints[i0+1].y, m_ctrlPoints[i0+2].y, m_ctrlPoints[i0+3].y );
	point4 zVec( m_ctrlPoints[i0].z, m_ctrlPoints[i0+1].z, m_ctrlPoints[i0+2].z, m_ctrlPoints[i0+3].z );

	return point3(
		tVec *  (1.f/6) * m_baseMatrix * xVec,
		tVec *  (1.f/6) * m_baseMatrix * yVec,
		tVec *  (1.f/6) * m_baseMatrix * zVec );
}

point3 cBSpline::CalcAbs( float t )
{
	// the T we get isn't right, fix it.
	t *= m_ctrlPoints.size() - 3;
	int vert = (int)(floor(t));
	t -= (float)floor(t);
	return Calc( t, vert );
}