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
	m_pDefaultEffect = NULL;
	m_pDefaultTechnique = NULL;
	m_pDefaultInputLayout = NULL;
	m_pmtxWorldVar = NULL;
	m_pmtxViewVar = NULL;
	m_pmtxProjVar = NULL;
	m_pLightDirVar = NULL;
	m_pLightColorVar = NULL;
	m_pDepthStencilBuffer = NULL;
	m_pDepthStencilState = NULL;
	m_pDepthStencilView = NULL;
	m_pNumLightsVar = NULL;
	
	m_pTexturesVar = NULL;

	// Default to identity 
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixIdentity(&m_mtxProj);

	m_iNumLights = 0;
}


void cGraphicsLayer::DestroyAll()
{
	if(m_pDevice) 
		m_pDevice->ClearState();

	// Release in opposite order to creation usually
	SafeRelease(m_pDefaultInputLayout);
	SafeRelease(m_pDefaultEffect);
	SafeRelease(m_pMessageQueue);
	SafeRelease(m_pFont);
	SafeRelease(m_pFontSprite);
	SafeRelease(m_pDepthStencilView);
	SafeRelease(m_pDepthStencilState);
	SafeRelease(m_pRenderTargetView);
    SafeRelease(m_pBackBuffer);	
	SafeRelease(m_pDepthStencilBuffer);
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

	int iCount = 0;
	while(1)
	{
		iCount++;
		if(iCount > 10)
			break;

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
	
		TCHAR strOutput[2048];
		
		const char* pCompileErrors = static_cast<const char*>(pMessage->pDescription);
		TCHAR wcsErrors[2048];
		UINT uiNumConverted = 0;
        mbstowcs_s(&uiNumConverted, wcsErrors, 2048, pCompileErrors, 2048);

		swprintf_s(strOutput, 2048, L"D3DDMSG [Cat[%i] Sev[%i] ID[%i]: %s\n",
			pMessage->Category, pMessage->Severity, pMessage->ID, wcsErrors);
		OutputDebugString(strOutput);
	}
}

void cGraphicsLayer::Clear(const float (&colClear)[4])
{
	assert(m_pDevice);
	m_pDevice->ClearRenderTargetView(m_pRenderTargetView, colClear);
}

void cGraphicsLayer::ClearDepthStencil(const float fDepth, const UINT8 uiStencil)
{
	assert(m_pDevice);
	m_pDevice->ClearDepthStencilView(m_pDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, fDepth, uiStencil);
}

void cGraphicsLayer::UpdateLights()
{
	return;
	int iLightData[4] = {m_iNumLights, 0, 0, 0};

	m_pNumLightsVar->SetIntVector(iLightData);

	for(int iCurLight = 0 ; iCurLight < m_iNumLights ; iCurLight++)
	{
		m_pLightDirVar->SetFloatVectorArray((float*)m_aLights[iCurLight].m_vDirection, iCurLight, 1);
		m_pLightColorVar->SetFloatVectorArray((float*)m_aLights[iCurLight].m_vColor, iCurLight, 1);	
	}
}

void cGraphicsLayer::InitD3D(int width, int height)
{
	HRESULT r = 0;
	
	// Keep a copy of the screen dimensions
	m_rcScreenRect.left = m_rcScreenRect.top = 0;
	m_rcScreenRect.right = width;
	m_rcScreenRect.bottom = height;	

	CreateDeviceAndSwapChain();
	CreateViewport();
	CreateDepthStencilBuffer();
	CreateDebugText();

	// Attach the render target view to the output merger state
    m_pDevice->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	CreateDefaultShader();
}

void cGraphicsLayer::CreateDeviceAndSwapChain()
{
	HRESULT r = 0;

	// Structure to hold the creation parameters for the device
	DXGI_SWAP_CHAIN_DESC descSwap;
	ZeroMemory(&descSwap, sizeof(descSwap));

	// Only want one back buffer
	descSwap.BufferCount = 1;

	// Width and height of the back buffer
    descSwap.BufferDesc.Width = m_rcScreenRect.right;
    descSwap.BufferDesc.Height = m_rcScreenRect.bottom;

	// Standard 32bit surface type
    descSwap.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 60hz refresh rate
    descSwap.BufferDesc.RefreshRate.Numerator = 60;
    descSwap.BufferDesc.RefreshRate.Denominator = 1;
    descSwap.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Connect it to our main window
    descSwap.OutputWindow = m_hWnd;

	// No multisampling
    descSwap.SampleDesc.Count = 1;
    descSwap.SampleDesc.Quality = 0;

	// Windowed mode
    descSwap.Windowed = TRUE;
	
	// Create the device using hardware acceleration 
	r = D3D10CreateDeviceAndSwapChain( 
			NULL,							// Default adapter
			D3D10_DRIVER_TYPE_HARDWARE,		// Hardware accelerated device
			NULL,							// Not using a software DLL for rendering
			D3D10_CREATE_DEVICE_DEBUG,		// Flag to allow debug output
			D3D10_SDK_VERSION,				// Indicates the SDK version being used
			&descSwap,		
			&m_pSwapChain,
			&m_pDevice);

	if(FAILED(r))
	{
		throw cGameError(L"Could not create IDirect3DDevice10");
	}

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

	r = m_pDevice->QueryInterface(__uuidof(ID3D10InfoQueue), (LPVOID*)&m_pMessageQueue);
	if(FAILED(r))
	{
		throw cGameError(L"Could not create IDirect3DDevice10 message queue");
	}
	m_pMessageQueue->SetMuteDebugOutput(false);	// No muting
	m_pMessageQueue->SetMessageCountLimit(-1);	// Unlimited messages
}

