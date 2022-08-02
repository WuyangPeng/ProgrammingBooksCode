/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#include "stdafx.h"
#include <assert.h>
#include "MsgDaemon.h"

cMsgDaemon* cMsgDaemon::m_pGlobalMsgDaemon = NULL;

cMsgDaemon::cMsgDaemon()
{
}

cMsgDaemon::~cMsgDaemon()
{
	// iterate and destroy all the objects?
}



void cMsgDaemon::RegObject( objID id, iGameObject* pObj )
{
	/**
	 * We must have unique ID's for each object.
	 */
	assert( m_objectMap[ id ] == NULL );

	m_objectMap[ id ] = pObj;
}



void cMsgDaemon::UnRegObject( objID id )
{
	m_objectMap[ id ] = NULL;
}



UINT cMsgDaemon::DeliverMessage( const sMsg& msg )
{
	// Make sure there isn't a bogus receiver
	assert( g_invalidID != msg.m_dest );

	iGameObject* pDest = m_objectMap[ msg.m_dest ];
	if( pDest == NULL )
	{
		TCHAR buff[1024];
		swprintf_s( buff, 1024, L"Message %d sent to non-existent object %d",
			msg.m_type, msg.m_dest );
		throw cGameError( buff );
	}
	return pDest->ProcMsg( msg );
}



void DebPrint( TCHAR* first, ... )
{
	TCHAR buff[1024];

	va_list marker;

	va_start( marker, first );     /* Initialize variable arguments. */

	vswprintf_s( buff, 1024, first, marker );

	va_end( marker );              /* Reset variable arguments.      */

	// g_gameServer is the same for the server and the client.
	SendMessage( sMsg( msgPrintString, g_gameServer, buff ) );
}

void LogPrint( TCHAR* first, ... )
{
	TCHAR buff[1024];

	va_list marker;

	va_start( marker, first );     /* Initialize variable arguments. */

	vswprintf_s( buff, 1024, first, marker );

	va_end( marker );              /* Reset variable arguments.      */

	static bool bFirst = true;
	static FILE* fp;
	if( bFirst )
	{
		bFirst = false;

		if( IsClient() )
		{
			fopen_s( &fp, "clientLog.txt", "w" );
			fprintf( fp, "Log file for Client\n===============================\n" );
		}
		else
		{
			fopen_s(&fp, "serverLog.txt", "w" );
			fprintf( fp, "Log file for Server\n===============================\n" );
		}
	}
	fwprintf( fp, buff );
	fprintf( fp, "\n" );
	fflush(fp);
}


cGameWorld* GetWorld()
{
	iGameObject* pObj = MsgDaemon()->Get( g_gameWorldID );
	return (cGameWorld*) pObj;
}


void ReliableSendToPlayer( cNetMessage& nMsg, objID player )
{
	sMsg msg;
	msg.m_pData = &nMsg;
	msg.m_i[1] = player;
	msg.m_type = msgSendNetMessageR;
	msg.m_dest = g_gameServer;
	SendMessage( msg );
}

void UnreliableSendToPlayer( cNetMessage& nMsg, objID player )
{
	sMsg msg;
	msg.m_pData = &nMsg;
	msg.m_i[1] = player;
	msg.m_type = msgSendNetMessageUR;
	msg.m_dest = g_gameServer;
	SendMessage( msg );
}

void UnreliableBroadcast( cNetMessage& nMsg )
{
	sMsg msg;
	msg.m_pData = &nMsg;
	msg.m_type = msgBroadcastUR;
	msg.m_dest = g_gameServer;
	SendMessage( msg );
}

void ReliableBroadcast( cNetMessage& nMsg )
{
	sMsg msg;
	msg.m_pData = &nMsg;
	msg.m_type = msgBroadcastR;
	msg.m_dest = g_gameServer;
	SendMessage( msg );
}

void ReliableBroadcastExcept( cNetMessage& nMsg, objID exception )
{
	sMsg msg;
	msg.m_pData = &nMsg;
	msg.m_i[1] = exception;
	msg.m_type = msgBroadcastRExcept;
	msg.m_dest = g_gameServer;
	SendMessage( msg );
}


