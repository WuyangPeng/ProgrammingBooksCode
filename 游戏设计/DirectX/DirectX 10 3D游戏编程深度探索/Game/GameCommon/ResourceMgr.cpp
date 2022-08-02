/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include "ResourceMgr.h"
#include "..\gamelib\file.h"

extern int g_useTextures;

#pragma warning(disable : 4996)
/**
 * instantiation of the global pointer to the resource manager.
 */
cResourceMgr* cResourceMgr::m_pGlobalResourceMgr = NULL;

cResourceMgr::cResourceMgr()
{
	if( m_pGlobalResourceMgr )
		throw cGameError( L"cResourceMgr object already created!\n" );
	m_pGlobalResourceMgr = this;
}

cResourceMgr::cResourceMgr( TCHAR* resFile )
{
	if( m_pGlobalResourceMgr )
		throw cGameError( L"cResourceMgr object already created!\n" );
	m_pGlobalResourceMgr = this;

	cFile file;

  try
  {
    file.Open( resFile );
  }
  catch( cFileCannotCreate )
  {
    throw cGameError( L"cResourceMgr could not locate the resource file!\n" );
  }

	TCHAR buff[1024];
	TCHAR type[1024];
	TCHAR filename[256];
	int id;
	// first line is RES_BEGIN
	file.ReadNonCommentedLine( buff, '#' );		
	while( 1 )
	{
		file.ReadNonCommentedLine( buff, '#' );		

		//swscanf_s( buff, L"%s", type );
		if( wcsstr( buff, L"RES_END" ) )
			break;

		swscanf( buff, L"%s %d %s", type, &id, filename );
		if( 0 == wcscmp( L"MODEL", type ) )
		{
			float scale;
			swscanf( buff, L"%s %d %s %f", type, &id, filename, &scale );
			cModel* pModel = new cModel( filename );
			pModel->Scale( scale );
			m_resourceMap[id] = (void*)pModel;
		}
		else if( 0 == wcscmp( L"TEXTURE", type ) && g_useTextures )
		{
			cTexture* pTex = new cTexture( filename );
			m_resourceMap[id] = (void*)pTex;
		}
		else if( 0 == wcscmp( L"SOUND", type ) )
		{
			cSoundWrapper* pSound = new cSoundWrapper( filename );
			m_resourceMap[id] = (void*)pSound;
		}
	}
}

cResourceMgr::~cResourceMgr()
{
	/* iterate through the map, destroying everything. */
	map< resID, void* >::iterator iter;
	for( iter = m_resourceMap.begin();
		iter != m_resourceMap.end();
		iter++ )
	{
		delete (*iter).second;

		m_resourceMap[ (*iter).first ] = NULL;
	}

	m_pGlobalResourceMgr = NULL;
}