void cGraphicsLayer::CreateViewport()
{
	// Create a viewport the same size as the backbuffer
	D3D10_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(vp));
    vp.Width = m_rcScreenRect.right;
    vp.Height = m_rcScreenRect.bottom;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_pDevice->RSSetViewports( 1, &vp );
}

void cGraphicsLayer::CreateDebugText()
{
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

void cGraphicsLayer::CreateDepthStencilBuffer()
{
	HRESULT r = 0;
	// Create the depth buffer
	D3D10_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = m_rcScreenRect.right;
	descDepth.Height = m_rcScreenRect.bottom;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	r = m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencilBuffer); 
	if(FAILED(r))
	{
		throw cGameError(L"Unable to create depth buffer");
	}

	D3D10_DEPTH_STENCIL_DESC descDS;
	ZeroMemory(&descDS, sizeof(descDS));
	descDS.DepthEnable = true;
	descDS.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	descDS.DepthFunc = D3D10_COMPARISON_LESS;

	// Stencil test values
	descDS.StencilEnable = true;
	descDS.StencilReadMask =  (UINT8)0xFFFFFFFF;
	descDS.StencilWriteMask = (UINT8)0xFFFFFFFF;

	// Stencil op if pixel is front
	descDS.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	descDS.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	descDS.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	descDS.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	// Stencil op if pixel is back
	descDS.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	descDS.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	descDS.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	descDS.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	r = m_pDevice->CreateDepthStencilState(&descDS, &m_pDepthStencilState);
	if(FAILED(r))
	{
		throw cGameError(L"Could not create depth/stencil state");
	}
	m_pDevice->OMSetDepthStencilState(m_pDepthStencilState, 1);

	D3D10_DEPTH_STENCIL_VIEW_DESC descDSView;
	ZeroMemory(&descDSView, sizeof(descDSView));
	descDSView.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSView.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSView.Texture2D.MipSlice = 0;

	r = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &descDSView, &m_pDepthStencilView);
	if(FAILED(r))
	{
		throw cGameError(L"Could not create depth/stencil view");
	}
}

