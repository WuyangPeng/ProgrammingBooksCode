/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"

#include <string>
#include <vector>
using namespace std;

class cMultiTexApp : public cApplication,
	public iKeyboardReceiver
{

public:

	ID3D10Buffer* m_pSphereVertexBuffer;
	ID3D10Buffer* m_pCloudVertexBuffer;

	ID3D10EffectTechnique* m_pTechnique;

	float m_timeDelta;

	matrix4	m_earthMat;
	matrix4	m_cloudMat;

	vector< cGraphicsLayer::cDefaultVertex > m_earthVerts;
	vector< cGraphicsLayer::cDefaultVertex > m_cloudVerts;
	cTexture* m_pTextures[8];

	UINT m_uiCurrentPass;
	//==========--------------------------  cApplication

	virtual void DoFrame( float timeDelta );
	virtual void SceneInit();

	cMultiTexApp() :
		cApplication()
	{
		m_title = wstring( L"MultiTex madness" );

		for( int i=0; i<8; i++ )
		{
			m_pTextures[i] = NULL;
		}

		m_uiCurrentPass = 6;

		m_pSphereVertexBuffer = NULL;
		m_pCloudVertexBuffer = NULL;

		m_pTechnique = NULL;
	}

	virtual ~cMultiTexApp()
	{
		/**
		 * Delete all of the textures
		 */
		for( int i=0; i<8; i++ )
		{
			delete m_pTextures[i];
		}
	}

	virtual void KeyUp( int key );
	virtual void KeyDown( int key ){}

	void CreateSphereVertices( float radius, vector<cGraphicsLayer::cDefaultVertex>* pVec, float* scales );
	void InitLights();

	void LoadTextures();

	void DrawBackground();
};

cApplication* CreateApplication()
{
	return new cMultiTexApp();
}

void DestroyApplication( cApplication* pApp )
{
	delete pApp;
}


void cMultiTexApp::SceneInit()
{
	Graphics()->AddLight(D3DXCOLOR(0.9f, 0.9f, 0.5f, 1.0f), D3DXVECTOR3(1,1,0));

	m_pTechnique = Graphics()->GetDefaultEffect()->GetTechniqueByName("MultiTexTechnique");
	if(!m_pTechnique)
		return;

	/**
	 * Request keyboard updates
	 */
	Input()->GetKeyboard()->SetReceiver( this );

	/**
	 * initialize our scene
	 */
	ID3D10Device* pDevice = Graphics()->GetDevice();

	/**
	 * initialize the camera
	 * the 'up' vector is tilted to make the earth appear off-axis
	 */
	Graphics()->SetViewMtx( 
		*(D3DXMATRIX*)&matrix4::CameraLookAt(
			point3(4, 10, -15 ), 
			point3(0,0,0) )
	);
	Graphics()->UpdateMatrices();

	m_timeDelta = 0.03f; // a 30th of a second is a good first value

	float scales[2] = {1.0f, 11.0f};
	CreateSphereVertices( 10.f, &m_earthVerts, &scales[0] );
	CreateSphereVertices( 10.2f, &m_cloudVerts, &scales[0] );

	{
		D3D10_BUFFER_DESC descBuffer;
		memset(&descBuffer, 0, sizeof(descBuffer));
		descBuffer.Usage = D3D10_USAGE_DEFAULT;
		descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * (m_cloudVerts.size() - 2);
		descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		descBuffer.CPUAccessFlags = 0;
		descBuffer.MiscFlags = 0;
	   
		D3D10_SUBRESOURCE_DATA resData;
		memset(&resData, 0, sizeof(resData));
		resData.pSysMem = &m_earthVerts[0];
		Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &m_pSphereVertexBuffer);
	}

	/*{	
		D3D10_BUFFER_DESC descBuffer;
		memset(&descBuffer, 0, sizeof(descBuffer));
		descBuffer.Usage = D3D10_USAGE_DEFAULT;
		descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * m_uiSphereVertexCount;
		descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		descBuffer.CPUAccessFlags = 0;
		descBuffer.MiscFlags = 0;
	   
		D3D10_SUBRESOURCE_DATA resData;
		memset(&resData, 0, sizeof(resData));
		resData.pSysMem = &m_earthVerts;
		Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &m_pCloudVertexBuffer);
	}*/


	InitLights();
	LoadTextures();

}

