/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/
#include "stdafx.h"

#include "bezier.h"

//  Controls:
//      Keypad / Arrow Keys : control teapot
//      [Z] : Increase Tesselation level
//      [X] : Decrease Tesselation level
//      [C] : Cycle rendering mode (filled/wireframe)
//      [V] : Toggle Contrl mesh


class cBezierApp : public cApplication,
	public iKeyboardReceiver

{

	// Controls for the object.
	float m_yaw;
	float m_pitch;
	float m_roll;
	float m_dist;

	// how long the last frame took (the next one should take about as long)
	float m_timeDelta;

	// The actual object
	cBezierObject m_bezObj;

	// matrix for the teapot
	matrix4	m_objMat;

	// If this is true, draw the control net
	bool m_drawNet;

	ID3D10RasterizerState* m_pSolidState;
	ID3D10RasterizerState* m_pWireState;

public:

	//==========--------------------------  cApplication

	virtual void DoFrame( float timeDelta );
	virtual void SceneInit();


	cBezierApp() :
		cApplication()
	{
		m_title = std::wstring( L"Parametric Surface Sample Application" );
	}

	//==========--------------------------  iKeyboardReceiver

	virtual void KeyUp( int key );
	virtual void KeyDown( int key );

	//==========--------------------------  cBezierApp
	void InitLights();
};

cApplication* CreateApplication()
{
	return new cBezierApp();
	
}

void cBezierApp::SceneInit()
{
	Input()->GetKeyboard()->SetReceiver( this );

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

	//// initialize the camera
	Graphics()->SetViewMtx( *(D3DXMATRIX*)&matrix4::Identity );

	//// we could load any mesh file we wanted here 
	m_bezObj.Load( L"..\\bin\\media\\teapot.bez" );

	m_yaw = -0.0f;
	m_pitch = -0.0f;
	m_roll = 0.0f;
	m_dist = 50.0f;
	
	m_drawNet = true;

	m_timeDelta = 0.03f; // a 30th of a second is a good first value

	// set up our Lights system.
	InitLights();

}


void cBezierApp::DoFrame( float timeDelta )
{
	// update the time
	m_timeDelta = timeDelta;

	m_objMat.MakeIdent();
	m_objMat.Rotate( m_yaw, m_pitch, m_roll );
	m_objMat.Place( point3(0.001f, -15.0, m_dist) );

	Graphics()->UpdateMatrices();
	Graphics()->UpdateLights();

	// Clear the previous contents of the backbuffer
	float colClear[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	Graphics()->Clear(colClear);
	Graphics()->ClearDepthStencil(1.0f, 0);

	m_bezObj.Draw( m_objMat, m_drawNet );

	// flip the buffer.
	Graphics()->Present();
}

void cBezierApp::InitLights()
{

}


void cBezierApp::KeyUp( int key )
{
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
	if( key == DIK_V )
	{
		m_drawNet = !m_drawNet;
	}
}


void cBezierApp::KeyDown( int key )
{

	switch( key )
	{
	case DIK_Z:
		m_bezObj.IncTesselation();
		break;

	case DIK_X:
		m_bezObj.DecTesselation();
		break;

	case DIK_PRIOR:
	case DIK_NUMPAD9:
		m_dist -= m_timeDelta * 30.f;
		break;

	case DIK_NEXT:
	case DIK_NUMPAD3:
		m_dist += m_timeDelta * 30.f;
		break;

	case DIK_UP:
	case DIK_NUMPAD8:
		m_yaw += m_timeDelta * 1.f;
		break;

	case DIK_DOWN:
	case DIK_NUMPAD2:
		m_yaw -= m_timeDelta * 1.f;
		break;

	case DIK_RIGHT:
	case DIK_NUMPAD6:
		m_pitch += m_timeDelta * 1.f;
		break;

	case DIK_LEFT:
	case DIK_NUMPAD4:
		m_pitch -= m_timeDelta * 1.f;
		break;

	case DIK_HOME:
	case DIK_NUMPAD7:
		m_roll += m_timeDelta * 1.f;
		break;

	case DIK_END:
	case DIK_NUMPAD1:
		m_roll -= m_timeDelta * 1.f;
		break;
	}

}

