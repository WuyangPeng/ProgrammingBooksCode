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

#define MAX_LIGHTS 10	// Ensure this is the same as the shader

class cGraphicsLayer
{
public:
	class cDefaultVertex
	{
	public:
		D3DXVECTOR3 m_vPosition;  
		D3DXVECTOR3 m_vNormal;
		D3DXCOLOR m_vColor;
		D3DXVECTOR2 m_TexCoords[2];
	};

	class cLight
	{
	public:
		cLight()
		{
		}

		D3DXCOLOR m_vColor;
		D3DXVECTOR3 m_vDirection;
	};

protected:

	HWND					m_hWnd;			// The handle to the window

	ID3D10Device*			m_pDevice;		// The IDirect3DDevice10 interface

	ID3D10Texture2D*		m_pBackBuffer;	// Pointer to the back buffer

	ID3D10Texture2D*		m_pDepthStencilBuffer;// Pointer to the depth/stencil buffer
	ID3D10DepthStencilState*m_pDepthStencilState; // The depth/stencil buffer state
	ID3D10DepthStencilView* m_pDepthStencilView;  // View of the depth stencil buffer

	ID3D10RenderTargetView* m_pRenderTargetView;  // Pointer to the render target view

	IDXGISwapChain*         m_pSwapChain;	// Pointer to the swap chain

	RECT	m_rcScreenRect;					// The dimensions of the screen

	cGraphicsLayer(HWND hWnd);				// Constructor
	static cGraphicsLayer*	m_pGlobalGLayer;// Pointer to the main global gfx object

	ID3DX10Font*			m_pFont;		// The font used for rendering text
	ID3DX10Sprite*			m_pFontSprite;	// Sprites used to hold font characters

	ID3D10InfoQueue*		m_pMessageQueue;// Queue used to hold messages from D3D

	static const UINT		m_uiMAX_CHARS_PER_FRAME = 512;	

	ID3D10Effect*			m_pDefaultEffect;		// Default rendering shader
	ID3D10EffectTechnique*	m_pDefaultTechnique;	// Default rendering technique
	ID3D10InputLayout*		m_pDefaultInputLayout;	// Default vertex layout

	ID3D10EffectMatrixVariable* m_pmtxWorldVar;		// Pointer to world matrix variable in the default shader
	ID3D10EffectMatrixVariable* m_pmtxViewVar;		// Pointer to the view matrix variable in the default shader
	ID3D10EffectMatrixVariable* m_pmtxProjVar;		// Pointer to the projection matrix variable in the default shader

	ID3D10EffectVectorVariable* m_pLightDirVar;		// Pointer to the light direction array in the shader
	ID3D10EffectVectorVariable* m_pLightColorVar;	// Pointer to the light color array in the shader
	ID3D10EffectVectorVariable* m_pNumLightsVar;	// Pointer to the variable holding the number of lights 

	ID3D10EffectVectorVariable* m_pTextureDataVar;	// Pointer to the variable holding the number of lights 
	ID3D10EffectShaderResourceVariable* m_pTexturesVar;	// Pointer to the texture variable

	D3DXMATRIX m_mtxWorld;					// World matrix
	D3DXMATRIX m_mtxView;					// View matrix
	D3DXMATRIX m_mtxProj;					// Projection matrix

	cLight m_aLights[MAX_LIGHTS];			// Light array
	int m_iNumLights;						// Number of active lights

public:

	// Adds a light to the light array if there is room
	void AddLight(const D3DXCOLOR& vColor, const D3DXVECTOR3 vDir)
	{
		if(m_iNumLights < MAX_LIGHTS)
		{		
			m_aLights[m_iNumLights].m_vColor = vColor;
			m_aLights[m_iNumLights].m_vDirection = vDir;
			m_iNumLights++;
		}
	}

	// Sends light data to the shader
	void UpdateLights();

	// Updates the transformation matrices
	void SetWorldMtx(const D3DXMATRIX& mtxWorld){m_mtxWorld = mtxWorld;}
	void SetViewMtx(const D3DXMATRIX& mtxView){m_mtxView = mtxView;}
	D3DXMATRIX GetViewMtx(){return m_mtxView;}

	void SetProjMtx(const D3DXMATRIX& mtxProj){m_mtxProj = mtxProj;}

	// Gets the transformation matrices
	const D3DXMATRIX& GetWorldMtx() const {return m_mtxWorld;}
	const D3DXMATRIX& GetViewMtx() const {return m_mtxView;}
	const D3DXMATRIX& GetProjdMtx() const {return m_mtxProj;}

	void SetTexture(int iIdx, ID3D10ShaderResourceView* pTexShaderView);
	void SetTextureArray(ID3D10ShaderResourceView** ppTexShaderView, UINT uiCount)
	{
		m_pTexturesVar->SetResourceArray(ppTexShaderView, 0, uiCount);
	}

	void SetNumActiveTexture(int texCount, int iCurrent);

	// Sends transformation matrix data to the shaders
	void UpdateMatrices();

	// Shutdown
	void DestroyAll();
	~cGraphicsLayer();
	
	/**
	 * Initialization calls.
	 */
	void InitD3D(int width, int height);
	void CreateDeviceAndSwapChain();
	void CreateViewport();
	void CreateDebugText();
	void CreateDepthStencilBuffer();
	void CreateDefaultShader();

	/**
	 * This function uses Direct3DX to write text to the back buffer.
	 * Its much faster than using the GDI
	 */
	void DrawTextString(int x, int y, D3DXCOLOR color, const TCHAR* str);

	ID3D10EffectTechnique* GetDefaultTechnique() const {return m_pDefaultTechnique;}
	ID3D10Effect* GetDefaultEffect() const {return m_pDefaultEffect;}

	HWND GetHWnd(){return m_hWnd;}

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

	// Clears the depth/stencil buffer
	void ClearDepthStencil(const float fDepth, const UINT8 uiStencil);

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
