/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "../math3d/point3.h"
#include "../math3d/matrix4.h"
#include "Model.h"
#include "file.h"

using namespace std;

cModel::cModel(const TCHAR* name, int nVerts, int nTris) :
	m_name(name)
{
	int i;

	m_verts.reserve(nVerts);
	cGraphicsLayer::cDefaultVertex vert;
	for(i=0; i<nVerts; i++)
	{
		m_verts.push_back(vert);
	}

	m_tris.reserve(nTris);
	sTri tri;
	for(i=0; i<nTris; i++)
	{
		m_tris.push_back(tri);
	}

	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
}

cModel::~cModel()
{
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
}


cModel::cModel(const TCHAR* filename)
{
	int i;

	cFile file;
	file.Open(filename);

	queue<wstring> m_tokens;

	file.TokenizeNextNCLine(&m_tokens, '#');

	// first token is the name.
	m_name = m_tokens.front();
	m_tokens.pop();

	// next is the # of fields in the vertex info
	int nVertexFields = _wtoi(m_tokens.front().c_str());
	m_tokens.pop();

	// next is the triangle offset
	int offset = _wtoi(m_tokens.front().c_str());
	m_tokens.pop();

	// next is the # of vertices
	int nVerts = _wtoi(m_tokens.front().c_str());
	m_tokens.pop();

	// next is the # of triangles
	int nTris = _wtoi(m_tokens.front().c_str());
	m_tokens.pop();

	if(!m_tokens.empty())
	{
		// additional info in the header
	}

	// Reserve space in the vector for all the verts.
	// This will speed up all the additions, since only
	// one resize will be done.
	m_verts.reserve(nVerts);
	for(i=0; i<nVerts; i++)
	{
		//while(!m_tokens.empty()) m_tokens.pop();
		file.TokenizeNextNCLine(&m_tokens, '#');

		cGraphicsLayer::cDefaultVertex curr;

		// Vertex data is guarenteed
		curr.m_vPosition.x = (float)_wtof(m_tokens.front().c_str());
		m_tokens.pop();
		curr.m_vPosition.y = (float)_wtof(m_tokens.front().c_str());
		m_tokens.pop();
		curr.m_vPosition.z = (float)_wtof(m_tokens.front().c_str());
		m_tokens.pop();

		// hack to load color
		if(nVertexFields == 4)
		{
			curr.m_vColor = D3DXCOLOR(_wtoi( m_tokens.front().c_str() ));

			m_tokens.pop();
		}


		// Load normal data if nfields is 6 or 8
		if(nVertexFields == 6 || nVertexFields == 8)
		{
			curr.m_vNormal.x = (float)_wtof(m_tokens.front().c_str());
			m_tokens.pop();
			curr.m_vNormal.y = (float)_wtof(m_tokens.front().c_str());
			m_tokens.pop();
			curr.m_vNormal.z = (float)_wtof(m_tokens.front().c_str());
			m_tokens.pop();
		}
		else
		{
			curr.m_vNormal = D3DXVECTOR3(0, 0, 0);
		}

		// Load texture data if nfields is 5 or 8
		if(nVertexFields == 5 || nVertexFields == 8)
		{
			curr.m_TexCoords[0].x = (float)_wtof(m_tokens.front().c_str());
			m_tokens.pop();
			curr.m_TexCoords[0].y = (float)_wtof(m_tokens.front().c_str());
			m_tokens.pop();
		}
		else
		{
			curr.m_TexCoords[0].x = 0.f;
			curr.m_TexCoords[0].y = 0.f;
		}

		m_verts.push_back(curr);
	}

	// Reserve space in the vector for all the verts.
	// This will speed up all the additions, since only
	// one resize will be done.
	m_tris.reserve(nTris);
	for(i=0; i<nTris; i++)
	{
		m_tokens.empty();
		file.TokenizeNextNCLine(&m_tokens, '#');

		sTri tri;

		// vertex data is guaranteed
		tri.v[0] = _wtoi(m_tokens.front().c_str()) - offset;
		m_tokens.pop();
		tri.v[1] = _wtoi(m_tokens.front().c_str()) - offset;
		m_tokens.pop();
		tri.v[2] = _wtoi(m_tokens.front().c_str()) - offset;
		m_tokens.pop();

		m_tris.push_back(tri);
	}

	if(nVertexFields == 3 || nVertexFields == 4 || nVertexFields == 5)
	{
		// Normals weren't provided.  Generate our own.

		// First set all the normals to zero.
		for(i=0; i<nVerts; i++)
		{
			m_verts[i].m_vNormal = D3DXVECTOR3(0,0,0);
		}

		// Then go through and add each triangle's normal 
		// to each of it's verts.
		for(i=0; i<nTris; i++)
		{
			plane3 plane(
				m_verts[ m_tris[i].v[0] ].m_vPosition,
				m_verts[ m_tris[i].v[1] ].m_vPosition,
				m_verts[ m_tris[i].v[2] ].m_vPosition);

			m_verts[ m_tris[i].v[0] ].m_vNormal += D3DXVECTOR3(plane.n.x, plane.n.y, plane.n.z);
			m_verts[ m_tris[i].v[1] ].m_vNormal += D3DXVECTOR3(plane.n.x, plane.n.y, plane.n.z);
			m_verts[ m_tris[i].v[2] ].m_vNormal += D3DXVECTOR3(plane.n.x, plane.n.y, plane.n.z);
		}

		// Finally normalize all of the normals
		for(i=0; i<nVerts; i++)
		{
			D3DXVec3Normalize(&m_verts[i].m_vNormal, &m_verts[i].m_vNormal);
		}
	}

	// Setup vertex and index buffers
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;

	D3D10_BUFFER_DESC descBuffer;
	memset(&descBuffer, 0, sizeof(descBuffer));
    descBuffer.Usage = D3D10_USAGE_DEFAULT;
	descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * NumVerts();
    descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    descBuffer.CPUAccessFlags = 0;
    descBuffer.MiscFlags = 0;
   
	D3D10_SUBRESOURCE_DATA resData;
	memset(&resData, 0, sizeof(resData));
    resData.pSysMem = &m_verts[0];
	Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &m_pVertexBuffer);

	descBuffer.Usage = D3D10_USAGE_DEFAULT;
    descBuffer.ByteWidth = sizeof(WORD) * NumTris() * 3;        
    descBuffer.BindFlags = D3D10_BIND_INDEX_BUFFER;
    descBuffer.CPUAccessFlags = 0;
    descBuffer.MiscFlags = 0;
    resData.pSysMem = &m_tris[0];
    Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &m_pIndexBuffer);    
}

void cModel::Scale(float amt)
{
	int size = m_verts.size();
	for(int i=0; i<size; i++)
	{
		D3DXVec3Scale(&m_verts[i].m_vPosition, &m_verts[i].m_vPosition, amt);
	}
}

void cModel::Draw()
{
	UINT uiStride = sizeof(cGraphicsLayer::cDefaultVertex);
	UINT uiOffset = 0;
	
    Graphics()->GetDevice()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &uiStride, &uiOffset);
    Graphics()->GetDevice()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    Graphics()->GetDevice()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Graphics()->GetDevice()->DrawIndexed(m_tris.size() * 3, 0, 0);
}


float cModel::GenRadius()
{
	float best = 0.f;
	int size = m_verts.size();
	for(int i=0; i<size; i++)
	{
		float curr = D3DXVec3Length(&m_verts[i].m_vPosition);
		if(curr > best)
			best = curr;
	}
	return best;
}