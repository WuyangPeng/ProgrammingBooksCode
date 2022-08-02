/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/
#include "stdafx.h"

class cD3DSampleApp : public cApplication
{

public:

	wstring m_filename;
	cModel* m_pModel;

	void InitLights();

	//==========--------------------------  cApplication

	virtual void DoFrame( float timeDelta );
	virtual void SceneInit();

	virtual void SceneEnd()
	{
		delete m_pModel;
	}

	cD3DSampleApp() :
		cApplication()
	{
		m_title = wstring( L"D3D 10 Sample - Spinning Objects" );
		m_pModel = NULL;
		m_filename = L"..\\BIN\\Media\\rabbit.o3d";
		m_pVertexBuffer = NULL;
	}

protected:
	ID3D10Buffer* m_pVertexBuffer;
};

cApplication* CreateApplication()
{
	return new cD3DSampleApp();
}

void DestroyApplication( cApplication* pApp )
{
	delete pApp;
}

void cD3DSampleApp::SceneInit()
{
	/**
	 * Create a model with the given filename,
	 * and resize it so it fits inside a unit sphere.
	 */
	m_pModel = new cModel( m_filename.c_str() );
	m_pModel->Scale(1.0f / m_pModel->GenRadius() );

	InitLights();
}


void cD3DSampleApp::InitLights()
{
	Graphics()->AddLight(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}


void cD3DSampleApp::DoFrame( float timeDelta )
{
	if(!Graphics()) 
		return;

	Graphics()->UpdateMatrices();
	Graphics()->UpdateLights();

	// Clear the previous contents of the backbuffer
	float colClear[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	Graphics()->Clear(colClear);
	Graphics()->ClearDepthStencil(1.0f, 0);
	
	D3D10_TECHNIQUE_DESC descTechnique;
    Graphics()->GetDefaultTechnique()->GetDesc(&descTechnique);
    for(UINT uiCurPass = 0; uiCurPass < descTechnique.Passes; uiCurPass++)
    {		
        Graphics()->GetDefaultTechnique()->GetPassByIndex(uiCurPass)->Apply(0);
		m_pModel->Draw();
    }

	// Present the back buffer to the primary surface to make it visible
	Graphics()->Present();
}