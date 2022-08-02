/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _GRAPHICSLAYER_H
#define _GRAPHICSLAYER_H

#include <d3d10.h>
#include <d3dx10.h>

#include <list>
#include <string>
using std::wstring;
using std::list;

#include "GameTypes.h"
#include "DxHelper.h"

//--------------------------------------------------------------------------------------
// Manages the insertion point when drawing text
//--------------------------------------------------------------------------------------

class cApplication; 

class cGraphicsLayer
{

protected:

	HWND					m_hWnd;			// The handle to the window

	ID3D10Device*			m_pDevice;		// The IDirect3DDevice10 interface

	ID3D10Texture2D*		m_pBackBuffer;	// Pointer to the back buffer

	ID3D10RenderTargetView* m_pRenderTargetView; // Pointer to the render target view

	IDXGISwapChain*         m_pSwapChain;	// Pointer to the swap chain

	RECT	m_rcScreenRect;					// The dimensions of the screen

	cGraphicsLayer(HWND hWnd);				// Constructor
	static cGraphicsLayer*	m_pGlobalGLayer;// Pointer to the main global gfx object

	ID3DX10Font*			m_pFont;		// The font used for rendering text
	ID3DX10Sprite*			m_pFontSprite;	// Sprites used to hold font characters

	ID3D10InfoQueue*		m_pMessageQueue;// Queue used to hold messages from D3D

	static const UINT		m_uiMAX_CHARS_PER_FRAME = 512;	

public:

	void DestroyAll();
	~cGraphicsLayer();
	
	/**
	 * Initialization calls.
	 */

	void InitD3D(int width, int height, int bpp);

	/**
	 * This function uses Direct3DX to write text to the back buffer.
	 * Its much faster than using the GDI
	 */
	void DrawTextString(int x, int y, D3DXCOLOR color, const TCHAR* str);


	void DumpMessages();
	//==========--------------------------  Accessor functions

	// Gets a pointer to the device
	ID3D10Device* GetDevice()
	{
		return m_pDevice;
	}

	// Gets a pointer to the back buffer
	ID3D10Texture2D* GetBackBuffer()
	{
		return m_pBackBuffer;
	}

	// Gets the screen width
	int Width() const
	{
		return m_rcScreenRect.right;
	}

	// Gets the screen height
	int Height() const
	{
		return m_rcScreenRect.bottom;
	}

	// Presents the back buffer to the primary surface
	void Present();

	// Clears the back buffer
	void Clear(const float (&colClear)[4]);

	// Gets a pointer to the main gfx object
	static cGraphicsLayer* GetGraphics()
	{
		return m_pGlobalGLayer;
	}

	// Initializes this object
	static void Create(
		HWND hWnd, // handle to the window
		short width, short height); // Device guid
};

inline cGraphicsLayer* Graphics()
{
	return cGraphicsLayer::GetGraphics();
}


#endif //_GRAPHICSLAYER_H
