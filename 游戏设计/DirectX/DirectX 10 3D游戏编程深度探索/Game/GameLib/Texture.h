/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>

class cGraphicsLayer;

class cTexture
{
protected:

	void ReadDDSTexture( ID3D10Texture2D** pTexture);

	ID3D10Texture2D*	m_pTexture;
	ID3D10ShaderResourceView* m_pShaderResourceView;

	wstring	m_name;

	// The stage for this particular texture.
	DWORD	m_stage;	

public:
	cTexture( const TCHAR* filename, DWORD stage = 0 );
	virtual ~cTexture();
 
	ID3D10Texture2D* GetTexture();

	ID3D10ShaderResourceView* GetShaderView();

};

#endif //_TEXTURE_H
