/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"


//Detail Texture example app
//Advanced 3D Game Programming using DirectX 10
//
//  Controls:
//      [D] : Turn detail textures on/off

class cDetailApp : public cApplication,
	public iKeyboardReceiver

{
	// Data for the square
	cGraphicsLayer::cDefaultVertex m_square[6];
	void LoadTextures();

	void SetStage1();
	void SetStage2();

	cTexture*	m_pTextures[2];

	// If this is true, draw some help on the screen
	bool m_drawHelp;

	void InitSquare();
	void DrawSquare();

	bool m_bCanDoMultitexture;
	bool m_bCanDoAddSigned;
	bool m_bDrawDetail;

public:

	//==========--------------------------  cApplication

	virtual void DoFrame( float timeDelta );
	virtual void SceneInit();

	cDetailApp() :
		cApplication()
	{
		m_pTextures[0] = NULL;
		m_pTextures[1] = NULL;
		m_pTextures[2] = NULL;
		m_title = wstring( L"Detail Textures" );
	}

	~cDetailApp()
	{
		delete m_pTextures[0];
		delete m_pTextures[1];
	}

	//==========--------------------------  iKeyboardReceiver

	virtual void KeyUp( int key );
	virtual void KeyDown( int key );

	//==========--------------------------  cDetailApp
};

cApplication* CreateApplication()
{
	return new cDetailApp();
}

void DestroyApplication( cApplication* pApp )
{
	delete pApp;
}

void cDetailApp::SceneInit()
{
	Input()->GetKeyboard()->SetReceiver( this );

	//// initialize the camera
	Graphics()->SetViewMtx( *(D3DXMATRIX*)&matrix4::Identity );

	// do draw the detail
	m_bDrawDetail = true;

	//// init our geometry
	InitSquare();

	//// load our textures
	LoadTextures();
}