void cGraphicsLayer::CreateDefaultShader()
{
	HRESULT r = 0;

	DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
    #if defined( DEBUG ) || defined( _DEBUG )
		// Turn on extra debug info when in debug config
		shaderFlags |= D3D10_SHADER_DEBUG;
    #endif

	ID3D10Blob* pErrors = 0;
	// Create the default rendering effect
	r = D3DX10CreateEffectFromFile(L"../GameLib/DefaultShader.fx", NULL, NULL, "fx_4_0", shaderFlags, 0, 
                                     m_pDevice, NULL, NULL, &m_pDefaultEffect, &pErrors, NULL);
	if(pErrors)
	{
		char* pCompileErrors = static_cast<char*>(pErrors->GetBufferPointer());
		TCHAR wcsErrors[MAX_PATH];
		UINT uiNumConverted = 0;
        mbstowcs_s(&uiNumConverted, wcsErrors, MAX_PATH, pCompileErrors, MAX_PATH);
		OutputDebugString(wcsErrors);
	}

	if(FAILED(r))
	{
		throw cGameError(L"Could not create default shader - DefaultShader.fx");
	}

	m_pDefaultTechnique = m_pDefaultEffect->GetTechniqueByName("DefaultTechnique");
	if(!m_pDefaultTechnique)
	{
		throw cGameError(L"Could not find default technique in DefaultShader.fx");
	}

	// Setup the input layout
    D3D10_INPUT_ELEMENT_DESC defaultLayout[] =
    {
        {"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,								D3D10_INPUT_PER_VERTEX_DATA, 0},  
		{"NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D10_APPEND_ALIGNED_ELEMENT,	D3D10_INPUT_PER_VERTEX_DATA, 0}, 
		{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D10_APPEND_ALIGNED_ELEMENT,	D3D10_INPUT_PER_VERTEX_DATA, 0}, 
		{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D10_APPEND_ALIGNED_ELEMENT,	D3D10_INPUT_PER_VERTEX_DATA, 0}, 
		{"TEXCOORD",	1, DXGI_FORMAT_R32G32_FLOAT,		0, D3D10_APPEND_ALIGNED_ELEMENT,	D3D10_INPUT_PER_VERTEX_DATA, 0}, 
	};

	UINT uiNumElements = sizeof(defaultLayout)/sizeof(defaultLayout[0]);
	D3D10_PASS_DESC descPass;
    m_pDefaultTechnique->GetPassByIndex(0)->GetDesc(&descPass);
    r = m_pDevice->CreateInputLayout(defaultLayout, uiNumElements, 
		descPass.pIAInputSignature, descPass.IAInputSignatureSize, &m_pDefaultInputLayout);
    if(FAILED(r))
    {
		throw cGameError(L"Could not create default layout");
	}
	m_pDevice->IASetInputLayout(m_pDefaultInputLayout);
	
	m_pmtxWorldVar = m_pDefaultEffect->GetVariableByName("g_mtxWorld")->AsMatrix();
    m_pmtxViewVar = m_pDefaultEffect->GetVariableByName("g_mtxView")->AsMatrix();
    m_pmtxProjVar = m_pDefaultEffect->GetVariableByName("g_mtxProj")->AsMatrix();

	m_pTexturesVar = m_pDefaultEffect->GetVariableByName( "g_Texture" )->AsShaderResource();

	D3DXMATRIX mtxWorld;
    D3DXMatrixIdentity(&mtxWorld);
	SetWorldMtx(mtxWorld);

	D3DXMATRIX mtxView;
	D3DXVECTOR3 vCamPos(0.0f, 1.0f, -12.0f);
    D3DXVECTOR3 vCamAt(0.0f, 1.0f, 0.0f);
    D3DXVECTOR3 vCamUp(0.0f, 1.0f, 0.0f);
    D3DXMatrixLookAtLH(&mtxView, &vCamPos, &vCamAt, &vCamUp);
	SetViewMtx(mtxView);

	D3DXMATRIX mtxProj;
    D3DXMatrixPerspectiveFovLH(&mtxProj, (float)D3DX_PI * 0.3f, 
		m_rcScreenRect.right/(float)m_rcScreenRect.bottom, 0.1f, 40.0f);
	SetProjMtx(mtxProj);

	UpdateMatrices();

	m_pLightDirVar = m_pDefaultEffect->GetVariableByName( "g_vLightDirections" )->AsVector();
    m_pLightColorVar = m_pDefaultEffect->GetVariableByName( "g_vLightColors" )->AsVector();
	m_pNumLightsVar = m_pDefaultEffect->GetVariableByName( "g_viLightStatus" )->AsVector();

	m_pTextureDataVar = m_pDefaultEffect->GetVariableByName( "g_viTextureStatus" )->AsVector();
}

void cGraphicsLayer::DrawTextString(int x, int y, 
							D3DXCOLOR color, const TCHAR* strOutput)
{ 
	return;
	m_pFontSprite->Begin(0);
	RECT rect = {x, y, m_rcScreenRect.right, m_rcScreenRect.bottom};
	m_pFont->DrawText(m_pFontSprite, strOutput, -1, &rect, DT_LEFT, color);
	m_pFontSprite->End();
}


void cGraphicsLayer::Create(HWND hWnd, short width, short height)
{
	new cGraphicsLayer(hWnd); // construct the object.

	// Init Direct3D and the device for fullscreen operation
	Graphics()->InitD3D(width, height);
}

void cGraphicsLayer::SetNumActiveTexture(int texCount, int iCurrent)
{
	int data[4] = {texCount, iCurrent, 0, 0};
	m_pTextureDataVar->SetIntVector(data);
}

void cGraphicsLayer::UpdateMatrices()
{

	m_pmtxWorldVar->SetMatrix((float*)&m_mtxWorld);
    m_pmtxViewVar->SetMatrix((float*)&m_mtxView);
    m_pmtxProjVar->SetMatrix((float*)&m_mtxProj);
}

void cGraphicsLayer::SetTexture(int iIdx, ID3D10ShaderResourceView* pTexShaderView)
{
	if(m_pTexturesVar)
	{
		m_pTexturesVar->SetResource(pTexShaderView);
	}
}