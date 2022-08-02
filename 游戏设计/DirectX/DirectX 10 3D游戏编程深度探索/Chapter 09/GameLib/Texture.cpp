/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "Texture.h"
#include "GraphicsLayer.h"

using std::vector;

cTexture::cTexture( const TCHAR* filename, DWORD stage )
{

	m_pShaderResourceView = NULL;
	ID3D10Texture2D* pTempTex = 0;

	m_pTexture = 0;

	m_name = wstring( filename );
	m_stage = stage;

	ReadDDSTexture( &m_pTexture );
}



cTexture::~cTexture()
{
	SafeRelease( m_pTexture );
}



void cTexture::ReadDDSTexture( ID3D10Texture2D** pTexture )
{
	HRESULT r = 0;
	
	r = D3DX10CreateTextureFromFile(
		Graphics()->GetDevice(),
		m_name.c_str(),
		NULL,
		NULL,
		(ID3D10Resource**)pTexture,
		NULL);

	if( FAILED( r ) )
	{
		throw cGameError( L"Bad DDS file\n");
	}
}


ID3D10Texture2D* cTexture::GetTexture()
{
	return m_pTexture;
}

ID3D10ShaderResourceView* cTexture::GetShaderView()
{
	if(!m_pShaderResourceView)
	{
		D3D10_TEXTURE2D_DESC decTexture;
		m_pTexture->GetDesc(&decTexture);

		D3D10_SHADER_RESOURCE_VIEW_DESC descShaderView;
		memset(&descShaderView, 0, sizeof(descShaderView));
		descShaderView.Format = decTexture.Format;
		descShaderView.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
		descShaderView.Texture2D.MipLevels = decTexture.MipLevels;
		
		Graphics()->GetDevice()->CreateShaderResourceView(
			m_pTexture, &descShaderView, &m_pShaderResourceView);

	}

	return m_pShaderResourceView;
}


