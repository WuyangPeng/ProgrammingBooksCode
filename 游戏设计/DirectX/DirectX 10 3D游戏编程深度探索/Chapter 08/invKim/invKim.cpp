/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"

#include <string>
using std::string;

class cIKApp : public cApplication,
	public iKeyboardReceiver,
	public iMouseReceiver
{

public:

	/**
	 * Lengths of the two links
	 */
	float m_l1, m_l2;

	/**
	 * Angles of the two joings
	 */
	float m_theta1, m_theta2;

	/**
	 * Location in worldspace of the end effector
	 */
	point3 m_endEffector;

	/**
	 * Location in worldspace of the grey diamond
	 * that the end effector trails after
	 */
	point3 m_mouse;

	/**
	 * how long the last frame took (the next one should take about as long)
	 */
	float m_timeDelta;

	/**
	 * If this is true, draw some help on the screen
	 */
	bool m_drawHelp;


	//==========--------------------------  cApplication

	virtual void DoFrame( float timeDelta );
	virtual void SceneInit();

	cIKApp() :
		cApplication()
	{
		m_title = wstring( L"Inverse Kinematics Sample App" );

		m_pJointVertexBuffer = NULL;
		m_pArmVertexBuffer = NULL;
		m_pDiamondVertexBuffer = NULL;
	}

	~cIKApp() 
	{
		m_title = wstring( L"Inverse Kinematics Sample App" );

		if(m_pJointVertexBuffer)
		{
			m_pJointVertexBuffer->Release();
			m_pJointVertexBuffer = NULL;
		}
	
		if(m_pArmVertexBuffer)
		{
			m_pArmVertexBuffer->Release();
			m_pArmVertexBuffer = NULL;
		}
		if(m_pDiamondVertexBuffer)
		{
			m_pDiamondVertexBuffer->Release();
			m_pDiamondVertexBuffer = NULL;
		}
	}

	virtual void InitInput()
	{
		// force exclusive access to the mouse
		cInputLayer::Create( AppInstance(), MainWindow()->GetHWnd(), true, true, true );
	}


	//==========--------------------------  iKeyboardReceiver

	virtual void KeyUp( int key );
	virtual void KeyDown( int key ){}

	//==========--------------------------  iMouseReceiver

	virtual void MouseMoved( int dx, int dy );
	virtual void MouseButtonUp( int button ){}
	virtual void MouseButtonDown( int button ){}

	//==========--------------------------  cIKApp

	void DrawLinkage();
	void FindJointAngles( float x, float y );

	ID3D10Buffer* m_pJointVertexBuffer;
	ID3D10Buffer* m_pArmVertexBuffer;
	ID3D10Buffer* m_pDiamondVertexBuffer;
};

cApplication* CreateApplication()
{
	return new cIKApp();
}

void DestroyApplication( cApplication* pApp )
{
	delete pApp;
}

void cIKApp::SceneInit()
{
	ID3D10Device* pDevice = Graphics()->GetDevice();

	/**
	 * Tell the keyboard object to send us state
	 * changes.
	 */
	Input()->GetKeyboard()->SetReceiver( this );
	Input()->GetMouse()->SetReceiver( this );

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

	D3DXMATRIX transMat;
	D3DXMatrixTranslation(&transMat, 0, 0, 15);
	Graphics()->SetWorldMtx(transMat);

	m_drawHelp = false;

	m_timeDelta = 0.03f; // a 30th of a second is a good first value

	m_l1 = 10.0;
	m_l2 = 8.0;
	m_endEffector = point3(5,5,0);
	m_mouse = point3(5,5,0);
	m_theta1 = 0.f;
	m_theta2 = 0.f;
}


