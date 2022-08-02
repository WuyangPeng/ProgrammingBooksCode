/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"

#include "RadiosityCalc.h"

#include <functional>
#include <string>

using namespace std;

cRadiosityCalc radCalc;

HWND g_hWnd;


class cRadiosityApp : public cApplication
{

public:

	//==========--------------------------  cRadiosityApp

	cRadiosityApp() : cApplication() 
	{
		m_title = wstring( L"Radiosity Sample" );
	}

	void SceneInit();
	void DoFrame( float timeDelta );
};

cApplication* CreateApplication()
{
	return new cRadiosityApp();
}

void DestroyApplication( cApplication* pApp )
{
	delete pApp;
}


void cRadiosityApp::SceneInit()
{
	// initialize our scene
	ID3D10Device* pDevice = Graphics()->GetDevice();

	// initialize the camera
	matrix4 camMat = matrix4::CameraLookAt( point3(0,0,22), point3(0,0,0) );
	Graphics()->SetViewMtx( *(D3DXMATRIX*)&camMat );

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

	ID3D10RasterizerState* pState = NULL;
	pDevice->CreateRasterizerState(&rastDesc, &pState);
	pDevice->RSSetState(pState);
	
	cFile file;
	file.Open( L"..\\Bin\\media\\complex.rad" );
	radCalc.Load( file );
	file.Close();
}

void cRadiosityApp::DoFrame( float timeDelta )
{

	static float rho = 0.f, theta = 0.0f, dist = 30.0f;

	static float wind = 0.0;
	wind += 0.1f;

	static bool bCWasUp = false;

	// first, run our key checks.
	if( Input()->GetKeyboard()->Poll( DIK_NUMPAD9 ) )
		dist -= 3.f;
	if( Input()->GetKeyboard()->Poll( DIK_NUMPAD3 ) )
		dist += 3.f;

	if( Input()->GetKeyboard()->Poll( DIK_NUMPAD8 ) )
		rho += 0.05f;
	if( Input()->GetKeyboard()->Poll( DIK_NUMPAD2 ) )
		rho -= 0.05f;

	if( Input()->GetKeyboard()->Poll( DIK_NUMPAD6 ) )
		theta += 0.05f;
	if( Input()->GetKeyboard()->Poll( DIK_NUMPAD4 ) )
		theta -= 0.05f;

	Snap( rho, -PI/2.f, PI/2.f );
	Snap( dist, 2.f, 100.f );

	point3 temp = point3::Spherical( theta, rho, dist );

	Graphics()->SetViewMtx( *(D3DXMATRIX*)&matrix4::CameraLookAt(temp, point3(0,0,0) ));

	static bool keepIterating = true;

	if( keepIterating )
	{
		keepIterating = radCalc.CalcNextIteration();
	}

	Graphics()->UpdateMatrices();
	Graphics()->UpdateLights();
	// draw the scene
	// Clear the previous contents of the backbuffer
	float colClear[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	Graphics()->Clear(colClear);
	Graphics()->ClearDepthStencil(1.0f, 0);

	radCalc.Draw();	

	// flip the buffer.
	Graphics()->Present();
}

