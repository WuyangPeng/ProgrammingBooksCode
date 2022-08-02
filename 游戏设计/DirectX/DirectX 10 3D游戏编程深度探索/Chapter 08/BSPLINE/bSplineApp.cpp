/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "../math3d/color3.h"
#include "bspline.h"

// the thing that dances around
class cBSplineTrail
{
	vector< cGraphicsLayer::cDefaultVertex >	m_vertList;
	cBSpline m_spline;

	/**
	 * Generate a point somewhere between (-10,-10,-10), (10,10,10)
	 */
	point3 GenRandomPoint()
	{
		float scale = 10.f;
		return point3(
			scale * (float)(rand()-(RAND_MAX/2)) / (RAND_MAX/2),
			scale * (float)(rand()-(RAND_MAX/2)) / (RAND_MAX/2),
			scale * (float)(rand()-(RAND_MAX/2)) / (RAND_MAX/2));
	}

public:

	cBSplineTrail()
	{
		m_spline.AddCtrlPoint( GenRandomPoint() );
		m_spline.AddCtrlPoint( GenRandomPoint() );
		m_spline.AddCtrlPoint( GenRandomPoint() );
		m_spline.AddCtrlPoint( GenRandomPoint() );

		m_currStep = 0;
		m_nSteps = 30;
		m_startPoint = 0;
		m_trailLength = 200;

		m_pVertexBuffer = NULL;
	}

	~cBSplineTrail()
	{
		if(m_pVertexBuffer)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer = 0;
		}
	}

	color3 m_tipColor;
	color3 m_mainColor;
	int m_currStep;
	int m_nSteps;
	int m_startPoint;
	int m_trailLength;

	void Process();
	void Draw();

	ID3D10Buffer* m_pVertexBuffer;
};


class cBSplineApp : public cApplication  
{
	cBSplineTrail	m_redTrail;
	cBSplineTrail	m_greenTrail;
	cBSplineTrail	m_blueTrail;
	cBSplineTrail	m_magentaTrail;
	cBSplineTrail	m_cyanTrail;
	cBSplineTrail	m_yellowTrail;

public:

	cBSplineApp() :
		cApplication()
	{
		m_title = wstring( L"BSpline Sample" );
	}
	~cBSplineApp()
	{
	}

	virtual void SceneInit();
	virtual void DoFrame( float timeDelta );
};

cApplication* CreateApplication()
{
	return new cBSplineApp();
}


/**
 * EachFrame: Perform processing on our trails and draw them
 */
void cBSplineApp::DoFrame( float timeDelta )
{
	ID3D10Device* pDevice = Graphics()->GetDevice();

	static float yaw = 0.f;
	static float pitch = 0.f;
	static float roll = 0.f;
	static float dist = 11.0f;

	// process the trails
	m_blueTrail.Process();
	m_redTrail.Process();
	m_greenTrail.Process();
	m_magentaTrail.Process();
	m_cyanTrail.Process();
	m_yellowTrail.Process();

	// rotate things around a little
	yaw += timeDelta * 0.8f;
	pitch += timeDelta* 0.35f;

	D3DXMATRIX objMat;
	D3DXMatrixIdentity(&objMat);
	D3DXMatrixRotationYawPitchRoll(&objMat, yaw, pitch, roll);
	D3DXMATRIX transMat;
	D3DXMatrixTranslation(&transMat, 0.0f, 0.0f, dist);
	objMat += transMat;

	Graphics()->SetWorldMtx( objMat );
	// then, draw the frame.
	Graphics()->UpdateMatrices();
	Graphics()->UpdateLights();

	// Clear the previous contents of the backbuffer
	float colClear[4] = {0.1f, 0.1f, 0.1f, 1.0f};
	Graphics()->Clear(colClear);
	Graphics()->ClearDepthStencil(1.0f, 0);

	m_blueTrail.Draw();
	m_redTrail.Draw();
	m_greenTrail.Draw();
	m_magentaTrail.Draw();
	m_cyanTrail.Draw();
	m_yellowTrail.Draw();

	// flip the buffer.
	Graphics()->Present();
}