void cDetailApp::DoFrame( float timeDelta )
{
	float colClear[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	Graphics()->Clear(colClear);
	Graphics()->ClearDepthStencil(1.0f, 0);

	static float total =0.f;
	total += timeDelta;
	//
	float dist = 1.1f + 40.f*(1.f + sin(total));

	if(m_bDrawDetail)
		Graphics()->SetNumActiveTexture(1, 0);
	else
		Graphics()->SetNumActiveTexture(2, 0);

	matrix4 mat;
	mat.ToTranslation( point3(0.0f, 0.0f, dist) );
	Graphics()->SetWorldMtx( *(D3DXMATRIX*)&mat );

	Graphics()->UpdateMatrices();

	//// Draw the square
	ID3D10Device* pDevice = Graphics()->GetDevice();

	DrawSquare();
	
	//// flip the buffer.
	Graphics()->Present();
}



void cDetailApp::KeyUp( int key )
{
	if( key == DIK_D )
	{
		m_bDrawDetail = !m_bDrawDetail;
	}
}


void cDetailApp::KeyDown( int key )
{
}


void cDetailApp::InitSquare()
{
	point3 v[4];
	v[0] = point3(-10.f, 10.f,0.f);
	v[1] = point3( 10.f, 10.f,0.f);
	v[2] = point3( 10.f,-10.f,0.f);
	v[3] = point3(-10.f,-10.f,0.f);

	m_square[0].m_vPosition = *(D3DXVECTOR3*)&v[0];
	m_square[0].m_vColor = D3DXCOLOR(1,1,1,1);
	m_square[0].m_vNormal = D3DXVECTOR3(0,0,0);
	m_square[0].m_TexCoords[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_square[0].m_TexCoords[1] = D3DXVECTOR2(0.0f, 0.0f);

	m_square[1].m_vPosition = *(D3DXVECTOR3*)&v[1];
	m_square[1].m_vColor = D3DXCOLOR(1,1,1,1);
	m_square[1].m_vNormal = D3DXVECTOR3(0,0,0);
	m_square[1].m_TexCoords[0] = D3DXVECTOR2(1.0f, 0.0f);
	m_square[1].m_TexCoords[1] = D3DXVECTOR2(1.0f, 0.0f);

	m_square[2].m_vPosition = *(D3DXVECTOR3*)&v[2];
	m_square[2].m_vColor = D3DXCOLOR(1,1,1,1);
	m_square[2].m_vNormal = D3DXVECTOR3(0,0,0);
	m_square[2].m_TexCoords[0] = D3DXVECTOR2(1.0f, 1.0f);
	m_square[2].m_TexCoords[1] = D3DXVECTOR2(1.0f, 1.0f);

	m_square[3].m_vPosition = *(D3DXVECTOR3*)&v[0];
	m_square[3].m_vColor = D3DXCOLOR(1,1,1,1);
	m_square[3].m_vNormal = D3DXVECTOR3(0,0,0);
	m_square[3].m_TexCoords[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_square[3].m_TexCoords[1] = D3DXVECTOR2(0.0f, 0.0f);

	m_square[4].m_vPosition = *(D3DXVECTOR3*)&v[2];
	m_square[4].m_vColor = D3DXCOLOR(1,1,1,1);
	m_square[4].m_vNormal = D3DXVECTOR3(0,0,0);
	m_square[4].m_TexCoords[0] = D3DXVECTOR2(1.0f, 1.0f);
	m_square[4].m_TexCoords[1] = D3DXVECTOR2(1.0f, 1.0f);

	m_square[5].m_vPosition = *(D3DXVECTOR3*)&v[3];
	m_square[5].m_vColor = D3DXCOLOR(1,1,1,1);
	m_square[5].m_vNormal = D3DXVECTOR3(0,0,0);
	m_square[5].m_TexCoords[0] = D3DXVECTOR2(0.0f, 1.0f);
	m_square[5].m_TexCoords[1] = D3DXVECTOR2(0.0f, 1.0f);

}

void cDetailApp::DrawSquare()
{
	ID3D10Device* pDevice = Graphics()->GetDevice();

	static ID3D10Buffer* pVertexBuffer = NULL;
	
	static bool bFirst = true;

	if(bFirst)
	{
		D3D10_BUFFER_DESC descBuffer;
		memset(&descBuffer, 0, sizeof(descBuffer));
		descBuffer.Usage = D3D10_USAGE_DEFAULT;
		descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * 6;
		descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		descBuffer.CPUAccessFlags = 0;
		descBuffer.MiscFlags = 0;
	   
		D3D10_SUBRESOURCE_DATA resData;
		memset(&resData, 0, sizeof(resData));
		resData.pSysMem = &m_square;
		Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &pVertexBuffer);

		bFirst = false;	
	}

	if(pVertexBuffer)
	{
		UINT uiStride = sizeof(cGraphicsLayer::cDefaultVertex);
		UINT uiOffset = 0;
		
		Graphics()->GetDevice()->IASetVertexBuffers(0, 1, &pVertexBuffer, &uiStride, &uiOffset);
		Graphics()->GetDevice()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D10_TECHNIQUE_DESC descTechnique;
		Graphics()->GetDefaultTechnique()->GetDesc(&descTechnique);
		for(UINT uiCurPass = 0; uiCurPass < descTechnique.Passes; uiCurPass++)
		{	
			Graphics()->GetDefaultTechnique()->GetPassByIndex(uiCurPass)->Apply(0);
			pDevice->Draw(6, 0);
		}
	}
}

void cDetailApp::LoadTextures()
{
	ID3D10Device* pDevice = Graphics()->GetDevice();

	/**
	 * base map in texture stage 0
	 */
	m_pTextures[0] = new cTexture( L"..\\bin\\media\\base.dds", 0 ); 
	m_pTextures[1] = new cTexture( L"..\\bin\\media\\detail3.dds", 0 ); 

	ID3D10ShaderResourceView* pViews[2];

	pViews[0] = m_pTextures[0]->GetShaderView();
	pViews[1] = m_pTextures[1]->GetShaderView();

	Graphics()->SetTextureArray(pViews, 2);
}


