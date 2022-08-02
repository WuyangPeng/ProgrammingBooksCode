/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"

#include <string>
using namespace std;

class cD3DSampleApp : public cApplication
{

public:

	//==========--------------------------  cApplication

	virtual void DoFrame( float timeDelta );

	cD3DSampleApp() :
		cApplication()
	{
		m_title = wstring( L"Direct3D Sample" );
	}
};

cApplication* CreateApplication()
{
	return new cD3DSampleApp();
}

void cD3DSampleApp::DoFrame( float timeDelta )
{
	if(!Graphics()) 
		return;

	// Clear the previous contents of the backbuffer
	float colClear[4] = {RandFloat(), RandFloat(), RandFloat(), 1.0f};
	Graphics()->Clear(colClear);
	
	// Output green text at a random location
	Graphics()->DrawTextString( rand()%640, rand()%480, 
			D3DXCOLOR(0, 1, 0, 1), L"Advanced Direct3D 10.0" );

	// Present the back buffer to the primary surface to make it visible
	Graphics()->Present();
}

