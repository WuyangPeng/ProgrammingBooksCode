/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include <algorithm>

#include "stdafx.h"
#include "GraphicsLayer.h"
#include "Application.h"
#include "GameErrors.h"
#include "DxHelper.h"
#include "Window.h"

using namespace std;


/**
 * This is the static member variable that points to the one
 * (and only one) graphics layer allowed in each application.
 */
cGraphicsLayer* cGraphicsLayer::m_pGlobalGLayer = NULL;

cGraphicsLayer::cGraphicsLayer(HWND hWnd)
{
	if(m_pGlobalGLayer)
		throw cGameError(
			L"cGraphicsLayer object already instantiated\n");
	m_pGlobalGLayer = this;

	m_hWnd = hWnd;
	m_pDevice = NULL;
	m_pBackBuffer = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_pFont = NULL;		
	m_pFontSprite = NULL;	
	m_pMessageQueue = NULL;
}


void cGraphicsLayer::DestroyAll()
{
	SafeRelease(m_pMessageQueue);
	SafeRelease(m_pFont);
	SafeRelease(m_pFontSprite);
	SafeRelease(m_pRenderTargetView);
    SafeRelease(m_pBackBuffer);	
	SafeRelease(m_pSwapChain);
	SafeRelease(m_pDevice);

	/**
	 * Prevent any further access to the graphics class
	 */
	m_pGlobalGLayer = NULL;
}

cGraphicsLayer::~cGraphicsLayer()
{
	DestroyAll();
}


void cGraphicsLayer::Present()
{
	HRESULT r = S_OK;

	assert(m_pDevice);
    
	r = m_pSwapChain->Present(0, 0);
	if(FAILED(r))
	{
		OutputDebugString(L"Present Failed!\n");
	}

	DumpMessages();
}

void cGraphicsLayer::DumpMessages()
{
	assert(m_pMessageQueue);

	HRESULT r = 0;

	while(1)
	{
		// Get the size of the message
		SIZE_T messageLength = 0;
		r = m_pMessageQueue->GetMessage(0, NULL, &messageLength);
		if(messageLength == 0)
			break;

		// Allocate space and get the message
		D3D10_MESSAGE * pMessage = (D3D10_MESSAGE*)malloc(messageLength);
		r = m_pMessageQueue->GetMessage(0, pMessage, &messageLength);
		if(FAILED(r))
		{
			OutputDebugString(L"Failed to get Direct3D Message");
			break;
		}
	
		TCHAR strOutput[MAX_PATH];
		swprintf_s(strOutput, MAX_PATH, L"D3DDMSG [Cat[%i] Sev[%i] ID[%i]: %s\n",
			pMessage->Category, pMessage->Severity, pMessage->ID, pMessage->pDescription);
		OutputDebugString(strOutput);
	}
}

void cGraphicsLayer::Clear(const float (&colClear)[4])
{
	HRESULT r = S_OK;
	assert(m_pDevice);

	m_pDevice->ClearRenderTargetView(m_pRenderTargetView, colClear);
}

void cGraphicsLayer::InitD3D(int width, int height, int bpp)
{
	HRESULT r = 0;

	// Structure to hold the creation parameters for the device
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(swapDesc));

	// Only want one back buffer
	swapDesc.BufferCount = 1;

	// Width and height of the back buffer
    swapDesc.BufferDesc.Width = 640;
    swapDesc.BufferDesc.Height = 480;

	// Standard 32bit surface type
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 60hz refresh rate
    swapDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Connect it to our main window
    swapDesc.OutputWindow = m_hWnd;

	// No multisampling
    swapDesc.SampleDesc.Count = 1;
    swapDesc.SampleDesc.Quality = 0;

	// Windowed mode
    swapDesc.Windowed = TRUE;
	
	// Create the device using hardware acceleration 
	r = D3D10CreateDeviceAndSwapChain( 
			NULL,							// Default adapter
			D3D10_DRIVER_TYPE_HARDWARE,		// Hardware accelerated device
			NULL,							// Not using a software DLL for rendering
			D3D10_CREATE_DEVICE_DEBUG,		// Flag to allow debug output
			D3D10_SDK_VERSION,				// Indicates the SDK version being used
			&swapDesc,		
			&m_pSwapChain,
			&m_pDevice);

	if(FAILED(r))
	{
		throw cGameError(L"Could not create IDirect3DDevice10");
	}

	r = m_pDevice->QueryInterface(__uuidof(ID3D10InfoQueue), (LPVOID*)&m_pMessageQueue);
	if(FAILED(r))
	{
		throw cGameError(L"Could not create IDirect3DDevice10 message queue");
	}
	m_pMessageQueue->SetMuteDebugOutput(false);	// No muting
	m_pMessageQueue->SetMessageCountLimit(-1);	// Unlimited messages

	// Keep a copy of the screen dimensions
	m_rcScreenRect.left = m_rcScreenRect.top = 0;
	m_rcScreenRect.right = width;
	m_rcScreenRect.bottom = height;

	// Get a copy of the pointer to the back buffer
    r = m_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&m_pBackBuffer);
    if(FAILED(r))
	{
		throw cGameError(L"Could not get back buffer");
	}
	
	// Create a render target view
    r = m_pDevice->CreateRenderTargetView(m_pBackBuffer, NULL, &m_pRenderTargetView);
    if(FAILED(r))
	{
		throw cGameError(L"Could not create render target view");
	}

	// Attach the render target view to the output merger state
    m_pDevice->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	// Create a viewport the same size as the backbuffer
	D3D10_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_pDevice->RSSetViewports( 1, &vp );

	// Create the font for rendering text
	D3DX10CreateFont(m_pDevice, 
		15, 0, 
		FW_BOLD, 
		1, 
		FALSE, 
		DEFAULT_CHARSET, 
        OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_DONTCARE, 
		L"Arial", 
		&m_pFont);
	assert(m_pFont);

	// Create the sprite to use to render letters
	D3DX10CreateSprite(m_pDevice, m_uiMAX_CHARS_PER_FRAME, &m_pFontSprite);
}


void cGraphicsLayer::DrawTextString(int x, int y, 
							D3DXCOLOR color, const TCHAR* strOutput)
{
	m_pFontSprite->Begin(0);
	RECT rect = {x, y, m_rcScreenRect.right, m_rcScreenRect.bottom};
	m_pFont->DrawText(m_pFontSprite, strOutput, -1, &rect, DT_LEFT, color);
	m_pFontSprite->End();
}


void cGraphicsLayer::Create(HWND hWnd, short width, short height)
{
	new cGraphicsLayer(hWnd); // construct the object.

	// Init Direct3D and the device for fullscreen operation
	Graphics()->InitD3D(width, height, 32);
}