void cBSplineApp::SceneInit()
{
	m_blueTrail.m_mainColor = color3::Blue;
	m_blueTrail.m_tipColor = color3::Yellow * 1.0f + color3::Blue*0.8f;

	m_redTrail.m_mainColor = color3::Red;
	m_redTrail.m_tipColor = color3::Yellow * 1.0f + color3::Blue*0.8f;

	m_greenTrail.m_mainColor = color3::Green;
	m_greenTrail.m_tipColor = color3::Yellow * 1.0f + color3::Blue*0.8f;

	m_magentaTrail.m_mainColor = color3::Magenta;
	m_magentaTrail.m_tipColor = color3::Yellow * 1.0f + color3::Blue*0.8f;

	m_cyanTrail.m_mainColor = color3::Cyan;
	m_cyanTrail.m_tipColor = color3::Yellow * 1.0f + color3::Blue*0.8f;

	m_yellowTrail.m_mainColor = color3::Yellow;
	m_yellowTrail.m_tipColor = color3::Yellow * 1.0f + color3::Blue*0.8f;
}


void cBSplineTrail::Process()
{
	// calculate the next step
	float t = (float)m_currStep/m_nSteps;

	cGraphicsLayer::cDefaultVertex tempVertex;
	tempVertex.m_vPosition = *(D3DXVECTOR3*)&(m_spline.Calc(t, m_spline.NumPoints()-4));
	tempVertex.m_vColor = m_tipColor.MakeDWord();
	tempVertex.m_TexCoords = D3DXVECTOR2(0,0);
	tempVertex.m_vNormal = D3DXVECTOR3(0,0,0);

	m_vertList.push_back(tempVertex);

	if( m_currStep++ == m_nSteps )
	{
		m_currStep = 0;
		m_spline.AddCtrlPoint( GenRandomPoint() );
	}

	int i;
	t = 0.f;
	for( i=(int)m_vertList.size()-(m_trailLength-40); i>=0 && i>(int)m_vertList.size()-m_trailLength; i-- )
	{
		// color the trailing 40 vertices black
		m_vertList[i].m_vColor = (color3::Black * t + m_mainColor * (1-t)).MakeDWord();
		t += 1.f/41.f;
	}

	t = 0.f;
	for( i=(int)m_vertList.size()-1; i>=0 && i>(int)m_vertList.size()-20; i-- )
	{
		// color the trailing 20 vertices black
		m_vertList[i].m_vColor = (m_mainColor * t + m_tipColor* (1-t)).MakeDWord();
		t += 1.f/21.f;
	}

	m_startPoint = m_vertList.size()-m_trailLength;
	if( m_startPoint < 0 ) 
		m_startPoint = 0;


}

void cBSplineTrail::Draw()
{
	ID3D10Buffer* pVertexBuffer = NULL;

	D3D10_BUFFER_DESC descBuffer;
	memset(&descBuffer, 0, sizeof(descBuffer));
    descBuffer.Usage = D3D10_USAGE_DEFAULT;
	descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * (m_vertList.size() - m_startPoint - 1);
    descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    descBuffer.CPUAccessFlags = 0;
    descBuffer.MiscFlags = 0;

	D3D10_SUBRESOURCE_DATA resData;
	memset(&resData, 0, sizeof(resData));
    resData.pSysMem = &m_vertList[m_startPoint];

	if(descBuffer.ByteWidth == 0)
	{
		return;
	}

	Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &pVertexBuffer);

	if(pVertexBuffer)
	{
		UINT uiOffset = 0;
		UINT uiStride = sizeof(cGraphicsLayer::cDefaultVertex);
		Graphics()->GetDevice()->IASetVertexBuffers(0, 1, &pVertexBuffer, &uiStride, &uiOffset);

		if(m_pVertexBuffer)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer = NULL;
		}
		
		m_pVertexBuffer = pVertexBuffer;
		Graphics()->GetDevice()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

		D3D10_TECHNIQUE_DESC descTechnique;
		Graphics()->GetDefaultTechnique()->GetDesc(&descTechnique);
		for(UINT uiCurPass = 0; uiCurPass < descTechnique.Passes; uiCurPass++)
		{		
			Graphics()->GetDefaultTechnique()->GetPassByIndex(uiCurPass)->Apply(0);
			Graphics()->GetDevice()->Draw((m_vertList.size() - m_startPoint - 1), 0);
		}		
	}
}