void cMultiTexApp::DoFrame( float timeDelta )
{
	/**
	 * update the time
	 */
	m_timeDelta = timeDelta;
	
	static float rotAmt = 3*PI/4;
	rotAmt += 0.75f * m_timeDelta;

	float colClear[4] = {0.0f, 0.0f, 0.6f, 1.0f};
	Graphics()->Clear(colClear);
	Graphics()->ClearDepthStencil(1.0f, 0);

	Graphics()->UpdateMatrices();

	/**
	 * then, draw the frame.
	 */

	ID3D10ShaderResourceView* pViews[8];
	for(UINT uiCurTex = 0 ; uiCurTex < 8 ; uiCurTex++)
	{
		pViews[uiCurTex] = m_pTextures[uiCurTex]->GetShaderView();
	}

	Graphics()->SetTextureArray(pViews, 8);	
	DrawBackground();
	Graphics()->SetTextureArray(pViews, 8);	
	

	point3 from( 0, 1, 0 );

	m_earthMat = 
		matrix4::AxisAngle( point3::j, rotAmt );

	/**
	 * The cloud matrix rotates a tiny bit faster
	 * than the earth matrix
	 */
	m_cloudMat = 
		matrix4::AxisAngle( point3::j, rotAmt * 0.7f );

	Graphics()->SetWorldMtx( *(D3DXMATRIX*)&m_earthMat );
	Graphics()->UpdateMatrices();

	Graphics()->SetNumActiveTexture(8, 0);

	UINT uiStride = sizeof(cGraphicsLayer::cDefaultVertex);
	UINT uiOffset = 0;
	
	Graphics()->GetDevice()->IASetVertexBuffers(0, 1, &m_pSphereVertexBuffer, &uiStride, &uiOffset);
	Graphics()->GetDevice()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D10_TECHNIQUE_DESC descTechnique;
	m_pTechnique->GetDesc(&descTechnique);
	for(UINT uiCurPass = 0; uiCurPass < descTechnique.Passes; uiCurPass++)
	{	
		m_pTechnique->GetPassByIndex(uiCurPass)->Apply(0);
		Graphics()->GetDevice()->Draw(m_cloudVerts.size() - 2, 0);
	}

	Graphics()->Present();
}

void cMultiTexApp::KeyUp( int key )
{
	if( key == DIK_1 )
	{
		m_uiCurrentPass++;
		if(m_uiCurrentPass >= 6)
			m_uiCurrentPass = 0;
	}
}


void cMultiTexApp::InitLights()
{
	
}


/**
 * Based off of InitSphereVertices from the
 * BumpEarth D3D SDK application
 */
void cMultiTexApp::CreateSphereVertices( float radius, vector<cGraphicsLayer::cDefaultVertex>* pVec, float* scales )
{
    int numSphereRings    = 30;
    int numSphereSegments = 30;

	cGraphicsLayer::cDefaultVertex curr;
	int i;

    // Establish constants used in sphere generation
    float fDeltaRingAngle = ( PI / numSphereRings );
    float fDeltaSegAngle  = ( 2.0f * PI / numSphereSegments );

    // Generate the group of rings for the sphere
    for( int ring = 0; ring < numSphereRings; ring++ )
    {    
        float r0 = (float)sin( (ring+0) * fDeltaRingAngle );
        float r1 = (float)sin( (ring+1) * fDeltaRingAngle );
        float y0 = (float)cos( (ring+0) * fDeltaRingAngle );
        float y1 = (float)cos( (ring+1) * fDeltaRingAngle );

        // Generate the group of segments for the current ring
        for( int seg = 0; seg < (numSphereSegments+1); seg++ )
        {
            float x0 =  r0 * (float)sin( seg * fDeltaSegAngle );
            float z0 =  r0 * (float)cos( seg * fDeltaSegAngle );
            float x1 =  r1 * (float)sin( seg * fDeltaSegAngle );
            float z1 =  r1 * (float)cos( seg * fDeltaSegAngle );

			curr.m_vPosition = *(D3DXVECTOR3*)&(radius * point3(x0,y0,z0));
			curr.m_vNormal = curr.m_vPosition;
			curr.m_vColor = D3DXCOLOR(1,1,1,1);
			
			D3DXVec3Normalize(&curr.m_vNormal, &curr.m_vNormal);
			
			for( i=0; i<2; i++ )
			{
				curr.m_TexCoords[i].x = scales[i] * -((FLOAT)seg)/numSphereSegments;
				curr.m_TexCoords[i].y = scales[i] * ((ring+0)/(FLOAT)numSphereRings);
			}
			pVec->push_back( curr );

			curr.m_vPosition = *(D3DXVECTOR3*)&(radius * point3(x1,y1,z1));
			curr.m_vNormal = curr.m_vPosition;
			
			D3DXVec3Normalize(&curr.m_vNormal, &curr.m_vNormal);
			
			for( i=0; i<2; i++ )
			{
				curr.m_TexCoords[i].x = scales[i] * -((FLOAT)seg)/numSphereSegments;
				curr.m_TexCoords[i].y = scales[i] * ((ring+1)/(FLOAT)numSphereRings);
			}
			pVec->push_back( curr );
        }
    }
}


void cMultiTexApp::LoadTextures()
{
	TCHAR* names[8] = { 
		L"..\\bin\\media\\earth.dds", 
		L"..\\bin\\media\\glowmap.dds", 
		L"..\\bin\\media\\detail.dds", 
		L"..\\bin\\media\\space.dds",
		L"..\\bin\\media\\glossmap.dds",
		L"..\\bin\\media\\stars.bmp",
		L"..\\bin\\media\\earthmask.dds",
		L"..\\bin\\media\\clouds.dds",
	};

	for( int i=0; i<8; i++ )
	{
		m_pTextures[i] = new cTexture( names[i], i);
	}
}

