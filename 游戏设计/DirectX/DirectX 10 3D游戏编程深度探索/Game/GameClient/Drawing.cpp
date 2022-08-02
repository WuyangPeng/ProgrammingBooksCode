/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/
// Drawing code

#include "stdafx.h"

extern int g_useTextures;

ID3D10Buffer* g_BufferBackup = NULL;

bool DrawCell( cGameCell* pCell )
{
	static cGraphicsLayer::cDefaultVertex v[32];

	int i,j;

	ID3D10Device* pDevice = Graphics()->GetDevice();

	//if( g_useTextures )
	//{
	//	pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	//	pDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	//	pDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	//}

//	Graphics()->SetWorldMtx( matrix4::Identity );

	int nPolys = pCell->m_polyList.size();
	for( i=0; i<nPolys; i++ )
	{
		/**
		 * Set up the texture.
		 */

		if( g_useTextures )
		{
			cTexture* pTex = (cTexture*)Resources()->Get( 
				pCell->m_polyList[i].m_texID );
			Graphics()->SetTexture( 0, pTex->GetShaderView() );
		}

		/**
		 * Cycle around the polygon grabbing the vertices
		 */
		int destCount = 0;
		int nVerts = pCell->m_polyList[i].m_nVerts;
		for( j=0; j<nVerts; j++ )
		{

			cGraphicsLayer::cDefaultVertex tempVertex;

			tempVertex.m_vPosition = *(D3DXVECTOR3*)&pCell->m_ptList[ pCell->m_polyList[i].m_vList[j].m_ind ];
			tempVertex.m_vColor = D3DXCOLOR(pCell->m_polyList[i].m_vList[j].m_col);
			tempVertex.m_vNormal = D3DXVECTOR3(0,0,0);
			tempVertex.m_TexCoords[0] = D3DXVECTOR2(
				pCell->m_polyList[i].m_vList[j].m_u,
				pCell->m_polyList[i].m_vList[j].m_v );

			v[destCount] = tempVertex;
			destCount++;

			if(j %3 == 0)
			{
				v[destCount++] = v[0];
			}

			
				
			/*sLitVertex(
				pCell->m_ptList[ pCell->m_polyList[i].m_vList[j].m_ind ],
				pCell->m_polyList[i].m_vList[j].m_col,
				0,
				pCell->m_polyList[i].m_vList[j].m_u,
				pCell->m_polyList[i].m_vList[j].m_v );*/
		}

		/**
		 * Draw the polygon
		 */

		ID3D10Buffer* pVertexBuffer = NULL;

		D3D10_BUFFER_DESC descBuffer;
		memset(&descBuffer, 0, sizeof(descBuffer));
		descBuffer.Usage = D3D10_USAGE_DEFAULT;
		descBuffer.ByteWidth = sizeof(cGraphicsLayer::cDefaultVertex) * (destCount);
		descBuffer.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		descBuffer.CPUAccessFlags = 0;
		descBuffer.MiscFlags = 0;
	   
		D3D10_SUBRESOURCE_DATA resData;
		memset(&resData, 0, sizeof(resData));
		resData.pSysMem = v;
		Graphics()->GetDevice()->CreateBuffer(&descBuffer, &resData, &pVertexBuffer);


		UINT uiStride = sizeof(cGraphicsLayer::cDefaultVertex);
		UINT uiOffset = 0;
		Graphics()->GetDevice()->IASetVertexBuffers(0, 1, &pVertexBuffer, &uiStride, &uiOffset);
		Graphics()->GetDevice()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		if(g_BufferBackup)
		{
			g_BufferBackup->Release();
			g_BufferBackup = NULL;
		}
		g_BufferBackup = pVertexBuffer;
	 
		D3D10_TECHNIQUE_DESC descTechnique;
		Graphics()->GetDefaultTechnique()->GetDesc(&descTechnique);
		for(UINT uiCurPass = 0; uiCurPass < descTechnique.Passes; uiCurPass++)
		{		
			Graphics()->GetDefaultTechnique()->GetPassByIndex(uiCurPass)->Apply(0);
			Graphics()->GetDevice()->Draw(destCount, 0);
		}

		/*pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 );

		pDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			pCell->m_polyList[i].m_nVerts - 2,
			v,
			sizeof( sLitVertex ) );*/

	}


	return true;
}


bool DrawEnt( cGameEnt* pEnt )
{
	if( pEnt->GetStatus() == gesMortis )
	{
		DebPrint(L"Mortis object found");
	}

	/**
	 * Switch based on the segment constants
	 */
	int iEdID = pEnt->GetID();
	int iSegment = GetIDSegment( iEdID );
	switch( iSegment )
	{

	case c_spawnSegment:
		// don't draw spawn ents.
		{
			pEnt->RebuildMatrix();
			matrix4 mat = pEnt->GetMatrix();
			cModel* pModel = (cModel*)Resources()->Get(303);

			if( g_useTextures )
			{
				cTexture* pTex = (cTexture*)Resources()->Get(111);
				Graphics()->SetTexture( 0, pTex->GetShaderView() );
			}

			Graphics()->SetWorldMtx(*(D3DXMATRIX*)&mat);
			Graphics()->UpdateMatrices();
			pModel->Draw();
			
			break;
		}
		break;

	case c_playerSegment:
		// If it isn't us, Then draw it.
		if( pEnt->GetID() != GetClientID() )
		{
			pEnt->RebuildMatrix();
			matrix4 mat = pEnt->GetMatrix();
			cModel* pModel = (cModel*)Resources()->Get(303);

			if( g_useTextures )
			{
				cTexture* pTex = (cTexture*)Resources()->Get(111);
				Graphics()->SetTexture( 0, pTex->GetShaderView() );
			}
			
			Graphics()->SetWorldMtx(*(D3DXMATRIX*)&mat);
			Graphics()->UpdateMatrices();
			pModel->Draw();
			break;
		}
		break;

	case c_projSegment:
		{
			if( pEnt->GetStatus() == gesAlive )
			{
				pEnt->RebuildMatrix();
				matrix4 mat = pEnt->GetMatrix();
				cModel* pModel = (cModel*)Resources()->Get(304);

				if( g_useTextures )
				{
					cTexture* pTex = (cTexture*)Resources()->Get(112);
					Graphics()->SetTexture( 0, pTex->GetShaderView() );
				}
					
				Graphics()->SetWorldMtx(*(D3DXMATRIX*)&mat);
				Graphics()->UpdateMatrices();
				pModel->Draw();
			}
		}
		break;

	default:
		LogPrint(L"Bad object to draw");
		break;
	}
	return true;
}


void InitLights()
{
	Graphics()->AddLight(D3DXCOLOR(1,1,1,1), D3DXVECTOR3(0,1,0));
	//LPDIRECT3DDEVICE9 pDevice = Graphics()->GetDevice();
 //   
 //   sLight light;

	//// Light 0
	//light = sLight::Directional( 
	//	point3(0,-4,2).Normalized(),
	//	0.7f * color3::White,
	//	color3::Black,
	//	0.5f * color3::White);

 //   // Set the light
 //   pDevice->SetLight( 0, &light );
	//pDevice->LightEnable(0, TRUE);

 //   sMaterial mat( 
	//	0.f, 
	//	color3(0.8f,0.8f,0.8f),
	//	color3(0.4f,0.4f,0.4f),
	//	color3(0.5f,0.5f,0.5f) );

 //   pDevice->SetMaterial(&mat);
}