void cIKApp::DoFrame( float timeDelta )
{
	/**
	 * update the time
	 */
	m_timeDelta = timeDelta;
	
	/**
	 * then, draw the frame.
	 */
	ID3D10Device* pDevice = Graphics()->GetDevice();
	if( pDevice )
	{
		Graphics()->UpdateMatrices();
		Graphics()->UpdateLights();

		// Clear the previous contents of the backbuffer
		float colClear[4] = {0.1f, 0.1f, 0.1f, 1.0f};
		Graphics()->Clear(colClear);
		Graphics()->ClearDepthStencil(1.0f, 0);

		/**
		 * Move the joints towards the mouse
		 */
		point3 dir = m_mouse - m_endEffector;
		float mag = dir.Mag();
		if( mag > 0.1f )
		{
			dir /= mag;
			Snap( mag, 0.f, 1.f );
			m_endEffector += 10.f * m_timeDelta * mag * dir;
		}

		/**
		 * Compute the theta angles for the
		 * new position of the end effector
		 */
		FindJointAngles( m_endEffector.x, m_endEffector.y );

		/**
		 * Draw the linkage
		 */
		DrawLinkage();

		/**
		 * flip the buffer.
		 */
		Graphics()->Present();
	}
}


void cIKApp::KeyUp( int key )
{
	if( key == DIK_H )
	{
		m_drawHelp = !m_drawHelp;
	}
}


void cIKApp::MouseMoved( int dx, int dy )
{
	m_mouse.x += dx * 0.1f;
	m_mouse.y -= dy * 0.1f;
}