/**
 * Draw a simple background.
 * uses the camera's location to set itself
 * up so that it's always facing towards
 * the viewer.
 */
void cMultiTexApp::DrawBackground()
{
	Graphics()->SetNumActiveTexture(1, 1);

	ID3D10ShaderResourceView* pView = m_pTextures[3]->GetShaderView();
	Graphics()->SetTextureArray(&pView, 1);

	static bool bFirst = true;

	static ID3D10Buffer* pVertexBuffer = NULL;

	D3DXMATRIX worldMat;
	D3DXMatrixIdentity(&worldMat);

	matrix4 mat = *(matrix4*)&Graphics()->GetViewMtx();

	matrix4 viewInv;
	viewInv.ToInverse( mat );

	Graphics()->SetWorldMtx( *(D3DXMATRIX*)&viewInv );
	Graphics()->UpdateMatrices();

	if(bFirst)
	{
		point3 v[4];
		v[0] =  point3( -150,  150, 80.f );
		v[1] =  point3(  150,  150, 80.f );
		v[2] =  point3(  150, -150, 80.f );
		v[3] =  point3( -150, -150, 80.f );

		cGraphicsLayer::cDefaultVertex square[6];

		square[0].m_vPosition = *(D3DXVECTOR3*)&v[0];
		square[0].m_vColor = D3DXCOLOR(1,1,1,1);
		square[0].m_vNormal = D3DXVECTOR3(0,0,0);
		square[0].m_TexCoords[0] = D3DXVECTOR2(0.0f, 0.0f);
		square[0].m_TexCoords[1] = D3DXVECTOR2(0.0f, 0.0f);

		square[1].m_vPosition = *(D3DXVECTOR3*)&v[1];
		square[1].m_vColor = D3DXCOLOR(1,1,1,1);
		square[1].m_vNormal = D3DXVECTOR3(0,0,0);
		square[1].m_TexCoords[0] = D3DXVECTOR2(1.0f, 0.0f);
		square[1].m_TexCoords[1] = D3DXVECTOR2(1.0f, 0.0f);

		square[2].m_vPosition = *(D3DXVECTOR3*)&v[2];
		square[2].m_vColor = D3DXCOLOR(1,1,1,1);
		square[2].m_vNormal = D3DXVECTOR3(0,0,0);
		square[2].m_TexCoords[0] = D3DXVECTOR2(1.0f, 1.0f);
		square[2].m_TexCoords[1] = D3DXVECTOR2(1.0f, 1.0f);

		square[3].m_vPosition = *(D3DXVECTOR3*)&v[0];
		square[3].m_vColor = D3DXCOLOR(1,1,1,1);
		square[3].m_vNormal = D3DXVECTOR3(0,0,0);
		square[3].m_TexCoords[0] = D3DXVECTOR2(0.0f, 0.0f);
		square[3].m_TexCoords[1] = D3DXVECTOR2(0.0f, 0.0f);

		square[4].m_vPosition = *(D3DXVECTOR3*)&v[2];
		square[4].m_vColor = D3DXCOLOR(1,1,1,1);
		square[4].m_vNormal = D3DXVECTOR3(0,0,0);
		square[4].m_TexCoords[0] = D3DXVECTOR2(1.0f, 1.0f);
		square[4].m_TexCoords[1] = D3DXVECTOR2(1.0f, 1.0f);

		square[5].m_vPosition = *(D3DXVECTOR3*)&v[3];
		square[5].m_vColor = D3DXCOLOR(1,1,1,1);
		square[5].m_vNormal = D3DXVECTOR3(0,0,0);
		square[5].m_TexCoords[0] = D3DXVECTOR2(0.0f, 1.0f);
		square[5].m_TexCoords[1] = D3DXVECTOR2(0.0f, 1.0f);

		
		D3D10_BUFFER_DESC descBuffer;
		memset(&descBuffer, 0, sizeof(descBuffer));
		descBuffer.Usage = D3D10_USAGE_DEFAULT;
		descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * 6;
		descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		descBuffer.CPUAccessFlags = 0;
		descBuffer.MiscFlags = 0;
	   
		D3D10_SUBRESOURCE_DATA resData;
		memset(&resData, 0, sizeof(resData));
		resData.pSysMem = &square;
		Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &pVertexBuffer);

		bFirst = false;
	}

	if(pVertexBuffer)
	{
		UINT uiStride = sizeof(cGraphicsLayer::cDefaultVertex);
		UINT uiOffset = 0;
		
		Graphics()->GetDevice()->IASetVertexBuffers(0, 1, &pVertexBuffer, &uiStride, &uiOffset);
		Graphics()->GetDevice()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D10_TECHNIQUE_DESC descTechnique;
		Graphics()->GetDefaultTechnique()->GetDesc(&descTechnique);
		for(UINT uiCurPass = 0; uiCurPass < descTechnique.Passes; uiCurPass++)
		{	
			Graphics()->GetDefaultTechnique()->GetPassByIndex(uiCurPass)->Apply(0);
			Graphics()->GetDevice()->Draw(6, 0);
		}
	}
}