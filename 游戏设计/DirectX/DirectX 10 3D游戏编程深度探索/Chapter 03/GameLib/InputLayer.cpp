/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "InputLayer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Application.h"
#include "Window.h"

cInputLayer* cInputLayer::m_pGlobalILayer = NULL;

cInputLayer::cInputLayer( 
	HINSTANCE hInst, 
	HWND hWnd, 
	bool bExclusive, 
	bool bUseKeyboard, 
	bool bUseMouse )
{


	m_pKeyboard = NULL;
	m_pMouse = NULL;

	if( m_pGlobalILayer )
	{
		throw cGameError(L"cInputLayer already initialized!\n");
	}
	m_pGlobalILayer = this;

	HRESULT hr;

	/**
	 * Create the DI8 object
	 */

	hr = DirectInput8Create( hInst, DIRECTINPUT_VERSION, 
						IID_IDirectInput8, (void**)&m_pDI, NULL );
    if( FAILED(hr) )
	{
		throw cGameError(L"DirectInput8 object could not be created\n"); 
	}

	try 
	{
		if( bUseKeyboard )
		{
			m_pKeyboard = new cKeyboard( hWnd );
		}
		if( bUseMouse )
		{
			m_pMouse = new cMouse( hWnd, bExclusive );
		}
	}
	catch( ... )
	{
		SafeRelease( m_pDI );
		throw;
	}

}


cInputLayer::~cInputLayer()
{
	if( m_pDI )
	{
		if( m_pKeyboard )
		{
			delete m_pKeyboard; // this does all the de-init.
		}

		if( m_pMouse )
		{
			delete m_pMouse; // this does all the de-init.
		}
		SafeRelease( m_pDI );
	}
	m_pGlobalILayer = NULL;
}

void cInputLayer::UpdateDevices()
{
	if( m_pKeyboard )
	{
		m_pKeyboard->Update();
	}
	if( m_pMouse )
	{
		m_pMouse->Update();
	}
}


void cInputLayer::SetFocus()
{
	if( m_pKeyboard )
	{
		m_pKeyboard->ClearTable();
	}
	if( m_pMouse )
	{
		m_pMouse->Acquire();
	}
}


void cInputLayer::KillFocus()
{
	if( m_pKeyboard )
	{
		m_pKeyboard->ClearTable();
	}
	if( m_pMouse )
	{
		m_pMouse->UnAcquire();
	}
}