void cIKApp::DrawLinkage()
{
	/**
	 * Use the lengths and theta information
	 * to compute the forward dynamics of 
	 * the arm, and draw it.
	 */
	cGraphicsLayer::cDefaultVertex box[5];
	cGraphicsLayer::cDefaultVertex joint[20];
	matrix4 rot1, trans1;
	matrix4 rot2, trans2;

	/**
	 * create a half circle to give our links rounded edges
	 */
	point3 halfCircle[10];
	int i;
	for( i=0; i<10; i++ )
	{
		float theta = (float)i*PI/9.0f;
		halfCircle[i] = point3(
			0.85f * sin( theta ),
			0.85f * cos( theta ),
			0.f );
	}

	rot1.ToZRot( m_theta1 );
	trans1.ToTranslation( point3( m_l1,0, 0 ) );

	rot2.ToZRot( m_theta2 );

	ID3D10Device* pDevice = Graphics()->GetDevice();

	/**
	 * Make and draw the upper arm
	 */
	matrix4 shoulderMat = rot1;
	for( i=0; i<10; i++ )
	{
		point3 temp = halfCircle[i];
		temp.x = -temp.x;
		
		cGraphicsLayer::cDefaultVertex tempVertex;
		tempVertex.m_vPosition = *(D3DXVECTOR3*)&(shoulderMat * temp);
		tempVertex.m_vNormal = D3DXVECTOR3(0,0,0);
		tempVertex.m_vColor = D3DXCOLOR(1, 0, 0, 1);
		tempVertex.m_TexCoords = D3DXVECTOR2(0,0);
		
		joint[i] = tempVertex;

		tempVertex.m_vPosition = *(D3DXVECTOR3*)&(shoulderMat * (halfCircle[i] + point3( m_l1, 0, 0 )));
		tempVertex.m_vColor = D3DXCOLOR(1, 1, 0, 1);

		joint[19-i] = tempVertex;
	}

	ID3D10Buffer* pJointVertexBuffer = NULL;

	D3D10_BUFFER_DESC descBuffer;
	memset(&descBuffer, 0, sizeof(descBuffer));
    descBuffer.Usage = D3D10_USAGE_DEFAULT;
	descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * 20;
    descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    descBuffer.CPUAccessFlags = 0;
    descBuffer.MiscFlags = 0;

	D3D10_SUBRESOURCE_DATA resData;
	memset(&resData, 0, sizeof(resData));
    resData.pSysMem = joint;

	if(descBuffer.ByteWidth == 0)
	{
		return;
	}
	
	Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &pJointVertexBuffer);

	if(pJointVertexBuffer)
	{
		UINT uiOffset = 0;
		UINT uiStride = sizeof(cGraphicsLayer::cDefaultVertex);
		Graphics()->GetDevice()->IASetVertexBuffers(0, 1, &pJointVertexBuffer, &uiStride, &uiOffset);

		if(m_pJointVertexBuffer)
		{
			m_pJointVertexBuffer->Release();
			m_pJointVertexBuffer = NULL;
		}
		
		m_pJointVertexBuffer = pJointVertexBuffer;
		Graphics()->GetDevice()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

		D3D10_TECHNIQUE_DESC descTechnique;
		Graphics()->GetDefaultTechnique()->GetDesc(&descTechnique);
		for(UINT uiCurPass = 0; uiCurPass < descTechnique.Passes; uiCurPass++)
		{		
			Graphics()->GetDefaultTechnique()->GetPassByIndex(uiCurPass)->Apply(0);
			Graphics()->GetDevice()->Draw(20, 0);
		}		
	}
	
	/**
	 * Make and draw the lower arm
	 */
	matrix4 elbowMat = rot2 * trans1 * rot1;
	for( i=0; i<10; i++ )
	{
		point3 temp = halfCircle[i];
		temp.x = -temp.x;
		
		cGraphicsLayer::cDefaultVertex tempVertex;
		tempVertex.m_vPosition = *(D3DXVECTOR3*)&(elbowMat * temp);
		tempVertex.m_vNormal = D3DXVECTOR3(0,0,0);
		tempVertex.m_vColor = D3DXCOLOR(1, 0, 1, 1);
		tempVertex.m_TexCoords = D3DXVECTOR2(0,0);
		
		joint[i] = tempVertex;

		tempVertex.m_vPosition = *(D3DXVECTOR3*)&(elbowMat * (halfCircle[i] + point3( m_l2, 0, 0.f )));
		tempVertex.m_vColor = D3DXCOLOR(0, 0, 1, 1);

		joint[19-i] = tempVertex;
	}


	ID3D10Buffer* pArmVertexBuffer = NULL;

	memset(&descBuffer, 0, sizeof(descBuffer));
    descBuffer.Usage = D3D10_USAGE_DEFAULT;
	descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * 20;
    descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    descBuffer.CPUAccessFlags = 0;
    descBuffer.MiscFlags = 0;

	memset(&resData, 0, sizeof(resData));
    resData.pSysMem = joint;

	if(descBuffer.ByteWidth == 0)
	{
		return;
	}
	
	Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &pArmVertexBuffer);

	if(pArmVertexBuffer)
	{
		UINT uiOffset = 0;
		UINT uiStride = sizeof(cGraphicsLayer::cDefaultVertex);
		Graphics()->GetDevice()->IASetVertexBuffers(0, 1, &pArmVertexBuffer, &uiStride, &uiOffset);

		if(m_pArmVertexBuffer)
		{
			m_pArmVertexBuffer->Release();
			m_pArmVertexBuffer = NULL;
		}
		
		m_pArmVertexBuffer = pArmVertexBuffer;
		Graphics()->GetDevice()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

		D3D10_TECHNIQUE_DESC descTechnique;
		Graphics()->GetDefaultTechnique()->GetDesc(&descTechnique);
		for(UINT uiCurPass = 0; uiCurPass < descTechnique.Passes; uiCurPass++)
		{		
			Graphics()->GetDefaultTechnique()->GetPassByIndex(uiCurPass)->Apply(0);
			Graphics()->GetDevice()->Draw(19, 0);
		}		
	}

	/**
	 * Draw a diamond where the mouse is
	 */
	matrix4 mouseTrans;
	mouseTrans.ToTranslation( m_mouse );
	
	cGraphicsLayer::cDefaultVertex tempVertex;

	tempVertex.m_vNormal = D3DXVECTOR3(0,0,0);
	tempVertex.m_vColor = tempVertex.m_vColor = D3DXCOLOR(0, 1, 1, 1);;
	tempVertex.m_TexCoords = D3DXVECTOR2(0,0);
	
	tempVertex.m_vPosition = *(D3DXVECTOR3*)&(point3(0.5f,0.f,0.f) * mouseTrans);
	box[0] = tempVertex;

	tempVertex.m_vPosition = *(D3DXVECTOR3*)&(point3(0.f,-0.5f,0.f) * mouseTrans);
	box[1] = tempVertex;

	tempVertex.m_vPosition = *(D3DXVECTOR3*)&(point3(-0.5f,0.f,0.f) * mouseTrans);
	box[2] = tempVertex;

	tempVertex.m_vPosition = *(D3DXVECTOR3*)&(point3(0.f,0.5f,0.f) * mouseTrans);
	box[3] = tempVertex;

	box[4] = box[0];

	ID3D10Buffer* pDiamondVertexBuffer = NULL;

	memset(&descBuffer, 0, sizeof(descBuffer));
    descBuffer.Usage = D3D10_USAGE_DEFAULT;
	descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * 5;
    descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    descBuffer.CPUAccessFlags = 0;
    descBuffer.MiscFlags = 0;

	memset(&resData, 0, sizeof(resData));
    resData.pSysMem = box;

	if(descBuffer.ByteWidth == 0)
	{
		return;
	}
	
	Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &pDiamondVertexBuffer);

	if(pDiamondVertexBuffer)
	{
		UINT uiOffset = 0;
		UINT uiStride = sizeof(cGraphicsLayer::cDefaultVertex);
		Graphics()->GetDevice()->IASetVertexBuffers(0, 1, &pDiamondVertexBuffer, &uiStride, &uiOffset);

		if(m_pDiamondVertexBuffer)
		{
			m_pDiamondVertexBuffer->Release();
			m_pDiamondVertexBuffer = NULL;
		}
		
		m_pDiamondVertexBuffer = pDiamondVertexBuffer;
		Graphics()->GetDevice()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

		D3D10_TECHNIQUE_DESC descTechnique;
		Graphics()->GetDefaultTechnique()->GetDesc(&descTechnique);
		for(UINT uiCurPass = 0; uiCurPass < descTechnique.Passes; uiCurPass++)
		{		
			Graphics()->GetDefaultTechnique()->GetPassByIndex(uiCurPass)->Apply(0);
			Graphics()->GetDevice()->Draw(5, 0);
		}		
	}
}

void cIKApp::FindJointAngles( float x, float y )
{
	float minD = (float)fabs(m_l1 - m_l2 );
	float maxD = m_l1 + m_l2;

	float L1 = m_l1;
	float L2 = m_l2;

	/**
	 * Find the standard theta and distance
	 */
	float dist = (float)sqrt(x*x+y*y);
	float theta = (float)atan2(y,x);

	/**
	 * Snap the distance to values we can reach
	 */
	Snap( dist, minD + EPSILON, maxD - EPSILON );

	/**
	 * Adjust the x and y to match the new distance
	 */
	x = (float)cos(theta)*dist;
	y = (float)sin(theta)*dist;

	/**
	 * Find thetaHat using the law of cosines
	 */

	float thetaHat = (float)acos( ( L2*L2 - L1*L1 - dist*dist ) / (-2*dist*L1) );

	/**
	 * theta - thetaHat is theta 1
	 */
	m_theta1 = theta - thetaHat;

	/**
	 * Use the law of cosines to get thetaArm
	 */
	float thetaArm = (float)acos( ( dist*dist - L1*L1 - L2*L2 ) / (-2*L2*L1) );

	/**
	 * With thetaArm we can easily find theta2
	 */
	m_theta2 = PI-thetaArm;

}