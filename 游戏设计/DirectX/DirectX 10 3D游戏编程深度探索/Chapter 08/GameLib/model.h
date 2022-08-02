/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
#include <string>
#include "..\math3d\tri.h"
#include "..\math3d\mathD3D.h"
#include "GraphicsLayer.h"

class cModel  
{
	typedef tri<WORD> sTri;

	std::vector< sTri >		m_tris;
	std::vector< cGraphicsLayer::cDefaultVertex >	m_verts;

	std::wstring			m_name;

	ID3D10Buffer*			m_pVertexBuffer;
	ID3D10Buffer*			m_pIndexBuffer;
public:

	cModel( const TCHAR* filename );
	cModel( const TCHAR* name, int nVerts, int nTris );

	~cModel();

	float GenRadius();
	void Scale( float amt );

	void Draw();

	//==========--------------------------  Access functions.

	int NumVerts(){ return m_verts.size(); }
	int NumTris(){ return m_tris.size(); }
	const TCHAR* Name(){ return m_name.c_str(); }

	/**
	 * Some other classes may end up using cModel
	 * to assist in their file parsing.  Because of this
	 * give them a way to get at the vertex and triangle 
	 * data.
	 */
	cGraphicsLayer::cDefaultVertex* VertData(){ return &m_verts[0]; }
	sTri* TriData(){ return &m_tris[0]; }

};

#endif // _MODEL_H
