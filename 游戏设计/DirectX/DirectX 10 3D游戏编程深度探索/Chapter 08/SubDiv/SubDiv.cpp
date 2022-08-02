/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "SubDivSurf.h"


//  Controls:
//      Keypad / Arrow Keys : control object
//      [X] : Subdivide Model (this can get slow!)
//      [C] : Change Rendering Mode (solid/wire/point)


class cSubDivApp : public cApplication,
	public iKeyboardReceiver
{

public:

	/**
	 * Controls for the object.
	 */
	float m_yaw;
	float m_pitch;
	float m_roll;
	float m_dist;

	/**
	 * how long the last frame took (the next one should take about as long)
	 */
	float m_timeDelta;

	/**
	 * We keep track of how many triangles we have in our scene 
	 * and print the info
	 */
	int m_nTris;

	//==========--------------------------  cApplication

	virtual void DoFrame( float timeDelta );
	virtual void SceneInit();
	virtual void SceneEnd(){ delete m_pSurf; }

	cSubDivApp() :
		cApplication()
	{
		m_title = wstring( L"Subdivision Surface Sample" );
		m_pSurf = NULL;
		m_filename = wstring( L"..\\bin\\media\\rabbit.o3d" );

		m_pSolidState = NULL;
		m_pWireState = NULL;
	}


	cSubDivSurf* m_pSurf;
	matrix4	m_surfMat;
	std::wstring m_filename;

	//==========-------------------------  iKeyboardReceiver

	virtual void KeyUp( int key );
	virtual void KeyDown( int key );

	//==========--------------------------  cSubDivApp

	void InitLights();

	ID3D10RasterizerState* m_pSolidState;
	ID3D10RasterizerState* m_pWireState;
};

cApplication* CreateApplication()
{
	return new cSubDivApp();
}

void DestroyApplication( cApplication* pApp )
{
	delete pApp;
}




void cSubDivApp::SceneInit()
{
	/**
	 * We're making the FOV less than 90 degrees.
	 * this is so the object doesn't warp as much
	 * when we're really close to it.
	 */

	/**
	 * Tell the keyboard object to send us state
	 * changes.
	 */
	Input()->GetKeyboard()->SetReceiver( this );

	/**
	 * initialize our scene
	 */

	ID3D10Device* pDevice = Graphics()->GetDevice();

	D3D10_RASTERIZER_DESC rastDesc;
	rastDesc.AntialiasedLineEnable = false;
	rastDesc.CullMode = D3D10_CULL_NONE;
	rastDesc.DepthBias = 0;
	rastDesc.DepthBiasClamp = 0;
	rastDesc.DepthClipEnable = false;
	rastDesc.FillMode = D3D10_FILL_SOLID;
	rastDesc.FrontCounterClockwise = TRUE;
	rastDesc.MultisampleEnable = false;
	rastDesc.ScissorEnable = false;
	rastDesc.SlopeScaledDepthBias = 0.0f;

	pDevice->CreateRasterizerState(&rastDesc, &m_pSolidState);
	pDevice->RSSetState(m_pSolidState);

	rastDesc.FillMode = D3D10_FILL_WIREFRAME;
	pDevice->CreateRasterizerState(&rastDesc, &m_pWireState);


	/**
	 * initialize the camera
	 */
	Graphics()->SetViewMtx( *(D3DXMATRIX*)&matrix4::Identity );


	m_pSurf = new cSubDivSurf( m_filename.c_str() );

	m_yaw = 0;
	m_pitch = PI;
	m_roll = 0.0f;
	m_dist = 3.0f;
	m_nTris = m_pSurf->NumTris();

	m_timeDelta = 0.03f; // a 30th of a second is a good first value

	// set up our lighting system.
	InitLights();

}


float GetFrameRate( float timeDelta )
{
	if( timeDelta < 1/60.f )
		timeDelta = 1/60.f;

	float fps = (float)((int)(1.f/timeDelta));

	return fps;
}


void cSubDivApp::DoFrame( float timeDelta )
{
	/**
	 * update the time
	 */
	m_timeDelta = timeDelta;
	static int count = 0;

	/**
	 * then, draw the frame.
	 */
	ID3D10Device* pDevice = Graphics()->GetDevice();
	if( pDevice )
	{
		Graphics()->UpdateMatrices();
		Graphics()->UpdateLights();

		// Clear the previous contents of the backbuffer
		float colClear[4] = {0.1f, 0.1f, 0.1f, 1.0f};
		Graphics()->Clear(colClear);
		Graphics()->ClearDepthStencil(1.0f, 0);

		/**
		 * Here is where we actually draw our object
		 */
		m_surfMat.MakeIdent();
		m_surfMat.Rotate( m_yaw, m_pitch, m_roll );
		m_surfMat.Place( point3(0.001f, 0.0, m_dist) );

		m_pSurf->Draw( m_surfMat );


		/**
		 * flip the buffer.
		 */
		Graphics()->Present();
	}
}

void cSubDivApp::InitLights()
{
	Graphics()->AddLight(D3DXCOLOR(1, 1, 0, 1), D3DXVECTOR3(0,1,0));
}

void cSubDivApp::KeyUp( int key )
{
	if( key == DIK_X )
	{
		m_pSurf->Subdivide();
		m_nTris = m_pSurf->NumTris();
	}
	if( key == DIK_C )
	{
		ID3D10Device* pDevice = Graphics()->GetDevice();
		
		ID3D10RasterizerState* pState;
		pDevice->RSGetState(&pState);

		if(pState == m_pSolidState)
		{
			pDevice->RSSetState(m_pWireState);
		}
		else 
		{
			pDevice->RSSetState(m_pSolidState);
		}	

		if(pState)
			pState->Release();			
	}
}


void cSubDivApp::KeyDown( int key )
{
	if( key == DIK_PRIOR || key == DIK_NUMPAD9 )
	{
		m_dist -= m_timeDelta * 3.f;
	}
	if( key == DIK_NEXT || key == DIK_NUMPAD3 )
	{
		m_dist += m_timeDelta * 3.f;
	}

	if( key == DIK_UP || key == DIK_NUMPAD8 )
	{
		m_yaw += m_timeDelta * 1.5f;
	}
	if( key == DIK_DOWN || key == DIK_NUMPAD2 )
	{
		m_yaw -= m_timeDelta * 1.5f;
	}

	if( key == DIK_RIGHT || key == DIK_NUMPAD6 )
	{
		m_pitch += m_timeDelta * 1.5f;
	}
	if( key == DIK_LEFT || key == DIK_NUMPAD4 )
	{
		m_pitch -= m_timeDelta * 1.5f;
	}

	if( key == DIK_HOME || key == DIK_NUMPAD7 )
	{
		m_roll += m_timeDelta * 1.5f;
	}
	if( key == DIK_END || key == DIK_NUMPAD1 )
	{
		m_roll -= m_timeDelta * 1.5f;
	}
}